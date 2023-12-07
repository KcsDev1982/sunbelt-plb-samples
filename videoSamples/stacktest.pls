*---------------------------------------------------------------
.
. Program Name: stacktest
. Description:  Test the stack access under the debugger
.
. Revision History:
.
. 22-09-21 W H Keech
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 
*---------------------------------------------------------------

NAME            DIM             %10
NUM             FORM            %2.2
NUM1            INTEGER         %4
MFILE           FILE            %

FILE1           FILE
FILE2           AFILE
FILE3           IFILE
FILE4           PFILE
FILE5           XFILE

CARRAY          DIM             4[4]

A               DIM             1
Value           FORM            "10"

BaseRec         RECORD          DEFINITION
NAME            DIM             10
ADDR            FORM            5
                RECORDEND

BigRec          RECORD          (3)
NAME            DIM             5
Inner           RECORD          (2) Like BaseRec
                RECORDEND
 
*................................................................
.
. Code start
.
                CALL            Main
                STOP

*................................................................
.
. NestFunc1 - Sample function
.
NestFunc1       LFUNCTION
LowCount        FORM            2
                ENTRY
Rec1            RECORD
M1              DIM             3
M2              FORM            2
                RECORDEND

                MOVE            LowCount to Rec1.M2
                ADD             "1" TO Rec1.M2
                MOVE            LowCount to Value

                FUNCTIONEND

*................................................................
.
. NestFunc - Sample function
.
NestFunc        LFUNCTION
Count           FORM            2
Value           FORM            ^
                ENTRY
CA1             DIM             3[0..1]

                MOVE            "123" to CA1[0]
                MOVE            "abc" to CA1[1]

                RETURN          IF ( Count = 16 )

                ADD             "1" To Count

                IF              ( Count > 12 )
                CALL            NestFunc1 Using Count
                ENDIF

                CALL            NestFunc Using Count, Value
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
                MOVE            "A1" TO CARRAY[1]
                MOVE            "C3" TO CARRAY(3)
                MOVE            "B2" TO CARRAY(2)
                MOVE            "D4" TO CARRAY(4)

                MOVE            "CX" TO BigRec(2).NAME
                MOVE            "5" to BigRec(3).Inner(2).Addr

                OPEN            FILE1, "c:\temp\junk.txt"
                OPEN            MFILE, "c:\temp\junk.txt"
                CALL            NestFunc Using Value, Value
                STOP
                FUNCTIONEND
.
.
.
