# Project Installation Guide

## Machine Setup

### Install Microsoft Windows Kinect SDK 2.0
### Install PCL 1.8 x64 from http://unanancyowen.com/en/pcl18
- Add PCL to the system PATH
- Just hit next for the rest
- This will also install OpenNI
### Install QCGroundControl

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
COM_RC_IN_MODE: 2 (Virtual RC by Joystick)
https://groups.google.com/forum/#!topic/px4users/ZdJPo0ECIho

SYS_COMPANION: Companion Link (921600 baud)
https://dev.px4.io/offboard-control.html

### Disable Airspeed Indicator Check
CBRK_AIRSPD_CHK: 162128
https://groups.google.com/forum/#!topic/px4users/RL6mDPJsbHk

---

## Raspberry pi zero
- raspbian jessie lite
- TCP over USB
    http://blog.gbaman.info/?p=791
    http://blog.gbaman.info/?p=699
- python 2
- Wiring
    - BCM pin numbering using pins:
        13 for ____
        18 for ____
- Runs TCP Server on port 4433
- Message format (using Big Endian):
    struct {
        int   status;
        float angle;
        float power;
    }
