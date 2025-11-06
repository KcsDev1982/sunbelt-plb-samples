*
. FILELIST2.PLS  - Extended FILELIST demonstration with
.                 WRITE, UPDATE, and DELETE.
.

*-----------------------------*
*   Data definitions          *
*-----------------------------*

CUSTLIST   FILELIST
CUSTPRIM   IFILE          NAME="custprim.isi",FIXED=80,KEY=10
CUSTNAME   IFILE          NAME="custname.isi",FIXED=80,KEY=30
           FILELISTEND

CUSTREC    DIM            80          // Full customer record
CUSTNO     DIM            10          // Customer number (primary key)
CUSTNM     DIM            30          // Customer name
ADDR       DIM            25          // Street address
CITY       DIM            15          // City

CHOICE     DIM             1
ANS        DIM             1
.
           KEYIN          "Initialize with sample data (Y/N)? ",ANS
           IF             (ANS = "Y" | ANS = "y")
           CALL           INITDATA
           ENDIF

           OPEN           CUSTLIST

MAINLOOP   
           CALL           SHOWMENU
           IF             (CHOICE = "X" | CHOICE = "x")
           GOTO           DONE
           ENDIF

           IF             (CHOICE = "A" | CHOICE = "a")
           CALL           ADDCUST
           ELSEIF         (CHOICE = "U" | CHOICE = "u")
           CALL           UPDCUST
           ELSEIF         (CHOICE = "D" | CHOICE = "d")
           CALL           DELCUST
           ELSEIF         (CHOICE = "F" | CHOICE = "f")
           CALL           FINDCUST
           ELSE
           DISPLAY        *N,"Invalid choice.",*W1
           ENDIF

           GOTO           MAINLOOP

DONE       
           CLOSE          CUSTLIST
           STOP

*-----------------------------*
*   Subroutines               *
*-----------------------------*

SHOWMENU   
           DISPLAY        *ES
           DISPLAY        *N,"A - Add customer"
           DISPLAY        *N,"U - Update customer"
           DISPLAY        *N,"D - Delete customer"
           DISPLAY        *N,"F - Find customer"
           DISPLAY        *N,"X - Exit"
           KEYIN          *N,"Choice: ",CHOICE
           RETURN

*  Build a record buffer from the individual fields.
MAKEREC    
           PACKKEY        CUSTREC Using CUSTNO,CUSTNM,ADDR,CITY
           RETURN

ADDCUST    
           KEYIN          *N,"Customer number : ",CUSTNO
           KEYIN          *N,"Customer name   : ",CUSTNM
           KEYIN          *N,"Address         : ",ADDR
           KEYIN          *N,"City            : ",CITY

           CALL           MAKEREC

*  WRITE via FILELIST – all indexes maintained automatically.
           WRITE          CUSTLIST;CUSTREC
           IF             OVER
           DISPLAY        *N,"Duplicate or write error.",*W1
           ELSE
           DISPLAY        *N,"Customer added.",*W1
           ENDIF
           RETURN

UPDCUST    
           KEYIN          *N,"Customer number to update: ",CUSTNO

*  Locate by primary key using the primary IFILE.
           READ           CUSTPRIM,CUSTNO;CUSTREC
           IF             OVER
           DISPLAY        *N,"Customer not found.",*W1
           RETURN
           ENDIF

           DISPLAY        *N,"Current record: ",CUSTREC,*W1

*  Collect fully replaced values.
           KEYIN          *N,"New customer name : ",CUSTNM
           KEYIN          *N,"New address       : ",ADDR
           KEYIN          *N,"New city          : ",CITY

           CALL           MAKEREC

*  UPDATE via FILELIST – all key changes propagated to indices.
           UPDATE         CUSTLIST;CUSTREC
           IF             OVER
           DISPLAY        *N,"Update failed.",*W1
           ELSE
           DISPLAY        *N,"Customer updated.",*W1
           ENDIF
           RETURN

DELCUST    
           KEYIN          *N,"Customer number to delete: ",CUSTNO

           READ           CUSTPRIM,CUSTNO;CUSTREC
           IF             OVER
           DISPLAY        *N,"Customer not found.",*W1
           RETURN
           ENDIF

           DISPLAY        *N,"Deleting record: ",CUSTREC,*W1
           KEYIN          *N,"Confirm delete (Y/N)? ",ANS
           IF             (ANS <> "Y" & ANS <> "y")
           DISPLAY        *N,"Delete cancelled.",*W1
           RETURN
           ENDIF

*  DELETE via FILELIST – all related keys removed.
           DELETE         CUSTLIST
           IF             OVER
           DISPLAY        *N,"Delete failed.",*W1
           ELSE
           DISPLAY        *N,"Customer deleted.",*W1
           ENDIF
           RETURN

FINDCUST   
           KEYIN          *N,"Customer number to find: ",CUSTNO

           READ           CUSTPRIM,CUSTNO;CUSTREC
           IF             OVER
           DISPLAY        *N,"Customer not found.",*W1
           ELSE
           DISPLAY        *N,"Record: ",CUSTREC,*W1
           ENDIF
           RETURN

*  Optional initializer to create a couple of records.
INITDATA   
           ERASE          "custdata.dat"
           PREP           CUSTPRIM,"custdata.dat","custprim.isi","1-10",80
           PREP           CUSTNAME,"custdata.dat","custname.isi","11-40",80
           OPEN           CUSTLIST

           MOVE           "0000000001" TO CUSTNO
           MOVE           "John Smith                 " TO CUSTNM
           MOVE           "123 Main St               " TO ADDR
           MOVE           "Springfield      "          TO CITY
           CALL           MAKEREC
           WRITE          CUSTLIST;CUSTREC

           MOVE           "0000000002" TO CUSTNO
           MOVE           "Mary Jones                 " TO CUSTNM
           MOVE           "45 Oak Avenue             " TO ADDR
           MOVE           "Lakeside         "          TO CITY
           CALL           MAKEREC
           WRITE          CUSTLIST;CUSTREC

           CLOSE          CUSTLIST
           RETURN
