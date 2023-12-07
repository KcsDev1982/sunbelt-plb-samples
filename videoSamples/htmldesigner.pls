*---------------------------------------------------------------
.
. Program Name: htmldesigner
. Description:  Designer for HTMLCONTROL
. 
. Revision History:
.
.   21 Jun 19   W Keech
.      Original code
.
*---------------------------------------------------------------
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
. 
HtmlCtl         HTMLCONTROL 
.
EditForm        PLFORM          "designerf1.pwf"
HtmlForm        PLFORM          "designerf2.pwf"
SaveForm        PLFORM          "designerf3.pwf"

Client          CLIENT
CliInfo         DIM             1024
.
FullHtml        DIM             64000
DataUni         DIM             64000
JsonData        DIM             200
JsonEvent       XDATA
.
Result          FORM            5
CurIndex        FORM            5
Info            DIM             30
.
SnipData        DIM             32000
SnipFileName    DIM             270
SnipFile        FILE
Seq             FORM            "-1"
Zero            FORM            "0"
Rep7F           INIT            "|",0x7F
.
FileName        DIM             270
D1              DIM             1
Right           FORM            5
Bottom          FORM            5
IsWin           FORM            "0"
IsUtf8          FORM            "0"


HtmlPageBlank   INIT            "<html><head>",0xD,0xA:
                                "<META http-equiv='X-UA-Compatible' content='IE=edge' />",0xD,0xA:
                                "<STYLE>",0XD,0XA:
                                "</STYLE>",0XD,0XA:
                                "</HEAD>",0XD,0XA:
                                "<BODY>",0XD,0XA:
                                "</BODY>",0XD,0XA:
                                "</HTML>",0XD,0XA
A FILE
*................................................................
.
. Code start
.

                CALL            Main
                STOP
*................................................................
.
. FetchJsonStr - Fetch string data for String 'label'
. 
. Only update the result if the label is found
. 
FetchJsonStr 	LFUNCTION
pXData          XDATA           ^
xLabel          DIM             50
dReturn         DIM             ^
                ENTRY
.
xString         DIM             200
x200            DIM             200
xError          DIM             100
nvar            FORM            2
.
. Find the specified JSON label node
. 
                PACK            s$cmdlin, "label='",xLabel,"'"
                pXData.FindNode GIVING	nvar:
                                USING	*FILTER=S$cmdlin:		//Locate specified JSON label!
                                *POSITION=START_DOCUMENT_NODE	//Start at the beginning of the document!
                IF              ( nvar == 0 )
...
. Move to the child node of the 'orient' JSON label.
. 
                pXData.MoveToNode GIVING nvar USING *POSITION=MOVE_FIRST_CHILD
.
                IF              ( nvar == 0 )
...
. Fetch the data for the JSON  label.
. 
                pXData.GetText  GIVING xString
                PACK            s$cmdlin, xLabel,"= '",xString,"'"
                ELSE
                MOVE            "Error Move Node:", s$cmdlin
                ENDIF
                ELSE
                PACK            s$cmdlin, "Error Find Node:",nvar
                ENDIF

                TYPE            xString	
                IF              NOT EOS
                MOVE            xString, dReturn
                ENDIF
 
                FUNCTIONEND

*................................................................
.
. SaveIt - Handle the Save button on the Save Dialog
.
SaveIt          LFUNCTION
                ENTRY
                CLEAR           SnipData
                GETPROP         EditText2,Text=SnipFileName
                SCAN            ".snip" Into SnipFileName
                IF              Equal
                LENSET          SnipFileName
                ELSE
                ENDSET          SnipFileName
                APPEND          "." To SnipFileName
                ENDIF
                GETPROP         CheckBox1, Value=IsUtf8
                IF              (IsUtf8 == 0 )
                GETPROP         EditText1,Text=SnipData
                APPEND          "snip" To SnipFileName
                ELSE
                APPEND          "snip8" To SnipFileName
                IF              (IsWin == 0 )
                Client.SetUTF8Convert Using 0
                GETPROP         EditText1,Text=SnipData
                Client.SetUTF8Convert Using 1
                ELSE
                EditText1.GetUnicode Giving DataUni
                CONVERTUTF      DataUni, SnipData, "8"	;Convert Unicode to UTF8
                ENDIF
                ENDIF
 
                RESET           SnipFileName
                SETPROP         EditText2,Text=SnipFileName
                PREP            SnipFile,SnipFileName
                WEOF            SnipFile,Zero
                WRITE           SnipFile,Seq;*LL,*ABSON, SnipData;
                CLOSE           SnipFile
                DEACTIVATE      SaveDialog
                FUNCTIONEND
 
*................................................................
.
. CancelIt - Handle the Cancel button on the Save dialog
.
CancelIt        LFUNCTION
                ENTRY
                DEACTIVATE      SaveDialog
                FUNCTIONEND
 
*................................................................
.
. SaveAs - Handle the Save As button
.
SaveAs          LFUNCTION
                ENTRY
                ACTIVATE        SaveDialog
                FUNCTIONEND
 
*................................................................
.
. TemplateReset - Reset the template and snippet list
.
TemplateReset   LFUNCTION
                ENTRY
snipNames       DIM             32000

                FINDDIR         "htmlsnippets\*.snip*", snipNames, MODE=3
                ComboBox1.ResetContent
                SETPROP         EditText1,Text=HtmlPageBlank
                PACK            snipNames, snipNames, "|F"
                LOOP
                EXPLODE         snipNames, "|", FileName
                BREAK           If Zero
                UNPACK          FileName Into D1,SnipFileName
                TYPE            SnipFileName
                BREAK           if EOS
                ComboBox1.AddString Using SnipFileName
                REPEAT

                SETPROP         FORM2, TITLE="HtmlControl Test"		//ERB
                SETPROP         HtmlCtl, InnerHtml=""			//ERB
                SETPROP         EditText2, TEXT=""			//ERB

                SETFOCUS        ComboBox1				//ERB

                FUNCTIONEND
*................................................................
.
. ResetIt - Reset the edit area
.
ResetIt         LFUNCTION
                ENTRY
                SETPROP         EditText1,Text=HtmlPageBlank
                ListView1.DeleteAllItems
                CALL            TemplateReset
                FUNCTIONEND
 
*................................................................
.
. LoadTemplate - Load a template from disk
.
LoadTemplate    LFUNCTION
                ENTRY
                ListView1.DeleteAllItems
                EVENTINFO       0,result=Result
                SUB             "1" From Result
                ComboBox1.GetText Giving FileName Using Result
                PACK            SnipFileName Using "htmlsnippets\", FileName
                CHOP            SnipFileName
                SETPROP         EditText2,Text=SnipFileName
                OPEN            SnipFile,SnipFileName
                READ            SnipFile,Seq;*LL,*ABSON, SnipData;
                CLOSE           SnipFile

                SCAN            ".snip8" Into SnipFileName
                IF              Equal
                MOVE            "1" To IsUtf8
                ELSE
                MOVE            "0" To IsUtf8
                ENDIF

                SETPROP         CheckBox1, Value=IsUtf8

                IF              (IsUtf8 == 0 )
                SETPROP         EditText1,Text=SnipData
                ELSE
                IF              (IsWin == 0 )
                Client.SetUTF8Convert Using 0
                SETPROP         EditText1,Text=SnipData
                Client.SetUTF8Convert Using 1
                ELSE
                CONVERTUTF      SnipData, DataUni, "6"	;Convert input UTF8 to UTF16
                EditText1.SetUnicode Using DataUni
                ENDIF
                ENDIF
 
                PACK            S$CMDLIN, "HtmlControl Template '",SnipFileName,"'"	//ERB
                SETPROP         FORM2, TITLE=S$CMDLIN					//ERB

                FUNCTIONEND

*................................................................
.
. EnableIt - Test the enabled property
.
EnableIt        LFUNCTION
                ENTRY
                SETPROP         HtmlCtl,Enabled=1
                FUNCTIONEND
 
*................................................................
.
. DisableIt - Test the disabled property
.
DisableIt       LFUNCTION
                ENTRY
                SETPROP         HtmlCtl,Enabled=0
                FUNCTIONEND

*................................................................
.
. Test - Test the HTML 
.
Test            LFUNCTION
                ENTRY
                SETPROP         Form2,Visible=0
                GETPROP         CheckBox1, Value=IsUtf8
                IF              (IsUtf8 == 0 )
                SETPROP         HtmlCtl,CodePage=1
                GETPROP         EditText1,Text=FullHtml
                ELSE
                SETPROP         HtmlCtl,CodePage=0
                IF              (IsWin == 0 )
                Client.SetUTF8Convert Using 0
                GETPROP         EditText1,Text=FullHtml
                Client.SetUTF8Convert Using 1
                ELSE
                EditText1.GetUnicode Giving DataUni
                CONVERTUTF      DataUni, FullHtml, "8"	;Convert Unicode to UTF8
                ENDIF
                ENDIF

                // Turn on context menu for debugging	
                HtmlCtl.ContextMenu Using 1	
 
                // Could have used HtmlCtl.InnerHtml Using FullHtml	
                SETPROP         HtmlCtl,InnerHtml=FullHtml
                SETPROP         Form2,Visible=1
                FUNCTIONEND
*................................................................
.
. HideTextWin - Hide ethe test window
.
HideTestWin     LFUNCTION
                ENTRY
                SETPROP         Form2,Visible=0
                FUNCTIONEND
*................................................................
.
. FocusTesting - Set focus to the HTMLCONTROL
.
FocusTesting    LFUNCTION
                ENTRY
                SETFOCUS        HtmlCtl	
                FUNCTIONEND

*................................................................
.
. PrintIt - Show a print preview of the control
.
PrintIt         LFUNCTION
                ENTRY
PrtPict         PICT
PrtFile         PFILE

                GETPROP         EditText2,Text=SnipFileName
                HtmlCtl.MakePict Giving PrtPict
                SETPROP         Form2,Units=$LOENGLISH
                GETPROP         HtmlCtl, Width=Right,Height=Bottom
                ADD             "30" To Bottom
                ADD             "10" TO Right
                SETPROP         Form2,Units=$PIXELS
                PRTOPEN         PrtFile,"@pdf:",""
                PRTPAGE         PrtFile;*Orient=*landscape, "File Name: ", SnipFileName:
                                *UNITS=*LOENGLISH,*PICTRECT=*OFF,*PICT=30:BOTTOM:10:RIGHT:PRTPICT
                PRTCLOSE        PrtFile
                FUNCTIONEND

*................................................................
.
. HtmlEvCtl - Display the HTMLCONTROL event information
.
HtmlEvCtl       LFUNCTION
                ENTRY
                JsonEvent.LoadJson Using JsonData
                CALL            FetchJsonStr Using JsonEvent,"type",Info
                ListView1.InsertItemEx Giving CurIndex Using Info
                CALL            FetchJsonStr Using JsonEvent,"id",Info
                ListView1.SetItemText Using CurIndex, Info, 1
                CALL            FetchJsonStr Using JsonEvent,"pageX",Info
                ListView1.SetItemText Using CurIndex, Info, 2
                CALL            FetchJsonStr Using JsonEvent,"pageY",Info
                ListView1.SetItemText Using CurIndex, Info, 3
                CALL            FetchJsonStr Using JsonEvent,"metaKey",Info
                ListView1.SetItemText Using CurIndex, Info, 4
                CALL            FetchJsonStr Using JsonEvent,"which",Info
                ListView1.SetItemText Using CurIndex, Info, 5
                CALL            FetchJsonStr Using JsonEvent,"target",Info
                ListView1.SetItemText Using CurIndex, Info, 6
                FUNCTIONEND


*................................................................
.
. Main - Main entry point
.	
Main            FUNCTION
                ENTRY

                WINHIDE

                FORMLOAD        HtmlForm
                CREATE          Panel1;HtmlCtl=0:0:100:100,DOCK=6,Visible=1,TABID=1
                EVENTREG        HtmlCtl,200,HtmlEvCtl,ARG1=JsonData

                FORMLOAD        EditForm
                ListView1.DeleteAllContents
                ListView1.InsertColumnEx Using "type", 100, 0
                ListView1.InsertColumnEX Using "id",	160, 1
                ListView1.InsertColumn Using "pageX", 80, 2
                ListView1.InsertColumn Using "pageY", 80, 3
                ListView1.InsertColumn Using "metaKey", 80, 4
                ListView1.InsertColumn Using "which", 80, 5
                ListView1.InsertColumn Using "targetId", 160, 6

                FORMLOAD        SaveForm

                EVENTREG        HtmlSave,200,SaveIt
                EVENTREG        HtmlCancel,200,CancelIt

                CALL            TemplateReset 

                Client.GetInfo  Giving CliInfo
                TYPE            CliInfo
                IF              Eos
                SETPROP         PrtBtn,Visible=1
                MOVE            "1" To IsWin
                ELSE
                SETPROP         Form2,Visible=0
                ENDIF

                SETFOCUS        ComboBox1			
                LOOP
                EVENTWAIT
                REPEAT
                FUNCTIONEND


