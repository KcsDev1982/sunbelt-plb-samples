.routines
.
#d8             DIM             8
#month          DIM             2
#day            DIM             2
#year           DIM             4

#d1             DIM             1
pdim            DIM             ^
StripLeadingSpcae ROUTINE       pdim
                LOOP
                MOVE            pdim,#d1
                BREAK           IF (#d1!=" ")
                BUMP            pdim
                REPEAT
                RETURN

F10             FORM            10
dtstr           DIM             ^
dtval           INTEGER         ^
getDateVal      ROUTINE         dtstr,dtval
                REPLACE         " 0",dtstr
                EXPLODE         dtstr,"/",#month,#day,#year
                PACK            D10,#year,#month,#day
                MOVE            d10,F10
                MOVE            F10,dtval
                RETURN

.********************************************************************

#monthkey       DIM             5
#yearkey        DIM             10
#f2             FORM            2
getspan
                CLOCK           TIMESTAMP,#d8
                UNPACK          #D8,#year,#month,#day
                CLEAR           span
                MOVE            "1",#f2
                LOOP
                MOVE            #f2,tsmonth
                REPLACE         " 0",tsmonth
                PACK            #monthkey,"01X",tsmonth
                PACK            #yearkey,"02X",tsyear
                READ            chkbkdat,#monthkey,#yearkey;recrd
                IF              NOT OVER
                IF              (#year = tsyear AND #month=tsmonth )
                ELSE
                INCR            span ; assume this month isnt finished yet
                ENDIF
                ENDIF
                INCR            #f2
                BREAK           IF ( #f2 > "12" )
                REPEAT
                RETURN
