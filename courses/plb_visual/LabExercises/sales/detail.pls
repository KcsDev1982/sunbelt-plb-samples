*....................................................
.
.Open the Order Detail File
.
DtlOpen
                TRAP            DtlPrep IF IO
                OPEN            DTLFILE,"DETAIL.ISI"
                TRAPCLR         IO
*
.Build a collection of the input objects
.
                LISTINS         DTLTEXT,dtl_enQuantity:
                                dtl_txtDescription:
                                dtl_enPrice 
*
.Format the ListView
.
                ord_lvDetail.INSERTCOLUMN USING "Item ##",50,0,LVCFMT_CENTER
                ord_lvDetail.INSERTCOLUMN USING "Quantity",60,1,LVCFMT_CENTER
                ord_lvDetail.INSERTCOLUMN USING "Description",165,2,LVCFMT_LEFT
                ord_lvDetail.INSERTCOLUMN USING "Price",60,3,LVCFMT_RIGHT
. 
                RETURN
*....................................................
.
.Create the Order Detail File
.
DtlPrep
                ALERT           TYPE=YESNO,"The Order Detail file "::
                                "does not exist - Create It ?":
                                RESULT,"Warning"
                STOP            IF (RESULT = 7)
. 
                PREPARE         DTLFILE,"DETAIL","DETAIL":
                                "1-20","60"
                RETURN
*....................................................
.
.Retrieve Order Detail records from the ListView
.
DtlGet
                GETITEM         dtl_enQuantity,0,SQTY
                MOVE            SQTY,DTLQTY
                GETITEM         dtl_txtDescription,0,DTLDESC
                GETITEM         dtl_enPrice,0,SPRICE
                MOVE            SPRICE,DTLPRICE
                RETURN
*....................................................
.
.Store Order Detail records into the ListView
.
DtlPut
                MOVE            DTLQTY,SQTY
                SETITEM         dtl_enQuantity,0,SQTY
                SETITEM         dtl_txtDescription,0,DTLDESC
                MOVE            DTLPRICE,SPRICE
                SETITEM         dtl_enPrice,0,SPRICE
                RETURN
*....................................................
.
.Retrieve Order Detail records and store in the ListView
.
DtlListAll
                ord_lvDetail.DeleteAllItems
                MOVE            ORDNUM,DTLKEY
                READ            DTLFILE,DTLKEY;;
.
                LOOP
                READKS          DTLFILE;DTLDATA
                UNTIL           ((DTLORD != ORDNUM) OR OVER)
                MOVE            DTLITEM,DTLKEY
                MOVE            DTLQTY,SQTY
                MOVE            DTLPRICE,SPRICE
                ord_lvDetail.InsertItemEx USING DTLKEY,0:
                                *Param=DTLITEM:
                                *SubItem1=SQTY:
                                *SubItem2=DTLDESC:
                                *SubItem3=SPRICE
                REPEAT
*
.If no records, add a special entry to allow additions
. 
                ord_lvDetail.GetItemCount Giving Result
                IF              ZERO
                ord_lvDetail.InsertItemEx USING "*",0
                ENDIF
. 
                RETURN
*....................................................
.
.Show menu for right click on the detail listview
.
DTLCLICK        ROUTINE         Item
*
.Determine the click position
.
                ord_lvDetail.GetItemRect Giving Msg Using Item,0
                SETLPTR         Msg,8
                RESET           Msg,5
                MOVE            Msg,Top
                ADD             "2",TOP
                SETLPTR         Msg,12
                RESET           MSG,9
                MOVE            MSG,Left
                ADD             "10",Left
                SETPROP         ord_mnuRight,TOP=Top,LEFT=Left
                ACTIVATE        ord_mnuRight
                RETURN
*....................................................
.
.Delete the Detail records for the current order
.
DtlDeleteAll
                MOVE            ORDNUM,DTLKEY
                READ            DTLFILE,DTLKEY;;
.
                LOOP
                READKS          DTLFILE;DTLDATA
                UNTIL           OVER OR (DTLORD != ORDNUM)
                DELETE          DTLFILE
                REPEAT
.
                RETURN
*....................................................
.
.A right menu item has been selected
.
DtlMenu         ROUTINE         Value
                BRANCH          Value to DtlNew,DtlEdit,DtlDelete
                RETURN
*....................................................
.
.Add a Detail record for the current order
.
DtlNew
                SET             Adding
                DELETEITEM      DtlText,0
                SETFOCUS        dtl_enQuantity
                SETPROP         frmDetail,VISIBLE=$True
                RETURN
*....................................................
.
.Save a Detail record for the current order
.
DtlSave
                IF              (Adding)
                CLEAR           RESULT
                ord_lvDetail.GetItemText Giving DTLKEY USING Result
                IF              (DTLKEY = "*")
                ord_lvDetail.DeleteItem USING RESULT
                ENDIF
                MOVE            ORDNUM,DTLORD
                INCR            DTLORD
                MOVE            DTLORD,DTLKEY
                READ            DTLFILE,DTLKEY;;
                READKP          DTLFILE;NWORK10,DTLITEM
                IF              (NWORK10 = DTLORD)
                INCR            DTLITEM
                ELSE
                MOVE            "1",DTLITEM
                ENDIF
                CALL            DtlGet
                MOVE            ORDNUM,DTLORD
                WRITE           DTLFILE;DTLDATA
                MOVE            DTLITEM,DTLKEY
                ord_lvDetail.InsertItemEx USING DTLKEY,Result:
                                *Param=DTLITEM,*SubItem1=SQTY:
                                *SubItem2=DTLDESC,*SubItem3=SPRICE
                CLEAR           Adding
                ELSE
                CALL            DtlGet
                UPDATE          DTLFILE;DTLDATA
                MOVE            DTLQTY,SQTY
                MOVE            DTLPRICE,SPRICE
                ord_lvDetail.SetItemText USING ITEM,SQTY,1
                ord_lvDetail.SetItemText USING ITEM,DTLDESC,2
                ord_lvDetail.SetItemText USING ITEM,SPRICE,3 
                ENDIF
.
                SETPROP         frmDetail,VISIBLE=$False
                RETURN
*....................................................
.
.Edit a Detail record in the current order
.
DtlEdit
                ord_lvDetail.GetItemParam GIVING NWORK10 using ITEM
                RETURN          IF ZERO
.
                PACK            DTLKEY WITH ORDNUM,NWORK10
                READ            DTLFILE,DTLKEY;DTLDATA
                IF              OVER
                ALERT           STOP,"Error locating the detail record":
                                Result,"Error"
                RETURN
                ENDIF
.
                CALL            DtlPut
                SETPROP         dtl_cmdOK,ENABLED=$TRUE
                SETFOCUS        dtl_enQuantity
                SETPROP         frmDetail,VISIBLE=$True
                RETURN
*....................................................
.
.Delete a Detail record for the current order
.
DtlDelete
                ord_lvDetail.GetItemParam GIVING NWORK10 using ITEM
                RETURN          IF ZERO
*
.Delete the record
.
                PACK            DTLKEY WITH ORDNUM,NWORK10
                DELETE          DTLFILE,DTLKEY
                IF              OVER
                ALERT           CAUTION,"Error deleting the detail record.",RESULT
                RETURN
                ENDIF
*
.Delete the Listview Item
.
                ord_lvDetail.DeleteItem USING ITEM
*
.If the ListView is empty, add the placeholder symbol
.
                ord_lvDetail.GetItemCount Giving Result
                IF              ZERO
                ord_lvDetail.InsertItemEx USING "*"
                ENDIF
. 
                RETURN
*....................................................
.
.Enable the OK button when the required files are input
.
DtlVerify
                SETPROP         dtl_cmdOK,ENABLED=$FALSE
                GETITEM         dtl_enQuantity,0,Msg
                MOVE            Msg,RESULT
                RETURN          IF ZERO
                GETITEM         dtl_txtDescription,0,RESULT
                RETURN          IF ZERO
                GETITEM         dtl_enPrice,0,MSG
                MOVE            MSG,FORM72
                RETURN          IF ZERO 
.
                SETPROP         dtl_cmdOK,ENABLED=$TRUE
                RETURN
