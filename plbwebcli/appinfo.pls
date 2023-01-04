*---------------------------------------------------------------
.
. Program Name: appinfo
. Description:  PlbWebCli Application Sample 
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
FullData        DIM             300
FileUrl         DIM             120
.
Result          FORM            5
.
Client          CLIENT
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
.
TestClick       LFUNCTION
                ENTRY
                EVENTINFO       0,Result=Result
                SWITCH          Result
                CASE            1
                CALL            TestInfo
                CASE            2
                CALL            TestVersion
                CASE            3
                CALL            TestNetwork
                CASE            4
                CALL            TestBattery
                CASE            5
                CALL            TestLang
                CASE            6
                CALL            TestApi
                ENDSWITCH
                FUNCTIONEND
*................................................................
.
. Test AppGetInfo
.
TestInfo        LFUNCTION
                ENTRY
                Client.AppGetInfo Giving FullData Using AppInfoDevice
                Datalist1.ResetContent
                Datalist1.AddString Using FullData
                FUNCTIONEND
*................................................................
.
. Test AppVersion
.
TestVersion     LFUNCTION
                ENTRY
                Client.AppVersion Giving FullData Using "{ #"val1#": 25, #"val2#": 356 }"
                Datalist1.ResetContent
                Datalist1.AddString Using FullData
                FUNCTIONEND
*................................................................
.
. TestLang
.
TestLang        LFUNCTION
                ENTRY
                Client.AppGetInfo Giving FullData Using AppInfoLanguage
                Datalist1.ResetContent
                Datalist1.AddString Using FullData
                FUNCTIONEND
*................................................................
.
. TestNetwork
.
TestNetwork     LFUNCTION
                ENTRY
                Client.AppGetInfo Giving FullData Using AppInfoNetwork
                Datalist1.ResetContent
                Datalist1.AddString Using FullData
                FUNCTIONEND
*................................................................
.
. TestBattery
.
TestBattery     LFUNCTION
                ENTRY
                Client.AppGetInfo Giving FullData Using AppInfoBattery
                Datalist1.ResetContent
                Datalist1.AddString Using FullData
                FUNCTIONEND
*................................................................
.
. BatEvent
.
BatEvent        LFUNCTION
                ENTRY
                Datalist1.AddString Using FullData
                FUNCTIONEND
*................................................................
.
. TestAPI
.
TestAPI         LFUNCTION
                ENTRY
                Client.AppApi   Giving FullData Using "{ #"action#": 2 }"
                Datalist1.ResetContent
                Datalist1.AddString Using FullData
                FUNCTIONEND
*................................................................
.
. ApiEvent
.
ApiEvent        LFUNCTION
                ENTRY
                Datalist1.AddString Using FullData
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
                EVENTREG        CLIENT,APPEVENTBATTERY,BATEVENT,ARG1=FULLDATA
                EVENTREG        Client,AppEventAPI,ApiEvent,ARG1=FullData
                Client.AppGetInfo Giving FullData Using AppInfoBattery
 
                FORMLOAD        WebForm
                SETPROP         LabelText1:
                                Text="Info|Version|Network Status|Battery Status|Language|API"
                FUNCTIONEND
