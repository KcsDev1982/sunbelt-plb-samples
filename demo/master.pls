*---------------------------------------------------------------
.
. Program Name: master
. Description:  Sample master/dashboard program
.
. Revision History:
.
. 29 Aug 24 - Redesigned for version 10.7
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc

                CIFNDEF         $BS5_OPTION_NO_WINBORDER
$BS5_OPTION_NO_WINBORDER  EQU       4
                CENDIF                

*---------------------------------------------------------------

// <runtime wide variables>
isLoggedIn      BOOLEAN         %
isGui           BOOLEAN         %
isWebSrv        BOOLEAN         %
isPlbSrv        BOOLEAN         %
isWebview       BOOLEAN         %
isWebCliApp     BOOLEAN         %
isSmallScreen   BOOLEAN         %
curTheme        FORM            %2
loggedInUser    DIM             %40
charScrWidth    FORM            %3      // char screen width
charScrHeight   FORM            %2      // char screen Height
masterCurSel    FORM            %4      // Current selection for all

// <program wide variables>
.
Screen          RECORD
availHeight     DIM             10
availWidth      DIM             10
colorDepth      DIM             10
height          DIM             10
pixelDepth      DIM             10
width           DIM             10
                RECORDEND
.
Navigator       RECORD
appCodeName     DIM             100
appName         DIM             100
appVersion      DIM             100
cookieEnabled   DIM             3
language        DIM             20
platform        DIM             100
product         DIM             100
userAgent       DIM             500
                RECORDEND
.
alertResult     FORM            2
.
themeNames      INIT            "0 - Default",0x7F:
                                "1 - black tie",0x7F:
                                "2 - blitzer",0x7F:
                                "3 - cupertino",0x7F:
                                "4 - dark hive",0x7F:
                                "5 - dot luv",0x7F:
                                "6 - eggplant",0x7F:
                                "7 - excite bike",0x7F:
                                "8 - flick",0x7F:
                                "9 - hot sneaks",0x7F:
                                "10 - humanity",0x7F:
                                "11 - le frog",0x7F:
                                "12 - mint choc",0x7F:
                                "13 - overcast",0x7F:
                                "14 - pepper grinder",0x7F:
                                "15 - redmond",0x7F:
                                "16 - smoothness",0x7F:
                                "17 - south street",0x7F:
                                "18 - start",0x7F:
                                "19 - sunny",0x7F:
                                "20 - swanky purse",0x7F:
                                "21 - trontastic",0x7F:
                                "22 - ui darkness",0x7F:
                                "23 - ui lightness",0x7F:
                                "24 - vader"

.
.
webWin          PLFORM          smasterwv.plf
guiWin          PLFORM          smaster.plf
Client          CLIENT
Runtime         RUNTIME

*................................................................
.
. Code start
.

. If there is no authenticated user, refuse to run. This will prevent users
. from bypassing the answer program.
.
                IF              ( !isLoggedIn )
                GETMODE         *GUI=isGui
                IF              ( isGui )
                ALERT           STOP,"Master Program Must be called from ANSWER",alertResult,""
                ELSE
                DISPLAY         "Master Program Must be called from ANSWER",*W5
                ENDIF
                SHUTDOWN
                ENDIF

                CALL            Main
                LOOP
                EVENTWAIT
                REPEAT
                STOP

*................................................................
. Function to get Client Browser Version
.
GetBrowser      LFUNCTION
pBrowser        DIM             ^
                ENTRY
.
cliInfo         DIM             1024
userAgent       DIM             1024
x7F             INIT            0x7F
fp              FORM            5
lp              FORM            5
ndx             FORM            2
i               FORM            2
cBrwCnt         CONST           "7"
brwNames        DIM             50(cBrwCnt):
                                ("firefox"),("opr"),("trident"),("chrome"),("iphone"):
                                ("ipad"),("safari")
outNames        DIM             50(cBrwCnt):
                                ("Firefox"),("Opera"),("IE"),("Chrome"),("IPhone"):
                                ("IPad"),("Safari")
xVer            DIM             10
.
                CLEAR           pBrowser
.
                Client.GetInfo  GIVING cliInfo
                TYPE            cliInfo
                IF              NOT EOS
.
                EXPLODE         cliInfo,x7F,Screen,Navigator
                TYPE            Navigator.userAgent
                IF              NOT EOS
                LOWERCASE       Navigator.userAgent,userAgent
                FOR             i,1,cBrwCnt
                SCAN            BrwNames(i),userAgent
                IF              EQUAL
                MOVE            i,ndx
                MOVEFPTR        userAgent,fp //Save start of browser found!
                MOVELPTR        brwNames(i),lp
                MOVE            outNames(i),pBrowser
                BREAK
                ENDIF
                REPEAT
.
                TYPE            pBrowser
                IF              EOS
                MOVE            "Unknown",pBrowser
                ELSE
.
. Search the 'userAgent' data for possible version strings.
.
. First default to 'version/n.n.n' string because browser may use the format.
.
                RESET           userAgent
                SCAN            "version/",userAgent
                IF              EQUAL
                BUMP            userAgent,8
                IF              NOT EOS
                PARSE           userAgent,xVer,"09.."
                ENDIF
                ENDIF
.
. At this point, the FP MUST be at the first character of the browser name that was found.
.
                TYPE            xVer
                IF              EOS
.
. Scan Internet Explorer for 'rv:nn.nn'
.
                IF              ( ndx == 3 )      //Browser = Internet Explorer
.
                RESET           userAgent
                SCAN            "rv:",userAgent
                IF              EQUAL
                BUMP            userAgent,3
                IF              NOT EOS
                PARSE           userAgent,xVer,"09.."
                ENDIF
                ENDIF
.
                ELSE            // Other browser
.
. Other Browsers except for IE
.
                RESET           userAgent,fp         // Reset to beginning of browser name!
                BUMP            userAgent,lp         // LP is the length of the browser name found by SCAN!
                IF              NOT EOS
                CMATCH          "/",userAgent
                IF              EQUAL
                BUMP            userAgent
                IF              NOT EOS
                PARSE           userAgent,xVer,"09.."
                ENDIF
                ENDIF
                ENDIF
                ENDIF
                ENDIF
.
. Return Client Browser if it can be extracted from the 'userAgent' data.
.
                TYPE            xVer
                IF              NOT EOS
                PACK            pBrowser,pBrowser," ",xVer
                ENDIF
.
                ENDIF           //Browser type not found
.
                ENDIF           //No Navigator data available
.
                ENDIF           //No GetInfo data available
                FUNCTIONEND

*................................................................
.
. Load the programs combobox from the plb_master.ctl file
.
LoadPrograms    LFUNCTION
pCombo          COMBOBOX        ^
                ENTRY
recordData      DIM             80
seq             FORM            "-1"
ctlFile         FILE

                pCombo.ResetContent
                EXCEPTSET       noCtlFile IF IO
                OPEN            ctlFile, "plb_master.ctl"
                EXCEPTCLEAR     IO

                LOOP
                READ            ctlFile,seq;recordData
                BREAK           IF OVER
 
                CHOP            recordData
                CMATCH          ".", recordData
                IF              NOT EQUAL
                pCombo.AddString Using recordData
                ENDIF
                REPEAT
.
                CLOSE           ctlFile
                RETURN

noCtlFile
                pCombo.AddString Using "reset"
                FUNCTIONEND

*................................................................
.
. Load the staus line
.
LoadStatus      LFUNCTION
edtParam        EDITTEXT        ^
statInfo        STATTEXT        ^
                ENTRY
statusLine      DIM             80
runVersion      DIM             50

                GETPROP         edtParam, text=S$CMDLIN

                IF              (isWebSrv)
                CALL            GetBrowser Using statusLine
                ELSE
                CLOCK           VERSION, runVersion
                PACK            statusLine, "Runtime Version: '", runVersion, "'"
                ENDIF

                SETPROP         statInfo, text=statusLine
                FUNCTIONEND

*................................................................
.
. Signout
.
SignOut         LFUNCTION
                ENTRY
                SHUTDOWN
                FUNCTIONEND

*................................................................
.
. CHAIN a program
.
SwitchPrograms  LFUNCTION
pCombo          COMBOBOX        ^
edtProgram      EDITTEXT        ^
                ENTRY
programName     DIM             76

                pCombo.GetText  GIVING programName
                TYPE            programName
                IF              NOT EOS
 
                IF              ( NOCASE programName == "reset" )
                SETPROP         edtProgram, text=""
                ELSE
                SETPROP         edtProgram, text=programName
                ENDIF

                ENDIF
.
                FUNCTIONEND

*................................................................
.
. CHAIN a program
.
ChainProgram    LFUNCTION
edtProgram      EDITTEXT        ^
edtParam        EDITTEXT        ^
                ENTRY
programName     DIM             76
errLine         DIM             80
.
. get the name of the program the user entered
.
                GETPROP         edtProgram,*Text=programName
.
. Set the command line parameters
.
                SETPROP         edtParam, text=S$CMDLIN
                SETMODE         *PERCENTCONVERT=0
.
. catch the error if the progam can't be loaded
.
                EXCEPTSET       ProgNotFound if CFAIL
.
. try to chain to specified program
.
                CHAIN           programName

ProgNotFound
.
. the alert the user with the error
.
                PACK            errLine,programName," Error: ",S$ERROR$
                ALERT           STOP,errLine,alertResult,"Program Load Error"
.
. clear the text in the edit field and put focus back so
. user can re-enter a program name.
.
                SETPROP         edtProgram,text=""
                SETFOCUS        edtProgram
                
                FUNCTIONEND

*................................................................
.
. Set a new theme
.
ChangeTheme     LFUNCTION
                ENTRY
themeNum        FORM            3
                EVENTINFO       0,Result=themeNum
                MOVE            (themeNum-1) to curTheme
                Runtime.SetWebTheme Using curTheme
                FUNCTIONEND

*................................................................
.
. CHAIN a WebView program
.
WebProgram      LFUNCTION
                ENTRY

                CALL            ChainProgram Using mwvEdtProgram, mwvEdtParam

                FUNCTIONEND

*................................................................
.
. WebPrograms - Change in the Programs Combobox
.
WebPrograms     LFUNCTION
                ENTRY

                CALL            SwitchPrograms Using mwvCbPrograms, mwvEdtProgram

                FUNCTIONEND
*................................................................
.
. Webview or Bootstap 5 enabled GUI
.
WebMaster       LFUNCTION
                ENTRY

                Runtime.SetWebTheme Using curTheme,*Options=($BS5_OPTION_GRADIENT+$BS5_OPTION_PROGRESS+$BS5_OPTION_NO_WINBORDER)
.
. On smaller screens change to % positioning for left and width
.
                IF              (isWebCliApp || isSmallScreen)
                SETMODE         *PERCENTCONVERT=1
                ENDIF

                FORMLOAD        webWin

                mwvCbTheme.ResetContent
                mwvCbTheme.AddString Using ThemeNames
                mwvCbTheme.SetCurSel Using curTheme

                CALL            LoadPrograms Using mwvCbPrograms
                CALL            LoadStatus Using mwvEdtParam, mwvStatInfo

                SETPROP         mwvFrmMain,visible=$TRUE
                FUNCTIONEND
*................................................................
.
. CHAIN a GUI program
.
GuiProgram      LFUNCTION
                ENTRY
 
                CALL            ChainProgram Using masEdtProgram, masEdtParam
                
                FUNCTIONEND

*................................................................
.
. GuiPrograms - Change in the Programs Combobox
.
GuiPrograms     LFUNCTION
                ENTRY

                CALL            SwitchPrograms Using masCbPrograms, masEdtProgram

                FUNCTIONEND
*................................................................
.
. Basic GUI for older graphical systems
.
GuiMaster       LFUNCTION
                ENTRY
.
. On smaller screens change to % positioning for left and width
.
                IF              (isWebCliApp || isSmallScreen)
                SETMODE         *PERCENTCONVERT=1
                ENDIF

                FORMLOAD        guiWin

                CALL            LoadPrograms Using masCbPrograms
                CALL            LoadStatus Using masEdtParam, masStatInfo

                SETPROP         masFrmMain,Visible=$TRUE
                FUNCTIONEND

*................................................................
.
. Classic Keyin/Display for character based systems
.
ConMaster       LFUNCTION
                ENTRY
cx              FORM            2       // character Scr center x
cy              FORM            3       // character Scr center y
localTime       DIM             20
formattedTime   DIM             20
programName     DIM             76
.
. Find the middle of the Scr.
.
                CALC            cx=charScrWidth/2
                CALC            cy=charScrHeight/2
.
                LOOP
.
. show banner
.
                CLOCK           TIMESTAMP,localTime
                EDIT            localTime,formattedTime,MASK="9999-99-99 99:99:99"
                DISPLAY         *SETSWALL=1:charScrHeight:1:charScrWidth,*BGCOLOR=*BLUE,*WHITE,*ES;
                DISPLAY         *SETSWALL=1:3:1:charScrWidth,*BORDER:
                                *p=2:2,"Sunbelt Computer Software ":
                                *P=(charScrWidth-21):2,formattedTime:
                                *SETSWALL=3:charScrHeight:1:charScrWidth,*BORDER:
                                *RTKDD,*H=charScrWidth,*LTKDD,*SHRINKSW:
                                *P=2:(charScrHeight-3),*RED,"Escape to exit",*WHITE;
.
. Welcome messge
.
                DISPLAY         *p=(cx-10):(cy-7),"Welcome ",*ll,loggedInUser
.
. Prompt
.
                DISPLAY         *P=(cx-15):(cy-5),"Enter Program Name:"
.
. Make sure we exit cleanly on interrup (CTRL-C) or escape
.
                TRAP            Signout IF INTERRUPT
                TRAP            Signout IF ESCAPE
.
. display a box for the user to enter the name of the program
.
                KEYIN           *SETSWALL=(cy-1):(cy+1):2:(charScrWidth-1),*BORDER,*P=2:2:
                                *UC,*RPTCHAR="_":(charScrWidth-4),*P=2:2,programName
.
. CHAIN back to answer if "X"
.
                STOP            IF ( programName = "X" )
.
. we want to provide a meaning for error if user didn't type program
. correctly so set the trap
.
                EXCEPTSET       CProgNotFound if CFAIL
                CHAIN           ProgramName

CProgNotFound
.
. beep and display a meaningful error message in red along with the runtime
. error code
.
                BEEP
.
. this disply is only temporarily in the Scr so we save the current
. subwindow state at the beginning, wait, then restore the original state
.
                DISPLAY         *SAVESW,*SETSWALL=(cy-1):(cy+2):(cx-20):(cx+20),*BORDER:
                                *SHRINKSW,*BGCOLOR=*WHITE,*ES,*P=11:1,*RED,"Program Load Failed":
                                *P=1:2,S$ERROR$,*W=4:
                                *RESTSW

                REPEAT

                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY

                CALL            ConMaster IF (!isGui)

                WINHIDE

                IF              (isWebview)
                CALL            WebMaster
                ELSE
                CALL            GuiMaster
                ENDIF
                FUNCTIONEND

