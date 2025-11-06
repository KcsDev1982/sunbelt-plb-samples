*==========================================================
.  CUSTOMER FILE WRITE/READ EXAMPLE – SEQUENTIAL FILE
*==========================================================

CUSTFILE   FILE                            // Customer data file

Seq        FORM        "-1"                // Sequential access indicator

CUSTREC    RECORD                          // Customer record layout
CUSTNO     DIM         5                   // Customer number
CUSTNAME   DIM         30                  // Customer name
CUSTPHONE  DIM         15                  // Customer phone
BALANCE    FORM        7.2                 // Customer balance
           RECORDEND

*----------------------------------------------------------
.  Program entry
*----------------------------------------------------------

*--- Create (or truncate) the customer data file
           ERASE       "CUSTOMER.DAT"
           PREPARE     CUSTFILE,"CUSTOMER.DAT"
           IF          OVER
               DISPLAY *N,"Error preparing CUSTOMER.DAT"
               STOP
           ENDIF

*----------------------------------------------------------
.  Input loop – write customer records sequentially
*----------------------------------------------------------
WRITELOOP  CLEAR       CUSTREC

           KEYIN       *N,"Customer number (blank to finish): ",CUSTREC.CUSTNO
           IF          (CUSTREC.CUSTNO = " ")
               GOTO    DONEWRITE
           ENDIF

           KEYIN       *N,"Customer name  : ",CUSTREC.CUSTNAME
           KEYIN       *N,"Customer phone : ",CUSTREC.CUSTPHONE
           KEYIN       *N,"Balance        : ",CUSTREC.BALANCE

*--- WRITE: file,Seq;record   (Seq = "-1" ? sequential)
           WRITE       CUSTFILE,Seq;CUSTREC

           GOTO        WRITELOOP

DONEWRITE  CLOSE       CUSTFILE

*----------------------------------------------------------
.  Reopen the file and read/display all customer records
*----------------------------------------------------------
*--- OPEN for reading
           OPEN        CUSTFILE,"CUSTOMER.DAT"
           IF          OVER
               DISPLAY *N,"Error opening CUSTOMER.DAT"
               STOP
           ENDIF

*--- Ensure Seq is set for sequential reads
           MOVE        "-1"                TO Seq

           DISPLAY     *N,*N,"Customer list from CUSTOMER.DAT:",*N

READLOOP   READ        CUSTFILE,Seq;CUSTREC
           IF          OVER                // End of file
               GOTO    DONEREAD
           ENDIF

           DISPLAY     *N:
                       "No: ",CUSTREC.CUSTNO,"  ":
                       "Name: ",CUSTREC.CUSTNAME,"  ":
                       "Phone: ",CUSTREC.CUSTPHONE,"  ":
                       "Balance: ",CUSTREC.BALANCE

           GOTO        READLOOP

DONEREAD   CLOSE       CUSTFILE
           DISPLAY     *N,*N,"End of customer list.",*W5
           STOP
