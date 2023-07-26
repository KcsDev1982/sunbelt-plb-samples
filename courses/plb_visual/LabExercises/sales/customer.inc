*
.Customer File
.
CUSTNUM         FORM            10 
CONAME          DIM             40  
ADDRESS         DIM             40  
CITY            DIM             30  
STATE           DIM             2
ZIPCODE         DIM             5
CONTACTFN       DIM             20
CONTACTLN       DIM             20
.
CUSTDATA        VARLIST         CUSTNUM,CONAME,ADDRESS,CITY:
                                STATE,ZIPCODE,CONTACTFN,CONTACTLN
.
CUSTFCNT        CONST           "8"  
CUSTKEY         DIM             10
CUSTKEYA        DIM             43(CUSTFCNT)
CUSTSRCH        DIM             1(CUSTFCNT),("X"),("F"),("F"),("F"),("X"),("X"),("F"),("F")
.
CUSTLIST        FILELIST
CUSTFILE        IFILE           NAME="CUSTOMER.ISI"
CUSTFILA        AFILE           NAME="CUSTOMER.AAM"
                FILELISTEND
.
CUSTTEXT        COLLECTION
CUSTCMD         COLLECTION
