*---------------------------------------------------------------
.
. Program Name: gcalender_ics.pls
. Description:  Sample google calendar support
.               Product a CSV file
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

		CIFNDEF		$LV_CSVWR_NOANSI2OEM
$LV_CSVWR_NOANSI2OEM Integer 4,"0x100"
		CENDIF

// Runtime status variables
isGui           BOOLEAN
isWebSrv        BOOLEAN
isPlbSrv        BOOLEAN
isWebview       BOOLEAN
isWebCliApp     BOOLEAN
isSmallScreen   BOOLEAN

// Global data
mainForm        PLFORM          gcalendar_csv.plf
Client          CLIENT

eventRecord     RECORD
isValid         BOOLEAN
startDate       DIM             10
startTime       DIM             8
endDate         DIM             10
endTime         DIM             8
summary         DIM             40
location        DIM             80
description     DIM             40
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
. Fetch the event data fron the form
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
                startDate.GetAsString Giving eventRecord.startDate Using "%m/%d/%Y"
                startDate.GetAsString Giving eventRecord.startTime Using "%h:%M %a"

                GETPROP         calEdtEnd,*TEXT=dateInfo
                endDate.SetAsString Using dateInfo,"%Y-%m-%dT%H:%M",1
                endDate.GetAsString Giving eventRecord.endDate Using "%m/%d/%Y"
                endDate.GetAsString Giving eventRecord.endTime Using "%h:%M %a"

                endDate.Compare Using startDate
                IF              LESS
                ALERT           CAUTION,"The end date is before the start date !",result,"Calendar",
                RETURN
                ENDIF

                SET             eventRecord.isValid

                FUNCTIONEND


*................................................................
.
. CReate the CSV file
.
. Required Headers:
.     Subject: The name of the event.
.     Start Date: The date the event begins (e.g., "05/30/2020").
.     Start Time: The time the event begins (e.g., "10:00 AM").
. Optional Headers:
.     End Date: The date the event ends (e.g., "05/30/2020").
.     End Time: The time the event ends (e.g., "1:00 PM").
.     All Day Event: A boolean value indicating if it's an all-day event (e.g., "True" or "False").
.     Description: A text field for event details.
.     Location: The location of the event.
.     Private: A boolean value indicating if the event is private.
.
. Important Considerations:
.    File Size: Google Calendar only accepts CSV files up to 1MB in size.
.    Formatting: Ensure the date and time formats are correct and consistent.
.    Encoding: CSV files should be encoded in UTF-8.
.    Delimiter: Commas are used as delimiters between fields. If commas are needed within a field, enclose that field in quotation marks.
.    Importing: Follow Google Calendar's import instructions, selecting the correct calendar and file.
.
.
CsvBuild        LFUNCTION
                ENTRY
                calLvEvents.SaveCsvFile Using "sample.csv",*Options=($LV_CSVWR_QUOTED+$LV_CSVWR_OUTPUTHEADER+$LV_CSVWR_NOANSI2OEM)
                FUNCTIONEND

*................................................................
.
. Add one event to the lisview
.
AddEvent        LFUNCTION
                ENTRY
                CALL            FetchEventData

                IF              ( eventRecord.isValid )
                calLvEvents.InsertItemEx Using eventRecord.summary:
                                *subitem1=eventRecord.startDate,*subitem2=eventRecord.startTime:
                                *subitem3=eventRecord.endDate,*subitem4=eventRecord.endTime:
                                *subitem5=eventRecord.location,*subitem6=eventRecord.description
                ENDIF
                FUNCTIONEND

*................................................................
.
. Clear all events in the lisview
.
ClearEvents     LFUNCTION
                ENTRY
                calLvEvents.DeleteAllItems
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



