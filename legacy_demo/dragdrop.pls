*...........................................................................
. Example Program: DRAGDROP.PLS
.
. This example program illustrates the following features
.
.       1. DRAG/DROP using DRAGITEM and DROPID option.
.
.       2. Uses a DIALOG to provide user help information under the
.        menu item HELP. 
.
. User actions:
.
.   1. User can click on entry in DATALIST to select fonts.
.
.   2. User can click on font in DATALIST and hold mouse button and move
.      mouse to the STATTEXT or either ICON presented. When the action
.      is to drag to the STATTEXT object, this causes the font of the 
.      STATTEXT to be changed. There is also a result displayed on the
.      bottom line of the window. The user can use either the left or
.      right buttons.
.
.  3.  User can drag all or part of the EDITTEXT object data to the
.      STATTEXT object. This causes the data in the STATTEXT object to
.      changed to that of the EDITTEXT data.  The user uses the left
.      button to select a part of the EDITTEXT data and the right mouse
.      button to drag EDITTEXT data.
.
. Copyright @ 1997,1998, Sunbelt Computer Systems, Inc.
. All Rights Reserved.
.............................................................................
.
. Revision History
.
. 9-8-98 JSS Convert display statements (except screen setup) to GUI style
*............................................................................
.Required Objects
.
Icon1           ICON
Icon2           ICON
.
List            DATALIST
Text            STATTEXT
Edit            EDITTEXT
Font            FONT
.
St              STATTEXT
St2             STATTEXT
Note            DIM             40
*
.Local Data
.
FntName         DIM             30
Result          FORM            9
Type            FORM            2
*
. This dialog is used to show the user application information.
. Note:   The first object in the HELP Dialog show always be a BUTTON
.   which is used to terminate the DIALOG.  It is expected that the
.   normal operation will be to use TEXT type objects to provide the
.   user information.  The implemented here also uses the EDIT object
.   to provide a different look. If a EDIT object is used, then a
.   DISABLEITEM of the EDIT object should be done to not allow the
.   user to change the EDIT object data.
.
HelpDlg         DIALOG
HelpData        INIT            "TYPE=MODAL,SIZE=45:10,":
                                "BUTTON=4:4:5:10:'&OK',":
                                "EDIT=9:9:5:40,":
                                "TEXT=2:2:5:10:'About...',":
                                "TEXT=8:8:5:40:'MORE DATA HERE FOR USER'"
HelpLine        INIT            "&About Sample..."
*..........................................................................
.
.Ready the Display
.
                SETMODE         *LTGRAY=ON
                DISPLAY         *BGCOLOR=*YELLOW,*ES;
*
. Create a stattext object to display results, etc.
.
                CREATE          St=23:23:1:39,"","FIXED(10,BOLD)"
                CREATE          St2=23:23:41:79,"","FIXED(10,BOLD)"
                ACTIVATE        St
                ACTIVATE        St2
*
. Create the HELP user dialog
.
                CREATE          HelpDlg,HelpData
                SETMODE         *HDIALOG=HelpDlg,*HSTRING=HelpLine
                SETITEM         HELPDLG,2,0,HELPLINE   ;Place data in EDIT object
                DISABLEITEM     HELPDLG,2     ;Disable EDIT object
                SETFOCUS        HELPDLG,1     ;Set focus to BUTTON
*
. Create DATALIST object and load it
.
                CREATE          List=10:20:10:30      ;Create the DATALIST
                GETINFO         FONTS, List       ;Load DATALIST with fonts
                ACTIVATE        List, ListAction, Result ;Show the DATALIST
                DRAGITEM        List, DROP     	// Allow items in the DATALIST
                                		// to be dragged by holding down
                                		// mouse button.
*
. Create STATTEXT object which has a DROPID associated with it. The presence
. of the DROPID option means that when an object is dragged and dropped on
. this object, then the DROPID is sent to the action routine of the object
. which was dragged.
.
. Also, note that this STATTEXT object can be dragged as specified by the
. DRAGITEM statement.
.
                CREATE          Text=4:6:10:30,"Drag Me...",">Arial(12,BOLD)",DROPID=3
                ACTIVATE        Text,TextAction,Result
                DRAGITEM        Text,ON        ;Allow the STATTEXT to be dragged.
*
. Create ICON objects which have a DROPID associated with them. The presence of
. the DROPID option means that an object can be dragged to these ICON objects
. and dropped. The result is that the DROPID is sent to the action routine
. of the dragged object.
.
                CREATE          Icon1=4:40,10031,DROPID=1
                ACTIVATE        Icon1,XICON1,Result
                CREATE          Icon2=8:40,10041,DROPID=2
                ACTIVATE        Icon2
*
. Create EDITTEXT object which does not have a DROPID. However, the EDITTEXT
. object can be dragged and dropped on other objects.
.
. Note: The left mouse button is used to select data from the EDITTEXT object
. which is to be dragged.  Depressing and holding the right mouse
. button allows the selected text to be dragged in this test.
.
                CREATE          Edit=12:13:40:50,FONT=">Arial(12,BOLD)":
                                BORDER,MAXCHARS=10
                SETITEM         Edit, 0,"Drag Me..."    ;Initialize the EDITTEXT object
                ACTIVATE        Edit,EditAction,Result
                DRAGITEM        Edit,DROP      // Allow the EDITTEXT object to be
                                		// dragged.
*
.Wait for an Event to Occur
.
                LOOP
                WAITEVENT
                REPEAT
*............................................................................
. A STATTEXT Event Occurred
.
TextAction
                PACK            Note WITH "STATTEXT Result was: ",Result
                SETITEM         St,0,Note
                SETITEM         St2,0,""  
                RETURN
*.............................................................................
. A DATALIST Event Occurred
.
. Note that this routines has to process events from the DATALIST as well as
.  from DRAG/DROP actions which the user has performed.
.
. Note: The 9th digit of the result variable indicates when a DRAG/DROP
. action has been done. When the 9th digit has a value of 4 or 5,
. then a DRAG/DROP action was performed with the left mouse button
. (4) or the right mouse button (5).  The lower 8 digits contains
. the value of the DROPID for the object where the drop action occurred.
.
ListAction
                PACK            Note WITH "DATALIST Result was: ",Result
                SETITEM         St,0,Note
                SETITEM         St2,0,""  
                RETURN          IF ( Result < 900 ) ;No DRAG\DROP action, then RETURN
*
. This routine now will process the DROPID value
.
. The STATTEXT object has a DROPID of 3. Thus, when we see a DROPID value
. of 3 in this routine, we will change the FONT of the STATTEXT to be the
. same as dragged from the DATALIST.
.
                MOVE            Result TO Type
                IF              (Type = 3)
                GETITEM         List, 0, Result      ;Get item selected from DATALIST
                GETITEM         List, Result, FntName  ;Get DATALIST font name
                CREATE          Font, FntName,SIZE=12,BOLD  ;Create a FONT object using
                                DATALIST font name
                COUNT           RESULT,FntName
                SETLPTR         FntName,RESULT
                PACK            S$CMDLIN,">",FntName,"(12,BOLD)"
                PACK            Note WITH "FONT:",S$CMDLIN
                SETITEM         St2,0,Note
 
                SETPROP         Text,FONT=Font     ;Change the FONT of the STATEXT
                ENDIF
                RETURN
*............................................................................
. An ICON1 Event Occurred
.
. This routine resets the STATTEXT object.
.
XICON1
                PACK            Note WITH "ICON1 Result was: ",Result
                SETITEM         St,0,Note
                SETITEM         St2,0,""  
 
                CREATE          Text=4:6:10:30,"Drag Me...",">Arial(12,BOLD)",DROPID=3
                ACTIVATE        Text,TextAction,Result
                DRAGITEM        Text,ON
                RETURN
*...........................................................................
. An EDITTEXT Event Occurred
.
. This routine process normal events for the EDITTEXT object and DRAG/DROP
.  events performed by the user.
.
. Again, the 9th digit of the Result value indicates when a DRAG/DROP 
. action is performed.
.
EditAction
                PACK            Note WITH "EDITTEXT Result was: ",Result
                SETITEM         St,0,Note
                SETITEM         St2,0,""
                RETURN          IF ( Result < 900 )
*
. Again noting that the DROPID of the STATTEXT object has a value of 3,
. this routine checks for a DROPID of 3 and changes the text of the
. STATTEXT where the EDITTEXT data was dragged to.
.
                MOVE            Result TO Type
                IF              (Type = 3)        ;Check for DROPID of 3
                GETITEM         Edit, 1, FntName ;Get selected data from EDITTEXT object
                COUNT           Result FROM FntName
                IF              (Result = 0)
                GETITEM         Edit, 0, FntName ;Get all of EDITTEXT data
                ENDIF
                SETITEM         Text,0,FntName  ;Change STATTEXT text to EDITTEXT data
                ENDIF
                RETURN
