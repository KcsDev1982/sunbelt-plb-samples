*---------------------------------------------------------------
.
. Program Name: jsonarray
. Description:  Sample program to create a json array
.
. Revision History:
.
. 21-09-07 W Keech
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc

*---------------------------------------------------------------
xData           XDATA
.
JsonOptToDisk	FORM		"6" // JSON_SAVE_USE_INDENT+JSON_SAVE_USE_EOR
OutData         DIM             1000

*................................................................
.
. Code start
.
                CALL            Main
                STOP

*................................................................
.
. GenJson - Create a json file with an array of data
.
GenJson         LFUNCTION
                ENTRY
result          FORM            5
                xData.CreateElement giving result:
                                using *POSITION=CREATE_AS_FIRST_CHILD:
                                *LABEL="employees":
                                *JSONTYPE=JSON_TYPE_ARRAY:
                                *OPTIONS=MOVE_TO_CREATED_NODE

		xData.CreateText giving result:
                                using *POSITION=CREATE_AS_LAST_CHILD:
				*TEXT="Sam"
		xData.CreateText giving result:
                                using *POSITION=CREATE_AS_LAST_CHILD:
				*TEXT="Tom"
		xData.CreateText giving result:
                                using *POSITION=CREATE_AS_LAST_CHILD:
				*TEXT="Al"
	
         
		xData.StoreJson Giving OutData
                DISPLAY         *WRAPON, *LL, OutData
                KEYIN           "Done:", OutData
 				
                FUNCTIONEND
*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
		WINSHOW
                CALL            GenJson 
                FUNCTIONEND

.

.


