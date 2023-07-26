                INCLUDE         PLBEQU.INC
                INCLUDE         PLBMETH.INC
                INCLUDE         RESIZE.PLS
                INCLUDE         CUSTOMER.INC
                INCLUDE         ORDER.INC
                INCLUDE         DETAIL.INC
*
.Utility Variables
.
RESULT          INTEGER         4
YESNO           INTEGER         1,"0x24"
ADDING          INTEGER         1
SEARCHING       INTEGER         1
MSG             DIM             55
NWORK10         FORM            10
DIM10           DIM             10
VALUE           INTEGER         4
SQTY            DIM             10
SPRICE          DIM             10
FORM72          FORM            7.2
TOP             FORM            4
LEFT            FORM            4
ITEM            INTEGER         4
FIELDNO         FORM            2
.
CUSTOMER        PLFORM          CUSTOMER.PLF
DETAIL          PLFORM          DETAIL.PLF
ORDER           PLFORM          ORDER.PLF
ABOUT           PLFORM          ABOUT.PLF
MAIN            PLFORM          MAIN.PLF
.
		WINHIDE
                FORMLOAD        CUSTOMER
                FORMLOAD        ORDER
                FORMLOAD        DETAIL
                FORMLOAD        MAIN
.
                LOOP
                EVENTWAIT
                REPEAT
.
                INCLUDE         CUSTOMER.PLS
                INCLUDE         ORDER.PLS
                INCLUDE         DETAIL.PLS
                INCLUDE         REPORT.PLS
 
