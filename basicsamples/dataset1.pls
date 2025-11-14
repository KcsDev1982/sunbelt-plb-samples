DataSet1        DATASET
TempText        DIM             200
ReturnVal       DIM             200
CustKey         DIM             20

                MOVE            "CUST001" TO CustKey
                MOVE            "Sample customer data" TO TempText

                DataSet1.AddItem USING *Text=TempText,*Key=CustKey

                DataSet1.GetItem GIVING ReturnVal USING *KEY=CustKey

                DISPLAY         *N,"Retrieved: ", ReturnVal,*W5

                DataSet1.DeleteItem USING *KEY=CustKey

                STOP
