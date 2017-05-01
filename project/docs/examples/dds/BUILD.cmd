:: For different projects, arguments of the lines must be modified to match the correct files

%DDS_ROOT%\ACE_wrappers\bin\tao_idl -I %DDS_ROOT% -I %TAO_ROOT%\orbsvcs -Wb,export_macro=exampleMessenger_Export -Wb,export_include=exampleMessenger_Export.h exampleMessage.idl
%DDS_ROOT%\bin\opendds_idl -Wb,export_macro=exampleCommon_Export -Wb,export_include=exampleMessengerCommon_Export.h exampleMessage.idl
perl %ACE_ROOT%/bin/mwc.pl -type vc14 exampleMessenger.mwc
generate_export_file.pl FaceMessenger > "exampleMessenger_Export.h"
