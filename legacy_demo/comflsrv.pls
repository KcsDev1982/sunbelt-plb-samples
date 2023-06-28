*....................................................................
. Example program   COMFILE
.  by Matthew Lake
.  
.  Aug 06 2010 Complete Rewite - server program
.  
.....................................................................
.
C               COMFILE
stat            DIM             21
tm              FORM            "5" // 5 second timeout
wconn           INIT            "100000000000000000001" // connect mask
wMsk            INIT            "010100000000000000000" // write mask
rMsk            INIT            "001100000000000000000" // read mask
nextConn        FORM            "1"
.
msg             DIM             200
crlf            INIT            0x0d,0x0a
data            DIM             80

.  
. Create a listening socket on port 5555
. 
                COMOPEN         C,"S,C,0.0.0.0,5555"
.
. loop to wait for incomming connection
.
                LOOP
                COMCHECK        C,wconn,tm,stat
.
. just keep waiting if timeout
.
.  this is actually a good place to do idle work if any needs to be done
                IF              OVER
.     CALL IDLE_PROCESSING
                CONTINUE
                ENDIF
.
. check pending connections
.
                ENDSET          stat
                CMATCH          "1",stat
                IF              EQUAL
                COMATTACH       C
                ENDIF
.
. we have a connection, process it
.
.   FORK   // !!! FORK is UNIX runtimes only !!!
.   IF OVER
                CALL            ProcessClient
.     SHUTDOWN // !!! UNIX runtime - shutdown client after fork !!! //
.   ENDIF
.
. here, we are done with the client but we do not want a full
. close on the comfile, we want to wait for the next client
. to connect.
. 
                COMCLOSE        C,nextConn
.
. back to top of loop to wait for next connection
. 
                REPEAT
.
ProcessClient
.
.
. wait till it is ok to send data
.
                COMCHECK        C,wMsk,tm,stat
.
. sent welcome message
.
                COMWRITE        C;"Hello world"
.
. wait for client to send data
.
                LOOP
                COMCHECK        C,rMsk,tm,stat
.
. just keep waiting if there was a timeout
.
                CONTINUE        IF OVER
.
. check for connection error
.
                RESET           stat,4
                CMATCH          "1",stat
                BREAK           IF EQUAL
.
. read the data the server sent back
.
                COMREAD         C;msg;
.
. process the data received.
.
                LOOP
                REMOVE          msg,data
                BREAK           IF EOS
                DISPLAY         *ll,data
                REPEAT
                MATCH           "quit",data
                BREAK           IF EQUAL
.
                REPEAT

                RETURN
 
