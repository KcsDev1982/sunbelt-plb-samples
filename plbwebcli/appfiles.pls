*---------------------------------------------------------------
.
. Program Name: appfiles
. Description:  PlbWeCli Application Files Sample 
.
. Revision History:
.
. 17-04-07 whk
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*----------------------------------------------------
MyRoot          INTEGER         4 


WebForm         PLFORM          appfilesf.pwf
.
FullData        DIM             200
JsonBody        DIM             400
.
Result          FORM            5
.
BaseDir         DIM             150
FileName        DIM             200
Path            DIM             260
.
NodePos         FORM            4
.
SampleData      XDATA
.
DirData         DIM             40960
.
Client          CLIENT
RunTime         RUNTIME
.
JsonOptToDisk   FORM            "6" // JSON_SAVE_USE_INDENT+JSON_SAVE_USE_EOR
XmlOptToDisk    FORM            "6" // XML_SAVE_USE_INDENT+XML_SAVE_USE_EOR
.
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
. TestClick - Handle a request to perform a test
.
TestClick       LFUNCTION
                ENTRY
                EVENTINFO       0,result=Result
                SWITCH          Result
                CASE            1
                CALL            GetData
                CASE            2
                CALL            DelDir
                CASE            3
                CALL            MakeDir
                ENDSWITCH
                FUNCTIONEND
*................................................................
.
. GetData
.
GetData         LFUNCTION
                ENTRY
                GETPROP         EditText2, Text=Path
                Client.AppDirGet Using Path, 1
                FUNCTIONEND

*................................................................
.
. GetDataDone
.
GetDataDone     LFUNCTION
                ENTRY
                Client.AppDialog Using DirData, "Dir Get", "Ok"
                SampleData.LoadJson Using DirData
                SampleData.SaveJson Using "appfiles.json", JsonOptToDisk
                SampleData.SaveXml Using "appfiles.xml", XmlOptToDisk
                TreeView1.LoadXmlFile Using "appfiles.xml"
                FUNCTIONEND

*................................................................
.
. DelDir
.
DelDir          LFUNCTION
                ENTRY
                GETPROP         EditText2, Text=Path
                Client.AppDirDel Using Path
                FUNCTIONEND

*................................................................
.
. GetDataDel
.
GetDataDel      LFUNCTION
                ENTRY
                Client.AppDialog Using DirData, "Dir Delete", "Ok"
                SampleData.LoadJson Using DirData
                SampleData.SaveJson Using "appfiles.json", JsonOptToDisk
                FUNCTIONEND

*................................................................
.
. MakeDir
.
MakeDir         LFUNCTION
                ENTRY
                GETPROP         EditText2, Text=Path
                Client.AppDirAdd Using Path
                FUNCTIONEND

*................................................................
.
. GetDataAdd
.
GetDataAdd      LFUNCTION
                ENTRY
                Client.AppDialog Using DirData, "Dir Add", "Ok"
                SampleData.LoadJson Using DirData
                SampleData.SaveJson Using "appfiles.json", JsonOptToDisk
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
. Register and Startup the events, load the main form
.
Main            LFUNCTION
                ENTRY
                WINHIDE
                FORMLOAD        WebForm
                EVENTREG        Client,AppEventDirGet,GetDataDone,ARG1=DirData
                EVENTREG        Client,AppEventDirAdd,GetDataAdd,ARG1=DirData
                EVENTREG        Client,AppEventDirDel,GetDataDel,ARG1=DirData
                SETPROP         EditText2, Text="cdvfile://localhost/persistent/"
                FUNCTIONEND
