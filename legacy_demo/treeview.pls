*...........................................................................
.Example Program: TREEVIEW.PLS
.
. This file contains a small sample of using TreeView with an ImageList
. and ListView
.
.  Copyright @ 1998, Sunbelt Computer Systems, Inc.
.  All Rights Reserved.
.............................................................................
 
TEST            PLFORM          TREEVIEW.PLF
 
TVI_ROOT        INTEGER         4,"0xFFFF0000"
TVI_1ST         INTEGER         4,"0xFFFF0001"
TVI_LAST        INTEGER         4,"0xFFFF0002"
TVI_SORT        INTEGER         4,"0xFFFF0003"
 
MyRoot          INTEGER         4
 
Images          IMAGELIST
 
CurIndex        FORM            5
Data1           DIM             10
.
                FORMLOAD        Test
.
. Create and populate the ImageList. Use 16x16 bit icons
.
;..  CREATE    Images,ImageSizeH=32,ImageSizeV=32
                CREATE          Images,ImageSizeH=16,ImageSizeV=16
.
                Images.AddIcon  Using 10130 // Image 0, Icons contained in the default
                Images.AddIcon  Using 10131 // Image 1, resource, PLBWIN.EXE
                Images.AddIcon  Using 10132 // Image 2
.
. Attach the ImageList to the TreeView
.
                TreeView001.SetImageList Using Images
.
. Insert the TreeView items
.
                TreeView001.InsertItem Giving MyRoot Using "Root 1", TVI_ROOT:
                                TVI_1ST, *Image=1
                TreeView001.InsertItem Using  "Level 1", MyRoot, TVI_SORT, *Image=2:
                                *SelImage=0
                TreeView001.InsertItem Using  "Level 2", MyRoot, TVI_SORT, *Image=2:
                                *SelImage=0
                TreeView001.InsertItem Using  "Other 1", MyRoot, TVI_SORT, *Image=2:
                                *SelImage=0
.
. Set the ListView column headings
.
                ListView001.InsertColumn Using "Names", 140, 0
                ListView001.InsertColumn Using "Phone No.", 80, 2
.
. Insert two rows into the ListView
.
                ListView001.InsertItem Giving CurIndex Using "Bill K"
                ListView001.SetItemText Using CurIndex, "495-1232", 1
.
                ListView001.InsertItem Giving CurIndex Using "Ed B"
                ListView001.SetItemText Using CurIndex, "221-6315", 1
. 
                LOOP
                WAITEVENT
                REPEAT
