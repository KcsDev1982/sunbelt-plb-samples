*---------------------------------------------------------------
.
. Program Name: math.pls
. Description:  Visual PL/B Programming program
.  
DATA            DIM             20
Value1          FORM            10
Value2          FORM            10
Value3          FORM            10
Length1         INTEGER         1
Length2         INTEGER         1
Result          INTEGER         1
MAIN            PLFORM          MATH.PLF
.
                WINHIDE
                FORMLOAD        MAIN
                LOOP
                EVENTWAIT
                REPEAT
.
ValidateData
                GETITEM         txtValue1,0,Length1
                GETITEM         txtValue2,0,Length2
                IF              (Length1 > 0 AND Length2 > 0)
                GETITEM         txtValue1,0,DATA
                MOVE            DATA,Value1
                GETITEM         txtValue2,0,DATA
                MOVE            DATA,Value2
                SETFLAG         NOT ZERO
                ELSE
                ALERT           CAUTION,"You must enter two values.":
                                Result,"Error"
                SETFLAG         ZERO
                ENDIF
                RETURN
