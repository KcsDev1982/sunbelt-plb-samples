*---------------------------------------------------------------
.
. Program Name: Lab10.pls
. Description:  Introduction to PL/B Lab 10 program
.           
.
ACCOUNT         DIM             *4
NAME            DIM             *20
ADDRESS         DIM             *35
CITY            DIM             *20
STATE           DIM             *2
ZIP             FORM            *5
BALANCE         FORM            *4.2
.
REPLY           DIM             1
*
.Display the form
.
                DISPLAY         *P10:14,"*** Data Received ***":
                                *P10:15,"Account: ",ACCOUNT:
                                *P10:16,"   Name: ",NAME:
                                *P10:17,"Address: ",ADDRESS:
                                *P10:18,"   City: ",CITY:
                                *P10:19,"  State: ",STATE:
                                *P10:20,"    Zip: ",ZIP:
                                *P10:21,"Balance: ",BALANCE
                KEYIN           *HD,"Continue. ",REPLY
                STOP
