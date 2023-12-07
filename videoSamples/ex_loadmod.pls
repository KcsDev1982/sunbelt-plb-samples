*---------------------------------------------------------------
.
. Program Name: ex_loadmod
. Description:  LOADMOD example program
.
. Revision History:
.
.   18 May 21   W Keech
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc	
*---------------------------------------------------------------

*................................................................
.
. Code start
.
                CALL            Main
		STOP
				
*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
Num1		FORM		10
		LOADMOD		"ex_module"
		CALLS		"ex_module;RandNum" Giving Num1
		Display 	Num1
		CALLS		"ex_module;RandNum" Giving Num1 Using "6"
		Display 	Num1
		CALLS		"ex_module;RandNum" Giving Num1
		Display 	Num1
		CALLS		"ex_module;RandNum" Giving Num1
		Display 	Num1
		CALLS		"ex_module;RandNum" Giving Num1
		Display 	Num1
		Keyin		Num1
                FUNCTIONEND
