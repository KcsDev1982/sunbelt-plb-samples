*...........................................................................
.
.Example Program: DRAG.PLS
.
. This program creates a button on the screen and enables it Drag Property.
.  Dragging the Button to a new location causes an alert to be displayed 
.  indicating the new position.  The Button also detects the use of the
.  right mouse button for a click.  A menu item changes the right click 
.  detection to double click detection.
.
. Copyright @ 1997, Sunbelt Computer Systems, Inc.
. All Rights Reserved
*...........................................................................
.
.Replacment File Menu
.
FileMenu        MENU
FileData        INIT            ")File;)Double Clicks Only;E)xit"
*
.The Draggable Object
.
BtnDrag         BUTTON
*
.Local Variables
.
Result          FORM            9
Top             FORM            2
Left            FORM            2
MClick          FORM            4
NoteData        DIM             100
OnlyFlag        FORM            "0"
*..........................................................................
.
.Ready the Screen
.
                DISPLAY         *ES
*
.Create the Replacement File Menu
.
                CREATE          FileMenu,FileData
                ACTIVATE        FileMenu,FileRout,Result
*
.Create the Draggable Button
.
                CREATE          BtnDrag=3:4:30:40,"Drag Me",ENABLED=0
                ACTIVATE        BtnDrag,BtnRout,Result
                DRAGITEM        BtnDrag,ON
*
.Wait for an Event to Occur
.
                LOOP
                WAITEVENT
                REPEAT
*...........................................................................
.
.A Button Event Occurred
.
BtnRout
*
.Determine the Click Type
.
                MOVE            (Result / 100000000),MClick
                IF              (MClick = 1)
                IF              (OnlyFlag = 0)
                ALERT           NOTE,"Right Mouse Click Seen.",Result
                ENDIF
                ELSE            IF   (MClick = 3)
                IF              (OnlyFlag = 1)
                ALERT           Note,"Right Mouse Double Click Seen",Result
                ENDIF
.
                ELSE
*
.Output the New Position
.
                MOVE            (Result / 10000),Left
                MOVE            Result,Top
                PACK            NoteData WITH "The new position for the button is ":
                                Top,":",Left,"."
                ALERT           NOTE,NoteData,Result
                ENDIF
.
                RETURN
*...........................................................................
.
.File Menu Item Selected
.
FileRout
                STOP            IF (Result = 2)
*
.Flip the Only Flag
.
                IF              (OnlyFlag = 0)
                MOVE            "1",OnlyFlag
                CHECKITEM       FileMenu,1,ON
                ELSE
                MOVE            "0",OnlyFlag
                CHECKITEM       FileMenu,1,OFF
                ENDIF
.
                RETURN
