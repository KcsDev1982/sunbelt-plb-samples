*
. FILELIST1.PLS  - Simple FILELIST demonstration
.

*-----------------------------*
*   Data definitions          *
*-----------------------------*

CUSTLIST   FILELIST
CUSTPRIM   IFILE          NAME="custprim.isi",FIXED=80,KEY=10
CUSTNAME   IFILE          NAME="custname.isi",FIXED=80,KEY=30
           FILELISTEND

CUSTREC    DIM            80          // Entire customer record text
CUSTNO     DIM            10          // Customer number key
CUSTNM     DIM            30          // Customer name key (for display only)

ANS        DIM             1
.
           KEYIN          "Create sample records (Y/N)? ",ANS
           IF             (ANS = "Y" | ANS = "y")
           CALL           BuildData
           ENDIF

           CALL           LookupLoop
           STOP

*-----------------------------*
*   BuildData - write sample  *
*   records using FILELIST    *
*-----------------------------*

BuildData  LFUNCTION
           ENTRY
           ERASE          "custdata.dat"
           PREP           CUSTPRIM,"custdata.dat","custprim.isi","1-10",80
           PREP           CUSTNAME,"custdata.dat","custname.isi","11-40",80

*  Open the FILELIST (both IFILEs)
           OPEN           CUSTLIST

*  First sample record
           MOVE           "0000000001" TO CUSTREC
           ENDSET         CUSTREC
           APPEND         "John Smith                 " TO CUSTREC
           APPEND         "123 Main St               " TO CUSTREC
           APPEND         "Springfield      "          TO CUSTREC
           RESET          CUSTREC

*  WRITE to FILELIST – text + all indices updated.:contentReference[oaicite:2]{index=2}
           WRITE          CUSTLIST;CUSTREC

*  Second sample record
           RESET          CUSTREC
           MOVE           "0000000002" TO CUSTREC
           ENDSET         CUSTREC
           APPEND         "Mary Jones                 " TO CUSTREC
           APPEND         "45 Oak Avenue             " TO CUSTREC
           APPEND         "Lakeside         "          TO CUSTREC
           RESET          CUSTREC

           WRITE          CUSTLIST;CUSTREC

*  Close both files via FILELIST.:contentReference[oaicite:3]{index=3}
           CLOSE          CUSTLIST

           FUNCTIONEND

*-----------------------------*
*   LookupLoop - read via     *
*   primary key and display   *
*-----------------------------*

LookupLoop LFUNCTION
           ENTRY

Loop      

           KEYIN          *N,"Enter customer number (blank to exit): ",CUSTNO

           IF             (CUSTNO = "")
           RETURN
           ENDIF

*  Open only the FILELIST once for lookups.
           OPEN           CUSTLIST

*  READ using the primary IFILE (CUSTPRIM).  The FILELIST
*  will still be used later for UPDATE/DELETE if desired.:contentReference[oaicite:4]{index=4}
           READ           CUSTPRIM,CUSTNO;CUSTREC

           IF             OVER
           DISPLAY        *N,"Customer not found.",*W1
           ELSE
*            Simple display of full record text
           DISPLAY        *N,"Record: [",CUSTREC,"]",*W1
           ENDIF

           CLOSE          CUSTLIST

           GOTO           Loop

           FUNCTIONEND
