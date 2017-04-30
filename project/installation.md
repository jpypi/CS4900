
# Install
## Visualstudio 2015 C++ Community Edition
Registered to
username: apods-group@outlook.com
password: UASproject

## Microsoft Windows Kinect SDK 2.0
##Install PCL 1.8 x64 from http://unanancyowen.com/en/pcl18
- Add PCL to the system PATH
- Just hit next for the rest
- This will also install OpenNI


## QCGroundControl
#Pixhawk Config vars (can set via QCGroundControl)
	https://pixhawk.org/firmware/parameters
## Radio Calibration
### RC1
MAX: 1889
MIN: 117
TRIM: 1503

### RC4
MAX: 1991
MIN: 1007
TRIM: 1499

## To use Pixhawk without an RC radio (for autonomous mode)
COM_RC_IN_MODE: 2 (Virtual RC by Joystick)
https://groups.google.com/forum/#!topic/px4users/ZdJPo0ECIho

SYS_COMPANION: Companion Link (921600 baud)
https://dev.px4.io/offboard-control.html

## Disable Airspeed Indicator Check
CBRK_AIRSPD_CHK: 162128
https://groups.google.com/forum/#!topic/px4users/RL6mDPJsbHk

# OpenDDS building example
- %DDS_ROOT%/bin/opendds_idl Telemetry.idl
- tao_idl -I$DDS_ROOT -I$TAO_ROOT/orbsvcs Telemetry.idl
- perl %ACE_ROOT%/bin/mwc.pl -type vc14 pcm.mwc
- perl %ACE_ROOT%\bin\generate_export_file.pl telemetryCommon' > telemetryCommon_Export.h

- %DDS_ROOT%/bin/opendds_idl pc.idl
- tao_idl -I$DDS_ROOT -I$TAO_ROOT/orbsvcs -Wb,export_macro=telemetryMessageCommon_Export -Wb,export_include=telemetryMessageCommon_Export.h pc.idl
- perl %ACE_ROOT%/bin/mwc.pl -type vc14 pcm.mwc
- 
- pcm.sln