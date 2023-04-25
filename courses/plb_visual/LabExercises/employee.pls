*---------------------------------------------------------------
.
. Program Name: employee.pls
. Description:  Visual PL/B Programming program
.  
NAME            DIM             50
ADDRESS         DIM             50
CITY            DIM             50
STATE           DIM             2
ZIPCODE         DIM             5
DOB             DIM             8
STATUS          DIM             10
.
RESULT          FORM            5
LENGTH          FORM            5
.
MAIN            PLFORM          employee.plf

.
                WINHIDE
                FORMLOAD        MAIN
                LOOP
                EVENTWAIT
                REPEAT
