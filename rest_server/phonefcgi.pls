*---------------------------------------------------------------
.
. Program Name: phonefcgi
. Description:  A sample program for the REST API
.               This program is written to demonstrate the
.               Fast CGI support
.
. Revision History:
.
. 10 Apr 2026 whk
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc

*---------------------------------------------------------------

Runtime         RUNTIME
PauseTime       FORM            ".1"
GUI             FORM            2

.
. Message Data
.
MsgId           DIM             8
MsgTo           DIM             20
MsgFrom         DIM             20
MsgPhone        DIM             16
MsgData         DIM             200
.
. Database
.
PhoneMsgDb      DBFILE
SqlCommand      DIM             4096
SqlId           FORM            8
F10             FORM            "10"
.
. REST request
.
Request         DIM             40
Uri             DIM             400
UriSections     FORM            3
UriParts        DIM             100(7)
Host            DIM             100

.
. JSON Variables
.
MsgJson         JSONDATA
MsgJsonText     DIM             40960
.
*................................................................
.
. Code start
.
                CALL            Main
.
. Pause to allow the web server to send the response
.
                PAUSE           PauseTime
                STOP

*................................................................
.
. RestNotImpl
.
. Returns not implemented message
.
RestNotImpl     LFUNCTION
                ENTRY
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                FUNCTIONEND

*................................................................
.
. RestDelete
.
. DELETE /MyServices/phonemsg/2
.
. Deletes message based on primary key
.
RestDelete      LFUNCTION
                ENTRY
                PACK            SqlCommand Using "Delete from msgs where id=",UriParts(4)
                DBSEND          PhoneMsgDb;SqlCommand
                DBEXECUTE       PhoneMsgDb
                Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json", *Body="Delete Complete", *ExtraHdrs="", *Options=0
                FUNCTIONEND

*................................................................
.
. RestMakeResponse
.

. Makes a JSON response based on the given SQL command
.
RestMakeResponse LFUNCTION
                ENTRY
pos             FORM            2
                MsgJson.Reset
                CLEAR           pos
                MsgJson.SetArray USING "messages", ""
                DBSEND          PhoneMsgDb;SqlCommand
                DBEXECUTE       PhoneMsgDb
                LOOP
                DBFETCH         PhoneMsgDb,F10;MsgId, MsgTo, MsgFrom, MsgPhone, MsgData
                UNTIL           OVER
                MsgJson.SetString Using "messages[$1].Message.id",MsgId,pos
                MsgJson.SetString Using "messages[$1].Message.to",MsgTo,pos
                MsgJson.SetString Using "messages[$1].Message.from",MsgFrom,pos
                MsgJson.SetString Using "messages[$1].Message.phoneNumber",MsgPhone,pos
                MsgJson.SetString Using "messages[$1].Message.message",MsgData,pos
                ADD             "1" to pos
                REPEAT
                MsgJson.Store   Giving MsgJsonText
                MsgJson.Reset
                FUNCTIONEND
*................................................................
.
. RestGetName
.
. GET /MyServices/phonemsg/search/Name
.
. Searches for messages sent to Name
.
RestGetName     LFUNCTION
                ENTRY
                UPPERCASE       UriParts(4)
                MATCH           UriParts(4) To "SEARCH"
                IF              Equal
                PACK            SqlCommand Using "Select id, msgto, msgfrom, msgphone, msgdata from msgs where lower(msgto)=lower('",UriParts(5),"') order by msgto"
                CALL            RestMakeResponse
                Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json", *Body=MsgJsonText, *ExtraHdrs="", *Options=0
                ELSE
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                ENDIF
                FUNCTIONEND

*................................................................
.
. RestGetKey
.
. GET /MyServices/phonemsg/2
.
. Retrieves message based on primary key
.
RestGetKey      LFUNCTION
                ENTRY
                MOVE            UriParts(4) To SqlId
                IF              ( SqlId > 0 )
               
                PACK            SqlCommand Using "Select id, msgto, msgfrom, msgphone, msgdata from msgs where id=",SqlId," order by msgto"
                CALL            RestMakeResponse
                Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json", *Body=MsgJsonText, *ExtraHdrs="", *Options=0
                ELSE
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                ENDIF
                FUNCTIONEND

*................................................................
.
. RestGetAll
.
. GET /MyServices/phonemsg
.
. Retrieves all messages
.
RestGetAll      LFUNCTION
                ENTRY
          
                MOVE            "Select id, msgto, msgfrom, msgphone, msgdata from msgs order by msgto",SqlCommand
                CALL            RestMakeResponse
                Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json":
                                *Body=MsgJsonText, *ExtraHdrs="", *OutFile="msg.out" *Options=0

                FUNCTIONEND

*................................................................
.
. RestOptions
.
. Return the supported actions
.
RestOptions     LFUNCTION
                ENTRY
OptionHdr       INIT            "Allow: GET,POST,PUT,DELETE,OPTIONS",0xD,0xA
                Runtime.HttpResponse Using *HttpCode=200,*MimeType="text/html", *Body="", *ExtraHdrs=OptionHdr, *Options=0
                FUNCTIONEND

*................................................................
.
. RestFetchData
.
. This function will get the HTML message body from STDIN. It will then use
. the JSONDATA methods to extract the necessay fields.
.
RestFetchData   LFUNCTION
                ENTRY
HtmlData        DIM             4096
ReqResult       FORM            5

                Runtime.HttpStdinSize giving ReqResult
                DISPLAY         ReqResult
                Runtime.HttpStdinData giving HtmlData
                DISPLAY         HtmlData
                MsgJson.Parse   Using HtmlData

                MsgJson.GetString Giving MsgTo USING "to"
                MsgJson.GetString Giving MsgFrom USING "from"
                MsgJson.GetString Giving MsgPhone USING "phoneNumber"
                MsgJson.GetString Giving MsgData USING "message"
                FUNCTIONEND

*................................................................
.
. RestPost
.
. POST /MyServices/phonemsg
.
. Adds a new message
.
. Body contains json data object
. Primary key is return in Location: field
.
RestPost        LFUNCTION
                ENTRY
LineTerm        INIT            0xD,0xA
LocationHdr     DIM             200

                MOVE            "unknown" To MsgTo
                MOVE            "unknown" To MsgFrom
                MOVE            "unknown" To MsgPhone
                MOVE            "None" To  MsgData
                CALL            RestFetchData
 
                PACK            SqlCommand Using "insert into msgs(msgto,msgfrom,msgphone,msgdata) values('",MsgTo:
                                "', '",MsgFrom,"', '",MsgPhone,"', '",MsgData,"' )"
 
                DBSEND          PhoneMsgDb;SqlCommand
                DBEXECUTE       PhoneMsgDb
                DBSEND          PhoneMsgDb;"select last_insert_rowid()"
                DBEXECUTE       PhoneMsgDb
                DBFETCH         PhoneMsgDb,F10;MsgId
                PACK            LocationHdr Using "Location: http://", Host, Uri, "/", MsgId, LineTerm
                Runtime.HttpResponse Using *HttpCode=201,*MimeType="text/html", *Body=" created", *ExtraHdrs=LocationHdr, *Options=0
                FUNCTIONEND

*................................................................
.
. RestPut
.
. PUT /MyServices/phonemsg/2
.
. Updates message based on primary key
.
. Body contains json data object
.
RestPut         LFUNCTION
                ENTRY
                MOVE            UriParts(4) To SqlId

                IF              ( SqlId > 0 )

                PACK            SqlCommand Using "Select id, msgto, msgfrom, msgphone, msgdata from msgs where id=",SqlId," order by msgto"
                DBSEND          PhoneMsgDb;SqlCommand
                DBEXECUTE       PhoneMsgDb
                DBFETCH         PhoneMsgDb,F10;MsgId, MsgTo, MsgFrom, MsgPhone, MsgData

                IF              OVER
                Runtime.HttpResponse Using *HttpCode=404,*MimeType="text/html", *Body="Not found" *ExtraHdrs="", *Options=0
                ELSE

                CALL            RestFetchData
                PACK            SqlCommand Using "Update msgs SET msgto='",MsgTo,"', msgfrom='", MsgFrom,"', msgphone='",MsgPhone:
                                "', msgdata='", MsgData,"' where id=",SqlId
                DBSEND          PhoneMsgDb;SqlCommand
                DBEXECUTE       PhoneMsgDb
                Runtime.HttpResponse Using *HttpCode=204,*MimeType="text/html", *Body="" *ExtraHdrs="", *Options=0

                ENDIF

                ELSE
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                ENDIF
                FUNCTIONEND
*................................................................
.
. RestAction
.
. Handle a REST Request
.
RestAction      LFUNCTION
                ENTRY
.
. Decoding the requested action
.
                Runtime.CgiString Giving Request Using "REQUEST_METHOD"
                Runtime.CgiString Giving Uri Using "REQUEST_URI"
                Runtime.CgiString Giving Host Using "HTTP_HOST"

                EXPLODE         Uri Using "/" Giving UriSections into UriParts

                SWITCH          Request
 
                CASE            "DELETE"
                IF              (UriSections = 4 )
                CALL            RestDelete
                ELSE
                CALL            RestNotImpl
                ENDIF
               

                CASE            "GET"
                IF              (UriSections = 5 )
                CALL            RestGetName
                ELSE            If (UriSections = 4 )
                CALL            RestGetKey
                ELSE
                CALL            RestGetAll
                ENDIF

                CASE            "OPTIONS"
                CALL            RestOptions

                CASE            "PATCH"
                CALL            RestNotImpl

                CASE            "POST"
                IF              (UriSections = 3 )
                CALL            RestPost
                ELSE
                CALL            RestNotImpl
                ENDIF

                CASE            "PUT"
                IF              (UriSections = 4 )
                CALL            RestPut
                ELSE
                CALL            RestNotImpl
                ENDIF
 
                DEFAULT
                CALL            RestNotImpl

                ENDSWITCH
                FUNCTIONEND
*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
ReqResult       FORM            5
nCount          FORM            6

                GETMODE         *GUI=GUI
                IF              ( GUI != 0 )
                WINSHOW
                ENDIF
.
. Start by creating a default database if one is not availiable
.
                DBCONNECT       PhoneMsgDb, "SQLITE;;phonefcgi.db","",""
                DBSEND          PhoneMsgDb;"create table msgs(id integer primary key, msgto char(20), msgfrom char(20), msgphone char(16), msgdata char(200) )"
                EXCEPTSET       SkipBuild IF DBFAIL
                DBEXECUTE       PhoneMsgDb
                DBSEND          PhoneMsgDb;"insert into msgs(msgto,msgfrom,msgphone,msgdata) values('bill', 'mike', '1-345-555-1212', 'Moved meeting to 12:00pm' )"
                DBEXECUTE       PhoneMsgDb
                DBSEND          PhoneMsgDb;"insert into msgs(msgto,msgfrom,msgphone,msgdata) values('bill', 'bob', '1-235-555-1212', 'Lunch tomorrow ?' )"
                DBEXECUTE       PhoneMsgDb
                DBSEND          PhoneMsgDb;"insert into msgs(msgto,msgfrom,msgphone,msgdata) values('bill', 'lazy bro', '1-995-555-1212', 'Need to borrow $10' )"
                DBEXECUTE       PhoneMsgDb
SkipBuild       EXCEPTCLEAR     DBFAIL
.
. Decoding the requested action
.
.
                LOOP
 
                Runtime.HttpRequest Giving ReqResult Using *Timeout=3

                SWITCH          ReqResult

                CASE            0       // A request was made
                CALL            RestAction
                ADD             "1", nCount
                DISPLAY         nCount, " ", *LL, Request, " ", Uri

                CASE            1       // Shutdown message received from PWS server!
                DBDISCONNECT    PhoneMsgDb
                SHUTDOWN

                CASE            2       // Time out
                IF              ( GUI != 0 )
                EVENTCHECK
                ENDIF

                CASE            3       // Previous request still outstanding
                CALL            RestNotImpl

                DEFAULT         // Error
                DBDISCONNECT    PhoneMsgDb
                SHUTDOWN
                
                ENDSWITCH

                REPEAT

                FUNCTIONEND
.
.
.
