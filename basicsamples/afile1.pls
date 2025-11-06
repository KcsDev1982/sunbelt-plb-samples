*====================================================
. AAM Sample Program
. Demonstrates creation, writing, and reading of an AAM file
*====================================================

Customer    AFILE
CustID      DIM        10
Name        DIM        30
City        DIM        20
Balance     FORM       7.2

Key         DIM        33

          CALL    Main
          STOP

*----------------------------------------------------
. Main Routine
*----------------------------------------------------
Main      LFUNCTION
          ENTRY

*--- Create or open the file
          PREPARE   Customer, "customer.dat","customer.aam","1-10,11-40,41-60","70"

*--- Add some customer records
          MOVE      "C001"      TO CustID
          MOVE      "John Smith" TO Name
          MOVE      "Dallas"    TO City
          MOVE      125.75      TO Balance
          WRITE     Customer;CustID,Name,City,Balance

          MOVE      "C002"      TO CustID
          MOVE      "Mary Smith" TO Name
          MOVE      "Houston"   TO City
          MOVE      89.20       TO Balance
          WRITE     Customer;CustID,Name,City,Balance

          CLOSE     Customer

*--- Read generic
	  OPEN      Customer, "customer.aam"
          DISPLAY   *N,"Customer Records:",*N
          MOVE      "02FSmith" TO Key
          READ      Customer,Key;CustID,Name,City,Balance
LoopRD    IF        OVER
              GOTO   EndRead
           ENDIF

           DISPLAY  CustID, " - ", Name, " - ", City, " - ", Balance
           READKG   Customer;CustID,Name,City,Balance
           GOTO     LoopRD
EndRead

*--- Read a specific record by key
          MOVE      "01XC002      " TO Key
          READ      Customer,Key;CustID,Name,City,Balance
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
