+==============================================================================
.
. Date:  24 March 2015
.
. Purpose: This sample program demonstrates SetWebStyle method
.
*------------------------------------------------------------------------------
.
                INCLUDE         plbequ.inc
.
Form            PLFORM          "webstylef.pwf"
CssName         DIM             40
StrValue        DIM             40
FullData        DIM             80
Result          FORM            5
nPanel          FORM            3
nLabel          FORM            3
nCount          FORM            3
.
Data            INIT            "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam,":
                                " quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure ":
                                "dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et":
                                " iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Nam liber tempor cum soluta nobis ":
                                "eleifend option congue nihil imperdiet doming id quod mazim placerat facer possim assum. Typi non habent claritatem insitam; est usus legentis in ":
                                "iis qui facit eorum claritatem. Investigationes demonstraverunt lectores legere me lius quod ii legunt saepius."


*------------------------------------------------------------------------------
.
		WINHIDE
                FORMLOAD        Form
                Panel1.innerhtml Using Data
                DELETEITEM      Combobox1, 0
                INSERTITEM      Combobox1, 999, "box-shadow: 10px 10px"
                INSERTITEM      Combobox1, 999, "border: 2px green solid"
                INSERTITEM      Combobox1, 999, "padding: 2px"
                INSERTITEM      Combobox1, 999, "border-radius: 25px"
                INSERTITEM      Combobox1, 999, "padding: 10px"
                INSERTITEM      Combobox1, 999, "background: linear-gradient(180deg, red, blue)"
                INSERTITEM      Combobox1, 999, "background: radial-gradient(red 5%, green 15%, blue 60%)"
                INSERTITEM      Combobox1, 999, "background: white"
                INSERTITEM      Combobox1, 999, "transform: scale(0.5,0.5)"
                INSERTITEM      Combobox1, 999, "transform: skewX(20deg)"
                INSERTITEM      Combobox1, 999, "transform: skewX(-20deg)"
                INSERTITEM      Combobox1, 999, "transform: skewX(0deg)"
                INSERTITEM      Combobox1, 999, "outline: red dotted thick"
                INSERTITEM      Combobox1, 999, "outline: none"
                INSERTITEM      Combobox1, 999, "width: 50%"
                INSERTITEM      Combobox1, 999, "column-count: 3"
                INSERTITEM      Combobox1, 999, "column-rule: 4px outset ##ff00ff"
                INSERTITEM      Combobox1, 999, "text-shadow: 0 0 3px ##FF0000"
                INSERTITEM      Combobox1, 999, "color: white"
                INSERTITEM      Combobox1, 999, "text-shadow: 2px 2px 4px ##000000"
                INSERTITEM      Combobox1, 999, "text-align: center"
.
                Combobox1.GetCount GIVING nCount //Combobox item count!
.
. This is the main program loop
.
                LOOP
                WAITEVENT
                REPEAT
                STOP

PanelSet
                GETPROP         EditText1, *Text=CssName
                GETPROP         EditText2, *Text=StrValue
                Panel1.SetWebStyle Using CssName,StrValue
                RETURN

LabelSet
                GETPROP         EditText1, *Text=CssName
                GETPROP         EditText2, *Text=StrValue
                LabelText3.SetWebStyle Using CssName,StrValue
                RETURN

ComboChange
                EVENTINFO       0,result=Result
                Combobox1.GetText Giving FullData
ComboChange1
                EXPLODE         fulldata using ":" Into CssName, StrValue
                BUMP            StrValue
                SETPROP         EditText1, *Text=CssName
                SETPROP         EditText2, *Text=StrValue
                RETURN
.
NextPanelClick
.
                Combobox1.GetText Giving FullData USING nPanel
                TYPE            FullData
                IF              NOT EOS
                CALL            PanelSet
                ADD             "1", nPanel
                IF              ( nPanel >= nCount )
                CLEAR           nPanel  //Zero based value!
                ENDIF
                Combobox1.SetCurSel USING nPanel
                Combobox1.GetText Giving FullData USING nPanel
                CALL            ComboChange1
                ENDIF
. 
                RETURN
.
NextLabelClick
.
                Combobox1.GetText Giving FullData USING nLabel
                TYPE            FullData
                IF              NOT EOS
                CALL            LabelSet
                ADD             "1", nLabel
                IF              ( nLabel >= nCount )
                CLEAR           nLabel  //Zero based value!
                ENDIF
                Combobox1.SetCurSel USING nLabel
                Combobox1.GetText Giving FullData USING nLabel
                CALL            ComboChange1
                ENDIF
. 
                RETURN
.
Reset
                CHAIN           "mb_webstyle.plc"
.
