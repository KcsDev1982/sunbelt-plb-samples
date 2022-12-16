
*---------------------------------------------------------------
.
. Program Name: appcor
. Description:  PlbWeCli Application Core Sample 
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

WebForm         PLFORM          appcorf.pwf
.
FullData        DIM             1024
FileUrl         DIM             120
.
Result          FORM            5
.
Client          CLIENT
.
ResultLog       FILE
Seq             FORM            "-1"
.
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
TestClick       LFUNCTION
                ENTRY
                EVENTINFO       0,result=Result
                SWITCH          Result
                CASE            1
                CALL            TestInfo
                CASE            2
                CALL            TestPict
                CASE            3
                CALL            TestVibe
                CASE            4
                CALL            TestUp
                CASE            5
                CALL            TestLoc
                CASE            6
                CALL            TestScan
                ENDSWITCH
                FUNCTIONEND
*................................................................
.
. TestInfo
.
TestInfo        LFUNCTION
                ENTRY
                Client.AppGetInfo Giving FullData Using AppInfoDevice
                Datalist1.ResetContent
                Datalist1.AddString Using FullData
                FUNCTIONEND
*................................................................
.
. TestPict
.
TestPict        LFUNCTION
                ENTRY
                Client.AppGetPicture Using "{#"cleanUp#":  true }"
                Client.AppGetPicture 
                FUNCTIONEND
*................................................................
.
. PictEvent - AppEventGetPict
.
PictEvent       LFUNCTION
                ENTRY
                Datalist1.ResetContent
                Datalist1.AddString Using FileUrl
                FUNCTIONEND
*................................................................
.
. TestLoc
. 
TestLoc         LFUNCTION
                ENTRY
                Client.AppGeoLocation Using *Type=0
                FUNCTIONEND
*................................................................
.
. LocEvent - AppEventLocation
. 
LocEvent        LFUNCTION
                ENTRY
                Datalist1.ResetContent
                Datalist1.AddString Using FullData
                FUNCTIONEND
*................................................................
.
. TestScan
.
TestScan        LFUNCTION
                ENTRY
                Client.AppScanBarCode
                FUNCTIONEND
*................................................................
.
. ScanEvent - AppEventScanBarCode
.
ScanEvent       LFUNCTION
                ENTRY
                Datalist1.ResetContent
                Datalist1.AddString Using FullData
                FUNCTIONEND
*................................................................
.
. TestVibe
.
TestVibe        LFUNCTION
                ENTRY
                Client.AppVibrate Using 500
                FUNCTIONEND
*................................................................
.
. TestUp - Test download and upload
.
TestUp          LFUNCTION
                ENTRY
                EVENTREG        Client,AppEventDoDownload,EventDn1,ARG1=FullData
                Client.AppDownLoad Giving Result Using "Bill1.txt", "cdvfile://localhost/persistent/Bill1.txt"  
                FUNCTIONEND
*................................................................
.
. EventDn1 - AppEventDoDownload
.
EventDn1        LFUNCTION
                ENTRY
                Datalist1.ResetContent
                Datalist1.AddString Using FullData
                WRITE           ResultLog,Seq;FullData
                EVENTREG        Client,AppEventDoUpload,EventUp1,ARG1=FullData
                Client.AppUpload Giving Result Using "cdvfile://localhost/persistent/Bill1.txt", "Bill2.txt"  
                FUNCTIONEND

*................................................................
.
. EventUp1 - AppEventDoUpload
.
EventUp1        LFUNCTION
                ENTRY
                Datalist1.AddString Using FullData
                WRITE           ResultLog,Seq;FullData
                EVENTREG        Client,AppEventDoDownload,EventDn2,ARG1=FullData
                Client.AppDownLoad Giving Result Using "Bill1.jpg", "cdvfile://localhost/persistent/Bill1.jpg" 
                FUNCTIONEND

*................................................................
.
. EventDn2 - AppEventDoDownload
.
EventDn2        LFUNCTION
                ENTRY
                Datalist1.AddString Using FullData
                WRITE           ResultLog,Seq;FullData
                EVENTREG        Client,AppEventDoUpload,EventUp2,ARG1=FullData
                Client.AppUpload Giving Result Using "cdvfile://localhost/persistent/Bill1.jpg", "Bill2.jpg"  
                FUNCTIONEND

*................................................................
.
. EventUp21 - AppEventDoUpload
.
EventUp2        LFUNCTION
                ENTRY
                Datalist1.AddString Using FullData
                WRITE           ResultLog,Seq;FullData
                ERASE           "!cdvfile://localhost/persistent/Bill1.txt"
                ERASE           "!cdvfile://localhost/persistent/Bill1.jpg"
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
. Register and Startup the events, load the main form
.
Main            LFUNCTION
                ENTRY
                WINHIDE
                FORMLOAD        WebForm
                SETPROP         LabelText1:
                                Text="Info|Get Picture|Vibrate|Upload|Location|Scan Barcode"
.
                EVENTREG        Client,AppEventGetPict,PictEvent,ARG1=FileUrl
                EVENTREG        Client,AppEventLocation,LocEvent,ARG1=FullData
                EVENTREG        Client,AppEventScanBarCode,ScanEvent,ARG1=FullData

                PREP            ResultLog,"appcor.log",EXCLUSIVE

                FUNCTIONEND
