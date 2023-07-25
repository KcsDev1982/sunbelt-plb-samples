...............................................................................
. This program uses the directory '.\restapi' for the
. REST working directory.
. 
. Purpose:
.    This program has been modified from the original program
.    named 'phonemsgorg.pls' so it expects to be located in
.    directory relative to the 'plbwebsrv.105A\code' directory
.    as follows:
.    
.       c:\sunbelt\plbwebsrv.105A\code\
.
.    Note:
.       1. This program can ONLY be executed so it works properly
.          when using a >9.9A PLBWIN, PLBNET, or PLB runtime.
.
. Date: 03/31/2017
.
...............................................................................
.
	include plbmeth.inc
.
Runtime		RunTime
F10		Form	"10"
Result		Form	8
.
CurDir		DIM	300		//ERB
CurDirRestApi	DIM	300		//ERB
.
HtmlData	Dim	4096

JsonOptToDisk		FORM	"6" // JSON_SAVE_USE_INDENT+JSON_SAVE_USE_EOR
.
. Message Data
.
MsgId		Dim	8
MsgTo		Dim	20
MsgFrom		Dim	20
MsgPhone	Dim	16
MsgData		Dim	200
.
.
.
PhoneMsgDb	DBFILE
SqlCommand	Dim	4096
SqlId		Form	8
.
.
GUI		FORM	2		//ERB
.
Request		Dim	40
Uri		Dim	400
UriSections	Form	3
UriParts	Dim	100(7)
Host		Dim	100
.
. XDATA Variables
.
MsgInfo		XDATA
MsgJson		Dim	40960
.
.
.
OptionHdr	Init	"Allow: GET,POST,PUT,DELETE,OPTIONS",0xD,0xA
LineTerm	Init	0xD,0xA
LocationHdr	Dim	200
*==============================================================================
. Set the CWD for the REST runtime.
.
	GETMODE	*GUI=GUI					//ERB
.
	IF ( GUI == 0 )						//ERB
.
	 PATH CURRENT, CurDir					//ERB
	 IF NOT OVER						//ERB
	  PACK	CurDirRestApi, CurDir, "/restapi/"		//ERB
	  PATH CHANGE, CurDirRestApi				//ERB
	  IF OVER						//Deb
;..	    ALERT NOTE, CurDirRestApi, Result, "Over"		//Deb
	  ELSE							//Eeb
;..	    ALERT NOTE, CurDirRestApi, Result, "Not Over..."	//Deb
	  ENDIF							//Deb
	 ENDIF							//ERB
.	
	ELSE							//ERB
.
	 PATH CURRENT, CurDir					//ERB
	 IF NOT OVER						//ERB
	  PACK	CurDirRestApi, CurDir, "\restapi\"		//ERB
	  PATH CHANGE, CurDirRestApi				//ERB
	  IF OVER						//Deb
;..	   ALERT NOTE, CurDirRestApi, Result, "Over"		//Deb
	  ELSE							//Eeb
;..	   ALERT NOTE, CurDirRestApi, Result, "Not Over..."	//Deb
	  ENDIF							//Deb
	 ENDIF							//ERB
.
	ENDIF							//ERB
.
...............................................................................
. Start by creating a default database if one is not availiable
.
	DbConnect	PhoneMsgDb, "SQLITE;;phonemsg.db","",""
	DbSend		PhoneMsgDb;"create table msgs(id integer primary key, msgto char(20), msgfrom char(20), msgphone char(16), msgdata char(200) )"
	Trap		SkipBuild IF DBFAIL
	DbExecute	PhoneMsgDb
	DbSend		PhoneMsgDb;"insert into msgs(msgto,msgfrom,msgphone,msgdata) values('bill', 'mike', '1-345-555-1212', 'Moved meeting to 12:00pm' )"
	DbExecute	PhoneMsgDb
	DbSend		PhoneMsgDb;"insert into msgs(msgto,msgfrom,msgphone,msgdata) values('bill', 'bob', '1-235-555-1212', 'Lunch tomorrow ?' )"
	DbExecute	PhoneMsgDb
	DbSend		PhoneMsgDb;"insert into msgs(msgto,msgfrom,msgphone,msgdata) values('bill', 'lazy bro', '1-995-555-1212', 'Need to borrow $10' )"
	DbExecute	PhoneMsgDb
SkipBuild
	NoReturn
.
. Decoding the reuested action
.
	IF ( GUI != 0 )
	 WinHide
	ENDIF
	Runtime.CgiString Giving Request Using "REQUEST_METHOD"
	Runtime.CgiString Giving Uri Using "REQUEST_URI"
	Runtime.CgiString Giving Host Using "HTTP_HOST"

.
. Break up URI to parts
.
	Explode Uri Using "/" Giving UriSections into UriParts

	Switch	Request	
	
	Case "DELETE"
		If (UriSections = 4 )
			CALL HandleDelete
		Else
		  Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
		Endif	

	Case "GET"
		If (UriSections = 5 )
		  CALL HandleGetName
		Else If (UriSections = 4 )
		  CALL HandleGetKey
		Else
		  CALL HandleGetAll
		Endif

	Case "OPTIONS"
		CALL HandleOptions

	Case "PATCH"
		CALL HandlePatch

	Case "POST"
		If (UriSections = 3 )
		  CALL HandlePost
		Else
		  Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
		Endif	

	Case "PUT"
		If (UriSections = 4 )
			CALL HandlePut
		Else
		  Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
		Endif	
		

	Default
		Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
	EndSwitch
	DbDisconnect PhoneMsgDb
	Stop

.
. DELETE /MyServices/phonemsg/2
.
. Deletes message based on primary key
.
HandleDelete
	pack SqlCommand Using "Delete from msgs where id=",UriParts(4)
	DbSend		PhoneMsgDb;SqlCommand
	DbExecute	PhoneMsgDb
	Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json", *Body=MsgJson, *ExtraHdrs="", *Options=0	
	Return
.
. GET /MyServices/phonemsg/search/Name
.
. Searches for messages sent to Name
.
.
HandleGetName
	UpperCase UriParts(4)
	Match UriParts(4) To "SEARCH"
	IF Equal
	  MsgInfo.Reset
	  MsgInfo.CreateElement GIVING result:
			USING *POSITION=CREATE_AS_FIRST_CHILD:
				  *LABEL="messages":
				  *JSONTYPE=JSON_TYPE_ARRAY:
				  *OPTIONS=MOVE_TO_CREATED_NODE
	  pack SqlCommand Using "Select id, msgto, msgfrom, msgphone, msgdata from msgs where lower(msgto)=lower('",UriParts(5),"') order by msgto"
	  DbSend		PhoneMsgDb;SqlCommand
	  DbExecute	PhoneMsgDb
	  Loop
	    Dbfetch		PhoneMsgDb,F10;MsgId, MsgTo, MsgFrom, MsgPhone, MsgData
	    UNTIL OVER
	    Call	ResultAddOneMessage
	    Repeat
	  MsgInfo.StoreJson Giving MsgJson
	  MsgInfo.Reset
	  Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json", *Body=MsgJson, *ExtraHdrs="", *Options=0
	Else
	  Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
	Endif
	Return
.
. GET /MyServices/phonemsg/2
.
. Retrieves message based on primary key
.
HandleGetKey
	Move UriParts(4) To SqlId
	IF ( SqlId > 0 )
	  MsgInfo.Reset
	  MsgInfo.CreateElement GIVING result:
			USING *POSITION=CREATE_AS_FIRST_CHILD:
				  *LABEL="messages":
				  *JSONTYPE=JSON_TYPE_ARRAY:
				  *OPTIONS=MOVE_TO_CREATED_NODE
	  pack SqlCommand Using "Select id, msgto, msgfrom, msgphone, msgdata from msgs where id=",SqlId," order by msgto"
	  DbSend		PhoneMsgDb;SqlCommand
	  DbExecute	PhoneMsgDb
	  Loop
	    Dbfetch		PhoneMsgDb,F10;MsgId, MsgTo, MsgFrom, MsgPhone, MsgData
	    UNTIL OVER
	    Call	ResultAddOneMessage
	    Repeat
	  MsgInfo.StoreJson Giving MsgJson
	  MsgInfo.Reset
	  Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json", *Body=MsgJson, *ExtraHdrs="", *Options=0
	Else
	  Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
	Endif
	Return
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
	DbSend		PhoneMsgDb;"Select id, msgto, msgfrom, msgphone, msgdata from msgs order by msgto"
	DbExecute	PhoneMsgDb
	Loop
	Dbfetch		PhoneMsgDb,F10;MsgId, MsgTo, MsgFrom, MsgPhone, MsgData
	UNTIL OVER
	Call	ResultAddOneMessage
	Repeat
	MsgInfo.StoreJson Giving MsgJson
	MsgInfo.Reset
	Runtime.HttpResponse Using *HttpCode=200,*MimeType="application/json":
				   *Body=MsgJson, *ExtraHdrs="", *OutFile="msg.out" *Options=0
	Return
.
. OPTIONS
.
. Return the supported actions
.
HandleOptions
	Runtime.HttpResponse Using *HttpCode=200,*MimeType="text/html", *Body="",*ExtraHdrs=OptionHdr, *Options=0
	return
.
. PATCH 
.
. Not supported - but could be like PUT
.
HandlePatch
	Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
	Return
.
. POST /MyServices/phonemsg
.
. Adds a new message
.
. Body contains json data object
. Primary key is return in Location: field
.
HandlePost
	Move	"unknown" To MsgTo
	Move	"unknown" To MsgFrom 
	Move	"unknown" To MsgPhone 
	Move	"None" To  MsgData
	Call	GetPostOrPutData	
	
	pack SqlCommand Using "insert into msgs(msgto,msgfrom,msgphone,msgdata) values('",MsgTo:
			       "', '",MsgFrom,"', '",MsgPhone,"', '",MsgData,"' )"
			       
	DbSend		PhoneMsgDb;SqlCommand
	DbExecute	PhoneMsgDb 
	DbSend		PhoneMsgDb;"select last_insert_rowid()"
	DbExecute	PhoneMsgDb 
	Dbfetch		PhoneMsgDb,F10;MsgId
	Pack	LocationHdr Using "Location: http://", Host, Uri, "/", MsgId, LineTerm
	Runtime.HttpResponse Using *HttpCode=201,*MimeType="text/html", *Body=" created", *ExtraHdrs=LocationHdr, *Options=0
	Return

.
. PUT /MyServices/phonemsg/2
.
. Updates message based on primary key
.
. Body contains json data object
.
HandlePut
	Move UriParts(4) To SqlId
	IF ( SqlId > 0 )
	  MsgInfo.Reset
	  MsgInfo.CreateElement GIVING result:
			USING *POSITION=CREATE_AS_FIRST_CHILD:
				  *LABEL="messages":
				  *JSONTYPE=JSON_TYPE_ARRAY:
				  *OPTIONS=MOVE_TO_CREATED_NODE
	  pack SqlCommand Using "Select id, msgto, msgfrom, msgphone, msgdata from msgs where id=",SqlId," order by msgto"
	  DbSend		PhoneMsgDb;SqlCommand
	  DbExecute	PhoneMsgDb
	  Dbfetch		PhoneMsgDb,F10;MsgId, MsgTo, MsgFrom, MsgPhone, MsgData
	  IF OVER
	    Runtime.HttpResponse Using *HttpCode=404,*MimeType="text/html", *Body="Not found" *ExtraHdrs="", *Options=0
	  Else
	    Call	GetPostOrPutData
	    pack	SqlCommand Using "Update msgs SET msgto='",MsgTo,"', msgfrom='", MsgFrom,"', msgphone='",MsgPhone:
					  "', msgdata='", MsgData,"' where id=",SqlId
	    DbSend	PhoneMsgDb;SqlCommand
	    DbExecute	PhoneMsgDb
	    Runtime.HttpResponse Using *HttpCode=204,*MimeType="text/html", *Body="" *ExtraHdrs="", *Options=0
	  Endif
	Else
	  Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
	Endif
	Return
.
. This function will get the HTML message body from STDIN. It will then use 
. the XDATA methods to extract the necessay fields.
.
GetPostOrPutData
	Stream	*STDIN,HtmlData
	MsgInfo.LoadJson Using HtmlData

	CALL	FetchJsonStringValue	USING	MsgInfo,"to",MsgTo
	CALL	FetchJsonStringValue	USING	MsgInfo,"from", MsgFrom 
	CALL	FetchJsonStringValue	USING	MsgInfo,"phoneNumber", MsgPhone 
	CALL	FetchJsonStringValue	USING	MsgInfo,"message", MsgData
	Return

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
	Return
	
....
. Fetch string data for String 'label'
. Only update the result if the label is found
. 
FetchJsonStringValue	FUNCTION
pXData			XDATA	^
xLabel			DIM	50
dReturn			DIM	^
			ENTRY
.
xString	DIM	200
x200	DIM	200
xError	DIM	100
nvar	FORM	2
....................

.....
. Find the specified JSON label node
. 
	PACK s$cmdlin, "label='",xLabel,"'"
	pXData.FindNode	GIVING	nvar:
			USING	*FILTER=S$cmdlin:		//Locate specified JSON label!
				*POSITION=START_DOCUMENT_NODE	//Start at the beginning of the document!
	IF ( nvar == 0 )
...
. Move to the child node of the 'orient' JSON label.
. 
	 pXData.MoveToNode GIVING nvar USING *POSITION=MOVE_FIRST_CHILD
.
	 IF ( nvar == 0 )
...
. Fetch the data for the JSON  label.
. 
	  pXData.GetText GIVING xString
	  PACK s$cmdlin, xLabel,"= '",xString,"'"
	 ELSE
	  MOVE "Error Move Node:", s$cmdlin
	 ENDIF
	ELSE
	 PACK s$cmdlin, "Error Find Node:",nvar
	ENDIF

	TYPE xString	
	IF NOT EOS
	 MOVE xString, dReturn
	ENDIF
.	
	FUNCTIONEND	
