*==========================================================
.  CUSTOMER FILE WRITE/READ – SEQUENTIAL
*==========================================================

CUSTFILE   FILE

Seq        FORM        "-1"                . Sequential access control

CUSTNO     DIM         5                  . Customer number
CUSTNAME   DIM         30                 . Customer name
CUSTPHONE  DIM         15                 . Customer phone
BALANCE    FORM        7.2                . Customer balance

*----------------------------------------------------------
.  Program entry
*----------------------------------------------------------

*--- Create/truncate the file for writing
           PREPARE    CUSTFILE,"CUSTOMER.DAT"
           IF         OVER
           DISPLAY    *N,"Error preparing CUSTOMER.DAT"
           STOP
           ENDIF

*----------------------------------------------------------
.  Input loop – write records to file
*----------------------------------------------------------
WRITELOOP  MOVE       " "                 TO CUSTNO
           MOVE       " "                 TO CUSTNAME
           MOVE       " "                 TO CUSTPHONE
           MOVE       0                   TO BALANCE

           KEYIN      *N,"Customer number (blank to finish): ",CUSTNO
           IF         (CUSTNO = " ")
           GOTO       DONEWRITE
           ENDIF

           KEYIN      *N,"Customer name  : ",CUSTNAME
           KEYIN      *N,"Customer phone : ",CUSTPHONE
           KEYIN      *N,"Balance        : ",BALANCE

*--- WRITE file sequentially: file,Seq;field list
           WRITE      CUSTFILE,Seq;CUSTNO,CUSTNAME,CUSTPHONE,BALANCE

           GOTO       WRITELOOP

DONEWRITE  CLOSE      CUSTFILE

*----------------------------------------------------------
.  Reopen file and read/display all records
*----------------------------------------------------------
           OPEN       CUSTFILE,"CUSTOMER.DAT"
           IF         OVER
           DISPLAY    *N,"Error opening CUSTOMER.DAT"
           STOP
           ENDIF

           MOVE       "-1"                TO Seq

           DISPLAY    *N,*N:
                      "Customer list from CUSTOMER.DAT:"

READLOOP   READ       CUSTFILE,Seq;CUSTNO,CUSTNAME,CUSTPHONE,BALANCE
           IF         OVER
           GOTO       DONEREAD
           ENDIF

           DISPLAY    *N,"No: ",CUSTNO,"  ":
                      "Name: ",CUSTNAME,"  ":
                      "Phone: ",CUSTPHONE,"  ":
                      "Balance: ",BALANCE

           GOTO       READLOOP

DONEREAD   CLOSE      CUSTFILE
           DISPLAY    *N,*N,"End of customer list.",*W5
           STOP
