	 LISTOFF
.
	 %XREFOFF  ;DO NOT include in cross reference!!			  9.1E
.
	 %IFNDEF   $ADMEQU_LOADED
$ADMEQU_LOADED EQU  1			;Flag that ADMEQU is loaded
*==============================================================================
. ADMIN	support	equates
.
. Last Revision	Date:  01 Oct 2021
.
. Revision History:
.
	 %IFDEF	   $ADMEQU_HISTORY
.:: 02 Jan 03 -	Create Admin equate include definitions.		  :8.7
.:: 27 Feb 03 -	Added $ADMITEMSRVLOGCUR, $ADMITEMSRVLOGMAX,		  :8.7A
.::		$ADMITEMSRVLOGSTART, and $ADMITEMSRVLOGRECS.		  :8.7A
.:: 20 Mar 03 -	Added $ADMLOG for the ADMSETINFO action	commands.	  :8.7A
.:: 28 Apr 03 -	Added $ADMITEMUSERNAME,	$ADMITEMCOMPUTERNAME,		  :8.7B
.::		$ADMITEMMODULENAME, $ADMITEMAAMFILENAME,		  :8.7B
.::		$ADMITEMISIFILENAME, $ADMITEMPRTFILENAME,		  :8.7B
.::		$ADMITEMTXTFILENAME, $ADMITEMSRVNAME,			  :8.7B
.::		$ADMITEMSRVUSERNAME, $ADMITEMSRVCOMPUTERNAME, and	  :8.7B
.::		$ADMITEMFILENAMEALL.					  :8.7B
.:: 28 Jul 03 -	Added $ADMCMDLOGMSGLEVEL0, $ADMCMDLOGMSGLEVEL1,	and	  :8.7C
.::		$ADMCMDLOGMSGLEVEL2.					  :8.7C
.:: 26 May 04 -	Review for 9.0 release.					  :9.0
.:: 28 Apr 05 -	Added $ADMITEMCPUTIME.					  :9.0F
.:: 22 Feb 06 -	Added $ADMITEMSRVPROGMEM, $ADMITEMSRVHEAPMEM,		  :9.1
.::		$ADMITEMSRVLOCALMEM, and $ADMITEMSRVCHILDCOUNT.		  :9.1
.:: 24 Jan 07 -	Added %XREFOFF to prevent cross	reference output!	  :9.1E
.:: 02 Jul 07 -	Updated	for 9.2	release.				  :9.2
.:: 16 Jul 07 -	Corrected syntax error for $AdmItemSrvMemCommittedBytes.  :9.2A
.:: 01 Dec 08 - Reviewed for 9.3 release.				  :9.3
.:: 05 Jun 09 - Added $ADMITEMSRVLOGRECTYPE.				  :9.3A
.:: 15 Feb 10 - Reviewed for 9.4 release.				  :9.4
.:: 09 Aug 10 - Updated for 9.4C patch release.				  :9.4C
.:: 12 Oct 10 - Updated for 9.4D patch release.				  :9.4D
.:: 31 Mar 11 - Reviewed for 9.5 release.				  :9.5
.:: 12 Aug 11 - Updated for the 9.5A release.				  :9.5A
.:: 01 Oct 12 - Reviewed for 9.6 release.				  :9.6
.:: 08 Mar 13 - Reviewed for 9.6A release.				  :9.6A
.:: 17 Feb 14 - Reviewed for 9.6C release.				  :9.6C
.:: 02 Sep 14 - Reviewed for 9.7 release.				  :9.7
.:: 09 Jan 15 - Reviewed for 9.7A release.				  :9.7A
.:: 29 May 15 - Reviewed for 9.7C release.				  :9.7C
.:: 01 Oct 15 - Reviewed for 9.8 release.				  :9.8
.:: 11 Mar 16 - Reviewed for 9.8A release.				  :9.8A
.:: 24 Oct 16 - Reviewed for 9.9 release.				  :9.9
.:: 		Added AdmGetInfo equates.				  :9.9
.:: 21 Apr 17 - Reviewed for 9.9A release.				  :9.9A
.:: 02 Oct 17 - Reviewed for 10.0 release.				  :10.0
.:: 27 Oct 17 - Changed ADMIN equates to be a DEFINE of a literal string. :10.0A
.:: 02 Apr 18 - Reviewed for 10.0A patch release.			  :10.0A
.:: 01 Oct 18 - Reviewed for 10.1 release.				  :10.1
.:: 01 Feb 19 - Reviewed for 10.1A release.				  :10.1A
.:: 01 Oct 19 - Reviewed for 10.2 release.				  :10.2
.:: 06 Apr 20 - Reviewed for 10.2A release.				  :10.2A
.:: 05 Oct 20 - Reviewed for 10.3 release.				  :10.3
.:: 23 Apr 21 - Reviewed for 10.3A release.				  :10.3A
.:: 01 Oct 21 - Reviewed for 10.4 release.                                :10.4
	 %ENDIF

 	 %IFDEF	   $ADMEQU_USE_EQU					  :10.0A
*------------------------------------------------------------------------------
. Admin	General	Ids
.
$CHILDTASKLIST	EQU	0
$ADMINTASKLIST	EQU	1
 
*------------------------------------------------------------------------------
. Admin	Child Data Types
.
$ADMITEMADMID		EQU	0
$ADMITEMUSERIP		EQU	1
$ADMITEMPROGRAMNAME	EQU	2
$ADMITEMFILENAME	EQU	3
$ADMITEMFILENAMEALL	EQU	3					  8.7B
$ADMITEMUPTIME		EQU	4
$ADMITEMLOGLEVEL	EQU	5
$ADMITEMCLIVER		EQU	6
$ADMITEMTASKID		EQU	7
$ADMITEMFULLCLIVER	EQU	8
$ADMITEMSHAREDMEM	EQU	9
$ADMITEMKEYNAME		EQU	10
$ADMITEMLOGSTATE	EQU	11
$ADMITEMSENDBYTES	EQU	12
$ADMITEMRECVBYTES	EQU	13
$ADMITEMRUNTYPE		EQU	14
$ADMITEMIDLETIME	EQU	15
$ADMITEMUSERNAME	EQU	16					  8.7B
$ADMITEMCOMPUTERNAME	EQU	17					  8.7B
$ADMITEMMODULENAME	EQU	18					  8.7B
$ADMITEMAAMFILENAME	EQU	19					  8.7B
$ADMITEMISIFILENAME	EQU	20					  8.7B
$ADMITEMPRTFILENAME	EQU	21					  8.7B
$ADMITEMTXTFILENAME	EQU	22					  8.7B
$ADMITEMRESERVE1	EQU	23					  9.0C
$ADMITEMRESERVE2	EQU	24					  9.0C
$ADMITEMCHILDCPUTIME	EQU	25					  9.0F
 
*------------------------------------------------------------------------------
. Admin	Server Data Types
.
$ADMITEMSRVVER		EQU	100
$ADMITEMLOGONCNT	EQU	101
$ADMITEMLOGONFAIL	EQU	102
$ADMITEMSRVUPTIME	EQU	103
$ADMITEMSRVTYPE		EQU	104	// 1-Application,2-File	Manager,3-Automation
$ADMITEMSRVEXENAME	EQU	105
$ADMITEMSRVININAME	EQU	106
$ADMITEMSRVLOGNAME	EQU	107
$ADMITEMSRVCHILDCNT	EQU	108
$ADMITEMSRVCHILDMAX	EQU	109
$ADMITEMSRVLOGCUR	EQU	110	// Server current log file position
$ADMITEMSRVLOGMAX	EQU	111	// Server log file maximum records
$ADMITEMSRVLOGSTART	EQU	112	// Server log starting data record
$ADMITEMSRVLOGRECS	EQU	113	// Server log file data	records
$ADMITEMSRVNAME		EQU	114					  8.7B
$ADMITEMSRVUSERNAME	EQU	115					  8.7B
$ADMITEMSRVCOMPUTERNAME	EQU	116					  8.7B
$ADMITEMSRVPROGMEM	EQU	117					  9.1
$ADMITEMSRVHEAPMEM	EQU	118					  9.1
$ADMITEMSRVLOCALMEM	EQU	119					  9.1
$ADMITEMSRVCHILDCOUNT	EQU	120					  9.1
$AdmItemSrvMemAvailableBytes	EQU 121					  9.2
$AdmItemSrvMemCommittedInUse	EQU 122					  9.2
$AdmItemSrvProcPrivateBytes	EQU 123					  9.2
$AdmItemSrvProcVirtualBytes	EQU 124					  9.2
$AdmItemSrvPageFilePercentUsage	EQU 125					  9.2
$AdmItemSrvProcThreadCount	EQU 126					  9.2
$AdmItemSrvMemCommitLimit	EQU 127					  9.2
$AdmItemSrvMemCommittedBytes	EQU 128					  9.2
$ADMITEMSRVLOGRECTYPE		EQU 129					  9.3A
$ADMITEMSRVALLCHILDCOUNT	EQU 130					  9.4B
$ADMITEMSRVALLCHILDHIGH		EQU 131					  9.4B
$ADMITEMSRVMAILMASK		EQU 132					  9.4C
$ADMITEMSRVHTTPMASK		EQU 133					  9.4C
$ADMITEMSRVREPID		EQU 134					  9.4D
$ADMITEMSRVREPSTATE		EQU 135					  9.4D
$AdmitemSrvWalMain		EQU 136					  9.5A
$AdmItemSrvWalMan		EQU 137					  9.5A
$AdmitemSrvWalUnMan		EQU 138					  9.5A

*------------------------------------------------------------------------------
. Admin	PL/B Runtime Values for Authorization License Information Requests 9.9
. See PL/B Language Reference manual under 'ADMGETINFO' Note 6.
.
$AdmItemSerialNumber	EQU	1
$AdmItemProductName	EQU	2
$AdmItemMaxLic		EQU	13
$AdmItemUsedLic		EQU	15
$AdmItemCompanyName	EQU	16
$AdmItemMisAddr		EQU	24
$AdmItemProductVer	EQU	25

*------------------------------------------------------------------------------
. Admin	PL/B Runtime Values for License Requestor Information Requests	  9.9
. See PL/B Language Reference manual under 'ADMGETINFO' Note 7.
.
.$AdmItemUserIp		EQU	1
$AdmItemMinLic		EQU	12
.$AdmItemMaxLic		EQU	13
.$AdmItemUsedLic	EQU	15
$AdmItemLicAdmId	EQU	23
$AdmItemLicThresh	EQU	24
$AdmItemLicBlock	EQU	25

*------------------------------------------------------------------------------
. Admin	PL/B Runtime Data Types
.
$ADMITEMLOCKIO	    	EQU	200
$ADMITEMRECORDLOCK	EQU	201
$ADMITEMXPIO		EQU	202
$ADMITEMW33RETRY	EQU	203
 
*------------------------------------------------------------------------------
. Admin	Commands
.
$ADMCMDSOFTTERM		EQU 1
$ADMCMDHARDTERM		EQU 2
$ADMCMDLOGGINGON	EQU 3
$ADMCMDLOGGINGOFF	EQU 4
$ADMCMDSETLOGLEVEL	EQU 5	; Value	parameter is 0-2
$ADMCMDSETADMFLAGS	EQU 6	; (Reserved Sunbelt Internal Usage)
$ADMCMDSHUTDOWNLOGON	EQU 7
$ADMCMDLOGMSGLEVEL0	EQU 8
$ADMCMDLOGMSGLEVEL1	EQU 9
$ADMCMDLOGMSGLEVEL2	EQU 10
$ADMCMDSETMAILMASK	EQU 11						  9.4C
$ADMCMDSETHTTPMASK	EQU 12						  9.4C

*------------------------------------------------------------------------------
. Admin	Setinfo	Actions
.
$ADMADD		EQU	1
$ADMDELETE	EQU	2
$ADMREPLACE	EQU	3
$ADMLOG		EQU	4
*------------------------------------------------------------------------------
.
	 %ELSE				;$ADMEQU_USE_EQU		  10.0A

*------------------------------------------------------------------------------
. Admin	General	Ids
.
$CHILDTASKLIST	DEFINE	"""0"""
$ADMINTASKLIST	DEFINE	"""1"""
 
*------------------------------------------------------------------------------
. Admin	Child Data Types
.
$ADMITEMADMID		DEFINE	"""0"""
$ADMITEMUSERIP		DEFINE	"""1"""
$ADMITEMPROGRAMNAME	DEFINE	"""2"""
$ADMITEMFILENAME	DEFINE	"""3"""
$ADMITEMFILENAMEALL	DEFINE	"""3"""					  8.7B
$ADMITEMUPTIME		DEFINE	"""4"""
$ADMITEMLOGLEVEL	DEFINE	"""5"""
$ADMITEMCLIVER		DEFINE	"""6"""
$ADMITEMTASKID		DEFINE	"""7"""
$ADMITEMFULLCLIVER	DEFINE	"""8"""
$ADMITEMSHAREDMEM	DEFINE	"""9"""
$ADMITEMKEYNAME		DEFINE	"""10"""
$ADMITEMLOGSTATE	DEFINE	"""11"""
$ADMITEMSENDBYTES	DEFINE	"""12"""
$ADMITEMRECVBYTES	DEFINE	"""13"""
$ADMITEMRUNTYPE		DEFINE	"""14"""
$ADMITEMIDLETIME	DEFINE	"""15"""
$ADMITEMUSERNAME	DEFINE	"""16"""				  8.7B
$ADMITEMCOMPUTERNAME	DEFINE	"""17"""				  8.7B
$ADMITEMMODULENAME	DEFINE	"""18"""				  8.7B
$ADMITEMAAMFILENAME	DEFINE	"""19"""				  8.7B
$ADMITEMISIFILENAME	DEFINE	"""20"""				  8.7B
$ADMITEMPRTFILENAME	DEFINE	"""21"""				  8.7B
$ADMITEMTXTFILENAME	DEFINE	"""22"""				  8.7B
$ADMITEMRESERVE1	DEFINE	"""23"""				  9.0C
$ADMITEMRESERVE2	DEFINE	"""24"""				  9.0C
$ADMITEMCHILDCPUTIME	DEFINE	"""25"""				  9.0F
 
*------------------------------------------------------------------------------
. Admin	Server Data Types
.
$ADMITEMSRVVER		DEFINE	"""100"""
$ADMITEMLOGONCNT	DEFINE	"""101"""
$ADMITEMLOGONFAIL	DEFINE	"""102"""
$ADMITEMSRVUPTIME	DEFINE	"""103"""
$ADMITEMSRVTYPE		DEFINE	"""104"""	// 1-Application,2-File	Manager,3-Automation
$ADMITEMSRVEXENAME	DEFINE	"""105"""
$ADMITEMSRVININAME	DEFINE	"""106"""
$ADMITEMSRVLOGNAME	DEFINE	"""107"""
$ADMITEMSRVCHILDCNT	DEFINE	"""108"""
$ADMITEMSRVCHILDMAX	DEFINE	"""109"""
$ADMITEMSRVLOGCUR	DEFINE	"""110"""	// Server current log file position
$ADMITEMSRVLOGMAX	DEFINE	"""111"""	// Server log file maximum records
$ADMITEMSRVLOGSTART	DEFINE	"""112"""	// Server log starting data record
$ADMITEMSRVLOGRECS	DEFINE	"""113"""	// Server log file data	records
$ADMITEMSRVNAME		DEFINE	"""114"""				  8.7B
$ADMITEMSRVUSERNAME	DEFINE	"""115"""				  8.7B
$ADMITEMSRVCOMPUTERNAME	DEFINE	"""116"""				  8.7B
$ADMITEMSRVPROGMEM	DEFINE	"""117"""				  9.1
$ADMITEMSRVHEAPMEM	DEFINE	"""118"""				  9.1
$ADMITEMSRVLOCALMEM	DEFINE	"""119"""				  9.1
$ADMITEMSRVCHILDCOUNT	DEFINE	"""120"""				  9.1
$AdmItemSrvMemAvailableBytes	DEFINE """121"""			  9.2
$AdmItemSrvMemCommittedInUse	DEFINE """122"""			  9.2
$AdmItemSrvProcPrivateBytes	DEFINE """123"""			  9.2
$AdmItemSrvProcVirtualBytes	DEFINE """124"""			  9.2
$AdmItemSrvPageFilePercentUsage	DEFINE """125"""			  9.2
$AdmItemSrvProcThreadCount	DEFINE """126"""			  9.2
$AdmItemSrvMemCommitLimit	DEFINE """127"""			  9.2
$AdmItemSrvMemCommittedBytes	DEFINE """128"""			  9.2
$ADMITEMSRVLOGRECTYPE		DEFINE """129"""			  9.3A
$ADMITEMSRVALLCHILDCOUNT	DEFINE """130"""			  9.4B
$ADMITEMSRVALLCHILDHIGH		DEFINE """131"""			  9.4B
$ADMITEMSRVMAILMASK		DEFINE """132"""			  9.4C
$ADMITEMSRVHTTPMASK		DEFINE """133"""			  9.4C
$ADMITEMSRVREPID		DEFINE """134"""			  9.4D
$ADMITEMSRVREPSTATE		DEFINE """135"""			  9.4D
$AdmitemSrvWalMain		DEFINE """136"""			  9.5A
$AdmItemSrvWalMan		DEFINE """137"""			  9.5A
$AdmitemSrvWalUnMan		DEFINE """138"""			  9.5A

*------------------------------------------------------------------------------
. Admin	PL/B Runtime Values for Authorization License Information Requests 9.9
. See PL/B Language Reference manual under 'ADMGETINFO' Note 6.
.
$AdmItemSerialNumber	DEFINE	"""1"""
$AdmItemProductName	DEFINE	"""2"""
$AdmItemMaxLic		DEFINE	"""13"""
$AdmItemUsedLic		DEFINE	"""15"""
$AdmItemCompanyName	DEFINE	"""16"""
$AdmItemMisAddr		DEFINE	"""24"""
$AdmItemProductVer	DEFINE	"""25"""

*------------------------------------------------------------------------------
. Admin	PL/B Runtime Values for License Requestor Information Requests	  9.9
. See PL/B Language Reference manual under 'ADMGETINFO' Note 7.
.
.$AdmItemUserIp		DEFINE	"""1"""
$AdmItemMinLic		DEFINE	"""12"""
.$AdmItemMaxLic		DEFINE	"""13"""
.$AdmItemUsedLic	DEFINE	"""15"""
$AdmItemLicAdmId	DEFINE	"""23"""
$AdmItemLicThresh	DEFINE	"""24"""
$AdmItemLicBlock	DEFINE	"""25"""

*------------------------------------------------------------------------------
. Admin	PL/B Runtime Data Types
.
$ADMITEMLOCKIO	    	DEFINE	"""200"""
$ADMITEMRECORDLOCK	DEFINE	"""201"""
$ADMITEMXPIO		DEFINE	"""202"""
$ADMITEMW33RETRY	DEFINE	"""203"""
 
*------------------------------------------------------------------------------
. Admin	Commands
.
$ADMCMDSOFTTERM		DEFINE """1"""
$ADMCMDHARDTERM		DEFINE """2"""
$ADMCMDLOGGINGON	DEFINE """3"""
$ADMCMDLOGGINGOFF	DEFINE """4"""
$ADMCMDSETLOGLEVEL	DEFINE """5"""	; Value	parameter is 0-2
$ADMCMDSETADMFLAGS	DEFINE """6"""	; (Reserved Sunbelt Internal Usage)
$ADMCMDSHUTDOWNLOGON	DEFINE """7"""
$ADMCMDLOGMSGLEVEL0	DEFINE """8"""
$ADMCMDLOGMSGLEVEL1	DEFINE """9"""
$ADMCMDLOGMSGLEVEL2	DEFINE """10"""
$ADMCMDSETMAILMASK	DEFINE """11"""					  9.4C
$ADMCMDSETHTTPMASK	DEFINE """12"""					  9.4C

*------------------------------------------------------------------------------
. Admin	Setinfo	Actions
.
$ADMADD		DEFINE	"""1"""
$ADMDELETE	DEFINE	"""2"""
$ADMREPLACE	DEFINE	"""3"""
$ADMLOG		DEFINE	"""4"""
*------------------------------------------------------------------------------
.
	 %ENDIF				;$ADMEQU_USE_EQU		  10.0A
.
	 %ENDIF				;$ADMEQU_LOADED			  9.1F
.
	 %XREFON   ;Restore cross reference state flag			  9.1E
.
	 LISTON
