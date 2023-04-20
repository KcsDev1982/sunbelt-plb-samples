*---------------------------------------------------------------
.
. Program Name: Lab07.pls
. Description:  Introduction to PL/B Lab 7 program
. 
H               INTEGER         4
Q               INTEGER         4
D               INTEGER         4
N               INTEGER         4
P               INTEGER         4
.
C               INTEGER         4
I               INTEGER         4
.
COMBINATIONS    FORM            7
ITERATIONS      FORM            7
COUNT           FORM            "20"
REPLY           DIM             1
.
                TRAP            QUIT IF ESCAPE
.
                FOR             H FROM 0 TO 2
                FOR             Q FROM 0 TO 4
                FOR             D FROM 0 TO 10
                FOR             N FROM 0 TO 20
                FOR             P FROM 0 TO 100 
.
                IF              (((H * 50) + (Q * 25) + (D * 10) + (N * 5) + P) = 100)
 
.                DISPLAY         *HD,H,":",Q,":",D,":",N,":",P
.                DECR            COUNT
.                IF              ZERO
.                KEYIN           *HD,"Continue...",REPLY
.                MOVE            "20",COUNT
.                ENDIF
 
                INCR            C
                ENDIF
. 
                INCR            I
.
                REPEAT
                REPEAT
                REPEAT
                REPEAT
                REPEAT
.
                MOVE            C,Combinations
                MOVE            I,Iterations
                KEYIN           *HD,*R,"Combinations: ",*DV,COMBINATIONS:
                                "  Iterations: ",*DV,ITERATIONS,"  ",REPLY;
.  
QUIT
                STOP
