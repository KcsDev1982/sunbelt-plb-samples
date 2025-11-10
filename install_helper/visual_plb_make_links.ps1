#
# Parameter Examples sent to 'makeonelink.ps1'.
#
#  $Product		--> "Visual PLB 10.8"
#  $ShortcutName	--> "Visual PLB"
#  $Workingdir		--> "c:\Sunbelt\plbwin.108\code"
#  $Target		--> "plbwin.exe"
#  $Plcarg		--> " -h c:\Sunbelt\plbwin.108\code\watch.plc"
#  $Showlog		--> "on"   on --> turn on 'makeonelink.ps1 logging'.
#
#    .\makeonelink.ps1 "Visual PLB 10.8" "Visual PLB" "c:\Sunbelt\plbwin.108A\code" "plbwin.exe"
#
#  Test Command line:
#
#  $Product		--> "Visual PLB 10.8"
#  $ShortcutName	--> "Test_Notepad"
#  $Workingdir		--> "C:\Windows\System32"
#  $Target		--> "notepad.exe"
#  $Plcarg		--> "arguments option for the target."
#  $Showlog		--> "on"   on --> turn on 'makeonelink.ps1 logging'.
#
#    .\makeonelink.ps1 "Visual PLB 10.8" "Test_Notepad" "C:\Windows\System32" "notepad.exe"
#
#******************************************************************************
#
$Product = "Visual PLB 10.8"
$Workingdir = "c:\Sunbelt\plbwin.108\code"
$Runtime = "$Workingdir\plbwin.exe"
$Plcarg = " -h  $Workingdir"
$Showlog = ""
#
.\makeonelink.ps1  "$Product"  "PLB Console Dev"  "$Workingdir"  "$workingdir\dosstart.bat"  ""  "$Showlog"
.\makeonelink.ps1  "$Product"  "PLB DB Explorer"  "$Workingdir"  "$Runtime"  "$Plcarg\dbexplorer.plc"  "$Showlog"
.\makeonelink.ps1  "$Product"  "PLB DBExplorer Reference"  "$Workingdir"  "$Workingdir\dbexplorer.chm"  ""  "$Showlog"
.\makeonelink.ps1  "$Product"  "PLB Designer Reference"  "$Workingdir"  "$Workingdir\designer.chm"  ""  "$Showlog"
.\makeonelink.ps1  "$Product"  "PLB Form Designer"  "$Workingdir"  "$Runtime"  "$Plcarg\designer.plc"  "$Showlog"
.\makeonelink.ps1  "$Product"  "PLB IDE Reference"  "$Workingdir"  "$Workingdir\sunide.chm"  ""  "$Showlog"
.\makeonelink.ps1  "$Product"  "PLB IDE"  "$Workingdir"  "$Runtime"  "$Plcarg\sunide.plc"  "$Showlog"
.\makeonelink.ps1  "$Product"  "PLB Language Reference"  "$Workingdir"  "$Workingdir\plb.chm"  ""  "$Showlog"
.\makeonelink.ps1  "$Product"  "PLB Runtime Reference"  "$Workingdir"  "$Workingdir\plbrun.chm"  ""  "$Showlog"
.\makeonelink.ps1  "$Product"  "PLB Schema Editor"  "$Workingdir"  "$Runtime"  "$Plcarg\schemaeditor.plc"  "$Showlog"
.\makeonelink.ps1  "$Product"  "PLB Util Reference"  "$Workingdir"  "$Workingdir\plbutil.chm"  ""  "$Showlog"
.\makeonelink.ps1  "$Product"  "PLB Watch"  "$Workingdir"  "$Runtime"  "$Plcarg\watch.plc"  "$Showlog"
.\makeonelink.ps1  "$Product"  "Visual PLB"  "$Workingdir"  "$Workingdir\plbwin.exe"  ""  "$Showlog"
#
# End
#
