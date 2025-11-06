*---------------------------------------------------------------*
.  Example: BUTTON Object Usage in Sunbelt PL/B
.  This example creates a window with an Exit button.
*---------------------------------------------------------------*

Button1         BUTTON
UserAction      FORM       4

*---------------------------------------------------------------*
.  Create a window and add a button control
*---------------------------------------------------------------*
                CREATE      Button1=5:8:5:8,"Exit"

*---------------------------------------------------------------*
.  Activate button and make the window visible
*---------------------------------------------------------------*
                ACTIVATE    Button1,Exit,UserAction


*---------------------------------------------------------------*
.  Wait for user events
*---------------------------------------------------------------*
MainLoop
                LOOP
                WAITEVENT
                REPEAT

*---------------------------------------------------------------*
.  Button click event handler
*---------------------------------------------------------------*
Exit
                STOP
