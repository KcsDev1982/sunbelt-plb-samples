*---------------------------------------------------------------
.
. Program Name: Lab05.pls
. Description:  Introduction to PL/B Lab 5 program
.           
.
CHOICE          FORM            1
*
.Catch chaining errors
.
START
                TRAP            CHAINERR IF CFAIL
*
.Show the menu
. 
                KEYIN           *ES,*P1:1,"System Menu":
                                *P5:3,"1. Lab 1":
                                *P5:4,"2. Lab 2":
                                *P5:5,"3. Lab 3":
                                *P5:6,"4. Lab 4":
                                *P5:7,"5. End":
                                *P1:9,"Enter your selection: ",CHOICE
*
.Branch to selected program
.
                DISPLAY         *ES
                BRANCH          CHOICE TO LAB1,LAB2,LAB3,LAB4,QUIT
                KEYIN           *B,*HD,"Invalid selection.",CHOICE
                GOTO            START
*
.Execute Lab 1
.
LAB1
                CHAIN           "LAB01"
*
.Execute Lab 2
.
LAB2
                CHAIN           "LAB02"
*
.Execute Lab 3
.
LAB3
                CHAIN           "LAB03"
*
.Execute Lab 4
.
LAB4
                CHAIN           "LAB04"
*
.Terminate the program
.
QUIT
                STOP
*
.Chain error
.
CHAINERR
                KEYIN           *B,*HD,"Error chaining to selected program. ",CHOICE
                STOP
