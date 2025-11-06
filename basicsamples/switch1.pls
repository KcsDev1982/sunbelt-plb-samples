*---------------------------------------------------------*
. Nested SWITCH Example
. Demonstrates hierarchical menu selection
*---------------------------------------------------------*

MAINMENU        FORM        1
SUBOPTION       FORM        1

                DISPLAY *HD,"MAIN MENU",*N:
                        "1. File Options",*N:
                        "2. Print Options",*N:
                        "3. Exit",*W2

                KEYIN "Select Main Option: ", MAINMENU

                SWITCH MAINMENU
                CASE "1"
                    DISPLAY *N,"-- File Menu --",*N:
                            "1. Open",*N:
                            "2. Save",*N:
                            "3. Close",*W2
                    KEYIN "Select File Option: ", SUBOPTION

                    SWITCH SUBOPTION
                    CASE "1"
                        DISPLAY "Opening file..."
                    CASE "2"
                        DISPLAY "Saving file..."
                    CASE "3"
                        DISPLAY "Closing file..."
                    DEFAULT
                        DISPLAY "Invalid File Option"
                    ENDSWITCH

                CASE "2"
                    DISPLAY *N,"-- Print Menu --",*N:
                            "1. Print Setup",*N:
                            "2. Print Preview",*N:
                            "3. Print Document",*W2
                    KEYIN "Select Print Option: ", SUBOPTION

                    SWITCH SUBOPTION
                    CASE "1"
                        DISPLAY "Configuring printer..."
                    CASE "2"
                        DISPLAY "Showing preview..."
                    CASE "3"
                        DISPLAY "Printing document..."
                    DEFAULT
                        DISPLAY "Invalid Print Option"
                    ENDSWITCH

                CASE "3"
                    DISPLAY "Exiting program..."
                    STOP

                DEFAULT
                    DISPLAY "Invalid Main Menu Option"
                ENDSWITCH

                DISPLAY *N,"Program Complete."
                STOP
