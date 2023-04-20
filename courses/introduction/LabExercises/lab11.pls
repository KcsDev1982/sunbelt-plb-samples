*---------------------------------------------------------------
.
. Program Name: Lab11.pls
. Description:  Introduction to PL/B Lab 11 program
.           
.
STRING          INIT            "Sunbelt Computer Software"
LETTER          INIT            "s"
NEWLET          INIT            "X"
COUNT           FORM            2
START           FORM            3
REPLY           DIM             1
S               FORM            6
DIM1            DIM             1

.
                DISPLAY         *HD,*R,"Before: ",STRING

                CALL            COUNT_CHAR

                DISPLAY         *HD,*R," Count: ",COUNT
.
                KEYIN           *HD,*R,"Press any key...",REPLY
                STOP
. 
COUNT_CHAR
                MOVEFPTR        STRING,START
                LOOP
                CMATCH          LETTER,STRING
                IF              EQUAL
                INCR            COUNT
                ENDIF
                BUMP            STRING
                REPEAT          UNTIL EOS
.
                RESET           STRING,START
                RETURN
.
REP_CHAR
                MOVEFPTR        STRING,START
                LOOP
                CMATCH          LETTER,STRING
                IF              EQUAL
                CMOVE           NEWLET,STRING
                ENDIF
                BUMP            STRING
                REPEAT          UNTIL EOS
.
                RESET           STRING,START
                RETURN
.
INVERT_CHAR
                MOVEFPTR        STRING,START
                LOOP
                MOVE            STRING,DIM1
                IF              (DIM1 >= "A" AND DIM1 <= "Z" OR DIM1 >="a" AND DIM1 <="z")
                XOR             040,String
                ENDIF
                BUMP            STRING
                REPEAT          UNTIL EOS
.
                RESET           STRING,START
                RETURN
.  
DEL_CHAR
                MOVEFPTR        STRING,START
                LOOP
                CMATCH          LETTER,STRING
                IF              EQUAL
. SPLICE "",STRING,1
. BUMP St
                ENDIF
                BUMP            STRING
                REPEAT          UNTIL EOS
.
                RESET           STRING,START
                RETURN
