...............................................................................
. This program uses the directory '.\restapi' for the
. REST working directory.
.
. Purpose:
.    This program has been modified from the original program
.    named 'phonemsgorg.pls' so it expects to be located in
.    directory relative to the 'plbwebsrv.106A\code' directory
.    as follows:
.
.       c:\sunbelt\plbwebsrv.106A\code\
.
.    Note:
.       1. This program can ONLY be executed so it works properly
.          when using a >9.9A PLBWIN, PLBNET, or PLB runtime.
.
. Date: 03/21/2024
.
...............................................................................
.
                INCLUDE         plbmeth.inc
.
Runtime         RUNTIME
F10             FORM            "10"
Result          FORM            8
.
PauseTime       FORM            ".1"
.
CurDir          DIM             300
CurDirRestApi   DIM             300
.
HtmlData        DIM             4096

JsonOptToDisk   FORM            "6" // JSON_SAVE_USE_INDENT+JSON_SAVE_USE_EOR
.
. Message Data
.
MsgId           DIM             8
MsgTo           DIM             20
MsgFrom         DIM             20
MsgPhone        DIM             16
MsgData         DIM             200
.
.
.
PhoneMsgDb      DBFILE
SqlCommand      DIM             4096
SqlId           FORM            8
.
.
GUI             FORM            2               //ERB
.
Request         DIM             40
Uri             DIM             400
UriSections     FORM            3
UriParts        DIM             100(7)
Host            DIM             100
.
. XDATA Variables
.
MsgInfo         XDATA
MsgJson         DIM             40960
.
.
.
OptionHdr       INIT            "Allow: GET,POST,PUT,DELETE,OPTIONS",0xD,0xA
LineTerm        INIT            0xD,0xA
LocationHdr     DIM             200
*==============================================================================
. Set the CWD for the REST runtime.
.
                GETMODE         *GUI=GUI                                        //ERB
.
                IF              ( GUI == 0 )                                            //ERB
.
                PATH            CURRENT, CurDir                                 //ERB
                IF              NOT OVER                                                //ERB
                PACK            CurDirRestApi, CurDir, "/restapi/"              //ERB
                PATH            CHANGE, CurDirRestApi                           //ERB
                IF              OVER                                            //Deb
;..         ALERT NOTE, CurDirRestApi, Result, "Over"           //Deb
                ELSE            //Eeb
;..         ALERT NOTE, CurDirRestApi, Result, "Not Over..."    //Deb
                ENDIF           //Deb
                ENDIF           //ERB
.
                ELSE            //ERB
.
                PATH            CURRENT, CurDir                                 //ERB
                IF              NOT OVER                                                //ERB
                PACK            CurDirRestApi, CurDir, "\restapi\"              //ERB
                PATH            CHANGE, CurDirRestApi                           //ERB
                IF              OVER                                            //Deb
;..        ALERT NOTE, CurDirRestApi, Result, "Over"            //Deb
                ELSE            //Eeb
;..        ALERT NOTE, CurDirRestApi, Result, "Not Over..."     //Deb
                ENDIF           //Deb
                ENDIF           //ERB
.
                ENDIF           //ERB
.
...............................................................................
. Start by creating a default database if one is not availiable
.
                DBCONNECT       PhoneMsgDb, "SQLITE;;phonemsg.db","",""
                DBSEND          PhoneMsgDb;"create table msgs(id integer primary key, msgto char(20), msgfrom char(20), msgphone char(16), msgdata char(200) )"
                TRAP            SkipBuild IF DBFAIL
                DBEXECUTE       PhoneMsgDb
                DBSEND          PhoneMsgDb;"insert into msgs(msgto,msgfrom,msgphone,msgdata) values('bill', 'mike', '1-345-555-1212', 'Moved meeting to 12:00pm' )"
                DBEXECUTE       PhoneMsgDb
                DBSEND          PhoneMsgDb;"insert into msgs(msgto,msgfrom,msgphone,msgdata) values('bill', 'bob', '1-235-555-1212', 'Lunch tomorrow ?' )"
                DBEXECUTE       PhoneMsgDb
                DBSEND          PhoneMsgDb;"insert into msgs(msgto,msgfrom,msgphone,msgdata) values('bill', 'lazy bro', '1-995-555-1212', 'Need to borrow $10' )"
                DBEXECUTE       PhoneMsgDb
SkipBuild
                NORETURN
.
. Decoding the reuested action
.
                IF              ( GUI != 0 )
                WINHIDE
                ENDIF
                Runtime.CgiString Giving Request Using "REQUEST_METHOD"
                Runtime.CgiString Giving Uri Using "REQUEST_URI"
                Runtime.CgiString Giving Host Using "HTTP_HOST"

.
. Break up URI to parts
.
                EXPLODE         Uri Using "/" Giving UriSections into UriParts

                SWITCH          Request
 
                CASE            "DELETE"
                IF              (UriSections = 4 )
                CALL            HandleDelete
                ELSE
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                ENDIF

                CASE            "GET"
                IF              (UriSections = 5 )
                CALL            HandleGetName
                ELSE            If (UriSections = 4 )
                CALL            HandleGetKey
                ELSE
                CALL            HandleGetAll
                ENDIF

                CASE            "OPTIONS"
                CALL            HandleOptions

                CASE            "PATCH"
                CALL            HandlePatch

                CASE            "POST"
                IF              (UriSections = 3 )
                CALL            HandlePost
                ELSE
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                ENDIF

                CASE            "PUT"
                IF              (UriSections = 4 )
                CALL            HandlePut
                ELSE
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                ENDIF
 

                DEFAULT
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                ENDSWITCH
                DBDISCONNECT    PhoneMsgDb
		PAUSE		PauseTime	// Allow time for WebServer to process before exit
                STOP

.
. DELETE /MyServices/phonemsg/2
.
. Deletes message based on primary key
.
HandleDelete
                PACK            SqlCommand Using "Delete from msgs where id=",UriParts(4)
                DBSEND          PhoneMsgDb;SqlCommand
                DBEXECUTE       PhoneMsgDb
                Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json", *Body=MsgJson, *ExtraHdrs="", *Options=0
                RETURN
.
. GET /MyServices/phonemsg/search/Name
.
. Searches for messages sent to Name
.
.
HandleGetName
                UPPERCASE       UriParts(4)
                MATCH           UriParts(4) To "SEARCH"
                IF              Equal
                MsgInfo.Reset
                MsgInfo.CreateElement GIVING result:
                                USING *POSITION=CREATE_AS_FIRST_CHILD:
                                *LABEL="messages":
                                *JSONTYPE=JSON_TYPE_ARRAY:
                                *OPTIONS=MOVE_TO_CREATED_NODE
                PACK            SqlCommand Using "Select id, msgto, msgfrom, msgphone, msgdata from msgs where lower(msgto)=lower('",UriParts(5),"') order by msgto"
                DBSEND          PhoneMsgDb;SqlCommand
                DBEXECUTE       PhoneMsgDb
                LOOP
                DBFETCH         PhoneMsgDb,F10;MsgId, MsgTo, MsgFrom, MsgPhone, MsgData
                UNTIL           OVER
                CALL            ResultAddOneMessage
                REPEAT
                MsgInfo.StoreJson Giving MsgJson
                MsgInfo.Reset
                Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json", *Body=MsgJson, *ExtraHdrs="", *Options=0
                ELSE
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                ENDIF
                RETURN
.
. GET /MyServices/phonemsg/2
.
. Retrieves message based on primary key
.
HandleGetKey
                MOVE            UriParts(4) To SqlId
                IF              ( SqlId > 0 )
                MsgInfo.Reset
                MsgInfo.CreateElement GIVING result:
                                USING *POSITION=CREATE_AS_FIRST_CHILD:
                                *LABEL="messages":
                                *JSONTYPE=JSON_TYPE_ARRAY:
                                *OPTIONS=MOVE_TO_CREATED_NODE
                PACK            SqlCommand Using "Select id, msgto, msgfrom, msgphone, msgdata from msgs where id=",SqlId," order by msgto"
                DBSEND          PhoneMsgDb;SqlCommand
                DBEXECUTE       PhoneMsgDb
                LOOP
                DBFETCH         PhoneMsgDb,F10;MsgId, MsgTo, MsgFrom, MsgPhone, MsgData
                UNTIL           OVER
                CALL            ResultAddOneMessage
                REPEAT
                MsgInfo.StoreJson Giving MsgJson
                MsgInfo.Reset
                Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json", *Body=MsgJson, *ExtraHdrs="", *Options=0
                ELSE
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                ENDIF
                RETURN
.
. GET /MyServices/phonemsg
.
. Retrieves all messages
.
HandleGetAll
                MsgInfo.Reset
                MsgInfo.CreateElement GIVING result:
                                USING *POSITION=CREATE_AS_FIRST_CHILD:
                                *LABEL="messages":
                                *JSONTYPE=JSON_TYPE_ARRAY:
                                *OPTIONS=MOVE_TO_CREATED_NODE
                DBSEND          PhoneMsgDb;"Select id, msgto, msgfrom, msgphone, msgdata from msgs order by msgto"
                DBEXECUTE       PhoneMsgDb
                LOOP
                DBFETCH         PhoneMsgDb,F10;MsgId, MsgTo, MsgFrom, MsgPhone, MsgData
                UNTIL           OVER
                CALL            ResultAddOneMessage
                REPEAT
                MsgInfo.StoreJson Giving MsgJson
                MsgInfo.Reset
                Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json":
                                *Body=MsgJson, *ExtraHdrs="", *OutFile="msg.out" *Options=0
                RETURN
.
. OPTIONS
.
. Return the supported actions
.
HandleOptions
                Runtime.HttpResponse Using *HttpCode=200,*MimeType="text/html", *Body="",*ExtraHdrs=OptionHdr, *Options=0
                RETURN
.
. PATCH
.
. Not supported - but could be like PUT
.
HandlePatch
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                RETURN
.
. POST /MyServices/phonemsg
.
. Adds a new message
.
. Body contains json data object
. Primary key is return in Location: field
.
HandlePost
                MOVE            "unknown" To MsgTo
                MOVE            "unknown" To MsgFrom
                MOVE            "unknown" To MsgPhone
                MOVE            "None" To  MsgData
                CALL            GetPostOrPutData
 
                PACK            SqlCommand Using "insert into msgs(msgto,msgfrom,msgphone,msgdata) values('",MsgTo:
                                "', '",MsgFrom,"', '",MsgPhone,"', '",MsgData,"' )"
 
                DBSEND          PhoneMsgDb;SqlCommand
                DBEXECUTE       PhoneMsgDb
                DBSEND          PhoneMsgDb;"select last_insert_rowid()"
                DBEXECUTE       PhoneMsgDb
                DBFETCH         PhoneMsgDb,F10;MsgId
                PACK            LocationHdr Using "Location: http://", Host, Uri, "/", MsgId, LineTerm
                Runtime.HttpResponse Using *HttpCode=201,*MimeType="text/html", *Body=" created", *ExtraHdrs=LocationHdr, *Options=0
                RETURN

.
. PUT /MyServices/phonemsg/2
.
. Updates message based on primary key
.
. Body contains json data object
.
HandlePut
                MOVE            UriParts(4) To SqlId
                IF              ( SqlId > 0 )
                MsgInfo.Reset
                MsgInfo.CreateElement GIVING result:
                                USING *POSITION=CREATE_AS_FIRST_CHILD:
                                *LABEL="messages":
                                *JSONTYPE=JSON_TYPE_ARRAY:
                                *OPTIONS=MOVE_TO_CREATED_NODE
                PACK            SqlCommand Using "Select id, msgto, msgfrom, msgphone, msgdata from msgs where id=",SqlId," order by msgto"
                DBSEND          PhoneMsgDb;SqlCommand
                DBEXECUTE       PhoneMsgDb
                DBFETCH         PhoneMsgDb,F10;MsgId, MsgTo, MsgFrom, MsgPhone, MsgData
                IF              OVER
                Runtime.HttpResponse Using *HttpCode=404,*MimeType="text/html", *Body="Not found" *ExtraHdrs="", *Options=0
                ELSE
                CALL            GetPostOrPutData
                PACK            SqlCommand Using "Update msgs SET msgto='",MsgTo,"', msgfrom='", MsgFrom,"', msgphone='",MsgPhone:
                                "', msgdata='", MsgData,"' where id=",SqlId
                DBSEND          PhoneMsgDb;SqlCommand
                DBEXECUTE       PhoneMsgDb
                Runtime.HttpResponse Using *HttpCode=204,*MimeType="text/html", *Body="" *ExtraHdrs="", *Options=0
                ENDIF
                ELSE
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                ENDIF
                RETURN
.
. This function will get the HTML message body from STDIN. It will then use
. the XDATA methods to extract the necessay fields.
.
GetPostOrPutData
                STREAM          *STDIN,HtmlData
                MsgInfo.LoadJson Using HtmlData

                CALL            FetchJsonStringValue    USING   MsgInfo,"to",MsgTo
                CALL            FetchJsonStringValue    USING   MsgInfo,"from", MsgFrom
                CALL            FetchJsonStringValue    USING   MsgInfo,"phoneNumber", MsgPhone
                CALL            FetchJsonStringValue    USING   MsgInfo,"message", MsgData
                RETURN

.
. Adds one result as a json sub-object names Message
.
ResultAddOneMessage
                MsgInfo.CreateElement GIVING result:
                                USING *POSITION=CREATE_AS_LAST_CHILD:
                                *LABEL="Message":
                                *JSONTYPE=JSON_TYPE_OBJECT:
                                *OPTIONS=MOVE_TO_CREATED_NODE

                MsgInfo.CreateElement GIVING result:
                                USING *POSITION=CREATE_AS_FIRST_CHILD:
                                *LABEL="id":
                                *TEXT=MsgId:
                                *JSONTYPE=JSON_TYPE_STRING:
                                *OPTIONS=MOVE_TO_CREATED_NODE

                MsgInfo.CreateElement GIVING result:
                                USING *POSITION=CREATE_AS_NEXT_SIBLING:
                                *LABEL="to":
                                *TEXT=MsgTo:
                                *JSONTYPE=JSON_TYPE_STRING:
                                *OPTIONS=MOVE_TO_CREATED_NODE

                MsgInfo.CreateElement GIVING result:
                                USING *POSITION=CREATE_AS_NEXT_SIBLING:
                                *LABEL="from":
                                *TEXT=MsgFrom:
                                *JSONTYPE=JSON_TYPE_STRING

                MsgInfo.CreateElement GIVING result:
                                USING *POSITION=CREATE_AS_NEXT_SIBLING:
                                *LABEL="phoneNumber":
                                *TEXT=MsgPhone:
                                *JSONTYPE=JSON_TYPE_STRING


                MsgInfo.CreateElement GIVING result:
                                USING *POSITION=CREATE_AS_NEXT_SIBLING:
                                *LABEL="message":
                                *TEXT=MsgData:
                                *JSONTYPE=JSON_TYPE_STRING

                MsgInfo.MoveToNode USING *POSITION=MOVE_PARENT_NODE
                MsgInfo.MoveToNode USING *POSITION=MOVE_PARENT_NODE
                RETURN
 
....
. Fetch string data for String 'label'
. Only update the result if the label is found
.
FetchJsonStringValue FUNCTION
pXData          XDATA           ^
xLabel          DIM             50
dReturn         DIM             ^
                ENTRY
.
xString         DIM             200
x200            DIM             200
xError          DIM             100
nvar            FORM            2
....................

.....
. Find the specified JSON label node
.
                PACK            s$cmdlin, "label='",xLabel,"'"
                pXData.FindNode GIVING  nvar:
                                USING   *FILTER=S$cmdlin:               //Locate specified JSON label!
                                *POSITION=START_DOCUMENT_NODE   //Start at the beginning of the document!
                IF              ( nvar == 0 )
...
. Move to the child node of the 'orient' JSON label.
.
                pXData.MoveToNode GIVING nvar USING *POSITION=MOVE_FIRST_CHILD
.
                IF              ( nvar == 0 )
...
. Fetch the data for the JSON  label.
.
                pXData.GetText  GIVING xString
                PACK            s$cmdlin, xLabel,"= '",xString,"'"
                ELSE
                MOVE            "Error Move Node:", s$cmdlin
                ENDIF
                ELSE
                PACK            s$cmdlin, "Error Find Node:",nvar
                ENDIF

                TYPE            xString
                IF              NOT EOS
                MOVE            xString, dReturn
                ENDIF
.
                FUNCTIONEND
