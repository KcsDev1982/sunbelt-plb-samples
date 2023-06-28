............................................................................
. Example Program: ADDROBJS.PLS
.
. This program illustrates the use of graphical objects without forms.
. The program is a simple name and address file maintenance program with
. several nice features.  As entries are added to the file, they are also
. added to a Datalist. Entries may then be selected from the Datalist.
. A nice Associated Aamdex Method search dialog is also provided.
.
. Copyright @ 1997-1999, Sunbelt Computer Systems, Inc.
. All Rights Reserved.
.............................................................................
. Revision History
.
.   9-8-98 JSS Convert display statements (except screen setup) to GUI style
. 10-13-98 JSS Convert from obsolete dialog to modal window dialog
.
............................................................................
. File Menu Redefinition
.
File            MENU
FileData        INIT            ")File;E)xit"
.
. Records Menu Definition
.
Action          MENU
ActData         INIT            ")Records;":
                                "/A)Add Record",011,"Ctrl+A;":
                                "/D)Delete Record",011,"Ctrl+D;":
                                "/TPas)te Record",011,"Ctrl+T;":
                                "/S)Search Records",011,"Ctrl+S;":
                                "/U)Update Record",011,"Ctrl+U"
.
. Field Labels
.
Header          STATTEXT
NameText        STATTEXT
StrText         STATTEXT
CityText        STATTEXT
StText          STATTEXT
ZipText         STATTEXT
.
. Name Datalist
.
NameList        DATALIST
NameCnt         FORM            "000"
.
. Field Edittexts
.
NameEdit        EDITTEXT
StrEdit         EDITTEXT
CityEdit        EDITTEXT
StEdit          EDITTEXT
ZipEdit         EDITTEXT
.
. Font Names
.
Font1           INIT            "Times(24,BOLD)"
Font2           INIT            "Times(12,BOLD)"
Font3           INIT            "Times(10,BOLD)"
.
. Window  and its objects for modal dialog
.
SDialog         WINDOW
SDsrch          BUTTON          ;Search Button
SDcancel        BUTTON          ;Cancel Button
SDet1           EDITTEXT        ;Data to use in search
SDsfor          STATTEXT        ;Prompt for et1
SDsfield        STATTEXT        ;Prompt for combo1
SDstype         STATTEXT        ;Prompt for combo2
SDcombo1        COMBOBOX        ;Which field to search
SDcombo2        COMBOBOX        ;Type of AAM search
.
. Search Variables
.
SearchId        EQU             128
SrchData        DIM             80
Key             DIM             200
FieldVal        FORM            "01"
SrchType        FORM            "01"
SrchTyps        DIM             1(4)
SrchChar        DIM             1
.
. Misc Alerts
.
RecordExists    INIT            "The record for ^0 already exists."
BadKeyAlert     INIT            "The key #"^0#" doesn't contain enough":
                                " information."
.
. File Spec and Data for one record
.
. AIAM Keys         1-190     All data
.       1-40    Name
.       41-90   Street
.       91-130  City
.       131-170 State
.       171-190 Zip Code
.
. ISAM Key      1-40    Name
.
AddressFile     AFILE           FIXED=190
NameFile        IFILE           FIXED=190, KEYLEN=40
AiamName        INIT            "AddrFile.aam"
IsamName        INIT            "AddrFile.isi"
DataName        INIT            "AddrFile.txt"
AiamKeys        INIT            "1-190,1-40,41-90,91-130,131-170,171-190"
.
NameData        LIST
Name            DIM             40
Street          DIM             50
City            DIM             40
State           DIM             40
ZipCode         DIM             20
                LISTEND
.
. Local Data
.
Result          FORM            4
Len             FORM            4
NewName         DIM             40
.
. Colors
.
MAGENTA         COLOR
............................................................................
. Start of the code
.
. Initalize the data for the SrchTyps array
.
                MOVE            "F" TO SrchTyps(1)
                MOVE            "X" TO SrchTyps(2)
                MOVE            "L" TO SrchTyps(3)
                MOVE            "R" TO SrchTyps(4)
.
. Create the objects
.
                SETMODE         *LTGRAY=ON,*3D=ON,*Pixel=OFF
                DISPLAY         *BGCOLOR=*YELLOW,*ES
.
. Define this standard color in a color object for later use
.
                CREATE          MAGENTA=*MAGENTA  
.
. Create the Menu Items
.
                CREATE          File,FileData
                CREATE          Action,ActData
.
. Display the Heading
.
                CREATE          Header=1:4:25:55,"Address Demo",Font1,BORDER:
                                FGCOLOR=MAGENTA,STYLE=3DOUT
.
. Create the Field Labels
.
                CREATE          NameText=5:6:5:17,"Name:",Font2,BORDER,STYLE=3DFLAT
                CREATE          StrText=7:8:5:17,"Street:",Font2,BORDER,STYLE=3DFLAT
                CREATE          CityText=9:10:5:17,"City:",Font2,BORDER,STYLE=3DFLAT
                CREATE          StText=11:12:5:17,"State:",Font2,BORDER,STYLE=3DFLAT
                CREATE          ZipText=13:14:5:17,"Zip Code:",Font2,BORDER,STYLE=3DFLAT
.
.Create the Edittext Objects in Reverse Order
.
                CREATE          NameEdit=5:6:20:70,MAXCHARS=40,FONT=Font2,BORDER
                CREATE          StrEdit=7:8:20:70,MAXCHARS=50,FONT=Font2,BORDER
                CREATE          CityEdit=9:10:20:70,MAXCHARS=40,FONT=Font2,BORDER
                CREATE          StEdit=11:12:20:70,MAXCHARS=40,FONT=Font2,BORDER
                CREATE          ZipEdit=13:14:20:70,MAXCHARS=20,FONT=Font2,BORDER
.
.Create the Names Datalist
.
                CREATE          NameList=16:23:5:75,FONT=Font2
.
.Create the Search Dialog Window & its Objects
.
                CREATE          SDialog=100:300:100:450:
                                WinType=1:              ie, modal
                                TITLE="Record Search"
                CREATE          SDialog;SDsrch=150:175:130:200,"Search",FONT=Font3
                CREATE          SDialog;SDcancel=150:175:220:290,"Cancel",FONT=Font3
                CREATE          SDialog;SDet1=20:40:100:300,FONT=Font2
                CREATE          SDialog;SDsfor=20:40:5:95,"Search For:",Font2:
                                ALIGNMENT=3                           ;Right
                CREATE          SDialog;SDsfield=60:80:5:95,"Search Field:",Font2:
                                ALIGNMENT=3                           ;Right
                CREATE          SDialog;SDstype=100:120:5:95,"Search Type:",Font2:
                                ALIGNMENT=3                           ;Right
                CREATE          SDialog;SDcombo1=60:140:100:300,"":
                                ";Any Field;Name;Street;City;State;Zipcode":
                                FONT=Font2
                CREATE          SDialog;SDcombo2=100:160:100:300,"":
                                ";Free Float;Exact;Left;Right":
                                FONT=Font2
.
. Open the files or create them if they don't exist
.
                TRAP            PrepIsam IF IO
                OPEN            NameFile,IsamName,SHARE
                TRAP            PrepAiam IF IO
                OPEN            AddressFile,AiamName,"?",SHARE
                TRAPCLR         IO
                GOTO            ScreenSetup
.
. Isam File Doesn't Exist - Create It
.
PrepIsam
                PREP            NameFile, DataName, IsamName, "40", "190"
                RETURN
.
. Aim Index Doesn't Exist - Create It
.
PrepAiam
                PREP            AddressFile, DataName, AiamName, AiamKeys, "190"
                RETURN
.
. Activate the Objects
.
ScreenSetup
.
                WINREFRESH
.
                ACTIVATE        Header
                ACTIVATE        NameText
                ACTIVATE        StrText
                ACTIVATE        CityText
                ACTIVATE        StText
                ACTIVATE        ZipText
.
                ACTIVATE        ZipEdit
                ACTIVATE        StEdit
                ACTIVATE        CityEdit
                ACTIVATE        StrEdit
                ACTIVATE        NameEdit
.
                ACTIVATE        FILE,ExitActioN,Result
                ACTIVATE        ActioN,RecAction,Result
.
                ACTIVATE        SDsrch,SearchAction,Result
                ACTIVATE        SDcancel,CancelDialog,Result
                ACTIVATE        SDet1
                ACTIVATE        SDsfor
                ACTIVATE        SDsfield
                ACTIVATE        SDstype
                ACTIVATE        SDcombo1
                ACTIVATE        SDcombo2
.
. Fill the datalist with whatever records exist in the file.
.
                CLEAR           NameCnt
                LOOP
                READ            NameFile,NameCnt;NameData
                UNTIL           OVER
                INSERTITEM      NameList,NameCnt,Name
                ADD             "1",NameCnt
                REPEAT
                   
                DISABLEITEM     NameList,0
                ACTIVATE        NameList,ListAction,Result
.
                CALL            ResetScreen
.
. Wait for an Event to Occur
.
                LOOP
                WAITEVENT
                REPEAT
...........................................................................
. Record Menu Item Selected
.
RecAction
                BRANCH          Result OF NewAction, DeleteAction:
                                PasteAct, StartSDialog, UpdateAction
                RETURN
.
. Setup the proper display state for the various objects
.
ResetScreen
                IF              ( NameCnt = 0)
                DELETEITEM      StrEdit,0
                DELETEITEM      CityEdit,0
                DELETEITEM      StEdit,0
                DELETEITEM      ZipEdit,0
                DELETEITEM      NameEdit,0
                ACTIVATE        NameEdit
                DISABLEITEM     NameList,0
                DISABLEITEM     Action,2
                DISABLEITEM     Action,3
                DISABLEITEM     Action,5
                ELSE
                ENABLEITEM      NameList, 0
                ENABLEITEM      Action,2
                ENABLEITEM      Action,3
                ENABLEITEM      Action,5
                ENDIF
                RETURN
...........................................................................
. Record Addition Requested
.
NewAction
                CALL            GETDATA                  // Retrieve Values
.
. Check for Valid Key
.
                COUNT           Len,Name
                RETURN          IF ZERO
.
. Check for Duplicate Key
.
                READ            NameFile,Name;NewName
                IF              OVER
.
. Write the Data to Disk
.       
                WRITE           AddressFile;Name,Street,City,State,Zipcode
                INSERT          NameFile,Name
.
. Add the Name to the Datalist
.
                INSERTITEM      NameList,NameCnt,Name
                ADD             "1",NameCnt
                SETITEM         NameList,0,NameCnt
                MOVE            NameCnt,Result
                CALL            ListAction
                ELSE
.
. Record Already Exists
.
                PARAMTEXT       Name,"","",""
                ALERT           CAUTION,RecordExists,Result
                IF              (NameCnt > 0)
                GETITEM         NameList,0,Result
                CALL            ListAction
                ENDIF
.
                ENDIF
.
                CALL            ResetScreen
                RETURN
.........................................................................
. Search Requested - Activate the Search Dialog
.
StartSDialog
.
                SETITEM         SDet1,0,""
                SETITEM         SDcombo1,0,FieldVal
                SETITEM         SDcombo2,0,SrchType
.
                SETFOCUS        SDet1
                ACTIVATE        SDialog
                RETURN
.
. Search Button In Search Dialog Clicked
.
SearchAction
 
                DEACTIVATE      SDialog
                GETITEM         SDet1,0,SrchData
                GETITEM         SDcombo1,0,FieldVal
                GETITEM         SDcombo2,0,SrchType
 
.
. Construct the Key
.
                MOVE            SrchTyps(SrchType),SrchChar
                PACK            Key WITH FieldVal,SrchChar,SrchData
                MOVELPTR        Key,Result
.
. Read for the Key if Valid (3 Characters Minimum)
.
                IF              (Result > 5)
                TRAP            SetOver IF IO
                READ            AddressFile,Key;Name,Street,City,State,ZipCode
                TRAPCLR         IO
                ELSE
                CALL            SetOver
                ENDIF
                IF              OVER
                ALERT           NOTE,"Search was Unsuccessful.",Result
                RETURN
                ENDIF
.
. Locate & Select the record in the datalist, display in the edittext objects.
.
                CLEAR           NameCnt
                LOOP
                ADD             "1",NameCnt
                GETITEM         NameList,NameCnt,NewName
                MATCH           Name,NewName
                BREAK           IF EQUAL
                REPEAT          UNTIL OVER
                MOVE            NameCnt,Result
                CALL            ListAction                    ;display in edittext
                SETITEM         NameList,Result,NameCnt       ;select in datalist
                RETURN
............................................................................
. Invalid Key Specified
.
SetOver
                PARAMTEXT       SrchData,"","",""
                ALERT           STOP,BadKeyAlert,Result
                SETFLAG         OVER
                RETURN
.
. User Cancelled Search Dialog
.
CancelDialog
.
                DEACTIVATE      SDialog
                RETURN
...........................................................................
. Display Selected List Item in Edittext Objects
. (Trailing Spaces are Truncated from Each Field)
.
ListAction
                GETITEM         NameList,Result,Name
                READ            NameFile,Name;Name,Street,City,State,Zipcode
                IF              NOT OVER
.
                COUNT           Len,Street
                SETLPTR         Street,Len
.
                COUNT           Len,City
                SETLPTR         City,Len
.
                COUNT           Len,State
                SETLPTR         State,Len
.
                COUNT           Len,ZipCode
                SETLPTR         ZipCode,Len
.
                COUNT           Len,Name
                SETLPTR         Name,Len
.
                CALL            SETDATA
.
                ACTIVATE        NameEdit
                ENDIF
.
                RETURN
............................................................................
.Update the File with the New Information
.
UpdateAction
.
                PACK            Key WITH "02X",Name
                READ            AddressFile,Key;Name
                IF              NOT OVER
                CALL            GETDATA
                UPDATE          AddressFile;Name,Street,City,State,ZipCode
                ENDIF
                RETURN
...........................................................................
.Copy the Current Entry to the Clipboard
.
PasteAct
                CALL            GETDATA
                CLIPSET         Name,Street,City,State,ZipCode
                RETURN
............................................................................
. Delete the current list entry 
.
DeleteAction
.
. Delete From the File First
.
                PACK            Key with "02X",Name
                READ            AddressFile,Key;Name
                DELETEK         NameFile,Name
                DELETE          AddressFile
.
. Delete From the Name List
.
                GETITEM         NameList,0,Result
                DELETEITEM      NameList,Result
.
.Turn Off Selection Bar if Last Item
.
                SUB             "1",NameCnt
                IF              (NameCnt > 0)
                SETITEM         NameList,0,1
                MOVE            "1",Result
                CALL            ListAction
                ENDIF
.
. Reset the Screen and Return
.
                CALL            ResetScreen
                RETURN
...........................................................................
. Exit Requested
.
ExitAction
.
                CLOSE           AddressFile
                CLOSE           NameFile
                STOP
...........................................................................
. Transfer Data from the Edittext Objects to the Variables
.
GETDATA
                GETITEM         NameEdit,0,Name
                GETITEM         StrEdit,0,Street
                GETITEM         CityEdit,0,City
                GETITEM         StEdit,0,State
                GETITEM         ZipEdit,0,ZipCode
                RETURN
...........................................................................
. Transfer Data from the Variables to the Edittext Objects
.
SETDATA
                SETITEM         NameEdit,0,Name
                SETITEM         StrEdit,0,Street
                SETITEM         CityEdit,0,City
                SETITEM         StEdit,0,State
                SETITEM         ZipEdit,0,ZipCode
                RETURN
