. program to display an analog clock...
. By Matthew Lake
.
. Rev history
. Jul 26 2010 - added descriptive comments
. 
.  Program illustrates Higher math functions ( sin/cos )
.  APICALL
.  SHAPE
.  LINE 
.  TIMER
.  EXCEPTSET
.
.-----borrowed from brian jackson
GWL_EXSTYLE     INTEGER         4,"0xFFFFFFEC"
WS_EX_LAYERED   INTEGER         4,"0x00080000"
LWA_ALPHA       INTEGER         4,"0x00000002"
attributes      INTEGER         4
bytOpacity      INTEGER         1,"128"
byteZero        INTEGER         1,"0"
hWnd            INTEGER         4

getWindowLong   PROFILE         !user32:
                                GetWindowLongA:
                                int4:
                                int4:
                                int4

setWindowLong   PROFILE         !user32:
                                SetWindowLongA:
                                int4:
                                int4:
                                int4:
                                int4

setLayeredWindowAttributes PROFILE !user32:
                                SetLayeredWindowAttributes:
                                int4:
                                int4:
                                int1:
                                int1:
                                int4

#mwin           WINDOW
$CLOSE          CONST           "5"
$RESIZE         CONST           "17"
                WINHIDE
.
. create a window that will contain the clock
.
                CREATE          #mwin=1:300:1:300,TOPMOST=1
.
. make the window transparent using APIs
.
                GETPROP         #mwin,hwnd=hwnd
                APICALL         GetWindowLong giving attributes using hwnd,GWL_EXSTYLE
                OR              WS_EX_LAYERED into attributes
                APICALL         setWindowLong using hWnd,GWL_EXSTYLE,attributes
                APICALL         setLayeredWindowAttributes using hWnd,byteZero,bytOpacity,LWA_ALPHA
.
. hook up desired events
.
                EVENTREG        #mwin,$CLOSE,term
                EVENTREG        #mwin,$RESIZE,ShowClock
.
. create the clock on the window
.
                CALL            ShowClock using #mwin
.
. show the window AFTER everything is created and ready to display.
.
                ACTIVATE        #mwin
.
. wait for registered event to happen
.
                LOOP
                EVENTWAIT
                REPEAT
.
. the $CLOSE event will end the program
.
term
                STOP

#Pi             FORM            "3.14159" ; constant PI needed for radiant calculation
#work1          FORM            2.5
#work2          FORM            2.5
#hrs            STATTEXT        (12)
#time           TIMER
#face           SHAPE

#Win            WINDOW          ^
#HideNum        FORM            1
ShowClock       ROUTINE         #Win,#HideNum
#T              FORM            4.5
#B              FORM            4.5
#L              FORM            4.5
#R              FORM            4.5
#x              FORM            2
#label          DIM             2
#Color1         FORM            "8421504"  ;0x808080
#Color2         FORM            "12632256"  ;0X404040
#timeout        FORM            "10"  ;This is a 1 second timeout

                CLEAR           #T,#L
.
. Get the size of the window that will contain the clock.
.
                GETPROP         #Win,WIDTH=#R,HEIGHT=#B
.
. create a circle for the clock face
. 
                CREATE          #Win;#face=#T:#B:#L:#R,SHAPE=1,ZORDER=10,BGCOLOR=#Color1,FILLCOLOR=#Color2
.
. initial RADIANT values for 12 o'clock  SIN and COS work in radians, not degrees.
.
                CALC            #work2=#pi/6
                CALC            #work1=-(#work2*3)  ;12 o'clock
.
. Clock Center
.
                DIV             "2",#R
                DIV             "2",#B
.
                IF              ( #HideNum = "0" )
                FOR             #x,"1","12"
.        
                ADD             #work2,#work1  ; numeric position incrament
                SIN             #work1,#T  ; get x
                COS             #work1,#L  ; get y
.        
                MULT            (#B-10),#T  ; adjust for radius
                MULT            (#R-10),#L
                ADD             (#B-8),#T
                ADD             (#R-4),#L
.        
. create the stattext for the clock face numbers
.        
                MOVE            #x,#label
                CREATE          #Win;#hrs(#x)=#T:(#T+20):#L:(#L+20),#label:
                                "'>MS Sans Serif'(8)":
                                BACKSTYLE=2:
                                ZORDER=11:
                                USEALTKEY=1
                ACTIVATE        #hrs(#x)
                REPEAT
                ENDIF
.
                ACTIVATE        #face
.
. create a timer object to continually update the displayed time
.
... MOVE "10",#timeout
                CREATE          #win;#time,#timeout
                ACTIVATE        #time,#UpdateClock,#timeout
. RETURN     ;fall through to update for initial positions

#HrHand         LINE
#MinHand        LINE
#SecHand        LINE
#tm             DIM             15
#hour           FORM            2.4
#min            FORM            2.4
#sec            FORM            2.4
..#R is left/right center
..#B is top/Bottom center

#UpdateClock
.
                EXCEPTSET       StopClock if object
.
. get the current time to display
.
                CLOCK           TIME,#tm
                EXPLODE         #tm,":",#hour,#min,#sec
.
. analog clocks only have a 12 hour display so adjust the hour if necessary
.
                IF              ( #hour > "12" )
                SUB             "12",#hour
                ENDIF
.
. radiant position of hour + partial hour...
. 
                CALC            #work1=("2"*#Pi)*(#hour/"12") + (#work2*(#min/"60")) - (#work2*3)
                SIN             #work1,#T   ; get x
                COS             #work1,#L   ; get y
                MULT            (#B/2),#T   ; adjust for radius
                MULT            (#R/2),#L
                ADD             (#B),#T
                ADD             (#R),#L
                CREATE          #Win;#HrHand=#B:#T:#R:#L,ZORDER=13,BDRWIDTH=5
                ACTIVATE        #HrHand
.
. exact minute use..
. MOVE (("2"*#Pi)*((#min/"60")) ),#work1 ; radiant position of minute
. for partial minute position use this instead
. 
                CALC            #work1=("2"*#Pi)*(#min/"60") + ((#work2/5)*(#sec/"60")) - (#work2*3)
                SIN             #work1,#T   ; get x
                COS             #work1,#L   ; get y
                MULT            (#B*3/4),#T  ; adjust for radius
                MULT            (#R*3/4),#L
                ADD             (#B),#T
                ADD             (#R),#L
                CREATE          #Win;#MinHand=#B:#T:#R:#L,ZORDER=14,BDRWIDTH=3
                ACTIVATE        #MinHand
.
. finally, calculate the position for the second hand.
.
                CALC            #work1=(("2"*#Pi)*((#sec/"60")))-(#work2*3)
                SIN             #work1,#T   ; get x
                COS             #work1,#L   ; get y
                MULT            (#B),#T   ; adjust for radius
                MULT            (#R),#L
                ADD             (#B),#T
                ADD             (#R),#L
                CREATE          #Win;#SecHand=#B:#T:#R:#L,ZORDER=15,BDRWIDTH=1
                ACTIVATE        #SecHand
.
                EXCEPTCLEAR     Object
                RETURN
StopClock
                DESTROY         #time
                RETURN
