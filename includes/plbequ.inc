	 LISTOFF
.
	 %XREFOFF  ;DO NOT include in cross reference!!			  9.1E
.
	 %IFNDEF   $PLBEQU_LOADED
$PLBEQU_LOADED EQU  1			;Flag that PLBEQU is loaded
*==============================================================================
. GUI designer support equates
.
. Last Revision	Date:  07 Aug 2025
.
. Revision History:
.
	 %IFDEF	   $PLBEQU_HISTORY					 :8.3A
.:: 15 Jan 97 -	Create PLB equate include definitions.			 :8.1
.:: 06 Feb 97 -	Added ICON to APPEARANCE property.			 :8.1
.::	      -	Added GROUPID to DROPID	property.			 :8.1
.::	      -	Added SHAPE to BGCOLOR and BDRCOLOR properties.		 :8.1
.:: 25 Feb 97 -	Added LINKHSCROLL and LINKVSCROLL.			 :8.1
.:: 05 Mar 97 -	Added AUTOSCALE, PICTSIZEH, PICTSIZEV, and WINPOS.	 :8.1
.:: 02 Apr 97 -	Changed	EDITTYPE to use	DECIMAL	and INTEGER		 :8.1
.:: 22 Apr 97 -	Added LINE object.					 :8.1
.::	      -	Added X1, X2, Y1, and Y2 properties for	LINE object.	 :8.1
.:: 04 Jun 97 -	Added MREGION to DROPID	property.			 :8.1C
.::	      -	Added MREGION to VISIBLE property.			 :8.1C
.:: 12 Jun 97 -	Reversed DECIMAL and INTEGER equate values for EDITTYPE	 :8.1C
.::		object.							 :8.1C
.::		Added GRIDALIGN, GRIDSIZEH, GRIDSIZEV, and UNITS for the :8.1C
.::		WINDOW object.						 :8.1C
.:: 16 Jun 97 -	Updated	that the READONLY property can only be applied to:8.1C
.::		an EDITTEXT object through the CREATE statement.	 :8.1C
.:: 01 Jul 97 -	Added conditional compile detection equate which can	 :8.1E
.::		allow PLBEQU.INC to exist multiple times in the	source	 :8.1E
.::		without	causing	errors.					 :8.1E
.:: 15 Jul 97 -	Added option to	AUTOREDRAW property.			 :8.1F
.:: 23 Jul 97 -	Added OVERTYPE and SELECTALL properties	for EDITTEXT.	 :8.1F
.:: 09 Dec 97 -	Updated	MULTISELECT to document	EXTENDED.  Also	removed	 :8.2
.::		MULTISELECT from being a SETPROP control.		 :8.2
.::		Removed	ALIGNMENT from being a SETPROP control for an	 :8.2
.::		EDITTEXT.						 :8.2
.:: 11 Dec 97 -	Added KEYPRESS DEFINES and CONST declarations.		 :8.2
.::		See $PLBDEF and	$PLBCONST below.			 :8.2
.:: 02 Jan 98 -	Added SHAPE object to HEIGHT, LEFT, TOP, and WIDTH	 :8.2A
.::		properties.						 :8.2A
.:: 11 Aug 98 -	Corrected default for PERCENT property.			 :8.2K
.:: 12 Aug 98 -	Added PICTURE and ICON properties for BUTTON object.	 :8.2K
.:: 21 Aug 98 -	Added VALUE property for PROGRESS object.		 :8.2K
.:: 17 Sep 98 -	Added PARENTWIN	property for WINDOW object.		 :8.2K
.:: 22 Sep 98 -	Added TREEVIEW object to property descriptions.	 Also,	 :8.2M
.::		descriptions for new TREEVIEW properties BUTTONS,	 :8.2M
.::		HIDESEL, INDENT, and TREELNSTYLE.			 :8.2M
.:: 12 Oct 98 -	Added LISTVIEW object to property descriptions.	 Added	 :8.2M
.::		descriptions for new LISTVIEW properties ARRANGE,	 :8.2M
.::		HIDECOLHDR, LABELWRAP, and VIEWSTYLE.			 :8.2M
.:: 13 Oct 98 -	Added IMAGELIST	object property	descriptions for	 :8.2M
.::		IMAGESIZEH, IMAGESIZEV,	MASKCOLOR, and USEMASK.		 :8.2M
.:: 11 Dec 98 -	Updated	to reflect properties for AUTOMATION, CONTAINER, :8.3
.::		CONTROL, and VARIANT objects.				 :8.3
.:: 10 Feb 99 -	Added TOOLTIP property.					 :8.3
.:: 11 Feb 99 -	Added ALERT TYPE={dnumnvar} pre-defined	values.		 :8.3
.:: 19 Feb 99 -	Added NEGBORDERS and NEGMENUS properties for a WINDOW	 :8.3
.::		object.							 :8.3
.:: 09 Mar 99 -	Updated	description of the NEGMENUS property.		 :8.3A
.:: 26 Mar 99 -	Added FULLROW property for LISTVIEW.			 :8.3A
.:: 28 Apr 99 -	Added $ENTER definition.				 :8.3B
.:: 29 Apr 99 -	Added $TRUE and	$FALSE equates.				 :8.3C
.:: 19 Jul 99 -	Added ALIGNTEXT	property for RADIO, CHECKBOX, RADIOGRP,	 :8.3E
.::		and CHECKGRP object support.				 :8.3E
.:: 19 Jul 00 -	Added TOOLTIPHWND property available to	any object which :8.3E
.::		supports the TOOLTIP property.				 :8.3E
.:: 09 May 00 -	Added IMAGECOLORS property for the IMAGELIST object.	 :8.4A
.:: 16 May 00 -	Modified to reflect that SORTED	is not supported property:8.4B
.::		for a DATALIST in a SETPROP operation.			 :8.4B
.:: 29 Jun 00 -	Added VARABSVALUE property for the VARIANT object.	 :8.4B
.:: 07 Jul 00 -	Added SELGROUPID property for RADIO object.		 :8.4B
.:: 25 Sep 00 -	Modified SCROLLBAR property to support EDITTEXT	object.	 :8.4E
.:: 16 Oct 00 -	Added $VALIDATE	event number.				 :8.4E
.:: 07 Dec 00 -	Added equates to support DTYPE,	DTYPEBASE, and DTYPESUB	 :8.5A
.::		pseudo command operator	type values.			 :8.5A
.:: 01 Feb 01 -	Added NOMENURESIZE property for	a WINDOW object.	 :8.5C
.:: 11 Mar 02 -	Added LISTVIEW properties ACTIVATE, CHECKBOX, GRIDLINE,	 :8.6B
.::		HOTTRACK, HOVERSEL, and	HOVERTIME.			 :8.6B
.:: 11 Mar 02 -	Added TREEVIEW properties CHECKBOX, FULLROW, & HOTTRACK. :8.6B
.:: 11 Mar 02 -	Added $ITEMACTIVATE event number for LISTVIEW object.	 :8.6B
.:: 16 Apr 02 -	Modified WINTYPE property to support MDI windows.	 :8.6C
.:: 16 Apr 02 -	Added new properties for Window	object as follows:	 :8.6C
.::		AUTOSCROLL, MINSCROLLH,	MINSCROLLV, INTASKBAR, MDIBORDER,:8.6C
.::		MDIHEIGHT, MDILEFT, MDISCROLL, MDITOP, MDIWIDTH, TOPMOST,:8.6C
.::		and WINBORDER.						 :8.6C
.:: 12 Jun 02 -	Added new properties for STATUSBAR, STATUSPANEL, TOOLBAR,:8.6D
.::		and TOOLBUTTON objects.					 :8.6D
.:: 31 Dec 02 -	Added LISTOFF/LISTON control.				 :8.7
.:: 10 Jan 03 -	Added $VT_ARRAY	support	for VARIANT objects.		 :8.7
.:: 20 Mar 03 -	Added new properties for SPLITTER and PANEL objects.	 :8.7A
.::		Added ANCHOR, DOCKPADB,	DOCKPADL, DOCKPADR, DOCKPADT,	 :8.7A
.::		MINEXTRA, and MINSIZE.	Updated	DOCK property.		 :8.7A
.:: 24 Mar 03 -	Added description of WINHEIGHT and WINWIDTH properties	 :8.7B
.::		that were added	in release 8.6D.			 :8.7B
.:: 16 Jul 03 -	Updated	object type values for MAINWINDOW, STATUSPANEL,	 :8.7C
.::		TOOLBUTTON, SPLITTER, PANEL and	EDITNUMBER.		 :8.7C
.:: 28 Jul 03 -	Updated	for new	properties of COMBOBOX,	DATALIST,	 :8.7C
.::		EDITNUMBER, and	EDITTEXT objects.			 :8.7C
.:: 24 Nov 03 -	Added new DPI property for EDITNUMBER object.		 :8.7D
.:: 19 Jan 04 -	Added new properties for EDITDATETIME object.		 :9.0
.:: 09 Feb 04 -	Added INTEGER 8	type.  Also, updated INTEGER subtypes.	 :9.0
.:: 09 Feb 04 -	Added type values for LABELTEXT	& ANIMATE.		 :9.0
.:: 25 May 04 -	Updated	for new	LABELTEXT object.			 :9.0
.:: 25 May 04 -	Updated	for new	ANIMATE	object.				 :9.0
.:: 25 May 04 -	Added new properties for FONT object.			 :9.0
.:: 26 May 04 -	Updated	for new	MENUITEM object.			 :9.0
.:: 26 May 04 -	Updated	for MENU object.				 :9.0
.:: 09 Jun 04 -	Added OSEVENTMASK property.				 :9.0A
.:: 12 Jul 04 -	Added $MOUSEWHEEL, $HSCROLL, and $VSCROLL events.	 :9.0B
.:: 12 Jul 04 -	Updated	the OSEVENTMASK	property.			 :9.0B
.:: 23 Jul 04 -	Added RICHEDITTEXT object.				 :9.0B
.:: 31 Mar 05 -	Added BUTTONENTRYKEY property for WINDOW object.	 :9.0E
.:: 31 Mar 05 -	Added EDITNUMBER object	for VALUE property.		 :9.0E
.:: 01 Apr 05 -	Added EDITNUMBER object	for STATIC property.		 :9.0F
.:: 11 Apr 05 -	Added STATTEXT object for DOCK property.		 :9.0F
.:: 23 Aug 05 -	Updated	the object types.				 :9.1
.:: 18 Nov 05 -	Added $MAXIMIZE	and $MINIMIZE equates.			 :9.1
.:: 09 Jan 06 -	Added PANEL object for CLIPCTRL	property.		 :9.0H
.:: 22 Feb 06 -	Added STATUSBAR	and TOOLBAR equates that were missing.	 :9.1
.:: 28 Jun 06 -	Updated	the CLIPCTRL, MENUORDER, MERGETYPE, RESOURCE,	 :9.1A
.::		and TABID properties.					 :9.1A
.:: 19 Jul 06 -	Updated	the HELPID property to include the MENUITEM	 :9.1C
.::		object.							 :9.1C
.:: 19 Jul 06 -	Added MDILIST property.					 :9.1C
.:: 17 Nov 06 -	Modified WINTYPE for CE	values.				 :9.1C
.:: 22 Jan 07 -	Updated	the TOPMOST property description.		 :9.1E
.:: 24 Jan 07 -	Added %XREFOFF to prevent cross	reference output!	 :9.1E
.:: 02 Jul 07 -	Updated	VT variable types.				 :9.2
.:: 05 Oct 07 -	Modified the TOPMOST description for extended behavior.	 :9.2B
.:: 03 Jan 08 -	Added $TICKNONE	equate.					 :9.2B
.:: 31 Jan 08 -	Added the SCROLLSIZEMODE property.			 :9.2C
.:: 04 Apr 08 -	9.2C patch release.					 :9.2C
.:: 14 May 08 - Added conditional compiler directives for $TRUE/$FALSE.	 ;9.2D
.:: 02 Jul 08 - Added XFILE mode values.				 :9.3
.:: 19 Aug 08 - Corrected problem where the $T_RADIOGRP amd $T_RADIO	 :9.3
.:: 		equated values were reversed.				 :9.3
.:: 09 Sep 08 - Removed the $NONE value from the AUTOSCALE property for  :9.3
.::		PICT object.						 :9.3 
.:: 22 Sep 08 - Added special ANSI graphic character values.		 :9.3
.:: 22 Sep 08 - Added $T_NETOBJECT, $T_NETCONTROL, $BT_NETOBJECT,	 :9.3
.::		$BT_NETCONTROL, $ST_NETOBJECT, and $ST_NETCONTROL	 :9.3
.::		equated values.						 :9.3
.:: 30 Oct 08 - Added the GROUPVALUE property for a RADIO object.	 :9.3
.:: 07 Nov 08 - Added NETCONTROL as a referenced object for ACCEPTTAB.	 :9.3
.:: 07 Nov 08 - Added ENTERTAB property description.			 :9.3
.:: 07 Nov 08 - Corrected problem where $IDIGNORE was misspelled.	 :9.3
.:: 01 Dec 08 - Reviewed for final 9.3 release.				 :9.3
.:: 18 Dec 08 - Removed the $NONE from the TEXTALIGN property values.	 :9.3A
.:: 15 Jan 09 - Added the $XFILE_FILTERNOCASE definition.		 :9.3A
.:: 13 Apr 09 - Added CLIPSIB documentation.				 :9.3A
.:: 16 Apr 09 - Correct default setting for FORMAT property.		 :9.3A
.:: 05 Jun 09 - Reviewed for final 9.3A release.			 :9.3A
.:: 15 Feb 10 - Reviewed for 9.4 release.				 :9.4
.:: 08 Jul 10 - Added the TABSTYLE property for a TABCONTROL object.	 :9.4C
.:: 		Added the TABCONTROL object to the IMAGELIST property.	 :9.4C
.:: 30 Jul 10 - Modified for EDITTYPE property change.			 :9.4C
.:: 09 Aug 10 - Reviewed for 9.4C patch release.			 :9.4C
.:: 05 Oct 10 - Added $SCALEFULL and $SCALEMANUAL equates.		 :9.4C
.:: 31 Mar 11 - Reviewed for 9.5 release.				 :9.5
.:: 08 Jun 11 - Added the $T_XFILE value.				 :9.5A
.:: 03 Aug 11 - Added BUTTON/CHECKBOX to TITLE property. Also, added	 :9.5A
.::		STATTEXT to the TEXT property.				 :9.5A
.:: 11 Aug 11 - Added STATUSBAR to the TEXT property.			 :9.5A
.:: 30 Jan 12 - Added HTTP *FLAGS bit mask values.			 :9.5B
.:: 05 Mar 12 - Updated for missing types.				 :9.6
.:: 11 Apr 12 - Corrected a $PLBHTTP compiler warning issue.		 :9.6
.:: 01 Oct 12 - Updated for 9.6 release.				 :9.6
.:: 10 Jan 13 - Added the VT_I1 definition.				 :9.6A
.:: 10 Jan 13 - Added extended VT type values that can be returned from	 :9.6A
.:: 		GETPROP VARIANT VARTYPE operation.			 :9.6A
.:: 08 Mar 13 - Reviewed for 9.6A release.				 :9.6A
.:: 17 Feb 14 - Reviewed for 9.6C release.				 :9.6C
.:: 13 Mar 14 - Added SHOWWEBMENU property.				 :9.7
.:: 20 Jun 14 - Added CLIENT and RUNTIME object type references.	 :9.7
.:: 02 Sep 14 - Updated for 9.7 release.				 :9.7
.:: 05 Nov 14 - Added $FileInput equate for BUTTONTYPE property.         :9.7A
.:: 18 Dec 14 - Added $AUTOTRISTATE equate for TRISTATE property.	 :9.7A
.:: 09 Jan 15 - Updated for 9.7A release.				 :9.7A
.:: 29 May 15 - Updated for 9.7C release.				 :9.7C
.:: 01 Oct 15 - Reviewed for 9.8 release.				 :9.8
.:: 09 Nov 15 - Added XDATA object type references.			 :9.8A
.:: 25 Feb 16 - Added $MB_ICONQUESTION equate for ALERT.		 :9.8A
.:: 11 Mar 16 - Reviewed for 9.8A release.				 :9.8A
.:: 08 Jun 16 - Added $ClientEventOrient for CLIENT object.		 :9.8B
.:: 01 Jul 16 - Reviewed changes for 9.8B patch release.		 :9.8B
.:: 22 Jul 16 - Added IMAGELIST object to URLSOURCE description.	 :9.9
.:: 		IMAGELISTH and IMAGELISTV properties allowed in SETPROP	 :9.9
.:: 		for PWS IMAGELIST. Modified CHECKBOX properties to allow :9.9
.:: 		SETPROP of this property for a PWS TREEVIEW.		 :9.9
.:: 16 Aug 16 - Add event modifier defines used for MouseUp, MouseDown,	 :9.9
.:: 		MouseWheel, and KeyPress events.			 :9.9
.:: 01 Sep 16 - Added $RUNSUSPEND, $RUNRESUME, and $RUNIDLE events.	 :9.9
.:: 29 Sep 16 - Added descriptions for WEBHEIGHT, WEBLEFT, WEBPOSITION,  :9.9
.::             WEBTOP, and WEBWIDTH properties.			 :9.9
.:: 17 Oct 16 - Reviewed for 9.9 release.				 :9.9
.:: 22 Mar 17 - Added $JQueryEvent event				 :9.9A
.:: 21 Apr 17 - Reviewed for 9.9A release.				 :9.9A
.:: 02 Oct 17 - Reviewed for 10.0 release.				 :10.0
.:: 27 Oct 17 - Added $ClientEventPostMessage equate.			 :10.0A
.:: 01 Nov 17 - Added $MAXIMIZEWIDTH for PWS.				 :10.0A
.:: 08 Jan 18 - Added InnerHtml property for HTMLCONTROL object.	 :10.0A
.:: 26 Jan 18 - Added the $ClientEventPostMessage equate.		 :10.0A
.:: 		Added HTMLCONTROL object.				 :10.0A
.:: 16 Feb 18 - Added the CODEPAGE property for HTMLCONTROL.		 :10.0A
.:: 02 Apr 18 - Reviewed for 10.0A patch release.			 :10.0A
.:: 01 Oct 18 - Reviewed for 10.1 release and updated for ERROR object.	 :10.1
.:: 19 Oct 18 - Added STATUSBAR and TOOLBAR to support object for the    :10.1A
.::		WEBCLASS, WEBHEIGHT, WEBWIDTH, WEBLEFT, WEBTOP, and      :10.1A
.::		WEBPOSITION properties.					 :10.1A
.:: 01 Feb 19 - Added SPLITTER to support object for the WEBCLASS,	 :10.1A
.::		WEBHEIGHT, WEBWIDTH, WEBLEFT, WEBTOP, and WEBPOSITION    :10.1A
.::		properties.						 :10.1A
.:: 01 Oct 19 - Reviewed for 10.2 release.				 :10.2
.:: 06 Apr 20 - Added PICT object to the BACKSTYLE and identified the	 :10.2A
.:: 		restrictions for usage.					 :10.2A
.:: 05 Oct 20 - Reviewed for 10.3 release.				 :10.3
.:: 		Added $HTTP_FLAG_NO_U66 for HTTP *FLAGS.		 :10.3
.:: 09 Nov 20 - Added $HTTP_FLAG_USESUNSSL for HTTP *FLAGS.		 :10.3A
.:: 	      - Added MAILSEND *OPTIONS bit mask variables		 :10.3A
.:: 	        $MAIL_FLAG_OPENSSL, $MAIL_FLAG_STARTTLS			 :10.3A
.:: 	        $MAIL_FLAG_CONTENT_DISP, and $MAIL_FLAG_USESUNSSL.	 :10.3A
.:: 23 Apr 21 - Reviewed for 10.3A release.				 :10.3A
.:: 07 May 21 - Added HTTP *FLAGS bit values of $HTTP_FLAG_TLSV1,	 :10.3B
.:: 		$HTTP_FLAG_TLSV11, $HTTP_FLAG_TLSV12, and		 :10.3B
.:: 		$HTTP_FLAG_USESSLDEFS.					 :10.3B
.:: 02 Jun 21 - Changed $HTTP_FLAG_RAWBIN_RESULT to be named		 :10.3B
.:: 		$HTTP_FLAG_RAWBINARY.					 :10.3B
.:: 01 Oct 21 - Reviewed for 10.4 release checking changes since 10.3A.  :10.4
.:: 03 Oct 22 - Added CONTEXT property used for web objects.		 :10.5
.:: 		Added BUTTSTATE property for BUTTON web object.		 :10.5
.:: 		Added INPUTTYPE property for EDITTEXT web object.	 :10.5
.:: 		Added SWITCH property for CHECKBOX web object.		 :10.5
.:: 		Added WEBMODE property for HTMLCONTROL and WINDOW.	 :10.5
.:: 		Added WEBOBJECT property for PL/B objects.		 :10.5
.::		Added DATACOLUMN, DATAROW, and DATATABLE properties.	 :10.5
.:: 18 May 23 - Added color constants for Bootstrap 5 Contexts           :10.6
.:: 02 Oct 23 - Reviewed for the 10.6 release.				 :10.6
.:: 29 Aug 24 - Modified for MPI ( Multi Page Interface ) support.	 :10.7 
.:: 01 Oct 24 - Added $HTTP_FLAG_USE_IPV6 flags value for HTTP.		 :10.7
.::		Added $MAIL_FLAG_USEIPV6 options value for MAILSEND.	 :10.7
.:: 07 Aug 25 - Added DATASET properties: COUNT, DATAFILTER, DATATYPE,	 :10.8
.:: 		MAXITEMS and NULLSIZE.					 :10.8 
.::
	 %ENDIF								 :8.3A
.
*------------------------------------------------------------------------------
.
. Note:	 Sections added	to this	include	file are for user information
.	 for an	application.  This file	can be modified	and used to meet
.	 the requirements for any user application.
.
*------------------------------------------------------------------------------
.
	 %IFNDEF   $PLBDEF						  8.2
$PLBDEF	 EQU	   1		;1 ==> include KEYPRESS	defines		  8.7
	 %ENDIF								  8.2
.
	 %IFNDEF   $PLBCONST						  8.2
$PLBCONST EQU	   1		;1 ==> include KEYPRESS	CONST		  8.7
	 %ENDIF								  8.2
.
	 %IFNDEF   $PLBALERT						  8.3f
$PLBALERT EQU	   1		;1 ==> include ALERT TYPE INTEGERs	  8.7
	 %ENDIF								  8.3f
.
	 %IFNDEF   $PLBDTYPE						  8.5A
$PLBDTYPE EQU	   1		;1 ==> include DTYPE equates		  8.7
	 %ENDIF								  8.5A
.
	 %IFNDEF   $PLBXFILE						  9.3
$PLBXFILE EQU	   1		;1 ==> include XFILE mode values
	 %ENDIF
.
	 %IFNDEF   $PLBGRAPHIC						  9.3
$PLBGRAPHIC EQU	   1		;1 ==> include special graphic values
	 %ENDIF
.
	 %IFNDEF   $PLBHTTP						  9.6
$PLBHTTP EQU	   1		;1 ==> include HTTP integers
	 %ENDIF	 
.
	 %IFNDEF   $PLBMAILSEND						  10.3A
$PLBMAILSEND EQU   1		;1 ==> include MAILSEND integers
	 %ENDIF

.
	 %IFNDEF   $PLBGETMODE						  9.9A
$PLBGETMODE EQU	   1		;1 ==> include GETMODE integers
	 %ENDIF
.
	 %IFNDEF   $PLBEQU						  8.1E
$PLBEQU	  EQU	   1		;Flag that PLBEQU is used.		  8.1E
*------------------------------------------------------------------------------
. General Usage	Equates
.
$ON	 EQU	   1
$OFF	 EQU	   0
$NONE	 EQU	   0
.
	%IFNDEF	   $TRUE						  9.2D
$TRUE	 EQU	   1							  8.3C
	%ENDIF								  9.2D
.
	%IFNDEF	   $FALSE						  9.2D
$FALSE	 EQU	   0							  8.3C
	%ENDIF								  9.2D
.
*------------------------------------------------------------------------------
. Event	Type Indicators
.
$LOAD	      EQU    0
$ACTIVATE     EQU    1
$DEACTIVATE   EQU    2
$CHANGE	      EQU    3
$CLICK	      EQU    4
$CLOSE	      EQU    5
$DBLCLICK     EQU    6
$DRAGDROP     EQU    7
$DRAGOVER     EQU    8
$GOTFOCUS     EQU    9
$KEYPRESS     EQU    10
$LOSTFOCUS    EQU    11
$MOVE	      EQU    12
$MOUSEDOWN    EQU    13
$MOUSEUP      EQU    14
$MOUSEMOVE    EQU    15
$PAINT	      EQU    16
$RESIZE	      EQU    17
$TIMER	      EQU    18
$OLDEVENT     EQU    19
$FORMINIT     EQU    20
$OBJMOVE      EQU    21
$UPDATED      EQU    22			;AUTOMATION object
$COLCLICK     EQU    23			;ONLY allowed with LISTVIEW object
.					;when SORTHEADER property set to $ON.
$VALIDATE     EQU    24			;8.5
$ITEMACTIVATE EQU    25			;8.6B LISTVIEW event.
$BUTTONCLICK  EQU    26			;8.6D TOOLBAR event.
$ITEMCLICK    EQU    26			;Same as $BUTTONCLICK for TOOLBAR or
					;MENUITEM objects.
$MOUSEWHEEL   EQU    27			;9.0B LISTVIEW mouse wheel
$HSCROLL      EQU    28			;9.0B LISTVIEW horizontal scrollbar
$VSCROLL      EQU    29			;9.0B LISTVIEW vertical	scrollbar
$SELCHANGE    EQU    30			;9.0B
$LINKCLICK    EQU    31			;9.0B
$SUSPEND      EQU    32			;9.4
$CHILDSIG     EQU    33			;9.8 PL/B Web Server ONLY
$RUNSUSPEND   EQU    34			;9.9 PL/B Web Server RUNTIME ONLY
$RUNRESUME    EQU    35			;9.9 PL/B Web Server RUNTIME ONLY
$RUNIDLE      EQU    36			;9.9 PL/B Web Server RUNTIME ONLY
.
$JQueryEvent  EQU    200		;9.9A PL/B Web Server RUNTIME ONLY
$JQUERY       EQU    200
.
$ClientEventOrient      EQU 301		;9.8B  PL/B Web Server ONLY
$SCRNORIENT             EQU 301		;9.8B  PL/B Web Server ONLY
$ClientEventPostMessage EQU 302		;10.0A PL/B Web Server ONLY
$POSTMESSAGE            EQU 302		;10.0A PL/B Web Server ONLY
.
*==============================================================================
. Object Properties
.
*------------------------------------------------------------------------------
.   ACCEPTTAB=dnumnvar				CREATE	SETPROP	GETPROP	  9.0B
.
. Description:
.	This property is used to set or	get the	TAB character acceptance state.
.
.	If the state is	ON, then TAB characters	are accepted by	the
.	object and do not cause	a focus	change.	If the state
.	is OFF,	the TAB	character causes a focus change.
.
. Objects:
.	RICHEDITTEXT
.       NETCONTROL							  9.3
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   ACTIVATE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	When this property is set to $ONECLICK,	the LISTVIEW object sends an
.	ACTIVATE event when the	user clicks an item. This property also
.	enables	hot tracking in	the LISTVIEW object. Hot tracking means	that
.	when the cursor	moves over an item, it is highlighted but not
.	selected.
.
.	When this property is set to $TWOCLICK,	the LISTVIEW object sends an
.	ACTIVATE event when the	user double-clicks an item. This property
.	also enables hot tracking in the LISTVIEW object. Hot tracking means
.	that when the cursor moves over	an item, it is highlighted but not
.	selected.
.
.	Note:
.
.	  1. This property will	not take affect	unless a Microsoft file
.	     version of	4.70 or	later of 'comctl32.dll'	is installed on
.	     a given workstation.
.
.	  2. This property will	only affect the	operation of the LISTVIEW
.	     object when the VIEWSTYLE property	is set to $VIEWREPORT style.
.
. Objects:
.	LISTVIEW
.
. dnumnvar values:
.
$STANDARD     EQU   	1	// Default
$ONECLICK     EQU	2
$TWOCLICK     EQU	3
.
*------------------------------------------------------------------------------
.   ACTIVEROW=dnumnvar				CREATE	SETPROP	GETPROP   10.5
.
. Description:
.	This property is used to set or obtain the zero based active row.
.
. Objects:
.       DATATABLE
.
*------------------------------------------------------------------------------
.   ALIGNMENT=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	The ALIGNMENT property defines how the text is to be output
.	horizontally for the object.
.
.	Note1: The EDITTEXT object doesn't support changing of this property
.	       using the SETPROP statement.
.
. Objects:
.       DATACOLUMN                                                       10.5
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	LABELTEXT							  9.0
.	RICHEDITTEXT							  9.0B
.	STATTEXT
.
. dnumnvar values:
.
.$NONE	      EQU	0	       // Default
$CENTER	      EQU	1
$LEFT	      EQU	2
$RIGHT	      EQU	3
.
*------------------------------------------------------------------------------
.   ALIGNTEXT=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	The ALIGNTEXT property specifies whether the text is to	be aligned
.	to the left or right of	a control indicator.
.
. Objects:
.	CHECKBOX
.	CHECKGRP
.	RADIO
.	RADIOGRP
.
. dnumnvar values:
.
.$NONE	      EQU	0	       // Default
$ALIGNLEFT    EQU	1
$ALIGNRIGHT   EQU	2
.
*------------------------------------------------------------------------------
.   ALLOWMINUS=dnumnvar				CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used to prevent or allow negative numbers. If the
.	property is set	to $OFF, a leading minus sign is not allowed. If 
.	set to $ON, a leading minus sign is allowed.
.
. Objects:
.	EDITNUMBER
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.  ALTTEXT=svarslit				CREATE	SETPROP	 GETPROP  9.7
.
. Description:
.       This property defines the alternate text that is to be rendered
.       in place of an image when the image is not shown for an ICON or PICT
.       object at a PL/B Web Client. An image may not appear based on a
.       browser configuration setting or because the image resource is not
.       accessible. The URLSOURCE property identifies the image resource
.       being rendered.
.
.	Note:
.	   1. In release 9.8B, the suppport to allow the SETPROP of the
.	      ALTTEXT property was added.
.	
. Objects:
.       ICON
.       PICT
.
. svarslit values:
.
.	The <svarslit> variable	is a text string that is displayed at a
.	client browser when an ICON or PICT image resource can be rendered.
.
*------------------------------------------------------------------------------
.   ANCHOR=dnumnvar				CREATE	SETPROP	GETPROP	  8.7A
.
. Description:
.	This property allows an	object to be anchored to one or	more edges
.	of its parent object. Anchoring	an object to its parent	ensures
.	that the anchored edges	remain in the same position relative to
.	the edges of the parent	container when it is resized. By default
.	objects	are anchored to	the top/left The possible
.	anchor values are as follows:
.
.	$ANCHORBL	- Bottom, Left
.	$ANCHORBLR	- Bottom, Left/Right
.	$ANCHORBR	- Bottom, Right
.	$ANCHORTBL	- Top/Bottom, Left
.	$ANCHORTBLR	- Top/Bottom, Left/Right
.	$ANCHORTBR	- Top/Bottom, Right
.	$ANCHORTL	- Top, Left
.	$ANCHORTLR	- Top, Left/Right
.	$ANCHORTR	- Top, Right
.
. Objects:
.	ANIMATE								  9.0
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	GROUPBOX
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	ICON
.	LABELTEXT							  9.0
.	LISTVIEW
.	MREGION
.	MOVIE
.	PANEL
.	PICT
.	PROGRESS
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	SLIDER
.	STATTEXT
.	STATUSBAR
.	TABCONTROL
.	TOOLBAR
.	TREEVIEW
.	VSCROLLBAR
.
. dnumnvar values:
.
.$NONE		EQU	0
$ANCHORBL	EQU	1
$ANCHORBLR	EQU	2
$ANCHORBR	EQU	3
$ANCHORTBL	EQU	4
$ANCHORTBLR	EQU	5
$ANCHORTBR	EQU	6
$ANCHORTL	EQU	7
$ANCHORTLR	EQU	8
$ANCHORTR	EQU	9
.
*------------------------------------------------------------------------------
.  ANGLE=dnumnvar				CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property is used in set or	get the	font angle in 1/10 of a
.	degree.
.
.
. Objects:
.	FONT
.
*------------------------------------------------------------------------------
.   APPEARANCE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	The APPEARANCE property	specifies when an object should
.	have a 3D look or a non-3D look.  This property	should replace
.	the STYLE property for these objects.  If this property	is
.	not specified, the default appearance is determined by the
.	current	SETMODE	*3D state.  If the SETMODE *3D state has not
.	been specified,	then the appearance defaults to	be the same
.	as defined for the window.
.
. Note:	Under Windows95	these objects always have a 3D presentation
.	regardless of the control value	provided.
.
. Objects:
.	ANIMATE								  9.0
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	DATALIST
.	ICON
.	LABELTEXT							  9.0
.	LISTVIEW
.	POPUPMENU  (OBSOLETE)
.	RADIO
.	RADIOGRP
.	TOOLBAR
.	TREEVIEW
.	WINDOW
.
. dnumnvar values:
.
$3D	      EQU	1
$FLAT	      EQU	2
$LISTLBL      EQU       3      //PLB Web Server LABELTEXT ONLY		  9.7C
$H1           EQU       4      //PLB Web Server LABELTEXT ONLY            9.7C
$PROG         EQU       5      //PLB Web Server LABELTEXT ONLY            9.7C
$BS5ALERT     EQU       6      //PLB Web Server LABELTEXT ONLY           10.6
$BS5ALERTX    EQU       7      //PLB Web Server LABELTEXT ONLY           10.6
.
*------------------------------------------------------------------------------
.   ARRANGE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property sets the arrangement of icons in large and small icon
.	view mode. It may be one of:
.
.	$ARRANGELEFT - Arrange the icons along the left	of the ListView.
.	$ARRANGETOP  - Arrange the icons along the top of the ListView.
.	$ARRANGENONE - Do not arrange the icons	in any special order.
.
. Objects:
.	LISTVIEW
.
. dnumnvar values:
.
$ARRANGELEFT  EQU	1
$ARRANGETOP   EQU	2
$ARRANGENONE  EQU	3	       // Default
.
*------------------------------------------------------------------------------
.   AUTOACT=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is the property indicating when an OLE container
.	object should be activated. It may be one of:
.
.	$AUTOACTDBLCLICK  - The	object is automatically	activated when the
.			   container object is double-clicked or the ENTER
.			   key is pressed when the container object has
.			   the focus.
.	$AUTOACTGETFOCUS  - The	object is automatically	activated when the
.			   container object gets keyboard focus.
.	$AUTOACTMANUAL	  - The	object is not automatically activated. It
.			   can be activated by using the $DoVerb method.
.
. Objects:
.	CONTAINER
.
. dnumnvar values:
.
$AUTOACTDBLCLICK EQU	   1		// Default
$AUTOACTGETFOCUS EQU	   2
$AUTOACTMANUAL	 EQU	   3
.
*------------------------------------------------------------------------------
.   AUTOPLAY=dnumnvar				CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property enables or disables the automatic	playing	of
.	an AVI file when opened	by an ANIMATE object.
.
. Objects:
.	ANIMATE
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   AUTOREDRAW=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	When this property is set to zero, then	the repainting of the
.	object is disabled.  When this property	is set to one, then the
.	repainting of the objects takes	place as normal. If this property
.	is set to two the object is erased before it is	refreshed.
.
. Objects:
.	COMBOBOX
.	DATALIST
.	LISTVIEW
.	POPUPMENU  (OBSOLETE)
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1	       // Default
$WITHERASE    EQU	2
.
*------------------------------------------------------------------------------
.   AUTOENTER=dnumnvar				CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used to set or	get the	automatic Entry	State.
.
.    (EDITNUMBER)
.	If the state is	ON, then the object automatically tabs to the next
.	object in the tabbing sequence when the	number is completed using
.	the keyboard.  If a number has decimal digits, then it is considered
.	complete when all the decimal digits have been entered.	 If the
.	value does not have decimal digits, then all the integer digits
.	must be	entered.
.
.    (EDITTEXT)
.	If the state is	ON, the	object automatically tabs to the next
.	object in the tab sequence when	the following conditions occur:
.
.	    1. The EDITTEXT object is a	single line edit object.
.	    2. The EDITTEXT MAXCHARS property is set to	a non-zero value.
.	    3. The user	keys the last character	in the edit field as
.	       determined from the MAXCHARS property.
.
.	    Note:
.		1. The autoenter action	does not occur if data is keyed
.		   at a	caret position other than the last position
.		   of the edit field as	determined by the MAXCHARS
.		   property value.
.
.		2. The autoenter action	does not occur if the user sets
.		   the caret to	a full edit field, as determined by the
.		   MAXCHARS property, and re-enters data in an OVERTYPE
.		   mode.
.
. Objects:
.	EDITNUMBER
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU 	1
.
*------------------------------------------------------------------------------
.   AUTOSCALE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	how a picture should be	scaled to fit
.	PICT object rectangle coordinates. This	property is overridden
.	by the RESIZE property.
.
. Objects:
.	PICT
.
. dnumnvar values:
.
$SCALEBEST    EQU	1		// Default
$SCALEHORZ    EQU	2
$SCALENONE    EQU	3		// Same	as RESIZE=$OFF
$SCALEVERT    EQU	4
$SCALEFULL    EQU       5						  9.4C
$SCALEMANUAL  EQU       6						  9.4C
.
*------------------------------------------------------------------------------
.   AUTOSCROLL=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property provides automatic scrollbar handling for	a
.	window.	This property is used in conjunction with the MINSCROLLH,
.	MINSCROLLV, and	SCROLLBAR properties of	a WINDOW object.
.
.	If a window object is sized less than either the MINSCROLLH,
.	or MINSCROLLV properties, a scrollbar is shown and scrolling
.	is automatically handled.
.
.	Additionally, when autoscrolling is on,	the client area	of the
.	window object automatically scrolls to make the	control	with
.	input focus visible.
.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   AUTOSIZE[=dnumnvar]	(CHECKGRP/RADIOGRP)	CREATE	SETPROP	GETPROP
.   AUTOSIZE=dnumnvar	(STATUSPANEL)			SETPROP	GETPROP	  8.6D
.   AUTOSIZE=dnumnvar	(TOOLBUTTON)			SETPROP	GETPROP	  8.6D
.
. Description:
.
.    (CHECKGRP or RADIOGRP)
.	This property defines if the bottom border is to be adjusted
.	automatically to fit the number	of items specified.  If	the
.	AUTOSIZE property is not specified the default action is to
.	not resize the bottom border.  If the AUTOSIZE property	is
.	specified without an assignment, the action is the same	as
.	if AUTOSIZE=1 where given.
.
.     (STATUSPANEL)
.	This property allows the user to specify the type of sizing
.	to be used for the STATUSPANEL object.	The possible size types
.	are as follows:
.
.	PanSizeContents	- Size the panel to the	contents. Do not
.			  get smaller than the MINWIDTH	property.
.	PanSizeNone	- Size the panel using the WIDTH property.
.	PanSizeSpring	- Size the panel to use	up any remaining
.			  space	left after all other panels are
.			  displayed. Do	not get	smaller	than the
.			  MINWIDTH property.
.
.     (TOOLBUTTON)
.	This property specifies	that the TOOLBAR object	should not assign
.	the standard width to the TOOLBUTTON. Instead, the TOOLBUTTON's	width
.	will be	calculated based on the	width of the text plus the image
.	of the TOOLBUTTON.
.
. Objects:
.	CHECKGRP
.	RADIOGRP
.	STATUSPANEL
.	TOOLBUTTON
.
. dnumnvar values:
.
.(CHECKGRP, RADIOGRP, or TOOLBUTTON)
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
.(STATUSPANEL)
$PANSIZECONTENTS	EQU	1
$PANSIZENONE		EQU	2
$PANSIZESPRING		EQU	3
.
*------------------------------------------------------------------------------
.   AUTOVERB=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property enables or disables the automatic	context	menu for
.	an OLE insertable object. It contains any verbs	that the OLE
.	insertable object provides.
.
. Objects:
.	CONTAINER
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   AUTOWORDSEL=dnumnvar			CREATE	SETPROP	GETPROP	  9.0B
.
. Description:
.	This property is used to set or	get the	state of automatic word	selecti
.
.	If the state is	ON, then selecting any part of the text	in
.	the object results in the selection of the entire word.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   AUTOZOOM[=dnumnvar]				CREATE	SETPROP	GETPROP
.
. Description:
.	This property enables or disables the zooming capability for
.	a PICT object.
.
. Objects:
.	PICT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   BACKSTYLE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property defines the type of background to	be used	for
.	supported objects.  The	BACKSTYLE can be OPAQUE, which prevents
.	underlying objects from	showing	through	this object.  The
.	BACKSTYLE can also be TRANSPARENT which	allows underlying
.	objects	to show	through	the supported objects.
.
. Objects:
.	ANIMATE								  9.0
.	CONTAINER
.	GROUPBOX
.	PICT		PWS runtime
.	PICT		PNG image only using PLBWIN, PLBNET, or PLBCLIENT
.	SHAPE
.	STATTEXT
.	TOOLBAR
.
. dnumnvar values:
.
.$NONE	      EQU	0	       // Default
$OPAQUE	      EQU	1
$TRANSPARENT  EQU	2
.
*------------------------------------------------------------------------------
.   BDRCOLOR=dnumnvar|color object		CREATE	SETPROP	GETPROP
.
. Description:
.	This property allows the color of the BORDER to	be specified by
.	the user program.  If the BDRCOLOR parameter is	a <color object>,
.	then the <color	object>	must be	created	before it is used.  The
.	<dnumnvar> value can also be used to specify the color as a
.	RGB value or a Windows system color index.  The	<dnumnvar> value
.	can be thought of as 4 byte values.  When the high order byte
.	contains a value of 0x00, then the next	3 bytes	(24 bits) get
.	interpreted as a RGB value.  When the high order byte has a value
.	of 0x80, then the lower	order byte is used as an index value into
.	the Windows System colors.  The	Windows	system colors can be
.	defined	by the user under Windows 95 and Windows NT.
.
.	Index		Value		Meaning
.
.	COLOR_ACTIVEBORDER		Active window border.
.	COLOR_ACTIVECAPTION		Active window caption.
.	COLOR_APPWORKSPACE		Background color of multiple
.					document interface (MDI) applications.
.	COLOR_BACKGROUND		Desktop.
.	COLOR_BTNFACE			Face shading on	push buttons.
.	COLOR_BTNSHADOW			Edge shading on	push buttons.
.	COLOR_BTNTEXT			Text on	push buttons.
.	COLOR_CAPTIONTEXT		Text in	caption, size box,
.					and scroll bar arrow box.
.	COLOR_GRAYTEXT			Grayed (disabled) text.
.					This color is set to 0 if the
.					current	display	driver does not
.					support	a solid	gray color.
.	COLOR_HIGHLIGHT			Item(s)	selected in a control.
.	COLOR_HIGHLIGHTTEXT		Text of	item(s)	selected in a control.
.	COLOR_INACTIVEBORDER		Inactive window	border.
.	COLOR_INACTIVECAPTION		Inactive window	caption.
.	COLOR_INACTIVECAPTIONTEXT	Color of text in an inactive
.					    caption.
.	COLOR_MENU			Menu background.
.	COLOR_MENUTEXT			Text in	menus.
.	COLOR_SCROLLBAR			Scroll bar gray	area.
.	COLOR_SHADOW			Color of automatic window shadows.
.	COLOR_WINDOW			Window background.
.	COLOR_WINDOWFRAME		Window frame.
.	COLOR_WINDOWTEXT		Text in	windows.
.
.       CONTEXT_xxx                     Bootstrap 5 Context colors.
.
.
. Objects:
.	CHECKGRP
.	CONTAINER
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	GROUPBOX
.	LINE
.	MOVIE
.	PICT
.	PROGRESS
.	RADIOGRP
.	SHAPE
.	STATTEXT
.
. dnumnvar values:
.
$SCROLLBAR	      CONST   "2147483648"    ;Hex value 0x80000000
$BACKGROUND	      CONST   "2147483649"    ;Hex value 0x80000001
$ACTIVECAPTION	      CONST   "2147483650"    ;Hex value 0x80000002
$INACTIVECAPTION      CONST   "2147483651"    ;Hex value 0x80000003
$MENU		      CONST   "2147483652"    ;Hex value 0x80000004
$WINDOW		      CONST   "2147483653"    ;Hex value 0x80000005
$WINDOWFRAME	      CONST   "2147483654"    ;Hex value 0x80000006
$MENUTEXT	      CONST   "2147483655"    ;Hex value 0x80000007
$WINDOWTEXT	      CONST   "2147483656"    ;Hex value 0x80000008
$CAPTIONTEXT	      CONST   "2147483657"    ;Hex value 0x80000009
$ACTIVEBORDER	      CONST   "2147483658"    ;Hex value 0x8000000A
$INACTIVEBORDER	      CONST   "2147483659"    ;Hex value 0x8000000B
$APPWORKSPACE	      CONST   "2147483660"    ;Hex value 0x8000000C
$HIGHLIGHT	      CONST   "2147483661"    ;Hex value 0x8000000D
$HIGHLIGHTTEXT	      CONST   "2147483662"    ;Hex value 0x8000000E
$BTNFACE	      CONST   "2147483663"    ;Hex value 0x8000000F
$BTNSHADOW	      CONST   "2147483664"    ;Hex value 0x80000010
$GRAYTEXT	      CONST   "2147483665"    ;Hex value 0x80000011
$BTNTEXT	      CONST   "2147483666"    ;Hex value 0x80000012
$INACTIVECAPTIONTEXT  CONST   "2147483667"    ;Hex value 0x80000013
$BTNHIGHLIGHT	      CONST   "2147483668"    ;Hex value 0x80000014
.
$CONTEXT_DEFAULT      CONST   "2147483904"    ;Hex value 0x80000100
$CONTEXT_DANGER	      CONST   "2147483905"    ;Hex value 0x80000101
$CONTEXT_DARK         CONST   "2147483906"    ;Hex value 0x80000102
$CONTEXT_INFO         CONST   "2147483907"    ;Hex value 0x80000103
$CONTEXT_LIGHT        CONST   "2147483908"    ;Hex value 0x80000104
$CONTEXT_PRIMARY      CONST   "2147483909"    ;Hex value 0x80000105
$CONTEXT_SECONDARY    CONST   "2147483910"    ;Hex value 0x80000106
$CONTEXT_SUCCESS      CONST   "2147483911"    ;Hex value 0x80000107
$CONTEXT_WARNING      CONST   "2147483912"    ;Hex value 0x80000108
.
*------------------------------------------------------------------------------
.   BDRPATTERN=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property allows the user to specify the type of border
.	pattern	is to be used for the object.  The possible border
.	patterns are as	follows:
.
.	Dash		- Pen is dashed.
.	DashDot		- Pen has alternating dashes and dots.
.	DashDot2	- Pen has dashes and double dots.
.	Dot		- Pen is dotted.
.	InsideFrame	- Pen is solid.	 The figure and	border is created
.			  inside the frame defined by the user specified
.			  rectangle.
.	Solid		- Pen is solid.
.	None		- Pen defaults to solid.
.
.	Note1: The border pattern only takes affect when the BDRWIDTH
.	       property	has a value of 1.
.
. Objects:
.	LINE
.	SHAPE
.
. dnumnvar values:
.
.$NONE	      EQU	0	       // Default
$DASH	      EQU	1
$DASHDOT      EQU	2
$DASHDOT2     EQU	3
$DOT	      EQU	4
$INSIDEFRAME  EQU	5
$SOLID	      EQU	6
.
*------------------------------------------------------------------------------
.   BDRSTYLE=dnumnvar (STATUSPANEL)			SETPROP	GETPROP	  8.6D
.   BDRSTYLE=dnumnvar (TOOLBAR)			CREATE	SETPROP	GETPROP	  8.6D
.   BDRSTYLE=dnumnvar (PANEL)			CREATE	SETPROP	GETPROP	  8.7A
.   BDRSTYLE=dnumnvar (SPLITTER)		CREATE	SETPROP	GETPROP	  8.7A
.   BDRSTYLE=dnumnvar (RICHEDITTEXT)		CREATE	SETPROP	GETPROP	  9.0B
.
. Description:
.
.     (STATUSPANEL)
.	This property allows the user to specify the type of border
.	display	around a STATUSPANEL object.  The possible border styles
.	are as follows:
.
.	     PanBdrNone	     - No border.
.	     PanBdrRaised    - Raised border.
.	     PanBdrSunken    - Sunken border.
.
.     (TOOLBAR,	PANEL, RICHEDITTEXT, or	SPLITTER)
.	This property allows the user to specify the type of border
.	to be used for the object.  The	possible border	styles
.	are as follows:
.
.	     NoBorder	     - No border is used.
.	     FixedSingle     - Single line border.
.	     Fixed3D	     - Border with a 3D	look.
.
. Objects:
.	PANEL
.	RICHEDITTEXT							  9.0B
.	SPLITTER
.	STATUSPANEL
.	TOOLBAR
.
. dnumnvar values:
.
.(STATUSPANEL)
$PANBDRNONE		EQU	1
$PANBDRRAISED		EQU	2
$PANBDRSUNKEN		EQU	3
.
.(TOOLBAR)
.$NONE		EQU	0
.$NOBORDER	EQU	1
.$FIXEDSINGLE	EQU	2
.$FIXED3D	EQU	3
.
*------------------------------------------------------------------------------
.   BDRWIDTH=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property defines the width	of the pen used	to draw	the
.	object.
.
.	Note1: The border pattern only takes affect when the BDRWIDTH
.	       property	has a value of 1.
.
. Objects:
.	LINE
.	SHAPE
.
. dnumnvar values:
.
.	The <dnumnvar> value specifies number of pixels	for width.
.
*------------------------------------------------------------------------------
.   BGCOLOR=dnumnvar|color object		CREATE	SETPROP	GETPROP
.
. Description:
.	This property allows the user program to specify the color to
.	be used	for the	background color.  The parameter description
.	is the same as for the BDRCOLOR	property.
.
. Objects:
.	ANIMATE								  9.0
.	CHECKBOX
.	CHECKGRP
.	CONTAINER
.	COMBOBOX
.	DATALIST
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	GROUPBOX
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	IMAGELIST
.	LABELTEXT							  9.0
.	LISTVIEW
.	PICT
.	POPUPMENU ( OBSOLETE )
.	PROGRESS
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	STATTEXT
.	STATUSBAR
.	VSCROLLBAR
.	WINDOW
.
. dnumnvar values:
.
.	See the	BDRCOLOR property for the color	equate values.
.
*------------------------------------------------------------------------------
.   BOLD[=dnumnvar]				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	that the font should be	bolded.	 When
.	the <dnumnvar> value is	not provided, this indicates that the
.	BOLD is	turned on.
.
. Objects:
.	FONT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   BORDER[=dnumnvar]				CREATE	SETPROP	GETPROP
.
. Description:
.	This property defines when an object is	to have	a border.
.	If the <dnumnvar> parameter is not provided, this indicates that
.	the border is to be used.
.
. Objects:
.	ANIMATE								  9.0
.	CHECKGRP
.	CONTAINER
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	LABELTEXT							  9.0
.	LISTVIEW
.	MOVIE
.	PICT
.	RADIOGRP
.	SLIDER
.	STATTEXT
.	TREEVIEW
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   BTNHEIGHT=dnumnvar				CREATE	SETPROP	GETPROP	  8.6D
.
. Description:
.	This property specifies	the height in pixels of	any TOOLBUTTON
.	object that has	the AUTOSIZE property set FALSE.
.
. Objects:
.	TOOLBAR
.
. dnumnvar values:
.
.     The <dnumnvar> value is specified	in pixels.
.
*------------------------------------------------------------------------------
.   BTNSTYLE=dnumnvar					SETPROP	GETPROP	  8.6D
.
. Description:
.	This property allows the user to specify the type of button
.	to be used for the object.  The	possible button	styles
.	are as follows:
.
.	TbSyleDropDown	- Creates a drop-down style button that	can
.			  display a list when the button is clicked.
.			  When the button is clicked a pop menu	will be
.			  shown	and the	$BUTTONCLICK Event Modifier
.			  will contain a one-based menu	selection value.
.
.			  If the TOOLBAR has the DOWNARROW property set,
.			  drop-down buttons will have a	drop-down arrow
.			  displayed in a separate section to their right.
.			  If the arrow is clicked, a pop menu will be
.			  shown	and the	$BUTTONCLICK Event Modifier
.			  will contain a one-based menu	selection value.
.			  If the associated button is clicked, a
.			  $BUTTONCLICK event will be created with a
.			  Event	Modifier value of 0.
.
.	TbSyleDropDownW	- Version 5.80.	Specifies that the button will have
.			  a drop-down arrow, but not as	a separate section.
.			  Buttons with this style behave the same, regardless
.			  of whether the DOWNARROW property is set for the
.			  TOOLBAR object.
.
.	TbSylePush	- Standard push	button.
.
.	TbSyleSep	- Creates a separator, providing a small gap
.			  between button groups. A button that has this
.			  style	does not receive user input.
.
.	TbStyleToggle	- Creates a dual-state push button that	toggles
.			  between the pressed and non-pressed states each
.			  time the user	clicks it. The button has a different
.			  background color when	it is in the pressed state.
.
.	TbStyleToggleGrp - Creates a button that stays pressed until another
.			   button in the group is pressed, similar to option
.			   buttons (also known as radio	buttons).
.
. Objects:
.	TOOLBUTTON
.
. dnumnvar values:
.
$TBSTYLEDROPDOWN	EQU	1
$TBSTYLEDROPDOWNW	EQU	2
$TBSTYLEPUSH		EQU	3
$TBSTYLESEP		EQU	4
$TBSTYLETOGGLE		EQU	5
$TBSTYLETOGGLEGRP	EQU	6
.
*------------------------------------------------------------------------------
.   BTNWIDTH=dnumnvar				CREATE	SETPROP	GETPROP	  8.6D
.
. Description:
.	This property specifies	the width in pixels of any TOOLBUTTON
.	object that has	the AUTOSIZE property set FALSE.
.
. Objects:
.	TOOLBAR
.
. dnumnvar values:
.
.     The <dnumnvar> value is specified	in pixels.
.
*------------------------------------------------------------------------------
.   BULLETINDENT=dnumnvar			CREATE	SETPROP	GETPROP	  9.0B
.
. Description:
.	This property specifies	the indentation	of any text
.	that has the bullet style set. The SELBULLET property is used
.	to set the bullet style.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.     The <dnumnvar> value is specified	in pixels.
.
*------------------------------------------------------------------------------
.   BUTTONENTRYKEY=dnumnvar			CREATE	SETPROP	GETPROP	  9.0E
.
. Description:
.	When this property is set to a value of	1, then	a Click	event is
.	generated when an Entry	key is keyed when a BUTTON object currently
.	has the	focus. When this property is set to a value of 0 (default),
.	then a Click event is only gnerated when an Entry key is keyed for a
.	BUTTON object if a DEFAULT property has	been set for one of the	
.	BUTTON objects currently on the	current	Window.	Otherwise, the
.	Enter key for a	BUTTON object does not generate	a Click	event.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   BUTTONS=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property causes plus (+) and minus	(-) button boxes to appear
.	next to	a parent's list	of child items when the	TREELNSTYLE is set
.	for $LINESATROOT.  When	the +/-	box is present , then clicking this
.	box will open or close the selected parent list.
.
. Objects:
.	TREEVIEW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   BUTTONSTATE=dnumnvar			CREATE	SETPROP	GETPROP   10.5
.
. Description:
.       The BUTTONSTATE property is only used when a BUTTON object has
.       been created as a web object using the WebView mode. This property
.       uses a combination of Bootstrap 5 'Contextual classes' and button
.       state types to invoke a variety of appearances for a web button
.       object.
.
. Objects:
.	BUTTON (WebView Only)
.
. dnumnvar values:
.
$BTNSTATE_DEFAULT   EQU 0       //default. 
$BTNSTATE_OUTLINE   EQU 1       //button outline.
$BTNSTATE_SPIN      EQU 2       //button spinner.
$BTNSTATE_SPINGROW  EQU 3       //button grow spinner.
.
*------------------------------------------------------------------------------
.   BUTTONTYPE=dnumnvar                         CREATE          GETPROP   9.6
.
. Description: (Comctl32 Version 6 Required)
.       This property allows the button extended type to be applied to
.       provide a split button or a command link presentation.
.
. Objects:
.	BUTTON
.
. dnumnvar values:
.
$SplitBUtton  EQU	1
$CommandLink  EQU	2
$FileInput    EQU       3    //PL/B Web Server ONLY!                      9.7A
.
*------------------------------------------------------------------------------
.   CALBGCOLOR=dnumnvar|color object		CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property allows the user program to specify the color to
.	be used	in the drop down calendar as the background color
.	displayed within the month. The	parameter description is the same
.	as for the BDRCOLOR property.
.
. Objects:
.	EDITDATETIME
.
. dnumnvar values:
.
.	See the	BDRCOLOR property for the color	equate values.
.
*------------------------------------------------------------------------------
.   CALFGCOLOR=dnumnvar|color object		CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property allows the user program to specify the color to
.	be used	in the drop down calendar to display text within a month.  
.	The parameter description is the same as for the BDRCOLOR property.
.
. Objects:
.	EDITDATETIME
.
. dnumnvar values:
.
.	See the	BDRCOLOR property for the color	equate values.
.
*------------------------------------------------------------------------------
.   CANCEL[=dnumnvar]				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	that the BUTTON	object activation routine
.	is to gain program control when	the escape key is entered.
.
. Objects:
.	BUTTON
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   CAPTION=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property allows a user to specify if a Window is to be
.	created	with or	without	a title	bar.  This property is
.	provided to the	OS to eliminate/retain the caption bar as
.	appropriate.
.
.	NOTE1: Under Windows95 and Win32s, the CAPTION property	will
.	       have an effect on a MODAL or MODELESS window.  The
.	       CAPTION property	does not have an affect	on the PRIMARY
.	       window types.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1	       // Default
.
*------------------------------------------------------------------------------
.   CAUSEVALID=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	that moving focus to the object	will trigger
.	the VALIDATE evenvt for	the previously selected	object.
.
. Objects:
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	HSCROLLBAR
.	LABELTEXT							  9.0
.	LISTVIEW
.	POPUPMENU
.	RADIO
.	RADIOGRP
.	RICHEDITTEXT							  9.0B
.	SLIDER
.	STATTEXT
.	STATUSBAR
.	TABCONTROL
.	TOOLBAR
.	TREEVIEW
.	VSCROLLBAR
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // not enabled
.$ON	      EQU	1	       // enabled (Default)
.
*------------------------------------------------------------------------------
.   CENTER[=dnumnvar]				CREATE
.
. Description:
.
.     EDITTEXT and STATTEXT (Description)
.
.	The CENTER property specifies that the text is to be centered
.	horizontally for the object.  The property is replaced with
.	the ALIGNMENT property.	 The ALIGNMENT property	is to be used
.	for performing SETPROP and GETPROP operations.
.
.	If the syntax form is used where the <dnumnvar>	value is not
.	specified, this	indicates that the CENTER property is to be
.	turned on.
.
.	Also note that if the CENTER property is turned	off, this causes
.	the text output	to be justified	to the left.
.
.     ANIMATE (Description)						  9.0
.
.	The CENTER property specifies that the animation is to be centered
.	horizontally in	the object.
.
.	If the syntax form is used where the <dnumnvar>	value is not
.	specified, this	indicates that the CENTER property is to be
.	turned on.
.
.	Also note that if the CENTER property is turned	off, this causes
.	the animation to be shown in the top-left.
.
. Objects:
.	ANIMATE								  9.0
.	EDITTEXT
.	STATTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   CENTERPOS=dnumnvar				CREATE
.
. Description:
.	When the user defined rectangle	is larger than the EDITTEXT
.	object,	this property controls whether the EDITTEXT object is to
.	be centered TOP/BOTTOM or not.	The default action is to
.	have the EDITTEXT object centered TOP/BOTTOM within the	user
.	defined	rectangle parameters.  If the CENTERPOS	property is
.	set to $TOPLEFTPOS, then the CREATE action is to have the
.	EDITTEXT object	rectangle be located at	the TOP/LEFT coordinates.
.
. Objects:
.	EDITTEXT
.
. dnumnvar values:
.
$CENTERPOS    EQU	0	       // Default
$TOPLEFTPOS   EQU	1
.
*------------------------------------------------------------------------------
.   CHECKBOX=dnumnvar				  See Objects:
.
. Description:
.	When this property is set to $ON, it enables check boxes for
.	items in a TREEVIEW/LISTVIEW object. The object	creates	and sets a
.	state image list with two images. State	image 1	is the unchecked
.	box, and state image 2 is the checked box. Setting the state image
.	to zero	removes	the check box altogether. The GetItemCheck and
.	SetItemCheck methods can be used when this property is set for
.	either a TREEVIEW or LISTVIEW.	The FindItemCheck can be used
.	for a LISTVIEW object.
.
.	Note:
.
.	  1. This property will	not take affect	unless a Microsoft file
.	     version of	4.70 or	later of 'comctl32.dll'	is installed on
.	     a given workstation.
.
.	  2. This property will	only affect the	operation of the LISTVIEW
.	     object when the VIEWSTYLE property	is set to $VIEWREPORT style.
.
.	  3. The CHECKBOX property can only be used for	CREATE and GETPROP
.	     in	a TREEVIEW object. The CHECKBOX property can be used for
.	     CREATE, SETPROP, and GETPROP when using a PWS TREEVIEW object.
.
. Objects:
.       DATATABLE                               CREATE	SETPROP	GETPROP  10.5
.	LISTVIEW				CREATE	SETPROP	GETPROP
.	TREEVIEW (Windows)			CREATE		GETPROP
.	TREEVIEW (PL/B Web Server)		CREATE  SETPROP GETPROP   9.9
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.  CHECKED=dnumnvar (EDITDATETIME)		CREATE	SETPROP	GETPROP	  9.0
.  CHECKED=dnumnvar (MENUITEM)				SETPROP	GETPROP	  9.0
.  CHECKED=dnumnvar (DATAROW)				SETPROP	GETPROP	 10.5
.
. Description:
.	If the object is an EDITDATETIME object, this property is used to set
.	or get the status of a checkbox	displayed in the EDITDATETIME object.
.	A checkbox is displayed	when the SHOWCHECKBOX property is set to $ON.
.
.	If the property	is set to $OFF,	no check mark is shown in the checkbox
.	and the	EDITDATETIME object allows no data entry.
.
.	If the property	is set to $ON, a check mark is shown in	the checkbox
.	and the	EDITDATETIME object allows data	entry.
.
.	If the object is a MENUITEM object, this property sets or clears a
.	check mark beside the menu item.
.
.	If the object is a DATAROW object, this property sets or clears a
.	checkbox at the start of a row.
.
. Objects:
.       DATAROW                                                          10.5
.	EDITDATETIME
.	MENUITEM							  9.0
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   CLASS=svarslit				CREATE	SETPROP	GETPROP
.   CLASSID=svarslit				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is the associated	text name for the CLSID	for the
.	OLE insertable object. If set, the current OLE insertable object in a
.	OLE container object will be replaced by a new OLE insertable object
.	created	using the given	text name.
.
. Objects:
.	AUTOMATION
.	CONTAINER
.	CONTROL
.
. svarslit values:
.
.	The <svarslit> is a text programmatic identifier associated with a
.	CLSID.	If the <svarslit> is a single '?' character, then an OLE
.	Insertable Object Dialog is presented so that a	user can select
.	the OLE	object to be used.
.
*------------------------------------------------------------------------------
.   CLIPCTRL=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	Excludes the area occupied by child windows/objects when
.	drawing	within the parent window.  If the property is turned
.	on, this can slow the performance of drawing objects due to
.	OS overhead in determining valid clipping regions.
.
. Objects:
.	PANEL
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   CLIPSIB=dnumnvar                            CREATE  SETPROP GETPROP   8.2M
.
. Description:
.       This property controls whether an object can be displayed on
.       top of the EDITTEXT, EDITNUMBER, or RICHEDITTEXT objects. 
.
. Objects:
.	EDITTEXT
.	EDITNUMBER
.       RICHEDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   CMDNOTE=dnumnvar                            CREATE SETPROP GETPROP    9.6
.
. Description: (Comctl32 Version 6 Required)
.       This property specifies a text note that is associated with a button
.       object when the BUTTONTYPE property is set to be a command link.
.
. Objects:
.	BUTTON
.
*------------------------------------------------------------------------------
.   CODEPAGE=dnumnvar                           CREATE SETPROP GETPROP    10.0A
.
. Description:
.       This property is used to control all interactions with the HTMLCONTROL
.       object. This includes data for the InnerHtml property and method,
.       the GetAttr method, and the SetAttr method.
.
.       Note:
.          All data to\from the HTMLCONTROL object must be UTF-8 encoded. 
.
. Objects:
.	HTMLCONTROL
.
. dnumnvar values:
.
.$NONE	      EQU	0	// No data conversion
$UTF8	      EQU	1	// Default convert to UTF-8
.400 - 65536			// Windows ONLY codepage to UTF-8
.
*------------------------------------------------------------------------------
.  COLUMNID=svarslit				CREATE	SETPROP	 GETPROP  10.5
.
. Description:
.       This property sets or clears a name identifier for a column. 
.	
. Objects:
.       DATACOLUMN
.
. svarslit values:
.
.	The <svarslit> variable	is a text string. It should not contain spaces.
.
*------------------------------------------------------------------------------
.   COLUMNWIDTH=dnumnvar			CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used to set or	get column width of a multicolumn
.	DATALIST object.
.
. Objects:
.	DATALIST
.
*------------------------------------------------------------------------------
.   COMBOSTYLE=dnumnvar				CREATE		GETPROP
.
. Description:
.	The COMBOSTYLE property	specifies the type of COMBOBOX window
.	object to be generated.	 A default combobox list object	is a
.	combobox with a	drop down list where the combobox does not have
.	an editable capability.	 The $EDIT <dnumnvar> value
.	defines	a combobox list	like the default except	the combobox
.	does allow editing capability.	Only the current selection field
.	can be edited.	The $SIMPLE <dnumnvar> value is	the
.	same as	the $EDIT except the list is always present.
.
. Objects:
.	COMBOBOX
.	POPUPMENU ( OBSOLETE )
.
. dnumnvar values:
.
.$NONE	      EQU	0	       // Same as $LIST
$EDIT	      EQU	1
$LIST	      EQU	2	       // Default
$SIMPLE	      EQU	3
.
*------------------------------------------------------------------------------
.  COMPUTE=svarslit				CREATE	SETPROP	 GETPROP  10.5
.
. Description:
.       This property sets the default value of a column when a
.       'AddRow' method does not specify input data to be used.
.	
. Objects:
.       DATACOLUMN
.
. svarslit values:
.
.	The <svarslit> variable	must contain a valid compute string
.       as shown below:
.
.	DEFAULT(<str>)
.	CURDATE
.	CURTIME
.	CURDATETIME
.	IDENTIFY
.	TODAY
.
.
*------------------------------------------------------------------------------
.   CONTENTTYPE=dnumnvar		       CREATE	SETPROP	GETPROP   10.5
.
. Description:
.       The CONTENTTYPE property specifies the type of content that 
.       the column contains.
.
. Objects:
.       DATACOLUMN
.
. dnumnvar values:
.
$TC_DEFAULT	EQU		0	// Default 
$TC_HIDDEN	EQU		1	// Hidden 
$TC_EDITABLE	EQU		2	// Listview mode - can be editted 
$TC_TITLE	EQU		3	// Card mode - Title 
$TC_DETAILS	EQU		4	// Card mode - Details 
$TC_IMAGE	EQU		5	// Card mode - Image 
$TC_HEADER	EQU		6	// Card mode - Header 
$TC_FOOTER	EQU		7	// Card mode - Footer 
$TC_BUTTON1	EQU		8	// Card mode - Button 
$TC_BUTTON2	EQU		9	// Card mode - Button 
$TC_BUTTON3	EQU		10	// Card mode - Button 
$TC_START	EQU		11	// Start time 
$TC_END		EQU		12	// End time 
$TC_GPS		EQU		13	// GPS Address 
.
*------------------------------------------------------------------------------
.   CONTEXT=dnumnvar				CREATE	SETPROP	GETPROP   10.5
.
. Description:
.       The CONTEXT property is only used when the object has been created
.       as a web object using the WebView mode. This property uses
.       Bootstrap 5 'Contextual classes' to invoke a style for
.       background and color attributes.
.
. Objects:
.	BUTTON (WebView Only)
.       DATACOLUMN
.       DATAROW
.       DATATABLE
.
. dnumnvar values:
.
$OC_DEFAULT	EQU		0	// Default 
$OC_DANGER	EQU		1
$OC_DARK	EQU		2
$OC_INFO        EQU		3
$OC_LIGHT       EQU		4
$OC_PRIMARY     EQU		5
$OC_SECONDARY	EQU		6
$OC_SUCCESS    	EQU		7
$OC_WARNING    	EQU		8
.
*------------------------------------------------------------------------------
.   COUNT=dnumnvar				CREATE	SETPROP	GETPROP   10.8
.
. Description:
.       The COUNT property is used to get the current number of active
.       data items in a DATASET object.
.
. Objects:
.       DATASET
.
. dnumnvar values:
.
*------------------------------------------------------------------------------
.   CUETEXT=svarslit                            CREATE SETPROP  GETPROP   9.6
.
. Description: (Comctl32 Version 6 Required)
.       The CUETEXT property sets the cue banner text that is displayed
.       for an edit control of a COMBOBOX object. The cue banner is
.       displayed when the COMBOBOX has no selection.
.       
.       The CUETEXT property sets the cue banner text that is displayed
.       for an EDITTEXT object. The cue banner is displayed when the
.       EDITTEXT is empty. The CUETEXT property is only displayed by
.       the Windows OS for a single line EDITTEXT control.
.
. Objects:
.       COMBOBOX
.       EDITTEXT
.
*------------------------------------------------------------------------------
.   CUSTOMFORMAT=svarslit			CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property sets or gets the custom format string used when the
.	FORMAT property	is set to $DTFORMATCUSTOM.
.	
.	The format string consists of a	series of elements that	represent a 
.	particular piece of information	and define its display format. The 
.	elements will be displayed in the order	they appear in the format
.	string.
.
.	Date and time format elements will be replaced by the actual date and
.	time. They are defined by the following	groups of characters:
.
.	Element	Description
.
.	"d"	The one- or two-digit day.
.	"dd"	The two-digit day. Single-digit	day values are preceded	by a
.		zero.
.	"ddd"	The three-character weekday abbreviation.
.	"dddd"	The full weekday name.
.	"h"	The one- or two-digit hour in 12-hour format.
.	"hh"	The two-digit hour in 12-hour format. Single-digit values are
.		preceded by a zero.
.	"H"	The one- or two-digit hour in 24-hour format.
.	"HH"	The two-digit hour in 24-hour format. Single-digit values are
.		preceded by a zero.
.	"m"	The one- or two-digit minute.
.	"mm"	The two-digit minute. Single-digit values are preceded by a
.		zero.
.	"M"	The one- or two-digit month number.
.	"MM"	The two-digit month number. Single-digit values	are preceded
.		by a zero.
.	"MMM"	The three-character month abbreviation.
.	"MMMM"	The full month name.
.	"t"	The one-letter AM/PM abbreviation (that	is, AM is displayed as
.		"A").
.	"tt"	The two-letter AM/PM abbreviation (that	is, AM is displayed as
.		"AM").
.	"yy"	The last two digits of the year	(that is, 1996 would be
.		displayed as "96").
.	"yyyy"	The full year (that is,	1996 would be displayed	as "1996").
.
.	To make	the information	more readable, you can add body	text to	the for
.	string by enclosing it in single quotes. Spaces	and punctuation	marks d
.	need to	be quoted.
.
. Objects:
.	EDITDATETIME
.
. svarslit values:
.
.	The <svarslit> variable	is a format string.
.
*------------------------------------------------------------------------------
.   DATAFILTER=svarslit				CREATE	SETPROP	GETPROP   10.8
.
. Description:
.       The DATAFILTER property allows a filter string to be set for a
.       DATASET object. If the filter string, it is used when DATASET
.       items are being accessed in the GetItem and FindItem methods.
.       By default, this property is not set. The DATASET filtering is
.       only used for data items that contain valid JSON data.
.
. Objects:
.       DATASET
.
. svarslit value:
.
.	String that contains a valid filter expression.
.	See FILTER instruction.
.
*------------------------------------------------------------------------------
.   DATA=svarslit				CREATE	SETPROP	GETPROP
.
. Description:
.	This property allows the items in a DATALIST to	be initialized using
.	a string composed of a list of items with each item separated with
.	semi-colon.
.
. Objects:
.	DATALIST
.
. svarslit value:
.
.	String of semicolon separated list items.
.
*------------------------------------------------------------------------------
.   DATATYPE=dnumnvar				CREATE	SETPROP	GETPROP   10.5
.
. Description:
. 
.      DATACOLUMN
.       The DATATYPE property specifies the type of data contained in  
.       a column.
.
.      DATASET 
.       The DATATYPE property is a type assigned to the DATASET items.
.
. Objects:
.       DATACOLUMN
.       DATASET								  10.8
.
. dnumnvar values: ( DATACOLUMN )
.
$CDT_NONE    	EQU		0
$CDT_BOOL    	EQU		1		// Boolean	- <input type="checkbox"> 
$CDT_BUTTON    	EQU		2		// Button	- <input type="button"> 
$CDT_COLOR    	EQU		3		// Color	- <input type="color"> 
$CDT_CHAR    	EQU		4		// Character	- <input type="text"> 	
$CDT_DATE    	EQU		5		// Date		- <input type="date"> 
$CDT_DATETM    	EQU		6		// DateTime	- <input type="datetime-local">
$CDT_DECIMAL    EQU		7		// Decimal	- <input type="number"> size/scale 
$CDT_EMAIL    	EQU		8		// EMail	- <input type="email"> 
$CDT_IMAGE    	EQU		9		// Image	- <input type="image"> 
$CDT_MONTH    	EQU		10		// Month	- <input type="month"> 
$CDT_PASSWORD   EQU		11		// Password	- <input type="password"> 
$CDT_SEARCH    	EQU		12		// Search	- <input type="search"> 
$CDT_TELEPHONE  EQU		13		// Telephone	- <input type="tel"> 
$CDT_TIME    	EQU		14		// Time		- <input type="time"> 
$CDT_URL    	EQU		15		// URL		- <input type="url"> 
$CDT_WEEK    	EQU		16		// Week		- <input type="week"> 
.
.
. dnumnvar values: ( DATASET )						  10.8
.
$DST_DEFAULT   	EQU		0		// Mixed data types: text,
.						   JSON, binary, ...
$DST_MIXED	EQU		0		// Mixed same as default
$DST_JSON    	EQU		1		// JSON only verified
.
*------------------------------------------------------------------------------
.   DECIMALDIGITS=dnumnvar			CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used to set or	get number of decimal digits allowed.
.
. Objects:
.	EDITNUMBER
.
*------------------------------------------------------------------------------
.   DEFAULT[=dnumnvar]	(BUTTON)		CREATE	SETPROP	GETPROP
.   DEFAULT[=dnumnvar]	(MENUITEM)			SETPROP	GETPROP	  9.0
.
. Description:
.	This property specifies	that the BUTTON	object activation routine
.	is to gain program control when	the enter key is entered and
.	a non-button object has	the focus.  However, if	a button object
.	other than the DEFAULT button object has the focus when	the enter
.	key is entered,	then the activation routine of the button object
.	with the focus gains the program control.
.
.	Note1:	The operation when a button object other than the DEFAULT
.		button object has the focus is different from prior releases
.		to release 8.1.
.
.	If the object is a MENUITEM object, this property specifies the	menu
.	item selected when a menu has been selected and	the enter key is
.	pressed.
.
. Objects:
.	BUTTON
.	MENUITEM							  9.0
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   DETECTURL=dnumnvar				CREATE	SETPROP	GETPROP	  9.0B
.
. Description:
.	This property is used to set or	get the	state of URL detection.
.
.	If the state is	ON, then any text entered into the object that is
.	determined by the RICHEDEDITTEXT to be a Uniform Resource Locator
.	is be formatted	as a link. If a	left mouse button is pressed while
.	over a link, the $LINK event will occur.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   DIGITS[=dnumnvar]				CREATE
.
. Description:
.	This property is a CREATE only property.
.	The property specifies that the	EDITTEXT object	is to only
.	allow numeric digits 0 through 9.  When	this property is set to
.	indicate off state, then this indicates	that all characters are
.	allowed.
.
.	Note1: Use of the property should be replaced through use of
.	       the EDITTYPE property.
.
. Objects:
.	EDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   DISPLAYTYPE=dnumnvar			CREATE	SETPROP	GETPROP
.
. Description:
.	This property is used to control how the OLE insertable	object is
.	drawn within an	OLE container object. It may be	one of:
.
.	$DISPTYPECONTENT - The content of a OLE	insertable object is shown.
.
.	$DISPTYPEICON	- The OLE insertable object is shown as	an icon.
.
. Objects:
.	CONTAINER
.
. dnumnvar values:
.
$DISPTYPECONTENT EQU	   1		// Default
$DISPTYPEICON	 EQU	   2
.
*------------------------------------------------------------------------------
.   DIVIDER=dnumnvar				CREATE	SETPROP	GETPROP	  8.6D
.
. Description:
.	This property indicates	whether	any a divider line should
.	be shown at the	top of a TOOLBAR object.
.
. Objects:
.	TOOLBAR
.
. dnumnvar values:
.
.$OFF	    EQU	      0
.$ON	    EQU	      1
.
*------------------------------------------------------------------------------
.  DIVISIONID=svarslit				CREATE         GETPROP	  9.7
.
. Description:
.       This property can be used in a CREATE or GETPROP for a WINDOW
.       object. This property is only applied when the WINDOW object is
.       created for a PL/B Web Server client. This property allows the
.       WINDOW object to be included in a specific client division with a
.       name identification. The division identification string is case
.       sensitivity. A division defines a named section in a HTML
.       document. A division is used together with the CSS to layout
.       a web page.
.
.       The expected use of this property is for PL/B users who have
.       advanced knowledge of Web Page development. This property allows
.       those users to direct the PL/B WINDOW to a specific HTML
.       division with a specific name.
.	
. Objects:
.       WINDOW
.
. svarslit values:
.
.	The <svarslit> variable	is a Web HTML division name.
.
*------------------------------------------------------------------------------
.   DOCK=dnumnvar				CREATE	SETPROP	GETPROP	  8.7A
.
. Description:
.	This property indicates	if a control should be docked to the edge of
.	the parent object. When	an object is docked to an edge of its parent,
.	it is always positioned	flush against the edge of any other docked
.	objects	that are lower in the z-order when the parent object is
.	resized.  The DOCK property may	be one of:
.
.	$DOCKBOTTOM	- The object's bottom edge is docked.
.	$DOCKLEFT	- The object's left edge is docked.
.	$DOCKNONE	- The object is	not docked.
.	$DOCKRIGHT	- The object's right edge is docked.
.	$DOCKTOP	- The object's top edge	is docked.
.	$DOCKFULL	- The object takes up the rest of docking space.
.
. Objects:
.	ANIMATE								  9.0
.	BUTTON
.	CHECKBOX
.	COMBOBOX
.	CONTROL
.	DATALIST
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	LABELTEXT							  9.0
.	LISTVIEW
.	PANEL
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SLIDER
.	SPLITTER
.	STATTEXT							  9.0F
.	STATUSBAR
.	TABCONTROL
.	TOOLBAR
.	TREEVIEW
.	VSCROLLBAR
.
. dnumnvar values:
.
$DOCKBOTTOM	EQU	1
$DOCKLEFT	EQU	2
$DOCKNONE	EQU	3
$DOCKRIGHT	EQU	4
$DOCKTOP	EQU	5
$DOCKFULL	EQU	6
.
$WINDOCKBOTTOM	EQU	1
$WINDOCKLEFT	EQU	2
$WINDOCKNONE	EQU	3
$WINDOCKRIGHT	EQU	4
$WINDOCKTOP	EQU	5
.
*------------------------------------------------------------------------------
.   DOCKPADB=dnumnvar				CREATE	SETPROP	GETPROP	  8.7A
.
. Description:
.	The DOCKPADB property identifies the padding between
.	the bottom of a	window and the first docked object.
.
. Objects:
.	PANEL
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	a pixel	value.
.
*------------------------------------------------------------------------------
.   DOCKPADL=dnumnvar				CREATE	SETPROP	GETPROP	  8.7A
.
. Description:
.	The DOCKPADB property identifies the padding between
.	the left of a window and the first docked object.
.
. Objects:
.	PANEL
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	a pixel	value.
.
*------------------------------------------------------------------------------
.   DOCKPADR=dnumnvar				CREATE	SETPROP	GETPROP	  8.7A
.
. Description:
.	The DOCKPADB property identifies the padding between
.	the right of a window and the first docked object.
.
. Objects:
.	PANEL
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	a pixel	value.
.
*------------------------------------------------------------------------------
.   DOCKPADT=dnumnvar				CREATE	SETPROP	GETPROP	  8.7A
.
. Description:
.	The DOCKPADB property identifies the padding between
.	the top	of a window and	the first docked object.
.
. Objects:
.	PANEL
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	a pixel	value.
.
*------------------------------------------------------------------------------
.   DOWNARROW=dnumnvar				CREATE	SETPROP	GETPROP	  8.6D
.
. Description:
.	This property indicates	whether	a down arrow should be displayed
.	beside any TOOLBUTTON object with a style of $TBSTYLEDROPDOWN.
.
. Objects:
.	TOOLBAR
.
. dnumnvar values:
.
.$OFF	    EQU	      0
.$ON	    EQU	      1
.
*------------------------------------------------------------------------------
.   DPI=dnumnvar				CREATE	SETPROP	GETPROP	  8.7D
.
. Description:
.	The DPI	(Decimal Point Implied)	property allows	data entry into	an
.	EDITNUMBER object that specifies a non-zero value for the
.	DECIMALDIGITS property without requiring the imput of a	decimal	
.	point.
.
. Objects:
.	EDITNUMBER
.
. dnumnvar values:
.
.$OFF	    EQU	      0
.$ON	    EQU	      1
.
*------------------------------------------------------------------------------
.   DRAWMODE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the current foreground mix mode.
.	The foreground mix mode	defines	how colors from	the object
.	and the	colors in the existing presentation image are to be
.	combined.
.
.	The following is a Windows summary of the drawmodes.
.
.	Mix mode	Description
.
.	BLACKNESS	Pixel is always	0.
.
.	COPYPEN		Pixel is the pen color.
.
.	INVERT		Pixel is the inverse of	the screen color.
.
.	MASKNOTPEN	Pixel is a combination of the colors common
.			to both	the screen and the inverse of the pen.
.
.	MASKPEN		Pixel is a combination of the colors common
.			to both	the pen	and the	screen.
.
.	MASKPENNOT	Pixel is a combination of the colors common
.			to both	the pen	and the	inverse	of the screen.
.
.	MERGENOTPEN	Pixel is a combination of the screen color and
.			the inverse of the pen color.
.
.	MERGEPEN	Pixel is a combination of the pen color	and
.			the screen color.
.
.	MERGEPENNOT	Pixel is a combination of the pen color	and
.			the inverse of the screen color.
.
.	NOP		Pixel remains unchanged.
.
.	NOTCOPYPEN	Pixel is the inverse of	the pen	color.
.
.	NOTMASKPEN	Pixel is the inverse of	the MASKPEN color.
.
.	NOTMERGEPEN	Pixel is the inverse of	the MERGEPEN color.
.
.	NOTXORPEN	Pixel is the inverse of	the XORPEN color.
.
.	WHITENESS	Pixel is always	1.
.
.	XORPEN		Pixel is a combination of the pen color	and
.			the screen color, but not in both.
.
. Objects:
.	LINE
.	SHAPE
.
. dnumnvar values:
.
.$NONE	      EQU	0	//Same as default
$BLACKNESS    EQU	1
$COPYPEN      EQU	2	//Default
$INVERT	      EQU	3
$MASKNOTPEN   EQU	4
$MASKPEN      EQU	5
$MASKPENNOT   EQU	6
$MERGENOTPEN  EQU	7
$MERGEPEN     EQU	8
$MERGEPENNOT  EQU	9
$NOP	      EQU	10
$NOTCOPYPEN   EQU	11
$NOTMASKPEN   EQU	12
$NOTMERGEPEN  EQU	13
$NOTXORPEN    EQU	14
$WHITENESS    EQU	15
$XORPEN	      EQU	16
.
*------------------------------------------------------------------------------
.  DROPDOWNALIGN=dnumnvar			CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property is used to set or	get the	drop-down alignment of
.	the drop-down month calendar.
.
. Objects:
.	EDITDATETIME
.
. dnumnvar values:
.
.$OFF			EQU	0	// Default (Same as $DROPDOWNALIGNLEFT)
$DROPDOWNALIGNLEFT	EQU	1
$DROPDOWNALIGNRIGHT	EQU	2
.
*------------------------------------------------------------------------------
.   DROPID=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	When this property is specified, then the object which has the
.	DROPID property	can receive an item drop action.  The value of
.	the DROPID is sent to the activation routine of	the object which
.	is being dragged.
.
. Objects:
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	DATALIST
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	GROUPBOX
.	HSCROLLBAR
.	ICON
.	LISTVIEW
.	MOVIE
.	MREGION
.	PICT
.	POPUPMENU ( OBSOLETE )
.	PROGRESS
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	SLIDER
.	STATTEXT
.	TABCONTROL
.	TREEVIEW
.	VSCROLLBAR
.
. dnumnvar values:
.
*------------------------------------------------------------------------------
.  EDITCSS=svarslit					SETPROP	GETPROP	 10.5
.
. Description:
.       This property sets or clears an edit class used for a column.
.	
. Objects:
.       DATACOLUMN                                                             
.
. svarslit values:
.
.	The <svarslit> variable	is a CSS class name.
.
*------------------------------------------------------------------------------
.   EDITHIDESEL=dnumnvar			CREATE	SETPROP	GETPROP
.
. Description:
.	This property negates the default behavior for EDITTEXT	object.
.	The default behavior hides the selection when the EDITTEXT
.	loses the input	focus and inverts the selection	when the
.	EDITTEXT receives the input focus.  If this property is	turned
.	on, the	selected text is inverted, even	if the EDITTEXT	does
.	not have the focus.
.
. Objects:
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.  EDITLIST=svarslit					SETPROP	GETPROP	 10.5
.
. Description:
.       This property sets or clears an edit list used for a column.
.	
. Objects:
.       DATACOLUMN                                                             
.
. svarslit values:
.
.	The <svarslit> variable	is a list of fields that are
.       delimited using a semi-colon character
.
*------------------------------------------------------------------------------
.   EDITTYPE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the type of EDITTEXT object as follows:
.
.	ALL		-	Allow data entry of any	keyed characters.
.
.	DECIMAL		-	Only allow data	entry into the EDITTEXT
.				of numeric digits ( 0 through 9	), '-',
.				and '.'.
.	INTEGER		-	Only allow data	entry into the EDITTEXT
.				of numeric digits only.	( 0 through 9 ).
.	LOWERCASE	-	Convert	all characters to lowercase as they
.				are entered into the EDITTEXT.
.	UPPERCASE	-	Convert	all characters to uppercase as they
.				are entered into the EDITTEXT.
.	NUMERIC         -	Only allow data	entry into the EDITTEXT   9.4C
.				of numeric digits ( 0 through 9	), '-',
.				locale decimal, and locale thousand.
.
.	Note1:	This property should be	used in	place of older properties
.		which provide the same functions.
.
. Objects:
.	EDITTEXT
.
. dnumnvar values:
.
.$NONE	      EQU	0	       // Default
$ALL	      EQU	1
$INTEGER      EQU	2
$DECIMAL      EQU	3
$LOWERCASE    EQU	4
$UPPERCASE    EQU	5
$NUMERIC      EQU       6                                                 9.4C
.
*------------------------------------------------------------------------------
.   ENABLED=dnumnvar (Objects not MENUITEM)	CREATE	SETPROP	GETPROP
.   ENABLED=dnumnvar (MENUITEM)				SETPROP	GETPROP
.
. Description:
.	This property specifies	when an	object is to be	DISABLED/ENABLED.
.	If the ENABLED property	is set to $OFF for the CREATE/SETPROP
.	statements, this is the	same as	if a DISABLEITEM with an ITEMNO
.	value of zero was executed for the object.  If the ENABLED
.	property is set	to $ON for the SETPROP,	this is	the same as if
.	an ENABLEITEM with an ITEMNO value of zero was executed	for the
.	object.	 The GETPROP statement returns the current DISABLED/ENABLED
.	state for the object.
.
.	Note1: If the ENABLED property is set to $OFF for the objects
.	       ICON, MREGION, MOVIE, GROUPBOX, or PROGRESS there is
.	       no visible graying which	identifies that	the object is
.	       disabled.  However, there are no	events processed for
.	       these object when the ENABLED property is set to	$OFF.
.
. Objects:
.	ANIMATE								  9.0
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	DATALIST
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	GROUPBOX
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	ICON
.	LABELTEXT							  9.0
.	LISTVIEW
.	MENUITEM							  9.0
.	MREGION
.	MOVIE
.	PICT
.	POPUPMENU
.	PROGRESS
.	RADIO
.	RADIOGRP
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	SLIDER
.	STATTEXT
.	STATUSBAR
.	TABCONTROL
.	TOOLBAR
.	TREEVIEW
.	VSCROLLBAR
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1	       // Default
.
*------------------------------------------------------------------------------
.   ENTERTAB=dnumnvar				CREATE	SETPROP	GETPROP	  9.3
.
. Description: 
.	This property is used to set or	get the	conversion state that controls
.	the behavior where an ENTER key value is changed to a TAB key value
.	for a NETCONTROL.
.
.	If the state is	ON, then an ENTER key value is changed to a TAB
.	key value. If the state is OFF, an ENTER key value is not changed. 
.
. Objects:
.       NETCONTROL
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   EVENTFILTER=svarslit			CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	a string control structure, which allows
.	events for the EDITTEXT	object to be controlled.  See manual
.	discussion under create	for specific details.
.
. Objects:
.	EDITNUMBER							  8.7C
.	EDITTEXT
.
. svarslit values:
.
.	The <svarslit> string is composed of 'Y' and 'N'
.	characters, which relate to a given EDITTEXT object
.	event type by position in the string.
.
*------------------------------------------------------------------------------
.   FGCOLOR=dnumnvar|color object		CREATE	SETPROP	GETPROP
.
. Description:
.	This property allows the user program to specify the color to
.	be used	for the	foreground color of the	object.	 The parameter
.	description is the same	as for the BDRCOLOR property.
.
. Objects:
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	DATALIST
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	GROUPBOX
.	LABELTEXT							  9.0
.	LISTVIEW
.	POPUPMENU ( OBSOLETE )
.	PROGRESS
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
.	STATTEXT
.	WINDOW
.
. dnumnvar values:
.
.	See BDRCOLOR property for details.
.
*------------------------------------------------------------------------------
.   FILLCOLOR=dnumnvar|color object		CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the color to be	used when filling the
.	shape object.  Please see the description under	BDRCOLOR for
.	a detailed discussion of colors.
.
. Objects:
.	SHAPE
.
. dnumnvar values:
.
.	See BDRCOLOR property for details.
.
*------------------------------------------------------------------------------
.   FILLSTYLE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property defines the type of hatch	used to	fill a shape
.	object.	 The following is a summary of the types of hatches
.	available under	Windows.
.
.		Value		Meaning
.
.		DOWNDIAG	45-degree downward left-to-right hatch
.		CROSS		Horizontal and vertical	crosshatch
.		DIAGCROSS	45-degree crosshatch
.		UPDIAG		45-degree upward left-to-right hatch
.		HORIZLINE	Horizontal hatch
.		VERTLINE	Vertical hatch
.		NOHATCH		SHAPE object filled with solid color as
.				specified by FILLCOLOR.
.		CLEARHATCH	SHAPE object fill area becomes transparent
.				such that underlying colors show through
.				the object.
.
. Objects:
.	SHAPE
.
. dnumnvar values:
.
.$NONE	      EQU	0	       // Same as $NOHATCH
$CROSS	      EQU	1
$DIAGCROSS    EQU	2
$DOWNDIAG     EQU	3
$HORZLINE     EQU	4
$NOHATCH      EQU	5	       // Default
$CLEARHATCH   EQU	6
$UPDIAG	      EQU	7
$VERTLINE     EQU	8
.
.
*------------------------------------------------------------------------------
.   FLOATMENU=dnumnvar                          CREATE SETPROP  GETPROP   9.6
.
. Description: (Comctl32 Version 6 Required)
.       The FLOATMENU property specifies the object id of a FLOATMENU that
.       is to be associated with a button. If a FLOATMENU has been
.       specified, the drop down arrow invokes the FLOATMENU. Also, a right
.       mouse down action invokes the FLOATMENU.
.
. Objects:
.	BUTTON
.       CHECKBOX
.       LISTVIEW
.       RADIO
.       TREEVIEW
.       WINDOW
.
*------------------------------------------------------------------------------
.   FONT=svarslit|font object			CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the font to be used for	the supported
.	objects.
.
. Objects:
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	DATALIST
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	GROUPBOX
.	LABELTEXT							  9.0
.	LISTVIEW
.	POPUPMENU ( OBSOLETE )
.	PROGRESS
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
.	STATTEXT
.	STATUSBAR
.	TABCONTROL
.	TOOLBAR
.	TREEVIEW
.	WINDOW
.
. svarslit|font:
.
*------------------------------------------------------------------------------
.  FORMAT=dnumnvar				CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property is used in set or	get the	format of the EDITDATETIME
.	object.	This property can be one of:
.
.	$DTFORMATLONG	- Displays the date in long format. The	format string
.			  for this style is defined by LOCALE_SLONGDATEFORMAT,
.			  which	produces output	like "Monday, August 25, 2003".
.
.	$DTFORMATSHORT	- Displays the date in short format. The format	string
.			  for this style is defined by LOCALE_SSHORTDATE,
.			  which	produces output	like "8/25/03".
.
.	$DTFORMATTIME	- Displays the time. The  format string	for this style
.			  is defined by	LOCALE_STIMEFORMAT, which produces
.			  output like "10:33:15	AM".
.
.	$DTFORMATCUSTOM	- Displays the date and	time in	the format specified
.			  by the CUSTOMFORMAT property.
.
. Objects:
.	EDITDATETIME
.
. dnumnvar values:
.
.$DEFAULT	 EQU	0	  // Use Default ($DTFORMATSHORT)	  9.3A
$DTFORMATLONG	 EQU	1
$DTFORMATSHORT	 EQU	2
$DTFORMATTIME	 EQU	3
$DTFORMATCUSTOM	 EQU	4
.
*------------------------------------------------------------------------------
.   FULLROW=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	When this property is set to zero, then	the LISTVIEW extended style
.	is set to the default for FULLROW selection which means	that a
.	a row can only be selected by clicking on the first column items.
.	Also, only the first column items are highlighted for a	row selection.
.	When this property is set to a nonzero value, then the LISTVIEW
.	extended style is set to allow a row item to be	selected by clicking
.	anywhere in a row item view area.  In this case, the full row is
.	highlighted for	a given	selection.
.
.	This property can also be used for a TREEVIEW object.  If it
.	is set to $ON for a TREEVIEW, then it enables full-row selection.
.
.	Note:
.
.	  1. This property will	not take affect	unless a Microsoft file
.	     version of	4.71 or	later of 'comctl32.dll'	is installed on
.	     a given workstation.
.
.	  2. This property will	only affect the	operation of the LISTVIEW
.	     object when the VIEWSTYLE property	is set to $VIEWREPORT style.
.
.	  3. For a TREEVIEW object, this property will not take	affect
.	     unless a Microsoft	file version of	4.70 or	later of
.	     'comctl32.dll' is installed on a given workstation.
.
.	  2. This option cannot	be used	if the TREELNSTYLE is not set to
.	     $NOLINES for a TREEVIEW object.
.
. Objects:
.	LISTVIEW
.	TREEVIEW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   GRIDALIGN=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	When this property is set to zero, then	the alignment to grid
.	coordinates are	disabled.  When	this property is set to	one,
.	then objects, which are	created	for the	specified window, are
.	automatically aligned to the grid coordinates for the window.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   GRIDLINE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	When this property is set to $ON, then gridlines are displayed
.	around items and subitems.
.
.	Note:
.
.	  1. This property will	not take affect	unless a Microsoft file
.	     version of	4.70 or	later of 'comctl32.dll'	is installed on
.	     a given workstation.
.
.	  2. This property will	only affect the	operation of the LISTVIEW
.	     object when the VIEWSTYLE property	is set to $VIEWREPORT style.
.
. Objects:
.       DATATABLE                                                        10.5
.	LISTVIEW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   GRIDSIZEH=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property allows the horizontal grid size to be specified.	The
.	dnumnvar value specifies the horizontal	grid size based	on the UNITS
.	scale currently	in use for the WINDOW object.
.
.	Note1: The GETPROP statement also returns the current horizontal
.	       grid size as a value determined by the current UNITS scale
.	       specified for the WINDOW	object.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in the	same units as currently	used
.	for the	WINDOW object.	This means that	if the UNITS property for the
.	WINDOW object is currently set to 'TWIPS', then	the <dnumnvar> value
.	specifies the number of	'TWIPS'	for the	horizontal size.
.
*------------------------------------------------------------------------------
.   GRIDSIZEV=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property allows the vertical grid size to be specified.  The
.	dnumnvar value specifies the vertical grid size	based on the UNITS
.	scale currently	in use for the WINDOW object.
.
.	Note1: The GETPROP statement also returns the current vertical
.	       grid size as a value determined by the current UNITS scale
.	       specified for the WINDOW	object.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in the	same units as currently	used
.	for the	WINDOW object.	This means that	if the UNITS property for the
.	WINDOW object is currently set to 'TWIPS', then	the <dnumnvar> value
.	specifies the number of	'TWIPS'	for the	vertical size.
.
*------------------------------------------------------------------------------
.   GROUPID=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the group identifier for a radio button	or
.	checkbox object. All objects with the same group identifier are
.	treated	as one group for purposes of moving focus using	the TAB	or
.	arrow keys. For	radio buttons, this property is	also used to
.	determine which	radio button to	turn off when one is turned on.
.
. Objects:
.	CHECKBOX
.	RADIO
.
. dnumnvar values:
.
*------------------------------------------------------------------------------
.   GROUPVALUE=dnumnvar					SETPROP	GETPROP	  9.3
.
. Description:
.	This property is a GETPROP/SETPROP only property. This property
.	sets the button state value for a RADIO object the same as a
.	SETITEM instruction.
.
. Objects:
.	RADIO
.
. dnumnvar values:
.
*------------------------------------------------------------------------------
.   HEIGHT=dnumnvar					SETPROP	GETPROP
.
. Description:
.	This property is a GETPROP/SETPROP only	property.  The height
.	of the object can be retrieved using the GETPROP statement.
.	The height is determined by subtracting	the top	object rectangle
.	coordinate from	the bottom object rectangle coordinate.	 The
.	SETPROP	statement can be used to change	the current height of
.	an object.
.
. Objects:
.	ANIMATE								  9.0
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.	DIALOG
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	FLOATMENU
.	GROUPBOX
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	ICON
.	LABELTEXT							  9.0
.	LISTVIEW
.	MREGION
.	MOVIE
.	PICT
.	POPUPMENU ( OBSOLETE )
.	PROGRESS
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	SLIDER
.	STATTEXT
.	STATUSBAR
.	TABCONTROL
.	TOOLBAR
.	TREEVIEW
.	VSCROLLBAR
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in the	same units as used for
.	the creation of	an object.  This means that if an object was
.	created	using pixels, then the height expects to use pixels.
.
*------------------------------------------------------------------------------
.   HELPID=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is used in conjunction with a Windows Help file
.	provided by the	user.  If a program is executing with the F1HELP
.	set to ON using	a SETMODE statement, then this HELPID value is
.	used as	the help index context value for finding a given subject
.	in the help file when an object	has the	focus and the F1 function
.	key is entered.
.
.	For the	MENUITEM obect,	the HELPID property can	only be	used in
.	the GETPROP and	SETPROP	instructions.
.
. Objects:
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	HSCROLLBAR
.	LISTVIEW
.	MENUITEM							  9.1C
.	ICON
.	POPUPMENU ( OBSOLETE )
.	PROGRESS
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SLIDER
.	TABCONTROL
.	TREEVIEW
.	VSCROLLBAR
.
. dnumnvar values:
.
.	The <dnumnvar> value defines a help file context index value.
.
*------------------------------------------------------------------------------
.   HIDECOLHDR=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property indicates	if the column headers should be	displayed
.	or hidden when the ListView is in report view.
.
. Objects:
.       DATATABLE                                                        10.5
.	LISTVIEW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   HIDESEL=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	whether	a currently selected LISTVIEW/TREEVIEW
.	entry should remain highlighted	or not when the	focus is removed
.	from the LISTVIEW/TREEVIEW object.  The	default	is to have a selected
.	LISTVIEW/TREEVIEW entry	remain highlighted.
.
. Objects:
.	LISTVIEW
.	TREEVIEW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   HORZEXTENT=dnumnvar				CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used to set or	get the	width, in pixels, by which a
.	list box can be	scrolled horizontally (the scrollable width).  If
.	the width of the list box is smaller than this value, the horizontal
.	scroll bar horizontally	scrolls	items in the list box.	If the width
.	of the list box	is equal to or greater than this value,	the
.	horizontal scroll bar is hidden	or, if the object has the
.	SCROLLHIDE property set	$OFF, disabled.
.
. Objects:
.	COMBOBOX
.	DATALIST
.
*------------------------------------------------------------------------------
.   HOSTNAME=svarslit				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is used by the OLE insertable object's server
.	application when the server application	is open	to provide editing
.	of the OLE insertable object.
.
. Objects:
.	CONTAINER
.
. svarslit values:
.
.	The <svarslit> is a user-defined string.
.
*------------------------------------------------------------------------------
.   HOTTRACK=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	When this property is set to $ON, it enables hot-track selection
.	in a LISTVIEW/TREEVIEW object. Hot-track selection will	cause
.	the text of any	item that may be selected to be	underlined
.
.	Note:
.
.	  1. This property will	not take affect	unless a Microsoft file
.	     version of	4.71 or	later of 'comctl32.dll'	is installed on
.	     a given workstation.
.
.	  2. For a LISTVIEW object this	property requires that the
.	     ACTIVATE property be set to $ONECLICK or $TWOCLICK.
.
.  	  3. This property will	only affect the	operation of the LISTVIEW
.	     object when the VIEWSTYLE property	is set to $VIEWREPORT style.
.
. Objects:
.	LISTVIEW
.	TREEVIEW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   HOVERSEL=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	When this property is set to $ON, it enables hot-track selection
.	in a LISTVIEW object. Hot track	selection means	that an	item is
.	automatically selected when the	cursor remains over the	item
.	for a certain period of	time.
.
.	Note:
.
.	  1. This property will	not take affect	unless a Microsoft file
.	     version of	4.70 or	later of 'comctl32.dll'	is installed on
.	     a given workstation.
.
.	  2. This property will	only affect the	operation of the LISTVIEW
.	     object when the VIEWSTYLE property	is set to $VIEWREPORT style.
.
. Objects:
.	LISTVIEW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   HOVERTIME=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	When this property is sets the time for	automatic hot-track
.	selection. (See	the HOVERSEL property) The time	value is in
.	milliseconds. A	value of 0 indicates the default time is
.	used.
.
.	Note:
.
.	  1. This property will	not take affect	unless a Microsoft file
.	     version of	4.70 or	later of 'comctl32.dll'	is installed on
.	     a given workstation.
.
.	  2. This property will	only affect the	operation of the LISTVIEW
.	     object when the VIEWSTYLE property	is set to $VIEWREPORT style.
.
. Objects:
.	LISTVIEW
.
*------------------------------------------------------------------------------
.   HWND=nvar							GETPROP
.
. Description:
.	This property is a GETPROP only	property.  The HWND property
.	value is a Windows window handle for the supported object.
.	This HWND value	could be used in WINAPI	functions where
.	a window handle	is required for	the function.
.
. Objects:
.	ANIMATE								  9.0
.	BUTTON
.	CHECKBOX
.	COMBOBOX
.	CONTROL
.	DATALIST
.	DIALOG
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	LABELTEXT							  9.0
.	LISTVIEW
.	MOVIE
.	POPUPMENU ( OBSOLETE )
.	RADIO
.	SLIDER
.	STATUSBAR
.	RICHEDITTEXT							  9.0B
.	TABCONTROL
.	TOOLBAR
.	TREEVIEW
.	VSCROLLBAR
.	WINDOW
.
. nvar values:
.
.	The <nvar> value retrieve is a Windows window handle for
.	the supported object.
.
*------------------------------------------------------------------------------
.   ICON=dnumnvar|svarslit|icon	object		CREATE	SETPROP
.
. Description:
.	This property is supported only	for CREATE and SETPROP statements.
.	The property specifies when an icon is to replace the text for a
.	BUTTON object.	This property is supported only	for Windows95/98/NT.
.
. Objects:
.	BUTTON
.
. operand values:
.
.	The <dnumnvar> value is	used to	identify a 'resource id' to be used
.	when retrieving	the icon.   The	'resource id' value can	be any internal
.	runtime	supported values ( 10,000 to 11,500 ).	This value can also
.	be any user defined resource identification values as provided in a
.	resource library.  If the 'resource id'	value is zero, then the
.	ICON property is removed from the BUTTON object	and the	text name
.	for the	BUTTON will be used.
.
.	The <svarslit> string specifies	an icon	file name, which is to be used
.	for the	BUTTON object.	The icon file name will	default	to an
.	extension of '.ico'.  This name	supports the $MACRO and	generic
.	PLBVOL_	file name formats.  The	runtime	will use the 'PLB_PATH'
.	directories to initially locate	the file.  If the file is not found
.	using the 'PLB_PATH' directories, then the file	is passed to Windows to
.	be located in the Windows directories.	If the <svarslit> string
.	is NULL, then the ICON property	is removed from	the BUTTON object
.	and the	text name for the BUTTON will be used.
.
.	The <icon> object can be specified where the <icon> object must	have
.	been previously	created.  The data for the <icon> object is used
.	for the	button.
.
*------------------------------------------------------------------------------
.   IMAGECOLORS=dnumnvar			CREATE		GETPROP
.
. Description:
.	This property can only be used in a CREATE or GETPROP operation,
.	and it specifies the number of bits supported for colors
.	in an IMAGELIST	object.	 When this property is not specified,
.	the default is 32 bit colors.
.
. Objects:
.	IMAGELIST
.
. dnumnvar values:
.
.	The <dnumnvar> value is	the number of bits supported for colors.
.	Acceptable <dnumnvar> values are 4, 8, 16, or 32.  Any other
.	values specified are implemented as a value of 32.
.
*------------------------------------------------------------------------------
.  IMAGEINDEX=dnumnvar					SETPROP	GETPROP	  8.6D
.
. Description:
.	This property references the one-based indexed value of	the images
.	in an IMAGELIST	object assigned	to the parent TOOLBAR Object.
.	A value	of zero	indicates no image. A value of one indicates the
.	first image in the IMAGELIST object.
.
.	A TOOLBAR object contains a default IMAGELIST, but this	can be
.	changed	using the SetImageList SetImageListDisabled,
.	and SetImageListHot TOOLBAR object methods.
.
.	For an ICON object, the	IMAGEINDEX is used as an index into an
.	imagelist linked to the	ICON using the IMAGELIST property.
.
. Objects:
.	ICON								  9.0
.	TOOLBUTTON
.
. dnumnvar values:
.
.	One based image	value.
.
*------------------------------------------------------------------------------
.  IMAGELIST={imagelist	object}			CREATE	SETPROP		  9.0
.
. Description:
.	This property allows the images	from an	IMAGELIST object to be used
.	for the	parent object.
.
. Objects:
.	ICON
.	LISTVIEW
.	TABCONTROL							  9.4C
.	TOOLBAR
.	TREEVIEW
.
*------------------------------------------------------------------------------
.  IMAGELISTD={imagelist object}		CREATE	SETPROP		  9.0
.
. Description:			
.	This property associates an IMAGELIST object with the disabled images
.	of a TOOLBAR object.  See the TOOLBAR method 'SetImageListDisabled'
.	for more details about disabled	images for a TOOLBAR object.
.
. Objects:
.	TOOLBAR
.
*------------------------------------------------------------------------------
.  IMAGELISTH={imagelist object}		CREATE	SETPROP		  9.0
.
. Description:
.	This property associates an IMAGELIST object with the hot images of a
.	TOOLBAR	object.	 See the TOOLBAR method	'SetImageListHot' for more
.	details	about hot images for a TOOLBAR object.
.
. Objects:
.	TOOLBAR
.
*------------------------------------------------------------------------------
.  IMAGELISTSM={imagelist object}		CREATE	SETPROP		  9.0
.
. Description:
.	This property associates an IMAGELIST object with the small icons of a
.	LISTVIEW object.  See the LISTVIEW method 'SetImageListSmall' for more
.	details	about small icons for a	LISTVIEW object.
.
. Objects:
.	LISTVIEW
.
*------------------------------------------------------------------------------
.  IMAGELISTST={imagelist object}		CREATE	SETPROP		  9.0
.
. Description:
.	This property associates an IMAGELIST object with the state icons of a
.	LISTVIEW object.  See the LISTVIEW method 'SetImageListState' for more
.	details	about state icons for a	LISTVIEW object.
.
. Objects:
.	LISTVIEW
.
*------------------------------------------------------------------------------
.   IMAGESIZEH=dnumnvar				CREATE		GETPROP
.   IMAGESIZEH=dnumnvar	( PWS IMAGELIST )	CREATE	SETPROP	GETPROP  9.9
.
. Description:
.	This property specifies	the width in pixels for	the images to be
.	stored in the IMAGELIST	object. The SETPROP of this property is
.	for support of the PL/B Web Server IMAGELIST object.
.
. Objects:
.	IMAGELIST
.
. dnumnvar values:
.
.	The <dnumnvar> value is	the number of pixels for image width.
.
*------------------------------------------------------------------------------
.   IMAGESIZEV=dnumnvar				CREATE		GETPROP
.   IMAGESIZEH=dnumnvar	( PWS IMAGELIST )	CREATE	SETPROP	GETPROP  9.9
.
. Description:
.	This property specifies	the height in pixels for the images to be
.	stored in the IMAGELIST	object. The SETPROP of this property is
.	for support of the PL/B Web Server IMAGELIST object.
.
. Objects:
.	IMAGELIST
.
. dnumnvar values:
.
.	The <dnumnvar> value is	the number of pixels for image height.
.
*------------------------------------------------------------------------------
.   INDENT=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property defines the width	of the indentation between parent
.	items and children items.  A value of zero causes a Windows default
.	to be used.
.
. Objects:
.	TREEVIEW
.
. dnumnvar values:
.
.	The <dnumnvar> value specifies the number of pixels for	indentation.
.
*------------------------------------------------------------------------------
.   INNERHTML=svarslit				CREATE	SETPROP	GETPROP  10.0A
.
. Description:
.	This property can be used to render a HTML Web page into
.	a HTMLCONTROL object.
.
. Objects:
.	HTMLCONTROL
.
. svarslit values:
.
.	The <svarslit> variable	is a HTML string for the object.
.
*------------------------------------------------------------------------------
.   INPUTTYPE=dnumnvar				CREATE	SETPROP	GETPROP  10.5
.
. Description:
.       The INPUTTYPE property is only used when an EDITTEXT object has
.       been created as a web object using the WebView mode. This property
.       sets the input 'type' of the HTML <input> tag used by an EDITTEXT
.       web object.
.
. Objects:
.	EDITTEXT (WebView Only)
.
. dnumnvar values:
.
$ET_INPUTDEFAULT   EQU  0           //text    <input type="text">
$ET_INPUTCOLOR     EQU  1           //color
$ET_INPUTDATE      EQU  2           //date
$ET_INPUTDTLOCAL   EQU  3           //datetime-local
$ET_INPUTEMAIL     EQU  4           //email
$ET_INPUTMONTH     EQU  5           //month
$ET_INPUTNUMBER    EQU  6           //number
$ET_INPUTPASSWORD  EQU  7           //password
$ET_INPUTSEARCH    EQU  8           //search
$ET_INPUTTEL       EQU  9           //tel
$ET_INPUTTEXT      EQU  10           //text
$ET_INPUTTIME      EQU  11           //time
$ET_INPUTWEEK      EQU  13           //week

*------------------------------------------------------------------------------
.   INTASKBAR=dnumnvar				CREATE		GETPROP
.
. Description:
.	This property forces a top-level window	onto the taskbar when
.	the window is visible and the WINBORDER	type for the window is
.	'FIXEDTOOL' or 'SIZABLETOOL'.  This property is	ignored	when
.	the WINBORDER type is any other	setting.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   INTEGERDIGITS=dnumnvar			CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used to set or	get number of integer digits allowed.
.
. Objects:
.	EDITNUMBER
.
*------------------------------------------------------------------------------
.   INTEGRAL=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	when a DATALIST	is to resize for the
.	number of items	in a list versus leaving the size of the DATALIST
.	to be as defined by the	user rectangle coordinates.  When the
.	INTEGRAL property is set to OFF, then the size of the list box
.	is the size specified by the user coordinate values.  When the
.	INTEGRAL property is set to ON,	then the normal	action of Windows
.	is to resize a list box	so that	the list box does not display
.	partial	items.
.
. Objects:
.	DATALIST
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1	       // Default
.
*------------------------------------------------------------------------------
.   ITALIC[=dnumnvar]				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	that the font should be	italic.	 When
.	the <dnumnvar> value is	not provided, this indicates that the
.	ITALIC property	is turned on.
.
. Objects:
.	FONT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   LABELWRAP=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property indicates	if the text labels may wrap in icon view.
.	If set to $OFF,	text labels will be displayed on a single line in
.	icon view.
.
. Objects:
.	LISTVIEW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   LEFT=dnumnvar					SETPROP	GETPROP
.
. Description:
.	This property is a GETPROP/SETPROP only	property.  The LEFT
.	property returns the left coordinate of	a created objected.
.
. Objects:
.	ANIMATE								  9.0
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.	DIALOG
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	FLOATMENU
.	GROUPBOX
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	ICON
.	LABELTEXT							  9.0
.	LISTVIEW
.	MREGION
.	MOVIE
.	PICT
.	POPUPMENU ( OBSOLETE )
.	PROGRESS
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	SLIDER
.	STATTEXT
.	STATUSBAR
.	TABCONTROL
.	TOOLBAR
.	TREEVIEW
.	VSCROLLBAR
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in the	same units as used when
.	the object was created.
.
*------------------------------------------------------------------------------
.   LEFTMARGIN=dnumnvar				CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used in set or	get the	left margin of an EDITTEXT
.	or EDITNUMBER object.
.
. Objects:
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
*------------------------------------------------------------------------------
.   LIC=svarslit				CREATE		GETPROP
.
. Description:
.	This property allows a PLB program to retrieve or
.	specify	a valid	LICENSE	identifier for the CONTROL
.	or AUTOMATION object.
.
. Objects:
.	AUTOMATION
.	CONTROL
.
. svarslit values:
.
.	The <svarslit> variable	is a license string for	the object.
.
*------------------------------------------------------------------------------
.   LINKHSCROLL=<hscrollbar>			CREATE		GETPROP
.
. Description:
.	This property is to allow a horizontal scrollbar object	to be
.	linked to the scrollbar	which may be generated for a PICT or a
.	WINDOW object.	After the logical linkage is established, then
.	operations on the linked scrollbar can be executed.  This means
.	that a GETITEM for the <hscrollbar> object can be executed to
.	determine the current settings of the scrollbar	which has be
.	generated for another object.
.
.	Note1: It is not possible to change the	MIN, MAX, or SHIFT values
.	       for a picture linked scrollbar using either the SETPROP or
.	       SETITEM.	A picture-linked scrollbar can change the thumb
.	       position	and tab	id. These restrictions do not apply to
.	       a window	linked scrollbar.
.
. Objects:
.	PICT
.	WINDOW
.
*------------------------------------------------------------------------------
.   LINKVSCROLL=<vscrollbar>			CREATE		GETPROP
.
. Description:
.	This property is to allow a vertical scrollbar object to be
.	linked to the scrollbar	which may be generated for a PICT or a
.	WINDOW object.	After the logical linkage is established, then
.	operations on the linked scrollbar can be executed.  This means
.	that a GETITEM for the <vscrollbar> object can be executed to
.	determine the current settings of the scrollbar	which has be
.	generated for another object.
.
.	Note1: It is not possible to change the	MIN, MAX, or SHIFT values
.	       for a linked scrollbar using either the SETPROP or SETITEM.
.	       It is possible to change	the thumb position however.
.
. Objects:
.	PICT
.	WINDOW
.
*------------------------------------------------------------------------------
.   LOWERCASE[=dnumnvar]			CREATE
.
. Description:
.	This property is a CREATE only property.
.	The property specifies that the	EDITTEXT object	is to convert
.	all entered data to lowercase.	When this property is set to
.	be OFF,	then this indicates that no data conversion occurs.
.
.	Note1: Use of the property should be replaced through use of 
.	       the EDITTYPE property.
.
. Objects:
.	EDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   MASKCOLOR=dnumnvar|color object		CREATE	SETPROP	GETPROP
.
. Description:
.	This property allows the user program to specify the color to
.	be used	as the mask color in the AddBmpMasked method.  The parameter 
.	description is the sameas for the BDRCOLOR property.
.
. Objects:
.	IMAGELIST
.
. dnumnvar values:
.
.	See the	BDRCOLOR property for the color	equate values.
.
*------------------------------------------------------------------------------
.   MAX=dnumnvar			     See Objects:
.
. Description:
.	This property defines the maximum value	when the slider	thumb is at
.	the bottom or right most position of the supported object.
.
. Objects:
.	HSCROLLBAR					SETPROP	GETPROP
.	SLIDER					CREATE	SETPROP	GETPROP
.	VSCROLLBAR					SETPROP	GETPROP
.
. dnumnvar values:
.
.	The value is a logical unit as specified by the	user.
.
*------------------------------------------------------------------------------
.   MAXBOX=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	when a MAXIMIZE	box for	the window
.	object should be allowed or not.
.
.	Note1: The MAXBOX property does	not have an effect if the 
.	       CAPTION property	is set to $OFF for a MODAL or MODELESS
.	       window type.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1	       // Default
.
*------------------------------------------------------------------------------
.   MAXCHARS=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	Specifies the maximum number of	characters allowed to
.	be entered into	EDITTEXT object. This applies whether
.	EDITTEXT is single line	or multiline.
.
. Objects:
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values:
.
.	The <dnumnvar> value defines number of characters.
.
*------------------------------------------------------------------------------
.   MAXCOLS=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	The property is	the maximum number of characters allowed for
.	an individual line in a	multiline EDITEXT object.  This	property
.	is ignored if the MULTILINE is not used.
.
. Objects:
.	EDITTEXT
.
. dnumnvar values:
.
.	The <dnumnvar> value defines number of characters.
.
*------------------------------------------------------------------------------
.   MAXIMUMDATE=svarslit			CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property sets or gets the maximum date allowed for	the
.	EDITDATETIME object.
.
.	The string returned or given is	in the format of YYYYMMDD, where
.	YYYY is	a four digit year, MM is a two digit month, and	DD is a
.	two digit day.
.
. Objects:
.	EDITDATETIME
.
. svarslit values:
.
.	The <svarslit> variable	is a date string.
.
*------------------------------------------------------------------------------
.   MAXITEMS=dnumnvar				CREATE	SETPROP	GETPROP   10.8
.
. Description:
.       The MAXITEMS property sets the maximum item count for the
.       number of active items that can be added to the DATASET.
.
. Objects:
.       DATASET
.
. dnumnvar values:
. 
.       The numeric value is the maximum item count.
. 
*------------------------------------------------------------------------------
.   MAXSIZE=dnumnvar				        SETPROP	GETPROP   10.5
.
. Description:
.	Specifies the maximum number of	characters allowed to
.	be entered into	a column
.
. Objects:
.	DATACOLUMN							  
.
. dnumnvar values:
.
.	The <dnumnvar> value defines number of characters.
.
*------------------------------------------------------------------------------
.   MDIBORDER=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property defines when a MDI client	window in a window object
.	is to have a border.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   MDIHEIGHT=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the height in pixels for the MDI client
.	window.	If this	property is zero, the bottom of	the MDI	client
.	is pinned to the bottom	of the WINDOW object.
.
. Objects:
.	WINDOW
.
*------------------------------------------------------------------------------
.   MDILEFT=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the left position in pixels for	the MDI	client
.	window.
.
. Objects:
.	WINDOW
.
*------------------------------------------------------------------------------
.   MDILIST=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is used to indicate that a MDI window menu list should
.	be appended to the MENU	object list.
.
. Objects:
.	MENU
.
*------------------------------------------------------------------------------
.   MDISCROLL=dnumnvar				CREATE		GETPROP
.
. Description:
.	This property specifies	what type of scrollbars	are to be provided
.	for the	MDI client window in a window object. Actual scrollbar
.	handling is automatically performed.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$NONE		EQU	0	       // Default
.$SCRBOTH	EQU	1
.$SCRHORZ	EQU	2
.$SCRNONE	EQU	3
.$SCRVERT	EQU	4
*------------------------------------------------------------------------------
.   MDITOP=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the top	position in pixels for the MDI client
.	window.
.
. Objects:
.	WINDOW
.
*------------------------------------------------------------------------------
.   MDIWIDTH=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the width in pixels for	the MDI	client
.	window.	If this	property is zero, the right of the MDI client
.	is pinned to the right of the WINDOW object.
.
. Objects:
.	WINDOW
.
*------------------------------------------------------------------------------
.   MENUORDER=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the position of	the menu in the	menubar.
.
. Objects:
.	MENU
.
. dnumnvar values:
.	The dnumnvar value is a	user defined value starting with zero that
.	gives the expected position of the menu	in the menubar.
.
*------------------------------------------------------------------------------
.   MENUTEXT=svarslit					SETPROP	GETPROP	  8.6D
.
. Description:
.	This property is used to provide a menu	string for the popup
.	menu of	a TOOLBUTTON with the BTNSTYLE property	set to
.	$TBSTYLEDROPDOWN or $TBSTYLEDROPDOWNW.
.
.	The string is the same as provided to a	FLOATMENU object, but
.	with no	leading	menu name.
.
. Objects:
.	TOOLBUTTON
.
. svarslit value:
.
.	String of semicolon separated menu items.
.
*------------------------------------------------------------------------------
.   MERGETYPE=dnumnvar				CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property specifies	the position of	the menu in the	menubar.
.
. Objects:
.	MENU
.
. dnumnvar values:
.	This property is used ot assign	a merging action for a menu.  Menus
.	can be merged when a CONTAINER object that has a menu is activated.
.
. dnumnvar values:
.
$MERGENONE    EQU  0	 //Default
$MERGELEFT    EQU  1
$MERGEMIDDLE  EQU  2
$MERGERIGHT   EQU  3
.
*------------------------------------------------------------------------------
.   MIN=dnumnvar			     See Objects:
.
. Description:
.	This property defines the minimum value	when the slider	thumb is at
.	the top	or left	most position of the supported object.
.
. Objects:
.	HSCROLLBAR					SETPROP	GETPROP
.	SLIDER					CREATE	SETPROP	GETPROP
.	VSCROLLBAR					SETPROP	GETPROP
.
. dnumnvar values:
.
.	The value is a logical unit as specified by the	user.
.
*------------------------------------------------------------------------------
.   MINBOX=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	when a MINIMIZE	box for	the window
.	object should be allowed or not.
.
.	Note1: The MINBOX property does	not have an effect if the 
.	       CAPTION property	is set to $OFF for a MODAL or MODELESS
.	       window type.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1	       // Default
.
*------------------------------------------------------------------------------
.   MINEXTRA=dnumnvar				CREATE	SETPROP	GETPROP	  8.7A
.
. Description:
.	The MINEXTRA property specifies	the minimum distance that
.	must remain between the	SPLITTER object	and the	edge of	the
.	opposite side of the closest object docked to the opposite side.
.
. Objects:
.	SPLITTER
.
. dnumnvar values:
.
.	The <dnumnvar> value is	a pixel	value.
.
.
*------------------------------------------------------------------------------
.   MINHEIGHT=dnumnvar                          CREATE  SETPROP GETPROP   9.6
.
. Description:
.	The MINHEIGHT property can be used to set a minimum height for a
.	WINDOW object. This minimum height prevents a window from being
.       sized below this size.
.
. Objects:
.       WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in pixels.
.
*------------------------------------------------------------------------------
.   MINIMUMDATE=svarslit			CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property sets or gets the minimum date allowed for	the
.	EDITDATETIME object.
.
.	The string returned or given is	in the format of YYYYMMDD, where
.	YYYY is	a four digit year, MM is a two digit month, and	DD is a
.	two digit day.
.
. Objects:
.	EDITDATETIME
.
. svarslit values:
.
.	The <svarslit> variable	is a date string.
.
*------------------------------------------------------------------------------
.   MINSCROLLH=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is used in conjunction with the AUTOSCROLL property
.	to specify the minimum horizontal size the window can shrink to
.	before scrollbars appear.
.
. Objects:
.	PANEL
.	WINDOW
.
*------------------------------------------------------------------------------
.   MINSCROLLV=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is used in conjunction with the AUTOSCROLL property
.	to specify the minimum vertical	size the window	can shrink to
.	before scrollbars appear.
.
. Objects:
.	PANEL
.	WINDOW
.
*------------------------------------------------------------------------------
.   MINSIZE=dnumnvar				CREATE	SETPROP	GETPROP	  8.7A
.
. Description:
.	The MINSIZE property specifies the minimum distance that
.	must remain between the	SPLITTER object	and the	edge of	the
.	object that the	SPLITTER object	is docked to.
.
. Objects:
.	SPLITTER
.
. dnumnvar values:
.
.	The <dnumnvar> value is	a pixel	value.
.
*------------------------------------------------------------------------------
.   MINWIDTH=dnumnvar	(STATUSPANEL)			SETPROP	GETPROP
.   MINWIDTH=dnumnvar   (WINDOW)                CREATE  SETPROP GETPROP   9.6
.
. Description:
.	This property sets or returns the minimum width	of a STATUSPANEL
.	object.	This property is only used when	the AUTOSIZE property
.	is set to $PANSIZECONTENTS or $PANSIZESPRING.
.	
.       The MINWIDTH property can be used to set a minimum width for
.       a WINDOW object. This minimum width prevents a window from being
.       sized below this size.
.
. Objects:
.	STATUSPANEL
.       WINDOW								  9.6
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in pixels.
.
*------------------------------------------------------------------------------
.   MPIBORDER=dnumnvar				CREATE	SETPROP	GETPROP	  10.7
.
. Description:
.	This property defines when a MPI client	window in a window object
.	is to have a border.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   MPIHEIGHT=dnumnvar				CREATE	SETPROP	GETPROP	  10.7
.
. Description:
.	This property specifies	the height in pixels for the MPI client
.	window.	If this	property is zero, the bottom of	the MPI	client
.	is pinned to the bottom	of the WINDOW object.
.
. Objects:
.	WINDOW
.
*------------------------------------------------------------------------------
.   MPILEFT=dnumnvar				CREATE	SETPROP	GETPROP	  10.7
.
. Description:
.	This property specifies	the left position in pixels for	the MPI	client
.	window.
.
. Objects:
.	WINDOW
.
*------------------------------------------------------------------------------
.   MPISCROLL=dnumnvar				CREATE		GETPROP	  10.7
.
. Description:
.	This property specifies	what type of scrollbars	are to be provided
.	for the	MPI client window in a window object. 
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$NONE		EQU	0	       // Default
.$SCRBOTH	EQU	1
.$SCRHORZ	EQU	2
.$SCRNONE	EQU	3
.$SCRVERT	EQU	4
*------------------------------------------------------------------------------
.   MPITOP=dnumnvar				CREATE	SETPROP	GETPROP	  10.7
.
. Description:
.	This property specifies	the top	position in pixels for the MPI client
.	window.
.
. Objects:
.	WINDOW
.
*------------------------------------------------------------------------------
.   MPIWIDTH=dnumnvar				CREATE	SETPROP	GETPROP	  10.7
.
. Description:
.	This property specifies	the width in pixels for	the MPI	client
.	window.	If this	property is zero, the right of the MPI client
.	is pinned to the right of the WINDOW object.
.
. Objects:
.	WINDOW
.
*------------------------------------------------------------------------------
.   MODIFYFLAG=dnumnvar					SETPROP	GETPROP	  8.7C
.
. Description:
.	This property sets or retrieves	the state of an	edit object's
.	modification flag. The flag indicates whether the contents
.	of the edit object have	been modified. The system automatically	clears
.	the modification flag to zero when the object is created. If the user
.	changes	the object's text, the system sets the flag to $ON.
.
. Objects:
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   MULTICOLUMN=dnumnvar			CREATE		GETPROP
.
. Description:
.	This property is used to indicate if the DATALIST object should
.	contain	multiple columns. The size of the columns is set using the
.	COLUMNWIDTH property.
.
. Objects:
.	DATALIST
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   MULTILINE[=dnumnvar]			CREATE	SETPROP	GETPROP
.
. Description for EDITTEXT:
.
.	This property defines the number of lines to be	allowed
.	for an EDITTEXT	object.	 If a user <dnumnvar> value
.	is not specified, then the number of lines allowed is
.	set to 32000.  If the number of	lines specified	can
.	fit into the user specified rectangle coordinates, then
.	scrollbars are not provided.  Otherwise, scrollbars will
.	exist for the EDITTEXT object.
.
. Description for RICHEDITTEXT:						  9.0B
.
.	This property is used for a RICHEDITTEXT object	to set or get the 
.	multiline capability of	the object.
.
.	If ON, then multiple lines are allowed.	If OFF then only a single
.	line is	allowed.
.
. Objects:
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values for EDITTEXT:
.
.	The <dnumnvar> value specifies number of lines.
.
. dnumnvar values for RICHEDITTEXT:					  9.0B
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   MULTIROW=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is used to indicate if labels are	allowed	to be
.	shown in multiple rows.	If multiple rows are not allowed, and
.	the labels are too large to fit	in one row, left and right
.	arrow buttons are drawn	to allow access	to the other labels.
.
. Objects:
.	TABCONTROL
.
. dnumnvar values:
.
.$OFF	      EQU	0	     //	Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   MULTISELECT[=dnumnvar]			CREATE	SETPROP	GETPROP
.
. Description:
.	This property allows a multiple	items to be selected from an
.	object.	 If the	<dnumnvar> parameter is	not provided, the
.	MULTISELECT is set to ON.  
.
.	Note1:	The SETPROP statement does not support this property for
.		the DATALIST object.
.
.	Note2:	The $EXTENDED value is only valid for a	DATALIST object.
.		When $EXTENDED is used for MULTISELECT type, then the
.		DATALIST allows	a range	of items to be selected	by using
.		the SHIFT key or the MOUSE.
.
.	Note3:	When this property is turned ON	for the	LISTVIEW object,
.		then multiple entries can be selected by using the SHIFT
.		key and	the MOUSE.  This action	is controlled by Windows.
.
. Objects:
.	DATALIST
.	LISTVIEW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
$EXTENDED     EQU	2	       // DATALIST only
.
*------------------------------------------------------------------------------
.   NEGBORDERS=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is available for a WINDOW	object to identify
.	whether	the runtime should negotiate border usage for a
.	CONTAINER object create	on the WINDOW.
.	
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   NEGMENUS=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is available for a WINDOW	object to identify
.	whether	the runtime should negotiate menu usage	for a
.	CONTAINER object create	on the WINDOW.
.
.	Note:
.	     1.	When the NEGMENUS property is set to $ON, then user
.		PL/B MENU string controls named	'<l', '<L', '<m', '<M',
.		'<r', and '<R' can be used to identify the positioning of
.		a form's top level menu	items as melded/integrated with	the
.		menu items for a CONTAINER object.  If none of these
.		controls are specified,	then the PL/B window menu items
.		will be	replaced by the	menu items for a CONTAINER object
.		when the CONTAINER has the focus; and the PL/B window menu
.		items will be available	when the CONTAINER does	not have
.		the focus.  These menu string controls are defined as follows:
.
.		    -l or -L	-  A top level PL/B menu item is to be placed
.				   to the left of the menu items for a
.				   CONTAINER object.
.
.		    -r or -R	-  A top level PL/B menu item is to be placed
.				   to the right	of the menu items for a
.				   CONTAINER object.
.
.		    -m or -M	-  A top level PL/B menu item is to be placed
.				   into	the middle of the menu items for a
.				   CONTAINER object.  The actual placement
.				   of the top level PL/B menu item in this
.				   case	is actually controlled by the current
.				   CONTAINER object being executed.
.	
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   NOAUTOZOOM	(OBSOLETE)			CREATE
.
. Description:
.	This is	an obsolete property maintained	only for backward
.	source compatibility.  The NOAUTOZOOM property is the same
.	as AUTOZOOM=0.
.
.	Note1:	The AUTOZOOM property must be used if SETPROP/GETPROP
.		operations are required.
.
. Objects:
.	PICT
.
. dnumnvar values:
.
.	None
.
*------------------------------------------------------------------------------
.   NOINTEGRAL	(OBSOLETE)			CREATE
.
. Description:
.	This property is a CREATE only property	and is obsolete.
.	This property maintained only for backward source compatibility.
.	The NOINTEGRAL property	is the same as INTEGRAL=0.
.
.	Note1:	The INTEGRAL property must be used if SETPROP/GETPROP
.		operations are required.
.
. Objects:
.	DATALIST
.
. dnumnvar values:
.
.	None
.
*------------------------------------------------------------------------------
.   NOMENURESIZE=dnumnvar			CREATE	SETPROP	GETPROP
.
. Description:
.	This property is available for a WINDOW	object to specify when
.	the overall WINDOW object height should	be changed or not
.	should a MENU object be	created	and added to the WINDOW	object.
.	When the NOMENURESIZE property value is	set to zero, this
.	will cause the overall WINDOW object height to be increased when
.	a MENU object is added such that the client height is unchanged
.	for the	WINDOW object.	However, if the	NOMENURESIZE property
.	value is set to	a non-zero value, this will cause the overall
.	WINDOW object height to	remain unchanged when a	MENU object
.	is added such that the client height for the WINDOW object
.	is changed.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   NOPERCENT	(OBSOLETE)			CREATE
.
. Description:
.	This property is a CREATE only property	and is obsolete.
.	This property maintained only for backward source compatibility.
.	The NOPERCENT property is the same as PERCENT=0.
.
.	Note1:	The PERCENT property must be used if SETPROP/GETPROP
.		operations are required.
.
. Objects:
.	PROGRESS
.
. dnumnvar values:
.
.	None
.
*------------------------------------------------------------------------------
.   NORESIZE	(OBSOLETE)			CREATE
.
. Description:
.	This property is a CREATE only property	and is obsolete.
.	This property maintained only for backward source compatibility.
.	The NORESIZE property is the same as RESIZE=0.
.
.	Note1:	The RESIZE property must be used if SETPROP/GETPROP
.		operations are required.
.
. Objects:
.	PICT
.
. dnumnvar values:
.
.	None
.
*------------------------------------------------------------------------------
.   NOSCROLL	(OBSOLETE)			CREATE
.
. Description:
.	This property is a CREATE only property	and is obsolete.
.	This property maintained only for backward source compatibility.
.	The NOSCROLL property is the same as SCROLLBAR=0.
.
.	Note1:	The SCROLLBAR property must be used if SETPROP/GETPROP
.		operations are required.
.
. Objects:
.	PICT
.
. dnumnvar values:
.
.	None
*------------------------------------------------------------------------------
.   NULLSIZE=dnumnvar				CREATE	SETPROP	GETPROP   10.8
.
. Description:
.       The MAXITEMS property is sets the text size to be used when a
.       DATASET item is added with NULL input. The default NULLSIZE is
.       100 bytes.
.
. Objects:
.       DATASET
.
. dnumnvar values:
.
.       Value is the maximum allowed NULL size for a DATASET item.
.
*------------------------------------------------------------------------------
.   NUMERIC[=dnumnvar]				CREATE
.
. Description:
.	This property is a CREATE only property.
.	The property specifies that the	EDITTEXT object	is to allow 
.	numeric	digits 0 through 9, '-'	character, and '.' character.
.	When this property is set to the OFF state, this indicates that
.	all characters are allowed.  If	the <dnumnvar> value is	not
.	provided, the NUMERIC property is set to ON.
.
.	Note1: Use of the property should be replaced through use of 
.	       the EDITTYPE property.
.
. Objects:
.	EDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	1	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   OBJECTID=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	a identification number	for an object.
.	The OBJECTID value is available	through	the use	of the EVENTINFO
.	or EVENTREG statements to identify the object which caused
.	an event to occur.
.
. Objects:
.	ANIMATE								  9.0
.	AUTOMATION
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.       DATATABLE                                                        10.5
.	DIALOG
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	FLOATMENU
.	GROUPBOX
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	ICON
.	LABELTEXT							  9.0
.	LINE
.	LISTVIEW
.	MENU
.	MREGION
.	MOVIE
.	PICT
.	POPUPMENU ( OBSOLETE )
.	PROGRESS
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	SLIDER
.	STATTEXT
.	STATUSBAR
.	SUBMENU
.	TABCONTROL
.	TOOLBAR
.	TIMER
.	TREEVIEW
.	VSCROLLBAR
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumvar> is a user-specified number to identify an	object.
.
*------------------------------------------------------------------------------
.   OLEDROP=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property enables or disables the capability of dropping an	
.	OLE insertable object on an empty OLE container	object.
.
. Objects:
.	CONTAINER
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   OLETYPE=dnumnvar				GETPROP
.
. Description:
.	This property returns the type of OLE insertable object	in the
.	OLE container object. This property is only valid for a	GETPROP
.	statement.  Also, see the property OLETYPEA as a related property.
.	The OLETYPE property will return one of:
.
.	$OLETYPEEMPTY	- The OLE container object is empty.	       
.	$OLETYPEEMBED	- The OLE container object contains a embedded
.			  OLE insertable object.
.	$OLETYPELINK	- The OLE container object contains a linked
.			  OLE insertable object.
.
. Objects:
.	CONTAINER
.
. dnumnvar values:
.
$OLETYPEEMPTY	EQU	1	       
.$OLETYPEEMBED	EQU	2
.$OLETYPELINK	EQU	3
.
*------------------------------------------------------------------------------
.   OLETYPEA=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is used to control the type of OLE insertable object
.	allowed	in an OLE container object. This property affects any
.	method used to place a OLE insertable object into a OLE	container 
.	object.	See the	property OLETYPE as a related property.	It must	
.	be one of:
.
.	$OLETYPEBOTH	- The OLE container object can contain either an
.			  embedded or linked OLE insertable object.	       
.	$OLETYPEEMBED	- The OLE container object must	contain	a embedded
.			  OLE insertable object.
.	$OLETYPELINK	- The OLE container object must	contain	a linked
.			  OLE insertable object.
.
. Objects:
.	CONTAINER
.
. dnumnvar values:
.
$OLETYPEBOTH	EQU	1	       
$OLETYPEEMBED	EQU	2
$OLETYPELINK	EQU	3
.
*------------------------------------------------------------------------------
.   ORDER=dnumnvar				     	SETPROP	GETPROP   10.5
.
. Description:
.	Specifies the display position of a column
.
. Objects:
.	DATACOLUMN							  
.
. dnumnvar values:
.
.	The <dnumnvar> value defines zero based display position.
.
*------------------------------------------------------------------------------
.   ORIENTATION=dnumnvar			CREATE	SETPROP	GETPROP
.
. Description:
.	The property controls the whether a slider object is to	be
.	horizontal or vertical.
.
. Objects:
.	SLIDER
.
. dnumnvar values:
.
.$NONE	      EQU	0	       // Same as $VERT
$HORZ	      EQU	1
$VERT	      EQU	2	       // Default
.
*------------------------------------------------------------------------------
.   OSEVENTMASK=dnumnvar			CREATE	SETPROP	GETPROP	  9.0A
.
. Description:
.
.	The property provides an event bit mask	that can prevent specific
.	system events from being executed for an object.
.
. Objects:
.	LISTVIEW
.
. dnumnvar values:
.
$MASK_NONE	   INTEGER 4,"0x00000000" // Default
$MASK_WMCHAR	   INTEGER 4,"0x00000001" // Disable OS	default	WM_CHAR	action
$MASK_WMMOUSEWHEEL INTEGER 4,"0x00000002" // Disable OS	default	WM_MOUSEWHEEL
$MASK_WMHSCROLL	   INTEGER 4,"0x00000004" // Disable OS	default	WM_HSCROLL
$MASK_WMVSCROLL	   INTEGER 4,"0x00000008" // Disable OS	default	WM_VSCROLL
.
*------------------------------------------------------------------------------
.   OVERTYPE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	The property controls whether an edit object is	to allow data
.	entry to overtype current data for the object.
.
. Objects:
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   PAGE=dnumnvar				CREATE 
.
. Description:
.	This is	a CREATE only property.
.	This property specifies	the page to be used for	the pict object
.	when a DCX picture is used.
.
. Objects:
.	PICT
.
. dnumnvar values:
.
.	The <dnumnvar> specifies a page	value.
.
.
*------------------------------------------------------------------------------
.   PAGEPOS=dnumnvar				CREATE	SETPROP	GETPROP   10.5
.
. Description:
.	This property is used to set or obtain the current page being shown.
.
. Objects:
.       DATATABLE
.
.
*------------------------------------------------------------------------------
.   PAGESIZE=dnumnvar				CREATE	SETPROP	GETPROP   10.5
.
. Description:
.	This property is used to set or obtain the number of rows displayed 
.       on a page. The value of zero indicates that paging is not used.
.
. Objects:
.       DATATABLE
.
*------------------------------------------------------------------------------
.   PARAM=dnumnvar				CREATE	SETPROP	GETPROP   10.5
.
. Description:
.	This property is used to set or obtain a value associated with 
.       the row.
.
. Objects:
.       DATAROW
.
*------------------------------------------------------------------------------
.   PARENTWIN=<WINDOW> object			CREATE	SETPROP
.   PARENTWIN=<nvar>						GETPROP
.
. Description:
.	This property identifies a WINDOW object, which	is to be the parent
.	window for a WINDOW being created or changed.  This property can
.	be used	in a CREATE or SETPROP statement for the operation.  The
.	PARENTWIN property can also be used in a GETPROP statement to
.	retrieve the parent window handle for a	WINDOW object.	Please
.	the following about the	PARENTWIN property:
.	Note1: The SYSMENU property does not have an effect if the 
.
.	Note1: If a WINDOW object specified for	the PARENTWIN property
.	       has not been created, then an O121 error	will occur.
.
.	Note2: A WINDOW	object which has been created as a MODAL or
.	       MODELESS	type cannot be used as the parent for another
.	       window.	An O134	error will occur if a MODAL or MODELESS
.	       window is specified as a	parent window.
.
.	Note3: An O134 error will occur	if a PARENTWIN property	is used
.	       for a MODAL WINDOW object.  A parent window cannot be
.	       specified for a MODAL WINDOW object.
.
.	Note4: The PARENTWIN property can be used for any window created
.	       as a PRIMARY or MODELESS	type.
.
.	Note5: If a parent window is DESTROYed,	then any windows that
.	       the parent has ownership	of will	also be	destroyed.
.
. Objects:
.	WINDOW
.
. <Window> object operand:
.
.	The <Window> object must be a reference	to a window, which has
.	previously been	created.
.
. nvar values:
.
.	The <nvar> value retrieved by GETPROP is the window handle for a
.	parent window.
.
*------------------------------------------------------------------------------
.   PARTIALPUSH=dnumnvar				SETPROP	GETPROP	  8.6D
.
. Description:
.	When the PARTIALPUSH property is set to	$ON, the toolbar button	
.	appears	to have	its face grayed. This appearance is different from 
.	the dimmed appearance when the ENABLED property	is set to $OFF
.	since the PARTIALPUSH appearance gives a haze to the entire 
.	button face.  
.
. Objects:
.	TOOLBUTTON
.
. dnumnvar values:
.
.$OFF	    EQU	      0		     
.$ON	    EQU	      1
.
*------------------------------------------------------------------------------
.   PASSWORD[=dnumnvar]				CREATE
.
. Description:
.	This is	a CREATE only property.
.	This property specifies	that the EDITTEXT is to	have each
.	character echoed as a '*' character.  If the <dnumnvar>	value
.	is not specified, the PASSWORD property	is set to ON.
.
. Objects:
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   PASSWORDCHAR=svarslit			CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property sets or gets the password	character for an EDITTEXT
.	object.	 When a	password character is set, that	character is
.	displayed in place of the characters typed by the user.	 This
.	property is used in conjunction	with the PASSWORD property.
.
. Objects:
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. svarslit value:
.
.	String of data.	Only the first character is used or set.
.
*------------------------------------------------------------------------------
.   PERCENT=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	if a percentage	value is to be displayed
.	for the	progress object	or not.
.
. Objects:
.	PROGRESS
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1	       // Default
.
*------------------------------------------------------------------------------
.   PICTSIZEH=nvar						GETPROP
.
. Description:
.	This property is a GETPROP only	property. This retrieves the
.	horizontal size	of a picture. The value	is expressed in	pixels.
.
. Objects:
.	PICT
.
. nvar values:
.
.	The <nvar> value retrieved is the horizontal pixel size	of the picture.
.
*------------------------------------------------------------------------------
.   PICTSIZEV=nvar						GETPROP
.
. Description:
.	This property is a GETPROP only	property. This retrieves the
.	vertical size of a picture. The	value is expressed in pixels.
.
. Objects:
.	PICT
.
. nvar values:
.
.	The <nvar> value retrieved is the vertical pixel size of the picture.
.
*------------------------------------------------------------------------------
.   PICTURE=dnumnvar|svarslit|pict object    CREATE  SETPROP
.
. Description:
.	This property is supported only	for CREATE and SETPROP statements.
.	The property specifies when a picture is to replace the	text for a
.	BUTTON object.	This property is supported only	for Windows95/98/NT.
.	The allowed picture type can be	any of the normally supported PICT
.	object formats.	 This property is under	the control of the Windows
.	API and	there is no operations to resize the picture.
.
. Objects:
.	BUTTON
.
. operand values:
.
.	The <dnumnvar> value is	used to	identify a 'resource id' to be used
.	when retrieving	the picture.  This value can be	any user defined
.	resource identification	values as provided in a	resource library.
.	If the 'resource id' value is zero, then the PICTURE property is
.	removed	from the BUTTON	object and the text name for the BUTTON
.	will be	used.
.
.	The <svarslit> string specifies	a picture file name, which is to be
.	used for the BUTTON object.  The picture file name will	default	to an
.	extension of '.bmp'.  This name	supports the $MACRO and	generic
.	PLBVOL_	file name formats.  The	runtime	will use the 'PLB_PATH'
.	directories to initially locate	the file. If the file is not found
.	using the 'PLB_PATH' directories, then the file	is passed to Windows
.	to be located in the Windows directories.  If the <svarslit> string
.	is NULL, then the PICTURE property is removed from the BUTTON object
.	and the	text name for the BUTTON will be used.
.
.	The <pict> object can be specified where the <pict> object must	have
.	been previously	created.  The data for the <pict> object is used
.	for the	button.
.
*------------------------------------------------------------------------------
.   POS=dnumnvarH:dnumnvarV				SETPROP	GETPROP
.
. Description:
.	This property is a SETPROP/GETPROP only	property.
.	The POS	property specifies the starting	horizontal and vertical
.	pixel coordinate in a pict object where	the picture is to be
.	displayed.
.
. Objects:
.	PICT
.
. dnumnvar values:
.
.	The <dnumnvarH>	value is the horizontal	pixel coordinate in the	pict.
.	The <dnumnvarV>	value is the vertical pixel coordinate in the pict.
.
*------------------------------------------------------------------------------
.   PRINTER[=dnumnvar]				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	that the DATALIST object is to be filled
.	with the current Windows printer names.	 If the	<dnumnvar> value
.	is not provided, the PRINTER property is set to	ON.
.
. Objects:
.	DATALIST
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   PUSHED=dnumnvar					SETPROP	GETPROP	  8.6D
.
. Description:
.	 When the PUSHED property is set to $ON, the toolbar button 
.	 appears sunken	or inset relative to the other buttons.	
.
. Objects:
.	TOOLBUTTON
.
. dnumnvar values:
.
.$OFF	    EQU	      0		     
.$ON	    EQU	      1
.
*------------------------------------------------------------------------------
.   PUSHLIKE=dnumnvar                           CREATE SETPROP  GETPROP   9.6
.
. Description:
.        The PUSHLIKE property causes the CHECKBOX object to look and
.        act like a push button. The push like button appears to be
.        raised when it is not pushed or checked. It appears to be
.        sunken when it is pushed or checked. 
.
.	 The PUSHLIKE property causes the RADIO object to look and act
.	 like a push button. The push like button appears to be raised
.        when it is not pushed or checked. It appears to be sunken when
.        it is pushed or checked.
.
. Objects:
.       CHECKBOX
.	RADIO
.
. dnumnvar values:
.
.$OFF	    EQU	      0		//Default		     
.$ON	    EQU	      1
.
*------------------------------------------------------------------------------
.   READONLY[=dnumnvar]				CREATE		GETPROP
.
. Description:
.	This property specifies	that the edit object is	a read only
.	object.	 The user can place the	caret into the edit object
.	to cut/copy data, however, the current edit data can not
.	be changed by the user.	 If the	<dnumnvar> value is not	specified,
.	the READONLY property is turned	on.
.
.	Note1: The CREATE statement is required	to invoke the READONLY
.	       property.  It is	not possible to	invoke the READONLY property
.	       by a SETPROP statement.
.
. Objects:
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values:
.
.$OFF	      EQU	0	       Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   RESIZE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	if a picture is	to be resized to fit
.	pict object rectangle coordinates.
.
. Objects:
.	PICT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   RESOURCE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is a CREATE/SETPROP/GETPROP only property.
.	The RESOURCE property allows a resource	id to be controlled for
.	supported objects.
.
.	When a resource	id is specified	for an IMAGELIST object, then the
.	image/picture specified	by the resource	id is segmented	and replaces
.	all images for the IMAGELIST object.
.
. Objects:
.	ICON
.	IMAGELIST							  9.0
.	PICT
.
. dnumnvar values:
.
.	The <dnumnvar> value is	valid resource id, which can be	found
.	in a resource DLL or resources loaded for a PLFORM.
.
*------------------------------------------------------------------------------
.   RIBDLL=svarslit                             CREATE SETPROP  GETPROP   9.6
.
. Description: (Comctl32 Version 6 Required)
.       This property can be used in a CREATE, GETPROP, or SETPROP
.       instruction. The RIBDLL specifies the name of an external dll
.       that contains ribbon resources.
.
. Objects:
.       WINDOW
.
*------------------------------------------------------------------------------
.   RIBNAME=svarslit                            CREATE SETPROP  GETPROP   9.6
.
. Description: (Comctl32 Version 6 Required)
.       The RIBMODE property specifies a mode value that controls
.       the behavior for displaying a ribbon resource.
.
. Objects:
.       WINDOW
.
*------------------------------------------------------------------------------
.   RIBMODE=dnumnvar                            CREATE SETPROP  GETPROP   9.6
.
. Description:
.	The RIBMODE property specifies a mode value that controls the
.	behavior for displaying a ribbon resource.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
$ShowRibModeAll      EQU   0	       // Default
$ShowRibModeDockOnly EQU   1
.
*------------------------------------------------------------------------------
.   RIGHT[=dnumnvar]				CREATE
.
. Description:
.	The RIGHT property specifies that the text is to be right justified 
.	horizontally for the object.  The property is replaced by 
.	the ALIGNMENT property.	 The ALIGNMENT property	is to be used
.	for performing SETPROP and GETPROP operations.
.
.	If the syntax form is used where the <dnumnvar>	value is not
.	specified, this	indicates that the RIGHT property is to	be
.	turned on.
.
.	Also note that if the RIGHT property is	turned off, this causes
.	the text output	to be justified	to the left.
.
. Objects:
.	EDITTEXT
.	STATTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   RIGHTBUTTON[=dnumnvar]			CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	whether	the right mouse	button can be
.	used to	cause an event or not.	If the <dnumnvar> value
.	is not provided, the RIGHTBUTTON property is turned on.
.
. Objects:
.	FLOATMENU
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   RIGHTMARGIN=dnumnvar			CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used in set or	get the	right margin of	an edit
.	object.
.
. Objects:
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
*------------------------------------------------------------------------------
.   RTF=svarslit					SETPROP	GETPROP	  9.0B
.
. Description:
.	This property gets or sets the object contents as Rich Text 
.	Format (RTF) formatted text.
.
. Objects:
.	RICHEDITTEXT
.
. svarslit value:
.
.	String of RTF data.
. 
*------------------------------------------------------------------------------
.   RUNNAME=svarslit					SETPROP	GETPROP	  8.6D
.
. Description:
.	This property specifies	the run-time name of the object. It is used
.	when accessing an object from the ITEMS, PANELS	or BUTTONS collection.
.
. Objects:
.	MENUITEM							  9.0
.	STATUSPANEL
.	TOOLBUTTON
.
. svarslit value:
.
.	String containing a name.
.
*------------------------------------------------------------------------------
.   SCALE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	a percentage by	which a	picture	object
.	is scaled.
.
. Objects:
.	PICT
.
. dnumnvar values:
.
.	The <dnumnvar> value is	percentage value.
.
*------------------------------------------------------------------------------
.   SCROLLBAR[=dnumnvar]			CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	what type of scrollbars	are to be provided
.	for a EDITTEXT,	PICTURE, or WINDOW object.  If the <dnumnvar> value
.	is not provided, the SCROLLBAR property	is set to $SCRBOTH.
.
. Objects:
.	COMBOMBOX							  8.7C
.	DATALIST							  8.7C
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.	PICT
.	WINDOW
.
. dnumnvar values:
.
.$NONE	      EQU	0	       // Default
$SCRBOTH      EQU	1
$SCRHORZ      EQU	2
$SCRNONE      EQU	3
$SCRVERT      EQU	4
.
*------------------------------------------------------------------------------
.   SCROLLHIDE=dnumnvar				CREATE		GETPROP
.
. Description:
.	This property is used to indicate if scrollbars	should be hidden or
.	disabled if no required. If the	value is $OFF, scrollbars are disabled.
.	A value	of $ON causes the scrollbars to	be hidden.
.
. Objects:
.	COMBOBOX
.	DATALIST
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   SCROLLSIZEMODE=dnumnvar			CREATE	SETPROP	GETPROP	  9.2C
.
. Description:
.	This property can be used in a CREATE instruction to cause a scrollbar
.	size to	conform	to the user specified sizes.
.
. Objects:
.	HSCROLLBAR
.	VSCROLLBAR
.
. dnumnvar values:
.
.	The value is a logical unit as specified by the	user.
.
$SCROSDEFAULT EQU	0	  // Default
$SCRUSERMODE  EQU	1
.
*------------------------------------------------------------------------------
.   SELALIGN=dnumnvar					SETPROP	GETPROP	  9.0B
.
. Description:
.	This property allows the user to specify the alignment of the
.	selected text. The allowed values are as follows:
.
.	$PFA_LEFT	- The text is left aligned.
.
.	$PFA_RIGHT	- The text is right aligned.
.
.	$PFA_CENTER	- The text is center aligned.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
$PFA_LEFT	EQU	1
$PFA_RIGHT	EQU	2
$PFA_CENTER	EQU	3
.
*------------------------------------------------------------------------------
.   SELBULLET=dnumnvar					SETPROP	GETPROP	  9.0B
.
. Description:
.	This property is used to set or	get a value indicating
.	whether	the bullet style is applied to the current selection
.	or insertion point.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   SELCHAROFFSET=dnumnvar				SETPROP	GETPROP	  9.0B
.
. Description:
.	This property specifies	the offset from	the baseline of	the text
.	in the current selection or insertion point.
.
.	If the value is	greater	than zero, the text is shown as	a superscript.
.	If the value is	less than zero,	the text is shown as a subscript.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.     The <dnumnvar> value is specified	in pixels.
.
*------------------------------------------------------------------------------
.   SELCOLOR=dnumnvar|color object			SETPROP	GETPROP	  9.0B
.
. Description:
.	This property is used to set or	get the	color for
.	the current selection or insertion point.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.	See the	BDRCOLOR property for the color	equate values.
.
*------------------------------------------------------------------------------
.   SELECTALL=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	The property controls whether all of the data for an edit object is to
.	be selected or not selected when the object gains the focus.  If this
.	property is set	to ON, then all	of the data in the object is
.	automatically highlighted when the object gains	the focus.
.
. Objects:
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.  SELECTED=dnumnvar    				SETPROP	GETPROP	 10.5
.
. Description:
.	This property sets or clears the selected state of the row.
.
. Objects:
.       DATAROW						  
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   SELECTEDRTF=svarslit				SETPROP	GETPROP	  9.0B
.
. Description:
.	This property gets or sets the currently selected Rich Text
.	Format (RTF) formatted text.
.
. Objects:
.	RICHEDITTEXT
.
. svarslit value:
.
.	String of RTF data.
.
*------------------------------------------------------------------------------
.   SELFONTBOLD=dnumnvar				SETPROP	GETPROP	  9.0B
.
. Description:
.	This property is used to set or	get a value indicating 
.	whether	the BOLD style is applied to the current selection 
.	or insertion point.
.
. Objects:
.	RICHEDITTEXT							 
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1
*------------------------------------------------------------------------------
.   SELFONTCHARSET=dnumnvar				SETPROP	GETPROP	  9.0B
.
. Description:
.	This property is used to set or	get the	character set
.	of the current selection or insertion point.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
$ANSI_CHARSET		EQU	0
$DEFAULT_CHARSET	EQU	1
$SYMBOL_CHARSET		EQU	2
$MAC_CHARSET		EQU	77
$SHIFTJIS_CHARSET	EQU	128
$HANGEUL_CHARSET	EQU	129
$HANGUL_CHARSET		EQU	129
$GB2312_CHARSET		EQU	134
$CHINESEBIG5_CHARSET	EQU	136
$OEM_CHARSET		EQU	255
$JOHAB_CHARSET		EQU	130
$HEBREW_CHARSET		EQU	177
$ARABIC_CHARSET		EQU	178
$GREEK_CHARSET		EQU	161
$TURKISH_CHARSET	EQU	162
$VIETNAMESE_CHARSET	EQU	163
$THAI_CHARSET		EQU	222
$EASTEUROPE_CHARSET	EQU	238
$RUSSIAN_CHARSET	EQU	204
.
*------------------------------------------------------------------------------
.   SELFONTITALIC=dnumnvar				SETPROP	GETPROP	  9.0B
.
. Description:
.	This property is used to set or	get a value indicating
.	whether	the ITALIC style is applied to the current selection
.	or insertion point.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1
*------------------------------------------------------------------------------
.   SELFONTNAME=svarslit				SETPROP	GETPROP	  9.0B
.
. Description:
.	This property gets or sets the font name for the current
.	selection or insertion point.
.
. Objects:
.	RICHEDITTEXT
.
. svarslit value:
.
.	Font name.
.
*------------------------------------------------------------------------------
.   SELFONTSIZE=dnumnvar				SETPROP	GETPROP	  9.0B
.
. Description:
.	This property gets or sets the size of the font	for the	current
.	selection or insertion point.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.     The <dnumnvar> value is specified	in tenths of a point.
.
*------------------------------------------------------------------------------
.   SELFONTUNDER=dnumnvar				SETPROP	GETPROP	  9.0B
.
. Description:
.	This property is used to set or	get a value indicating
.	whether	the UNDERLINE style is applied to the current selection
.	or insertion point.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1
*------------------------------------------------------------------------------
.   SELGROUPID=nvar						GETPROP
.
. Description:
.	This property is a GETPROP only	property.  This	property returns
.	the OBJECTID value for a RADIO object which is currently selected
.	within a radio group identified	by a GROUPID value.  If	this
.	property is used for a RADIO object, which is NOT included in any
.	radio group, then the single RADIO object is processed as a radio
.	group of one and the OBJECTID of the single RADIO object is
.	returned when the RADIO	object is selected.  In	all cases, a value
.	of zero	is returned when no RADIO object is selected for a radio
.	group.
.
. Objects:
.	RADIO
.
. nvar values:
.
.	      The OBJECTID is returned in the {nvar} variable for a 
.	      selected RADIO object in a radio group.
.
*------------------------------------------------------------------------------
.   SELHANGINDENT=dnumnvar				SETPROP	GETPROP	  9.0B
.
. Description:
.	This property specifies	the distance between the left edge
.	of the first text line in the selected paragraph and the
.	left edge of all subsequent lines in the same paragraph.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.     The <dnumnvar> value is specified	in pixels.
.
*------------------------------------------------------------------------------
.   SELLENGTH=dnumnvar	  (SLIDER)		CREATE	SETPROP	GETPROP
.   SELLENGTH=dnumnvar	  (RICHEDITTEXT)		SETPROP	GETPROP	  9.0B
.
. Description for SLIDER:
.	This property specifies	the number of units to highlight in
.	the slider object view when the	SELRANGE property is set to ON.
.	It is recommended that the SELLENGTH value be defined in the
.	range specified	by the MAX and MIN property values.
.
.	Note1:	The highlighted	output does not	occur when the SELLENGTH
.		property value plus the	SELSTART value is greater than
.		32767.	The highlighted	output may not occur if	'nvar'
.		value is negative.
.
. Description for RICHEDITTEXT:						  9.0B
.	This property is used to set or	get the	length of the current
.	selection. This	property is only allowed in a GETPROP and SETPROP
.	for a RICHEDITTEXT object.
.
. Objects:
.	SLIDER
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values SLIDER:
.
.	The <dnumnvar> value is	logical	user specified units.
.
. dnumnvar values for RICHEDITTEXT:					  9.0B
.
.     The <dnumnvar> value is specified	in characters.
.
*------------------------------------------------------------------------------
.   SELPROTECTED=dnumnvar				SETPROP	GETPROP	  9.0B
.
. Description:
.	This property is used to set or	get a value indicating
.	whether	the current selection is protected from
.	being changed.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1
*------------------------------------------------------------------------------
.   SELRANGE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	The property specifies if a highlighted	selection is to	be 
.	applied	to the slider object.  When this PROPERTY it turned
.	ON, the	slider object uses the SELSTART	and SELLENGTH
.	values to define the highlighted selection output.
.
. Objects:
.	SLIDER
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   SELRIGHTINDENT=dnumnvar				SETPROP	GETPROP	  9.0B
.
. Description:
.	This property specifies	the distance between the right edge
.	of the object and the right edge of the	text that is selected
.	or added at the	current	insertion point.
.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.     The <dnumnvar> value is specified	in pixels.
.
*------------------------------------------------------------------------------
.   SELSTART=dnumnvar	(SLIDER)		CREATE	SETPROP	GETPROP
.   SELSTART=dnumnvar	(RICHEDITTEXT)			SETPROP	GETPROP	  9.0B
.
. Description for SLIDER:
.	This property specifies	the starting logical unit from which
.	the slider object begins the highlighted output	when the SELRANGE
.	property is set	to ON.
.
.	Note1:	The highlighted	output does not	occur when the SELLENGTH
.		property value plus the	SELSTART value is greater than
.		32767.	The highlighted	output may not occur if	'nvar'
.		value is negative.
.
. Description for RICHEDITTEXT:						  9.0B
.	This property is used to set or	get the	start of the current
.	selection. This	property is only allowed in a GETPROP and SETPROP
.	for a RICHEDITTEXT object.
.
. Objects:
.	SLIDER
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values for SLIDER:
.
.	The <dnumnvar> value is	logical	user specified unit.
.
. dnumnvar values for RICHEDITTEXT:					  9.0B
.
.     The <dnumnvar> value is specified	in characters.
.
*------------------------------------------------------------------------------
.   SELTEXT=svarslit					SETPROP	GETPROP	  8.7C
.
. Description:
.	This property gets or replaced the selected text. It works in
.	conjunction with the TEXTOUTCONV property.
.
. Objects:
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. svarslit value:
.
.	String of data.
.
*------------------------------------------------------------------------------
.   SELTYPE=nvar						GETPROP	  9.0B
.
. Description:
.	This property is a GETPROP only	property.  The value
.	return is the type of selection.
.
. Objects:
.	RICHEDITTEXT
.
. nvar values:
.
$SEL_EMPTY		EQU	0x0000
$SEL_TEXT		EQU	0x0001
$SEL_OBJECT		EQU	0x0002
$SEL_MULTICHAR		EQU	0x0004
$SEL_MULTIOBJECT	EQU	0x0008
.
*------------------------------------------------------------------------------
.   SEPARATOR=dnumnvar					SETPROP	GETPROP	  9.0
.
. Description:
.	This property is used to indicate that a menu item is to be shown as
.	a separator line.
.
. Objects:
.	MENUITEM
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   SHAPE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the type of shape to be	output for the
.	shape object.  If the SHAPE property is	invalid, the shape
.	object defaults	to a rectangle output.
.
. Objects:
.	SHAPE
.
. dnumnvar values:
.
.$NONE	      EQU	0	       // Same as $RECTANGLE
$OVAL	      EQU	1
$RECTANGLE    EQU	2	       // Default
$RNDRECT      EQU	3
.
*------------------------------------------------------------------------------
.   SHIELD=dnumnvar                             CREATE SETPROP  GETPROP   9.6
.
. Description: (Comctl32 Version 6 Required)
.       The SHIELD property specifies whether an elevation icon is to be
.       displayed for a button or command link. If this property is not
.       used, the elevation icon is not displayed. The elevation icon is
.       the shield icon that is presented when the administrator privileges
.       are required. If a value of 1 is specifies that the OS elevation
.       icon is to be presented. For a value of 0, the elevation icon is
.       not presented.
.
. Objects:
.	BUTTON
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   SHIFT=dnumnvar			     See Objects:
.
. Description:
.	This property defines the number of units to move the slider
.	thumb when the mouse is	clicked	in the object slide area.
.	This also occurs when the page up or page down keys are	entered.
.
. Objects:
.	HSCROLLBAR					SETPROP	GETPROP
.	SLIDER					CREATE	SETPROP	GETPROP
.   	VSCROLLBAR					SETPROP	GETPROP
.
. dnumnvar values:
.
.	The value is a logical unit as specified by the	user.
.
*------------------------------------------------------------------------------
.   SHORTCUT=dnumnvar					SETPROP	GETPROP	  9.0
.
. Description:
.	This property is used to assign	a short	cut key	to a menu item.
.
. Objects:
.	MENUITEM
.
. dnumnvar values:
.
.	0 indicates no short cut key.
.	1   - 15  indicates F1-F15 function keys.
.	16  - 30  indicates shift F1-15	function keys.
.	31  - 40  indicates control 0-9.
.	41  - 66  indicates control A-Z.
.	67  - 81  indicates control F1-F15 function keys.
.	82  - 91  indicates control shift 0-9.
.	92  - 117 indicates control shift A-Z.
.	118 - 132 indicates control shift F1-F15 function keys.
.
*------------------------------------------------------------------------------
.  SHOWCHECKBOX=dnumnvar			CREATE		GETPROP	  9.0
.
. Description:
.	This property is used to indicate if the EDITDATETIME object should
.	show a checkbox	in the control.
.
. Objects:
.	EDITDATETIME
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
*------------------------------------------------------------------------------
.   SHOWPANEL=dnumnvar				CREATE	SETPROP	GETPROP	  8.6D
.
. Description:
.	This property indicates	whether	any STATUSPANEL	objects	that
.	have been added	to the object are displayed. If	set to $OFF,
.	the TEXT property may be used to set the text for the STATUSBAR
.	object.
.
. Objects:
.	STATUSBAR
.
. dnumnvar values:
.
.$OFF	    EQU	      0
.$ON	    EQU	      1
.
*------------------------------------------------------------------------------
.   SHOWTIPS=dnumnvar				CREATE			  8.6D
.
. Description:
.	This property indicates	whether	ToolTips should	be shown
.	over TOOLBUTTON	objects.
.
. Objects:
.	TOOLBAR
.
. dnumnvar values:
.
.$OFF	    EQU	      0
.$ON	    EQU	      1
.
*------------------------------------------------------------------------------
.  SHOWUPDOWN=dnumnvar				CREATE		GETPROP	  9.0
.
. Description:
.	This property is used to indicate if the EDITDATETIME object should
.	display	a drop-down month calendar or an up-down control. If the
.	property is set	to $OFF, the drop-down month calendar is shown.	If
.	set to $ON, the	up-down	control	is shown.
.
.	If the FORMAT property is set to $DTFORMATTIME,	an up-down control
.	is always shown.
.
. Objects:
.	EDITDATETIME
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.  SHOWWEBMENU=dnumnvar				CREATE	SETPROP	GETPROP	  9.7
.
. Description:
.	This property is used for a WINDOW object to control whether the MENU,
.	SUBMENU, and FLOATMENU objects are to be made visible when a
.	Plb Web Server runtime is being used. The default value for this
.	property is 0 which allow all menus to be used as normally expected.
.	This property can have a value of 0 to 3.
.	
. Objects:
.	FLOATMENU
.	MENU
.	SUBMENU
.
. dnumnvar values:
.
$ShowMenu          EQU       0       // Default
$ShowMenuNone      EQU       1       // No menus are made visible
$ShowMenuAllOn     EQU       2       // Show all menus
$ShowMenuInBrowser EQU       3       // Show only in browser
.
*------------------------------------------------------------------------------
.   SIZE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the point size for a font object.
.
. Objects:
.	FONT
.
. dnumnvar values:
.
.	The <dnumnvar> value is	a point	size for a font.
.
*------------------------------------------------------------------------------
.   SIZEGRIP=dnumnvar				CREATE	SETPROP	GETPROP	  8.6D
.
. Description:
.	This property enables or disables the drawing of a sizing grip
.	in the lower-right corner of a STATUSBAR object. The sizing grip 
.	is to provide an indication to the user	when a form is resizable.
.
. Objects:
.	STATUSBAR
.
. dnumnvar values:
.
.$OFF	      EQU	0	       
.$ON	      EQU	1
.
.
*------------------------------------------------------------------------------
.   STRIPED=dnumnvar				CREATE	SETPROP	GETPROP   10.5
.
. Description:
.	This property allows zebra-stripes to be applied to the table.
.
. Objects:
.       DATATABLE
.
. dnumnvar values:
.
.$OFF	      EQU	0	       
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   SWITCH=dnumnvar				CREATE	SETPROP	GETPROP	  10.5
.
. Description:
.       The SWITCH property is only used when a CHECKBOX object has
.       been created as a web object using the WebView mode. This property
.       uses a Bootstrap 5 'switch class' to show a toggle switch for a
.       web checkbox object.
.
. Objects:
.	CHECKBOX (WebView Only)
.
. dnumnvar values:
.
.$OFF	      EQU	0	//No toggle switch by default.      
.$ON	      EQU	1	//Toggle switch used.
.
*------------------------------------------------------------------------------
.   SIZEMODE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is used to control how the OLE insertable	object is 
.	displayed within an OLE	container object. It may be one	of:
.
.	$SIZEMODEAUTO	- The OLE container object window is re-sized to 
.			  the size of the OLE insertable object. 
.	$SIZEMODECLIP	- The OLE insertable object is clipped to the size of
.			  the OLE container object window. 
.	$SIZEMODESCALE	- The OLE insertable object is evenly scaled for 
.			  a best fit in	the OLE	container object window. 
.	$SIZEMODESTRETCH - The OLE insertable object is	scaled to fully	fit
.			  in the OLE container object window. 
.
. Objects:
.	CONTAINER
.
. dnumnvar values:
.
$SIZEMODEAUTO	 EQU	  1		
$SIZEMODECLIP	 EQU	  2		// Default
$SIZEMODESCALE	 EQU	  3
$SIZEMODESTRETCH EQU	  4
.
*------------------------------------------------------------------------------
.   SORTED[=dnumnvar]				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	that the items in the DATALIST object
.	are to be sorted.  If the <dnumnvar> value is not provided,
.	the SORTED property is turned ON.
.
.	Note1:	When the SORTED	property is used, Windows controls the
.		sorting	method.	 The Windows method is to sort the
.		item name field	alphabetically starting	with the first
.		character.  Windows does not support any alternate sorting
.		methods.
.
.	Note2:	For a DATALIST,	the SORTED property can	only be	used in
.		a CREATE or GETPROP operation.
.
. Objects:
.	COMBOBOX
.	DATALIST
.	POPUPMENU ( OBSOLETE )
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   SORTHEADER=dnumnvar				CREATE		GETPROP
.
. Description:
.	This property indicates	that column headers will act like buttons.
.	If set to $ON, then the	user can click on a column header and the
.	program	will receive a $COLCLICK event.	 This provides a means
.	where a	user application can determine which column has	been
.	selected by a user with	the intended action being that the
.	application can	sort the data using the	column data.
.
.	Note1:	Neither	Windows	nor the	runtime	automatically sorts the
.		data for a selected column.  This is the responsibility
.		of the user application	program.
.
. Objects:
.	LISTVIEW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   SORTORDER=dnumnvar				CREATE		GETPROP
.
. Description:
.	This property indicates	the default sort order of items	in the
.	first/left most	column.	This property can be set to one	of the
.	following:
.
.	$SORTASC  - Sort item text labels in a ascending fashion.
.	$SORTDSC  - Sort item text labels in a descending fashion.
.	$SORTNONE - No default sort order.
.
. Objects:
.       DATATABLE                                                        10.5
.	LISTVIEW
.
. dnumnvar values:
.
$SORTASC      EQU	1
$SORTDSC      EQU	2
$SORTNONE     EQU	3	       // Default
.
*-----------------------------------------------------------------------------
.   SOURCEDOC=svarslit				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is the filename name used	as data	for the	OLE insertable
.	object.	If set,	the current OLE	insertable object in a OLE container 
.	object will be replaced	by a OLE insertable object created from	the
.	data in	the file.
.
. Objects:
.	CONTAINER
.
. svarslit values:
.
.	The <svarslit> is a filename.
.
*------------------------------------------------------------------------------
.   SPECIALMENU=dnumnvar				SETPROP	GETPROP	  9.0
.
. Description:		
.	This property is used to assign	a special menu action to a menu	item.
.
. Objects:
.	MENUITEM
.
. dnumnvar values:
.
$SPCMENUNONE	   EQU 0
$SPCMENUCOPY	   EQU 1
$SPCMENUCUT	   EQU 2
$SPCMENUDELETE	   EQU 3
$SPCMENUPASTE	   EQU 4
$SPCMENUSELALL	   EQU 5
$SPMENUUNDO	   EQU 6
.
*-----------------------------------------------------------------------------
.   STATIC[=dnumnvar]				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	that the object	is used	for output only
.	purposes.  The object with this	property can not get the focus and not
.	cut/copy operations can	be perform.
.
. Objects:
.	EDITNUMBER							  9.0F
.	EDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   STRIKE=dnumnvar				CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property specifies	that the font should be	displayed with a line
.	through	the center of the font.	When the <dnumnvar> value is
.	not provided, this indicates that the STRIKE property is turned	on.
.
. Objects:
.	FONT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
*------------------------------------------------------------------------------
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT	CREATE	SETPROP	GETPROP
.
. Description:
.	The STYLE property specifies when an object should
.	have a 3D look or a non-3D look.  The various forms of STYLE
.	defines	that an	object can have	presentations as follows:
.
.	  3DOFF	- Object does not have a 3D look.
.	  3DON	- Object has a 3D sunken look.
.	  3DFLAT- Object has a 3D flat look.
.	  3DOUT	- Object has a 3D outward look.
.
.	Note1: Some objects are	limited	to presentations described as
.	       3DON or 3DOFF only.  For	these objects the user should
.	       use the APPEARANCE property and not the STYLE property.
.
. Objects:
.	CHECKBOX		(See Note1:)
.	CHECKGRP		(See Note1:)
.	COMBOBOX		(See Note1:)
.	CONTAINER
.	DATALIST		(See Note1:)
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	GROUPBOX
.	MOVIE
.	PICT
.	POPUPMENU ( OBSOLETE )	(See Note1:)
.	PROGRESS
.	RADIOGRP		(See Note1:)
.	RADIO			(See Note1:)
.	STATTEXT
.	WINDOW			(See Note1:)
.
. dnumnvar values:
.
$DEFAULT      EQU	0	       // Default
$3DON	      EQU	1
$3DOFF	      EQU	2
$3DFLAT	      EQU	3
$3DOUT	      EQU	4
.
*------------------------------------------------------------------------------
.   SUBMENU={submenu}					SETPROP	GETPROP	  9.0
.
. Description: 
.	This property is used to assign	a SUBMENU object to a menu item.
.
. Objects:
.	MENUITEM
.
*------------------------------------------------------------------------------
.   SYSMENU=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	whether	a window object	should output
.	a sysmenu or not.
.
.	Note1: The SYSMENU property does not have an effect if the 
.	       CAPTION property	is set to $OFF for a MODAL or MODELESS
.	       window type.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0
.$ON	      EQU	1	       // Default
.
*------------------------------------------------------------------------------
.   TABFIXHTH=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the height in pixels for the 
.	TABCONTROL labels.  This property only takes affect when the
.	TABWTHSTYLE property is	set to FIXED.
.
. Objects:
.	TABCONTROL
.
. dnumnvar values:
.
.	The <dnumnvar> value is	the number of pixels for label height.
.
*------------------------------------------------------------------------------
.   TABFIXWTH=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the width in pixels for	the 
.	TABCONTROL labels.  This property only takes affect when the
.	TABWTHSTYLE property is	set to FIXED.
.
. Objects:
.	TABCONTROL
.
. dnumnvar values:
.
.	The <dnumnvar> value is	the number of pixels for label width.
.
*------------------------------------------------------------------------------
.   TABID=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the location of	this object in the
.	tabbing	order sequence.	 If the	TABID property is not used, the
.	object is assigned an internal tabbing order value, which is 
.	determined by the order	that objects are created and an	
.	initial	TABID value specified for the window of	the object.  If	the
.	TABID property id is specified,	then the value of the TABID
.	determines the location	of the object in the tabbing sequence.
.	The tabbing sequence processes from lower TABID	valued objects
.	to higher TABID	valued objects as the TAB key is entered.
.
.	Note1:	The *NODEFTABID=OFF in the SETMODE statement can be
.		used to	exclude	any object with	an internally assigned
.		tabid from the tabbing sequence.
.
. Objects:
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	LISTVIEW
.	POPUPMENU ( OBSOLETE )
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
. 	SLIDER
.	STATUSBAR							  9.1A
.	TABCONTROL
.	TREEVIEW
.	VSCROLLBAR
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	a user-specified value to tabbing order.
.
*------------------------------------------------------------------------------
.   TABLABEL=svarslit				CREATE	SETPROP	GETPROP
.
. Description:
.	This property provides the data	items used to generate the
.	TABCONTROL labels.  The	data provided in the <svarslit>	is
.	set of items separated by semicolon characters.	 If the	TABLABEL 
.	is not specified or the	<svarslit> is NULL, then the TABCONTROL
.	will not have any tab labels.
.
. Objects:
.	TABCONTROL
.
. svarslit values:
.
.	The <svarslit> is a list of items separated by a semicolon.
.
*------------------------------------------------------------------------------
.   TABSTOPS=svarslit				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	a data string, which is	composed of tabstop
.	location values	separated by semicolon characters.  See	the manual
.	for detailed description.
.
. Objects:
.	DATALIST
.
. svarslit values:
.
.	The <svarslit> data string is tabstop location values separated
.	by semicolons.
.
*------------------------------------------------------------------------------
.   TABSTYLE=dnumnvar				CREATE	SETPROP	GETPROP    9.4C
.
. Description:
.       This property specifies whether the TABCONTROL tabs are to be
.       located at the top, left, bottom, or right of the control.
.
. Objects:
.	TABCONTROL
.
. dnumnvar values:
.
$TC_TOP		EQU	0 (Default)
$TC_BOTTOM	EQU	1
$TC_LEFT	EQU	2
$TC_RIGHT	EQU	3
*------------------------------------------------------------------------------
.   TABWTHSTYLE=dnumnvar			CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the look of the	labels.	If the $FIXED 
.	value is used, the TABFIXHTH and TABFIXWTH properties determine
.	the height and width of	the labels. The	$JUST value causes any
.	multiple row TABCONTROL	to size	the labels evenly to fill each row.
.
. Objects:
.	TABCONTROL
.
. dnumnvar values:
.
.$NONE	      EQU	0
$FIXED	      EQU	1
$JUST	      EQU	2
$NOJUST	      EQU	3
.
*------------------------------------------------------------------------------
.  TAG=dnumnvar						SETPROP	GETPROP	  8.6D
.
. Description:
.	This property is used to identify a MENUITEM or	TOOLBUTTON object when
.	a parent object	receives a $ITEMCLICK event.
.
. Objects:
.	MENUITEM							  9.0
.	TOOLBUTTON
.
. dnumnvar values:
.
.	The <dnumvar> is a user-specified number to identify an	object.
.
*------------------------------------------------------------------------------
.   TEXT=svarslit					SETPROP	GETPROP	  8.6D
.				  EDITNUMBER	CREATE	SETPROP	GETPROP
.				  LABELTEXT	CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the text to display in the object. If
.	the object is an EDITTEXT, the property	works in conjunction
.	with the TEXTOUTCONV property.
.
.	For a LABELTEXT	object the TEXT	data length up to 4096 bytes is
.	allowed	for a CREATE operation.
.
. Objects:
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	LABELTEXT							  9.0
.	MENU								  9.0
.	MENUITEM							  9.0
.	RICHEDITTEXT							  9.0B
.	STATTEXT
.       STATUSBAR
.	STATUSPANEL
.	TOOLBUTTON
.
. svarslit value:
.
.	String of data.
.
*------------------------------------------------------------------------------
.  TEXTALIGN=dnumnvar				CREATE	SETPROP	GETPROP	  8.6D
.
. Description:
.	This property allows the user to specify the alignment of
.	text on	all TOOLBUTTON objects in a TOOLBAR object.  The possible 
.	alignment values are as	follows:
.
.	TextAlignRight	- Text is positioned to	the right of any image.
.	TextAlignUnder	- Text is positioned under any image.
.
. Objects:
.	TOOLBAR
.
. dnumnvar values:
.
$TEXTALIGNRIGHT	EQU	1
$TEXTALIGNUNDER	EQU	2	(default)
.
*------------------------------------------------------------------------------
.   TEXTOUTCONV=dnumnvar			CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used to control the conversion	of text	from
.	an EDITTEXT object, when text is obtain	by a GETPROP or	GETITEM
.	statement. It must be one of:
.
.	$CONVDEFAULT	- The conversion default to the	global runtime
.			  conversion.  The default global runtime conversion
.			  is $CONVEOL.
.	$CONVEOL	- The CR/LF combinations are replaced with 0x7F
.			  characters.
.	$CONVEXPAND	- The CR/LF combinations are replaced with 0x7F
.			  characters.
.			  Tab characters are expanded into spaces.
.	$CONVRAW	- No conversion	is done.
.	$CONVEXPAND	- The CR/LF combinations are replaced with 0x7F
.			  characters.
.			  All characters below a space in value	are turned
.			  into a single	space character.
.
. Objects:
.	EDITTEXT
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values:
.
$CONVDEFAULT	EQU	1
$CONVEOL	EQU	2
$CONVEXPAND	EQU	3
$CONVRAW	EQU	4
$CONVSPACES	EQU	5
.
*------------------------------------------------------------------------------
.   THEME=svarslit                              CREATE SETPROP  GETPROP   9.6
.
. Description: (Comctl32 Version 6 Required)
.       The THEME property allows the visual style of another Windows
.       application to be used for a control in place of the default
.       visual style. If the <svarslit> is NULL, the default visual
.       style is used. The Windows "Explorer" application is a documented
.       alternative theme that can be specified at this time. This
.       property can be used for future alternative visual styles as they
.       are made available by Microsoft. Note, that a visual style for
.       any one GUI object may not have a visual affect as applied by an
.       alternative visual style.
.
. Objects:
.	BUTTON
.       CHECKBOX
.       COMBOBOX
.       EDITTEXT
.       LISTVIEW
.       RADIO
.       TREEVIEW
.       WINDOW
.
*------------------------------------------------------------------------------
.   TICKFREQ=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the frequency at which tick marks are
.	applied	to the slider object output.  The <dnumnvar> value for
.	this property should be	in the range of	the MIN	and MAX	values.
.
. Objects:
.	SLIDER
.
. dnumnvar values:
.
.	The <dnumnvar> is a user logical unit value.
.
*------------------------------------------------------------------------------
.   TICKSTYLE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the type of look that a	slider object
.	takes on.  This	property causes	tick unit marks	
.	to be placed on	either side of the slide thumb control;
.	on both	sides of the slide thumb control; or no	tick
.	mark output at all.  The number	of tick	units to be applied
.	depend on the MAX, MIN,	and TICKFREQ property values.
.
.	Note1: Values other than those shown for <dnumnvar> result in
.	       no tick mark output.
.
. Objects:
.	SLIDER
.
. dnumnvar values:
.
.$NONE	      EQU	3
$TICKBOTH     EQU	1
$TICKBOTTOM   EQU	2
$TICKRIGHT    EQU	2
$TICKNONE     EQU	3
$TICKTOP      EQU	4
$TICKLEFT     EQU	4
.
*------------------------------------------------------------------------------
.   TITLE=svarslit				CREATE	SETPROP	GETPROP
.
. Description:
.	This property allows a title to	be specified for the supported
.	objects.
.
. Objects:
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.       DATACOLUMN                                                       10.5
.	GROUPBOX
.	RADIOGRP
.	WINDOW
.
. svarslit values:
.
.	The <svarslit> variable	is a title string.
.
*------------------------------------------------------------------------------
.   TITLEBGGCOLOR=dnumnvar|color object		CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property allows the user program to specify the color to
.	be used	in the drop down calendar as the background color displayed
.	in the calendar's title.  The parameter	description is the same	as
.	for the	BDRCOLOR property.
.
. Objects:
.	EDITDATETIME
.
. dnumnvar values:
.
.	See the	BDRCOLOR property for the color	equate values.
.
*------------------------------------------------------------------------------
.   TITLEFGCOLOR=dnumnvar|color	object		CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property allows the user program to specify the color to
.	be used	in the drop down calendar to color used	to display text	
.	within the calendar's title. The parameter description is the 
.	same as	for the	BDRCOLOR property.
.
. Objects:
.	EDITDATETIME
.
. dnumnvar values:
.
.	See the	BDRCOLOR property for the color	equate values.
.
*------------------------------------------------------------------------------
.   TOOLTIP=svarslit				CREATE	SETPROP	GETPROP
.
. Description:	    
.	This property allows a user specified string to	be provided in a
.	tooltip	window for an object.
.
. Objects:
.	ANIMATE								  9.0
.	BUTTON
.	CHECKBOX
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	GROUPBOX
.	HSCROLLBAR
.	ICON
.	LABELTEXT							  9.0
.	LISTVIEW
.	MREGION
.	MOVIE
.	PICT
.	STATTEXT
.	STATUSPANEL							  8.6D
.	PROGRESS
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	SLIDER
.	TABCONTROL
.	TOOLBUTTON							  8.6D
.	TREEVIEW
.	VSCROLLBAR
.
. svarslit values:
.
.	The <svarslit> variable	is a tooltip string.
.
*------------------------------------------------------------------------------
.   TOOLTIPHWND=nvar						GETPROP
.
. Description:	    
.	This property is a GETPROP only	property.  The TOOLTIPHWND property
.	value is a Windows window handle for the supported object TOOLTIP
.	window.	 This TOOLTIPHWND value	can be used in WINAPI functions
.	where a	window handle is required for the function.
.
. Objects:
.	ANIMATE								  9.0
.	BUTTON
.	CHECKBOX
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	GROUPBOX
.	HSCROLLBAR
.	ICON
.	LABELTEXT							  9.0
.	LISTVIEW
.	MREGION
.	MOVIE
.	PICT
.	STATTEXT
.	PROGRESS
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	SLIDER
.	TABCONTROL
.	TREEVIEW
.	VSCROLLBAR
.
. nvar values:
.     
.	The <nvar> value returned is the Windows handle	for the	TOOLTIP
.	window used for	a specified object.
.
*------------------------------------------------------------------------------
.   TOP=dnumnvar					SETPROP	GETPROP
.
. Description:
.	This property is a SETPROP/GETPROP only	property.  The property
.	is the current top coordinate for an object.
.
. Objects:
.	ANIMATE								  9.0
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.	DIALOG
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	FLOATMENU
.	GROUPBOX
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	ICON
.	LABELTEXT							  9.0
.	LISTVIEW
.	MREGION
.	MOVIE
.	PICT
.	POPUPMENU ( OBSOLETE )
.	PROGRESS
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	SLIDER
.	STATTEXT
.	STATUSBAR
.	TABCONTROL
.	TOOLBAR
.	TREEVIEW
.	VSCROLLBAR
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in the	same units as used when
.	the object was created.	
.
*------------------------------------------------------------------------------
.   TOPMOST=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	that a window should be	placed
.	above all non-topmost windows and should stay above them, even 
.	when the window	is deactivated
.
.	VALUE		Behavior
.
.	  0 (Off)	  - The	TOPMOST	property is turned off.
.	  1 (Application) - The	PLB WINDOW does	NOT remain on TOP of non-PLB
.			    windows  WHEN a PLB	application becomes inactive.
.			    However, the PLB WINDOW remains as the TOP WINDOW
.			    to other PLB windows WHEN the PLB applcation
.			    becomes active.
.	  2 (Global)	  - The	PLB WINDOW remains on TOP of all windows WHEN
.			    a PLB application becomes inactive.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	// Default
.$ON	      EQU	1	// Application
.$GLOBAL      EQU	2	// Global				  9.2B
.
*------------------------------------------------------------------------------
.   TRAILINGCOLOR=dnumnvar|color object		CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property allows the user program to specify the color to
.	be used	in the drop down calendar to used to display header day	
.	and trailing day text. Header and trailing days	are the	days 
.	from the previous and following	months that appear on the 
.	current	month calendar.	The parameter description is the same 
.	as for the BDRCOLOR property.
.
. Objects:
.	EDITDATETIME
.
. dnumnvar values:
.
.	See the	BDRCOLOR property for the color	equate values.
.
*------------------------------------------------------------------------------
.    TRANSACTION=dnumnvar				CREATE	SETPROP	GETPROP   10.5
.
. Description:
.	This property enables or disables transactions. When transactions 
.       are enabled, the DATATABLE tracks all operations using an undo stack.
.       This allows the PL/B program to execute the 'Commit', 'Rollback', 
.       and 'Undo' methods for the DATATABLE.
.
. Objects:
.       DATATABLE
.
. dnumnvar values:
.
.$OFF	      EQU	0	       
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   TREELNSTYLE=dnumnvar			CREATE	SETPROP	GETPROP
.
. Description:
.	This property indicates	the type of lines drawn	between	parent
.	and children items.
.
.	Note1: When the	value of <dnumnvar> is $DEFAULT	or greater than
.	       the $NOLINES value, then	the $LINES is used as the default
.	       TREEVIEW	line style.
.
. Objects:
.	TREEVIEW
.
. dnumnvar values:
.
.$DEFAULT     EQU	0	  //Use	Default
$LINES	      EQU	1	  //Entries are	viewed with intersecting lines
$LINESATROOT  EQU	2	  //Entries are	viewed with intersecting lines
				  // to	a common root entry point
$NOLINES      EQU	3	  //Entries do not have	intersecting lines
.
*------------------------------------------------------------------------------
.   TRISTATE[=dnumnvar]				CREATE	SETPROP	GETPROP
.
. Description:
.     	This property specifies	that a checkbox	object is to have the
.	capability of a	third state or not.  When the TRISTATE property
.	is turned ON, this allows the checkbox object to be checked
.	and grayed as a	third state.  When the TRISATE property	is turned
.	OFF, the checkbox object only has two states where the checkbox
.	is either blanked or checked.
.
.	Note1:	Under program control the SETITEM statement can	be used
.		to set the current state of the	checkbox object.
.
. Objects:
.	CHECKBOX
.	CHECKGRP
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
$AUTOTRISTATE EQU       2   CHECKBOX Automatic mode
.
*------------------------------------------------------------------------------
.   UNDERLINE=dnumnvar				CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property specifies	that the font should be	underlined. When
.	the <dnumnvar> value is	not provided, this indicates that the
.	UNDERLINE property	is turned on.
.
. Objects:
.	FONT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
*------------------------------------------------------------------------------
.   UNITS=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the UNITS scale	to be used when	positioning
.	or sizing objects/grid for a specific WINDOW object.  The allowable
.	units are defined as follows:
.
.	HIENGLISH   - Units specified as .001 inches.
.
.	HIMETRIC    - Units used is .01	centimeters.
.
.	LOENGLISH   - Units specified as .01 inches.
.
.	LOMETRIC    - Units specified as .1 centimeters.
.
.	PIXELS	    - Units specified in pixels.
.
.	TWIPS	    - Units specified as .05 of	a point	[1/1440	of an inch].
.
.	Note1: This property affects the following properties:
.	       TOP, LEFT, WIDTH, HEIGHT, GRIDSIZEH, GRIDSIZEV,
.	       X1, X2, Y1, and Y2. It doesn't affect event results.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
$HIENGLISH    EQU	1
$HIMETRIC     EQU	2
$LOENGLISH    EQU	3
$LOMETRIC     EQU	4
$PIXELS	      EQU	5	       // Default
$TWIPS	      EQU	6
.
*------------------------------------------------------------------------------
.   UPDATEOPT=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property is used to control when the content of an	OLE  
.	insertable object is updated within an OLE container object. It	
.	may be one of:
.
.	$UPDATEOPTAUTO	 - The content of the OLE insertable object is 
.			   updated any time the	data is	changed. 
.	$UPDATEOPTFROZEN - The content of the OLE insertable object is 
.			   updated whenever the	linked data is saved from 
.			   within the application in which it was created.
.	$UPDATEOPTMANUAL - The content of the OLE insertable object is only 
.			   updated when	the Update method is called. 
.
. Objects:
.	CONTAINER
.
. dnumnvar values:
.
$UPDATEOPTAUTO	 EQU	   1		// Default
$UPDATEOPTFROZEN EQU	   2		
$UPDATEOPTMANUAL EQU	   3
.
*------------------------------------------------------------------------------
.   UPDOWNALIGN=dnumnvar			CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used to set or	get the	alignment value	of an UpDown
.	control	component of an	EDITNUMBER object. If the default or
.	$UPDOWNALIGNNONE value is used,	no UpDown control is created. If
.	$UPDOWNALIGNLEFT, or $UPDOWNALIGNRIGHT is used,	an UpDown control
.	is created inside the EDITNUMBER object	by reducing the	object's width.
.
.	An UpDown control only affects the integer portion of a	EDITNUMBER
.	object.	The UPDOWNCHANGE, UPDOWNMAX, and UPDOWNMIN properties
.	must also be set.
.
. Objects:
.	EDITNUMBER
.
. dnumnvar values:
.
.$DEFAULT	  EQU	     0	       //Use Default ($UPDOWNALIGNNONE)
$UPDOWNALIGNLEFT  EQU	     1	       //UpDown	control	should be on the left
$UPDOWNALIGNNONE  EQU	     2	       //No UpDown control is to be used
$UPDOWNALIGNRIGHT EQU	     3	       //UpDown	control	should be on the right
.
*------------------------------------------------------------------------------
.   UPDOWNCHANGE=dnumnvar			CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used to set or	get the	change value of	the UpDown
.	control. The change value is used to modify the	current	value of
.	the EDITNUMBER object, when the	UpDown control is used.	If no value
.	is specified on	a create, then a value of 1 is used.
.
. Objects:
.	EDITNUMBER
.
 
*------------------------------------------------------------------------------
.   UPDOWNMAX=dnumnvar				CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used to set or	get the	maximum	value of the UpDown
.	control. If the	maximum	value is exceeded while	using the control,
.	the value wraps	to the minimum value. If no value
.	is specified on	a create a value of 100	is used.
.
. Objects:
.	EDITNUMBER
.
 
*------------------------------------------------------------------------------
.   UPDOWNMIN=dnumnvar				CREATE	SETPROP	GETPROP	  8.7C
.
. Description:
.	This property is used to set or	get the	minimum	value of the UpDown
.	control. If the	value drops below the minimum value while using	the
.	control, the value wraps to the	maximum	value. If no value
.	is specified on	a create, then a value of 0 is used.
.
. Objects:
.	EDITNUMBER
.
*------------------------------------------------------------------------------
.   UPPERCASE[=dnumnvar]			CREATE
.
. Description:
.	This property is a CREATE only property.
.	This property specifies	that the EDITTEXT object is to convert
.	all entered data to uppercase.	When this property is set to
.	be OFF,	then this indicates that no data conversion occurs.
.
.	Note1: Use of the property should be replaced by using the EDITTYPE
.	       property.
.
. Objects:
.	EDITTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.  URLSOURCE=svarslit				CREATE	SETPROP	 GETPROP  9.7
.
. Description:
.       This property is required to specify a URL for a Web resource to
.       be used for a ICON or PICT object being presented by a PL/B Web
.       Server client. The Web resource can be a .gif, .jpg, or .png file
.       specified by the URL.
.       
.	Note:
.	   1. In release 9.8B, the suppport to allow the SETPROP of the
.	      URLSOURCE property was added.
.	
. Objects:
.       ICON
.	IMAGELIST							  9.9
.       PICT
.
. svarslit values:
.
.	The <svarslit> variable	is a Web URL where the image resource is
.	located.
.
*------------------------------------------------------------------------------
.   USEALTKEY=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	if the Windows ALT+KEY is to be	allowed
.	for the	STATTEXT object.  If the USEALTKEY property is set to ON,
.	then using an '&' character in the name	of the STATTEXT	object
.	will allow the ALT+KEY feature to work.	 If the	USEALTKEY property
.	is set to OFF, then any	'&' character in the name of the
.	STATTEXT object	is output as part of the name and the ALT+KEY
.	feature	does not generate any events for the object.
.
. Objects:
.	LABELTEXT							  9.0
.	STATTEXT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   USECOLORMASK=dnumnvar			CREATE	SETPROP	GETPROP	  9.0
.
. Description:
.	This property specifies	if the MASKCOLOR property is to	be used	for
.	an IMAGELIST object.  When the dnumnvar	value is zero, then the
.	MASKCOLOR property for the IMAGELIST property is not used.  If the
.	dnumnvar value is not zero, then the MASKCOLOR property	is used	for
.	the IMAGELIST object.
.
. Objects:
.	IMAGELIST
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.  USECSS=svarslit				CREATE         GETPROP	  9.7
.
. Description:
.       This property can be used to specify a Cascading Style Sheet
.       (CSS) file that is to be used by a PL/B Web Server client.
.       This user defined CSS file can contain special user class names
.       specified in a style sheet language format. Each CSS class
.       describes the presentation semantics (look and format) of the
.       Web objects used for the PL/B Web Server client. In addition
.       to this user specified CSS file, the PL/B Web Server client uses
.       the default CSS files named 'PlbWebBasic.css', 'PlbWebphone.css',
.       and 'PlbWebIpad.css'. This property is only available for the
.       WINDOW object.
.	
. Objects:
.       WINDOW
.
. svarslit values:
.
.	The <svarslit> variable	is a CSS file name.
.
*------------------------------------------------------------------------------
.   USEMASK=dnumnvar				CREATE		GETPROP
.
. Description:
.	This property is used on CREATE	to indicate that the IMAGELIST should 
.	be masked or non-masked. 
.
. Objects:
.	IMAGELIST
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   VALUE=dnumnvar			     See Objects:
.
. Description: 
.
.    PROGRESS object:
.	This property specifies	the percentage value to	be used	for a
.	PROGRESS object.  The VALUE property can be used to retrieve and set
.	values for the PROGRESS	object as an option to using SETITEM and
.	GETITEM	statements.
.
.    EDITNUMBER	object:
.	This VALUE property can	be used	to retrieve and	set values for the
.	EDITNUMBER object:
.
. Objects:
.	EDITNUMBER					SETPROP	GETPROP
.	PROGRESS				CREATE	SETPROP	GETPROP
.
. dnumnvar values:
.
.    PROGRESS object:
.   	The <dnumnvar> value can be from 0 to 100.  If a value greater 
.	than 100 is specified, then the	value is truncated to be 100.
.
.    EDITNUMBER	object:
.	The property value can be specified as a <dnumnvar> value.
.
*------------------------------------------------------------------------------
.   VARABSVALUE=svar						GETPROP
.
. Description:
.	The VARABSVALUE	property can only be used with a GETPROP instruction.
.	This property retrieves	the current ABSOLUTE/RAW data for a VARIANT
.	object.	 This data can only be retrieved into a	DIM variable.  The
.	actual number of bytes retrieved depends on the	type of	the VARIANT
.	object.	 The following table identifies	the expected number of
.	bytes to be retrieved for the raw data.	 The format of the raw
.	depends	on the VARIANT type and	is the same as described by Windows
.	documentation.
.
.	Notes:
.	      1. If the	VARIANT	object was created using the $VT_ARRAY
.		 VARIANT ARRAY type, then the GETPROP operation	will
.		 retrieve the first VARIANT ARRAY variant value.
.
.	   VARIANT TYPE		BYTE SIZE
.
.	     $VT_EMPTY		   0		    // nothing
.	     $VT_NULL		   0		    // SQL style Null
.	     $VT_I1		   1		    // 1 byte signed int  9.2
.	     $VT_I2		   2		    // 2 byte signed int
.	     $VT_I4		   4		    // 4 byte signed int
.	     $VT_I8		   8		    // 8 byte signed int  9.2
.	     $VT_R4		   4		    // 4 byte real
.	     $VT_R8		   8		    // 8 byte real
.	     $VT_CY		   8		    // currency
.	     $VT_DATE		   8		    // date
.	     $VT_BSTR		   nnn		    // Unicode string
.	     $VT_DISPATCH	   4		    // IDispatch FAR*
.	     $VT_ERROR		   4		    // SCODE
.	     $VT_BOOL		   2		    // True=-1,	False=0
.	     $VT_VARIANT	   4		    // VARIANT FAR*
.	     $VT_UNKNOWN	   4		    // IUnknown	FAR*
.	     $VT_UI1		   1		    // unsigned	char
.	     $VT_UI2		   2		    // 2 byte unsigned int9.2
.	     $VT_UI4		   4		    // 4 byte unsigned int9.2
.	     $VT_UI8		   8		    // 8 byte unsigned int9.2
.	     $VT_INT16		   2		    // 16 bit signed int  9.2
.	     $VT_INT32		   4		    // 32 bit signed int  9.2
.	     $VT_INT64		   8		    // 64 bit signed int  9.2
.	     $VT_UINT16		   2		    // 16 bit unsigned int9.2
.	     $VT_UINT32		   4		    // 32 bit unsigned int9.2
.	     $VT_UINT64		   8		    // 64 bit unsigned int9.2
.
. Objects:
.	VARIANT
.
. values:
.
.	The VARIANT absolute/raw data.
.
*------------------------------------------------------------------------------
.   VARPTR=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	The VARPTR property identifies when a VARIANT is to be passed to
.	an OLE application for a property/method parameter as a	VT_VARIANT.
.	This property causes the runtime to pass a VT_VARIANT to the
.	interface where	the VT_VARIANT contains	the address of the variant
.	data itself. The requirement for passing a VT_VARIANT is controlled
.	by the OLE application being used by the PLB program.  The
.	{dnumnvar} can be set to zero (	$OFF ) which indicates the VARIANT
.	object is to be	processed as a VARIANT,	which is the default. If
.	the {dnumnvar} value is	set to a non-zero value	( $ON ), then
.	this indicates that the	VARIANT	object is to be	passed to the OLE
.	interface as a VT_VARIANT.
.
. Objects:
.	VARIANT
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   VARTYPE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	The VARTYPE property identifies	the VARIANT data type as allowed
.	for conversion between PLB data	types and applicable Windows
.	variant	types.
.
.	Notes:
.	      1. The $VT_ARRAY value can be added with other VARIANT
.		 types to cause	a VARIANT ARRAY	to be generated	for
.		 a CREATE operation.  In this case, a one dimensioned
.		 VARIANT ARRAY is created with a single	VARIANT	element.
.
.	      2. The $VT_ARRAY value can not be	used in	a SETPROP operation.
.		 This will cause a runtime O132	error to occur.
.
. Objects:
.	VARIANT
.
. dnumnvar values:
.
$VT_EMPTY     EQU	0	       // nothing
$VT_NULL      EQU	1	       // SQL style Null
$VT_I1	      EQU	16	       // 1 byte signed	int		  9.2
$VT_I2	      EQU	2	       // 2 byte signed	int
$VT_I4	      EQU	3	       // 4 byte signed	int
$VT_I8	      EQU	20	       // 8 byte signed	int		  9.2
$VT_R4	      EQU	4	       // 4 byte real
$VT_R8	      EQU	5	       // 8 byte real
$VT_CY	      EQU	6	       // currency
$VT_DATE      EQU	7	       // date
$VT_BSTR      EQU	8	       // OLE Automation string
$VT_DISPATCH  EQU	9	       // IDispatch FAR*
$VT_ERROR     EQU	10	       // SCODE
$VT_BOOL      EQU	11	       // True=-1, False=0
$VT_VARIANT   EQU	12	       // VARIANT FAR*
$VT_UNKNOWN   EQU	13	       // IUnknown FAR*
$VT_UI1	      EQU	17	       // unsigned char
$VT_UI2	      EQU	18	       // 2 byte unsigned int		  9.2
$VT_UI4	      EQU	19	       // 4 byte unsigned int		  9.2
$VT_UI8	      EQU	21	       // 8 byte unsigned int		  9.2
$VT_INT16     EQU	2	       // 16 bit signed	int		  9.2
$VT_INT32     EQU	3	       // 32 bit signed	int		  9.2
$VT_INT64     EQU	20	       // 64 bit signed	int		  9.2
$VT_UINT16    EQU	18	       // 16 bit unsigned int		  9.2
$VT_UINT32    EQU	19	       // 32 bit unsigned int		  9.2
$VT_UINT64    EQU	21	       // 64 bit unsigned int		  9.2
$VT_ARRAY     EQU   0x2000	       // Variant array
.
..............
. Note the following VT type values are NOT directly supported and/or used by
. the PL/B runtimes. These VT type values are being included in the
. 'plbequ.inc' to be available for the PL/B application detection when a
. GETPROP VARTYPE is being used. These values are intentionally not
. included in the PL/B Language Reference Manually. The interpretation and
. use of the following variant types is the responsibility of the end-user's
. application. These variant type equates were added in 9.6A.
.
VT_DECIMAL	EQU	14 
VT_INT		EQU	22
VT_UINT		EQU	23
VT_VOID		EQU	24
VT_HRESULT	EQU	25
VT_PTR		EQU	26
VT_SAFEARRAY	EQU	27
VT_CARRAY	EQU	28
VT_USERDEFINED	EQU	29
VT_LPSTR	EQU	30
VT_LPWSTR	EQU	31
VT_RECORD	EQU	36
VT_FILETIME	EQU	64
VT_BLOB		EQU	65
VT_STREAM	EQU	66
VT_STORAGE	EQU	67
VT_STREAMED_OBJECT EQU	68
VT_STORED_OBJECT EQU	69
VT_BLOB_OBJECT	EQU	70
VT_CF		EQU	71
VT_CLSID	EQU	72
VT_BSTR_BLOB	EQU	0xfff
VT_VECTOR	EQU	0x1000
VT_BYREF	EQU	0x4000
VT_RESERVED	EQU	0x8000
VT_ILLEGAL	EQU	0xffff
VT_ILLEGALMASKED EQU	0xfff
VT_TYPEMASK	EQU	0xfff
.
*------------------------------------------------------------------------------
.   VARVALUE=dnumnvar				CREATE	SETPROP	GETPROP
.   VARVALUE=svarslit
.   VARVALUE=AUTOMATION	object
.   VARVALUE=VARIANT object
.
. Description:
.	The VARVALUE property allows the value of the VARIANT to be
.	assigned in accordance with the	VARTYPE	of the object.
.
.	Notes:
.	      1. If the	VARIANT	object type specifies the $VT_ARRAY
.		 VARIANT ARRAY type, then a CREATE or SETPROP will
.		 set the value of the first VARIANT ARRAY element.
.
.	      2. If the	VARIANT	object was created using the $VT_ARRAY
.		 VARIANT ARRAY type, then the GETPROP operation	will
.		 retrieve the first VARIANT ARRAY variant value.
.
. Objects:
.	VARIANT
.
. values:
.
.	The VARIANT value is processed as per the VARTYPE of the object.
.
*------------------------------------------------------------------------------
.   VIEWSTYLE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property indicates	what view should be displayed by the  
.	LISTVIEW object. The views are:
.
.	$VIEWICON     -	Large Icon
.	$VIEWLIST     -	List
.	$VIEWREPORT   -	Report
.	$VIEWSICON    -	Small Icon
.
. Objects:
.	LISTVIEW
.
. dnumnvar values:
.
$VIEWICON     EQU	1
$VIEWLIST     EQU	2
$VIEWREPORT   EQU	3	       // Default
$VIEWSICON    EQU	4
.
*------------------------------------------------------------------------------
.   VISIBLE=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	if an object is	to be made visible or
.	invisible.  If the VISIBLE property is set to $ON and the current
.	state of the object is invisible, then this is the same	as if
.	if an ACTIVATE statement without any activation	routine	was 
.	executed for the object.  However, if the VISIBLE property is set 
.	$ON and	the object is already visible, then the	object remains
.	visible	and no change occurs.  If the VISIBLE property is set to
.	$OFF, this is the same as if a DEACTIVATE statement was	executed
.	for the	object.	 The GETPROP retrieves the current VISIBLE state
.	for the	object.
.
.	Note1: The VISIBLE property is ignored for a WINDOW object when
.	       the WINTYPE is set for MODAL.  This can not be allowed 
.	       since the program execution remains at the ACTIVATE
.	       statement while the MODAL dialog	is processed.  If the
.	       VISIBLE property	were allowed, then this	would cause
.	       program execution to remain at the CREATE statement
.	       causing a program to hang since no events could be 
.	       registered for use.
.
.	Note2: The VISIBLE property for	the MREGION object causes the
.	       mouse region to be activated or deactivated as per the
.	       property	value provided.
.	       
. Objects:
.	ANIMATE								  9.0
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	GROUPBOX
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	ICON
.	LABELTEXT							  9.0
.	LISTVIEW
.	MENU								  9.0
.	MOVIE
.	MREGION
.	PICT
.	POPUPMENU
.	PROGRESS
.	RADIO
.	RADIOGRP
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	SLIDER
.	STATTEXT
.	STATUSBAR
.	TABCONTROL
.	TOOLBAR
.	TREEVIEW
.	VSCROLLBAR
.	WINDOW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.  WEBCLASS=svarslit				CREATE	SETPROP	GETPROP	  9.7
.
. Description:
.       This property can be used to specify a class name that is case
.       sensitive and this class name must exist in one of the Cascading
.       Style Sheet (.css) files that are being used by a PL/B Web Server
.       client. This property is available for any GUI object allowed for
.       the PL/B Web Server client.
.	
. Objects:
.       BUTTON
.       CHECKBOX
.       COLOR
.       COMBOBOX
.       DATACOLUMN                                                       10.5
.       DATALIST                                                         10.5
.       EDITDATETIME
.       EDITNUMBER
.       EDITTEXT
.       FLOATMENU
.       FONT
.       GROUPBOX
.       HTMLCONTROL							  10.0A
.       ICON
.       LABELTEXT
.       LINE
.       LISTVIEW
.       MREGION
.       MENU
.       RADIO
.       SUBMENU
.       PANEL
.       PICT
.       PROGRESS
.       STATTEXT
.       SPLITTER                                                          10.1A
.	STATUSBAR							  10.1A
.       TABCONTROL
.       TIMER
.       TOOLBAR								  10.1A
.       TREEVIEW							  9.9
.       WINDOW								  9.9
.       
.
. svarslit values:
.
.	The <svarslit> variable	is a CSS class name.
.
*------------------------------------------------------------------------------
.  WEBHEIGHT=svarslit				CREATE	SETPROP	GETPROP	  9.9
.
. Description:
.       
.       The WEBHEIGHT property specifies the height property to be applied
.       to the HTML element\object rendered at the client browser for the
.       PL\B Web Server object.
.       
.       The WEBHEIGHT {svarlit} is formatted as a case sensitive string
.       to allow the PLB program to specify the HTML element height
.       property with string values consistent to CSS style syntax formats
.       including units of px, cm, em, ...etc. 
.	
. Objects:
.       BUTTON
.       CHECKBOX
.       COMBOBOX
.       DATALIST
.       EDITDATETIME
.       EDITNUMBER
.       EDITTEXT
.       FLOATMENU
.       GROUPBOX
.       HTMLCONTROL							  10.0A
.       ICON
.       LABELTEXT
.       LISTVIEW
.       MREGION
.       PANEL
.       PICT
.       PROGRESS
.       RADIO
.       SHAPE
.       SLIDER
.       SPLITTER                                                          10.1A
.       STATTEXT
.	STATUSBAR							  10.1A
.       TABCONTROL
.       TIMER
.       TOOLBAR								  10.1A
.       TREEVIEW
.       WINDOW
.
. svarslit values:
.
.	The <svarslit> variable	is formatted the same as a CSS height
.	style used for HTML elements.
.
.       Example:
.
.          WEBHEIGHT="100px"
.          WEBHEIGHT="20em"
.          WEBHEIGHT="25%"
.
*------------------------------------------------------------------------------
.  WEBLEFT=svarslit				CREATE	SETPROP	GETPROP	  9.9
.
. Description:
.       
.       The WEBLEFT property specifies the left property to be applied
.       to the HTML element\object rendered at the client browser for the
.       PL\B Web Server object.
.       
.       The WEBLEFT {svarlit} is formatted as a case sensitive string
.       to allow the PLB program to specify the HTML element left
.       property string with values consistent to CSS style syntax formats
.       including units of px, cm, em, ...etc. 
.	
. Objects:
.       BUTTON
.       CHECKBOX
.       COMBOBOX
.       DATALIST
.       EDITDATETIME
.       EDITNUMBER
.       EDITTEXT
.       FLOATMENU
.       GROUPBOX
.       HTMLCONTROL							  10.0A
.       ICON
.       LABELTEXT
.       LISTVIEW
.       MREGION
.       PANEL
.       PICT
.       PROGRESS
.       RADIO
.       SHAPE
.       SLIDER
.       STATTEXT
.       SPLITTER                                                          10.1A
.	STATUSBAR							  10.1A
.       TABCONTROL
.       TIMER
.       TOOLBAR								  10.1A
.       TREEVIEW
.       WINDOW
.
. svarslit values:
.
.	The <svarslit> variable	is formatted the same as a CSS left
.	style used for HTML elements.
.
.       Example:
.
.          WEBLEFT="100px"
.          WEBLEFT="20em"
.          WEBLEFT="25%"
.
*------------------------------------------------------------------------------
.  WEBMODE=dnumnvar				CREATE	SETPROP	GETPROP	  10.5
.
. Description:
.
.       The WEBMODE property is used to specify whether the WebView mode
.       is to be allowed or not allowed for a HTMLCONTROL or WINDOW object.
.       Once these objects are created using a specific web mode, all
.       child objects are created and processed accordingly.
.
. Objects:
.       HTMLCONTROL
.       WINDOW
.
. dnumnvar values:
.
$WMODE_DEFAULT  EQU 0	//Use runtime default settings for mode
$WMODE_WIN32	EQU 1	//Allow WIN32 controls
$WMODE_BOTH	EQU 1	//Allow WIN32 and WebView controls
$WMODE_WEBVIEW	EQU 3	//Allow WebView controls
.
*------------------------------------------------------------------------------
.  WEBOBJECT=dnumnvar				CREATE	SETPROP	GETPROP	  10.5
.
. Description:
.       
.       The WEBOBJECT property is used to create PL/B objects as web objects
.       when the WEBMODE is set with WebView turned on.
.
. Objects:
.       BUTTON
.       CHECKBOX
.       COMBOBOX
.       DATALIST
.       EDITDATETIME
.       EDITNUMBER
.       EDITTEXT
.       FLOATMENU
.       GROUPBOX
.       HTMLCONTROL
.       ICON
.       IMAGELIST
.       LABELTEXT
.       LISTVIEW
.       MREGION
.       PANEL
.       PICT
.       PROGRESS
.       RADIO
.       SHAPE
.       SLIDER
.       SPLITTER
.       STATTEXT
.       STATUSBAR
.       TABCONTROL
.       TOOLBAR
.       TREEVIEW
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.  WEBPOSITION=dnumnvar				CREATE	SETPROP	GETPROP	  9.9
.
. Description:
.       
.       The WEBPOSITION property specifies the position property to be
.       applied to the HTML element\object rendered at the client browser
.       for the PL\B Web Server object.
.
. Objects:
.       BUTTON
.       CHECKBOX
.       COMBOBOX
.       DATALIST
.       EDITDATETIME
.       EDITNUMBER
.       EDITTEXT
.       FLOATMENU
.       GROUPBOX
.       HTMLCONTROL							  10.0A
.       ICON
.       LABELTEXT
.       LISTVIEW
.       MREGION
.       PANEL
.       PICT
.       PROGRESS
.       RADIO
.       SHAPE
.       SLIDER
.       STATTEXT
.       SPLITTER                                                          10.1A
.	STATUSBAR							  10.1A
.       TABCONTROL
.       TIMER
.       TOOLBAR								  10.1A
.       TREEVIEW
.       WINDOW
.
. dnumnvar values:
.
.       The allowed WEBPOSITION {dnumnvar} values are defined as
.       follows in accordance to expected CSS positioning methods
.       supported for an HTML element.
.
.          Value  - Description
.
.            0      The CSS position property is set to be 'absolute' which
.                   is the default.
.                            
.            1      The CSS position property is set to be 'static' and
.                   the CSS margin is set to be 'auto'.
.
.            2      The CSS position property is set to be 'relative'.
.
.            3      The CSS position property is set to be 'fixed'.
.
.
.$DEFAULT	 EQU	0	// Use Default same as $WEB_ABSOLUTE
$WEB_ABSOLUTE	 EQU	0	//Same as default for WEBPOSITION
$WEB_STATIC	 EQU	1
$WEB_RELATIVE	 EQU	2
$WEB_FIXED	 EQU	3
.
.       Example:
.
.          WEBPOSITION=$WEB_STATIC
.
*------------------------------------------------------------------------------
.  WEBTOP=svarslit				CREATE	SETPROP	GETPROP	  9.9
.
. Description:
.       
.       The WEBTOP property specifies the top property to be applied
.       to the HTML element\object rendered at the client browser for the
.       PL\B Web Server object.
.       
.       The WEBTOP {svarlit} is formatted as a case sensitive string
.       to allow the PLB program to specify the HTML element TOP
.       property with string values consistent to CSS style syntax formats
.       including units of px, cm, em, ...etc. 
.	
. Objects:
.       BUTTON
.       CHECKBOX
.       COMBOBOX
.       DATALIST
.       EDITDATETIME
.       EDITNUMBER
.       EDITTEXT
.       FLOATMENU
.       GROUPBOX
.       HTMLCONTROL							  10.0A
.       ICON
.       LABELTEXT
.       LISTVIEW
.       MREGION
.       PANEL
.       PICT
.       PROGRESS
.       RADIO
.       SHAPE
.       SLIDER
.       STATTEXT
.       SPLITTER                                                          10.1A
.	STATUSBAR							  10.1A
.       TABCONTROL
.       TIMER
.       TOOLBAR								  10.1A
.       TREEVIEW
.       WINDOW
.
. svarslit values:
.
.	The <svarslit> variable	is formatted the same as a CSS top
.	style used for HTML elements.
.
.       Example:
.
.          WEBTOP="100px"
.          WEBTOP="20em"
.          WEBTOP="25%"
.
*------------------------------------------------------------------------------
.  WEBWIDTH=svarslit				CREATE	SETPROP	GETPROP	  9.9
.
. Description:
.       
.       The WEBWIDTH property specifies the width property to be applied
.       to the HTML element\object rendered at the client browser for the
.       PL\B Web Server object.
.       
.       The WEBWIDTH {svarlit} is formatted as a case sensitive string
.       to allow the PLB program to specify the HTML element width
.       property with string values consistent to CSS style syntax formats
.       including units of px, cm, em, ...etc. 
.	
. Objects:
.       BUTTON
.       CHECKBOX
.       COMBOBOX
.       DATACOLUMN                                                       10.5
.       DATALIST                                                         10.5
.       EDITDATETIME
.       EDITNUMBER
.       EDITTEXT
.       FLOATMENU
.       GROUPBOX
.       HTMLCONTROL							  10.0A
.       ICON
.       LABELTEXT
.       LISTVIEW
.       MREGION
.       PANEL
.       PICT
.       PROGRESS
.       RADIO
.       SHAPE
.       SLIDER
.       STATTEXT
.       SPLITTER                                                          10.1A
.	STATUSBAR							  10.1A
.       TABCONTROL
.       TIMER
.       TOOLBAR								  10.1A
.       TREEVIEW
.       WINDOW
.
. svarslit values:
.
.	The <svarslit> variable	is formatted the same as a CSS width
.	style used for HTML elements.
.
.       Example:
.
.          WEBWIDTH="100px"
.          WEBWIDTH="20em"
.          WEBWIDTH="25%"
.
*------------------------------------------------------------------------------
.   WIDTH=dnumnvar					SETPROP	GETPROP
.
. Description:
.	This property is a GETPROP/SETPROP only	property.  The width
.	of the object can be retrieved using the GETPROP statement.
.	The width is determined	by subtracting the left	object rectangle
.	coordinate from	the right object rectangle coordinate.	The
.	SETPROP	statement can be used to change	the current width of
.	an object.
.
.     (STATUSPANEL)							  8.6D
.	This property sets or returns the fixed	width of a STATUSPANEL
.	object.	This property is only used when	the AUTOSIZE property
.	is set to $PANSIZENONE.
.
.
. Objects:
.	ANIMATE								  9.0
.	BUTTON
.	CHECKBOX
.	CHECKGRP
.	COMBOBOX
.	CONTAINER
.	CONTROL
.	DATALIST
.	DIALOG
.	EDITDATETIME							  9.0
.	EDITNUMBER							  8.7C
.	EDITTEXT
.	FLOATMENU
.	GROUPBOX
.	HSCROLLBAR
.       HTMLCONTROL							  10.0A
.	ICON
.	LABELTEXT							  9.0
.	LISTVIEW
.	MREGION
.	MOVIE
.	PICT
.	POPUPMENU ( OBSOLETE )
.	PROGRESS
.	RADIOGRP
.	RADIO
.	RICHEDITTEXT							  9.0B
.	SHAPE
.	SLIDER
.	STATTEXT
.	STATUSBAR
.	STATUSPANEL
.	TABCONTROL
.	TOOLBAR
.	TREEVIEW
.	VSCROLLBAR
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in the	same units as used for
.	the creation of	an object.  This means that if an object was
.	created	using pixels, then the width expects to	use pixels.
.	For a STATUSPANEL object the <dnumnvar>	value is provided in
.	pixels.
.
*------------------------------------------------------------------------------
.   WINBORDER=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the type of window border for the
.	window object.
.
.	The allowed window borders are as follows:
.
.	NOBORDER      -	This style creates a window with no border and
.			no caption.
.
.	FIXEDSINGLE   -	This style creates a window with a single border
.			that can't be sized.
.
.	FIXED3D	      -	This style creates a window with a 3D border
.			that can't be sized.
.
.	SIZABLE3D     -	This style is the same as FIXED3D, but allows the
.			window to be sized.
.
.	FIXEDDIALOG   -	Creates	a window that has a double border and
.			can't be sized.
.
.	SIZABLE	      -	This style is the same as FIXEDSINGLE, but allows the
.			window to be sized.
.
.	FIXEDTOOL     -	This style creates a tool window. This type is a 
.			window intended	to be used as a	floating toolbar. A
.			tool window has	a title	bar that is shorter than a 
.			normal title bar, and the window title is drawn	
.			using a	smaller	font. A	tool window does not appear
.			in the taskbar or in the dialog	that appears when
.			the user presses ALT+TAB.  If a	tool window has	a
.			system menu, its icon is not displayed on the 
.			title bar. However, you	can display the	system 
.			menu by	right clicking or by typing ALT+SPACE.
.
.	SIZABLETOOL   -	This style is the same as FIXEDTOOL, but allows	the
.			window to be sized.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$NONE	      EQU	0	// Use a default based on WINTYPE
$NOBORDER	EQU	1
$FIXEDSINGLE	EQU	2
$FIXED3D	EQU	3
$SIZABLE3D	EQU	4
$FIXEDDIALOG	EQU	5
$SIZABLE	EQU	6
$FIXEDTOOL	EQU	7
$SIZABLETOOL	EQU	8
.
*------------------------------------------------------------------------------
.   WINHEIGHT=dnumnvar					SETPROP	GETPROP	  8.6D
.
. Description:
.	This property is a GETPROP/SETPROP only	property.  This	property
. 	identifies the actual Window height size that includes both the
.	client and the non-client areas.  Please note that the current
.	HEIGHT property	identifies the size of the CLIENT area of a
.	Window object.	A user can subtract the	client property	height
.	value from the full Window value to determine the
.	non-client height for a	Window object.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
*------------------------------------------------------------------------------
.   WINOFFSETH=dnumnvar					SETPROP	GETPROP
.
. Description:
.	This property is a GETPROP/SETPROP only	property.  The WINOFFSETH
.	property identifies a relative horizontal offset for the
.	visible	viewing	area of	a WINDOW.  By default the visible
.	viewing	offset starts with a zero value.
.
.	Note1: It is possible to create	objects	outside	the normal
.	       viewing area for	a Window.  If this is done, then the
.	       WINOFFSETH and WINOFFSETV properties can	be used	to
.	       bring these objects into	the viewing area.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	a pixel	value, which defines a horizontal
.	offset for the visible area of a Window.
.
*------------------------------------------------------------------------------
.   WINOFFSETV=dnumnvar					SETPROP	GETPROP
.
. Description:
.	This property is a GETPROP/SETPROP only	property.  The WINOFFSETV
.	property identifies a relative vertical	offset for the
.	visible	viewing	area of	a WINDOW.  By default the
.	visible	viewing	offset starts with a zero value.
.
.	Note1: It is possible to create	objects	outside	the normal
.	       viewing area for	a Window.  If this is done, then the
.	       WINOFFSETH and WINOFFSETV properties can	be used	to
.	       bring these objects into	the viewing area.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.	The <dnumnvar> value is	a pixel	value, which defines a vertical
.	offset for the visible area of a Window.
.
*------------------------------------------------------------------------------
.   WINPOS=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	the positioning	of a window when a
.	window object is activated.
.
.	The allowed window positioning types are as follows:
.
.	ABSOLUTE   -	This causes a window object to be positioned to
.			the top/left co-ordinates of the window	object.
.		     
.	DESKCENTER   -	This causes a window object to be centered on the 
.			desktop.
.		      
.	PARENTCENTER -	This centers a MODAL or	MODELESS window	object over
.			the parent window. If the window object	is not a MODAL
.			or MODELESS window object, it is treated as if
.			DESKCENTER was used.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$NONE	      EQU	0		// Same	as Default
$ABSOLUTE     EQU	1		// Default
$DESKCENTER   EQU	2
$PARENTCENTER EQU	3	       
$MAXIMIZE     EQU	4						  9.1
$MINIMIZE     EQU	5						  9.1
$MAXIMIZEWIDTH EQU	6						  10.0A
.
*------------------------------------------------------------------------------
.   WINTYPE=dnumnvar				CREATE		GETPROP
.
. Description:
.	This property specifies	the type of window applied for the
.	window object.
.
.	The allowed window types are as	follows:
.
.	MODAL	   -  This causes a MODAL dialog window	to be created.
.		      When this	window is activated using the ACTIVATE
.		      statement, the program execution remains
.		      at the ACTIVATE statement	until the window is
.		      destroyed	or deactivated.	 While a MODAL window
.		      is active, no events other than events for the MODAL
.		      window are processed until the MODAL window is
.		      terminated.
.
.	MODELESS   -  This causes a MODELESS dialog window to be created.
.		      This window is a Window's	popup window, which will
.		      always remain on top of any primary window.  Another
.		      feature is that this window acts as a child window
.		      to a primary window.  If the primary window gets
.		      minimized, then the MODELESS dialog window is also
.		      minimized.  However, the MODELESS	dialog window
.     		      does not affect the minimized task bar selections.
.		      The MODELESS dialog window can not be minimized.
.		      The MODELESS dialog window does not lock out event
.		      processing for other windows while the MODELESS
.		      window is	active.
 
.	OBJONLY	   -  The use for the objects only window type is reserved
.		      for use by the PLB designer.  If this type is used
.		      in a program, then it is implemented as a
.		      PRIMARYSIZE window type.
.
.     PRIMARYFIXED -  This type	creates	a Window's Primary window which
.		      can not be sized.	 A primary window can be minimized
.		      and maximized.  A	primary	window will always be
.		      presented	under a	MODAL/MODELESS dialog window.
.		      If a primary window is active when a MODELESS window
.		      is created, then the primary window acts as the
.		      parent window for	the MODELESS window.
.
.     PRIMARYSIZE  -  The primary sized	window type is a Windows' Primary
.		      window which can be sized.  All other features are
.		      the same as PRIMARYFIXED.
.
.     MDICLIENT	   -  This type	creates	a window that contains a MDI client
.		      window to	support	MDICHILD type windows. The
.		      properties: MDIBORDER, MDISCROLL,	MDITOP,	MDILEFT,
.		      MDIHEIGHT	and MDIWIDTH can be used to manipulate
.		      the MDI client window. Also the MDILayout	and MDIShow
.		      methods also affect the MDI client window.
.
.     MDICHILD	   -  This type	creates	a MDI child window for use with	a
.		      host MDICLIENT style window.
.
.     MPICLIENT	   -  This type	creates	a window that contains a MPI client
.		      window to	support	MPICHILD type windows. The
.		      properties: MPIBORDER, MPISCROLL,	MPITOP,	MPILEFT,
.		      MPIHEIGHT	and MPIWIDTH can be used to manipulate
.		      the MPI client window. Also the MPILayout	and MPIShow
.		      methods also affect the MPI client window. This
.		      window type only exists when a Plbwebsrv or Plbwin
.                     ( WebView2 ) runtime is being used.
.
.     MPICHILD	   -  This type	creates	a MPI child window for use with	a
.		      host MPICLIENT style window. This window type only
.		      exists when a Plbwebsrv or Plbwin ( WebView2 ) runtime
.		      is being used.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
.$NONE		   EQU	0	       // Same as Default
$MODAL		   EQU	1
$MODELESS	   EQU	2
$OBJONLY	   EQU	3	       // PLFORM use only
$PRIMARYFIXED	   EQU	4
$PRIMARYSIZE	   EQU	5	       // Default
$MDICLIENT	   EQU	6
$MDICHILD	   EQU	7
$CEMODALNOMENU	   EQU	8	       // CE values with MENU		  9.1A
$CEMODELESSNOMENU  EQU	9						  9.1A
$CEFIXEDNOMENU	   EQU 10						  9.1A
$CESIZEABLENOMENU  EQU 11						  9.1A
$MPICLIENT	   EQU 12	//Plbwebsrv or Plbwin (WebView2) Only	  10.7
$MPICHILD	   EQU 13	//Plbwebsrv or Plbwin (WebView2) Only	  10.7
.
*------------------------------------------------------------------------------
.   WINWIDTH=dnumnvar					SETPROP	GETPROP	  8.6D
.
. Description:
.	This property is a GETPROP/SETPROP only	property.  This	property
.	identifies the actual Window width size	that includes both the
.	client and the non-client areas.  Please note that the current
.	WIDTH property identifies the size of the CLIENT area of a
.	Window object.	A user can subtract the	client property	width
.	value from the full Window value to determine the
.	non-client width for a Window object.
.
. Objects:
.	WINDOW
.
. dnumnvar values:
.
*------------------------------------------------------------------------------
.   WORDWRAP[=dnumnvar]				CREATE	SETPROP	GETPROP
.
. Description:
.	For a MULTILINE	EDITTEXT object	this property causes
.	the data entry to continue at the beginning of the
.	next line when the right most boundary of the EDITTEXT
.	object is encountered.	If the <dnumnvar> value	is not
.	specified, the WORDWRAP	property is set	to ON.
.
. Objects:
.	EDITTEXT
.	LABELTEXT							  9.0
.	RICHEDITTEXT							  9.0B
.
. dnumnvar values:
.
.$OFF	      EQU	0	       // Default
.$ON	      EQU	1
.
*------------------------------------------------------------------------------
.   WRAPPABLE=dnumnvar				CREATE	SETPROP	GETPROP	  8.6D
.
. Description:
.	This property indicates	if buttons in a	TOOLBAR	object should
.	wrap to	multiple lines if there	is no enough space to show
.	all the	buttons.
.
. Objects:
.	TOOLBAR
.
. dnumnvar values:
.
.$OFF	    EQU	      0
.$ON	    EQU	      1
.
*------------------------------------------------------------------------------
.   X1=dnumnvar						SETPROP	GETPROP
.
. Description:
.	This property is a GETPROP/SETPROP only	property.  The X1 property
.	specifies the X	coordinate for the starting point of the LINE
.	object.
.
. Objects:
.	LINE
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in the	same units as used for
.	the creation of	an object.  This means that if an object was
.	created	using pixels, then the X1 value	expects	to use pixels.
*------------------------------------------------------------------------------
.   X2=dnumnvar						SETPROP	GETPROP
.
. Description:
.	This property is a GETPROP/SETPROP only	property.  The X2 property
.	specifies the X	coordinate for the ending point	of the LINE
.	object.
.
. Objects:
.	LINE
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in the	same units as used for
.	the creation of	an object.  This means that if an object was
.	created	using pixels, then the X2 value	expects	to use pixels.
*------------------------------------------------------------------------------
.   Y1=dnumnvar						SETPROP	GETPROP
.
. Description:
.	This property is a GETPROP/SETPROP only	property.  The Y1 property
.	specifies the Y	coordinate for the starting point of the LINE
.	object.
.
. Objects:
.	LINE
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in the	same units as used for
.	the creation of	an object.  This means that if an object was
.	created	using pixels, then the Y1 value	expects	to use pixels.
*------------------------------------------------------------------------------
.   Y2=dnumnvar						SETPROP	GETPROP
.
. Description:
.	This property is a GETPROP/SETPROP only	property.  The Y2 property
.	specifies the Y	coordinate for the ending point	of the LINE
.	object.
.
. Objects:
.	LINE
.
. dnumnvar values:
.
.	The <dnumnvar> value is	provided in the	same units as used for
.	the creation of	an object.  This means that if an object was
.	created	using pixels, then the Y2 value	expects	to use pixels.
*------------------------------------------------------------------------------
.   ZOOMFACTOR=dnumnvar			CREATE	SETPROP	GETPROP		  9.0B
.
. Description:
.	This property specifies	the zoom percentage of the object.
.
.	The text can be	decreased in size by setting this value	below 100
.	or increased by	setting	this value above 100.
.
. Objects:
.	RICHEDITTEXT
.
. dnumnvar values:
.
.     The <dnumnvar> value is specified	in percent. The	default	is 100 percent.
.
*------------------------------------------------------------------------------
.   ZORDER=dnumnvar				CREATE	SETPROP	GETPROP
.
. Description:
.	This property specifies	which object should be displayed
.	on top when more than one object exists	in the same space
.	and in the same	plane.
.
.	Note1:	Any objects in 'Plane 1' will always be	on top of
.		any object in 'Plane 0'	with the exception of the
.		TABCONTROL object.  Although, the TABCONTROL object
.		exists in 'Plane 1', the 'Plane	0' objects can be
.		placed on top of the TABCONTROL	by having a higher
.		ZORDER value than the TABCONTROL.
.
.	Note2:	When the ZORDER	value for any object is	higher than
.		any other object in the	same plane, then the object 
.		with the higher	value exists on	top. 
.
.	Note3:	The ZORDER exists for a	window object only to define
.		a default zorder starting value	for objects created
.		for that window	object without an explicit ZORDER.
.
. Objects:
.	ANIMATE			;Plane	1				  9.0
.	BUTTON			;Plane	1
.	CHECKBOX		;Plane	1
.	CHECKGRP		;Plane	1
.	COMBOBOX		;Plane	1
.	CONTAINER		;Depends on object usage
.	CONTROL			;Plane	1
.	DATALIST		;Plane	1
.	EDITDATETIME		;Plane	1				  9.0
.	EDITNUMBER		;Plane	1				  8.7C
.	EDITTEXT		;Plane	1
.	GROUPBOX		;Plane	0
.	HSCROLLBAR		;Plane	1
.       HTMLCONTROL		;Plane  1				  10.0A
.	ICON			;Plane	0
.	LABELTEXT		;Plane	1				  9.0
.	LINE			;Plane	0
.	LISTVIEW		;Plane	1
.	MREGION			;Plane	0
.	MOVIE			;Plane	1
.	PICT			;Plane	0
.	POPUPMENU ( OBSOLETE )	;Plane	1
.	PROGRESS		;Plane	0
.	RADIOGRP		;Plane	1
.	RADIO			;Plane	1
.	RICHEDITTEXT		;Plane	1				  9.0B
.	SHAPE			;Plane	0
.	SLIDER			;Plane	1
.	STATTEXT		;Plane	0
.	STATUSBAR		;Plane	1
.	TABCONTROL		;Plane	1
.	TOOLBAR			;Plane	1
.	TREEVIEW		;Plane	1
.	VSCROLLBAR		;Plane	1
.	WINDOW			;No Plane
.
. dnumnvar values:
.
.	The <dnumnvar> value is	a user-defined value.
.
*---End	PLBEQU Definitions-----------------------------------------------------
.
	 %ENDIF			       ;PLBEQU				  8.1E
.
	 %IF $PLBDEF = 1	       ;1 ==> Include these DEFINITIONS	  8.2
.
*===Begin PLBDEF Definitions=================================================
;
;   Function key DEFINE's
;	   These expressions are used with the KeyPress	event to determine if a
;	   part	of an IF statement. They will function as a stand-a-lone
;	   expression ie: [IF $F1] or in combination within a compound
;	   expression ie: [IF ($F1 & $SHIFT)] within a .PLF form file. These
;	   work	only within the	object,	which has, focus and WILL NOT function
;	   in the KeyPress event for the FORM.
;
$ENTER	   DEFINE     (#EventResult=13)
;
$F1	   DEFINE     (#EventResult=112)
$F2	   DEFINE     (#EventResult=113)
$F3	   DEFINE     (#EventResult=114)
$F4	   DEFINE     (#EventResult=115)
$F5	   DEFINE     (#EventResult=116)
$F6	   DEFINE     (#EventResult=117)
$F7	   DEFINE     (#EventResult=118)
$F8	   DEFINE     (#EventResult=119)
$F9	   DEFINE     (#EventResult=120)
$F10	   DEFINE     (#EventResult=121)
$F11	   DEFINE     (#EventResult=122)
$F12	   DEFINE     (#EventResult=123)
;
$PGUP	   DEFINE     (#EventResult=33)
$PGDN	   DEFINE     (#EventResult=34)
$END	   DEFINE     (#EventResult=35)
$HOME	   DEFINE     (#EventResult=36)
$FLEFT	   DEFINE     (#EventResult=37)
$UP	   DEFINE     (#EventResult=38)
$FRIGHT	   DEFINE     (#EventResult=39)
$DOWN	   DEFINE     (#EventResult=40)
;
$INS	   DEFINE     (#EventResult=45)
 
$DEL	   DEFINE     (#EventResult=46)
;
$PAUSE	   DEFINE     (#EventResult=19)
$SCRL_LCK  DEFINE     (#EventResult=145)
;
; These	are found as part of the Numeric pad NOT found in the Qwerty key area
;
$NUM_STAR  DEFINE     (#EventResult=106)    ; Displays Character "*"
$NUM_PLUS  DEFINE     (#EventResult=107)    ; Displays Character "+"
$NUM_MINUS DEFINE     (#EventResult=109)    ; Displays Character "-"
$NUM_SLASH DEFINE     (#EventResult=111)    ; Displays Character "/"
;
; Modifiers... These code are used in conjunction with the EventResult values
;
$NO_MOD		 DEFINE	   (#EventMod=0)    ; No modifier key used
$ALT		 DEFINE	   (#EventMod=1)    ; Alt key used
$CTL		 DEFINE	   (#EventMod=2)    ; Ctrl key used
$CTL_$ALT	 DEFINE	   (#EventMod=3)    ; Ctrl & Alt keys used together
$SHIFT		 DEFINE	   (#EventMod=4)    ; Shift key	used
;$ALT_$SHIFT	 DEFINE	   NOP		    ; No code generated. Not supported
$CTL_$SHIFT	 DEFINE	   (#EventMod=6)    ; Ctrl & Shift keys	used together
$CTL_$ALT_$SHIFT DEFINE	   (#EventMod=7)    ; Ctrl, Alt	& Shift	keys together
;
; Event Modifier values for events: MouseDown, MouseUp, MouseWheel, & KeyPress
; 
$ALT_MOD	 DEFINE	1	; Event Modifier value for ALT key
$CTRL_MOD	 DEFINE	2	; Event Modifier value for CTRL key
$SHIFT_MOD	 DEFINE 4	; Event Modifier value for SHIFT key
$LEFTBUTTON_MOD	 DEFINE	8	; Event Modifier value for Left Mouse Button
$RIGHTBUTTON_MOD DEFINE 16	; Event Modifier value for Right Mouse Button
$DBLCLICK_MOD	 DEFINE 32	; Event Modifier value for Double Click
$WHEEL_MOD	 DEFINE 64	; Event Modifier value for Mouse Wheel event
;
*---End	PLBDEF Definitions-----------------------------------------------------
.
	 %ENDIF			       ;PLBDEF				  8.2
.
	 %IF $PLBCONST = 1	       ;1 ==> Include these CONST	  8.2
.
*===Begin KEYPRESS CONST values================================================
.
.   Definitions	of Windows Virtual Key Result Values for $KEYPRESS Events
.------------------------------------------------------------------------------
.
$vkyBreak  const   "3"			. ctrl/Break key     (only with	Ctrl: mod=2)
$vkyBksp   const   "8"			. Backspace	     (can shift)
.   ctrl/bksp appears as char='I', mod=2 (ctrl)
$vkyEnter  const   "13"			. Enter	key	     (can shift	and/or ctrl)
$vkyPause  const   "19"			. Pause	key	     (can shift)
$vkyCaps   const   "20"			. Caps lock toggle   (can shift)
$vkyNumLk  const   "144"		. Num lock toggle    (can shift)
$vkyScroll const   "145"		. Scroll lock toggle (can shift)
$vkyEsc	   const   "27"			. Escape key	     (can shift)
$vkyPgUp   const   "33"			. shift	and ctrl are possible
$vkyPgDn   const   "34"			.     (ditto)
$vkyEnd	   const   "35"			.     (ditto)
$vkyHome   const   "36"			.     (ditto)
$vkyLFA	   const   "37"			. arrow	keys (ditto)
$vkyUPA	   const   "38"			.     (ditto)
$vkyRTA	   const   "39"			.     (ditto)
$vkyDNA	   const   "40"			.     (ditto)
$vkyIns	   const   "45"			.     (ditto)
$vkyDel	   const   "46"			.     (ditto)
$vkyStar   const   "106"		. Ctrl Gray * key (only	with Ctrl)
$vkyPlus   const   "107"		. Ctrl Gray + key (only	with Ctrl)
$vkyMinus  const   "109"		. Ctrl Gray - key (only	with Ctrl)
$vkySlash  const   "111"		. Ctrl Gray / key (only	with Ctrl)
$vkyF1	   const   "112"		. shift	and ctrl are possible
$vkyF2	   const   "113"		.     (ditto)
$vkyF3	   const   "114"		.     (ditto)
$vkyF4	   const   "115"		.     (ditto)
$vkyF5	   const   "116"		.     (ditto)
$vkyF6	   const   "117"		.     (ditto)
$vkyF7	   const   "118"		.     (ditto)
$vkyF8	   const   "119"		.     (ditto)
$vkyF9	   const   "120"		.     (ditto)
$vkyF10	   const   "121"		.     (ditto)
$vkyF11	   const   "122"		.     (ditto)
$vkyF12	   const   "123"		.     (ditto)
.
*---End	KEYPRESS CONST values-------------------------------------------------
.
	 %ENDIF			       ;PLBCONST			  8.2
.
	 %IF $PLBALERT = 1	       ;1 ==> Include ALERT integers	  8.3f
.
*===Begin ALERT	TYPE Integer values===========================================
.
.   Definitions	of Windows MessageBox type values and result values.
.-----------------------------------------------------------------------------
.
.
$MB_OK		     INTEGER 4,"0x000000"   - OK Button
$MB_OKCANCEL	     INTEGER 4,"0x000001"   - OK/CANCEL	buttons
$MB_ABORTRETRYIGNORE INTEGER 4,"0x000002"   - ABORT/RETRY/IGNORE
$MB_YESNOCANCEL	     INTEGER 4,"0x000003"   - YES/NO/CANCEL
$MB_YESNO	     INTEGER 4,"0x000004"   - YES/NO
$MB_RETRYCANCEL	     INTEGER 4,"0x000005"   - RETRY/CANCEL
.
$MB_ICONSTOP	     INTEGER 4,"0x000010"   - Stop-sign	icon
$MB_QUESTION	     INTEGER 4,"0x000020"   - Question-mark icon
$MB_ICONQUESTION     INTEGER 4,"0x000020"   - Question-mark icon	  9.8A
$MB_ICONEXCLAMATION  INTEGER 4,"0x000030"   - Exclamation-point	ico
$MB_ICONINFORMATION  INTEGER 4,"0x000040"   - Information 'i' icon
.
$MB_DEFBUTTON1	     INTEGER 4,"0x000000"   - Default button one
$MB_DEFBUTTON2	     INTEGER 4,"0x000100"   - Default button two
$MB_DEFBUTTON3	     INTEGER 4,"0x000200"   - Default button three
$MB_DEFBUTTON4	     INTEGER 4,"0x000400"   - Default button four
.
$MB_SETFOREGROUND    INTEGER 4,"0x010000"   - Set foreground window
$MB_RIGHT	     INTEGER 4,"0x080000"   - Text right justified
.
$MB_RTLREADING	     INTEGER 4,"0x100000"   - Right to left reading
.
$IDOK	   CONST   "1"		- OK button was	selected.
$IDCANCEL  CONST   "2"		- CANCEL button	was selected.
$IDABORT   CONST   "3"		- ABORT	button was selected.
$IDRETRY   CONST   "4"		- RETRY	button was selected.
$IDIGNORE  CONST   "5"		- IGNORE button	was selected.
$IDYES	   CONST   "6"		- YES button was selected.
$IDNO	   CONST   "7"		- NO button was	selected.
.
*---End	ALERT TYPE values------------------------------------------------------
.
	 %ENDIF				;PLBALERT			  8.3f
.
	 %IF $PLBDTYPE = 1		;1 ==> Include DTYPE equates	  8.5A
.
*===Begin DTYPE	Equate values=================================================
.
.   Definitions	of TYPE instruction, compiler DTYPE operator, compiler
.   DTYPEBASE operator, and compiler DTYPESUB operator values.
.-----------------------------------------------------------------------------
. Language reference TRUE types	reflected by the TYPE instruction accessing
. data variables in the PLB program UDA.
. 
.    Note:
.       1. All data variable used by the TYPE instruction MUST exist
.          in the program UDA.
.          
.       2. The PLB data contruct references like EQUATE, PROFILE,
.          EQUCMDLIN, and RECORDDEF are NOT available for the TYPE
.          instruction because the DO NOT exist in the PLB program UDA.
.          These PLB data contruct references are ONLY used by the
.          compiler when compiling a program.
.
$T_VARLIST	EQU  0x0004		;True type for variable in UDA
$T_FORM		EQU  0x0010		;True type for variable in UDA
$T_FILELIST	EQU  0x0014		;True type for variable in UDA
$T_DIM		EQU  0x0020		;True type for variable in UDA
$T_FILE		EQU  0x0040		;True type for variable in UDA
$T_IFILE	EQU  0x0041		;True type for variable in UDA
$T_AFILE	EQU  0x0042		;True type for variable in UDA
$T_PFILE	EQU  0x0043		;True type for variable in UDA
$T_SNDFILE	EQU  0x0044		;True type for variable in UDA
$T_DBFILE	EQU  0x0045		;True type for variable in UDA
$T_BFILE	EQU  0x0046		;True type for variable in UDA
$T_COMFILE	EQU  0x0047		;True type for variable in UDA
$T_ADMIN	EQU  0x0049		;True type for variable in UDA
$T_XFILE        EQU  0x004B             ;True type for variable in UDA    9.5A
$T_FORMLITERAL	EQU  0x0110		;FORM Literal			  9.5A
$T_DIMLITERAL	EQU  0x0120		;DIM Literal			  9.5A
$T_INTEGER	EQU  0x0108		;True type for variable in UDA
$T_INTEGER1	EQU  0x0108		;Integer 1 True type for variable in UDA
$T_INTEGER2	EQU  0x0208		;Integer 2 True type for variable in UDA
$T_INTEGER3	EQU  0x0308		;Integer 3 True type for variable in UDA
$T_INTEGER4	EQU  0x0408		;Integer 4 True type for variable in UDA
$T_INTEGER8	EQU  0x0808		;Integer 8 True type for variable in UDA
.
$T_BUTTON	EQU  0x0130		;True type for object in UDA
$T_CHECKBOX	EQU  0x0230		;True type for object in UDA
$T_CHECKGRP	EQU  0x0330		;True type for object in UDA
$T_DATALIST	EQU  0x0430		;True type for object in UDA
$T_DIALOG	EQU  0x0530		;True type for object in UDA
$T_EDITTEXT	EQU  0x0630 		;True type for object in UDA
$T_ICON		EQU  0x0730		;True type for object in UDA
$T_MENU		EQU  0x0830		;True type for object in UDA
$T_MREGION	EQU  0x0930		;True type for object in UDA
$T_MOVIE	EQU  0x0A30		;True type for object in UDA
$T_PICT		EQU  0x0B30		;True type for object in UDA
$T_POPUPMENU	EQU  0x0C30		;True type for object in UDA
$T_RADIOGRP	EQU  0x0D30		;True type for object in UDA
$T_RADIO	EQU  0x0E30		;True type for object in UDA
$T_SUBMENU	EQU  0x0F30		;True type for object in UDA
$T_STATTEXT	EQU  0x1030		;True type for object in UDA
$T_TIMER	EQU  0x1130		;True type for object in UDA
$T_COLOR	EQU  0x1230		;True type for object in UDA
$T_FLOATMENU	EQU  0x1330		;True type for object in UDA
$T_FONT		EQU  0x1430		;True type for object in UDA
$T_GROUPBOX	EQU  0x1530		;True type for object in UDA
$T_IMAGELIST	EQU  0x1630		;True type for object in UDA
$T_LISTVIEW	EQU  0x1730		;True type for object in UDA
$T_PROGRESS	EQU  0x1830		;True type for object in UDA
$T_HSCROLLBAR	EQU  0x1930		;True type for object in UDA
$T_VSCROLLBAR	EQU  0x1A30		;True type for object in UDA
$T_STATUSBAR	EQU  0x1B30		;True type for object in UDA
$T_TREEVIEW	EQU  0x1C30		;True type for object in UDA
$T_TOOLBAR	EQU  0x1D30		;True type for object in UDA
$T_WINDOW	EQU  0x1E30		;True type for object in UDA
$T_COMBOBOX	EQU  0x1F30		;True type for object in UDA
$T_SHAPE	EQU  0x2030		;True type for object in UDA
$T_SLIDER	EQU  0x2130		;True type for object in UDA
$T_TABCONTROL	EQU  0x2230		;True type for object in UDA
$T_COLLECTION	EQU  0x2330		;True type for object in UDA
$T_PLBFORM	EQU  0x2430		;True type for object in UDA
$T_LINE		EQU  0x2530		;True type for object in UDA
$T_AUTOMATION	EQU  0x2630		;True type for object in UDA
$T_CONTAINER	EQU  0x2730		;True type for object in UDA
$T_CONTROL	EQU  0x2830		;True type for object in UDA
$T_VARIANT	EQU  0x2930		;True type for object in UDA
$T_MAINWINDOW	EQU  0x2B30		;True type for object in UDA
$T_STATUSPANEL	EQU  0x2C30		;True type for object in UDA
$T_TOOLBUTTON	EQU  0x2D30		;True type for object in UDA
$T_SPLITTER	EQU  0x2E30		;True type for object in UDA
$T_PANEL	EQU  0x2F30		;True type for object in UDA
$T_EDITNUMBER	EQU  0x3030		;True type for object in UDA
$T_EDITDATETIME	EQU  0x3130		;True type for object in UDA
$T_LABELTEXT	EQU  0x3230		;True type for object in UDA
$T_ANIMATE	EQU  0x3330		;True type for object in UDA
$T_MENUITEM	EQU  0x3430		;True type for object in UDA
$T_RICHEDITTEXT	EQU  0x3530		;True type for object in UDA
$T_GENERIC	EQU  0x3630		;True type for object in UDA
$T_NETOBJECT	EQU  0x3730		;True type for object in UDA	  9.3
$T_NETCONTROL	EQU  0x3830		;True type for object in UDA	  9.3
$T_CLIENT	EQU  0x3930		;True type for object in UDA	  9.7
$T_RUNTIME	EQU  0x3A30		;True type for object in UDA	  9.7
$T_XDATA	EQU  0x3B30		;True type for object in UDA	  9.8A
$T_HTMLCONTROL	EQU  0x3C30		;True type for object in UDA	  10.0A
$T_ERROR	EQU  0x3D30		;True type for object in UDA	  10.1
$T_DATATABLE	EQU  0x4330		;True type for object in UDA	  10.5
.
.-----------------------------------------------------------------------------
. Language reference Data Variable Label types reflected by the compiler
. pseudo command DTYPE(label) operator.
. 
.    Note:
.       1. The DTYPE label type values are determined by the PLBCMP compiler
.          as determined from the symbol table references used to compile
.          the program.
.
.       2. The DTYPE label type values MAY NOT be exactly the same as
.          compared to the TYPE instruction data variable types. For example,
.          the INTEGER data variable types are different.
.
.       3. In addition, PLB data contruct references like EQUATE, PROFILE,
.          EQUCMDLIN, and RECORDDEF are available for the DTYPE compiler
.          operation. But these same PLB data contruct references DO NOT
.          exist for the TYPE isntruciton.
.
$DT_VARLIST	EQU  0x0004		;True type for variable compiled
$DT_INTEGER	EQU  0x0008		;True type for variable compiled
$DT_FORM	EQU  0x0010		;True type for variable compiled
$DT_FILELIST	EQU  0x0014		;True type for variable compiled
$DT_DIM		EQU  0x0020		;True type for variable compiled
$DT_FILE	EQU  0x0040		;True type for variable compiled
$DT_IFILE	EQU  0x0041		;True type for variable compiled
$DT_AFILE	EQU  0x0042		;True type for variable compiled
$DT_PFILE	EQU  0x0043		;True type for variable compiled
$DT_SNDFILE	EQU  0x0044		;True type for variable compiled
$DT_DBFILE	EQU  0x0045		;True type for variable compiled
$DT_BFILE	EQU  0x0046		;True type for variable compiled
$DT_COMFILE	EQU  0x0047		;True type for variable compiled
$DT_ADMIN	EQU  0x0049		;True type for variable compiled
$DT_XFILE       EQU  0x004B             ;True type for variable compiled  9.5A
$DT_PROFILE	EQU  0x007B		;True type for variable compiled
$DT_EQUCMDLIN	EQU  0x007C		;True type for variable compiled
$DT_EQU		EQU  0x007D		;True type for variable compiled
$DT_RECORD	EQU  0x0104		;True type for variable compiled
$DT_RECORDEF	EQU  0x0204		;True type for variable compiled
.
$DT_BUTTON	EQU  0x0130		;True type for object compiled
$DT_CHECKBOX	EQU  0x0230		;True type for object compiled
$DT_CHECKGRP	EQU  0x0330		;True type for object compiled
$DT_DATALIST	EQU  0x0430		;True type for object compiled
$DT_DIALOG	EQU  0x0530		;True type for object compiled
$DT_EDITTEXT	EQU  0x0630 		;True type for object compiled
$DT_ICON	EQU  0x0730		;True type for object compiled
$DT_MENU	EQU  0x0830		;True type for object compiled
$DT_MREGION	EQU  0x0930		;True type for object compiled
$DT_MOVIE	EQU  0x0A30		;True type for object compiled
$DT_PICT	EQU  0x0B30		;True type for object compiled
$DT_POPUPMENU	EQU  0x0C30		;True type for object compiled
$DT_RADIOGRP	EQU  0x0D30		;True type for object compiled
$DT_RADIO	EQU  0x0E30		;True type for object compiled
$DT_SUBMENU	EQU  0x0F30		;True type for object compiled
$DT_STATTEXT	EQU  0x1030		;True type for object compiled
$DT_TIMER	EQU  0x1130		;True type for object compiled
$DT_COLOR	EQU  0x1230		;True type for object compiled
$DT_FLOATMENU	EQU  0x1330		;True type for object compiled
$DT_FONT	EQU  0x1430		;True type for object compiled
$DT_GROUPBOX	EQU  0x1530		;True type for object compiled
$DT_IMAGELIST	EQU  0x1630		;True type for object compiled
$DT_LISTVIEW	EQU  0x1730		;True type for object compiled
$DT_PROGRESS	EQU  0x1830		;True type for object compiled
$DT_HSCROLLBAR	EQU  0x1930		;True type for object compiled
$DT_VSCROLLBAR	EQU  0x1A30		;True type for object compiled
$DT_STATUSBAR	EQU  0x1B30		;True type for object compiled
$DT_TREEVIEW	EQU  0x1C30		;True type for object compiled
$DT_TOOLBAR	EQU  0x1D30		;True type for object compiled
$DT_WINDOW	EQU  0x1E30		;True type for object compiled
$DT_COMBOBOX	EQU  0x1F30		;True type for object compiled
$DT_SHAPE	EQU  0x2030		;True type for object compiled
$DT_SLIDER	EQU  0x2130		;True type for object compiled
$DT_TABCONTROL	EQU  0x2230		;True type for object compiled
$DT_COLLECTION	EQU  0x2330		;True type for object compiled
$DT_PLBFORM	EQU  0x2430		;True type for object compiled
$DT_LINE	EQU  0x2530		;True type for object compiled
$DT_AUTOMATION	EQU  0x2630		;True type for object compiled
$DT_CONTAINER	EQU  0x2730		;True type for object compiled
$DT_CONTROL	EQU  0x2830		;True type for object compiled
$DT_VARIANT	EQU  0x2930		;True type for object compiled
$DT_MAINWINDOW	EQU  0x2B30		;True type for object compiled
$DT_STATUSPANEL	EQU  0x2C30		;True type for object compiled
$DT_TOOLBUTTON	EQU  0x2D30		;True type for object compiled
$DT_SPLITTER	EQU  0x2E30		;True type for object compiled
$DT_PANEL	EQU  0x2F30		;True type for object compiled
$DT_EDITNUMBER	EQU  0x3030		;True type for object compiled
$DT_EDITDATETIME EQU  0x3130		;True type for object compiled
$DT_LABELTEXT	EQU  0x3230		;True type for object compiled
$DT_ANIMATE	EQU  0x3330		;True type for object compiled
$DT_MENUITEM	EQU  0x3430		;True type for object compiled
$DT_RICHEDITTEXT EQU  0x3530		;True type for object compiled
$DT_GENERIC	EQU  0x3630		;True type for object compiled
$DT_NETOBJECT	EQU  0x3730		;True type for object compiled	  9.3
$DT_NETCONTROL	EQU  0x3830		;True type for object compiled	  9.3
$DT_CLIENT	EQU  0x3930		;True type for object compiled	  9.7
$DT_RUNTIME	EQU  0x3A30		;True type for object compiled	  9.7
$DT_XDATA	EQU  0x3B30		;True type for object compiled	  9.8A
$DT_HTMLCONTROL EQU  0x3C30		;True type for object compiled	  10.0A
$DT_ERROR	EQU  0x3D30		;True type for object compiled	  10.1
.
.-----------------------------------------------------------------------------
. Language reference BASE types	reflected by pseudo command DTYPEBASE(label)
. operator.
.
$BT_RECORD	EQU  0x0004		;Base type for variable
$BT_RECORDEF	EQU  0x0004		;Base type for variable
$BT_VARLIST	EQU  0x0004		;Base type for variable
$BT_INTEGER	EQU  0x0008		;Base type for variable
$BT_FORM	EQU  0x0010		;Base type for variable
$BT_FILELIST	EQU  0x0014		;Base type for variable
$BT_DIM		EQU  0x0020		;Base type for variable
$BT_FILE	EQU  0x0040		;Base type for variable
$BT_IFILE	EQU  0x0041		;Base type for variable
$BT_AFILE	EQU  0x0042		;Base type for variable
$BT_PFILE	EQU  0x0043		;Base type for variable
$BT_DBFILE	EQU  0x0045		;Base type for variable
$BT_BFILE	EQU  0x0046		;Base type for variable
$BT_COMFILE	EQU  0x0047		;Base type for variable
$BT_PROFILE	EQU  0x007B		;Base type for variable
$BT_EQUCMDLIN	EQU  0x007C		;Base type for variable
$BT_EQU		EQU  0x007D		;Base type for variable
.
$BT_BUTTON	EQU  0x0030		;Base type for object
$BT_CHECKBOX	EQU  0x0030		;Base type for object
$BT_CHECKGRP	EQU  0x0030		;Base type for object
$BT_DATALIST	EQU  0x0030		;Base type for object
$BT_DIALOG	EQU  0x0030		;Base type for object
$BT_EDITTEXT	EQU  0x0030		;Base type for object
$BT_ICON	EQU  0x0030		;Base type for object
$BT_MENU	EQU  0x0030		;Base type for object
$BT_MREGION	EQU  0x0030		;Base type for object
$BT_MOVIE	EQU  0x0030		;Base type for object
$BT_PICT	EQU  0x0030		;Base type for object
$BT_POPUPMENU	EQU  0x0030		;Base type for object
$BT_RADIO	EQU  0x0030		;Base type for object
$BT_RADIOGRP	EQU  0x0030		;Base type for object
$BT_SUBMENU	EQU  0x0030		;Base type for object
$BT_STATTEXT	EQU  0x0030		;Base type for object
$BT_TIMER	EQU  0x0030		;Base type for object
$BT_COLOR	EQU  0x0030		;Base type for object
$BT_FLOATMENU	EQU  0x0030		;Base type for object
$BT_FONT	EQU  0x0030		;Base type for object
$BT_GROUPBOX	EQU  0x0030		;Base type for object
$BT_IMAGELIST	EQU  0x0030		;Base type for object
$BT_LISTVIEW	EQU  0x0030		;Base type for object
$BT_PROGRESS	EQU  0x0030		;Base type for object
$BT_HSCROLLBAR	EQU  0x0030		;Base type for object
$BT_VSCROLLBAR	EQU  0x0030		;Base type for object
$BT_STATUSBAR	EQU  0x0030		;Base type for object
$BT_TREEVIEW	EQU  0x0030		;Base type for object
$BT_TOOLBAR	EQU  0x0030		;Base type for object
$BT_WINDOW	EQU  0x0030		;Base type for object
$BT_COMBOBOX	EQU  0x0030		;Base type for object
$BT_SHAPE	EQU  0x0030		;Base type for object
$BT_SLIDER	EQU  0x0030		;Base type for object
$BT_TABCONTROL	EQU  0x0030		;Base type for object
$BT_COLLECTION	EQU  0x0030		;Base type for object
$BT_PLBFORM	EQU  0x0030		;Base type for object
$BT_LINE	EQU  0x0030		;Base type for object
$BT_AUTOMATION	EQU  0x0030		;Base type for object
$BT_CONTAINER	EQU  0x0030		;Base type for object
$BT_CONTROL	EQU  0x0030		;Base type for object
$BT_VARIANT	EQU  0x0030		;Base type for object
$BT_MAINWINDOW	EQU  0x0030		;Base type for object
$BT_STATUSPANEL	EQU  0x0030		;Base type for object
$BT_TOOLBUTTON	EQU  0x0030		;Base type for object
$BT_SPLITTER	EQU  0x0030		;Base type for object
$BT_PANEL	EQU  0x0030		;Base type for object
$BT_EDITNUMBER	EQU  0x0030		;Base type for object
$BT_EDITDATETIME EQU 0x0030		;Base type for object
$BT_LABELTEXT	EQU  0x0030		;Base type for object
$BT_ANIMATE	EQU  0x0030		;Base type for object
$BT_MENUITEM	EQU  0x0030		;Base type for object
$BT_RICHEDITTEXT EQU 0x0030		;Base type for object
$BT_GENERIC	EQU  0x0030		;Base type for object
$BT_NETOBJECT	EQU  0x0030		;Base type for object		  9.3
$BT_NETCONTROL	EQU  0x0030		;Base type for object		  9.3
$BT_CLIENT	EQU  0x0030		;Base type for object		  9.7
$BT_RUNTIME	EQU  0x0030		;Base type for object		  9.7
$BT_XDATA	EQU  0x0030		;Base type for object		  9.8A
$BT_HTMLCONTROL EQU  0x0030             ;Base type for object		  10.0A
$BT_ERROR	EQU  0x0030		;Base type for object		  10.1
.
.-----------------------------------------------------------------------------
. Language reference SUB types reflected by pseudo command DTYPESUB(label)
. operator.
.
$ST_DIM		EQU  0x00		;Sub type for variable
$ST_FORM	EQU  0x00		;Sub type for variable
$ST_INTEGER1	EQU  0x01		;Sub type for variable INTEGER 1
$ST_INTEGER2	EQU  0x02		;Sub type for variable INTEGER 2
$ST_INTEGER3	EQU  0x03		;Sub type for variable INTEGER 3
$ST_INTEGER4	EQU  0x04		;Sub type for variable INTEGER 4
$ST_INTEGER8	EQU  0x08		;Sub type for variable INTEGER 8
$ST_FILE	EQU  0x00		;Sub type for variable
$ST_FILELIST	EQU  0x00		;Sub type for variable
$ST_IFILE	EQU  0x00		;Sub type for variable
$ST_AFILE	EQU  0x00		;Sub type for variable
$ST_VARLIST	EQU  0x00		;Sub type for variable
$ST_EQU		EQU  0x00		;Sub type for variable
$ST_EQUCMDLIN	EQU  0x00		;Sub type for variable
$ST_DBFILE	EQU  0x00		;Sub type for variable
$ST_PFILE	EQU  0x00		;Sub type for variable
$ST_BFILE	EQU  0x00		;Sub type for variable
$ST_COMFILE	EQU  0x00		;Sub type for variable
$ST_PROFILE	EQU  0x00		;Sub type for variable
$ST_RECORD	EQU  0x01		;Sub type for variable
$ST_RECORDEF	EQU  0x02		;Sub type for variable
.
$ST_BUTTON	EQU  0x01		;Sub type for object
$ST_CHECKBOX	EQU  0x02		;Sub type for object
$ST_CHECKGRP	EQU  0x03		;Sub type for object
$ST_DATALIST	EQU  0x04		;Sub type for object
$ST_DIALOG	EQU  0x05		;Sub type for object
$ST_EDITTEXT	EQU  0x06		;Sub type for object
$ST_ICON	EQU  0x07		;Sub type for object
$ST_MENU	EQU  0x08		;Sub type for object
$ST_MREGION	EQU  0x09		;Sub type for object
$ST_MOVIE	EQU  0x0A		;Sub type for object
$ST_PICT	EQU  0x0B		;Sub type for object
$ST_POPUPMENU	EQU  0x0C		;Sub type for object
$ST_RADIOGRP	EQU  0x0D		;Sub type for object
$ST_RADIO	EQU  0x0E		;Sub type for object
$ST_SUBMENU	EQU  0x0F		;Sub type for object
$ST_STATTEXT	EQU  0x10		;Sub type for object
$ST_TIMER	EQU  0x11		;Sub type for object
$ST_COLOR	EQU  0x12		;Sub type for object
$ST_FLOATMENU	EQU  0x13		;Sub type for object
$ST_FONT	EQU  0x14		;Sub type for object
$ST_GROUPBOX	EQU  0x15		;Sub type for object
$ST_IMAGELIST	EQU  0x16		;Sub type for object
$ST_LISTVIEW	EQU  0x17		;Sub type for object
$ST_PROGRESS	EQU  0x18		;Sub type for object
$ST_HSCROLLBAR	EQU  0x19		;Sub type for object
$ST_VSCROLLBAR	EQU  0x1A		;Sub type for object
$ST_STATUSBAR	EQU  0x1B		;Sub type for object
$ST_TREEVIEW	EQU  0x1C		;Sub type for object
$ST_TOOLBAR	EQU  0x1D		;Sub type for object
$ST_WINDOW	EQU  0x1E		;Sub type for object
$ST_COMBOBOX	EQU  0x1F		;Sub type for object
$ST_SHAPE	EQU  0x20		;Sub type for object
$ST_SLIDE	EQU  0x21		;Sub type for object
$ST_TABCONTROL	EQU  0x22		;Sub type for object
$ST_COLLECTION	EQU  0x23		;Sub type for object
$ST_PLBFORM	EQU  0x24		;Sub type for object
$ST_LINE	EQU  0x25		;Sub type for object
$ST_AUTOMATION	EQU  0x26		;Sub type for object
$ST_CONTAINER	EQU  0x27		;Sub type for object
$ST_CONTROL	EQU  0x28		;Sub type for object
$ST_VARIANT	EQU  0x29		;Sub type for object
$ST_MAINWINDOW	EQU  0x2B		;Sub type for object
$ST_STATUSPANEL	EQU  0x2C		;Sub type for object
$ST_TOOLBUTTON	EQU  0x2D		;Sub type for object
$ST_SPLITTER	EQU  0x2E		;Sub type for object
$ST_PANEL	EQU  0x2F		;Sub type for object
$ST_EDITNUMBER	EQU  0x30		;Sub type for object
$ST_EDITDATETIME EQU 0x31		;Sub type for object
$ST_LABELTEXT	EQU  0x32		;Sub type for object
$ST_ANIMATE	EQU  0x33		;Sub type for object
$ST_MENUITEM	EQU  0x34		;Sub type for object
$ST_RICHEDITTEXT EQU 0x35		;Sub type for object
$ST_GENERIC	EQU  0x36		;Sub type for object
$ST_NETOBJECT	EQU  0x37		;Sub type for object		  9.3
$ST_NETCONTROL	EQU  0x38		;Sub type for object		  9.3	
$ST_CLIENT	EQU  0x39		;Sub type for object		  9.7
$ST_RUNTIME	EQU  0x3A		;Sub type for object		  9.7
$ST_XDATA	EQU  0x3B		;Sub type for object		  9.8A
$ST_HTMLCONTROL EQU  0x3C               ;Sub type for object		  10.0A
$ST_ERROR	EQU  0x3D		;Sub type for object		  10.1
.
*---End	DTYPE Equate values----------------------------------------------------
.
	 %ENDIF				;PLBDTYPE			  8.5A
.
	 %IF $PLBXFILE = 1		;1 ==> Include XFILE mode values  9.3
.
*===Begin XFILE	Equate values=================================================
.
.   Definitions	of XFILE Open values.
.-----------------------------------------------------------------------------
.
$XFILE_NOCASE		INTEGER 4,"0x00000001"	;Data field and record set
						;  labels are not case
						;  sensitive.
$XFILE_CLOSEDSCHEMA	INTEGER	4,"0x00000002"	;Do not allow additions to
						;  schema.
$XFILE_KEEPOPEN		INTEGER	4,"0x00000004"	;Keep the physical file open.
$XFILE_WRITESCHEMA	INTEGER	4,"0x00000008"	;Write out the schema on a
						;  FLUSH or CLOSE statement.
$XFILE_NOLOADSCHEMA	INTEGER	4,"0x00000010"	;Do not load the schema from
						;  disk.
$XFILE_NOEMPTYFIELDS	INTEGER	4,"0x00000020"	;Error on reading an empty
						;  field.
$XFILE_ALLCHARS		INTEGER	4,"0x00000080"	;Allow all characters to be
						;  read for all XML data
						;  fields. When this bit mode
						;  is used, the character
						;  values less than 0x20 are
						;  not substituted by a white
						;  space.
$XFILE_OPENREADONLY	INTEGER	4,"0x00000100"	;Open XML and schema in READ
						;  Only. (9.1)
$XFILE_WRTISO8859       INTEGER 4,"0x00000200"  ;Encoding is set for ISO8859.
                                                ;  This allows 8-bit character
                                                ;  values in the XML file.
$XFILE_DROPEMPTYFIELDS	INTEGER 4,"0x00000400"  ;Do not output empty fields
$XFILE_FILTERNOCASE	INTEGER	4,"0x00000800"	;Filtered READS are not case
						; sensitive.
$XFILE_XMLOUTFMTUSETABS INTEGER 4,"0x00001000"  ;Use a tab character to indent
                                                ; when outputting XML tags.
$XFILE_XMLOUTFMTSPCSUPRESS INTEGER 4,"0x00002000" ;Suppress leading and
                                                  ; trailing spaces when
                                                  ; outputting XML data.
$XFILE_XMLOUTFMTESCALWAYS INTEGER 4,"0x00004000" ;Always escape double-quote
                                                 ; (") and single-quote (')
                                                 ; characters. 
$XFILE_XMLOUTFMTCVTTOSPC INTEGER 4,"0x00008000" ;Convert any character less
                                                ; than 0x20 to 0x20.
$XFILE_XMLOUTFMTNOEOR4BLKS INTEGER 4,"0x00010000" ;No CRLF after <starttag>
                                                ; when XML element is all
                                                ; blank characters.
.
*---End	XFILE Equate values----------------------------------------------------
.
	 %ENDIF				;PLBDTYPE			  8.5A
.
	 %IF $PLBGRAPHIC = 1		;1 ==> Include graphic values	  9.3
.
*===Begin Special Graphic values==============================================
.
.   Default UTF16 Graphic Values For ANSI
.
.-----------------------------------------------------------------------------
. ANSI Screen Definition values for Special Graphic Characters.
.
$GRAPHIC_HLN	INTEGER	2,"0x00C4"	;Horizontal single line		  9.3
$GRAPHIC_VLN	INTEGER	2,"0x00B3"	;Vertical single line		  9.3
$GRAPHIC_HLNDD	INTEGER	2,"0x00CD"	;Horizontal double line		  9.3
$GRAPHIC_VLNDD	INTEGER	2,"0x00CD"	;Vertical double line 		  9.3
$GRAPHIC_LFA	INTEGER	2,"0x001B"	;Left Arrow			  9.3
$GRAPHIC_RTA	INTEGER	2,"0x001A"	;Right Arrow 			  9.3
$GRAPHIC_UPA	INTEGER	2,"0x0018"	;Up Arrow              		  9.3
$GRAPHIC_DNA	INTEGER	2,"0x0019"	;Down Arrow   			  9.3
$GRAPHIC_ULC	INTEGER	2,"0x00DA"	;Upper left single corner 	  9.3
$GRAPHIC_DTK	INTEGER	2,"0x00C2"	;Down tick single lines		  9.3
$GRAPHIC_URC	INTEGER	2,"0x00BF"	;Upper right single corner	  9.3
$GRAPHIC_RTK	INTEGER	2,"0x00C3"	;Right tick single lines	  9.3
$GRAPHIC_CRS	INTEGER	2,"0x00C5"	;Cross single lines		  9.3
$GRAPHIC_LTK	INTEGER	2,"0x00B4"	;Left tick single lines		  9.3
$GRAPHIC_LLC	INTEGER	2,"0x00C0"	;Lower left single corner 	  9.3
$GRAPHIC_UTK	INTEGER	2,"0x00C1"	;Up tick single lines		  9.3
$GRAPHIC_LRC	INTEGER	2,"0x00D9"	;Lower right single corner	  9.3
$GRAPHIC_ULCSD	INTEGER	2,"0x00D6"	;Upper left single hor double ver corner  9.3
$GRAPHIC_DTKSD	INTEGER	2,"0x00D2"	;Down tick single hor double ver lines	  9.3
$GRAPHIC_URCSD	INTEGER	2,"0x00B7"	;Upper right single hor double ver corner 9.3
$GRAPHIC_RTKSD	INTEGER	2,"0x00C7"	;Right tick single hor double ver lines	  9.3
$GRAPHIC_CRSSD	INTEGER	2,"0x00D7"	;Cross single hor double ver lines	  9.3
$GRAPHIC_LTKSD	INTEGER	2,"0x00B6"	;Left tick single hor double ver lines	  9.3
$GRAPHIC_LLCSD	INTEGER	2,"0x00D3"	;Lower left single hor double ver corner  9.3
$GRAPHIC_UTKSD	INTEGER	2,"0x00D0"	;Up tick single hor double ver lines	  9.3
$GRAPHIC_LRCSD	INTEGER	2,"0x00BD"	;Lower right single hor double ver corner 9.3
$GRAPHIC_ULCDS	INTEGER	2,"0x00D5"	;Upper left double hor single ver corner  9.3
$GRAPHIC_DTKDS	INTEGER	2,"0x00D1"	;Down tick double hor single ver lines	  9.3
$GRAPHIC_URCDS	INTEGER	2,"0x00B8"	;Upper right double hor single ver corner 9.3
$GRAPHIC_RTKDS	INTEGER	2,"0x00C6"	;Right tick double hor single ver lines	  9.3
$GRAPHIC_CRSDS	INTEGER	2,"0x00D8"	;Cross double hor single ver lines	  9.3
$GRAPHIC_LTKDS	INTEGER	2,"0x00B5"	;Left tick double hor single ver lines	  9.3
$GRAPHIC_LLCDS	INTEGER	2,"0x00D4"	;Lower left double hor single ver corner  9.3
$GRAPHIC_UTKDS	INTEGER	2,"0x00CF"	;Up tick double hor single ver lines	  9.3
$GRAPHIC_LRCDS	INTEGER	2,"0x00BE"	;Lower right double hor single ver corner 9.3
$GRAPHIC_ULCDD	INTEGER	2,"0x00C9"	;Upper left double corner	  9.3
$GRAPHIC_DTKDD	INTEGER	2,"0x00CB"	;Down tick double lines		  9.3
$GRAPHIC_URCDD	INTEGER	2,"0x00BB"	;Upper right double corner	  9.3
$GRAPHIC_RTKDD	INTEGER	2,"0x00CC"	;Right tick double lines	  9.3
$GRAPHIC_CRSDD	INTEGER	2,"0x00CE"	;Cross double lines		  9.3
$GRAPHIC_LTKDD	INTEGER	2,"0x00B9"	;Left tick double lines		  9.3
$GRAPHIC_LLCDD	INTEGER	2,"0x00C8"	;Lower left double corner	  9.3
$GRAPHIC_UTKDD	INTEGER	2,"0x00CA"	;Up tick double lines		  9.3
$GRAPHIC_LRCDD	INTEGER	2,"0x00BC"	;Lower right double corner	  9.3
.
*---End Special Graphic values-------------------------------------------------
.
	 %ENDIF				;PLBGRAPHIC			  9.3
.
	 %IF $PLBHTTP = 1	       ;1 ==> Include HTTP integers	  9.5B
.
*===Begin HTTP *FLAGS Integer values===========================================
.
.   The HTTP instruction *FLAGS bit mask values.
.------------------------------------------------------------------------------
.
$HTTP_FLAG_RAWCOMMAND	    INTEGER 4,"0x0001"				  9.5B
$HTTP_FLAG_NOHEADER	    INTEGER 4,"0x0002"				  9.5B
$HTTP_FLAG_JUSTHEADER	    INTEGER 4,"0x0004"				  9.5B
$HTTP_FLAG_SSL		    INTEGER 4,"0x0008"				  9.5B
$HTTP_FLAG_HTTP11	    INTEGER 4,"0x0010"				  9.5B
$HTTP_FLAG_RAW_RESULT	    INTEGER 4,"0x0020"				  9.5B
$HTTP_FLAG_RAWBINARY	    INTEGER 4,"0x0040"				  9.7/10.3B
$HTTP_FLAG_FIRST_RAW_RESULT INTEGER 4,"0x0080"				  9.7C
$HTTP_FLAG_NO_U66           INTEGER 4,"0x0100"				 10.3
$HTTP_FLAG_USESUNSSL	    INTEGER 4,"0x0200"				 10.3A
$HTTP_FLAG_TLSV1            INTEGER 4,"0x0400"				 10.3B
$HTTP_FLAG_TLSV11	    INTEGER 4,"0x0800"				 10.3B
$HTTP_FLAG_TLSV12	    INTEGER 4,"0x1000"				 10.3B
$HTTP_FLAG_USESSLDEFS	    INTEGER 4,"0x2000"				 10.3B
$HTTP_FLAG_USE_IPV6	    INTEGER 4,"0x4000"				 10.7
.
*---End	HTTP *FLAGS values-----------------------------------------------------
.
	 %ENDIF				;PLBHTTP
.
	 %IF $PLBMAILSEND = 1		;1 ==> Include MAILSEND integers 10.3A
.
*===Begin MAILSEND *OPTIONS Integer values===================================
.
.   The MAILSEND instruction *OPTIONS bit mask values.
.------------------------------------------------------------------------------
.
$MAIL_FLAG_OPENSSL	    INTEGER 4,"0x0010"
$MAIL_FLAG_STARTTLS	    INTEGER 4,"0x0080"
$MAIL_FLAG_CONTENT_DISP	    INTEGER 4,"0x0100"	//Use Content-Disposition
$MAIL_FLAG_USESUNSSL	    INTEGER 4,"0x0200"	//Use Sunbelt OpenSSL DLLs
						//  when available. Only
						//  used by Windows PL/B
						//  runtimes.
$MAIL_FLAG_USEIPV6	    INTEGER 4,"0x400"   //Use IPV6 outgoing URL/Address
.
*---End	MAILSEND *OPTIONS values-----------------------------------------------
.
	 %ENDIF				;PLBMAILSEND
.
	 %IF $PLBGETMODE = 1	       ;1 ==> Include GETMODE integers	  9.9A
.
*===Begin GETMODE Integer values===============================================
.
.   The GETMODE instruction *KEYSTATE bit mask values.
.------------------------------------------------------------------------------
.
$GetMode_KeyState_VK_MENU	INTEGER	4,"0x00000001"			  9.9A
$GetMode_KeyState_VK_CONTROL	INTEGER	4,"0x00000002"			  9.9A
$GetMode_KeyState_VK_SHIFT	INTEGER	4,"0x00000004"			  9.9A
$GetMode_KeyState_VK_CAPITOL	INTEGER	4,"0x00000008"			  9.9A
$GetMode_KeyState_VK_NUMLOCK	INTEGER	4,"0x00000010"			  9.9A
$GetMode_KeyState_VK_SCROLL	INTEGER	4,"0x00000020"			  9.9A
.
*---End	GETMODE keyword values-------------------------------------------------
.
	 %ENDIF				;PLBGETMODE

*------------------------------------------------------------------------------
	 %ENDIF				;$PLBEQU_LOADED			  9.1F
.
	 %XREFON   ;Restore cross reference state flag			  9.1E
.
	 LISTON
