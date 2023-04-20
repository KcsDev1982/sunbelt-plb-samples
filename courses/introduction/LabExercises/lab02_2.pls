*---------------------------------------------------------------
.
. Program Name: Lab02_2.pls
. Description:  Introduction to PL/B Lab 2 Step 2 program
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
                KEYIN           *ES,*P=10:5,"Account: ",ACCOUNT:
                                *P=10:6,"   Name: ",NAME:
                                *P=10:7,"Address: ",ADDRESS:
                                *P=10:8,"   City: ",CITY:
                                *P=10:9,"  State: ",STATE:
                                *P=10:10,"Zipcode: ",ZIP:
                                *P=10:11,"Balance: ",BALANCE
.
ANS             DIM             1
                KEYIN           *P=1:24,*EL,"Another Entry?  ",ANS
                CMATCH          "Y",ANS
                GOTO            START IF EQUAL
                STOP
