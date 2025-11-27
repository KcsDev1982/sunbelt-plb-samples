*===========================================================
*  GetWeekdayNameFromString
*  Input : STRING containing a date or datetime
*          Accepted formats include:
*          YYYY-MM-DD
*          YYYY-MM-DD HH:MM:SS
*          (and any valid SetAsString format)
*
*  Output: DIM full weekday name
*===========================================================

GetWeekdayNameFromString LFUNCTION
InStr         DIM         40
              ENTRY

WKSTR         DIM         2
WKNUM         FORM        1
FullName      DIM         10
RET           FORM        2
TMPDT         DATETIME

*-----------------------------------------------------------
* Load the incoming string into a DATETIME object
* SetAsString handles standard date formats (see docs).
*-----------------------------------------------------------
              TMPDT.SetAsString    GIVING RET USING *Value=InStr

* If SetAsString failed (RET ? 0), you may handle errors here.
* But for simplicity, we proceed assuming valid input.

*-----------------------------------------------------------
* Extract weekday number 0–6 (Sunday=0)
*-----------------------------------------------------------
              TMPDT.GetAsString    GIVING WKSTR USING *Format="%w"
              MOVE                 WKSTR TO WKNUM

*-----------------------------------------------------------
* Map number to full weekday name
*-----------------------------------------------------------
              SELECT               USING WKNUM
              WHEN                 0
                MOVE               "Sunday"        TO FullName
              WHEN                 1
                MOVE               "Monday"        TO FullName
              WHEN                 2
                MOVE               "Tuesday"       TO FullName
              WHEN                 3
                MOVE               "Wednesday"     TO FullName
              WHEN                 4
                MOVE               "Thursday"      TO FullName
              WHEN                 5
                MOVE               "Friday"        TO FullName
              WHEN                 6
                MOVE               "Saturday"      TO FullName
              ENDSELECT

              FUNCTIONEND          USING FullName
*---------------------------------------
* Example: Convert a date string to
*          a full weekday name.
*---------------------------------------

MyDateStr     DIM         40
WDAYNAME      DIM         10

              MOVE        "2025-12-25" TO MyDateStr

              CALL        GetWeekdayNameFromString GIVING WDAYNAME USING MyDateStr

              DISPLAY     *N,"Weekday is: ",WDAYNAME,*W4
              STOP
