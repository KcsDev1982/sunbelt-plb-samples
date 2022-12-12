*---------------------------------------------------------------
.
. Program Name: datatbl_tran
. Description:  Test DataTable Transactions
.
. Revision History:
.
. 22-10-19 whk
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*---------------------------------------------------------------
Table1          DATATABLE
MainForm        PLFORM          datatbl_tranf.pwf

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
. SetupTable
.
SetupTable      LFUNCTION
                ENTRY
                
                SETPROP         Table1, *Pagesize=10, *Context=$OC_PRIMARY 
                SETPROP         TABLE1,*MULTISELECT=$OFF,*GRIDLINE=$ON

                Table1.AddColumn Using 0
                Table1.AddColumn Using 1
                Table1.AddColumn Using 2
                Table1.AddColumn Using 3

                SETPROP         Table1.columns(0),*Title="Name", *WebWidth="180px", *ALIGNMENT=$LEFT, *ContentType=$TC_EDITABLE
                SETPROP         Table1.columns(1),*Title="Address", *WebWidth="180px", *ALIGNMENT=$LEFT, *ContentType=$TC_EDITABLE
                SETPROP         Table1.columns(2),*Title="Phone", *WebWidth="180px", *ALIGNMENT=$LEFT, *ContentType=$TC_EDITABLE        
                SETPROP         Table1.columns(3),*Title="Identity", *WebWidth="80px", *ALIGNMENT=$CENTER,COMPUTE="IDENTITY"    

                Table1.Commit

                Table1.HtmlBind Using HtmlTable, $HTML_STYLE_LISTVIEW

                FUNCTIONEND
               
*................................................................
.
. AddRec
.
AddRec          LFUNCTION
                ENTRY
RowId           FORM            5

                GETPROP         Table1,*ActiveRow=RowId
                Table1.AddRow   Using "Unknown", RowId
 
                FUNCTIONEND
*................................................................
.
. DelRec
.
DelRec          LFUNCTION
                ENTRY
RowId           FORM            5

                GETPROP         Table1,*ActiveRow=RowId
                Table1.DeleteRow Using RowId 
                FUNCTIONEND
*................................................................
.
. UndoRec
.
UndoRec         LFUNCTION
                ENTRY
                Table1.Undo
                FUNCTIONEND
*................................................................
.
. ComRec
.
ComRec          LFUNCTION
                ENTRY
                Table1.Commit
 
                FUNCTIONEND
*................................................................
.
. RolRec
.
RolRec          LFUNCTION
                ENTRY
                table1.Rollback
 
                FUNCTIONEND
*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
D20             DIM             20
                WINHIDE

                CREATE          Table1, *Striped=$ON,*Transaction=$ON
 
                FORMLOAD        MainForm
                CALL            SetupTable

                FUNCTIONEND
