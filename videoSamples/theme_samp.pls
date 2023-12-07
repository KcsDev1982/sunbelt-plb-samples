*---------------------------------------------------------------
.
. Program Name: <name>
. Description:  <description>
.
. Revision History:
.
. <date> <programmer>
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc

                %IFNDEF         $BS5ALERT
$BS5ALERT       EQU             6      //PLB Web Server LABELTEXT ONLY           10.6
$BS5ALERTX      EQU             7      //PLB Web Server LABELTEXT ONLY           10.6
                %ENDIF

*---------------------------------------------------------------
SampleForm      PLFORM          theme_samp.pwf

Images          IMAGELIST
Run             RUNTIME
ThemeNames      INIT            "0 - Default",0x7F:
                                "1 - black tie",0x7F:
                                "2 - blitzer",0x7F:
                                "3 - cupertino",0x7F:
                                "4 - dark hive",0x7F:
                                "5 - dot luv",0x7F:
                                "6 - eggplant",0x7F:
                                "7 - excite bike",0x7F:
                                "8 - flick",0x7F:
                                "9 - hot sneaks",0x7F:
                                "10 - humanity",0x7F:
                                "11 - le frog",0x7F:
                                "12 - mint choc",0x7F:
                                "13 - overcast",0x7F:
                                "14 - pepper grinder",0x7F:
                                "15 - redmond",0x7F:
                                "16 - smoothness",0x7F:
                                "17 - south street",0x7F:
                                "18 - start",0x7F:
                                "19 - sunny",0x7F:
                                "20 - swanky purse",0x7F:
                                "21 - trontastic",0x7F:
                                "22 - ui darkness",0x7F:
                                "23 - ui lightness",0x7F:
                                "24 - vader"
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
. Change to a new theme
.
ChangeTheme     LFUNCTION
                ENTRY
ThemeNum        FORM            3
                EVENTINFO       0,Result=ThemeNum
                Run.SetWebTheme Using *Context=5,*theme=(ThemeNum-1)
                FUNCTIONEND

*................................................................
.
. Perfom a test
.
PressTestButton LFUNCTION
                ENTRY
                SETPROP         Progress1,FGCOLOR=$CONTEXT_PRIMARY,BGCOLOR=$CONTEXT_DARK,Value=75
                SETPROP         LabelText1,BGCOLOR=$CONTEXT_DANGER,FGCOLOR=$CONTEXT_DANGER,appearance=$BS5ALERTX
                LabelText1.RemoveWebClass Using "text-danger"
                LabelText1.AddWebClass Using "opacity-25 text-primary"
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
                WINHIDE

                Run.SetWebTheme Using *options=3
 
                FORMLOAD        SampleForm

                ComboBox1.ResetContent
                ComboBox1.AddString Using ThemeNames
                SETPROP         ComboBox1,*Width=180

                ListView1.InsertItemEx Using *TEXT="Bill",*Subitem1="62 East Street",*Subitem2="Edmonton"
                ListView1.InsertItemEx Using *TEXT="Ed",*Subitem1="22 West Ave",*Subitem2="Halifax"
                ListView1.InsertItemEx Using *TEXT="Kim",*Subitem1="85 North Street",*Subitem2="Orangeville"

                CREATE          WebForm1;Images,ImageSizeH=16,ImageSizeV=16,webobject=1,urlsource="images\plbtools.png"

                TabControl1.SetImageList Using Images
                TabControl1.SetTabImage Using 0, 1
                TabControl1.SetTabImage Using 1, 5
                TabControl1.SetTabImage Using 2, 4

                SETPROP         LabelText1,FGCOLOR=$CONTEXT_PRIMARY,BGCOLOR=$CONTEXT_PRIMARY,appearance=$BS5ALERT
                SETPROP         EditNumber1,BDRCOLOR=$CONTEXT_SUCCESS
                SETPROP         Progress1,BGCOLOR=$CONTEXT_WARNING,Value=20
                FUNCTIONEND
.
.
.
