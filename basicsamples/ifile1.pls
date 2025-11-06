*====================================================
. ISI Sample Program
. Demonstrates creation, writing, and reading of an ISI file
*====================================================

Customer    IFILE
CustID      DIM        10
Name        DIM        30
City        DIM        20
Balance     FORM       7.2

          CALL    Main
          STOP

*----------------------------------------------------
. Main Routine
*----------------------------------------------------
Main      LFUNCTION
          ENTRY

*--- Create or open the file
          PREPARE   Customer, "customer.data","customer.isi","1-10","70"

*--- Add some customer records
          MOVE      "C001"      TO CustID
          MOVE      "John Smith" TO Name
          MOVE      "Dallas"    TO City
          MOVE      125.75      TO Balance
          WRITE     Customer,CustId;CustID,Name,City,Balance

          MOVE      "C002"      TO CustID
          MOVE      "Mary Jones" TO Name
          MOVE      "Houston"   TO City
          MOVE      89.20       TO Balance
          WRITE     Customer,CustId;CustID,Name,City,Balance

*--- Read sequentially (ascending key order)
	  OPEN      Customer, "customer.isi"
          DISPLAY   *N,"Customer Records:",*N
          READKS    Customer;CustID,Name,City,Balance
LoopRD    IF        OVER
              GOTO   EndRead
           ENDIF

           DISPLAY  CustID, " - ", Name, " - ", City, " - ", Balance
           READKS   Customer;CustID,Name,City,Balance
           GOTO     LoopRD
EndRead

*--- Read a specific record by key
          MOVE      "C002" TO CustID
          READ      Customer, CustID;CustID,Name,City,Balance
          IF        NOT OVER
              DISPLAY *N,*N,"Record Found:",*N
              DISPLAY CustID," - ",Name," - ",City," - ",Balance
          ELSE
              DISPLAY *N,"Record not found."
          ENDIF

*--- Done
          CLOSE     Customer
          PAUSE     "5"
          FUNCTIONEND
