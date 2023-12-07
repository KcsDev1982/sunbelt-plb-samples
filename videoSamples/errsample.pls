*---------------------------------------------------------------
.
. Program Name: errsample
. Description:  sample program that causes an error
.
. Revision History:
.
. 28 Sep 21   W Keech
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc	
*---------------------------------------------------------------

MyFile		FILE
Seq		FORM		"-1"
Data		DIM		250
Prep		FORM		"0"

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
                IF		(Prep)
                PREPARE		MyFile,"test1.txt"
                ENDIF
                READ		MyFile,Seq;Data
                FUNCTIONEND
