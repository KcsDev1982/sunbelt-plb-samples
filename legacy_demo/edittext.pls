*...........................................................................
.
.Example Program: EDITTEXT.PLS
.
.  This demonstration programs shows some of the capabilities of the 
.  Edittext objects.
.
.  Copyright @ 1997, Sunbelt Computer Systems, Inc.
.  All Rights Reserved.
.............................................................................
.
. Revision History
.
. 9-10-98 JSS: Convert to GUI screen I/O
.              Modify search routine to work for newly entered text.
.              
. Aug 06 2010 updated to eliminate obsolete DIALOG object and to use
.   new techniques, properties and methods.
.
............................................................................
.
                INCLUDE         PLBEQU.INC
.
.
.Define the Replacement File Menu
.
FileMenu        MENU
FileData        INIT            ")File;E)xit"
*
.Define the New Search Menu
.
FindMenu        MENU
FindData        INIT            ")Search;/F)Find ...",011,"Ctrl+F;":
                                "/G(Find a)gain",011,"Ctrl+G"
*
.Define the Find window objects
.
Findcol         COLLECTION
FindWin         WINDOW
FindBtn         BUTTON
CancBtn         BUTTON
Label           STATTEXT
Edit            EDITTEXT

*
.Search Variables
.
SrchBtn         FORM            "1"
CanBtn          EQU             2
SrchText        EQU             3
SrchFld         FORM            "4"
STxtSize        FORM            8
SrchData        DIM             100
Stxt            DIM             5120
*
.Edittext Object and Data
.
EditText        EDITTEXT
.
Sample          INIT            "What is PL/B?",0x7F,0x7F,0x7F,0x7F:
                                "The PL/B language is an interactive,":
                                " data entry programming language ":
                                "designed primarily for business programming. ":
                                "Since its creation,PL/B has evolved into ":
                                "a powerful business programming ":
                                "language running under more than 60 combinations ":
                                "of hardware and operating ":
                                "systems. ",0x7F,0x7F:
                                "The PL/B language is easy to learn":
                                " and powerful enough to create complex programs."
*
.Page Heading
.
Header          STATTEXT
*
.Local Variables
.
StartSel        FORM            4
EndSel          FORM            4
Result          FORM            9
MAGENTA         COLOR
WHITE           COLOR
BLACK           COLOR
*............................................................................
.
.Ready the Screen
.
                SETMODE         *LTGRAY=ON,*3D=ON
                DISPLAY         *BGCOLOR=*YELLOW,*ES
. Define colors
                CREATE          MAGENTA=*MAGENTA
                CREATE          WHITE=*WHITE
*
.Create the Screen Heading
.
                CREATE          Header=2:4:23:55,"Edit Text Demo":
                                "Times(24,ITALIC,BOLD)",BORDER,STYLE=3DOUT:
                                ALIGNMENT=1,FGCOLOR=MAGENTA
.
*
.Create the Replacement File Menu
.
                CREATE          FileMenu,FileData
*
.Create the New Search Menu
.
                CREATE          FindMenu,FindData
*
.Create the Find Window
.
                CREATE          FindWin=1:150:1:420,TITLE="Find Window":
                                WINTYPE=$MODELESS,WINPOS=$PARENTCENTER:
                                BGCOLOR=$BtnFace
*
. Now that the window is created, create the object on the window
.
                CREATE          FindWin;FindBtn=95:120:100:150,"Find":
                                DEFAULT=$TRUE,ENABLED=$False
                CREATE          FindWin;CancBtn=95:120:200:250,"Cancel",CANCEL=$True
                CREATE          FindWin;Label=50:75:20:70,"Find:",">Arial(12)"
                CREATE          FindWin;Edit=50:75:100:400,FONT=">Arial(12)":
                                BORDER=$TRUE,STYLE=3DON
*
. register the events we want to process
.

                EVENTREG        Edit,$CHANGE,CanSrch
                EVENTREG        FindBtn,$CLICK,Search
                EVENTREG        CancBtn,$CLICK,Cancel
                EVENTREG        FindWin,$CLOSE,Cancel
*
. Establish a collection that contains all the objects of our find window
.
                LISTINS         Findcol,FindWin,Edit,Label,CancBtn,FindBtn
.
*
.Create an Edittext Object on the main window
.
                CREATE          EditText=5:24:5:75,BORDER,FONT="Times(12)":
                                MULTILINE,WORDWRAP,MAXCHARS=5120,BGCOLOR=WHITE
.
*
.Load the Data into the Edittext Object
.
                SETPROP         EditText,TEXT=Sample
*
. Activate all the objects
.
                ACTIVATE        FileMenu,Quit,Result
                ACTIVATE        FindMenu,FindIt,Result
                ACTIVATE        Header
                ACTIVATE        EditText
*
.Wait for an Event to Occur
.
                LOOP
                WAITEVENT
                REPEAT
*...........................................................................
.
.Find Menu Item Selected
.
FindIt
                IF              (Result = 1)                     // Find   Requested
*
. Get current contents of edit text box into Stxt for searching
.
                GETPROP         EditText,TEXT=Stxt
*
. Get the currently selected text to initialize the find window
.
                GETPROP         EditText,SELTEXT=SrchData
                SETPROP         Edit,TEXT=SrchData
*
. set find button appropreatly
. 
                CALL            CanSrch
*
.Activate the Find Dialog
.
                ACTIVATE        Findcol
                SETFOCUS        Edit
.
                RESET           Stxt
                ELSE
*
.Search Again Requested
.
                BUMP            Stxt
                CALL            SEARCH
.
                ENDIF

                RETURN
*............................................................................
.
. Search Edit Handling Routine
.
CanSrch
*
. Enable or Disable the Find Button and Find Again Menu Item
. Based on the Contents of the Search Text
.
                Edit.GetTextLength giving StxtSize
                IF              ZERO
                SETPROP         FindBtn,ENABLED=$False
                DISABLEITEM     FindMenu,2
                ELSE
                SETPROP         FindBtn,ENABLED=$TRUE
                ENABLEITEM      FindMenu,2
                ENDIF
.
                RETURN
*............................................................................
.
.Search for the Specified Text
.
Search
                DEACTIVATE      FindCol
.
*
.Search for the String
.
                GETPROP         Edit,TEXT=SrchData
                SCAN            SrchData,Stxt
*
.If Found, Highlight Selection
.
                IF              EQUAL
                MOVEFPTR        Stxt,StartSel
                SUB             "1",StartSel
                SETITEM         EditText,1,StartSel
                COUNT           Result,SrchData
                SETITEM         EditText,2,(StartSel + Result)
                SETFOCUS        EditText
                ELSE
*
.Catch Search Failure
.
                ALERT           CAUTION,"String Not Found",RESULT,"Search"
                ENDIF
.
                RETURN
*............................................................................
.
. Cancel the Find dialog
.
Cancel
                DEACTIVATE      FindCol
                RETURN
*.............................................................................
.
.Terminate the Program
.
Quit
                STOP
