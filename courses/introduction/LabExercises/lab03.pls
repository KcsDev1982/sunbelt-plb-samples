*---------------------------------------------------------------
.
. Program Name: Lab03.pls
. Description:  Introduction to PL/B Lab 3 program
.           
.
ACCOUNT         DIM             4
NAME            DIM             20
ADDRESS         DIM             35
CITY            DIM             20
STATE           DIM             2
ZIP             FORM            5
BALANCE         FORM            4.2
.
                TRAP            QUIT IF ESCAPE
                TRAP            LAB10 IF F1
*
.Display the form
.
                DISPLAY         *ES,*P10:5,"Account:":
                                *P10:6,"   Name:":
                                *P10:7,"Address:":
                                *P10:8,"   City:":
                                *P10:9,"  State:":
                                *P10:10,"    Zip:":
                                *P10:11,"Balance:"
*
.Get the Account Number
.
Start
                KEYIN           *IT,*P=19:5,*DE,*DVRV=ACCOUNT
                GOTO            GETBAL IF UP
*
.Get the Name
.
GETNAME
                KEYIN           *P=19:6,*DVRV=NAME
                GOTO            START IF UP
*
.Get the Address
.
GETADDR
                KEYIN           *P=19:7,*DVRV=ADDRESS
                GOTO            GETNAME IF UP
*
.Get the City
.
GETCITY
                KEYIN           *P=19:8,*DVRV=CITY
                GOTO            GETADDR IF UP
*
.Get the State
.
GETSTATE
                KEYIN           *P=19:9,*DVRV=STATE
                GOTO            GETCITY IF UP
*
.Get the Zipcode
.
GETZIP
                KEYIN           *P=19:10,*DVRV=ZIP
                GOTO            GETSTATE IF UP
*
.Get the Balance
.
GETBAL
                KEYIN           *P=19:11,*DVRV=BALANCE
                GOTO            GETZIP IF UP
.
ANS             DIM             1
                KEYIN           *IN,*P=1:24,*EL,"Another Entry?  ",ANS
                GOTO            GETBAL IF UP
                CMATCH          "Y",ANS
                GOTO            START IF EQUAL
.
QUIT
                STOP
 
                IF              Zero
                ENDIF
*
.Chain to Exercise 1
.
LAB10
                DISPLAY         *ES
                TRAP            CHAINERR IF CFAIL
                CHAIN           "LAB01"
                STOP
*
.Lab 1 not found
.
CHAINERR
                KEYIN           *B,*HD,"Lab 1 program not found.",ANS
                STOP
