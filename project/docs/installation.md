# Project Installation Guide

### Install QCGroundControl

---

## Vision Processing Module

### Environment
#### Main Software Requirements
- Kinect for Windows SDK v2.0
- Point Cloud Library 1.8.0
- Visual Studio Community 2015
- CMake 3.5.0
- Kinect2Grabber

#### Software details
- Kinect for Windows SDK v2.0
	= Provides drivers and many examples on reading data from Kinect v2 sensor.
- Point Cloud Library 1.8.0
	= The Point Cloud Library (PCL) is a standalone, large scale, open project for 2D/3D image and point cloud processing.
- Visual Studio Community 2015
	= An integrated development environment (IDE) from Microsoft
- CMake 3.5.0
	= CMake is an open-source, cross-platform family of tools designed to build, test and package software.
	= CMake is used to control the software compilation process using simple platform and compiler independent configuration files, and generate native makefiles and workspaces that can be used in the compiler environment of your choice.
- Kinect2Grabber
	= Kinect2Grabber is Grabber of PCL(Point Cloud Library) to retrieve the point cloud data from Kinect v2 using Kinect for Windows SDK v2.x.
	= This Grabber only depend on Kinect for Windows SDK v2.x.

#### Additional Dependencies of software listed above
* These get installed using the PCL 1.8.0 prebuilt installer.

- Boost (C++ Semi Standard Library)
- Eigen (Matrix Library)
- FLANN (Nearest Neighbor Search Library)
- VTK (Visualization Library)


### Installation

#### Kinect for Windows SDK v2.0:
1. Download the official Kinect for Windows SDK v2.0 from microsoft<br/>
   https://www.microsoft.com/en-us/download/details.aspx?id=44561
2. Follow installation guide provided my microsoft.

#### CMake 3.5.0
* Important Note: Although newer versions of CMake are likely to work, they have not been tested with.
* Newer CMake versions can be downloaded from CMake official website. (https://cmake.org).

1. CMake version 3.5.0 can be downloaed from (https://cmake.org/files/v3.5/)
2. Follow installation guide provided by CMake.

#### Point Cloud Library 1.8.0
* Important Note: As of 2017-4-30, PCL does not have a download for PCL version 1.8.0.

1. You can download PreBuild Binary of PCL 1.8.0 from the following page<br/>
   http://unanancyowen.com/?p=1794&lang=en
2. Modify the following evironment variables and restart your machine

	Variable Name | Value
	--------------|-------------------------------------------------------------------------
	PCL_ROOT      | C:\Program Files\PCL 1.8.0 (or C:\Program Files (x86)\PCL 1.8.0)
	Path          | ;%PCL_ROOT%\bin;%OPENNI2_REDIST64% (or %OPENNI2_REDIST%)

#### Kinect2Grabber
* Visual Processing module relies on this to get point clouds.
* This does not need to be installed as the VisualProcessingModule contains all of this.
* This is mostly a reference to respect author to allow for the most basic functionality in order to attain point clouds from Kinect SDK 2.0.

1. Can be attained from (https://github.com/UnaNancyOwen/KinectGrabber).
2. Generate the project using CMake

---

## OpenDDS
### Installing the Library
- The OpenDDS library can be downloaded from http://opendds.org/downloads.html
- The steps for building the library can be found at http://opendds.org/quickstart/GettingStartedWindows.html
- Additional information on openDDS installation can be found at http://opendds.org/documents/building.html

Make sure when opening the DDS_TAOv2_all.sln in Visual Studio to use the developer command prompt that ran configure (or setenv.cmd)

### Building Project Code
All DDS projects/solutions require
- a .mpc file
- a .mwc file

The content of the .mwc file should likely not change.
The .mpc file describes the solution and each project within it.
Examples of these two files can be found in the examples directory.

A Build Script is used to automate compiling .idl files and .mpc files into a visual studio solution file.
Before using the build script, one must run setenv.cmd (in the same command prompt) from the OpenDDS install directory.
An example of a build scipt can be found in the examples directory.

After creating the visual studio solution file, the solution may be opened from the command prompt (that has run setenv.cmd).
Provided the code is correct and all steps have been followed, one may compile the executables from the menu Build->Build Solution.

### Running Project Code
All DDS executables must be run from a command prompt that has run setenv.cmd.

---

## Pixhawk

### Pixhawk Config vars (can set via QCGroundControl)
https://pixhawk.org/firmware/parameters

### Radio Calibration For RC Car
#### RC1
    MAX: 1889
    MIN: 117
    TRIM: 1503

#### RC4
    MAX: 1991
    MIN: 1007
    TRIM: 1499

### To use Pixhawk without an RC radio (for autonomous mode)
COM_RC_IN_MODE: 2 (Virtual RC by Joystick)<br/>
https://groups.google.com/forum/#!topic/px4users/ZdJPo0ECIho


SYS_COMPANION: Companion Link (921600 baud)<br/>
https://dev.px4.io/offboard-control.html

### Disable Airspeed Indicator Check
CBRK_AIRSPD_CHK: 162128<br/>
https://groups.google.com/forum/#!topic/px4users/RL6mDPJsbHk

---

## Raspberry pi zero
- raspbian jessie lite
- TCP over USB<br/>
    http://blog.gbaman.info/?p=791<br/>
    http://blog.gbaman.info/?p=699
- python 2
- Wiring
    - BCM pin numbering using pins:
        - 13 for steering servo
        - 18 for ESC throttle
- Runs TCP Server on port 4433
- Message format (using Big Endian):
```
    struct {
        int   status;
        float angle;
        float power;
    }
```

---

