*...........................................................................
.
.Example Program: SCRDEMO.PLS
.
.This sample programs shows some of the graphical objects available.
.Also, coordination between objects is shown.
.
.Copyright @ 1997, Sunbelt Computer Systems, Inc.
.All Rights Reserved.
.............................................................................
.
.Sample Menu Item
.
SMenu           MENU
SData           INIT            ")Sample;":
                                "Chec)k Menu Item;":
                                ")Disable Test Alert;":
                                ")Test Alert..."
*
.Local Variables
.
Result          FORM            1
CheckV          FORM            "0"
DisableV        FORM            "0"
Current         FORM            "1"
Counter         FORM            1
*
.Objects and Data
.
Quit            BUTTON
.
BookCB          COMBOBOX
BookData        INIT            "x;":
                                "Business;":
                                "Fiction;":
                                "Health;":
                                "Mystery;":
                                "Romance;":
                                "Travel;":
                                "Western"
.
BookList        DATALIST
Reason          ICON
DisableL        CHECKBOX
DisableB        CHECKBOX
Text            STATTEXT
Text1           STATTEXT
EDIT            EDITTEXT
*
.Book Names
.
BName           DIM             20
BName1          INIT            "Sunset Over Water"
BName2          INIT            "Selling Oranges"
BName3          INIT            "You and Your Liver"
BName4          INIT            "Visiting Wawa"
BName5          INIT            "Taxes Made Easy"
BName6          INIT            "New Dance Steps"
*
.Book Values
.
BValue          FORM            1
BValue1         FORM            "2"
BValue2         FORM            "1"
BValue3         FORM            "3"
BValue4         FORM            "6"
BValue5         FORM            "4"
BValue6         FORM            "5"
*............................................................................
.
.Ready the Screen
.
                SETMODE         *LTGRAY=ON,*3D=ON
                DISPLAY         *BGCOLOR=*YELLOW,*ES;
*
.Create the Sample Menu
.
                CREATE          SMenu,SData
*
.Create the Label and Edittext Object
.
                CREATE          Text=4:5:5:20,"Book Title:","Times(9,Bold)",ALIGNMENT=3
                CREATE          Edit=4:5:22:50,FONT="Times(9,Bold)",BORDER
*
.Create the Label and Combobox
.
                CREATE          Text1=6:7:5:20,"Book Classification:":
                                "Times(9,Bold)",ALIGNMENT=3
                CREATE          BookCB=6:7:22:50,"",BookData
*
.Create the Book Datalist
.
                CREATE          BookList=9:14:5:50,FONT="Times(12,Bold)"
*
.Create the Icon
.
                CREATE          Reason=2:70,10040
*
.Create the Disable Buttons
.
                CREATE          DisableL=16:17:5:24,"Disable Book &List"
                CREATE          DisableB=18:19:5:24,"Disable Quit &Button"
*
.Create the Quit Button
.
                CREATE          Quit=22:23:35:45,"&Quit"
*
.Load the Datalist
.
                MOVE            "1",Counter
                LOOP
                LOAD            BName BY Counter FROM BName1,BName2:
                                BName3,BName4,BName5,BName6
                INSERTITEM      BookList,999,BName
                ADD             "1",Counter
                REPEAT          UNTIL (Counter = 7)
*
.Activate the Sample Menu
.
                ACTIVATE        SMenu,Menu,Result
*
.Activate the Label and Edittext
.
                ACTIVATE        Text
                SETITEM         Edit,0,BName
                ACTIVATE        Edit
*
.Activate the Label and Combobox
.
                ACTIVATE        Text1
                SETITEM         BookCB,0,BValue1
                ACTIVATE        BookCB,BookMenu,Result
*
.Activate the Datalist
.
                SETITEM         BookList,0,Current
                ACTIVATE        BookList,BookList,Result
*
.Activate the Icon
.
                ACTIVATE        Reason,Reason,Result
*
.Activate the Disable Checkboxes
.
                ACTIVATE        DisableL,DisList,Result
                ACTIVATE        DisableB,DisButton,Result
*
.Activate the Quit Button
.
                ACTIVATE        Quit,QuitR,Result
*
.Place the Focus on the DataList
.
                SETFOCUS        BookList
*
.Wait for an Event to Occur
.
                LOOP
                WAITEVENT
                REPEAT
*..............................................................................
.      
.Menu Item Selected
.
Menu
                BRANCH          Result to Check,Disable,Alert
                RETURN
*
.Flip the Check Flag
.
Check
                IF              (CheckV = 0)
                SET             CheckV
                CHECKITEM       SMenu,Result,ON
                ELSE
                CLEAR           CheckV
                CHECKITEM       SMenu,Result,OFF
                ENDIF
                RETURN
*
.Disable the Item
.
Disable
                IF              (DisableV = 0)
                SET             DisableV
                DISABLEITEM     SMenu,3
                SETITEM         SMenu,Result,")Enable Test Alert"
                ELSE
                CLEAR           DisableV
                ENABLEITEM      SMenu,3
                SETITEM         SMenu,Result,")Disable Test Alert"
                ENDIF
.
                RETURN
*
.Display an Alert
.
Alert
                ALERT           NOTE,"Test Alert",Result,"SCRDEMO"
                RETURN
*..........................................................................
.
.A Combobox Item was Selected
.
BookMenu
                STORE           Result USING Current,BValue1,BValue2,BValue3,BValue4:
                                BValue5,BValue6
                RETURN
*..........................................................................
.
.A Datalist Item Was Selected - Update the Edittext and Combobox Objects
.
BookList
                MOVE            Result,Current
.
                LOAD            BName USING Current FROM BName1:
                                BName2,BName3,BName4,BName5,BName6
.
                LOAD            BValue USING Current FROM BValue1,BValue2:
                                BValue3,BValue4,BValue5,BValue6
.
                SETITEM         Edit,0,BName
                SETITEM         BookCB,0,BValue
.
                RETURN
*.........................................................................
.
.Icon Clicked
.
Reason
                ALERT           NOTE,"Sample application using GUI PL/B",Result:
                                "SCRDEMO"
                RETURN
*..........................................................................
.
.Disable the book list
.
DisList
                IF              (Result = 0)
                SETITEM         DisableL,0,1
                DISABLEITEM     BookList,0
                ELSE
                SETITEM         DisableL,0,0
                ENABLEITEM      BookList,0
                ENDIF
.
                RETURN
*...........................................................................
.
.Disable the Quit button
.
DisButton
                IF              (Result = 0)
                SETITEM         DisableB,0,1
                DISABLEITEM     Quit,0
                ELSE
                SETITEM         DisableB,0,0
                ENABLEITEM      Quit,0
                ENDIF
.
                RETURN
*..........................................................................
.
.Terminate the Program
.
QuitR
                ALERT           PLAIN,"Do you wish to exit this program ?":
                                RESULT,"SCRDEMO"
                STOP            IF (Result = 1)
                RETURN
