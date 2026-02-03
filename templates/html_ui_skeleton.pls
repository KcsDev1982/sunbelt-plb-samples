*---------------------------------------------------------------
.
. Program Name: <name>
. Description:  <description>
.
. Revision History:
.
. <date> <programmer>
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc

                CIFNDEF         $CLI_STATE_CORDOVA
$CLI_STATE_CORDOVA EQU          2
$CLI_STATE_BOOTSTRAP5 EQU       16
                CENDIF

// Runtime status variables
isGui           BOOLEAN
isWebSrv        BOOLEAN
isPlbSrv        BOOLEAN
isWebview       BOOLEAN
isWebCliApp     BOOLEAN
isSmallScreen   BOOLEAN

// Global data
mainForm        PLFORM          html_ui_skeleton.plf
Client          CLIENT
Runtime		RUNTIME
jsonData        DIM             200

*................................................................
.
. Code start
.
                CALL            Main
                WINHIDE
                LOOP
                EVENTWAIT
                REPEAT
                STOP

*................................................................
.
. Check what type of runtime support we have
.
CheckStatus     LFUNCTION
                ENTRY
runtimeData     DIM             50
runtimeVersion  DIM             5
unused          DIM             1
plbRuntime      DIM             9
WidthData       DIM             5
checkWidth      FORM            5

                GETMODE         *GUI=isGui ; Check for character mode runtime
                IF              (isGui)
                CLOCK           VERSION,runtimeData ; Check windows console
                UNPACK          runtimeData,runtimeVersion,unused,plbRuntime
                CHOP            plbRuntime
                
                IF              (NOCASE plbRuntime == "PLBCON")
                CLEAR           isGui
                ENDIF
                IF              (NOCASE plbRuntime == "PLBWEBSV")
                SET             isWebSrv
                ENDIF
                IF              (NOCASE plbRuntime == "PLBSERVE")
                SET             isPlbSrv
                ENDIF
                ENDIF

                IF              (isGui)
                WINHIDE
                
                Client.Getstate Giving isWebCliApp Using $CLI_STATE_CORDOVA
                Client.Getstate Giving isWebview Using $CLI_STATE_BOOTSTRAP5

                IF              (isWebSrv) ; Check for a small screen (such as iphone)
                Client.GetWinInfo Giving WidthData Using 0x2
                MOVE            WidthData To checkWidth
                MOVE            (checkWidth <= 700) to isSmallScreen
                ENDIF
                ENDIF

                FUNCTIONEND

*................................................................
.
. Load a supporting HTML file
.
LoadSupportHtml LFUNCTION
htmlCtl         HTMLCONTROL     ^
fileName        DIM             250
                ENTRY
htmlFile        FILE
htmlBuffer      DIM             ^
fileSize        INTEGER         4
fullFileName    DIM             250
seq             FORM            "-1"

                EXCEPTSET       NoFile IF IO
                OPEN            htmlFile,fileName,Read

                GETFILE         htmlFile,TxtName=fullFileName ; Read the registration file into a buffer
                FINDFILE        fullFileName,FileSize=fileSize
                IF              (!fileSize)
                INCR            fileSize
                ENDIF

                DMAKE           htmlBuffer,fileSize
                READ            htmlFile,Seq;*ABSON,htmlBuffer
                htmlCtl.InnerHtml Using htmlBuffer,$HTML_HAS_EVENTS
                CLOSE           htmlFile
                DFREE           htmlBuffer
noFile
                FUNCTIONEND


*................................................................
.
. Event handler
.
HctlEvent       LFUNCTION
                ENTRY
editData        DIM             40
result          FORM            5

                SCAN            "submit" in JsonData
                IF              EQUAL
                ALERT           PLAIN,"Submit was pressed",result
                ENDIF

                SCAN            "sampleInput" in JsonData
                IF              EQUAL
		htmlHctlMain.GetAttr Giving editData using "sampleInput","value"
                ALERT           PLAIN,editData,result
                ENDIF

                FUNCTIONEND

*................................................................
.
. Set up the events on the HTML objects and register the event handler
.
HctlSetupEvents LFUNCTION
                ENTRY
                EVENTREG        htmlHctlMain,$JQueryEvent,HctlEvent,ARG1=JsonData
                htmlHctlMain.SetAttr using "sampleInput","data-plbevent","change"
                htmlHctlMain.SetAttr using "submit","data-plbevent","click"
                htmlHctlMain.UpdateEvents
                FUNCTIONEND

*................................................................
.
. Set up the PL/B z-order for the HTML objects
.
HctlSetupFocus  LFUNCTION
                ENTRY
                htmlHctlMain.SetAttr using "sampleInput","data-plbtabid","10"
                htmlHctlMain.SetAttr using "submit","data-plbtabid","20"
		htmlHctlMain.UpdateEvents
                FUNCTIONEND

*................................................................
.
. Setup the PL/B ENABLE/DISABLE HTML objects on the HTML page
.
HctlSetupEnabled  LFUNCTION
                ENTRY
                htmlHctlMain.SetAttr using "submit","data-plbenable","on"
		htmlHctlMain.UpdateEvents
                FUNCTIONEND

*................................................................
.
. Call a JavaScript routine in the HTML page
.
HtclCallJS      LFUNCTION
                ENTRY
UID             DIM             36
result          FORM            5
                htmlFrmMain.SetAsClient
                Client.jsrun    Giving UID Using "plbGetGuid();"
                Client.FlushMessages
                ALERT           PLAIN,UID,result
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
result          FORM            4

                CALL            CheckStatus
                IF              (!isGui)
                KEYIN           "This runtime can't run this program. ",result
                STOP
                ENDIF
                
                IF              (!isWebview)
                ALERT           STOP,"This program requires WebView support.",result
                STOP
                ENDIF

                IF              (isWebCliApp || isSmallScreen) ; On smaller screens change to % positioning for left and width
                SETMODE         *PERCENTCONVERT=1
                ENDIF

		Runtime.SetWebTheme	Using 19
                FORMLOAD        mainForm

                htmlFrmMain.SetAsClient
                Client.SetUTF8Convert Using 0

                CALL            LoadSupportHtml USING htmlHctlMain,"html_ui_skeleton.html"
		
                CALL            HctlSetupEvents

                CALL            HctlSetupFocus

		CALL            HctlSetupEnabled

		SETPROP		htmlHctlMain,enabled=0

                CALL            HtclCallJS

		SETPROP		htmlHctlMain,enabled=1
		SETFOCUS        htmlHctlMain
 
                FUNCTIONEND
