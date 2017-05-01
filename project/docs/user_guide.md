# User Guide

## Start up
- Calibrate Pixhawk
- Connect pixhawk via FTDI telem 2
- Start pixhawk telemetry publisher
- Start raspbery pi socket server
- Start start the control process (DDS subscriber -> raspberry pi)
- Start visual processing module


## Raspberry PI
- ssh pi@raspberrypi.local
- Run ./control.py (this starts a TCP socket server)

### Visual Processing Module

- Run VisualProcessingModule.exe
- 2 Windows should pop up:
    - A console which displays processing status information as well as other
      debug information depending on what debug switches are enabled. The
      console will also display the information printed by the temporary path
      planning function which resides in main.cpp
	- A visualizer which shows the filtered point clouds:<br/>
		RED = Largest Plane<br/>
		GREEN = Largest cloud cluster<br/>
		BLUE = Second largest cloud cluster<br/>
		GREY = Everything else
- What kind of debug information that is printed to the console can be
  enabled/disabled by the user.  These adjustments need to be made in main.cpp
  and at the top there are several development switches defined. Setting the
  value to 1 enables it and setting it to 0 disables it.

