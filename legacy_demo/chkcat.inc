*****************************************************************************
.Catagory configuration routines
.
.********************************
.EdtCatDesc
.EdtCatAcode
.EdtCatNcode
.CatSummary

Dcatdesc        AFILE
*
.Dcatdesc is 30 byte records
.
catrcrd         LIST
catdesc         DIM             ^20
cat2desc        DIM             2
catcode         FORM            2
catreserv       DIM             6 ;reserved
                LISTEND

NxtCatCode      FORM            2

#d10            DIM             ^10
#d40            DIM             ^40
#d50            DIM             ^50

#f4             FORM            4
#mod            FORM            1

StartCat
                CLEAR           ftrap
                TRAP            noFile IF IO
                OPEN            Dcatdesc,catagories
                IF              (ftrap)
                PREP            Dcatdesc,catagories,catagories,"U,1-20,21-22,23-24","30"
                MOVE            "Default",catdesc
                MOVE            "df",cat2desc
                SET             catcode
                WRITE           Dcatdesc;catrcrd
                ENDIF
                TRAPCLR         IO
                CALL            LoadCat
                RETURN

CatAdd
                SETPROP         BdgModBtn,ENABLED=0
                GETITEM         EdtCatDesc,0,#d40
                CHOP            #d40,#d40
                RETURN          IF (#d40="")
                GETITEM         EdtCatAcode,0,#d10
                CHOP            #d10,#d10
                RETURN          IF (#d10="")
                CALL            StripLeadingSpcae USING #d10
                CALL            StripLeadingSpcae USING #d40
                MOVE            #d40,Catdesc
                MOVE            #d10,Cat2desc
                MOVE            NxtCatCode,catcode
                INCR            NxtCatCode
                PACK            #d10,"02X",Cat2desc
                READ            Dcatdesc,#d10;#d50
                IF              OVER
                WRITE           Dcatdesc;catrcrd
                ELSE
                ALERT           note,"Alpha code already exists",#f4,"Error"
                RETURN
                ENDIF

                PACKKEY         #d50,catrcrd
                CatSummary.AddString USING #d50
                INSERTITEM      CCode,99,catdesc
                CLEAR           #d10,#d40
                SETITEM         EdtCatDesc,0,#d40
                SETITEM         EdtCatAcode,0,#d10
                RETURN

CatSMod
                CALL            bdgModCncl
                CALL            AcntCnl
                CatSummary.GetCaretIndex GIVING #f4
                CatSummary.GetText GIVING #d50 USING #f4
                CHOP            #d50,#d50
                UNPACK          #d50,catrcrd
                CHOP            CatDesc,CatDesc
                CHOP            Cat2Desc,Cat2Desc
                SETITEM         EdtCatDesc,0,CatDesc
                SETITEM         EdtCatAcode,0,Cat2Desc
                PACK            #d50,"01X",CatDesc
                READ            Dcatdesc,#d50;catrcrd
                SET             #mod
                SETPROP         CatSummary,ENABLED=0
                SETPROP         CatModBtn,ENABLED=1
                MOVE            "Cancel",#d10
                SETITEM         CatRmBtn,0,#d10
                SETFOCUS        EdtCatDesc
                RETURN

CatMod
                GETITEM         EdtCatDesc,0,#d40
                CHOP            #d40,#d40
                RETURN          IF (#d40="")
                GETITEM         EdtCatAcode,0,#d10
                CHOP            #d10,#d10
                RETURN          IF (#d10="")
                CALL            StripLeadingSpcae USING #d10
                CALL            StripLeadingSpcae USING #d40
                MOVE            #d40,Catdesc
                MOVE            #d10,Cat2desc
                UPDATE          Dcatdesc;catrcrd
                PACKKEY         #d50,catrcrd
                CatSummary.GetCaretIndex GIVING #f4
                CatSummary.DeleteString USING #f4
                CatSummary.InsertString USING #d50,#f4
CatCnl
                SETPROP         CatSummary,ENABLED=1
                SETPROP         CatModBtn,ENABLED=0
                MOVE            "Remove",#d10
                SETITEM         CatRmBtn,0,#d10
                CLEAR           #d10,#d40,#mod
                SETITEM         EdtCatDesc,0,#d40
                SETITEM         EdtCatAcode,0,#d10
                RETURN

CatRm
                IF              (#mod)
                CALL            CatCnl
                RETURN
                ENDIF
                CatSummary.GetCaretIndex GIVING #f4
                CatSummary.GetText GIVING #d40 USING #f4
                UNPACK          #d40,catrcrd
                CHOP            CatDesc,CatDesc
                PACK            #d40,"01X",CatDesc
                READ            Dcatdesc,#d40;catrcrd
                DELETE          Dcatdesc
                CatSummary.DeleteString USING #f4
                CatSummary.SetCurSel USING #f4
                SETPROP         BdgModBtn,ENABLED=0
                RETURN

LoadCat
.****LOAD Dynamic catagory discriptions AND expence summary LV****
                DELETEITEM      CCode,0
                DELETEITEM      BCode,0
                CLEAR           descCnt
                SET             NxtCatCode
                REPOSIT         Dcatdesc,ZERO
                TRAP            nothing noreset IF IO ;just read passed deleted records
                LOOP
                READ            Dcatdesc,seq;catrcrd
                BREAK           IF OVER
                IF              (catcode=NxtCatCode)
                INCR            NxtCatCode
                ENDIF
                PACKKEY         #d50,catrcrd
                CatSummary.AddString USING #d50
                CHOP            catdesc,catdesc
                LVExpence.InsertItem USING catdesc,9999
                INSERTITEM      CCode,99,catdesc
                INSERTITEM      BCode,99,catdesc
                INCR            descCnt
                BREAK           IF (descCnt > "50" )
                REPEAT
                TRAPCLR         IO
                RETURN

#Fp             FORM            ^
getcat          ROUTINE         #Fp
                MOVE            #fp,catcode
                PACK            #d40,"03X",catcode
                READ            Dcatdesc,#d40;catrcrd
                CHOP            catdesc,catdesc
                RETURN
