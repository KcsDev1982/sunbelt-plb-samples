*---------------------------------------------------------------
.
. Program Name: <name>
. Description:  <description>
.
. Revision History:
.
. <date> <programmer>
. Original code
.
. This program is created using 'CLASSMODULE'.
. In this case, this program can ONLY be accessed using public
. entry points ( FUNCTIONs ) included in this PL/B program.
.
*
. The 'CLASSMODULE' MUST be the first statement in this program
. logic.
. 
eStandAlone	EQU	0
.
		%IF eStandAlone = 0
		 CLASSMODULE	
		%ENDIF

                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*---------------------------------------------------------------
.
. All PL/B variables in this class module are private.
. COMMON variables are NOT ALLOWED in a class module.
. Only public access is through FUNCTIONs.
. CHAIN, TRAP, and Routine are not allowed.
. The class module can not be executed directly.
. LRoutine is allowed.

// <program wide variables>
nProp1Count	FORM		5

*................................................................
.
. Class Create
.
ClassCreate	FUNCTION		// PL/B CLASS 'CREATE <class>'
		ENTRY
		FUNCTIONEND

*................................................................
.
. Class Destroy
.
ClassDestroy	FUNCTION		// PL/B CLASS 'DESTROY <class>'
		ENTRY
		FUNCTIONEND

*................................................................
.
. Properties
.
Get_Prop1	FUNCTION		// PL/B CLASS 'GETPROP <class>, *Prop1=nvar'
         	ENTRY

		FUNCTIONEND	USING nProp1Count
.
Set_Prop1	FUNCTION		// PL/B CLASS 'SETPROP <class>, *Prop1=nvar'
ResetValue	FORM		5
       		ENTRY
.
		MOVE		ResetValue, nProp1Count
.
		FUNCTIONEND

*................................................................
.
. Methods
.
ZeroCount	FUNCTION	// PL/B CLASS Method 'doclass.ZeroCount GIVING RetOld' 
           	ENTRY
.
OldCount	FORM		5
.
		MOVE		nProp1Count, OldCount          	
		CLEAR		nProp1Count
.
           	FUNCTIONEND	USING OldCount

*................................................................
.
. Testing
.
		%IF eStandAlone = 1
		CALL		ClassCreate
		CALL		Get_Prop1 
		CALL		Set_Prop1 Using "5"
		CALL		ZeroCount
		%ENDIF
.
 
