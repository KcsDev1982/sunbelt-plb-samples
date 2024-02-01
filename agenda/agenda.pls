*---------------------------------------------------------------
.
. Program Name: A G E N D A
. Description:  The Desk Management System
.
. Version 3.0.A
. Author: Bud Hutchison
.
. Revision History:
.
.
...............................................................................
.   When Modifying AGENDA please check the following.  This is not intended to
.   be a complete list of things to check, but is a list of some basic items.
.   Please feel free to add to this list.
...............................................................................
.
.                      ************* CAUTION ******************
.
.  LINE 23 SHOULD BE RESERVED FOR:
.      PAGE #
.      ALARM notification
.      MESSAGE notification
.      PLAN notification
.
...............................................................................
*
. REVISION LOG:
*

...............................................................................
+
.
.Program Compilation Equates
.
.
.  The following equates are designed for the Databus programmer interested
. in debugging or modifying the Agenda system. Each equate refers to a
. particular section of the program. The equates have three (3) meaningful
. values:
.             0 - The Normal Setting
.
.                  In this setting the section will compile and appear
.                  on any listings requested.
.
.             1 - No Compilation
.
.                  In this setting the section will be neither compiled or
.                  listed. Necessary labels will be supplied for compilation
.                  purposes, but all will simply return to the system menu.
.
.             2 - Compile, Without Listing
.
.                  In this setting, the section will compile, but the listing
.                  will be disabled. This will allow a complete program to be
.                  generated, but with a much smaller listing.
.
.     Note, that a value of One (No Compilation) is not valid for UDA,LOGON,
.  EXIT, or SUBS. The result would be a program which would not compile.
.
.
. For Normal use, all values should be Zero (0).
.
.
UDA             EQU             0              // User Data Area
LOGON           EQU             0              // Log on Module
CAL             EQU             0              // Calendar Module
MSG             EQU             0              // Telephone Messages Module
USER            EQU             0              // User Status Section
DIRECTRY        EQU             0              // Telephone Directory Module
NOTEPAD         EQU             0              // Notepad Module
MEETINGS        EQU             0              // Meeting Planner Module
ALARM           EQU             0              // Alarm Module
EXIT            EQU             0              // Log Off Module
SUBS            EQU             0              // Common Subroutines Module
                LISTOFF
.
                IFEQ            UDA,0
                LISTON
                XIF
*..............................................................................
.
.Common Program Data
.
*
. COMMON DATA AREA FOR 'AGENDA2'
.
UNTRAPER        DIM             *30            // Untrappable error field                  022
ENTEROK         INIT            *"ok"          // "ok" IF WE CHAINED IN FROM AGENDA      *dsh
TIMESWCH        FORM            *"0"           // 0=12HR FORMAT; 1=24HR FORMAT           *dsh
DATESWCH        FORM            *"0"           // 0=American; 1=European                 *dsh
MANAGESW        FORM            *"0"           // 0=Unmanaged; 1=Managed Files           *dsh
EXITFLAG        FORM            *"0"           // Use an exit program? (0-No, 1-Yes)       022
EXITPROG        DIM             *26            // Name of possible exit program.           022
.
.  This switch is set by the AGENDA4 program upon the user requesting to view
.    messages or meetings. The switch will cause the program to enter the
.    appropriate module, once the log-on sequence is complete.
.
AGENDASW        FORM            *1             // Entry Controller
.                                   0 - Normal Entry
.                                   1 - Proceed Directly to Messages
.                                   2 - Proceed Directly to Meeting Planner
.
.  End of common data area
...............................................................................
.
PASSWORD        INIT            "AGENDA"       // Security Password
.                                   1<4 = Meeting Deletion Password Known
.                                   1<3 = System Shutdown Password Known
.                                   1<2 = User Addition Password Known
.                                   1<1 = User Change Password Known
.                                   1<0 = User Deletion Password Known
.       IF ANY DATANAMES ARE INSERTED PRIOR TO 'PASSWORD'
.          AGENDAPASS WILL NEED TO BE MODIFIED TO HANDLE THIS CHANGE.
...............................................................................
.
.  Misc Data Names
.
.  Used in searches and must be maintained
.
DAY1            FORM            3
DAY2            FORM            3
DAY3            FORM            3
DAY4            FORM            3
DAY5            FORM            3
DAY6            FORM            3
DAY7            FORM            3
.
.  End of search data
.
.Cursor Movement Values
.
UP              EQU             070            // Cursor Up
DOWN            EQU             062            // Cursor Down
RIGHT           EQU             066            // Cursor Right
LEFT            EQU             064            // Cursor Left
CMDKEY          INIT            "\"            // Command Key
.
.Graphic Characters
.
ULC             INIT            "+" 	// Upper Left Corner              
URC             INIT            "+" 	// Upper Right Corner            
LLC             INIT            "+" 	// Lower Left Corner              
LRC             INIT            "+" 	// Lower Right Corner               
HE              INIT            "-" 	// Horizontal Edge                 
HB              INIT            "-" 	// Horizontal Bar                 
VE              INIT            "|" 	// Vertical Edge                    
VB              INIT            "|" 	// Vertical Bar                     
RA              EQU            ">" 	// Right Arrow
.
.Currently Logged On User's Information
.
CURRUSER        FORM            6              // User Number
CURRNAME        DIM             20             // User Name
CURRGRP         DIM             5              // User Group
CURRSTAT        DIM             3              // User Status
CURREXT         DIM             5              // User Phone                         
AYEAR           FORM            2              // Alarm Year
ADAY            FORM            3              // Alarm Julian Day
AHOUR           FORM            2              // Alarm Hour
AMIN            FORM            2              // Alarm Minute
ASEC            FORM            2              // Alarm Second
ADATE           DIM             11             // Alarm Date
ATIME           DIM             8              // Alarm Time
ALARMSG         DIM             40             // Alarm Message
.
.  The balance of the data names are in alphabetical order.
.
ADDRESS1        DIM             30             // Directory Print - 2nd Entry AddressAGENDA2         INIT            "agenda2"
AKEY1           DIM             23             // User File Name Key
AKEY2           DIM             9              // User File Group Key
ALRMFLG         FORM            "0"
BLANKS          INIT            "                              " (30 SPACES)
BLANK20         INIT            "                    "          // 20 Blanks for clearing. 
BN              INIT            " N"              Used to replace blanks with N's
CA              INIT            "A"
CALRINF1        INIT            "AGENDA                        "   // Must stay 30 char long.
CAPREP          INIT            "AaBbCcDdEeFfGgHhIiJjKkLlMm":
                                "NnOoPpQqRrSsTtUuVvWwXxYyZz"
CD              INIT            "D"
CE              INIT            "E"
C$              INIT            "$"
CI              INIT            "I"
CITYST1         DIM             30
CLICKSW         FORM            1              // Clicking Enabled/Disabled Switch
CMDTRAP         FORM            2              // Current ESCAPE Trap     
CN              INIT            "N"
COLON           INIT            ":"            // SEPARATES FILE EXTENSION:ENVIRONMENT
COMMA           INIT            ","
COUNTDWN        FORM            "0"           *** JLS COUNTDOWN VARIABLE
COUNTST         INIT            "COUNT="          JLS
CS              INIT            "S"
CTWO            INIT            "2"
CURDAY          FORM            "0"            // Column position of the current day.     
CY              INIT            "Y"
DASH            INIT            " - "
DASHES          INIT            " - - - - - - - - - - - - - - - - - - - -"
DATE            DIM             11             // Formatted Date Variable
DAY             FORM            2              // Currently Selected Day
DAYFEB          FORM            "28"           // Number of Days in Selected Year's February
DAYWORK         FORM            2              // Gregorian Day Work Variable
DIM1            DIM             1
DIM11           DIM             11
DIM15           DIM             15
DIM17           DIM             17
DIM2            DIM             2
DIM20           DIM             20
DIM20A          DIM             20             // Used to hold input name from user.       
DIM20B          DIM             20             // Used to hold username that is found.    
DIM25           DIM             25
DIM26           DIM             26
DIM3            DIM             3
DIM30           DIM             30
DIM3A           DIM             3
DIM40           DIM             40                                  
DIM6            DIM             6
DIM7            DIM             7
DIM9            DIM             9
DTLCOUNT        FORM            3              // Detail Record Counter
EHOURSAV        FORM            2              // Ending Hour Save Area
EIGHT           FORM            "8"
EIGHTEEN        FORM            "18"
EIGHTY          FORM            "80"
ELEVEN          FORM            "11"
EMINSAV         FORM            2              // Ending Minute Save Area
.EMPTY    INIT      "NNNNNNNNNNNNNNNNNNNNNNNN"                      
ENDDAY          FORM            2              // Number of Days in the Selected Month
ENDHOUR2        FORM            2              // Ending Hour Save Area
ENDMIN2         FORM            2              // Ending Minute Save Area
EOFSW           FORM            1              // End of File Encountered Indicator
EOSFLAG         FORM            1              // End of String Indicator
ERRMSG          DIM             75                                                       
F               INIT            "F"
F03             INIT            "03F"
F1HIT           FORM            1              // 1 ==> Redraw screen & force Highlighting
FIFTEEN         FORM            "15"
FIRSTTM         FORM            "0"           // First time through - stop Welcome 
FIVE            FORM            "5"
FIFTY           FORM            "50"
FIFTY2          FORM            "52"
FIFTY5          FORM            "55"
FLAG1           FORM            1              // Universal Flag Byte 1
FLAG2           FORM            1              // Universal Flag Byte 2
FLAG3           FORM            1              // Universal Flag Byte 3
FLAG4           FORM            1              // Universal Flag Byte 4
FLAG5           FORM            "0"
FORM1           FORM            1
FORTY           FORM            "40"
FORTY1          FORM            "41"
FORTY2          FORM            "42"
FORTY3          FORM            "43"
FORTY4          FORM            "44"
FORTY5          FORM            "45"
FORTY6          FORM            "46"
FORTY7          FORM            "47"
FORTY8          FORM            "48"
FORTY9          FORM            "49"
FOUR            FORM            "4"
FOURTEEN        FORM            "14"
FREQ            FORM            2              // Appointment Frequency
FSTDAY          FORM            "0"            // Column pos. of the 1st day of the month. 
GRAPHPOS        FORM            "2"            // Graph Starting Hour (See GRAPH Routine)
GRAPHSW         FORM            1              // Graph Forcing Flag
GROUPFLG        FORM            1              // Primary or Secondary Group Indicator
HILITE          FORM            "0"            // "1" ==> Highlight Calendar             
HLINE           FORM            2              // HELP Function line counter             
HOURSAV         FORM            2              // Starting Hour Save Area
HOURWORK        FORM            2              // Hour
HOURWRK1        FORM            2              // Hour Work Area
HPOS            FORM            2              // Horizontal Position
HPOS1           FORM            2              // Horizontal Position
HPOSDAY         FORM            2              // Horizontal Position of Selected Day
HPOSEND         FORM            2              // Vertical Position of Last Day of the Month
INDEX           FORM            2              // Numeric Work Variable
INQSW           FORM            1              // Inquiry Active Flag
JDAYWORK        FORM            3              // Julian Day Work Variable
JDAYWRK1        FORM            3              // Julian Day Work Variable
JDAYOLD         FORM            3              // Old Julian Day to compare rollover       
JULDAY          FORM            3              // Currently Selected Julian Date
KEY             DIM             23             // Key for Telephone Message File
KEY11           DIM             11             // Key for Appointment Graph File
KEY17           DIM             17             // Key for Appointment File
KEY17B          DIM             17             // Dummy key for appointment file.         
KEY18           DIM             18             // Key for Messages
KEY20           DIM             20             // Key for Notepad & Alarm File
KEY6            DIM             6              // Key for ???
KEY9            DIM             9              // Key for User File
KEYA            DIM             60
KEYB            DIM             35
KEYC            DIM             20
KEYD            DIM             20
KEYE            DIM             20
KEYF            DIM             20
KEYG            DIM             20
KEYH            DIM             20
KEYI            DIM             20
KEYJ            DIM             20
KEYK            DIM             20
KEYL            DIM             20
KEYM            DIM             20
KEYN            DIM             20
KEYO            DIM             20
KEYP            DIM             20
KEYPTR          FORM            2              // Saved Keys Pointer
KEYQ            DIM             20
KEYR            DIM             20
KEYWORK         DIM             20             // Scratch Key Area
KEYWORK2        DIM             20             // Scratch Key Area Two
L04             INIT            "04L"
LASTDAY         FORM            3              // Ending Day
LASTYR          FORM            2              // Ending Year
LINE            FORM            2              // Line Counter for Print Routines
LOOPFLG         FORM            "0"            // Flag to prevent going through loop twice 016
LOGONSW         FORM            1              // Logged On Switch
LOWA            INIT            "a"
LOWE            INIT            "e"
LOWP            INIT            "p"
MASKSW          FORM            1              // Mask Display Switch
MBOT            FORM            "21"
MDESC           DIM             20
MEETHOUR        FORM            2              // Meeting Hour
MEETMIN         FORM            2              // Meeting Minute          
MINSAV          FORM            2              // Starting Minute Save Area
MINWORK         FORM            2              // Minute
MINWRK1         FORM            2              // Minute Work Area
MLEFT           FORM            "02"
MON             FORM            2              // Currently Selected Month
MONSV           FORM            2              // Var to save month on entry              
MONTABLE        INIT            "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" // Month Table
MONTH           DIM             3
MONWORK         FORM            2              // Gregorian Month Work Variable
MPCOUNT         FORM            3              // Number of Attendees requested in PLAN
MRIGHT          FORM            "79"
MSGSW           FORM            1              // Message Switch
.                                 0-
.                                 1-
.                                 2-
.                                 3-
.                                 4-
.                                 5-Got to message from plan
MTOP            FORM            "03"
NEWUSRSW        FORM            "1"            // New User Switch
NINE            FORM            "9"
NINE9           FORM            "999999999"
NINETEEN        FORM            "19"
YEARPREFIX      FORM            "20"
NINTY9          FORM            "99"
NINTY99         FORM            "999"
NOMORE          FORM            1              // No Succeeding Records Flag
NOPREV          FORM            1              // No Precceeding Records Flag
NOTE1           DIM             30             // Directory Print - 2nd Entry Note
NUMWKS          FORM            "0"            // Number of weeks to advance day.          
NUMDAYS         FORM            "00"           // Number of days in month.                 
NWORK1          FORM            5
NWORKSV         FORM            5
NWORK2          FORM            5
NWORK2A         FORM            2
NWORK2B         FORM            2
NWORK3          FORM            5
ONE             FORM            "1"
OPENFLAG        INIT            000            // File Open Flag
.                                   1<6 = Appointment Files Open
.                                   1<5 = Message File Open
.                                   1<4 = Directory File Open
.                                   1<3 = Notepad Files Open
.                                   1<2 = Planning Files Open
.                                   1<1 = Help File Open
PAGE            FORM            3              // Page Counter for Print Routines
PAROP           INIT            " ("
PARCL           INIT            ")"
PERIOD          INIT            "."
PHONE1          DIM             20             // Directory Print - 2nd Entry Phone Number
PLANFLG         FORM            "1"                                                      
PLANFLAG        FORM            "0"            // Flag to check if entering from Plan.     
PRTSW           FORM            "0"                                                       
PRTFLAG         FORM            "0"            // Check if we have a Alternate PRT defined 
PRTNAME         DIM             26             // Name of alternate system printer         
PRINTREP        INIT            " XN ",031,"|",06,"|"
PYEARLEN        FORM            3              // Prior Year's Length in Days
REPLY           DIM             1              // Response Variable
REPLYH          DIM             1              // Response Variable
REQFLAG         FORM            1              // Entry Required Flag
ROFLAG          FORM            "1"            // Flag to detect if Day option is chosen.  
RODAY           FORM            3              // Julian day for reoccuring option.        
RULE1           INIT            "12a..1...2...3...4...5...6...7...8...9..10..11..12p"
RULE2           INIT            " 7...8...9..10..11..12p..1...2...3...4...5...6...7 "
RULE3           INIT            "12p..1...2...3...4...5...6...7...8...9..10..11..12a"
SAMEDAY         FORM            1              // Flag Passed Between CHECKDT & CHECKTM
SAVEDAY         FORM            3              // Place to save JULDAY              25N+
SAVEYR          FORM            2              // Place to save JULDAY              25N+
SCNDAY          FORM            "0"            // Column Pos. for second longest column.   
SDAYSAV         FORM            2              //   "
SEQ             FORM            "-1"           // Sequential Access Variable
SEVEN           FORM            "7"
SEVNTEEN        FORM            "17"
SEVENTY7        FORM            "77"
SEVENTY9        FORM            "79"
SIX             FORM            "6"
SIX0            FORM            "000000"
SIXTEEN         FORM            "16"
SIXTY           FORM            "60"
SLASH           INIT            "/"            // SEPARATES FILE NAME/EXTENSION
SMONSAV         FORM            2              // PRINT Routine 1st day of current week
SPACE           INIT            " "
SPACE2          INIT            "  "
SPACZERO        INIT            " 0"
SPLFLAG         FORM            1              // Printed Output is Being Spooled
SPLNAME         INIT            "123456789012.1234:12345678"   // Spool File Name
STAR            INIT            "*"
STARTDAY        FORM            3              // Starting Day
STARTYR         FORM            2              // Starting Year
SWITCH          FORM            1              // Universal Switch Byte
SWITCHI         FORM            "0"            //      0/1 => SCRATCHI IS CLOSED/OPEN
SYRSAV          FORM            2              //   "
SYSOPEN         FORM            "0"            // "1" IF SYSTEM FILES ARE OPEN
TDDATE          FORM            "0"                                                     
TEN             FORM            "10"
TERMTYPE        FORM            "1"            // Terminal Type Indicator
.                   0 - Advanced Video Features Available
.                   1 - Advanced Video Features Unavailable
THIRTEEN        FORM            "13"
THIRTY          FORM            "30"
THIRTY1         FORM            "31"
THIRTY2         FORM            "32"
THIRTY3         FORM            "33"
THIRTY4         FORM            "34"
THIRTY5         FORM            "35"
THIRTY6         FORM            "36"
THIRTY7         FORM            "37"
THIRTY8         FORM            "38"
THIRTY9         FORM            "39"
THREE           FORM            "3"
THREE65         FORM            "365"
THIRTY38        FORM            "338"
THRDAY          FORM            "0"            // Column pos for third longest column      016
TIME            DIM             8              // Formatted Time (hh:mm ?m)
TIMEDIF         FORM            "00"
TMFLAG          FORM            "0"            // Flag for transfer from MSG to DIR.       015
TOCOUNT         FORM            1              // Timeout Counter
TWELVE          FORM            "12"
TWENTY          FORM            "20"
TWENTY1         FORM            "21"
TWENTY2         FORM            "22"
TWENTY3         FORM            "23"
TWENTY4         FORM            "24"
TWENTY5         FORM            "25"
TWENTY6         FORM            "26"
TWENTY7         FORM            "27"
TWENTY8         FORM            "28"
TWENTY9         FORM            "29"
TWO             FORM            "2"
UGROUP1         DIM             5              // User's Group Work Variable
USRNAME1        DIM             20             // User Name Work Variable
USRNO1          FORM            6              // User Number Work Variable
USRNO2          FORM            6              // User Number Work Variable
USRNOSV         FORM            6
VPOS            FORM            2              // Vertical Position
VPOSDAY         FORM            2              // Vertical Position of Selected Day
VPOSEND         FORM            2              // Vertical Position of Last Day of the Month
WRKJUL          FORM            3              // Starting day of "current" week
WRKJULX         FORM            3              // Starting day of "current" week
WRKYR           FORM            2              // Starting year of "current" week
WRKYRX          FORM            2              // Starting year of "current" week
X01             INIT            "01X"
X02             INIT            "02X"
YEAR            FORM            2              // Currently Selected Year
YEAREND         FORM            2              // Graph Ending Year
YEARLEN         FORM            3              // Selected Year's Length in Days
YEARSTR         FORM            2              // Graph Starting Year
YEARWORK        FORM            2              // Year Work Variable
YEARWRK1        FORM            2              // Year Work Variable
.YEARWRK2 FORM      2              // Year Work Variable
ZERO5SP         INIT            "0     "
ZERO            FORM            "0"
ZIPCODE1        DIM             10             // Directory Print - 2nd Entry Zipcode
.
.  End Misc Data Names
.
.  Include the Tranlated data file.
.
                INCLUDE         agenda_tran.inc
.
. Include the file specifications.
.
		INCLUDE         agenda_file.inc

*..............................................................................
.
                LISTOFF
                IFEQ            LOGON,0
                LISTON
                XIF
+.............................................................................
.
.                       L O G - O N   S E Q U E N C E
..............................................................................
                DISPLAY         *SETSWALL=1:24:1:80
		MOVE		"ok" TO ENTEROK
                CALL            PROFILE            // GET TIME FORMAT FROM SYSTEM PROFILE 
*
.Check for a Shutdown System
.
                TRAP            START1 IF IO
                OPEN            CNTFILE,AGCTRL
                OPEN            CONTROL,AGDCONT,SHARE
.
                FILEPI          1;CONTROL
                READTAB         CONTROL,ZERO;REPLY
.
                CMATCH          SPACE,REPLY
                GOTO            START1A IF EQUAL
*
.System is Shutdown
.
START
                TRAP            CFAIL IF CFAIL
                CHAIN           AGENDA2
                COMPARE         ZERO,EXITFLAG             // Use the exit program?        
                IF              EQUAL                                  
                SHUTDOWN
                ELSE                                    
                CHAIN           EXITPROG                  // Chain to the exit program.    
                ENDIF                            
.
CFAIL
                KEYIN           *B,*HD,*EL,*DV,ERRAG2,*T10,REPLY;
                COMPARE         ZERO,EXITFLAG             // Use the exit program?         
                IF              EQUAL                                    
                SHUTDOWN
                ELSE            			                       
                CHAIN           EXITPROG                  // Chain to the exit program.    
                ENDIF                            
*
.Open the System Files
.
START1
                NORETURN
* SET TERMTYPE = 0 IF HIGHLIGHTING OK
START1A
                MOVE            ZERO,TERMTYPE
VIDSKIP
                BRANCH          SYSOPEN OF LOGON                                       
                MOVE            ONE,SYSOPEN                                           
                TRAP            TRAPIO GIVING ERRMSG IF IO   // Can't open a file  
.
ST1M
                OPEN            USRFILE,FSU,SHARE
                OPEN            NOTEFILE,FSN,SHARE
                OPEN            MESSAGE,FSM,SHARE
                TRAPCLR         IO
*
.Display the Signon
.
LOGON
                NORETURN
                TRAPCLR         IO                   // Clear general IO trap          
                TRAP            FASTEXIT IF F3                                        
                CALL            CLOCKDT
.
                DISPLAY         *CURSOFF,*HOFF,*ES,*N:
                                *N,*RPTCHAR CD:15:
                                *N,*RPTCHAR CD:6,*H 10,*RPTCHAR CD:10:
                                *N,*RPTCHAR CD:6,*H 13,*RPTCHAR CD:10:
                                *N,*RPTCHAR CD:6,*H 16,*RPTCHAR CD:8:
                                *N,*RPTCHAR CD:6,*H 19,*RPTCHAR CD:5:
                                *N,*RPTCHAR CD:6,*H 22,*RPTCHAR CD:3:
                                *N,*RPTCHAR CD:6,*H 24,CD:
                                *N,*RPTCHAR CD:6,*H 22,*RPTCHAR CD:3:
                                *N,*RPTCHAR CD:6,*H 19,*RPTCHAR CD:5:
                                *N,*RPTCHAR CD:6,*H 16,*RPTCHAR CD:8:
                                *N,*RPTCHAR CD:6,*H 13,*RPTCHAR CD:10:
                                *N,*RPTCHAR CD:6,*H 10,*RPTCHAR CD:10:
                                *N,*RPTCHAR CD:15:
                                *V 5,*H 43,ULC,*RPTCHAR HE:19,URC:
                                *N,*H 43,VE,DATEST,*H 51,DATE,*H 63,VE:
                                *N,*H 43,VE,*H 63,VE:
                                *N,*H 43,VE,TIMEST,*H 51,TIME,*H 63,VE:
                                *N,*H 43,LLC,*RPTCHAR HE:19,LRC
                BRANCH          FIRSTTM TO LOGON1
                MOVE            ONE TO FIRSTTM
                DISPLAY         *P31:3,CALLER1,SPACE,AGNINM,SPACE,VERSION;
.
LOGON1
*                                                                           
.Reset the function pointers to 1, to default to the 1st function in ring menus
.                                                                          
                MOVE            ONE,FUNC                   // Initialize Calendar menu.    
                MOVE            ONE,PFUNC                  // Initialize Cleanup menu.     
                MOVE            ONE,MFUNC                  // Initialize Message menu.     
                MOVE            ONE,MRFUNC                 // Initialize Review menu.      
                MOVE            ONE,CFUNC                  // Initialize User status menu.
                MOVE            ONE,TDFUNC                 // Initialize Directory menu.   
                MOVE            ONE,NFUNC                  // Initialize Notepad menu.    
                MOVE            ONE,AFUNC                  // Initialize Alarm menu.       
                MOVE            ONE,BFUNC                  // Initialize Planner menu.     
                MOVE            ONE,HFUNC                  // Initialize Help menu.        
                BRANCH          LOGONSW TO LOGON15
.
*
.Logging on Another User ?
.
                COMPARE         EIGHT,SFUNC
                GOTO            LOGON2 IF NOT EQUAL
                BRANCH          NEWUSRSW TO LOGON11
*
.Get the User ID From the ID File, If Present
.
LOGON2
                TRAP            LOGON11 IF IO
                OPEN            SCRATCH,AGENDAID,READ
                TRAPCLR         IO
*
.Read Through the ID File
.
                MOVE            ZERO,DTLCOUNT
LOGON3
                READ            SCRATCH,SEQ;USERID,DIM26
                GOTO            LOGON4 IF OVER
.
                CMATCH          SPACE,USERID
                GOTO            LOGON3 IF EQUAL
                GOTO            LOGON3 IF EOS
                MATCH           HILITEST,USERID
                GOTO            LOGON3B IF NOT EQUAL          // Check for printer.        
                MOVE            ONE,HILITE           // Remember we got highlighting req.
                GOTO            LOGON3
*
.Check for System printer.
.
LOGON3B
                MATCH           COUNTST,USERID              
                IF              EQUAL
                MOVELPTR        USERID TO SEVEN
                RESET           USERID TO SEVEN
                MOVE            USERID,COUNTDWN
                RESET           USERID
                GOTO            LOGON3
                ENDIF
                MATCH           SYSTPRT,USERID                // Do we have a system prt?  
                GOTO            LOGON3A IF NOT EQUAL          // No, continue reading.    
                MOVE            ONE,PRTFLAG                   // Yes, move one to flag.   
                MOVE            DIM26,PRTNAME                 // Save off the name.       
                GOTO            LOGON3                        // Continue reading.       
*
.Save the User Identification Number
.
LOGON3A
                ADD             ONE,DTLCOUNT
                STORE           USERID BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI,KEYJ      // Five more USERID's  
                COMPARE         TEN,DTLCOUNT
                GOTO            LOGON3 IF NOT EQUAL
*
.We Have Either All ID's or 10 of 'Em
.
LOGON4
                CLOSE           SCRATCH
                TRAPCLR         IO
.
                BRANCH          TERMTYPE OF LOGON4A   // CAN'T DO HIGHLIGHTING           
                BRANCH          HILITE OF LOGON4A     // ONE MEANS DO HILITE IF POSSIBLE
                MOVE            ONE,TERMTYPE          // IF WE'RE HERE, WE DON'T WANT IT
.
LOGON4A
                MOVE            ONE,KEYPTR
                COMPARE         ONE,DTLCOUNT          // Null User ID File
                GOTO            LOGON11 IF LESS
                GOTO            LOGON9 IF EQUAL       // Only One...
*
.Show 'Em the List of User's
.
                MOVE            ZERO,NEWUSRSW
                MOVE            ONE,KEYPTR
                DISPLAY         *V 11;
*
.Get a User's Key
.
LOGON5
                CALL            LOAD07                                             
                PACK            KEYWORK WITH X01,USERID
*
.Look Up the User's Name
.
                FILEPI          1;USRFILE
                READTAB         USRFILE,KEYWORK;*17,USRNAME
                GOTO            LOGON6 IF NOT OVER
.
                MOVE            INVID TO USRNAME                                  
*
.Show 'Em the Name
.
LOGON6
                COMPARE         KEYPTR,FIVE                                              
                IF              LESS                   // Show all 10 User Names.            
                ADD             FIVE,KEYPTR                                              
                DISPLAY         *P 57:KEYPTR,USRNAME  // Display 2nd column.                 
                SUB             FIVE,KEYPTR                                              
                ELSE            
                DISPLAY         *H 33,USRNAME        // Display 1st column.               
                ENDIF           
                ADD             ONE,KEYPTR
                COMPARE         KEYPTR,DTLCOUNT
                GOTO            LOGON5 IF NOT LESS
*
.All the User's are on the Screen; Allow Selection
.
                CALL            BANNER01
                DISPLAY         *P60:21,ENTUSR,*HOFF:
                                *HD,*EL,UPDWNCMD;
                MOVE            ONE,KEYPTR
.
LOGON7
                MOVE            KEYPTR,VPOS
                TRAP            LOGON11 IF F5                                             
                COMPARE         KEYPTR,FIVE         // Allow cursor to move to all     
                IF              LESS                // User id's.                           
                ADD             FIVE,VPOS           // Move to 2nd Column.                 
                KEYIN           *P55:VPOS,RA,*H 55,*T60,*+,*RV,REPLY:
                                *HA -1," ";                                              
                SUB             FIVE,VPOS                                                
                ELSE           
                ADD             TEN,VPOS            // Move to 1st column.
                KEYIN           *P31:VPOS,RA,*H 31,*T60,*+,*RV,REPLY:
                                *HA -1," ";                                               
                ENDIF          
                IF              UP                                                           
                CMOVE           UP,REPLY                                                  
                DISPLAY         *HA -1,SPACE,SPACE;                                      
                ENDIF          
                IF              DOWN                                                               
                CMOVE           DOWN,REPLY                                             
                DISPLAY         *HA -1,SPACE,SPACE;                                    
                ENDIF          
                GOTO            LOGON10 IF LESS                                         
                TRAPCLR         F5                                                       
                GOTO            LOGON9 IF EOS
.
                CMATCH          070,REPLY
                GOTO            LOGON8 IF EQUAL
                CMATCH          SPACE,REPLY
                GOTO            LOGON7D IF EQUAL
                CMATCH          062,REPLY
                GOTO            LOGON7 IF NOT EQUAL
*
.Move Down a User
.
LOGON7D
                ADD             ONE,KEYPTR
                COMPARE         KEYPTR,DTLCOUNT
                GOTO            LOGON7 IF NOT LESS
                MOVE            ONE,KEYPTR
                GOTO            LOGON7
*
.Move Up a User
.
LOGON8
                SUB             ONE,KEYPTR
                GOTO            LOGON7 IF NOT ZERO
                MOVE            DTLCOUNT,KEYPTR
                GOTO            LOGON7
*
.We Have the Selected User
.
LOGON9
                CALL            LOAD07                                            
                PACK            KEYWORK WITH X01,USERID
.
                FILEPI          1;USRFILE
                READ            USRFILE,KEYWORK;USERID,CURRUSER,CURRNAME,CURREXT,LOFLAG:
                                CURRGRP,STATDATE,STATTIME,CURRSTAT,STATMSG,FMTIME,MEETFLG
                CALL            BADID IF OVER                                   
                GOTO            LOGON14
.                                                  
BADID
                KEYIN           *B,*HD,*EL,*DV,INVID2,*DV,USERID,". ",REPLY;
                GOTO            LOGON11
*
.A Timeout Occurred
.
LOGON10
                CLEAR           FUNCDESC
                MOVE            TWO,FLAG1
                GOTO            LOGON7
*
.Allow Entry of the ID Number
.
LOGON11
                NORETURN
                CALL            BANNER               // Display banner line
                MOVE            TEN TO MTOP
                MOVE            SIXTEEN TO MBOT
                MOVE            THIRTY5 TO MLEFT
                MOVE            EIGHTY TO MRIGHT
                CALL            SETSW01
                DISPLAY         *HD,*EL,*P1:17,*EL,PLUSR;
                BRANCH          TERMTYPE OF LOGON12   // CAN'T DO HIGHLIGHTING           
                BRANCH          HILITE OF LOGON12     // ONE MEANS DO HILITE IF POSSIBLE
                MOVE            ONE,TERMTYPE          // IF WE'RE HERE, WE DON'T WANT IT
.
LOGON12
                KEYIN           *P32:17,*T60,*RV,*ESON,USERID,*ESOFF;
                GOTO            LOGON13 IF LESS
                IF              EOS
                COMPARE         ZERO,EXITFLAG     	// Use the exit program?       
                IF              EQUAL            	// No, just stop.               
                STOP
                ELSE            			// Yes,                       
                CHAIN           EXITPROG        	// Chain to the exit program.    
                ENDIF           			// End of If.                    
                ENDIF
*
.See If We Know Who He Is
.
                PACK            KEYWORK WITH X01,USERID
.
                FILEPI          1;USRFILE
                READ            USRFILE,KEYWORK;USERID,CURRUSER,CURRNAME,CURREXT,LOFLAG:
                                CURRGRP,STATDATE,STATTIME,CURRSTAT,STATMSG,FMTIME,MEETFLG
                GOTO            LOGON14 IF NOT OVER
*
.Invalid User ID
.
                DISPLAY         *B,*H 50,INVID,*W;
                GOTO            LOGON11
*
.A Timeout Occurred
.
LOGON13
                CLEAR           FUNCDESC
                MOVE            TWO,FLAG1
                COMPARE         ONE,FLAG2
                GOTO            LOGON12 IF NOT EQUAL
                DISPLAY         *HD,*EL;                                               
                GOTO            LOGON12
*
.Log the Known User Onto the System
.
LOGON14
                FILEPI          1;USRFILE
                UPDATAB         USRFILE;*42,STAR
*
.Display the Current User
.
LOGON15
                CALL            BANNER
                DISPLAY         *P1:17,*EL:
                                *HON,*P35:21,CURRNAME,*HOFF;
                TRAP            FASTEXIT IF F3                                        
*
.Ensure that the First Message Time is Set Correctly
.
                MOVE            CURRUSER,DIM6
                CALL            FMTIME
*
.If the User is Logged Out or Not Available, Allow Change
.
                BRANCH          LOGONSW TO LOGON17
                CMATCH          CI,CURRSTAT
                GOTO            LOGON16 IF NOT EQUAL
*
.If the User is Logged In But the Date is Different, Allow Change
.
                CALL            CLOCKDT
                MOVE            DATE,KEY6            // Truncate for good MATCH
                MATCH           KEY6,DATE
                GOTO            LOGON17 IF EQUAL
*
.See if He Wants to Refresh the Status
.
LOGON16
                KEYIN           *CLICK,*HD,*EL,*DV,CHSTAT:
                                *HA -1,*T60,REPLY,*HD,*EL;
                CMATCH          NO,REPLY                                                
                GOTO            LOGON17 IF EQUAL
*
.Update the Status
.
.LO17                                                               
                CALL            CLOCKDT
                MOVE            IN,CURRSTAT
                MOVE            DATE,STATDATE
                MOVE            TIME,STATTIME
                CLEAR           STATMSG
.
                FILEPI          1;USRFILE
                UPDATAB         USRFILE;*48,STATDATE,STATTIME,CURRSTAT,STATMSG
*
.Set Up the User's Alarm Information
.
LOGON17
                CALL            FATIME
*
.Check for Special Entry Points
.
                COMPARE         ZERO,AGENDASW
                GOTO            LOGON18 IF EQUAL
.
                MOVE            CURRUSER,USRNO
                MOVE            CURRNAME,USRNAME
.
                COMPARE         TWO,AGENDASW
                GOTO            PLAN IF EQUAL
.
                MOVE            ONE,MSGSW
                GOTO            MESSAGE
*
.See if Any New Messages
.
LOGON18
                MOVE            CURRUSER,USRNO
                MOVE            CURRNAME,USRNAME
                MOVE            ONE,LOGONSW
                CLEAR           FUNCDESC
                MOVE            ZERO,FLAG1
+..............................................................................
.
.                          S Y S T E M   M E N U
...............................................................................
.
.
.Restore the Original User
.                                     
                TRAP            FASTEXIT IF F3                                           
                TRAP            QUITKEY IF F27                                          
                TRAP            QUITKEY IF ESCAPE                                        
                MOVE            ZERO,INQSW
                MOVE            CURRUSER,USRNO
                MOVE            CURRNAME,USRNAME
*
.Reset the Selected Date
.
                CALL            CLOCKDT
                MOVE            JDAYWORK,JULDAY
                MOVE            JDAYWORK,JDAYOLD       // For rollover comparison          
                MOVE            YEARWORK,YEAR
                MOVE            MONWORK,MON
                MOVE            DAYWORK,DAY
*
.Draw the Screen
.
                CALL            SHOWAPTS                     // Display next appointment.  
                DISPLAY         *P1:21,*HON,*EL,VISAGNI,VERSION:
                                *H 35,CURRNAME,PAROP,CURRSTAT,PARCL:
                                *H HELPPSNI,HELPSTNI,*HOFF,*HD,*EL,LRCMD; // CURRSTAT added to display band.
.
.See If He Has Any Alarms or Meetings
.
                CLEAR           FUNCDESC
                MOVE            ZERO,FLAG1
                CALL            CHKALRM
                DISPLAY         *HD,*EL,LRCMD;           // redisplay line 24 message                                       
*
.Display the Available Functions
.
MENU1
                MOVE            ZERO,FLAG2
                DISPLAY         *P2:22,SFUNC1,SFUNC2,SFUNC3:
                                SFUNC4,SFUNC5,SFUNC6:
                                SFUNC7,SFUNC8,SFUNC9;
*
.Position to the Correct Function
.
MENU2
                LOAD            FUNCDESC BY SFUNC FROM SFUNC1,SFUNC2:
                                SFUNC3,SFUNC4,SFUNC5,SFUNC6,SFUNC7,SFUNC8,SFUNC9
.
                MOVE            SFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           SFPOS,NWORK2
                MOVE            SFPOS,DIM2
                MOVE            DIM2,HPOS
*
.Allow Entry of a Command
.
                DISPLAY         *PHPOS:22,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              LEFT                                                             
                CMOVE           LEFT,REPLY                                                
                DISPLAY         SPACE,*+,FUNCDESC;                                       
                GOTO            MENU21                                                 
                ENDIF           032
                IF              RIGHT                                                             
                CMOVE           RIGHT,REPLY                                             
                DISPLAY         SPACE,*+,FUNCDESC;                                       
                GOTO            MENU21                                                    
                ENDIF           032
                GOTO            MENU1 IF F26
                GOTO            MENU8 IF F1
                GOTO            MENU8 IF F2                                              
                GOTO            MENU8 IF F4                                             
                GOTO            MENU7 IF F5
                GOTO            MENU7 IF F9                                             
                GOTO            MENU6 IF LESS
                GOTO            MENU5 IF EOS
                DISPLAY         *HA -1,SPACE,*+,FUNCDESC;
*
.Check for a Direction Command
.
MENU21          CMATCH          066,REPLY                                               
                GOTO            MENU3 IF EQUAL
                CMATCH          064,REPLY
                GOTO            MENU4 IF EQUAL
                CMATCH          SPACE,REPLY
                GOTO            MENU3 IF EQUAL
*
.Check for a Function Letter
.
                RESET           SLETS
                SCAN            REPLY,SLETS
                IF              NOT EQUAL                   // Add lower case option.          
                RESET           SLETS2                                       
                SCAN            REPLY,SLETS2                                      
                GOTO            MENU2 IF NOT EQUAL                               
                MOVEFPTR        SLETS2,SFUNC                                     
                GOTO            MENU2                                             
                ENDIF           026
                MOVEFPTR        SLETS,SFUNC
                GOTO            MENU2
*
.Move Right to the Next Function
.
MENU3
                ADD             ONE,SFUNC
                COMPARE         TEN,SFUNC
                GOTO            MENU2 IF NOT EQUAL
                MOVE            ONE,SFUNC
                GOTO            MENU2
*
.Move Left to the Previous Function
.
MENU4
                SUB             ONE,SFUNC
                GOTO            MENU2 IF NOT EQUAL
                MOVE            NINE,SFUNC
                GOTO            MENU2
*
.We Have a Selected Function
.
MENU5
                BRANCH          SFUNC TO CALENDAR,MESSAGE,USERS:
                                TD$CMD,NOTEPAD,ALARM,PLAN,EXIT,EXIT
                CALL            INTERR
*
.A Timeout Occurred
.
MENU6
                CALL            CLOCKDT                 
                DISPLAY         *P51:6,DATE              // Redisplay the Date for rollover 
                DISPLAY         *P51:8,TIME,*P1:21       
                MOVE            CURRUSER,DIM6            // Move current user.             
                CALL            FMTIME                   // Find the message time.       
                CALL            CHKALRM
                CALL            SHOWAPTS                 // Display next appointment.     
                DISPLAY         *HD,*EL,LRCMD;           // redisplay line 24 message
                BRANCH          FLAG2 TO MENU1
                GOTO            MENU2
*
.Help Requested
.
MENU7
                MOVE            ONE,HMENU
                MOVE            SFUNC,HFUNCNO
                CALL            HELP
                GOTO            LOGON
*
.Turn Clicking On or Off as Needed
.
MENU8
                BRANCH          CLICKSW TO MENU9
                MOVE            ONE,CLICKSW
                GOTO            MENU2
.
MENU9
                MOVE            ZERO,CLICKSW
                GOTO            MENU2
                LISTOFF
.
.User Exit Section Control
.
                IFEQ            EXIT,0
                LISTON
                XIF
+..............................................................................
.
.                     P R O G R A M   T E R M I N A T I O N
...............................................................................
.
. F3 Fast Exit requested.                                                   
.                                                                            
FASTEXIT        RESET           REPLY                                                    
                CMOVE           YES,REPLY                                               
                DISPLAY         *CLICK,*HD,*EL,FASTEX,REPLY;                            
                KEYIN           *T10,*HA -1,*UC,*RV,REPLY;                               
                GOTO            LOGON IF F5                                               
                CMATCH          YES,REPLY                                                 
                GOTO            EXIT IF EQUAL                                           
                CMATCH          NO,REPLY                                                 
                GOTO            LOGON IF EQUAL                                           

TRAPIO
                DISPLAY         *HD,*HON,*EL,ERRFILE,DIM25,*W5,*HOFF                     
                DISPLAY         ERRMSG;                                                  
                COMPARE         ZERO,EXITFLAG      	// Use the exit program?         
                IF              EQUAL         		// No, just stop.               
                STOP
                ELSE            			// Yes,                          
                CHAIN           EXITPROG          	// Chain to the exit program.  
                ENDIF           			// End of If.                    
.
*
.Exit Requested
.
EXIT
                MOVE            ZERO,CMDTRAP                                         
                TRAP            LOGON IF ESCAPE                              
                TRAP            LOGON IF F27                                 
                TRAP            LOGON IF F5
                DISPLAY         *CURSOFF,*SETSWALL=1:24:1:80,*HOFF,*HD,*EL,AGENEND;
.
                COMPARE         ZERO,LOGONSW
                GOTO            EXIT4 IF EQUAL    Not Logged On
*
.Read the Current User's Record
.
                PACK            KEY9 WITH X02,CURRUSER
.
                FILEPI          3;USRFILE
                READTAB         USRFILE,KEY9;*11,USRNO,*48,STATDATE,STATTIME,STATFLAG
                CALL            INTERR IF OVER
.
                MOVE            ZERO,CMDTRAP                                          
                TRAP            LOGON IF ESCAPE                                       
                TRAP            LOGON IF F27                                         
EXIT1
                CMOVE           CE,REPLY                                             
                DISPLAY         *CLICK,*HD,*EL,EXSTAT,EXSTAT2,REPLY;                 
                KEYIN           *T10,*HA -1,*RV,REPLY;                               
                GOTO            LOGON IF F5                                         
                CMATCH          CE,REPLY                                            
                GOTO            EXIT2 IF EQUAL                                      
                CMATCH          LOWE,REPLY                                          
                GOTO            EXIT2 IF EQUAL                                     
                CMATCH          SPACE TO REPLY
                GOTO            EXIT2 IF EOS
                REP             EXOPT,REPLY
                MOVE            ZERO,INDEX
                MOVE            REPLY,INDEX
                COMPARE         ONE,INDEX
                GOTO            EXIT1 IF LESS
                COMPARE         FOUR,INDEX
                GOTO            EXIT1 IF NOT LESS

                LOAD            STATFLAG FROM INDEX OF OUT,IN,NA
                MOVE            STATFLAG TO DIM3A
*
.Get the Status Message
.
                KEYIN           *HD,*EL,*DV,MSGST,*RPTCHAR "_":17,*H 10,*IT,STATMSG;
                DISPLAY         *IN,*H 10,STATMSG;
                GOTO            EXIT1 IF F5
.
EX18
                CALL            CLOCKDT              // Get current time & date       
                MOVE            DATE,STATDATE
                MOVE            TIME,STATTIME
*
.Log the User Off the System
.
                FILEPI          1;USRFILE
                UPDATAB         USRFILE;*42,SPACE,*48,STATDATE,STATTIME,DIM3A,STATMSG
                GOTO            EXIT3
*
.User pressed the Return key
.
EXIT2
                FILEPI          1;USRFILE
                UPDATAB         USRFILE;*42,SPACE
*
.If Spooling, Remind the User of His Printed Data
.
EXIT3
                COMPARE         ZERO,SPLFLAG
                GOTO            EXIT4 IF EQUAL
.
                SPLCLOSE
                MOVE            ZERO,SPLFLAG
*
.If the Log On Function, Allow Another User
.
EXIT4
                COMPARE         EIGHT,SFUNC
                GOTO            EXIT5 IF NOT EQUAL
.
                MOVE            ZERO,LOGONSW
                GOTO            LOGON
*
.Terminate the Program
.
EXIT5
                DISPLAY         *SETSWALL=1:24:1:80,*HOFF,*ES;
                COMPARE         ZERO,EXITFLAG    	// Use the exit program?        
                IF              EQUAL            	               
                SHUTDOWN
                ELSE            			                         
                CHAIN           EXITPROG         	// Chain to the exit program.   
                ENDIF           			                 
                LISTOFF
.
.Calendar Module Control
.
                IFEQ            CAL,1
CALENDAR        GOTO            LOGON
                XIF
                IFNE            CAL,2
                LISTON
                XIF
                IFNE            CAL,1
                INCLUDE         agenda_cal.inc
                LISTOFF
                XIF
*
.Telephone Messages Module Control
.
                IFEQ            MSG,1
MESSAGE         GOTO            LOGON
                XIF
                IFNE            MSG,2
                LISTON
                XIF
                IFNE            MSG,1
                INCLUDE         agenda_msg.inc
                LISTOFF
                XIF
*
.User Display Module Control
.
                IFEQ            USER,1
USERS           GOTO            LOGON
                XIF
                IFNE            USER,2
                LISTON
                XIF
                IFNE            USER,1
                INCLUDE         agenda_user.inc
                LISTOFF
                XIF
*
.Telephone Directory Module Control
.
                IFEQ            DIRECTRY,1
TD$CMD          GOTO            LOGON
                XIF
                IFNE            DIRECTRY,2
                LISTON
                XIF
                IFNE            DIRECTRY,1
                INCLUDE         agenda_dir.inc
                LISTOFF
                XIF
*
.Desk Notepad Module Control
.
                IFEQ            NOTEPAD,1
NOTEPAD         GOTO            LOGON
                XIF
                IFNE            NOTEPAD,2
                LISTON
                XIF
                IFNE            NOTEPAD,1
                INCLUDE         agenda_note.inc
                LISTOFF
                XIF
*
.Meeting Planner Module Control
.
                IFEQ            MEETINGS,1
MPADDA24
PLAN2
PLAN            GOTO            LOGON
                XIF
                IFNE            MEETINGS,2
                LISTON
                XIF
                IFNE            MEETINGS,1
                INCLUDE         agenda_plan.inc
                LISTOFF
                XIF
*
.Desk Alarms Module Control
.
                IFEQ            ALARM,1
ALARM           GOTO            LOGON
                XIF
                IFNE            ALARM,2
                LISTON
                XIF
                IFNE            ALARM,1
                INCLUDE         agenda_alr.inc
                LISTOFF
                XIF
*
.Subroutine Module Control
.
                LISTOFF
                IFEQ            SUBS,0
                LISTON
                XIF
                INCLUDE         agenda_subs.inc
                LISTON
QK1             STOP                                                   
*                                                                          
.POSITION TO EXIT                                                           
.                                                                           
QUITKEY         MOVE            NINE,SFUNC                                             
                GOTO            MENU1                                                 
.
. *** End ***
.
