*................................................................
.
. Demonstration of searching for a substring in PL/B
. Uses the SEARCH instruction and an LFUNCTION
.
*................................................................

*------------------------------*
*  Data Definitions (Globals)  *
*------------------------------*
sentence       DIM        80
searchWord     DIM        20
position       FORM       3
foundFlag      FORM       1

		CALL	Main
		PAUSE 	"2"
		STOP

*................................................................
.
. Main program
.
Main           LFUNCTION
               ENTRY

               KEYIN   "Enter a sentence: ", sentence, *N:
                       "Enter word to search for: ", searchWord

               CALL    FindWord USING sentence, searchWord, position, foundFlag

               IF       (foundFlag)
                        DISPLAY *N, "The word [", searchWord, "] was found at position ", position
               ELSE
                        DISPLAY *N, "The word [", searchWord, "] was NOT found."
               ENDIF

               FUNCTIONEND
*................................................................
.
. FindWord - LFUNCTION to locate a substring within a string
.
FindWord       LFUNCTION
textLine       DIM        80
targetWord     DIM        20
posResult      FORM       ^
flagResult     FORM       ^
               ENTRY

               CLEAR     flagResult
               CLEAR     posResult

               SCAN    targetWord IN textLine

               IF        EQUAL
                 MOVEFPTR  textLine, posResult
                 SET flagResult
               ENDIF

               FUNCTIONEND 
