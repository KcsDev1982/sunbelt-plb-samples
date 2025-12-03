*---------------------------------------------------------------
.
. Program Name: sunbelt_chat_resp.pls
. Description:  PL/B AI ChatBot Sample Using Responses API
.
. Revision History:
.
. Date: 08/13/2025 SM
. Original code
.
. To download pictures via right click set the following
. in the PLBWIN.INI file
.
. PLBWIN_WVDEBUG=ON
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc


*---------------------------------------------------------------
.
. Runtime status variables
.
isGui           BOOLEAN
isWebSrv        BOOLEAN
isPlbSrv        BOOLEAN
isWebview       BOOLEAN
isWebCliApp     BOOLEAN
isSmallScreen   BOOLEAN

*---------------------------------------------------------------
.
. Global data
.
mainForm        PLFORM          sunbelt_chat_resp.plf
chatDtMessages  DATATABLE
Client          CLIENT

                %ENCRYPTON
apiKey          INIT            "Add your OpenAI API key here"
                %ENCRYPTOFF

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

                GETMODE         *GUI=isGui // Check for character mode runtime
                IF              (isGui)
                CLOCK           VERSION,runtimeData // Check windows console
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

                IF              (isWebSrv) // Check for a small screen (such as iphone)
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

                GETFILE         htmlFile,TxtName=fullFileName // Read the registration file into a buffer
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
. SetFocus - set focus on prompt input area and set tab IDs
.
SetFocus        LFUNCTION
                ENTRY
        
                SETFOCUS        chatHtmlMessages
                chatHtmlMessages.Focus Using "promptInput"
 
                chatHtmlMessages.SetAttr using "promptInput", *NAME="data-plbtabid", *VALUE="1"
                chatHtmlMessages.SetAttr using "sendBtn", *NAME="data-plbtabid", *VALUE="2"
                chatHtmlMessages.SetAttr using "embedAddBtn", *NAME="data-plbtabid", *VALUE="3"
                chatHtmlMessages.SetAttr using "createImage", *NAME="data-plbtabid", *VALUE="4"
                chatHtmlMessages.SetAttr using "addContextBtn", *NAME="data-plbtabid", *VALUE="5"
                chatHtmlMessages.SetAttr using "deleteFileContextBtn", *NAME="data-plbtabid", *VALUE="6"
                chatHtmlMessages.SetAttr using "deleteAllEmbeddingsBtn", *NAME="data-plbtabid", *VALUE="7"
                chatHtmlMessages.SetAttr using "modelPicker", *NAME="data-plbtabid", *VALUE="98"
                chatHtmlMessages.SetAttr using "settingsBtn", *NAME="data-plbtabid", *VALUE="99"
                chatHtmlMessages.SetAttr using "clearChat", *NAME="data-plbtabid", *VALUE="100"
                chatHtmlMessages.SetAttr using "confirmClearChatBtn", *NAME="data-plbtabid", *VALUE="101"
                chatHtmlMessages.SetAttr using "cancelClearChatBtn", *NAME="data-plbtabid", *VALUE="102"
 
                chatHtmlMessages.UpdateEvents
 
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
result          FORM            4
jsCall          DIM             4096
decryptedApiKey DIM             200

                CALL            CheckStatus
                IF              (!isGui)
                KEYIN           "This runtime can't run this program. ",result
                STOP
                ENDIF
                
                IF              (!isWebview)
                ALERT           STOP,"This program requires WebView support.",result
                STOP
                ENDIF

                IF              (isWebCliApp || isSmallScreen) // On smaller screens change to % positioning for left and width
                SETMODE         *PERCENTCONVERT=1
                ENDIF

                FORMLOAD        mainForm
 
                CALL            LoadSupportHtml USING chatHtmlMessages,"sunbelt_chat_resp_sup.html"
                CALL            SetFocus
 
                chatFrmMain.SetAsClient
                Client.SetUTF8Convert Using 0
 
                MOVE            apiKey,decryptedApiKey
                DECRYPT         decryptedApiKey
                PACK            jsCall Using "setApiKey('",decryptedApiKey,"');"  // set and give API key to the script
                Client.jsrun    USING jsCall
                Client.FlushMessages
 
                FUNCTIONEND
