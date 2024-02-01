*---------------------------------------------------------------
.
. Module Name: agenda_file.inc
. Description: File Layout Module
.
. Revision History:
.
.  Misc Files
.
FSA             INIT            "agenda"       // Name of AGENDA                                        
FSD             INIT            "agendad"      // Name of DIRFILE                        
FSG             INIT            "agendag"      // Name of GRAPH                          
FSH             INIT            "agendah"      // Name of HELPFILE                       
FSM             INIT            "agendam"      // Name of AGENDAM                        
FSN             INIT            "agendan"      // Name of NOTEFILE                                  
FSP             INIT            "agendap"      // Name of PLAN                           
FSP1            INIT            "agendap1"     // Name of PLAN1                          
FSU             INIT            "agendau"      // Name of AGENDAU                        
FSW             INIT            "agenda_work"  // Name of SCRATCHI  

AGENDA2         INIT            "agenda2"
AGENDAID        INIT            "agendaid"
AGDCONT         INIT            "agenda.cont"
AGCTRL          INIT            "agenda.ctrl"
.
.
.
SCRATCH         FILE            STATIC=2
SCRATCHI        IFILE           KEYLEN=35
+..............................................................................
.
.Data for the Counter Information File
.
.
.    Data File Name: agendac.data
.     Record Length: 8
.       File Format: Uncompressed
.
.
MAXUSRNO        FORM            6        1 - 6      // Number
MAXAPPT         FORM            2        7 - 8      // Sequential Counter
.               -------
.                  8  Bytes
.
CNTFILE         FILE            FIXED=8,UNCOMPRESSED
+..............................................................................
.
.Data for the User Information File
.
.
.    Data File Name: agendau.data
.          Aimdexed: 1-10, 11-16, 17-36, 43-47   (agendau.aam)
.     Record Length: 91
.       File Format: Uncompressed
.
.
USERID          DIM             10       1 - 10      // Identification Number
USRNO           FORM            6       11 - 16      // Number
USRNAME         DIM             20      17 - 36      // Name
USREXT          DIM             5       37 - 41      // Telephone Extension Number
LOFLAG          DIM             1       42           // Logged On Flag
UGROUP          DIM             5       43 - 47      // Group
STATDATE        DIM             6       48 - 53      // Status Date
STATTIME        DIM             8       54 - 61      // Status Time
STATFLAG        DIM             3       62 - 64      // Status Flag
STATMSG         DIM             17      65 - 81      // Status Comment
FMTIME          DIM             9       82 - 90      // First Message Date/Time
MEETFLG         FORM            1       91           // Meeting Notification Flag
.               -------
.                  91  Bytes
.
USRFILE         AFILE           FIXED=91,STATIC=2,UNCOMPRESSED
+..............................................................................
.
.Data for the Appointment File
.
.
.    Data File Name: agenda.data
.           Indexed: 1-17        (agenda.isi)
.          Aimdexed: 1-6, 44-98  (agenda.aam)
.     Record Length: 98
.       File Format: Compressed
.
.
.USRNO   FORM      6        1 -  6      // User Number
.YEAR    FORM      2        7 -  8      // Appointment Year
.JULDAY  FORM      3        9 - 11      // Appointment Julian Day
HOUR            FORM            2       12 - 13      // Appointment Starting Hour
MIN             FORM            2       14 - 15      // Appointment Starting Minute
COUNTER         FORM            2       16 - 17      // Sequential Counter
ENDHOUR         FORM            2       18 - 19      // Appointment Ending Hour
ENDMIN          FORM            2       20 - 21      // Appointment Ending Minute
STIME           DIM             8       22 - 29      // Appointment Starting Time (Formatted)
ETIME           DIM             8       30 - 37      // Appointment Ending Time (Formatted)
TPOS            FORM            2       38 - 39      // Day-Table Starting Position
NBLOCKS         FORM            2       40 - 41      // Number of 15 Minute Blocks Occupied
SECFLAG         DIM             1       42           // Confidential Apppointment Indicator
.                                         Space = Not Confidential
.                                           "*" = Confidential
TFLAG           DIM             1       43           // Tentative or Firm Appointment Flag
DATA            DIM             55      44 - 98      // Appointment Information
.                ------
.                  98  Bytes
.
AGENDA          IFILE           KEYLEN=17,VAR=98,COMPRESSED
AGENDAIM        AFILE           VAR=98,STATIC=2,COMPRESSED
+..............................................................................
.
.Data for the Appointment Graph File
.
.
.    Data File Name: agendag.data
.           Indexed: 1-11        (agendag.isi)
.     Record Length: 109
.       File Format: Uncompressed
.
.
.USRNO   FORM      6        1 -   6     // User Number
.YEAR    FORM      2        7 -   8     // Year
.JULDAY  FORM      3        9 -  11     // Julian Day
COUNT           FORM            2       12 -  13     // Number of Appointments
.
TABLE           INIT            "NNNNNNNNNNNNNNNNNNNNNNNN":    This Table Represents the 96
                                "NNNNNNNNNNNNNNNNNNNNNNNN":    15 Minutes Blocks in Each Day
                                "NNNNNNNNNNNNNNNNNNNNNNNN":    N = Not Occupied
                                "NNNNNNNNNNNNNNNNNNNNNNNN"     t = Tentative Appointment
.                                                 c = Conflicting Appointment
.                                             Space = Firm Appointment
.               -------                         006 = Adjoining Meetings
.                  109  Bytes                         Indicator
.
GRAPH           IFILE           KEYLEN=11,FIXED=109,UNCOMPRESSED
+..............................................................................
.
.Data for the Telephone Messages File
.
.
.    Data File Name: agendam.data
.           Indexed: 1-18        (agendam.isi)
.     Record Length: 387
.       File Format: Compressed
.
.
RECTYPE         FORM            1       1            // Record Type
.                                         1 = New Message
.                                         2 = Saved Message
.                                         3 = Deleted Message
.USRNO   FORM      6        2 -   7     // User Number
.YEAR    FORM      2        8 -   9     // Message Year
.JULDAY  FORM      3       10 -  12     // Message Julian Day
.HOUR    FORM      2       13 -  14     // Message Hour
.MIN     FORM      2       15 -  16     // Message Minute
SECOND          FORM            2       17 -  18     // Message Second
DATETAKN        DIM             11      19 -  29     // Date Taken
DOWTAKEN        DIM             9       30 -  38     // Day of Week Taken
TIMETAKN        DIM             8       39 -  46     // Time Taken
TAKENBY         DIM             12      47 -  58     // Message Take By
DATESAVD        DIM             11      59 -  69     // Date Saved                         025
.DATESAVD INIT    "t Corp.    "                                              025
DOWSAVED        DIM             9       70 -  78     // Day of Week Saved
TIMESAVD        DIM             8       79 -  86     // Time Saved
SAVEDBY         DIM             12      87 -  98     // Saved By
CALLER          DIM             30      99 - 128     // Caller's Name
CALRINFO        DIM             30      129 - 158    // Other Caller Information
PHONE           DIM             20      159 - 178    // Caller's Phone Number
FLAGS           DIM             8       179 - 186    // Call Flags
.SECFLAG DIM       1       187          // Confidential Flag
MSG1            DIM             50      188 - 237    // Message Part 1
MSG2            INIT            " 0...1...2...3...4...5...6...7...8...9..10..11..12"    *dsh
MSG3            INIT            " 7...8...9..10..11..12..13..14..15..16..17..18..19"    *dsh
MSG4            INIT            "12..13..14..15..16..17..18..19..20..21..22..23...0"    *dsh
..MSG2     DIM       50      238 - 287    // Message Part 2
..MSG3     DIM       50      288 - 337    // Message Part 3
..MSG4     DIM       50      338 - 387    // Message Note
.               --------
.                  387  Bytes
.
MESSAGE         IFILE           KEYLEN=18,VAR=387,STATIC=2,COMPRESSED
+..............................................................................
.
.Data for the Telephone Directory File
.
.
.    Data File Name: agendad.data
.          Aimdexed: 1-6,7-36,157-186 (agendad.aam)
.     Record Length: 186
.       File Format: Compressed
.
.
.USRNO   FORM      6        1 -   6     // User Number ( 0 = Public Number)
.NAME    DIM       30       7 -  36     // Entry Name
.NAME2   DIM       30      37 -  66     // Entry Name Continued
ADDRESS         DIM             30      67 -  96     // Entry Address
CITYST          DIM             30      97 - 126     // Entry City/State
ZIPCODE         DIM             10     127 - 136     // Entry Zipcode
.PHONE   DIM       20     137 - 156     // Entry Phone Number
NOTE            DIM             30     157 - 186     // Entry Note
.               -------
.                  186  Bytes
.
DIRFILE         AFILE           VAR=186,STATIC=2,COMPRESSED
+..............................................................................
.
.Data for the Notepad & Alarm File
.
.
.    Data File Name: agendan.data
.           Indexed: 1-20        (agendan.isi)
.          Aimdexed: 1-6, 38-93  (agendan.aam)
.     Record Length: 94
.       File Format: Compressed
.
.
.RECTYPE FORM      1       1            // Record Type
.                                         1 = Alarm Record
.                                         2 = Notepad Record
.USRNO   FORM      6        2 -  7      // User Number
.YEAR    FORM      2        8 -  9      // Year Entered
.JULDAY  FORM      3       10 - 12      // Julian Date Entered
.HOUR    FORM      2       13 - 14      // Hour Entered
.MIN     FORM      2       15 - 16      // Minute Entered
.SECOND  FORM      2       17 - 18      // Second Entered
.COUNTER FORM      2       19 - 20      // Line Number
.DATE    DIM       11      21 - 31      // Formatted Date
.STIME   DIM       8       32 - 39      // Formatted Time
.DATA    DIM       55      40 - 94      // Message
.               -------
.                  94  Bytes
.
NOTEFILE        IFILE           KEYLEN=20,VAR=94,COMPRESSED
NOTEFILA        AFILE           VAR=94,STATIC=2,COMPRESSED
+..............................................................................
.
.Data for the Planned Meetings File
.
.
.    Data File Name: agendap.data
.           Indexed: P1#*,1-17            (agendap.isi)
.                    P1#*,18-23,7-17,1-6  (agendap1.isi)
.     Record Length: 152
.       File Format: Uncompressed
.
.USRNO   FORM      6        1 -  6      // User Number
.YEAR    FORM      2        7 -  8      // Meeting Year
.JULDAY  FORM      3        9 - 11      // Meeting Julian Date
.HOUR    FORM      2       12 - 13      // Meeting Starting Hour
.MINUTE  FORM      2       14 - 15      // Meeting Starting Minute
.COUNTER FORM      2       16 - 17      // Meeting Number
.USRNO2  FORM      6       18 - 23      // Planning User Number
.ENDHOUR FORM      2       24 - 25      // Meeting Ending Hour
.ENDMIN  FORM      2       26 - 27      // Meeting Ending Minute
.DATE11  DIM       11      28 - 38      // Formatted Meeting Date
.STIME   DIM       8       39 - 46      // Formatted Meeting Starting Time
.ETIME   DIM       8       47 - 54      // Formatted Ending Time
.USRNAM  DIM       20      55 - 74      // Planning User Name
LOCATION        DIM             20      75 - 94      // Meeting Location
CONFIRM         DIM             3       95 - 97      // Confirmation Flag
.DATA    DIM       55      98 -152      // Meeting Information
.               ------
.                  152  bytes
.
PLAN            IFILE           KEYLEN=17,FIXED=152,UNCOMPRESSED
PLAN1           IFILE           KEYLEN=23,FIXED=152,UNCOMPRESSED
+..............................................................................
.
.Data for the Help File
.
.
.    Data File Name: agendah.data
.           Indexed: P1=*,2-5    (agendah.isi)
.     Record Length: 80
.       File Format: Compressed
.
.
.        INIT      "*"      1           // Header Record Identifier
HMENU           FORM            2        2  - 3      // Menu Number
HFUNCNO         FORM            2        4  - 5      // Function Number
.        FORM      2        6  - 7      // Number of Data Lines             *dsh
.        FORM      2        8  - 9      // Window Top Position
.        FORM      2        10 - 11     // Window Bottom Position
.        FORM      2        12 - 13     // Window Left Position
.        FORM      2        14 - 15     // Window Right Position
.
HELPDATA        DIM             80       1 - 80      // Help Information
.
.
HELPFILE        IFILE           KEYLEN=4,VAR=80,COMPRESSED
+..............................................................................
.
.Data for the Control File
.
.
.    Data File Name: agenda.cont
.     Record Length: 108
.       File Format: Uncompressed
.
.
.FLAG     DIM       1              // Space = System Up
.                                        * = System Down - Manual Restart Reqd
.                                        $ = System Down - Auto Restart Enabled
.USRNAME  DIM       20             // User Name
.DATE     DIM       11             // Date Taken Down
.TIME     DIM       8              // Time Taken Down
.DATE     DIM       11             // Date to be Restored
.TIME     DIM       8              // Time to be Restored
.YEAR     FORM      2              // Year to be Restored
.JULDAY   FORM      3              // Julian Day to be Restored
.HOUR     FORM      2              // Hour to be Restored
.MIN      FORM      2              // Minute to be Restored
.MSG      DIM       40             // Reason System Taken Down
.                 ------
.                   108  Bytes
.
.
CONTROL         FILE            FIXED=108,UNCOMPRESSED
.
. *** End ***
.
