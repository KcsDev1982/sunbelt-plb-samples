*---------------------------------------------------------------
.
. Program Name: calc.pls
. Description:  Visual PL/B Programming program
.  
FMENUD          INIT            ")File;E)xit"
FMENU           MENU
HMENUD          INIT            ")Help;)About"
HMENU           MENU
MAIN            PLFORM          CALC.PLF
RESULT          INTEGER         1
.
                WINHIDE
.
                FORMLOAD        MAIN
. 
                CREATE          frmInvest;FMENU,FMENUD
                ACTIVATE        FMENU,FILEMENU,RESULT
. 
                CREATE          frmInvest;HMENU,HMENUD,FMENU
                ACTIVATE        HMENU,HELPMENU,RESULT
.
                LOOP
                EVENTWAIT
                REPEAT
*
.File Menu
.
FILEMENU
                STOP
 
*
.Help Menu
.
HELPMENU
                RETURN
