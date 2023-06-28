*..........................................................................
.
.Example Program: COLOR.PLS
.
. This sample program is provided to help understand the RGB values which
. can be used for COLOR objects.
.
. Note: The actual colors which a given system displays is a function
. of the video driver and card in use.  The colors displayed 
. depends on wether 16, 256, or more colors are allowed.
.
. Copyright @ 1997, Sunbelt Computer Systems, Inc.
. All Rights Reserved.
*...........................................................................
.
LISTCOL         DATALIST
LISTCOL1        DATALIST
COURIER         FONT
TIMES           FONT
STAT            STATTEXT
STAT1           STATTEXT
STAT2           STATTEXT
COLOR           COLOR
.
COLARR          COLOR           (12)         ;12 element COLOR object array
.
BLACK           COLOR           ^,COLARR(1)        ;COLOR pointers
BLUE            COLOR           ^,COLARR(2)
GREEN           COLOR           ^,COLARR(3)
CYAN            COLOR           ^,COLARR(4)
RED             COLOR           ^,COLARR(5)
MAGENTA         COLOR           ^,COLARR(6)
YELLOW          COLOR           ^,COLARR(7)
WHITE           COLOR           ^,COLARR(8)
GRAY            COLOR           ^,COLARR(9)
DKGRAY          COLOR           ^,COLARR(10)
LTGRAY          COLOR           ^,COLARR(11)
MDGRAY          COLOR           ^,COLARR(12)
.
DEFNAME         DIM             10(12):
                                ("*BLACK"):
                                ("*BLUE"):
                                ("*GREEN"):
                                ("*CYAN"):
                                ("*RED"):
                                ("*MAGENTA"):
                                ("*YELLOW"):
                                ("*WHITE"):
                                ("*GRAY"):
                                ("*DKGRAY"):
                                ("*LTGRAY"):
                                ("*MDGRAY")
.
RGBFILE         FILE            BUFFER=4000
RGBREC          LIST
XRED            DIM             3
DIM1            DIM             1
XGREEN          DIM             3
DIM1A           DIM             1
XBLUE           DIM             3
DIM12           DIM             12
XNAME           DIM             25
                LISTEND
.
FRED            FORM            3
FGREEN          FORM            3
FBLUE           FORM            3
.
NRED            FORM            3
NGREEN          FORM            3
NBLUE           FORM            3
.
CNT             FORM            2
RESULT          FORM            4
SEQ             FORM            "-1"
*.........................................................................
.
. Define the FONT objects used in the program
.
                CREATE          COURIER,"Courier"
                CREATE          TIMES,"Times New Roman"
*
. Create a default set of COLOR objects
. Note that this initialization not only initializes the COLARR elements,
. but also defines the COLOR object pointers declared in the UDA.
.
                CREATE          COLARR(1)=*BLACK
                CREATE          COLARR(2)=*BLUE
                CREATE          COLARR(3)=*GREEN
                CREATE          COLARR(4)=*CYAN
                CREATE          COLARR(5)=*RED
                CREATE          COLARR(6)=*MAGENTA
                CREATE          COLARR(7)=*YELLOW
                CREATE          COLARR(8)=*WHITE
                CREATE          COLARR(9)=*GRAY
                CREATE          COLARR(10)=*DKGRAY
                CREATE          COLARR(11)=*LTGRAY
                CREATE          COLARR(12)=*MDGRAY
.
                CREATE          COLOR=*RED        ;Default for COLOR object
*
. Initialize the program controls and initialize the screen
.
                SETMODE         *LTGRAY=ON:        ;Allow GRAY color substitued for YELLOW
                                *PIXEL=ON        ;Program coordinates are PIXEL units
*
. Since *LTGRAY is on the *YELLOW is substituted as GRAY.  Thus this statement
. paints the screen defined by the screen definition size as GRAY background.
.
                DISPLAY         *BGCOLOR=*YELLOW,*ES;
*
. Create a title STATTEXT field
.
                CREATE          STAT1=10:35:250:375: ;Coordinates are specified as PIXELS
                                "Color Sample Test": ;Title data to be displayed
                                TIMES:  ;Times FONT object used
                                BGCOLOR=WHITE,STYLE=3DON:
                                BORDER  ;Include border

                ACTIVATE        STAT1  	// Activate the STATTEXT without any
                                	// activation routine
*
. Create DATALIST object named 'LISTCOL' to hold RGB data records.
.
                CREATE          LISTCOL=50:200:50:225:
                                BGCOLOR=WHITE,STYLE=3DON:
                                FONT=COURIER:
                                SORTED  ;Define DATALIST as sorted list
*
. Open RGB.TXT data file and load the DATA list with the RGB data
.
. The data stored into the DATALIST is the NAME, RED value, Green value, and
. Blue value.
.
                OPEN            RGBFILE,"rgb.txt",EXCLUSIVE
                LOOP
                READ            RGBFILE,SEQ;RGBREC
                BREAK           IF OVER
                SETLPTR         XNAME
                PACK            S$CMDLIN,XNAME,XRED,XGREEN,XBLUE
                INSERTITEM      LISTCOL,9999,S$CMDLIN
                REPEAT
.
                ACTIVATE        LISTCOL:        ;DATALIST object being activated
                                XLISTCOL:        ;Activation routine for object
                                RESULT        ;Result passed to activation routine
*
. Create second DATALIST object named 'LISTCOL1' to hold default color
. selections.
.
                CREATE          LISTCOL1=203:400:50:225:
                                BGCOLOR=WHITE,STYLE=3DON:
                                FONT=COURIER  ;Courier FONT object used
*
. Load the second DATALIST with the default color selections
.
                MOVE            "1",CNT
                LOOP
                SETLPTR         DEFNAME(CNT)
                INSERTITEM      LISTCOL1,9999,DEFNAME(CNT)
                ADD             "1",CNT
                COMPARE         "13",CNT
                REPEAT          IF LESS
.
                ACTIVATE        LISTCOL1:        ;DATALIST object being activated
                                XLISTCOL1:        ;Activation routine for object
                                RESULT        ;Result passed to activation routine
*
.Wait for an Event to Occur
.
                LOOP
                WAITEVENT
                REPEAT
                STOP
*...........................................................................
.
. This is the activation routine for the DATALIST object named LISTCOL.
. This routines performs the following basic functions:
.
.    1. Retrieves the data record specified in the DATALIST object.
.    2. Breaks the data record out into component variables.
.    3. Creates a COLOR object using the RED, GREEN, and BLUE values
. specified in the data record.
.    4. Retrieve COLOR object RGB values back using GETITEM.
.    5. Creates a STATTEXT object using the COLOR object for the background
. color.
.    6. Activate the STATTEXT object.
.
XLISTCOL
*
. Get the selected item from the DATALIST.  The result passed to this
. activation routine is the number of the data list item selected by
. the user.
.
                GETITEM         LISTCOL,RESULT,S$CMDLIN
*
. Break the data list data out into the components variables.
.
                UNPACK          S$CMDLIN,XNAME,FRED,FGREEN,FBLUE
*
. Create a data variable with the necessary text to be placed into the
. STATTEXT object.  This identifies the RGB component values to the user
. for the specified color.
.
                PACK            S$CMDLIN,"RED:",FRED,"  GREEN:",FGREEN,"  BLUE:",FBLUE
*
. Create the COLOR object with the RGB component values from the DATALIST
. record selected.
.
                CREATE          COLOR=FRED:FGREEN:FBLUE
*
. Having create the COLOR object, now we are showing that the RGB values
. can be retrieve from the COLOR using GETITEM.
.
. When the data field for the GETITEM is a numeric variable, then the
. the RED component is returned for an item number value of one. The
. GREEN component is returned for an item number value of two. The
. BLUE component is returned for an item number value of three.
.
LISTCOL2
                GETITEM         COLOR,1,NRED
                GETITEM         COLOR,2,NGREEN
                GETITEM         COLOR,3,NBLUE
*
. Create the STATTEXT object using the just created COLOR object as the
. background color.
.
                CREATE          STAT=50:75:250:425: ;Use PIXEL coordinates
                                S$CMDLIN:  ;Text for the STATTEXT data
                                "'>MS Sans Serif'": ;Font used for the STATTEXT data
                                BGCOLOR=COLOR: ;Define the background color
                                STYLE=3DON:
                                BORDER  ;Define a border to be used
                ACTIVATE        STAT    // Activate the STATTEXT object 
                                	// without an activation routine.
*
. Create a STATTEXT object using the GETITEM RGB values.
.
                PACK            S$CMDLIN,"GETITEM VALUES:",NRED,"-",NGREEN,"-",NBLUE
                CREATE          STAT2=90:115:250:425: ;Use PIXEL coordinates
                                S$CMDLIN:   ;Text for the STATTEXT data
                                "'>MS Sans Serif'":  ;Font used for the STATTEXT data
                                BGCOLOR=WHITE:
                                STYLE=3DON:
                                BORDER   ;Define a border to be used
                ACTIVATE        STAT2   // Activate the STATTEXT object
                                	// without an activation routine.
                RETURN
*...........................................................................
.
. This is the activation routine for the DATALIST object named 'LISTCOL1'.
. This routine uses an array of color objects to create the default
. color using the DATALIST selection number as the index.
.
XLISTCOL1
*
. Get name of DATALIST selected item
.
                GETITEM         LISTCOL1,RESULT,S$CMDLIN
*
. Change the COLOR object values using GETITEM and SETITEM.
.
                GETITEM         COLARR(RESULT),1,NRED
                GETITEM         COLARR(RESULT),2,NGREEN
                GETITEM         COLARR(RESULT),3,NBLUE
.
                SETITEM         COLOR,1,NRED
                SETITEM         COLOR,2,NGREEN
                SETITEM         COLOR,3,NBLUE
*
. Go output STATTEXT data
.
                GOTO            LISTCOL2
