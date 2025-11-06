*-------------------------------------------------------------------
.  CUSTOMER.PLX – Demonstration of KEYIN input and data handling
*-------------------------------------------------------------------

NAME             DIM             30          ; Customer name
ADDRESS          DIM             40          ; Street address
CITY             DIM             25          ; City name
STATE            DIM             2           ; Two-character state code
ZIPCODE          DIM             10          ; Postal/ZIP code
AMOUNTDUE        FORM            7.2         ; Numeric field for money

*-------------------------------------------------------------------
.  Begin program execution
*-------------------------------------------------------------------

                 DISPLAY         *ES, *HD, "Customer Entry Form", *N, *N

*-------------------------------------------------------------------
.  Request user input for each field using KEYIN
*-------------------------------------------------------------------

                 KEYIN           *P=10:05, "Enter Customer Name   : ", NAME:
                                  *P=10:07, "Enter Street Address : ", ADDRESS:
                                  *P=10:09, "Enter City           : ", CITY:
                                  *P=10:11, "Enter State (2 chars): ", STATE:
                                  *P=10:13, "Enter ZIP Code       : ", ZIPCODE:
                                  *P=10:15, "Enter Amount Due     : ", AMOUNTDUE

*-------------------------------------------------------------------
.  Display confirmation of entered information
*-------------------------------------------------------------------

                 DISPLAY         *N, *HD, "------------------------------------------"
                 DISPLAY         *N, "Customer Name   : ", NAME
                 DISPLAY         *N, "Street Address  : ", ADDRESS
                 DISPLAY         *N, "City, State ZIP : ", CITY, ", ", STATE, "  ", ZIPCODE
                 DISPLAY         *N, "Amount Due      : $", AMOUNTDUE
                 DISPLAY         *N, "------------------------------------------", *N, *N

*-------------------------------------------------------------------
.  End program – show message, then pause for 5 seconds
*-------------------------------------------------------------------

                 DISPLAY         *N, "Program will end in 5 seconds..."
                 PAUSE           "5"
                 STOP
