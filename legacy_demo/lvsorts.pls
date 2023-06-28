*...........................................................................
.Example Program: LVSORTS.PLS    CALL AS EXTERNAL ROUTINE
.
.This sample program illustrates a method for sorting ListView columns.
.
.
.Copyright @ 1998, Sunbelt Computer Systems, Inc.
.All Rights Reserved.
.
. ISSUE DATE: 10-21-98
.............................................................................
.
#DETAILS        EQU             0  // 1 to show working window, anything else to not
.
#LVIN           LISTVIEW        ^
#CURINDEX       FORM            5
#SORTCOL        FORM            ^
#COLNO          FORM            2
#NCOLS          FORM            ^
#NDX            FORM            3
#ROWCT          FORM            5
#SORTORDR       INTEGER         ^
#SORTSW         INTEGER         1
#COLW           FORM            4
#ITMCT          FORM            4
#WIDE           FORM            5
#HIGH           FORM            5
#MAX            FORM            5
.
#NOTE           DIM             250
#DATA           DIM             255
#CLR            DIM             1
#DV5            FORM            5
.
#FORM1          WINDOW
#WORKLV         LISTVIEW

 		WINSHOW
		KEYIN		*ES,"This program can not be run directly. ",#CLR
		STOP
 
SORTLV          ROUTINE         #LVIN,#SORTCOL,#SORTORDR,#NCOLS
.
. Sorting is accomplished by creating a working Listview object, extracting
. data from #LVIN to it, then clearing data from #LVIN, and reloading it with
. the sorted data. The SORTORDER=1 property of the working object, #WORKLV,
. sets sorting to ASCENDING.
.
. NOTE that since only the first column of a Listview can be sorted, we have
. to rearrange the #LVIN data when we load it into #WORKLV and rearrange it
. again when we put it back.
.
.
. Get number of items
.
         	#LVIN.GetItemCount GIVING #ITMCT
.
. Get listview size
.
                GETPROP         #LVIN,HEIGHT=#HIGH,WIDTH=#WIDE
.
                IFEQ            #DETAILS,1       //Display the working ListView
. 
. Create the work listview for sorting, #WORKLV
.
                CREATE          #FORM1=10:(#HIGH+10):10:(10+#WIDE):
                                BgColor=2147483663:
                                Enabled=1:
                                FgColor=2147483666:
                                ObjectId=0:
                                Title="#FORM1":
                                MinBox=1:
                                MaxBox=1:
                                SysMenu=1:
                                Caption=1:
                                ClipCtrl=0:
                                Appearance=1:
                                WinType=5:
                                AutoRedraw=1:
                                ScrollBar=3:
                                Font="'>MS Sans Serif'(8)":
                                GridAlign=0:
                                GridSizeH=10:
                                GridSizeV=10:
                                Visible=1:    ;set to 1 to see #WORKLV
                                Units=5
 
                CREATE          #FORM1;#WORKLV=0:#HIGH:0:#WIDE:
                                BgColor=16777215:
                                Border=1:
                                DropId=0:
                                Enabled=1:
                                FgColor=2147483666:
                                HelpId=0:
                                ObjectId=0:
                                TabId=10:
                                ZOrder=10:
                                Appearance=1:
                                AutoRedraw=1:
                                Font="'>MS Sans Serif'(8)":
                                HideSel=1:
                                ViewStyle=3:
                                MultiSelect=0:
                                Arrange=3:
                                HideColHdr=0:
                                LabelWrap=0:
                                SortOrder=#SORTORDR:
                                Visible=1:      
                                SortHeader=0
 
                XIF
.
                IFNE            #DETAILS,1      //Don't show working ListView
                CREATE          #WORKLV=10:(10+#HIGH):10:(10+#WIDE):
                                BgColor=16777215:
                                Border=1:
                                DropId=0:
                                Enabled=1:
                                FgColor=2147483666:
                                HelpId=0:
                                ObjectId=0:
                                TabId=10:
                                ZOrder=10:
                                Appearance=1:
                                AutoRedraw=1:
                                Font="'>MS Sans Serif'(8)":
                                HideSel=1:
                                ViewStyle=3:
                                MultiSelect=0:
                                Arrange=3:
                                HideColHdr=0:
                                LabelWrap=0:
                                SortOrder=#SORTORDR:
                                Visible=0:      
                                SortHeader=0
 
                XIF
.
.
. Insert the Columns needed
.
                MOVE            "0",#NDX
                LOOP
                IF              (#NDX = 0)
                MOVE            #SORTCOL,#COLNO
                ELSEIF          (#NDX = #SORTCOL)
                MOVE            "0",#COLNO
                ELSE
                MOVE            #NDX,#COLNO
                ENDIF
 
        	#LVIN.GetColumnWidth GIVING #COLW USING #COLNO
         	#LVIN.GetColumnText GIVING #NOTE USING #COLNO
      	#WORKLV.InsertColumn USING #NOTE,#COLW,#NDX
 
                ADD             "1",#NDX
                REPEAT          UNTIL (#NDX = #NCOLS)
.
. The number of items (lines) in the listview = #ITMCT from above.
.
.
. Extract #LVIN data & insert into #WORKLV in the sequence from NEW #NDX
.
                MOVE            "0",#ROWCT
                LOOP
                MOVE            (#ITMCT-#ROWCT-1),#DV5
 
                #LVIN.GetItemText GIVING #NOTE USING #DV5,#SORTCOL
                #WORKLV.InsertItem GIVING #CURINDEX USING #NOTE
 
                MOVE            "1",#NDX
                LOOP
                IF              (#NDX = #SORTCOL)
                MOVE            "0",#COLNO
                ELSE
                MOVE            #NDX,#COLNO
                ENDIF
 
                #LVIN.GetItemText GIVING #NOTE USING #DV5,#COLNO
                #WORKLV.SetItemText USING #CURINDEX, #NOTE, #NDX
 
                ADD             "1",#NDX
                REPEAT          UNTIL (#NDX = #NCOLS)
                ADD             "1",#ROWCT
                REPEAT          UNTIL (#ROWCT = #ITMCT)
.
.
. Turn off AUTOREDRAW for #LVIN while re-inserting data, turn it on after
. inserting is completed. This makes the sorted data "pop" into the sorted
. order. Not using AUTOREDRAW makes the data "flow" into sorted order. Of
. course, machine speed affects these effects.
.
                SETPROP         #LVIN,AUTOREDRAW=0
.
. Now extract the work data, which is now sorted, and put it back
.
                MOVE            "0",#ROWCT
                LOOP
                MOVE            "0",#NDX
                LOOP
                IF              (#NDX = 0)
                MOVE            #SORTCOL,#COLNO    ;Column 0 in original LV
                ELSEIF          (#NDX = #SORTCOL)
                MOVE            "0",#COLNO      ;This data is in WORKLV column 0
                ELSE
                MOVE            #NDX,#COLNO
                ENDIF
 
                #WORKLV.GetItemText GIVING #NOTE USING #ROWCT,#COLNO
                #LVIN.SetItemText USING #ROWCT, #NOTE, #NDX
 
                ADD             "1",#NDX
                REPEAT          UNTIL (#NDX = #NCOLS)   
                ADD             "1",#ROWCT
                REPEAT          UNTIL (#ROWCT = #ITMCT)
.
.
. Turn AUTOREDRAW back on for #LVIN after re-inserting data
.
                SETPROP         #LVIN,AUTOREDRAW=1
.
                RETURN
....
