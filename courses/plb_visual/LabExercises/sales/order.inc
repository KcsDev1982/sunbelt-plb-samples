*
.Order File
.
ORDNUM          FORM            10
ORDCUST         FORM            10   
ORDDATE         DIM             8  
ORDSHIP         FORM            1 
ORDSALES        DIM             3
.
ORDDATA         VARLIST         ORDNUM,ORDCUST,ORDDATE:
                                ORDSHIP,ORDSALES
.  
ORDKEY          DIM             10
ORDFILE         IFILE           NAME="ORDER.ISI"
.
ORDTEXT         COLLECTION
ORDCMD          COLLECTION
