*---------------------------------------------------------------
.
. Program Name: xdatahtml.pls
. Description:  Sample program using XDATA to create HTML 5 page
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
HtmlPage        XDATA
Name            DIM             20
Line            DIM             100

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

.....
.
. Add the document type for HTML 5
.
                HtmlPage.CreateDocType Using MOVE_DOCUMENT_NODE, "html",*Options=MOVE_TO_CREATED_NODE
                HtmlPage.CreateElement Using CREATE_AS_NEXT_SIBLING, "html",*Options=MOVE_TO_CREATED_NODE
.....
.
. Create the head section
.
                HtmlPage.CreateElement Using CREATE_AS_FIRST_CHILD, "head",*Options=MOVE_TO_CREATED_NODE
.....
.
. Add the title
.
                HtmlPage.CreateElement Using CREATE_AS_LAST_CHILD, "title", "HTML 5 test file" 
.....
.
. Add the meta tag
.
                HtmlPage.CreateElement Using CREATE_AS_LAST_CHILD, "meta", *Options=MOVE_TO_CREATED_NODE
                HtmlPage.CreateAttribute Using CREATE_AS_FIRST_CHILD,"charset", "UTF-8"
                HtmlPage.MoveToNode Using MOVE_PARENT_NODE
.....
.
. Add some css for <h1> tag
.
                HtmlPage.CreateElement Using CREATE_AS_LAST_CHILD, "style", *Options=MOVE_TO_CREATED_NODE
                HtmlPage.CreateAttribute Using CREATE_AS_FIRST_CHILD,"type", "text/css"
                HtmlPage.CreateText Using CREATE_AS_LAST_CHILD, "h1 { color: red } "
                HtmlPage.MoveToNode Using MOVE_PARENT_NODE
.....
.
. Create the body section
.
                HtmlPage.CreateElement Using CREATE_AS_NEXT_SIBLING, "body",*Options=MOVE_TO_CREATED_NODE
.....
.
. Create an <h1> tag
.
                PACK            Line Using "Sample Html Page for ",Name
                HtmlPage.CreateElement Using CREATE_AS_LAST_CHILD, "h1", Line
.....
.
. Create an <p> tag
.
                HtmlPage.CreateElement Using CREATE_AS_LAST_CHILD, "p", "Paragraph 1"
.....
.
. Create a <p> with inner <strong> tag
.
                HtmlPage.CreateElement Using CREATE_AS_LAST_CHILD, "p", "Paragraph 2. ",*Options=MOVE_TO_CREATED_NODE
                HtmlPage.CreateElement Using CREATE_AS_LAST_CHILD, "strong", "Strong Text."
                HtmlPage.CreateText Using CREATE_AS_LAST_CHILD, "Paragraph 2 continues. "
.....
.
. Save to disk
.
                HtmlPage.SaveXml Using "t.html",*Options=XmlOptToDiskNoHdr
                KEYIN           "Hit return to display generated page. (t.html)", Name
                BATCH           "t.html"
                FUNCTIONEND
................................................................................
