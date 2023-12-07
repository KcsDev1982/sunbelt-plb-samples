*---------------------------------------------------------------
.
. Program Name: datatbl_card
. Description:  Test DataTable Cards
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
MainForm        PLFORM          datatbl_cardf.pwf
Cards           DATATABLE

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
                PACK            InfoLine with "Card Activate: ",Item
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
                PACK            InfoLine with "Button Click: ",Item, " Col: ", Subitem
                DataList1.InsertString Using InfoLine,0
                FUNCTIONEND
 
*................................................................
.
. SetupCards
.
SetupCards      LFUNCTION
                ENTRY
                
                CREATE          Cards

                Cards.AddColumn Using 0, *ContentType=$TC_HEADER
                Cards.AddColumn Using 1, *ContentType=$TC_TITLE
                Cards.AddColumn Using 2, *ContentType=$TC_DETAILS
                Cards.AddColumn Using 3, *ContentType=$TC_BUTTON1
                Cards.AddColumn Using 4, *ContentType=$TC_FOOTER  
                Cards.AddColumn Using 5

                SETPROP         Cards.columns(2), *ALIGNMENT=$CENTER     
 
                Cards.AddRow    USING "Featured":
                                *subitem1="Special title treatment":
                                *subitem2="With support text below as a natural lead-in to additional content.":
                                *subitem3="Go somewhere":
                                *subitem4="1 day ago"

                Cards.AddRow    USING "Featured":
                                *subitem1="Special title treatment":
                                *subitem2="With supporting text below as a natural lead-in to additional content.":
                                *subitem3="Go somewhere":
                                *subitem4="2 days ago"

                Cards.AddRow    USING "Featured":
                                *subitem1="Special title treatment":
                                *subitem2="With supporting text below as a natural lead-in to additional content.":
                                *subitem3="Go somewhere":
                                *subitem4="2 days ago"

                Cards.AddRow    USING "Featured":
                                *subitem1="Special title treatment":
                                *subitem2="With supporting text below as a natural lead-in to additional content.":
                                *subitem3="Go somewhere":
                                *subitem4="3 days ago"
                
                SETPROP         Cards.rows(2),*context=3

                EVENTREG        Cards,$ITEMACTIVATE,Do_Item
                EVENTREG        Cards,$UPDATED,Do_Update 
                FUNCTIONEND
 
*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY

                WINHIDE

                FORMLOAD        MainForm
                CALL            SetupCards
                Cards.HtmlBind  Using HtmlTable, $HTML_STYLE_CARD

                
                FUNCTIONEND
