*---------------------------------------------------------------
.
. Program Name: appmaster
. Description:  PlbWebCli Application Master 
.
. Revision History:
.
. 17-04-07 whk
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*---------------------------------------------------------------         
.
LastSelection   FORM            %4
.
NVAR            FORM            3
ProgNam         DIM             100
D80             DIM             80
MAIN            MAINWINDOW
NEGONE          FORM            "-1"
NULL            DIM             1
VER             DIM             5
.
.
Color0          COLOR
Color1          COLOR
Color2          COLOR
Color3          COLOR
Color4          COLOR
iColor0         INTEGER         4,"0xFFE1FB" //Light Pink
iColor1         INTEGER         4,"0x80FF80" //Green
iColor2         INTEGER         4,"0xFF80FF" //Pink
iColor3         INTEGER         4,"0xFF8080" //Blueish
iColor4         INTEGER         4,"0x0080FF" //Orange
.
CLIENT          CLIENT
Browser         DIM             50
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
fUnix           FORM            5
.
PathChr         INIT            "\" //Default to Windows!
.
X               PLFORM          appmaster.PWF
.
*................................................................
.
. Code start
.
Start
                CALL            Main
                LOOP
                EVENTWAIT
                REPEAT
                STOP

*................................................................
.
. CHAIN - Chain to another program
.
CHAIN		LFUNCTION
		ENTRY
nRadio          FORM            3

                GETPROP         Radio1, VALUE=nRadio   ;appcor.plc
                IF              ( nRadio )
                DELETEITEM      EditText1, 0
                MOVE            "appcor.plc", ProgNam
                CLEAR           LastSelection
                ELSE
                GETPROP         Radio2, VALUE=nRadio   ;appcap.plc
                IF              ( nRadio )
                DELETEITEM      EditText1, 0
                MOVE            "appcap.plc", ProgNam
                CLEAR           LastSelection
                ELSE
                GETPROP         Radio3, VALUE=nRadio  ;appcon.plc
                IF              ( nRadio )
                DELETEITEM      EditText1, 0
                MOVE            "appcon.plc", ProgNam
                CLEAR           LastSelection
                ELSE
                GETPROP         Radio4, VALUE=nRadio  ;appinfo.plc
                IF              ( nRadio )
                DELETEITEM      EditText1, 0
                MOVE            "appinfo.plc", ProgNam
                CLEAR           LastSelection
                ELSE
.
                CALL            ProgramCBClick
.
                GETPROP         EditText1, TEXT=ProgNam
                CHOP            ProgNam
                TYPE            ProgNam     ;Check for user program
                IF              EOS    
                ALERT           NOTE,"Program Selection Not Specified!", NVAR, "PLB Answer"
                RETURN
                ENDIF
                ENDIF
                ENDIF
                ENDIF
                ENDIF
.
                GETPROP         CmdLineET, TEXT=S$CMDLIN
.
		EXCEPTSET       ChainError IF CFAIL
                CHAIN           ProgNam
		
ChainError	
                PACK            D80, "'", ProgNam, "' not found!"
                ALERT           NOTE,D80, NVAR, "PLB Answer Chain Error"
                UNPACK          "",S$ERROR$
                FUNCTIONEND

*................................................................
.
. GetBrowser -  Client Browser Version
.
GetBrowser      LFUNCTION
pBrowser        DIM             ^
                ENTRY
.
DInfo           DIM             1024
DLow            DIM             1024
x7F             INIT            0x7F
FP              FORM            5
LP              FORM            5
NDX             FORM            2
I               FORM            2
cBrwCnt         CONST           "7"
BrwNames        DIM             50(cBrwCnt):
                                ("firefox"), ("opr"), ("trident"), ("chrome"),("iphone"):
                                ("ipad"),("safari")
OutNames        DIM             50(cBrwCnt):
                                ("Firefox"), ("Opera"), ("IE"), ("Chrome"),("IPhone"):
                                ("IPad"),("Safari")
XVer            DIM             10
...
.
                CLEAR           pBrowser
.
                Client.GetInfo  GIVING DInfo
                TYPE            DInfo
                IF              NOT EOS
.
                EXPLODE         DInfo, x7F, Screen, Navigator
                TYPE            Navigator.userAgent
                IF              NOT EOS
                LOWERCASE       Navigator.userAgent, DLow
                FOR             I, 1, cBrwCnt
                SCAN            BrwNames(I), DLow
                IF              EQUAL
                MOVE            I, NDX
                MOVEFPTR        DLow, FP //Save start of browser found!
                MOVELPTR        BrwNames(I), LP
                MOVE            OutNames(I), pBrowser
                BREAK
                ENDIF
                REPEAT
.
                TYPE            pBrowser
                IF              EOS
                MOVE            "Unknown", pBrowser
                ELSE
.
. Search the 'userAgent' data for possible version strings.
.
.
. First default to 'version/n.n.n' string because
. browser may use the format.
.
                RESET           DLow
                SCAN            "version/", DLow
                IF              EQUAL
                BUMP            DLow, 8
                IF              NOT EOS
                PARSE           DLow, xVer, "09.."
                ENDIF
                ENDIF
.
. At this point, the FP MUST be at the first character
. of the browser name that was found.
.
                TYPE            xVer
                IF              EOS
.
.
. Scan Internet Explorer for 'rv:nn.nn'
.
                IF              ( NDX == 3 )      //Browser = Internet Explorer
.
                RESET           DLow
                SCAN            "rv:", DLow
                IF              EQUAL
                BUMP            DLow, 3
                IF              NOT EOS
                PARSE           DLow, xVer, "09.."
                ENDIF
                ENDIF
.
                ELSE            //Other browser 
.
. Other Browsers except for IE
.
                RESET           DLow, FP        //Reset to beginning of browser name!
                BUMP            DLow, LP           //LP is the length of the browser name found by SCAN!
                IF              NOT EOS
                CMATCH          "/", DLow
                IF              EQUAL
                BUMP            DLow
                IF              NOT EOS
                PARSE           DLow, xVer, "09.."
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
                PACK            pBrowser, pBrowser, " ", xVer
                ENDIF
.
                ENDIF           //Browser type not found
.
                ENDIF           //No Navigator data available
.
                ENDIF           //No GetInfo data available
.
                FUNCTIONEND

*................................................................
.
. ProgramCBClick -  Combobox Programs
.
ProgramCBClick  LFUNCTION
                ENTRY
.
xText           LIKE            ProgNam
.
                SETPROP         Radio1, VALUE=0
                SETPROP         Radio2, VALUE=0
                SETPROP         Radio3, VALUE=0
.
                ProgramCB.GetText GIVING xText
                TYPE            xText
                IF              NOT EOS
                ProgramCB.GetCurSel GIVING LastSelection
                IF              ( LastSelection >= 0 )
                ADD             "1", LastSelection //Make 1 relative!
                ENDIF
                SETPROP         EditText1, TEXT=xText
                ENDIF
.
                FUNCTIONEND

*................................................................
.
. LoadProgramCB -  Load Programs Combobox
.
LoadProgramCB   LFUNCTION
                ENTRY
.
FILE            FILE
SEQ             FORM            "-1"
xName           LIKE            ProgNam
.
                DEBUG
                EXCEPTSET       ExitIO IF IO
.
                OPEN            FILE, "masterprogApp.txt"
.
                LOOP
                READ            FILE, SEQ;*ll, xName
                BREAK           IF OVER
.
                CHOP            xName, xName
                TYPE            xName
                CONTINUE        IF EOS
.
                ProgramCB.AddString USING xName
.
                REPEAT
.
                IF              ( LastSelection > 0 )
                ProgramCB.SetCurSel USING ( LastSelection - 1 )
                CALL            ProgramCBClick
                ELSE
                ProgramCB.SetCurSel USING NEGONE
                ENDIF
                SETPROP         ProgramST, VISIBLE=1
                SETPROP         ProgramCB, VISIBLE=1
                RETURN
.
ExitIO
.
                UNPACK          "", S$ERROR$
.
                FUNCTIONEND
.
.....
. Panel Colors
.
fColors         INTEGER         1 //Flag panel color usage.
.
DoPanels        FUNCTION
                ENTRY
.
                IF              ( fColors )
                SETPROP         Panel0, BGCOLOR=Color0
                SETPROP         Panel1, BGCOLOR=Color1
                SETPROP         Panel2, BGCOLOR=Color2
                SETPROP         Panel3, BGCOLOR=Color3
                SETPROP         Panel4, BGCOLOR=Color4
                CLEAR           fColors
                ELSE
                SETPROP         Panel0, BGCOLOR=iColor0
                SETPROP         Panel1, BGCOLOR=iColor1
                SETPROP         Panel2, BGCOLOR=iColor2
                SETPROP         Panel3, BGCOLOR=iColor3
                SETPROP         Panel4, BGCOLOR=iColor4
                SET             fColors
                ENDIF
.
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
                WINHIDE
.
.....
. Check for Unix runtime!
. 
                GETMODE         *OPENABS=fUnix
                IF              ( fUnix == 99 )
....
. We have a Unix runtime!
. 
                MOVE            "/", PathChr //Change to Unix path delimiter!
                ENDIF
.
                GETPROP         MAIN, VISIBLE=NVAR
                IF              ( NVAR != 0 )
                WINHIDE
                ENDIF
.
                CHOP            S$ERROR$
                TYPE            S$ERROR$
                IF              NOT EOS

                ALERT           NOTE,S$ERROR$,NVAR,"PLB Answer error recovery"
                UNPACK          "", S$ERROR$
                ENDIF
.
                Client.AddCss   USING "appmaster.css"
.
                TEST            WebForm1   ;Is the .PWF form already loaded!
                IF              ZERO
                FORMLOAD        X
                SETPROP         WebForm1, VISIBLE=1
                CALL            LoadProgramCB  //Load test program names
                GETPROP         Panel0, BGCOLOR=Color0
                GETPROP         Panel1, BGCOLOR=Color1
                GETPROP         Panel2, BGCOLOR=Color2
                GETPROP         Panel3, BGCOLOR=Color3
                GETPROP         Panel4, BGCOLOR=Color4 
                ENDIF
.
.....
. Show Runtime and Client Browser Version
.
                CLOCK           VERSION, VER
                PACK            D80, "Version: ", VER
.
                CALL            GetBrowser USING Browser
                TYPE            Browser
                IF              NOT EOS
                PACK            D80, D80, "   Client: ", Browser
                ENDIF
                SETPROP         VersionST, TEXT=D80
.
                TYPE            S$CMDLIN
                IF              NOT EOS
                SETPROP         CmdLineET, TEXT=S$CMDLIN
                ENDIF

		FUNCTIONEND
.
.
