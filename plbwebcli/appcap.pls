*---------------------------------------------------------------
.
. Program Name: appcap
. Description:  PlbWebCli Application Capture Sample 
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


WebForm         PLFORM          appcapf.pwf
.
FullData        DIM             400
FileUrl         DIM             400
.
Result          FORM            5
MaxLen          FORM            5
Form1           FORM            1
InFile          DIM             200
OutFile         DIM             40
.
Client          CLIENT
.
FindRes         FORM            8
.
.

JsonData        XDATA
JsonOptToDisk   FORM            "6" // JSON_SAVE_USE_INDENT+JSON_SAVE_USE_EOR
.

.

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
. Cap - Perform capure event
.
Cap		LFUNCTION
                ENTRY

                GETPROP         Radio1,Value=Form1
                IF              (Form1 == 1) THEN
                Client.AppCapture Using *Type=AppCaptureImage,*Options="{#"limit#": 1 }"
                ENDIF

                GETPROP         Radio2,Value=Form1
                IF              (Form1 == 1) THEN
                Client.AppCapture Using *Type=AppCaptureAudio
        
                ENDIF

                GETPROP         Radio3,Value=Form1
                IF              (Form1 == 1) THEN
                Client.AppCapture Using *Type=AppCaptureVideo,*Options="{#"duration#": 10 }"
                ENDIF

                FUNCTIONEND
*................................................................
.
. EventCap - AppEventDoCapture
.
EventCap	LFUNCTION
                ENTRY

                JsonData.LoadJson Using FileUrl
                JsonData.SaveJson Using "appcap.json", JsonOptToDisk

                JsonData.FindNode Giving FindRes Using "NOCASE(parentlabel='name')", MOVE_DOCUMENT_NODE
                IF              (FindRes = 0 )
                JsonData.getText Giving OutFile
                JsonData.FindNode Giving FindRes Using "NOCASE(parentlabel='localURL')", MOVE_DOCUMENT_NODE
                IF              (FindRes = 0 )
                JsonData.getText Giving InFile
                SETPROP         LabelText1,*Text=InFile
                Client.AppUpload Giving Result Using InFile, OutFile
                ENDIF
                ENDIF

                FUNCTIONEND

*................................................................
.
. EventUp - AppEventDoUpload
.
EventUp         LFUNCTION
                ENTRY
                JsonData.LoadJson Using FullData
                JsonData.SaveJson Using "appcap1.json", JsonOptToDisk
                Client.AppDialog Using FullData, "Upload", "Cool;Wow"
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
		EVENTREG        Client,AppEventDoCapture,EventCap,ARG1=FileUrl
                EVENTREG        Client,AppEventDoUpload,EventUp,ARG1=FullData

                FORMLOAD        WebForm

                SETPROP         Radio1,Value=1
		FUNCTIONEND
