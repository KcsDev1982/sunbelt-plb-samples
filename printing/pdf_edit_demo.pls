*---------------------------------------------------------------
.
. Program Name: pdf_edit_demo.pls
. Description:  Demonstration of edit fields in a PDF
.
. Revision History:
.
. Date: 05/22/2025
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc

*---------------------------------------------------------------

mainForm        PLFORM          pdf_edit_demo.plf

//
// Field Data
//
//      F=<flags>               .Field flags (EFFlagXxxx)
//      N=<Name>                .Field name
//      T=<type>                .Field edit type (EFTypeXxxx)
//      L=<length>              .Maximum length
//      B=<border>              .Broder styles (EFBdrXxxx)
//      X=<extra>               .Extra Commands
//      J=<javascript>          .JavaScript filter code for T=99
//
EFFlagNone      CONST           "0"     // Do not print this field
EFFlagPrint     CONST           "4"     // Allow field to be printed
.
EFTypeAll       CONST           "0"     // Any characters ( Default if 'B' only )
EFTypeNumInt    CONST           "1"     // Numeric digits only ( 0 through 9 )
EFTypeNum       CONST           "2"     // Numeric digits only ( 0 through 9 )
                                // + minus sign (-) + decimal point (.)
EFTypeLower     CONST           "3"     // Convert to lowercase as entered
EFTypeUpper     CONST           "4"     // Convert to uppercase as entered
EFTypeScript    CONST           "99"    // Use a custom JavaScript filter
.
EFBdrNone       CONST           "0"     // No border
EFBdrBasic      CONST           "1"     // Basic border
EFBdrUnder      CONST           "2"     // Basic border with underline
.
. /Q Values
.
EFAlnLeft       CONST           "0"     // Left-justified  ( Default )
EFAlnCenter     CONST           "1"     // Centered
EFAlnRight      CONST           "2"     // Right-justified
.
. /Ff Values
.
EFFmtMultiLine  CONST           "4096"
EFFmtPassword   CONST           "8192"
.
EditFieldData   DIM             4096
EditFieldExtra  DIM             1024
EditFieldJS     DIM             2048
.
LineEnd         INIT            0xd,0xa

// Data used to create a PDF file
pFile           PFILE
hdrFont         FONT
regFont         FONT
pdfFileName     INIT            "c:\sunbelt\edit_demo.pdf"

clrBlue         INTEGER         4,"0xFF8000"


// Data for load a PDF file from disk
pdfData         DIM             ^
pdfIsLoaded     BOOLEAN         FALSE


// Global data

firstName       DIM             40
lastName        DIM             40
userAddress     DIM             400
userSSN         DIM             11
userAge         DIM             2

// JavaScript for SSN Filter
JS_SSN          INIT            "if(!event.willCommit)",0xd,0xa:
                                "{",0xd,0xa:
                                " if( ( ( event.selStart == 3 ) || ( event.selStart == 6 ) ) && ( event.change != '-' ) )",0xd,0xa:
                                " {",0xd,0xa:
                                "   event.change = '-';",0xd,0xa:
                                " }",0xd,0xa:
                                "( event.rc = !isNaN(event.change) && event.selStart == 0 ) || ",0xd,0xa:
                                "( event.rc = !isNaN(event.change) && event.selStart == 1 ) ||",0xd,0xa:
                                "( event.rc = !isNaN(event.change) && event.selStart == 2 ) ||",0xd,0xa:
                                "( event.rc = ( event.change == '-' && event.selStart == 3 ) ) ||",0xd,0xa:
                                "( event.rc = !isNaN(event.change) && event.selStart == 4 ) ||",0xd,0xa:
                                "( event.rc = !isNaN(event.change) && event.selStart == 5 ) ||",0xd,0xa:
                                "( event.rc = ( event.change == '-' && event.selStart == 6 ) ) ||",0xd,0xa:
                                "( event.rc = !isNaN(event.change) && event.selStart == 7 ) ||",0xd,0xa:
                                "( event.rc = !isNaN(event.change) && event.selStart == 8 ) ||",0xd,0xa:
                                "( event.rc = !isNaN(event.change) && event.selStart == 9 ) ||",0xd,0xa:
                                "( event.rc = !isNaN(event.change) && event.selStart == 10 );",0xd,0xa:
                                "}"

*................................................................
.
. Code start
.
                WINHIDE
                CALL            Main
                LOOP
                EVENTWAIT
                REPEAT
                STOP
*................................................................
.
. Load a PDF file into a buffer
.
LoadPdfFile     LFUNCTION
fileName        DIM             ^
                ENTRY
winTitle        DIM             200                                             //Erb
pdfFile         FILE
seq             FORM            "-1"
fileSize        INTEGER         4

*
.Cleanup any previous load
.
                dlExtracted.ResetContent

                IF              (pdfIsLoaded)
                DFREE           pdfData
                CLEAR           pdfIsLoaded
		SETPROP		btnExtract,ENABLED=pdfIsLoaded
                ENDIF
*
.Get the file size
.
                FINDFILE        fileName,FileSize=fileSize
                RETURN          if Not Zero
*
.Catch empty file
.
                IF              (!fileSize)
                RETURN
                ENDIF
*
.Open the file
.
                EXCEPTSET       noFile if IO
                OPEN            pdfFile,fileName,READ
                EXCEPTCLEAR     IO
*
.Allocate the buffer
.
                DMAKE           pdfData,fileSize
                IF              Zero
                CLOSE           pdfFile
                RETURN
                ENDIF
*
.Retrieve the PDF data
.
                READ            pdfFile,seq;*Abson,pdfData
                CLOSE           pdfFile
                SET             pdfIsLoaded
.
                PACK            winTitle, "PDF Edit Demo  Loaded PDF: '",fileName,"'"
                SETPROP         frmDemo, TITLE=winTitle
		SETPROP		btnExtract,ENABLED=pdfIsLoaded
                RETURN
*
. Just return on an I/O error
.
noFile
                PACK            winTitle, "PDF Edit Demo  Unable to load PDF: '",fileName,"'"
                SETPROP         frmDemo, TITLE=winTitle                                                                                                                 //Erb
                FUNCTIONEND

*................................................................
.
. Fetch a current value for a named field from a PDF file
.
FetchPdfValue   LFUNCTION
fileData        DIM             ^
fieldName       DIM             ^
outValue        DIM             ^
                ENTRY
scanName1       DIM             100
scanName2       INIT            "/Type/Annot/V("
bumpSize        INTEGER         2
scanFP          INTEGER         2
curLen          INTEGER         2

*
. Just return if PDF is not loaded
.
                RETURN          IF (!pdfIsLoaded)
*
. Setup for scan
.
                RESET           fileData
                MOVELPTR        fileData,curLen
                RESET           outValue
                CHOP            fieldName
*
. Look for V field (value) Eg.
. /Subtype/Widget/T(FirstName) ... /Type/Annot/V(
. and extract data between ( and )
.
                PACK            scanName1,"/Subtype/Widget/T(",fieldName,")"
                COUNT           bumpSize,scanName2
                CLEAR           scanFP
.
. Make sure we find the last instance of the value
.
                LOOP
                SCAN            scanName1, fileData
                WHILE           EQUAL
                SCAN            scanName2, fileData
                WHILE           EQUAL

                BUMP            fileData,bumpSize
                MOVEFPTR        fileData,scanFP
                REPEAT
.
. Now extract out the data between the () brackets
.
                IF              (scanFP > 0)
                RESET           fileData,scanFP
                SCAN            ")", fileData
                IF              EQUAL
                BUMP            fileData,-1
                LENSET          fileData
                RESET           fileData,scanFP
                MOVE            fileData,outValue
                SETLPTR         fileData,curLen
                ENDIF
                ENDIF

                FUNCTIONEND

*................................................................
.
. Add Alignment
.
. /Q number
.
. Page 434      Text justification
.
AddPdfAlign     LFUNCTION
Type            FORM            1
                ENTRY
alnCmd          DIM             10
                PACK            alnCmd, "/Q ",Type," ",LineEnd
                APPEND          alnCmd,EditFieldExtra
                FUNCTIONEND
*................................................................
.
. Add Apperance
.
. /MK << /BC [0 1 0] /BG [1 1 1] >>  %Set Border color and Background color
.
. Page 408-409  Appearance characteristics
.
AddPdfAppear    LFUNCTION
Appearance      DIM             100
                ENTRY
appCmd          DIM             120
                PACK            appCmd, "/MK << ",Appearance," >>",LineEnd
                APPEND          appCmd,EditFieldExtra
                FUNCTIONEND

*................................................................
.
. Add border style
.
. /BS << /W .2 /S /U >>       %Border style width and underline
.
. Page 386      12.5.4 Border Styles
.
AddPdfBdrStyle  LFUNCTION
Style           DIM             100
                ENTRY
styleCmd        DIM             120
                PACK            styleCmd, "/BS << ",Style," >>",LineEnd
                APPEND          styleCmd,EditFieldExtra
                FUNCTIONEND

*................................................................
.
. Add default text field value
.
. /DA (1 0 0 rg /Ti 12 Tf)    %Set FG color and Font size
.
. Page 434      The default appearance
.
AddPdfDefAppear LFUNCTION
Appear          DIM             100
                ENTRY
appCmd          DIM             120
                PACK            appCmd, " /DA (",Appear,")",LineEnd
                APPEND          appCmd,EditFieldExtra
                FUNCTIONEND
*................................................................
.
. Add ToolTip
.
. /TU (Numeric digits only!)
.
. Page 433
.
AddPdfToolTip   LFUNCTION
Tip             DIM             80
                ENTRY
tipCmd          DIM             100

                PACK            tipCmd, " /TU (",Tip,")",LineEnd
                APPEND          tipCmd,EditFieldExtra
                FUNCTIONEND

*................................................................
.
. Add Format Flags
.
. /Ff number
.
. Page 433 and 443. See Table 221 and 228
.
AddPdfFFlags    LFUNCTION
Flags           FORM            8
                ENTRY
ffNum           DIM             10

                PACK            ffNum, Flags, LineEnd
                SQUEEZE         ffNum,ffNum
                APPEND          " /Ff ",EditFieldExtra
                APPEND          ffNum,EditFieldExtra
                FUNCTIONEND

*................................................................
.
. Add JavaScript
.
. /JS code
.
. Page 430      A text string or text stream containing the
.               JavaScript to be executed.
.
. Page 81 table 31. See Page 418 table 198.
.
AddPdfJS        LFUNCTION
JavaScript      DIM             ^
                ENTRY
                MOVE          JavaScript,EditFieldJS
                FUNCTIONEND
*................................................................
.
. Create a *EDIT
.
CreatePdfEdit   LFUNCTION
Type            FORM            2
Flag            FORM            8
Name            DIM             32
Border          FORM            4
Length          FORM            4
                ENTRY
valData         DIM             10
 
                CLEAR           EditFieldData,EditFieldExtra,EditFieldJS
                PACK            EditFieldData,"T=",Type,",F=",Flag,",N=",Name
                SQUEEZE         EditFieldData,EditFieldData
                ENDSET          EditFieldData

                IF              (Border > 0)
                PACK            valData,",B=",Border
                SQUEEZE         valData,valData
                APPEND          valData,EditFieldData
                ENDIF

                IF              (Length > 0)
                PACK            valData,",L=",Length
                SQUEEZE         valData,valData
                APPEND          valData,EditFieldData
                ENDIF
                FUNCTIONEND
*................................................................
.
. Print out a *EDIT
.
PrintPdfEdit    LFUNCTION
Prt             PFILE           ^
Pos             DIM             40
                ENTRY
size            FORM            5
posT            FORM            5
posB            FORM            5
posL            FORM            5
posR            FORM            5
 
                RESET           EditFieldExtra
                COUNT           size,EditFieldExtra
                IF              NOT ZERO
                APPEND          ",X=",EditFieldData
                APPEND          EditFieldExtra,EditFieldData
                ENDIF

                RESET           EditFieldJS
                COUNT           size,EditFieldJS
                IF              NOT ZERO
                APPEND          ",J=#"",EditFieldData
                APPEND          EditFieldJS,EditFieldData
                APPEND          "#"",EditFieldData
                ENDIF

                RESET           EditFieldData
                EXPLODE         Pos,":",posT,posB,posL,posR

                PRTPAGE         Prt; *EDIT=posT:posB:posL:posR:EditFieldData;
                FUNCTIONEND

*................................................................
.
. Create the PDF file. Page size is 8 1/2 by 11
.
CreatePdfFile   LFUNCTION
                ENTRY
.
winTitle        DIM             200
.
                dlExtracted.ResetContent
                PRTOPEN         pFile,"pdf:","Test PDF Edit Demo":
                                PDFNAME=pdfFileName:
                                FLAGS=1
.

                PRTPAGE         pFile; *UNITS=*LOENGLISH;

                PRTPAGE         PFILE;*FGColor=clrBlue,*Units=*Pixels,*PenSize=32,*Units=*LoEnglish:
                                *P=0:100,*Line=825:100

                PRTPAGE         PFILE; *FONT=hdrFont,*ALIGN=*CENTER,*P=412:19,"Editable Fields Sample"

                PRTPAGE         pFile; *ALIGN=*LEFT,*FONT=regFont, *FGColor=0,*P75:125,"First Name:";
                CALL            CreatePdfEdit using EFTypeAll,EFFlagPrint, "First_Name", EFBdrBasic, "40"
                CALL            PrintPdfEdit using pFile,"120:150:175:275"
.
                PRTPAGE         pFile; *P300:125,"Last Name:";
                CALL            CreatePdfEdit using EFTypeAll,EFFlagPrint, "Last_Name", EFBdrUnder, "40"
                CALL            PrintPdfEdit using pFile,"120:150:400:500"

                PRTPAGE         pFile; *P75:175,"Address:";
                CALL            CreatePdfEdit using EFTypeAll,EFFlagPrint, "User_Address", EFBdrNone, "400"
                CALL            AddPdfToolTip using "Enter the full address"
                CALL            AddPdfFFlags using EFFmtMultiLine
                CALL            AddPdfDefAppear Using "1 0 0 rg /Ti 12 Tf"
                CALL            PrintPdfEdit using pFile,"170:250:175:475"

                PRTPAGE         pFile; *P75:275,"SSN:";
                CALL            CreatePdfEdit using EFTypeScript, EFFlagNone, "User_SSN", EFBdrBasic, "11"
                CALL            AddPdfJS Using JS_SSN
                CALL            PrintPdfEdit using pFile,"270:300:175:325"

                PRTPAGE         pFile; *P75:325,"Age:";
                CALL            CreatePdfEdit using EFTypeNumInt, EFFlagPrint, "User_Age", EFBdrNone, "2"
                CALL            AddPdfAlign Using EFAlnRight
                CALL            AddPdfBdrStyle Using "/W 2 /S /I"
                CALL            PrintPdfEdit using pFile,"320:350:175:225"

                PACK            winTitle, "PDF Edit Demo  Created PDF: '",pdfFileName,"'"
                SETPROP         frmDemo, TITLE=winTitle

                FUNCTIONEND

*................................................................
.
. Make the PDF file
.
PDFMake         LFUNCTION
                ENTRY
                CALL            CreatePdfFile
                PRTCLOSE        pFile
                FUNCTIONEND

*................................................................
.
. Execute the PDF and then load the PDF file
.
PDFLoad         LFUNCTION
                ENTRY
                EXECUTE         pdfFileName
                CALL            LoadPdfFile using pdfFileName
                FUNCTIONEND

*................................................................
.
. Extract the fields out the the PDF file
.
PDFExtract      LFUNCTION
                ENTRY
dataLine        DIM             80

                dlExtracted.ResetContent

		RETURN          IF (!pdfIsLoaded)

                CALL            FetchPdfValue using pdfData, "First_Name", firstName

                PACK            dataLine, "First_Name -> ",firstName
                dlExtracted.AddString using dataLine
              
                CALL            FetchPdfValue using pdfData, "Last_Name", lastName
                PACK            dataLine, "Last_Name -> ",lastName
                dlExtracted.AddString using dataLine

                CALL            FetchPdfValue using pdfData, "User_Address", userAddress
                PACK            dataLine, "User_Address -> ", userAddress
                dlExtracted.AddString using dataLine

                CALL            FetchPdfValue using pdfData, "User_SSN", userSSN
                PACK            dataLine, "User_SSN -> ", userSSN
                dlExtracted.AddString using dataLine

                CALL            FetchPdfValue using pdfData, "User_Age", userAge
                PACK            dataLine, "User_Age -> ", userAge
                dlExtracted.AddString using dataLine
 

 
                FUNCTIONEND
*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
                CREATE          hdrFont,"Arial",SIZE=32
                CREATE          regFont,"Arial",SIZE=12
                FORMLOAD        mainForm
                FUNCTIONEND
