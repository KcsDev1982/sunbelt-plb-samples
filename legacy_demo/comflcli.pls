*....................................................................
. Example program   COMFILE
.  by Matthew Lake
.  
.  Aug 06 2010 Complete Rewite - Client program
.  
.....................................................................
.
C               COMFILE
stat            DIM             21
tm              FORM            "5" // 5 second timeout
wMsk            INIT            "010100000000000000000" // write mask
rMsk            INIT            "001000000000000000000" // read mask

msg             DIM             200
crlf            INIT            0x0d,0x0a
data            DIM             80

                PACK            msg,"GET /index.php HTTP/1.1",crlf:
                                "HOST: www.sunbelt-plb.com",crlf,crlf
.  
. open a connection to a web server
. 
                COMOPEN         C,"S,O,www.sunbelt-plb.com,80"
.
. wait till it is ok to send data
.
                COMCHECK        C,wMsk,tm,stat
.
. sent an HTTP get request
.
                COMWRITE        C;*ll,msg
.
. wait for a responce from the server
.
                LOOP
                COMCHECK        C,rMsk,tm,stat
.
. break if there was a timeout
.
                BREAK           IF OVER
.
. read the data the server sent back
.
                COMREAD         C;msg;
                LOOP
                REMOVE          msg,data
                BREAK           IF EOS
                DISPLAY         *ll,msg
                REPEAT
 
                REPEAT
. 
. once we are done with the connection, close it
.
                COMCLOSE        C
.
. wait for user to hit enter before exiting
.
                KEYIN           msg
                STOP
 
