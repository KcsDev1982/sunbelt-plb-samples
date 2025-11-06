*------------------------------------------------------------
. DATETIME methods demo (SetToNow, SetAsString, Adjust, Compare, GetAsString)
*------------------------------------------------------------

*-----------------------------
* Data Definitions
*-----------------------------
NOW         DATETIME
PARSED      DATETIME
WORK        DATETIME

RET         FORM        2
CMP         FORM        2

VAL         DIM         30      // input value to parse
OUT_ISO     DIM         40      // ISO-8601 UTC
OUT_LOC     DIM         40      // Local time, custom format
OUT_PAR     DIM         40      // Parsed value (formatted)
OUT_ADJ     DIM         40      // Adjusted parsed value (formatted)

ADJ1        DIM         8       // e.g., +3D  (add 3 days)
ADJ2        DIM         8       // e.g., -2H  (subtract 2 hours)

            CALL        Main
            STOP

*-----------------------------
* Main routine
*-----------------------------
Main        LFUNCTION
            ENTRY

* Set NOW to current UTC, then format as ISO-8601
            MOVE        "0" TO RET
            NOW.SetToNow            GIVING RET USING *LocalTime=0
            NOW.GetAsString         GIVING OUT_ISO USING *Format="%Y-%m-%dT%H:%M:%f%Z"

* Also show NOW in Local Time with a custom format
            NOW.GetAsString         GIVING OUT_LOC USING *Format="%Y-%m-%d %H:%M:%S",*LocalTime=1

* Parse a specific date/time string into PARSED
            MOVE        "2025-12-25 14:30:00" TO VAL
            PARSED.SetAsString      GIVING RET USING *Value=VAL
            PARSED.GetAsString      GIVING OUT_PAR USING *Format="%Y-%m-%d %H:%M:%S",*LocalTime=1

* Make a working copy and apply adjustments
            WORK.SetToDateTime      GIVING RET USING *DateTime=PARSED

* Example adjustments: add 3 days, then subtract 2 hours
            MOVE        "+3D" TO ADJ1
            WORK.Adjust             GIVING RET USING *Value=ADJ1

            MOVE        "-2H" TO ADJ2
            WORK.Adjust             GIVING RET USING *Value=ADJ2

            WORK.GetAsString        GIVING OUT_ADJ USING *Format="%Y-%m-%d %H:%M:%S",*LocalTime=1

* Compare NOW to PARSED (CMP < 0: NOW < PARSED, CMP = 0: equal, CMP > 0: NOW > PARSED)
            MOVE        "0" TO CMP
            NOW.Compare             GIVING CMP USING *DateTime=PARSED

*-----------------------------
* Display results
*-----------------------------
            DISPLAY     *HD,*N,"DATETIME Methods Demo",*N
            DISPLAY     *N,"NOW (UTC ISO):    ",OUT_ISO
            DISPLAY     *N,"NOW (Local):      ",OUT_LOC
            DISPLAY     *N,"PARSED (Local):   ",OUT_PAR
            DISPLAY     *N,"ADJUSTED (Local): ",OUT_ADJ

            IF          (CMP<0)
              DISPLAY   *N,"Compare: NOW is earlier than PARSED",*W2
            ELSEIF      (CMP=0)
              DISPLAY   *N,"Compare: NOW equals PARSED",*W2
            ELSE
              DISPLAY   *N,"Compare: NOW is later than PARSED",*W2
            ENDIF

            FUNCTIONEND
