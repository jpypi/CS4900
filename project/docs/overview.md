# Project Overview

## Code Locations
### Main Code (Kinect, DDS, RPI)
https://github.com/jpypi/CS4900/blob/master/project

### Pixhawk Serial Interface
https://github.com/swatza/Autopilot_Interface_Win

## Project Structure

- Kinect -> Visual Processing Module
- Visual Processing Module -> publish DDS control messages
- Control Module: DDS control messages -> TCP connection to Raspberry pi
- Raspberry pi PWM -> Steering servo and ESC throttle
- Pixhawk ftdi (telem2) -> telemetry DDS message publisher
