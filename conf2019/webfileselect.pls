*---------------------------------------------------------------
.
. Program Name: webfileselect
. Description:  This program displays a Modal Dialog and allows an end-user to
.    to a select file that are to be downloaded from a PL/B Web Server.
. 
. Revision History:
.
.   21 Jun 19   W Keech
.      Original code
.
*---------------------------------------------------------------
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc


PROGPLF         PLFORM          "webfileselectf.plf"
xSortCol        FORM            2(0..2), ("11"), ("7"), ("6")
D1              DIM             1
D150            DIM             150
D200            DIM             200
D16000          DIM             16000
DEST            DIM             ^, D16000
.
dName           DIM             150
TS              DIM             14
.
.
LoadListView    LFUNCTION
SearchDir       DIM             200
                ENTRY
.....
.
iCnt            INTEGER         4
Mode            INTEGER         4,"0x23" //Exclude: Hidden, Directories, Raw Write Time
.
xDate           DIM             20
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
.
                LOOP
.
                EXPLODE         DEST,"|",D200
                IF              ZERO
                BREAK
                ENDIF
....
.
                EXPLODE         D200, ";", dName, TS
                UNPACK          dName, D1, D150
                UNPACK          TS, Y, YY, MM, DD, hh, mmm, sss
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
                OR              0x20,D1
.
                LISTVIEW1.InsertItemEx USING D150, iCnt, *SubItem1=xDate, *SubItem2=TS
.
                REPEAT
.
                MOVE            "11", xSortCol(0)
                MOVE            "8", xSortCol(1)
                MOVE            "10", xSortCol(2) //Default to descending TIMESTAMP 2.40      2.40
                ListView1.SortColumn USING *COLUMN=2:
                                *TYPE=xSortCol(2):  //Pre-sort TimeStamp 2.40
                                *MASK="YYYYMMDDhhmmss"
.
                FUNCTIONEND

                STOP

pOutFile        DIM             ^ //Output - User DIM to receive selected file!
pScan           DIM             ^ //Input  - Path where input selection files located.
pPrefix         DIM             ^ //Input  - Prefix (example: prt_) or NULL
pSearchName     DIM             ^ //Input  - Search named (example: '*.*', '*.pdf', ...etc

LastScan        DIM             300 //LASTSCAN_PATH configuration!
ScanPath        DIM             300 //LASTSCAN_PATH configuration

dQuote          INIT            """"  //""""
fQuit           INTEGER         4
fIsUnix         FORM            3  //99 --> Unix PLB runtime!
dPathChr        INIT            "\"  // '\' --> Windows default

StartProg       ROUTINE         pOutFile, pScan, pPrefix, pSearchName

                MOVEPTR         pOutFile, pOutFile
                RETURN          IF OVER
                CLEAR           pOutFile
.
                MOVEPTR         pScan, pScan
                RETURN          IF OVER
.
                MOVEPTR         pPrefix, pPrefix
                RETURN          IF OVER
.
                MOVEPTR         pSearchName, pSearchName
                RETURN          IF OVER
                TYPE            pSearchName
                IF              EOS
                MOVE            "*.*", pSearchName
                ENDIF

                TYPE            pScan
                RETURN          IF EOS

                MOVE            pScan, ScanPath

                CHOP            ScanPath, ScanPath
                TYPE            ScanPath
                RETURN          IF EOS

                                // Shortcut to determine if Unix runtime being used.
 
                GETMODE         *DISPFLUSH=fIsUnix
                IF              ( fIsUnix == "99" )
                MOVE            "/", dPathChr //Unix path character
                ENDIF

                ENDSET          ScanPath
                MOVE            ScanPath, D1
                IF              ( ( D1 == "\" ) or ( D1 == "/" ) )
                BUMP            ScanPath, -1
                LENSET          ScanPath
                RESET           ScanPath
                ELSE
                RESET           ScanPath
                ENDIF
                PACK            LastScan, ScanPath, dPathChr, pPrefix, pSearchName

                TEST            SelectWin
                IF              ZERO
                FORMLOAD        ProgPlf
                ENDIF

                LISTVIEW1.DeleteAllItems

                CLEAR           fQuit

                CALL            LoadListView USING LastScan

                SETPROP         SelectWin, VISIBLE=1  //Modal Dialog

                CLEAR           fQuit
                RETURN


RES             FORM            10
MINUS1          INTEGER         4, "0xFFFFFFFF"
fMINUS1         FORM            "-1"
.
XNAME           DIM             100
XCNT            FORM            5
XCHK            FORM            3
XFIND           FORM            5
.
ItemClick       ROUTINE         RES
.
                RETURN          IF ( RES == MINUS1 )
.
                CLEAR           XNAME
                ListView1.GetItemText GIVING XNAME USING RES
                TYPE            XNAME
                RETURN          IF EOS
                SETPROP         SelectFileST, TEXT=XNAME
                RETURN
.
XRES            FORM            8
.
Change          ROUTINE         XRES
                RETURN          IF ( XRES == MINUS1 )
 
                CLEAR           XNAME
                ListView1.GetItemText GIVING XNAME USING XRES
                TYPE            XNAME
                RETURN          IF EOS
   
                SETPROP         SelectFileST, TEXT=XNAME
 
                RETURN
.....
.
ExitOK
                DEBUG
                MOVE            "1", fQuit
                SETPROP         SelectWin, VISIBLE=0
                GETPROP         SelectFileST, TEXT=pOutFile
ExitOKx         RETURN
.
.....
.
Cancel
                SETPROP         SelectFileST, TEXT=""  //No file is selected!
                MOVE            "1", fQuit
                SETPROP         SelectWin, VISIBLE=0
                RETURN
.

.
...............................................................................
.
ColClick        FUNCTION
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
                                *MASK="YYYYMMDDhhmmss"
.
                ENDIF
.
                FUNCTIONEND
.
...............................................................................
.
.
...............................................................................
.

