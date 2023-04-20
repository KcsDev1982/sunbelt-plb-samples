*---------------------------------------------------------------
.
. Program Name: Lab02_3.pls
. Description:  Introduction to PL/B Lab 2 Step 3 program
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
Start
                KEYIN           *ES,*IT,*P=10:5,*DE,"Account: ",*DVRV=ACCOUNT:
                                *P=10:6,"   Name: ",*DVRV=NAME:
                                *P=10:7,"Address: ",*DVRV=ADDRESS:
                                *P=10:8,"   City: ",*DVRV=CITY:
                                *P=10:9,"  State: ",*DVRV=STATE:
                                *P=10:10,"Zipcode: ",*DVRV=ZIP:
                                *P=10:11,"Balance: ",*DVRV=BALANCE
.
ANS             DIM             1
                KEYIN           *P=1:24,*EL,"Another Entry?  ",ANS
                CMATCH          "Y",ANS
                GOTO            START IF EQUAL
                STOP
