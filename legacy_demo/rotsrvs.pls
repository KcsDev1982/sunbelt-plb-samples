*
* Date: 5-1-2001
*         
* This sample server task is pre-loaded by the Sunbelt Automation Server
* task as a ROT ( Running Objects Table ) program object.  This program
* has a specific CLASS ID and a PROG ID which has been assigned in the
* 'PLBROT.INI' file.
*
*      PROGID  ==>  SUNBELT.ROT
*      CLASSID  ==>  {B7DCD1EE-E34A-4448-BA0C-4C6398E0E16B}
*
* This sample ROT server task uses the Plbwin.ProgramNE interface which
* requires immediate responses to an event input request.
*
* This program can ONLY send results back to the CLIENT by using SETPROP
* to set values for internal VARIANT objects named *RESULT, *ARG1, and
* *ARG2.
*
* This program demonstrates the SETMODE *THREADRDY= control which
* indicates to the Automation Server when the program is ready to be
* connected to another client.
*
Timer           TIMER
Result          FORM            1
Time            DIM             20
Button1         BUTTON
Button2         BUTTON
Button3         BUTTON
Msg             DIM             70
Title           DIM             100
Arr             DIM             1(2)
Ndx             FORM            1
Count           FORM            5
EXIT            FORM            1
ROTCNT          FORM            5
 
                WINSHOW
                SETWTITLE       "ROT Server"
                DISPLAY         *ES,*P1:1,"ROT Server Started"
 
                CREATE          Timer, 5
                ACTIVATE        Timer, ShowTime, Result
 
                CREATE          Button1=8:10:5:15,"Exit"
                ACTIVATE        Button1,Exit,Result
 
                CREATE          Button2=8:10:35:42,"Event"
                ACTIVATE        Button2,ShipEvent,Result
 
                CREATE          Button3=8:10:55:62,"Error"
                ACTIVATE        Button3,CauseError,Result
 
                EVENTREG        *Client, 200, ShowMsg, ARG1=Msg, ARG2=Title
                EVENTREG        *Client, 201, Exit
                EVENTREG        *Client, 202, ShipEvent
                EVENTREG        *Client, 203, Error
                EVENTREG        *Client, 204, Stop
                EVENTREG        *Client, 205, ShipThread
 
                LOOP
                WAITEVENT
                REPEAT
.....
. Initiate program EXIT.
.
Exit
                SETPROP         *RESULT,VARVALUE="Server Program Disconnected!"
....
. The SETMODE *THREADRDY=ON operation identifies that another client can
. now be attached to this program object.
.
                SETMODE         *THREADRDY=ON
                RETURN
 
.....
. STOP command identifies that this program object should STOP.
.
STOP
                SETPROP         *RESULT,VARVALUE="Server Program terminating!"
                STOP
 
.....
. Set current Server Time.
.
ShowTime
                CLOCK           Time To Time
                DISPLAY         *P1:3,"Time: ",Time
                RETURN
 
.....
. A message has been received from a CLIENT to be processed.
.
ShowMsg
                DISPLAY         *P1:5,"Msg: ",Msg
                SETWTITLE       Title    
                SETPROP         *ARG1,VARVALUE="Message Received!"
                ADD             "1",COUNT
                SETPROP         *ARG2,VARVALUE=COUNT
                RETURN
 
.....
. A message event has been received from a CLIENT requesting the
. current time setting.
.
ShipEvent
                PACK            S$CMDLIN,"Server Time is:",Time
                SETPROP         *RESULT,VARVALUE=S$CMDLIN
                RETURN
.....
. A message event has been received from a CLIENT requesting the
. current thread number setting.
.
XTHREAD         FORM            10
.
ShipThread
                GETMODE         *THREADID=XTHREAD
                PACK            S$CMDLIN,"Server Thread #:",XTHREAD
                SETPROP         *RESULT,VARVALUE=S$CMDLIN
                RETURN
.....
. Force non-trapped error.
.
Error
CauseError
                MOVE            ARR(NDX),S$CMDLIN    ;F02 Error expected!
