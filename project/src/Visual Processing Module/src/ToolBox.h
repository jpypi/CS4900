/*
Author: Aleksandr Dobrev

Last major update: 2017-04-25


*/


#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include <time.h>

#include "shared.h"

#pragma once

class PointCloudWriter {
	pcl::PCDWriter writer;
public:
	PointCloudWriter();
	int savePointCloud(std::string filepath, PointCloudT::Ptr point_cloud);
private:
	//Functions
	int _savePointCloud(std::string filename, PointCloudT::Ptr point_cloud);

};

PointCloudWriter::PointCloudWriter() {
	writer = pcl::PCDWriter();
}

int PointCloudWriter::savePointCloud(std::string filepath, PointCloudT::Ptr point_cloud) {
		return _savePointCloud(filepath, point_cloud);
	}


int PointCloudWriter::_savePointCloud(std::string filename, PointCloudT::Ptr point_cloud) {

		std::cerr << "Saving Point Cloud [ contains " << point_cloud->points.size() << " points ]. Filename: " << filename << std::endl;
		writer.write<PointType>(filename, *point_cloud, false);

		return 0;
}
///////////////////////////////////////////////////////////////////////////////

class Timer {
public:
	Timer();
	void start();
	void stop();
	unsigned long getTime();
	bool isRunning();
private:
	//Variables
	bool running;
	unsigned long start_time;
	unsigned long end_time;
};


Timer::Timer() {
	running = false;
}

void Timer::start() {
	if (!isRunning()) {
		start_time = (unsigned long)clock();
		running = true;
	}
	else {
		std::cerr << "A timer is already running! End timer befofre starting again!" << std::endl;
	}
}

void Timer::stop() {
	if (isRunning()) {
		end_time = (unsigned long)clock();
		running = false;
	}
	else {
		std::cerr << "No active timer running! Must start a timer before calling stop()." << std::endl;
	}
}

unsigned long Timer::getTime() {
	unsigned long time_dif;

	time_dif =  (unsigned long)(end_time - start_time) ;
	return time_dif;
}

bool Timer::isRunning() {
	return running;
}
