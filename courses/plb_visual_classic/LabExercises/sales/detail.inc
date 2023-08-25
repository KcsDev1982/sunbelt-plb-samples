*
.Order Detail File
.
DTLORD          FORM            10
DTLITEM         FORM            10
DTLDESC         DIM             20
DTLQTY          FORM            10 
DTLPRICE        FORM            7.2 
.
DTLDATA         VARLIST         DTLORD,DTLITEM,DTLDESC,DTLQTY,DTLPRICE
.  
DTLKEY          DIM             20
DTLFILE         IFILE           NAME="DETAIL.ISI"
.
DTLTEXT         COLLECTION
