*....................................................
.
.Open the Customer File
. If the customer file is empty, all controls except the
.  New and Close buttons are disabled.  Otherwise, the 
.  first record is displayed.
*
.Open the file
.
CustOpen
                TRAP            CustPrep IF IO
                OPEN            CUSTLIST
                TRAPCLR         IO
*
.Build a collection of the EditText objects
. and a collection of the command buttons 
. except New and Close.
.
                LISTINS         CUSTTEXT,cust_txtNumber:
                                cust_txtName,cust_txtAddress:
                                cust_txtCity,cust_txtState:
                                cust_txtZipcode,cust_txtFName:
                                cust_txtLName
.
                LISTINS         CUSTCMD,cust_cmdDelete:
                                cust_cmdFirst,cust_cmdPrevious:
                                cust_cmdNext,cust_cmdLast
*
.Attempt to read the first record
.
                CALL            CustFirst
                CALL            CustCount
                RETURN
*....................................................
.
.Create the Customer File
.
CustPrep
                ALERT           TYPE=YESNO,"The Customer file "::
                                "does not exist - Create It ?":
                                RESULT,"Warning"
                STOP            IF (RESULT = 7)
. 
                PREPARE         CUSTFILE,"CUSTOMER","CUSTOMER":
                                "1-10","167"
                PREPARE         CUSTFILA,"CUSTOMER","CUSTOMER":
                                "U,1-10,11-50,51-90,91-120,121-122,123-127,128-147,148-167","167"  
                RETURN
*....................................................
.
.Close the customer form
.
CustClose
                IF              (Searching)
                SETPROP         CUSTCMD,ENABLED=1
                CLEAR           CUSTDATA,Searching
                SETPROP         cust_cmdNew,ENABLED=1
                SETPROP         cust_txtNumber,READONLY=1
                SETPROP         cust_cmdFind,TITLE="&Find"
                SETPROP         cust_cmdDelete,TITLE="&Delete"
                CALL            CustPut
                CALL            CustRead
                CALL            CustCount
                ELSE
                CALL            CustDelete IF (Adding)
                SETPROP         frmCustomer,VISIBLE=0
                ENDIF
                RETURN
*....................................................
.
.Read the Customer File by Customer Number
.
CustRead
                CALL            CustFirst IF (CUSTNUM = 0)
.
                MOVE            CUSTNUM,CUSTKEY
                TRAP            CustRead1 IF IO
                READ            CUSTFILE,CUSTKEY;CUSTDATA
                TRAPCLR         IO
                RETURN          IF OVER
.
                CALL            CustPut
.
CustRead1
                RETURN
*....................................................
.
.Read the First Customer Record
.
CustFirst
                IF              (SEARCHING)
                READ            CUSTFILA,CUSTKEYA;CUSTDATA 
                ELSE
                FILL            " ",CUSTKEY
                READ            CUSTFILE,CUSTKEY;;
                READKS          CUSTFILE;CUSTDATA
.
                IF              OVER
                SETPROP         CUSTTEXT,ENABLED=0
                SETPROP         CUSTCMD,ENABLED=0
                RETURN
                ENDIF
                ENDIF
.
                CALL            CustPut
                RETURN
*....................................................
.
.Read the Previous Customer Record
.
CustPrevious
                IF              (Searching)
                READKGP         CUSTFILA;CUSTDATA
                ELSE
                READKP          CUSTFILE;CUSTDATA
                ENDIF
                IF              OVER
                ALERT           NOTE,"Beginning of file.",RESULT,"Move Previous"
                GOTO            CustFirst
                ENDIF
.
                CALL            CustPut
                RETURN
*....................................................
.
.Read the Next Customer Record
.
CustNext
                IF              (SEARCHING)
                READKG          CUSTFILA;CUSTDATA
                ELSE
                READKS          CUSTFILE;CUSTDATA
                ENDIF
                IF              OVER
                ALERT           NOTE,"End of file.",RESULT,"Move Next"
                GOTO            CustLast
                ENDIF
.
                CALL            CustPut
                RETURN
*....................................................
.
.Read the Last Customer Record
.
CustLast
                IF              (SEARCHING)
                READLAST        CUSTFILA,CUSTKEYA;CUSTDATA 
                ELSE
                FILL            "9",CUSTKEY
                READ            CUSTFILE,CUSTKEY;;
                READKP          CUSTFILE;CUSTDATA
                RETURN          IF OVER
                ENDIF
.
                CALL            CustPut
                RETURN
*....................................................
.
.Delete the Customer Record
.
CustDelete
                IF              (Adding)
                SETPROP         CUSTCMD,ENABLED=1
                CLEAR           CUSTDATA,Adding
                SETPROP         cust_cmdNew,ENABLED=1
                SETPROP         cust_txtNumber,READONLY=1
                CALL            CustPut
                CALL            CustRead
. 
                ELSE
                RETURN          IF (CUSTNUM = 0)
                DELETE          CUSTLIST
                CALL            CustNext
                CALL            CustPrevious IF OVER 
                CALL            CustCount
                ENDIF
. 
                CALL            OrdCust
                RETURN
*....................................................
.
.Add a Customer Record
.
CustNew
                SET             ADDING   // Indicate Adding
                SETPROP         CUSTTEXT,ENABLED=1   // Enable EditTexts
                SETPROP         cust_txtNumber,READONLY=0 // Allow Number Entry
                SETPROP         CUSTCMD,ENABLED=0  // Disable Buttons
                SETPROP         cust_cmdNew,ENABLED=0 // Disable New  
                SETPROP         cust_cmdDelete,ENABLED=1  // Enable Delete
                SETFOCUS        cust_txtNumber   // Position Cursor
                DELETEITEM      CUSTTEXT,0  // Clear Fields
                RETURN
*....................................................
.
.Save a Customer Record
.
CustSave
                CALL            CUSTGET
.
                IF              (ADDING)   
                WRITE           CUSTLIST;CUSTDATA
                CALL            CustCount
                CLEAR           ADDING
                SETPROP         CUSTCMD,ENABLED=1
                SETPROP         cust_cmdNew,ENABLED=1
                SETPROP         cust_txtNumber,READONLY=1
                ELSE
                UPDATE          CUSTLIST;CUSTDATA
                ENDIF
.
                SETPROP         cust_cmdSave,ENABLED=0
                CALL            OrdCust
                RETURN
*....................................................
.
.Update the count of Customers
.
CustCount
                IF              (SEARCHING)
                SETITEM         cust_lblCount,0,"Search Results"
                ELSE
                GETFILE         CUSTFILE,RECORDCOUNT=NWORK10
.
                IF              (NWORK10 = 0)
                MOVE            "No Customers",MSG
                ELSEIF          (NWORK10 = 1)
                MOVE            "1 Customer",MSG
                ELSE
                MOVE            NWORK10,DIM10
                SQUEEZE         DIM10,DIM10
                PACK            MSG WITH DIM10," Customers"
                ENDIF
.
                SETITEM         cust_lblCount,0,MSG 
.
                IF              (NWORK10 > 1)
                SETPROP         CUSTCMD,ENABLED=$TRUE
                ENDIF
                ENDIF
                RETURN
*....................................................
.
.Transfer Record Data to the Form Objects
.
CustPut
                IF              (CUSTNUM > 0)
                MOVE            CUSTNUM,CUSTKEY
                ELSE
                CLEAR           CUSTKEY
                ENDIF
.
                SETITEM         cust_txtNumber,0,CUSTKEY
                SETITEM         cust_txtName,0,CONAME
                SETITEM         cust_txtAddress,0,ADDRESS
                SETITEM         cust_txtCity,0,CITY
                SETITEM         cust_txtState,0,STATE
                SETITEM         cust_txtZipcode,0,ZIPCODE
                SETITEM         cust_txtFName,0,CONTACTFN
                SETITEM         cust_txtLName,0,CONTACTLN
                RETURN
*....................................................
.
.Transfer Record Data from the Form Objects
.
CustGet
                GETITEM         cust_txtNumber,0,Result
                IF              ZERO
                CLEAR           CUSTNUM
                ELSE
                GETITEM         cust_txtNumber,0,CUSTKEY
                MOVE            CUSTKEY,CUSTNUM
                ENDIF
.
                GETITEM         cust_txtName,0,CONAME
                GETITEM         cust_txtAddress,0,ADDRESS
                GETITEM         cust_txtCity,0,CITY
                GETITEM         cust_txtState,0,STATE
                GETITEM         cust_txtZipcode,0,ZIPCODE
                GETITEM         cust_txtFName,0,CONTACTFN
                GETITEM         cust_txtLName,0,CONTACTLN
                RETURN
*....................................................
.
.Enable the Save button when the required files are input
.
CustVerify
                SETPROP         cust_cmdSave,ENABLED=$FALSE
                GETITEM         Cust_txtNumber,0,RESULT // Number is required
                RETURN          IF ZERO
                GETITEM         Cust_txtName,0,RESULT // Name is required
                RETURN          IF ZERO
.
                SETPROP         cust_cmdSave,ENABLED=$TRUE
                RETURN
*....................................................
.
.Locate a customer
.
CustFind
                IF              (Searching)
                CALL            CUSTGET
                CLEAR           CUSTKEYA
                IMPLODE         MSG,";",cust_txtNumber:
                                cust_txtName,cust_txtAddress:
                                cust_txtCity,cust_txtState:
                                cust_txtZipcode,cust_txtFName:
                                cust_txtLName
                EXPLODE         MSG,";",CUSTKEYA
                FOR             FIELDNO,"1",CUSTFCNT
                COUNT           RESULT,CUSTKEYA(FIELDNO)
                IF              NOT ZERO
                IF              (CUSTSRCH(FIELDNO) = "F" AND RESULT < 3)
                ALERT           CAUTION,"At least three characters required for search":
                                RESULT,"Find"
                RETURN
                ENDIF
                PACK            DIM10 WITH FIELDNO,CUSTSRCH(FIELDNO)
                REP             " 0",DIM10
                SPLICE          DIM10,CUSTKEYA(FIELDNO)
                ENDIF
                REPEAT
                READ            CUSTFILA,CUSTKEYA;CUSTDATA
                IF              OVER
                ALERT           NOTE,"No matching records found",RESULT,"Find"
                SETFOCUS        cust_txtNumber
                ENDIF
                CALL            CUSTPUT
                SETPROP         cust_cmdDelete,ENABLED=1
                SETPROP         cust_cmdFirst,ENABLED=1
                SETPROP         cust_cmdPrevious,ENABLED=1
                SETPROP         cust_cmdNext,ENABLED=1
                SETPROP         cust_cmdLast,ENABLED=1
                RETURN
 
                ELSE
                SET             SEARCHING   // Indicate Adding
                SETPROP         CUSTCMD,ENABLED=0  // Disable Navigation
                SETPROP         cust_cmdNew,ENABLED=0 // Disable New
                SETPROP         CUSTTEXT,ENABLED=1   // Enable EditTexts
                SETPROP         cust_txtNumber,READONLY=0 // Allow Number Entry
                SETPROP         cust_cmdClose,ENABLED=1:  // Enable Delete
                                Title="Cancel"  // Change Caption
                SETPROP         cust_cmdFind,Title="Search" // Change Caption
                SETFOCUS        cust_txtNumber   // Position Cursor
                DELETEITEM      CUSTTEXT,0  // Clear Fields
                ENDIF
.
                CALL            CustCount
                RETURN
