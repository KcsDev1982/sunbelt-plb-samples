*---------------------------------------------------------------
.
. Program Name: ex_module
. Description:  Module for LOADMOD example program
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

Result		FORM		5

*................................................................
.
. Code start
.
		WINHIDE		
                ALERT		STOP,"This program can't be run in a stand-alone mode.", Result		
		STOP
				
*................................................................
.
. RandNum - Random number from 1-Max
.				
RandNum       	FUNCTION
Max		FORM		"0000000100"
                ENTRY
Num		INTEGER		4
Cpu		INTEGER		4
PauseTime	FORM		".010"

		PAUSE		PauseTime
		CLOCK		SECONDS	to Num
		CLOCK		CPUTIME to Cpu
		CALC		Num=( (Num*Cpu) - ( ( (Num*Cpu) / Max ) * Max ) + 1 )
		
                FUNCTIONEND	using Num
