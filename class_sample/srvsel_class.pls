*---------------------------------------------------------------
.
. Program Name: srvsel_class
. Description:  This classmodule displays a Modal Dialog and allows an end-user to
.    to a select file that are to be downloaded from a PL/B Server.
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
.
*---------------------------------------------------------------
               
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

ClassForm       PLFORM          "webfileselectf.plf"

xSortCol        FORM            2(0..2), ("11"), ("7"), ("6")
.
D16000          DIM             16000
DEST            DIM             ^, D16000
.
LastScan        DIM             300 	// LASTSCAN_PATH configuration!
ScanPath        DIM             300 	// LASTSCAN_PATH configuration
.
CurPath         DIM             300 // File path
CurPrefix       DIM             300 // Prefix (example: prt_) or NULL
CurSearchName   DIM             300 // Search named (example: '*.*', '*.pdf', ...etc
CurOutFile      DIM             300

*................................................................
.
. Class Create
.
ClassCreate     FUNCTION       
                ENTRY
                PATH            CURRENT INTO CurPath
                MOVE            "*.*" INTO CurSearchName
                CLEAR           CurPrefix
                FORMLOAD        ClassForm
                FUNCTIONEND

*................................................................
.
. Class Destroy
.
ClassDestroy    FUNCTION        
                ENTRY
                DESTROY         SelectWin 
                FUNCTIONEND

*................................................................
.
. Properties
.
Get_Prefix      FUNCTION        // Get the current Prefix (example: prt_) or NULL
                ENTRY

                FUNCTIONEND     USING CurPrefix
.
Set_Prefix      FUNCTION        // Set the current Prefix (example: prt_) or NULL
NewPrefix       DIM             300
                ENTRY
.
                MOVE            NewPrefix, CurPrefix
.
                FUNCTIONEND

.
Get_Path        FUNCTION        // Get current file path
                ENTRY

                FUNCTIONEND     USING CurPath
.
Set_Path        FUNCTION        // Set the current file path
NewPath         DIM             300
                ENTRY
.
                MOVE            NewPath, CurPath
.
                FUNCTIONEND

Get_Search      FUNCTION        // Get the current Search named (example: '*.*', '*.pdf', ...etc
                ENTRY

                FUNCTIONEND     USING CurSearchName
.
Set_Search      FUNCTION        // Set the current Search named (example: '*.*', '*.pdf', ...etc
NewSearch       DIM             300
                ENTRY
.
                MOVE            NewSearch, CurSearchName
.
                FUNCTIONEND
 
*................................................................
.
. Methods
.
GetFileName     FUNCTION        // Method the request a filename
                ENTRY
Char1		DIM		1
fIsUnix         FORM            3  		// 99 --> Unix PLB runtime!
dPathChr        INIT            "\"  		// '\' --> Windows default
             
                TYPE            CurSearchName
                IF              EOS
                MOVE            "*.*", CurSearchName
                ENDIF

                TYPE            CurPath
                RETURN          IF EOS

                MOVE            CurPath, ScanPath

                CHOP            ScanPath, ScanPath
                TYPE            ScanPath
                RETURN          IF EOS

                GETMODE         *DISPFLUSH=fIsUnix 	// Shortcut to determine if Unix runtime being used.
                IF              ( fIsUnix == "99" )
                MOVE            "/", dPathChr 		//Unix path character
                ENDIF

                ENDSET          ScanPath
                MOVE            ScanPath, Char1
                IF              ( ( Char1 == "\" ) or ( Char1 == "/" ) )
                BUMP            ScanPath, -1
                LENSET          ScanPath
                RESET           ScanPath
                ELSE
                RESET           ScanPath
                ENDIF
                PACK            LastScan, ScanPath, dPathChr, CurPrefix, CurSearchName

                LISTVIEW1.DeleteAllItems

                CALL            LoadListView USING LastScan

                SETPROP         SelectWin, VISIBLE=1  //Modal Dialog
                GETPROP         SelectFileST, TEXT=CurOutFile

                FUNCTIONEND     USING CurOutFile


*................................................................
.
. Load up the listview with file names
.
LoadListView    LFUNCTION
SearchDir       DIM             200
                ENTRY
Char1		DIM		1
Char150		DIM		150
Char200		DIM		200
.
iCnt            INTEGER         4
Mode            INTEGER         4,"0x23" //Exclude: Hidden, Directories, Raw Write Time
.
FileName        DIM             150
TimeStamp	DIM             14
.
XDate           DIM             20
.
Y               DIM             2
YY              DIM             2
MM              DIM             2
DD              DIM             2
hh              DIM             2
mmm             DIM             2
sss             DIM             4
.
AmPm            DIM             2
.
fhh             FORM            2
.
.........................
.
                FINDDIR         SearchDir, DEST, MODE=Mode
                TYPE            DEST
                RETURN          IF EOS
                PACK            DEST, DEST, "|x" 

                LOOP

                EXPLODE         DEST,"|",Char200
                IF              ZERO
                BREAK
                ENDIF

                EXPLODE         Char200, ";", FileName, TimeStamp
                UNPACK          FileName, Char1, Char150
                UNPACK          TimeStamp, Y, YY, MM, DD, hh, mmm, sss
.
                MOVE            hh, fhh
                IF              ( fhh >= "12" )
                SUB             "12", fhh
                MOVE            fhh, hh
                REPLACE         " 0", hh
                MOVE            "PM", AmPm
                ELSE
                MOVE            "AM", AmPm
                ENDIF
.
                PACK            xDate, MM, "/", DD, "/", YY, "  ", hh, ":", mmm, " ", AmPm
.
                OR              0x20,Char1
.
                LISTVIEW1.InsertItemEx USING Char150, iCnt, *SubItem1=xDate, *SubItem2=TimeStamp
.
                REPEAT
.
                MOVE            "11", xSortCol(0)
                MOVE            "8", xSortCol(1)
                MOVE            "10", xSortCol(2) //Default to descending TIMESTAMP 2.40      2.40
                ListView1.SortColumn USING *COLUMN=2:
                                *TYPE=XSORTCOL(2):  //Pre-sort TimeStamp 2.40
                                *MASK="YYYYMMDDHHMMSS"
                FUNCTIONEND
*................................................................
.
. Handler for an item click
.
ItemClick       LFUNCTION
Result          FORM            10
                ENTRY
SelName         DIM             100
Minus1          INTEGER         4, "0xFFFFFFFF"
.
                RETURN          IF ( Result == Minus1 )
.
                CLEAR           SelName
                ListView1.GetItemText GIVING SelName USING Result
                TYPE            SelName
                RETURN          IF EOS
                SETPROP         SelectFileST, TEXT=SelName
                FUNCTIONEND
*................................................................
.
. Handler for a selection change
.
Change          LFUNCTION
Result          FORM            8
                ENTRY
SelName         DIM             100
Minus1          INTEGER         4, "0xFFFFFFFF"

                RETURN          IF ( Result == Minus1 )
 
                CLEAR           SelName
                ListView1.GetItemText GIVING SelName USING Result
                TYPE            SelName
                RETURN          IF EOS
   
                SETPROP         SelectFileST, TEXT=SelName
 
                FUNCTIONEND

*................................................................
.
. Handler for the OK button
.
ExitOK          LFUNCTION
                ENTRY
                SETPROP         SelectWin, VISIBLE=0
                FUNCTIONEND

*................................................................
.
. Handler for the CANCEL button
.
CanceL          LFUNCTION
                ENTRY
                SETPROP         SelectFileST, TEXT=""  //No file is selected!
                SETPROP         SelectWin, VISIBLE=0
                FUNCTIONEND

*................................................................
.
. Handler for a column click
.
ColClick        LFUNCTION
nCol            FORM            2
                ENTRY
.
......
.
xCol            FORM            2
nvar            FORM            2 //debug
.
                RETURN          IF ( nCol > 1 )
.
                ADD             "1", xSortCol(nCol)
.
                IF              ( nCol == 1 )

                ADD             "1", xSortCol(2) ;TIMESTAMP  2.40
                ADD             "1", nCol, xCol
.
                IF              ( xSortCol(nCol) > 8 ) 
                MOVE            "7", xSortCol(nCol)
                MOVE            "9", xSortCol(2)
                ENDIF

                ListView1.SortColumn USING *COLUMN=2, *TYPE=xSortCol(2):
                                *MASK="YYYYMMDDHHMMSS"
.
                ENDIF
.
                FUNCTIONEND

*................................................................
.
. Testing
.
                %IF             eStandAlone = 1
SampleOutName   DIM             300
                CALL            ClassCreate
                CALL            GetFileName Giving SampleOutName
                %ENDIF
.
...............................................................................
.
.
...............................................................................
.
