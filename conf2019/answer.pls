*---------------------------------------------------------------
.
. Program Name: answer
. Description:  Answer program for 2019 conference
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

signon          PLFORM          signon.pwf

userPath        INIT            "C:\sunbelt\td\"
userIsiName     DIM             260 
userFileName    DIM             260 
users           IFILE
userName        DIM             20
userPswd        DIM             20

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


*................................................................
.
. Logon - Get the name and check against a file
. 
Logon           LFUNCTION
                ENTRY
Name            DIM             20
Pswd            DIM             20
nvar            FORM            2
rootPath        DIM             100
saveToPath      DIM             40
runtime         RUNTIME

                HctlSignon.GetAttr Giving Name Using "uname", "value"
                HctlSignon.GetAttr Giving Pswd Using "psw", "value"
.
. Add code to lookup and verify
.
                READ            users,Name;userName,*LL, userPswd, signonName
                IF              Over
                ALERT           NOTE,"User name not found!", nvar, "PLB Answer"
                RETURN
                ENDIF
                IF              (Pswd == userPswd)
.
. All ok go to master 
.
                SETPROP         signonForm, *Visible=0
                PACK            signonPath, userPath, userName
                SQUEEZE         signonPath,signonPath," "
                runtime.GetDir  Giving rootPath Using 3
                runtime.GetDir  Giving saveToPath Using 5
                PACK            httpRootPath, rootPath, "\", saveToPath, "td\", userName
                SQUEEZE         httpRootPath,httpRootPath," "
                PACK            httpRootPath1, rootPath, "\td\", userName
                SQUEEZE         httpRootPath1,httpRootPath1," "
                PACK            urlPath, "td/",userName, "/"
                SQUEEZE         urlPath,urlPath," "
                STOP
                ENDIF
                ALERT           NOTE,"Invalid password!", nvar, "PLB Answer"
                FUNCTIONEND
*................................................................
.
. SignonEvent - Main event handler for the Signon form
. 
SignonEvent     LFUNCTION
                ENTRY
JsonData        DIM             4096
JsonEvent       XDATA
BtnId           DIM             20
 
                EVENTINFO       0, Arg1=JsonData
                JsonEvent.LoadJson Using JsonData
 
                CALL            FetchJsonStringValue Using JsonEvent,"id",BtnId
                SWITCH          BtnId
                CASE            "cancel"
                SHUTDOWN
                CASE            "logon"
                CALL            Logon
                CASE            "forgot"
                SHUTDOWN
                ENDSWITCH
                FUNCTIONEND
*................................................................
.
. Shutdown if not handle files
.
Shutdown
                SHUTDOWN
*................................................................
.
. Make Isam
.
MakeIsam        LFUNCTION
                ENTRY
attdFile        FILE
seq             FORM            "-1"
name            DIM             2
fullName        DIM             40
saveToPath      DIM             100
rootPath        DIM             100
httpRootPath    DIM             300
newPath         DIM             300
runtime         RUNTIME

                                // Get the http root and add a td direcoty
                runtime.GetDir  Giving rootPath Using 3
                PACK            httpRootPath1, rootPath, "\td"
                SQUEEZE         httpRootPath1,httpRootPath1," "
                PATH            Create Using httpRootPath1
 
                runtime.GetDir  Giving saveToPath Using 5
                PACK            httpRootPath, rootPath, "\", saveToPath, "td"
                SQUEEZE         httpRootPath,httpRootPath," "
                PATH            Create Using httpRootPath
 
                PATH            Create Using userPath
                TRAP            Shutdown If IO
                PACK            userFileName With userPath, "conf2019users.txt"
                OPEN            attdFile, userFileName 
 
                PACK            userFileName With userPath, "confusers.txt"
                PREP            users, userFileName, userIsiName, "20", "80"
                LOOP
                READ            attdFile,seq;name,fullName
                BREAK           If OVER
                MOVE            name To userName
                MOVE            "p" To userPswd
                WRITE           users,userName;userName,userPswd,fullName
                PACK            newPath, userPath, userName, "\"
                SQUEEZE         newPath,newPath," " 
                PATH            Create Using newPath
                PACK            newPath, httpRootPath, "\", userName, "\"
                SQUEEZE         newPath,newPath," " 
                PATH            Create Using newPath
                PACK            newPath, httpRootPath1, "\", userName, "\"
                SQUEEZE         newPath,newPath," " 
                PATH            Create Using newPath
                REPEAT
                FUNCTIONEND
*................................................................
.
. Main - Main entry point
. 
Main            LFUNCTION
                ENTRY
client          CLIENT
isCordova       FORM            1

                WINHIDE
                TRAP            MakeIsam If IO
                PACK            userIsiName With userPath, "confusers.isi"
                OPEN            users,userIsiName
                TRAPCLR         IO
                FORMLOAD        signon
                client.GetState GIVING isCordova USING *STATEMASK=2
                IF              ( isCordova == 1 )
                SETPROP         SignonForm,Webwidth="100%"
                ENDIF
                LOOP
                EVENTWAIT
                REPEAT
                FUNCTIONEND
