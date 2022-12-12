
*---------------------------------------------------------------
.
. Program Name: appdlg
. Description:  PlbWeCli Application Dialog Sample 
.
. Revision History:
.
. 17-04-07 whk
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*---------------------------------------------------------------        

WebForm         PLFORM          appdlgf.pwf
.
FullData        DIM             200
.
Result          FORM            5
.
Bnum            FORM            5
.
Client          CLIENT

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
. TestClick - Handle a request to perform a test
.
TestClick       LFUNCTION
                ENTRY
                EVENTINFO       0,result=Result
                SWITCH          Result
                CASE            1
                CALL            TestPrompt
                CASE            2
                CALL            TestConfirm
                CASE            3
                CALL            TestAlert
                ENDSWITCH
                FUNCTIONEND
*................................................................
.
. TestPrompt
.
TestPrompt      LFUNCTION
                ENTRY
                Client.AppDialog Using "What color should it be:", "Cars", "Color It","Data goes here"
                FUNCTIONEND

*................................................................
.
. TestConfirm
.
TestConfirm     LFUNCTION
                ENTRY
                Client.AppDialog Using "How much should be added ?", "Numbers", "One;Two"
                FUNCTIONEND

*................................................................
.
. TestAlert
.
TestAlert       LFUNCTION
                ENTRY
                Client.AppDialog Using "Press to complete !", "Dialog Test", "You bet"
                FUNCTIONEND

*................................................................
.
. DialogEvent - AppEventDialog
.
DialogEvent     LFUNCTION
                ENTRY
                SETPROP         EditText1,*Text=FullData
                PACK            FullData with "Button Number: ", Bnum
                SETPROP         EditText2,*Text=FullData
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
. Register and Startup the events, load the main form
.
Main            LFUNCTION
                ENTRY
                WINHIDE
                FORMLOAD        WebForm
.
                EVENTREG        Client,AppEventDialog,DialogEvent,Modifier=Bnum,ARG1=FullData
                FUNCTIONEND
