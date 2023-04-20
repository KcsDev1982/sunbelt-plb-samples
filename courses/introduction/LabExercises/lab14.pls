*---------------------------------------------------------------
.
. Program Name: Lab14.pls
. Description:  Introduction to PL/B Lab 14 program
.           
.
ORIG            DIM             100
NEW             DIM             100
REPLY           DIM             1
*
.Retrieve the original path
.
                PATH            CURRENT,ORIG
                DISPLAY         *HD,"PATH - Originally: ",ORIG
*
.Check for the existance of the Demo folder
.
                PATH            EXIST,"C:\SUNBELT\PLBWIN.105\DEMO\"
                IF              NOT OVER
                DISPLAY         *HD,"PATH - DEMO directory exists."
                ELSE
                DISPLAY         *HD,"PATH - DEMO directory does not exist." 
                ENDIF
*
.Change to the Demo and Code folders
.
                PATH            CHANGE,"C:\SUNBELT\PLBWIN.105\DEMO\"
                PATH            CURRENT,NEW
                DISPLAY         *HD,"PATH - Changed: ",NEW
*
.Restore to the original value 
. 
                PATH            CHANGE,ORIG
                PATH            CURRENT,NEW 
                DISPLAY         *HD,"PATH - Restored: ",NEW 
*
.Retrieve the original searchpath
.
                SEARCHPATH      GET,ORIG
                DISPLAY         *HD,*R,"SEARCHPATH - Originally: ",ORIG
*
.Change to the Demo and Code folders
.
                SEARCHPATH      ADD,"C:\WINDOWS\"
                SEARCHPATH      GET,NEW
                DISPLAY         *HD,"SEARCHPATH - Changed: ",NEW
*
.Restore to the original value 
. 
                SEARCHPATH      SET,ORIG
                SEARCHPATH      GET,NEW 
                DISPLAY         *HD,"SEARCHPATH - Restored: ",NEW
.
                KEYIN           *HD,"Continue...",REPLY
                STOP
