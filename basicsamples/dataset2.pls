
                INCLUDE             PLBEQU.INC

DataSet1        DATASET
JsonText        DIM                 500
JsonOut         DIM                 500
CustKey         DIM                 20
Flags           FORM                5

                CREATE              DataSet1
                SETPROP             DataSet1, DATATYPE=$DST_JSON

*--------------------------------------------------------------*
* Add first JSON object                                        *
*--------------------------------------------------------------*
                MOVE                "{""Name"":""John Doe"",""Age"":30,""Status"":""Active""}" TO JsonText
                MOVE                "CUST001"               TO CustKey

                DataSet1.AddItem    USING *Text=JsonText, *Key=CustKey

*--------------------------------------------------------------*
* Add second JSON object                                       *
*--------------------------------------------------------------*
                MOVE                "{""Name"":""Mary Smith"",""Age"":25,""Status"":""Active""}" TO JsonText
                MOVE                "CUST002"               TO CustKey

                DataSet1.AddItem    USING *Text=JsonText, *Key=CustKey

*--------------------------------------------------------------*
* Retrieve JSON for CUST001                                    *
*--------------------------------------------------------------*
                MOVE                "CUST001"               TO CustKey

                DataSet1.GetItem    GIVING JsonOut USING *KEY=CustKey
                DISPLAY             *N, "JSON Retrieved: ", JsonOut

*--------------------------------------------------------------*
* Update JSON for CUST001                                      *
*--------------------------------------------------------------*
                MOVE                "{""Name"":""John Doe"",""Age"":31,""Status"":""Active""}" TO JsonText

                DataSet1.UpdateItem    USING *Text=JsonText, *Key=CustKey   ; Replaces existing

                DataSet1.GetItem    GIVING JsonOut USING *KEY=CustKey
                DISPLAY             *N, "JSON Updated:   ", JsonOut

*--------------------------------------------------------------*
* Delete CUST002                                               *
*--------------------------------------------------------------*
                MOVE                "CUST002"               TO CustKey
                DataSet1.DeleteItem USING *KEY=CustKey

                DISPLAY             *N, "Deleted CUST002",*W5

                STOP
