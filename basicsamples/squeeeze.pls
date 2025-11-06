*................................................................
.
. Demonstration of LFUNCTION and SQUEEZE
.
*................................................................

*------------------------------*
*  Data Definitions (Globals)  *
*------------------------------*
inputText       DIM        40
trimmedText     DIM        40

		CALL	Main
		STOP
*................................................................
.
. Main routine
.
Main            LFUNCTION
                ENTRY

                KEYIN   "Enter a name (with spaces): ", inputText

                CALL    TrimSpaces GIVING trimmedText USING inputText

                DISPLAY *N, "Original : [", inputText, "]"
                DISPLAY *N, "Trimmed  : [", trimmedText, "]",*W2

                FUNCTIONEND
*................................................................
.
. TrimSpaces - removes leading/trailing spaces
.
TrimSpaces      LFUNCTION
rawText         DIM        40
                ENTRY
cleanText       DIM        40

                MOVE    rawText TO cleanText
                SQUEEZE cleanText,cleanText        // Removes leading and trailing blanks

                FUNCTIONEND USING cleanText
