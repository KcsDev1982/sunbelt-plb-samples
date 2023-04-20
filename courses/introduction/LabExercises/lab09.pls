*---------------------------------------------------------------
.
. Program Name: Lab09.pls
. Description:  Introduction to PL/B Lab 9 program
.
FIRST           FORM            1 // DOW January 1st
LEAP            DIM             1 // Leap Year (Y/N)
MONTH           FORM            2 // Current Month
DAY             FORM            2 // Current Day
LENGTH          FORM            2 // Current Month's Length
REPLY           DIM             1 // Response Variable
DOW             FORM            "1" // Current DOW
DOWSPC          FORM            1 // Spacing counter
*
.Allow Exit
.
                TRAP            QUIT IF ESCAPE
*
.Get the variables
.
                KEYIN           *ES,"DOW for January 1st (1-7): ",DOW:
                                *N,"Leap Year? (Y/N) ",LEAP
*
.Loop through the months
.
                FOR             MONTH,"1","12"
*
.Set the current months length and display the name
. 
                SWITCH          MONTH
                CASE            "1"
                DISPLAY         *N,*N,*H 10,"JANUARY";
                MOVE            "31",LENGTH
                CASE            "2"
                DISPLAY         *N,*N,*H 10,"FEBRUARY";
                IF              (LEAP = "Y")
                MOVE            "29",LENGTH
                ELSE
                MOVE            "28",LENGTH
                ENDIF
                CASE            "3"
                DISPLAY         *N,*N,*H 10,"MARCH";
                MOVE            "31",LENGTH
                CASE            "4"
                DISPLAY         *N,*N,*H 10,"APRIL";
                MOVE            "30",LENGTH
                CASE            "5"
                DISPLAY         *N,*N,*H 10,"MAY";
                MOVE            "31",LENGTH
                CASE            "6"
                DISPLAY         *N,*N,*H 10,"JUNE";
                MOVE            "30",LENGTH
                CASE            "7"
                DISPLAY         *N,*N,*H 10,"JULY";
                MOVE            "31",LENGTH
                CASE            "8"
                DISPLAY         *N,*N,*H 10,"AUGUST";
                MOVE            "30",LENGTH
                CASE            "9"
                DISPLAY         *N,*N,*H 10,"SEPTEMBER";
                MOVE            "31",LENGTH
                CASE            "10"
                DISPLAY         *N,*N,*H 10,"OCTOBER";
                MOVE            "31",LENGTH
                CASE            "11"
                DISPLAY         *N,*N,*H 10,"NOVEMBER";
                MOVE            "30",LENGTH
                DEFAULT
                DISPLAY         *N,*N,*H 10,"DECEMBER";
                MOVE            "31",LENGTH
                ENDSWITCH
*
.Display the column headings
.
                DISPLAY         *N," Sun Mon Tue Wed Thu Fri Sat"
*
.Space over to the beginning day of the week
.
                FOR             DOWSPC,"1",DOW
                DISPLAY         "    ";
                REPEAT
*
.Print the days
.
                FOR             DAY,"1",LENGTH
                INCR            DOW
                IF              (DOW = 8)
                MOVE            "1",DOW
                DISPLAY         ""
                ENDIF
                DISPLAY         " ",DAY," ";
                REPEAT
*
.Go print the next month
.
                KEYIN           *N,"Continue? ",REPLY,*H 1,*EL;
                REPEAT
*
.All done
.
                KEYIN           *HD,*R,"Complete.",REPLY;
QUIT
                STOP
