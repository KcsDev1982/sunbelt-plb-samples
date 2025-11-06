*---------------------------------------------------------*
. SWITCH with Expressions
. Demonstrates computed CASE evaluation
*---------------------------------------------------------*

NUM1            FORM        3
NUM2            FORM        3
RESULT          FORM        3
TRUE            FORM        "1"		

                KEYIN "Enter first number: ", NUM1, *N:
                       "Enter second number: ", NUM2

                MOVE (NUM1 + NUM2) TO RESULT

                SWITCH TRUE
                CASE (RESULT < 10)
                    DISPLAY "The sum is less than 10."
                CASE (RESULT >= 10 & RESULT <= 20)
                    DISPLAY "The sum is between 10 and 20."
                CASE (RESULT > 20)
                    DISPLAY "The sum is greater than 20."
                DEFAULT
                    DISPLAY "Unexpected result."
                ENDSWITCH

                DISPLAY *N,"Calculation complete.",*W2
                STOP
