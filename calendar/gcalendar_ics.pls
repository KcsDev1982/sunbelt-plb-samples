*---------------------------------------------------------------
.
. Program Name: gcalender_ics.pls
. Description:  Sample google calendar support
.               Product a ICS file
.
. Revision History:
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
mainForm        PLFORM          gcalendar_ics.plf
Client          CLIENT

icsFile         FILE
seq             FORM            "-1"

.................................................
.
. Format of ICS file
.
. BEGIN:VCALENDAR
. VERSION:2.0
. PRODID:-//PLB Calendar Event//EN
. BEGIN:VEVENT
. UID:aee8f239-c76a-4f50-8a02-c0bacd738441
. DTSTAMP:20250724T194258Z
. DTSTART:20250810T120000
. DTEND:20250810T140000
. SUMMARY:Museum Trip
. LOCATION:Big Museum
. DESCRIPTION:Lunch will be provided
. END:VEVENT
. END:VCALENDAR
.
eventRecord     RECORD
isValid         BOOLEAN
UID             DIM             36      // UID
timeStamp       DIM             16      // DTSTAMP
startTime       DIM             16      // DTSTART
endTime         DIM             16      // DTEND
summary         DIM             40      // SUMMARY
location        DIM             80      // LOCATION
description     DIM             40      // DESCRIPTION
                RECORDEND


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

                htmlCtl.InnerHtml Using htmlBuffer

                CLOSE           htmlFile
                DFREE           htmlBuffer

noFile
                FUNCTIONEND

*................................................................
.
. Fetch the event data from the form
.
FetchEventData  LFUNCTION
                ENTRY
jsCall          DIM             4096
guid            DIM             40
dateInfo        DIM             16
curDate         DATETIME
startDate       DATETIME
endDate         DATETIME
result          FORM            5

                CLEAR           eventRecord

                GETPROP         calEdtEvent,*TEXT=eventRecord.summary

                COUNT           result,eventRecord.summary
                IF              ZERO
                ALERT           CAUTION,"The event name must not be empty!",result,"Calendar",
                RETURN
                ENDIF

                GETPROP         calEdtDesc,*TEXT=eventRecord.description
                GETPROP         calEdtLoc,*TEXT=eventRecord.location

                GETPROP         calEdtStart,*TEXT=dateInfo
                startDate.SetAsString Using dateInfo,"%Y-%m-%dT%H:%M",1
                startDate.GetAsString Giving eventRecord.startTime Using "%Y%m%dT%H%M%S"

                GETPROP         calEdtEnd,*TEXT=dateInfo
                endDate.SetAsString Using dateInfo,"%Y-%m-%dT%H:%M",1
                endDate.GetAsString Giving eventRecord.endTime Using "%Y%m%dT%H%M%S"

                endDate.Compare Using startDate
                IF              LESS
                ALERT           CAUTION,"The end date is before the start date !",result,"Calendar",
                RETURN
                ENDIF
 
                curDate.SetToNow
                curDate.GetAsString Giving eventRecord.timeStamp Using "%Y%m%dT%H%M%SZ",1

                PACK            jsCall  Using "calGetGuid();"
                Client.jsrun    Giving eventRecord.UID Using jsCall
                Client.FlushMessages

                SET             eventRecord.isValid

                FUNCTIONEND
*................................................................
.
. Create a link with the the ICS information to download
.
IcsLink         LFUNCTION
fileName        DIM             40
                ENTRY
htmlData        DIM             4096
line            DIM             100
result          FORM            3

                IF              (eventRecord.isValid)
                CLEAR           htmlData
                APPEND          "<div>",htmlData
                PACK            line, "<a href='#' download='", fileName, "' id='icsdl'>Download ICS file</a>"
                APPEND          line,htmlData
                APPEND          "</div>",htmlData
                APPEND          "<script>",htmlData
                APPEND          " var icsData = 'BEGIN:VCALENDAR\n' + ",htmlData
                APPEND          "   'VERSION:2.0\n' + ",htmlData
                APPEND          "   'PRODID:-//PLB Calendar Event//EN\n' + ",htmlData

                APPEND          "   'BEGIN:VEVENT\n' + ",htmlData
                PACK            line, "   'UID:", eventRecord.UID, "\n' + "
                APPEND          line,htmlData
                PACK            line, "   'DTSTAMP:", eventRecord.timeStamp, "\n' + "
                APPEND          line,htmlData
                PACK            line, "   'DTSTART:", eventRecord.startTime, "\n' + "
                APPEND          line,htmlData
                PACK            line, "   'DTEND:", eventRecord.endTime, "\n' + "
                APPEND          line,htmlData
                PACK            line, "   'SUMMARY:", eventRecord.summary, "\n' + "
                APPEND          line,htmlData

                COUNT           result,eventRecord.location
                IF              NOT ZERO
                PACK            line, "   'LOCATION:", eventRecord.location, "\n' + "
                APPEND          line,htmlData
                ENDIF

                COUNT           result,eventRecord.description
                IF              NOT ZERO
                PACK            line, "   'DESCRIPTION:", eventRecord.description, "\n' + "
                APPEND          line,htmlData
                ENDIF

                APPEND          "   'END:VEVENT\n' + ",htmlData
                APPEND          "   'END:VCALENDAR\n'; ",htmlData
                APPEND          " var icsLk = document.getElementById('icsdl');",htmlData
                APPEND          " icsLk.href = 'data:text/calendar;charset=utf-8,' + encodeURIComponent(icsData);",htmlData
                APPEND          "</script>",htmlData
                RESET           htmlData

                calHtmlResult.InnerHtml Using htmlData
                ENDIF
                FUNCTIONEND
*................................................................
.
. Write the start of the ICS file
.
IcsOpenFile     LFUNCTION
fileName        DIM             ^
                ENTRY
                IF              (eventRecord.isValid)
                PREP            icsFile,fileName
                WRITE           icsFile,Seq;"BEGIN:VCALENDAR"
                WRITE           icsFile,Seq;"VERSION:2.0"
                WRITE           icsFile,Seq;"PRODID:-//PLB Calendar Event//EN"
                ENDIF

                FUNCTIONEND

*................................................................
.
. Write one event into the ICS file
.
IcsWriteEvent   LFUNCTION
                ENTRY
result          FORM            4

                IF              (eventRecord.isValid)
                WRITE           icsFile,Seq;"BEGIN:VEVENT"
                WRITE           icsFile,Seq;"UID:",*LL,eventRecord.UID
                WRITE           icsFile,Seq;"DTSTAMP:",*LL,eventRecord.timeStamp
                WRITE           icsFile,Seq;"DTSTART:",*LL,eventRecord.startTime
                WRITE           icsFile,Seq;"DTEND:",*LL,eventRecord.endTime
                WRITE           icsFile,Seq;"SUMMARY:",*LL,eventRecord.summary

                COUNT           result,eventRecord.location
                IF              NOT ZERO
                WRITE           icsFile,Seq;"LOCATION:",*LL,eventRecord.location
                ENDIF

                COUNT           result,eventRecord.description
                IF              NOT ZERO
                WRITE           icsFile,Seq;"DESCRIPTION:",*LL,eventRecord.description
                ENDIF

                WRITE           icsFile,Seq;"END:VEVENT"
                ENDIF

                FUNCTIONEND

*................................................................
.
. Write the end of the ICS file
.
IcsCloseFile    LFUNCTION
                ENTRY
                IF              (eventRecord.isValid)
                WRITE           icsFile,Seq;"END:VCALENDAR"
                CLOSE           icsFile
                ENDIF

                FUNCTIONEND

*................................................................
.
. Build an ICS file and an ICC link
.
IcsBuild        LFUNCTION
                ENTRY
                CALL            FetchEventData
                CALL            IcsOpenFile Using "sample.ics"
                CALL            IcsWriteEvent
                CALL            IcsCloseFile
                CALL            IcsLink Using "sample.ics"
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



