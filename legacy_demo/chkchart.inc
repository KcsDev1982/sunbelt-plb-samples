*****************************************************************************
.Charting and statistics functions
.
.***********************************
Balance         FORM            6.2
.month   DIM 2
.monthkey  DIM 6
#yearkey        DIM             7
pcnt            FORM            3.4
mvalues         FORM            5(12,25)
cvalues         FORM            5(12,25)
#Month_Total_Income FORM        6.2(12)
#Year_Total_Income FORM         6.2
#Month_Balance  FORM            6.2
avg             FORM            6.2
avgtot          FORM            6.2

pichart         RECORD
pcnt            DIM             ^200 
labels          DIM             ^1000 
                RECORDEND

ptotal          FORM            6.2
#sz             FORM            1

#f2             FORM            2
#f4             FORM            4
#f42            FORM            4
#f43            FORM            4
#f44            FORM            4
#f7p2           FORM            7.2
#d10            DIM             ^10
#d20            DIM             ^20
#d40            DIM             ^40


loadchartmod
                CLOCK           timestamp,ts
                UNPACK          ts,timestampd
                MOVE            tsyear,#f4

                SETITEM         EdtSelYear,1,tsyear
                SETPROP         HSYearSel, MIN=mnyear, MAX=#F4
                MOVE            tsyear,#f4
                SETITEM         HSYearSel,0,#f4

                MOVE            tsmonth,#f4
                SETITEM         monthbox,0,#f4

                LOADMOD         "chkbchrt"
                RETURN

getpercents
.year to date
                CLOCK           timestamp,ts
                UNPACK          ts,timestampd

                GETITEM         EdtSelYear,0,tsyear

                MOVE            tsmonth,#f4
                SETITEM         monthbox,0,#f2
                CALL            YearChart
                CALL            MonthChart
                RETURN

YearChart
                CLEAR           pichart,ptotal
                REPOSIT         Dcatdesc,ZERO
                LOOP
                TRAP            nothing IF IO ;just read passed deleted records
                READ            Dcatdesc,seq;catrcrd
                TRAPCLR         IO
                BREAK           IF OVER
                CALL            SetupPiDat USING atotal(catcode),catdesc,#Year_Total_Income
                REPEAT
                CALL            SetupPiY
                GETPROP         Form001Shape002,TOP=#f4,LEFT=#f42,HEIGHT=#f43,WIDTH=#f44
                DIV             "2",#f44
                ADD             #f44,#f42
                DIV             "2",#f43
                ADD             #f43,#f4
                MOVE            "35",#f43
                CALL            "1|chkbchrt;destroychart"
                CALL            "1|chkbchrt;pi" USING totltab,#f4,#f42,#f43,pichart.pcnt,pichart.labels
                RETURN

MonthChart
                MOVE            tsmonth,#f2
                CLEAR           pichart,ptotal
                REPOSIT         Dcatdesc,ZERO
                MOVE            ( #Month_Total_Income(#f2) - #Month_Balance ),#f7p2
                LOOP
                TRAP            nothing IF IO ;just read passed deleted records
                READ            Dcatdesc,seq;catrcrd
                TRAPCLR         IO
                BREAK           IF OVER
                CALL            SetupPiDat USING matotal(catcode),catdesc,#f7p2
                REPEAT

                CALL            SetupPiM

                GETPROP         Form001Shape003,TOP=#f4,LEFT=#f42,HEIGHT=#f43,WIDTH=#f44
                DIV             "2",#f44
                ADD             #f44,#f42
                DIV             "2",#f43
                ADD             #f43,#f4
                MOVE            "35",#f43
                CALL            "2|chkbchrt;destroyChart"
                CALL            "2|chkbchrt;pi" USING totltab,#f4,#f42,#f43,pichart.pcnt,pichart.labels

                RETURN

overbdg         INIT            ";2,,2"
inbdg           INIT            ";1,,1"
gettotals
                CALL            getspan

                GETITEM         EdtSelYear,0,tsyear
                GETITEM         MonthBox,0,#f2
                MOVE            #f2,tsmonth
                REPLACE         " 0",tsmonth
 
                CALL            GetYearTotals
                CLEAR           #f4,avgtot,PTOTAL
. check discard peek value option...
. if not set,
. CLEAR maxval
.
                LOOP
                INCR            #f4
                MOVE            atotal(#f4),#d10
                CALL            getcat USING #f4
                LVExpence.SetItemText USING (#f4-1),#d10,3 ;year to date
.
                MOVE            ((atotal(#f4)-( maxval(#f4) ))/(span-1)),avg
                MOVE            avg,#d10
                ADD             avg,avgtot
                LVExpence.SetItemText USING (#f4-1),#d10,2 ; year avg
. check if over balance
.
                CALL            bdgcheck2 USING #f42,matotal(#f4)
                MOVE            catdesc,#d40
                IF              (#f42="0")
                LVExpence.SetItemText USING (#f4-1),overbdg,4
                ELSE
                LVExpence.SetItemText USING (#f4-1),inbdg,4
                ENDIF
                LVExpence.SetItemText USING (#f4-1),#d40,0
                BREAK           IF (#f4=descCnt)
                REPEAT

. year to date balance
                MOVE            Balance,#d10
                SETITEM         EdtExtra,0,#d10
                IF              ( Balance < 0 )
                SETPROP         EdtExtra,FGCOLOR=red
                ELSE
                SETPROP         EdtExtra,FGCOLOR=black
                ENDIF

. average end of month balance
                MOVE            (Balance/span),avg
                MOVE            avg,#d10
                SETITEM         EdtExtraAVG,0,#d10
                IF              ( avg < 0 )
                SETPROP         EdtExtraAVG,FGCOLOR=red
                ELSE
                SETPROP         EdtExtraAVG,FGCOLOR=black
                ENDIF

. year total income

                MOVE            #Year_Total_Income,#d10
                SETITEM         EdtTotalI,0,#d10

. monthly avg income

                IF              (span > "2")
                MOVE            ( ( #Year_Total_Income - imaxval )/span ),avg
                ELSE
                MOVE            (#Year_Total_Income/span),avg
                ENDIF
                MOVE            avg,#d10
                SETITEM         EdtAVGI,0,#d10

. year total expence

                MOVE            (#Year_Total_Income-Balance),#f7p2
                MOVE            #f7p2,#d10
                SETITEM         ytdTTLEXP,0,#d10

. month avg expence

                IF              (span > "2")
                SUB             emaxval,#f7p2
                DIV             (span-1),#f7p2
                ENDIF
                MOVE            #f7p2,#d10
                SETITEM         avgTTLEXP,0,#d10

. month details..... ( broken )
                CALL            newmonth
                RETURN

GetYearTotals
                CLEAR           #Year_Total_Income,atotal,ptotal
                CLEAR           pichart,maxval,imaxval
                CLEAR           #Month_Total_Income,matotal,#Month_Balance
                CLEAR           emaxval,Balance,mvalues
 
                PACK            #yearkey,"02X",tsyear
                CLEAR           #f4
                PACK            d20,"03Xyear start"   ;26 Mar 2004 get start of
                READLAST        chkbkdat,actAcntkey,d20,#yearkey;; ;specified year
                IF              OVER ; year doesn't have marker...
                REPOSIT         chkbkdat,ZERO
                ENDIF

                BUMP            actAcntkey,3
                MOVE            actAcntkey,F3
                RESET           actAcntkey
 
                LOOP
                READ            chkbkdat,seq;recrd
                BREAK           IF OVER
 
                CONTINUE        IF (accnt != F3)
 
                RESET           Date,7
                IF              ( date = tsyear AND ecode != 0 AND ecode != 99)
.
                ADD             pmnt,atotal(ecode)
                SUB             pmnt,Balance
                RESET           date
                SETLPTR         date,2
                IF              ( date = tsmonth )
                ADD             pmnt,matotal(ecode)
                SUB             pmnt,#Month_Balance
                ENDIF
                MOVE            date,#f2
                ADD             pmnt,mvalues(#F2,ecode)
                IF              ( mvalues(#F2,ecode) > maxval(ecode) )
                MOVE            mvalues(#F2,ecode),maxval(ecode) 
                ENDIF
.
                ELSE            IF ( date = tsyear AND ecode = 0)
.
                ADD             dep,#Year_Total_Income
                ADD             dep,Balance
                IF              (dep > imaxval)
                MOVE            dep,imaxval
                ENDIF
                RESET           date
                SETLPTR         date,2
                IF              ( date = tsmonth )
                ADD             dep,#Month_Balance
                ENDIF
                MOVE            date,#f2
                ADD             dep,#Month_Total_Income(#f2)
.
                ENDIF
                REPEAT

                RETURN

NewMonth
                MOVE            tsmonth,#f2
                CLEAR           ptotal
                REPOSIT         Dcatdesc,ZERO
                LOOP
                TRAP            nothing IF IO ;just read passed deleted records
                READ            Dcatdesc,seq;catrcrd
                TRAPCLR         IO
                BREAK           IF OVER
                MOVE            mvalues(#f2,catcode),matotal(catcode)
                ADD             matotal(catcode),ptotal
                MOVE            matotal(catcode),#d10
                LVExpence.SetItemText USING (catcode-1),#d10,1 ;month total
.
                MOVE            catcode,#f42
                CALL            bdgcheck2 USING #f42,matotal(catcode)
                CHOP            catdesc
                MOVE            catdesc,#d40
                IF              (#f42="0")
                LVExpence.SetItemText USING (catcode-1),overbdg,4
                ELSE
                LVExpence.SetItemText USING (catcode-1),inbdg,4
                ENDIF
                LVExpence.SetItemText USING (catcode-1),#d40,0
                REPEAT

                MOVE            ptotal,#d10
                SETITEM         curTTLEXP,0,#d10

                MOVE            #Month_Total_Income(#f2),#d10
                SETITEM         EdtCurI,0,#d10

                MOVE            (#Month_Total_Income(#f2)-ptotal),#Month_Balance
                MOVE            #Month_Balance,#d10
                SETITEM         EdtExtraCur,0,#d10
                IF              (  #Month_Balance < 0 )
                SETPROP         EdtExtraCur,FGCOLOR=red
                ELSE
                SETPROP         EdtExtraCur,FGCOLOR=black
                ENDIF

                RETURN
 
#d1             DIM             1
linechart
                CLEAR           #f2,#f4
.
                LOOP
                INCR            #f2
                CLEAR           #f4
                LOOP
                INCR            #f4
                LVExpence.GetItemCheck GIVING tIndex USING (#F4-1)
                IF              (tIndex)
                MOVE            mvalues(#f2,#f4),cvalues(#f2,#f4)
                ELSE
                MOVE            "0",cvalues(#f2,#f4)
                ENDIF
                BREAK           IF (#f4=descCnt)
                REPEAT
                BREAK           IF (#f2="12")
                REPEAT

                GETPROP         Form001Shape001,TOP=#f4,LEFT=#f42,HEIGHT=#f43,WIDTH=#f44
                ADD             #f4,#f43
                ADD             #f42,#f44

                CALL            "3|chkbchrt;line" USING totltab,#f4,#f43,#f42,#f44,cvalues

                RETURN

SetupPiY
                MOVE            (Balance/#Year_Total_Income),pcnt
                CALL            CompleatPi
                RETURN

SetupPiM
                MOVE            TSMONTH,#f2
                MOVE            (#Month_Balance/#Month_Total_Income(#f2)),pcnt
                CALL            CompleatPi
                RETURN

CompleatPi
                MULT            "100",pcnt
                ADD             pcnt,ptotal
                APPEND          pcnt,pichart.pcnt
                APPEND          "Excess",pichart.labels
                RESET           pichart.pcnt
                RESET           pichart.labels
                RETURN

cattotal        FORM            ^.
catlabel        DIM             ^ ;20
ttotal          FORM            ^.
SetupPiDat      LROUTINE        cattotal,catlabel,ttotal
                MOVE            (cattotal/ttotal),pcnt
                MULT            "100",pcnt
                ADD             pcnt,ptotal
                APPEND          pcnt,pichart.pcnt
                APPEND          ",",pichart.pcnt
                APPEND          catlabel,pichart.labels
                APPEND          ",",pichart.labels
                RETURN

destroycharts
                CALL            "1|chkbchrt;destroyChart"
                CALL            "2|chkbchrt;destroyChart"
                CALL            "3|chkbchrt;destroyChart"
                RETURN
