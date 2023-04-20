*---------------------------------------------------------------
.
. Program Name: Lab16.pls
. Description:  Introduction to PL/B Lab 16 program
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
*
.Work Variables
.
INDEX           FORM            2
REPLY           DIM             1
*........................................................
.
.Begin Execution
.
                TRAP            QUIT IF ESCAPE
.
START
                DISPLAY         *BGCOLOR=*BLUE,*FGCOLOR=*WHITE:
                                *ES,*P27:2,"Customer Data":
                                *P15:3,*ULCSD,*RPTCHAR=*HLN:50,*URCSD:
                                *P15:4,*VLN,*H 66,*VLN:
                                *P15:5,*VLN,*H 66,*VLN:
                                *P15:6,*VLN,*H 66,*VLN:
                                *P15:7,*VLN,*H 66,*VLN:
                                *P15:8,*VLN,*H 66,*VLN:
                                *P15:9,*VLN,*H 66,*VLN:
                                *P15:10,*VLN,*H 66,*VLN:
                                *P15:11,*VLN,*H 66,*VLN:
                                *P15:12,*VLN,*H 66,*VLN:
                                *P15:13,*LLCSD,*RPTCHAR=*HLN:50,*LRCSD:
                                *P20:5," Number:":
                                *P20:6,"   Name:":
                                *P20:7,"Address:":
                                *P20:8,"   City:":
                                *P20:9,"  State:":
                                *P20:10,"Zipcode:":
                                *P20:11,"Balance:"
*
.Get the customer number
.
GETNUMBER
                KEYIN           *IT,*P29:5,*RPTCHAR="_":7,*H 29,NUMBER;
                GOTO            GETBALANCE IF F5
                COMPARE         "0",NUMBER
                GOTO            GETNAME IF ZERO
                DISPLAY         *H 29,NUMBER;
*
.Get the customer name
.
GETNAME
                KEYIN           *IT,*P29:6,*RPTCHAR="_":30,*H 29,NAME;
                GOTO            GETNUMBER IF F5
                COUNT           INDEX,NAME
                GOTO            GETNAME IF ZERO
                DISPLAY         *H 29,NAME;
*
.Get the customer address
.
GETADDR
                KEYIN           *P29:7,*RPTCHAR="_":30,*H 29,ADDRESS;
                GOTO            GETNAME IF F5
                COUNT           INDEX,ADDRESS
                GOTO            GETADDR IF ZERO
                DISPLAY         *H 29,ADDRESS;
*
.Get the customer city
.
GETCITY
                KEYIN           *P29:8,*RPTCHAR="_":20,*H 29,CITY;
                GOTO            GETADDR IF F5
                COUNT           INDEX,CITY
                GOTO            GETCITY IF ZERO
                DISPLAY         *H 29,CITY;
*
.Get the customer state
.
GETSTATE
                KEYIN           *IN,*P29:9,*RPTCHAR="_":2,*H 29,STATE;
                GOTO            GETCITY IF F5
                COUNT           INDEX,STATE
                GOTO            GETCITY IF ZERO
                DISPLAY         *H 29,STATE;
*
.Get the zip code
.
GETZIP
                KEYIN           *DE,*P29:10,*RPTCHAR="_":5,*H 29,ZIP;
                GOTO            GETSTATE IF F5
                COUNT           INDEX,ZIP
                GOTO            GETZIP IF ZERO
                DISPLAY         *H 29,ZIP;
*
.Get the balance
.
GETBALANCE
                KEYIN           *DE,*P29:11,"_______.__",*H 29,BALANCE;
                GOTO            GETNUMBER IF F5
                DISPLAY         *H 29,BALANCE; 
*
.Display the entry
.
                DISPLAY         *P30:15,NUMBER,*P30:16,NAME:
                                *P30:17,Address,*P30:18,CITY,",",STATE," ",ZIP:
                                *P30:19,BALANCE
                KEYIN           *HD,"Continue ... ",REPLY,*P30:15,*EF
                GOTO            START
*
.Terminate the program
.
QUIT
                STOP
