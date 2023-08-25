*....................................................
.
.Open the Order File
. If the Order file is empty, all controls except the
.  New and Close buttons are disabled.  Otherwise, the 
.  first record is displayed.
*
.Open the file
.
OrdOpen
	TRAP	OrdPrep IF IO
	OPEN	ORDFILE,"ORDER.ISI"
	TRAPCLR	IO
*
.Open the Order Detail file
.
	CALL	DtlOpen	
*
.Build a collection of the input objects
. and a collection of the command buttons 
. except New and Close.
.
	LISTINS	ORDTEXT,ord_txtNumber:
		ord_edtDate,ord_rdoUPS:
		ord_rdoFedEx,ord_rdoDHL:
		ord_cboSalesRep
.
	LISTINS	ORDCMD,ord_cmdSave,ord_cmdDelete:
		ord_cmdFirst,ord_cmdPrevious:
		ord_cmdNext,ord_cmdLast
*
.Load the Customer combobox
.
	CALL	OrdCust
*
.Attempt to read the first record
.
	CALL	OrdFirst
	CALL	OrdCount
.
	RETURN
*....................................................
.
.Create the Order File
.
OrdPrep
	ALERT	TYPE=YESNO,"The Order file "::
		"does not exist - Create It ?":
		RESULT,"Warning"
	STOP	IF (RESULT = 7)
.	
	PREPARE	ORDFILE,"ORDER","ORDER":
		"1-10","32"
	RETURN
*....................................................
.
.Close the order form
.
OrdClose
	CALL	OrdDelete IF (Adding)
	SETPROP	frmOrder,VISIBLE=0
	RETURN	
*....................................................
.
.Read the Order File by Order Number
.
OrdRead
	CALL	OrdFirst IF (ORDNUM = 0)
.
	MOVE	ORDNUM,ORDKEY
	TRAP	OrdRead1 IF IO
	READ	ORDFILE,ORDKEY;ORDDATA
	TRAPCLR	IO
	RETURN	IF OVER
.
	CALL	OrdPut
.
OrdRead1
	RETURN
*....................................................
.
.Read the First Order Record
.
OrdFirst
	FILL	" ",ORDKEY
	READ	ORDFILE,ORDKEY;;
	READKS	ORDFILE;ORDDATA
.
	IF	OVER
	SETPROP	ORDTEXT,ENABLED=0
	SETPROP	ORDCMD,ENABLED=0
	RETURN
	ENDIF
.
	CALL	OrdPut
	RETURN
*....................................................
.
.Read the Previous Order Record
.
OrdPrevious
	READKP	ORDFILE;ORDDATA
	IF	OVER
	ALERT	NOTE,"Beginning of file.",RESULT,"Move Previous"
	GOTO	OrdFirst
	ENDIF
.
	CALL	OrdPut
	RETURN	
*....................................................
.
.Read the Next Order Record
.
OrdNext
	READKS	ORDFILE;ORDDATA
	IF	OVER
	ALERT	NOTE,"End of file.",RESULT,"Move Next"
	GOTO	OrdLast
	ENDIF
.
	CALL	OrdPut
	RETURN
*....................................................
.
.Read the Last Order Record
.
OrdLast
	FILL	"9",ORDKEY
	READ	ORDFILE,ORDKEY;;
	READKP	ORDFILE;ORDDATA
	RETURN	IF OVER
.
	CALL	OrdPut
	RETURN		
*....................................................
.
.Delete the Order Record
.
OrdDelete
	IF	(Adding)
	CLEAR	ORDDATA,Adding
	SETPROP	ord_cmdNew,ENABLED=1
	SETPROP	ord_txtNumber,READONLY=1
	CALL	OrdPut
	CALL	OrdRead
	ELSE
	RETURN	IF (ORDNUM = 0)
	DELETE	ORDFILE
	CALL	DtlDeleteAll
	CALL	OrdNext
	CALL	OrdPrevious IF OVER 
	CALL	OrdCount
	ENDIF
.
	CALL	DtlListAll	
	RETURN
*....................................................
.
.Add a Order Record
.
OrdNew	
	SET	ADDING			// Indicate Adding
	SETPROP	ORDTEXT,ENABLED=1	 	// Enable EditTexts
	SETPROP	ord_txtNumber,READONLY=0	// Allow Number Entry
	SETPROP	ord_cmdDelete,ENABLED=1 	// Enable Delete
	SETPROP	ord_cmdNew,ENABLED=0	// Disable New 
	SETPROP	ord_cmdSave,ENABLED=0	// Disable Save
	SETFOCUS	ord_txtNumber 		// Position Cursor
	DELETEITEM ord_txtNumber,0		// Clear Numer
	SETITEM	ord_cboCustnum,0,0
	SETITEM	ord_cboSalesRep,0,0
	CLOCK	TIMESTAMP,MSG
	SETITEM	ord_edtDate,0,MSG
	SETITEM	ord_rdoUPS,0,1
	ord_lvDetail.DeleteAllItems
	RETURN
*....................................................
.
.Save a Order Record
.
OrdSave
	CALL	ORDGET
.
	IF	(ADDING)			
	WRITE	ORDFILE;ORDDATA
	CALL	OrdCount
	CLEAR	ADDING
	SETPROP	ord_cmdNew,ENABLED=1
	SETPROP	ord_txtNumber,READONLY=1
	ELSE
	UPDATE	ORDFILE;ORDDATA
	ENDIF
.
	RETURN
*....................................................
.
.Update the count of Orders
.
OrdCount
	GETFILE	ORDFILE,RECORDCOUNT=NWORK10
.
	IF	(NWORK10 = 0)
	MOVE	"No Orders",MSG
	ELSEIF	(NWORK10 = 1)
	MOVE	"1 Order",MSG
	ELSE
	MOVE	NWORK10,DIM10
	SQUEEZE	DIM10,DIM10
	PACK	MSG WITH DIM10," Orders"
	ENDIF
.
	SETITEM	ord_lblCount,0,MSG	
.
	IF	(NWORK10 > 1)
	SETPROP	ORDCMD,ENABLED=$TRUE
	ENDIF
	RETURN
*....................................................
.
.Transfer Record Data to the Form Objects
.
OrdPut
	IF	(ORDNUM > 0)
 	MOVE	ORDNUM,ORDKEY
 	ELSE
 	CLEAR	ORDKEY
 	ENDIF
	SETITEM	ord_txtNumber,0,ORDKEY
.
	ord_cboCustnum.GetCount Giving NWORK10
	FOR 	RESULT,"1",NWORK10
	ord_cboCustnum.GetItemData GIVING VALUE:
		USING RESULT
	REPEAT	WHILE (VALUE != ORDCUST)
	ord_cboCustnum.SetCurSel USING RESULT
		
	SETITEM	ord_cboCustnum,0,ORDCUST
.	
	SETITEM	ord_edtDate,0,ORDDATE
.
	IF	(ORDSHIP = 1)
	SETITEM	ord_rdoUPS,0,1
	ELSEIF	(ORDSHIP = 2)
	SETITEM	ord_rdoFedEx,0,1
	ELSE
	SETITEM	ord_rdoDHL,0,1
	ENDIF
.
	SETITEM	ord_cboSalesRep,0,ORDSALES
.
	CALL	DtlListAll
	RETURN
*....................................................
.
.Transfer Record Data from the Form Objects
.
OrdGet
	GETITEM	ord_txtNumber,0,Result
	IF	ZERO
	CLEAR	ORDNUM
	ELSE	
	GETITEM	ord_txtNumber,0,ORDKEY
	MOVE	ORDKEY,ORDNUM
	ENDIF
.
	GETITEM	ord_cboCustnum,0,RESULT
	DECR	RESULT
	ord_cboCustnum.GetItemData GIVING ORDCUST:
		USING RESULT
.	
	GETITEM	ord_edtDate,0,ORDDATE
.	
	GETITEM	ord_rdoUPS,0,RESULT
	IF	NOT ZERO
	MOVE	"1",ORDSHIP
	ELSE
	GETITEM	ord_rdoFedEx,0,RESULT
	IF	NOT ZERO
	MOVE	"2",ORDSHIP
	ELSE
	MOVE	"3",ORDSHIP
	ENDIF
	ENDIF
.
	GETITEM	ord_cboSalesRep,0,ORDSALES
.
	RETURN
*....................................................
.
.Enable the Save button when the required files are input
.
OrdVerify
	SETPROP	ord_cmdSave,ENABLED=$FALSE
	GETITEM	ord_txtNumber,0,RESULT	// Number is required
	RETURN 	IF ZERO
	GETITEM	ord_cboCustnum,0,RESULT	// Customer is required
	RETURN	IF ZERO
	GETITEM	ord_cboSalesRep,0,RESULT	// SalesRep is required
	RETURN	IF ZERO	
.
	SETPROP	ord_cmdSave,ENABLED=$TRUE
	RETURN
*....................................................
.Load the customer combobox
.
OrdCust
	DELETEITEM ord_cboCustnum,0
.	
	FILL	" ",CUSTKEY
	READ	CUSTFILE,CUSTKEY;;
.
	LOOP
	READKS	CUSTFILE;DIM10,CONAME
	UNTIL	OVER
	ord_cboCustnum.AddString GIVING RESULT USING CONAME
	ord_cboCustnum.SetItemData USING CUSTNUM,RESULT
	REPEAT
.
	READ	CUSTFILE,CUSTNUM;CUSTDATA
	RETURN		
