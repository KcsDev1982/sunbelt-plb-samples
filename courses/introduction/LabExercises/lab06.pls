*---------------------------------------------------------------
.
. Program Name: Lab06.pls
. Description:  Introduction to PL/B Lab 6 program
.           
.
REPLY           DIM             1
CHOICE          DIM             1
.
                CALL            PROMPT
                KEYIN           *HD,*R,"The reply was: ",*DV,CHOICE,"  ",REPLY
                STOP
.
PROMPT
                LOOP
                KEYIN           *HD,*N:
                                *N,"A. Add record":
                                *N,"D. Delete record":
                                *N,"C. Change record":
                                *N,"F. Find a record":
                                *N,"L. List all records":
                                *N,*N,"Enter your selection: ",CHOICE
                REPEAT          UNTIL (CHOICE = "A" OR CHOICE = "D" OR: 
                                CHOICE = "C" OR CHOICE="F" OR CHOICE = "L")
.         
                RETURN
 
