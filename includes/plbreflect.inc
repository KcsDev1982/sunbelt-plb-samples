                   LISTOFF
.
                   %XREFOFF     ;DO NOT include in cross reference!!                   
.
                   %IFNDEF      $PLBREFL
$PLBREFL           EQU          1			;Flag that PLBREFL is used.
*==============================================================================
. PLB METHOD support definitions
.
. Last Revision Date:  20 Jan 2021
.
. Revision History:
.
                   %IFDEF       $PLBREFL_HISTORY     
                                          
.:: 10 Apr 20 - Create PLB reflection definitions.                       :10.3
.:: 20 Jan 21 - Modified the ReflDataLabel and ReflExecLabel 'name' 	 :10.3A
.:: 		member to have a size of 64 in support of PL/B labels
.:: 		in the PLBM meta data that are longer than 32 characters.

                   %ENDIF
*------------------------------------------------------------------------------
.
. Note:	 Sections added	to this	include	file are for user information
.	 for an	application.  This file	can be modified	and used to meet
.	 the requirements for any user application.
.
*------------------------------------------------------------------------------

*------------------------------------------------------------------------------
.   REFLECTION                                                               10.3
.
. Events:
.
.   none
.
. Properties:
.
.   none
.
. Methods:
.
.   CheckBuild      GIVING {nvar} USING *PlcName={svarslit}:                 
.                                       *Options={dnumnvar}      Optional   
.   ClearSymbols    GIVING {nvar} USING *Options={dnumnvar}      Optional
.   GetBuildInfo    GIVING {svar} USING *Options={dnumnvar}      Optional
.   GetCodeAdr      GIVING {svar} USING *Include={svarslit}:  
.                                       *LineNo={dnumnvar}:   
.                                       *Options={dnumnvar}      Optional 
.   GetCodeLoc      GIVING {svar} USING *Address={dnumnvar}:     
.                                       *Options={dnumnvar}      Optional 
.   GetConstant     GIVING {svar} USING *Label={svarslit}:       Optional
.                                       *Namespace={dnumnvar}:   Optional  
.                                       *Include={svarslit}:     Optional  
.                                       *Options={dnumnvar}      Optional    
.   GetErrorDesc    GIVING {svar} USING *Code={dnumnvar}
.   GetErrorInfo    GIVING {svar} USING *Options={dnumnvar}      Optional
.   GetEvent        GIVING {svar} USING *Name={svarslit}:        Optional
.                                       *Options={dnumnvar}      Optional 
.   GetFuncData    GIVING {svar} USING  *Label={svarslit}:       Optional
.                                       *Namespace={dnumnvar}:   Optional   
.                                       *Options={dnumnvar}      Optional    
.   GetFuncExec    GIVING {svar} USING  *Label={svarslit}:       Optional
.                                       *Namespace={dnumnvar}:   Optional   
.                                       *Options={dnumnvar}      Optional                                     
.   GetInclude      GIVING {svar} USING *Id={svarslit}:
.                                       *HashIndex={dnumnvar}:   Optional 
.                                       *Options={dnumnvar}      Optional 
.   GetKeyword      GIVING {svar} USING *Keyword={svarslit}:     Optional
.                                       *Options={dnumnvar}      Optional 
.   GetLabelData    GIVING {svar} USING *Label={svarslit}:       Optional
.                                       *Namespace={dnumnvar}:   Optional 
.                                       *Include={svarslit}:     Optional   
.                                       *Options={dnumnvar}      Optional 
.   GetLabelExec    GIVING {svar} USING *Label={svarslit}:       Optional
.                                       *Namespace={dnumnvar}:   Optional   
.                                       *Include={svarslit}:     Optional 
.                                       *Options={dnumnvar}      Optional 
.   GetMethod       GIVING {svar} USING *Name={svarslit}:        Optional
.                                       *Options={dnumnvar}      Optional 
.   GetObject       GIVING {svar} USING *Name={svarslit}:        Optional
.                                       *Options={dnumnvar}      Optional 
.   GetProp         GIVING {svar} USING *Name={svarslit}:        Optional
.                                       *Options={dnumnvar}      Optional 
.   GetRecord       GIVING {svar} USING *Label={svarslit}:       Optional 
.                                       *Namespace={dnumnvar}:   Optional   
.                                       *Options={dnumnvar}      Optional    
.   GetSymbolSource GIVING {svar} USING *Options={dnumnvar}      Optional                                  
.   LoadSymbols     GIVING {nvar} USING *Source={svarslit}:                 
.                                       *Options={dnumnvar}      Optional   
.
. Method Constants:
.
. ClearSymbols
.
REFL_CLEAR_ALL     EQU          1
.
. GetBuildInfo
.
REF_BUILD_LINE1    EQU          0
REF_BUILD_LINE2    EQU          1
REF_BUILD_LINE3    EQU          2
.
. GetEvent
.
REFL_NEXT_EVENT    EQU          1
.
. GetInclude
.
REFL_INC_RESET     EQU          1       // Reset to first include in symbol table
REFL_INC_BY_HASH   EQU          2       // Return source file specified by the HashIndex value
REFL_INC_LINKS     EQU          4       // Include Source links "nnnn (first data); mmmm (last data); rrrr (first exe); ssss (last exe) 
REFL_INC_BY_NAME   EQU          8       // Return source file specified by file name
REFL_INC_BY_ID     EQU          16      // Return source file specified by 2 character id
.
. GetKeyword
.
REFL_NEXT_KEYWORD  EQU          1
.
. GetMethod
.
REFL_NEXT_METHOD   EQU          1
.REFL_GET_PARTIAL   EQU          4	// Filter by partial label
.
. GetObject
.
REFL_NEXT_OBJECT   EQU          1
.
. GetProp
.
REFL_NEXT_PROP     EQU          1
.
. GetLabelData and GetLabelExec
.
REFL_GET_RESET     EQU          1	// Reset to first label name in symbol table
REFL_GET_INFUNC    EQU          2	// Return labels in functions as well
REFL_GET_PARTIAL   EQU          4	// Filter by partial label
REFL_GET_EXACT     EQU          8	// Fetch an exact label
REF_GET_FULL_DESC  EQU          16	// Fetch the full description
.
. GetFuncData and GetFuncExec
.
.REFL_GET_PARTIAL	EQU	4	// Filter by partial label
.REFL_GET_EXACT		EQU	8	// Fetch an exact label
.REF_GET_FULL_DESC	EQU	16	// Fetch the full description
.
. LoadSymbols
.
REF_LOAD_RESET     EQU          1	// Reload the file
REF_LOAD_SCAN      EQU          2	// Scan for .plc, .plbm, .lst
.
*------------------------------------------------------------------------------
. Data Label Record Definition (GetFuncData, GetLabelData, GetRecord)
. Fields separated by ; 
.
ReflDataLabel      RECORD       DEFINITION
symbol             DIM          32		// Symbol table name
name               DIM          64		// Name of label 
function           DIM          32		// Function name (blank if none)
namespace          FORM         8		// Namespace 
include            DIM          2		// Include identifier
lineNo             FORM         8		// Line number of declaration
type               DIM          1		// Type id
typeDesc           DIM          100		// Type description
isRecord           DIM          1		// Record indicator (Y or N)
recordLevel        FORM         2		// Record level
                   RECORDEND

*------------------------------------------------------------------------------
. Error Record Definition (GetErrorInfo)
. Fields separated by 0x7F 
.
ReflError          RECORD       DEFINITION
type               DIM          1		// (E)rror or (W)arning
include            DIM          2		// Include identifier
lineNo             FORM         8		// Line number of declaration
code               FORM         5		// Error code 
lineOffset         FORM         5		// Offset error starts at
line               DIM          1024		// Line data
                   RECORDEND
*------------------------------------------------------------------------------
. Event Record Definition (GetEvent)
. Fields separated by ; 
.
ReflEvent          RECORD       DEFINITION
name               DIM          32		// Event name
number             FORM         8		// Event number
                   RECORDEND

*------------------------------------------------------------------------------
. Execution Label Record Definition (GetFuncExec, GetLabelExec)
. Fields separated by ; 
.
ReflExecLabel      RECORD       DEFINITION
symbol             DIM          32		// Symbol table name
name               DIM          64		// Name of label 
function           DIM          32		// Function name (blank if none)
namespace          FORM         8		// Namespace 
include            DIM          2		// Include identifier
lineNo             FORM         8		// Line number of declaration
type               DIM          1		// Type id
typeDesc           DIM          100		// Type description
isFunction         DIM          1		// Function indicator (Y or N)
isExtern           DIM          1		// EXTERN indicator (Y or N)
alias              DIM          32		// EXTERN alias name
loadmod            DIM          250		// EXTERN load module name
entry              DIM          32		// EXTERN subroutine name
                   RECORDEND

*------------------------------------------------------------------------------
. Keyword Record Definition (GetKeyword, GetObject)
. Fields separated by :
.
ReflKeyword        RECORD       DEFINITION
name               DIM          32		// Keyword name
type               FORM         8		// Type (1-Execution, 2-Data, 4-Macro)
opCode             FORM         8		// Operation code
Syntax             DIM          100		// Syntax 
                   RECORDEND
*------------------------------------------------------------------------------
. Include Record Definition (GetInclude)
. Fields separated by ; 
.
ReflInclude        RECORD       DEFINITION
filename           DIM          256		// Name of file
include            DIM          2		// Include identifier
lineNo             FORM         8		// Line number of declaration
parentId           DIM          2		// Parent include identifier
                   RECORDEND

*------------------------------------------------------------------------------
. Method Record Definition (GetMethod)
. Fields separated by ; 
.
ReflMethod         RECORD       DEFINITION
name               DIM          32
syntax             DIM          1024
                   RECORDEND


*------------------------------------------------------------------------------
. Property Record Definition (GetProp)
. Fields separated by ; 
.
ReflProperty       RECORD       DEFINITION	
name               DIM          32
create             DIM          1 		// Create flag (C or blank)
get                DIM          1 		// Get flag (G or blank)
set                DIM          1 		// Set flag (S or blank)
syntax             DIM          40		// syntax
                   RECORDEND

*------------------------------------------------------------------------------
. Code Address Record Definition (GetCodeAdr,GetCodeLoc)
. Fields separated by ; 
.
ReflCodeAddr       RECORD       DEFINITION
filename           DIM          256		// Name of file
include            DIM          2		// Include identifier
lineNo             FORM         10		// Line number of declaration
address            FORM         10		// Address
                   RECORDEND

.
*------------------------------------------------------------------------------
                   %ENDIF       ;End $PLBREFL
.
                   %XREFON      ;Restore cross reference state flag                   
.
                   LISTON
