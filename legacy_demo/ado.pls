*...........................................................................
.Example Program: TADO.PLS by BILL KEECH
.
. This file contains small samples of using Automation with
. Office95 or Office97
.
. Copyright @ 1998, Sunbelt Computer Systems, Inc.  All Rights Reserved.
.............................................................................
.
Form            PLFORM          ADO
.
Set             AUTOMATION
Fields          AUTOMATION
FieldArr        AUTOMATION      (25)
FieldC          FORM            2
BoolRes         INTEGER         4
Num             FORM            4
Pos             INTEGER         4
Data            DIM             50
CurIdx          FORM            5
ColPos          FORM            5
.
                WINHIDE
                FORMLOAD        Form
.
                LOOP
                WAITEVENT
                REPEAT
                STOP
LoadList
                SETMODE         *MCURSOR=*WAIT
.
. Creating access to the 'Active Data Object' interface named 'Recordset'.
.
                CREATE          Set,Class="ADODB.Recordset"
. 
. Using the 'Open' method, the dataset named 'SunbeltTest' is accessed to
. define the data collected as per the 'SQL' operation.  The DSN is defined
. in 'Settings\Control Panel\ODBC32' using the ODBC Data Source Administrator
. under the tab 'User DSN'.  In this case the SQL statement is accessing the
. data as retrieved from the 'customer' file specified to the SunbeltTest DSN.
. Change the following statement to suit your system.
.
		TRAP		OpenFail IF OBJECT
                Set.Open        Using "Select * from customer","DSN=SunbeltTest"
		TRAPCLR		OBJECT
.
. Associate the 'FIELDS' property data to the PLB AUTOMATION object named 
. 'Fields'.
.
                GETPROP         Set,*FIELDS=Fields
.
. Retrieve the total field count which is defined for the 'customer' file.
.
                GETPROP         Fields,*Count=FieldC
.
. Using the 'Item' method, then all data associated with a given field
. defined by the 'Fields' AUTOMATION object, is associated with a specific
. PLB AUTOMATION object defined in the PLB AUTOMATION array named 'FieldArr'.
.
                FOR             Num from "1" to FieldC
                Fields.Item     Giving FieldArr(Num) Using (Num-1)
                REPEAT
                DESTROY         Fields
.
. At this point we have an array of PLB AUTOMATION objects ( FieldArr ) 
. where each FieldArr AUTOMATION object defines the set of data associated
. with a given SQL field defined for the 'customer' file.
.
. Now accessing data for each field defined in the 'customer' file, we
. will move the field data to a PLB LISTVIEW presentation.
.
. Retrieve the field name from each PLB AUTOMATION FieldArr object and
. put the field name into the LISTVIEW column header names.
.
                FOR             Num from "1" to FieldC
                GETPROP         FieldArr(Num),*Name=Data
                SUB             "1" From Num Giving ColPos
                DataListV.InsertColumn Using Data, 100, ColPos
                REPEAT
.
. This loop accesses the data associated with each FieldArr AUTOMATION
. object and moves the data into the corresponding LISTVIEW column.
.
                Set.MoveFirst
                LOOP
                GETPROP         Set,*EOF=Num
                BREAK           if ( Num <> 0 )
                FOR             Num from "1" to FieldC
                GETPROP         FieldArr(Num),*Value=Data
                IF              (Num = 1)
                DataListV.InsertItem Giving CurIdx Using Data
                ELSE
                SUB             "1" From Num Giving ColPos
                DataListV.SetItemText Using CurIdx, Data, ColPos
                ENDIF
                REPEAT
                CHECKEVENT      // Just in case the "Halt" Button was pushed
                Set.MoveNext
                REPEAT
.
. Cleanup by destroying each of the FieldArr AUTOMATION objects.
.
                FOR             Num from "1" to FieldC
                DESTROY         FieldArr(Num)
                REPEAT
.
. Finish by closing and destroying the dataset AUTOMATION object named
. 'Set'.
.
                Set.Close
                DESTROY         Set
                SETMODE         *MCURSOR=*ARROW
                RETURN

.
. Unable to connect to the database
.
OpenFail

		ALERT		STOP,"Unable to access the ADO Database",Num,"Ado Sample"
		STOP
