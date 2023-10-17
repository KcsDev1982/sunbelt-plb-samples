*---------------------------------------------------------------
.
. Program Name: class_sample
. Description:  Sample program to demonstrate PLBOBJECTs
.
. Revision History:
.
.   17 Jul 23   W Keech
.      Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc

*---------------------------------------------------------------
// <program wide variables>

OpenDlg         PLBOBJECT  	CLASS="srvsel_class"
Calculator      PLBOBJECT      	CLASS="webcalc_class"
 
CalcWin         PLFORM          "webcalc"


*................................................................
.
. Code start
.
                CALL            Main
                LOOP
                EVENTWAIT
                REPEAT
                STOP
*................................................................
.
. Select a file name using the OpenDlg PLBOBJECT
.
LoadSelect      LFUNCTION
                ENTRY
FileName        DIM             256
Result          FORM            1

                OpenDlg.GetFileName Giving FileName

                ALERT           NOTE,FileName,Result,"File Name"
 
                FUNCTIONEND

*................................................................
.
. Handle the $CHANGE event from the Calculator PLBOBJECT
.
CalcChange      LFUNCTION
                ENTRY
Result          FORM            10
Message         DIM             20

                EVENTINFO       0,RESULT=Result
               
                PACK            Message From "Value is ",Result	
                ALERT           NOTE,Message,Result,"Calc Result"
                FUNCTIONEND

*................................................................
.
. Get the current result from the Calculator PLBOBJECT
.
CalcResult      LFUNCTION
                ENTRY
BigNum          FORM            10
Message         DIM             20
Result          FORM            1

                GETPROP         Calculator,*Value=BigNum
                PACK            Message From "Value is ",BigNum

                ALERT           NOTE,Message,Result,"Calc Result"
                FUNCTIONEND

*................................................................
.
. Terminaste the program
.
Terminate       LFUNCTION
                ENTRY
                DESTROY         OpenDlg
                DESTROY         Calculator
                STOP
                FUNCTIONEND
*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
.
. Hide the main window and create the main form
.
                WINHIDE
                FORMLOAD        CalcWin
.
. Create the Calculator PLBOBJECT from the webcalc_class.plc module
.
                CREATE          Calculator
.
. Setup the Calculator PLBOBJECT $CHANGE event
.
                EVENTREG        Calculator,$CHANGE,CalcChange
.
. Invoke the Calculator PLBOBJECT CalcBind method
.
                Calculator.CalcBind Using pnlCalc
.
. Create the OpenDlg PLBOBJECT from the srvsel_class.plc module 
.
                CREATE          OpenDlg

                FUNCTIONEND
