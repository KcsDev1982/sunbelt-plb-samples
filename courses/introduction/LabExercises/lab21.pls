*---------------------------------------------------------------
.
. Program Name: Lab21.pls
. Description:  Introduction to PL/B Lab 21 program
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
KEY             DIM             7
KEY2            DIM             37
AKEY1           DIM             10
AKEY2           DIM             33
.
CFILE           IFILE
CFILE2          IFILE
CFILEA          AFILE
*
.Work Variables
.
INDEX           FORM            2
REPLY           DIM             1
ZERO            FORM            "0"
SEQ             FORM            "-1"
EOF             FORM            "-3"
*........................................................
.
.Begin Execution
.
                TRAP            QUIT IF ESCAPE
*
.Open the file
.
                TRAP            NOFILE IF IO
                OPEN            CFILE,"CUSTDATA"
                OPEN            CFILE2,"CUSTDATA"
                OPEN            CFILEA,"CUSTDATA"
                TRAPCLR         IO
.
START
                DISPLAY         *BGCOLOR=*BLUE,*FGCOLOR=*WHITE:
                                *ES,*P32:2,"Customer Data":
                                *P5:3,*ULCSD,*RPTCHAR=*HLN:70,*URCSD:
                                *P5:4,*VLN,*H 76,*VLN:
                                *P5:5,*VLN,*H 76,*VLN:
                                *P5:6,*VLN,*H 76,*VLN:
                                *P5:7,*VLN,*H 76,*VLN:
                                *P5:8,*VLN,*H 76,*VLN:
                                *P5:9,*VLN,*H 76,*VLN:
                                *P5:10,*VLN,*H 76,*VLN:
                                *P5:11,*VLN,*H 76,*VLN:
                                *P5:12,*VLN,*H 76,*VLN:
                                *P5:13,*VLN,*H 76,*VLN:
                                *P5:14,*VLN,*H 76,*VLN:
                                *P5:15,*LLCSD,*RPTCHAR=*HLN:70,*LRCSD:
                                *P10:5," Number:":
                                *P10:6,"   Name:":
                                *P10:7,"Address:":
                                *P10:8,"   City:":
                                *P10:9,"  State:":
                                *P10:10,"Zipcode:":
                                *P10:11,"Balance:"
                GOTO            NEXT
*......................................................
.
.Get a command
.
GETCMD
                KEYIN           *SETSWLR=6:74,*P2:13,*EL,*RESETSW,*P7:13:
                                "(A)dd, (F)ind, (L)ist, (D)elete, (N)ext, (P)revious, or (Q)uit: ":
                                *+,REPLY;
*
.Branch to the correct function
.
                REPLACE         "A1F2L3D4N5P6Q7",REPLY
                MOVE            REPLY,INDEX
                BRANCH          INDEX TO ADD,FIND,LIST,DELETE,NEXT,PREVIOUS,QUIT
                GOTO            GETCMD
*........................................................
.Add Routine
.
ADD
*
.Get the customer number
.
GETNUMBER
                KEYIN           *IT,*P19:5,*RPTCHAR="_":7,*H 19,NUMBER;
                GOTO            GETBALANCE IF F5
                COMPARE         "0",NUMBER
                GOTO            GETNAME IF ZERO
                DISPLAY         *H 19,NUMBER;
*
.Get the customer name
.
GETNAME
                KEYIN           *IT,*P19:6,*RPTCHAR="_":30,*H 19,NAME;
                GOTO            GETNUMBER IF F5
                COUNT           INDEX,NAME
                GOTO            GETNAME IF ZERO
                DISPLAY         *H 19,NAME;
*
.Get the customer address
.
GETADDR
                KEYIN           *P19:7,*RPTCHAR="_":30,*H 19,ADDRESS;
                GOTO            GETNAME IF F5
                COUNT           INDEX,ADDRESS
                GOTO            GETADDR IF ZERO
                DISPLAY         *H 19,ADDRESS;
*
.Get the customer city
.
GETCITY
                KEYIN           *P19:8,*RPTCHAR="_":20,*H 19,CITY;
                GOTO            GETADDR IF F5
                COUNT           INDEX,CITY
                GOTO            GETCITY IF ZERO
                DISPLAY         *H 19,CITY;
*
.Get the customer state
.
GETSTATE
                KEYIN           *IN,*P19:9,*RPTCHAR="_":2,*H 19,STATE;
                GOTO            GETCITY IF F5
                COUNT           INDEX,STATE
                GOTO            GETCITY IF ZERO
                DISPLAY         *H 19,STATE;
*
.Get the zip code
.
GETZIP
                KEYIN           *DE,*P19:10,*RPTCHAR="_":5,*H 19,ZIP;
                GOTO            GETSTATE IF F5
                COUNT           INDEX,ZIP
                GOTO            GETZIP IF ZERO
                DISPLAY         *H 19,ZIP;
*
.Get the balance
.
GETBALANCE
                KEYIN           *DE,*P19:11,"_______.__",*H 19,BALANCE;
                GOTO            GETNUMBER IF F5
                DISPLAY         *H 19,BALANCE; 
*
.Write the entry to the end of file
.
                WRITE           CFILE;NUMBER,NAME,ADDRESS,CITY,STATE,ZIP,BALANCE
                INSERT          CFILE2
                KEYIN           *HD,"Record added ... ",REPLY
                GOTO            START
*......................................................
.Find requested
.
FIND
                KEYIN           *B,*SETSWLR=6:74,*P2:13,*EL,*RESETSW,*P7:13:
                                "Number: ",NUMBER,"  Name: ",NAME
                COUNT           INDEX,NAME
                GOTO            GETCMD IF (NUMBER = 0 AND INDEX = 0)
*
.Build the number key
.
                COUNT           INDEX,NUMBER
                IF              NOT ZERO
                PACK            AKEY1 WITH "01X",NUMBER
                ELSE
                CLEAR           AKEY1
                ENDIF
*
.Build the name key
.
                COUNT           INDEX,NAME
                IF              NOT ZERO
                PACK            AKEY2 WITH "02F",NAME
                ELSE
                CLEAR           AKEY2
                ENDIF
*
.Do the initial read
.
                READ            CFILEA,AKEY1,AKEY2;NUMBER,NAME,ADDRESS,CITY,STATE,ZIP,BALANCE
*
.Catch no matches
.
                IF              OVER
                KEYIN           *B,*SETSWLR=6:74,*P2:13,*EL,*RESETSW,*P7:13:
                                "*** No matching records found. ",REPLY
                ELSE
                CALL            DISPLAY
                PACK            KEY2 WITH NAME,NUMBER
                READ            CFILE2,KEY2;NUMBER
                ENDIF
*
.Get another command
. 
                GOTO            GETCMD
*......................................................
.Delete requested
.
DELETE
*
.Position and delete from the AAM file
.
                PACK            AKEY1 with "01X",NUMBER
                READ            CFILEA,AKEY1;;
                IF              OVER
                KEYIN           *B,*SETSWLR=6:74,*P2:13,*EL,*RESETSW,*P7:13:
                                "*** Delete failed *** ",REPLY
                GOTO            GETCMD
                ENDIF
                DELETE          CFILEA
*
.Delete the key from the first index
. 
                MOVE            NUMBER,KEY
                DELETEK         CFILE,KEY
*
.Delete the key from the second index
.
                PACK            KEY2 WITH NAME,NUMBER
                DELETEK         CFILE2,KEY2
*
.Deletion complete
.
                KEYIN           *SETSWLR=6:74,*P2:13,*EL,*RESETSW,*P7:13:
                                "Record deleted. ",REPLY
*
.Move to the next or previous record
.
                READKS          CFILE2;NUMBER,NAME,ADDRESS,CITY,STATE,ZIP,BALANCE
                IF              OVER
                READKP          CFILE2;NUMBER,NAME,ADDRESS,CITY,STATE,ZIP,BALANCE
                ENDIF
                CALL            DISPLAY 
. 
                GOTO            GETCMD
*......................................................
.Next record requested
.
NEXT
                READKS          CFILE2;NUMBER,NAME,ADDRESS,CITY,STATE,ZIP,BALANCE
                IF              OVER
                KEYIN           *B,*SETSWLR=6:74,*P2:13,*EL,*RESETSW,*P7:13:
                                "No more records. ",REPLY
                READKP          CFILE2;NUMBER,NAME,ADDRESS,CITY,STATE,ZIP,BALANCE
                ENDIF
.
                CALL            DISPLAY
                GOTO            GETCMD
*......................................................
.Previous record requested
.
PREVIOUS
                READKP          CFILE2;NUMBER,NAME,ADDRESS,CITY,STATE,ZIP,BALANCE
                IF              OVER
                KEYIN           *B,*SETSWLR=6:74,*P2:13,*EL,*RESETSW,*P7:13:
                                "No previous records. ",REPLY
                READKS          CFILE2;NUMBER,NAME,ADDRESS,CITY,STATE,ZIP,BALANCE
                ENDIF
.
                CALL            DISPLAY
                GOTO            GETCMD
*......................................................
.List requested
.
LIST
                MOVE            "  ",NAME
                READ            CFILE2,NAME;;
                DISPLAY         *HD
*
.Display the file contents
.
                LOOP
                READKS          CFILE2;NUMBER,NAME,ADDRESS,CITY,STATE,ZIP,BALANCE
                UNTIL           OVER
                DISPLAY         NUMBER,":",NAME,":",BALANCE
                REPEAT
.
                KEYIN           *N,"Continue...",NAME
                GOTO            START
*.....................................................
.Terminate the program
.
QUIT
                CLOSE           CFILE
                CLOSE           CFILE2
                CLOSE           CFILEA
                STOP
*........................................................
.Display a customer record
.
DISPLAY
                DISPLAY         *P19:5,NUMBER,*P19:6,NAME,*P19:7,ADDRESS,*P19:8,CITY:
                                *P19:9,STATE,*P19:10,ZIP,*P19:11,BALANCE
                RETURN
*........................................................
.Data file not found
.
NOFILE
                KEYIN           *B,*HD,"Customer files not found. ",REPLY
                STOP
