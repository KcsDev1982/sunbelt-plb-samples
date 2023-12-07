*---------------------------------------------------------------
.
. Program Name: <name>
. Description:  <description>
.
. Revision History:
.
. <date> <programmer>
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc	
*---------------------------------------------------------------
// <program wide variables>
*................................................................
.
. Code start
.
                CALL            Main
		LOOP
		EVENTWAIT
		REPEAT
		STOP
//<various other functions and includes>
*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
		STOP
                FUNCTIONEND
