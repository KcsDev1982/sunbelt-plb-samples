*---------------------------------------------------------------
.
. Program Name: ai_examples.pls
. Description:  PL/B AIOBJECT examples using ChatGPT
.
. Revision History:
.
. Date: 03/12/2026 WK
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
mainForm        PLFORM          aiobj_examples.plf
chatDtMessages  DATATABLE
chatAI          AIOBJECT
Client          CLIENT

Instruct        INIT            "You are ChatGPT, an helpful assistant":
                                "- Providing accurate general knowledge.":
                                "- Offering extensive help with programming, web development, and all major coding languages.":
                                "**Response Formatting Guidelines:**":
                                "1. For programming, configuration, or technical markup examples:":
                                "- Always wrap examples in fenced code blocks with the correct language identifier ":
                                "(e.g., \`\`\`python, \`\`\`javascript, \`\`\`html, \`\`\`bash, \`\`\`yaml).":
                                "- For code or technical output not fitting a standard language, use a \`\`\`text code block.":
                                "2. For general knowledge or non-coding replies:":
                                "- Use concise, readable Markdown (e.g., lists, tables, bold or italic text), focusing on clarity for users.":
                                "3. Never use raw or rendered markup outside of code fences. All technical or code-based content must be inside properly labeled code blocks.":
                                "4. Always tailor formatting to the subject: code and technical data in code blocks; all other information in easy-to-read Markdown.":
                                "**Overall:**":
                                "- Maximize clarity and readability in all responses for users."

fileAI          AIOBJECT
fileName        DIM             256
FileInstruct    INIT            "You are a data processing bot. You don't talk, you don't explain your answers. ":
                                "Your only output is made of data to satisfy the received request."

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
. Pirate Letter Example
.
AskPirateLetter LFUNCTION
                ENTRY
question        INIT            "Write a letter to Mr Bill K saying that he owes 20 dollars for a coat."
bodyText        DIM             10240
body            JSONDATA

 
                body.SetString  Using "reasoning.effort","low"
                body.SetString  Using "input[0].role","developer"
                body.SetString  Using "input[0].content","Talk like a pirate."
                body.SetString  Using "input[1].role","user"
                body.SetString  Using "input[1].content",question

                body.GetString  Giving bodyText Using ""
                CALL            AddCard Using "Question",question

                chatAI.Question Using "",bodyText

                FUNCTIONEND

*................................................................
.
. Image Analysis
.
AskImage        LFUNCTION
                ENTRY
question        INIT            "What is the text in this image ?"
bodyText        DIM             10240
body            JSONDATA

                body.SetString  Using "input[0].role","user"
                body.SetString  Using "input[0].content[0].type","input_text"
                body.SetString  Using "input[0].content[0].text",question
                body.SetString  Using "input[0].content[1].type","input_image"
                body.SetString  Using "input[0].content[1].image_url","https://www.sunbelt-plb.net/aii/scan1.jpg"
                body.GetString  Giving bodyText Using ""

                CALL            AddCard Using "Question",question

                chatAI.Question Using "",bodyText

                FUNCTIONEND

*................................................................
.
. Ask the question to chatGPT
.
AskQuestion     LFUNCTION
                ENTRY
action          FORM            2
quest1          INIT            "Extract the name, address and phone number from the following and put it into a JSON format ":
                                " Sam Smith 722 456 2256 who lives at 20 cherry lane North Heford CA USA"
quest2          INIT            "Translate the following to german ":
                                " I would like to order a salad and a glass of water, please. "
quest3          INIT            "What is number contained in the following text in numeric format. Please be brief: one thousand and sixy-seven"
quest4          INIT            "Create a table for user data with columns: Name and Phone Number and format it as a valid XML document for Excel.":
                                "The information to use is Bill, 555 122 2233 Ed, 555 345 1234"

                chatCbType.GetCurSel Giving action

                SWITCH          Action

                CASE            0
                CALL            AddCard Using "Question",quest1
                chatAI.Question Using quest1
                SETPROP         chatBtnSend,*Enabled=0

                CASE            1
                CALL            AskImage
                SETPROP         chatBtnSend,*Enabled=0

                CASE            2
                CALL            AskPirateLetter
                SETPROP         chatBtnSend,*Enabled=0

                CASE            3
                CALL            AddCard Using "Question",quest2
                chatAI.Question Using quest2
                SETPROP         chatBtnSend,*Enabled=0

                CASE            4
                CALL            AddCard Using "Question",quest3
                chatAI.Question Using quest3
                SETPROP         chatBtnSend,*Enabled=0

                CASE            5
                CALL            AddCard Using "Question",quest4
                MOVE            "sample1.xml", fileName
                fileAI.Question Using quest4
                SETPROP         chatBtnSend,*Enabled=0

                ENDSWITCH
                FUNCTIONEND

*................................................................
.
. Got a AI response
.
AiChange        LFUNCTION
                ENTRY
aiRes           JSONDATA
cleanData       DIM             64000

                chatAI.Response Giving cleanData

                aiRes.parse     Using cleanData
                aiRes.getstring Giving cleanData using "output[1].content[0].text"

                CALL            AddCard Using "Response",cleanData
                SETFOCUS        chatCbType
                SETPROP         chatBtnSend,*Enabled=1
                FUNCTIONEND

*................................................................
.
. Got a AI response that need to be written to an file
.
AiFileOut       LFUNCTION
                ENTRY
aiRes           JSONDATA
cleanData       DIM             64000
outFile         FILE
Seq             FORM            "-1"

                fileAI.Response Giving cleanData

                aiRes.parse     Using cleanData
                aiRes.getstring Giving cleanData using "output[1].content[0].text"

                ERASE           fileName
                PREP            outFile,fileName
                WRITE           outFile,Seq;cleanData
                CLOSE           outFile

                PACK            cleanData, "generated file: ",fileName
                CALL            AddCard Using "Response",cleanData

                SETFOCUS        chatCbType
                SETPROP         chatBtnSend,*Enabled=1
                FUNCTIONEND

*................................................................
.
. Setup the AIOBJECT
.
AiSetup         LFUNCTION
                ENTRY
decryptedApiKey DIM             200

                MOVE            apiKey,decryptedApiKey // Decrypt API key
                DECRYPT         decryptedApiKey
.
. Create an AI object general questioning
.
                chatAI.Initialize Using "gpt-5",decryptedApiKey,Instruct
                EVENTREGISTER   chatAI,$ANSWER,AiChange
.
. Create an AI object for file output
.
                fileAI.Initialize Using "gpt-5",decryptedApiKey,FileInstruct
                EVENTREGISTER   fileAI,$ANSWER,AiFileOut

                chatCbType.ResetContent
.
. Setup the sample names
.
                chatCbType.AddString Using "Address Extration"
                chatCbType.AddString Using "Image Analysis"
                chatCbType.AddString Using "Pirate Letter"
                chatCbType.AddString Using "Translation"
                chatCbType.AddString Using "Text to Number Translation"
                chatCbType.AddString Using "Spreadsheet generation"
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
                
                CALL            AiSetup
                
                chatFrmMain.SetAsClient
                Client.SetUTF8Convert Using 0
                 
                FUNCTIONEND
