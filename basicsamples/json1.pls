*---------------------------------------------------------------
. Parse a JSON object using the PL/B JSON object
*---------------------------------------------------------------

JsonStr       DIM                  100
EventType     DIM                  32
ObjectID      DIM                  64
MouseX        FORM                 6
MouseY        FORM                 6

json          JSON
rc            FORM                 3

*---------------------------------------------------------------
. Example input (simulating $JQueryEvent’s ARG1 payload)
*---------------------------------------------------------------
              MOVE                 "{#"type#":#"click#",#"id#":#"sizzle#",#"pageX#":390,#"pageY#":96}" TO JsonStr

*---------------------------------------------------------------
. Load JSON into the JSON object
*---------------------------------------------------------------
              json.Parse            USING JsonStr

*---------------------------------------------------------------
. Extract simple fields by key
*   NOTE: Field access is shown via GetText / GetNumber by key.
*         Adjust key names to match your payload.
*---------------------------------------------------------------
              json.GetString       GIVING EventType USING "type"
              json.GetString       GIVING ObjectID  USING "id"
              json.GetNumber       GIVING MouseX    USING "pageX"
              json.GetNumber       GIVING MouseY    USING "pageY"

*---------------------------------------------------------------
. Show results
*---------------------------------------------------------------
              DISPLAY              *N,"Event Type : ",EventType
              DISPLAY              *N,"Object ID  : ",ObjectID
              DISPLAY              *N,"Mouse X    : ",MouseX
              DISPLAY              *N,"Mouse Y    : ",MouseY,*W2

              STOP
