............................................................................
. Example program: ICONS.PLS
.
. This demo shows the standard Icons which are available with
. the Windows runtime. The resource numbers for these standard
. Icons start at 10020.
.
. Copyright @ 1997-1999, Sunbelt Computer Systems, Inc.
. All Rights Reserved.
.............................................................................
. Revision History
.
. 9-15-98 JSS: Convert to GUI screen I/O
.............................................................................
.
.Define the Replacement File Menu
.
File            MENU
FileData        INIT            ")File;E)xit"
.
.Define the Program Banner
.
Header          STATTEXT
.
. Define the Icon Objects
.
Icon            ICON            (3)
.
. Definethe Next Button
.
Next            BUTTON
.
. Local Variables
.
IconNumb        FORM            "10000"
Result          FORM            1
Column          FORM            1
HPOS            FORM            2
.
ST1             STATTEXT
ST2             STATTEXT
NOTE            DIM             70
ANUMBER         DIM             6
............................................................................
. Ready the Screen
.
                SETMODE         *LTGRAY=ON
                SETWTITLE       "Demonstration Program"
                DISPLAY         *BGCOLOR=*YELLOW, *ES,*FGCOLOR=*MAGENTA
.
. Ready the Banner
.
                CREATE          Header=2:3:23:55,"Std Icon Demo","times(24,italic)"
                ACTIVATE        Header
.
. Ready the Next Button
.
                CREATE          Next=23:24:35:45,"Next"
                ACTIVATE        Next,NextIcon,Result
.
. Replace the File Menu
.
                CREATE          File,FileData
                ACTIVATE        File,End,Result
.
. Display three Icons
.
 
                MOVE            "Icon numbers: ",NOTE
                CREATE          ST1=10:10:15:60,NOTE,"FIXED(10,BOLD)"
                ACTIVATE        ST1
 
                CALL            NextIcon
.
. Wait for an Event to Occur
.
                LOOP
                WAITEVENT
                REPEAT
..........................................................................
. Fetch Next Three Icons
.
NextIcon
                MOVE            "1",Column
                LOOP
NextIcn1
                TRAP            NOICON IF OBJECT
                MOVE            (((Column - 1) * 10) + 30),HPOS
                CREATE          Icon(Column)=12:HPOS,IconNumb
                ACTIVATE        Icon(Column)
.
                RESET           NOTE,(HPOS-16)
                LENSET          NOTE
                APPEND          IconNumb,NOTE
                RESET           NOTE
                SETITEM         ST1,0,NOTE
 
.           DISPLAY   *P=HPOS:10,IconNumb
.
                ADD             "1",IconNumb
                STOP            IF (IconNumb     > 10140)
.
                ADD             "1",Column
                REPEAT          UNTIL (Column = 4)
                RETURN
.............................................................................
. Icon Does Not Exist
.
NoIcon
                NORETURN
                ADD             "1",IconNumb
                STOP            IF (IconNumb     > 10140)
                GOTO            NextIcn1
..........................................................................
. Exit Requested
.
End
                STOP
