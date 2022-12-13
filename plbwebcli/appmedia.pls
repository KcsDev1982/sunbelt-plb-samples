*---------------------------------------------------------------
.
. Program Name: appmedia
. Description:  PlbWeCli Application Media Sample 
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

WebForm         PLFORM          appmedia.pwf
.
Client          CLIENT
.
Result          FORM            5
FullData        DIM             80
.


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
                EVENTINFO       0,Result=Result
                SWITCH          Result
                CASE            1
                CALL            Play
                CASE            2
                CALL            Pause
                CASE            3
                CALL            Resume
                CASE            4
                CALL            Stop
                ENDSWITCH
                FUNCTIONEND
 
*................................................................
.
. Pause
.  
Pause           LFUNCTION
                ENTRY
                Client.AppMedia Giving Result Using AppMediaPause
                FUNCTIONEND

*................................................................
.
. Stop
.
Stop            LFUNCTION
                ENTRY
                Client.AppMedia Giving Result Using AppMediaStop
                FUNCTIONEND

*................................................................
.
. Play
.
Play            LFUNCTION
                ENTRY
                Client.AppMedia Giving Result Using AppMediaPlay, *URL="http://www.sunbelt-plb.com:8081/sound/SleepAway.mp3"
                FUNCTIONEND
 
*................................................................
.
. Resume
.
Resume          LFUNCTION
                ENTRY
                Client.AppMedia Giving Result Using AppMediaPlay
                FUNCTIONEND

*................................................................
.
. Exit
.
Exit            LFUNCTION
                ENTRY
                Client.AppMedia Giving Result Using AppMediaRelease
                STOP
                FUNCTIONEND

*................................................................
.
. MediaRes
.
MediaRes        LFUNCTION
                ENTRY
                Client.AppDialog Using FullData, "Media Result", "Cool;Wow"
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
                WINHIDE
                FORMLOAD        WebForm

                EVENTREG        Client,AppEventMedia,MediaRes,ARG1=FullData
.
                FUNCTIONEND

