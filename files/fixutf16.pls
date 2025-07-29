*---------------------------------------------------------------
.
. Program Name: fixutf16.pls
. Description:  Convert a UTF16 file to ASCII file
.
. Revision History:
.
. Date: 07/29/2025
. Original code
.
jsonFile        FILE
jsonBuffer      DIM             ^
outBuffer       DIM             ^
fileSize        INTEGER         4
fullFileName    DIM             250
fileName        DIM             80
seq             FORM            "-1"

                KEYIN           *ES, "Enter file name: ",fileName
                OPEN            jsonFile,fileName,Read
                GETFILE         jsonFile,TxtName=fullFileName
                FINDFILE        fullFileName,FileSize=fileSize
                IF              (!fileSize)
                INCR            fileSize
                ENDIF
.
                DMAKE           jsonBuffer,fileSize
                DMAKE           outBuffer,fileSize
.
                READ            jsonFile,Seq;*ABSON,jsonBuffer

                BUMP            jsonBuffer,2
                CONVERTUTF      jsonBuffer,outBuffer,4

                CLOSE           jsonFile
                DFREE           jsonBuffer

                PREP            jsonFile,"output.txt"
                WRITE           jsonFile,Seq;outBuffer
                CLOSE           jsonFile

                KEYIN           "Done: ",fileName
