*---------------------------------------------------------------
.
. Program Name: findfmt.pls
. Description:  Find the format for a text file using Byte Order Marks
.
. Revision History:
.
. Date: 07/29/2025
. Original code
.
file            FILE
bom1            INTEGER         1
bom2            INTEGER         1
bom3            INTEGER         1
bom4            INTEGER         1
fileName        DIM             80
seq             FORM            "-1"

                KEYIN           *ES, "Enter file name: ",fileName
                OPEN            file,fileName,Read
                READ            file,Seq;*ABSON,bom1,bom2,bom3,bom4
                CLOSE           file

                IF              (bom1 == 0xFF AND bom2 == 0XFE AND bom3 == 0 AND bom4 == 0)
                DISPLAY         "File Format: UTF-32 little-endian"
                ELSEIF          (bom1 == 0 AND bom2 == 0 AND bom3 == 0xFE AND bom4 == 0XFF)
                DISPLAY         "File Format: UTF-32 big-endian"
                ELSEIF          (bom1 == 0xFF AND bom2 == 0XFE)
                DISPLAY         "File Format: UTF-16 little-endian"
                ELSEIF          (bom1 == 0xFE AND bom2 == 0XFF)
                DISPLAY         "File Format: UTF-16 big-endian"
                ELSEIF          (bom1 == 0xEF AND bom2 == 0xBB AND bom3 == 0xBF )
                DISPLAY         "File Format: UTF-8"
                ELSE
                DISPLAY         "File Format: ASCII"
                ENDIF
                KEYIN           "Done: ",fileName
