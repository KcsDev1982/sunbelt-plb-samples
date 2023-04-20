*---------------------------------------------------------------
.
. Program Name: Lab08.pls
. Description:  Introduction to PL/B Lab 8 program
.
REPLY           DIM             1
*
.Get a command
.
                LOOP
. 
                KEYIN           *HD,*N,"A. Add a record":
                                *N,"C. Change a record":
                                *N,"D. Delete a record":
                                *N,"F. Find a record":
                                *N,"L. List all records":
                                *N,"Q. Quit":
                                *N,*N,"Enter your choice: ",REPLY
.
                SWITCH          REPLY
                CASE            "A"
                CALL            ADD
                CASE            "C"
                CALL            CHANGE
                CASE            "D"
                CALL            DELETE
                CASE            "F"
                CALL            FIND
                CASE            "L"
                CALL            LIST
                CASE            "Q"
                STOP
                DEFAULT
                DISPLAY         *B,*N,"Invalid choice - try again"
                ENDSWITCH
 
                REPEAT
*
.Add routine
.
ADD
                DISPLAY         *N,"Add called"
                RETURN
*
.Change routine
.
CHANGE
                DISPLAY         *N,"Change called"
                RETURN
*
.Delete routine
.
DELETE
                DISPLAY         *N,"Delete called"
                RETURN
*
.Find routine
.
FIND
                DISPLAY         *N,"Find called"
                RETURN
*
.List routine
.
LIST
                DISPLAY         *N,"List called"
                RETURN
