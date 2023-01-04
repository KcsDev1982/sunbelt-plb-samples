*---------------------------------------------------------------
.
. Program Name: appsb
. Description:  PlbWebCli Application Statusbar Sample 
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
WebForm         PLFORM          appstf.pwf
.
Client          CLIENT
Result          FORM            5



*................................................................
.
. Code start
.
                CALL            Main
                LOOP
                EVENTWAIT
                REPEAT
                STOP

*................................................................
.
. TestClick - Handle a request to perform a test
.
TestClick       LFUNCTION
                ENTRY
                EVENTINFO       0,result=Result
                SWITCH          Result
                CASE            1
                Client.AppStatusBar Using AppStatusBarHide 
                CASE            2
                Client.AppStatusBar Using AppStatusBarShow 
                CASE            3
                Client.AppStatusBar Using AppStatusBarOverlayOff 
                CASE            4
                Client.AppStatusBar Using AppStatusBarOverlayOn 
                CASE            5
                Client.AppStatusBar Using AppStatusBarDefault 
                CASE            6
                Client.AppStatusBar Using AppStatusBarLightContent 
                CASE            7
                Client.AppStatusBar Using AppStatusBarBlackTranslucent 
                CASE            8
                Client.AppStatusBar Using AppStatusBarBlackOpaque 
                CASE            9
                Client.AppStatusBar Using 0, *BackColor="cyan" 
                CASE            10
                Client.AppStatusBar Using 0, *BackColor="##FFFFFF" 
                ENDSWITCH
                FUNCTIONEND
.
*................................................................
.
. Main - Main program entry point
.
.
Main            LFUNCTION
                ENTRY
                WINHIDE
               
		FORMLOAD        WebForm
.
                FUNCTIONEND

