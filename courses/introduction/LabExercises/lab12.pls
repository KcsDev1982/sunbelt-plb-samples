*---------------------------------------------------------------
.
. Program Name: Lab12.pls
. Description:  Introduction to PL/B Lab 12 program
.           
.
VALUE1          FORM            7.5
VALUE2          FORM            7.5
OPCODE          DIM             1
ANSWER          FORM            7.5
REPLY           DIM             1
.
                TRAP            QUIT IF ESCAPE
.
                LOOP
                DISPLAY         *P10:10,"Calculator":
                                *P10:12,VALUE1:
                                *P8:13,"_":
                                *P10:13,VALUE2:
                                *P10:14,"--------------":
                                *P10:15,ANSWER
*
.Acquire the values
.
                KEYIN           *P10:12,*DVRV=VALUE1,*P8:13,OPCODE,*P10:13,*DVRV=VALUE2
.
                SWITCH          OPCODE
                CASE            "+"
                ADD             VALUE2,VALUE1,ANSWER
                CASE            "-"
                SUB             VALUE2,VALUE1,ANSWER
                CASE            "*"
                MULT            VALUE2,VALUE1,ANSWER
                CASE            "/"
                DIV             VALUE2,VALUE1,ANSWER
                DEFAULT
                DISPLAY         *P10:17,"Invalid operation specified.",*W2
                CONTINUE
                ENDSWITCH
*
.Display the results
.
                KEYIN           *P10:15,*DV,ANSWER,"  ",REPLY;
                MOVE            ANSWER,VALUE1
                CLEAR           VALUE2,ANSWER
                REPEAT
*
.Exit the Program
.
QUIT
                STOP
