*---------------------------------------------------------------
.
. Program Name: custinvoice
. Description:  Sample customer invoice using the HTML UI
.
. Revision History:
.
. 21 Oct 26 whk
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
htmlFrmMain     WINDOW
htmlHctlMain    HTMLCONTROL
Client          CLIENT
Runtime         RUNTIME
jsonData        DIM             200
htmlData        DIM             10240
tableHtml       DIM             20480
rowHtml         DIM             1024
items           DATATABLE
delim           INIT            0x7F

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

*
.Form Instantiation
.
CreateMainForm  LFUNCTION
                ENTRY
*
.Object Creates
.
                CREATE          htmlFrmMain=0:1000:0:1200,*TITLE="Customer Invoice App":
                                Appearance=2:
                                AutoRedraw=1:
                                AutoScroll=0:
                                BGColor=$BtnFace:
                                ButtonEnterKey=0:
                                Caption=1:
                                ClipCtrl=0:
                                DockPadB=0:
                                DockPadL=0:
                                DockPadR=0:
                                DockPadT=0:
                                Enabled=1:
                                FGColor=0x00000000:
                                FloatMenu=0:
                                Font="'>MS Sans Serif'(10.0)":
                                GridAlign=0:
                                GridSizeH=10:
                                GridSizeV=10:
                                Icon=0:
                                InTaskBar=0:
                                MaxBox=1:
                                MDIBorder=0:
                                MDIHeight=0:
                                MDILeft=0:
                                MDIScroll=3:
                                MDITop=0:
                                MDIWidth=0:
                                MinBox=1:
                                MinScrollH=0:
                                MinScrollV=0:
                                MinWidth=0:
                                NegBorders=0:
                                NegMenus=0:
                                NoMenuResize=0:
                                ObjectId=0:
                                RibMode=0:
                                RightToLeft=0:
                                Scrollbar=3:
                                SysMenu=1:
                                TopMost=0:
                                Units=5:
                                Visible=0:
                                WebMode=3:
                                WinBorder=6:
                                WinPos=2:
                                WinType=5:
                                ZOrder=10
.
                CREATE          htmlFrmMain;htmlHctlMain=0:1000:0:1200:
                                Anchor=5:
                                BGColor=$BtnFace:
                                CodePage=1:
                                Dock=3:
                                Enabled=1:
                                ObjectId=0:
                                Scrollbar=1:
                                TabID=20:
                                Visible=0:
                                WebMode=3:
                                WebObject=1:
                                WebPosition=0:
                                ZOrder=20


*
.Event Registrations
.
                EVENTREG        htmlFrmMain,$Close,Close_htmlFrmMain
*
.Object Activations
.
                ACTIVATE        htmlHctlMain
                ACTIVATE        htmlFrmMain
.
                FUNCTIONEND
*
.Event Routines
.
.===============================================================================
Close_htmlFrmMain LFUNCTION
                ENTRY
                STOP
                FUNCTIONEND

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
. Make one row of the HTML table
.
MakeRow         LFUNCTION
tablePos        FORM            2
totalF          FORM            ^
                ENTRY
rowNum          DIM             2
description     DIM             40
count           DIM             4
countF          FORM            4
cost            DIM             10
costF           FORM            5.2
total           DIM             10

                MOVE            tablePos,rowNum
                DECR            tablePos

                items.GetRowTextAll Giving rowHtml USING tablePos, delim
                EXPLODE         rowHtml, delim, description, count, cost

                MOVE            cost to costF
                MOVE            costF to cost
                SQUEEZE         cost,cost

                MOVE            count to countF
                MULT            countF,costF
                ADD             costF to totalF
 
 
                MOVE            costF to total
                SQUEEZE         total,total

                SQUEEZE         rowNum,rowNum
                PACK            rowHtml Using "<tr><td>",rowNum,"</td>":
                                "<td><input type='text' id='ides",rowNum,"' data-plbevent='change' class='form-control' value='",description,"' ></td>":
                                "<td><input type='number' id='icnt",rowNum,"' data-plbevent='change' class='form-control text-end' value='",count,"' min='1'></td>":
                                "<td><div class='input-group'><span class='input-group-text'>$</span><input type='number' id='icos",rowNum:
                                "' data-plbevent='change' class='form-control text-end' value='",cost,"' min='0'></div></td>":
                                "<td class='text-end fw-bold'>$",total,"</td>":
                                "<td class='text-center'><button id='irem",rowNum,"' data-plbevent='click' class='btn btn-danger btn-sm'>Remove</button></td></tr>"
                FUNCTIONEND

*................................................................
.
. Generate the HTML table
.
MakeTable       LFUNCTION
                ENTRY
totalF          FORM            5.2
taxF            FORM            5.2
total           DIM             10
rowCount        FORM            2
curCount        FORM            2
taxRate         FORM            "10"

                htmlHctlMain.GetValue Giving total Using "tax"
                SQUEEZE         total,total
                MOVE            total,taxRate

                CLEAR           tableHtml
                items.GetRowCount Giving rowCount
                IF              (rowCount > 0)
                FOR             curCount,1,rowCount
                CALL            MakeRow USING curCount,totalF
                APPEND          rowHtml,tableHtml
                REPEAT
                RESET           tableHtml
                ENDIF

                htmlHctlMain.SetHtml Using "invoiceItems", tableHtml
                htmlHctlMain.UpdateEvents

                MOVE            totalF to total
                SQUEEZE         total,total
                MOVE            ("$"+total),total
                htmlHctlMain.SetText Using "subTotal",total

                CALC            taxF=(totalF/100*taxRate)
                MOVE            taxF to total
                SQUEEZE         total,total
                MOVE            ("$"+total),total

                htmlHctlMain.SetText Using "totalTax",total

                ADD             taxF,totalF
                MOVE            totalF to total
                SQUEEZE         total,total
                MOVE            ("$"+total),total
                htmlHctlMain.SetText Using "total",total
                FUNCTIONEND

*................................................................
.
. Create the DATATABLE for the invoice items
.
CreateTable     LFUNCTION
                ENTRY
                CREATE          items
                items.AddColumn Using 0 // Name
                items.AddColumn Using 1 // quantity
                items.AddColumn Using 2 // Cost

                items.AddRow    Using   "Product A", *Row=99, *subitem1="2", *subitem2="10"
                items.AddRow    Using   "Service B", *Row=99, *subitem1="1", *subitem2="50"

                CALL            MakeTable

                FUNCTIONEND
*................................................................
.
. Event handler
.
HctlEvent       LFUNCTION
                ENTRY
editData        DIM             40
result          FORM            5
eventInfo       JSONDATA
row             FORM            2
 
 
                eventInfo.parse Using JsonData
 
                eventInfo.GetString Giving editData Using "id"
 
                IF              (editData LIKE "ides%")
                BUMP            editData, 4
                MOVE            editData to row
                RESET           editData
                htmlHctlMain.GetValue Giving editData   Using editData
                items.SetRowText Using (row-1), editData, 0
                ENDIF

                IF              (editData LIKE "icnt%")
                BUMP            editData, 4
                MOVE            editData to row
                RESET           editData
                htmlHctlMain.GetValue Giving editData   Using editData
                items.SetRowText Using (row-1), editData, 1
                CALL            MakeTable
                ENDIF

                IF              (editData LIKE "icos%")
                BUMP            editData, 4
                MOVE            editData to row
                RESET           editData
                htmlHctlMain.GetValue Giving editData Using editData
                items.SetRowText Using (row-1), editData, 2
                CALL            MakeTable
                ENDIF

                IF              (editData LIKE "irem%")
                BUMP            editData, 4
                MOVE            editData to row
                RESET           editData
                items.DeleteRow Using (row-1)
                CALL            MakeTable
                ENDIF
                
                SWITCH          editData
                CASE            "addItemBtn"
                items.AddRow    Using   "", *Row=99, *subitem1="1", *subitem2="0.00"
                CALL            MakeTable
           
                CASE            "generateInv"

                CASE            "printInv"

                CASE            "clearInv"
                items.DeleteAllRows
                CALL            MakeTable

                CASE            "tax"
                CALL            MakeTable
 
                ENDSWITCH

 
                FUNCTIONEND

*................................................................
.
. Set up the events on the HTML objects and register the event handler
.
HctlSetupEvents LFUNCTION
                ENTRY
                EVENTREG        htmlHctlMain,$JQueryEvent,HctlEvent,ARG1=JsonData
                htmlHctlMain.SetEvents using "addItemBtn","click"
                htmlHctlMain.SetEvents using "generateInv","click"
                htmlHctlMain.SetEvents using "printInv","click"
                htmlHctlMain.SetEvents using "clearInv","click"
                htmlHctlMain.SetEvents using "tax","change"
                htmlHctlMain.UpdateEvents
                FUNCTIONEND

*................................................................
.
. Set up the PL/B z-order for the HTML objects
.
HctlSetupFocus  LFUNCTION
                ENTRY
                htmlHctlMain.SetTabId using "customerAddress","20"
                htmlHctlMain.SetTabId using "customerCity","30"
                htmlHctlMain.SetTabId using "customerEmail","15"
                htmlHctlMain.SetTabId using "customerName","10"
                htmlHctlMain.SetTabId using "customerState","40"
                htmlHctlMain.SetTabId using "customerZip","50"
                htmlHctlMain.SetTabId using "generateInv","300"
                htmlHctlMain.SetTabId using "printInv","310"
                htmlHctlMain.SetTabId using "clearInv","320"
                htmlHctlMain.UpdateEvents
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

                Runtime.SetWebTheme Using 19
                CALL            CreateMainForm

                htmlHctlMain.SetAsClient
                Client.SetUTF8Convert Using 0

                htmlHctlMain.LoadHtml Using "custinvoice.html",$HTML_HAS_EVENTS
 
                CALL            HctlSetupEvents
                CALL            HctlSetupFocus

                SETPROP         htmlHctlMain,enabled=0
                CALL            CreateTable
                SETPROP         htmlHctlMain,enabled=1
                SETFOCUS        htmlHctlMain

                FUNCTIONEND
