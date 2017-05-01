# User Guide

## Start up
- Calibrate Pixhawk
- Connect pixhawk via FTDI telem 2
- Start pixhawk telemetry publisher
- Start raspbery pi socket server
- Start start the control process (DDS subscriber -> raspberry pi)
- Start Kinect visual processing module


## Raspberry PI
- ssh pi@raspberrypi.local
- Run ./control.py (this starts a TCP socket server)
