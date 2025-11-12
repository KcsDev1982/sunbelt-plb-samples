*===============================================================
.  JSONDATA Example - Array Handling with *INDEX1
.  ---------------------------------------------------------------
.  Demonstrates creating, storing, and reloading JSON arrays.
*===============================================================

RuntimeObj     RUNTIME
JObj           JSON
JsonText$      DIM         1024
Temp$          DIM         64
Status         FORM        3
Index          FORM        3

               CALL        Main
               PAUSE       "5"
               STOP

*----------------------------------------------------------------
Main           LFUNCTION
               ENTRY
*----------------------------------------------------------------
.---------------------------------------------------------------
. Build JSON array: Person.Phones[0..2]
.---------------------------------------------------------------
               JObj.SetString USING *NAME="Person.Name", *VALUE="Alice"

               JObj.SetString USING *NAME="Person.Phones[$1]", *INDEX1=0, *VALUE="705-555-1111"
               JObj.SetString USING *NAME="Person.Phones[$1]", *INDEX1=1, *VALUE="705-555-2222"
               JObj.SetString USING *NAME="Person.Phones[$1]", *INDEX1=2, *VALUE="705-555-3333"

*----------------------------------------------------------------
. Retrieve array elements using GetString
*----------------------------------------------------------------
               FOR        Index FROM 0 TO 2
                            JObj.GetString GIVING Temp$ USING *NAME="Person.Phones[$1]", *INDEX1=Index
                            DISPLAY *N,"Phone[",Index,"]: ",Temp$
               REPEAT

*----------------------------------------------------------------
. Store entire JSON structure
*----------------------------------------------------------------
               JObj.Store   GIVING JsonText$
               DISPLAY     *N,"JSON stored text:"
               DISPLAY     *N,JsonText$

*----------------------------------------------------------------
. Reset and Parse again
*----------------------------------------------------------------
               JObj.Reset   GIVING Status
               DISPLAY     *N,"JSONDATA object reset."

               JObj.Parse   GIVING Status USING *JSON=JsonText$
               IF          (Status <> 0)
                            DISPLAY *N,"Error parsing JSON. Code: ",Status
                            GOTO   ExitMain
               ENDIF

*----------------------------------------------------------------
. Retrieve again after Parse
*----------------------------------------------------------------
               FOR        Index FROM 0 TO 2
                            JObj.GetString GIVING Temp$ USING *NAME="Person.Phones[$1]", *INDEX1=Index
                            DISPLAY *N,"[Parsed] Phone[",Index,"]: ",Temp$
               REPEAT

*----------------------------------------------------------------
ExitMain
               FUNCTIONEND
