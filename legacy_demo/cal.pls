. Month Calendar
.
. Author: Matthew Lake
.  Sunbelt Computers Systems, Inc.
.
.............................................................................
.
. Program to illustrate how to create your own control using panels
. 
. Illustrates:
. WINDOW pointers
. PANEL
. STATTEXT
. COLOR
. FONT
. TOOLTIP
. TIMER ( running stand-alone )
.
. Tips/Trics used:
.  Using implode and explode to move data between dissimilar records
. using callbacks into calling program for event notification
. creating objects in calculated positions
.
. entry points:
.
. ZELLER ROUTINE INDATE,DOW
. CREATEMC ROUTINE TWIN,TOP,BOTTOM,LEFT,RIGHT
. MCSHOWDATE ROUTINE NOW
. MCGETDATE ROUTINE SelDATE
. MCHIGHLIGHT ROUTINE DATE,TipText
. MCRMHIGHLIGHT ROUTINE d20,TipText
. MCNOTIFYCHANGE ROUNITE CALLBACK
.............................................................................
                GOTO            #s
DATE            RECORD          definition
YEAR            DIM             4
MONTH           DIM             2
DAY             DIM             2
HOUR            DIM             2
MINUTE          DIM             2
SECOND          DIM             2
SS              DIM             4
                RECORDEND

CDATE           RECORD          definition ; date record used for calculations
YEAR            FORM            5 ; fields are to large to allow overflow without
MONTH           FORM            3 ; data loss
DAY             FORM            3
HOUR            FORM            3
MINUTE          FORM            3
SECOND          FORM            3
SS              FORM            5
                RECORDEND

#BUFFER         DIM             ^30
MONTHDAYS       FORM            2(0..13),("0"),("31"),("28"),("31"),("30"),("31"),("30"):
                                ("31"),("31"),("30"),("31"),("30"),("31"),("0")
.WEEKDAY DIM 10(0..6),("Sunday"),("Monday"),("Tuesday"),("Wednesday"):
.   ("Thursday"),("Friday"),("Saturday")

MONTHNAMES      DIM             12(12),("January"),("Feburary"),("March"),("April"):
                                ("May"),("June"),("July"),("August"):
                                ("September"),("October"),("November"):
                                ("December")

USSHRTNMS       FORM            1
SMONTHNAMES     DIM             12(12),("Jan"),("Feb"),("Mar"),("Apr"):
                                ("May"),("Jun"),("Jul"),("Aug"):
                                ("Sep"),("Oct"),("Nov"):
                                ("Dec")

ON              FORM            "1"
OFF             FORM            "0"

WKD1            RECORD          LIKE DATE
CWKD1           RECORD          LIKE CDATE

INDATE          DIM             ^
DOW             FORM            ^
D               FORM            2
C               FORM            2
FM5             FORM            5
ZELLER          ROUTINE         INDATE,DOW
.The following formula - named Zeller's Rule - allows you to calculate a day 
.of the week FOR any date:
.F = k + [(13 x m-1)/5] + D + [D/4] + [C/4] - 2 x C
.k is the day of the month. Let's use January 27, 2024 as an example. FOR 
.  this date, k = 27.
.m is the month number. Months have to be counted specially: March is 1, 
.  April is 2, AND so on to February, which is 12 (this makes the formula 
.  simpler, because on leap years February 29 is counted as the last day of 
.  the year). Because of this rule, January AND February are always counted 
.  as the 11th AND 12th months of the previous year. In our example, m = 11.
.D is the last two DIGITS of the year. Because of the month numbering, D = 23 
.  in our example, even though we are USING a date from 2024.
.C stands FOR century: it's the first two DIGITS of the year. 
.  In our CASE, C = 20.
                UNPACK          INDATE,WKD1
                IMPLODE         #BUFFER,",",WKD1
                EXPLODE         #BUFFER,",",CWKD1
                SUB             "2",CWKD1.MONTH
                IF              (CWKD1.MONTH <= "0")
                ADD             "12",CWKD1.MONTH
                SUB             "1",CWKD1.YEAR  ; jan/feb are 11/12 of previous year
                ENDIF           ; for our calculation
                MOVE            CWKD1.YEAR,D
                MOVE            (CWKD1.YEAR/100),C
                CALC            FM5=CWKD1.DAY+((("13"*CWKD1.MONTH)-1)/5)+D+(D/4)+(C/4)-(2*C)
                LOOP
                UNTIL           (FM5>="0")
                ADD             "7",FM5
                REPEAT
                MOVE            (FM5 - ( (FM5/7) *7 )),DOW
                RETURN

TWIN            WINDOW          ^
MCTRL           PANEL
MCTRLDAYS       STATTEXT        (0..6,7)
TITLE           STATTEXT
PMONTH          STATTEXT
NMONTH          STATTEXT
PYEAR           STATTEXT
NYEAR           STATTEXT
CBLUE           COLOR
CRED            COLOR
CBG             COLOR
fstyle          FONT
TOP             FORM            4
BOTTOM          FORM            4
LEFT            FORM            4
RIGHT           FORM            4
H               FORM            4
W               FORM            4
X               FORM            4
Y               FORM            4

WEEKLTR         INIT            "SMTWTFS"
NOW             DIM             20
CALLBACK        DIM             50
MNCURSOR        DIM             8
DISP            RECORD          LIKE Date
FM2             FORM            2
FM4             FORM            4
DIFF            DIM             20
DOWEEK          FORM            1
MD              FORM            2
WK              FORM            1
MONTHCAL        FORM            2(6,7)
D2              DIM             2
D8              DIM             8
OID             FORM            8
CMONTH          DIM             10
CYEAR           DIM             4
CDAY            DIM             2
BTNFACE         FORM            "2147483663"  //$BTNFACE

.***********************************************************************
. routine to create a calendar specifying a window and size of calendar
.
CREATEMC        ROUTINE         TWIN,TOP,BOTTOM,LEFT,RIGHT
.
. create some usefull colors
.
                CREATE          CBLUE=196:196:240
                CREATE          CRED=*RED
                CREATE          CBG=*WHITE
.
. The entire calendar will be contained within a panel
.
                CREATE          TWIN;MCTRL=TOP:BOTTOM:LEFT:RIGHT,BDRSTYLE=3,BGCOLOR=BTNFACE

. make some calculations needed to determine avaiable size for title display

                MOVE            (BOTTOM-TOP),H
                MOVE            (RIGHT-LEFT),W
                MOVE            W,OID
                DIV             "7",OID
.
. use longest possible date string
                PACK            #BUFFER,MONTHNAMES(9)," 7777"
.
. create month title
. 
                CREATE          MCTRL;TITLE=1:H:(2*OID):(W-(2*OID)),#BUFFER,">Arial":
                                ALIGNMENT=1
.
. determin if short month names should be used...
.
                GETPROP         TITLE,FONT=fstyle
.
. getinfo will return how many pixels our month title requires to display
.
                GETINFO         TYPE=fstyle,#BUFFER
                RESET           #BUFFER,25
                SETLPTR         #BUFFER,28
                MOVE            #BUFFER,FM4
.
. If the width of the label is larger than the width of the lable object
. we will use the short names for months
.
                GETPROP         TITLE,WIDTH=W
                IF              ( FM4 > W )
                SET             USSHRTNMS
                ELSE
                CLEAR           USSHRTNMS
                ENDIF
.
. default to todays date
. 
                CLOCK           TIMESTAMP,NOW
.
MCSHOWDATE      ROUTINE         NOW
                CLEAR           MONTHCAL
                UNPACK          NOW,DISP
.
. what day of the week was the first of the specified month
. 
                MOVE            NOW,DIFF
                RESET           DIFF,6  // position of DAY
                APPEND          "01",DIFF
                RESET           DIFF
                CALL            ZELLER USING DIFF,DOWEEK

. calculate size and positions for objects
                MOVE            (BOTTOM-TOP),H
                MOVE            (RIGHT-LEFT),W
.
. calculate how many weeks the month will span plus 2 rows for headers
. to figure out the height of each cell.
. 
                MOVE            DISP.MONTH,FM2
                IF              ( MONTHDAYS(FM2) = "31" AND DOWEEK >= "5" )
                DIV             "8",H
                ELSE            IF ( MONTHDAYS(FM2) = "30" AND DOWEEK = "6" )
                DIV             "8",H
                ELSE
                DIV             "7",H
                ENDIF
.
. there are always 7 columns 
. 
                MOVE            W,OID
                DIV             "7",OID
.
. start creating screen objects
.
                IF              (USSHRTNMS) // short names
                PACK            DIFF,SMONTHNAMES(FM2)," ",DISP.YEAR
                ELSE
                PACK            DIFF,MONTHNAMES(FM2)," ",DISP.YEAR
                ENDIF
.
                CREATE          MCTRL;TITLE=1:H:(2*OID):(W-(2*OID)),DIFF,">Arial":
                                ALIGNMENT=1
                ACTIVATE        TITLE
.
. create some control objects to move to next/previous month
.
                CREATE          MCTRL;PYEAR=1:H:1:OID,"<<",">Arial",ALIGNMENT=1
                CREATE          MCTRL;PMONTH=1:H:OID:(OID*2),"<",">Arial",ALIGNMENT=1
                CREATE          MCTRL;NMONTH=1:H:(W-(2*OID)):((W-(2*OID))+OID),">",">Arial",ALIGNMENT=1
                CREATE          MCTRL;NYEAR=1:H:((W-(2*OID))+OID):((W-(2*OID))+(OID*2)),">>",">Arial",ALIGNMENT=1
                ACTIVATE        PYEAR,PREYEAR,FM2
                ACTIVATE        PMONTH,PREMONTH,FM2
                ACTIVATE        NMONTH,NXMONTH,FM2
                ACTIVATE        NYEAR,NXYEAR,FM2
                MOVE            OID,W
.
. populate the calendar
. 
                MOVE            DISP.MONTH,FM2
                MOVE            DISP.YEAR,FM4
.
. adjust febuary for leap year
. 
                IF              (FM2="2")
                IF              ((FM4 - (( FM4/4)*4)) = "0")
                MOVE            "29",MONTHDAYS(FM2)
                ELSE
                MOVE            "28",MONTHDAYS(FM2)
                ENDIF
                ENDIF
.
. fill in the month grid array
. 
                MOVE            "1",WK
                FOR             MD,"1",MONTHDAYS(FM2)
                INCR            DOWEEK
                IF              ( DOWEEK >"7")
                SET             DOWEEK
                INCR            WK
                ENDIF
                MOVE            MD,MONTHCAL(WK,DOWEEK)
                REPEAT
.
. create day of week labels
. 
                CLEAR           X
                MOVE            " ",D2
                RESET           WEEKLTR
                FOR             Y,"1","7"
                CMOVE           WEEKLTR,D2
                CREATE          MCTRL;MCTRLDAYS(X,Y)=(((X+1)*H)+1):((((X+1)*H)+H)-1):(((Y*W)-W)+1):((Y*W)),D2:
                                ">Arial",OBJECTID=OID,BGCOLOR=CBG,ALIGNMENT=1
                ACTIVATE        MCTRLDAYS(X,Y)
                BUMP            WEEKLTR
                REPEAT
.
. create days
.
                MOVE            DISP.DAY,FM2
. cant display non-existant days
                IF              ( FM2 > MD )
                MOVE            (MD-1),FM2
                ENDIF
.
                FOR             X,"1","6"  // up to six weeks
                FOR             Y,"1","7"  // 7 days
.
. check month grid array to see if this is a valid day
.
                IF              ( MONTHCAL(X,Y) )
                MOVE            MONTHCAL(X,Y),D2
                PACK            D8,X,Y
                REPLACE         " 0",D8
                MOVE            D8,OID
.
.  FM2 holds the selected day so use a different background color
.
                IF              ( MONTHCAL(X,Y) = FM2 )
                CREATE          MCTRL;MCTRLDAYS(X,Y)=(((X+1)*H)+1):(((X+1)*H)+H):(((Y*W)-W)+1):(Y*W),D2:
                                ">Arial",OBJECTID=OID,BGCOLOR=CBLUE,ALIGNMENT=1
                MOVE            D8,MNCURSOR
                ELSE
                CREATE          MCTRL;MCTRLDAYS(X,Y)=(((X+1)*H)+1):(((X+1)*H)+H):(((Y*W)-W)+1):(Y*W),D2:
                                ">Arial",OBJECTID=OID,BGCOLOR=CBG,ALIGNMENT=1
                ENDIF
. color sundays red
                IF              (Y="1")
                SETPROP         MCTRLDAYS(X,Y),FGCOLOR=CRED
                ENDIF
.
. show the day and catch the click event for this day.
                ACTIVATE        MCTRLDAYS(X,Y)
                EVENTREG        MCTRLDAYS(X,Y),4,DAYCLICK,OBJECTID=OID
                ELSE
.
. if we advanced to this month, destroy residual objects from previously
. displayed months
.
                DESTROY         MCTRLDAYS(X,Y)
                ENDIF

                REPEAT
                REPEAT
.
. show the panel after all other objects are created.
.
                ACTIVATE        MCTRL
                RETURN
.***********************************************************************
. provide an entry point the caller can use to tell us what routine to call
. when things change
.
MCNOTIFYCHANGE  ROUTINE         CALLBACK
                RETURN
.
. call the routine the user requested
. 
UserChanged
                TEST            CALLBACK
                IF              NOT EOS
                CALLS           CALLBACK
                ENDIF
                RETURN
.***********************************************************************
. user clicked on a day
.
DAYCLICK
. get the previous selected day and set the backgroud to normal
                UNPACK          MNCURSOR,X,Y
                SETPROP         MCTRLDAYS(X,Y),BGCOLOR=CBG
.
. set the background of the newly selected day
                MOVE            OID,D8
                UNPACK          D8,X,Y
                SETPROP         MCTRLDAYS(X,Y),BGCOLOR=CBLUE
.
. update our internal cursor
.
                MOVE            D8,MNCURSOR
.
. see if user requested notification
. 
                CALL            UserChanged
                RETURN
.***********************************************************************
. user clicked on previous year control object
.
PREYEAR
. get the current date displayed
                CALL            MCGETDATE USING DIFF
                UNPACK          DIFF,WKD1
. subtract 1 from year
                MOVE            WKD1.YEAR,FM4
                DECR            FM4
                MOVE            FM4,WKD1.YEAR
.
. re-create the calendar with new date
. 
                PACK            DIFF,WKD1
                CALL            MCSHOWDATE USING DIFF
.
. see if user requested notification
. 
                CALL            UserChanged
                RETURN
.***********************************************************************
. user clicked on previous month control object
. 
PREMONTH
. get the current date displayed
                CALL            MCGETDATE USING DIFF
                UNPACK          DIFF,WKD1
.
. subtract one from month and roll to previous year if necessary
.
                MOVE            WKD1.MONTH,FM2
                DECR            FM2
                IF              ZERO
                MOVE            "12",FM2
                MOVE            WKD1.YEAR,FM4
                SUB             "1",FM4
                MOVE            FM4,WKD1.YEAR
                ENDIF
                MOVE            FM2,WKD1.MONTH
.
. re-create the calendar with new date
. 
                PACK            DIFF,WKD1
                REPLACE         " 0",DIFF
                CALL            MCSHOWDATE USING DIFF
.
. see if user requested notification
. 
                CALL            UserChanged
                RETURN
.***********************************************************************
. user clicked on next year control object
. 

NXYEAR
. get the current date displayed
                CALL            MCGETDATE USING DIFF
                UNPACK          DIFF,WKD1
                MOVE            WKD1.YEAR,FM4
.
. simply incrament the year.
. 
                INCR            FM4
                MOVE            FM4,WKD1.YEAR
.
. re-create the calendar with new date
. 
                PACK            DIFF,WKD1
                CALL            MCSHOWDATE USING DIFF
.
. see if user requested notification
. 
                CALL            UserChanged
                RETURN
.***********************************************************************
. user clicked on next year control object
. 
NXMONTH
. get the current date displayed
                CALL            MCGETDATE USING DIFF
                UNPACK          DIFF,WKD1
                MOVE            WKD1.MONTH,FM2
.
. add one to month and roll over year if necessary
. 
                INCR            FM2
                IF              ( FM2>"12")
                MOVE            "1",FM2
                MOVE            wkd1.YEAR,FM4
                INCR            FM4
                MOVE            fm4,wkd1.YEAR
                ENDIF
                MOVE            FM2,WKD1.MONTH
.
. re-create the calendar with new date
. 
                PACK            DIFF,WKD1
                CALL            MCSHOWDATE USING DIFF
.
. see if user requested notification
. 
                CALL            UserChanged
                RETURN
.***********************************************************************
. routine to return the currently displayed date in a packed string
.
MCGETDATE       ROUTINE         INDATE
.
. since the cursor only contains a grid posistion, we will construct the
. date from the data in the objects.
.
.
. get the name of the month and the year frin the title object
. .
                GETPROP         TITLE,TEXT=DIFF
                EXPLODE         DIFF," ",CMONTH,CYEAR
.
. get the day from the grid cursor position
.
                UNPACK          MNCURSOR,X,Y
                GETITEM         MCTRLDAYS(X,Y),0,CDAY
.
. search month name arrays for the numeric month.
.
                IF              (USSHRTNMS)
                SEARCH          CMONTH,SMONTHNAMES(1),"12",FM2
                ELSE
                SEARCH          CMONTH,MONTHNAMES(1),"12",FM2
                ENDIF
.
. now pack it all together.
.
                PACK            INDATE,CYEAR,FM2,CDAY
                REPLACE         " 0",INDATE
                RETURN
.***********************************************************************
. routine to bold a specified day and to set a tooltip value for that day
. 
d20             DIM             20
TOOLTIPTEXT     DIM             80
MCHIGHLIGHT     ROUTINE         d20,TOOLTIPTEXT
.
. get the current data displayed
. 
                CALL            MCGETDATE USING NOW
.
. make sure the day we are highlighting is in the current year/month
.
                SETLPTR         Now,6
                MOVELPTR        d20,FM5
                SETLPTR         d20,6
                RETURN          IF (NOW!=d20) ; correct year and month...
.
. search for the specified day in the grid
.
                SETLPTR         d20,8
                RESET           d20,7
                MOVE            d20,MD
                FOR             wk,"1","6"
                FOR             DOWEEK,"1","7"
                IF              ( MONTHCAL(wk,DOWEEK) = MD )
.
. selected day is found in grid, BOLD the font and set the TOOLTIP
.
                GETPROP         MCTRLDAYS(wk,DOWEEK),FONT=fstyle
                SETPROP         fstyle,BOLD=ON
                SETPROP         MCTRLDAYS(wk,DOWEEK),FONT=fstyle
                SETPROP         MCTRLDAYS(wk,DOWEEK),TOOLTIP=TOOLTIPTEXT
.
. make sure we clear our local variable so we don't have residue on next call
. 
                CLEAR           TOOLTIPTEXT
. don't waste time on the rest of the grid, just return.
                RETURN
                ENDIF
                REPEAT
                REPEAT
                CLEAR           TOOLTIPTEXT
                RETURN
.***********************************************************************
. this routine will clear the highlight for the specified day
. 
MCRMHIGHLIGHT   ROUTINE         d20,TOOLTIPTEXT
.
. get the current data displayed
. 
                CALL            MCGETDATE USING NOW
.
. make sure the day we are highlighting is in the current year/month
.
                SETLPTR         Now,6
                MOVELPTR        d20,FM5
                SETLPTR         d20,6
                RETURN          IF (NOW!=d20) ; correct year and month...
.
. search for the specified day in the grid
.
                SETLPTR         d20,8
                RESET           d20,7
                MOVE            d20,MD
                FOR             wk,"1","6"
                FOR             DOWEEK,"1","7"
                IF              ( MONTHCAL(wk,DOWEEK) = MD )
.
. selected day is found in grid, UNBOLD the font and set the TOOLTIP
.
                GETPROP         MCTRLDAYS(wk,DOWEEK),FONT=fstyle
                SETPROP         fstyle,BOLD=OFF
                SETPROP         MCTRLDAYS(wk,DOWEEK),FONT=fstyle
                SETPROP         MCTRLDAYS(wk,DOWEEK),TOOLTIP=TOOLTIPTEXT
.
. make sure we clear our local variable so we don't have residue on next call
. 
                CLEAR           TOOLTIPTEXT
. don't waste time on the rest of the grid, just return.
                RETURN
                ENDIF
                REPEAT
                REPEAT
                CLEAR           TOOLTIPTEXT
                RETURN
.
#S
**************************************************************************
. Sample program to illustrate how to use the calendar
.
t               FORM            4
b               FORM            4
l               FORM            4
r               FORM            4
dsave           DIM             20
MYWIN           WINDOW
.
. hide the main window
.
                WINHIDE
.
. create a window and pass it into the calendar create routine
.
                CREATE          MYWIN=1:125:1:140,WINBORDER=8
                CALL            CREATEMC USING MYWIN,"1","123","1","138"
.
. register $CLOSE and $RESIZE events on the window
.
                EVENTREG        MYWIN,5,EXIT ;close
                EVENTREG        MYWIN,17,RESIZ
.
. call routine that will update the calendar for today
.
                CALL            ShowToday
.
. tell the calendar functions that we want to know when somthing changes
.
                CALL            MCNOTIFYCHANGE using "ForceUpdate"
.
. show the window after everthing else
.
                ACTIVATE        MYWIN
.
. wait for user actions
.
                LOOP
                WAITEVENT
                REPEAT
EXIT
                SHUTDOWN
.
. resize event occurred
RESIZ
.
. get the current date from the calendar
.
                CALL            MCGETDATE USING dsave
.
. get the new size of the window
.
                GETPROP         MYWIN,TOP=t,LEFT=l,HEIGHT=b,WIDTH=r
.
. re-create the calendar with the new size
.
                SUB             "2",b
                SUB             "2",r
                CALL            CREATEMC USING MYWIN,"1",b,"1",r
.
. make sure we are displaying the same date we started with
.
                CALL            MCSHOWDATE USING dsave
                RETURN
.
. routine to initialize the screen and tell the calendar what day to show
.
dm8             DIM             8
ShowToday
. get todays date and time
                CLOCK           TIMESTAMP,dsave
.
. tell the calendar to show todays date
.
                CALL            MCSHOWDATE USING dsave
.
. set the window title with time and date
.
                UNPACK          dsave,WKD1
                PACK            dsave,WKD1.HOUR,":",WKD1.MINUTE,":",WKD1.SECOND," ":
                                WKD1.MONTH,"/",WKD1.DAY,"/",WKD1.YEAR
                SETPROP         MYWIN,TITLE=dsave
                RETURN
 
ForceUpdate     ROUTINE
. to-do, calendar changed...
. 
                RETURN
