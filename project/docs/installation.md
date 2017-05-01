# Project Installation Guide

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
