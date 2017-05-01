/*
Author: Aleksandr Dobrev

Last major update: 2017-05-01
*/


#pragma once

typedef pcl::PointXYZ PointType;
typedef pcl::PointCloud<PointType> PointCloudT;

typedef struct Obstacle {
	char valid;
	float x_min, x_max, y_min, y_max, z_min, z_max;
	float centroid_x, centroid_y, centroid_z;

} Obstacle;

typedef struct CoordinateXYZ {
	float x, y, z;

} CoordinateXYZ;

//Vehicle dimensions (in meters)
#define VEHICLE_WIDTH	0.33
#define VEHICLE_LENGTH	0.51
#define VEHICLE_HEIGHT	0.27

#define VEHICLE_LEFT_EDGE	-(VEHICLE_WIDTH/2)
#define VEHICLE_RIGHT_EDGE  (VEHICLE_WIDTH/2)


#define VEHICLE_DEGREES_MAX_LEFT -30
#define VEHICLE_DEGREES_MAX_RIGHT 30

#define PI 3.1415926535897932

