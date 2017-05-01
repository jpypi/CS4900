# Maintenance

## Pixhawk
- Use QGroundControl to calibrate the accelerometer
- Verify BAUD rate for either USB (57600) or FTDI (921600)
- Verify COM port number using Windows Device Manager for the serial connection

## OpenDDS
This project currently uses OpenDDS 3.10.
This project uses FACE as a base to simplify the code.
The primary example can be found in %DDS_ROOT%\DevGuideExamples\FACE\Simple\.

Topics, publishing connections, and subscribing connections are defined in the .ini file.
When setting up a dds connection to a topic, one need only use the connection named from the .ini file.
An example .ini file can be found in the examples directory.

## Raspberry PI
- ssh pi@raspberrypi.local
- Run ./control.py (this starts a TCP socket server)

### Bugs
- PWM to the ESC is slightly buggy as sometimes the car goes into full power
  reverse.

# Project Integration Status

Currently all individual pieces compile and run, however the integration of the
visual processing code with a DDS publisher function is not finished. This
piece still needs to be compiled but the kinect portion is currently compiled
using cmake, whereas DDS is built using MPC. This needs to be resolved to
complete integration.
