*=============================================================================
. PROGRAM: ADMSAMP1
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
.    Shows use of SUNADMIN_OPTION entry into SUNADMIN utility.
.
. INVOKED: ADMSAMP1
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
                KEYIN           *HD,"ENTER COMMAND LINE OPTIONS:",*IT,*RV,*DVEDIT=USERCMD
.
                CLEAR           OPT
.
                MOVE            USERCMD,S$CMDLIN
                CALLS           "SUNADMIN;SUNADMIN_OPTION" USING S$CMDLIN:
                                OPT:
                                RESULT:
                                ERRDATA:
                                ERRPTR
                IF              ( RESULT = 0 )
                DISPLAY         *HD,"-------------------------------------------------",*N:
                                "OPT.KEY........:",*LL,OPT.KEY,*N:  ;User Access Key String
                                "OPT.TYPE.......:",*LL,OPT.TYPE,*N:  ;Section Type
                                "OPT.LIST.......:",*LL,OPT.LIST,*N:  ;List option
                                "OPT.VERBOSE....:",*LL,OPT.VERBOSE,*N: ;Verbose option to show all
                                "OPT.PUBLIC.....:",*LL,OPT.PUBLIC,*N:  ;Public Key
                                "OPT.ADD........:",*LL,OPT.ADD,*N:  ;Add string
                                "OPT.DEL........:",*LL,OPT.DEL,*N:  ;Del string
                                "OPT.IPMASK.....:",*LL,OPT.IPMASK,*N:  ;IP MASK (nnn.nnn.nnn.nnn)
                                "OPT.COMMENT....:",*LL,OPT.COMMENT,*N: ;Comment string
                                "OPT.OUTPUT.....:",*LL,OPT.OUTPUT,*N:  ;OUTPUT file name
                                "OPT.CMDFILE....:",*LL,OPT.CMDFILE,*N: ;Command file name
                                "OPT.DEVICE.....:",*LL,OPT.DEVICE,*N  ;Output device
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
