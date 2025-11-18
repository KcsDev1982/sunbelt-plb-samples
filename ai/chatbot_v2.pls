*---------------------------------------------------------------
.
. Program Name: chatbot_v2.pls
. Description:  PL/B AI and speech recognition version 2
.
. Revision History:
.
. Date: 07/23/2025 SM
. Original code
.

                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc

// Runtime status variables
isGui           BOOLEAN
isWebSrv        BOOLEAN
isPlbSrv        BOOLEAN
isWebview       BOOLEAN
isWebCliApp     BOOLEAN
isSmallScreen   BOOLEAN

// Global data
mainForm        PLFORM          chatbot_v2.plf
chatDtMessages  DATATABLE
Client          CLIENT
jsonData        DIM             200
emptyAns        INIT            "<<empty>>"

                %ENCRYPTON
apiKey          INIT            "Add your OpenAI API key here"
                %ENCRYPTOFF

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
. Card Button Event
.
CardBtn         LFUNCTION
                ENTRY
eventResult     FORM            10
item            FORM            5
subItem         FORM            5

                EVENTINFO       0,result=eventResult
                CALC            item = ( eventResult / 100 )
                CALC            subItem = ( eventResult - ( item * 100 ) )
                chatDtMessages.DeleteRow USING item
                FUNCTIONEND
*................................................................
.
. Add one card
.
AddCard         LFUNCTION
type            DIM             20
info            DIM             ^
                ENTRY
title           DIM             10
footer          DIM             30
dateTime        DATETIME
cleanInfo       DIM             64000

                dateTime.SetToNow Using  $TRUE
                dateTime.GetAsString Giving footer Using "Time: %h:%M:%S %a"
                
                                // For questions, wrap in pre tag for readability
                IF              (type == "Question")
                PACK            cleanInfo,"<pre class='bg-light text-secondary ms-4 shadow-sm pre-question'>":
                                info,"</pre>"
                MOVE            "Me", title
                ELSE
                                // For responses
                PACK            cleanInfo,"<pre class='bg-light shadow-sm pre-response'>":
                                info,"</pre>"
                MOVE            "Chatbot", title
                ENDIF
                
                chatDtMessages.AddRow USING title:
                                *subitem1=type:
                                *subitem2=cleanInfo:
                                *subitem3="Remove":
                                *subitem4=footer
                FUNCTIONEND
 
*................................................................
.
. SetupCards
.
SetupCards      LFUNCTION
                ENTRY
                
                CREATE          chatDtMessages
                chatDtMessages.AddColumn Using 0, *ContentType=$TC_HEADER
                chatDtMessages.AddColumn Using 1, *ContentType=$TC_TITLE
                chatDtMessages.AddColumn Using 2, *ContentType=$TC_DETAILS
                chatDtMessages.AddColumn Using 3, *ContentType=$TC_BUTTON1
                chatDtMessages.AddColumn Using 4, *ContentType=$TC_FOOTER
                chatDtMessages.AddColumn Using 5
                
                EVENTREG        chatDtMessages,$UPDATED,CardBtn
                 
                FUNCTIONEND

*................................................................
.
. Ask the question to chatGPT
.
AskQuestion     LFUNCTION
                ENTRY
chars           FORM            4
jsCall          DIM             8192
decryptedApiKey DIM             200
question        DIM             8192
result          FORM            4

                GETPROP         chatEdtQuestion, text=question
                CHOP            question
                COUNT           chars from question
                
                chatHtmlSpeech.SetAttr using "chatResp","text",emptyAns // Clear previous response
                
                MOVE            apiKey,decryptedApiKey // Decrypt API key
                DECRYPT         decryptedApiKey

                IF              (chars > 0 AND chars < 3000 ) // Limit question to 3000 characters
                CALL            AddCard Using "Question",question
.
. Setup and call the async javascript routine
.
                PACK            jsCall Using "askGpt('",question,"','",decryptedApiKey,"');"
                Client.jsrun    Using jsCall
                Client.FlushMessages
                ELSE
                PACK            jsCall Using "console.log('",Question too long,"');"
                Client.jsrun    Using jsCall
                Client.FlushMessages
                ENDIF
                
                SETPROP         chatEdtQuestion, text=""
                 
                FUNCTIONEND

*................................................................
.
. Speech event and chat response event handler
.
ChatEvent       LFUNCTION
                ENTRY
data            DIM             64000
cleanData       DIM             64000
readyFlag       DIM             10
result          FORM            4

                SCAN            "chatResp" in JsonData
                IF              EQUAL
                
                                // Check if the response is ready
                chatHtmlSpeech.GetAttr giving readyFlag using "chatResp","data-ready"
                CHOP            readyFlag
                
                IF              (readyFlag == "true")
                                // Try methods in order until we get content
                
                                // Method 1: Try processed content
                                chatHtmlSpeech.GetAttr giving data using "chatResp","data-processed"
                CHOP            data
                
                                // Method 2: If processed is empty, try innerHTML
                                IF          (data == "" OR data == emptyAns)
                chatHtmlSpeech.GetAttr giving data using "chatResp","innerHTML"
                CHOP            data
                ENDIF
                
                                // Method 3: If still empty, try text content
                                IF          (data == "" OR data == emptyAns)
                chatHtmlSpeech.GetAttr giving data using "chatResp","text"
                CHOP            data
                ENDIF
.                
. If we got content by any method, add the card
.
                IF              (data != emptyAns AND data != "")
                MOVE            data,cleanData
                CALL            AddCard Using "Response",cleanData
                SETFOCUS        chatEdtQuestion
                ENDIF
                ENDIF
                ENDIF
                
                SCAN            "chatQues" in JsonData
                IF              EQUAL
                chatHtmlSpeech.GetAttr giving data using "chatQues","text"
                CHOP            data
                IF              (data != emptyAns)
                SETPROP         chatEdtQuestion, text=data
                SETFOCUS        chatEdtQuestion
                ENDIF
                ENDIF
                
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
                CALL            SetupCards
                chatDtMessages.HtmlBind Using chatHtmlMessages,$TBL_HTML_CARD
                
                CALL            LoadSupportHtml Using chatHtmlSpeech,"chatbot_v2_sup.html" // Load the HTML file
                
                EVENTREG        chatHtmlSpeech,$JQueryEvent,ChatEvent,ARG1=JsonData // Register event handler for JavaScript events
                
                chatFrmMain.SetAsClient
                Client.SetUTF8Convert Using 0
                 
                FUNCTIONEND
