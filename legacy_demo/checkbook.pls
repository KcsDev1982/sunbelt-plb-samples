***************************************************************************
.Personal Finance Manager (checkbook)
.              Author: Matthew Lake
.      Last modified: 10/25/2006
.****************************************************************************
. todo:
. delete transfer...remove from both accounts...
.****************************************************************************
.
*
. File and key Declaration
.

chkbkdat        AFILE
seq             FORM            "-1"
ZERO            CONST           "0"
key3            DIM             ^44
*
. chkbk file is 80 byte records defined as follows
.
recrd           LIST
chkno           FORM            6   ;1-6
Date            DIM             ^10 ;10  ;7-16 *(7-8,13-16)(7-16)
disc            DIM             ^40 ;40  ;17-56 *
pmnt            FORM            5.2   ;57-64
rsvrd           DIM             1   ;65 reserved
dep             FORM            5.2   ;66-73
ecode           FORM            2   ;74-75 *
chkclr          FORM            1    ;76 check has cleard the bank
accnt           FORM            2    ;77-78  *account num
tnsfr           FORM            1    ;79  does not count as income
rsvrd2          DIM             1   ;80 reserved
                LISTEND

descCnt         FORM            2
actAcntkey      DIM             ^5 ;5
*
. Time Stamp and date related fields
.
ts              DIM             ^16
timestampd      LIST
tsyear          DIM             4
tsmonth         DIM             2
tsday           DIM             2
                LISTEND

mnyear          FORM            4
mnmonth         FORM            2

maxdate         LIST
mxyear          FORM            4
mxmonth         FORM            2
                LISTEND

span            FORM            3 ; this checkbook covers this many months

wmonth          FORM            2
.wday FORM 2
wyear           FORM            4


*
. generic work vars
.
#deposit        FORM            1

olddat          DIM             ^50
olddat2         DIM             ^50
olddat3         DIM             ^50
ftrap           FORM            1
d1              DIM             1
d2              DIM             2
d3              DIM             3
d4              DIM             4
d6              DIM             6
d8              DIM             ^8
d10             DIM             ^10
d20             DIM             ^20
d40             DIM             ^40
d50             DIM             ^50
d80             DIM             80
Balence         FORM            7.2
bnkbal          FORM            7.2
tIndex          FORM            10
temp            FORM            10
len             FORM            2
len2            FORM            2
F2              FORM            2
F3              FORM            3
F4              FORM            4
f7p2            FORM            7.2
maxval          FORM            5.2(25)
imaxval         FORM            5.2
emaxval         FORM            5.2
pF              FORM            ^
i4              INTEGER         4
eventresult     FORM            9
LastSrcRow      FORM            10

*
. Chart Work Vars
.
atotal          FORM            6.2(25) ;year catagory totals
matotal         FORM            6.2(25) ;month catagory totals

LVS_SELECTED    INTEGER         2,"0x0002"
chkfrm          PLFORM          checking.plf

checkbook       DIM             20
debts           DIM             20
catagories      DIM             20
budget          DIM             20
Accnts          DIM             20

black           COLOR
red             COLOR
italics         FONT
Normal          FONT
*****************************************************************************
. Startup code
.

                WINHIDE

                CREATE          black=*black
                CREATE          red=*red
                CREATE          Normal,"'>MS Sans Serif'",SIZE=8,ITALIC=0
                CREATE          italics,"'>MS Sans Serif'",SIZE=8,ITALIC=1

                MOVE            "chkbk",checkbook
                MOVE            "dbt",debts
                MOVE            "cat",catagories
                MOVE            "bdg",budget
                MOVE            "Acnts",Accnts
 
                FORMLOAD        chkfrm
                SETITEM         CCode,0,0
.
                chkbk.InsertColumn USING "Clr",20,0
                chkbk.InsertColumn USING "Check No",60,1
                chkbk.InsertColumn USING "Date",70,2
                chkbk.InsertColumn USING "Disc",195,3
                chkbk.InsertColumn USING "Payment",60,4,01
                chkbk.InsertColumn USING "Code",35,5
                chkbk.InsertColumn USING "Deposit",60,6,01
                chkbk.InsertColumn USING "Balance",70,7,01
 
                chkbk.InsertAttrColor USING black,red
                chkbk.InsertAttrColumn USING 8
 
                LVexpence.InsertColumn USING "Description",96,0
                LVExpence.InsertColumn USING "Month",60,1,*FORMAT=01
                LVExpence.InsertColumn USING "Avg",60,2,*FORMAT=01
                LVExpence.InsertColumn USING "YTD",60,3,*FORMAT=01
                LVexpence.InsertAttrFont USING Normal,Italics
                LVexpence.InsertAttrColor USING black,red
                LVexpence.InsertAttrColumn USING 4
 
                CLEAR           ftrap
                TRAP            noFile IF IO
                OPEN            chkbkdat,checkbook
                IF              (ftrap)
                PREP            chkbkdat,checkbook,checkbook,"U,7-8,13-16,17-56,74-75,7-16,77-78","80"
                ENDIF
.
                CALL            StartCat
                CALL            StartAcct
                CALL            StartBdg
                CALL            StartDbt
. CALL LoadTrns ;. 24 Oct 2006

                TRAP            shareware noreset IF CFAIL
                CALL            loadchartmod
.
                MOVE            bnkbal,d10
                SETITEM         EdtBankBal,0,d10
                IF              ( bnkbal < 0 )
                SETPROP         EdtBankBal,FGCOLOR=red
                ELSE
                SETPROP         EdtBankBal,FGCOLOR=black
                ENDIF

.
. chkbk.GetItemCount GIVING tIndex
. DECR tIndex
. chkbk.EnsureVisible USING tIndex,0
.
                SETPROP         chkbtab,VISIBLE=1
                SETPROP         dbtstab,VISIBLE=0
                ACTIVATE        chkbkWindow ;,VISIBLE=1
                CALL            ModchkCnl
                LOOP
                WAITEVENT
                REPEAT

noFile
                SET             ftrap
                RETURN

PendingTrans    IFILE

F5              FORM            5
Ldfm2           FORM            2
startpos        FORM            10
LoadTrns
                DEBUG
                REPOSIT         chkbkdat,ZERO
                READ            chkbkdat,seq;recrd
                REPLACE         " 0",date
                EXPLODE         date,"/",mnmonth,d2,mnyear
. ****LOAD the checkbook DISPLAY AND calculate balence AND span****
                PACK            d20,"03LYEAR START"   ;29 Dec 2003
                READ            chkbkdat,actAcntkey,d20;recrd  ;03 Jan 2005
                IF              NOT OVER
                BUMP            date,6    ; 1/03/2005
                MOVE            date,ts    ; 1/03/2005
                FPOSITB         chkbkdat,startpos
                LOOP
                READKG          chkbkdat;recrd
                BREAK           IF OVER
                BUMP            date,6    ; 1/03/2005
                MOVE            date,ts    ; 1/03/2005
                FPOSITB         chkbkdat,startpos
                REPEAT
                ENDIF
                REPOSIT         chkbkdat,startpos
. load previous years uncleared transactions
                PACK            D80,"chkbk.txt,pending.isi ;76-76,P=#"76='0' & 13!='",ts,"'#""
                INDEX           D80
                IF              NOT OVER
                OPEN            PendingTrans,"pending.isi"
                MOVE            " ",D1
                READ            PendingTrans,D1;recrd
                BUMP            actAcntkey,3
                MOVE            actAcntKey,Ldfm2
                RESET           actAcntkey
                LOOP
                READKS          PendingTrans;recrd
                UNTIL           OVER
                IF              ( ACCNT = Ldfm2 )
                CALL            ADDTOLV
                ENDIF
                REPEAT
                CLOSE           PendingTrans
                ERASE           "pending.isi"
                ENDIF

. load this years data
                SETPROP         chkbk,AUTOREDRAW=0
                CLEAR           maxdate
                BUMP            actAcntkey,3
                MOVE            actAcntkey,F3
                RESET           actAcntkey
                LOOP
                READ            chkbkdat,seq;recrd
                UNTIL           OVER
                REPLACE         " 0",date
                MOVE            accnt,F4
                IF              (F3=F4)
                BUMP            date,6
                IF              ( chkclr = 0 OR date=ts)
                RESET           date
                CALL            ADDToLV
                ENDIF
         
                EXPLODE         date,"/",wmonth,d2,wyear
         
                IF              (wmonth < mnmonth)
                MOVE            wmonth,mnmonth
                ENDIF
                IF              (wmonth > mxmonth)
                MOVE            wmonth,mxmonth
                ENDIF
                IF              (wyear < mnyear)
                MOVE            wyear,mnyear
                ENDIF
                IF              (wyear > mxyear)
                MOVE            wyear,mxyear
                ENDIF
                ENDIF
                REPEAT
 
                CALL            doBalence

                CLOCK           timestamp,ts
                UNPACK          ts,timestampd
                DECR            mnmonth
                SUB             mnyear,mxyear,wyear
                SUB             mnmonth,mxmonth,wmonth
                MOVE            "12",F4
                MULT            wyear,F4
                IF              ( F4 > "12" )
                MOVE            wmonth,span
                ADD             F4,span
                ELSE
                MOVE            tsmonth,span
                ENDIF
.
. detect year roll over and place new year start tag in data file for
. the current account
.
                MOVE            tsyear,F4   ;29 Dec 2003
                IF              (F4 != mxyear)    ;29 Dec 2003
                chkbk.GetItemCount GIVING F5   ;29 Dec 2003
                DECR            F5    ;29 Dec 2003
                chkbk.GetItemText GIVING d10 USING F5,7 ;29 Dec 2003
                CHOP            d10    ;29 Dec 2003
                MOVE            d10,f7p2   ;29 Dec 2003
                MOVE            "0",chkno   ;29 Dec 2003
                CLEAR           pmnt    ;29 Dec 2003
                CLEAR           ecode    ;29 Dec 2003
                MOVE            f7p2,dep   ;29 Dec 2003
                PACK            date,"01/01/",tsyear  ;29 Dec 2003
                MOVE            "year start",disc  ;29 Dec 2003
                MOVE            F3,accnt   ;29 Dec 2003
                SET             chkclr    ;13 Jan 2005
                WRITE           chkbkdat;recrd   ;29 Dec 2003
                chkbk.DeleteAllItems ;29 Dec 2003
                CALL            LoadTrns   ;29 Dec 2003
                ENDIF           ;29 Dec 2003

                chkbk.GetItemCount GIVING tIndex  ;. 24 Oct 2006
                chkbk.EnsureVisible USING tIndex,0  ;. 24 Oct 2006
 
                SETPROP         chkbk,AUTOREDRAW=1
                MOVE            F3,F2
                CALL            UpdateBalance,F2,Balence
                RETURN

.****************************************************
. includes
                INCLUDE         chkcat.inc
                INCLUDE         chkchart.inc
                INCLUDE         chkbdg.inc
                INCLUDE         chkdbt.inc
                INCLUDE         chkmsc.inc
                INCLUDE         chkact.inc

*****************************************************************************
. Checkbook functions
.
F8              FORM            8
addCheck
                CLEAR           recrd
                GETITEM         EdtChkNo,0,d6
                CHOP            d6,d6
                IF              (d6="")
                CLEAR           chkno
                ELSE
                MOVE            d6,chkno
                ENDIF
.
                GETITEM         EdtDate,0,Date
                SETLPTR         Date,8
                MOVE            date,F8
                MULT            "10000.0001",F8
                MOVE            F8,D8
                EDIT            d8,Date,mask="99/99/9999"
                REPLACE         " 0",date
.
                GETITEM         EdtPayTo,0,disc
                GETITEM         EdtAmount,0,d8
                CHOP            d8,d8
                MOVE            d8,pmnt
.
                GETITEM         CCode,0,ecode
                IF              (ecode="0")
                ALERT           NOTe,"Please Select Transaction Code",F4,disc
                RETURN
                ENDIF
                GETITEM         CCode,ecode,d20
                CHOP            d20,d20
                PACK            d40,"01X",d20
                READ            DcatDesc,d40;catrcrd
                MOVE            catcode,ecode
. IF (Date="")
.  CLOCK timestamp,ts
.  UNPACK ts,timestampd
.  PACK Date,tsmonth,"/",tsday,"/",tsyear
. ENDIF
.
                CLEAR           dep
                CALL            ApplytoDPT
.
                BUMP            actAcntkey,3
                MOVE            actAcntkey,F3
                RESET           actAcntkey
                MOVE            F3,accnt
                WRITE           chkbkdat;recrd
                CALL            AddToLV
                MOVE            ecode,F4
                CALL            bdgcheck USING F4
                CLEAR           d1
                SETITEM         EdtChkNo,0,d1
                SETITEM         EdtDate,0,d1
                SETITEM         EdtPayTo,0,d1
                SETITEM         EdtAmount,0,d1
                SETITEM         CCode,0,0
                CALL            doBalence
                RETURN
 
AddDep
                CLEAR           recrd
.
                GETITEM         EdtDate,0,Date
                SETLPTR         Date,8
                MOVE            date,F8
                MULT            "10000.0001",F8
                MOVE            F8,D8
                EDIT            d8,Date,mask="99/99/9999"
                REPLACE         " 0",date
.
                GETITEM         EdtPayTo,0,disc
                GETITEM         EdtAmount,0,d8
                CHOP            d8,d8
                MOVE            d8,dep
. CHOP date,date
. IF (Date="")
.  CLOCK timestamp,ts
.  UNPACK ts,timestampd
.  PACK Date,tsmonth,"/",tsday,"/",tsyear
. ENDIF
                BUMP            actAcntkey,3
                MOVE            actAcntkey,F3
                RESET           actAcntkey
                MOVE            F3,accnt
                WRITE           chkbkdat;recrd
                CALL            AddToLV
                CLEAR           d1
                SETITEM         EdtChkNo,0,d1
                SETITEM         EdtDate,0,d1
                SETITEM         EdtPayTo,0,d1
                SETITEM         EdtAmount,0,d1
                SETITEM         CCode,0,0
                CALL            doBalence
                RETURN

******Modify checkbook entry
chkbkDBLclick   ROUTINE         pf
                chkbk.GetItemText GIVING d40 USING pf,5
                CHOP            d40,d40
                TYPE            d40
                IF              EOS
                SET             #deposit
                CLEAR           catcode
                ELSE
                CLEAR           #deposit
                ENDIF
 
                IF              (#deposit="0")
                IF              (d40="??")
                CLEAR           catcode
                SETITEM         CCode,0,catcode
                ELSE
                PACK            d10,"02X",d40
                READ            Dcatdesc,d10;catrcrd
                CHOP            catdesc,catdesc
                CCode.FindString GIVING catcode USING CatDesc,seq
                INCR            catcode
                IF              (catcode)
                SETITEM         CCode,0,catcode
                ENDIF
                ENDIF
                ENDIF

                chkbk.GetItemText GIVING d40 USING pf,1
                CHOP            d40,d40
                MOVE            d40,chkno
                SETITEM         EdtChkNo,0,d40

                chkbk.GetItemText GIVING d40 USING pf,2
                CHOP            d40,olddat2
                SQUEEZE         d40,d8,"/"
                MOVE            d8,F8
                MULT            "10000.0001",F8
                MOVE            F8,d40
                SETITEM         EdtDate,0,d40
                MOVE            d40,Date
 
                chkbk.GetItemText GIVING d40 USING pf,3
                CHOP            d40,d40
                SETITEM         EdtPayTo,0,d40
                MOVE            d40,disc
                MOVE            disc,olddat

                chkbk.GetItemText GIVING d40 USING pf,4
                CHOP            d40,d40
                MOVE            d40,pmnt

                chkbk.GetItemText GIVING d40 USING pf,6
                CHOP            d40,d40
                MOVE            d40,dep
 
                IF              (pmnt)
                MOVE            pmnt,d10
                MOVE            PMNT,OLDDAT3
                ELSE
                MOVE            dep,d10
                MOVE            DEP,OLDDAT3
                ENDIF
                SETITEM         EdtAmount,0,d10

                SETPROP         CheckBtn,VISIBLE=0
                SETPROP         DepBtn,VISIBLE=0
                SETPROP         ModChkbtn,VISIBLE=1
                SETPROP         ModCnlbtn,VISIBLE=1
                SETPROP         chkbk,ENABLED=0
                SETPROP         ChkbkSearch,ENABLED=0
                RETURN

Modchk
                PACK            d40,"05X",olddat2
                PACK            d50,"03X",olddat
                READ            chkbkdat,d40,d50,actAcntkey;recrd ;valid read req before update
                LOOP            ; make sure we have the right record
                MOVE            pmnt,d10
                BREAK           IF (olddat3 = d10)
                MOVE            dep,d10
                BREAK           IF (olddat3 = d10)
                READKG          chkbkdat;recrd
                REPEAT

                GETITEM         EdtDate,0,Date
                SETLPTR         Date,8
                MOVE            date,F8
                MULT            "10000.0001",F8
                MOVE            F8,D8
                EDIT            d8,Date,mask="99/99/9999"
                REPLACE         " 0",date

                GETITEM         EdtChkNo,0,d6
                CHOP            d6,d6
                IF              (d6="")
                CLEAR           chkno
                ELSE
                MOVE            d6,chkno
                ENDIF
                GETITEM         EdtPayTo,0,disc
                GETITEM         EdtAmount,0,d8
                CHOP            d8,d8
                IF              (#deposit="0")
                MOVE            d8,pmnt
                CLEAR           dep
                GETITEM         CCode,0,ecode
                GETITEM         CCode,ecode,d10
                IF              (ecode="0")
                ALERT           Note,"Please Select Transaction Code",F4,disc
                RETURN
                ENDIF
                CHOP            d10,d10
                PACK            d20,"01L",d10
                READ            dcatdesc,d20;catrcrd
                ELSE
                MOVE            d8,dep
                CLEAR           pmnt
                CLEAR           catcode
                ENDIF

                MOVE            catcode,ecode
                UPDATE          chkbkdat;recrd
                MOVE            chkno,d6

                chkbk.GetNextItem GIVING tIndex USING LVS_SELECTED

                CALL            getDateVal USING date,i4
                MOVE            i4,temp
                PACK            d20,temp,chkno
                chkbk.SetItemText USING tIndex,d20,0
                chkbk.SetItemText USING tIndex,d6,1
                CALL            haveidx
                CALL            doBalence

ModchkCnl
                CLEAR           d1,recrd
                SETITEM         EdtChkNo,0,d1
                SETITEM         EdtDate,0,d1
                SETITEM         EdtPayTo,0,d1
                SETITEM         EdtAmount,0,d1
                SETITEM         CCode,0,0
                SETPROP         chkbk,ENABLED=1
                SETPROP         CheckBtn,VISIBLE=1
                SETPROP         DepBtn,VISIBLE=1
                SETPROP         ModChkbtn,VISIBLE=0
                SETPROP         ModCnlbtn,VISIBLE=0
                SETPROP         ChkbkSearch,ENABLED=1
                RETURN

.*******************************************************************
. Interface routines
d8a             DIM             8
AddToLV
                CALL            getDateVal USING date,i4
                MOVE            i4,temp
                IF              (chkno="0" & dep > "0" )
                MOVE            "     ",d6
                ELSE
                MOVE            chkno,d6
                ENDIF
                PACK            d20,temp,d6
                MOVE            chkno,d6
                MOVE            pmnt,d8
                IF              (ecode)
                PACK            d10,"03X",ecode
                READ            DcatDesc,d10;catrcrd
                IF              NOT OVER
                MOVE            cat2desc,d2
                ELSE
                MOVE            "??",d2
                ENDIF
                ELSE
                CLEAR           d2
                ENDIF
                MOVE            dep,d8a
                chkbk.InsertItemEx GIVING tindex USING d20,999999:
                                *subitem1=d6:
                                *subitem2=date:
                                *subitem3=disc:
                                *subitem4=d8:
                                *subitem5=d2:
                                *subitem6=d8a
                IF              (chkclr=0)
                chkbk.SetItemCheck USING tindex,1
                SUB             dep,bnkbal
                ADD             pmnt,bnkbal
                ENDIF
                GOTO            lvaddDone

haveidx
                chkbk.SetItemText USING tIndex,date,2
                chkbk.SetItemText USING tIndex,disc,3
                MOVE            pmnt,d8
                chkbk.SetItemText USING tIndex,d8,4

                IF              (ecode)
                PACK            d10,"03X",ecode
                READ            DcatDesc,d10;catrcrd
                IF              NOT OVER
                chkbk.SetItemText USING tIndex,cat2desc,5
                ELSE
                chkbk.SetItemText USING tIndex,"??",5
                ENDIF
                ENDIF
 
                IF              (chkclr=0)
                chkbk.SetItemCheck USING tindex,1
                ADD             dep,bnkbal
                SUB             pmnt,bnkbal
                ENDIF
                MOVE            dep,d8
                chkbk.SetItemText USING tIndex,d8,6
lvaddDone
                chkbk.EnsureVisible USING tIndex,0
                RETURN

clrchk          ROUTINE         eventresult
                chkbk.GetItemText GIVING d40 USING eventresult,2
                CHOP            d40,d40
                RETURN          IF (d40="") ;29 Dec 2003
                MOVE            d40,Date ;(05xdate)
                chkbk.GetItemText GIVING d40 USING eventresult,3
                CHOP            d40,d40
                MOVE            d40,disc ;(03xdisc)
.
                PACK            d20,"05x",Date
                PACK            d50,"03x",disc
                READ            chkbkdat,d20,d50,actAcntkey;recrd
                RETURN          IF OVER  ;29 Dec 2003
.
                chkbk.GetItemText GIVING d20 USING eventresult,4
                LOOP
                MOVE            pmnt,d40
                BREAK           IF (d40 = d20)
                READKG          chkbkdat;recrd
                RETURN          IF OVER ;29 Dec 2003
                REPEAT
.
. 12 Jul 2005 fixed bug where balance adjustment below was
.   reversed.
.
                chkbk.GetItemCheck GIVING tIndex USING eventresult
                RETURN          IF (tIndex!=chkclr)
                IF              (tIndex)
                CLEAR           chkclr
                SUB             dep,bnkbal
                ADD             pmnt,bnkbal
                ELSE
                SET             chkclr
                ADD             dep,bnkbal
                SUB             pmnt,bnkbal
                ENDIF
                UPDATE          chkbkdat;recrd
.
                MOVE            bnkbal,d10
                SETITEM         EdtBankBal,0,d10
                IF              ( bnkbal < 0 )
                SETPROP         EdtBankBal,FGCOLOR=red
                ELSE
                SETPROP         EdtBankBal,FGCOLOR=black
                ENDIF
                RETURN

AutoCompleteChk
                CALL            AutoComplete USING EdtPayTo
                RETURN

edt             EDITTEXT        ^
AutoComplete    ROUTINE         edt
                GETITEM         Edt,0,d40
                GETITEM         Edt,1,i4
                SETLPTR         d40,i4
                MOVELPTR        d40,len
                IF              (len < 3)
                RETURN
                ENDIF
                PACK            key3,"03L",d40
                TRAP            ignore IF IO
                READLAST        chkbkdat,actAcntkey,key3;recrd
                RETURN          IF OVER
                TRAPCLR         IO
                CHOP            disc,disc
                COUNT           len2,disc
                BUMP            disc,len
                RETURN          IF EOS
                INSERTITEM      Edt,0,disc
                SETITEM         Edt,1,len
                SETITEM         Edt,2,9999
                IF              ( pmnt > "0" )
                MOVE            pmnt,d10
                ELSE
                MOVE            dep,d10
                ENDIF
                INSERTITEM      EdtAmount,0,d10

                MOVE            ecode,d40
                PACK            d10,"03X",d40
                READ            Dcatdesc,d10;catrcrd
                CHOP            catdesc,catdesc
                CCode.FindString GIVING catcode USING CatDesc,seq
                INCR            catcode
                IF              (catcode)
                SETITEM         CCode,0,catcode
                ENDIF
                RETURN

AutoComplete2   ROUTINE         edt
                GETITEM         Edt,0,d40
                GETITEM         Edt,1,i4
                SETLPTR         d40,i4
                MOVELPTR        d40,len
                IF              (len < 3)
                RETURN
                ENDIF
                READKGP         chkbkdat;recrd
                IF              OVER
                PACK            key3,"03L",d40
                TRAP            ignore IF IO
                READLAST        chkbkdat,key3;recrd
                RETURN          IF OVER
                TRAPCLR         IO
                ENDIF
                CHOP            disc,disc
                COUNT           len2,disc
                BUMP            disc,len
                RETURN          IF EOS
                DELETEITEM      edt,1
                INSERTITEM      Edt,1,disc
                IF              ( pmnt > "0" )
                MOVE            pmnt,d10
                ELSE
                MOVE            dep,d10
                ENDIF
                SETITEM         EdtAmount,0,d10

                MOVE            ecode,d40
                PACK            d10,"03X",d40
                READ            Dcatdesc,d10;catrcrd
                CHOP            catdesc,catdesc
                CCode.FindString GIVING catcode USING CatDesc,seq
                INCR            catcode
                IF              (catcode)
                SETITEM         CCode,0,catcode
                ENDIF
                MOVE            len2,pos2
                RETURN

AutoComplete3   ROUTINE         edt
                GETITEM         Edt,0,d40
                GETITEM         Edt,1,i4
                SETLPTR         d40,i4
                MOVELPTR        d40,len
                IF              (len < 3)
                RETURN
                ENDIF
                READKG          chkbkdat;recrd
                IF              OVER
                PACK            key3,"03L",d40
                TRAP            ignore IF IO
                READLAST        chkbkdat,key3;recrd
                RETURN          IF OVER
                TRAPCLR         IO
                ENDIF
                CHOP            disc,disc
                COUNT           len2,disc
                BUMP            disc,len
                RETURN          IF EOS
                DELETEITEM      edt,1
                INSERTITEM      Edt,1,disc
                IF              ( pmnt > "0" )
                MOVE            pmnt,d10
                ELSE
                MOVE            dep,d10
                ENDIF
                SETITEM         EdtAmount,0,d10
.
                MOVE            ecode,d40
                PACK            d10,"03X",d40
                READ            Dcatdesc,d10;catrcrd
                CHOP            catdesc,catdesc
                CCode.FindString GIVING catcode USING CatDesc,seq
                INCR            catcode
                IF              (catcode)
                SETITEM         CCode,0,catcode
                ENDIF
                MOVE            len2,pos2
                RETURN

ignore
                SETFLAG         OVER
                RETURN

redbalance      INIT            ";;;;;;;;2"
yrstartflag     FORM            1
d10a            DIM             10
doBalence
                CLEAR           yrstartflag
                SETPROP         chkbk,AUTOREDRAW=0
                chkbk.GetItemCount GIVING tIndex
                CLEAR           F4,Balence,BNKBAL
                LOOP
                IF              (yrstartflag = 0)
                chkbk.GetItemText GIVING d10 USING F4,3
                IF              (d10 = "year start")
                SET             yrstartflag
                ELSE
.    process previouse years uncleared checks
                chkbk.GetItemCheck GIVING F2 USING F4
                IF              ( F2 )
                chkbk.GetItemText GIVING d10 USING F4,4
                CHOP            d10,d10
                MOVE            d10,f7p2
                ADD             f7p2,BNKBAL
                chkbk.GetItemText GIVING d10 USING F4,6
                CHOP            d10,d10
                MOVE            d10,f7p2
                SUB             f7p2,BNKBAL
                ENDIF
                INCR            F4
                BREAK           IF (F4=tIndex)
                CONTINUE
                ENDIF
                ENDIF
.        
                chkbk.GetItemCheck GIVING F2 USING F4
                chkbk.GetItemText GIVING d10 USING F4,4
                CHOP            d10,d10
                MOVE            d10,f7p2
                SUB             f7p2,Balence
                IF              ( F2 )
                ADD             f7p2,BNKBAL
                ENDIF
                chkbk.GetItemText GIVING d10 USING F4,6
                CHOP            d10,d10
                MOVE            d10,f7p2
                ADD             f7p2,Balence
                IF              ( F2 )
                SUB             f7p2,BNKBAL
                ENDIF
                MOVE            Balence,d10
                chkbk.GetItemText GIVING d10a USING F4,7
                CHOP            d10a
                IF              (d10a != d10 )
                chkbk.SetItemText USING F4,d10,7
                IF              ( BALENCE < 0 )
                chkbk.SetItemText USING F4,redbalance,8 ; negative red
                ELSE
                CLEAR           d10
                chkbk.SetItemText USING F4,d10,8 ; normal
                ENDIF
                ENDIF
                INCR            F4
                BREAK           IF (F4=tIndex)
                REPEAT
                SETPROP         chkbk,AUTOREDRAW=1
.
                MOVE            Balence,d10
                SETITEM         EdtChkBal,0,d10
                IF              ( Balence < 0 )
                SETPROP         EdtChkBal,FGCOLOR=red
                ELSE
                SETPROP         EdtChkBal,FGCOLOR=black
                ENDIF
                ADD             Balence,BNKBAL
                RETURN
 
shareware
                NORETURN
                SETPROP         Form001Shape001,ZORDER=1
                SETPROP         Form001Shape002,ZORDER=1
                SETPROP         Form001Shape003,ZORDER=1
                RETURN

ini             FILE
flposit         FORM            10
SaveCFG
                CLEAR           flposit
                GETITEM         cfgAPRchk,0,ApplyInterest
                OPEN            ini,"plbwin.ini"
                LOOP
                READ            ini,seq;d50
                BREAK           IF OVER
                UPPERCASE       d50
                PARSE           d50,d40,"AZ__=="
                IF              (d40="APPLIY_INTEREST=")
                REPOSIT         ini,flposit
                WRITE           ini,seq;*LL,"Appliy_Interest=",ApplyInterest;
                CLOSE           ini
                RETURN
                ENDIF
                FPOSIT          ini,flposit
                REPEAT
                WRITE           ini,seq;"Appliy_Interest=",ApplyInterest
                CLOSE           ini
                RETURN

row             FORM            10
SrchData        DIM             40
SrchChk
                CLEAR           recrd
                GETITEM         EdtPayTo,0,disc
                IF              (disc="")
                RETURN
                ENDIF
                UPPERCASE       disc
.
                IF              (LastSrcRow="0")
                chkbk.GetItemCount GIVING row
                ELSE
                DECR            LastSrcRow
                IF              ZERO
                chkbk.GetItemCount GIVING row
                ELSE
                MOVE            LastSrcRow,row
                ENDIF
                ENDIF
.
                LOOP
                chkbk.GetItemText GIVING SrchData USING row,3
                UPPERCASE       SrchData
                SCAN            disc,SrchData
                BREAK           IF EQUAL
                DECR            row
                REPEAT          WHILE NOT ZERO
.
                IF              (row="0")
                ALERT           note,"Item Not Found",row,"Search"
                CLEAR           LastSrcRow
                RETURN
                ENDIF
                chkbk.EnsureVisible USING row,0
                chkbk.SetItemState USING row,3,3
                MOVE            row,LastSrcRow
                RETURN

BtnPress        FORM            ^
MousePos        FORM            ^
context         FLOATMENU
contextdat      INIT            "delete;Delete"
mntop           FORM            4
mnleft          FORM            4
LVItem          FORM            10
chkbkContext    ROUTINE         BtnPress,MousePos
                RETURN          IF (BtnPress != 16)
                MOVE            MousePos,mnTOP
                MOVE            (MousePos/10000),mnleft
                chkbk.GetNextItem GIVING LVItem USING LVS_SELECTED,seq
                ADD             "50",mntop
                ADD             "20",mnleft
                CREATE          chkbkWindow;context=mntop:(mntop+1):mnleft:(mnLeft+1),contextdat
                ACTIVATE        context,deletefunc,F2
 
                RETURN

DeleteFunc
                chkbk.GetItemText GIVING d40 USING LVItem,1
                CHOP            d40,d40
                MOVE            d40,chkno
                chkbk.GetItemText GIVING d40 USING LVItem,2
                CHOP            d40,d40
                MOVE            d40,Date
                chkbk.GetItemText GIVING d40 USING LVItem,3
                CHOP            d40,d40
                MOVE            d40,disc
                PACK            d40,"05X",Date
                PACK            d50,"03X",disc

                READ            chkbkdat,d40,d50,actAcntkey;recrd ;valid read req before update
.
                IF              (dep)
                MOVE            dep,f7p2
                ELSE
                MOVE            pmnt,f7p2
                ENDIF
. 
                PACK            d80,chkno," ",date," ",disc," ",f7p2
                ALERT           TYPE=20,d80,F2,"Delete record?"
                IF              (F2="6")
                DELETE          chkbkdat
                chkbk.DeleteItem USING LVItem
                CALL            doBalence
                ENDIF
                RETURN

Transfers       PLFORM          trans.plf
DoTransfer
                FORMLOAD        Transfers
                RETURN

FromAcnt        FORM            2
FromAcntdesc    DIM             40
ToAcnt          FORM            2
ToAcntDesc      DIM             40
TransAmt        FORM            5.2
validate        FORM            5.2
DoTransfer2
                FromAccnt.GetCurSel GIVING FromAcnt
                ToAccnt.GetCurSel GIVING ToAcnt
                FromAccnt.GetText GIVING FromAcntDesc USING FromAcnt
                ToAccnt.GetText GIVING ToAcntDesc USING ToAcnt
                CALL            GetAcntNum USING FromAcntDesc,FromAcnt
                CALL            GetAcntNum USING ToAcntDesc,ToAcnt

                IF              (FromAcnt = ToAcnt)
                ALERT           STOP,"Accounts cannot transfer funds to themselves!",F2,"Selection Error"
                SETFLAG         OVER
                RETURN
                ENDIF
                GETPROP         TransAmnt,VALUE=TransAmt
                IF              (TransAmt="0")
                ALERT           STOP,"You cannot tranfer nothing.",F2,"Amount Invalid"
                SETFLAG         OVER
                RETURN
                ENDIF
                CALL            CheckBalance USING FromAcntDesc,validate
                IF              (TransAmt > validate )
                MOVE            validate,D10
                PARAMTEXT       D10,"","",""
                ALERT           STOP,"Insufficient Funds. ^0 Available.",F2,"Amount Invalid"
                SETFLAG         OVER
                RETURN
                ENDIF
                CLEAR           recrd
                CLOCK           timestamp,ts
                UNPACK          ts,timestampd
                PACK            Date,tsmonth,"/",tsday,"/",tsyear
                PACK            disc,"Transfer to ",ToAcntDesc
                MOVE            TransAmt,pmnt
                MOVE            "99",ecode
                MOVE            FromAcnt,accnt
                SET             tnsfr
                WRITE           chkbkdat;recrd
                RESET           ACTACNTKEY,4
                MOVE            actacntkey,F2
                RESET           actacntkey
                IF              ( accnt = F2 )
                CALL            ADDTOLV
                CALL            DOBALENCE
                ELSE
                SUB             TransAmt,validate
                CALL            UpdateBalance,F2,validate
                ENDIF

                PACK            disc,"Transfer From ",FromAcntDesc
                MOVE            TransAmt,dep
                CLEAR           pmnt
                MOVE            ToAcnt,accnt
                WRITE           chkbkdat;recrd
                RESET           ACTACNTKEY,4
                MOVE            actacntkey,F2
                RESET           actacntkey
                IF              ( accnt = F2 )
                CALL            ADDTOLV
                CALL            DOBALENCE
                ELSE
                ADD             TransAmt,validate
                CALL            UpdateBalance,F2,validate
                ENDIF
                RETURN
