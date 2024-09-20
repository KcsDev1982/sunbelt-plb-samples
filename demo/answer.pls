*---------------------------------------------------------------
.
. Program Name: answer
. Description:  Sample answer/signin program
.
. Revision History:
.
. 29 Aug 24 - Redesigned for version 10.7
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc

                CIFNDEF         $CLI_STATE_CORDOVA
$CLI_STATE_CORDOVA        EQU       2
$CLI_STATE_BOOTSTRAP5     EQU       16
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

// <program wide variables>
.
. GETINFO System data
.
systemInfoData  DIM             644
systemInfoRec   RECORD
osType          FORM            1
osVersion       FORM            1
keyboardType    DIM             2
keyboardSubType DIM             2
functionKeyType DIM             2
hasPen          BOOLEAN
hasMouse        BOOLEAN
mouseButtons    FORM            1
buttonsSwapped  BOOLEAN
screenWidth     FORM            4
screenHeight    FORM            4
computerName    DIM             15
userName        DIM             20
windowsDir      DIM             260
systemDir       DIM             260
colorBits       FORM            2
windowHandle    INTEGER         4
windowInstance  INTEGER         4
taskbarState    FORM            1
taskbarTop      FORM            4
taskbarBottom   FORM            4
taskbarLeft     FORM            4
taskbarRight    FORM            4
monitorCount    FORM            2
virtualTop      FORM            10
virtualBottom   FORM            10
virtualLeft     FORM            10
virtualRight    FORM            10
                RECORDEND
.
plbUsers        IFILE
userRec         RECORD
email           DIM             40      // user email or name
password        DIM             16      // password
loginTime       DIM             14      // login time
                RECORDEND

webWin          PLFORM          answerwv.plf
guiWin          PLFORM          answer.plf
Client          CLIENT
Runtime         RUNTIME

*................................................................
.
. Code start
.

.
. Check to see if we have alredy been run and terminate if yes
.
                IF              ( isLoggedIn )
                SHUTDOWN
                ENDIF

                CALL            Main
                LOOP
                EVENTWAIT
                REPEAT
                STOP

*................................................................
.
. Shutdown the runtime
.
DoShutdown      LFUNCTION
                ENTRY
                SHUTDOWN
                FUNCTIONEND

*................................................................
.
. Open or Create Users file
.
UserFileAccess  LFUNCTION
                ENTRY
result          FORM            5
error           INIT            "Unable to open or create the user file!"

                EXCEPTSET       NoUserFile IF IO
                FINDFILE        "plb_users.isi"
                IF              EQUAL
                OPEN            plbUsers,"plb_users.isi"
                ELSE
                PREP            plbUsers,"plb_users.txt","plb_users.isi","1-20","65"
                ENDIF
                RETURN
.
. Could not Open or Create the Users file
.
NoUserFile      IF              (isGui )
                ALERT           STOP,error,result
                ELSE
                KEYIN           *DV,error,result
                ENDIF
                SHUTDOWN
                FUNCTIONEND

*-------------------------------------------------------------------------------
.
. If user is on file, compare the password. Otherwise add the user.
.
CheckPassword   LFUNCTION
                ENTRY
decodedPasword  DIM             12
tempPassword    DIM             12
result          FORM            5

                ENDSET          userRec.email
                EXTEND          userRec.email,40
                RESET           userRec.email
.
. we only save 12 character password so truncate anything extra
. and remove trailing spaces
.
                MOVE            userRec.password,tempPassword
                CHOP            tempPassword                            // Remove trailing spaces
                READ            plbUsers,userRec.email;userRec  // Use name as key to password file
                IF              NOT OVER
                DECODE64        userRec.password,decodedPasword         // Decode the saved password
                CHOP            decodedPasword                                  // Remove trailing spaces
                RETURN          IF ( tempPassword != decodedPasword )           // Return NOT Equal for bad password
                ELSE
                IF              ( isGui )                       // Notify user of new record
                ALERT           NOTE,"Added New User",result
                ELSE
                DISPLAY         "Added New User",*W=2
                ENDIF
.
. Encode the password stored on disk.
.
                MOVE            userRec.password,decodedPasword
                ENDSET          decodedPasword
                EXTEND          decodedPasword,12
                RESET           decodedPasword
                ENCODE64        decodedPasword,userRec.password // don't store plain text password in file
                WRITE           plbUsers;userRec                // Save User/Password info to disk
                ENDIF

                SETFLAG         EQUAL                          // Password was good
                FUNCTIONEND
*-------------------------------------------------------------------------------
.
. Update the user file and go to the master program
.
Signin          LFUNCTION
                ENTRY
timeStamp       DIM             20
.
. Get the current time and update the password file to log
. last log in time
.
                CLOCK           TIMESTAMP,timeStamp
                MOVE            timeStamp,userRec.loginTime
                UPDATE          plbUsers;userRec
.
. move the user name to the global authenticated user variable
. so other progams can check this
.
                MOVE            userRec.email,loggedInUser
.
. chain to master
.
                SET             isLoggedIn
                CHAIN           "master"
                STOP
                FUNCTIONEND

*................................................................
.
. Switch betweem light and dark mode
.
DarkSwitch      LFUNCTION
                ENTRY
switch          BOOLEAN
                GETPROP         awvChkDark,Value=switch
                IF              (Switch)
                MOVE            "3" TO curTheme
                awvPictLogo.SetWebStyle Using  "background-image", "none"
                SETPROP         awvChkDark,Value=0
                ELSE
                MOVE            "4" TO curTheme
                awvPictLogo.SetWebStyle Using  "background-image", "linear-gradient(red, yellow)"
                SETPROP         awvChkDark,Value=1
                ENDIF
                Runtime.SetWebTheme Using curTheme
                FUNCTIONEND

*................................................................
.
. Sign-in for Web
.
SigninWeb       LFUNCTION
                ENTRY
result          FORM            5

                GETPROP         awvEdtUserName,Text=userRec.email
                GETPROP         awvEdtPassword,Text=userRec.password
                CALL            CheckPassword

                IF              NOT EQUAL
                ALERT           awvFrmMain;STOP,"Invalid Password",result
                SETPROP         awvEdtPassword,Text=""
                SETFOCUS        awvEdtPassword
                RETURN
                ENDIF

                CALL            Signin
                FUNCTIONEND

 
*................................................................
.
. Webview or Bootstap 5 enabled GUI
.
WebAnswer       LFUNCTION
                ENTRY

.
. On smaller screens change to % positioning for left and width
.
                IF              (isWebCliApp || isSmallScreen)
                SETMODE         *PERCENTCONVERT=1
                ENDIF

.
. Setup the default theme support
.
                MOVE            "3" TO curTheme
                Runtime.SetWebTheme Using curTheme,*Options=($BS5_OPTION_GRADIENT+$BS5_OPTION_PROGRESS+$BS5_OPTION_NO_WINBORDER)
                FORMLOAD        webWin
                awvPictLogo.SetWebStyle Using  "border-radius", "25px"

.
. Turn off LOGO on smaller screens
.
                IF              (isPlbSrv || isWebCliApp || isSmallScreen)
                SETPROP         awvPictLogo,Visible=$FALSE
                ENDIF

.
. Resize window and static header on smaller screens
.
                IF              (isWebCliApp || isSmallScreen)
                SETPROP         awvStatHeader,WebLeft="5%",WebWidth="90%"
                awvStatHeader.SetWebStyle Using  "font-size", "18pt"
                SETPROP         awvFrmMain,WebWidth="100%"
                ELSE            IF      (isPlbSrv)
                SETPROP         awvStatHeader,Left=5
                ENDIF

.
. Make the form visible
.
                SETPROP         awvFrmMain,Visible=$TRUE
                SETFOCUS        awvEdtUserName
                FUNCTIONEND

*................................................................
.
. Sign-in for GUI
.
SigninGui       LFUNCTION
                ENTRY
result          FORM            5

                GETPROP         ansEdtUserName,Text=userRec.email
                GETPROP         ansEdtPassword,Text=userRec.password
                CALL            CheckPassword

                IF              NOT EQUAL
                ALERT           ansFrmMain;STOP,"Invalid Password",result
                SETPROP         ansEdtPassword,Text=""
                SETFOCUS        ansEdtPassword
                RETURN
                ENDIF

                CALL            Signin
                FUNCTIONEND

*................................................................
.
. Basic GUI for older graphical systems
.
GuiAnswer       LFUNCTION
                ENTRY
.
. On smaller screens change to % positioning for left and width
.
                IF              (isWebCliApp || isSmallScreen)
                SETMODE         *PERCENTCONVERT=1
                ENDIF

                FORMLOAD        guiWin

.
. Turn off LOGO on smaller screens
.
                IF              (isPlbSrv || isWebCliApp || isSmallScreen)
                SETPROP         ansPictLogo,Visible=$FALSE
                ENDIF

.
. Resize window and static header on smaller screens
.
                IF              (isWebCliApp || isSmallScreen)
                SETPROP         ansStatHeader,WebLeft="5%",WebWidth="90%"
                ansStatHeader.SetWebStyle Using  "font-size", "18pt"
                SETPROP         ansFrmMain,WebWidth="100%"
                ELSE            IF      (isPlbSrv)
                SETPROP         ansStatHeader,Left=5
                ENDIF
.
. Make the form visible
.
                SETPROP         ansFrmMain,Visible=$TRUE
                SETFOCUS        ansEdtUserName
                FUNCTIONEND

*................................................................
.
. Show a banner on a console system
.
ShowBanner      LFUNCTION
                ENTRY
timeStamp       DIM             20
formattedTime   DIM             20
.
. Get the current time and format it for display
.
                CLOCK           TIMESTAMP,timeStamp
                EDIT            timeStamp,formattedTime,MASK="9999-99-99 99:99:99"
.
. setup the screen with colors and borders all based on screen information
. retrieved from clock earlier in the program.
.
                DISPLAY         *SETSWALL=1:charScrHeight:1:charScrWidth,*BGCOLOR=*BLUE,*WHITE,*ES;
                DISPLAY         *SETSWALL=1:3:1:charScrWidth,*BORDER:
                                *p=3:2,"Sunbelt Computer Software":
                                *P=(charScrWidth-21):2,formattedTime:
                                *SETSWALL=3:charScrHeight:1:charScrWidth,*BORDER:
                                *RTKDD,*H=charScrWidth,*LTKDD,*SHRINKSW:
                                *P=2:(charScrHeight-3),*RED,"ESC to exit",*WHITE;
                FUNCTIONEND

*................................................................
.
. Classic Keyin/Display for character based systems
.
ConAnswer       LFUNCTION
                ENTRY
cx              FORM            2       // character screen center x
cy              FORM            3       // character screen center y
port            DIM             10

.
. get screen dimensions
.
                CLOCK           PORT,port
                RESET           port,4
                UNPACK          port,charScrHeight,charScrWidth
.
. display banner
.
                CALL            ShowBanner
.
. calculate the center of the screen
.
                CALC            cx=charScrWidth/2
                CALC            cy=charScrHeight/2
.
. User prompts
.
                DISPLAY         *P=(cx-15):(cy-2),"Username  : "
                DISPLAY         *H=(cx-15),"Password  : "
.
. Traps to exit runtime cleanly
.
                TRAP            DoShutdown IF INTERRUPT
                TRAP            DoShutdown IF ESCAPE
.
                LOOP
.
. Note: *IT does not expire.  It's used to change the
.       legacy behavior ( CAPS OFF = ALL CAPS )
.       of the caps lock key to modern behavior. ( CAPS ON = ALL CAPS )
.
. We are using *DVEDIT for the user name because we want to use
. the system logged in user as the default userRec.
.
                KEYIN           *IT,*P=(cx-3):(cy-2),*LC,*DVEDIT=userRec.email
                IF              ESCAPE
                SHUTDOWN
                ENDIF
                CHOP            userRec.email
                CONTINUE        if ( userRec.email = "" ) // No empty or null user names
                KEYIN           *P=(cx-3):(cy-1),*EL,*ESON,*LC,userRec.password,*ESOFF
                CONTINUE        if ( userRec.password = "" )     // No empty or null passwords
                CALL            CheckPassword
                UNTIL           EQUAL
                BEEP
                DISPLAY         *SAVESW,*SETSWALL=(cy-1):(cy+1):(cx-10):(cx+10),*BORDER:
                                *SHRINKSW,*BGCOLOR=*WHITE,*RED,*ES,"Invalid Password":
                                *W=4,*RESTSW,*SHRINKSW
                REPEAT
                DISPLAY         *IN;                    // Turn off Shift Inversion.
                CALL            Signin
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
runtimeData     DIM             50
runtimeVersion  DIM             5
unused          DIM             1
plbRuntime      DIM             9
WidthData       DIM             5
checkWidth      FORM            5

                CLEAR           S$ERROR$

.
. Check for character mode runtime
.
                GETMODE         *GUI=isGui

                IF              (isGui)
.
. Get System Information that could be useful later...
.
                GETINFO         SYSTEM,systemInfoData
                UNPACK          systemInfoData,systemInfoRec
.
. check windows console.
.
                CLOCK           VERSION,runtimeData
                UNPACK          runtimeData,runtimeVersion,unused,plbRuntime
                CHOP            plbRuntime
          
                IF              (NOCASE plbRuntime == "PLBCON")
                CLEAR           isGui
                ENDIF

                IF              (NOCASE plbRuntime == "PLBWEBSV")
                SET             isWebSrv
                ENDIF

                IF              (NOCASE plbRuntime == "PLBSERVE")
                SET             isPlbSrv
                ENDIF

                ENDIF

                IF              (isGui)
                WINHIDE
                ENDIF

.
. Open the user file and invoke the proper user interface
.
                CALL            UserFileAccess
                CALL            ConAnswer IF (!isGui)
               
                Client.Getstate Giving isWebCliApp Using $CLI_STATE_CORDOVA
                Client.Getstate Giving isWebview Using $CLI_STATE_BOOTSTRAP5

.
. Check for a small screen (such as iphone)
.
                IF              (isWebSrv)
                Client.GetWinInfo Giving WidthData Using 0x2
                MOVE            WidthData To checkWidth
                MOVE            (checkWidth <= 700) to isSmallScreen
                ENDIF

.
. Invoke the answer form based on level of UI support
.
                IF              (isWebview)
                CALL            WebAnswer
                ELSE
                CALL            GuiAnswer
                ENDIF

                FUNCTIONEND
.
. End of code
.
