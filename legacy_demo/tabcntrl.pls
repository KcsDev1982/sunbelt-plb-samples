*------------------------------------------------------------------------------
. Example Program: TABCNTRL.PLS
.
. This example program shows the use of the TAB control.
.
. Copyright 1997 @ Sunbelt Computer Systems, Inc.
. All Rights Reserved
*------------------------------------------------------------------------------
. First Define the Forms.  The forms for the labels are defined as Object Only
. and must preceed the definition of the main form.  This is because the 
. main form references the label forms and the compiler does not allow forward
. references.
.
LAB1            PLFORM          LABEL1
LAB2            PLFORM          LABEL2
LAB3            PLFORM          LABEL3
MAIN            PLFORM          MAIN
*
. Load the Forms.  The forms for the labels are loaded specifying the main
. form's Object Name. LAB1 is visible by default (defined in the form).
. LAB2 is not visible by default
.
                FORMLOAD        MAIN
                FORMLOAD        LAB1,MainForm
                FORMLOAD        LAB2,MainForm
                FORMLOAD        LAB3,MainForm
*
.
. Examine the code for the TabControl001 Object in the MAIN.PLF form using
. the Sunbelt Form Designer.
.
                LOOP
                WAITEVENT
                REPEAT
