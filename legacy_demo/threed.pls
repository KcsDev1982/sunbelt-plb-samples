*.........................................................................
.
.Example Program: THREED.PLS
.
.This program illustrates the use of three demensional buttons.
. The Play and Stop buttons simply toggle between themselves.  The Pause
. button will toggle on or off if the Play Button is Depressed. Otherwise,
. the Pause button is Disabled.
.
. Copyright @ 1997, Sunbelt Computer Systems, Inc.
. All Rights Reserved.
...........................................................................
.
.Define the Replacement File Menu
.
FileMenu        MENU
FileData        INIT            ")File;E)xit"
*
.Define the Objects Needed
.
Header          STATTEXT        // Program Banner
StateLab        STATTEXT        // Indicate Label
State           STATTEXT        // State Indicator
.
PlayUp          PICT            // Play Button in Up State
PlayDown        PICT            // Play Button in Down State
StopUp          PICT            // Stop Button in Up State
StopDown        PICT            // Stop Button in Down State
PauseUp         PICT            // Pause Button in Up State
PauseDwn        PICT            // Pause Button in Down State
PauseDis        PICT            // Pause Button in Disabled State
.
Black           COLOR
White           COLOR
*
.Local Variables
.
RESULT          FORM            1
*
.State Variables
.
Play            FORM            "0"         // Initial State is Up
Stop            FORM            "1"         // Initial State is Down
Pause           FORM            "0"         // Initial State is Up
*...........................................................................
.
.Draw the Screen
.
                DISPLAY         *ES,*FGCOLOR=*MAGENTA
*
.Create the Banner
.
                CREATE          Header=2:3:23:55,"3D Button Demo","Times(24,Italic)"
*
.Create the State Indicator
.
                CREATE          Black=*BLACK
                CREATE          White=*WHITE
.
                CREATE          StateLab=5:6:23:28,"State","System(10)":
                                FGCOLOR=Black,ALIGNMENT=3
                CREATE          State=5:6:30:40,"Stopped","System(10,Bold)":
                                FGCOLOR=BLACK,STYLE=3DON,BORDER
*
.Create the Replacement File Menu
.
                CREATE          FileMenu,FileData
*
.Create the Buttons
.
                CREATE          PlayUp=10:13:30:34,"PLAY-UP.BMP"
                CREATE          PlayDown=10:13:30:34,"PLAY-DN.BMP"
                CREATE          StopUp=10:13:35:39,"STOP-UP.BMP"
                CREATE          StopDown=10:13:35:39,"STOP-DN.BMP"
                CREATE          PauseUp=10:13:40:44,"PAUS-UP.BMP"
                CREATE          PauseDwn=10:13:40:44,"PAUS-DN.BMP"
                CREATE          PauseDis=10:13:40:44,"PAUS-DIS.BMP"
*
.Activate the Objects
.
                ACTIVATE        Header    // Program Banner
.
                ACTIVATE        StateLab    // State Indicator
                ACTIVATE        State
.
                ACTIVATE        FileMenu,End,Result   // Replacement File Menu
.
                ACTIVATE        PlayUp,PlayRout,Result  // Play Button
                ACTIVATE        StopDown,StopRout,Result  // Stop Button
                ACTIVATE        PauseDis    // Pause Button
*
.Wait for an Event to Occur
.
                LOOP
                WAITEVENT
                REPEAT
*..........................................................................
.
.The Play button was clicked
.
PlayRout
                RETURN          IF (Play = 1)       // Already Playing
*
.Change the State of the Play Button
.
                DEACTIVATE      PlayUp
                ACTIVATE        PlayDown,PlayRout,Result
                SET             Play
*
.Change the State of the Stop Button
.
                DEACTIVATE      StopDown
                ACTIVATE        StopUp,StopRout,Result
                CLEAR           Stop
*
.Change the State of the Pause Button
.
                DEACTIVATE      PauseDis
                ACTIVATE        PauseUp,PausRout,Result
                ENABLEITEM      PauseUp
                CLEAR           Pause
*
.Change the State Message
.
                SETITEM         State,0,"Playing"
                RETURN
*.........................................................................
.
.The Pause Button was Clicked
.
PausRout
*
.If Paused, Change to Playing
.
                IF              (Pause = 1)   // Already Paused
                DEACTIVATE      PauseDwn
                ACTIVATE        PauseUp,PausRout,Result
                CLEAR           Pause
                SETITEM         State,0,"Playing"
*
.Otherwise, Change to Paused
.
                ELSE
                DEACTIVATE      PauseUp
                ACTIVATE        PauseDwn,PausRout,Result
                SET             Pause
                SETITEM         State,0,"Paused"
                ENDIF
.
                RETURN
*.........................................................................
.
.The Stop Button Was Clicked
.
StopRout
                RETURN          IF (Stop = 1)     // Already Stopped
*
.Change the State of the Stop Button
.
                DEACTIVATE      StopUp
                ACTIVATE        StopDown,StopRout,Result
                SET             Stop
*
.Change the State of the Play Button
.
                DEACTIVATE      PlayDown
                ACTIVATE        PlayUp,PlayRout,Result
                CLEAR           Play
*
.Disable the Pause Button
.
                DEACTIVATE      PauseDwn
                DEACTIVATE      PauseUp
                ACTIVATE        PauseDis
                SET             Pause
*
.Change the State Message
.
                SETITEM         State,0,"Stopped"
                RETURN
*............................................................................
.
.Exit File Menu Item Selected
.
END
                STOP
