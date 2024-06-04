*==============================================================================
. PROGRAM: ViewOrders_Filter.pls
.
. PURPOSE: Test	AFILE READKG IO	using COLUMN Name IO formats.
.
. Revision History
.::
.:: 06 Jan 10 -	Created	to test	COLUMN Name formats.			 :9.4
.:: 10 Mar 10 -	Changed	SCHEMA instruction to use the replace mode.	 :9.4A
.::
;..	 INCLUDE   TCOMMON.INC
.
DOPT	 DIM	1		       ;Display	P80 option parameter
P80	 DIM	80
.
A	 AFILE
.
X1	 DIM	1
X100	 DIM	100
X100a	 DIM	100
.
xFILT	 DIM	100
.
. The 'viewdata.xml' includes the view for the customer.txt,
. orders.txt, and product.txt files.
. 
FN1	 INIT	"viewdata.xml"
.
Orderid		DIM	4
Custid		DIM	5
Prodid		DIM	3
Orderdate	DIM	8
Ordertime	DIM	8
Quantity	DIM	5
.
xOrderid	LIKE	Orderid
xCustid		LIKE	Custid
xProdid		LIKE	Prodid
xOrderdate	LIKE	Orderdate
xOrderTime	LIKE	Ordertime
xQuantity	LIKE	Quantity
.
CNT	FORM	5
RND	FORM	5
SEQ	FORM	"-1"
$0$	FORM	"0"
KEY	DIM	10
.
nAns		FORM	5
aProdid		DIM	3(3), (" 34"), (" 65"),	(" 57")
.
GOODVALUE	DIM	20
BADVALUE	DIM	20
.
*==============================================================================
. DISPLAY PROGRAM MESSAGE.
.
	DISPLAY	  "READKG AFILE	IO TEST	using COLUMN Names!"
.
STRT
.
*==============================================================================
.
	MOVE  "TESTAKG(00)  Aamdexing 'orders' file!",P80
	CALL	DSP80
.
	AAMDEX	"orders.txt -5-9"
	IF OVER
	 DISPLAY "AAMDEX OVER.."
	 GOTO	EXIT
	ENDIF
.
.....
.
	MOVE	"TESTAKG(01)  Opening files!",P80
	CALL	DSP80
.
	TRAP	IOEXIT IF IO
.
. Load the View schema from the 'viewdata.xml' file.
. 
	SCHEMA	"Default", Import=FN1, FLAGS=2	;Replace mode!		  9.4A
.
. Open the 'orders.aam' and retrieve the 'Orders' view from the
. default schema data. In this case, the view schema data can
. be used in a FILTER instruction to enhance the READ operations.
. 
	OPEN	A, "orders", VIEW="Orders"
.
.....
.
	MOVE  "TESTAKG(02)  Reading 'orders.txt'!",P80
	CALL	DSP80
.
.....
.
	MOVE  "01LB", KEY
	READ   A,KEY;	ORDERID=xOrderid:
			CUSTID=xCustid:
			PRODID=xProdid:
			ORDERDATE=xOrderdate:
			ORDERTIME=xOrderTime:
			QUANTITY=xQuantity;
	IF OVER
	 MOVE  "TESTAKG(03)  OVER for AFILE read!",P80
	 DISPLAY "OVER...", *LL,P80
	 GOTO  EXIT
	ENDIF
.
	READKGP	A;;	//Reposition back.
.
	DISPLAY	"xCustid: '",*ll,xCustid,"'"
.
. Using a FILTER, only return records that have a CUSTID
. field set to 'BERGS' or 'BLUMG'.
.
	MOVE	"CUSTID = 'BERGS' or CUSTID = 'BLUMG'", xFILT
	FILTER	A, xFILT
.
	DISPLAY *LL,"Using READ FILTER: ", xFilt
.
	LOOP
.
	 READKG	A;    ORDERID=Orderid:
		      CUSTID=Custid:
		      PRODID=Prodid:
		      ORDERDATE=Orderdate:
		      ORDERTIME=Ordertime:
		      QUANTITY=Quantity
	 BREAK IF OVER
.
	 ADD	"1", nAns
.
	 PACK	X100:
		Custid:
		Prodid
.
	 DISPLAY "X100 Data: '", *LL, X100, "'"
.
	REPEAT
.
.....
.
	DISPLAY	"Record Read Count: ",nAns
.
	CLOSE	A
.
...............................................................................
	GOTO	EXIT
.
IOEXIT
	DISPLAY "IO Error: ", *LL, S$ERROR$
 
EXIT
	 DISPLAY  "Test Completed!"
	 KEYIN	  "Hit enter to exit:",S$CMDLIN
.
	 STOP
.
*=============================================================================
DSP80				       ;Display	P80 when 'D' option used
	DISPLAY	  P80
BYPASS
	RETURN
.
 
 
 
 
