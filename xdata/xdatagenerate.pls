*---------------------------------------------------------------
.
. Program Name: xdatagenerate.pls
. Description:  Sample program using XDATA to create JSON/XML data
.
. Revision History:
.
. 2016-03-23 WHK
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*---------------------------------------------------------------
JsonOptToDisk   FORM            "6" // JSON_SAVE_USE_INDENT+JSON_SAVE_USE_EOR
XmlOptToDisk    FORM            "6" // XML_SAVE_USE_INDENT+XML_SAVE_USE_EOR
XmlOptToDiskNoHdr FORM          "7" // XML_SAVE_NO_DECLARATION+XML_SAVE_USE_INDENT+XML_SAVE_USE_EOR
.
JsonData        XDATA
Name            DIM             20
OutData         DIM             1000
*................................................................
.
. Code start
.
                CALL            Main
                STOP

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
.....
.
. Display the start
.
                WINSHOW
                MOVE            "Bill" To Name
                KEYIN           *ES,*HD,"Enter your name: ", *RV, Name

                JsonData.DeleteNode Using MOVE_DOCUMENT_NODE
.....
.
. Create the JSON root object
.
                JsonData.CreateElement Using MOVE_DOCUMENT_NODE, "object", *JsonType=JSON_TYPE_OBJECT, *Options=MOVE_TO_CREATED_NODE
.....
.
. Add an integer field
.
                JsonData.CreateElement Using MOVE_FIRST_CHILD, "value",*Text="1", *JsonType=JSON_TYPE_INTEGER 
.....
.
. Add a text field
.
                JsonData.CreateElement Using MOVE_LAST_CHILD, "FirstName",*Text=Name, *JsonType=JSON_TYPE_STRING 
.....
.
. Add an array
.
                JsonData.CreateElement Using MOVE_LAST_CHILD, "Actions", *Options=MOVE_TO_CREATED_NODE
                JsonData.CreateElement Using MOVE_FIRST_CHILD, "array", *JsonType=JSON_TYPE_ARRAY, *Options=MOVE_TO_CREATED_NODE
.....
.
. Add an object with a boolean field in the array
.
                JsonData.CreateElement Using MOVE_FIRST_CHILD, "object", *JsonType=JSON_TYPE_OBJECT, *Options=MOVE_TO_CREATED_NODE
                JsonData.CreateElement Using MOVE_FIRST_CHILD, "action",*Text="true", *JsonType=JSON_TYPE_BOOLEAN 

.....
.
. Add another object with a boolean field in the array
.
                JsonData.CreateElement Using MOVE_NEXT_SIBLING, "object", *JsonType=JSON_TYPE_OBJECT, *Options=MOVE_TO_CREATED_NODE
                JsonData.CreateElement Using MOVE_FIRST_CHILD, "action",*Text="false", *JsonType=JSON_TYPE_BOOLEAN 

.....
.
. Save to a file
.

                JsonData.SaveJson Using "t1.json", JsonOptToDisk 
                JsonData.SaveXML Using "t1.xml", XmlOptToDisk 
.....
.
. Display the result
.
                JsonData.StoreJson Giving OutData
		DISPLAY		"---------- JSON ---------- ",*N
                DISPLAY         *WRAPON, *LL, OutData
		DISPLAY		*N,"---------- XML ---------- ", *N
 		JsonData.StoreXml Giving OutData
                DISPLAY         *WRAPON, *LL, OutData
                KEYIN           *N,"Done (see t1.json,t1.xml):", Name

                FUNCTIONEND
................................................................................

