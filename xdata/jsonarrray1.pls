*---------------------------------------------------------------
.
. Program Name: jsonarray
. Description:  Sample program to create a json array
.
. Revision History:
.
. 21-09-07 W Keech
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc

*---------------------------------------------------------------
xData           XDATA
OutData         DIM             4096
JsonOptToDisk	FORM		"6" // JSON_SAVE_USE_INDENT+JSON_SAVE_USE_EOR

*................................................................
.
. Code start
.
                CALL            Main
                STOP
 
*................................................................
.
. GenEmployee - Create a employee object
.
GenEmployee     LFUNCTION
firstName       DIM             ^
lastName        DIM             ^
                ENTRY
result          FORM            5

      		// Create a new employee object
      		// Use the label prefix object to prevent object labels in the array
      		
                xData.CreateElement giving result:
                                using *POSITION=CREATE_AS_LAST_CHILD:
                                *LABEL="objectEmployee":
                                *JSONTYPE=JSON_TYPE_OBJECT:
                                *OPTIONS=MOVE_TO_CREATED_NODE
                                           
        	// Add in the employee data
 
                xData.CreateElement giving result:
                                using *POSITION=CREATE_AS_FIRST_CHILD:
                                *LABEL="firstName":
                                *TEXT=firstName:
                                *JSONTYPE=JSON_TYPE_STRING:
                                *OPTIONS=MOVE_TO_CREATED_NODE
.
                xData.CreateElement giving result:
                                using *POSITION=CREATE_AS_NEXT_SIBLING:
                                *LABEL="lastName":
                                *TEXT="Doe":
                                *JSONTYPE=JSON_TYPE_STRING 
                                          
        	// Reposition to array node
        	
                xData.MoveToNode using *POSITION=MOVE_PARENT_NODE
                xData.MoveToNode using *POSITION=MOVE_PARENT_NODE
                FUNCTIONEND
*................................................................
.
. GenJson - Create a json file with an array of data
.
GenJson         LFUNCTION
                ENTRY
result          FORM            5
                xData.CreateElement giving result:
                                using *POSITION=CREATE_AS_FIRST_CHILD:
                                *LABEL="employees":
                                *JSONTYPE=JSON_TYPE_ARRAY:
                                *OPTIONS=MOVE_TO_CREATED_NODE
               
                CALL		GenEmployee using "Sam", "Smith"
                CALL		GenEmployee using "Tom", "Jones"
                CALL		GenEmployee using "Al", "Json"
                
	
                xData.SaveJson  using "testarray.json", JsonOptToDisk	
		xData.StoreJson Giving OutData
                DISPLAY         *WRAPON, *LL, OutData
                KEYIN           "Done (see testarray.json):", OutData	
                FUNCTIONEND
*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
                CALL            GenJson 
                FUNCTIONEND

.

.


