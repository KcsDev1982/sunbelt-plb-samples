*---------------------------------------------------------------
.
. Program Name: Lab17.pls
. Description:  Introduction to PL/B Lab 17 program
.           
.
*
.Customer Record
.
NUMBER          FORM            7
NAME            DIM             30
ADDRESS         DIM             30
CITY            DIM             20
STATE           DIM             2
ZIP             DIM             5
BALANCE         FORM            7.2
.
CFILE           FILE
SEQ             FORM            "-1"
COUNT           FORM            7
REPLY           DIM             1
*.................................
.
.Create the customer file
.
                TRAP            NOPREP IF IO
                PREP            CFILE,"CUSTDATA",EXCLUSIVE
                TRAPCLR         IO
.
                DISPLAY         *HD,"Generating the data"
*
.Generate the records
.
                FOR             COUNT,"1","100000"
.
                MOVE            COUNT,NUMBER
                PACK            NAME WITH "Customer ",NUMBER
                SQUEEZE         NAME,NAME
                PACK            ADDRESS WITH "Address ",NUMBER
                SQUEEZE         ADDRESS,ADDRESS
                PACK            CITY WITH "City ",NUMBER
                SQUEEZE         CITY,CITY
                MOVE            "TX",STATE
                MOVE            NUMBER,ZIP
                MOVE            NUMBER,BALANCE
.
                WRITE           CFILE,SEQ;NUMBER,NAME,ADDRESS,CITY,STATE,ZIP,BALANCE
.
                REPEAT
*
.Close the file and exit
.
                CLOSE           CFILE
                KEYIN           *HD,"Complete. ",REPLY
                STOP
*
.Unable to create the file
.
NOPREP
                KEYIN           *B,*HD,"Unable to create custdata.txt. ",REPLY
                STOP
