                LISTOFF
.
                %XREFOFF        ;DO NOT include in cross reference!!                   
.
                %IFNDEF         $PLBDBUG
$PLBDBUG        EQU             1   ;Flag that PLBDBUG is used.
*==============================================================================
. PLB METHOD support definitions
.
. Last Revision Date:  17 Nov 2020
.
. Revision History:
.
                %IFDEF          $PLBDBUG_HISTORY     
                                          
.:: 17 Nov 20 - Create PLB debugger definitions.                        :10.3A

                %ENDIF
*------------------------------------------------------------------------------
.
. Note:  Sections added to this include file are for user information
.  for an application.  This file can be modified and used to meet
.  the requirements for any user application.
.
*------------------------------------------------------------------------------

*------------------------------------------------------------------------------
.   RUNTIME                                                               10.3A
.
. Events:
.
.   none
.
. Properties:
.
.   none
.
. Methods:
.
.   DebugConnect    GIVING {nvar} USING *HostName={svarslit}:  
.                                       *Port={dnumnvar}:        Optional               
.                                       *Options={dnumnvar}      Optional
.   DebugLastError  GIVING {svar} USING *Options={dnumnvar}      Optional   
.   DebugRecv       GIVING {svar} USING *Timeout={dnumnvar}:     Optional
.                                       *Options={dnumnvar}      Optional 
.   DebugSend       GIVING {nvar} USING *Msg={svarslit}:                 
.                                       *Options={dnumnvar}      Optional 
.   DebugShutdown   GIVING {nvar} USING *Options={dnumnvar}      Optional

*
.
. Method Constants:
.
MSG_BREAK       FORM            "0100"
MSG_GO          FORM            "0101"
.MSG_SETBP      FORM            "0102"
.MSG_CLEARBP    FORM            "0103"
MSG_CLEARBP_ALL FORM            "0104"
MSG_GETSTATUS   FORM            "0105"
MSG_STEP_IN     FORM            "0106"
MSG_STEP_OVER   FORM            "0107"
MSG_STEP_OUT    FORM            "0108"
.MSG_GETVARS    FORM            "0109"
.MSG_GETLVARS   FORM            "0110"
MSG_GETMODS	FORM		"0111"
MSG_SHUTDOWN	FORM		"0112"
MSG_ACTIVATE_D3	FORM		"0113"
MSG_DEACT_D3	FORM		"0114"
.MSG_SETTP      FORM            "0115"
.MSG_CLEARTP    FORM            "0116"
MSG_CLEARTP_ALL FORM            "0117"
.MSG_SETVAR     FORM            "0118"
.MSG_SETIP      FORM            "0119"
.MSG_SETFLAG    FORM            "0120"
MSG_GETESTK	FORM		"0121"
.MSG_GETFILES	FORM		"0122"
.MSG_RUNTOIP    FORM            "0123"
MSG_GETGVARS    FORM            "0124"


*------------------------------------------------------------------------------
. SET BREAKPOINT message Record Definition 
. Fields separated by 0x7F 
.
MSG_SETBP       RECORD		DEFINITION
CMD             FORM            "0102"
MODULE          FORM            9
IP              FORM            10
COUNT           FORM            9
RESET           FORM            9
                RECORDEND

*------------------------------------------------------------------------------
. CLEAR BREAKPOINT message Record Definition 
. Fields separated by 0x7F
.
MSG_CLEARBP     RECORD		DEFINITION
CMD             FORM            "0103"
MODULE          FORM            9
IP              FORM            10
DISABLE         FORM            1 // 0 - Delete or 1 - Disable or 2 - Enable
                RECORDEND

*------------------------------------------------------------------------------
. GET one variable Record Definition 
. Fields separated by 0x7F 
.
MSG_GETVAR      RECORD		DEFINITION
MODULE          FORM            9
VADDR           FORM            10 // - indicates code space
ITYPE           FORM            9
                RECORDEND
.
. ITYPE Definitions
.
ITYPE_BYTE      CONST           "0"
ITYPE_NORM      CONST           "1"
.
. Special DIM types
.
ITYPE_LSTRING   CONST           "2"
ITYPE_FP	CONST           "3"
ITYPE_LP        CONST           "4"
ITYPE_MOREDATA  CONST           "1000" // +1 for each additional 100 bytes
.
. Special Object Types
.
ITYPE_PROP      CONST           "1000" // Add in PROP number

*------------------------------------------------------------------------------
. GET variables message Record Definition 
. Fields separated by 0x7F 
.
MSG_GETVARS     RECORD		DEFINITION
CMD             FORM            "0109"
COUNT           FORM            4
VAR             RECORD          (100) LIKE MSG_GETVAR
                RECORDEND
*------------------------------------------------------------------------------
. GET local variables message Record Definition 
. Fields separated by 0x7F 
.
MSG_GETLVARS    RECORD		DEFINITION
CMD             FORM            "0110"
STACKLV         FORM            4
COUNT           FORM            4
VAR             RECORD          (100) LIKE MSG_GETVAR
                RECORDEND
*------------------------------------------------------------------------------
. SET/TRACE one variable Record Definition 
. Fields separated by 0x7F 
.
MSG_PUTVAR      RECORD		DEFINITION
MODULE          FORM            9	 // 2000 Global, 1000+ Local with stack
VADDR           FORM            10       // - indicates code space
ITYPE           FORM            9        // type
DATA		DIM		250      // Data
                RECORDEND
.
GMODULE		CONST		"2000"
LMODULE		CONST		"1000"
.
*------------------------------------------------------------------------------
. SET TRACEPOINT message Record Definition 
. Fields separated by 0x7F 
.
MSG_SETTP       RECORD		DEFINITION
CMD             FORM            "0115"
OP          	FORM            2
VAR             RECORD          LIKE MSG_PUTVAR
                RECORDEND
.
. OP Definitions
.
TP_OP_EQUAL     CONST           "0"
TP_OP_GT        CONST           "1"
TP_OP_GE        CONST           "2"
TP_OP_LT        CONST           "3"
TP_OP_LE        CONST           "4"
TP_OP_NOT       CONST           "5"
TP_OP_EQUAL_NC  CONST           "6"
TP_OP_LIKE      CONST           "7"
TP_OP_LIKE_NC   CONST           "8"
TP_OP_CHANGE    CONST           "9"

*------------------------------------------------------------------------------
. CLEAR TRACEPOINT message Record Definition 
. Fields separated by 0x7F
.
MSG_CLEARTP     RECORD		DEFINITION
CMD             FORM            "0116"
MODULE          FORM            9
VADDR           FORM            10
DISABLE         FORM            1 // 0 - Delete or 1 - Disable or 2 - Enable
                RECORDEND
*------------------------------------------------------------------------------
. SET variable message Record Definition 
. Fields separated by 0x7F 
.
MSG_SETVAR     RECORD		DEFINITION
CMD             FORM            "0118"
VAR             RECORD          LIKE MSG_PUTVAR
                RECORDEND

*------------------------------------------------------------------------------
. SET IP message Record Definition 
. Fields separated by 0x7F 
.
MSG_SETIP       RECORD		DEFINITION
CMD             FORM            "0119"
IP              FORM            10      // Instruction Pointer
                RECORDEND

*------------------------------------------------------------------------------
. SET FLAG message Record Definition 
. Fields separated by 0x7F 
.
MSG_SETFLAG     RECORD		DEFINITION
CMD             FORM            "0120"
FLAG            DIM             1      // FLAG ( Zero Less Over Eos )
VALUE		FORM		1
                RECORDEND

*------------------------------------------------------------------------------
. Files message Record Definition 
. Fields separated by 0x7F 
.
MSG_FILES       RECORD		DEFINITION
CMD             FORM            "0122"
OPENONLY        FORM            1      // Only open files
CURRMOD		FORM		1      // Only current module files
                RECORDEND
*------------------------------------------------------------------------------
. RUN TO IP message Record Definition 
. Fields separated by 0x7F 
.
MSG_RUNTOIP     RECORD		DEFINITION
CMD             FORM            "0123"
IP              FORM            10      // Instruction Pointer
                RECORDEND

*------------------------------------------------------------------------------
. Runtime Status Record Definition 
. Returned by MSG_BREAK
. Fields separated by 0x7F
.
RUN_STATUS      RECORD          DEFINITION
FEOS            FORM            1       // Flags
FZERO           FORM            1       // 
FLESS           FORM            1       // 
FOVER           FORM            1       //
PICNT           FORM            5       // PI Count
MODULEMAX       FORM            9       // Max module load count
CS              FORM            4       // Code Stack Size
ES		FORM		4	// Event stack size
FUNCTIONID	DIM		3	// Local variables
MODULENUM       FORM            9       // MODULE Number
STACK           DIM             24(100) // Code Stack entry (IP;MODULE NUM;LOCAL VARS)
                RECORDEND

*------------------------------------------------------------------------------
. BREAKPOINT HIT message Record Definition 
. Returned by MSG_BREAK
. Fields separated by 0x7F
.
MSG_BP          RECORD		DEFINITION
CMD             FORM            4       // 500
IP              FORM            10      // Instruction Pointer
BPTYPE          DIM             1       // B Q
STATUS          RECORD          LIKE RUN_STATUS
                RECORDEND

*------------------------------------------------------------------------------
. PROGRAM STATUS message Record Definition 
. Returned by MSG_GETSTATUS
. Fields separated by 0x7F 
.
MSG_STAT        RECORD		DEFINITION
CMD             FORM            4       // 501
IP              FORM            10      // Instruction Pointer
PLCNAME         DIM             250     // Program Name
STATUS          RECORD          LIKE RUN_STATUS
                RECORDEND

*------------------------------------------------------------------------------
. PROGRAM UNTRAPPED ERROR message Record Definition 
. Returned like a breakpoint
. Fields separated by 0x7F 
.
MSG_ERREXIT     RECORD		DEFINITION
CMD             FORM            4        // 502
S$ERROR         DIM             60 
FILENAME        DIM             250      // File name in error
IP              FORM            10       // Instruction Pointer
PLCNAME         DIM             250      // Program Name
STATUS          RECORD          LIKE RUN_STATUS
                RECORDEND

*------------------------------------------------------------------------------
. PROGRAM UNTRAPPED ERROR message Record Definition 
. Fields separated by 0x7F
. PLaced on the clipboard
.
MSG_ERR         RECORD		
CMD             FORM            4        // 502
S$ERROR         DIM             60 
FILENAME        DIM             250      // File name in error
IP              FORM            10       // Instruction Pointer
PLCNAME         DIM             250      // Program Name
FEOS            FORM            1        // Flags
FZERO           FORM            1        // 
FLESS           FORM            1        // 
FOVER           FORM            1        //
PICNT           FORM            5        // PI Count
CS              FORM            4        // Code Stack
MODULE          DIM             250      // MODULE Name
STACK           DIM             261(100) // Code Stack entry (IP;MODULE)
                RECORDEND

*------------------------------------------------------------------------------
. GET one variable Record Definition 
. Fields separated by 0x7F 
.
MSG_DATAVAR     RECORD		DEFINITION
MODULE          FORM            9
VADDR           FORM            10       // - indicates code space
ITYPE           FORM            9        // Returned type
STATE		DIM		60       // State
DATA		DIM		250      // Data
                RECORDEND

*------------------------------------------------------------------------------
. PROGRAM variable data message Record Definition 
. Fields separated by 0x7F
.
MSG_DATAVARS    RECORD		DEFINITION
CMD             FORM            4         // 503
VARCOUNT        FORM            4         // Var Data Returne
VAR             RECORD          (100) LIKE MSG_DATAVAR
                RECORDEND

*------------------------------------------------------------------------------
. PROGRAM local variable data message Record Definition 
. Fields separated by 0x7F
.
MSG_DATALVARS   RECORD		DEFINITION
CMD             FORM            4         // 504
VARCOUNT        FORM            4         // Var Data Returned
STACKLV         FORM            4
VAR             RECORD          (100) LIKE MSG_DATAVAR
		RECORDEND

*------------------------------------------------------------------------------
. PROGRAM module data message Record Definition 
. Fields separated by 0x7F
.
MSG_DATAMOD     RECORD		DEFINITION
POS		FORM		4
MODULE          DIM             250      // MODULE Name
PLCNAME         DIM             250      // Program Name
TIMESTAMP	FORM		10	 // UDA Timestamp
		RECORDEND

MSG_DATAMODS    RECORD		DEFINITION
CMD             FORM            4        // 505
MODULEMAX       FORM            9       // Max module load count
DATA		RECORD		(101) LIKE MSG_DATAMOD
		RECORDEND

*------------------------------------------------------------------------------
. EVENT Stack data message Record Definition 
. Fields separated by 0x7F
.
MSG_DATAEVENT   RECORD		DEFINITION  
POS		FORM		4     
TYPE 		DIM 		20
MODULENUM       FORM            9       // MODULE Number 
EADDR           FORM            10
OADDR           FORM            10 
KEYSTATE	FORM		10
OBJECTID 	FORM 		8
RESULT	 	FORM 		11
CHAR 		DIM 		1
MOD 		FORM 		4
ARG1		DIM		200
		RECORDEND

MSG_DATAESTK    RECORD		DEFINITION
CMD             FORM            4        // 506
EVENTMAX        FORM            9        // Max event count
DATA		RECORD		(50) LIKE MSG_DATAEVENT
		RECORDEND

*------------------------------------------------------------------------------
. Files data message Record Definition 
. Fields separated by 0x7F
.
MSG_DATAFILE   RECORD		DEFINITION       
VADDR           FORM            10        // File variable address
TYPE		DIM		10        // File Type (i.e. FILE, AFILE, IFILE, PFILE, XFILE )
FILENAME        DIM             250       // The '.isi', '.aam' or '.txt' file opened
TXTNAME         DIM             250       // The '.txt' file name that is opened for AFILE or IFILE.
MODE		DIM		10        // SHARE, READ, EXCLUSIVE
MANAGED		DIM		1	  // Y - Managed file, N -Not managed
MODULE          FORM            9         // Module number
		RECORDEND

MSG_DATAFILES   RECORD		DEFINITION
CMD             FORM            4        // 507
FILEMAX         FORM            9        // Max FILE
DATA		RECORD		(100) LIKE MSG_DATAFILE
		RECORDEND

*------------------------------------------------------------------------------
. GET one variable Record Definition 
. Fields separated by 0x7F 
.
MSG_GDATAVAR    RECORD		DEFINITION
NAME          	DIM             32
VADDR           FORM            10       // 
TYPEDESC        DIM        	40       // Type description
STATE		DIM		60       // State
DATA		DIM		250      // Data
                RECORDEND

*------------------------------------------------------------------------------
. PROGRAM Global variable data message Record Definition 
. Fields separated by 0x7F
.
MSG_GBLVARS    RECORD		DEFINITION
CMD             FORM            4         // 508
VARCOUNT        FORM            4         // Var Data Returne
VAR             RECORD          (100) LIKE MSG_GDATAVAR
                RECORDEND

.
.
*------------------------------------------------------------------------------
                %ENDIF          ;End $PLBDBUG
.
                %XREFON         ;Restore cross reference state flag                   
.
                LISTON
