*---------------------------------------------------------------
.
. Program Name: jqmsamp
. Description:  JQuery Mobile Sample
.               This program must be run as a .plm mime type
.               Theme css: css/themes/sunbeltapp.min.css
.
. Revision History:
.
. 17-09-28 whk
. Original code
.
               

GLobalInit      FORM            %1
GlobalTheme     DIM             %1
GlobalTrans     DIM             %10

                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 


*---------------------------------------------------------------   

.
Runtime         RUNTIME
Client          CLIENT
.
.
.
mainPageForm    PLFORM          jqmsampfm.pwf 
optPageForm     PLFORM          jqmsampfo.pwf
sampPage1Form   PLFORM          jqmsampf1.pwf
sampPage2Form   PLFORM          jqmsampf2.pwf
sampPage3Form   PLFORM          jqmsampf3.pwf
sampPage4Form   PLFORM          jqmsampf4.pwf
.
headerMain      INIT            "<a data-plbid='stop' class='ui-btn ui-icon-power ui-btn-icon-notext ui-corner-all' href='##'>Stop</a>":
                                "<h1 style='height: 2em'>Sample Pages</h1>":
                                "<a data-plbid='options' class='ui-btn ui-icon-grid ui-btn-icon-notext ui-corner-all' href='##'>Options</a>"

TestPageTable   INIT            "<ul id='pages' data-role='listview' data-inset='true'>":
                                "<li data-role='list-divider'>Sample JQuery Mobile Pages</li>":
                                "<li><a id='page1' href='##'>Regular Controls</a></li>": 
                                "<li><a id='page2' href='##'>Auto Enhanced Controls</a></li>": 
                                "<li><a id='page3' href='##'>Advanced Edit Types</a></li>": 
                                "<li><a id='page4' href='##'>Responsive Grid</a></li>":
                                "<li><a id='page5' href='##'>Collapsible</a ></li>":  
                                "</ul>"  

headerSamp1     INIT            "<a data-plbid='back' class='ui-btn ui-icon-back ui-btn-icon-notext ui-corner-all' href='##'>Back</a>":
                                "<h1 style='height: 2em'>Regular Controls</h1>"

headerSamp2     INIT            "<a data-plbid='back' class='ui-btn ui-icon-back ui-btn-icon-notext ui-corner-all' href='##'>Back</a>":
                                "<h1 style='height: 2em'>Auto Enhanced Controls</h1>"

headerSamp3     INIT            "<a data-plbid='back' class='ui-btn ui-icon-back ui-btn-icon-notext ui-corner-all' href='##'>Back</a>":
                                "<h1 style='height: 2em'>Tests</h1>"

headerSamp4     INIT            "<a data-plbid='back' class='ui-btn ui-icon-back ui-btn-icon-notext ui-corner-all' href='##'>Back</a>":
                                "<h1 style='height: 2em'>Responsive Grid</h1>"

headerOptions   INIT            "<div class='ui-grid-a ui-btn-right'>":
                                "<a data-plbid='reset' class='ui-btn ui-icon-delete ui-btn-icon-notext ui-corner-all' href='##'>Reset</a>":
                                "<a data-plbid='update' class='ui-btn ui-icon-check ui-btn-icon-notext ui-corner-all' href='##'>Update</a>":
                                "</div>":
                                "<h1 style='height: 2em'>Options</h1>":
                                "<a data-plbid='back' class='ui-btn ui-icon-back ui-btn-icon-notext ui-corner-all' href='##'>Back</a>"

optPageHtml     INIT            "<form>":
                                "<div class='ui-field-contain'>":
                                "<label for='selectTrans'>Pick Your Transition:</label>":
                                "<select name='selectTrans' id='selectTrans'>":
                                "<option value='1'>fade</option>":
                                "<option value='2'>pop</option>":
                                "<option value='3'>flip</option>":
                                "<option value='4'>turn</option>":
                                "<option value='5'>flow</option>":
                                "<option value='6'>slidefade</option>":
                                "<option value='7'>slide</option>":
                                "<option value='4'>slideup</option>":
                                "<option value='8'>slidedown</option>":
                                "<option value='9'>none</option>":
                                "</select>":
                                "</div>":
                                "<fieldset data-role='controlgroup' data-type='horizontal'>":
                                "<legend>Pick Your Theme:</legend>":
                                "<input name='radioTheme' id='radioThemea' type='radio' checked='checked' value='a'>":
                                "<label for='radioThemea'>A</label>":
                                "<input name='radioTheme' id='radioThemeb' type='radio' value='b'>":
                                "<label for='radioThemeb'>B</label>":
                                "<input name='radioTheme' id='radioThemec' type='radio' value='c'>":
                                "<label for='radioThemec'>C</label>":
                                "<input name='radioTheme' id='radioThemed' type='radio' value='d'>":
                                "<label for='radioThemed'>D</label>":
                                "<input name='radioTheme' id='radioThemee' type='radio' value='e'>":
                                "<label for='radioThemee'>E</label>":
                                "</fieldset>":
                                "</form>"

optThemeHtml    INIT            "<h3>Theme Shown Below:</h3>":
                                "<ul data-role='listview' data-inset='true' data-theme='?' data-divider-theme='?'>":
                                "<li data-role='list-divider'>Mail</li>":
                                "<li><a href='#'>Inbox</a></li>":
                                "<li><a href='#'>Outbox</a></li>":
                                "</ul>":
                                "<fieldset data-role='controlgroup' data-theme='?' data-type='horizontal' data-role='fieldcontain'>":
                                "<legend>Cache settings:</legend>":
                                "<input type='radio' name='radio-choice-a1' id='radio-choice-a1' value='on' checked='checked' />":
                                "<label for='radio-choice-a1'>On</label>":
                                "<input type='radio' name='radio-choice-a1' id='radio-choice-b1' value='off'  />":
                                "<label for='radio-choice-b1'>Off</label>":
                                "</fieldset>"

sampPage3Html   INIT            "<form>":
                                "<label for='search-1'>Search:</label>":
                                "<input name='search-1' id='search-1' type='search' value=''>":
                                "<label for='date-1'>Date: data-clear-btn='false'</label>":
                                "<input name='date-1' id='date-1' type='date' value='' data-clear-btn='false'>":
                                "<label for='month-1'>Month: data-clear-btn='false'</label>":
                                "<input name='month-1' id='month-1' type='month' value='' data-clear-btn='false'>":
                                "<label for='time-2'>Time: data-clear-btn='true'</label>":
                                "<input name='time-2' id='time-2' type='time' value='' data-clear-btn='true'>":
                                "<label for='tel-1'>Tel: data-clear-btn='false'</label>":
                                "<input name='tel-1' id='tel-1' type='tel' value='' data-clear-btn='false'>":
                                "<label for='email-1'>Email: data-clear-btn='false'</label>":
                                "<input name='email-1' id='email-1' type='email' value='' data-clear-btn='false'>":
                                "<label for='url-1'>Url: data-clear-btn='false'</label>":
                                "<input name='url-1' id='url-1' type='url' value='' data-clear-btn='false'>":
                                "<label for='password-1'>Password: data-clear-btn='false'</label>":
                                "<input name='password-1' id='password-1' type='password' value='' data-clear-btn='false' autocomplete='off'>":
                                "<label for='color-1'>Color: data-clear-btn='false'</label>":
                                "<input name='color-1' id='color-1' type='color' value='' data-clear-btn='false'>":
                                "</form>"

sampPage5Html   INIT            "<div data-role=#"collapsible#">": 
                                "<h3>I'm a single collapsible element</h3>": 
                                "<p>I'm the content inside of the single collapsible element.</p>":
                                "</div>": 
                                "<div data-role=#"collapsible-set#">": 
                                "<div data-role=#"collapsible#" data-collapsed=#"false#">": 
                                "<h3>I'm expanded on page load </h3>": 
                                "<p>I am collapsible content that is visible on page load. </p>": 
                                "<p>That's because of the data-collapsed=#"false#" attribute </p>": 
                                "</div>": 
                                "<div data-role=#"collapsible#">": 
                                "<h3>Expand me I have something to say </h3>": 
                                "<p> I am closed on page load, but still part of an accordion. </p>": 
                                "<div data-role=#"collapsible#">": 
                                "<h3> Wait, are you nested? </h3>":
                                "<p> Yes! You can even nest your collapsible content! </p>": 
                                "</div>":
                                "</div>": 
                                "</div>"
.
footerAll       INIT            "<h4>JQuery Mobile Samples</h4>"
.
. Data for event processing
.
JsonData        DIM             200
EventInfo       XDATA
EventId         DIM             20
JsonOptToDisk   FORM            "6" // JSON_SAVE_USE_INDENT+JSON_SAVE_USE_EOR
.
HtmlData        DIM             4096
NewTheme        INIT            "a"
.
nResult         FORM            2       //ERB
Options1        FORM            "002" // $JQMOPT_FIXED_HDRFTR
Options2        FORM            "003" // $JQMOPT_FIXED_HDRFTR + $JQMOPT_AUTO_ENHANCE
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
. mainEvent - Main page toolbar handler
.
mainEvent       LFUNCTION
                ENTRY
                EventInfo.LoadJson Using JsonData
                CALL            FetchJsonStr USING EventInfo,"id",EventId
                MATCH           "stop" TO EventId
                IF              Equal
                STOP
                ENDIF
                MATCH           "options" TO EventId
                IF              Equal
                ACTIVATE        sampOption
                ENDIF
                FUNCTIONEND
*................................................................
.
. mainPagePanelEvent - Main page panel events
.
mainPagePanelEvent LFUNCTION
                ENTRY
                EventInfo.LoadJson Using JsonData
                CALL            FetchJsonStr USING EventInfo,"id",EventId
                MATCH           "page1" TO EventId
                IF              Equal
                sampPage1.Activate
                ENDIF
                MATCH           "page2" TO EventId
                IF              Equal
                sampPage2.Activate
                ENDIF
                MATCH           "page3" TO EventId
                IF              Equal
                sampPage3Panel1.InnerHtml Using sampPage3Html
                sampPage3.Activate
                ENDIF
                MATCH           "page4" TO EventId
                IF              Equal
                sampPage3Panel1.InnerHtml Using sampPage3Html
                sampPage4.Activate
                ENDIF
                MATCH           "page5" TO EventId
                IF              Equal
                sampPage3Panel1.InnerHtml Using sampPage5Html
                ACTIVATE        sampPage3
                ENDIF
                FUNCTIONEND
*................................................................
.
. optionEvent - Option page toolbar handler
.
optionEvent     LFUNCTION
                ENTRY
                EventInfo.LoadJson Using JsonData
                CALL            FetchJsonStr USING EventInfo,"id",EventId
                MATCH           "back" TO EventId
                IF              Equal
                Runtime.JqmPage Using $JQMPAGE_BACK
                ENDIF
                MATCH           "update" TO EventId
                IF              Equal
                Client.JqGet    Giving GlobalTrans Using "##selectTrans option:selected","text"
                Runtime.JqmOptions Using *Transition=GlobalTrans
                MATCH           NewTheme To GlobalTheme
                IF              Not Equal
                MOVE            NewTheme To GlobalTheme
                CHAIN           "jqmsamp"
                ELSE
                Runtime.JqmPage Using $JQMPAGE_BACK
                ENDIF
                ENDIF
                MATCH           "reset" TO EventId
                IF              Equal
                MOVE            "0" to GlobalInit
                CHAIN           "jqmsamp"
                ENDIF
                FUNCTIONEND
*................................................................
.
. optionPanEvent - Option page panel event handler
.
optionPanEvent  LFUNCTION
                ENTRY
                EventInfo.LoadJson Using JsonData
                EventInfo.SaveJson Using "event.json", JsonOptToDisk
                CALL            FetchJsonStr USING EventInfo,"id",EventId
                MOVE            optThemeHtml to HtmlData
                SWITCH          EventId
                CASE            "radioThemea" 
                MOVE            "a" to NewTheme
                REPLACE         "?a" in HtmlData
                sampOptionPanel2.InnerHtml Using HtmlData
                CASE            "radioThemeb"
                MOVE            "b" to NewTheme
                REPLACE         "?b" in HtmlData
                sampOptionPanel2.InnerHtml Using HtmlData
                CASE            "radioThemec"
                MOVE            "c" to NewTheme
                REPLACE         "?c" in HtmlData
                sampOptionPanel2.InnerHtml Using HtmlData
                CASE            "radioThemed"
                MOVE            "d" to NewTheme
                REPLACE         "?d" in HtmlData
                sampOptionPanel2.InnerHtml Using HtmlData
                CASE            "radioThemee"
                MOVE            "e" to NewTheme
                REPLACE         "?e" in HtmlData
                sampOptionPanel2.InnerHtml Using HtmlData
                ENDSWITCH
                FUNCTIONEND
*................................................................
.
. sampleEvent1 - Smaple event 1
.
sampleEvent1    LFUNCTION
                ENTRY
                EventInfo.LoadJson Using JsonData
                CALL            FetchJsonStr USING EventInfo,"id",EventId
                MATCH           "back" TO EventId
                IF              Equal
                Runtime.JqmPage Using $JQMPAGE_BACK
                ENDIF
                FUNCTIONEND
*................................................................
.
. sampleEvent3 - Smaple event 3
.
sampleEvent3    LFUNCTION
                ENTRY
                EventInfo.LoadJson Using JsonData
                CALL            FetchJsonStr USING EventInfo,"id",EventId
                MATCH           "back" TO EventId
                IF              Equal
                Runtime.JqmPage Using $JQMPAGE_BACK
                ENDIF
                FUNCTIONEND
*................................................................
.
. sampleEvent4 - Smaple event 4
.
sampleEvent4    LFUNCTION
                ENTRY
                EventInfo.LoadJson Using JsonData
                CALL            FetchJsonStr USING EventInfo,"id",EventId
                MATCH           "back" TO EventId
                IF              Equal
                Runtime.JqmPage Using $JQMPAGE_BACK
                ENDIF
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
.
Main            LFUNCTION
                ENTRY
                WINHIDE
               
.
. First load the main form
.
                IF              (GlobalInit = 0 )
                MOVE            "a" to GlobalTheme
                MOVE            "fade" to GlobalTrans
                MOVE            "1" to GlobalInit
                ENDIF
                MATCH           "d" to GlobalTheme
                IF              Equal
                ADD             "8" To Options1 // $JQMOPT_NO_BGCOLOR
                ADD             "8" To Options2 // $JQMOPT_NO_BGCOLOR
                ENDIF
                Runtime.JqmOptions Giving nResult:    //ERB
                                Using headerMain, footerAll, GlobalTrans,*Theme=GlobalTheme,*Options=Options1
                IF              ( nResult == 1 )      //ERB
                ALERT           STOP, "JQuery Mobile mode not being used!", nResult //ERB
                STOP            //ERB
                ENDIF           //ERB
.
                FORMLOAD        mainPageForm
                EVENTREG        mainPage,200,mainEvent,ARG1=JsonData 
.
. Setup a table of test pages on the main page 
.
                mainPagePanel1.InnerHtml Using TestPageTable
                mainPagePanel1.EnableJqEvent Using "click","##pages li a"
                EVENTREG        mainPagePanel1,200,mainPagePanelEvent,ARG1=JsonData 
.
. Load the options page
.
                Runtime.JqmOptions Using headerOptions
                FORMLOAD        optPageForm
                sampOptionPanel1.InnerHtml Using optPageHtml
                sampOptionPanel1.EnableJqEvent Using "click","input"
                sampOptionPanel1.EnableJqEvent Using "change","##selectTrans"
                MOVE            optThemeHtml to HtmlData
                REPLACE         "?a" in HtmlData
                sampOptionPanel2.InnerHtml Using HtmlData
                EVENTREG        sampOption,200,optionEvent,ARG1=JsonData
                EVENTREG        sampOptionPanel1,200,optionPanEvent,ARG1=JsonData
.
. Next load the samples pages
.
                Runtime.JqmOptions Using headerSamp1
                FORMLOAD        sampPage1Form
                EVENTREG        sampPage1,200,sampleEvent1,ARG1=JsonData
.
. Load the auto enhanced controls page
.
                Runtime.JqmOptions Using headerSamp2,*Options=Options2
                FORMLOAD        sampPage2Form
                EVENTREG        sampPage2,200,sampleEvent1,ARG1=JsonData
.
. Load the generic samples page
.
                Runtime.JqmOptions Using headerSamp3,*Options=Options1
                FORMLOAD        sampPage3Form
                EVENTREG        sampPage3,200,sampleEvent3,ARG1=JsonData
.
. Load the ui-block samples page
.
                Runtime.JqmOptions Using headerSamp4,*Options=Options2
                FORMLOAD        sampPage4Form
                EVENTREG        sampPage4,200,sampleEvent4,ARG1=JsonData
.
                FUNCTIONEND
