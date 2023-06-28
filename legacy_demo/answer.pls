.===============================================================================
. Redisgned Answer program    25 Feb 2019
. 
. 15 Sep 14 - Added trap logic to catch failed create of PLBDemousers
.     files.
. 25 Feb 19 - Modified to allow this 'answer' program to be compiled and :10.1B
.     executed using a Unix/Linux PLB runtime. These changes  :10.1B
.     unexpected U15 error.           :10.1B
.
.------------------------------------------------------------------------
. Some Globals we will want in other programs
.
GUI             FORM            %1
AUser           DIM             %20
CSCRW           FORM            %3 ; char screen width
CSCRH           FORM            %2 ; char screen Height
.
. GETINFO System data
.
SYSINFO         DIM             602
SysInfoRec      RECORD
OsType          FORM            1
OsVer           FORM            1
KBType          DIM             2
KBStype         DIM             2
FkeyType        DIM             2
PenBased        FORM            1
Mouse           FORM            1
MBtns           FORM            1
MBtnSwap        FORM            1
SWidth          FORM            4
SHeight         FORM            4
CName           DIM             15
UName           DIM             20
WinDir          DIM             260
WinSdir         DIM             260
clrbits         FORM            2
HWND            INTEGER         4
Inst            INTEGER         4
Taskbar         FORM            1
TaskbarT        FORM            4
TaskbarB        FORM            4
TaskbarL        FORM            4
TaskbarR        FORM            4
                RECORDEND
.
Users           IFILE
User            RECORD
Name            DIM             20 ; user name
PW              DIM             16 ; password
WS              DIM             15 ; last login location
LTime           DIM             14 ; login time
                RECORDEND
.
$7F             INIT            0x7F
ts              DIM             20
TimeS           DIM             20
DM12            DIM             12
Buff            DIM             80
Result          FORM            2
Reply           DIM             1
Web             FORM            1
VERSION         DIM             50
RTVER           DIM             5
SKIP1           DIM             1
RUNTIME         DIM             9
.
cx              FORM            2 ; character screen center x
cy              FORM            3 ; character screen center y
.
. Macro to encode the password stored on disk.
.
EncodePW        MACRO
                MOVE            User.PW,DM12
                ENDSET          DM12
                EXTEND          DM12,12
                RESET           DM12
                ENCODE64        DM12,User.PW
                MEND

MWin            PLFORM          answer.plf
.-------------------------------------------------------------------------------
. Open or Create Users file
.
                FINDFILE        "PLBDemoUsers.isi"
                IF              EQUAL
                OPEN            Users,"PLBDemoUsers.isi"
                ELSE
                TRAP            NoCreate if IO
                PREP            Users,"PLBDemoUsers","PLBDemoUsers","1-20","65"
                TRAPCLR         IO
                ENDIF
.-------------------------------------------------------------------------------
. Check for character mode runtime
.
                GETMODE         *GUI=GUI
                GOTO            CVER_Unix IF (GUI = 0)
.
. Get System Information that could be useful later...
.
                GETINFO         SYSTEM,SYSINFO   //GUI ONLY!!
                UNPACK          SYSINFO,SysInfoRec
.
. check windows console.
. 
                CLOCK           VERSION,VERSION
                UNPACK          VERSION,RTVER,SKIP1,RUNTIME
                MATCH           "PLBCON",RUNTIME
                GOTO            cver IF EQUAL
                MATCH           "PLBWEBSV",RUNTIME
                IF              EQUAL
                MOVE            "1",Web
                ENDIF
.
. Run in GUI MODE
.
                WINHIDE
                FORMLOAD        MWin
.
. Try to load Clock loadmod, ignore it if it fails
.
                EXCEPTSET       NoClock if CFAIL
                CALLS           "ACLOCK;ShowClock" using AnsClockPanel,"1"
NoClock
                EXCEPTCLEAR     CFAIL
                CLEAR           S$ERROR$
.
. Initialize objects
.
USERCOUNT       FORM            4
                CHOP            SysInfoRec.CName
                IF              ( SysInfoRec.CName = "" )
                MOVE            "Undefined",SysInfoRec.CName
                ENDIF
                SETPROP         AnsCName,TEXT=SysInfoRec.CName
                SETPROP         AnsUserName,TEXT=SysInfoRec.UName
                SETFOCUS        AnsUserName
.-------------------------------------------------------------------------------
. Wait for user
.
                LOOP
                EVENTWAIT
                REPEAT

GoMaster
                IMPLODE         Buff,$7F,AnsUserName,AnsPassword,AnsCName
                EXPLODE         Buff,$7F,User
                CALL            CheckPass
                IF              NOT EQUAL
                ALERT           AnswerWin;STOP,"Invalid Password",Result
                SETPROP         AnsPassword,TEXT=""
                SETFOCUS        AnsPassword
                RETURN
                ENDIF
                GOTO            Login
.
. Could not Open or Create the authorization file.
.
NoCreate
                KEYIN           "Unable to create the PLBDemoUsers file. ",Result
                SHUTDOWN        ""
*=====================================================================
. Running in character mode
.
CVER
                TEST            SysInfoRec.CName  ;Get Computer and User Name
                IF              EOS
CVER_Unix                       //Entry point for Unix/Linux because
                                //'GETINFO' instruction is GUI only!
.
. get info from Unix Environment
.
                MOVE            "HOSTNAME",ts
                CLOCK           ENV,ts
                SCAN            "=",ts
                IF              ZERO                10.1B
                BUMP            ts
                MOVE            ts,User.WS
                ELSE            10.1B
                MOVE            "Unknown", User.WS //HOSTNAME keyword NOT found!!    10.1B
                ENDIF           10.1B  
.
                MOVE            "USER",ts
                CLOCK           ENV,ts
                SCAN            "=",ts
                BUMP            ts
                MOVE            ts,User.Name
.
                ELSE
                MOVE            SysInfoRec.CName,User.WS
                MOVE            SysInfoRec.UName,User.Name
                ENDIF
.
. get screen dimensions
. 
                CLOCK           PORT,ts
                RESET           ts,4
                UNPACK          ts,CSCRH,CSCRW
.
. display banner
.
                CALL            ShowBanner
.
. calculate the center of the screen
.
                CALC            cx=CSCRW/2
                CALC            cy=CSCRH/2
.
. User prompts
.
                DISPLAY         *P=(cx-15):(cy-3),"Worstation: ",*ll,User.WS
                DISPLAY         *H=(cx-15),"Username  : "
                DISPLAY         *H=(cx-15),"Password  : "
.
. Traps to exit runtime cleanly
.
                TRAP            EXIT IF INTERRUPT
                TRAP            EXIT IF ESCAPE
.
                LOOP
.
. Note: *IT does not expire.  It's used to change the 
.       legacy behavior ( CAPS OFF = ALL CAPS )
.       of the caps lock key to modern bahavior. ( CAPS ON = ALL CAPS )
.
. We are using *DVEDIT for the user name because we want to use
. the system logged in user as the default user.
.
                KEYIN           *IT,*P=(cx-3):(cy-2),*LC,*DVEDIT=User.Name
                IF              ESCAPE
                SHUTDOWN
                ENDIF
                CHOP            User.Name
                CONTINUE        if ( User.Name = "" ) ;No empty or null user names
                KEYIN           *P=(cx-3):(cy-1),*EL,*ESON,*LC,User.PW,*ESOFF
                CONTINUE        if ( User.PW = "" ) ;No empty or null passwords
                CALL            CheckPass
                UNTIL           EQUAL
                BEEP
                DISPLAY         *SAVESW,*SETSWALL=(cy-1):(cy+1):(cx-10):(cx+10),*BORDER:
                                *SHRINKSW,*BGCOLOR=*WHITE,*RED,*ES,"Invalid Password":
                                *W=4,*RESTSW,*SHRINKSW
                REPEAT
                DISPLAY         *IN;   ;Turn off Shift Inversion.
...
LOGIN
.
. Get the current time and update the password file to log
. last log in time
. 
                CLOCK           TIMESTAMP,ts
                MOVE            ts,User.LTime
                UPDATE          Users;User
.
. move the user name to the global authenticated user variable
. so other progams can check this
. 
                MOVE            User.Name,AUser
.
. chain to master
. 
                STOP
.
EXIT
                SHUTDOWN

ShowBanner
.
. Get the current time and format it for displa
.
                CLOCK           TIMESTAMP,ts
                EDIT            ts,TimeS,MASK="9999-99-99 99:99:99"
.
. setup the screen with colors and borders all based on screen information
. retrieved from clock earlier in the program.
. 
                DISPLAY         *SETSWALL=1:CSCRH:1:CSCRW,*BGCOLOR=*BLUE,*WHITE,*ES;
                DISPLAY         *SETSWALL=1:3:1:CSCRW,*BORDER:
                                *p=2:2,"Sunbelt Computer Software":
                                *P=(CSCRW-21):2,TimeS:
                                *SETSWALL=3:CSCRH:1:CSCRW,*BORDER:
                                *RTKDD,*H=CSCRW,*LTKDD,*SHRINKSW:
                                *P=2:(CSCRH-3),*RED,"ESC to exit",*WHITE;
                RETURN

*-------------------------------------------------------------------------------
.
CheckPass       FUNCTION
                ENTRY
DM12            DIM             12
PW              DIM             12
                ENDSET          User.Name
                EXTEND          User.Name,20
                RESET           User.Name
.
. we only save 12 character password so truncate anything extra
. and remove trailing spaces
.
                MOVE            User.PW,PW
                CHOP            PW    ;Remove trailing spaces
                READ            Users,User.Name;User ;Use name as key to password file
                IF              NOT OVER
                DECODE64        User.PW,DM12  ;Decode the saved password
                CHOP            DM12   ;Remove trailing spaces
                RETURN          IF ( PW != DM12 ) ;Return NOT Equal for bad password
                ELSE
                IF              ( GUI )   ;Notify user of new record
                ALERT           AnswerWin;NOTE,"Added New User",Result
                ELSE
                DISPLAY         "Added New User",*W=2
                ENDIF
                ENCODEPW        ;don't store plain text password in file
                WRITE           Users;User  ;Save User/Password info to disk
                ENDIF
                SETFLAG         EQUAL   ;Password was good
                FUNCTIONEND
