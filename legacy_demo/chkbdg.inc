****************************************************************************
. Budget managment
.

bdgdat          IFILE           NODUP,UPPER
bdgtot          FORM            7.2

*
.Budget file is 11 bytes
.

bdgrcrd         LIST
bdgcode         FORM            2
bdgamt          FORM            6.2
                LISTEND

#d10            DIM             ^10
#d20            DIM             ^20
#d40            DIM             ^40
#f4             FORM            4
#mod            FORM            1

StartBdg
                BdgLV.InsertColumn USING "Catagory",120,0
                BdgLV.InsertColumn USING "Amount",100,1,*FORMAT=01
                BdgLV.SetExtendedStyle USING 0x01,0x01

                CLEAR           ftrap
                TRAP            noFile IF IO
                OPEN            bdgdat,budget
                IF              (ftrap)
                PREP            bdgdat,budget,budget,"1-2","11"
                ENDIF
                TRAPCLR         IO
                CALL            LoadBdg
                RETURN

GetBdgDFlts
                LVExpence.GetItemText GIVING #d10 USING 1,2 ;check for avg's
                CHOP            #d10,#d10
                IF              (#d10="")
                CALL            gettotals ;Gettotals calculates avgs for us :o)
                ENDIF
                CLEAR           #f4 ;,total
                LOOP
                LVExpence.GetItemText GIVING #d20 USING #f4,0
                CHOP            #d20,#d20
                PACK            #d40,"01X",#d20
                READ            DcatDesc,#d40;catrcrd
                LVExpence.GetItemText GIVING #d10 USING #f4,2 ;def to avg
                CHOP            #d10,#d10
                MOVE            #d10,bdgamt
                MOVE            catcode,#d10
                MOVE            catcode,bdgcode
                READ            bdgdat,#d10;#d20
                IF              OVER
                MOVE            catcode,bdgcode
                WRITE           bdgdat,#d10;bdgrcrd
                ELSE
                UPDATE          bdgdat;bdgrcrd
                ENDIF
                BREAK           IF (#f4=descCnt)
                INCR            #f4
                REPEAT
                CALL            bdgclear
                RETURN

BdgAdd
                SETPROP         BdgModBtn,ENABLED=0
                GETITEM         Bcode,0,#f4
                GETITEM         bCode,#f4,#d20
                CHOP            #d20,#d20
                PACK            #d40,"01X",#d20
                READ            Dcatdesc,#d40;catrcrd
                BdgLV.FindItem  GIVING #f4 USING 0,catdesc
                RETURN          IF (#f4 >= "0")
                BdgLV.InsertItem GIVING #f4 USING catdesc,9999
                GETITEM         EdtBdgAmt,0,#d10
                CHOP            #d10,#d10
                bdgLV.SetItemText USING #f4,#d10,1
                MOVE            #d10,bdgamt
                MOVE            catcode,bdgcode
                MOVE            bdgcode,#d10
                WRITE           bdgdat,#d10;bdgrcrd
                CALL            bdgclear
                RETURN

BdgRm
                IF              (#mod)
                CALL            bdgModCncl
                RETURN
                ENDIF
 
                BdgLV.GetNextItem GIVING #f4 USING 0x0002
                BdgLV.GetItemText GIVING #d40 USING #f4,0
                CHOP            #d40,#d40
                PACK            #d20,"01X",#d40
                READ            Dcatdesc,#d20;catrcrd
                MOVE            catcode,#d10
                DELETE          bdgdat,#d10
                CALL            bdgclear
                RETURN
 

bdgModS         ROUTINE         pf
                BdgLV.GetItemText GIVING #d40 USING pf,0
                CHOP            #d40,#d40
                PACK            #d20,"01X",#d40
                READ            Dcatdesc,#d20;catrcrd
                CHOP            catdesc,catdesc
                BdgLV.GetItemText GIVING #d10 USING pf,1
                CHOP            #d10,#d10
                SETITEM         EdtBdgAmt,0,#d10
                SET             #f4
                LOOP
                GETITEM         Bcode,#f4,#d20
                CHOP            #d20,#d20
                BREAK           IF (#d20=catdesc)
                INCR            #f4
                REPEAT
                SETITEM         bCode,0,#f4
                SETPROP         BdgModBtn,ENABLED=1
                SETPROP         bdgLV,ENABLED=0
                MOVE            "Cancel",#d10
                SETITEM         bdgRmBtn,0,#d10
                CALL            CatCnl
                SET             #mod
                SETFOCUS        EdtBdgAmt
                SETITEM         EdtBdgAmt,1,0
                SETITEM         EdtBdgAmt,2,999
 
                RETURN

bdgMod
                GETITEM         BCode,0,#f4
                GETITEM         BCode,#f4,#d40
                PACK            #d20,"01X",#d40
                READ            Dcatdesc,#d20;catrcrd
                BdgLV.FindItem  GIVING #f4 USING 0,catdesc
                MOVE            catcode,#d10
                READ            bdgdat,#d10;bdgrcrd
                GETITEM         EdtBdgAmt,0,#d10
                CHOP            #d10,#d10
                MOVE            #d10,bdgamt
                UPDATE          bdgdat;bdgrcrd
                MOVE            "Remove",#d10
                SETITEM         bdgRmBtn,0,#d10
                CALL            bdgclear
                RETURN

bdgclear
                bdgLV.DeleteAllItems
                CALL            LoadBdg
                CLEAR           #d10
bdgModCncl
                MOVE            "Remove",#d10
                SETITEM         bdgRmBtn,0,#d10
                CLEAR           #mod,#d10
                SETPROP         bdgLV,ENABLED=1
                SETITEM         bCode,0,0
                SETITEM         EdtBdgAmt,0,#d10
                SETPROP         BdgModBtn,ENABLED=0
                RETURN

#f2             FORM            2
bdgcheck        ROUTINE         pF ;catagory num code
                MOVE            pf,#f2
                CALL            gettotals ;make sure totals are up to date
                MOVE            #f2,#d10
                PACK            #d20,"03X",#f2
                READ            bdgdat,#d10;bdgrcrd
                RETURN          IF OVER
                READ            DcatDesc,#d20;catrcrd
                IF              (matotal(catcode) > bdgamt)
                ALERT           NOTE,"This Entry puts you over budget!!!",#f4,catdesc
                ENDIF
                RETURN

pf2             FORM            ^
pff             FORM            ^.
#ff2            FORM            2
bdgcheck2       ROUTINE         pf2,pff
                MOVE            pf2,#ff2
                MOVE            #ff2,#d10
                READ            bdgdat,#d10;bdgrcrd
                RETURN          IF OVER
                IF              (pff > bdgamt)
                CLEAR           pf2
                ENDIF
                RETURN

LoadBdg
;****LOAD Budget Information****
                REPOSIT         bdgdat,ZERO
                CLEAR           bdgtot
                TRAP            nothing noreset IF IO ;just read passed deleted records
                LOOP
                READ            bdgdat,seq;bdgrcrd
                BREAK           IF OVER
                PACK            #d10,"03X",bdgcode
                READ            DcatDesc,#d10;catrcrd
                BdgLV.InsertItem GIVING #f4 USING catdesc,99999
                MOVE            bdgamt,#d10
                BdgLV.SetItemText USING #f4,#d10,1
                ADD             bdgamt,bdgtot
                REPEAT
                MOVE            bdgtot,#d10
                SETITEM         EdtBdgTot,0,#d10
                TRAPCLR         IO
                RETURN
