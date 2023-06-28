. Redesigned Master Program    10 Nov 2006
.
. Some Globals we got from answer
.
GUI             FORM            %1 ; support GUI
AUser           DIM             %20 ; Authenticated User
CSCRW           FORM            %3 ; char screen width
CSCRH           FORM            %2 ; char screen Height
POSLEFT         FORM            %5 ; Left window Position
POSTOP          FORM            %5 ; Top Window Position
PLBPORT         DIM             %10 ; PLB_PORT from CLOCK INI
.
ts              DIM             20
TimeS           DIM             20
Result          FORM            2
ProgramName     DIM             76
.
cx              FORM            2 ; character screen center x
cy              FORM            3 ; character screen center y
.

MastWin         PLFORM          master.plf
.
. If there is no authenticated user, refuse to run. This will prevent users
. from bypassing the answer program.
.
                IF              ( AUser = "" )
                GETMODE         *GUI=GUI
                IF              ( GUI )
                ALERT           STOP,"Master Program Must be called from ANSWER",Result,""
                ELSE
                DISPLAY         "Master Program Must be called from ANSWER",*W5
                ENDIF
                STOP
                ENDIF
                IF              ( GUI )
.
. If we are running in graphical mode, load the interface.
.
                FORMLOAD        MastWin
.
. Load analog clock module if available.
. 
                EXCEPTSET       NoClock if CFAIL
                CALLS           "ACLOCK;ShowClock" using MastClockPanel,"1"
NoClock
                EXCEPTCLEAR     CFAIL
                SETPROP         MasterWin,VISIBLE=1,LEFT=POSLEFT,TOP=POSTOP
.
                SETFOCUS        MastProgName
                LOOP
                EVENTWAIT
                REPEAT
                ELSE            ... character mode...
.
. Find the middle of the screen.
. 
                CALC            cx=CSCRW/2
                CALC            cy=CSCRH/2
.
                LOOP
.
. show banner
.
                CLOCK           TIMESTAMP,ts
                EDIT            ts,TimeS,MASK="9999-99-99 99:99:99"
                DISPLAY         *SETSWALL=1:CSCRH:1:CSCRW,*BGCOLOR=*BLUE,*WHITE,*ES;
                DISPLAY         *SETSWALL=1:3:1:CSCRW,*BORDER:
                                *p=2:2,"Sunbelt Computer Software ":
                                *P=(CSCRW-21):2,TimeS:
                                *SETSWALL=3:CSCRH:1:CSCRW,*BORDER:
                                *RTKDD,*H=CSCRW,*LTKDD,*SHRINKSW:
                                *P=2:(CSCRH-3),*RED,"ESC to exit",*WHITE;
.
. Welcome messge
.
                DISPLAY         *p=(cx-10):(cy-7),"Welcome ",*ll,AUser
.
. Prompt
.
                DISPLAY         *P=(cx-15):(cy-5),"Enter Program Name:"
.
. Make sure we exit cleanly on interrup (CTRL-C) or escape
. 
                TRAP            EXIT IF INTERRUPT
                TRAP            EXIT IF ESCAPE
.
. display a box for the user to enter the name of the program
. 
                KEYIN           *SETSWALL=(cy-1):(cy+1):2:(CSCRW-1),*BORDER,*P=2:2:
                                *UC,*RPTCHAR="_":(CSCRW-4),*P=2:2,ProgramName
.
. CHAIN back to answer if "X"
.
                STOP            IF ( ProgramName = "X" )
.
. we want to provide a meaning for error if user didn't type program
. correctly so set the trap
.
                TRAP            CProgNotFound if CFAIL
                CHAIN           ProgramName
                REPEAT
                ENDIF

CProgNotFound
.
. beep and display a meaningful error message in red along with the runtime
. error code
. 
                BEEP
.
. this disply is only temporarily in the screen so we save the current
. subwindow state at the beginning, wait, then restore the original state
. 
                DISPLAY         *SAVESW,*SETSWALL=(cy-1):(cy+2):(cx-20):(cx+20),*BORDER:
                                *SHRINKSW,*BGCOLOR=*WHITE,*ES,*P=11:1,*RED,"Program Load Failed":
                                *P=1:2,S$ERROR$,*W=4:
                                *RESTSW
                RETURN

EXIT
                STOP            ; chain back to answer
.
. following routines are for the graphical interface
.
GoProgram
.
. get the name of the program the user entered
. 
                GETPROP         MastProgName,*Text=ProgramName
.
. catch the error if the progam can't be loaded
. 
                EXCEPTSET       GProgNotFound if CFAIL
.
. try to chain to specified program
. 
                CHAIN           ProgramName

GProgNotFound
.
. setup alert box parameters, the alert the user with the error
.
                PARAMTEXT       ProgramName,S$ERROR$,"",""
                ALERT           STOP,"^0: ^1",Result,"Program Load Error"
.
. clear the text in the edit field and put focus back so
. user can re-enter a program name.
. 
                SETPROP         MastProgName,TEXT=""
                SETFOCUS        MastProgName
                RETURN
