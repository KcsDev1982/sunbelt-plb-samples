*........................................................................
. Example Program: GETINFO.PLS
.
. This program illustrates the use of the GETINFO verb.
.
. Copyright @ 1997, Sunbelt Computer Systems, Inc.
. All Rights Reserved.
.........................................................................
.
DATA            DIM             650
FontObj         FONT
ld
Pfile           PFILE
.
InfoList        DATALIST
InfoList1       DATALIST
CharList        DATALIST
Info            MENU
InfoData        INIT            "&Info;":
                                "&Datasources;":
                                "&Fonts;":
                                "&Printers;":
                                "&One Printer;":
                                "&System"
.
Dbinfo          MENU
DbinfoData      INIT            "&Database;":
                                "&Connect Info;":
                                "&Statment Info;":
                                "&General Info;":
                                "&Tables;":
                                "Disconnect"
DbinfoFile      DBFILE
Connected       FORM            "0"
*
.System Information
.
SysData         LIST
OsType          FORM            1
OsVersion       DIM             1 //reference as character, future compatibility
KeyType         FORM            2
KeySubType      FORM            2
KeyNumF         FORM            2
PenBased        FORM            1
HasMouse        FORM            1
MouseButtons    FORM            1
SwapMouse       FORM            1
ScrWidth        FORM            4 // primary display
ScrHeight       FORM            4 // primary display
ComputerName    DIM             15
UserName        DIM             20
WinDir          DIM             260
SysDir          DIM             260
ColorBits       FORM            2
WinHandle       INTEGER         4
WinInstance     INTEGER         4
TaskBarPos      FORM            1
TaskBarTop      FORM            4
TaskBarBottom   FORM            4
TaskBarLeft     FORM            4
TaskBarRight    FORM            4
NumberOfScreens FORM            2
VirtScreenTop   FORM            10 // absolute desktop top
VirtScreenLeft  FORM            10 // absolute desktop left
VirtScreenHt    FORM            10 // height of all screens combined
VirtScreenWd    FORM            10 // width of all screens combined
                LISTEND
*
. Font Info
.
FntData         LIST
FntAscent       DIM             4
FntDescent      DIM             4
FntHeight       DIM             4
FntFullHeight   DIM             4
FntAvgChrWidth  DIM             4
FntMaxChrWidth  DIM             4
FntStringWidth  DIM             4
FntFirstChar    DIM             1
FntLastChar     DIM             1
                LISTEND
.
Char            DIM             31[16]
NDX1            INTEGER         1
NDX2            INTEGER         1
NDX             INTEGER         1
*
. Printer Info
.
PrtData         LIST
PrtVersion      DIM             8
PrtPixelW       DIM             8
PrtPixelH       DIM             8
PrtMilW         DIM             8
PrtMilH         DIM             8
PrtColors       DIM             8
PrtFonts        DIM             8
PrtDrawPict     DIM             1
PrtNumCopies    DIM             4
PrtPagesAll     DIM             1
PrtPagesSelec   DIM             1
PrtPagesStart   DIM             8
PrtPagesEnd     DIM             8
                LISTEND
*
. Connect info
.
ConData         LIST
ConOdbcVer      DIM             5
ConDrvName      DIM             20
ConDrvVer       DIM             10
ConDrvOdbcVer   DIM             5
ConOdbcApiLevel DIM             1
ConSqlLevel     DIM             1
ConFileUseage   DIM             1
ConAccessMode   DIM             1
ConAutoCommit   DIM             1
ConTrace        DIM             1
ConCursors      DIM             1
ConTxn          DIM             1
ConFiller       DIM             100
ConQual         DIM             100
                LISTEND
*
. Statement Info
.
StData          LIST
StSqlLevel      DIM             1
StSqlConcur     DIM             1
StCursorType    DIM             1
StKeysetSize    DIM             8
StMaxLength     DIM             8
StMaxRows       DIM             8
                LISTEND
*
. General Info
.
GnData          LIST
GnSqlLevel      DIM             1
GnReadOnly      DIM             1
GnAccTables     DIM             1
GnAddCol        DIM             1
GnDropCol       DIM             1
GnCorrName      DIM             1
GnColumnAlias   DIM             1
GnProcedures    DIM             1
GnAccProcedures DIM             1
GnIdCase        DIM             1
GnQuotedIdCase  DIM             1
GnQuoteChar     DIM             1
GnSearchEsc     DIM             1
GnOutJoins      DIM             1
GnExpInOrderby  DIM             1
GnObcInSelect   DIM             1
GnGroupBy       DIM             1
                LISTEND
 
*
. Table information
.
TblData         LIST
TblName         DIM             128
TblType         DIM             128
TblOwner        DIM             128
TblQual         DIM             128
TblRemarks      DIM             254
                LISTEND
*
. Column information
.
ColData         LIST
ColName         DIM             128
ColTypeName     DIM             62
ColTypeNum      DIM             5
ColPrecision    DIM             5
ColLength       DIM             5
ColScale        DIM             5
ColRadix        DIM             5
ColFill         DIM             1
ColRemarks      DIM             254
                LISTEND
.
Line            DIM             1024
.
RESULT          FORM            9
.
$Click          CONST           "4"
OSVAL           INIT            "0123456789AB"
OSIDX           FORM            2
OSVER           DIM             13(0..11),("Unknown"):
                                ("Windows NT"):
                                ("Windows 3.1x"):
                                ("Windows 95"):
                                ("Windows 98"):
                                ("Windows 2000"):
                                ("Windows XP"):
                                ("Windows Vista"):
                                ("Windows CE"):
                                ("Windows 7"):
                                ("Unknown"):
                                ("Unknown")
*.........................................................................
. Initialize Char field for font test.
.
                FOR             NDX1 FROM "1" TO "16"
                FOR             NDX2 FROM "1" TO "16"
                PACK            Char[NDX1],Char[NDX1],NDX," "
                ADD             "1",NDX
                REPEAT
                REPEAT
.
                CREATE          InfoList=3:8:5:75,FONT="Fixed(9)",SORTED=1
                CREATE          InfoList1=13:17:5:75,FONT="Fixed(9)",SORTED=1
*
.Create and Activate the Info Menu Item
.
                CREATE          Info,InfoData
                ACTIVATE        Info,MenuAct,RESULT
*
.Create and Activate the Database Menu Item
.
                CREATE          Dbinfo, DbinfoData, Info
                ACTIVATE        Dbinfo,DbMenuAct,RESULT
*
.Wait for an Event to Occur
.
                LOOP
                WAITEVENT
                REPEAT
*..........................................................................
.Info Menu Item Selected
.
MenuAct
                DEACTIVATE      InfoList
                DEACTIVATE      InfoList1
.
                DISPLAY         *ES;
*
.Branch to the Selected Function
.
                BRANCH          RESULT TO GetDatasrc,GetFonts:
                                GetPrinters,GetOnePrt,GetSysInfo
                RETURN
*............................................................................
.Database Menu Item Selected
.
DbMenuAct
                DEACTIVATE      InfoList
                DEACTIVATE      InfoList1
.
                DISPLAY         *ES;
.
                IF              (Connected = 0)
.
. set an exception to jump to end of routine if the user cancels the dialog
.
                EXCEPTSET       DbCanceled IF DBFAIL
.
. a dbconnect with no souce parameter give a selection dialog.
.
                DBCONNECT       DbinfoFile, "", "", ""
.
. clear the exception because we don't want to catch other dbfail errors
.
                EXCEPTCLEAR     DBFAIL
                MOVE            "1" TO Connected
                ENDIF
*
.Branch to the Selected Function
.
                BRANCH          RESULT OF GetConn,GetState,GetGen,GetTables
.
                DBDISCONNECT    DbinfoFile
.
DbCanceled
                MOVE            "0" TO Connected
.
                RETURN
*...........................................................................
.Retrieve and Display the System Information
.
GetSysInfo
.
                GETINFO         SYSTEM,DATA       // Retrieve the Info
                UNPACK          DATA INTO SysData     // Disassemble the Info
.
                DISPLAY         *ES;
.
                IF              (OsType = 1)
                DISPLAY         *P=1:1,"Information for Windows";
                ELSE
                RETURN
                ENDIF
.
. whare version of windows are we on
.
                WHEREIS         OSVersion,OSVAL,OSIDX
.
                DISPLAY         *P=1:02,"Version           ", OSVER(OSIDX):
                                *P=1:03,"Keyboard Type:           ", KeyType:
                                *P=1:04,"Keyboard Subtype:        ", KeySubType:
                                *P=1:05,"FKey type:           ", KeyNumF;
.
                DISPLAY         *P=1:06,"Is Windows PEN based:    ";
                IF              (PenBased = 1)
                DISPLAY         "Yes"
                ELSE
                DISPLAY         "No"
                ENDIF
.
                DISPLAY         *P=1:07,"Is a mouse present:      ";
                IF              (HasMouse = 1)
                DISPLAY         "Yes"
                ELSE
                DISPLAY         "No"
                ENDIF
.
                DISPLAY         *P=1:08,"Number of mouse buttons: ",MouseButtons
.
                DISPLAY         *P=1:09,"Mouse buttons swapped:   ";
                IF              (SwapMouse = 1)
                DISPLAY         "Yes"
                ELSE
                DISPLAY         "No"
                ENDIF
.
                DISPLAY         *P=1:10,"Primary Screen width:    ",ScrWidth:
                                *P=1:11,"Primary Screen height:   ",ScrHeight:
                                *P=1:12,"Compuer name:           ",ComputerName:
                                *P=1:13,"User Name:           ",UserName:
                                *P=1:14,"Windows Dir:           ",WinDir:
                                *P=1:15,"System Dir:           ",SysDir:
                                *P=1:16,"Color Bits:           ",ColorBits:
                                *P=1:17,"Window Handle:           ",WinHandle:
                                *P=1:18,"Window Instance:         ",WinInstance:
                                *P=1:19,"Number of displays       ",NumberOfScreens:
                                *p=1:20,"Virtual Desktop Top      ",VirtScreenTop:
                                *p=1:21,"Virtual Desktop Left     ",VirtScreenLeft:
                                *p=1:22,"Virtual Desktop Height   ",VirtScreenHt:
                                *p=1:23,"Virtual Desktop Width    ",VirtScreenWd;
 
                RETURN
*..........................................................................
.Retrieve Printer Information
.
GetPrinters
.
                DELETEITEM      InfoList, 0
.
                GETINFO         PRINTERS, InfoList
                GETINFO         PRINTERS, DATA
                DISPLAY         *ES,*P1:1,"Default printer is: ",DATA;
                ACTIVATE        InfoList
                RETURN
.
GetOnePrt
.
. skip to end of routine if there is an error
. 
                EXCEPTSET       PrtCancel IF SPOOL
.
. Using an empty device name gives printer selection dialog
.
                PRTOPEN         Pfile,"",""
                GETINFO         TYPE=Pfile, DATA
                PRTCLOSE        Pfile
                UNPACK          DATA INTO PrtData
.
                DISPLAY         *ES,"Driver Version:  ", PrtVersion:
                                *N,"Page Width (pixals):       ", PrtPixelW:
                                *N,"Page Height (pixals):      ", PrtPixelH:
                                *N,"Page Width (millimeters):  ", PrtMilW:
                                *N,"Page Height (millimeters): ", PrtMilH:
                                *N,"Number of Colors:        ", PrtColors:
                                *N,"Number of Fonts:        ", PrtFonts:
                                *N,"Can print pictures:        ", PrtDrawPict:
                                *N,"Number of Copies:        ", PrtNumCopies:
                                *N,"Print All Pages:        ", PrtPagesAll:
                                *N,"Print Selection Only:      ", PrtPagesSelec:
                                *N,"Print Start Page:        ", PrtPagesStart:
                                *N,"Print End Page:        ", PrtPagesEnd
PrtCancel
                RETURN
*..........................................................................
. Retrieve Font Information
.
GetFonts
                InfoList.ResetContent
.
                GETINFO         FONTS, InfoList
                GETINFO         FONTS, DATA
                DISPLAY         *ES,*P1:1,"Default font is: ",DATA;
.
. hook up the CLICK event and put the event result in the result variable
. so we know when the selection changes.
. 
                EVENTREG        InfoList,$Click,ShowFont
                ACTIVATE        InfoList
.
. select the first item
. 
                SETITEM         InfoList, 0, 1
                CALL            ShowFont
                RETURN
*...........................................................................
. Show Example Text using Selected Font
.
ShowFont
                InfoList.GetFirstSel giving RESULT
                InfoList.GetText giving Line using RESULT
//  GETITEM InfoList, RESULT, Line
 
                CREATE          FontObj, Line, SIZE=12
                MOVE            "Sample data" TO DATA
                GETINFO         TYPE=FontObj, DATA
                UNPACK          DATA INTO FntData
.
                DISPLAY         *P=1:14,*EF, "Font Name (12pt): ", Line:
                                *P=1:15,"Ascent:  ",FntAscent:
                                *P=1:16,"Descent:  ",FntDescent:
                                *P=1:17,"Height:  ",FntHeight:
                                *P=1:18,"Full height:  ", FntFullHeight:
                                *P=1:19,"Avg Char Width: ", FntAvgChrWidth:
                                *P=1:20,"Max Char Width: ", FntMaxChrWidth:
                                *P=1:21,"Length of string 'Sample data': ":
                                FntStringWidth:
                                *P=1:22,"First char in font: ", FntFirstChar:
                                *P=1:23,"Last char in font:  ", FntLastChar;
.
                TRAP            ShowFont1 IF OBJECT
                CREATE          CharList=13:22:41:77,FONT=FontObj
                GOTO            ShowFont2
ShowFont1
                NORETURN
                SPLICE          ">",Line,0
                TRAP            ShowFont9 IF OBJECT
                CREATE          CharList=13:22:41:77,FONT=Line
ShowFont2
                TRAPCLR         OBJECT
                FOR             NDX1 FROM "1" TO "16"
                CharList.AddString using Char[NDX1]
                REPEAT
                ACTIVATE        CharList
                RETURN
ShowFont9
                ALERT           NOTE,"Could not retrieve Font Information",RESULT
                NORETURN
                RETURN
*............................................................................
.Retrieve Default Data Source
.
GetDataSrc
                InfoList.ResetContent
                GETINFO         DATASOURCE, InfoList
                DISPLAY         *ES,*P1:1,"No default datasource";
                ACTIVATE        InfoList
                RETURN
*............................................................................
.Retrieve Connection Info
.
GetConn
                GETINFO         TYPE=DbinfoFile, DATA, CONNECTION
                UNPACK          DATA,ConData
                DISPLAY         *ES,"ODBC Version:   ", ConOdbcVer:
                                *N, "Driver Name:   ", ConDrvName:
                                *N, "Driver Version:   ", ConDrvVer:
                                *N, "Driver ODBC Version: ", ConDrvOdbcVer:
                                *N, "ODBC API Level:   ", ConOdbcApiLevel:
                                *N, "SQL Support Level:   ", ConSqlLevel:
                                *N, "File Useage:   ", ConFileUseage:
                                *N, "Access Mode:   ", ConAccessMode:
                                *N, "Autocommit On:   ", ConAutoCommit:
                                *N, "Tracing On:   ", ConTrace:
                                *N, " SQL Cursor Support: ", ConCursors:
                                *N, "Transaction Support: ", ConTxn:
                                *N, "Qualifier:    ", ConQual
                RETURN
*............................................................................
.Retrieve ODBC State
.
GetState
                GETINFO         TYPE=DbinfoFile, DATA, STATEMENT
                UNPACK          DATA INTO StData
                DISPLAY         *ES,"SQL Level:       ", StSqlLevel:
                                *N, "SQL Concurrency: ", StSqlConcur:
                                *N, "Cursor Type:     ", StCursorType:
                                *N, "Keyset Size:     ", StKeysetSize:
                                *N, "Max Length:      ", StMaxLength:
                                *N, "Max Rows:       ", StMaxRows
                RETURN
*............................................................................
.Retrieve ODBC General Information
.
GetGen
                GETINFO         TYPE=DbinfoFile, DATA
                UNPACK          DATA INTO GnData
                DISPLAY         *ES,"SQL Level:         ", GnSqlLevel:
                                *N, "Read Only:         ", GnReadOnly:
                                *N, "Accessible Tables:        ", GnAccTables:
                                *N, "Add Columns:        ", GnAddCol:
                                *N, "Drop Columns:        ", GnDropCol:
                                *N, "Correlation Name Support: ", GnCorrName:
                                *N, "Column Alias Support:     ", GnColumnAlias:
                                *N, "Procedures Supported:     ", GnProcedures:
                                *N, "Procedures Accessible:    ", GnAccProcedures:
                                *N, "Identifier Case:        ", GnIdCase:
                                *N, "Quoted Identifier Case:   ", GnQuotedIdCase:
                                *N, "Quote Character:        ", GnQuoteChar:
                                *N, "Search Character Escape:  ", GnSearchEsc:
                                *N, "Outer Joins:        ", GnOutJoins:
                                *N, "Expressions in ORDER BY:  ", GnExpInOrderby:
                                *N, "ORDER BY cols in SELECT:  ", GnObcInSelect:
                                *n, "GROUP BY Support:        ", GnGroupBy
                RETURN
*...........................................................................
.Retrieve Table Names
.
GetTables
                InfoList.ResetContent
                GETINFO         TYPE=DbinfoFile, InfoList, TABLES
                DISPLAY         *ES,*P1:1,"No default table";
.
                EVENTREG        InfoList,$CLICK,TableAction
                ACTIVATE        InfoList
.
                InfoList.SetCurSel using 0
                CALL            TableAction
                RETURN
*............................................................................
.Retrieve Table Info
.
TableAction
.
                InfoList.GetFirstSel giving RESULT
                InfoList.GetText giving Line using RESULT
.
                UNPACK          Line INTO TblData
                DISPLAY         *P1:2,*EL,"Name     :", TblName;
                DISPLAY         *P1:3,*EL,"Type     :", TblType;
                DISPLAY         *P1:4,*EL,"Owner    :", TblOwner;
                DISPLAY         *P1:5,*EL,"Qualifier:", TblQual;
                DISPLAY         *P1:6,*EL,"Remarks  :", TblRemarks;
.
                CHOP            TblName
                InfoList1.ResetContent
                GETINFO         TYPE=DBinfoFile, InfoList1, COLUMNS=TblName
.
                EVENTREG        InfoList1,$CLICK,ColumnAction
                ACTIVATE        InfoList1
.
                InfoList1.SetCurSel using 0
.
                CALL            ColumnAction
                RETURN
*..............................................................................
.Retrieve Column Info
.
ColumnAction
                InfoList.GetFirstSel giving RESULT
                InfoList.GetText giving Line using RESULT
.
                UNPACK          Line INTO ColData
                DISPLAY         *P1:18,*EL,"Name       :", ColName;
                DISPLAY         *P1:19,*EL,"Type       :", ColTypeName;
                DISPLAY         *P1:20,*EL,"Type Num   :", ColTypeNum;
                DISPLAY         *P1:21,*EL,"Precision  :", ColPrecision;
                DISPLAY         *P1:22,*EL,"Length     :", ColLength;
                DISPLAY         *P1:23,*EL,"Scale/Radix:", ColScale, "/", ColRadix;
                DISPLAY         *P1:24,*EL,"Remarks    :", ColRemarks;
                RETURN
