*
. CREATECSV.PLS - Create a Customer CSV File
.-------------------------------------------------------------
. This program collects customer Name, ID, and Address
. information and writes it to a CSV file.
.-------------------------------------------------------------

*-----------------------------*
*  Data Definitions           *
*-----------------------------*
CUSTFILE     FILE
NAME         DIM         30
CUSTID       DIM         10
ADDRESS      DIM         50
LINEOUT      DIM         100
SEQ          FORM        "-1"

*-----------------------------*
*  Main Program Logic         *
*-----------------------------*

MAIN
              PREPARE    CUSTFILE,"CUSTOMERS.CSV"

NEXTREC
              KEYIN      *ES,*P=10:05,"Enter Customer Name (blank to end): ",NAME
              IF         (NAME = "")
              GOTO       DONE
              ENDIF

              KEYIN      *P=10:07,"Enter Customer ID: ",CUSTID
              KEYIN      *P=10:09,"Enter Customer Address: ",ADDRESS

*  Build CSV line: "Name,ID,Address"
              CLEAR      LINEOUT
              APPEND     NAME TO LINEOUT
              APPEND     "," TO LINEOUT
              APPEND     CUSTID TO LINEOUT
              APPEND     "," TO LINEOUT
              APPEND     ADDRESS TO LINEOUT

*  Write to file
              WRITE      CUSTFILE,SEQ;LINEOUT

*  Confirm entry
              DISPLAY    *N,"Record added: ",LINEOUT

              GOTO       NEXTREC

DONE
              CLOSE      CUSTFILE
              DISPLAY    *N,"Customer file 'CUSTOMERS.CSV' created successfully.",*W2
              STOP
