*---------------------------------------------------------------
.
. Program Name: datatbl_lv
. Description:  Test DataTable ListView
.
. Revision History:
.
. <date> <programmer>
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 


*---------------------------------------------------------------
Table1          DATATABLE
 
OrderRec        RECORD
Id              DIM             4
CustomerId      DIM             5
ProductId       DIM             3
OrderDate       DIM             8
OrderTime       DIM             8
Quantity        DIM             5 
                RECORDEND
 
MainForm        PLFORM          datatbl_lvf.pwf


*................................................................
.
. Code start
.
                CALL            Main
                LOOP
                EVENTWAIT
                REPEAT
                STOP
*................................................................
.
. $ITEMACTIVATE Event
.
Do_Item         LFUNCTION
                ENTRY
EventResult     FORM            10
Item            FORM            5
SubItem         FORM            5
InfoLine        DIM             80
                EVENTINFO       0,RESULT=EventResult
                CALC            Item = ( EventResult / 100 )
                CALC            SubItem = ( EventResult - ( Item * 100 ) )
                PACK            InfoLine with "Item Activate: ",Item, " Col: ", Subitem
                DataList1.InsertString Using InfoLine,0
                FUNCTIONEND

*................................................................
.
. $UPDATED Event
.
Do_Update       LFUNCTION
                ENTRY
EventResult     FORM            10
Item            FORM            5
SubItem         FORM            5
InfoLine        DIM             80
                EVENTINFO       0,RESULT=EventResult
                CALC            Item = ( EventResult / 100 )
                CALC            SubItem = ( EventResult - ( Item * 100 ) )
                PACK            InfoLine with "Updated Row: ",Item, " Col: ", Subitem
                DataList1.InsertString Using InfoLine,0
                FUNCTIONEND
 
*................................................................
.
. $UPDATED Event
.
Do_ColClick     LFUNCTION
                ENTRY
ColumnNumber    FORM            10
InfoLine        DIM             80
                EVENTINFO       0,RESULT=ColumnNumber
                PACK            InfoLine with "ColClick ", ColumnNumber
                DataList1.InsertString Using InfoLine,0
                CALL            SortTable Using ColumnNumber
                FUNCTIONEND
*................................................................
.
. $DBLCLICK Event
. 
Do_DblClick	LFUNCTION
                ENTRY
EventResult     FORM            10
InfoLine        DIM             80
                EVENTINFO       0,RESULT=EventResult
		PACK            InfoLine with "Double click on Row: ",EventResult
                DataList1.InsertString Using InfoLine,0
                FUNCTIONEND

*................................................................
.
. $CHANGE Event
. 
Do_Change    	LFUNCTION
                ENTRY    
EventResult     FORM            10
InfoLine        DIM             80
                EVENTINFO       0,RESULT=EventResult
		PACK            InfoLine with "Changed Row: ",EventResult
                DataList1.InsertString Using InfoLine,0
                FUNCTIONEND

*................................................................
.
. SetupTable
.
SetupTable      LFUNCTION
                ENTRY
                
                SETPROP         Table1, *Pagesize=10, *Context=$OC_PRIMARY
                SETPROP         TABLE1,*MULTISELECT=$OFF,*GRIDLINE=$ON,*CHECKBOX=$ON 

                Table1.AddColumn Using 0
                Table1.AddColumn Using 1
                Table1.AddColumn Using 2
                Table1.AddColumn Using 3
                Table1.AddColumn Using 4
                Table1.AddColumn Using 5

                SETPROP         Table1.columns(0),*Title="Order Id", *WebWidth="40px", *ALIGNMENT=$LEFT
                SETPROP         Table1.columns(1),*Title="Customer Id", *WebWidth="80px", *ALIGNMENT=$CENTER
                SETPROP         Table1.columns(2),*Title="Product Id", *WebWidth="40px", *ALIGNMENT=$LEFT        
                SETPROP         Table1.columns(3),*Title="Order Date", *WebWidth="80px", *ALIGNMENT=$CENTER              
                SETPROP         Table1.columns(4),*Title="Order Time", *WebWidth="120px", *ALIGNMENT=$CENTER: 
                                *DataType=$CDT_TIME, *ContentType=$TC_EDITABLE,COMPUTE="CURTIME"           
                SETPROP         Table1.columns(5),*Title="Quantity", *WebWidth="80px", *ALIGNMENT=$RIGHT:
                                *DataType=$CDT_DECIMAL, *ContentType=$TC_EDITABLE 


                EVENTREG        Table1,$ITEMACTIVATE,Do_Item
                EVENTREG        Table1,$DBLCLICK,Do_DblClick
                EVENTREG        Table1,$UPDATED,Do_Update 
                EVENTREG        Table1,$COLCLICK,Do_ColClick
                EVENTREG        Table1,$CHANGE,Do_Change
                
                FUNCTIONEND
*................................................................
.
. LoadTable
.
LoadTable       LFUNCTION
                ENTRY
Orders          FILE
Seq             FORM            "-1"

                Table1.DeleteAllRows
 
                OPEN            Orders,"orders.txt"
 
                LOOP
                READ            Orders,Seq;OrderRec
                UNTIL           OVER
                REPLACE         " 0" IN OrderRec.OrderTime

                IF              (OrderRec.Id == "   1")
                Table1.AddRow   USING OrderRec.Id:
                                *subitem1=OrderRec.CustomerId:
                                *subitem2=OrderRec.ProductId:
                                *subitem3=OrderRec.OrderDate:
                                *subitem4=OrderRec.OrderTime:
                                *subitem5=OrderRec.Quantity, *Context=$OC_DANGER
                ELSE
                Table1.AddRow   USING OrderRec.Id:
                                *subitem1=OrderRec.CustomerId:
                                *subitem2=OrderRec.ProductId:
                                *subitem3=OrderRec.OrderDate:
                                *subitem4=OrderRec.OrderTime:
                                *subitem5=OrderRec.Quantity
                ENDIF
 
                REPEAT
                CLOSE           Orders
		CALL            SortTable Using "0"
                FUNCTIONEND
                
*................................................................
.
. SortTable
.
SortTable       LFUNCTION
ColumnNumber    FORM            2 
                ENTRY
                IF              ( ColumnNumber = 0 )
                Table1.Sort     USING ColumnNumber,1,*COL1=2
                ELSEIF          ( ColumnNumber = 1 )
                Table1.Sort     USING ColumnNumber,1,*COL1=0:
                                *COL2=2
                ELSEIF          ( ColumnNumber = 3 )
                Table1.Sort     USING ColumnNumber,5,"mm/dd/yy":
                                *Col1=2,*Type1=3
                ELSE
                Table1.Sort     USING ColumnNumber,1,*Col1=0
                ENDIF
                FUNCTIONEND
*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY

                WINHIDE

                CREATE          Table1, *Striped=$ON,*Transaction=$OFF
 
                FORMLOAD        MainForm
                CALL            SetupTable
                CALL            LoadTable
 
                Table1.HtmlBind Using HtmlTable, $HTML_STYLE_LISTVIEW

                
                FUNCTIONEND
