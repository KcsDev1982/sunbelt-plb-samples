*
* Date: 1-3-2001
*
* Sample server task which demonstrates an interface to a CLIENT which
* requires immediate reponses to an event input request.
*
* This program can ONLY send results back to the CLIENT by using SETPROP
* to set values for internal VARIANT objects named *RESULT, *ARG1, and
* *ARG2.
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
 
                WINSHOW
                DISPLAY         *ES,*P1:1,"Server Started"
 
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
 
                LOOP
                WAITEVENT
                STOP            IF ( Exit != 0 )
                REPEAT
.....
. Initiate program EXIT.
.
Exit
                SETPROP         *RESULT,VARVALUE="Server Program STOPPING!"
                ADD             "1",EXIT        ;FORCE EXIT
                RETURN
 
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
. Force non-trapped error.
.
Error
CauseError
                MOVE            ARR(NDX),S$CMDLIN    ;F02 Error expected!
		STOP
