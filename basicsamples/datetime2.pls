*---------------------------------------------------------------------
.  Demonstration of the Sunbelt PL/B DATETIME object
.  Shows:  SetToNow, GetAsString, SetAsString, Adjust, Compare
*---------------------------------------------------------------------

*-------------------------------
*  Data Definitions
*-------------------------------
NOW             DATETIME                // Current system time (UTC)
LOCALTIME       DATETIME                // Local time copy
CUSTOM          DATETIME                // Parsed date/time
RET             FORM        2
CMP             FORM        2
OUT_ISO         DIM         40
OUT_LOCAL       DIM         40
OUT_CUSTOM      DIM         40
OUT_ADJ         DIM         40
VAL             DIM         30
ADJSTR          DIM         8

                CALL        MAIN
                STOP

*---------------------------------------------------------------------
.  Main routine
*---------------------------------------------------------------------
MAIN            LFUNCTION
                ENTRY

*---------------------------------------------------------------------
.  1.  Obtain current system date/time (UTC)
*---------------------------------------------------------------------
                NOW.SetToNow            GIVING RET USING *LocalTime=0
                NOW.GetAsString         GIVING OUT_ISO USING *Format="%Y-%m-%dT%H:%M:%S%Z"

*---------------------------------------------------------------------
.  2.  Get same time as Local
*---------------------------------------------------------------------
                LOCALTIME.SetToNow      GIVING RET USING *LocalTime=1
                LOCALTIME.GetAsString   GIVING OUT_LOCAL USING *Format="%Y-%m-%d %H:%M:%S",*LocalTime=1

*---------------------------------------------------------------------
.  3.  Parse a specific datetime string
*---------------------------------------------------------------------
                MOVE        "2025-12-25 14:30:00" TO VAL
                CUSTOM.SetAsString      GIVING RET USING *Value=VAL
                CUSTOM.GetAsString      GIVING OUT_CUSTOM USING *Format="%Y-%m-%d %H:%M:%S",*LocalTime=1

*---------------------------------------------------------------------
.  4.  Adjust that datetime (+2 days)
*---------------------------------------------------------------------
                MOVE        "+2D" TO ADJSTR
                CUSTOM.Adjust           GIVING RET USING *Value=ADJSTR
                CUSTOM.GetAsString      GIVING OUT_ADJ USING *Format="%Y-%m-%d %H:%M:%S",*LocalTime=1

*---------------------------------------------------------------------
.  5.  Compare NOW and CUSTOM
*---------------------------------------------------------------------
                MOVE        "0" TO CMP
                NOW.Compare             GIVING CMP USING *DateTime=CUSTOM

*---------------------------------------------------------------------
.  6.  Display results
*---------------------------------------------------------------------
                DISPLAY     *HD,*N,"DATETIME OBJECT DEMONSTRATION",*N
                DISPLAY     *N,"Current UTC Time : ",OUT_ISO
                DISPLAY     *N,"Local  Time      : ",OUT_LOCAL
                DISPLAY     *N,"Custom Time      : ",OUT_CUSTOM
                DISPLAY     *N,"Adjusted +2 Days : ",OUT_ADJ

                IF          (CMP<0)
                    DISPLAY *N,"NOW is earlier than CUSTOM",*W2
                ELSEIF      (CMP=0)
                    DISPLAY *N,"NOW equals CUSTOM",*W2
                ELSE
                    DISPLAY *N,"NOW is later than CUSTOM",*W2
                ENDIF

                FUNCTIONEND
