*............................................................................
.
.Example Program: WINAPI.PLS
.
.This sample programs demonstrates the use of the WINAPI instruction to
. to search for files using a user specified mask.
.
. Copyright @ 1997, Sunbelt Computer Systems, Inc.
. All Rights Reserved.
.............................................................................
.
. Revision History
.
. 10-6-98 JSS: Test System Info for GUI environment, use text based code
.               if not GUI.
. 10-6-98 JSS: FindFirst API needed to handle failure to find a match.
*............................................................................
.
. Include PROFILE declarations
.
                INCLUDE         PROFILE.INC
*
. FileData defines a DIM variable which will receive the names and
. properities of files which are found.  The FileData is a file data
. structure used within Windows.
.
FileData        DIM             400                     ;Name is at offset 44 + 260
FileAttr        INTEGER         4                       ;File Attributes
Extra           DIM             40                      ;
LongName        DIM             260                     ;
ShortName       DIM             14                      ;
.
Name            DIM             270
Ans             DIM             1
SmName          DIM             80
Term            INIT            0x0
.
FHANDLE         INTEGER         4                         ;File Handle
RESULT1         INTEGER         1                         ;Boolean result
RESULT          FORM            12
ST1             STATTEXT
ET1             EDITTEXT
ST2             STATTEXT
B1              BUTTON
BGC             COLOR
NOTE            DIM             70
LINE            FORM            "  3"
N10             FORM            10
MinusOne        FORM            "4294967295"        ; =0xffffffff
*............................................................................
                CREATE          BGC=*LTGRAY
.
.Retrieve the File Specification from the User
.
                CREATE          ST1=2:2:1:30,"Enter the File Specification: ":
                                "FIXED(BOLD)",ALIGNMENT=3
                CREATE          ET1=2:2:31:70,BGCOLOR=BGC
                CREATE          ST2=3:3:5:75,"","SYSTEM(10)"
                CREATE          B1=2:2:72:78,"OK"
                ACTIVATE        ST1
                ACTIVATE        ST2
                ACTIVATE        ET1
                ACTIVATE        B1,ET1CODE,RESULT
                SETFOCUS        ET1
                EVENTREG        ET1,11,ET1CODE
.         ACTIVATE  ET1,ET1CODE,RESULT
.
*
                LOOP
                WAITEVENT
                REPEAT
*
. Since the function 'FindFirstFileA' defines that string parameters
. must be terminated with a binary zero, we are appending a binary
. zero to the name keyed by the user.
.
ET1CODE
                GETITEM         ET1,0,SmName
                PACK            Name USING SmName,Term

                ALERT           NOTE,SmName,N10
*
. Execute the Windows Api function to find the first occurance of
. the file specification supplied by the user.
.
                WINAPI          FindFirst GIVING FHANDLE USING NAME,FileData
*
. If the return value identified as FHANDLE is zero or -1, then the file
. was not found.  In this case, this program simply exits.
.
                MOVE            FHANDLE,N10
                IF              ( FHANDLE = MinusOne )
                PACK            NOTE WITH "Name not found...",N10
                ALERT           STOP,NOTE,RESULT
                STOP
                ENDIF
 
*
. If we  get to this point, a file was found and the FHANDLE variable
. contains a file handle to be used in the 'FindNextFile' call later.
. The variable 'FileData' was modified to contain the names and properties
. of the file which was found. Note that we are using an UNPACK to 
. get the individual members of the 'FileData' structure.
.
                UNPACK          FileData INTO FileAttr:     ;File attributes
                                Extra:     ;Not used here
                                LongName:     ;Long file name found
                                ShortName     ;Short file name
 
*
. The FileAttr value found in the FileData structure identifies the
. type of file found.
.
                CALL            ShowName               ;Identify file type
*
. Now we want to loop and find all subsequent instances of the file name using
. the FindNext WINAPI function.
.
                LOOP
*
. Get the next file meeting the file name specifications given.
. Note: The FindNext PROFILE function uses the File Handle provided
. by the FindFirst PROFILE function.
.
                WINAPI          FindNext GIVING RESULT1 USING FHANDLE,FileData
.
. When the returned value found in RESULT1 is zero, then there are no more
. files   found using the file name specification.
.
                UNTIL           (RESULT1 = 0)
*
. At this point we have found another file and we will determine the
. file type.  We first unpack the FileData structure into the appropriate
. members to be used.
.
                UNPACK          FileData INTO FileAttr,Extra,LongName,ShortName
*
. The FileAttr value found in the FileData structure identifies the
. type of file found.
.
                CALL            ShowName                ;Identify File Type
*
. Continue the loop looking for the next file
.
                REPEAT
*
. Execute the function 'FindClose' to close the file handle provided
. by the 'FindFirstFile' function.
.
                WINAPI          FindClose GIVING RESULT1 USING FHANDLE
                ALERT           NOTE,"Complete...",RESULT
                STOP
*.........................................................................
. This subroutine determines the file type based on the value found
. in the FileAttr variable.
.
ShowName
.
. The LongName is an ASCIIZ terminated string.
. We want to find the end of the LongName and set the length pointer
. to the character before the binary zero termination character.
.
                SCAN            TERM,LongName
                BUMP            LongName, -1
                LENSET          LongName
                RESET           LongName
*
. Use the FileData structure FileAttr member to determine the type
. of file being used.
.
. FileAttr Values:
.    128 = Normal File
.     32 = Normal File with Archive Bit Set
.     16 = Directory
.
                ADD             "1",LINE
                IF              (LINE = 24)
                MOVE            "4",LINE
                ALERT           NOTE,"Continue....",N10
                ENDIF

                IF              (FileAttr = 128  | FileAttr = 32)
                MOVE            LongName TO NOTE
                DISPLAY         *P1:LINE,LongName
                ENDIF
.
                IF              (FileAttr = 16)
                PACK            NOTE WITH "Directory: ",LongName
                DISPLAY         *P1:LINE,"Directory: ",LongName
                ENDIF
.
                RETURN
