..............................................................
. Files:
.          plbsamp.asp     - ASP script to access and retrieve data 
.                            from a PL/B program named 'aspsrv.plc'.
. 
.          aspsrv.pls       - Simple PL/B program which reads an AAM
.                            file and retrieves data by event commands.
.       Data is returned to ASP script by modifying
.       an input event argument.
. 
. Purpose:                               
.   This test is to demonstrate how one would access a PL/B program
.   using ASP scripting to retrieve data.
. 
. Usage:
.          PLBSAMP.ASP
. 
.                1. Creates an program object named 'PlbSrv' using
.                   a new PL/B class identified as:
. 
.                         ProgID='Plbwin.ProgramNE'
.                         CLASSID={7B8BCB91-BC42-45A6-BC18-4D7D4497DE6E}
. 
.                2. Using 'PlbSrv.Run("aspsrv"), the ASP logic causes
.                   a PLBWIN Automation Server thread to start executing
.                   the 'aspsrv.plc' program.  Notice, that the "aspsrv" 
.                   in this case identifies a command line to start the 
.                   execution which can contain PLBWIN options if required.
.     
.  3. This ASP sample is NOT performing any error checking
.     using the ErrorText method.
.      
.                4. Uses 'PlbSrv.EventSend 1, ResString' program object
.     method to send an event identifier number 1 and the data
.     contained in 'ResString' to the 'aspsrv.plc' server
.     program.  The ASP logic flow is suspended at that
.     point until the PL/B server program retrieves the
.     necessary data and returns.  As implemented in this
.     demo, the input event number 1 for the PL/B server
.     program causes an AAM Read by key to occur.
.     
.     Also, note that the 'ResString' in this case is being
.     used as both an input to the 'aspsrv.plc' program
.     and an output from the 'aspsrv.plc' program to the ASP
.     script.  The 'aspsrv.plc' program uses SETPROP for the 
.     internal VARIANT named '*ARG1' when sending a result
.     back to the ASP script.
.     
.                5. Uses 'PlbSrv.EventSend 2, ResString' program object
.     method to send an event identifier number 2 with the
.     'ResString' VARIANT variable to be used for returning
.     a result.   As implemented in this demo, the input
.     event nubmer 2 for the PL/B server program causes
.     an AAM ReadKG operation to retrieve a next record.
.     The 'aspsrv.plc' program again uses the SETPROP for
.     the internal VARIANT named '*ARG1' to send a result
.     back to the ASP script in the 'ResString' variable.
. 
.                6. Uses 'PlbSrv.EventSend 3' program object method
.                   to send an event identifier number 3 to the 'aspsrv.plc'  
.                   server program.  The server program will perform
.                   cleanup actions and stop at that point.
. 
.                   Note:
.                         a. The PLBWIN Automation Server task remains loaded
.                            and is available to start executing other
.                            PL/B programs for subsequent ASP operations.
. 
.                         b. The 'PlbSrv' program object can not be used
.                            for any other actions.
. 
.          aspsrv.PLC
. 
.                1. Creates a working phone list AAM file if it does not
.                   exist.
. 
.                2. Uses EventReg to register three input events numbered
.                   '1', '2', and '3' as recieved from the '*CLIENT' ASP 
.     client.
.                   
.     These events are always process as FASTEVENT events.
.                   This means that these events are process immediately.
.                   Event number '1' is used to cause an AAM read by key.
.     Event number '2' is used to cause an AAM ReadKG operation.
.                   Event number '3' is used to cause the server program
.                  to stop executing.
. 
.                4. When Events numbered '1' and '2' are processed, then 
.                   the result is returned using the internal *ARG1 variant
.                   object which is being used to return results to the 
.     ASP client process.  Also, note that the Event numbered
.     '1' uses the 'ResString' as an input which contains the
.     data to be used in the AAM keyed search.
. 
.                5. When an Event number '3' is processed, then the 
.     'aspsrv.plc' server program is stopped.  Once this 
.     server program is terminated in this manner, then
.     this program thread can not be reused.  The client
.     process must create a new program object as required.
.     
..............................................................
PhoneFile       AFILE
Name            DIM             20
Phone           DIM             20
Key             DIM             23
Data            DIM             40

                WINSHOW
                TRAP            DoPrep If IO
                OPEN            PhoneFile, "TestPhone"
                TRAPCLR         IO
                EVENTREG        *Client, 1, DoRead, ARG1=Name
                EVENTREG        *Client, 2, DoReadNext
                EVENTREG        *Client, 3, DoExit
                DISPLAY         "Started"
                LOOP
                EVENTWAIT
                REPEAT
                STOP

DoPrep
                PREP            PhoneFile, "TestPhone.txt", "TestPhone.aam":
                                "1-20","40",Share
                WRITE           PhoneFile;"Sam Smith           ","555-1234"
                WRITE           PhoneFile;"Fred Jones          ","555-9988"
                WRITE           PhoneFile;"Tom Smith           ","555-1334"
                RETURN

DoRead
                DISPLAY         "DoRead"
                PACK            Key, "01F", Name
                READ            PhoneFile,Key;Name,Phone
                IF              Over
                MOVE            "!" To Data
                ELSE
                PACK            Data From Name,Phone
                ENDIF
                SETPROP         *Arg1,VARVALUE=Data
                RETURN

DoReadNext
                READKG          PhoneFile;Name,Phone
                IF              Over
                MOVE            "!" To Data
                ELSE
                PACK            Data From Name,Phone
                ENDIF
                SETPROP         *Arg1,VARVALUE=Data
                RETURN


DoExit
                CLOSE           PhoneFile
                STOP

