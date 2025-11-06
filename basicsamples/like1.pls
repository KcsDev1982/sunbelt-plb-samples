*-----------------------------------------------------------------
. Demonstrate LIKE operator usage in IF statements
*-----------------------------------------------------------------

NAME        DIM     30
PATTERN     DIM     30

        KEYIN   "Enter a name: ", NAME
        KEYIN   "Enter a pattern (use % or _): ", PATTERN

        IF   (NAME LIKE PATTERN)
             DISPLAY *N, "Match found!"
        ELSE
             DISPLAY *N, "No match."
        ENDIF

        IF   (NOCASE NAME LIKE "jo%")
             DISPLAY *N, "Name starts with 'jo' (any case)"
        ENDIF

        IF   (NAME LIKE "____")   // Exactly 4 characters
             DISPLAY *N, "Name has exactly 4 characters"
        ENDIF
        PAUSE "5"
        STOP
