*---------------------------------------------------------------
.
. Program Name: Lab13.pls
. Description:  Introduction to PL/B Lab 13 program
.           
.
DATA            DIM             100
NWORK20         FORM            20
*
.Standard Clock Keywords
.
                CLOCK           DATE,DATA
                DISPLAY         *HD,*R,"Date: ",DATA
.
                CLOCK           DAY,DATA
                DISPLAY         "Day: ",DATA
.
                CLOCK           TIME,DATA
                DISPLAY         "Time: ",DATA
.
                CLOCK           TIMESTAMP,DATA
                DISPLAY         "Timestamp: ",DATA
.
                CLOCK           WEEKDAY,DATA
                DISPLAY         "Weekday: ",DATA
.
                CLOCK           YEAR,DATA
                DISPLAY         "Year: ",DATA
.
                CLOCK           CPUTIME,NWORK20
                DISPLAY         "Cputime: ",NWORK20
.
                CLOCK           SECONDS,NWORK20
                DISPLAY         "Seconds: ",NWORK20
.
                CLOCK           SYSDATE,DATA
                DISPLAY         "Sysdate: ",DATA
*
.The Entire Environment
.
                CLEAR           DATA
                LOOP
                CLOCK           ENV,DATA
                BREAK           IF OVER
                DISPLAY         *N,"ENV: ",DATA;
                REPEAT
*
.INI Keyword
.
                MOVE            "PLB_PATH",DATA
                CLOCK           INI,DATA
                DISPLAY         "PLB_PATH: ",DATA
.
                MOVE            "PLB_SYSTEM",DATA
                CLOCK           INI,DATA
                DISPLAY         "PLB_SYSTEM: ",DATA
.  
                KEYIN           DATA
                STOP
