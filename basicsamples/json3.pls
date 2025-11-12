*===============================================================
.  JSONDATA Example with Object Variable
.  - Uses SetString, GetString, Store, Reset, Parse
*===============================================================

RuntimeObj     RUNTIME
JObj           JSON
JsonText$      DIM         1024
Temp$          DIM         64
Status         FORM        3

               CALL        Main
               PAUSE       "5"
               STOP

*----------------------------------------------------------------
Main           LFUNCTION
               ENTRY
*----------------------------------------------------------------
. Build JSON using the JSONDATA object variable JObj
*----------------------------------------------------------------
               JObj.SetString GIVING Status USING *NAME="Person.Name",    *VALUE="Alice"
               JObj.SetString GIVING Status USING *NAME="Person.Age",     *VALUE="30"
               JObj.SetString GIVING Status USING *NAME="Person.City",    *VALUE="North Bay"
               JObj.SetString GIVING Status USING *NAME="Person.Country", *VALUE="Canada"

*----------------------------------------------------------------
. Retrieve values with GetString (before Store/Parse)
*----------------------------------------------------------------
               JObj.GetString GIVING Temp$ USING *NAME="Person.Name"
               DISPLAY     *N,"[Original] Name   : ",Temp$

               JObj.GetString GIVING Temp$ USING *NAME="Person.City"
               DISPLAY     *N,"[Original] City   : ",Temp$

*----------------------------------------------------------------
. Store the JSON structure into JsonText$
*----------------------------------------------------------------
               JObj.Store   GIVING JsonText$

               DISPLAY     *N,"JSON stored text:"
               DISPLAY     *N,JsonText$

*----------------------------------------------------------------
. Reset JSONDATA object to clear all data
*----------------------------------------------------------------
               JObj.Reset   GIVING Status
               DISPLAY     *N,"JSONDATA object has been reset."

*----------------------------------------------------------------
. Parse the stored JSON back into JObj
*----------------------------------------------------------------
               JObj.Parse   GIVING Status USING *JSON=JsonText$

               IF          (Status <> 0)
                            DISPLAY *N,"ERROR: Parse failed, code = ",Status
                            GOTO   ExitMain
               ENDIF

*----------------------------------------------------------------
. Retrieve again with GetString (after Parse)
*----------------------------------------------------------------
               JObj.GetString GIVING Temp$ USING *NAME="Person.Country"
               DISPLAY     *N,"[Parsed]   Country: ",Temp$

               JObj.GetString GIVING Temp$ USING *NAME="Person.Age"
               DISPLAY     *N,"[Parsed]   Age    : ",Temp$

*----------------------------------------------------------------
ExitMain
               FUNCTIONEND
