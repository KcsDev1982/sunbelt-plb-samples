
                INCLUDE             PLBEQU.INC

DataSet1        DATASET
JsonText        DIM                 200
FilterExpr      DIM                 100
FindRet         DIM                 200
Prefix7         DIM                 7
Idx             FORM                5
Key             DIM                 40
Flags           FORM                10

* Equates (normally from PLBEQU.INC) shown here for clarity only
DSF_ITEM_GET_ITEM_INFO      EQU     4       ;0x00000004
DSF_ITEM_GET_NEXT_ITEM      EQU     8       ;0x00000008
DSF_ITEM_GET_FILTER_SEARCH  EQU     32      ;0x00000020

                CREATE              DataSet1
                SETPROP             DataSet1, DATATYPE=$DST_JSON

*--------------------------------------------------------------*
* Load some JSON orders                                        *
*--------------------------------------------------------------*
                MOVE                "{""Orderid"":49,""Prodid"":44,""City"":""Houston"",""Quantity"":40}" TO JsonText
                DataSet1.AddItem    USING *Text=JsonText

                MOVE                "{""Orderid"":111,""Prodid"":50,""City"":""Denver"",""Quantity"":10}" TO JsonText
                DataSet1.AddItem    USING *Text=JsonText

                MOVE                "{""Orderid"":200,""Prodid"":42,""City"":""Houston"",""Quantity"":5}" TO JsonText
                DataSet1.AddItem    USING *Text=JsonText

*--------------------------------------------------------------*
* DATAFILTER: orders with Quantity < 15                        *
*--------------------------------------------------------------*
                MOVE                "Quantity < 15" TO FilterExpr
                SETPROP             DataSet1, DATAFILTER=FilterExpr

*--------------------------------------------------------------*
* Find first item matching the DATAFILTER                      *
*--------------------------------------------------------------*
                MOVE                "1" TO Idx
                MOVE                (DSF_ITEM_GET_ITEM_INFO+DSF_ITEM_GET_FILTER_SEARCH + DSF_ITEM_GET_NEXT_ITEM) TO Flags

                DataSet1.FindItem   GIVING FindRet USING *INDEX=Idx, *FLAGS=Flags

FindLoop
* If error, FindRet starts with "$ERROR$=nnn" (e.g., 4 or 5)    *
                MOVE                FindRet TO Prefix7
                IF                  (Prefix7 = "$ERROR$")
                        GOTO        Done
                ENDIF

                DISPLAY             *N, "Filter match info: ", FindRet

*--------------------------------------------------------------*
* Find next item matching the DATAFILTER                       *
*--------------------------------------------------------------*
               EXPLODE              FindRet, "," Into Key,Idx

                DataSet1.FindItem   GIVING FindRet USING *INDEX=Idx, *FLAGS=Flags

                GOTO                FindLoop

Done
                PAUSE               "5"
                STOP
