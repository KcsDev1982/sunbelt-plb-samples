+==============================================================================
. PROGRAM: ADMSAMP2
.
. SYSTEM:  UNIX/WINDOWS/MSDOS
.
.
. AUTHOR:  EDWARD R. BOEDECKER
.
.    Sunbelt Computer Systems, Inc.
.    Tyler, Texas   75701
.
. PURPOSE: Demonstrate user program access to SUNADMIN utility.
.    Shows use of SUNADMIN_CMD entry point into SUNADMIN utility.
.
. INVOKED: ADMSAMP2
.
*==============================================================================
.
OPT             RECORD
.
KEY             DIM             16         ;User Access Key String
TYPE            FORM            1         ;Section Type
LIST            FORM            1         ;List option
VERBOSE         FORM            1         ;Verbose option to show all
PUBLIC          DIM             17         ;Public Key
ADD             DIM             17         ;Add string
DEL             DIM             17         ;Del string
IPMASK          DIM             17         ;IP MASK string    (nnn.nnn.nnn.nnn)
COMMENT         DIM             40         ;Comment string
OUTPUT          DIM             250         ;OUTPUT file name
CMDFILE         DIM             250         ;Command file name
DEVICE          DIM             250         ;Output device
.
                RECORDEND
.
USERCMD         DIM             250
RESULT          FORM            5
ERRDATA         DIM             ^500
ERRPTR          FORM            3
.
START
.
                KEYIN           *HD,"ENTER COMMAND:",*IT,*RV,*DVEDIT=USERCMD
.
                CLEAR           OPT
.
                MOVE            USERCMD,S$CMDLIN
                CALLS           "SUNADMIN;SUNADMIN_CMD" USING S$CMDLIN:
                                RESULT:
                                ERRDATA:
                                ERRPTR
                IF              ( RESULT = 0 )
                DISPLAY         *HD,"-------------------------------------------------",*N:
                                "COMMAND COMPLETED OK!"
                ELSE
                DISPLAY         *HD,"-------------------------------------------------",*N:
                                "ERROR RESULT:",RESULT,*N:
                                *LL,USERCMD,*N,*HA=ERRPTR,"^<---Here!"
                TYPE            ERRDATA
                IF              NOT EOS
                DISPLAY         "ERROR DATA :",*LL,ERRDATA,*N
                ENDIF
                ENDIF
.
                GOTO            START
