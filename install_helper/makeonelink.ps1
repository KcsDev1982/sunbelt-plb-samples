#
#  $Product		--> "Visual PLB 10.8"
#  $ShortcutName	--> "Visual PLB"
#  $Workingdir		--> "c:\Sunbelt\plbwin.108\code"
#  $Target		--> "c:\Sunbelt\plbwin.108\code\plbwin.exe"
#  $Plcarg		--> " -h c:\Sunbelt\plbwin.108\code\watch.plc"
#  $Showlog		--> "on" optional
#
#    .\makeonelink.ps1 "Visual PLB 10.8" "Visual PLB" "c:\Sunbelt\plbwinX.108\code" "c:\Sunbelt\plbwin.108\code\plbwin.exe" 
#    .\makeonelink.ps1 "Visual PLB 10.8" "Visual PLB" "c:\Sunbelt\plbwinX.108\code" "c:\Sunbelt\plbwin.108\code\plbwin.exe" " -h c:\Sunbelt\plbwin.108\code\watch.plc"
#
#  Test Command line Sample:
#
#  $Product		--> "Visual PLB 10.8"
#  $ShortcutName	--> "Test_Notepad"
#  $Workingdir		--> "C:\Windows\System32"
#  $Target		--> "notepad.exe"
#  $Plcarg		--> empty/not used
#  $Showlog		--> "on" optional
#
#    .\makeonelink.ps1 "Visual PLB 10.8" "Test_Notepad" "C:\Windows\System32" "notepad.exe"
#
param ( $Product, $ShortcutName, $Workingdir, $Target, $Plcarg, $Showlog )

# Create WScript.Shell COM object
$WshShell = New-Object -ComObject WScript.Shell

#
# Show Input parameters
#
if ( $Showlog -eq "on" ) {
Write-Host "*****************************"
Write-Host "Product:      '$Product'"
Write-Host "ShortcutName: '$ShortcutName'"
Write-Host "Workingdir:   '$Workingdir'"
Write-Host "Target:       '$Target'"
Write-Host "Plcarg:       '$Plcarg'"
Write-Host "Showlog:      '$Showlog'"
}

# Make Desktop Directory
#
	$Path = "$env:USERPROFILE\Desktop\$Product"
	if ( Test-Path  $Path  -PathType Container ) {
		if ( $Showlog -eq "on" ) {
		Write-Host "Directory exist: '$Path'!"
		}
	} else {
		mkdir $Path
		if ( $Showlog -eq "on" ) {
		Write-Host "Created Directory '$Path'!"
		}
	}

# Define the shortcut path
$ShortcutPath = "$env:USERPROFILE\Desktop\$Product\$ShortcutName.lnk"

# Create the shortcut object
$Shortcut = $WshShell.CreateShortcut($ShortcutPath)

# Set the target path (the program or file to run)
$Shortcut.TargetPath = "$Target"
$Shortcut.Arguments = "$Plcarg"

# (Optional) Set other shortcut properties
$Shortcut.WorkingDirectory = "$Workingdir"
$Shortcut.WindowStyle = 1  # 1 = Normal, 3 = Maximized, 7 = Minimized
$Shortcut.Description = "Launch '$ShortcutName'"
$Shortcut.IconLocation = "$Target,0"

# Save the shortcut to the desktop
$Shortcut.Save()
#
# End
#
