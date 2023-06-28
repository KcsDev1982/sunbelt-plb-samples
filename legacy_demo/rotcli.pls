 
.
. Date: 05-01-2001
.
. Sample CLIENT test which uses the PROGID='Plbwin.ProgramNE' class.
. This sample is to demonstrate the ROT ( Running Objects Table )
. which has been implemented for the Sunbelt Automation Server.
.
App             AUTOMATION
Prog1           AUTOMATION      CLASS="SUNBELT.ROT"
.Prog1  Automation    CLASS="{B7DCD1EE-E34A-4448-BA0C-4C6398E0E16B}"
.
Prog1State      INTEGER         1
.
RESVAR          VARIANT
VAR1            VARIANT
VAR1A           VARIANT
VAR2            VARIANT
VAR2A           VARIANT
TRUE            VARIANT
FALSE           VARIANT
.
Data1           DIM             100
.
TIME            DIM             20
.
MINUS1          FORM            "-1"
ZERO            FORM            "0"
ANSWER          DIM             100
.
 
Form            PLFORM          ROTcli.plf
.
.....
. Create working VARIANT objects for this program.
.
                CREATE          FALSE,VARTYPE=11,VARVALUE=ZERO    ;VT_BOOL
                CREATE          TRUE,VARTYPE=11,VARVALUE=MINUS1    ;VT_BOOL
                CREATE          RESVAR, VARTYPE=8     ;VT_BSTR
                CREATE          VAR1, VARTYPE=8     ;VT_BSTR
                CREATE          VAR1A, VARTYPE=8     ;VT_BSTR
                CREATE          VAR2, VARTYPE=8     ;VT_BSTR
                CREATE          VAR2A, VARTYPE=8     ;VT_BSTR
.....
. Set working VARIANT objects used to interface with a Server
. program as VARIANT pointer type.
.
                SETPROP         RESVAR, VARPTR=1
                SETPROP         VAR1, VARPTR=1
                SETPROP         VAR1A, VARPTR=1
                SETPROP         VAR2, VARPTR=1
                SETPROP         VAR2A, VARPTR=1
.....
. Create an application object.  The Automation Server will be started
. if it is not already loaded.
.
                CREATE          App,Class="Plbwin.Application"
 
;.. SetProp App,*Visible=1
.
                WINHIDE
.
                FORMLOAD        Form
 
RESTART
                LOOP
                WAITEVENT
                REPEAT
.....
. Server Error
.
. Note:
.      1. The S$ERROR$ data being reported at this point reflects an
.   OBJECT error which is occurring in this CLIENT program.
.
ServerError
                NORETURN
                SETPROP         Button001,ENABLED=0
                SETPROP         GetTime,ENABLED=0
                SETPROP         ForceError,ENABLED=0
                SETPROP         StopButton,ENABLED=0
                SETPROP         ThreadID,ENABLED=0
                MOVE            "NECLI PROG1 OBJECT ERROR!",S$CMDLIN
                INSERTITEM      DataList1,9999,S$CMDLIN
                INSERTITEM      DataList1,9999,S$ERROR$
                CLEAR           Prog1State
                SETITEM         Button003,0,"Start Prog1"
                RETURN
.....
. Start/Exit 'Prog1'
.
Prog1
                IF              ( Prog1State )
                SETPROP         Button001,ENABLED=0
                SETPROP         GetTime,ENABLED=0
                SETPROP         ForceError,ENABLED=0
                SETPROP         StopButton,ENABLED=0
                SETPROP         ThreadID,ENABLED=0
                SETPROP         VAR1,VARVALUE=""
                Prog1.EventSend Giving RESVAR Using 201
...
. Get response to termination request.
.
                GETPROP         RESVAR,VARVALUE=S$CMDLIN
                INSERTITEM      DataList1,9999,S$CMDLIN
.
                CLEAR           Prog1State
                SETITEM         Button003,0,"Start Prog1"
                TRAPCLR         OBJECT
                ELSE
.
.....
. Create a program object which DOES NOT use events, but expects immediate
. results to be returned when an EventSend method is posted.
.
.....
. This client program starts by connecting to a currently running
. program object which has been pre-loaded by the automation server.
. 
                CREATE          PROG1
.
...
. Check for problem executing the NE Server program.
.
                GETPROP         Prog1,*ErrorText=S$CMDLIN
                TYPE            S$CMDLIN
                IF              EOS
...
. No error reported for NEsrv started.
.
                MOVE            "1",Prog1State
                SETITEM         Button003,0,"Exit Prog1"
                SETPROP         Button001,ENABLED=1
                SETPROP         GetTime,ENABLED=1
                SETPROP         ForceError,ENABLED=1
                SETPROP         StopButton,ENABLED=1
                SETPROP         ThreadID,ENABLED=1
                TRAP            ServerError IF OBJECT
                ELSE
...
. There has been an error trying to start ROTSRVS program.  Need to check
. and make sure that the ROTSRVS program is accessible.
.
                INSERTITEM      DataList1,9999,"Unable to load ROTSRVS Program!"
                INSERTITEM      DataList1,9999,S$CMDLIN
                ENDIF
                ENDIF
                RETURN
.....
. Send Event Message for Prog1 and get an immediate response.
.
SendEvent200
                CLEAR           ANSWER
                CLOCK           TIME,TIME
                PACK            S$CMDLIN,"Prog1 Title Update by client at:":
                                Time
                SETPROP         VAR1A,VARVALUE=S$CMDLIN
                SETPROP         VAR1,VARVALUE="Msg from Client"
...
. Send message and get immediate response.
. The VAR1 and VAR1A VARIANTs in this case are being used as both input
. and output parameters.
.
                Prog1.EventSend Using 200, VAR1:
                                VAR1A
...
. VAR1 and VAR1A VARIANT objects should have result from server program.
.
                GETPROP         VAR1,VARVALUE=ANSWER
                PACK            S$CMDLIN,ANSWER," "
                CLEAR           ANSWER
                GETPROP         VAR1A,VARVALUE=ANSWER
                PACK            S$CMDLIN,S$CMDLIN,ANSWER,"<<<"
                INSERTITEM      DataList1,9999,S$CMDLIN
                RETURN
.....
. Send Event Message to retrieve the Server Time.
.
SendEvent202
...
. Send message and get Server Time response into a RESULT VARIANT.
.
                Prog1.EventSend Giving RESVAR Using 202
...
. Report the Server Time
.
                GETPROP         RESVAR,VARVALUE=S$CMDLIN
                INSERTITEM      DataList1,9999,S$CMDLIN
                RETURN
.....
. Send Event Message to force Server program error.
.
SendEvent203
...
. Send message and get Server Time response into a RESULT VARIANT.
.
                Prog1.EventSend Giving RESVAR Using 203
...
. Even though the Server Program has gone away at this point, the
. Program Server thread is still present so that we can get the error
. data using the ERRORTEXT property.
.
                GETPROP         Prog1,*ErrorText=S$CMDLIN
...
. Report the Error
.
                TYPE            S$CMDLIN
                IF              NOT EOS
                INSERTITEM      DataList1,9999,"ROTSRVS Error Detected!"
                INSERTITEM      DataList1,9999,S$CMDLIN
                ENDIF
                RETURN
.....
. Send Event Message to force Server program to STOP!.
.
SendEvent204
...
. Send message and get response into a RESULT VARIANT.
.
                Prog1.EventSend Giving RESVAR Using 204
...
. Even though the Server Program has gone away at this point, the
. Program Server thread is still present so that we can get the error
. data using the ERRORTEXT property.
.
                GETPROP         Prog1,*ErrorText=S$CMDLIN
...
. Report the Error
.
                TYPE            S$CMDLIN
                IF              NOT EOS
                INSERTITEM      DataList1,9999,"ROTSRVS Error Detected!"
                INSERTITEM      DataList1,9999,S$CMDLIN
                ENDIF
                RETURN
.....
. Send Event Message to get Server program THREAD ID.
.
SendEvent205
...
. Send message and get response into a RESULT VARIANT.
.
                Prog1.EventSend Giving RESVAR Using 205
...
. Report the Server THREAD ID
.
                GETPROP         RESVAR,VARVALUE=S$CMDLIN
                INSERTITEM      DataList1,9999,S$CMDLIN
                RETURN
