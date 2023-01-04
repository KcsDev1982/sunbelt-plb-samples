*---------------------------------------------------------------
.
. Program Name: appoffline
. Description:  PlbWebCli Application Offline Sample 
.
. Revision History:
.
. 17-04-07 whk
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*---------------------------------------------------------------       

WebForm         PLFORM          appofflnf.pwf
.
FullData        DIM             200
JsonBody        DIM             400
.
Result          FORM            5
.
BaseDir         DIM             150
SampleName      DIM             200
.
SampleData      XDATA
.
Client          CLIENT
RunTime         RUNTIME
.

               
*................................................................
.
. Code start
.
                CALL            Main
                LOOP
                EVENTWAIT
                REPEAT
                STOP

*................................................................
.
. TestClick - Handle a request to perform a test
.
TestClick	LFUNCTION
                ENTRY
                EVENTINFO       0,result=Result
                SWITCH          Result
                CASE            1
                CALL            Install
                CASE            2
                CALL            GoOffline
                CASE            3
                CALL            GoOffline1
                CASE            4
                CALL            GetData
                ENDSWITCH
                FUNCTIONEND

*................................................................
.
. Install
. 
Install		LFUNCTION
                ENTRY
                Client.AppDownLoad Using "offline/sunhello.css", "cdvfile://localhost/persistent/sunhello.css" 
                Client.AppDownLoad Using "offline/sunhello.html", "cdvfile://localhost/persistent/sunhello.html" 
                Client.AppDownLoad Using "offline/sunhello.js", "cdvfile://localhost/persistent/sunhello.js" 

                Client.AppDownLoad Using "offline/sunviewfile.css", "cdvfile://localhost/persistent/sunviewfile.css" 
                Client.AppDownLoad Using "offline/sunviewfile.html", "cdvfile://localhost/persistent/sunviewfile.html" 
                Client.AppDownLoad Using "offline/sunviewfile.js", "cdvfile://localhost/persistent/sunviewfile.js" 

                Client.AppDownLoad Using "offline/userdata.json", "cdvfile://localhost/persistent/userdata.json" 


                Client.AppInstallOffline Using "Offline Hello", "sunhello.html","sunhello.css","sunhello.js"
                Client.AppInstallOffline Using "Offline Test1", "sunhello.html","sunhello.css","sunhello.js"
                Client.AppInstallOffline Using "Offline File", "sunviewfile.html","sunviewfile.css","sunviewfile.js"
                Client.AppInstallOffline Using "Offline Test1","",*Options=2
                SETPROP         EditText2, Text="Installed"
                FUNCTIONEND

*................................................................
.
. GoOffline
.
GoOffline	LFUNCTION
                ENTRY
                Client.AppSetOffline Using "sunhello.html","sunhello.css","sunhello.js"
                SHUTDOWN
                FUNCTIONEND

*................................................................
.
. GoOffline1
.
GoOffline1	LFUNCTION
                ENTRY
                Client.AppSetOffline Using "sunviewfile.html","sunviewfile.css","sunviewfile.js"
                SHUTDOWN
                FUNCTIONEND

*................................................................
.
. GetData - Get a data file
.
GetData		LFUNCTION
                ENTRY
                EVENTREG        Client,AppEventDoUpload,UploadDone,ARG1=FullData
                Client.AppUpload Giving Result Using "cdvfile://localhost/persistent/sampleData.txt", "sampleData.txt"
                FUNCTIONEND

*................................................................
.
. UploadDone
.
UploadDone	LFUNCTION
                ENTRY
                RunTime.GetDir  GIVING BaseDir USING *TYPE=6   
                PACK            SampleName, BaseDir, "sampleData.txt" 
                SETPROP         EditText2, Text=SampleName
                SampleData.LoadJson Using SampleName, JSON_LOAD_FROM_FILE
                SampleData.StoreJson Giving JsonBody
                SETPROP         EditText1, Text=JsonBody
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
. Register and Startup the battery events
.
Main            LFUNCTION
                ENTRY
                WINHIDE
               
		FORMLOAD        WebForm
                SETPROP         EditText1, Text=""
                SETPROP         EditText2, Text=""

                FUNCTIONEND
