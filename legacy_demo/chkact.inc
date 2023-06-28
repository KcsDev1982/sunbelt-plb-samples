*********************************************
.  Multiple Account Management
.
.**declaired in form***
.AcntLst
.EdtAcntName
.AcntRmBtn
.**********************
*
.Accounts record len = 50
.
acnt            RECORD
desc            DIM             40
num             FORM            2
Balance         FORM            5.2
                RECORDEND
. shhh....don't tell eanybody we are maintinging keys for multiple columns
. in a single isi file...:)
. this is a hackers approach to a problem...beginners better off using aam...
acntnumkey      DIM             2
. I elecited to take this approach because the most number of records
. this file will ever have is 100 with a record size of 50...
. this comes out to 5000 bytes max...aamdex files start at 64k in size
. and the isi file even with multiple column keys won't get that large.
. A second isi file gives and extra 1500 byte overhead and not necesary
. for our purpose.... Dont try this at home kids...It works here because the
. account desc and the account num are different and should never intersect
.
#NxtAcnt        FORM            2
#d10            DIM             ^10
#d40            DIM             ^40
#d402           DIM             ^40
#f4             FORM            4
#f2             FORM            2
#MOD            FORM            1

accounts        IFILE           Nodup,UPPER

StartAcct
                CLEAR           ftrap
                TRAP            noFile IF IO
                OPEN            accounts,Accnts
                IF              (ftrap)
                PREP            accounts,Accnts,Accnts,"1-40","50"
                MOVE            "default",acnt.desc
                CLEAR           acnt.num
                WRITE           accounts;acnt
                MOVE            acnt.num,acntnumkey
                INSERT          accounts,acntnumkey
                ENDIF
                TRAPCLR         IO
                CALL            LoadAcct
                SETITEM         ActvAcntBox,1,1
                RETURN

AcntAdd
                GETITEM         EdtAcntName,0,#d40
                CHOP            #d40,#d40
                RETURN          IF (#d40="")
                MOVE            #d40,acnt.desc
                MOVE            #nxtAcnt,acnt.num
                TRAP            werror IF IO
                WRITE           accounts,#d40;acnt
                MOVE            acnt.num,acntnumkey
                INSERT          accounts,acntnumkey
                TRAPCLR         IO
                AcntLst.AddString USING #d40
                INSERTITEM      ActvAcntBox,99,acnt.desc
                CLEAR           #d40
                SETITEM         EdtAcntName,0,#d40
                RETURN

werror
                NORETURN
                ALERT           note,"Duplicates not allowed or write error",#f4,#d40
                RETURN

AcntRm
                IF              (#MOD)
                CALL            AcntCnl
                RETURN
                ENDIF
                AcntLst.GetCaretIndex GIVING #f4
                AcntLst.GetText GIVING #d40 USING #f4
                CHOP            #d40,#d40
                READ            accounts,#d40;acnt
                MOVE            acnt.num,acntnumkey
                DELETEK         accounts,acntnumkey
                DELETE          accounts
                AcntLst.DeleteString USING #f4
                AcntLst.SetCurSel USING #f4

. CALL ComboSrch USING ActvAcntBox,#d40,#f4
                ActvAcntBox.FindString GIVING #f4 USING #d40,seq
. INCR #f4 ;. 24 Oct 2006
                ActvAcntBox.GetCurSel GIVING #f2
. INCR #f2 ;. 24 Oct 2006
                IF              ( #f2 = #f4 )
                IF              ( #f2 != "1" )
                ActvAcntBox.SetCurSel USING 0
                ELSE
                ActvAcntBox.SetCurSel USING 1
                ENDIF
                ENDIF
                ActvAcntBox.DeleteString USING #f4 ;. 24 Oct 2006
                IF              ( #f2 = #f4 )
                CALL            ChngActvAccnt
                ENDIF
                RETURN

AcntSMod
                SET             #MOD
                CALL            CatCnl
                CALL            ModDbtCnl
                AcntLst.GetCaretIndex GIVING #f4
                AcntLst.GetText GIVING #d40 USING #f4
                CHOP            #d40,#d40
                SETITEM         EdtAcntName,0,#d40
                READ            accounts,#d40;acnt
                SETPROP         AcntLst,ENABLED=0
                SETPROP         acntMod,ENABLED=1
                MOVE            "&Cancel",#d10
                SETITEM         AcntRmBtn,0,#d10
                RETURN

AcntMod
                GETITEM         EdtAcntName,0,#d40
                CHOP            #d40,#d40
                RETURN          IF (#d40="")
                MOVE            acnt.desc,#d402
                DELETEK         accounts,#d402
                AcntLst.GetCaretIndex GIVING #f4
                AcntLst.DeleteString USING #f4
                AcntLst.InsertString USING #d40,#f4
                MOVE            #d40,acnt.desc
                INSERT          accounts,#d40
                UPDATE          accounts;acnt

AcntCnl
                CLEAR           #d40
                SETITEM         EdtAcntName,0,#d40
                MOVE            "&Remove",#d10
                SETITEM         AcntRmBtn,0,#d10
                SETPROP         AcntLst,ENABLED=1
                SETPROP         acntMod,ENABLED=0
                CLEAR           #MOD
                RETURN

LoadAcct
                CLEAR           #NxtAcnt
                REPOSIT         accounts,ZERO
                TRAP            nothing noreset IF IO ;just read passed deleted records
                LOOP
                READ            accounts,seq;acnt
                BREAK           IF OVER
                IF              (acnt.num=#NxtAcnt)
                INCR            #NxtAcnt
                ENDIF
                CHOP            acnt.desc
                AcntLst.AddString USING acnt.desc
                INSERTITEM      ActvAcntBox,99,acnt.desc
                REPEAT
                CLEAR           acnt.num
                PACK            actAcntkey,"06x",acnt.num
                RETURN

ChngActvAccnt
                GETITEM         ActvAcntBox,0,#f4
                GETITEM         ActvAcntBox,#f4,d40
                CHOP            d40,d40
                chkbk.DeleteAllItems
                READ            accounts,d40;acnt
                RETURN          IF OVER
                PACK            actAcntkey,"06x",acnt.num
                CLEAR           bnkbal
                CALL            LoadTrns
                MOVE            bnkbal,d10
                SETITEM         EdtBankBal,0,d10
                RETURN

acntno          FORM            2
newbal          FORM            ^
UpdateBalance   ROUTINE         acntno,newbal
                MOVE            acntno,acntnumkey
                READ            accounts,acntnumkey;acnt
                MOVE            newbal,acnt.Balance
                UPDATE          accounts;acnt
                RETURN
dimp            DIM             ^
CheckBalance    ROUTINE         dimp,newbal
                READ            accounts,dimp;acnt
                MOVE            acnt.Balance,newbal
                RETURN

GetAcntNum      ROUTINE         dimp,newbal
                READ            accounts,dimp;acnt
                MOVE            acnt.num,newbal
                RETURN
