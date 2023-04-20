*---------------------------------------------------------------
.
. Program Name: Lab07-1.pls
. Description:  Introduction to PL/B Lab 7 program
.
H               INTEGER         4
Q               INTEGER         4
D               INTEGER         4
N               INTEGER         4
P               INTEGER         4
.
COMBINATIONS    INTEGER         4
ITERATIONS      INTEGER         4
REPLY           DIM             1
COMBOS          FORM            3
ITERS           FORM            6
.
                TRAP            QUIT IF ESCAPE
.
                FOR             H FROM "0" TO "2"
                FOR             Q FROM "0" TO "4"
                FOR             D FROM "0" TO "10"
                FOR             N FROM "0" TO "20"
                FOR             P FROM "0" TO "100" USING "5"
. 
                IF              (((H * 50) + (Q * 25) + (D * 10) + (N * 5) + P) = 100)
.                DISPLAY         *HD,H,":",Q,":",D,":",N,":",P
                INCR            COMBINATIONS
                ENDIF
. 
                INCR            ITERATIONS
.
                REPEAT
                REPEAT
                REPEAT
                REPEAT
                REPEAT
.

                MOVE            COMBINATIONS,COMBOS
                MOVE            ITERATIONS,ITERS 
                KEYIN           *HD,*R,"Combinations: ",*DV,COMBOS:
                                "  Iterations: ",*DV,ITERS,"  ",REPLY;
.  
QUIT
                STOP
