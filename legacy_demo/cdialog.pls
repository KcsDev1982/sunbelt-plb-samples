*...........................................................................
.
.Example Program: CDIALOG.PLS
.
. This sample program allows the user to selected two colors from the color
.  dialog.  The selected colors are then used with various objects
.
. Copyright @ 1997,1998, Sunbelt Computer Systems, Inc.
. All Rights Reserved
.............................................................................
.
. Revision History
.
. 9-8-98 JSS Convert display statements (except screen setup) to GUI style

*.............................................................................
C               COLOR           ;Color object
C1              COLOR           ;Color object
C2              COLOR
F               FORM            "-1"
T               STATTEXT        ;Static text object
FOBJ            FONT            ;Font object
G               GROUPBOX        ;Group box object
TT              TIMER           ;Timer object
R               FORM            1
CNT             FORM            "000"
CNT1            FORM            3
PR              PROGRESS        ;Progress object
PR1             PROGRESS        ;Progress object
SC1             HSCROLLBAR      ;Horizontal scroll bar object
SC2             VSCROLLBAR      ;Vertical scroll bar object
RES             FORM            9
ST1             STATTEXT
ST2             STATTEXT
ST1DATA         DIM             30
ST2DATA         DIM             30
CB              COLOR
CBD             COLOR
*------------------------------------------------------------------------------
. When the RGB values are the same value, this makes a gray color.
.
                CREATE          CB=*LTGRAY
                CREATE          CBD=*MDGRAY
                CREATE          C1=0:0:0      	// three values the same make a gray color
                                		// STARTING with black at zero, going to
                                		// WHITE at 255
*
. The BKGCOLOR parameter of the SETMODE defines the default back ground color
. to refresh the window.  This color is also used for a WINERASE statement.
.
                SETMODE         *SCREEN=OFF
                SETMODE         *FULLSCR=MAX
                SETMODE         *BGCOLOR=CB
                CREATE          ST2=23:24:5:35,ST2DATA,"SYSTEM(10,BOLD)",BGCOLOR=CB
                ACTIVATE        ST2
                CREATE          ST1=1:2:45:75,ST1DATA,"SYSTEM(10,BOLD)",BGCOLOR=CB
                ACTIVATE        ST1
*
. Create COLOR object named 'C'.  The use of a -1 for the values causes the
. COLOR dialog to be envoked.
.
                SETITEM         ST1,0,"Choose a Color"

                CREATE          C=F:F:F
*
. Create COLOR object named 'C2'.  When there is no RGB values given then
. this also causes the COLOR dialog to be envoked.
.
                SETITEM         ST1,0,"Choose a Second Color"

                CREATE          C2

                SETITEM         ST1,0,""       ; clear this prompt
*
. Create a FONT object named 'FOBJ'.
.
                CREATE          FOBJ,"Arial",SIZE=12,BOLD
*
. Create a STATTEXT object named 'T'.
.
                CREATE          T=5:10:10:60:
                                "This is a &test":  ;& can now be place in stattext data
                                FOBJ:               ;Use font object for FONT parameter
                                BORDER:             ;
                                BDRCOLOR=C:         ;Define the border color
                                FGCOLOR=C1:         ;Define the foreground color
                                BGCOLOR=CBD          ;Define the background color
*
. Create a groupbox object named 'G'.
.
                CREATE          G=12:15:10:30:
                                FGCOLOR=C1:             ;Define foreground color
                                BGCOLOR=CBD:            ;Define background color
                                TITLE="Test":           ;Specify title text
                                FONT=">Arial(12,BOLD)": ;Specify string font parameter
                                STYLE=3DOUT
*
. Create a TIMER object with a .4 second timeout
.
                CREATE          TT=4
*
. Create a PROGRESS object named 'PR'. Note that the object window
. coordinates determines the horizontal or vertical nature of the progress
. box.
.
                CREATE          PR=2:3:10:50:
                                FGCOLOR=C:              ;Define foreground color
                                STYLE=3DFLAT:
                                BGCOLOR=C2              ;Define background color
*
. Create a PROGRESS object name 'PR1'.
.
                CREATE          PR1=1:20:70:74:
                                FGCOLOR=C2:             ;Define foreground color
                                STYLE=3DOUT:
                                BGCOLOR=C               ;Define background color
*
. Create a HSCROLLBAR object named 'SC1'.  The minimum value for the
. scroll bar is zero, the maximum value for the scroll bar is one hundred,
. and the page or shift incrementing\decrementing value is ten.
. This is a horizontal scroll bar.
.
                CREATE          SC1=21:22:10:40:
                                0:                      ;Minimum value is 0.
                                100:                    ;Maximum value is 100.
                                10                      ;Page or Shift value is 10.
.
                ACTIVATE        SC1:             ;HSCROLLBAR object
                                SC1X:        ;Activation routine for object
                                RES           ;Result passed to activation routine
*
. Create a VSCROLLVAR object named 'SC2'.
. This is a vertical scroll bar.
.
                CREATE          SC2=18:23:50:60:
                                100:                    ;Minimum value is 100.
                                200:                    ;Maximum value is 200.
                                25                      ;Page or Shift value is 25.
.
                ACTIVATE        SC2:             ;VSCROLLBAR object
                                SC2X:        ;Activation routine for object
                                RES           ;Result passed to activation routine
.
                ACTIVATE        PR1       	// PROGRESS object activated without
                                		// any activation routine
.
                ACTIVATE        PR            	// PROGRESS object activated without
                                		// any activation routine
.
                ACTIVATE        G              	// GROUPBOX object activated without
                                		// any activation routine
.
                ACTIVATE        T:            ;STATTEXT object activated
                                T1:           ;Activation routine for object
                                R             ;Result passed to activation routine
.
                ACTIVATE        TT:           ;TIMER object activated
                                X:            ;Activation routine for object
                                R             ;Result passed to activation routine
*
. Wait for an Event to Occur
.
                LOOP
                WAITEVENT
                REPEAT
*............................................................................
.
. This is the activation routine for the TIMER object. Every .4 seconds 
. this routine will be executed.  The basic functions of the logic is
. as follows:
.
. 1. Increment counter
.
.         2. Set PROGRESS objects to counter value. The value for a
.            PROGRESS object is a percentage.  The value can be 0 to 100.
.
.         3. When   the counter gets to 50, use the SETPROP ( set properties )
.            statement to redefined the foreground and backgroud colors
.    of the PROGRESS objects.
.
.         4. For even and odd counter values alternate the border color of
.            the STATTEXT object.
.
.         5. When the counter exceeds a value of 100, reset the counter to 
.            zero an continue.
.
X
                ADD             "1" TO CNT
                SETITEM         PR,0,CNT        ;Set new value of PROGRESS object.
                SETITEM         PR1,0,CNT       ;Set new value of PROGRESS object.
*
. When value of counter is 50, use the SETPROP ( set properties ) statement
. to change the foreground and background colors of the PROGRESS objects.
.
                IF              (CNT = 50)
                SETPROP         PR,FGCOLOR=C2,BGCOLOR=C    ;Change color properties
                SETPROP         PR1,FGCOLOR=C,BGCOLOR=C2   ;Change color properties
                ENDIF
 
*
. Determine the when counter is even or odd and change the border color
. property of the STATTEXT object accordingly.
.
                CALC            CNT1=CNT/2
                CALC            CNT1=CNT1*2
                IF              (CNT =CNT1)
                SETPROP         T,BDRCOLOR=C        ;Change border color property
                ELSE
                SETPROP         T,BDRCOLOR=C2       ;Change border color property
                ENDIF
 
*
. Determine when the counter exceeds 100 and reset to zero.
.
                IF              (CNT > 100)
                MOVE            "0",CNT
                ENDIF
                RETURN
*..........................................................................
.
. This is the activation routine for the STATTEXT object.  The intent
. is to demonstrate that user can use the ALT key plus the 'T' character
. to initiate a event for the STATTEXT object.
.
T1
                SETITEM         ST2,0,"Alt T Seen..."
                RETURN
*..........................................................................
.
. This is the activation routine for the Horizontal scroll bar. By
. clicking on various parts of the scroll bar you will see that the
. result vaues passed to the activation routine change.
.
SC1X
                PACK            ST2DATA WITH "H Scroll value was: ",RES
                SETITEM         ST2,0,ST2DATA
                RETURN
*............................................................................
.
. This is the activation routine for the Vertical scroll bar.  By
. clicking on various parts of the scroll bar you will see that the
. result values passed to the activation routine change.
.
SC2X
                PACK            ST2DATA WITH "V Scroll value was: ",RES
                SETITEM         ST2,0,ST2DATA
                RETURN
