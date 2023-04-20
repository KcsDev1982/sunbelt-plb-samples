*---------------------------------------------------------------
.
. Program Name: Lab02.pls
. Description:  Introduction to PL/B Lab 2 program
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
ANS             DIM             1
.
                TRAP            Quit IF ESC
                TRAP            Lab1 IF F1
.
START
                KEYIN           *IT,*P=10:5,"Account: ",*DE,*DVRV=ACCOUNT
.
GETNAME
                KEYIN           *P=10:6,"   Name: ",*DVRV=NAME
                GOTO            START IF UP
.
GETADDRESS
                KEYIN           *P=10:7,"Address: ",*DVRV=ADDRESS
                GOTO            GETNAME IF UP
.
GETCITY
                KEYIN           *P=10:8,"   City: ",*DVRV=CITY
                GOTO            GETADDRESS IF UP
.
GETSTATE
                KEYIN           *P=10:9,"  State: ",*DVRV=STATE
                GOTO            GETCITY IF UP
.
GETZIP
                KEYIN           *P=10:10,"Zipcode: ",*DVRV=ZIP
                GOTO            GETSTATE IF UP
.
GETBALANCE
                KEYIN           *P=10:11,"Balance: ",*DVRV=BALANCE
                GOTO            GETZIP IF UP
.  
                KEYIN           *IN,*P=1:24,*EL,"Another Entry?  ",ANS
                GOTO            GETBALANCE IF UP
                CMATCH          "Y",ANS
                GOTO            Start IF EQUAL 
                STOP
*
.Chain to Lab01
.      
Lab1
                TRAP            CHAINERR IF CFAIL
                CHAIN           "LAB01"
                STOP
.
CHAINERR
                KEYIN           *HD,"Error chaining to Lab01. ",ANS
.
QUIT
                STOP
