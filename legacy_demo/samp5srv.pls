..............................................................................
.
. Date: 12-15-2000
.
. Sample server program which can be access via samp5x.htm HTML page which
. uses JSCRIPT.
.
.  
. Files:
.          samp5x.htm      - HTML page using JavaScript to access and
.                            retrieve data from a PL/B program named
.                            'samp5srv.plc'.
. 
.          samp5srv.plc    - Simple PL/B program which reads an AAM
.                            file and retrieves data by specific key.
. 
. Purpose:                               
.          This test is to demonstrate how one would access a PL/B program
.          using the JavaScript language to retrieve specific data.
.
. Usage:
.          SAMP5X.HTM
. 
.                1. Creates an application object named PlbProgNE using
.                   a new PL/B class identified as:
. 
.                         CLASSID={7B8BCB91-BC42-45A6-BC18-4D7D4497DE6E}
. 
.                2. Using 'PlbProgNE.Run(progname), the HTML logic causes
.                   a PLBWIN Automation Server thread to start executing
.                   the 'samp5srv.plc' program.  Notice, that the 'progname'
.                   in this case contains a command line to start the 
.                   execution which can contain PLBWIN options if required.
. 
.                3. Uses 'PlbProgNE.ErrorText' program object method to
.                   retrieve any error which might occur while initially
.                   loading the 'samp5srv.plc' program.
. 
.                4. Uses 'PlbProgNE.EventSend(1,name)' program object method
.                   to send an event identifier number 1 and data to the
.                   'samp5srv.plc' server program.  The HTML logic flow
.                   is suspended at that point until the server program
.                   retrieves the necessary data and returns.
. 
.                5. Uses 'PlbProgNE.EventSend(2)' program object method
.                   to send an event identifier number 2 to the 'samp5srv.plc'
.                   server program.  The server program will perform
.                   cleanup actions and stop at that point.
.
.                   Note:
.                         a. The PLBWIN Automation Server task remains loaded
.                            and is available to start executing other
.                            PL/B programs for subsequent HTML pages.
. 
.                         b. The 'PlbProgNE' program object can not be used
.                            for any other actions in the current HTML page.
. 
.          SAMP5SRV.PLC
. 
.                1. Creates a working phone list AAM file if it does not
.                   exist.
. 
.                2. Creates a diagnostic log file named 'diag.txt'.
. 
.                3. Uses EventReg to register two input events numbered
.                   '1' and '2' as recieved from the '*CLIENT' user client.
.                   These events are always process as FASTEVENT events.
.                   This means that these events are process immediately.
.                   Event number '1' is used to cause an AAM read by key.
.                   Event number '2' is used to cause the server program
.                   to stop executing.
. 
.                4. When an Event number '1' is processed, then the result
.                   is returned using the internal *RESULT variant object
.                   which is used to return results to a user client
.                   process.
. 
.                5. When an Event number '2' is processed, then a result
.                   is returned using the internal *RESULT variant object.
.                   The returning of a result in this case is only cosmetic
.                   and is not required.  Once this server program is
.                   terminated in this manner, then this program thread
.                   can not be reused.  A client process must create a
.                   new program object as required.
. 
...............................................................................
.
PhoneFile       AFILE
Name            DIM             20
Phone           DIM             20
Key             DIM             23
diag            FILE
seq3            FORM            "-3"
cString         DIM             256
.
;........WINSHOW
.
.....
. Create debug log file.
.
                PREP            diag,"diag"
                CALL            WriteDiag using "SRV: Started"
.....
. Create Test Data file.
.
                TRAP            DoPrep If IO
                OPEN            PhoneFile, "TestPhone"
                TRAPCLR         IO
.....
. Register events to be received from client
.
                EVENTREG        *Client, 1, DoRead, ARG1=Name
                EVENTREG        *Client, 2, DoExit
.....
. Log debug startup data.
.
                CALL            WriteDiag using "SRV: Before L-E-R 1st time"
.....
. Main Loop
.
                LOOP
                EVENTWAIT
                REPEAT
                STOP
 
.....
. Function to create test phone data file.
.
DoPrep
                PREP            PhoneFile, "TestPhone.txt", "TestPhone.aam":
                                "1-20","40",Share
                WRITE           PhoneFile;"Sam Smith    ","456-1234"
                WRITE           PhoneFile;"Fred Jones   ","456-9988"
                WRITE           PhoneFile;"Tommy Smith   ","456-1334"
                WRITE           PhoneFile;"Tod Smith    ","456-1234"
                WRITE           PhoneFile;"Jon Dow    ","456-1234"
                WRITE           PhoneFile;"Steve Sammon   ","456-1334"
                WRITE           PhoneFile;"Buster Smith   ","456-1234"
                WRITE           PhoneFile;"Paula    ","456-9988"
                WRITE           PhoneFile;"Tim Smith    ","456-1334"
                RETURN
 
.....
. Function to READ the 'PhoneFile' for a specified key.
.
DoRead
                PACK            cString,"SRV: Entered DoRead -- Param 'Name' = ",Name
                CALL            WriteDiag using cString
                MATCH           "  ",Name
                IF              ( Equal or Eos )
                MOVE            "Nam Blank/Null",Name
                SETPROP         *RESULT,VARVALUE=Name
                RETURN
                ENDIF
...
. Search using floating key.
.
 
                PACK            Key, "01F", Name
                READ            PhoneFile,Key;Name,Phone
                IF              OVER
...
. Record NOT Found!
.
                MOVE            "NAME NOT FOUND!",S$CMDLIN
                PACK            cString,"SRV: NAME NOT FOUND! "
                CALL            WriteDiag using cString
                ELSE
...
. Record DATA Found!
.
                PACK            S$CMDLIN,NAME,PHONE
                PACK            cString,"SRV: NAME=",NAME,"<<<"
                CALL            WriteDiag using cString
                ENDIF
.
                SETPROP         *RESULT,VARVALUE=S$CMDLIN    ;Send RESULT to CLIENT!
                RETURN
 
.....
. Function to Exit the Server program.
.
DoExit
                PACK            cString,"SRV: DoExit"
                CALL            WriteDiag using cString
                CLOSE           PhoneFile
                PACK            cString,"SRV: DoExit: PhoneFile closed"
                CALL            WriteDiag using cString
                SETPROP         *RESULT,VARVALUE="SAMP5SRV Server Program Terminated!"
                STOP
 
.....
. Function to log data to a debug file.
.
text            DIM             256
WriteDiag       ROUTINE         text
                WRITE           diag,seq3;text
                RETURN
 
 
 
