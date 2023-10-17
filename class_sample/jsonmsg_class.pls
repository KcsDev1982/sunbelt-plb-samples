*---------------------------------------------------------------
.
. Program Name: jsonmsg_class
. Description:   This classmodule takes a JSON event message 
.		 ($JQueryEvent) and provides easy access to
.		 the message members.
.
. Revision History:
.
.   17 Jul 23   W Keech
.      Original code
.
. This program is created using 'CLASSMODULE'.
. In this case, this program can ONLY be accessed using public
. entry points ( FUNCTIONs ) included in this PL/B program.
.
*
. The 'CLASSMODULE' MUST be the first statement in this program
. logic.
.
eStandAlone     EQU             0
.
                %IF             eStandAlone = 0
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
JsonEvent       XDATA
JsonResult	DIM		100
JsonFlag	BOOLEAN

 		%IF             eStandAlone = 1
Data		DIM		100
		%ENDIF
*................................................................
.
. Class Create
.
ClassCreate     FUNCTION       
                ENTRY
                FUNCTIONEND

*................................................................
.
. Class Destroy
.
ClassDestroy    FUNCTION       
                ENTRY
		JsonEvent.Reset	
                FUNCTIONEND

*................................................................
.
. Properties
.
Get_type        FUNCTION        // The text event name
                ENTRY
		CALL            FetchJsonStr Using JsonEvent,"type",JsonResult
                FUNCTIONEND     USING JsonResult
.
Get_id          FUNCTION        // The 'id' name of the HTML object which generated the event
                ENTRY
		CALL            FetchJsonStr Using JsonEvent,"id",JsonResult
                FUNCTIONEND     USING JsonResult

Get_pageX       FUNCTION        // The X relative mouse position
                ENTRY
		CALL            FetchJsonStr Using JsonEvent,"pageX",JsonResult
                FUNCTIONEND     USING JsonResult

Get_pageY       FUNCTION        // The Y relative mouse position
                ENTRY
		CALL            FetchJsonStr Using JsonEvent,"pageY",JsonResult
                FUNCTIONEND     USING JsonResult

Get_metaKey     FUNCTION        // Flag if meta key state when event occurred
                ENTRY
		CALL            FetchJsonStr Using JsonEvent,"metaKey",JsonResult
		IF 		( NOCASE JsonResult = "true" )
		SET		JsonFlag
		ELSE
		CLEAR		JsonFlag
		ENDIF
                FUNCTIONEND     USING JsonFlag

Get_which       FUNCTION        // The key value or mouse button caused the event
                ENTRY
		CALL            FetchJsonStr Using JsonEvent,"which",JsonResult
                FUNCTIONEND     USING JsonResult

Get_target      FUNCTION        // The currentTarget id value that generated the event
                ENTRY
		CALL            FetchJsonStr Using JsonEvent,"target",JsonResult
                FUNCTIONEND     USING JsonResult

*................................................................
.
. Methods
.
ChangeMsg       FUNCTION        // Change message data to the supplied JSON string
JsonStr		DIM		^
                ENTRY
.
		JsonEvent.LoadJson Using JsonStr
.
                FUNCTIONEND

*................................................................
.
. Testing
.
                %IF             eStandAlone = 1
                CALL            ClassCreate
		CALL		ChangeMsg Using "66"
		CALL		ChangeMsg Using "{#"type#":#"click#",#"id#":#"sizzle#",#"pageX#":390,#"pageY#":96,#"metaKey#":false,#"which#":1,#"target#":#"sizzle#"}"
		CALL		Get_type Giving Data
		CALL		Get_id Giving Data
		CALL		Get_pageX Giving Data
		CALL		Get_pageY Giving Data
		CALL		Get_metaKey Giving Data
		CALL		Get_which Giving Data
		CALL		Get_target Giving Data
		CALL            ClassDestroy
                %ENDIF
.
 
