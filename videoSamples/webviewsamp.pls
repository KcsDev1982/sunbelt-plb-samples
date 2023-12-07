*---------------------------------------------------------------
.
. Program Name: WebViewSamp
. Description:  WebView Sample
.
. Revision History:
.
. 22-10-18 WHK
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc	
*---------------------------------------------------------------

MixedWebForm	PLFORM		webviewsampf.plf

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
. JQuery Event
.
BootStrapEvent
		RETURN

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
		WINHIDE
		FORMLOAD	MixedWebForm
                FUNCTIONEND
