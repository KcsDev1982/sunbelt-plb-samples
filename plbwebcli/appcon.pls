*---------------------------------------------------------------
.
. Program Name: appcon
. Description:  PlbWebCli Application Contacts Sample 
.
. Revision History:
.
. 17-04-07 whk
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*--------------------------------------------------------------- 

WebForm         PLFORM          appconf.pwf
.
FullData        DIM             1000
ContactData     DIM             1000
.
Result          FORM            5
MaxLen          FORM            5
Form1           FORM            1
InFile          DIM             200
OutFile         DIM             40
.
Client          CLIENT
.
JsonData        XDATA
JsonOptToDisk   FORM            "6" // JSON_SAVE_USE_INDENT+JSON_SAVE_USE_EOR
.
DisplayName     DIM             40
FindRes         FORM            8

*................................................................
.
. Code start
.
                CALL            Main
                LOOP
                EVENTWAIT
                REPEAT
                STOP
 

*................................................................
.
. HandleSel - Handle a request to perform a test
.
HandleSel       LFUNCTION
                ENTRY
                EVENTINFO       0,result=Result
                SWITCH          Result
                CASE            1
                Client.AppFindContact Using "[#"displayName#", #"name#"]":             
                                "{#"filter#": #"Bob#"}"
                CASE            2
                Client.AppPickContact Giving Result
                CASE            3
                Client.AppGetPicture Giving Result
                CASE            4
                STOP
                ENDSWITCH
                FUNCTIONEND


*................................................................
.
. EventPicked - AppEventContactPicked
.
EventPicked     LFUNCTION
                ENTRY
.
                JsonData.LoadJson Using ContactData
                JsonData.SaveJson Using "appcon.json", JsonOptToDisk
 
                JsonData.FindNode Giving FindRes Using "NOCASE(parentlabel='DisplayName')", MOVE_DOCUMENT_NODE

                IF              (FindRes == 0)
                JsonData.getJsonType Giving Result
                IF              (Result == JSON_TYPE_NULL)
                MOVE            "1" TO FindRes
                ENDIF
                ENDIF

                IF              (FindRes <> 0 )
                JsonData.FindNode Giving FindRes Using "parentlabel='formatted'", MOVE_DOCUMENT_NODE
                ENDIF

                IF              (FindRes <> 0 )
                MOVE            "No selection" To DisplayName
                ELSE
                JsonData.getText Giving DisplayName
                ENDIF
                Client.AppDialog Using DisplayName, "Contact Name", "Cool;Wow"
                FUNCTIONEND

*................................................................
.
. EventGetPict - AppEventGetPict
.
EventGetPict    LFUNCTION
                ENTRY
                Client.AppDialog Using ContactData, "Pict Info", "Get;Ok"
                FUNCTIONEND

*................................................................
.
. EventContact - AppEventGetContact
.
EventContact    LFUNCTION
                ENTRY
                JsonData.LoadJson Using ContactData
                JsonData.SaveJson Using "appcon1.json", JsonOptToDisk
 
                JsonData.FindNode Giving FindRes Using "parentlabel='displayName'", MOVE_DOCUMENT_NODE

                IF              (FindRes == 0)
                JsonData.getJsonType Giving Result
                IF              (Result == JSON_TYPE_NULL)
                MOVE            "1" TO FindRes
                ENDIF
                ENDIF

                IF              (FindRes <> 0 )
                JsonData.FindNode Giving FindRes Using "parentlabel='formatted'", MOVE_DOCUMENT_NODE
                ENDIF

                IF              (FindRes <> 0 )
                MOVE            "Not found" To DisplayName
                ELSE
                JsonData.getText Giving DisplayName
                ENDIF

                Client.AppDialog Using DisplayName, "Contacts", "Wow","Data goes here"
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
. Register and Startup the events, load the main form
.
Main            LFUNCTION
                ENTRY
                WINHIDE

                FORMLOAD        WebForm
.
                EVENTREG        Client,AppEventContactPicked,EventPicked,ARG1=ContactData
                EVENTREG        Client,AppEventGetPict,EventGetPict,ARG1=ContactData
                EVENTREG        Client,AppEventGetContact,EventContact,ARG1=ContactData
                FUNCTIONEND

