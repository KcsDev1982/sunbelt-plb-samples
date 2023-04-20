*---------------------------------------------------------------
.
. Program Name: Lab15.pls
. Description:  Introduction to PL/B Lab 15 program
.           
.
REPLY           DIM             1
CMDLINE         INIT            "dir /p"
.
                SHUTDOWN        "dir /p"
. SHUTDOWN ""
.
. SHUTDOWN "!dir /p"
.
. BEEP
.
.
                EXECUTE         "!LAB1.PLC",,FOREGROUND 
.
                KEYIN           *HD,*R,"Press any key... ",REPLY;

