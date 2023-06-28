*****************************************************************************
. Debt management
.
.
dbtdat          IFILE           NODUP,UPPER
*
.dbts file is 66 byte records 
.
dbtrcrd         LIST
dbtdisc         DIM             ^40
dbtamt          FORM            7.2
dbtlmnt         FORM            7.2
dbtrate         FORM            2.3
                LISTEND

ApplyInterest   FORM            1

dbttot          FORM            7.2
#mod            FORM            1

#d10            DIM             ^10
#d18            DIM             ^19
#d40            DIM             ^40
#d50            DIM             ^50
#d80            DIM             ^80
#f4             FORM            4

StartDbt
                CLEAR           ftrap
                TRAP            noFile IF IO
                OPEN            dbtdat,debts
                IF              (ftrap)
                PREP            dbtdat,debts,debts,"1-40","66"
                ENDIF
                TRAPCLR         IO
.
                MOVE            "Appliy_Interest",d40
                CLOCK           ini,d40
                IF              OVER
                CLEAR           ApplyInterest
                ELSE
                CHOP            d40,d40
                MOVE            d40,ApplyInterest
                ENDIF
.
                dbtlst.InsertColumn USING "Description",200,1
                dbtlst.InsertColumn USING "Amount",70,2,01
                dbtlst.InsertColumn USING "Last Payment",76,3
                dbtlst.InsertColumn USING "LP Amount",65,4,01
                dbtlst.InsertColumn USING "Limit",60,5,01
                dbtlst.InsertColumn USING "APR",60,6
                dbtlst.SetExtendedStyle USING 0x01,0x01
.
                SETITEM         cfgAPRchk,0,ApplyInterest
.
                CALL            LoadDbt
                RETURN

AddDbt
                GETITEM         EdtDbtDisc,0,#d40
                RETURN          IF (#d40="")
.
                GETITEM         EdtDbtAmt,0,#d10
                CHOP            #d10,#d10
                RETURN          IF (#d10="")
.
                CALL            StripLeadingSpcae USING #d10
                CALL            StripLeadingSpcae USING #d40
                MOVE            #d40,dbtdisc
                MOVE            #d10,dbtamt
.
                GETITEM         EdtDbtLmnt,0,#d10
                CHOP            #d10,#d10
                MOVE            #d10,dbtlmnt
.
                GETITEM         EdtDbtAPR,0,#d10
                CHOP            #d10,#d10
                CALL            StripLeadingSpcae USING #d10
                MOVE            #d10,dbtrate
.
                WRITE           dbtdat,dbtdisc;dbtrcrd
                CLEAR           #d18
. 
                CHOP            dbtdisc,dbtdisc
                dbtlst.InsertItem GIVING #f4 USING dbtdisc
                MOVE            dbtamt,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,1
                MOVE            dbtlmnt,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,4
                MOVE            dbtrate,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,5
.
                CLEAR           #d10,#d40
                SETITEM         EdtDbtDisc,0,#d40
                SETITEM         EdtDbtAmt,0,#d10
                SETITEM         EdtDbtLmnt,0,#d10
                SETITEM         EdtDbtAPR,0,#d10
                CALL            totlDBT
                RETURN

SModDbt
                dbtlst.GetNextItem GIVING #f4 USING 2 ;selected
                dbtlst.GetItemText GIVING #d40 USING #f4,0 ;description
                dbtlst.GetItemText GIVING #d10 USING #f4,1 ;Amount
                CHOP            #d40,#d40
                SETPROP         dbtlst,ENABLED=0

                CALL            StripLeadingSpcae USING #d10
                CALL            StripLeadingSpcae USING #d40
                SETITEM         EdtDbtDisc,0,#d40
                SETITEM         EdtDbtAmt,0,#d10
                dbtlst.GetItemText GIVING #d10 USING #f4,4 ;limit
                CALL            StripLeadingSpcae USING #d10
                SETITEM         EdtDbtLmnt,0,#d10

                dbtlst.GetItemText GIVING #d10 USING #f4,5 ;APR
                CALL            StripLeadingSpcae USING #d10
                SETITEM         EdtDbtAPR,0,#d10
.
                READ            dbtdat,#d40;dbtrcrd
                SETPROP         DbtModBtn,ENABLED=1
                MOVE            "Cancel",#d10
                SETITEM         rmdbtbtn,0,#d10
                SET             #mod
                SETITEM         EdtDbtAmt,1,0
                SETITEM         EdtDbtAmt,2,999
                SETFOCUS        EdtDbtAmt
                RETURN

ModDbt
                GETITEM         EdtDbtDisc,0,#d40
                CHOP            #d40,#d40
                RETURN          IF (#d40="")
.
                GETITEM         EdtDbtAmt,0,#d10
                CHOP            #d10,#d10
                RETURN          IF (#d10="")
.
                CALL            StripLeadingSpcae USING #d40
                CALL            StripLeadingSpcae USING #d10
                MOVE            #d40,dbtdisc
                MOVE            #d10,dbtamt
.
                GETITEM         EdtDbtLmnt,0,#d10
                CHOP            #d10,#d10
                MOVE            #d10,dbtlmnt
.
                GETITEM         EdtDbtAPR,0,#d10
                CHOP            #d10,#d10
                CALL            StripLeadingSpcae USING #d10
                MOVE            #d10,dbtrate
.
                UPDATE          dbtdat;dbtrcrd ;update the record data
                READKEY         dbtdat,#d40 ; get the old key
                DELETEK         dbtdat,#d40 ; delete the old key
                INSERT          dbtdat,dbtdisc ; insert the new key
. 
                CALL            getLastPmnt

                PACKKEY         #d80,dbtdisc,dbtamt," ",Date,pmnt,dbtlmnt

                dbtlst.GetNextItem GIVING #f4 USING 2 ;selected
                dbtlst.DeleteItem USING #f4
                dbtlst.InsertItem GIVING #f4 USING dbtdisc

                MOVE            dbtamt,#d10
                dbtlst.SetItemText USING #f4,#d10,1
                MOVE            Date,#d10
                dbtlst.SetItemText USING #f4,#d10,2
                MOVE            pmnt,#d10
                dbtlst.SetItemText USING #f4,#d10,3
                MOVE            dbtlmnt,#d10
                dbtlst.SetItemText USING #f4,#d10,4
                MOVE            dbtrate,#d10
                dbtlst.SetItemText USING #f4,#d10,5

                CALL            totlDBT
ModDbtCnl
                SETPROP         dbtlst,ENABLED=1
                MOVE            "Remove",#d10
                SETITEM         rmdbtbtn,0,#d10
                CLEAR           #d10,#d40,#mod
                SETITEM         EdtDbtDisc,0,#d40
                SETITEM         EdtDbtAmt,0,#d10
                SETITEM         EdtDbtLmnt,0,#d10
                SETITEM         EdtDbtAPR,0,#d10
                SETPROP         DbtModBtn,ENABLED=0
                RETURN

RmDbt
                IF              (#mod)
                CALL            ModDbtCnl
                RETURN
                ENDIF
                dbtlst.GetNextItem GIVING #f4 USING 2 ;selected

                dbtlst.GetItemText GIVING #d40 USING #f4,0 ;description
                CHOP            #d40,#d40
                READ            dbtdat,#d40;dbtrcrd
                DELETE          dbtdat

                dbtlst.DeleteItem USING #f4
                dbtlst.SetItemState USING #f4,2,2 ;selected
                CALL            totlDBT
                RETURN

TotlDbt
                REPOSIT         dbtdat,ZERO
                CLEAR           dbttot
                TRAP            nothing noreset IF IO ;just read passed deleted records
                LOOP
                READ            dbtdat,seq;dbtrcrd
                BREAK           IF OVER
                ADD             dbtamt,dbttot
                REPEAT
                TRAPCLR         IO
                MOVE            dbttot,#d10
                SETITEM         EdtDbtTotal,0,#d10
                RETURN

nothing
                RETURN

f7p3            FORM            7.3
ApplytoDPT
                MOVE            disc,#d40
                READ            dbtdat,#d40;dbtrcrd
                RETURN          IF OVER
appmpt
                PACKKEY         #d80,recrd
                PACK            #d50,"Apply to this debt? : ",dbtdisc
                ALERT           plain,#d50,#f4,"Apply to this dept?"
                IF              (#f4>"2")
                UNPACK          #d80,recrd
                RETURN
                ENDIF
                SWITCH          #f4
                CASE            "1"
                IF              (ApplyInterest="1")
                MOVE            (dbtamt*((dbtrate/100)/12)),f7p3
                MOVE            f7p3,f7p2
                PACK            #d50,"Apply $",f7p2," interest to balence first?"
                ALERT           TYPE=4,#d50,#f4,"Interest Charge"
                IF              ( #f4="6" | #f4="1" )
                ADD             f7p2,dbtamt
                ENDIF
                ENDIF
                MOVE            (dbtamt-pmnt),f7p2
                MOVE            f7p2,dbtamt
                UPDATE          dbtdat;dbtrcrd
                CHOP            dbtdisc,#d40
                MOVE            #d40,dbtdisc
                dbtlst.FindItem GIVING #f4 USING *TEXT=dbtdisc
                CALL            getLastPmnt
                IF              (#f4 > "-1")
                dbtlst.DeleteItem USING #f4
                dbtlst.InsertItem GIVING #f4 USING dbtdisc
                MOVE            dbtamt,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,1
                MOVE            Date,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,2
                MOVE            pmnt,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,3
                MOVE            dbtlmnt,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,4
                MOVE            dbtrate,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,5
                ELSE
                ALERT           STOP,dbtdisc,#f4,"LV Processing error!!!"
                UNPACK          #d80,recrd
                RETURN
                ENDIF
                CALL            totlDBT
                CASE            "2"
                READKS          dbtdat;dbtrcrd
                IF              OVER
                UNPACK          #d80,recrd
                RETURN
                ENDIF
                GOTO            appmpt
                ENDSWITCH
                UNPACK          #d80,recrd
                RETURN

LoadDbt
;****LOAD the debt management DISPLAY AND calculate balence****
                REPOSIT         dbtdat,ZERO
                TRAP            nothing noreset IF IO ;just read passed deleted records
                LOOP
                READ            dbtdat,seq;dbtrcrd
                BREAK           IF OVER
                CHOP            dbtdisc,#d40
                MOVE            dbtamt,#d10
                CHOP            #d10,#d10
                CALL            getLastPmnt

                CHOP            dbtdisc,dbtdisc
                dbtlst.InsertItem GIVING #f4 USING dbtdisc
                MOVE            dbtamt,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,1
                MOVE            Date,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,2
                MOVE            pmnt,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,3
                MOVE            dbtlmnt,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,4
                MOVE            dbtrate,#d10
                CHOP            #d10,#d10
                dbtlst.SetItemText USING #f4,#d10,5
                REPEAT
                TRAPCLR         IO
                CALL            TotlDbt
                RETURN

getLastPmnt
                CLEAR           recrd
                PACK            #d50,"03x",#d40
                READLAST        chkbkdat,#d50;recrd
                RETURN
