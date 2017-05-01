# Maintenance

## Kinect

## Pixhawk

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
