*..........................................................................
.
.Example Program: PICT1.PLS
.
. Sample picture demonstration program
.
. This program demonstrates the ability to open a picture
. object and put the picture into the CLIPBOARD or retrieve
. a picture from the CLIPBOARD.
.
. Copyright @ 1998, Sunbelt Computer Systems, Inc.
. All Rights Reserved.
............................................................................
.
. Replacement File Menu
.
FileMenu        MENU
FileMenuData    INIT            "File;":
                                ")Open Pict...;":
                                ")From Clipboard;":
                                ")Paste;":
                                ")Close;":
                                "-;":
                                "E)xit"
.
EffectsMenu     MENU
EffectsData     INIT            "Effects;Rotate 90;Rotate 180;Rotate 270;Page Count"
MenuResult      FORM            1
.
OpenItem        FORM            "1"
ClipItem        FORM            "2"
PasteItem       FORM            "3"
CloseItem       FORM            "4"
QuitItem        FORM            "6"
.
TRUE            FORM            "1"
FALSE           FORM            "0"
.
IsOpen          FORM            "0"  Are we in the open state
FileName        DIM             40
MyPict          PICT            A sample picture variable    
Done            FORM            "0"
.
Message         DIM             40
.
. Picture screen co-ordinates
.
Top             FORM            "01"
Bottom          FORM            "24"
Left            FORM            "01"
Right           FORM            "80"
.
. Start by creating the necessary objects
.
                DISPLAY         *ES,*P25:1,"PICTURE/CLIPBOARD"
.
                CREATE          FileMenu,FileMenuData
                DISABLEITEM     FileMenu,PasteItem
                DISABLEITEM     FileMenu,CloseItem
                ACTIVATE        FileMenu,MenuAction,MenuResult
 
                CREATE          EffectsMenu,EffectsData
                DISABLEITEM     EffectsMenu,0
                ACTIVATE        EffectsMenu,EffectsAct, MenuResult
.
. Wait for an Event to Occur
. 
                LOOP
                WAITEVENT
                REPEAT          WHILE ( Done = FALSE )
                STOP
.
*...........................................................................
.
. Process a File menu event
.
MenuAction
                BRANCH          MenuResult OF OpenAction, ClipAction, PasteAction:
                                CloseAction, NoAction, QuitAction
.
NoAction
                RETURN
*
. Open an Image File
.
OpenAction
                CREATE          MyPict=Top:Bottom:Left:Right,FileName,AUTOZOOM
                ACTIVATE        MyPict
*
. Enable and Disable Menu Items for an existant Pict Object
.
                DISABLEITEM     FileMenu, OpenItem
                DISABLEITEM     FileMenu, ClipItem
                ENABLEITEM      FileMenu, PasteItem
                ENABLEITEM      FileMenu, CloseItem
                ENABLEITEM      EffectsMenu, 0
                MOVE            TRUE TO IsOpen
                RETURN
*
. Copy the Image from the Clipboard, Set the menu accordingly
.
ClipAction
                CREATE          MyPict,0,Top,Bottom,Left,Right
                ACTIVATE        MyPict
                DISABLEITEM     FileMenu, OpenItem
                DISABLEITEM     FileMenu, ClipItem
                ENABLEITEM      FileMenu, PasteItem
                ENABLEITEM      FileMenu, CloseItem
                ENABLEITEM      EffectsMenu, 0
                MOVE            TRUE TO IsOpen
                RETURN
*
. Past the Image to the Clipboard 
.
PasteAction
                CLIPSET         MyPict
                RETURN
*
. Destroy the Image, Modify the menu options accordingly
.
CloseAction
                DESTROY         MyPict
                DISABLEITEM     FileMenu, PasteItem
                DISABLEITEM     FileMenu, CloseItem
                DISABLEITEM     EffectsMenu, 0
                ENABLEITEM      FileMenu, OpenItem
                ENABLEITEM      FileMenu, ClipItem
                MOVE            FALSE TO IsOpen
                RETURN
*
. This will fall through the REPEAT statement to the STOP statement
.
QuitAction
                MOVE            TRUE TO Done
                RETURN
................................................................................
.
* Process an Effects menu event
.
EffectsAct
                BRANCH          MenuResult Of R90, R180, R270,PageCnt
                RETURN
. 
R90
                MyPict.Rotate   Using 90
                RETURN
. 
R180
                MyPict.Rotate   Using 180
                RETURN
.
R270
                MyPict.Rotate   Using 270
                RETURN
.
PageCnt
                MyPict.GetPageCount Giving MenuResult
                PACK            Message Using "Page Count is: ",MenuResult
                ALERT           Note, Message, MenuResult
                RETURN
.
. End of program
