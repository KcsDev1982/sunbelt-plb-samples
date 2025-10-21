*---------------------------------------------------------------
.
. Program Name: gcalender_api.pls
. Description:  Sample google calendar support
.               Calendar API support
.
. Revision History:
.
. Revision History:
.
. Date: 10/20/2025
. Original code
.
. For more detailed information, see the sample code at: 
.
.      https://developers.google.com/workspace/calendar/api/quickstart/js
.
.      From the sample web page see the "Set up your environment" section
.      to create the needed keys.
.
.	YOUR_CLIENT_ID: the client ID that you created when you authorized credentials
.	YOUR_API_KEY: the API key that you created as a Prerequisite 
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
mainForm        PLFORM          gcalendar_api.plf
Client          CLIENT

isSignedIn      BOOLEAN
isAutorized	BOOLEAN

// TODO(developer): Set to client ID and API key from the Developer Console
                %ENCRYPTON
ecliKey         INIT            "YOUR_CLIENT_ID"
eapiKey         INIT            "YOUR_API_KEY"
ecalId          INIT            "primary"	// Can be replaced by specific calendar id
                %ENCRYPTOFF

.................................................
.
. Format of JSON event
.
. { 'summary': 'Google I/O 2025', 
.   'location': '800 Howard St., San Francisco, CA 94103',
.   'description': 'A chance to hear more about developer products.',
.   'start': { 'dateTime': '2025-08-09T09:00:00-00:00' },
.   'end': { 'dateTime': '2025-08-09T17:00:00-00:00' } }
.
eventRecord     RECORD
isValid         BOOLEAN
startTime       DIM             25      // 'start'
endTime         DIM             25      // 'end'
summary         DIM             40      // 'summary'
location        DIM             80      // 'location'
description     DIM             40      // 'description'
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

                htmlCtl.InnerHtml Using htmlBuffer,$HTML_HAS_EVENTS

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
                startDate.GetAsString Giving eventRecord.startTime Using "%Y-%m-%dT%H:%M:%S-00:00"

                GETPROP         calEdtEnd,*TEXT=dateInfo
                endDate.SetAsString Using dateInfo,"%Y-%m-%dT%H:%M",1
                endDate.GetAsString Giving eventRecord.endTime Using "%Y-%m-%dT%H:%M:%S-00:00"

                endDate.Compare Using startDate
                IF              LESS
                ALERT           CAUTION,"The end date is before the start date !",result,"Calendar",
                RETURN
                ENDIF
 
                SET             eventRecord.isValid

                FUNCTIONEND

*................................................................
.
. Create a JSON event record
.
.
AddEvent        LFUNCTION
                ENTRY
jsCall          DIM             4096
eventData	DIM		2048
calId          DIM              200
result          FORM            3

		CALL		FetchEventData

		IF              (eventRecord.isValid)
                CLEAR           eventData
                APPEND          "{ 'summary': '",eventData
		APPEND		eventRecord.summary,eventData

 		COUNT           result,eventRecord.location
                IF              NOT ZERO
		APPEND		"', 'location': '",eventData
                APPEND          eventRecord.location,eventData
                ENDIF

                COUNT           result,eventRecord.description
                IF              NOT ZERO
		APPEND		"', 'description': '",eventData
                APPEND          eventRecord.description,eventData
                ENDIF

		APPEND		"', 'start': { 'dateTime': '",eventData
		APPEND          eventRecord.startTime,eventData
		APPEND		"' }, 'end': { 'dateTime': '",eventData
		APPEND          eventRecord.endTime,eventData
		APPEND		"' } }",eventData
		RESET		eventData

                MOVE            ecalId,calId
                DECRYPT         calId

		PACK            jsCall Using "calSendMsg( 3 ,",eventData,",'",calId,"');"

                Client.jsrun    Using jsCall
                Client.FlushMessages
		ENDIF

                FUNCTIONEND

*................................................................
.
. Sign into the user's google account
.
SignIn          LFUNCTION
                ENTRY
jsCall          DIM             4096
cliKey          DIM             200
apiKey          DIM             200

                IF              (!isSignedIn)
                MOVE            ecliKey,cliKey
                DECRYPT         cliKey
                MOVE            eapiKey,apiKey
                DECRYPT         apiKey
                PACK            jsCall Using "calSendMsg( 0 ,'",cliKey,"','",apiKey,"');"
                Client.jsrun    Using jsCall
                Client.FlushMessages
                PAUSE           "1"
                SET             isSignedIn
                ENDIF

                Client.jsrun    Using "calSendMsg( 1, {}, ' ' );"
                Client.FlushMessages
                SET             isAutorized
                FUNCTIONEND

*................................................................
.
. Sign out of the user's google account
.
SignOut         LFUNCTION
                ENTRY
                IF              ( isAutorized )
                Client.jsrun    Using "calSendMsg( 2, {}, ' ' );"
                Client.FlushMessages
                CLEAR           isAutorized
                ENDIF
                FUNCTIONEND
*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
result          FORM            4
jsCall          DIM             4096
 

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


                CALL            LoadSupportHtml Using calHtmlIdx,"gcalendar_adm.html"
                CALL            LoadSupportHtml Using calHtmlArea,"gcalendar_sup.html"

                calFrmMain.SetAsClient
                Client.SetUTF8Convert Using 0

 

                FUNCTIONEND



