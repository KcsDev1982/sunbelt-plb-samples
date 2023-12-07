*---------------------------------------------------------------
.
. Program Name: funcexample
. Description:  Exmaples of various functions
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*................................................................
.
. Code start
.
                CALL            Main
                STOP

Example1	LFUNCTION
Param1		INIT		"Sam   "
Param2		FORM		"000005"
		ENTRY
Ans		DIM		1

		DISPLAY		"Param1: ",Param1,"   Param2: ",Param2;
		Keyin 		Ans
		FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
MyNum		FORM		"100"

                WINSHOW
		CALL		Example1 Using "Ted",MyNum
		CALL		Example1
                FUNCTIONEND
