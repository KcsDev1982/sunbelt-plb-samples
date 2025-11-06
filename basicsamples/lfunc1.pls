*................................................................
.
. Demonstration of LFUNCTION usage in Sunbelt PL/B
.
*................................................................

*-----------------------------*
*  Data definitions (globals) *
*-----------------------------*
num1           FORM        7.2
num2           FORM        7.2
sumResult      FORM        7.2

		CALL Main
		STOP

*................................................................
.
. Main routine
.
Main           LFUNCTION
               ENTRY

               KEYIN   "Enter first number: ", num1, *N:
                       "Enter second number: ", num2

               CALL    AddValues GIVING sumResult USING num1, num2

               DISPLAY *N,"The sum of ", num1, " + ", num2, " = ", sumResult,*W2

               FUNCTIONEND
*................................................................
.
. AddValues - A sample function that adds two FORM values
.
AddValues      LFUNCTION
a              FORM        7.2
b              FORM        7.2
               ENTRY
result         FORM        7.2

               MOVE    (a + b) TO result

               FUNCTIONEND USING result
*................................................................
