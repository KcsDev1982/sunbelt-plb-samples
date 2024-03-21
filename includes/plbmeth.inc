         LISTOFF
.
         %XREFOFF  ;DO NOT include in cross reference!!                   9.1E
.
         %IFNDEF   $PLBMETH
$PLBMETH EQU       1			;Flag that PLBMETH is used.
*==============================================================================
. PLB METHOD support definitions
.
. Last Revision Date:  04 Mar 2024
.
. Revision History:
.
         %IFDEF    $PLBMETH_HISTORY                                      :8.3A
.:: 12 Oct 98 - Create PLB method parameter definitions.                 :8.3
.:: 09 Nov 98 - Added methods for PICT object.                           :8.3a
.:: 11 Dec 98 - Updated for 83b changes.                                 :8.3b
.:: 19 Feb 99 - Added TabStops method reference for DATALIST.            :8.3
.:: 19 Feb 99 - Modified to add internal runtime methods for CONTAINER.  :8.3
.:: 26 Mar 99 - Added GetExtendedStyle and SetExtendedStyle methods for  :8.3A
.::             LISTVIEW object.                                         :8.3A
.:: 07 May 99 - Added LVIS_OVERLAYMASK & LVIS_STATEIMAGEMASK.            :8.3C
.:: 23 Aug 99 - Added LVS_EX_CHECKBOXES.                                 :8.3F
.:: 16 May 00 - Modified to reflect that SORTED is not supported for a   :8.4B
.::             DATALIST in a SETPROP instruction.                       :8.4B
.:: 16 May 00 - Added IMAGECOLORS object for IMAGELIST object.           :8.4B
.:: 25 Sep 00 - Added Change and Double Click events for a TREEVIEW.     :8.4E
.:: 11 Mar 02 - Added new property and method references for LISTVIEW    :8.6B
.::             and TREEVIEW objects.                                    :8.6B
.:: 16 Apr 02 - Added WINDOW object methods for MDI support.             :8.6C
.:: 12 Jun 02 - Added support of methods for STATUSBAR and TOOLBAR,      :8.6D
.:: 26 Aug 02 - Added FormToPict method for WINDOW object.               :8.6E
.:: 26 Aug 02 - Added LoadStdToolBitmap method for IMAGELIST object.     :8.6E
.:: 31 Dec 02 - Added LISTOFF/LISTON control.                            :8.7
.:: 10 Jan 03 - Added methods for VARIANT object.                        :8.7
.:: 14 Jan 03 - Added GetItemState and SetItemState methods for TREEVIEW.:8.7
.:: 27 May 03 - Added AllowEmptyTab method for DATALIST.                 :8.7B
.:: 28 Jul 03 - Updated for COMBOBOX, DATALIST, EDITNUMBER, and          :8.7C
.::             EDITTEXT objects.                                        :8.7C
.:: 26 May 04 - Updated for ANIMATE, FLOATMENU, LISTVIEW, MENU, and      :9.0
.::             SUBMENU objects.                                         :9.0
.:: 23 Jul 04 - Added new RICHEDITTEXT object.                           :9.0B
.:: 23 Jul 04 - Updated LISTVIEW and TREEVIEW objects.                   :9.0B
.:: 17 Mar 05 - Added COLOR object methods.                              :9.0E
.:: 11 Apr 05 - Added GetTopIndex method for LISTVIEW.                   :9.0F
.:: 19 Apr 05 - Added FONT object methods.                               :9.0F
.:: 06 Jun 05 - Added methods for FLOATMENU, MENU, MENUITEM, & SUBMENU.  :9.0F
.:: 20 Jun 05 - Added CF_FORCESCREENFONTOUT for FONT object.             :9.0G
.:: 28 Jun 06 - Updated LISTVIEW, TOOLBAR, and WINDOW objects.           :9.1A
.:: 19 Jul 06 - Updated the FLOATMENU, MENU, SUBMENU, & MENUITEM objects.:9.1C
.:: 18 Sep 06 - Added $LV_SETITEM_REPLACEROW & $LV_SETITEM_SKIPNULL.     :9.1C
.:: 17 Nov 06 - Added $TV_XMLRD_ADDLAST for LoadXmlFile for TREEVIEW.    :9.1C
.:: 19 Jan 07 - Added BrowseForFolder method for a WINDOW object.        :9.1D
.:: 24 Jan 07 - Added %XREFOFF to prevent cross reference output!        :9.1E
.:: 02 Jul 07 - Updated for 9.2 release.				 :9.2
.:: 02 Jul 08 - Updated Listview/Treeview equates for 9.3.		 :9.3
.:: 01 Dec 08 - Reviewed for final 9.3 release.				 :9.3
.:: 15 Jan 09 - Updated for SaveXmlToDim and GetXmlDataSize methods.	 :9.3A
.:: 05 Jun 09 - Updated for 9.3A release.				 :9.3A
.:: 15 Feb 10 - Reviewed for 9.4 release.				 :9.4
.:: 08 Mar 10 - Added Flags option for LISTVIEW SubItemHitTest method.	 :9.4A
.:: 08 Apr 10 - Updated Format option for LISTVIEW SetColumnFormat.	 :9.4B
.:: 28 May 10 - Updated for 9.4B release.                                :9.4B
.:: 09 Jun 10 - Changed TV_XMLWR_OUTPUTALLATTR and TV_XMLWR_ISO8859	 :9.4C
.:: 		label references to have a leading '$' character as per	 :9.4C
.:: 		the PLB Language Reference documentation.		 :9.4C
.:: 09 Jul 10 - Added TABCONTROL methods.				 :9.4C
.:: 09 Aug 10 - Reviewed for 9.4C patch release.			 :9.4C
.:: 25 Oct 10 - Added $LV_GETITEM_ORDERARRAY & $LV_CSVWR_ORDERARRAY.	 :9.4D
.:: 16 Dec 10 - Added $LV_SETITEM_NOBINARYCHARS.			 :9.4D
.:: 05 Jan 11 - Added $LV_XMLWR_OUTPUTHEADER & $LV_XMLWR_NAMEATTR.	 :9.5
.:: 31 Mar 11 - Reviewed for 9.5 release.				 :9.5
.:: 04 Aug 11 - Updated the methods for the WINDOW object.		 :9.5A
.:: 12 Aug 11 - Updated the LISTVIEW methods SetItemTextAll and		 :9.5A
.::		SetColumnWidth to support new parameters.		 :9.5A
.:: 01 Oct 12 - Updated for the 9.6 release.				 :9.6
.:: 08 Mar 13 - Reviewed for 9.6A release.				 :9.6A
.:: 01 Aug 13 - Corrected several typos.				 :9.6B
.:: 14 Feb 14 - Updated for 9.6C release.				 ;9.6C
.:: 02 Sep 14 - Updated for 9.7 release.				 ;9.7
.:: 05 Nov 14 - Added $CHANGE event for BUTTON object using PL/B Web     ;9.7A
.::             Server runtime. Added BUTTON methods named GetFileCount, ;9.7A
.::             GetFileItem, and SetFileOptions.                         ;9.7A
.:: 09 Jan 15 - Updated for 9.7A release.				 ;9.7A
.:: 29 May 15 - Updated for 9.7C release.				 ;9.7C
.:: 01 Oct 15 - Reviewed for 9.8 release.				 :9.8
.:: 06 Jan 16 - Added XDATA object methods.				 :9.8A
.:: 05 Feb 16 - Added new methods for CLIENT and RUNTIME objects.	 :9.8A
.:: 11 Mar 16 - Reviewed for 9.8A release.				 :9.8A
.:: 05 Feb 16 - Added new APPxxx methods for CLIENT object.		 :9.8B
.:: 08 Jun 16 - Added ClientEventOrient for CLIENT object.		 :9.8B
.:: 01 Jul 16 - Reviewed changes for 9.8B patch release.		 :9.8B
.:: 22 Jul 16 - Modified for PL/B Web Server (PWS) IMAGELIST & TREEVIEW	 :9.9
.:: 		objects.						 :9.9
.:: 01 Sep 16 - Added $RUNSUSPEND, $RUNRESUME, and $RUNIDLE events.	 :9.9
.:: 29 Sep 16 - Updated object descriptions to include new properties of :9.9
.::		WEBHEIGHT, WEBLEFT, WEBPOSITION, WEBTOP, and WEBWIDTH.	 :9.9
.::		Also added WEB properties to TREEVIEW and WINDOW objects.:9.9
.:: 01 Oct 16 - Added CLIENT 'GetInfo' option parameter equate values.	 :9.9
.:: 17 Oct 16 - Reviewed for 9.9 release.				 :9.9
.:: 09 Feb 17 - Added Beacon events used for PL/B Web Client apps.	 :9.9A
.:: 01 Mar 17 - Added HttpResponse method for RUNTIME object.		 :9.9A
.:: 09 Mar 15 - Added JqGet, JqSet, AppBeacon, AppBeaconStatus CLIENT    :9.9A
.::		methods and generic methods EnableJqEvent and            :9.9A
.::		DisableJqEvent                                           :9.9A
.:: 22 Mar 17 - Added $HTML_HAS_EVENTS flag for InnerHtml Method	 :9.9A
.::             Added $JQ_FLAG_CSS and $JQ_FLAG_PROP for JqGet/JqSet     :9.9A
.:: 21 Apr 17 - Reviewed for 9.9A release.				 :9.9A
.:: 05 Jul 17 - Added client methods AddJs, AppSetOffline,		 :10.0
.::		AppInstallOffline, AppDirAdd, AppDirDel, AppDirGet,	 :10.0
.::		AppStatusBar						 :10.0
.:: 26 Jul 17 - Added JqmOptions and JqmPage RUNTIME methods		 :10.0
.:: 07 Aug 17 - Added InnerHtml method flags $HTML_FROM_FILE,		 :10.0
.::		$HTML_USE_SCROLLBARS, and $HTML_3D_BORDER		 :10.0
.:: 02 Oct 17 - Reviewed for 10.0 release.				 :10.0
.:: 27 Oct 17 - Added ClientEventPostMessage equate.			 :10.0A
.:: 19 Jan 18 - Updated the InnerHtml method for a PANEL.		 :10.0A
.:: 26 Jan 18 - Added the HTMLCONTROL.					 :10.0A
.:: 16 Feb 18 - Added CODEPAGE property for HTMLCONTROL.		 :10.0A
.:: 02 Apr 18 - Updated for 10.0A patch release.			 :10.0A
.:: 14 Sep 18 - All objects\methods\properties have been updated.	 :10.1
.:: 01 Oct 18 - Added the ERROR object.					 :10.1
.:: 15 Jan 19 - Added the WEBCLASS, WEBHEIGHT, WEBWIDTH, WEBLEFT, WEBTOP,:10.1A
.:: 		and WEBPOSITION properties to the SPLITTER, STATUSBAR and:10.1A
.:: 		TOOLBAR.						 :10.1A
.:: 01 Feb 19 - Added the 'CheckHost' method for the RUNTIME object.	 :10.1A
.:: 		Added the 'GetDescription' method for the ERROR object.	 :10.1A
.:: 17 Jul 19 - Added ' $LV_CSVRD_NOOEM2ANSI'.				 :10.2
.:: 27 Aug 19 - Added FTP object methods.				 :10.2
.:: 01 Oct 19 - Reviewed for 10.2 release.				 :10.2
.:: 06 Apr 20 - Added HttpRequest, HttpStdinSize, HttpStdinData methods  :10.2A
.::             for RUNTIME and ContextMenu method for HTMLCONTROL.      :10.2A
.:: 05 Oct 20 - Updated for 10.3.				         :10.3
.:: 26 Mar 21 - Added the DATETIME object.			         :10.3A
.:: 23 Apr 21 - Added LISTVIEW, RUNTIME, TABCONTROL and TREEVIEW methods.:10.3A
.::             Added parameter to WINDOW 'BrowseForFolder' method.	 :10.3A
.:: 01 Oct 21 - Updated for 10.4 release.                                :10.4
.:: 09 Jun 22 - Added RUNTIME object method 'GetKnownPath'.		 :10.5
.:: 15 Aug 22 - Added XDATA type named JSON_TYPE_ARRAY_NOLABEL.		 :10.5
.:: 03 Oct 22 - Reviewed for 10.5 release checking changes since 10.4B.  :10.5
.:: 05 Dec 22 - Updated the parameters for the DATATABLE methods.	 :10.5A
.:: 06 Mar 23 - Added $TV_XMLWR_NOLABEL_KEEP flag to TREEVIEW SaveXmlFile:10.5B
.:: 		method Options.						 :10.5B
.:: 02 Oct 23 - Added the MODULE object.                                 :10.6
.::             Updated methods for the 10.6 release.
.:: 04 Mar 24 - Updated for the 10.6A release.				 :10.6A
.::
         %ENDIF                                                          :8.3A
*------------------------------------------------------------------------------
.
. Note1:  Sections added to this include file are for user information
.         for an application.  This file can be modified and used to meet
.         the requirements for any user application.
.
*==============================================================================
. Syntax
.
. {obj}.{method} [GIVING {res}] [USING [*{KEY}=]{parm}[,[*{KEY}=]{parm}..]]
.
.    Where:
.
.          {obj}    - Object variable PLB label reference which has
.                     supported methods.
.          {method} - Method is an identifier for the operation to be
.                     performed for the {object} variable.  The syntax for
.                     the {method} can be one of the following:
.
.                     {method}  -  1. Method keyword name.
.                                  2. @{svar} variable which contains the
.                                     method keyword name.
.          {res}    - Dim, Form, Integer, or an object ( AUTOMATION, COLOR,
.                     FONT, IMAGELIST, or VARIANT ) to receive the result for
.                     the specified {method}.  The specific type(s) allowed
.                     depends on the {method} requirements.
.          {parm}   - Dim, Form, Integer, immediate numeric value, 
.                     literal, or an object ( AUTOMATION, COLOR, FONT,
.                     IMAGELIST, or VARIANT ) specifying an output
.                     parameter value.  The specific type(s) allowed depends
.                     on the {method} requirements.
.          {KEY}   -  This is a keyword text name which can be used with the
.                     specified {method} parameters.  The use of {KEY} is
.                     optional.  It is possible that some {methods} may not
.                     have named text keywords which means the parameters
.                     must be in the proper parameter position.  If a {method}
.                     has any parameter without a {KEY} name, then those
.                     parameters must be specified in the parameter list
.                     before parameters where {KEY} is used.
.                     The {KEY} input can be one of the following:
.
.                     {KEY}  - 1. *{Keyword Name}
.                              2. @{svar} variable which contains the
.                                 Keyword Name.
.    Examples:
.
.       MYLIST     LISTVIEW
.       $10$       FORM       "10"
.       RESULT     INTEGER    4
.       USERNUM    INTEGER    4,"12345"
.       INDEXVAR   INIT       "INDEX"
.
.                  CREATE     MYLIST...
.       ;.OK.......MYLIST.SetItemParam GIVING RESULT USING 10, 12345
.       ;.OK.......MYLIST.SetItemParam USING *INDEX=10, *PARAM=USERNUM
.       ;.OK.......MYLIST.SetItemParam USING *PARAM=USERNUM, *INDEX=$10$
.       ;.OK.......MYLIST.SetItemParam USING @INDEXVAR=10, *PARAM=12345
.       ;.ERROR....MYLIST.SetItemParam USING *INDEX=10, 12345
.
*------------------------------------------------------------------------------
. Method Runtime Errors
.
.   O123 - Specified property does not exist for object.
.   O124 - Too many parameters have been specified for an object method.
.   O125 - Method specified does not exist for object.
.   O126 - Invalid parameter type specified for a method.
.   O127 - Method does not provide a result yet a result is being requested.
.   O128 - Required parameter is missing from method parameter list.
.   O129 - Duplicate method parameter specified.
.   O130 - Invalid parameter name specified.
. 
*------------------------------------------------------------------------------
. Object Characteristics
*------------------------------------------------------------------------------
.   ANIMATE                                                               9.0
.
. Events:
.
.   $CHANGE       EQU    3
.   $CLICK        EQU    4
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $MOVE         EQU    12
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   AUTOPLAY=dnumnvar                        CREATE  SETPROP  GETPROP
.   BACKSTYLE=dnumnvar                       CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.   CENTER=dnumnvar                          CREATE
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   Close                GIVING {nvar}
.   Open                 GIVING {nvar} USING *NAME={svarslit}
.   Play                 GIVING {nvar} USING *START={dnumnvar}:    Optional
.                                            *END={dnumnvar}:      Optional
.                                            *REPEAT={dnumnvar}    Optional
.   Stop                 GIVING {nvar}
*------------------------------------------------------------------------------
.   AUTOMATION
.
. Events:
.
.   Reference Automation Server vendor documentation for supported events.
.
. Properties:
.
.   ADVISEKEY=dnumnvar                                        GETPROP
.   CLASS=svarslit                           CREATE  SETPROP  GETPROP
.   CLASSID=svarslit                         CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   LIC=svarslit                             CREATE           GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   REMSERVER=svarslit                       CREATE           GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.
.   Reference Automation Server vendor documentation for additional 
.   properties which are supported.
.
. Methods:
.
.   Reference Automation Server vendor documentation for methods.
.
. Method Constants:
.
.   Reference Automation Server vendor documentation for method parameter
.   values.
.
*------------------------------------------------------------------------------
.   BUTTON                                                                9.6
.
. Events:
.
.   $CHANGE       EQU    3   //PL/B Web Server ONLY!                      9.7A
.   $CLICK        EQU    4
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $MOVE         EQU    12
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   BUTTONSTATE=dnumnvar (WebView only)      CREATE  SETPROP  GETPROP	 10.5
.   BUTTONTYPE=dnumnvar                      CREATE           GETPROP     9.6
.   CANCEL[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAPTION=dnumnvar                         CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   CONTEXT=dnumnvar (WebView only)          CREATE  SETPROP  GETPROP	 10.5
.   CMDNOTE=svarslit                         CREATE  SETPROP  GETPROP
.   DEFAULT[=dnumnvar]                       CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FLOATMENU=dnumnvar                       CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   ICON=dnumnvar|svarslit|icon object       CREATE  SETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   PICTURE=dnumnvar|svarslit|pict object    CREATE  SETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SHIELD=dnumnvar                          CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   THEME=svarslit                           CREATE  SETPROP  GETPROP
.   TITLE=svarslit                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}   OPTIONAL 
.   IoCancelMode         GIVING {nvar} USING *Value={dnumnvar}
.   GetFileCount         GIVING {nvar}                           PWS ONLY 9.7A
.   GetFileItem          GIVING {svar} USING *Index={dnumnvar}:  PWS ONLY 9.7A
.                                            *Flags={dnumnvar}            9.7A
.   SetFileOptions       GIVING {nvar} USING *Filter=(svarslit}: PWS ONLY 9.7A
.                                            *Flags={dnumnvar}            9.7A
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
. 0	- Turn off Button AAM Cancel mode
. 1	- Turn on Button AAM Cancel mode
.
*------------------------------------------------------------------------------
.   CHECKBOX                                                                
.
. Events:
.
.   $CLICK        EQU    4
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $MOVE         EQU    12
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ALIGNTEXT=dnumnvar                       CREATE  SETPROP  GETPROP
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAPTION=dnumnvar                         CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FLOATMENU=dnumnvar                       CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   GROUPID=dnumnvar                         CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   PUSHLIKE=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   SWITCH=dnumnvar (WebView only)           CREATE  SETPROP  GETPROP	 10.5
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   THEME=svarslit                           CREATE  SETPROP  GETPROP
.   TITLE=svarslit                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   TRISTATE=dnumnvar                        CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VALUE=dnumnvar                                   SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}   OPTIONAL 
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
*------------------------------------------------------------------------------
.   CHECKGRP                                                              
.
. Events:
.
.   $CLICK        EQU    4
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOVE         EQU    12
.
. Properties:
.
.   ALIGNTEXT=dnumnvar                       CREATE  SETPROP  GETPROP
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   THEME=svarslit                           CREATE  SETPROP  GETPROP
.   TITLE=svarslit                           CREATE  SETPROP  GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   TRISTATE=dnumnvar                        CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VALUE=dnumnvar                                   SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   None
.
*------------------------------------------------------------------------------
.   CLIENT                                                                9.7
.
. Events:
.
.   $ClientEventOrient      EQU 301		;9.8B  PL/B Web Server ONLY
.   $ClientEventPostMessage EQU 302		;10.0A PL/B Web Server ONLY
.
. Properties:
.
.   None
.
. Methods:
.
.   AddCss          GIVING {nvar} USING *Url={svarslit}:
. 
.   AddJs           GIVING {nvar} USING *Url={svarslit}:		  9.9B
.                                       *Options={dnumnvar}   Optional    9.9B
.   AppBeacon       GIVING {nvar} USING *Id={svarslit}        Optional    9.9A
.                                       *Uuid={svarslit}:     Optional    9.9A
.                                       *Major={dnumnvar}     Optional    9.9A
.                                       *Minor={dnumnvar}     Optional    9.9A
.                                       *EventFreq={dnumnvar} Optional    9.9A
.                                       *Flags={dnumnvar}     Optional    9.9A
.   AppBeaconStatus GIVING {nvar} USING *Flags={dnumnvar}     Optional    9.9A
.   AppCapture      GIVING {nvar} USING *Type={dnumnvar}:                 9.8B  
.                                       *Options={svarslit}   Optional    9.8B 
.   AppDialog      GIVING {nvar} USING *Text={svarslit}:             	  9.8B 
.                                       *Title={svarslit}:    Optional    9.8B
.                                       *Button={svarslit}:   Optional    9.8B
.                                       *DefaultText={svarslit} Optional  9.8B
.   AppDirAdd      GIVING {nvar} USING *Path={svarslit}:             	  9.9B
.                                      *Options={svarslit}   Optional     9.9B
.   AppDirDel      GIVING {nvar} USING *Path={svarslit}:             	  9.9B
.                                      *Options={svarslit}   Optional     9.9B
.   AppDirGet      GIVING {nvar} USING *Path={svarslit}:             	  9.9B
.                                      *Options={svarslit}   Optional     9.9B
.   AppDownload    GIVING {nvar} USING *Url={svarslit}:             	  9.8B  
.   					*FileName={svarslit}:      	  9.8B 
.                                       *Options={svarslit}   Optional    9.8B 
.   AppExtendedError GIVING {svar} USING *Options={dnumnvar}  Optional    9.8B  
.   AppFindContact  GIVING {nvar} USING *Fields={svarslit}:               9.8B  
.                                       *Options={svarslit}   Optional    9.8B                         
.   AppGetInfo	    GIVING {svar} USING *Type={dnumnvar}:     Optional    9.8B  
.                                       *Options={svarslit}   Optional    9.8B   
.   AppGetPicture   GIVING {nvar} USING *Options={svarslit}   Optional    9.8B     
.   AppGeoLocation  GIVING {nvar} USING *Type={dnumnvar}:                 9.8B  
.                                       *Options={svarslit}   Optional    9.8B 
.   AppInstallOffline GIVING {nvar} USING *Name={svarslit}:   		  9.9B
.                                       *Html={svarslit}:	          9.9B 
.                                       *Css={svarslit}:      Optional    9.9B 
.                                       *Js={svarslit}:       Optional    9.9B  
.                                       *Options={dnumnvar}   Optional    9.9B
.   AppMedia        GIVING {nvar} USING *Action={dnumnvar}:               9.8B  
.   					*Url={svarslit}:      Optional	  9.8B 
.                                       *Volume={dnumnvar}    Optional    9.8B 
.   AppPickContact  GIVING {nvar} 				          9.8B  
.   AppScanBarCode  GIVING {nvar} USING *Options={svarslit}   		  9.8B  
.   AppSetOffline   GIVING {nvar} USING *Html={svarslit}:   		  9.9B
.                                       *Css={svarslit}:      Optional    9.9B 
.                                       *Js={svarslit}:       Optional    9.9B  
.                                       *Options={dnumnvar}   Optional    9.9B                   
.   AppStatusBar    GIVING {nvar} USING *Mode={dnumnvar}:                 9.9B  
.                                       *BackColor={svarslit} Optional    9.9B 
.   AppUpload       GIVING {nvar} USING *Url={svarslit}:             	  9.8B  
.   					*FileName={svarslit}:      	  9.8B 
.                                       *Options={svarslit}   Optional    9.8B 
.   AppVibrate      GIVING {nvar} USING *Time={dnumnvar}      Optional    9.8B
.   FlushMessages   GIVING {nvar}     
.   GetInfo         GIVING {svar} USING *Options={dnumnvar}:  Optional
.                                       *Delimiter={svarslit} Optional
.   GetLocation     GIVING {svar} USING *Options={dnumnvar}   Optional    9.7A
.   GetMonitorInfo  GIVING {svar} USING *Options={dnumnvar}   Optional
.   GetState        GIVING {nvar} USING *StateMask={dnumnvar}             9.7A
.   GetWinInfo      GIVING {svar} USING *Options={dnumnvar}:  Optional    9.7C
.                                       *Delimiter={svarslit} Optional    9.7C
.   JqGet           GIVING {svar} USING *Selector={svarslit}:             9.9A
.                                       *Name={svarslit}:                 9.9A
.                                       *Flags={dnumnvar}     Optional    9.9A
.   JqSet           GIVING {nvar} USING *Selector={svarslit}:             9.9A
.                                       *Name={svarslit}:                 9.9A
.                                       *Value={svarslit}:                9.9A
.                                       *Flags={dnumnvar}     Optional    9.9A  
.   JsMakeString    GIVING {svar} USING *Text={svarslit}
.   JsRun           GIVING {svar} USING *Js={svarslit}
.                                       *Options={dnumnvar}   Optional
.   Open            GIVING {nvar} USING *Url={svarslit}:
.                                       *Options={dnumnvar}   Optional
.   Print           GIVING {nvar}
.   SetUTF8Convert  GIVING {nvar} USING *State={dnumnvar}                 9.7C
.   SetUTF16Table   GIVING {nvar} USING *Table={svarslit}                 9.7C
.   StorageGet      GIVING {svar} USING *Key={svarslit}:                  9.8A
.                                       *Options={dnumnvar}   Optional    9.8A
.   StorageSet      GIVING {nvar} USING *Key={svarslit}:                  9.8A
.                                       *Value={svarslit}:    Optional    9.8A
.                                       *Options={dnumnvar}   Optional    9.8A        
.
. Method Constants:
.
. GetInfo Options Constants:
.
$INFO_ALL			EQU	0
$INFO_AVAIL_HEIGHT		EQU	1
$INFO_AVAIL_WIDTH		EQU	2
$INFO_COLOR_DEPTH		EQU	4
$INFO_HEIGHT			EQU	8
$INFO_PIXEL_DEPTH		EQU	16
$INFO_WIDTH			EQU	32
$INFO_APP_CODE_NAME		EQU	64
$INFO_APP_NAME			EQU	128
$INFO_APP_VERSION		EQU	256
$INFO_COOKIE_ENABLED		EQU	512	
$INFO_LANGUAGE			EQU	1024
$INFO_PLATFORM			EQU	2048
$INFO_PRODUCT			EQU	4096
$INFO_USER_AGENT		EQU	8192
$INFO_PEER_IP			EQU	16384
$INFO_HTTP_HOST			EQU	32768
.
. JqGet/JqSet Options Constants:
.
$JQ_FLAG_CSS			EQU	1
$JQ_FLAG_PROP			EQU	2
.
. APPxxxxx Method Constants:
.
.....
. Return Error Values
.
AppErrorNone			EQU	0
AppErrorNoCordovaSupport	EQU	1
AppErrorWithExtendedInfo	EQU	2
AppErrorWithNoExtendedInfo	EQU	3
AppErrorUnknownInfoType		EQU	4
AppErrorNoInfoReturned		EQU	5
AppErrorBadCaptureType		EQU	6
AppErrorBadMediaType		EQU	7
AppErrorUnknownService  	EQU 	8
AppErrorUnknownPushAction	EQU	9
AppErrorUnknownGeoType		EQU	10
AppErrorInvalidPath		EQU	11
.....
. AppCapture Type Values
.
AppCaptureImage			EQU 	0
AppCaptureAudio			EQU	1
AppCaptureVideo			EQU	2
.....
. AppGetInfo Type Values
.
AppInfoDevice			EQU	0
AppInfoBattery			EQU	1
AppInfoNetwork			EQU	2
AppInfoLanguage			EQU	3
.....
. AppGeoLocation Type Values
.
AppGeoGetLocation		EQU	0
AppGeoWatchLocation		EQU	1
AppGeoClearWatch		EQU	2
.....
. AppMedia Action Values
.
AppMediaPlay			EQU	0
AppMediaPause			EQU	1
AppMediaRewind			EQU	2
AppMediaStop			EQU	3
AppMediaRelease			EQU	4
.....
. AppPushAction Action Values
.
AppPushActionHasPermission	EQU	0
AppPushActionUnRegister		EQU	1
AppPushActionSetBadgeNum	EQU	2
AppPushActionGetBadgeNum	EQU	3
AppPushActionFinish		EQU	4
.....
. AppServiceLogon Service Values
.
AppServiceAzure			EQU	0
.....
. CLIENT Events Numbers
.
AppEventContactPicked		EQU	101
AppEventGetPict			EQU	102
AppEventDoCapture		EQU	103
AppEventDoUpload		EQU	104
AppEventDoDownload		EQU	105
AppEventApi			EQU	106
AppEventDialog			EQU	107
AppEventGetContact		EQU	108
AppEventMedia			EQU	109
AppEventPushReg			EQU	110
AppEventPushNotify		EQU	111
AppEventPushErr			EQU	112
AppEventPushAction		EQU	113
AppEventBattery			EQU	114
AppEventLocation		EQU	115
AppEventBatteryLow		EQU	116
AppEventBatteryCrit		EQU	117
AppEventGetPictError		EQU	118
AppEventScanBarCode		EQU	119
.
. AppBeacon Flags
.	
AppBeaconMonitorStart			EQU		1
AppBeaconMonitorStop			EQU		2
AppBeaconRangeStart			EQU		4
AppBeaconRangeStop			EQU		8
AppBeaconBlueToothEnable		EQU		16
AppBeaconBlueToothDisable		EQU		32
AppBeaconRequestWhenInUseAuthorization	EQU		64
AppBeaconRequestAlwaysAuthorization	EQU		128
AppBeaconMonitorStopAll			EQU		256
AppBeaconRangeStopAll			EQU		512
AppBeaconRequestState			EQU		1024
.
. AppBeacon Events
.
AppEventDidDetermineStateForRegion		EQU	120
AppEventDidStartMonitoringForRegion		EQU	121
AppEventDidRangeBeaconsInRegion			EQU	122
AppEventMonitoringDidFailForRegionWithError	EQU	123
AppEventDidExitRegion				EQU	124
AppEventDidEnterRegion				EQU	125
AppEventBeaconStatus				EQU	126
.
. AppDirGet Options
.
AppDirGetWithMeta			EQU		1
.
. AppDirXxx Events
.
AppEventDirAdd				EQU		127
AppEventDirDel				EQU		128
AppEventDirGet				EQU		129
.
. AppStatusBar Modes
.
AppStatusBarHide		EQU	1
AppStatusBarShow		EQU	2
AppStatusBarOverlayOff		EQU	4	      
AppStatusBarOverlayOn		EQU	8
AppStatusBarDefault		EQU	16
AppStatusBarLightContent	EQU	32
AppStatusBarBlackTranslucent	EQU	64
AppStatusBarBlackOpaque		EQU	128
.
ClientEventOrient		EQU	301
ClientEventPostMessage		EQU	302	//10.0A
.
CliUserEventStart		EQU	500
.
*------------------------------------------------------------------------------
.   COLOR
.
. Events:
.
.   None
.
. Properties:
.
.   USERDATA=svarslit                        CREATE                       9.4B
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.
. Methods:
.
.   ChooseColor          GIVING {nvar} USING *FLAGS={dnumnvar}:           9.0E
.                                            *HWND={dnumnvar}  ;Optional  9.7A
.   GetHSB               GIVING {nvar}					  9.6
.   SetHSB		 GIVING {nvar} USING *HSB={dnumnvar}		  9.6
.
. Method Constants:
.
CC_FULLOPEN         Integer 4,"0x0002"   ;ChooseColor
CC_PREVENTFULLOPEN  Integer 4,"0x0004"
CC_SOLIDCOLOR       Integer 4,"0x0080"
CC_ANYCOLOR         Integer 4,"0x0100"
.
*------------------------------------------------------------------------------
.   COMBOBOX
.
. Events:
.
.   $CHANGE       EQU    3
.   $CLICK        EQU    4
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP     8.7A
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   AUTOREDRAW=dnumnvar                      CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   COMBOSTYLE=dnumnvar                      CREATE           GETPROP
.   CUETEXT=svarslit                         CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP     8.7A
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP     9.4B
.   HORZEXTENT=dnumnvar                      CREATE  SETPROP  GETPROP     8.7C
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   ROWSVISIBLE=dnumnvar                     CREATE           GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SCROLLBAR[=dnumnvar]                     CREATE  SETPROP  GETPROP
.   SCROLLHIDE=dnumnvar                      CREATE           GETPROP
.   SORTED[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   THEME=svarslit                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddString            GIVING {nvar} USING *String={svarlit}:
.                                            *Flags={dnumnvar}:		  9.6
.                                            *Delimiter={dnumnvar}	  9.6
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}   OPTIONAL 
.   DeleteString         GIVING {nvar} USING *Index={dnumnvar}
.   Dir                  GIVING {nvar} USING *FileSpec={svarlit}:
.                                            *Flags={dnumnvar}
.   FindString           GIVING {nvar} USING *String={svarlit}:
.                                            *Index={dnumnvar}
.   FindStringExact      GIVING {nvar} USING *String={svarlit}:
.                                            *Index={dnumnvar}
.   GetCount             GIVING {nvar}
.   GetCurSel            GIVING {nvar}
.   GetItemData          GIVING {nvar} USING *Index={dnumnvar}
.   GetText              GIVING {svar} USING *Index={dnumnvar}
.   GetTopIndex          GIVING {nvar}
.   InsertString         GIVING {nvar} USING *String={svarlit}:
.                                            *Index={dnumnvar}
.   ResetContent
.   SelectString         GIVING {nvar} USING *String={svarlit}:
.                                            *Index={dnumnvar}
.   SetCurSel            GIVING {nvar} USING *Index={dnumnvar}
.   SetItemData          GIVING {nvar} USING *Data={dnumnvar}:
.                                            *Index={dnumnvar}
.   SetTopIndex          GIVING {nvar} USING *Index={dnumnvar}
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
.DDL_READWRITE    Integer 4,"0x0000"         ;Dir Flags same as DATALIST
.DDL_READONLY     Integer 4,"0x0001"
.DDL_HIDDEN       Integer 4,"0x0002"
.DDL_SYSTEM       Integer 4,"0x0004"
.DDL_DIRECTORY    Integer 4,"0x0010"
.
*------------------------------------------------------------------------------
.   CONTAINER
.
.   PL/B designer browse capability can help provide information for insertable
.   objects to be placed into a container.
.
. Events:
.
.   $CLICK        EQU    4
.   $DBLCLICK     EQU    6
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $RESIZE       EQU    17
.   $OBJMOVE      EQU    21
.   $UPDATED      EQU    22
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   AUTOACT=dnumnvar                         CREATE  SETPROP  GETPROP
.   AUTOVERB=dnumnvar                        CREATE  SETPROP  GETPROP
.   BACKSTYLE=dnumnvar                       CREATE  SETPROP  GETPROP
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   CLASS=svarslit                           CREATE  SETPROP  GETPROP
.   CLASSID=svarslit                         CREATE  SETPROP  GETPROP
.   DISPLAYTYPE=dnumnvar                     CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP     9.4B
.   HOSTNAME=svarslit                        CREATE  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   OLEDROP=dnumnvar                         CREATE  SETPROP  GETPROP
.   OLETYPE=dnumnvar                                          GETPROP
.   OLETYPEA=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SIZEMODE=dnumnvar                        CREATE  SETPROP  GETPROP
.   SOURCEDOC=svarslit                       CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   UPDATEOPT=dnumnvar                       CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   $Delete              GIVING {nvar}
.   $DoVerb              GIVING {nvar} USING *Verb={dnumnvar}
.   $Update              GIVING {nvar}
.
. Method Constants:
....
. $DoVerb *Verb Constants
.
OLEPrimary          CONST "0"   ;The default action for the object.
OLEShow             CONST "-1"  ;Activates the object for editing.
OLEOpen             CONST "-2"  ;Opens the object in a separate application
                                ;window.
OLEHide             CONST "-3"  ;For embedded objects, hides the application
                                ;that created the object.
OLEUIActivate       CONST "-4"  ;If the object supports in-place activation,
                                ;activates the object for in-place activation
                                ;and shows any user interface tools.
OLEInPlaceActivate  CONST "-5"  ;If the user moves the focus to the OLE
                                ;container control, creates a window for
                                ;the object and prepares the object to be
                                ;the object to be edited.
OLEDiscardUndoState CONST "-6"  ;Used when the object is activated for
                                ;editing to discard all record of changes
                                ;that the object's application can undo.
.
*------------------------------------------------------------------------------
.   CONTROL
.
.   PLBDSIGN browse capability can help provide information for ActiveX
.   controls available on a workstation.
.
. Events:
.
.   Reference vendor documentation for ActiveX control for supported events.
.
. Properties:
.
.   ACCEPTTAB=dnumnvar                       CREATE  SETPROP  GETPROP
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   CLASS=svarslit                           CREATE  SETPROP  GETPROP
.   CLASSID=svarslit                         CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP     9.4B
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   LIC=svarslit                             CREATE           GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
.   Reference vendor documentation for ActiveX control for additional
.   properties which are supported.
.
. Methods:
.
.   Reference vendor documentation for ActiveX control for supported methods.
.
. Method Constants:
.
.   Reference vendor documentation for ActiveX control for method parameter
.   values.
.
*------------------------------------------------------------------------------
.   DATALIST
.
. Events:
.
.   $CLICK        EQU    4
.   $DBLCLICK     EQU    6
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP     8.7A
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   AUTOREDRAW=dnumnvar                      CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   COLUMNWIDTH=dnumnvar                     CREATE  SETPROP  GETPROP     8.7C
.   DATA=svarslit                            CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP     8.7A
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP     9.4B
.   HORZEXTENT=dnumnvar                      CREATE  SETPROP  GETPROP     8.7C
.   HWND=nvar                                                 GETPROP
.   INTEGRAL=dnumnvar                        CREATE  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   MULTICOLUMN=dnumnvar                     CREATE           GETPROP
.   MULTISELECT[=dnumnvar]                   CREATE  SETPROP  GETPROP
.   NOINTEGRAL  (OBSELETE)                   CREATE
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   PRINTER[=dnumnvar]                       CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SCROLLBAR[=dnumnvar]                     CREATE  SETPROP  GETPROP
.   SCROLLHIDE=dnumnvar                      CREATE           GETPROP
.   SORTED[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TABSTOPS=svarslit                        CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   USERTL=dnumnvar                          CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddString            GIVING {nvar} USING *String={svarlit}
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}   OPTIONAL 
.   AllowEmptyTab        GIVING {nvar} USING *Value={dnumnvar}            8.7B
.   DeleteString         GIVING {nvar} USING *Index={dnumnvar}
.   Dir                  GIVING {nvar} USING *FileSpec={svarlit}:
.                                            *Flags={dnumnvar}
.   FindString           GIVING {nvar} USING *String={svarlit}:
.                                            *Index={dnumnvar}
.   FindStringExact      GIVING {nvar} USING *String={svarlit}:
.                                            *Index={dnumnvar}
.   GetCaretIndex        GIVING {nvar}
.   GetCount             GIVING {nvar}
.   GetFirstSel          GIVING {nvar}
.   GetNextSel           GIVING {nvar}
.   GetItemData          GIVING {nvar} USING *Index={dnumnvar}
.   GetSel               GIVING {nvar} USING *Index={dnumnvar}
.   GetSelCount          GIVING {nvar}
.   GetText              GIVING {svar} USING *Index={dnumnvar}
.   GetTextLen           GIVING {nvar} USING *Index={dnumnvar}
.   GetTopIndex          GIVING {nvar}
.   InsertString         GIVING {nvar} USING *String={svarlit}:
.                                            *Index={dnumnvar}
.   PreventKeyClickEvent GIVING {nvar} USING *Value={dnumnvar}            9.7A
.   ResetContent
.   SelectString         GIVING {nvar} USING *String={svarlit}:
.                                            *Index={dnumnvar}
.   SelItemRange         GIVING {nvar} USING *Select={dnumnvar}:
.                                            *First={dnumnvar}:
.                                            *Last={dnumnvar}
.   SetCaretIndex        GIVING {nvar} USING *Index={dnumnvar}
.   SetCurSel            GIVING {nvar} USING *Index={dnumnvar}
.   SetItemData          GIVING {nvar} USING *Data={dnumnvar}:
.                                            *Index={dnumnvar}
.   SetSel               GIVING {nvar} USING *Select={dnumnvar}:
.                                            *Index={dnumnvar}
.   SetTopIndex          GIVING {nvar} USING *Index={dnumnvar}
.   TabStops             GIVING {nvar} USING *String={svarlit}
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
DDL_READWRITE    Integer 4,"0x0000"         ;Dir Flags
DDL_READONLY     Integer 4,"0x0001"
DDL_HIDDEN       Integer 4,"0x0002"
DDL_SYSTEM       Integer 4,"0x0004"
DDL_DIRECTORY    Integer 4,"0x0010"
DDL_ARCHIVE      Integer 4,"0x0020"
DDL_DRIVES       Integer 4,"0x4000"
DDL_EXCLUSIVE    Integer 4,"0x8000"
.
*------------------------------------------------------------------------------
.   DATACOLUMN                                                              10.5
.
. Events:
.
.   none
.
. Properties:
.
.   ALIGNMENT=dnumnvar                       CREATE  SETPROP  GETPROP
.   COLUMNID=svarslit                        CREATE  SETPROP  GETPROP
.   CONTENTTYPE=dnumnvar                     CREATE  SETPROP  GETPROP
.   CONTEXT=dnumnvar                         CREATE  SETPROP  GETPROP
.   COMPUTE=svarslit                         CREATE  SETPROP  GETPROP
.   DATATYPE=dnumnvar                        CREATE  SETPROP  GETPROP
.   EDITCSS=svarslit                         CREATE  SETPROP  GETPROP
.   EDITLIST=svarslit                        CREATE  SETPROP  GETPROP
.   MAXSIZE=dnumnvar                         CREATE  SETPROP  GETPROP
.   ORDER=dnumnvar                           CREATE  SETPROP  GETPROP
.   TITLE=svarslit                           CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit                        CREATE  SETPROP  GETPROP
.   WEBWIDTH=svarslit                        CREATE  SETPROP  GETPROP
.
. Methods:
.
.   none
.
*------------------------------------------------------------------------------
.   DATATABLE                                                              10.5
.
. Events:
.
.   $CHANGE       EQU    3
.   $CLICK        EQU    4                                                
.   $DBLCLICK     EQU    6                                               
.   $COLCLICK     EQU    23
.   $ITEMACTIVATE EQU    25                                               
.
. Properties:
.
.   ACTIVEROW=dnumnvar
.   CHECKBOX=dnumnvar                        CREATE  SETPROP  GETPROP
.   CONTEXT=dnumnvar                         CREATE  SETPROP  GETPROP
.   GRIDLINE=dnumnvar                        CREATE  SETPROP  GETPROP
.   HIDECOLHDR=dnumnvar                      CREATE  SETPROP  GETPROP
.   MULTISELECT=dnumnvar                     CREATE  SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   PAGEPOS=dnumnvar                         CREATE  SETPROP  GETPROP
.   PAGESIZE=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SORTORDER=dnumnvar                       CREATE  SETPROP  GETPROP
.   STRIPED=dnumnvar                         CREATE  SETPROP  GETPROP
.   TRANSACTION=dnumnvar                     CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddColumn           GIVING {nvar}  USING *Pos={dnumnvar}:
.                                            *ContentType={dnumnvar}: Optional
.                                            *Id={svarslit}           Optional 
.   AddRow              GIVING {nvar}  USING *Text={svarlit}:
.                                            *Row={dnumnvar}          Optional
.                                            *Param={dnumnvar}:       Optional
.                                            *Checked={dnumnvar}:     Optional
.                                            *Selected={dnumnvar}:    Optional
.                                            *Context={dnumnvar}:    Optional
.                                            *SubItem1={svarlit}:     Optional
.                                            .
.                                            .
.                                            .
.                                            *SubItem40={svarlit}     Optional  
.   Commit              GIVING {nvar}
.   DeleteAllColumns    GIVING {nvar}
.   DeleteAllRows       GIVING {nvar}   
.   DeleteColumn        GIVING {nvar} USING *Col={dnumnvar}
.   DeleteRow           GIVING {nvar} USING *Row={dnumnvar}
.   EnsureVisible       GIVING {nvar} USING *Row={dnumnvar}:               10.6
.                                           *Col={dnumnvar}           Optional
.   FindRow             GIVING {nvar} USING *Start={dnumnvar}:        Optional
.                                           *Text={svarlit}:          Optional
.                                           *Param={dnumnvar}:        Optional
.                                           *Col={dnumnvar}:          Optional
.                                           *Flags={dnumnvar}         Optional
.   FindNextRow         GIVING {nvar} USING *Flags={dnumnvar}
.                                           *Start={dnumnvar}         Optional
.   GetColumnCount      GIVING {nvar}
.   GetOrderArray       GIVING {svar}
.   GetRowCount         GIVING {nvar}
.   GetRowText          GIVING {svar} USING *Row={dnumnvar}:
.                                           *Col={dnumnvar}           Optional
.   GetRowTextAll       GIVING {svar} USING  *Row={dnumnvar}:         
.                                            *Delimiter={svarslit}:   Optional
.                                            *Options={dnumnvar}      Optional 
.   HtmlBind            GIVING {nvar} USING  *Object={htmlcontrol}: 
.                                            *Style={dnumnvar}:       Optional
.                                            *Options={dnumnvar}      Optional
.   HtmlSave            GIVING {svar} USING  *FileName={svarslit}:    Optional
.                                            *Style={dnumnvar}:       Optional
.                                            *Options={dnumnvar}      Optional
.   HtmlUnBind          GIVING {nvar}
.   HtmlUpdate          GIVING {nvar}
.   LoadCsvFile         GIVING {nvar}  USING *FileName={svarslit}:        
.                                            *Options={dnumnvar}:     Optional
.                                            *Delimiter={svarslit}    Optional
.   Rollback            GIVING {nvar}
.   SaveCsvFile         GIVING {nvar}  USING *FileName={svarslit}:        
.                                            *Options={dnumnvar}:     Optional
.                                            *Delimiter={svarslit}    Optional
.   SetRowText          GIVING {nvar}  USING *Row={dnumnvar}:
.                                            *Text={svarlit}:
.                                            *Col={dnumnvar}          Optional
.   SetRowTextAll       GIVING {nvar}  USING *Row={dnumnvar}:          
.                                            *Text={svarlit}:
.                                            *Delimiter={svarlit}:    Optional
.                                            *Options={dnumnvar}      Optional
.   Sort                GIVING {nvar} USING *Col={dnumnvar}:
.                                            *Type={dnumnvar}:
.                                            *Mask={svarlit}:
.                                            *Col1={col1}:            Optional
.                                            *Type1={type1}:          Optional
.                                            *Mask1={mask1}:          Optional
.                                            *Col2={col2}:            Optional
.                                            *Type2={type2}:          Optional
.                                            *Mask2={mask2}:          Optional
.                                            *Col3={col3}:            Optional
.                                            *Type3={type3}:          Optional
.                                            *Mask3={mask3}           Optional
.   Undo               GIVING {nvar}
.
. Collection Support:
.
.   Columns
.   Rows
.
. Method Constants:
.
. AddColumn Method *ContentType Equates
. AddRow Method *Context Equates
. 
.$TC_DEFAULT	EQU		0	// Default 
.$TC_HIDDEN	EQU		1	// Hidden 
.$TC_EDITABLE	EQU		2	//  LISTVIEW mode - can be edited 
.$TC_TITLE	EQU		3	// Title 
.$TC_DETAILS	EQU		4	// Details 
.$TC_IMAGE	EQU		5	// Image 
.$TC_HEADER	EQU		6	// Header 
.$TC_FOOTER	EQU		7	// Footer 
.$TC_BUTTON1	EQU		8	// Button 1
.$TC_BUTTON2	EQU		9	// Button 2
.$TC_BUTTON3	EQU		10	// Button 3
.$TC_START	EQU		11	// Start time 
.$TC_END		EQU		12	// End time 
.$TC_GPS		EQU		13	// GPS Address 
.
. GetRowTextAll Method *Options Equates
. 
$TBL_CSVWR_QUOTED	EQU	1
$TBL_CSVWR_NOZEROWIDTH	EQU	16	//0x10
$TBL_CSVWR_BYORDERARRAY	EQU	128	//0x80
.
. HtmlBind Method *Style Equates
. HtmlSave Method *Style Equates
.
$HTML_STYLE_LISTVIEW 	EQU     1
$HTML_STYLE_CARD	EQU     2
$TBL_HTML_LISTVIEW 	EQU     1	//Same as PL/B Language Reference
$TBL_HTML_CARD		EQU     2	//Same as PL/B Language Reference
.
. LoadCSVFile Method *Options Equates
.
$TBL_CSVRD_QUOTED	EQU	1
$TBL_CSVRD_INPUTHEADER	EQU	8
$TBL_CSVRD_NOZEROWIDTH	EQU	16	//0x10
.
. SaveCSVFile Method *Options Equates
.
.$TBL_CSVWR_QUOTED	EQU	1
$TBL_CSVWR_OUTPUTSEL	EQU	2
$TBL_CSVWR_OUTPUTCHK	EQU	4
$TBL_CSVWR_OUTPUTHEADER	EQU	8
.$TBL_CSVWR_NOZEROWIDTH	EQU	16	//0x10
$TBL_CSVWR_LOWERCASE	EQU	32	//0x20
$TBL_CSVWR_UPPERCASE	EQU	64	//0x40
.$TBL_CSVWR_BYORDERARRAY EQU	128	//0x80
.
. SetRowTextAll Method *Options Equates
.
.$TBL_CSVRD_QUOTED	EQU	1
.$TBL_CSVRD_NOZEROWIDTH	EQU	16	//0x10
$TBL_CSVRD_REPLACEROW	EQU	32	//0x20
$TBL_CSVRD_SKIPNUL	EQU	64	//0x40
$TBL_CSVRD_BYORDERARRAY	EQU	128	//0x80
.
*------------------------------------------------------------------------------
.   DATAROW                                                              10.5
.
. Events:
.
.   none
.
. Properties:
.
.   CHECKED=dnumnvar                         CREATE  SETPROP  GETPROP
.   CONTEXT=dnumnvar                         CREATE  SETPROP  GETPROP
.   PARAM=dnumnvar                           CREATE  SETPROP  GETPROP
.   SELECTED=dnumnvar                        CREATE  SETPROP  GETPROP
.
. Methods:
.
.   none
.
*------------------------------------------------------------------------------
.   DATETIME                                                              10.3A
.
. Events:
.
.   none
.
. Properties:
.
.   none
.
. Methods:
.
.   Adjust               GIVING {nvar} USING *Value={svarslit}         
.   Compare              GIVING {nvar} USING *DateTime={datetime}     
.   GetAsString          GIVING {svar} USING *Format={svarslit}:      Optional
.                                            *LocalTime={dnumnvar}    Optional
.   SetToDateTime        GIVING {nvar} USING *DateTime={datetime} 
.   SetToNow             GIVING {nvar} USING *LocalTime={dnumnvar}    Optional            
.   SetAsString          GIVING {nvar} USING *Value={svarslit}:      
.                                            *Format={svarslit}:      Optional
.                                            *LocalTime={dnumnvar}    Optional
.
*------------------------------------------------------------------------------
.   EDITDATETIME                                                           
.
. Events:
.
.   $CHANGE       EQU    3
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP     8.7A
.   AUTOENTER=dnumnvar                       CREATE  SETPROP  GETPROP     8.7C
.   AUTOFORWARD=dnumnvar                     CREATE  SETPROP  GETPROP
.   CALBGCOLOR=dnumnvar|color object         CREATE  SETPROP  GETPROP
.   CALFGCOLOR=dnumnvar|color object         CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   CHECKED=dnumnvar                         CREATE  SETPROP  GETPROP
.   CUSTOMFORMAT=svarslit                    CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP     8.7A
.   DROPDOWNALIGN=dnumnvar                   CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   FORMAT=dnumnvar                         CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP     9.4B
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   MAXIMIMDATE=svarslit                     CREATE  SETPROP  GETPROP
.   MINIMIMDATE=svarslit                     CREATE  SETPROP  GETPROP    
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SHOWCHECKBOX=dnumnvar                    CREATE           GETPROP
.   SHOWUPDOWN=dnumnvar                      CREATE           GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TEXT=svarslit                                    SETPROP  GETPROP     
.   TITLEBGCOLOR=dnumnvar|color object       CREATE  SETPROP  GETPROP
.   TITLEFGCOLOR=dnumnvar|color object       CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   TRAILINGCOLOR=dnumnvar|color object      CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}   OPTIONAL 
.   GetDTFlags           GIVING {nvar}
.   SetDTFlags           GIVING {nvar} USING *Value={dnumnvar}
.   UtcMode              GIVING {nvar} USING *Value={dnumnvar}    Optional
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
*------------------------------------------------------------------------------
.   EDITNUMBER                                                            8.7C
.
. Events:
.
.   $CHANGE       EQU    3
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ALIGNMENT=dnumnvar                       CREATE  SETPROP  GETPROP
.   ALLOWMINUS=dnumnvar                      CREATE  SETPROP  GETPROP     8.7C
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP     8.7A
.   AUTOENTER=dnumnvar                       CREATE  SETPROP  GETPROP     8.7C
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   CLIPSIB=dnumnvar                         CREATE  SETPROP  GETPROP
.   DECIMALDIGITS=dnumnvar                   CREATE  SETPROP  GETPROP     8.7C
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP     8.7A
.   DPI=dnumnvar                             CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   EDITHIDESEL=dnumnvar                     CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   EVENTFILTER=svarslit                     CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP     9.4B
.   HWND=nvar                                                 GETPROP
.   INTEGERDIGITS=dnumnvar                   CREATE  SETPROP  GETPROP     8.7C
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   LEFTMARGIN=dnumnvar                      CREATE  SETPROP  GETPROP     8.7C
.   MODIFYFLAG=dnumnvar                              SETPROP  GETPROP     8.7C
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   OVERTYPE=dnumnvar                        CREATE  SETPROP  GETPROP
.   READONLY[=dnumnvar]                      CREATE           GETPROP
.   RIGHTMARGIN=dnumnvar                     CREATE  SETPROP  GETPROP     8.7C
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SELECTALL=dnumnvar                       CREATE  SETPROP  GETPROP
.   STATIC[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TEXT=svarslit                                    SETPROP  GETPROP     8.6D
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   UPDOWNALIGN=dnumnvar                     CREATE  SETPROP  GETPROP     8.7C
.   UPDOWNCHANGE=dnumnvar                    CREATE  SETPROP  GETPROP     8.7C
.   UPDOWNMAX=dnumnvar                       CREATE  SETPROP  GETPROP     8.7C
.   UPDOWNMIN=dnumnvar                       CREATE  SETPROP  GETPROP     8.7C
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VALUE=dnumnvar                                   SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}   OPTIONAL 
.   CanUndo              GIVING {nvar}
.   Clear                GIVING {nvar}
.   ClearUndo            GIVING {nvar}
.   Copy                 GIVING {nvar}
.   Cut                  GIVING {nvar}
.   GetTextLength        GIVING {nvar}
.   Paste                GIVING {nvar}
.   ScrollToCaret        GIVING {nvar}
.   Select               GIVING {nvar} USING [*Start=]{dnumnver}:
.                                            [*End=]{dnumnvar}
.   SelectAll            GIVING {nvar}
.   Undo                 GIVING {nvar}
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
*------------------------------------------------------------------------------
.   EDITTEXT
.
. Events:
.
.   $CHANGE       EQU    3
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ALIGNMENT=dnumnvar                       CREATE  SETPROP  GETPROP
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP     8.7A
.   AUTOENTER=dnumnvar                       CREATE  SETPROP  GETPROP
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   CENTER[=dnumnvar]                        CREATE
.   CENTERPOS=dnumnvar                       CREATE
.   CLIPSIB=dnumnvar                         CREATE  SETPROP  GETPROP
.   CUETEXT=svarslit                         CREATE  SETPROP  GETPROP
.   DIGITS[=dnumnvar]                        CREATE
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP     8.7A
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   EDITHIDESEL=dnumnvar                     CREATE  SETPROP  GETPROP
.   EDITTYPE=dnumnvar                        CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   EVENTFILTER=svarslit                     CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP     9.4B
.   HWND=nvar                                                 GETPROP
.   INPUTTYPE=dnumnvar (PWS only)            CREATE  SETPROP  GETPROP	 10.5
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   LEFTMARGIN=dnumnvar                      CREATE  SETPROP  GETPROP     8.7C
.   LOWERCASE[=dnumnvar]                     CREATE
.   MAXCHARS=dnumnvar                        CREATE  SETPROP  GETPROP
.   MAXCOLS=dnumnvar                         CREATE  SETPROP  GETPROP
.   MODIFYFLAG=dnumnvar                              SETPROP  GETPROP     8.7C
.   MULTILINE[=dnumnvar]                     CREATE  SETPROP  GETPROP
.   NUMERIC[=dnumnvar]                       CREATE
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   OVERTYPE=dnumnvar                        CREATE  SETPROP  GETPROP
.   PASSWORD[=dnumnvar]                      CREATE
.   PASSWORDCHAR=svarslit                    CREATE  SETPROP  GETPROP     8.7C
.   READONLY[=dnumnvar]                      CREATE           GETPROP
.   RIGHT[=dnumnvar]                         CREATE
.   RIGHTMARGIN=dnumnvar                     CREATE  SETPROP  GETPROP     8.7C
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SCROLLBAR[=dnumnvar]                     CREATE  SETPROP  GETPROP
.   SELECTALL=dnumnvar                       CREATE  SETPROP  GETPROP
.   SELTEXT=svarslit                                 SETPROP  GETPROP     8.7C
.   STATIC[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TEXT=svarslit                                    SETPROP  GETPROP     8.6D
.   TEXTOUTCONV=dnumnvar                     CREATE  SETPROP  GETPROP     8.7C
.   THEME=svarslit                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   UPPERCASE[=dnumnvar]                     CREATE
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   WORDWRAP[=dnumnvar]                      CREATE  SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}   OPTIONAL 
.   CanUndo              GIVING {nvar}
.   Clear                GIVING {nvar}
.   ClearUndo            GIVING {nvar}
.   Copy                 GIVING {nvar}
.   Cut                  GIVING {nvar}
.   GetCharIndexFromPos  GIVING {nvar} USING [*Vert=]{dnumnvar}:
.                                            [*Horz=]{dnumnvar}
.   GetFirstVisibleLine  GIVING {nvar}
.   GetLine              GIVING {svar} USING [*Line=]{dnumnvar}
.   GetLineCount         GIVING {nvar}
.   GetPosFromCharIndex  GIVING {nvar} USING [*CharIndex=]{dnumnvar}
.   GetTextLength        GIVING {nvar}
.   GetUnicode           GIVING {svar} USING [*Flags=]{dnumnvar}          9.6C
.   LineFromChar         GIVING {nvar} USING [*CharIndex=]{dnumnvar}
.   LineIndex            GIVING {nvar} USING [*Line=]{dnumnvar}
.   LineLength           GIVING {nvar} USING [*CharIndex=]{dnumnvar}
.   LineScroll           GIVING {nvar} USING [*Chars=]{dnumnvar}:
.                                            [*Lines=]{dnumnvar}
.   Paste                GIVING {nvar}
.   Scroll               GIVING {nvar} USING [*Action=]{dnumnvar}
.   ScrollToCaret        GIVING {nvar}
.   Select               GIVING {nvar} USING [*Start=]{dnumnver}:
.                                            [*End=]{dnumnvar}
.   SelectAll            GIVING {nvar}
.   SetUnicode           GIVING {nvar} USING [*String=]{svarlit}:         9.6C
.                                            [*Flags=]{dnumnvar}
.   Undo                 GIVING {nvar}
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
....
. Scroll *Action Equates
.
$LineUp         EQU     0
$LineDown       EQU     1
$PageUp         EQU     2
$PageDown       EQU     3
.
*------------------------------------------------------------------------------
.   ERROR                                                                 10.1
.
. Events:
.
.   None
.
. Properties:
.
.   none
.
. Methods:
.
.   AddError        GIVING {nvar} USING *Code={dnumnvar}:
.	                                *SubCode={dnumnvar}:  Optional
.	                                *Message={svarslit}:  Optional
.	                                *Flags={dnumnvar}     Optional
.
.   ClearAll        GIVING {nvar}
.
.   ClearError      GIVING {nvar} USING *Pos={dnumnvar}       Optional
.
.   GetCode         GIVING {svar} USING *Pos={dnumnvar}       Optional
.
.   GetCount        GIVING {nvar}
.
.   GetDescription  GIVING {svar} USING *CODE={svarslit}:                 10.1A
.                                       *SUBCODE={svarslit}:
.                                       *FILENAME={svarslit}: Optional
.                                       *FLAGS={dnumnvar}     Optional
.
.   GetErrorStackSize GIVING {nvar}
.
.   GetMaxTextSize  GIVING {nvar} USING *Pos={dnumnvar}:      Optional
.	                                *Flags={dnumnvar}     Optional
.
.   GetMessage      GIVING {svar} USING *Pos={dnumnvar}:      Optional
.	                                *Flags={dnumnvar}     Optional
.
.   GetSubCode      GIVING {nvar} USING *Pos={dnumnvar}       Optional
.
.   GetSubMessage   GIVING {svar} USING *Pos={dnumnvar}:      Optional
.	                                *Flags={dnumnvar}     Optional
.
.   LogMessages     GIVING {nvar} USING *FileName={svarslit}: Optional
.	                                *Flags={dnumnvar}     Optional
.
.   SetErrorStackSize GIVING {nvar} USING *Size={dnumnvar}:   Optional
.	                                  *Flags={dnumnvar}   Optional
.
.   GetProgram      GIVING {svar} USING *Pos={dnumnvar}:      Optional
.	                                *Flags={dnumnvar}     Optional
.
.   GetTime         GIVING {svar} USING *Pos={dnumnvar}:      Optional
.	                                *Flags={dnumnvar}     Optional
.
. Method Constants:
.
. AddError Method *Flags Values
.
$PLBERR_USER_EXCEPTION   EQU 1   ;Add user error that is trappable.
$PLBERR_USER_NOEXCEPTION EQU 2   ;Add user error that is not trappable.
.
. GetMaxTextSize Method *Flags Values
. 
$MAXTEXTSIZEALL         EQU  1   ;Return maximum for all errors.
.
. GetSubMessage Method *Options Values
. 
$PLBERR_ANOTHER_SUBMESSAGE    EQU 0   ;Get the next available sub message.
$PLBERR_FIRST_SUBMESSAGE      EQU 1   ;Reset and get the first sub message.
.
. LogMessages Method *Options Values
.
$ERRLOGON                     EQU 1   ;Turn on logging.
$ERRLOGOFF                    EQU 2   ;Turn off logging.
$ERRLOGRESET                  EQU 4   ;Reset the error log file.
.
*------------------------------------------------------------------------------
.   FLOATMENU                                                             9.0
.
. Events:
.
.   $CLICK        EQU    4
.   $ITEMCLICK    EQU    26
.
. Properties:
.
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RIGHTBUTTON=nvar                         CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}        Optional 
.   AddItem              GIVING {nvar} USING *CHECKED={dnumnvar}:     Optional
.                                            *DEFAULT={dnumnvar}:     Optional
.                                            *ENABLED={dnumnvar}:     Optional
.                                            *ITEMPOS={dnumnvar}:     Optional
.                                            *SEPARATOR={dnumnvar}:   Optional
.                                            *SHORTCUT={dnumnvar}:    Optional
.                                            *SPCMENU={dnumnvar}:     Optional
.                                            *SUBMENU={submenu obj}:  Optional
.                                            *TAG={dnumnvar}:         Optional
.                                            *TEXT={svarslit}:        Optional
.                                            *RUNNAME={svarslit}:     Optional
.                                            *HELPID={dnumnvar}:      Optional
.                                            *HELPTOPIC={svarslit}:   Optional
.                                            *USERDATA={svarslit}     Optional
.   GetItem              GIVING {menuitem object} USING *KEY={svarslit}
.   GetItemCount         GIVING {nvar} USING *KEY={nvar | svarslit}       9.0F
.   GetItemState         GIVING {nvar} USING *KEY={nvar | svarslit}       9.0F
.   GetItemType          GIVING {nar} USING *KEY={nvar | svarslit}        9.0F
.   GetItemName          GIVING {svar} USING *KEY={nvar | svarslit}       9.0F
.   RemoveItem           GIVING {nvar} USING *KEY={svarslit}
.   Activate             GIVINE {nvar} USING *Left={dnumnvar}:            9.4B
.                                            *Top={dnumnvar}:             9.4B
.                                            *Flags={dnumnvar}            9.4B
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
MFT_END                 Integer 4,"0xFFFFFFFF"   ;GetItemType {nvar} returned
MFT_STRING              Integer 4,"0x00000000"
MFT_BITMAP              Integer 4,"0x00000004"
MFT_MENUBARBREAK        Integer 4,"0x00000020"
MFT_MENUBREAK           Integer 4,"0x00000040"
MFT_SEPARATOR           Integer 4,"0x00000800"
MFT_RIGHTORDER          Integer 4,"0x00002000"
.
MFS_END                 Integer 4,"0xFFFFFFFF"   ;GetItemState {nvar} returned
MFS_CHECKED             Integer 4,"0x00000008"
MFS_DEFAULT             Integer 4,"0x00001000"
MFS_DISABLED            Integer 4,"0x00000003"
MFS_GRAYED              Integer 4,"0x00000003"
MFS_ENABLED             Integer 4,"0x00000000"
MFS_HILITE              Integer 4,"0x00000080"
.
*------------------------------------------------------------------------------
.   FONT                                                                  9.0F
.
. Events:
.
. Properties:
.
.   ANGLE=dnumnvar                           CREATE  SETPROP  GETPROP     9.0
.   BOLD[=dnumnvar]                          CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   ITALIC[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SIZE=dnumnvar                            CREATE  SETPROP  GETPROP
.   STRIKE=dnumnvar                          CREATE  SETPROP  GETPROP     9.0
.   UNDERLINE=dnumnvar                       CREATE  SETPROP  GETPROP     9.0
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.
. Methods:
.
.   ChooseFont           GIVING {nvar} USING *FLAGS={dnumnvar}:       Optional
.                                            *HDC={dnumnvar}:         Optional
.                                            *SIZEMIN={dnumnvar}:     Optional
.                                            *SIZEMAX={dnumnvar}:     Optional
.                                            *COLOR={color object}:   Optional
.                                            *HWND={dnumnvar}         Optional 9.7A
.
. Method Constants:
.
CF_SCREENFONTS          Integer 4,"0x00000001"   ;ChooseFont *FLAGS method
CF_PRINTERFONTS         Integer 4,"0x00000002"
CF_INITTOLOGFONTSTRUCT  Integer 4,"0x00000040"
CF_EFFECTS              Integer 4,"0x00000100"
CF_SCRIPTSONLY          Integer 4,"0x00000400"
CF_FIXEDPITCHONLY       Integer 4,"0x00004000"
CF_SCALABLEONLY         Integer 4,"0x00020000"
CF_TTONLY               Integer 4,"0x00040000"
CF_NOFACESEL            Integer 4,"0x00080000"
CF_NOSIZESEL            Integer 4,"0x00080000"
CF_FORCESCREENFONTOUT   Integer 4,"0X80000000"
.
*------------------------------------------------------------------------------
.   FTP                                                                   10.2
.
. Events:
.
.   None
.
. Properties:
.
.   none
.
. Methods:
.
.   Ascii           GIVING {nvar}         
.
.   Binary          GIVING {nvar}
.
.   Cd              GIVING {nvar} USING *Path={svarslit}

.   Close           GIVING {nvar}
.
.   Connect         GIVING {nvar} USING *Host={svarslit}:
.	                                *User={svarslit}:  
.	                                *Password={svarslit}:  
.	                                *Flags={dnumnvar}        Optional
.
.
.   Debug           GIVING {nvar} USING *LogFile={svarslit}:
.	                                *Level={dnumnvar}:       Optional
.	                                *Flags={dnumnvar}        Optional
.
.   Delete          GIVING {nvar} USING *RemoteFile={svarslit}
.
.   Dir             GIVING {nvar} USING *RemoteFile={svarslit}:
.	                                *Flags={dnumnvar}        Optional 
.
.   DirItem         GIVING {svar}
.
.   Get             GIVING {nvar} USING *RemoteFile={svarslit}:
.	                                *LocalFile={svarslit}    Optional
.
.   MkDir           GIVING {nvar} USING *Path={svarslit} 
.
.
.   Put             GIVING {nvar} USING *LocalFile={svarslit}:
.	                                *RemoteFile={svarslit}   Optional 
. 
.   Pwd             GIVING {svar}
.
.   Rename          GIVING {nvar} USING *OldName={svarslit}:
.	                                *NewName={svarslit}   
.
.   RmDir           GIVING {nvar} USING *Path={svarslit}
.
.   Size            GIVING {nvar} USING *RemoteFile={svarslit}
.
.   ModDate         GIVING {svar} USING *RemoteFile={svarslit}
.
.   LastResponse    GIVING {svar}
.
.   Site            GIVING {nvar} USING *Cmd={svarslit}
.
.   SysType         GIVING {svar}
.
.
. Method Constants:
.
. Connect Method *Flags Values
.
$FTP_CONNECT_USE_SSL     EQU 1
$FTP_CONNECT_REUSE_SSL   EQU 2
$FTP_CONNECT_IMPLICIT    EQU 4                                           10.4
.
. Debug Method *Level Values
. 
$FTP_DEBUG_LEVEL_NONE    EQU 0
$FTP_DEBUG_LEVEL_ERRONLY EQU 1
$FTP_DEBUG_LEVEL_ACTIONS EQU 2
$FTP_DEBUG_LEVEL_FULL    EQU 3
.
. Debug Method *Flags Values
. 
$FTP_DEBUG_FILE_APPEND   EQU 1
$FTP_DEBUG_FILE_FLUSH    EQU 2
$FTP_DEBUG_FILE_CLOSE    EQU 4
.
. Dir Method *Flags Values
. 
$FTP_LIST_ALL_INFO       EQU 0
$FTP_LIST_NAMES_ONLY     EQU 1
$FTP_LIST_MLSD           EQU 2                                           10.6A
.
*------------------------------------------------------------------------------
.   GROUPBOX                                                                
.
. Events:
.
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   BACKSTYLE=dnumnvar                       CREATE  SETPROP  GETPROP
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TITLE=svarslit                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
*------------------------------------------------------------------------------
.   HSCROLLBAR
.
. Events:
.   
.   $CLICK        EQU    4
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $MOVE         EQU    12
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   MAX=dnumnvar                             CREATE  SETPROP  GETPROP
.   MIN=dnumnvar                             CREATE  SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SCROLLSIZEMODE=dnumnvar                  CREATE  SETPROP  GETPROP
.   SHIFT=dnumnvar                           CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   None
.
*------------------------------------------------------------------------------
.   HTMLCONTROL								  10.0A
.
. Events:
.
.   $JQueryEvent  EQU    200
.
. Properties:
.
.   ANCHOR=dnumnvar                             CREATE  SETPROP GETPROP
.   BGCOLOR=dnumnvar|color object               CREATE  SETPROP GETPROP
.   CODEPAGE=dnumnvar                           CREATE  SETPROP GETPROP
.   DOCK=dnumnvar                               CREATE  SETPROP GETPROP
.   ENABLED=dnumnvar (data-plbenable required)  CREATE  SETPROP GETPROP
.   HEIGHT=dnumnvar                                     SETPROP GETPROP
.   HWND=nvar                                                   GETPROP
.   INNERHTML=svarslit                          CREATE  SETPROP GETPROP
.   LEFT=dnumnvar                                       SETPROP GETPROP
.   OBJECTID=dnumnvar                           CREATE  SETPROP GETPROP
.   RUNNAME=svarslit                            CREATE  SETPROP GETPROP
.   TABID=dnumnvar (data-plbtabid required)     CREATE  SETPROP GETPROP
.   TOP=dnumnvar                                        SETPROP GETPROP
.   USERDATA=svarslit                           CREATE  SETPROP GETPROP
.   VISIBLE=dnumnvar                            CREATE  SETPROP GETPROP
.   WEBCLASS=svarslit                           CREATE  SETPROP GETPROP
.   WEBHEIGHT=svarslit                          CREATE  SETPROP GETPROP
.   WEBLEFT=svarslit                            CREATE  SETPROP GETPROP
.   WEBMODE=dnumnvar                            CREATE  SETPROP GETPROP	 10.5
.   WEBOBJECT=dnumnvar                          CREATE  SETPROP GETPROP	 10.5
.   WEBPOSITION=dnumnvar                        CREATE  SETPROP GETPROP
.   WEBTOP=svarslit                             CREATE  SETPROP GETPROP
.   WEBWIDTH=svarslit                           CREATE  SETPROP GETPROP
.   WIDTH=dnumnvar                                      SETPROP GETPROP
.   ZORDER=dnumnvar                             CREATE  SETPROP GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}     Optional 
.   ContextMenu          GIVING {nvar} USING *Flags={dnumnvar}
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY
.                                            *Selector={svarslit}: Optional
.                                            *Flags={dnumnvar}     Optional
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY
.                                            *Selector={svarslit}: Optional
.                                            *Flags={dnumnvar}     Optional
.   Focus                GIVING {nvar} USING *Id={svarslit}:
.                                            *Flags={dnumnvar}     Optional
.   GetAttr              GIVING {nvar} USING *Id={svarslit}:
.                                            *Name={svarslit}:
.                                            *Flags={dnumnvar}     Optional
.   GetCss               GIVING={svar} USING *Id={svarslit}:
.                                            *Name={svarslit}:
.                                            *Flags={dnumnvar}     Optional 
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}     PWS ONLY
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}:  PWS ONLY
.                                            *Flags={dnumnvar}     Optional
.   InnerHtml            GIVING {nvar} USING *Html={svarslit}:
.                                            *Flags={dnumnvar}     Optional
.   SetAttr              GIVING {nvar} USING *Id={svarslit}:
.                                            *Name={svarslit}:
.                                            *Value={svarslit}:
.                                            *Flags={dnumnvar}     Optional
.   SetCss               GIVING {nvar} USING *Id={svarslit}:
.                                            *Name={svarslit}:
.                                            *Value={svarslit}:
.                                            *Flags={dnumnvar}     Optional
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}:  PWS ONLY
.                                            *StrValue={svarslit}:
.                                            *Flags={dnumnvar}     Optional
.   UpdateEvents         GIVING {nvar} USING *Flags={dnumnvar}     Optional
.   MakePict             GIVING {pict}
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
...........
.
. For ContextMenu *Flags
.
$HTML_CONTEXTMENU_ON	EQU	1
.
. For InnerHtml *Flags={dnumnvar}
.
$HTML_HAS_EVENTS	EQU	1
$HTML_FROM_URL		EQU	2	;HTML parameter is a URL
$HTML_USE_SCROLLBARS	EQU	4	;Plbwin only
$HTML_3D_BORDER	EQU	8	;Plbwin only
.
*------------------------------------------------------------------------------
.   ICON                                                                
.
. Events:
.
.   $CLICK        EQU    4
.   $DBLCLICK     EQU    6 
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   ALTTEXT=svarslit     (PWS runtime)       CREATE  SETPROP  GETPROP
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   IMAGEINDEX=dnumnvar                              SETPROP  GETPROP
.   IMAGELIST=imagelist                      CREATE  SETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RESOURCE=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   URLSOURCE=svarslit   (PWS runtime)       CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
*------------------------------------------------------------------------------
.   IMAGELIST
.
. Events:
.
.   None
.
. Properties:
.
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   IMAGECOLORS=dnumnvar                     CREATE           GETPROP
.   IMAGESIZEH=dnumnvar                      CREATE           GETPROP
.   IMAGESIZEH=dnumnvar  (PWS runtime)       CREATE  SETPROP  GETPROP     9.9
.   IMAGESIZEV=dnumnvar                      CREATE           GETPROP
.   IMAGESIZEV=dnumnvar  (PWS runtime)       CREATE  SETPROP  GETPROP     9.9
.   MASKCOLOR=dnumnvar|color object          CREATE  SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RESOURCE=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   URLSOURCE=svarslit   (PWS runtime)       CREATE  SETPROP  GETPROP     9.9
.   USECOLORMASK=dnumnvar                    CREATE           GETPROP
.   USEMASK=dnumnvar                         CREATE           GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.
. Methods:
.
.   AddBmp               GIVING {nvar} USING *Bmp={varlit}:
.                                            *Mask={varlit}        Optional
.   AddBmpMasked         GIVING {nvar} USING *Bmp={varlit}
.   AddIcon              GIVING {nvar} USING *Icon={varlit}
.   AddLoadIcon          GIVING {nvar} USING *FileName={svarslit}:
.                                            *ResourceId={dnumnvar}
.   AddLoadImage         GIVING {nvar} USING *FileName={svarslit}:
.                                            *ResourceId={dnumnvar}
.   GetImageCount        GIVING {nvar}
.   LoadStdToolBitmap    GIVING {nvar}
.   Remove               GIVING {nvar} USING *Index={dnumnvar}
.   RemoveAll            GIVING {nvar}
.   ReplaceBmp           GIVING {nvar} USING *Index=(dnumnvar}:
.                                            *Bmp={varlit}:
.                                            *Mask={varlit}        Optional
.   ReplaceIcon          GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Icon={varlit}
.   WriteBmpFile         GIVING {nvar} USING *FileName={svarslit}
.
*------------------------------------------------------------------------------
.   LABELTEXT                                                                
.
. Events:
.
.   $CLICK        EQU    4
.   $DBLCLICK     EQU    6
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   ALIGNMENT=dnumnvar                       CREATE  SETPROP  GETPROP
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   TEXT=svarslit                            CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USEALTKEY=dnumnvar                       CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   WORDWRAP[=dnumnvar]                      CREATE  SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
*------------------------------------------------------------------------------
.   LINE                                                                
.
. Events:
.
.   $CLICK        EQU    4
.   $DBLCLICK     EQU    6
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BDRPATTERN=dnumnvar                      CREATE  SETPROP  GETPROP
.   BDRWIDTH=dnumnvar                        CREATE  SETPROP  GETPROP
.   DRAWMODE=dnumnvar                        CREATE  SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   X1=dnumnvar                                      SETPROP  GETPROP
.   X2=dnumnvar                                      SETPROP  GETPROP
.   Y1=dnumnvar                                      SETPROP  GETPROP
.   Y2=dnumnvar                                      SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
*------------------------------------------------------------------------------
.   LISTVIEW
.
. Events:
.
.   $CHANGE       EQU    3
.   $CLICK        EQU    4                                                8.3b
.   $DBLCLICK     EQU    6                                                8.3b
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $RESIZE       EQU    17
.   $COLCLICK     EQU    23
.   $VALIDATE     EQU    24
.   $ITEMACTIVATE EQU    25                                               8.6B
.   $MOUSEWHEEL   EQU    27			
.   $HSCROLL      EQU    28			
.   $VSCROLL      EQU    29			
.
. Properties:
.
.   ACTIVATE=dnumnvar                        CREATE  SETPROP  GETPROP     ;86B
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   ARRANGE=dnumnvar                         CREATE  SETPROP  GETPROP
.   AUTOREDRAW=dnumnvar                      CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   CHECKBOX=dnumnvar                        CREATE  SETPROP  GETPROP     ;86B
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FLOATMENU=dnumnvar                       CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   FULLROW=dnumnvar                         CREATE  SETPROP  GETPROP     ;83A
.   GRIDLINE=dnumnvar                        CREATE  SETPROP  GETPROP     ;86B
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP     9.4B
.   HIDECOLHDR=dnumnvar                      CREATE  SETPROP  GETPROP
.   HIDESEL=dnumnvar                         CREATE  SETPROP  GETPROP
.   HOTTRACK=dnumnvar                        CREATE  SETPROP  GETPROP     ;86B
.   HOVERSEL=dnumnvar                        CREATE  SETPROP  GETPROP     ;86B
.   HOVERTIME=dnumnvar                       CREATE  SETPROP  GETPROP     ;86B
.   HWND=nvar                                                 GETPROP
.   IMAGELIST=imagelist                      CREATE  SETPROP
.   IMAGELISTSM=imagelist                    CREATE  SETPROP
.   IMAGELISTST=imagelist                    CREATE  SETPROP
.   LABELWRAP=dnumnvar                       CREATE  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   MULTISELECT[=dnumnvar]                   CREATE  SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   OSEVENTMASK=dnumnvar                     CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SORTHEADER=dnumnvar                      CREATE           GETPROP
.   SORTORDER=dnumnvar                       CREATE           GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   THEME=svarslit                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VIEWSTYLE=dnumnvar                       CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   Arrange              GIVING {nvar} USING *Code={dnumnvar}
.   DeleteAllContents    GIVING {nvar}
.   DeleteAllItems       GIVING {nvar}
.   DeleteColumn         GIVING {nvar} USING *Index={dnumnvar}
.   DeleteItem           GIVING {nvar} USING *Index={dnumnvar}
.   EnableScrollBar      GIVING {nvar} USING *Enable={dnumnvar}
.   EnsureVisible        GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Partial={dnumnvar}
.   FindItem             GIVING {nvar} USING *Start={dnumnvar}:    Optional
.                                            *Text={svarlit}:      Optional
.                                            *Param={dnumnvar}:    Optional
.                                            *Flags={dnumnvar}     Optional
.   FindItemCheck        GIVING {nvar} USING *Start={dnumnvar}
.   GetAttributeColumn   GIVING {nvar}
.   GetBGColorColumn     GIVING {nvar}
.   GetColResizeFlag     GIVING {nvar} USING *Index={dnumnvar}
.   GetColumnCount       GIVING {nvar}
.   GetColumnFormat      GIVING {nvar} USING *Index={dnumnvar}
.   GetColumnOrderArray  GIVING {svar}
.   GetColumnText        GIVING {svar} USING *Index={dnumnvar}
.   GetColumnWidth       GIVING {nvar} USING *Index={dnumnvar}
.   GetColumnWidths      GIVING {svar}                                    10.3A
.   GetCountPerPage      GIVING {nvar}
.   GetExtendedStyle     GIVING {nvar}
.   GetFGColorColumn     GIVING {nvar}
.   GetIconSpacing       GIVING {nvar} USING *Flags={dnumnvar}		  9.6 
.   GetItemCheck         GIVING {nvar} USING *Index={dnumnvar}
.   GetItemCount         GIVING {nvar}
.   GetItemImage         GIVING {nvar} USING *Index={dnumnvar}
.   GetItemParam         GIVING {nvar} USING *Index={dnumnvar}
.   GetItemRect          GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Subitem={dnumnvar}
.   GetItemState         GIVING {nvar} USING *Index={dnumnvar}:
.                                            *StateMask={dnumnvar}
.   GetItemText          GIVING {svar} USING *Index={dnumnvar}:
.                                            *SubItem={dnumnvar}   Optional
.   GetItemTextAll      GIVING  {svar} USING *Index={dnumnvar}:           9.0B
.                                            *Delimiter={svarslit}:Optional
.                                            *Options={dnumnvar}   Optional9.1A
.   GetLastDropXY        GIVING {nvar} USING *Flags={dnumnvar}
.   GetNextItem          GIVING {nvar} USING *Flags={dnumnvar}:
.                                            *Start={dnumnvar}     Optional
.   GetStringWidth       GIVING {nvar} USING *String={svarlit}
.   GetTopIndex          GIVING {nvar}     
.   GetXmlDataSize       GIVING {nvar} USING *Options={dnumnvar}:   Optional
.                                            *TableName={svarslit}: Optional
.                                            *RowName={svarslit}    Optional                               9.0F
.   InsertAttrColor      GIVING {nvar} USING *COLOR1={color object}:      9.0
.                                            *COLOR2={color object}:      9.0
.                                            *COLOR3={color object}:      9.0
.                                            *COLOR4={color object}:      9.0
.                                            *COLOR5={color object}:      9.0
.                                            *COLOR6={color object}:      9.0
.                                            *COLOR7={color object}:      9.0
.                                            *COLOR8={color object}:      9.0
.                                            *COLOR9={color object}:      9.0
.                                            *COLOR10={color object}:     9.0
.                                            *COLOR11={color object}:     9.0
.                                            *COLOR12={color object}:     9.0
.                                            *COLOR13={color object}:     9.0
.                                            *COLOR14={color object}:     9.0
.                                            *COLOR15={color object}:     9.0
.                                            *COLOR16={color object}:     9.0
.                                            *COLOR17={color object}:     9.0
.                                            *COLOR18={color object}:     9.0
.                                            *COLOR19={color object}:     9.0
.                                            *COLOR20={color object}      9.6B
.   InsertAttrColumn     GIVING {nvar} USING *Index={dnumnvar}            9.0
.   InsertAttrDefault    GIVING {nvar} USING *Default={svarslit}          9.0
.   InsertAttrFont       GIVING {nvar} USING *FONT1={font object}:        9.0
.                                            *FONT2={font object}:        9.0
.                                            *FONT3={font object}:        9.0
.                                            *FONT4={font object}:        9.0
.                                            *FONT5={font object}:        9.0
.                                            *FONT6={font object}:        9.0
.                                            *FONT7={font object}:        9.0
.                                            *FONT8={font object}:        9.0
.                                            *FONT9={font object}:        9.0
.                                            *FONT10={font object}:       9.0
.                                            *FONT11={font object}:       9.0
.                                            *FONT12={font object}:       9.0
.                                            *FONT13={font object}:       9.0
.                                            *FONT14={font object}:       9.0
.                                            *FONT15={font object}:       9.0
.                                            *FONT16={font object}:       9.0
.                                            *FONT17={font object}:       9.0
.                                            *FONT18={font object}:       9.0
.                                            *FONT19={font object}:       9.0
.                                            *FONT20={font object}        9.6B
.   InsertAttrRGB        GIVING {nvar} USING *RGB1={varlit}:              9.3A
.                                            *RGB2={varlit}:              9.3A
.                                            *RGB3={varlit}:              9.3A
.                                            *RGB4={varlit}:              9.3A
.                                            *RGB5={varlit}:              9.3A
.                                            *RGB6={varlit}:              9.3A
.                                            *RGB7={varlit}:              9.3A
.                                            *RGB8={varlit}:              9.3A
.                                            *RGB9={varlit}:              9.3A
.                                            *RGB10={varlit}:             9.3A
.                                            *RGB11={varlit}:             9.3A
.                                            *RGB12={varlit}:             9.3A
.                                            *RGB13={varlit}:             9.3A
.                                            *RGB14={varlit}:             9.3A
.                                            *RGB15={varlit}:             9.3A
.                                            *RGB16={varlit}:             9.3A
.                                            *RGB17={varlit}:             9.3A
.                                            *RGB18={varlit}:             9.3A
.                                            *RGB19={varlit}:             9.3A
.                                            *RGB20={varlit}:             9.6B
.                                            *Flags={dnumnvar}            9.3A
.   InsertColumn         GIVING {nvar} USING *Text={svarlit}:
.                                            *Width={dnumnvar}:
.                                            *Index={dnumnvar}:
.                                            *Format={dnumnvar}    Optional
.   InsertColumnBgClr    GIVING {nvar} USING *Index={dnumnvar}
.   InsertColumnEx       GIVING {nvar} USING *Text={svarlit}:
.                                            *Width={dnumnvar},
.                                            *Index={dnumnvar}:
.                                            *Format={dnumnvar}:   Optional
.                                            *Image={dnumnvar}:    Optional
.                                            *Order={dnumnvar}     Optional
.   InsertColumnFgClr    GIVING {nvar} USING *Index={dnumnvar}
.   InsertItem           GIVING {nvar} USING *Text={svarlit}:
.                                            *Index={dnumnvar}:    Optional
.                                            *Image={dnumnvar}:    Optional
.                                            *Param={dnumnvar}:    Optional
.                                            *State={dnumnvar}:    Optional
.                                            *StateMask={dnumnvar} Optional
.   InsertItemEx         GIVING {nvar} USING *Text={svarlit}:
.                                            *Index={dnumnvar}     Optional
.                                            *Image={dnumnvar}:    Optional
.                                            *Param={dnumnvar}:    Optional
.                                            *State={dnumnvar}:    Optional
.                                            *Statemask={dnumnvar}:Optional
.                                            *SubItem1={svarlit}:  Optional
.                                            *SubItem2={svarlit}:  Optional
.                                            *SubItem3={svarlit}:  Optional
.                                            *SubItem4={svarlit}:  Optional
.                                            *SubItem5={svarlit},  Optional
.                                            *SubItem6={svarlit}:  Optional
.                                            *SubItem7={svarlit}:  Optional
.                                            *SubItem8={svarlit}:  Optional
.                                            *SubItem9={svarlit}:  Optional
.                                            *SubItem10={svarlit}  Optional
.   IsScrollVisible     GIVING {nvar}
.   LoadCsvFile         GIVING {nvar}  USING *FileName={svarslit}:        9.0B
.                                            *Options={dnumnvar}:   Optional
.                                            *Delimiter={svarslit}  Optional
.   LoadXmlFile         GIVING {nvar}  USING *FileName={svarslit}:        9.0B
.                                            *Options={dnumnvar}:   Optional
.                                            *TableName={svarslit}: Optional
.                                            *RowName={svarslit}    Optional
.   SaveCsvFile         GIVING {nvar}  USING *FileName={svarslit}:        9.0B
.                                            *Options={dnumnvar}:   Optional
.                                            *Delimiter={svarslit}  Optional
.   SaveXmlFile         GIVING {nvar}  USING *FileName={svarslit}:        9.0B
.                                            *Options={dnumnvar}:   Optional
.                                            *TableName={svarslit}: Optional
.                                            *RowName={svarslit}    Optional
.   SaveXmlToDim         GIVING {svar} USING *Options={dnumnvar}:   Optional
.                                            *TableName={svarslit}: Optional
.                                            *RowName={svarslit}    Optional
.   SetColResizeFlag     GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Flag={dnumnvar}
.   SetColumnFormat      GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Format={dnumnvar}
.   SetColumnImage       GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Image={dnumnvar}
.   SetColumnOrder       GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Order={dnumnvar}
.   SetColumnText        GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Text={svarlit}
.   SetColumnWidth       GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Width={dnumnvar}:
.                                            *Flags={dnumnvar}            9.5A
.   SetColumnWidths      GIVING {nvar} USING *WIDTHS={svarlit}            10.3A
.   SetExtendedStyle     GIVING {nvar} USING *MASK={dnumnvar}:
.                                            *STYLE={dnumnvar}
.   SetIconSpacing	 GIVING {nvar} USING *Width={dnumnvar}:		  9.6
.                                            *Height={dnumnvar}:
.                                            *WidthMin={dnumnvar}:
.                                            *WidthMax={dnumnvar}:
.                                            *HeightMin={dnumnvar}:
.                                            *HeightMax={dnumnvar}
.   SetImageList         GIVING {nvar} USING *ImageList={imagelist}
.   SetImageListSmall    GIVING {nvar} USING *ImageList={imagelist}
.   SetImageListState    GIVING {nvar} USING *ImageList={imagelist}
.   SetItemCheck         GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Value={dnumnvar}
.   SetItemImage         GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Image={dnumnvar}
.   SetItemParam         GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Param={dnumnvar}
.   SetItemState         GIVING {nvar} USING *Index={dnumnvar}:
.                                            *State={dnumnvar}:
.                                            *StateMask={dnumnvar}
.   SetItemText          GIVING {nvar} USING *Index={dnumnvar}:
.                                            *Text={svarlit}:
.                                            *SubItem={dnumnvar}   Optional
.   SetItemTextAll       GIVING {nvar} USING *Index={dnumnvar}:           9.1A
.                                            *Text={svarlit}:
.                                            *Delimiter={svarlit}: Optional
.                                            *Options={dnumnvar}   Optional
.   SetLVFlags           GIVING {nvar} USING *Flags={dnumnvar}:		  9.4C
.                                            *Mode={dnumnvar}
.   SortColumn           GIVING {nvar} USING *Column={dnumnvar}:
.                                            *Type={dnumnvar}:
.                                            *Mask={svarlit}:
.                                            *Column1={col1}:      Optional
.                                            *Type1={type1}:       Optional
.                                            *Mask1={mask1}:       Optional
.                                            *Column2={col2}:      Optional
.                                            *Type2={type2}:       Optional
.                                            *Mask2={mask2}:       Optional
.                                            *Column3={col3}:      Optional
.                                            *Type3={type3}:       Optional
.                                            *Mask3={mask3}        Optional
.   SubItemHitTest       GIVING {nvar} USING *Horz={dnumnvar}:
.                                            *Vert={dnumnvar}:
.                                            *Flags={dnumnvar} Optional	  9.4A
.   Update               GIVING {nvar}
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
LVA_DEFAULT      Integer 4,"0x0000"         ;Arrange Code
LVA_ALIGNLEFT    Integer 4,"0x0001"
LVA_ALIGNTOP     Integer 4,"0x0002"
LVA_SNAPTOGRID   Integer 4,"0x0005"
 
LVFI_PARTIAL     Integer 4,"0x0008"         ;FindItem Flags
 
LVNI_ALL         Integer 4,"0x0000"         ;GetNextItem Flags
LVNI_FOCUSED     Integer 4,"0x0001"
LVNI_SELECTED    Integer 4,"0x0002"
LVNI_CUT         Integer 4,"0x0004"
LVNI_DROPHILITED Integer 4,"0x0008"
LVNI_ABOVE       Integer 4,"0x0100"
LVNI_BELOW       Integer 4,"0x0200"
LVNI_TOLEFT      Integer 4,"0x0400"
LVNI_TORIGHT     Integer 4,"0x0800"
 
LVCFMT_LEFT            Integer 4,"0x00000000" ;InsertColumn Format
LVCFMT_RIGHT           Integer 4,"0x00000001"
LVCFMT_CENTER          Integer 4,"0x00000002"
LVCFMT_FIXED_WIDTH     Integer 4,"0x00000100" ;Windows Vista		  9.4B
LVCFMT_IMAGE           Integer 4,"0x00000800" ;Column has image           8.6B
LVCFMT_BITMAP_ON_RIGHT Integer 4,"0x00001000" ;Image displayed on right   8.6B
LVCFMT_COL_HAS_IMAGES  Integer 4,"0x00008000"                             8.6B
LVCFMT_NO_DPI_SCALE    Integer 4,"0x00040000" ;Windows Vista		  9.4B
LVCFMT_FIXED_RATIO     Integer 4,"0x00080000" ;Windows Vista		  9.4B
LVCFMT_SPLITBUTTON     Integer 4,"0x01000000" ;Windows Vista		  9.4B
.
                                            ;InsertItem   State/StateMask
                                            ;GetItemState       StateMask
LVIS_FOCUSED        Integer 4,"0x0001"      ;SetItemState State/StateMask
LVIS_SELECTED       Integer 4,"0x0002"
LVIS_CUT            Integer 4,"0x0004"
LVIS_DROPHILITED    Integer 4,"0x0008"
LVIS_OVERLAYMASK    Integer 4,"0x0F00"
LVIS_STATEIMAGEMASK Integer 4,"0xF000"
 
LVS_EX_GRIDLINES        Integer 4,"0x00000001" ;SetExtendedStyle MASK/STYLE
LVS_EX_CHECKBOXES       Integer 4,"0x00000004" ;& GetExtendedStyle return value
LVS_EX_TRACKSELECT      Integer 4,"0x00000008" ;
LVS_EX_HEADERDRAGDROP   Integer 4,"0x00000010"
LVS_EX_FULLROWSELECT    Integer 4,"0x00000020" ;applies to report mode only
LVS_EX_ONECLICKACTIVATE Integer 4,"0x00000040"
LVS_EX_UNDERLINEHOT     Integer 4,"0x00000800"
LVS_EX_UNDERLINECOLD    Integer 4,"0x00001000"
 
$LV_XMLRD_IGNORE_ATTR   Integer 4,"0x001"   ;LoadXmlFile Options          9.0B
$LV_XMLRD_NO_CONV       Integer 4,"0x002"
$LV_XMLRD_USECOLUMNS    Integer 4,"0x004"
 
$LV_XMLWR_NOATTR        Integer 4,"0x0001"  ;SaveXmlFile Options          9.0B
$LV_XMLWR_NOCOLS        Integer 4,"0x0002"
$LV_XMLWR_NOATTRCOLS    Integer 4,"0x0004"
$LV_XMLWR_OUTPUTASATTR  Integer 4,"0x0008"
$LV_XMLWR_OUTPUTSEL     Integer 4,"0x0010"
$LV_XMLWR_OUTPUTCHK     Integer 4,"0x0020"
$LV_XMLWR_OUTPUTALLATTR	Integer	4,"0x0040"
$LV_XMLWR_NOZEROWIDTH	Integer	4,"0x0080"
$LV_XMLWR_ISO8859	Integer	4,"0x0100"				  9.2B
$LV_XMLWR_LOWERCASE	Integer	4,"0x0200"				  9.3A
$LV_XMLWR_UPPERCASE	Integer	4,"0x0400"				  9.3A
$LV_XMLWR_OUTPUTHEADER	Integer 4,"0x0800"				  9.4E
$LV_XMLWR_NAMEATTR	Integer 4,"0x1000"				  9.4E
 
$LV_CSVRD_QUOTED        Integer 4,"0x001"   ;LoadCsvFile Options          9.0B
$LV_CSVRD_INPUTHEADER   Integer 4,"0x008"                                 9.1A
$LV_CSVRD_NOZEROWIDTH   Integer 4,"0x010"                                 9.1A
$LV_CSVRD_NOOEM2ANSI	Integer 4,"0x100"				  9.9A
 
$LV_CSVWR_QUOTED        Integer 4,"0x001"   ;SaveCsvFile Options          9.0B
$LV_CSVWR_OUTPUTSEL     Integer 4,"0x002"
$LV_CSVWR_OUTPUTCHK     Integer 4,"0x004"
$LV_CSVWR_OUTPUTHEADER  Integer 4,"0x008"                                 9.1A
$LV_CSVWR_NOZEROWIDTH   Integer 4,"0x010"                                 9.1A
$LV_CSVWR_LOWERCASE	Integer 4,"0x020"				  9.3A
$LV_CSVWR_UPPERCASE	Integer 4,"0x040"				  9.3A
$LV_CSVWR_ORDERARRAY	Integer 4,"0x080"				  9.4D
 
$LV_GETITEM_QUOTED      Integer 4,"0x001"   ;GetItemTextAll Options       9.1A
$LV_GETITEM_NOZEROWIDTH Integer 4,"0x010"                                 9.1A
$LV_GETITEM_ORDERARRAY	Integer 4,"0x080"				  9.4D
 
$LV_SETITEM_QUOTED        Integer 4,"0x001"   ;SetItemTextAll Options     9.1A
$LV_SETITEM_NOZEROWIDTH   Integer 4,"0x010"                               9.1A
$LV_SETITEM_REPLACEROW    Integer 4,"0x020"                               9.1C
$LV_SETITEM_SKIPNULL      Integer 4,"0x040"                               9.1C
$LV_SETITEM_NOBINARYCHARS Integer 4,"0x080"				  9.4E
.
$LV_EXTENDED_FORMAT1    Integer 4,"0x001"   ;SubitemHitTest Flags	  9.4A
.
$LV_SCW_EXTENDED          Integer 4,"0x00000001"  ;SetColumnWidth Flags   9.5A
$LV_SCW_AUTOSIZE          Integer 4,"0x00000003"                          9.5A
$LV_SCW_AUTOSIZEHEADER    Integer 4,"0x00000005"                          9.5A
$LV_SCW_ALLCOLUMNS        Integer 4,"0x00008000"                          9.5A
$LV_SCWALL_EXTENDED       Integer 4,"0x00008001"                          9.5A
$LV_SCWALL_AUTOSIZE       Integer 4,"0x00008003"                          9.5A
$LV_SCWALL_AUTOSIZEHEADER Integer 4,"0x00008005"                          9.5A
.
*------------------------------------------------------------------------------
.   MENU                                                                  9.0
.
. Events:
.
.   $CLICK        EQU    4
.   $ITEMCLICK    EQU    26
.
. Properties:
.
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   MDILIST=dnumnvar                         CREATE  SETPROP  GETPROP
.   MENUORDER=dnumnvar                               SETPROP  GETPROP
.   MERGETYPE=dnumnvar                               SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   TEXT=svarslit                                    SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.
. Methods:
.
.   AddItem              GIVING {nvar} USING *CHECKED={dnumnvar}:     Optional
.                                            *DEFAULT={dnumnvar}:     Optional
.                                            *ENABLED={dnumnvar}:     Optional
.                                            *ITEMPOS={dnumnvar}:     Optional
.                                            *SEPARATOR={dnumnvar}:   Optional
.                                            *SHORTCUT={dnumnvar}:    Optional
.                                            *SPCMENU={dnumnvar}:     Optional
.                                            *SUBMENU={submenu obj}:  Optional
.                                            *TAG={dnumnvar}:         Optional
.                                            *TEXT={svarslit}:        Optional
.                                            *RUNNAME={svarslit}:     Optional
.                                            *HELPID={dnumnvar}:      Optional
.                                            *HELPTOPIC={svarslit}:   Optional
.                                            *USERDATA={svarslit}     Optional
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   GetItem              GIVING {menuitem object} USING *KEY={svarslit}
.   GetItemCount         GIVING {nvar} USING *KEY={nvar | svarslit}       9.0F
.   GetItemName          GIVING {svar} USING *KEY={nvar | svarslit}       9.0F
.   GetItemState         GIVING {nvar} USING *KEY={nvar | svarslit}       9.0F
.   GetItemType          GIVING {nar} USING *KEY={nvar | svarslit}        9.0F
.   RemoveItem           GIVING {nvar} USING *KEY={svarslit}
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
.MFT_END                 Integer 4,"0xFFFFFFFF"   ;GetItemType {nvar} returned
.MFT_STRING              Integer 4,"0x00000000"
.MFT_BITMAP              Integer 4,"0x00000004"
.MFT_MENUBARBREAK        Integer 4,"0x00000020"
.MFT_MENUBREAK           Integer 4,"0x00000040"
.MFT_SEPARATOR           Integer 4,"0x00000800"
.MFT_RIGHTORDER          Integer 4,"0x00002000"
.
.MFS_END                 Integer 4,"0xFFFFFFFF"   ;GetItemState {nvar} returned
.MFS_CHECKED             Integer 4,"0x00000008"
.MFS_DEFAULT             Integer 4,"0x00001000"
.MFS_DISABLED            Integer 4,"0x00000003"
.MFS_GRAYED              Integer 4,"0x00000003"
.MFS_ENABLED             Integer 4,"0x00000000"
.MFS_HILITE              Integer 4,"0x00000080"
.
*------------------------------------------------------------------------------
.   MENUITEM                                                              9.0F
.
. Events:
.
. Properties:
.
.   CHECKED=dnumnvar                                 SETPROP  GETPROP
.   DEFAULT=dnumnver                                 SETPROP  GETPROP
.   ENABLED=dnumnvar                                 SETPROP  GETPROP
.   HELPID=dnumnvar                                  SETPROP  GETPROP     9.1C
.   HELPTOPIC=svarslit                               SETPROP  GETPROP     9.4B
.   RUNNAME=svarslit                                 SETPROP  GETPROP
.   SEPARATOR=dnumnvar                               SETPROP  GETPROP
.   SHORTCUT=dnumnvar                                SETPROP  GETPROP
.   SPECIALMENU=dnumnvar                             SETPROP  GETPROP
.   SUBMENU=dnumnvar                                 SETPROP  GETPROP
.   TAG=dnumnvar                                     SETPROP  GETPROP
.   TEXT=svarslit                                    SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.
. Methods:
.
.   GetItem              GIVING {menuitem object} USING *KEY={nvar | svarslit}
.   GetItemCount         GIVING {nvar} USING *KEY={nvar | svarslit}
.   GetItemName          GIVING {svar} USING *KEY={nvar | svarslit}
.   GetItemState         GIVING {nvar} USING *KEY={nvar | svarslit}
.   GetItemType          GIVING {nar} USING *KEY={nvar | svarslit}
.
. Method Constants:
.
.MFT_END                 Integer 4,"0xFFFFFFFF"   ;GetItemType {nvar} returned
.MFT_STRING              Integer 4,"0x00000000"
.MFT_BITMAP              Integer 4,"0x00000004"
.MFT_MENUBARBREAK        Integer 4,"0x00000020"
.MFT_MENUBREAK           Integer 4,"0x00000040"
.MFT_SEPARATOR           Integer 4,"0x00000800"
.MFT_RIGHTORDER          Integer 4,"0x00002000"
.
.MFS_END                 Integer 4,"0xFFFFFFFF"   ;GetItemState {nvar} returned
.MFS_CHECKED             Integer 4,"0x00000008"
.MFS_DEFAULT             Integer 4,"0x00001000"
.MFS_DISABLED            Integer 4,"0x00000003"
.MFS_GRAYED              Integer 4,"0x00000003"
.MFS_ENABLED             Integer 4,"0x00000000"
.MFS_HILITE              Integer 4,"0x00000080"
.
.
*------------------------------------------------------------------------------
.   MODULE                                                                10.6
.
. Events:
.
.   None
.
. Properties:
.
.   None
.
. Methods:
.
.   InitializeUda   GIVING {nvar} USING *Flags={dnumnvar}
.   
.   UnLoad          GIVING {nvar} USING *Flags={dnumnvar}
. 
*------------------------------------------------------------------------------
.   MOVIE                                                                
.
. Events:
.
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   HWND=nvar                                                   GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT      CREATE  SETPROP GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   None
.
*------------------------------------------------------------------------------
.   MREGION                                                                
.
. Events:
.
.   $CLICK        EQU    4
.   $DBLCLICK     EQU    6
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
*------------------------------------------------------------------------------
.   NETCONTROL
.
. Events:
.
.   Reference vendor documentation for .NET control for supported events.
.
. Properties:
.
.   ACCEPTTAB=dnumnvar                       CREATE  SETPROP  GETPROP
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   ENTERTAB=dnumnvar                        CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP     9.4B
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
.   Reference vendor documentation for .NET control for additional
.   properties which are supported.
.
. Methods:
.
.   Reference vendor documentation for .NET control for supported methods.
.
. Method Constants:
.
.   Reference vendor documentation for .NET control for method parameter
.   values.
.
*------------------------------------------------------------------------------
.   NETOBJECT
.
. Events:
.
.   Reference vendor documentation for .NET object for supported events.
.
. Properties:
.
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.
.   Reference vendor documentation for .NET object for additional
.   properties which are supported.
.
. Methods:
.
.   Reference vendor documentation for .NET object for supported methods.
.
. Method Constants:
.
.   Reference vendor documentation for .NET object for method parameter
.   values.
.
*------------------------------------------------------------------------------
.   PANEL
.
. Events:
.
.   $CLICK	  EQU    4 // PL/B Web Server ONLY!
.   $DBLCLICK	  EQU    6 // PL/B Web Server ONLY!
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $PAINT        EQU    16
.   $RESIZE       EQU    17
.
. Properties:
.
.   ANCHOR=dnumnvar                             CREATE  SETPROP GETPROP
.   AUTOREDRAW=dnumnvar                         CREATE  SETPROP GETPROP
.   AUTOSCROLL=dnumnvar                         CREATE  SETPROP GETPROP     8.6C
.   BDRSTYLE=dnumnvar (PANEL)                   CREATE  SETPROP GETPROP
.   BGCOLOR=dnumnvar|color object               CREATE  SETPROP GETPROP
.   CLIPCTRL=dnumnvar                           CREATE  SETPROP GETPROP
.   DOCK=dnumnvar                               CREATE  SETPROP GETPROP
.   DOCKPADB=dnumnvar                           CREATE  SETPROP GETPROP
.   DOCKPADL=dnumnvar                           CREATE  SETPROP GETPROP
.   DOCKPADR=dnumnvar                           CREATE  SETPROP GETPROP
.   DOCKPADT=dnumnvar                           CREATE  SETPROP GETPROP
.   ENABLED=dnumnvar                            CREATE  SETPROP GETPROP
.   HEIGHT=dnumnvar                                     SETPROP GETPROP
.   HWND=nvar                                                   GETPROP
.   LEFT=dnumnvar                                       SETPROP GETPROP
.   MINSCROLLH=dnumnvar                         CREATE  SETPROP GETPROP
.   MINSCROLLV=dnumnvar                         CREATE  SETPROP GETPROP
.   OBJECTID=dnumnvar                           CREATE  SETPROP GETPROP
.   RUNNAME=svarslit                            CREATE  SETPROP GETPROP
.   SCROLLBAR[=dnumnvar]                        CREATE  SETPROP GETPROP
.   TOOLTIP=svarslit                            CREATE  SETPROP GETPROP
.   TOP=dnumnvar                                        SETPROP GETPROP
.   USERDATA=svarslit                           CREATE  SETPROP GETPROP     9.4B
.   VISIBLE=dnumnvar                            CREATE  SETPROP GETPROP
.   WEBCLASS=svarslit (PWS only)                CREATE  SETPROP GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)               CREATE  SETPROP GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)                 CREATE  SETPROP GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)             CREATE  SETPROP GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)                  CREATE  SETPROP GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)                CREATE  SETPROP GETPROP	  9.9
.   WIDTH=dnumnvar                                      SETPROP GETPROP
.   WINOFFSETH=dnumnvar                                 SETPROP GETPROP
.   WINOFFSETV=dnumnvar                                 SETPROP GETPROP
.   ZORDER=dnumnvar                             CREATE  SETPROP GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   GetChildCount        GIVING {nvar}
.   GetObjectAsPointer   GIVING (object} USING *Key={dnumnvar|svarlit}:   9.2C
.                                              *Flags={dnumnvar} Optional 9.2C
.   InnerHtml            GIVING {nvar} USING *Html={svarslit}:		  9.7
.                                            *Flags={dnumnvar} Optional   9.7
.   PrtPreviewAction     GIVING {nvar} USING *Action={dnumnvar}:          9.4D
.                                            *Value={dnumnvar} Optional   9.4D
.   PrtPreviewClose      GIVING {nvar}                                    9.4D
.   PrtPreviewOpen       GIVING {nvar} USING *SpoolFile={svarslit}:
.                                            *PrinterName={svarslit}:  Optional 
.                                            *StartPage={dnumnvar}:    Optional
.                                            *GotoPage={dnumnvar}:     Optional
.                                            *EndPage={dnumnvar}:      Optional
.                                            *Zoom={dnumnvar}          Optional
.   SetBGColorTransparent GIVING {nvar} USING *Mode={dnumnvar}                             
.   SetHScrollPos        GIVING {nvar} USING *Position={dnumnvar}	  9.2
.   SetVScrollPos        GIVING {nvar} USING *Position={dnumnvar}	  9.2
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
...........
. For SetBGColorTransparent *Mode={dnumnvar} 
.
. $OFF	 EQU	   0
. $ON	 EQU	   1
.
...........
. For SetHScrollPos *Position={dnumnvar}
.
.$SB_LINELEFT	EQU	0	;Scroll left on unit.			  9.2
.$SB_LINERIGHT	EQU	1	;Scroll right one unit.			  9.2
.$SB_PAGELEFT	EQU	2	;Scroll left one page.			  9.2
.$SB_PAGERIGHT	EQU	3	;Scroll right one page.			  9.2
.$SB_LEFT	EQU	6	;Scroll to minimum left position.	  9.2
.$SB_RIGHT	EQU	7	;Scroll to maximum right position.	  9.2
.
...........
. For SetVScrollPos *Position={dnumnvar}
.
.$SB_LINEUP	EQU	0	;Scroll up one line.			  9.2
.$SB_LINEDOWN	EQU	1	;Scroll down one line.			  9.2
.$SB_PAGEUP	EQU	2	;Scroll up one page.			  9.2
.$SB_PAGEDOWN	EQU	3	;Scroll down one page.			  9.2
.$SB_TOP	EQU	6	;Scroll to minimum top position.  9.2
.$SB_BOTTOM	EQU	7	;Scroll to maximum bottom position.	  9.2
...........
. For InnerHtml *Flags={dnumnvar}
.
.$HTML_HAS_EVENTS	EQU	1	;Panel only
.$HTML_FROM_URL		EQU	2	;HTML parameter is a URL
.$HTML_USE_SCROLLBARS	EQU	4	;Plbwin only
.$HTML_3D_BORDER		EQU	8	;Plbwin only
.
*------------------------------------------------------------------------------
.   PICT
.
. Events:
.
.   $CLICK        EQU    4
.   $DBLCLICK     EQU    6
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   ALTTEXT=svarslit (PWS only)              CREATE           GETPROP	  9.7
.   ANCHOR=dnumnvar                          CREATE  SETPROP GETPROP
.   AUTOSCALE=dnumnvar                       CREATE  SETPROP  GETPROP
.   AUTOZOOM[=dnumnvar]                      CREATE  SETPROP  GETPROP
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   LINKHSCROLL=<hscrollbar>                 CREATE           GETPROP
.   LINKVSCROLL=<vscrollbar>                 CREATE           GETPROP
.   NOAUTOZOOM  (OBSELETE)                   CREATE
.   NORESIZE    (OBSELETE)                   CREATE
.   NOSCROLL    (OBSELETE)                   CREATE
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   PAGE=dnumnvar                            CREATE
.   PICTSIZEH=nvar                                            GETPROP
.   PICTSIZEV=nvar                                            GETPROP
.   POS=dnumnvarH:dnumnvarV                          SETPROP  GETPROP
.   RESIZE=dnumnvar                          CREATE  SETPROP  GETPROP
.   RESOURCE=dnumnvar                                SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP GETPROP
.   SCALE=dnumnvar                           CREATE  SETPROP  GETPROP
.   SCROLLBAR[=dnumnvar]                     CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   URLSOURCE=svarslit (PWS only)            CREATE           GETPROP	  9.7
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   GetPageCount         GIVING {nvar}
.   GetZBottom           GIVING {nvar}
.   GetZLeft             GIVING {nvar}
.   GetZRight            GIVING {nvar}
.   GetZTop              GIVING {nvar}
.   Rotate               GIVING {nvar} USING *Degree={dnumnvar}
.   WriteBmpFile         GIVING {nvar} USING *FileName={svarslit}
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
DEG_90   Integer 4,"90"                ;Rotate Degree
DEG_180  Integer 4,"180"
DEG_270  Integer 4,"270"
.
*------------------------------------------------------------------------------
.   PROGRESS                                                                
.
. Events:
.
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   NOPERCENT                                CREATE  
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   PERCENT=dnumnvar                         CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VALUE=dnumnvar                                   SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
*------------------------------------------------------------------------------
.   RADIO                                                             
.
. Events:
.
.   $CLICK        EQU    4
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ALIGNTEXT=dnumnvar                       CREATE  SETPROP  GETPROP
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FLOATMENU=dnumnvar                       CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   GROUPID=dnumnvar                         CREATE  SETPROP  GETPROP
.   GROUPVALUE=dnumnvar                              SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   PUSHLIKE=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SELGROUPID=dnumnvar                                       GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   THEME=svarslit                           CREATE  SETPROP  GETPROP
.   TITLE=svarslit                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VALUE=dnumnvar                                   SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
*------------------------------------------------------------------------------
.   RADIOGRP                                                              
.
. Events:
.
.   $CLICK        EQU    4
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOVE         EQU    12
.
. Properties:
.
.   ALIGNTEXT=dnumnvar                       CREATE  SETPROP  GETPROP
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   THEME=svarslit                           CREATE  SETPROP  GETPROP
.   TITLE=svarslit                           CREATE  SETPROP  GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   TRISTATE=dnumnvar                        CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VALUE=dnumnvar                                   SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.
*------------------------------------------------------------------------------
.   RICHEDITTEXT                                                          9.0B
.
. Events:
.
.   $CHANGE       EQU    3
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $VALIDATE     EQU    24
.   $SELCHANGE    EQU    30
.   $LINKCLICK    EQU    31
.
. Properties:
.
.   ACCEPTTAB=dnumnvar                       CREATE  SETPROP  GETPROP
.   ALIGNMENT=dnumnvar                       CREATE  SETPROP  GETPROP
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   AUTOENTER=dnumnvar                       CREATE  SETPROP  GETPROP
.   AUTOWORDSEL=dnumnvar                     CREATE  SETPROP  GETPROP
.   BDRSTYLE=dnumnvar (RICHEDITTEXT)         CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BULLETINDENT=dnumnvar                    CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DETECTURL=dnumnvar                       CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   EDITHIDESEL=dnumnvar                     CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar (Objects not MENUITEM)  CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP     9.4B
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   LEFTMARGIN=dnumnvar                      CREATE  SETPROP  GETPROP
.   MAXCHARS=dnumnvar                        CREATE  SETPROP  GETPROP
.   MODIFYFLAG=dnumnvar                              SETPROP  GETPROP
.   MULTILINE=dnumnvar                       CREATE  SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   OVERTYPE=dnumnvar                        CREATE  SETPROP  GETPROP
.   PASSWORD[=dnumnvar]                      CREATE
.   PASSWORDCHAR=svarslit                    CREATE  SETPROP  GETPROP
.   READONLY[=dnumnvar]                      CREATE           GETPROP
.   RIGHTMARGIN=dnumnvar                     CREATE  SETPROP  GETPROP
.   RTF=svarslit                                     SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SCROLLBAR[=dnumnvar]                     CREATE  SETPROP  GETPROP
.   SCROLLHIDE=dnumnvar                      CREATE           GETPROP
.   SELALIGN=dnumnvar                                SETPROP  GETPROP
.   SELBULLET=dnumnvar                               SETPROP  GETPROP
.   SELCHAROFFSET=dnumnvar                           SETPROP  GETPROP
.   SELCOLOR=dnumnvar|color object                   SETPROP  GETPROP
.   SELECTALL=dnumnvar                       CREATE  SETPROP  GETPROP
.   SELECTEDRTF=svarslit                             SETPROP  GETPROP
.   SELFONTBOLD=dnumnvar                             SETPROP  GETPROP
.   SELFONTCHARSET=dnumnvar                          SETPROP  GETPROP
.   SELFONTITALIC=dnumnvar                           SETPROP  GETPROP
.   SELFONTNAME=svarslit                             SETPROP  GETPROP
.   SELFONTSIZE=dnumnvar                             SETPROP  GETPROP
.   SELFONTUNDER=dnumnvar                            SETPROP  GETPROP
.   SELHANGINDENT=dnumnvar                           SETPROP  GETPROP
.   SELLENGTH=dnumnvar                               SETPROP  GETPROP
.   SELPROTECTED=dnumnvar                            SETPROP  GETPROP
.   SELRIGHTINDENT=dnumnvar                          SETPROP  GETPROP
.   SELSTART=dnumnvar                                SETPROP  GETPROP
.   SELTEXT=svarslit                                 SETPROP  GETPROP
.   SELTYPE=nvar                                              GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TEXT=svarslit                                    SETPROP  GETPROP
.   TEXTOUTCONV=dnumnvar                     CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   WORDWRAP[=dnumnvar]                      CREATE  SETPROP  GETPROP
.   ZOOMFACTOR=dnumnvar                      CREATE  SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   CanRedo              GIVING {nvar}
.   CanUndo              GIVING {nvar}
.   Clear                GIVING {nvar}
.   ClearUndo            GIVING {nvar}
.   Copy                 GIVING {nvar}
.   Cut                  GIVING {nvar}
.   FindText             GIVING {nvar} USING *Search={dnumnvar}:
.                                            *Text={svarlit}:
.                                            *Start={dnumnvar}:    Optional
.                                            *End={dnumnvar}       Optional
.   GetCharIndexFromPos  GIVING {nvar} USING *Vert={dnumnvar}:
.                                            *Horz={dnumnvar}
.   GetFirstVisibleLine  GIVING {nvar}
.   GetLine              GIVING {svar} USING *Line={dnumnvar}
.   GetLineCount         GIVING {nvar}
.   GetPosFromCharIndex  GIVING {nvar} USING *CharIndex={dnumnvar}
.   GetTextLength        GIVING {nvar}
.   GetUnicode           GIVING {svar} USING [*Flags=]{dnumnvar}          9.6C
.   LineFromChar         GIVING {nvar} USING *CharIndex={dnumnvar}
.   LineIndex            GIVING {nvar} USING *Line={dnumnvar}
.   LineLength           GIVING {nvar} USING *CharIndex={dnumnvar}
.   LineScroll           GIVING {nvar} USING *Chars={dnumnvar}:
.                                            *Lines={dnumnvar}
.   LoadFile             GIVING {nvar} USING *FileName={svarlit}:
.                                            *Options={dnumnvar}   Optional
.   Paste                GIVING {nvar}
.   Redo                 GIVING {nvar}
.   RedoActionName       GIVING {nvar}
.   SaveFile             GIVING {nvar} USING *FileName={svarlit}:
.                                            *Options={dnumnvar}   Optional
.   Scroll               GIVING {nvar} USING *Action={dnumnvar}
.   ScrollToCaret        GIVING {nvar}
.   Select               GIVING {nvar} USING *Start={dnumnver}:
.                                            *End={dnumnvar}
.   SelectAll            GIVING {nvar}
.   SetUnicode           GIVING {nvar} USING [*String=]{svarlit}:         9.6C
.                                            [*Flags=]{dnumnvar}
.   Undo                 GIVING {nvar}
.   UndoActionName       GIVING {nvar}
.
. Collection Support:
.
.   None
.
. Method Constants:
.
. FindText *Search= values
.
$FR_DOWN           Integer 4,"0x01"         ;FindText Search
$FR_WHOLEWORD      Integer 4,"0x02"
$FR_MATCHCASE      Integer 4,"0x04"
 
. LoadFile / SaveFile *Options=
.
. Stream formats.
.
$SF_TEXT           Integer 4,"0x0001"       ;LoadFile/Save Options
$SF_RTF            Integer 4,"0x0002"
$SF_RTFNOOBJS      Integer 4,"0x0003"
$SF_TEXTIZED       Integer 4,"0x0004"
$SF_UNICODE        Integer 4,"0x0010"
$SF_USECODEPAGE    Integer 4,"0x0020"
$SFF_SELECTION     Integer 4,"0x8000"
 
.
. RedoActionName / UndoActionName Results
.
$ACTIONUNKNOWN     Integer 4,"0"            ;RedoActionName/UndoActionName
$ACTIONTYPING      Integer 4,"1"            ;  results
$ACTIONDELETE      Integer 4,"2"
$ACTIONDRAGDROP    Integer 4,"3"
$ACTIONCUT         Integer 4,"4"
$ACTIONPASTE       Integer 4,"5"
.
*------------------------------------------------------------------------------
.   RUNTIME                                                               9.7A
.
. Events:
.
.   $CHILDSIG     EQU    33	;PL/B Web Server RUNTIME ONLY		  9.8
.   $RUNSUSPEND   EQU    34	;PL/B Web Server RUNTIME ONLY		  9.9
.   $RUNRESUME    EQU    35	;PL/B Web Server RUNTIME ONLY		  9.9
.   $RUNIDLE      EQU    36	;PL/B Web Server RUNTIME ONLY		  9.9
.
. Properties:
.
.   none
.
. Methods:
.
.   CheckHost       GIVING {nvar} USING *HostName={svarslit}:             10.1A
.                                       *Port={dnumnvar}:     Optional
.                                       *Timeout={dnumnvar}:  Optional
.                                       *Options={dnumnvar}   Optional
.   CgiString       GIVING {svar} USING *Key={svarslit}:                  9.8A
.                                       *Options={dnumnvar}   Optional   
.   GetChildId      GIVING {svar} USING *Options={dnumnvar}   Optional	  9.8
.   GetDir          GIVING {svar} USING *Type={dnumnvar}
.   GetFileTimes    GIVING {runtime} USING *FileName={svarslit}:          10.6A
.                                       *CreateTime={datetime}: Optional
.                                       *AccessTime={datetime}: Optional
.                                       *WriteTime={datetime}   Optional
.   GetKnownPath    GIVING {svar} USING *Type={dnumnvar}                  10.5
.   HttpResponse    GIVING {nvar} USING *HttpCode={dnumnvar}:             9.9A
.                                       *MimeType={svarslit}: Optional
.                                       *Body={svarslit}:     Optional
.                                       *ExtraHdrs={svarslit}:Optional
.                                       *OutFile={svarslit}:  Optional
.                                       *Options={dnumnvar}   Optional
.   HttpRequest     GIVING {nvar} USING *TimeOut={dnumnvar}:  Optional    10.2A
.                                       *Options={dnumnvar}   Optional
.   HttpStdinSize   GIVING {nvar}                                         10.2A
.   HttpStdinData   GIVING {svar} USING *Offset={dnumnvar}:   Optional 	  10.2A
.                                       *Options={dnumnvar}   Optional
.   IntParse        GIVING {nvar} USING *NUMERICSTR={svarslit}:           10.3A
.                                       *FORMAT={dnumnvar}       Optional
.   IntToString     GIVING {svar} USING *INTEGER={nvar}:                  10.3A
.                                       *FORMAT={dnumnvar}
.   JqmOptions	    GIVING {nvar} USING *Header={svarslit}:      Optional 9.9B
.                                       *Footer={svarslit}:      Optional
.                                       *Transition={svarslit}:  Optional
.                                       *Theme={svarslit}:	 Optional
.                                       *Options={dnumnvar}      Optional
.   JqmPage         GIVING {nvar} USING *Action={dnumnvar}:		  9.9B
.                                       *Position={dnumnvar}:    Optional
.                                       *Transition={svarslit}:  Optional
.                                       *Options={dnumnvar}      Optional
.   SetFileTimes    GIVING {nvar} USING *FileName={svarslit}:             10.6A
.                                       *CreateTime={datetime}:  Optional
.                                       *AccessTime={datetime}:  Optional
.                                       *WriteTime={datetime}    Optional
.   SetWebTheme     GIVING {nvar} USING *Theme={dnumnvar}:       Optional 10.6
.                                       *Context={dnumnvar}:     Optional
.                                       *Options={dnumnvar}      Optional
.   SignalChild     GIVING {nvar} USING *ChildId={svarslit}:		  9.8
.                                       *Options={dnumnvar}   Optional
.   VerifyUtf       GIVING {nvar} USING *STRING={svarslit}:               10.1B
.                                       *FLAGS={dnumvar}:        Optional
.                                       *LENGTH={dnumnvar}       Optional
.
. Method Constants:
.
. GetDir Method *Type Values
.
$GETDIR_CURRENT         EQU  0   ;Current working directory returned
$GETDIR_PROGRAMROOT     EQU  1   ;PLBWEB_PROGRAM_ROOT keyword returned
$GETDIR_PROGRAMROOTSSL  EQU  2   ;PLBWEB_SSL_PROGRAM_ROOT keyword returned
$GETDIR_ROOT            EQU  3   ;PLBWEB_ROOT keyword returned
$GETDIR_ROOTSSL         EQU  4   ;PLBWEB_SSL_ROOT keyword returned
$GETDIR_CLIENTNAME      EQU  5   ;Client name				  9.8
$GETDIR_UPLOADS         EQU  6   ;PLBWEB_UPLOADS			  9.8
.
. GetChildId Method *Options Values
. 
$GETCHILDID_IDSTRING    EQU  0   ;Return the IDnnnnnn identifier!	  9.8
.
. GetKnownPath Method *Type Values					  10.5
. 
$FOLDERID_Desktop		CONST "0"
$FOLDERID_Documents		CONST "1"
$FOLDERID_Downloads		CONST "2"
$FOLDERID_Fonts			CONST "3"
$FOLDERID_Music			CONST "4"
$FOLDERID_OneDrive		CONST "5"
$FOLDERID_Pictures		CONST "6"
$FOLDERID_Programs		CONST "7"
$FOLDERID_ProgramData		CONST "8"
$FOLDERID_ProgramFiles		CONST "9"
$FOLDERID_RoamingAppData	CONST "10"	
$FOLDERID_System		CONST "11"
$FOLDERID_SystemX86		CONST "12"
$FOLDERID_Videos		CONST "13"
$FOLDERID_Windows		CONST "14"

$FOLDERID_LocalAppData		CONST "15"
$FOLDERID_LocalDocuments	CONST "16"
$FOLDERID_LocalDownloads	CONST "17"
$FOLDERID_LocalMusic		CONST "18"
$FOLDERID_LocalPictures		CONST "19"
$FOLDERID_LocalVideos		CONST "20"

$FOLDERID_Public		CONST "21"
$FOLDERID_PublicDesktop		CONST "22"
$FOLDERID_PublicDocuments	CONST "23"
$FOLDERID_PublicDownloads	CONST "24"
$FOLDERID_PublicPictures	CONST "25"
$FOLDERID_PublicMusic		CONST "26"
$FOLDERID_PublicVideos		CONST "27"
.
. SignalChild Method *Options Values
. 
$SIGNALCHILD_SENDSIGNAL  EQU 0   ;Set the signal for child task	  9.8
$SIGNALCHILD_CLEARSIGNAL EQU 1   ;Clear the signal for child task        9.8
$SIGNALCHILD_AVAILABLE   EQU 2   ;Return child task availability         9.8
.
. HttpResponse Method *Options Values
.
$HttpResp_NoAccessControl	EQU 1 ;Prevent the output of the default Access-Control headers
$HttpResp_AllowCacheControl	EQU 2 ;Prevent the output of the default Cache-Control header
.
. HttpRequest Results
.
$HttpReq_Started		EQU 0 ;New FastCGI request started
$HttpReq_Shutdown		EQU 1 ;PWS is shutting down - terminate program
$HttpReq_Timeout                EQU 2 ;No FastCGI request came in before *TIMEOUT
$HttpReq_InProgress             EQU 3 ;FastCGI request is still in progress
$HttpReq_NotActive              EQU 4 ;FastCGI mode is not active
.$HttpReq_Error_XX		EQU 5+ ;FastCGI error
.
. IntParse Method *FORMAT Values
.
.$IntParse_DecimalOrHexadecimal	EQU 0 ;Parse input as decimal or hexadecimal
.$IntParse_Hexadecimal	        EQU 1 ;Parse input as hexadecimal ONLY
.
. IntToString Method *FORMAT Values
.
.$IntToString_DecimalOutput	EQU 0 ;Generate decimal string output
.$IntToString_Hexadecimal	EQU 1 ;Generate hexadecimal string output
.
. JqmOptions Method *Options Values
.
$JQMOPT_AUTO_ENHANCE		EQU 1 ;Automatically enhance basic controls
$JQMOPT_FIXED_HDRFTR		EQU 2 ;Fix header and footer to top and bottom of window
$JQMOPT_KEEP_OPTIONS		EQU 4 ;Keep all options through a CHAIN
$JQMOPT_NO_BGCOLOR	        EQU 8 ;Do not use background color properties
.
. JqmPage Method *Action Values
.
$JQMPAGE_BACK			EQU 1 ;Go back to the last or given position page
$JQMPAGE_COUNT			EQU 2 ;Return the current count of pages
$JQMPAGE_OBJECTID		EQU 3 ;Return the OBJECTID of the current or given position page
$JQMPAGE_WEBID			EQU 4 ;Return the WEBID of the current or given position page
$JQMPAGE_REMOVE			EQU 5 ;Remove the current or given position page from the stack
$JQMPAGE_REMOVEALL		EQU 6 ;Clear the page stack
.
. VerifyUTF Medhod *Flags Values
.
$VERIFYUTF_DEFAULT      EQU 0 ;Verify that input string is valid UTF-8.    10.1B
$VERIFYUTF_LOGICAL_LEN  EQU 1 ;Return evaluated logical length of string.  10.1B
$VERIFYUTF_PHYSICAL_LEN EQU 2 ;Return evaluated physical length of string. 10.1B
.
. SetWebTheme Method *Options Values
.
$BS5_OPTION_GRADIENT    EQU 1 ;Use JQueryUI '.bg-gradient' class.          10.6
$BS5_OPTION_PROGRESS    EQU 2 ;Spply Bootstrap 5 style to PROGRESS bar.    10.6
.
*------------------------------------------------------------------------------
.
.   SHAPE                                                                
.
. Events:
.
.   $CLICK        EQU    4
.   $DBLCLICK     EQU    6
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   BACKSTYLE=dnumnvar                       CREATE  SETPROP  GETPROP
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BDRPATTERN=dnumnvar                      CREATE  SETPROP  GETPROP
.   BDRWIDTH=dnumnvar                        CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   DRAWMODE=dnumnvar                        CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FILLCOLOR=dnumnvar|color object          CREATE  SETPROP  GETPROP
.   FILLSTYLE=dnumnvar                       CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SHAPE=dnumnvar                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
*------------------------------------------------------------------------------
.   SLIDER                                                                
.
. Events:
.
.   $CHANGE       EQU    3   
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   MAX=dnumnvar                             CREATE  SETPROP  GETPROP
.   MIN=dnumnvar                             CREATE  SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   ORIENTATION=dnumnvar                     CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SELLENGTH=dnumnvar                       CREATE  SETPROP  GETPROP
.   SELRANGE=dnumnvar                        CREATE  SETPROP  GETPROP
.   SELSTART=dnumnvar                        CREATE  SETPROP  GETPROP
.   SHIFT=dnumnvar                           CREATE  SETPROP  GETPROP
.   TICKFREQ=dnumnvar                        CREATE  SETPROP  GETPROP
.   TICKSTYLE=dnumnvar                       CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
*------------------------------------------------------------------------------
.   SPLITTER                                                                
.
. Events:
.
.   $MOVE         EQU    12
.
. Properties:
.
.   BDRSTYLE=dnumnvar                        CREATE  SETPROP GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   MINEXTRA=dnumnvar                        CREATE  SETPROP  GETPROP
.   MINSIZE=dnumnvar                         CREATE  SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  10.1A
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  10.1A
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  10.1A
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  10.1A
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  10.1A
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  10.1A
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   None
.
*------------------------------------------------------------------------------
.
.   STATTEXT                                                                
.
. Events:
.
.   $CLICK        EQU    4
.   $DBLCLICK     EQU    6
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   ALIGNMENT=dnumnvar                       CREATE  SETPROP  GETPROP
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   BACKSTYLE=dnumnvar                       CREATE  SETPROP  GETPROP
.   BDRCOLOR=dnumnvar|color object           CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   CENTER=dnumnvar                          CREATE  
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RIGHT=dnumnvar                           CREATE  
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   TEXT=svarslit                            CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USEALTKEY=dnumnvar                       CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
*------------------------------------------------------------------------------
.   STATUSBAR
.
. Events:
.
.   $CLICK        EQU    4
.   $DBLCLICK     EQU    6
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SHOWPANEL=dnumnvar                       CREATE  SETPROP  GETPROP
.   SIZEGRIP=dnumnvar                        CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TEXT=svarslit                            CREATE  SETPROP  GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  10.1A
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  10.1A
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  10.1A
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  10.1A
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  10.1A
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  10.1A
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddPanel       [GIVING {nvar}] USING [*Width=]{dnumnvar}:
.                                        [*AutoSize=]{dnumnvar}:   Optional
.                                        [*BdrStyle=]{dnumnvar}:   Optional
.                                        [*MinWidth=]{dnumnvar}:   Optional
.                                        [*Text=]{svarslit}:       Optional
.                                        [*RunName=]{svarslit}:    Optional
.                                        [*ToolTip=]{svarslit}     Optional
.
.   GetPanel             GIVING {statuspanel}] USING [*Key=]{nvarsvarslit}
.
.   RemovePanel          GIVING {nvar} USING [*Key=]{nvarsvarslit}
.
. Collection Support:
.
.   Panels
.
. Method Constants:
.
*------------------------------------------------------------------------------
.   STATUSPANEL
.
. Events:
.
.   None
.
. Properties:
.
.   AUTOSIZE=dnumnvar                          SETPROP  GETPROP
.   BDRSTYLE=dnumnvar                          SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object              SETPROP  GETPROP
.   MINWIDTH=dnumnvar                          SETPROP  GETPROP
.   RUNNAME=svarslit                           SETPROP  GETPROP
.   TEXT=svarslit                              SETPROP  GETPROP
.   TOOLTIP=svarslit                           SETPROP  GETPROP
.   USERDATA=svarslit                          SETPROP  GETPROP     9.4B
.   WIDTH=dnumnvar                             SETPROP  GETPROP
.
. Methods:
.
.   None
.
*------------------------------------------------------------------------------
.   SUBMENU                                                               9.0
.
. Events:
.
.   $CLICK        EQU    4
.   $ITEMCLICK    EQU    26
.
. Properties:
.
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                           SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.
. Methods:
.
.   AddItem              GIVING {nvar} USING *CHECKED={dnumnvar}:     Optional
.                                            *DEFAULT={dnumnvar}:     Optional
.                                            *ENABLED={dnumnvar}:     Optional
.                                            *ITEMPOS={dnumnvar}:     Optional
.                                            *SEPARATOR={dnumnvar}:   Optional
.                                            *SHORTCUT={dnumnvar}:    Optional
.                                            *SPCMENU={dnumnvar}:     Optional
.                                            *SUBMENU={submenu obj}:  Optional
.                                            *TAG={dnumnvar}:         Optional
.                                            *TEXT={svarslit}:        Optional
.                                            *RUNNAME={svarslit}:     Optional
.                                            *HELPID={dnumnvar}:      Optional
.                                            *HELPTOPIC={svarslit}:   Optional
.                                            *USERDATA={svarslit}     Optional
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   GetItem              GIVING {menuitem object} USING *KEY={svarslit}
.   GetItemCount         GIVING {nvar} USING *KEY={nvar | svarslit}       9.0F
.   GetItemState         GIVING {nvar} USING *KEY={nvar | svarslit}       9.0F
.   GetItemType          GIVING {nar} USING *KEY={nvar | svarslit}        9.0F
.   GetItemName          GIVING {svar} USING *KEY={nvar | svarslit}       9.0F
.   RemoveItem           GIVING {nvar} USING *KEY={svarslit}
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
.MFT_END                 Integer 4,"0xFFFFFFFF"   ;GetItemType {nvar} returned
.MFT_STRING              Integer 4,"0x00000000"
.MFT_BITMAP              Integer 4,"0x00000004"
.MFT_MENUBARBREAK        Integer 4,"0x00000020"
.MFT_MENUBREAK           Integer 4,"0x00000040"
.MFT_SEPARATOR           Integer 4,"0x00000800"
.MFT_RIGHTORDER          Integer 4,"0x00002000"
.
.MFS_END                 Integer 4,"0xFFFFFFFF"   ;GetItemState {nvar} returned
.MFS_CHECKED             Integer 4,"0x00000008"
.MFS_DEFAULT             Integer 4,"0x00001000"
.MFS_DISABLED            Integer 4,"0x00000003"
.MFS_GRAYED              Integer 4,"0x00000003"
.MFS_ENABLED             Integer 4,"0x00000000"
.MFS_HILITE              Integer 4,"0x00000080"
.
*------------------------------------------------------------------------------
.   TABCONTROL
.
. Events:
.
.   $CHANGE       EQU    3
.   $CLICK        EQU    4
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar (Objects not MENUITEM)  CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   MULTIROW=dnumnvar                        CREATE  SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   TABFIXHTH=dnumnvar                       CREATE  SETPROP  GETPROP
.   TABFIXWTH=dnumnvar                       CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TABLABEL=svarslit                        CREATE  SETPROP  GETPROP
.   TABSTYLE=dnumnvar                        CREATE  SETPROP  GETPROP
.   TABWTHSTYLE=dnumnvar                     CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.7
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   DeleteTab            GIVING {nvar} USING *Index={dnumnvar}            9.4C
.   GetStyle             GIVING {nvar}                                    9.4C
.   GetTabCount          GIVING {nvar}                                    9.4C
.   GetTabImage          GIVING {nvar} USING *Index={dnumnvar}            9.4C
.   GetTabParam          GIVING {nvar}
.   HitTest              GIVING {nvar} USING *X={dnumnvar}:
.                                            *Y={dnumnvar}
.   InsertTab            GIVING {nvar} USING *Index={dnumnvar}:           9.4C
.                                            *Label={svarslit}: Optional
.                                            *Image={dnumnvar}: Optional
.                                            *Param={dnumnvar}  Optional
.   RemoveImageList      GIVING {nvar}                                    9.4C
.   SetImageList         GIVING {nvar} USING *ImageList={imagelist}       9.4C
.   SetStyle             GIVING {nvar} USING *Style={dnumnvar}:           9.4C
.                                            *Mode={dnumnvar}
.   SetTab               GIVING {nvar} USING *Index={dnumnvar}:           9.4C
.                                            *Label={svarslit}: Optional
.                                            *Image={svarslit}  Optional
.   SetTabImage          GIVING {nvar} USING *Index={dnumnvar}:           9.4C
.                                            *Image={dnumnvar}
.   SetTabParam          GIVING {nvar} USING *Index={dnumnvar}:           9.4C
.                                            *Param={dnumnvar}
.   SetUpTabs            GIVING {nvar} USING *Labels={svarslit}:          10.3A
.                                            *Options={dnumnvar} Optional
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Collection Support:
.
.   None
.
. Method Constants:
.
. SetStyle *Style=values
.
$TCS_FLATBUTTONS    Integer 4,"0x00000008"
$TCS_FORCEICONLEFT  Integer 4,"0x00000010"
$TCS_FORCELABELLEFT Integer 4,"0x00000020"
$TCS_HOTTRACK       Integer 4,"0x00000040"
$TCS_BUTTONS        Integer 4,"0x00000100"
$TCS_MULTILINE      Integer 4,"0x00000200"
$TCS_FIXEDWIDTH     Integer 4,"0x00000400"
$TCS_RAGGEDRIGHT    Integer 4,"0x00000800"
.
*------------------------------------------------------------------------------
.   TIMER
.
. Events:
.
.   $TIMER	  EQU    18
.
. Properties:
.
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.
. Methods:
.
.   None
.
*------------------------------------------------------------------------------
.   TOOLBAR
.
. Events:
.
.   $CLICK        EQU    4         ;Right button only
.   $DBLCLICK     EQU    6         ;Right button only
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $BUTTONCLICK  EQU    26
.   $ITEMCLICK    EQU    26
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   BACKSTYLE=dnumnvar                       CREATE  SETPROP  GETPROP
.   BDRSTYLE=dnumnvar                        CREATE  SETPROP  GETPROP
.   BTNHEIGHT=dnumnvar                       CREATE  SETPROP  GETPROP
.   BTNWIDTH=dnumnvar                        CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DIVIDER=dnumnvar                         CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DOWNARROW=dnumnvar                       CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   IMAGELIST=imagelist                      CREATE  SETPROP
.   IMAGELISTD=imagelist                     CREATE  SETPROP
.   IMAGELISTH=imagelist                     CREATE  SETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SHOWTIPS=dnumnvar                        CREATE
.   TEXTALIGN=dnumnvar                       CREATE  SETPROP  GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  10.1A
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  10.1A
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  10.1A
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  10.1A
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  10.1A
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  10.1A
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   WRAPPABLE=dnumnvar                       CREATE  SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.  AddButton  GIVING {toolbutton} USING *AutoSize={dnumnvar}:  Optional
.                                 *BtnStyle={dnumnvar}:        Optional
.                                 *Enabled={dnumnvar}:         Optional
.                                 *ImageIndex={dnumnvar}:      Optional
.                                 *PartialPush={dnumnvar}:     Optional
.                                 *Pushed={dnumnvar}:          Optional
.                                 *Tag={dnumnvar}:             Optional
.                                 *Visible={dnumnvar}:         Optional
.                                 *Text={svarslit}:            Optional
.                                 *RunName={svarslit}:         Optional
.                                 *ToolTip={svarslit}:         Optional
.                                 *MenuText={svarslit}         Optional
.   GetButton            GIVING {toolbutton} USING *Key={nvarsvarslit}
.   GetButtonByState     GIVING {toolbutton} USING *Key={nvarsvarslit}:
.			                           *State={dnumnvar}      Optional
.   RemoveButton         GIVING {nvar} USING *Key={nvarsvarslit}
.   ResetImageList       GIVING {nvar}
.   ResetImageListDisabled GIVING {nvar}
.   ResetImageListHot    GIVING {nvar}
.   SetImageList         GIVING {nvar} USING *ImageList={imagelist}
.   SetImageListDisabled GIVING {nvar} USING *ImageList={imagelist}
.   SetImageListHot      GIVING {nvar} USING *ImageList={imagelist}
.   SetTBFlags           GIVING {nvar} USING *Flags={dnumnvar}:
.                                            *Mode={dnumnvar}
.   WriteImageListBmp    GIVING {nvar} USING *FileName={svarlit}:
.                                            *Type={dnumnvar}      Optional
.
. Collection Support:
.
.   Buttons
.
. Method Constants:
.
$TB_STATE_PUSHED   Integer 4,"1"             ;GetButtonByState State      9.1A
$TB_STATE_PARTIAL  Integer 4,"2"                                          9.1A
$TB_STATE_ENABLED  Integer 4,"3"                                          9.1A
$TB_STATE_VISIBLE  Integer 4,"4"                                          9.1A
$TB_STATE_AUTOSIZE Integer 4,"5"                                          9.1A
.
*------------------------------------------------------------------------------
.   TOOLBUTTON
.
. Events:
.
.   None
.
. Properties:
.
.   AUTOSIZE=dnumnvar				     SETPROP  GETPROP
.   BTNSTYLE=dnumnvar                                SETPROP  GETPROP
.   DOWNARROW=dnumnvar                               SETPROP  GETPROP
.   ENABLED=dnumnvar                                 SETPROP  GETPROP
.   IMAGEINDEX=dnumnvar                              SETPROP  GETPROP
.   MENUTEXT=svarslit                                SETPROP  GETPROP
.   PARTIALPUSH=dnumnvar                             SETPROP  GETPROP
.   PUSHED=dnumnvar                                  SETPROP  GETPROP
.   RUNNAME=svarslit                                 SETPROP  GETPROP
.   TAG=dnumnvar                                     SETPROP  GETPROP
.   TEXT=svarslit                                    SETPROP  GETPROP
.   TOOLTIP=svarslit                                 SETPROP  GETPROP
.   USERDATA=svarslit                                SETPROP  GETPROP   
.   VISIBLE=dnumnvar                                 SETPROP  GETPROP   
.
. Methods:
.
.   None
.
*------------------------------------------------------------------------------
.   TREEVIEW
.
. Events:
.
.   $CHANGE       EQU    3                                                8.4E
.   $CLICK        EQU    4
.   $DBLCLICK     EQU    6                                                8.4E
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   AUTOREDRAW=dnumnvar                      CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   BUTTONS=dnumnvar                         CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   CHECKBOX=dnumnvar                        CREATE           GETPROP    ;8.6B
.   CHECKBOX=dnumnvar  ( PWS runtime )       CREATE  SETPROP  GETPROP    ;9.9
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FLOATMENU=dnumnvar                       CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   FULLROW=dnumnvar                         CREATE  SETPROP  GETPROP    ;8.6B
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP     9.4B
.   HIDESEL=dnumnvar                         CREATE  SETPROP  GETPROP
.   HOTTRACK=dnumnvar                        CREATE  SETPROP  GETPROP    ;8.6B
.   HWND=nvar                                                 GETPROP
.   IMAGELIST=imagelist                      CREATE  SETPROP
.   INDENT=dnumnvar                          CREATE  SETPROP  GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   THEME=svarslit                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   TREELNSTYLE=dnumnvar                     CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBOBJECT=dnumnvar                       CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   DeleteAll            GIVING {nvar}
.   DeleteItem           GIVING {nvar} USING *Item={dnumnvar}
.   EnsureVisible        GIVING {nvar} USING *Item={dnumnvar}
.   Expand               GIVING {nvar} USING *Item={dnumnvar}:
.                                            *Code={dnumnvar}
.   GetCount             GIVING {nvar}
.   GetFileCount         GIVING {nvar}                                    10.3A
.   GetFileItem          GIVING {svar} USING *Index={dnumnvar}:           10.3A
.                                            *Flags={dnumnvar}   Optional
.   GetItemCheck         GIVING {nvar} USING *Item={dnumnar}
.   GetItemImage         GIVING {nvar} USING *Item={dnumnvar}
.   GetItemParam         GIVING {nvar} USING *Item={dnumnvar}
.   GetItemSelImage      GIVING {nvar} USING *Item={dnumnvar}
.   GetItemState         GIVING {nvar} USING *Item={dnumnvar}:
.                                            *StateMask={dnumnvar} Optional
.   GetItemText          GIVING {svar} USING *Item={dnumnvar}
.   GetLastDropXY        GIVING {nvar} USING *Flags={dnumnvar}     Optional
.   GetNextItem          GIVING {nvar} USING *Item={dnumnvar}:
.                                            *Code={dnumnvar}
.   GetVisibleCount      GIVING {nvar}
.   GetXmlDataSize       GIVING {nvar} USING *Options={dnumnvar}:   Optional
.                                            *TableName={svarslit}: Optional
.                                            *RowName={svarslit}    Optional
.   InsertItem           GIVING {nvar} USING *Text={svarlit}:
.                                            *Parent={dnumnvar}:
.                                            *After={dnumnvar}:
.                                            *Image={dnumnvar}:    Optional
.                                            *SelImage={dnumnvar}: Optional
.                                            *Param={dnumnvar}     Optional
.   ItemHitTest          GIVING {nvar} USING *Horz={dnumnvar}:
.                                            *Vert={dnumnvar}
.   LoadXmlFile          GIVING {nvar} USING *FileName={svarslit}:        9.0B
.                                            *Options={dnumnvar}   Optional
.   SaveXmlFile          GIVING {nvar} USING *FileName={svarslit}:        9.0B
.                                            *Options={dnumnvar}   Optional
.   SaveXmlToDim         GIVING {svar} USING *Options={dnumnvar}:   Optional
.                                            *TableName={svarslit}: Optional
.                                            *RowName={svarslit}    Optional
.   SelectItem           GIVING {nvar} USING *Item={dnumnvar}:
.                                            *Code={dnumnvar}
.   SetFileOptions       GIVING {nvar} USING *Filter={svarslit}: Optional 10.3A
.                                            *Flags={dnumnvar}   Optional
.   SetItem              GIVING {nvar} USING *Item={dnumnvar}:
.                                            *Text={svarlit}:      Optional
.                                            *Image={dnumnvar} :   Optional
.                                            *SelImage={dnumnvar}: Optional
.                                            *Param={dnumnvar}     Optional
.   SetImageList         GIVING {nvar} USING *ImageList={imagelist}
.   SetItemCheck         GIVING {nvar} USING *Item={dnumnvar}:
.                                            *Value={dnumnvar}
.   SetItemState         GIVING {nvar} USING *Item={dnumnvar}:
.                                            *State={dnumnvar}:
.                                            *StateMask={dnumnar}  Optional
.   SortChildren         GIVING {nvar} USING *Item={dnumnvar}:
.                                            *Recurse={dnumnvar}
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. Method Constants:
.
TVI_ROOT             Integer 4,"0xFFFF0000"  ;DeleteItem Item
                                             ;InsertItem Parent
TVI_FIRST            Integer 4,"0xFFFF0001"  ;InsertItem After
TVI_LAST             Integer 4,"0xFFFF0002"
TVI_SORT             Integer 4,"0xFFFF0003"
 
TVE_COLLAPSE         Integer 4,"0x0001"      ;Expand Code
TVE_EXPAND           Integer 4,"0x0002"
TVE_TOGGLE           Integer 4,"0x0003"
TVE_COLLAPSERESET    Integer 4,"0x8000"
 
TVGN_ROOT            Integer 4,"0x0000"      ;GetNextItem Code
TVGN_NEXT            Integer 4,"0x0001"
TVGN_PREVIOUS        Integer 4,"0x0002"
TVGN_PARENT          Integer 4,"0x0003"
TVGN_CHILD           Integer 4,"0x0004"
TVGN_FIRSTVISIBLE    Integer 4,"0x0005"
TVGN_NEXTVISIBLE     Integer 4,"0x0006"
TVGN_PREVIOUSVISIBLE Integer 4,"0x0007"
TVGN_DROPHILITE      Integer 4,"0x0008"
TVGN_CARET           Integer 4,"0x0009"
 
TVIS_SELECTED        Integer 2,"0x0002"      ;GetItemState & SetItemState
TVIS_CUT             Integer 2,"0x0004"
TVIS_DROPHILITED     Integer 2,"0x0008"
TVIS_BOLD            Integer 2,"0x0010"
TVIS_EXPANDED        Integer 2,"0x0020"
TVIS_EXPANDEDONCE    Integer 2,"0x0040"
TVIS_EXPANDPARTIAL   Integer 2,"0x0080"
TVIS_OVERLAYMASK     Integer 2,"0x0F00"
TVIS_STATEIMAGEMASK  Integer 2,"0xF000"
 
$TV_XMLRD_IGNORE_ATTR Integer 4,"0x001"      ;LoadXmlFile Options         9.0B
$TV_XMLRD_NO_CONV     Integer 4,"0x002"
$TV_XMLRD_ADDLAST     Integer 4,"0x004"                                   9.1C
 
$TV_XMLWR_NOATTR       Integer 4,"0x001"     ;SaveXmlFile Options         9.0B
$TV_XMLWR_USE_DTAG     Integer 4,"0x002"
$TV_XMLWR_OUTPUTALLATTR Integer 4,"0x004"
$TV_XMLWR_ISO8859      Integer 4,"0x008"				  9.2B
$TV_XMLWR_LOWERCASE    Integer 4,"0x010"				  9.3A
$TV_XMLWR_UPPERCASE    Integer 4,"0x020"				  9.3A
$TV_XMLWR_NOLABEL_KEEP Integer 4,"0x040"				 10.5B
.
. GetFileItem *Flags Values
. 
. $GetFileItem_PathFile             EQU 1    ;Path and File returned
. $GetFileItem_FileType             EQU 2    ;File type extension returned
. $GetFileItem_FileSize             EQU 4    ;File size of file selection 
.
. SetFileOptions *Flags Values
. 
. $SetFileOptions_EnableOneDrag     EQU  0   ;Enable one file drag/drop
. $SetFileOptions_EnableMultDrag    EQU  1   ;Enable multiple file drag/drop
. $SetFileOptions_DisableDragDrop   EQU  2   ;Disable drag/drop mode
. $SetFileOptions_FreeAllocDragDrop EQU  3   ;Free allocations for drag/drop operations
.
.Note: A TreeView item number is an Integer 4 or a FORM 10
.
*------------------------------------------------------------------------------
.   VARIANT
.
. Events:
.
.   None
.
. Properties:
.
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VARABSVALUE=svar                                          GETPROP
.   VARPTR=dnumnvar                          CREATE  SETPROP  GETPROP
.   VARTYPE=dnumnvar|variant object          CREATE  SETPROP  GETPROP
.   VARVALUE=varlit|variant object           CREATE  SETPROP  GETPROP
.
. Methods:
.
.   GetAllData           GIVING {svar}
.   GetDim               GIVING {nvar}
.   GetElement           GIVING {variant} USING *Index={dnumnvar}:
.                                               *Index1={dnumnvar}: Optional
.                                               *Index2={dnumnvar}: Optional
.                                               *Index3={dnumnvar}: Optional
.                                               *Index4={dnumnvar}: Optional
.   GetElemCount         GIVING {nvar}    USING *DimPos={dnumnvar}  Optional
.   PutElement           GIVING {nvar}    USING *Value={varant}:
.                                               *Index={dnumnvar}
.                                               *Index1={dnumnvar}: Optional
.                                               *Index2={dnumnvar}: Optional
.                                               *Index3={dnumnvar}: Optional
.                                               *Index4={dnumnvar}: Optional
.   SetElemCount         GIVING {nvar}    USING *Size={dnumnvar}
.
. VARIANT Method Contstants:
.
.   None
.
. NOTE:
.      1. The Index values are zero relative.  The first element in a
.         VARIANT ARRAY has an index value of zero.
.
*------------------------------------------------------------------------------
.   VSCROLLBAR
.
. Events:
.   
.   $CLICK        EQU    4
.   $DRAGDROP     EQU    7
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $MOVE         EQU    12
.   $VALIDATE     EQU    24
.
. Properties:
.
.   ANCHOR=dnumnvar                          CREATE  SETPROP  GETPROP
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   CAUSEVALID=dnumnvar                      CREATE  SETPROP  GETPROP
.   DOCK=dnumnvar                            CREATE  SETPROP  GETPROP
.   DROPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HELPID=dnumnvar                          CREATE  SETPROP  GETPROP
.   HELPTOPIC=svarslit                       CREATE  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   MAX=dnumnvar                             CREATE  SETPROP  GETPROP
.   MIN=dnumnvar                             CREATE  SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SCROLLSIZEMODE=dnumnvar                  CREATE  SETPROP  GETPROP
.   SHIFT=dnumnvar                           CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   TOOLTIP=svarslit                         CREATE  SETPROP  GETPROP
.   TOOLTIPHWND=nvar                                          GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   None
.
*------------------------------------------------------------------------------
.   WINDOW
.
. Events:
.
.   $LOAD         EQU    0
.   $ACTIVATE     EQU    1
.   $DEACTIVATE   EQU    2
.   $CLICK	  EQU    4 // PL/B Web Server ONLY!
.   $CLOSE        EQU    5
.   $DBLCLICK	  EQU    6 // PL/B Web Server ONLY!
.   $DRAGOVER     EQU    8
.   $GOTFOCUS     EQU    9
.   $KEYPRESS     EQU    10
.   $LOSTFOCUS    EQU    11
.   $MOVE         EQU    12
.   $MOUSEDOWN    EQU    13
.   $MOUSEUP      EQU    14
.   $MOUSEMOVE    EQU    15
.   $PAINT        EQU    16
.   $RESIZE       EQU    17
.   $FORMINIT     EQU    20
.   $VALIDATE     EQU    24
.   $SUSPEND      EQU    32
.
. Properties:
.
.   APPEARANCE=dnumnvar                      CREATE  SETPROP  GETPROP
.   AUTOREDRAW=dnumnvar                      CREATE  SETPROP  GETPROP
.   AUTOSCROLL=dnumnvar                      CREATE  SETPROP  GETPROP     8.6C
.   BGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   BORDER[=dnumnvar]                        CREATE  SETPROP  GETPROP
.   BUTTONENTERKEY=dnumnvar                  CREATE  SETPROP  GETPROP
.   CAPTION=dnumnvar                         CREATE  SETPROP  GETPROP
.   CLIPCTRL=dnumnvar                        CREATE  SETPROP  GETPROP
.   DIVISIONID=svarslit (PWS only)           CREATE           GETPROP	  9.7
.   ENABLED=dnumnvar                         CREATE  SETPROP  GETPROP
.   FGCOLOR=dnumnvar|color object            CREATE  SETPROP  GETPROP
.   FLOATMENU=dnumnvar                       CREATE  SETPROP  GETPROP
.   FONT=svarslit|font object                CREATE  SETPROP  GETPROP
.   GRIDALIGN=dnumnvar                       CREATE  SETPROP  GETPROP
.   GRIDSIZEH=dnumnvar                       CREATE  SETPROP  GETPROP
.   GRIDSIZEV=dnumnvar                       CREATE  SETPROP  GETPROP
.   HEIGHT=dnumnvar                                  SETPROP  GETPROP
.   HWND=nvar                                                 GETPROP
.   ICON=dnumnvar|svarslit|icon object       CREATE  SETPROP
.   INTASKBAR=dnumnvar                       CREATE           GETPROP     8.6C
.   LEFT=dnumnvar                                    SETPROP  GETPROP
.   LINKHSCROLL=<hscrollbar>                 CREATE           GETPROP
.   LINKVSCROLL=<vscrollbar>                 CREATE           GETPROP
.   MAXBOX=dnumnvar                          CREATE  SETPROP  GETPROP
.   MDIBORDER=dnumnvar                       CREATE  SETPROP  GETPROP     8.6C
.   MDIHEIGHT=dnumnvar                       CREATE  SETPROP  GETPROP     8.6C
.   MDILEFT=dnumnvar                         CREATE  SETPROP  GETPROP     8.6C
.   MDISCROLL=dnumnvar                       CREATE           GETPROP     8.6C
.   MDITOP=dnumnvar                          CREATE  SETPROP  GETPROP     8.6C
.   MDIWIDTH=dnumnvar                        CREATE  SETPROP  GETPROP     8.6C
.   MINBOX=dnumnvar                          CREATE  SETPROP  GETPROP
.   MINHEIGHT=dnumnvar                       CREATE  SETPROP  GETPROP
.   MINSCROLLH=dnumnvar                      CREATE  SETPROP  GETPROP     8.6C
.   MINSCROLLV=dnumnvar                      CREATE  SETPROP  GETPROP     8.6C
.   MINWIDTH=dnumnvar                        CREATE  SETPROP  GETPROP
.   NEGBORDERS=dnumnvar                      CREATE  SETPROP  GETPROP
.   NEGMENUS=dnumnvar                        CREATE  SETPROP  GETPROP
.   NOMENURESIZE=dnumnvar                    CREATE  SETPROP  GETPROP
.   OBJECTID=dnumnvar                        CREATE  SETPROP  GETPROP
.   PARENTWIN=<WINDOW> object                CREATE  SETPROP
.   PARENTWIN=<nvar>                                          GETPROP
.   RIBDLL=svarslit                          CREATE  SETPROP  GETPROP
.   RIBMODE=dnumnvar                         CREATE  SETPROP  GETPROP
.   RIBNAME=svarslit                         CREATE  SETPROP  GETPROP
.   RIGHTTOLEFT=dnumnvar                     CREATE  SETPROP  GETPROP
.   RUNNAME=svarslit                         CREATE  SETPROP  GETPROP
.   SCROLLBAR[=dnumnvar]                     CREATE  SETPROP  GETPROP
.   SHOWWEBMENU=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.7
.   STYLE=dnumnvar|3DON|3DOFF|3DFLAT|3DOUT   CREATE  SETPROP  GETPROP
.   SYSMENU=dnumnvar                         CREATE  SETPROP  GETPROP
.   TABID=dnumnvar                           CREATE  SETPROP  GETPROP
.   THEME=svarslit                           CREATE  SETPROP  GETPROP
.   TITLE=svarslit                           CREATE  SETPROP  GETPROP
.   TOP=dnumnvar                                     SETPROP  GETPROP
.   TOPMOST=dnumnvar                         CREATE  SETPROP  GETPROP
.   UNITS=dnumnvar                           CREATE  SETPROP  GETPROP
.   USECSS=svarslit                          CREATE           GETPROP	  9.7
.   USERDATA=svarslit                        CREATE  SETPROP  GETPROP     9.4B
.   VISIBLE=dnumnvar                         CREATE  SETPROP  GETPROP
.   WEBCLASS=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WEBHEIGHT=svarslit (PWS only)            CREATE  SETPROP  GETPROP	  9.9
.   WEBLEFT=svarslit (PWS only)              CREATE  SETPROP  GETPROP	  9.9
.   WEBMODE=dnumnvar                         CREATE  SETPROP  GETPROP	 10.5
.   WEBPOSITION=dnumnvar (PWS only)          CREATE  SETPROP  GETPROP	  9.9
.   WEBTOP=svarslit (PWS only)               CREATE  SETPROP  GETPROP	  9.9
.   WEBWIDTH=svarslit (PWS only)             CREATE  SETPROP  GETPROP	  9.9
.   WIDTH=dnumnvar                                   SETPROP  GETPROP
.   WINBORDER=dnumnvar                       CREATE  SETPROP  GETPROP     8.6C
.   WINHEIGHT=dnumnvar                               SETPROP  GETPROP
.   WINOFFSETH=dnumnvar                              SETPROP  GETPROP
.   WINOFFSETV=dnumnvar                              SETPROP  GETPROP
.   WINPOS=dnumnvar                          CREATE  SETPROP  GETPROP
.   WINTYPE=dnumnvar                         CREATE           GETPROP
.   WINWIDTH=dnumnvar                                SETPROP  GETPROP
.   ZORDER=dnumnvar                          CREATE  SETPROP  GETPROP
.
. Methods:
.
.   Activate             GIVING {nvar}
.   AddWebClass		 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.   BackGrndMouseMove    GIVING {nvar} USING *Mode={dnumnvar}         Optional
.   BrowseForFolder      GIVING {svar} USING *Instructions={svarslit}:    9.1D
.                                            *Csidlvalue={dnumnvar}: opt  9.1D
.                                            *Bifvalue={dnumnvar}:   opt  9.1D
.                                            *Path={svarslit}        opt  10.3A
.   CheckValidate        GIVING {nvar}
.   Close                GIVING {nvar}
.   Erase                GIVING {nvar}
.   FormToPict           GIVING {pict}
.   GetActiveMdiChild    GIVING {nvar}
.   GetLocaleInfo        GIVING {svar} USING *Type={dnumnvar}:            9.5A
.                                            *Flags={dnumnvar}            9.5A
.   GetMdiChildCount     GIVING {nvar}   
.   GetObjectAsPointer   GIVING {objectptr} USING *Key={dnumnvar|svarslit}:
.                                                 *Flags={dnumnvar}     Optional    
.   IoCancelMode         GIVING {nvar} USING *Value={dnumnvar}
.   IsMinimized          GIVING {nvar}
.   MdiChildNext         GIVING {nvar}                                    9.5A
.   MdiChildPrev         GIVING {nvar}                                    9.5A                      
.   MDILayout            GIVING {nvar} USING *Layout={dnumnvar}
.   MDIShow              GIVING {nvar} USING *Show={dnumnvar}
.   MonitorInfo          GIVING {svar} USING *Flags={dnumnvar}:           9.3A
.                                            *Hwnd={dnumnvar}             9.3A
.   MouseWheelMode       GIVING {nvar} USING *Value={dnumnvar}
.   NotifyIcon           GIVING {nvar} USING *Icon={dnumnvar|svarslit}    9.4B
.                                            *Tooltip={svarslit}          9.4B
.   PrintForm            GIVING {nvar} USING *PrintDC={dnumnvar}:
.                                            *Left={dnumnvar}:
.                                            *Top={dnumnvar}:
.                                            *Width={dnumnvar}:
.                                            *Height={dnumnvar}
.   PrintFormPict        GIVING {nvar} USING *Hwnd={dnumnvar}             9.2B
.   Refresh              GIVING {nvar}
.   ResetScaleOrigin     GIVING {nvar} USING *Flags={dnumnvar}            9.3A
.   RibbonGetProp	 GIVING {nvar|svar} USING *Id={dnumnvar}:	  9.6
.                                                 *PROPERTY={dnumnvar}
.   RibbonSetModes       GIVING {nvar} USING *Mode={dnumnvar}
.   RibbonSetProp        GIVING {nvar} USING *Id={dnumnvar}:              9.6
.                                            *Property={dnumnvar}:
.                                            *Value={dnumnvar|svarslit}
.   RibbonShowContext    GIVING {nvar} USING *Id={dnumnvar}:              9.6
.                                            *Left={dnumnvar}:
.                                            *Top={dnumnvar}
.   Scale                GIVING {nvar} USING *Height={dnumnvar}:          9.3A
.                                            *Width={dnumnvar}:           9.3A
.					     *FontSize={dnumnvar}:        9.3A
.					     *Flags={dnumnvar}            9.3A
.   SetAsClient          GIVING {nvar}                                    10.5
.   SetForegroundWindow  GIVING {nvar}                                    9.4C
.   SetHScrollPos        GIVING {nvar} USING *Position={dnumnvar}	  9.2
.   SetVScrollPos        GIVING {nvar} USING *Position={dnumnvar}	  9.2
.   Show                 GIVING {nvar} USING *Mode={dnumnvar}
.   SetWebStyle          GIVING {nvar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *StrValue={svarslit}:        9.7C
.                                            *Flags={dnumnvar}   OPTIONAL 9.7C
.   GetWebStyle          GIVING {svar} USING *CssName={svarslit}: PWS ONLY9.7C
.                                            *Flags={dnumnvar}   Optional 9.7C
.   GetWebId             GIVING {svar} USING *Flags={dnumnvar}   PWS ONLY 9.7C
.   DisableJqEvent       GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   EnableJqEvent        GIVING {nvar} USING *Events=(svarslit}:   PWS ONLY 9.9A
.                                            *Selector={svarslit}: Optional 9.9A
.                                            *Flags={dnumnvar}     Optional 9.9A
.   RemoveWebClass	 GIVING {nvar} USING *Classes={svarslit}: WEB ONLY 10.6
.                                            *Flags={dnumnvar}    Optional 
.
. WINDOW Method Constants:
.
$ArrangeIcons           EQU     1           ;MDILayout Method
$Cascade                EQU     2
$TileHorizontal         EQU     3
$TileVertical           EQU     4
.
$SW_HIDE                EQU     0           ;Show Method
$SW_SHOWNORMAL          EQU     1
$SW_NORMAL              EQU     1
$SW_SHOWMINIMIZED       EQU     2
$SW_SHOWMAXIMIZED       EQU     3
$SW_MAXIMIZE            EQU     3
$SW_SHOWNOACTIVATE      EQU     4
$SW_SHOW                EQU     5
$SW_MINIMIZE            EQU     6
$SW_SHOWMINNOACTIVE     EQU     7
$SW_SHOWNA              EQU     8
$SW_RESTORE             EQU     9
.
...........
. For BrowseForFolder *Csidlvalue={dnumnvar}
.
CSIDL_DESKTOP                   INTEGER 2,"0x0000"   // <desktop>
CSIDL_INTERNET                  INTEGER 2,"0x0001"   // Internet Explorer (icon
CSIDL_PROGRAMS                  INTEGER 2,"0x0002"   // Start Menu\Programs
CSIDL_CONTROLS                  INTEGER 2,"0x0003"   // My Computer\Control Pan
CSIDL_PRINTERS                  INTEGER 2,"0x0004"   // My Computer\Printers
CSIDL_PERSONAL                  INTEGER 2,"0x0005"   // My Documents
CSIDL_FAVORITES                 INTEGER 2,"0x0006"   // <user name>\Favorites
CSIDL_STARTUP                   INTEGER 2,"0x0007"   // Start Menu\Programs\Sta
CSIDL_RECENT                    INTEGER 2,"0x0008"   // <user name>\Recent
CSIDL_SENDTO                    INTEGER 2,"0x0009"   // <user name>\SendTo
CSIDL_BITBUCKET                 INTEGER 2,"0x000a"   // <desktop>\Recycle Bin
CSIDL_STARTMENU                 INTEGER 2,"0x000b"   // <user name>\Start Menu
CSIDL_MYDOCUMENTS               INTEGER 2,"0x000c"   // logical "My Documents"
CSIDL_MYMUSIC                   INTEGER 2,"0x000d"   // "My Music" folder
CSIDL_MYVIDEO                   INTEGER 2,"0x000e"   // "My Videos" folder
.
CSIDL_DESKTOPDIRECTORY          INTEGER 2,"0x0010"   // <user name>\Desktop
CSIDL_DRIVES                    INTEGER 2,"0x0011"   // My Computer
CSIDL_NETWORK                   INTEGER 2,"0x0012"   // Network Neighborhood
.                                                       (My Network Places)
CSIDL_NETHOOD                   INTEGER 2,"0x0013"   // <user name>\nethood
CSIDL_FONTS                     INTEGER 2,"0x0014"   // windows\fonts
CSIDL_TEMPLATES                 INTEGER 2,"0x0015"
CSIDL_COMMON_STARTMENU          INTEGER 2,"0x0016"   // All Users\Start Menu
CSIDL_COMMON_PROGRAMS           INTEGER 2,"0x0017"   // All Users\Start Menu\Pr
CSIDL_COMMON_STARTUP            INTEGER 2,"0x0018"   // All Users\Startup
CSIDL_COMMON_DESKTOPDIRECTORY   INTEGER 2,"0x0019"   // All Users\Desktop
CSIDL_APPDATA                   INTEGER 2,"0x001a"   // <user name>\Application
CSIDL_PRINTHOOD                 INTEGER 2,"0x001b"   // <user name>\PrintHood
CSIDL_LOCAL_APPDATA             INTEGER 2,"0x001c"   // <user name>\Local
.                                                    Settings\Applicaiton Data
.                                                    (non roaming)
.
CSIDL_ALTSTARTUP                INTEGER 2,"0x001d"   // non localized startup
CSIDL_COMMON_ALTSTARTUP         INTEGER 2,"0x001e"   // non localized common
CSIDL_COMMON_FAVORITES          INTEGER 2,"0x001f"
.
CSIDL_INTERNET_CACHE            INTEGER 2,"0x0020"
CSIDL_COOKIES                   INTEGER 2,"0x0021"
CSIDL_HISTORY                   INTEGER 2,"0x0022"
CSIDL_COMMON_APPDATA            INTEGER 2,"0x0023"   // All Users\Application
CSIDL_WINDOWS                   INTEGER 2,"0x0024"   // GetWindowsDirectory()
CSIDL_SYSTEM                    INTEGER 2,"0x0025"   // GetSystemDirectory()
CSIDL_PROGRAM_FILES             INTEGER 2,"0x0026"   // C:\Program Files
CSIDL_MYPICTURES                INTEGER 2,"0x0027"   // C:\Program Files\My Pic
.
CSIDL_PROFILE                   INTEGER 2,"0x0028"   // USERPROFILE
CSIDL_SYSTEMX86                 INTEGER 2,"0x0029"   // x86 system directory on
CSIDL_PROGRAM_FILESX86          INTEGER 2,"0x002a"   // x86 C:\Program Files on
CSIDL_PROGRAM_FILES_COMMON      INTEGER 2,"0x002b"   // C:\Program Files\Common
CSIDL_PROGRAM_FILES_COMMONX86   INTEGER 2,"0x002c"   // x86 Program Files\Commo
CSIDL_COMMON_TEMPLATES          INTEGER 2,"0x002d"   // All Users\Templates
.
CSIDL_COMMON_DOCUMENTS          INTEGER 2,"0x002e"   // All Users\Documents
CSIDL_COMMON_ADMINTOOLS         INTEGER 2,"0x002f"   // All Users\Start
.                                           Menu\Programs\Administrative Tools
CSIDL_ADMINTOOLS                INTEGER 2,"0x0030"   // <user name>\Start
.                                           Menu\Programs\Administrative Tools
.
CSIDL_CONNECTIONS               INTEGER 2,"0x0031"   // Network and Dial-up
.                                                       Connections
CSIDL_COMMON_MUSIC              INTEGER 2,"0x0035"   // All Users\My Music
CSIDL_COMMON_PICTURES           INTEGER 2,"0x0036"   // All Users\My Pictures
CSIDL_COMMON_VIDEO              INTEGER 2,"0x0037"   // All Users\My Video
CSIDL_RESOURCES                 INTEGER 2,"0x0038"   // Resource Direcotry
.
CSIDL_RESOURCES_LOCALIZED       INTEGER 2,"0x0039"   // Localized Resource
.                                                       Directories
CSIDL_COMMON_OEM_LINKS          INTEGER 2,"0x003a"   // Links to All Users OEM
.                                                       specific apps
CSIDL_CDBURN_AREA               INTEGER 2,"0x003b"   // USERPROFILE\Local
.                                                       Settings\Application
.                                                       Data\Microsoft\CD
.                                                       Burning
.                               INTEGER 2,"0x003c"   // Unused
CSIDL_COMPUTERSNEARME           INTEGER 2,"0x003d"   // Computers Near Me
.                                                       (computered from
.                                                       Workgroup membership)
.
CSIDL_FLAG_CREATE               INTEGER 2,"0x8000"   // combine with CSIDL_
.                                                       value to force folder
.                                                       creation in
.                                                       SHGetFolderPath()
.
CSIDL_FLAG_DONT_VERIFY          INTEGER 2,"0x4000"   // combine with CSIDL_
.                                                       value to return an
.                                                       unverified folder path
CSIDL_FLAG_NO_ALIAS             INTEGER 2,"0x1000"   // combine with CSIDL_
.                                                       value to insure
.                                                       non-alias versions of
.                                                       the pidl
CSIDL_FLAG_PER_USER_INIT        INTEGER 2,"0x0800"   // combine with CSIDL_
.                                                       to indicate per-user
.                                                       init (eg. upgrade)
CSIDL_FLAG_MASK                 INTEGER 2,"0xFF00"   // mask for all possible
.                                                       flag values.
.
...........
. For BrowseForFolder *Bifvalue={dnumnvar}
.
BIF_RETURNONLYFSDIRS   INTEGER 2,"0x0001" // For finding a folder to start
.                                            document searching
.
BIF_DONTGOBELOWDOMAIN  INTEGER 2,"0x0002" // For starting the Find Computer
.
.                                 0x0004  // Not Used
BIF_RETURNFSANCESTORS  INTEGER 2,"0x0008" // BIF_USENEWUI must be set. The
.                                            browse dialog box displays
.                                            shareable resources on remote
.                                            systems. It is intended for
.                                            applications that want to expose
.                                            remote shares on a local system.
.
BIF_EDITBOX            INTEGER 2,"0x0010" // Add an editbox to the dialog
.
BIF_VALIDATE           INTEGER 2,"0x0020" // insist on valid result (or CANCEL)
 
BIF_NEWDIALOGSTYLE     INTEGER 2,"0x0040" // Use the new dialog layout with
.                                            the ability to resize. Caller
.                                            needs to call OleInitialize()
.                                            before using this API
.
BIF_USENEWUI           INTEGER 2,"0x0050" // (BIF_NEWDIALOGSTYLE | BIF_EDITBOX)
.
BIF_BROWSEINCLUDEURLS  INTEGER 2,"0x0080" // Allow URLs to be displayed or
.                                            entered (Requires BIF_USENEWUI)
.
BIF_UAHINT             INTEGER 2,"0x0100" // Add a UA hint to the dialog, in
.                                            place of the edit box. May not be
.                                            combined with BIF_EDITBOX
.
BIF_NONEWFOLDERBUTTON  INTEGER 2,"0x0200" // Do not add the "New Folder" 
.                                            button to the dialog.  Only 
.                                            applicable with 
.                                            BIF_NEWDIALOGSTYLE.
.
BIF_NOTRANSLATETARGETS INTEGER 2,"0x0400" // don't traverse target as shortcut
.
BIF_BROWSEFORCOMPUTER  INTEGER 2,"0x1000" // Browsing for Computers.
.
BIF_BROWSEFORPRINTER   INTEGER 2,"0x2000" // Browsing for Printers
.
BIF_BROWSEINCLUDEFILES INTEGER 2,"0x4000" // Browsing for Everything
.
BIF_SHAREABLE          INTEGER 2,"0x8000" // sharable resources displayed 
.                                            (remote shares, requires 
.                                             BIF_USENEWUI)
.
...........
. For SetHScrollPos *Position={dnumnvar}
.
$SB_LINELEFT	EQU	0	;Scroll left on unit.			  9.2
$SB_LINERIGHT	EQU	1	;Scroll right one unit.			  9.2
$SB_PAGELEFT	EQU	2	;Scroll left one page.			  9.2
$SB_PAGERIGHT	EQU	3	;Scroll right one page.			  9.2
$SB_LEFT	EQU	6	;Scroll to minimum left position.	  9.2
$SB_RIGHT	EQU	7	;Scroll to maximum right position.	  9.2

.
...........
. For SetVScrollPos *Position={dnumnvar}
.
$SB_LINEUP	EQU	0	;Scroll up one line.			  9.2
$SB_LINEDOWN	EQU	1	;Scroll down one line.			  9.2
$SB_PAGEUP	EQU	2	;Scroll up one page.			  9.2
$SB_PAGEDOWN	EQU	3	;Scroll down one page.			  9.2
$SB_TOP		EQU	6	;Scroll to minimum top position.	  9.2
$SB_BOTTOM	EQU	7	;Scroll to maximum bottom position.	  9.2
.
...........
. For MonitorInfo *Flags={dnumnvar}
. Only one of the following flags are allowed!
. 
$MONITOR_DEFAULTTONULL	  INTEGER 4,"0x00000000" ;Return NULL             9.3A
$MONITOR_DEFAULTTOPRIMARY INTEGER 4,"0x00000001" ;Return primary monitor  9.3A
$MONITOR_DEFAULTTONEAREST INTEGER 4,"0x00000002" ;Return nearest monitor  9.3A

...........
. For GetLocaleInfo *Type={dnumnvar}
.
.
. Locale Type Values
.
LOCALE_ILANGUAGE	      INTEGER 4,"0x00000001"   // language id
LOCALE_SLANGUAGE	      INTEGER 4,"0x00000002"   // localized name of language
LOCALE_SENGLANGUAGE	      INTEGER 4,"0x00001001"   // English name of language
LOCALE_SABBREVLANGNAME	      INTEGER 4,"0x00000003"   // abbreviated language name
LOCALE_SNATIVELANGNAME	      INTEGER 4,"0x00000004"   // native name of language
 
LOCALE_ICOUNTRY		      INTEGER 4,"0x00000005"   // country code
LOCALE_SCOUNTRY		      INTEGER 4,"0x00000006"   // localized name of country
LOCALE_SENGCOUNTRY	      INTEGER 4,"0x00001002"   // English name of country
LOCALE_SABBREVCTRYNAME	      INTEGER 4,"0x00000007"   // abbreviated country name
LOCALE_SNATIVECTRYNAME	      INTEGER 4,"0x00000008"   // native name of country
LOCALE_IGEOID		      INTEGER 4,"0x0000005B"   // geographical location	id
 
LOCALE_IDEFAULTLANGUAGE	      INTEGER 4,"0x00000009"   // default language id
LOCALE_IDEFAULTCOUNTRY	      INTEGER 4,"0x0000000A"   // default country code
LOCALE_IDEFAULTCODEPAGE	      INTEGER 4,"0x0000000B"   // default oem code page
LOCALE_IDEFAULTANSICODEPAGE   INTEGER 4,"0x00001004"   // default ansi code page
LOCALE_IDEFAULTMACCODEPAGE    INTEGER 4,"0x00001011"   // default mac code page
 
LOCALE_SLIST		      INTEGER 4,"0x0000000C"   // list item separator
LOCALE_IMEASURE		      INTEGER 4,"0x0000000D"   // 0 = metric, 1	= US
 
LOCALE_SDECIMAL		      INTEGER 4,"0x0000000E"   // decimal separator
LOCALE_STHOUSAND	      INTEGER 4,"0x0000000F"   // thousand separator
LOCALE_SGROUPING	      INTEGER 4,"0x00000010"   // digit	grouping
LOCALE_IDIGITS		      INTEGER 4,"0x00000011"   // number of fractional digits
LOCALE_ILZERO		      INTEGER 4,"0x00000012"   // leading zeros	for decimal
LOCALE_INEGNUMBER	      INTEGER 4,"0x00001010"   // negative number mode
LOCALE_SNATIVEDIGITS	      INTEGER 4,"0x00000013"   // native digits	for 0-9
 
LOCALE_SCURRENCY	      INTEGER 4,"0x00000014"   // local	monetary symbol
LOCALE_SINTLSYMBOL	      INTEGER 4,"0x00000015"   // intl monetary	symbol
LOCALE_SMONDECIMALSEP	      INTEGER 4,"0x00000016"   // monetary decimal separator
LOCALE_SMONTHOUSANDSEP	      INTEGER 4,"0x00000017"   // monetary thousand separator
LOCALE_SMONGROUPING	      INTEGER 4,"0x00000018"   // monetary grouping
LOCALE_ICURRDIGITS	      INTEGER 4,"0x00000019"   // # local monetary digits
LOCALE_IINTLCURRDIGITS	      INTEGER 4,"0x0000001A"   // # intl monetary digits
LOCALE_ICURRENCY	      INTEGER 4,"0x0000001B"   // positive currency mode
LOCALE_INEGCURR		      INTEGER 4,"0x0000001C"   // negative currency mode
 
LOCALE_SDATE		      INTEGER 4,"0x0000001D"   // date separator (derived from LOCALE_SSHORTDATE, use that instead)
LOCALE_STIME		      INTEGER 4,"0x0000001E"   // time separator (derived from LOCALE_STIMEFORMAT, use that instead)
LOCALE_SSHORTDATE	      INTEGER 4,"0x0000001F"   // short	date format string
LOCALE_SLONGDATE	      INTEGER 4,"0x00000020"   // long date format string
LOCALE_STIMEFORMAT	      INTEGER 4,"0x00001003"   // time format string
LOCALE_IDATE		      INTEGER 4,"0x00000021"   // short	date format ordering (derived from LOCALE_SSHORTDATE, use that instead)
LOCALE_ILDATE		      INTEGER 4,"0x00000022"   // long date format ordering (derived from LOCALE_SLONGDATE, use	that instead)
LOCALE_ITIME		      INTEGER 4,"0x00000023"   // time format specifier	(derived from LOCALE_STIMEFORMAT, use that instead)
LOCALE_ITIMEMARKPOSN	      INTEGER 4,"0x00001005"   // time marker position (derived	from LOCALE_STIMEFORMAT, use that instead)
LOCALE_ICENTURY		      INTEGER 4,"0x00000024"   // century format specifier (short date,	LOCALE_SSHORTDATE is preferred)
LOCALE_ITLZERO		      INTEGER 4,"0x00000025"   // leading zeros	in time	field (derived from LOCALE_STIMEFORMAT,	use that instead)
LOCALE_IDAYLZERO	      INTEGER 4,"0x00000026"   // leading zeros	in day field (short date, LOCALE_SSHORTDATE is preferred)
LOCALE_IMONLZERO	      INTEGER 4,"0x00000027"   // leading zeros	in month field (short date, LOCALE_SSHORTDATE is preferred)
LOCALE_S1159		      INTEGER 4,"0x00000028"   // AM designator
LOCALE_S2359		      INTEGER 4,"0x00000029"   // PM designator
 
LOCALE_ICALENDARTYPE	      INTEGER 4,"0x00001009"   // type of calendar specifier
LOCALE_IOPTIONALCALENDAR      INTEGER 4,"0x0000100B"   // additional calendar types specifier
LOCALE_IFIRSTDAYOFWEEK	      INTEGER 4,"0x0000100C"   // first	day of week specifier
LOCALE_IFIRSTWEEKOFYEAR	      INTEGER 4,"0x0000100D"   // first	week of	year specifier
 
LOCALE_SDAYNAME1	      INTEGER 4,"0x0000002A"   // long name for	Monday
LOCALE_SDAYNAME2	      INTEGER 4,"0x0000002B"   // long name for	Tuesday
LOCALE_SDAYNAME3	      INTEGER 4,"0x0000002C"   // long name for	Wednesday
LOCALE_SDAYNAME4	      INTEGER 4,"0x0000002D"   // long name for	Thursday
LOCALE_SDAYNAME5	      INTEGER 4,"0x0000002E"   // long name for	Friday
LOCALE_SDAYNAME6	      INTEGER 4,"0x0000002F"   // long name for	Saturday
LOCALE_SDAYNAME7	      INTEGER 4,"0x00000030"   // long name for	Sunday
LOCALE_SABBREVDAYNAME1	      INTEGER 4,"0x00000031"   // abbreviated name for Monday
LOCALE_SABBREVDAYNAME2	      INTEGER 4,"0x00000032"   // abbreviated name for Tuesday
LOCALE_SABBREVDAYNAME3	      INTEGER 4,"0x00000033"   // abbreviated name for Wednesday
LOCALE_SABBREVDAYNAME4	      INTEGER 4,"0x00000034"   // abbreviated name for Thursday
LOCALE_SABBREVDAYNAME5	      INTEGER 4,"0x00000035"   // abbreviated name for Friday
LOCALE_SABBREVDAYNAME6	      INTEGER 4,"0x00000036"   // abbreviated name for Saturday
LOCALE_SABBREVDAYNAME7	      INTEGER 4,"0x00000037"   // abbreviated name for Sunday
LOCALE_SMONTHNAME1	      INTEGER 4,"0x00000038"   // long name for	January
LOCALE_SMONTHNAME2	      INTEGER 4,"0x00000039"   // long name for	February
LOCALE_SMONTHNAME3	      INTEGER 4,"0x0000003A"   // long name for	March
LOCALE_SMONTHNAME4	      INTEGER 4,"0x0000003B"   // long name for	April
LOCALE_SMONTHNAME5	      INTEGER 4,"0x0000003C"   // long name for	May
LOCALE_SMONTHNAME6	      INTEGER 4,"0x0000003D"   // long name for	June
LOCALE_SMONTHNAME7	      INTEGER 4,"0x0000003E"   // long name for	July
LOCALE_SMONTHNAME8	      INTEGER 4,"0x0000003F"   // long name for	August
LOCALE_SMONTHNAME9	      INTEGER 4,"0x00000040"   // long name for	September
LOCALE_SMONTHNAME10	      INTEGER 4,"0x00000041"   // long name for	October
LOCALE_SMONTHNAME11	      INTEGER 4,"0x00000042"   // long name for	November
LOCALE_SMONTHNAME12	      INTEGER 4,"0x00000043"   // long name for	December
LOCALE_SMONTHNAME13	      INTEGER 4,"0x0000100E"   // long name for	13th month (if exists)
LOCALE_SABBREVMONTHNAME1      INTEGER 4,"0x00000044"   // abbreviated name for January
LOCALE_SABBREVMONTHNAME2      INTEGER 4,"0x00000045"   // abbreviated name for February
LOCALE_SABBREVMONTHNAME3      INTEGER 4,"0x00000046"   // abbreviated name for March
LOCALE_SABBREVMONTHNAME4      INTEGER 4,"0x00000047"   // abbreviated name for April
LOCALE_SABBREVMONTHNAME5      INTEGER 4,"0x00000048"   // abbreviated name for May
LOCALE_SABBREVMONTHNAME6      INTEGER 4,"0x00000049"   // abbreviated name for June
LOCALE_SABBREVMONTHNAME7      INTEGER 4,"0x0000004A"   // abbreviated name for July
LOCALE_SABBREVMONTHNAME8      INTEGER 4,"0x0000004B"   // abbreviated name for August
LOCALE_SABBREVMONTHNAME9      INTEGER 4,"0x0000004C"   // abbreviated name for September
LOCALE_SABBREVMONTHNAME10     INTEGER 4,"0x0000004D"   // abbreviated name for October
LOCALE_SABBREVMONTHNAME11     INTEGER 4,"0x0000004E"   // abbreviated name for November
LOCALE_SABBREVMONTHNAME12     INTEGER 4,"0x0000004F"   // abbreviated name for December
LOCALE_SABBREVMONTHNAME13     INTEGER 4,"0x0000100F"   // abbreviated name for 13th month (if exists)
 
LOCALE_SPOSITIVESIGN	      INTEGER 4,"0x00000050"   // positive sign
LOCALE_SNEGATIVESIGN	      INTEGER 4,"0x00000051"   // negative sign
LOCALE_IPOSSIGNPOSN	      INTEGER 4,"0x00000052"   // positive sign	position (derived from INEGCURR)
LOCALE_INEGSIGNPOSN	      INTEGER 4,"0x00000053"   // negative sign	position (derived from INEGCURR)
LOCALE_IPOSSYMPRECEDES	      INTEGER 4,"0x00000054"   // mon sym precedes pos amt (derived from ICURRENCY)
LOCALE_IPOSSEPBYSPACE	      INTEGER 4,"0x00000055"   // mon sym sep by space from pos	amt (derived from ICURRENCY)
LOCALE_INEGSYMPRECEDES	      INTEGER 4,"0x00000056"   // mon sym precedes neg amt (derived from INEGCURR)
LOCALE_INEGSEPBYSPACE	      INTEGER 4,"0x00000057"   // mon sym sep by space from neg	amt (derived from INEGCURR)
 
.
.#if(WINVER >= 0x0400)
LOCALE_FONTSIGNATURE	      INTEGER 4,"0x00000058"   // font signature
LOCALE_SISO639LANGNAME	      INTEGER 4,"0x00000059"   // ISO abbreviated language name
LOCALE_SISO3166CTRYNAME	      INTEGER 4,"0x0000005A"   // ISO abbreviated country name
.#endif	/* WINVER >= 0x0400 */
 
.#if(WINVER >= 0x0500)
LOCALE_IDEFAULTEBCDICCODEPAGE INTEGER 4,"0x00001012"   // default ebcdic code page
LOCALE_IPAPERSIZE	      INTEGER 4,"0x0000100A"   // 1 = letter, 5	= legal, 8 = a3, 9 = a4
LOCALE_SENGCURRNAME	      INTEGER 4,"0x00001007"   // english name of currency
LOCALE_SNATIVECURRNAME	      INTEGER 4,"0x00001008"   // native name of currency
LOCALE_SYEARMONTH	      INTEGER 4,"0x00001006"   // year month format string
LOCALE_SSORTNAME	      INTEGER 4,"0x00001013"   // sort name
LOCALE_IDIGITSUBSTITUTION     INTEGER 4,"0x00001014"   // 0 = context, 1 = none, 2 = national
 
.#endif	/* WINVER >= 0x0500 */
 
.#if (WINVER >=	0x0600)
LOCALE_SNAME		      INTEGER 4,"0x0000005c"   // locale name (ie: en-us)
LOCALE_SDURATION	      INTEGER 4,"0x0000005d"   // time duration	format
LOCALE_SKEYBOARDSTOINSTALL    INTEGER 4,"0x0000005e"
LOCALE_SSHORTESTDAYNAME1      INTEGER 4,"0x00000060"   // Shortest day name for	Monday
LOCALE_SSHORTESTDAYNAME2      INTEGER 4,"0x00000061"   // Shortest day name for	Tuesday
LOCALE_SSHORTESTDAYNAME3      INTEGER 4,"0x00000062"   // Shortest day name for	Wednesday
LOCALE_SSHORTESTDAYNAME4      INTEGER 4,"0x00000063"   // Shortest day name for	Thursday
LOCALE_SSHORTESTDAYNAME5      INTEGER 4,"0x00000064"   // Shortest day name for	Friday
LOCALE_SSHORTESTDAYNAME6      INTEGER 4,"0x00000065"   // Shortest day name for	Saturday
LOCALE_SSHORTESTDAYNAME7      INTEGER 4,"0x00000066"   // Shortest day name for	Sunday
LOCALE_SISO639LANGNAME2	      INTEGER 4,"0x00000067"   // 3 character ISO abbreviated language name
LOCALE_SISO3166CTRYNAME2      INTEGER 4,"0x00000068"   // 3 character ISO country name
LOCALE_SNAN		      INTEGER 4,"0x00000069"   // Not a	Number
LOCALE_SPOSINFINITY	      INTEGER 4,"0x0000006a"   // + Infinity
LOCALE_SNEGINFINITY	      INTEGER 4,"0x0000006b"   // - Infinity
LOCALE_SSCRIPTS		      INTEGER 4,"0x0000006c"   // Typical scripts in the locale
LOCALE_SPARENT		      INTEGER 4,"0x0000006d"   // Fallback name	for resources
LOCALE_SCONSOLEFALLBACKNAME   INTEGER 4,"0x0000006e"   // Fallback name	for within the console
LOCALE_SLANGDISPLAYNAME	      INTEGER 4,"0x0000006f"   // Lanugage Display Name	for a language
.#endif	//(WINVER >= 0x0600)
.
................
. RibbonSetProp  *Property Values
. 
UI_PKEY_Enabled					EQU  1
UI_PKEY_LabelDescription			EQU  2
UI_PKEY_Keytip					EQU  3
UI_PKEY_Label					EQU  4
UI_PKEY_TooltipDescription			EQU  5
UI_PKEY_TooltipTitle				EQU  6
UI_PKEY_SelectedItem				EQU  104
UI_PKEY_BooleanValue				EQU  200
UI_PKEY_DecimalValue				EQU  201
UI_PKEY_StringValue				EQU  202
UI_PKEY_FontProperties				EQU  300
UI_PKEY_FontProperties_Family			EQU  301 
UI_PKEY_FontProperties_Size			EQU  302 
UI_PKEY_FontProperties_Bold			EQU  303 
UI_PKEY_FontProperties_Italic			EQU  304 
UI_PKEY_FontProperties_Underline		EQU  305 
UI_PKEY_FontProperties_Strikethrough		EQU  306 
UI_PKEY_FontProperties_VerticalPositioning	EQU  307 
UI_PKEY_FontProperties_ForegroundColor		EQU  308 
UI_PKEY_FontProperties_BackgroundColor		EQU  309 
UI_PKEY_FontProperties_ForegroundColorType	EQU  310 
UI_PKEY_FontProperties_BackgroundColorType	EQU  311 
UI_PKEY_RecentItems				EQU  350
UI_PKEY_Color					EQU  400
.
UI_PKEY_ColorType				EQU  401 
.
. Sub values for UI_PKEY_ColorType
.
UI_SWATCHCOLORTYPE_NOCOLOR			EQU  0
UI_SWATCHCOLORTYPE_AUTOMATIC			EQU  1
UI_SWATCHCOLORTYPE_RGB				EQU  2
.
UI_PKEY_ColorMode				EQU  402 
UI_PKEY_ThemeColorsCategoryLabel		EQU  403
UI_PKEY_StandardColorsCategoryLabel		EQU  404
UI_PKEY_RecentColorsCategoryLabel		EQU  405
UI_PKEY_AutomaticColorLabel			EQU  406
UI_PKEY_NoColorLabel				EQU  407
UI_PKEY_MoreColorsLabel				EQU  408
UI_PKEY_Viewable				EQU  1000
UI_PKEY_Minimized				EQU  1001
.
UI_PKEY_QuickAccessToolbarDock			EQU  1002
.
. Subvalues for UI_PKEY_QuickAccessToolbarDock
.
UI_CONTROLDOCK_TOP				EQU  1
UI_CONTROLDOCK_BOTTOM				EQU  3
.
UI_PKEY_GlobalBackgroundColor			EQU  2000
UI_PKEY_GlobalHighlightColor			EQU  2001
UI_PKEY_GlobalTextColor				EQU  2002
.
*------------------------------------------------------------------------------
.   XDATA                                                                 9.8A
.
. Events:
.
.	None
.
. Properties:
.
.	None
.
. Methods:
.
. ChildCount         GIVING {nvar}
. CreateAttribute    GIVING {nvar} USING *POSITION={dnumnvar}:
.                                        *LABEL={svarslit}:
.                                        *TEXT={svarslit}: 
.                                        *JSONTYPE={dnumnvar}:     Optional 
.                                        *OPTIONS={dnumnvar}:      Optional 
. CreateComment      GIVING {nvar} USING *POSITION={dnumnvar}:
.                                        *COMMENT={svarslit}:
.                                        *OPTIONS={dnumnvar}       Optional
. CreateDocType      GIVING {nvar} USING *POSITION={dnumnvar}:
.                                        *NAME={svarslit}:
.                                        *SYSID={svarslit}:        Optional
.                                        *PUBID={svarslit}:        Optional 
.                                        *OPTIONS={dnumnvar}:      Optional 
. CreateElement      GIVING {nvar} USING *POSITION={dnumnvar}:
.                                        *LABEL={svarslit}:
.                                        *TEXT={svarslit}:	   Optional
.                                        *JSONTYPE={dnumnvar}:     Optional 
.                                        *OPTIONS={dnumnvar}       Optional
. CreatePI           GIVING {nvar} USING *POSITION={dnumnvar}:   
.                                        *TARGET={svarslit}: 
.                                        *DATA={svarslit}: 
.                                        *OPTIONS={dnumnvar}       Optional 
. CreateText         GIVING {nvar} USING *POSITION={dnumnvar}:   
.                                        *TEXT={svarslit}: 
.                                        *JSONTYPE={dnumnvar}:     Optional 
.                                        *OPTIONS={dnumnvar}       Optional 
. DeleteNode         GIVING {nvar} USING *POSITION={dnumnvar}      Optional
. FindNode           GIVING {nvar} USING *FILTER={svarslit}:
.                                        *POSITION={dnumnvar}:     Optional
.                                        *OPTIONS={dnumnvar}       Optional 
. FindNext           GIVING {nvar}
. GetComment         GIVING {svar}
. GetData            GIVING {svar}
. GetExtendedError   GIVING {svar} USING *OPTIONS={dnumnvar}       Optional
. GetJsonType        GIVING {nvar}
. GetLabel           GIVING {svar}
. GetName            GIVING {svar}
. GetPubId           GIVING {svar}
. GetPosition        GIVING {nvar}
. GetSysId           GIVING {svar}
. GetTarget          GIVING {svar}
. GetText            GIVING {svar}
. GetType            GIVING {nvar}
. LoadJson           GIVING {nvar} USING *DATA={svarslit}:
.                                        *OPTIONS={dnumnvar}       Optional 
. LoadXml            GIVING {nvar} USING *DATA={svarslit}:
.                                        *OPTIONS={dnumnvar}       Optional
. MoveToNode         GIVING {nvar} USING *POSITION={dnumnvar}
. Reset              GIVING {nvar}
. SaveJson           GIVING {nvar} USING *FILENAME={svarslit}:
.                                        *OPTIONS={dnumnvar}       Optional 
. SaveXml            GIVING {nvar} USING *FILENAME={svarslit}:
.                                        *OPTIONS={dnumnvar}:      Optional  
.                                        *ROOTNAME={svarslit}      Optional
. StoreJson          GIVING {svar} USING *OPTIONS={dnumnvar}       Optional
. StoreJsonSize      GIVING {nvar} USING *OPTIONS={dnumnvar}       Optional  
. StoreXml           GIVING {svar} USING *OPTIONS={dnumnvar}       Optional  
.                                        *ROOTNAME={svarslit}      Optional
. StoreXmlSize       GIVING {nvar} USING *OPTIONS={dnumnvar}:      Optional
.                                        *ROOTNAME={svarslit}      Optional
. UpdateNode         GIVING {nvar} USING *LABEL={svarslit}:        Optional
.                                        *TEXT={svarslit}:         Optional
.                                        *JSONTYPE={dnumnvar}:     Optional 
.                                        *NAME={svarslit}:         Optional
.                                        *SYSID={svarslit}:        Optional
.                                        *PUBID={svarslit}:        Optional 
.                                        *COMMENT={svarslit}:      Optional
.                                        *TARGET={svarslit}:       Optional
.                                        *DATA={svarslit}          Optional
.
. XDATA Method Constants:
.
.....
. Return Error Values
.
XDATA_ERR_NONE			EQU		0
XDATA_ERR_NO_MEM		EQU		1
XDATA_ERR_INVALID_POSITION_TYPE	EQU		2
XDATA_ERR_INVALID_DELETE_NODE	EQU		3	// No node in that position to delete
XDATA_ERR_NODE_NOT_FOUND	EQU		4
XDATA_ERR_INVALID_UPDATE_DATA	EQU		5	// This node type does not have this type of data
XDATA_ERR_NO_CURRENT_POSITION	EQU		6	// No Current position
XDATA_ERR_DOCUMENT_POSITION	EQU		7	// Action not allowed at document position
XDATA_ERR_BAD_FILTER_FIELD	EQU		8
XDATA_ERR_BAD_FILTER		EQU		9
XDATA_ERR_NO_CURRENT_FILTER	EQU		10
XDATA_ERR_INVALID_POSITION	EQU		11
XDATA_ERR_OPEN_FAILED		EQU		12
XDATA_ERR_PARSER_CREATE		EQU		13
XDATA_ERR_PARSE			EQU		14
XDATA_ERR_BAD_READ		EQU		15
XDATA_ERR_FILE_CREATE		EQU		16
XDATA_ERR_FILE_TOO_BIG		EQU		17
XDATA_ERR_BAD_WRITE		EQU		18

XDATA_ERR_XMLSUBERRSTART	EQU		500 // All errors betten 500-600 are XML sub errors
.....
. Node Types
.
DOM_ELEMENT_NODE		EQU		1
DOM_ATTRIBUTE_NODE		EQU		2	
DOM_TEXT_NODE			EQU		3
DOM_CDATA_SECTION_NODE		EQU		4
DOM_ENTITY_REFERENCE_NODE	EQU		5
DOM_ENTITY_NODE			EQU		6
DOM_PROCESSING_INSTRUCTION_NODE EQU		7
DOM_COMMENT_NODE		EQU		8
DOM_DOCUMENT_NODE		EQU		9
DOM_DOCUMENT_TYPE_NODE		EQU		10
DOM_DOCUMENT_FRAGMENT_NODE	EQU		11
DOM_NOTATION_NODE		EQU		12
.....
. JSON TYPES
.
JSON_TYPE_NONE			EQU		0
JSON_TYPE_OBJECT		EQU		1
JSON_TYPE_ARRAY			EQU		2
JSON_TYPE_INTEGER		EQU		3
JSON_TYPE_DOUBLE		EQU		4
JSON_TYPE_STRING		EQU		5
JSON_TYPE_BOOLEAN		EQU		6
JSON_TYPE_NULL			EQU		7
JSON_TYPE_ARRAY_NOLABEL		EQU		258			  10.5
.....
. POSITION Types
.
MOVE_CURRENT_NODE		EQU		0
MOVE_PARENT_NODE		EQU		1
MOVE_FIRST_CHILD		EQU		2
MOVE_LAST_CHILD			EQU		3
MOVE_PREVIOUS_SIBLING		EQU		4
MOVE_NEXT_SIBLING		EQU		5
MOVE_DOCUMENT_NODE		EQU		6
.....
. Create POSITION Types
.
CREATE_AS_CURRENT_NODE		EQU		0
CREATE_AS_PARENT_NODE		EQU		1
CREATE_AS_FIRST_CHILD		EQU		2
CREATE_AS_LAST_CHILD		EQU		3
CREATE_AS_PREVIOUS_SIBLING	EQU		4
CREATE_AS_NEXT_SIBLING		EQU		5
.....
. Delete POSITION Types
.
DELETE_CURRENT_NODE		EQU		0
DELETE_PARENT_NODE		EQU		1
DELETE_FIRST_CHILD		EQU		2
DELETE_LAST_CHILD		EQU		3
DELETE_PREVIOUS_SIBLING		EQU		4
DELETE_NEXT_SIBLING		EQU		5
DELETE_DOCUMENT_NODE		EQU		6
.....
. Find POSITION Types
.
START_CURRENT_NODE		EQU		0
START_PARENT_NODE		EQU		1
START_FIRST_CHILD		EQU		2
START_LAST_CHILD		EQU		3
START_PREVIOUS_SIBLING		EQU		4
START_NEXT_SIBLING		EQU		5
START_DOCUMENT_NODE		EQU		6
.
.....
. CreateXxx Options
.
MOVE_TO_CREATED_NODE		EQU		1
.
.....
. LoadJson Options
.
.
JSON_LOAD_FROM_FILE		EQU		1
JSON_LOAD_READONLY		EQU		2
.
.....
. LoadXml Options
.
XML_LOAD_FROM_FILE		EQU		1
XML_LOAD_READONLY		EQU		2
.
.....
. SaveJson/StoreJson Options
.
JSON_SAVE_USE_INDENT		EQU		2
JSON_SAVE_USE_EOR		EQU		4
.
.....
. SaveXml/StoreXml Options
.
XML_SAVE_NO_DECLARATION		EQU		1
XML_SAVE_USE_INDENT		EQU		2
XML_SAVE_USE_EOR		EQU		4
XML_SAVE_SPC_SUPRESS		EQU		8
XML_SAVE_ESC_ALWAYS		EQU		16
XML_SAVE_CVT_TO_SPACES		EQU		32
XML_SAVE_TAB_INDENT		EQU		64
XML_SAVE_ISO_8859		EQU		128
.....
. GetExtendedError Options
.
XDATA_CLEAR_ERROR		EQU		1
.
*------------------------------------------------------------------------------
         %ENDIF                        ;End $PLBMETH
.
         %XREFON   ;Restore cross reference state flag                    9.1E
.
         LISTON
