*---------------------------------------------------------------
.
. Program Name: treeview.pls
. Description:  Visual PL/B Programming program
.  
*
.Define the Objects Required
.
MAIN            PLFORM          treeview.PLF
IL              IMAGELIST
*
.Necessary Values
.
TVI_ROOT        INTEGER         4,"0xFFFF0000"
TVI_LAST        INTEGER         4,"0xFFFF0004"
.
TVGN_CARET      INTEGER         4,"0x0009"
*
.Work Variables
.
ROOT            INTEGER         4
SALES           INTEGER         4
DEV             INTEGER         4
DIST            INTEGER         4
RESULT          FORM            9
NAME            DIM             30

.             
*
.Create and Fill the IMAGELIST Object
.
                CREATE          IL,ImageSizeH=16,ImageSizeV=16
.
                IL.AddIcon      Using 10130
                IL.AddIcon      Using 10131
                IL.AddIcon      Using 10132
*
.Create the TREEVIEW and Associate the Icons
.
		WINHIDE
		FORMLOAD        MAIN
                TV.SetImageList USING IL
*
.Create the Root Level
.
                TV.InsertItem   Giving ROOT using "President":
                                TVI_ROOT,TVI_LAST,*Image=1
*
.Create the First Level Items
.
                TV.InsertItem   GIVING SALES USING "Sales":
                                ROOT,TVI_LAST,*Image=2,*SelImage=0
                TV.InsertItem   GIVING DEV USING "Development":
                                ROOT,TVI_LAST,*Image=2,*SelImage=0
                TV.InsertItem   GIVING DIST USING "Distribution":
                                ROOT,TVI_LAST,*Image=2,*SelImage=0
*  
.Create the Items for Sales
.  
                TV.InsertItem   USING "Ben White",SALES:
                                TVI_LAST,*Image=2,*SelImage=0
                TV.InsertItem   USING "John Williams",SALES:
                                TVI_LAST,*Image=2,*SelImage=0
*
.Create the Items for Development
.
                TV.InsertItem   USING "Don Henson",DEV:
                                TVI_LAST,*Image=2,*SelImage=0
                TV.InsertItem   USING "Frank Wright",DEV:
                                TVI_LAST,*Image=2,*SelImage=0
                TV.InsertItem   USING "Larry Williams",DEV:
                                TVI_LAST,*Image=2,*SelImage=0
                TV.InsertItem   USING "Steve Delaney",DEV:
                                TVI_LAST,*Image=2,*SelImage=0
*
.Create the Items for Distribution
.
                TV.InsertItem   USING "Sam Adams",DIST:
                                TVI_LAST,*Image=2,*SelImage=0
                TV.InsertItem   USING "Beth Miller",DIST:
                                TVI_LAST,*Image=2,*SelImage=0
.
.Show the TREEVIEW object
.
                ACTIVATE        TV,SELECT,RESULT
*
.Wait for an Event to Occur
.
                LOOP
                EVENTWAIT
                REPEAT
*
.An Item was Selected
.
SELECT
                TV.GETITEMTEXT  GIVING NAME USING RESULT
                DISPLAY         *P20:15,*EL,NAME,*W2,*HA 0,*EL;
                RETURN
