*---------------------------------------------------------------
.
. Program Name: AGENDA2
. Description:  Shutdown Monitor Program
.
. Version 3.0.A
. Author: Bud Hutchison
.
. Revision History:
.
.
.
. VARIABLES SET BY AGENDA
.
UNTRAPER        DIM             *30            * Untrappable error field
ENTEROK         DIM             *2             * "ok" IF WE CHAINED IN FROM AGENDA
TIMESWCH        FORM            *"0"           * 0=12HR FORMAT; 1=24HR FORMAT
DATESWCH        FORM            *"0"           * 0=American; 1=European
MANAGESW        FORM            *"0"           * 0=Unmanaged; 1=Managed Files
EXITFLAG        FORM            *"0"           * Use an exit program? (0-No, 1-Yes)
EXITPROG        DIM             *26            * Name of possible exit program.
AGENDASW        FORM            *1             * Used by AGENDA4 (obsolete)
PASSWORD        INIT            "AGENDA"       * Restoration Password
.DATESW EQU 0
.TIMESW EQU 0
.
AGDCONT         INIT            "agenda.cont"
*.............................................................................
.
.Data for the Control File
.
FLAG            DIM             1              * Flag Byte
DOWNUSER        DIM             20             * User Name Taking Down the System
DOWNDATE        DIM             11             * Date Taken Down
DOWNTIME        DIM             8              * Time Taken Down
BACKDATE        DIM             11             * Estimated Back Date
BACKTIME        DIM             8              * Estimated Back Time
BACKYEAR        FORM            2              * Year to be Restored
BACKJDAY        FORM            3              * Julian Date to be Restored
BACKHOUR        FORM            2              * Hour to be Restored (24 Hour Format)
BACKMIN         FORM            2              * Minute to be Restored
MSG             DIM             40             * Reason System Taken Down
.
CONTROL         FILE            FIXED=108,UNCOMPRESSED
*
.Data Local to This Program
.
FUNCDESC        DIM             12             * Function Description
.
.Graphic Characters
.
ULC             INIT            "+"     // Upper Left Corner
URC             INIT            "+"     // Upper Right Corner
LLC             INIT            "+"     // Lower Left Corner
LRC             INIT            "+"     // Lower Right Corner
HE              INIT            "-"     // Horizontal Edge
HB              INIT            "-"     // Horizontal Bar
VE              INIT            "|"     // Vertical Edge
VB              INIT            "|"     // Vertical Bar
RA              EQU             ">"     // Right Arrow
.
REPLY           DIM             1              * Response Variable
RESTFLAG        FORM            1              * Restore Flag
SEQ             FORM            "-1"           * Sequential Access Variable
ZERO            FORM            "0"            * Value of Zero
ONE             FORM            "1"            * Value of One
DIM2            DIM             2              * Two Byte Alpha Work Variable
DIM3            DIM             3              * Three Byte Alpha Work Variable
DIM9A           DIM             9              * Date/Time Match Area
DIM9B           DIM             9              * Date/Time Match Area
DIM10           DIM             10             * Ten Byte Alpha Work Variable
YEARWORK        FORM            2              * Year Work Variable
JDAYWORK        FORM            3              * Julian Date Work Variable
MONWORK         FORM            2              * Month Work Variable
DAYWORK         FORM            2              * Date Work Variable
HOURWORK        FORM            2              * Hour Work Variable
MINWORK         FORM            2              * Minute Work Variable
SECOND          FORM            2              * Second Work Variable
NWORK1          FORM            3              * Five Byte Numeric Work Variable
NWORK2          FORM            3              * Two Byte Numeric Work Variable
NWORK3          FORM            3              * Three Byte Numeric Work Variable
INDEX           FORM            2              * Two Byte Numeric Work Variable
SPACZERO        INIT            " 0"
FOUR            FORM            "4"
TWELVE          FORM            "12"
THIRTEEN        FORM            "13"
NINETEEN        FORM            "19"           * Value of Nineteen
YEARPREFIX      FORM            "20"
THIRTY          FORM            "30"           * Value of Thirty
THIRTY1         FORM            "31"           * Value of Thirty-One
YEARLEN         FORM            3              * Year Length In Days
PYEARLEN        FORM            3              * Prior Year's Length In Days
DAYFEB          FORM            2              * Number of Days in February
TIME            DIM             8              * Time Variable
DATE            DIM             11             * Date Variable
RIGHT           EQU             066            * Move Right Value
LEFT            EQU             064            * Move Left Value
SPACE           INIT            " "            * Space Value
HPOS            FORM            2              * Horizontal Position
.
                INCLUDE         agenda2_tran.inc
.
*..............................................................................
                MATCH           "ok",ENTEROK
                GOTO            A2$CMD7 IF NOT EQUAL
.
.Open the Control File
.
START           TRAP            NOCONT IF IO
                OPEN            CONTROL,AGDCONT
                TRAPCLR         IO
.
                TRAP            EXIT IF F3
*
.Read the Record
.
                FILEPI          1;CONTROL
                READ            CONTROL,ZERO;FLAG,DOWNUSER,DOWNDATE,DOWNTIME:
                                BACKDATE,BACKTIME,BACKYEAR,BACKJDAY,BACKHOUR,BACKMIN,MSG
*
.Is the System Shutdown ?
.
                CMATCH          " ",FLAG
                GOTO            A2$CMD7 IF EQUAL
.
                CALL            CLOCKDT
                CMATCH          "$",FLAG            // Auto-Restart ?
                CALL            CHKSTART IF EQUAL   // Yes, Go See If Time
*
.Draw the Screen
.
                COUNT           NWORK1,DOWNUSER
                SETLPTR         DOWNUSER,NWORK1
.
                COUNT           NWORK1,MSG
                SETLPTR         MSG,NWORK1
.
                CMATCH          "$",FLAG
                GOTO            START1 IF EQUAL
                CLEAR           AUTOMSG
.
START1          CALL            CLOCKDT
                DISPLAY         *ES,*H 2,AG2TITNI,VERSION,*H 24,SSM:
                                *H 59,DATE,"  ",TIME:
                                *P1:2,ULC,*RPTCHAR HE:78,URC:
                                *P1:3,VB,*H 80,VE,*P1:4,VB,*H 80,VE:
                                *P1:5,VB,*H 80,VE,*P1:6,VB,*H 80,VE:
                                *P1:7,VB,*H 80,VE,*P1:8,VB,*H 80,VE:
                                *P1:9,VB,*H 80,VE,*P1:10,VB,*H 80,VE:
                                *P1:11,VB,*H 80,VE,*P1:12,VB,*H 80,VE:
                                *P1:13,VB,*H 80,VE,*P1:14,VB,*H 80,VE:
                                *P1:15,VB,*H 80,VE,*P1:16,VB,*H 80,VE:
                                *P1:17,VB,*H 80,VE,*P1:18,VB,*H 80,VE:
                                *P1:19,VB,*H 80,VE,*P1:20,VB,*H 80,VE:
                                *P1:21,VB,*H 80,VE,*P1:22,VB,*H 80,VE:
                                *P1:23,LLC,*RPTCHAR HB:78,LRC:
                                *P5:5,SS1NI,DOWNDATE:
                                *P2:7,SS2,DOWNTIME,SS3,*+,DOWNUSER,SS4,MSG,".":
                                *P2:9,SS5,AUTOMSG,SS6,BACKDATE:
                                SS7,BACKTIME,".":
                                *P5:12,SS8,SS9:
                                *P2:14,SS10,SS11:
                                *P2:16,SS12,SS13:
                                *P2:18,SS14NI,SS15:
                                *P2:20,SS16;
.
                BRANCH          RESTFLAG TO RESTORE1
*
.See What He Wants to Do
.
A2$CMD          DISPLAY         *HD,*EL,*H 2,FUNC1,*H 9,FUNC2,*H 19,FUNC3;
*
.Position to the Correct Function
.
A2$CMD1         LOAD            FUNCDESC BY FUNC FROM FUNC1,FUNC2,FUNC3
.
                MOVE            FUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            "2",NWORK2
                ADD             ONE,NWORK2
                RESET           CMDPOS,NWORK2
                MOVE            CMDPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
                DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                DISPLAY         *H HPOS,*HA -1,SPACE;
                IF              LEFT
                CMOVE           LEFT,REPLY
                ENDIF           032
                IF              RIGHT
                CMOVE           RIGHT,REPLY
                ENDIF           032
                GOTO            A2$CMD5 IF LESS
                GOTO            A2$CMD4 IF EOS
                DISPLAY         *H HPOS,*+,FUNCDESC;
*
.Check for a Direction Command
.
                CMATCH          RIGHT,REPLY
                GOTO            A2$CMD2 IF EQUAL
                CMATCH          SPACE,REPLY
                GOTO            A2$CMD2 IF EQUAL
                CMATCH          LEFT,REPLY
                GOTO            A2$CMD3 IF EQUAL
*
.Check for a Function Letter
.
                RESET           CMDLETS
                SCAN            REPLY,CMDLETS
                GOTO            A2$CMD1 IF NOT EQUAL
                MOVEFPTR        CMDLETS,FUNC
                GOTO            A2$CMD1
*
.Move Right to the Next Function
.
A2$CMD2         ADD             ONE,FUNC
                COMPARE         "4",FUNC
                GOTO            A2$CMD1 IF NOT EQUAL
                MOVE            ONE,FUNC
                GOTO            A2$CMD1
*
.Move Left to the Next Function
.
A2$CMD3         SUB             ONE,FUNC
                GOTO            A2$CMD1 IF NOT ZERO
                MOVE            "3",FUNC
                GOTO            A2$CMD1
*
.We Have a Selected Function
.
A2$CMD4         BRANCH          FUNC TO EXIT,RESTORE,REORG
.
                KEYIN           *B,*H 39,*EL,*DV,BRERR:
                                *DV,FUNC,*H 79,REPLY;
                GOTO            A2$CMD
*
.A Timeout Occurred
.
A2$CMD5         CALL            CLOCKDT
                DISPLAY         *P59:1,DATE,"  ",TIME;
.
                FILEPI          1;CONTROL
                READTAB         CONTROL,ZERO;*1,FLAG;
.
                CMATCH          " ",FLAG
                GOTO            A2$CMD6 IF EQUAL
                CMATCH          "$",FLAG
                CALL            CHKSTART IF EQUAL
                GOTO            A2$CMD1
*
.The System Has Been Restored
.
A2$CMD6         DISPLAY         *CLICK,*HD,*EL,SYSRSTNI;
.
A2$CMD7         TRAP            CFAIL IF CFAIL
                CHAIN           "agenda"
                COMPARE         ZERO,EXITFLAG             // Use the exit program?
                IF              EQUAL
                SHUTDOWN
                ELSE
                CHAIN           EXITPROG                  // Chain to the exit program.
                ENDIF
*..............................................................................
.
.Restore the System
.
RESTORE         KEYIN           *HD,*EL,*DV,SECPASS,*ESON,DIM10;
                GOTO            A2$CMD IF F5
.
                MATCH           DIM10,PASSWORD
                GOTO            A2$CMD IF LESS
                GOTO            A2$CMD IF NOT EQUAL
*
.Reset the Shutdown Byte
.
RESTORE1        FILEPI          1;CONTROL
                WRITE           CONTROL,ZERO;SPACE,DOWNUSER,DOWNDATE,DOWNTIME:
                                BACKDATE,BACKTIME,BACKYEAR,BACKJDAY,BACKHOUR,BACKMIN,MSG
                CLOSE           CONTROL
                GOTO            A2$CMD6
*..............................................................................
.
. Reorganize Function
.
REORG           KEYIN           *HD,*EL,*DV,SECPASS,*ESON,DIM10;
                GOTO            A2$CMD IF F5
.
                MATCH           DIM10,PASSWORD
                GOTO            A2$CMD IF LESS
                GOTO            A2$CMD IF NOT EQUAL
*
.Restore After Done ?
.
                CMOVE           NO,REPLY
                KEYIN           *HD,*EL,*DV,RESTSYST:
                                *HA -1,*RV,REPLY;
                GOTO            A2$CMD IF F5
.
                CMATCH          NO,REPLY
                GOTO            REORG1 IF NOT EQUAL
.
                COMPARE         ZERO,EXITFLAG             // Use the exit program?
                IF              EQUAL                      // No, use regular chain.
                CALL            INDEXALL
                SHUTDOWN
                ELSE
                CLEAR           REPLY
                CALL            INDEXALL
                CHAIN           EXITPROG                  //  Chain to the exit program.
                ENDIF
                SHUTDOWN
*
.Reorganize and Restore
.
REORG1          CLEAR           REPLY
                CALL            INDEXALL
                MOVE            ONE,RESTFLAG
                GOTO            START
*..............................................................................
.
.Exit the Program
.
EXIT            DISPLAY         *ES;
                CLOSE           CONTROL
                COMPARE         ZERO,EXITFLAG             // Use the exit program?
                IF              EQUAL
                SHUTDOWN
                ELSE
                CHAIN           EXITPROG                  // Chain to the exit program.
                ENDIF
*..............................................................................
.
.See if Time to Automatically Restart
.
.   Enter with:     BACKYEAR = Year to be Restored
.                   BACKJDAY = Julian Day to be Restored
.                   BACKHOUR = Hour to be Restored (24 Hour Format)
.                   BACKMIN  = Minute to be Restored
.
.                   YEARWORK = Current Year
.                   JDAYWORK = Current Julian Day
.                   HOURWORK = Current Hour (24 Hour Format)
.                   MINWORK  = Current Minute
.
.   Exits with:     If Not Time, Returns
.                   If Time, Exits to AGENDA
.
CHKSTART        PACK            DIM9A WITH BACKYEAR,BACKJDAY,BACKHOUR,BACKMIN
                PACK            DIM9B WITH YEARWORK,JDAYWORK,HOURWORK,MINWORK
.
                MATCH           DIM9A,DIM9B
                GOTO            RESTORE1 IF NOT LESS        // Restore the System
                RETURN
+..............................................................................
.
.Obtain the Current Time and Date
.
. Enter with:  TIMESWCH = 0  Non-Military Time (hh:mm ?m)
.                         1  Military Time (hh:mm)
.
.             DATESWCH  = 0  mm/dd/yy Format
.                         1  dd mmm 20yy Format
.
.  Exits with: JDAYWORK = Current Julian Day
.              YEARWORK = Current Year
.                  DATE = Formatted Date
.              HOURWORK = Current Hour
.               MINWORK = Current Minute
.                SECOND = Current Second
.                  TIME = Formatted Time
.
.
.Clock the Current Date
.
CLOCKDT         CLOCK           YEAR,DIM2
                MOVE            DIM2,YEARWORK
.
                CLOCK           DAY,DIM3
                MOVE            DIM3,JDAYWORK
.
                CALL            JULGREG
*
.Clock the Current Time
.
                CLOCK           TIME,TIME
                SETLPTR         TIME,2
                MOVE            ZERO,HOURWORK
                MOVE            TIME,HOURWORK
.?         MULT      ONE,HOURWORK
.
                RESET           TIME,4
                SETLPTR         TIME,5
                MOVE            ZERO,MINWORK
                MOVE            TIME,MINWORK
.?         MULT      ONE,MINWORK
.
                RESET           TIME,7
                SETLPTR         TIME,8
                MOVE            ZERO,SECOND
                MOVE            TIME,SECOND
.?         MULT      ONE,SECOND
+..............................................................................
.
. Format the Time
.
.  Enter with:  HOURWORK = Hour
.                MINWORK = Minute
.
.  Exits with:  TIME = Formatted Time
.
.               If TIMESWCH = 0, Format is hh:mm ?m
.               If TIMESWCH = 1, Format is hh:mm
.
.  Note: If HOURWORK = SEQ, then TIME will be set to "Note"
.
NICETIME        COMPARE         SEQ,HOURWORK
                GOTO            NICETIM1 IF NOT EQUAL
                MOVE            NOTEMSG,TIME
                RETURN
.
NICETIM1
..         IFEQ      TIMESW,0
                BRANCH          TIMESWCH OF N2ICETIM //  Military format
                MOVE            AM,DIM3
                MOVE            HOURWORK,INDEX
                COMPARE         TWELVE,INDEX
                GOTO            NICETIM2 IF LESS
                MOVE            PM,DIM3
.
NICETIM2        COMPARE         ZERO,INDEX
                GOTO            NICETIM3 IF NOT EQUAL
                MOVE            TWELVE,INDEX
                GOTO            NICETIM4
.
NICETIM3        COMPARE         THIRTEEN,INDEX
                GOTO            NICETIM4 IF LESS
                SUB             TWELVE,INDEX
.
NICETIM4        MOVE            MINWORK,DIM2
                REP             SPACZERO,DIM2
                MOVE            ":",REPLY
                PACK            TIME WITH INDEX,REPLY,DIM2,DIM3
                RETURN
..         XIF
.
..         IFEQ      TIMESW,1
N2ICETIM        MOVE            ":",REPLY
                PACK            TIME WITH HOURWORK,REPLY,MINWORK
                REP             SPACZERO,TIME
                RETURN
..         XIF
+..............................................................................
.
.Julian Date to Gregorian Date Conversion
.
.  Enter with:  JDAYWORK = JULIAN DAY
.               YEARWORK = YEAR
.
.               DATESWCH = 0  mm/dd/yy Format
.                          1  dd mmm 20yy Format
.
.  Exits with:  MONWORK  = Gregorian Month
.               DAYWORK  = Gregorian Day
.               YEARWORK = Year
.                 DATE   = Formatted Date (dd mmm 20yy)
.
.Convert the Date
.
JULGREG         MOVE            "28",NWORK3
                MOVE            ZERO,MONWORK
                MOVE            JDAYWORK,NWORK2
.
                MOVE            YEARWORK,NWORK1
                DIV             FOUR,NWORK1
                MULT            FOUR,NWORK1
                COMPARE         YEARWORK,NWORK1
                GOTO            JULGREG1 IF NOT EQUAL
                ADD             ONE,NWORK3
.
JULGREG1        ADD             ONE,MONWORK
                LOAD            NWORK1 BY MONWORK FROM THIRTY1,NWORK3,THIRTY1,THIRTY:
                                THIRTY1,THIRTY,THIRTY1,THIRTY1:
                                THIRTY,THIRTY1,THIRTY,THIRTY1
.
                SUB             NWORK1,NWORK2
                GOTO            JULGREG2 IF EQUAL
                GOTO            JULGREG1 IF NOT LESS
.
JULGREG2        ADD             NWORK1,NWORK2
                MOVE            NWORK2,DAYWORK
*
.Format the Date (mm/dd/yy)
.
                BRANCH          DATESWCH OF JGE
..         IFEQ      DATESW,0
                MOVE            "/",REPLY
                PACK            DATE WITH MONWORK,REPLY,DAYWORK,REPLY,YEARWORK
                REP             SPACZERO,DATE
                RETURN
..         XIF
*
.Format the Date (dd mmm 20yy)
.
..         IFEQ      DATESW,1
JGE             LOAD            DIM3 BY MONWORK FROM JAN,FEB,MAR,APR,MAY:
                                JUN,JUL,AUG,SEP,OCT,NOV,DEC
.
                PACK            DATE WITH DAYWORK,SPACE,DIM3,SPACE,YEARPREFIX,YEARWORK
..         XIF
.
                RETURN

*..............................................................................
.
.Error Routines
.
NOCONT          KEYIN           *B,*HD,*EL,*DV,NOCONT,REPLY;
                COMPARE         ZERO,EXITFLAG            // Use the exit program?
                IF              EQUAL
                SHUTDOWN
                ELSE
                CHAIN           EXITPROG                  // Chain to the exit program.
                ENDIF
.
CFAIL           KEYIN           *B,*HD,*EL,*DV,CHERRNI,REPLY;
                RETURN
.
NOUSERS         KEYIN           *B,*HD,*EL,*DV,NUERR,REPLY;
                NORETURN
                GOTO            A2$CMD

INDEXALL
//
//  Aamdexing the Users File
//
                AAMDEX          "agendau.data,agendau.aam,L91 -U,P1##'*',1-10,11-16,17-36,43-47"
//
//  Indexing & Ammdexing the Appointments File
//
                INDEX           "agenda.data,agenda.isi,L98 -1-17"
                AAMDEX          "agenda.data,agenda.aam,L98 -U,1-6,44-98"
//
// Indexing the Appointment Graph File
//
                INDEX           "agendag.data,agendag.isi,L109 -1-11"
//
//  Indexing the Messages File
//
                INDEX           "agendam.data,agendam.isi,L387 -1-18,S,V"
//
//  Aamdexing the Directory File
//
                AAMDEX          "agendad.data,agendad.aam,L186 -U,1-6,7-36,157-186"
//
//  Indexing & Aamdexing the Notepad & Alarms File
//
                AAMDEX          "agendan.data,agendan.aam,L94 -U,P1='2',2-7,40-94"
                INDEX           "agendan.data,agendan.isi,L94 -1-20"
//
//  Indexing the Meeting Planner File
//
                INDEX           "agendap.data,agendap.isi,L152 -1-17,P1##*"
                INDEX           "agendap.data,agendap1.isi,L152 -18-23,7-17,1-6,P1##*"
//
//  Indexing the Help File
//
                INDEX           "agendah.data -2-5,P1=*,S,V"
                RETURN
.
. *** End ***
.
