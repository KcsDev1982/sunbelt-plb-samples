.
. Sample CGI program to be invoked from plbcgi.exe
.
HdrData         INIT            "HTTP/1.0 200 OK",0xD,0xA,"Content-Type: text/html":
                                0xD,0xA,0xD,0xA:
                                "Hello From PL/B", 0xD, 0xA, "REQUEST_METHOD: "
QryStr          INIT            0xA, 0xD," QUERY_STRING: ", 0xA, 0xD
StdIn           INIT            0xA, 0xD," StdIn Data: ", 0xA, 0xD
Data            DIM             200
Data1           DIM             40
GotData         FORM            "0"
 
. Event 1 contains stdin data broken into 200 byte chunks.
 
                EVENTREG        *Client,1,GetStdData
 
. Event 2 indicates that all stdin data has been sent
 
                EVENTREG        *Client,2,DoneStdData
 
. Event 3 is used to return environment variable data
 
                EVENTREG        *Client,3,GetEnvData
 
                LOOP
                EVENTWAIT
                REPEAT          While (GotData = 0 )
 
.
. Get an environment variable by sending an event 2 to plbcgi
.
                EVENTSEND       *Client,2,ARG1="REQUEST_METHOD"
                EVENTWAIT
 
.
. Put data into stdout by sending an event 1 to plbcgi
.
                EVENTSEND       *Client,1,ARG1=HdrData
                EVENTSEND       *Client,1,ARG1=Data1
 
                EVENTSEND       *Client,2,ARG1="QUERY_STRING"
                EVENTWAIT
 
                EVENTSEND       *Client,1,ARG1=QryStr
                EVENTSEND       *Client,1,ARG1=Data1
 
                EVENTSEND       *Client,1,ARG1=StdIn
                EVENTSEND       *Client,1,ARG1=Data
                STOP
 
GetStdData
                EVENTINFO       0, ARG1=Data
                RETURN
 
DoneStdData
                MOVE            "1" To GotData
                RETURN
 
GetEnvData
                EVENTINFO       0, ARG1=Data1
                RETURN
