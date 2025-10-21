                LISTOFF
.
                %XREFOFF        ;DO NOT include in cross reference!!
.
                %IFNDEF         $PLBSTDL
$PLBSTDL        EQU             1   ;Flag that PLBSTDL is used.
*==============================================================================
. PLB STANDARD LIBRARY FUNCTIONS
.
. Last Revision Date:  02 Oct 2020
.
. Revision History:
.
                %IFDEF          $PLBSTDL_HISTORY
                                          
.:: 10 Apr 20 - Create PLB standard library.                        :10.3
.:: 18 Mar 25 - Changed s$cmdlin to be S$CMDLIN to correct	    :10.7B
.:: 		compilation errors when doing a case sensitive
.:: 		compile.

                %ENDIF
*------------------------------------------------------------------------------


*................................................................
.
. FetchJsonStr - Fetch string data for String 'label'
.
. Only update the result if the label is found
.
FetchJsonStr    FUNCTION
pXData          XDATA           ^
xLabel          DIM             50
dReturn         DIM             ^
                ENTRY
.
xString         DIM             200
x200            DIM             200
xError          DIM             100
nvar            FORM            2
.
. Find the specified JSON label node
.
                PACK            S$CMDLIN, "label='",xLabel,"'"
                pXData.FindNode GIVING nvar:
                                USING *FILTER=S$CMDLIN:  	//Locate specified JSON label!
                                *POSITION=START_DOCUMENT_NODE 	//Start at the beginning of the document!
                IF              ( nvar == 0 )
...
. Move to the child node of the 'orient' JSON label.
.
                pXData.MoveToNode GIVING nvar USING *POSITION=MOVE_FIRST_CHILD
.
                IF              ( nvar == 0 )
...
. Fetch the data for the JSON  label.
.
                pXData.GetText  GIVING xString
                PACK            S$CMDLIN, xLabel,"= '",xString,"'"
                ELSE
                MOVE            "Error Move Node:", S$CMDLIN
                ENDIF
                ELSE
                PACK            S$CMDLIN, "Error Find Node:",nvar
                ENDIF

                TYPE            xString 
                IF              NOT EOS
                MOVE            xString, dReturn
                ENDIF
 
                FUNCTIONEND
 
.
*------------------------------------------------------------------------------
                %ENDIF          ;End $PLBSTDL
.
                %XREFON         ;Restore cross reference state flag
.
                LISTON
