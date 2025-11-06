JsonObj       JSON
Result$       DIM 512
Age           FORM 5

* Parse incoming JSON
            JsonObj.Parse USING *JSON="{#"name#":#"John#",#"age#":42,#"active#":true}"

* Retrieve values
            JsonObj.GetString GIVING Result$ USING *NAME="name"
            DISPLAY Result$

            JsonObj.GetNumber GIVING Age USING *NAME="age"
            DISPLAY Age

* Modify JSON
            JsonObj.SetString USING *NAME="city", *VALUE="Denver"

* Export as JSON text
            JsonObj.GetString GIVING Result$ USING *NAME=""
            DISPLAY Result$

* Cleanup
            JsonObj.Reset
            PAUSE  "5"
