*---------------------------------------------------------------
.
. Program Name: gcalender.pls
. Description:  Sample google calendar support
.               Embedded calendar support
.
. Revision History:
.
. Date: 10/20/2025
. Original code
.
. Note:
.
.	The html file named gcalendar_sup.html must be updated with a
.	Google <iframe> embed code from the "Integrate calendar" section
.
. Step 1: Get the embed code from Google Calendar 
.	Open Google Calendar on your computer.
.	Click the Settings menu (the gear icon) in the top right corner, then select Settings.
.	In the left-hand menu, click on the name of the calendar you wish to embed.
.	Scroll down to the "Integrate calendar" section and copy the <iframe> code that is provided.
.	To customize the calendar's appearance, click Customize before copying the code. You can 
.	  choose the default view, color, and size options. 
.
. Step 2: Add the embed code to the gcalendar_sup.html file  
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
mainForm        PLFORM          gcalendar.plf
Client          CLIENT


*---------------------------------------------------------------
// <program wide variables>
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
.
. Check for character mode runtime
.
                GETMODE         *GUI=isGui

                IF              (isGui)
.
. check windows console.
.
                CLOCK           VERSION,runtimeData
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
.
. For version 10.6 uncomment the line below
.
.               MOVE    1 to isWebview

.
. Check for a small screen (such as iphone)
.
                IF              (isWebSrv)
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
*
.Read the registration file into a buffer
.
                GETFILE         htmlFile,TxtName=fullFileName
                FINDFILE        fullFileName,FileSize=fileSize
                IF              (!fileSize)
                INCR            fileSize
                ENDIF
.
                DMAKE           htmlBuffer,fileSize
.
                READ            htmlFile,Seq;*ABSON,htmlBuffer

                htmlCtl.InnerHtml Using htmlBuffer,$HTML_HAS_EVENTS

                CLOSE           htmlFile
                DFREE           htmlBuffer

noFile
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

.
. On smaller screens change to % positioning for left and width
.
                IF              (isWebCliApp || isSmallScreen)
                SETMODE         *PERCENTCONVERT=1
                ENDIF

                FORMLOAD        mainForm

                CALL            LoadSupportHtml Using calHtmlArea,"gcalendar_sup.html"
      
                calFrmMain.SetAsClient
                Client.SetUTF8Convert Using 0
 
                FUNCTIONEND



