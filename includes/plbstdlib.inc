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
                PACK            s$cmdlin, "label='",xLabel,"'"
                pXData.FindNode GIVING nvar:
                                USING *FILTER=S$cmdlin:  	//Locate specified JSON label!
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
                PACK            s$cmdlin, xLabel,"= '",xString,"'"
                ELSE
                MOVE            "Error Move Node:", s$cmdlin
                ENDIF
                ELSE
                PACK            s$cmdlin, "Error Find Node:",nvar
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
