
                INCLUDE             PLBEQU.INC

DataSet1        DATASET
JsonText        DIM                 200
FilterExpr      DIM                 100
Result          DIM                 200
Prefix7         DIM                 7
Count           FORM                5
Index           FORM                5

                CREATE              DataSet1
                SETPROP             DataSet1, DATATYPE=$DST_JSON

*--------------------------------------------------------------*
* Load some JSON orders into the DATASET                       *
*--------------------------------------------------------------*
                MOVE                "{""Orderid"":49,""Prodid"":44,""City"":""Houston"",""Quantity"":40}" TO JsonText
                DataSet1.AddItem    USING *Text=JsonText

                MOVE                "{""Orderid"":111,""Prodid"":50,""City"":""Denver"",""Quantity"":10}" TO JsonText
                DataSet1.AddItem    USING *Text=JsonText

                MOVE                "{""Orderid"":200,""Prodid"":42,""City"":""Houston"",""Quantity"":5}" TO JsonText
                DataSet1.AddItem    USING *Text=JsonText

*--------------------------------------------------------------*
* Set DATAFILTER: only Houston orders                          *
*--------------------------------------------------------------*
                MOVE                "City='Houston'" TO FilterExpr
                SETPROP             DataSet1, DATAFILTER=FilterExpr

* Get the number of active items in the DATASET (COUNT prop)   *
                GETPROP             DataSet1, COUNT=Count

*--------------------------------------------------------------*
* Loop through all items and show only those matching filter   *
*--------------------------------------------------------------*
                FOR                 Index FROM "1" TO Count
                DataSet1.GetItem    GIVING Result USING *INDEX=Index

* Check if GetItem returned an error ($ERROR$=nnn)             *
                MOVE                Result TO Prefix7
                IF                  (Prefix7 = "$ERROR$")
                        CONTINUE
                ENDIF

                DISPLAY             *N, "Match (Houston): ", Result
                REPEAT
                PAUSE              "5"
                STOP
