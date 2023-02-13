*---------------------------------------------------------------
.
. Program Name: xdatahtml.pls
. Description:  Sample program using XDATA to read JSON/XML data
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
XmlData         XDATA
Name            DIM             200
OutData         DIM             1000
Result          FORM            8
MoveRes         FORM            8
Level           FORM            2
Count           FORM            2
Value           FORM            5
Label           DIM             40
Text            DIM             40
SysId           DIM             40
PubId           DIM             40
Target          DIM             40
LineCount       FORM            2
.
.
.
$O_FILTER$      FORM            "17" ;0x11 OPEN with user FILTER
Prompt          INIT            "Select File"
Path            DIM             200
Filter          INIT            "JSON,":
                                "JsonData(*.json),": ;1st comment
                                "*.json,": ;1st filter
                                "XmlData(*.xml),": ;2nd comment
                                "*.xml" ;2nd filter


*................................................................
.
. Code start
.
                CALL            Main
                STOP

*................................................................
.
. Show One Child
.
ShowChild       LFUNCTION
                ENTRY
                XmlData.MoveToNode Giving MoveRes Using MOVE_FIRST_CHILD 
                RETURN          IF ( MoveRes <> 0 )
                ADD             "1" TO Level
                CALL            DisplayOne
                CALL            ShowChild
                LOOP
                XmlData.MoveToNode Giving MoveRes Using MOVE_NEXT_SIBLING
                WHILE           ( MoveRes = 0 )
                CALL            DisplayOne
                CALL            ShowChild
                REPEAT
                XmlData.MoveToNode Using MOVE_PARENT_NODE
                SUB             "1" From Level
                FUNCTIONEND

*................................................................
.
. Display One Node
.
DisplayOne      LFUNCTION
                ENTRY
                IF              (LineCount = 20)
                KEYIN           "Next  20: ", Name
                MOVE            "0" TO LineCount
                ELSE
                ADD             "1" TO LineCount
                ENDIF
                MOVE            Level To Count
                LOOP
                DISPLAY         " ";
                SUB             "1" From Count
                BREAK           IF( Count = 0 ) 
                REPEAT
                XmlData.GetType Giving Value

                SWITCH          Value
 
                CASE            DOM_ELEMENT_NODE
                XmlData.GetLabel Giving Label
                DISPLAY         "ELEMENT   ", *LL, Label

                CASE            DOM_ATTRIBUTE_NODE
                XmlData.GetLabel Giving Label
                XmlData.GetText Giving Text
                DISPLAY         "ATTRIBUTE ", *LL, Label, "=", Text
   
                CASE            DOM_TEXT_NODE 
                XmlData.GetText Giving Text
                DISPLAY         "TEXT      ", *LL,Text

                CASE            DOM_PROCESSING_INSTRUCTION_NODE 
                XmlData.GetTarget Giving Target
                XmlData.GetData Giving Text
                DISPLAY         "PI     ", *LL, Target, " - ",  *LL, Text 

                CASE            DOM_COMMENT_NODE
                XmlData.GetComment Giving Text
                DISPLAY         "COMMENT   ", *LL, Text

                CASE            DOM_DOCUMENT_TYPE_NODE
 
                XmlData.GetComment Giving Text
                XmlData.GetName Giving Name
                XmlData.GetSysId Giving SysId
                XmlData.GetPubId Giving PubId
                DISPLAY         "DOCTYPE     ", *LL, Name, " - ",  *LL, SysId, " - ",  *LL, PubId 
 
                ENDSWITCH

                FUNCTIONEND
 
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
                MOVE            "t1.json" To Name
                KEYIN           *ES,*HD
                GETFNAME        Type=$O_FILTER$,Prompt,Name,Path,Filter
                STOP            IF OVER
.....
.
. Load the data
.
                IF              (Nocase Name Like "%.json")
                XmlData.LoadJson Giving Result Using Name, JSON_LOAD_FROM_FILE
                ELSE
                XmlData.LoadXml Giving Result Using Name, XML_LOAD_FROM_FILE
                ENDIF
                IF              (Result <> 0 )
                IF              (Result = 14 )
                XmlData.GetExtendedError Giving Name
                DISPLAY         Name
                ENDIF
                KEYIN           "Invalid file name or type.", Name
                STOP
                ENDIF
.....
.
. Show the tree
.
                MOVE            "1" TO Level
                MOVE            "0" TO LineCount
                CALL            ShowChild
                KEYIN           "Done (",*DV,*LL,NAME,"): ", Name
                STOP
                FUNCTIONEND
................................................................................
