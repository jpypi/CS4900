/*

Author: Aleksandr Dobrev <aleksandr.a.dobrev@wmich.edu>

Last major update: 2017-05-01

*/

// Disable Error C4996 that occur when using Boost.Signals2.
#ifdef _DEBUG
#define _SCL_SECURE_NO_WARNINGS
#endif

// === DEVELOPMENT INFORMATION SWITCHES === 
#define SWITCH_TIMER__STDOUT					1	//Timer status updates to STDOUT.
#define SWITCH_DEBUG_GENERAL__STDOUT			1	//General Debug updates to STDOUT.
#define SWITCH_DEBUG_CLOUDSIZE__STDOUT			0	//Cloud size changes updates to STDOUT
#define SWITCH_DEBUG_FUNCTION_STATUS__STDOUT	0	//Function vulnerable calls updates to STDOUT.

// === OTHER SWITCHES ===
#define SWITCH_SAVE_POINTCLOUDS_TO_FILE			0	// Save point clouds to file.

#include "kinect2_grabber.h"
#include <pcl/visualization/pcl_visualizer.h>
///////////////////////////
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/passthrough.h>
#include <pcl/features/normal_3d.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/common/common.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/common/centroid.h>
#include <pcl/common/eigen.h>
#include <pcl/point_cloud.h>

#include "ToolBox.h";
#include "shared.h"

//==========================================================
// Global variables

//Used for writing Point Clouds and other debugging features
PointCloudWriter pcw = PointCloudWriter();
Timer timer = Timer();

//Temporary obstacles storage.
#define MAX_OBSTACLES 3
Obstacle obstacles[MAX_OBSTACLES];
Obstacle obstacle_largest_plane;
//----------------------------------------------------------

/*
Function: initializePlanarSegmentation
> Description
This function initializes a SACSegmentationFromNormals and
a ModelCoefficients object which will be used later for
plane segmentation. It configures those objects based on
initialization information in this funcion.

> Arguments
[IN/OUT] pcl::SACSegmentationFromNormals<PointType, pcl::Normal> *plane_seg
[IN/OUT] pcl::ModelCoefficients::Ptr plane

> Returns:
N/A
*/
void initializePlanarSegmentation(pcl::SACSegmentationFromNormals<PointType, pcl::Normal> *plane_seg, pcl::ModelCoefficients::Ptr plane){
	plane->values.resize(4); //make room for a plane equation (zx+by+cz+d=0);

	plane_seg->setOptimizeCoefficients(true);
	plane_seg->setModelType(pcl::SACMODEL_NORMAL_PLANE);
	plane_seg->setNormalDistanceWeight(0.1);
	plane_seg->setMethodType(pcl::SAC_RANSAC);
	plane_seg->setMaxIterations(100);
	//Modify Threshold for sensitivity (distance between points) of point grouping.
	plane_seg->setDistanceThreshold(0.05f);
}

/*
Function: initializeCylinderSegmentation
> Description
This function initializes a SACSegmentationFromNormals and 
a ModelCoefficients object which will be used later for
Cylinder segmentation. It configures those objects based on 
initialization information in this funcion.

> Arguments
[IN/OUT] pcl::SACSegmentationFromNormals<PointType, pcl::Normal> *cylinder_seg
[IN/OUT] pcl::ModelCoefficients::Ptr cylinder

> Returns:
N/A
*/
void initializeCylinderSegmentation(pcl::SACSegmentationFromNormals<PointType, pcl::Normal> *cylinder_seg, pcl::ModelCoefficients::Ptr cylinder) {
	cylinder_seg->setOptimizeCoefficients(true);
	cylinder_seg->setModelType(pcl::SACMODEL_CYLINDER);
	cylinder_seg->setMethodType(pcl::SAC_RANSAC);
	cylinder_seg->setNormalDistanceWeight(0.1);
	cylinder_seg->setMaxIterations(100);
	cylinder_seg->setDistanceThreshold(0.05);
	cylinder_seg->setRadiusLimits(0.02, 0.45);
}

/*
Function: planarSegmentation
> Description
This function segments a plane from a given point cloud
and Normalized point cloud, and a plane segmenatation
model.

> Arguments
[IN] PointCloudT::ConstPtr cloud
- Input cloud.
[IN] pcl::PointCloud<pcl::Normal>::Ptr cloud_normals
- Input point cloud normals to input cloud.
[IN] pcl::ModelCoefficients::Ptr plane
- Model of a plane to search for to be segmented.
[OUT] pcl::PointIndices::Ptr inliers_plane
- Indinces representing the plane segmented.
[IN] pcl::SACSegmentationFromNormals<PointType, pcl::Normal> *plane_seg
- Object used for plane segmentation containing plane
segmentation filter.


> Returns:
- (int) Error code of function.
*/
int planarSegmentation(PointCloudT::ConstPtr cloud, pcl::PointCloud<pcl::Normal>::Ptr cloud_normals, pcl::ModelCoefficients::Ptr plane, pcl::PointIndices::Ptr	inliers_plane, pcl::SACSegmentationFromNormals<PointType, pcl::Normal> *plane_seg ){
	//Set cloud & normals for processing.
	plane_seg->setInputCloud(cloud);
	plane_seg->setInputNormals(cloud_normals);

	//Segment the largest plane in cloud.
	if (SWITCH_DEBUG_FUNCTION_STATUS__STDOUT) std::cerr << "STATUS: Planar Segmentation STARTED" << std::endl;
	plane_seg->segment(*inliers_plane, *plane);
	if (SWITCH_DEBUG_FUNCTION_STATUS__STDOUT) std::cerr << "STATUS: Planar Segmentation FINISHED " << std::endl;

	//Check if a planar model was found.
	if (inliers_plane->indices.size() == 0) {
		if (SWITCH_DEBUG_FUNCTION_STATUS__STDOUT) std::cerr << "STATUS: Failed to estimate a planar model for the given dataset." << std::endl;
		return(-1);
	}
	else {
		return(0);
	}
}

/*
Function: cylinderSegmentation
> Description
This function segments a cylinder from a given point cloud 
and Normalized point cloud, and a cylinder segmenatation 
model.

> Arguments
[IN] PointCloudT::ConstPtr cloud
- Input cloud.
[IN] pcl::PointCloud<pcl::Normal>::Ptr cloud_normals
- Input point cloud normals to input cloud.
[IN] pcl::ModelCoefficients::Ptr cylinder
- Model of a cylinder to search for to be segmented.
[OUT] pcl::PointIndices::Ptr inliers_cylinder
- Indinces representing the cylinder segmented.
[IN] pcl::SACSegmentationFromNormals<PointType, pcl::Normal> *cylinder_seg
- Object used for cylinder segmentation containing cylinder
	segmentation filter.


> Returns:
- (int) Error code of function.
*/
int cylinderSegmentation(PointCloudT::ConstPtr cloud, pcl::PointCloud<pcl::Normal>::Ptr cloud_normals, pcl::ModelCoefficients::Ptr cylinder, pcl::PointIndices::Ptr inliers_cylinder, pcl::SACSegmentationFromNormals<PointType, pcl::Normal> *cylinder_seg) {
	//Set cloud for processing.
	cylinder_seg->setInputCloud(cloud);
	cylinder_seg->setInputNormals(cloud_normals);

	//Segment the largest plane in cloud.
	if (SWITCH_DEBUG_FUNCTION_STATUS__STDOUT) std::cerr << "STATUS: Cylinder Segmentation STARTED" << std::endl;
	cylinder_seg->segment(*inliers_cylinder, *cylinder);
	if (SWITCH_DEBUG_FUNCTION_STATUS__STDOUT) std::cerr << "STATUS: Cylinder Segmentation FINISHED" << std::endl;

	if (inliers_cylinder->indices.size() == 0) {
		if (SWITCH_DEBUG_FUNCTION_STATUS__STDOUT) std::cerr << "STATUS: Failed to estimate a cylinder model for the given dataset." << std::endl;
		return(-1);
	}
	else {
		return(0);
	}
}

/*
Function: planarExtraction
> Description
This function extracts a plane from an input cloud and 
stores the plane inliers and plane outliers in new seperate 
point clouds. The point indices representing the plane 
inliers are provided as an arg.

> Arguments
[IN] PointCloudT::ConstPtr cloud
- Input cloud.
[OUT] PointCloudT::ConstPtr plane_cloud_inliers
- Point cloud with the plane.
[OUT] PointCloudT::ConstPtr plane_cloud_outliers
- Point cloud without the plane.
[IN] pcl::PointIndices::Ptr inliers_plane
- Point indinces of the plane that needs to be extracted.

> Returns:
N/A
*/
void planarExtraction(PointCloudT::ConstPtr cloud, PointCloudT::Ptr plane_cloud_inliers, PointCloudT::Ptr plane_cloud_outliers, pcl::PointIndices::Ptr inliers_plane){
	//Extract inliers
	pcl::ExtractIndices<PointType> extract;
	extract.setInputCloud(cloud);
	extract.setIndices(inliers_plane);
	extract.setNegative(false);	//Extract the inliers
	extract.filter(*plane_cloud_inliers); //plane_cloud_inliers contains the plane.

	//Extract outliers
	extract.setNegative(true); //Extract the outliers
	extract.filter(*plane_cloud_outliers); //cloud outliers contains everything BUT the plane.

	if (SWITCH_DEBUG_CLOUDSIZE__STDOUT) std::cerr << "PointCloud without plane: " << plane_cloud_outliers->points.size() << " data points." << std::endl;
}

/*
Function: cylinderExtraction
> Description
This function extracts a cylinder from an input cloud and
stores the cylinder inliers and cylinder outliers in new seperate
point clouds. The point indices representing the cylinder
inliers are provided as an arg.

> Arguments
[IN] PointCloudT::ConstPtr cloud
- Input cloud.
[OUT] PointCloudT::ConstPtr cylinder_cloud_inliers
- Point cloud with the cylinder.
[OUT] PointCloudT::ConstPtr cylinder_cloud_outliers
- Point cloud without the cylinder.
[IN] pcl::PointIndices::Ptr inliers_cylinder
- Point indinces of the cylinder that needs to be extracted.

> Returns:
N/A
*/
void cylinderExtraction(PointCloudT::ConstPtr cloud, PointCloudT::Ptr cylinder_cloud_inliers, PointCloudT::Ptr cylinder_cloud_outliers, pcl::PointIndices::Ptr inliers_cylinder) {
	//Extract inliers
	pcl::ExtractIndices<PointType> extract;
	extract.setInputCloud(cloud);
	extract.setIndices(inliers_cylinder);
	extract.setNegative(false);	//Extract the inliers
	extract.filter(*cylinder_cloud_inliers); //cylinder_cloud_inliers contains the cylinder.

	//Extract outliers
	//extract.setNegative(true); //Extract the outliers
	//extract.filter(*cylinder_cloud_outliers); //cloud outliers contains everything BUT the cylinder.

	if (SWITCH_DEBUG_CLOUDSIZE__STDOUT) std::cerr << "PointCloud without cylinder: " << cylinder_cloud_outliers->points.size() << " data points." << std::endl;
}

/*
Function: estimatePointNormals
> Description
This function calculates an estimate of the normalized 
point values in a given point cloud.

> Arguments
[IN] PointCloudT::ConstPtr cloud
- Input cloud.
[OUT] pcl::PointCloud<pcl::Normal>::Ptr cloud_normals
- Output pointcloud with point normals as points.
[IN] pcl::NormalEstimation<PointType, pcl::Normal>::Ptr normal_estimation
- Normal Estimation object.

> Returns:
N/A
*/
void estimatePointNormals(PointCloudT::ConstPtr cloud, pcl::PointCloud<pcl::Normal>::Ptr cloud_normals, pcl::NormalEstimation<PointType, pcl::Normal>::Ptr normal_estimation) {
	pcl::search::KdTree<PointType>::Ptr kdtree;
	
	normal_estimation->setSearchMethod(kdtree);
	normal_estimation->setInputCloud(cloud);
	//normal_estimation->setRadiusSearch(0.02);
	normal_estimation->setKSearch(50);

	if (SWITCH_DEBUG_FUNCTION_STATUS__STDOUT) std::cerr << "Point Normal estimation started" << std::endl;
	normal_estimation->compute(*cloud_normals);
	if (SWITCH_DEBUG_FUNCTION_STATUS__STDOUT) std::cerr << "Point Normal estimation finished" << std::endl;
}
 
/*
Function: filterNans
> Description
This function removes invalid (NaN) points from an input 
point cloud.

> Arguments
[IN] PointCloudT::ConstPtr unfiltered_cloud
- Input cloud.
[OUT] PointCloudT::Ptr cloud
- Output cloud after NaNs are removed.

> Returns:
N/A
*/
void filterNans(PointCloudT::ConstPtr unfiltered_cloud, PointCloudT::Ptr cloud) {
	std::vector<int> indexes;
	
	if (SWITCH_DEBUG_CLOUDSIZE__STDOUT) std::cerr << "PointCloud before NAN filtering has: " << unfiltered_cloud->points.size() << " data points." << std::endl;
	pcl::removeNaNFromPointCloud(*unfiltered_cloud, *cloud, indexes);
	if (SWITCH_DEBUG_CLOUDSIZE__STDOUT) std::cerr << "PointCloud after NAN filtering has: " << cloud->points.size() << " data points." << std::endl;
}

/*
Function: downsamplePointCloud
> Description
This function uses a voxel grid to downsample the input 
point cloud.

> Arguments
[IN] PointCloudT::Ptr cloud
- Input cloud.
[OUT] PointCloudT::Ptr filtered_cloud
- Output cloud after downsampling.

> Returns:
N/A
*/
void downsamplePointCloud(PointCloudT::Ptr cloud, PointCloudT::Ptr downsampled_cloud) {

	//Instantiate an object for filtering.
	pcl::VoxelGrid<PointType> vgrid;

	if (SWITCH_DEBUG_CLOUDSIZE__STDOUT) std::cerr << "PointCloud before downsampling (voxelGrid) has: " << cloud->points.size() << " data points." << std::endl;

	vgrid.setInputCloud(cloud);

	//**** Higher values = smaller point cloud. (More points filtered) ****
	//vgrid.setLeafSize(0.259f, 0.259f, 0.259f);
	//vgrid.setLeafSize(0.199f, 0.199f, 0.199f); //Current
	vgrid.setLeafSize(0.179f, 0.179f, 0.179f); //Current
	//vgrid.setLeafSize(0.103f, 0.103f, 0.103f);
	//vgrid.setLeafSize(0.095f, 0.095f, 0.095f); //GOOD
	//vgrid.setLeafSize(0.089f, 0.089f, 0.089f); //GOOD
	//vgrid.setLeafSize(0.068f, 0.068f, 0.068f);
	//vgrid.setLeafSize(0.018f, 0.018f, 0.018f);
	vgrid.filter(*downsampled_cloud);

	if (SWITCH_DEBUG_CLOUDSIZE__STDOUT) std::cerr << "PointCloud after downsampling (voxelGrid) has: " << downsampled_cloud->points.size() << " data points." << std::endl;
}

/*
Function: filterMaxDistance
> Description
This function filters the input cloud up to a set min and 
max depth values. Basically removes anything closer/beyond 
the set bounds

> Arguments
[IN] PointCloudT::Ptr cloud
- Input cloud.
[OUT] PointCloudT::Ptr filtered_cloud
- Output cloud after min/max distance is filtered.

> Returns:
N/A
*/
void filterMaxDistance(PointCloudT::Ptr cloud, PointCloudT::Ptr filtered_cloud) {
	pcl::PassThrough<PointType> ptf;

	if (SWITCH_DEBUG_CLOUDSIZE__STDOUT) std::cerr << "PointCloud before max distance filtering has: " << cloud->points.size() << " data points." << std::endl;

	ptf.setInputCloud(cloud);
	ptf.setFilterFieldName("z");
	ptf.setFilterLimits(0.0, 6.0);
	ptf.filter(*filtered_cloud);

	if (SWITCH_DEBUG_CLOUDSIZE__STDOUT) std::cerr << "PointCloud after max distance filtering has: " << filtered_cloud->points.size() << " data points." << std::endl;
}

/*
Function: computeCentroidPoint
> Description
This function computes the centroid point from an input 
point cloud and stores it in a CoordinateXYZ struct.

> Arguments
[IN] PointCloudT::Ptr cloud
- Input cloud that represents some obstacle.

> Returns:
(struct CoordinateXYZ)
- An CoordinateXYZ struct which nicely stores X,Y,Z values 
	of the centroid point of the input cloud.
*/
struct CoordinateXYZ computeCentroidPoint(PointCloudT::Ptr cloud) {
	int num_points = cloud->points.size();
	CoordinateXYZ coords;

	std::vector<int> indices;
	Eigen::Vector4f centroid;

	pcl::compute3DCentroid(*cloud, indices, centroid);
	pcl::compute3DCentroid(*cloud, centroid);

	coords.x = centroid[0];
	coords.y = centroid[1];
	coords.z = centroid[2];

	if (SWITCH_DEBUG_GENERAL__STDOUT) std::cout << "Centroid XYZ coordinates are ( " << centroid[0] << ", " << centroid[1] << ", " << centroid[2] << " )" << std::endl;

	return coords;
}

/*
Function: computeObstacleInformation
> Description
This function creates an Obstacle struct given an input
point cloud and returns the corresponding Obstacle struct 
representing that point cloud.

> Arguments
[IN] PointCloudT::Ptr cloud
- Input cloud that represents some obstacle.

> Returns:
(struct Obstacle)
	- An obstacle containing information from point cloud.
*/
struct Obstacle computeObstacleInformation(PointCloudT::Ptr cloud) {
	Obstacle obstacle;
	CoordinateXYZ coords;

	PointType min_pt;
	PointType max_pt;

	//get min & max xyz values.
	pcl::getMinMax3D(*cloud, min_pt, max_pt); 
	//Fill Obstacle struct with data.
	obstacle.z_min = min_pt.z;
	obstacle.y_min = min_pt.y;
	obstacle.x_min = min_pt.x;
	obstacle.z_max = max_pt.z;
	obstacle.y_max = max_pt.y;
	obstacle.x_max = max_pt.x;

	//Get centroid point of cloud.
	coords = computeCentroidPoint(cloud); //compute centroid of cloud and store in Obstacle struct.
	//Fill Obstacle struct with centroid data.
	obstacle.centroid_x = coords.x;
	obstacle.centroid_y = coords.y;
	obstacle.centroid_z = coords.z;

	//Mark as a valid obstacle
	obstacle.valid = 'T';

	if (SWITCH_DEBUG_GENERAL__STDOUT) std::cerr << "[x]min = " << obstacle.x_min << " [x]max = " << obstacle.x_max << std::endl;
	if (SWITCH_DEBUG_GENERAL__STDOUT) std::cerr << "[y]min = " << obstacle.y_min << " [x]max = " << obstacle.y_max << std::endl;
	if (SWITCH_DEBUG_GENERAL__STDOUT) std::cerr << "[z]min = " << obstacle.z_min << " [x]max = " << obstacle.z_max << std::endl;
	
	return obstacle;
}

/*
Function: statisticalOutlierFilter
> Description
This function uses the input cloud to extract outlier 
indicies. Extracts a point cloud without the indinces and 
stores them in a temporary point cloud which overwrites 
the input point cloud provided through args.

> Arguments
[IN] PointCloudT::Ptr cloud
- Input cloud that requires outliers to be removed

> Returns:
N/A
*/
void statisticalOutlierFilter(PointCloudT::Ptr cloud) {
	PointCloudT tempcloud;

	pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
	sor.setInputCloud(cloud);
	sor.setMeanK(20);
	sor.setStddevMulThresh(0.3);
	sor.filter(tempcloud);

	//Use this if one wants to save the outliers vs inliers.
	//sor.setNegative(false);
	//sor.filter(*cloud_filtered);

	*cloud = tempcloud; //overwrite input cloud to one without outliers
}



/*
Function: euclidianClusterExtraction
> Description
This function extracts up to MAX_OBSTACLES clusters from 
input cloud and stores each cluster in a PointCloudT
pointer provided via arguments (cluster_cloud_n).

> Arguments
[IN] PointCloudT::Ptr cloud
	- Input cloud that requires euclidian cluster extraction
[OUT] PointCloudT::Ptr cluster_cloud_1
	- Output cloud
[OUT] PointCloudT::Ptr cluster_cloud_2

> Returns:
	N/A
*/
void euclidianClusterExtraction(PointCloudT::Ptr cloud, PointCloudT::Ptr cluster_cloud_1, PointCloudT::Ptr cluster_cloud_2) {

	pcl::search::KdTree<PointType>::Ptr kdtree (new pcl::search::KdTree<PointType>);
	std::vector<pcl::PointIndices> cluster_indices;
	pcl::EuclideanClusterExtraction<PointType> ecluster;

	kdtree->setInputCloud(cloud);
	
	//ecluster.setClusterTolerance(0.07); //2cm = 0.02
	//ecluster.setClusterTolerance(0.09);
	//ecluster.setClusterTolerance(0.10);
	ecluster.setClusterTolerance(0.21);

	ecluster.setMinClusterSize(40);	//in points
	ecluster.setMaxClusterSize(2500);
	ecluster.setSearchMethod(kdtree);

	ecluster.setInputCloud(cloud);
	ecluster.extract(cluster_indices); //extract the cloud indices.

	int suffix_c = 1;
//	int max_c = 2; //Maximum number of clusters.
	

	for (std::vector<pcl::PointIndices>::const_iterator i = cluster_indices.begin(); i < cluster_indices.end(); ++i) {
		
		PointCloudT::Ptr cluster_cloud(new PointCloudT);
 
		for (std::vector<int>::const_iterator j = i->indices.begin(); j != i->indices.end(); ++j) {
			cluster_cloud->points.push_back(cloud->points[*j]);
		}

		cluster_cloud->width = cluster_cloud->points.size();
		cluster_cloud->height = 1;
		cluster_cloud->is_dense = true;
		//cluster_cloud->is_dense = false;

		statisticalOutlierFilter(cluster_cloud); //filter outliers

		if (SWITCH_DEBUG_CLOUDSIZE__STDOUT) std::cout << "PointCloud representing the cluster has " << cluster_cloud->points.size() << " data points" << std::endl;
		
		//Save pointcloud
		if (SWITCH_SAVE_POINTCLOUDS_TO_FILE) {
			std::stringstream filename;
			filename << "cloud_cluster_" << suffix_c << ".pcd";
			pcw.savePointCloud(filename.str(), cluster_cloud);
		}

		switch (suffix_c) {
		case 1:	
			*cluster_cloud_1 = *cluster_cloud;
			if (SWITCH_DEBUG_GENERAL__STDOUT) std::cerr << "Obstacle: Cluster 1." << std::endl;
			break;
		case 2:
			*cluster_cloud_2 = *cluster_cloud;
			if (SWITCH_DEBUG_GENERAL__STDOUT) std::cerr << "Obstacle: Cluster 2." << std::endl;
			break;
		default:
			if (SWITCH_DEBUG_GENERAL__STDOUT) std::cerr << "Obstacle: UNHANDLED!" << std::endl;
			break;
		
		}

		//Save current cluster into obstacle struct and gather relevant information.
		obstacles[suffix_c - 1] = computeObstacleInformation(cluster_cloud);

		suffix_c++;

		//Loop Exit condition.
		if (suffix_c >= MAX_OBSTACLES) {
			break;
		}
	}
}

/*
Function: pathPlanner
> Description
This function calculates a very basic path towards the 
center of the largest point cloud cluster while taking in 
account all other obstacles and stopping if something is in 
the way.
- This should only be a temporary testing function until a 
	full path planning module is implemented.

> Arguments:
[IN] struct Obstacle obstacles[]
	- An array of Obstacle structs.
[OUT]: Error code

> Returns:
	- (int) Error code of function.
*/
int pathPlanner(struct Obstacle obstacles[]){
	int power = 0;
	float angle = 0.0;

	int i = 0;


	if (obstacles[0].valid == 'T') {

		power = 1;
		angle = asin(obstacles[0].centroid_x / obstacles[0].centroid_z);

		//Safety to not stress servos on vehicle
		if (angle < VEHICLE_DEGREES_MAX_LEFT)		angle = (float) VEHICLE_DEGREES_MAX_LEFT;
		else if (angle > VEHICLE_DEGREES_MAX_RIGHT) angle = (float) VEHICLE_DEGREES_MAX_RIGHT;

		for (i = 0; i < MAX_OBSTACLES && obstacles[i].valid == 'T'; i++) {
			std::cerr << "Object #" << std::endl;
			/* If the object
				is within 1 meter in Z 
				AND
				min X point is withing 1/2 WIDTH of the Vehicle OR max X point is within 1/2 WIDTH of the Vehicle
				AND
				min Y is above the lower than the highest point of the vehicle
			*/
			if (
				(obstacles[i].z_min < 1.0) &&
				( (obstacles[i].x_min < VEHICLE_RIGHT_EDGE) && (obstacles[i].x_max > VEHICLE_LEFT_EDGE) ) &&
				(obstacles[i].y_min < VEHICLE_HEIGHT)
				) {
				power = 0;
				angle = 0.0;
			}
		}
	}
	
	PCL_ERROR("PATH PLAN:");
	std::cerr << endl;
	std::cerr << "Power = " << power << "; Angle = " << angle << endl;

	return 0;
}

int main(int argc, char* argv[])
{
	//==========================================================
	// PCL Visualizer

	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(
		new pcl::visualization::PCLVisualizer("Point Cloud Visualizer"));
	viewer->setCameraPosition(0.0, 0.0, -2.5, 0.0, 0.0, 0.0);
	//----------------------------------------------------------

	//==========================================================
	//Filtering-related Objects

	pcl::NormalEstimation<PointType, pcl::Normal>::Ptr normal_estimation (new pcl::NormalEstimation<PointType, pcl::Normal>);
	//pcl::search::KdTree<PointType>::Ptr kdtree(new pcl::search::KdTree<PointType>());
	//----------------------------------------------------------

	//==========================================================
	//Point Clouds

	PointCloudT::ConstPtr	unfiltered_cloud(new PointCloudT);		//Original cloud coming from Kinect
	PointCloudT::Ptr		nonans_cloud(new PointCloudT);			//Cloud after filtered from spurious nans
	PointCloudT::Ptr		cloud (new PointCloudT);				//Cloud after filtered from max distance
	PointCloudT::Ptr		downsampled_cloud (new PointCloudT);	//Cloud after filtered by voxelgrid.

	PointCloudT::Ptr		plane_cloud_inliers(new PointCloudT);	//Cloud containing plane inliers.
	PointCloudT::Ptr		plane_cloud_outliers(new PointCloudT);	//Cloud containing plane outliers.

	PointCloudT::Ptr		cylinder_cloud_inliers(new PointCloudT);  // NIU
	PointCloudT::Ptr		cylinder_cloud_outliers(new PointCloudT); // NIU

	PointCloudT::Ptr		cluster_cloud_1 (new PointCloudT);		//Cloud containing 1st cluster.
	PointCloudT::Ptr		cluster_cloud_2(new PointCloudT);		//Cloud containing 2nd cluster

	pcl::PointCloud<pcl::Normal>::Ptr plane_cloud_normals(new pcl::PointCloud<pcl::Normal>);
	pcl::PointCloud<pcl::Normal>::Ptr cylinder_cloud_normals(new pcl::PointCloud<pcl::Normal>);
	//----------------------------------------------------------

	//==========================================================
	//Planar Segmenation Init

	pcl::ModelCoefficients::Ptr	plane(new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr		inliers_plane(new pcl::PointIndices);
	pcl::SACSegmentationFromNormals<PointType, pcl::Normal> plane_seg(new pcl::SACSegmentationFromNormals<PointType, pcl::Normal>); //Create a segmenation object.

	initializePlanarSegmentation(&plane_seg, plane);

	pcl::ModelCoefficients::Ptr	cylinder(new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr		inliers_cylinder(new pcl::PointIndices);
	pcl::SACSegmentationFromNormals<PointType, pcl::Normal> cylinder_seg(new pcl::SACSegmentationFromNormals<PointType, pcl::Normal>); //Create a segmenation object.

	initializeCylinderSegmentation(&cylinder_seg, cylinder);
	//----------------------------------------------------------

	//==========================================================
	// Temporary variables

	CoordinateXYZ temp_coords;
	//----------------------------------------------------------


	// Retrieved Point Cloud Callback Function
	boost::mutex mutex;
	boost::function<void(const pcl::PointCloud<PointType>::ConstPtr&)> function =
		[&unfiltered_cloud, &mutex](const pcl::PointCloud<PointType>::ConstPtr& ptr) {
		boost::mutex::scoped_lock lock(mutex);

		/* Point Cloud Processing */
		unfiltered_cloud = ptr->makeShared();
	};

	// Kinect2Grabber
	boost::shared_ptr<pcl::Grabber> grabber = boost::make_shared<pcl::Kinect2Grabber>();

	// Register Callback Function
	boost::signals2::connection connection = grabber->registerCallback(function);

	// Start Grabber
	grabber->start();

	while (!viewer->wasStopped()) {
		PCL_ERROR("-----NEW FRAME-----");
		std::cerr << endl;

		// Update Viewer
		viewer->spinOnce(800); //Delay.

		obstacles[0].valid = 'F';

		timer.start(); //START TIMER

		filterNans(unfiltered_cloud, nonans_cloud); //remove all NaN points from cloud.

		//Verify current pointcloud is not a NULL point cloud.
		if (nonans_cloud->points.size() > 0) {

			filterMaxDistance(nonans_cloud, cloud); //filter min/max depth.

			downsamplePointCloud(cloud, downsampled_cloud);
			//downsampled_cloud = cloud; ////FOR TESTING ONLY! Don't use unless you wise human.

			//Estimate Point Normals for the plane
			estimatePointNormals(downsampled_cloud, plane_cloud_normals, normal_estimation);

			//Plane Segmentation & Extraction (Extract only if there is something to extract).
			if (planarSegmentation(downsampled_cloud, plane_cloud_normals, plane, inliers_plane, &plane_seg) == 0) {
				planarExtraction(downsampled_cloud, plane_cloud_inliers, plane_cloud_outliers, inliers_plane);
			}

			//Temp store largest plane.
			if (SWITCH_DEBUG_GENERAL__STDOUT) std::cerr << "Obstacle: Largest Plane." << std::endl;
			obstacle_largest_plane = computeObstacleInformation(plane_cloud_inliers);
			
			//Euclidian Cluster Extraction
			euclidianClusterExtraction(plane_cloud_outliers, cluster_cloud_1, cluster_cloud_2);

			timer.stop(); // END TIMER
			if (SWITCH_TIMER__STDOUT) std::cerr << "> Time: " << timer.getTime() << " ms" << std::endl;


			boost::mutex::scoped_try_lock lock(mutex);
			pcl::visualization::PointCloudColorHandlerCustom<PointType> plane_cloud_inliers_handler(plane_cloud_inliers, 255, 20, 20);		// RED = PLANE
			pcl::visualization::PointCloudColorHandlerCustom<PointType> cluster_cloud_inliers_handler(cluster_cloud_1 , 20, 255, 20);		// GREEN = Cluster 1
			pcl::visualization::PointCloudColorHandlerCustom<PointType> cluster_cloud_inliers_handler_2(cluster_cloud_2, 20, 20, 255);		// BLUE = Cluster 2
			pcl::visualization::PointCloudColorHandlerCustom<PointType> plane_cloud_outliers_handler(plane_cloud_outliers, 200, 200, 200);	// GRAY = Everything else

			if (lock.owns_lock() && plane_cloud_inliers && plane_cloud_outliers) {
				//Update Point Cloud Viewer
				if (
					!viewer->updatePointCloud(plane_cloud_inliers, plane_cloud_inliers_handler, "plane inliers")
					|| !viewer->updatePointCloud(plane_cloud_outliers, plane_cloud_outliers_handler, "cloud outliers")
					|| !viewer->updatePointCloud(cluster_cloud_1, cluster_cloud_inliers_handler, "cluster inliers 1")
					|| !viewer->updatePointCloud(cluster_cloud_2, cluster_cloud_inliers_handler_2, "cluster inliers 2")
					) {
					viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "plane inliers");
					viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud outliers");
					viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cluster inliers 1");
					viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cluster inliers 2");

					viewer->addPointCloud(plane_cloud_inliers, plane_cloud_inliers_handler, "plane inliers");
					viewer->addPointCloud(plane_cloud_outliers, plane_cloud_outliers_handler, "cloud outliers");
					viewer->addPointCloud(cluster_cloud_1, cluster_cloud_inliers_handler, "cluster inliers 1");
					viewer->addPointCloud(cluster_cloud_1, cluster_cloud_inliers_handler_2, "cluster inliers 2");

				}
			}

			

			if (SWITCH_SAVE_POINTCLOUDS_TO_FILE) pcw.savePointCloud("Raw_PointCloud.pcd", downsampled_cloud);


		}
		// Valid + Invalid code execution section 
		pathPlanner(obstacles);
		//
	}

	// Stop Grabber
	grabber->stop();

	// Disconnect Callback Function
	if (connection.connected()) {
		connection.disconnect();
	}

	return 0;
}