*---------------------------------------------------------------
.
. Program Name: Lab04.pls
. Description:  Introduction to PL/B Lab 4 program
.           
.
MIN             FORM            2
MAX             FORM            2
TEST            FORM            2
.
REPLY           DIM             1
*
.Get the values
.
Start
                KEYIN           *HD,*R,"Enter values for":
                                *HD,*R,"Min: ",MIN:
                                *HD,*R,"Max: ",MAX:
                                *HD,*R,"Test: ",TEST
                STOP            IF F3
*
.Go test them
. 
                CALL            TestValue
*
.Report the findings
.  
                IF              ZERO
                DISPLAY         *HD,*R,TEST," is between ",MIN," and ",MAX
                ELSE
                DISPLAY         *HD,*R,TEST," is NOT between ",MIN," and ",MAX
                ENDIF
*
.Wait for acknowlegement
.
                KEYIN           *HD,*R,*R,"Press any key to continue. ",REPLY 
*
.Do it again
.
                GOTO            Start
*
.Check the value
.
TestValue
. 
                IF              (TEST > MIN AND TEST < MAX)
                SETFLAG         ZERO
                ELSE
                SETFLAG         NOT ZERO
                ENDIF
. 
                RETURN
*
.Quit requested
.
QUIT
                STOP
