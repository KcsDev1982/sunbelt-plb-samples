*---------------------------------------------------------------
.
. Program Name: master
. Description:  Master program for conference
. 
. Revision History:
.
.   21 Jun 19   W Keech
.      Original code
.
*---------------------------------------------------------------
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc

signonPath      DIM             %100
httpRootPath    DIM             %100 // For downloads
httpRootPath1   DIM             %100 // For browser access 
urlPath         DIM             %100
signonName      DIM             %40

masterStarted   DIM             %1
mainWin         MAINWINDOW
result          FORM            5
mainForm        PLFORM          main.pwf


*................................................................
.
. Code start
.
                CALL            Main
                STOP
 
*................................................................
.
. FetchJsonStringValue - Fetch string data for String 'label'
. 
. Only update the result if the label is found
. 
FetchJsonStringValue LFUNCTION
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
                                USING *FILTER=S$cmdlin:  //Locate specified JSON label!
                                *POSITION=START_DOCUMENT_NODE //Start at the beginning of the document!
                IF              ( nvar == 0 )
...
. Move to the child node of the 'orient' JSON label.
. 
                pXData.MoveToNode GIVING nvar USING *POSITION=Move_FIRST_CHILD
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
.===============================================================================
CopyFile        LFUNCTION
inFile          DIM             ^
outFile         DIM             ^
                ENTRY
infoLine        DIM             100  

                EXCEPTSET       CopyFileError IF IO

                COPYFILE        inFile, outFile

                PACK            infoLine Using "Copied ", inFile, " to ", outFile
                ActionList.InsertString Using infoLine, 0
                RETURN
.
CopyFileError
                PACK            infoLine Using "Copy Error on ", inFile
                ActionList.InsertString Using infoLine, 0 
                FUNCTIONEND
 
*................................................................
.
. Download - Handles Download button
. 
Download        LFUNCTION
                ENTRY
outFile         DIM             300 //Output - User DIM to receive selected file!
scan            DIM             200 //Input  - Path on PWS server where input selection files are located.
prefix          DIM             50 //Input  - Prefix (example: prt_) or NULL
searchName      DIM             50 //Input  - Search named (example: '*.*', '*.pdf', ...etc
infoLine        DIM             80
oname           DIM             200
iname           DIM             200
client          CLIENT


                MOVE            "*.*", SearchName
                MOVE            signonPath To Scan
                CALLS           "webfileselect;StartProg" USING outFile: //Output - User DIM to receive selected file!
                                scan:  //Input  - Path where input selection files located.
                                prefix: //Input  - Prefix (example: prt_) or NULL
                                searchName //Input  - Search named (example: '*.*', '*.pdf', ...etc 
                TYPE            OutFile
                IF              NOT EOS 
                PACK            iname Using signonPath, "\", outFile 
                PACK            oname Using httpRootPath, "\", outFile 
                PACK            infoLine Using "Download ", oname
                ActionList.InsertString Using infoLine, 0
                CALL            CopyFile Using iname, oname
 
 
                PACK            oname Using urlPath, outFile 
                PACK            infoLine Using "Download ", oname
                ActionList.InsertString Using infoLine, 0
                client.Open     USING *URL=oname, *OPTIONS=1
                ENDIF
                FUNCTIONEND
*................................................................
.
. Chain - Handles Chain button
. 
Chain           LFUNCTION
                ENTRY
programName     DIM             40
infoLine        DIM             80
nvar            FORM            2
 
                EXCEPTSET       ChainIssue NORESET IF CFAIL  
                GETPROP         EditText1, TEXT=programName
                CHOP            programName
                TYPE            programName     
                IF              EOS    
                ALERT           NOTE,"Program Selection Not Specified!", nvar, "PLB Master"
                RETURN
                ENDIF
 
                CHAIN           programName
                RETURN
 
ChainIssue      PACK            infoLine, "'", programName, "' not found!"
                ALERT           NOTE,infoLine, nvar, "PLB Master Chain Error"
                UNPACK          "", S$ERROR$
                CHAIN           "master"
                FUNCTIONEND
*................................................................
.
. Compile - Handles Compile button
. 
Compile         LFUNCTION
                ENTRY
CmplerCmd       DIM             400
outFile         DIM             300 //Output - User DIM to receive selected file!
scan            DIM             200 //Input  - Path on PWS server where input selection files are located.
prefix          DIM             50 //Input  - Prefix (example: prt_) or NULL
searchName      DIM             50 //Input  - Search named (example: '*.*', '*.pdf', ...etc
infoLine        DIM             80
srcName         DIM             200
plcName         DIM             200
lstName         DIM             200
lstName1        DIM             200
urlName         DIM             200
client          CLIENT


                MOVE            "*.pls", SearchName
                MOVE            signonPath To Scan
                CALLS           "webfileselect;StartProg" USING outFile: //Output - User DIM to receive selected file!
                                scan:  //Input  - Path where input selection files located.
                                prefix: //Input  - Prefix (example: prt_) or NULL
                                searchName //Input  - Search named (example: '*.*', '*.pdf', ...etc 
                TYPE            OutFile
                IF              NOT EOS 
                PACK            srcName Using signonPath, "\", outFile 
                SCAN            "." In outFile
                LENSET          outFile
                RESET           outFile
                PACK            plcName Using signonPath, "\", outFile, "plc"
                PACK            lstName Using signonPath, "\", outFile, "lst"
                PACK            lstName1 Using httpRootPath1, "\", outFile, "lst"
                PACK            urlName Using urlPath, outFile, "lst"
                PACK            CmplerCmd Using "C:\SUNBELT\PLBWIN.101B\CODE\PLBWIN.EXE -I C:\SUNBELT\PLBWIN.101B\CODE\PLBWIN.INI PLBCMP #"":
                                srcName,"#",#"", plcName:
                                "#",#"",lstName,"#" -ZG,ZT,S,ZH,E,X,P #"TD#"" 

                ActionList.InsertString Using CmplerCmd, 0
                EXECUTE         CmplerCmd
 
                CALL            CopyFile Using lstName, lstName1
                client.Open     USING *URL=urlName
                ENDIF
 
.  FindFile
.
                FUNCTIONEND
*................................................................
.
. Upload - Handles Upload button
. 
Upload          LFUNCTION
                ENTRY
fileCount       FORM            5
pos             FORM            5
fname           DIM             200
oname           DIM             200
iname           DIM             200
infoLine        DIM             100
time            DIM             12
                CLOCK           TIME to time
                PACK            infoLine,"Upload started.... ",time
                ActionList.InsertString Using infoLine, 0
                Upload.GetFileCount Giving fileCount 
                SUB             "1" From fileCount
                FOR             pos From "0" TO fileCount
                Upload.GetFileItem Giving fname Using pos, 1
                PACK            iname Using "!", fname
                PACK            oname Using signonPath, "\", fname 
                CALL            CopyFile      Using iname, oname
                REPEAT
                CLOCK           TIME to time
                PACK            infoLine,"Upload complete.... ",time
                ActionList.InsertString Using infoLine, 0
                FUNCTIONEND
*................................................................
.
. Main - Main entry point
. 
Main            LFUNCTION
                ENTRY
nvar            FORM            2
infoLine        DIM             40
client          CLIENT
isCordova       FORM            1

                                // Make sure we have a valid path
                TYPE            signonPath
                IF              EOS
                SHUTDOWN
                ENDIF
 
                GETPROP         mainWin, Visible=Result
                IF              ( Result != 0 )
                WINHIDE
                ENDIF
 
                TYPE            masterStarted
                IF              EOS
                UNPACK          "",  S$ERROR$
                MOVE            "1",  masterStarted
                SEARCHPATH      ADD, signonPath
                ENDIF
 
                CHOP            S$ERROR$
                TYPE            S$ERROR$
                IF              NOT EOS
                ALERT           NOTE,S$ERROR$,NVAR,"PLB Master error recovery"
                UNPACK          "", S$ERROR$
                ENDIF
 
                SETMODE         *PercentConvert=1
                FORMLOAD        mainForm
                SETMODE         *PercentConvert=0

                client.GetState GIVING isCordova USING *STATEMASK=2
                IF              ( isCordova == 1 )
                SETPROP         WebForm1,Webwidth="100%"
                ENDIF
 
                                // Allow multiple files to be uploaded at one time
                Upload.SetFileOptions Using *Flags=1
                PACK            infoLine, "Hello ", signonName
                ActionList.InsertString Using infoLine, 0
                LOOP
                EVENTWAIT
                REPEAT
                FUNCTIONEND

