
*---------------------------------------------------------------
.
. Program Name: wvhtmldesigner
. Description:  WebView Designer for HTMLCONTROL 
.
. Revision History:
.
. V1.0   21 Jun 2019   W Keech   Original code
. V2.0   27 Feb 2022   T Keech   Redesign     
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*---------------------------------------------------------------     

. 
.
EditForm        PLFORM          "wvdesignerf1.pwf"
SaveForm        PLFORM          "wvdesignerf2.pwf"

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

htmlChangedFlag FORM            1 
htmlChangeAns   FORM            1             


HtmlPageBlank   INIT            "<html><head>",0xD,0xA:
                                "<style>",0XD,0XA:
                                "</style>",0XD,0XA:
                                "</head>",0XD,0XA:
                                "<body>",0xd,0xa:
                                "</body>",0xd,0xa:
                                "</html>",0xd,0xa

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
                GETPROP         mainWinHtmlEdittext,Text=SnipData
                APPEND          "snip" To SnipFileName
                ELSE
                APPEND          "snip8" To SnipFileName
                IF              (IsWin == 0 )
                Client.SetUTF8Convert Using 0
                GETPROP         mainWinHtmlEdittext,Text=SnipData
                Client.SetUTF8Convert Using 1
                ELSE
                mainWinHtmlEdittext.GetUnicode Giving DataUni
                CONVERTUTF      DataUni, SnipData, "8" ;Convert Unicode to UTF8
                ENDIF
                ENDIF
 
                RESET           SnipFileName
                SETPROP         EditText2,Text=SnipFileName
                PREP            SnipFile,SnipFileName
                WEOF            SnipFile,Zero
                WRITE           SnipFile,Seq;*LL,*ABSON, SnipData;
                CLOSE           SnipFile
                DEACTIVATE      SaveDialog
                CLEAR           htmlChangedFlag
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
. TemplateReset - Reset the template
.
TemplateReset   LFUNCTION
                ENTRY
                SETPROP         mainWinHtmlEdittext,Text=HtmlPageBlank
                SETPROP         HtmlCtl, InnerHtml=""   
                FUNCTIONEND
*................................................................
.
. loadSnippetListview - Load snippet list
.
loadSnippetListview LFUNCTION
                ENTRY
snipNames       DIM             32000

                FINDDIR         "wvsnippets\*.snip*", snipNames, MODE=3
                mainWinSnippetListview.DeleteAllItems
                PACK            snipNames, snipNames, "|F"
                LOOP
                EXPLODE         snipNames, "|", FileName
                BREAK           If Zero
                UNPACK          FileName Into D1,SnipFileName
                TYPE            SnipFileName
                BREAK           if EOS
                mainWinSnippetListview.InsertItem Using SnipFileName
                REPEAT

                SETFOCUS        mainWinSnippetListview    //ERB

                FUNCTIONEND
*................................................................
.
. ResetIt - Reset the edit area
.
ResetIt         LFUNCTION
                ENTRY
                SETPROP         mainWinHtmlEdittext,Text=HtmlPageBlank
                mainWinEventListview.DeleteAllItems
                CALL            TemplateReset
                FUNCTIONEND
 
*................................................................
.
. LoadTemplate - Load a template from disk
.
LoadTemplate    LFUNCTION
                ENTRY
result          FORM            5

                mainWinEventListview.DeleteAllItems
                EVENTINFO       0,result=Result
                
                IF              ( htmlChangedFlag )    
                ALERT           plain,"Save changes to .snip file?",htmlChangeAns,"Html content has changed"
                SWITCH          htmlChangeAns
                CASE            1
                CALL            SaveAs
                CASE            3
                RETURN
                ENDSWITCH
                ENDIF


                mainWinSnippetListview.GetItemText Giving FileName Using Result
                PACK            SnipFileName Using "wvsnippets\", FileName
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
                SETPROP         mainWinHtmlEdittext,Text=SnipData
                ELSE
                IF              (IsWin == 0 )
                Client.SetUTF8Convert Using 0
                SETPROP         mainWinHtmlEdittext,Text=SnipData
                Client.SetUTF8Convert Using 1
                ELSE
                CONVERTUTF      SnipData, DataUni, "6" ;Convert input UTF8 to UTF16
                mainWinHtmlEdittext.SetUnicode Using DataUni
                ENDIF
                ENDIF
 
                PACK            S$CMDLIN, "HtmlControl Template '",SnipFileName,"'" //ERB

                CLEAR           htmlChangedFlag

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
. TestHtml - Test the HTML 
.
TestHtml        LFUNCTION
                ENTRY

                GETPROP         CheckBox1, Value=IsUtf8
                IF              (IsUtf8 == 0 )
                SETPROP         HtmlCtl,CodePage=1
                GETPROP         mainWinHtmlEdittext,Text=FullHtml
                ELSE
                SETPROP         HtmlCtl,CodePage=0
                IF              (IsWin == 0 )
                Client.SetUTF8Convert Using 0
                GETPROP         mainWinHtmlEdittext,Text=FullHtml
                Client.SetUTF8Convert Using 1
                ELSE
                mainWinHtmlEdittext.GetUnicode Giving DataUni
                CONVERTUTF      DataUni, FullHtml, "8" ;Convert Unicode to UTF8
                ENDIF
                ENDIF

                                // Turn on context menu for debugging 
                HtmlCtl.ContextMenu Using 1 
 
                                // Could have used HtmlCtl.InnerHtml Using FullHtml 
                SETPROP         HtmlCtl,InnerHtml=FullHtml
                FUNCTIONEND

*................................................................
.
. HtmlEvCtl - Display the HTMLCONTROL event information
.
HtmlEvCtl       LFUNCTION
                ENTRY
                JsonEvent.LoadJson Using JsonData
                CALL            FetchJsonStr Using JsonEvent,"type",Info
                mainWinEventListview.InsertItemEx Giving CurIndex Using Info
                CALL            FetchJsonStr Using JsonEvent,"id",Info
                mainWinEventListview.SetItemText Using CurIndex, Info, 1
                CALL            FetchJsonStr Using JsonEvent,"pageX",Info
                mainWinEventListview.SetItemText Using CurIndex, Info, 2
                CALL            FetchJsonStr Using JsonEvent,"pageY",Info
                mainWinEventListview.SetItemText Using CurIndex, Info, 3
                CALL            FetchJsonStr Using JsonEvent,"metaKey",Info
                mainWinEventListview.SetItemText Using CurIndex, Info, 4
                CALL            FetchJsonStr Using JsonEvent,"which",Info
                mainWinEventListview.SetItemText Using CurIndex, Info, 5
                CALL            FetchJsonStr Using JsonEvent,"target",Info
                mainWinEventListview.SetItemText Using CurIndex, Info, 6
                FUNCTIONEND


*................................................................
.
. mainWinToolbarClick - dispatch mainWinToolBar events
.
mainWinToolbarClick LFUNCTION
                ENTRY
toolBarResult   INTEGER         4 
               
                EVENTINFO       0,result=toolBarResult
                DEBUG
                PERFORM         toolbarResult of mainWinSnippetListviewDBlClick:
                                saveAs:
                                resetIt:
                                testHtml:
                                disableIt:
                                enableIt:
                                mainWinexit
                            
                                
                FUNCTIONEND



*................................................................
.
. mainWinSnippetListviewClick - dispatch mainWinToolBar events
.
mainWinSnippetListviewClick LFUNCTION
                ENTRY
                CALL            loadTemplate 
                CALL            testHtml   
                FUNCTIONEND


*................................................................
.
. mainWinSnippetListviewDoubleClick - dispatch mainWinToolBar events
.
mainWinSnippetListviewDBlClick LFUNCTION
                ENTRY
                CALL            loadTemplate 
                CALL            testHtml   
                FUNCTIONEND


*................................................................
.
. mainWinToolbarClick - dispatch mainWinToolBar events
.
mainWinExit     LFUNCTION
                ENTRY
                IF              ( htmlChangedFlag )    
                ALERT           plain,"Save changes to .snip file?",htmlChangeAns,"Html content has changed"
                SWITCH          htmlChangeAns
                CASE            1
                CALL            SaveAs
                CASE            3
                RETURN
                ENDSWITCH
                ENDIF
                STOP
                FUNCTIONEND

*................................................................
.
. mainWinHtmlEdittextChange
.
mainWinHtmlEdittextChange LFUNCTION
                ENTRY
                SET             htmlChangedFlag
                CALL            testHtml
                FUNCTIONEND


*................................................................
.
. Main - Main entry point
. 
Main            FUNCTION
                ENTRY

                WINHIDE

		

                FORMLOAD        EditForm

		mainWin.SetAsClient
		Client.GetInfo  Giving CliInfo
                TYPE            CliInfo
                IF              Eos
		ALERT		STOP,"This program requires WebView 2 support!", Result
 		
                STOP
                ENDIF

                EVENTREG        HtmlCtl,$JQueryEvent,HtmlEvCtl,ARG1=JsonData

                mainWinEventListview.DeleteAllContents
                mainWinEventListview.InsertColumn Using "Type",100, 0
                mainWinEventListview.InsertColumn Using "Id",160, 1
                mainWinEventListview.InsertColumn Using "PageX", 80, 2
                mainWinEventListview.InsertColumn Using "PageY", 80, 3
                mainWinEventListview.InsertColumn Using "MetaKey", 80, 4
                mainWinEventListview.InsertColumn Using "Which", 80, 5
                mainWinEventListview.InsertColumn Using "TargetId", 160, 6
                
                mainWinSnippetListview.DeleteAllContents
                mainWinSnippetListview.InsertColumn Using "",300,0
                mainWinSnippetListview.InsertColumn Using "",400,1
              

                FORMLOAD        SaveForm

                EVENTREG        HtmlSave,200,SaveIt
                EVENTREG        HtmlCancel,200,CancelIt

                CALL            loadSnippetListview 
                CALL            TemplateReset 

                SETFOCUS        mainWinSnippetListview   
              
                FUNCTIONEND
                

 

