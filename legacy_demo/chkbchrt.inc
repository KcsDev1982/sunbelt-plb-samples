*********************************************************************
.Charts LoadMod
.           Author: Matthew Lake
.    Last Modified: 30 Mar 2004
.
.********************************************************************

*
.Objects etc
.
chart   LINE    (315)
label   STATTEXT (100)
graph	COLLECTION 

dcolor  INTEGER 4
colorchanger	FORM	"8499"

pi      FORM    "3.141592652"
work3   FORM    3.9         ;calculated...number of radiants in a circle

*
.Counters
.
cnt     FORM    3       ;percent counter
cnt2    FORM    3       ;point counter
cnt3    FORM    3       ;label counter for pi chart
lcntr	FORM	3	;label counter (line chart)

*
. work vars for calculated values
.
work    FORM    4.9         ;work varibles used during point calculation
work1   FORM    4.9
work2   FORM    4.9
pcnt    FORM    4         ;percent to draw
strt    FORM    4           ;start drawing at what percent

to      RECORD              ; draw line to this point
x       FORM    4
y       FORM    4
        RECORDEND

savex	FORM	4
savey	FORM	4

*
.Temp vars
.
d1	DIM	1
junk    DIM     80
junk2   DIM     80
junkF	FORM	4.2

*
.Misc
.
labels  FORM    1       ; flag to indicate weather labels are provided
labelp  FORM    3       ; a label point is calculated based 
.                       ; on radius + 30 from the middle of the slice :o)

connect FORM    1           ;connect points =1 slice edge=0
.
        STOP	;Cant Run Directly!!!
.
plist   DIM     ^       ;percent list
llist   DIM     ^       ;label list
radius  FORM    ^       ;radius
cntrx   FORM    ^       ;center X
cntry   FORM    ^       ;center Y
pWin    WINDOW  ^       ; window to draw pi on

pi   ROUTINE pWin,cntrx,cntry,radius,plist,llist
        MOVE    (pi*5.065),work3    ;number of radiants in a circle
        COUNT   cnt,llist
        IF (cnt)
          SET   labels
        ENDIF
        CLEAR   cnt,cnt2,cnt3,dcolor
        LOOP
                MOVE    cnt,strt
.                PARSE   plist,junk,"09.."
.                CHOP    junk,junk
.                MOVE    junk,pcnt
.                BUMP    plist
		EXPLODE	plist,",",junk
.		IF (EOS)
		IF (ZERO)
                MOVE    junk,pcnt
                ENDSET	plist
		  IF (pcnt="0")
		    BREAK
		  ENDIF
		ENDIF
                MOVE    junk,pcnt
                MOVE    (strt+(pcnt/2)),labelp
                MOVE    strt,cnt
                SUB     "1",cnt
                CLEAR   connect
                LOOP
                        INCR    cnt
                        MOVE    ((CNT)/work3),WORK   ;convert % to radiants
.
                        SIN     work,work1           ;calculate points to
                        COS     work,work2
                        MULT    radius,work1            ;convert points to reflect
                        MULT    radius,work2            ;the radius of chart
                        ADD     cntrx,work1        ;and set center
                        ADD     cntry,work2

                        MOVE    work1,to.x           ; save calculated points
                        MOVE    work2,to.y
			MOVE	savex,work1
			MOVE	savey,work2

                        IF (connect)                 ; connect the points?
                          CALL  creatline
			  MOVE	to.x,savex
			  MOVE	to.y,savey
                        ELSE
                          MOVE  cntrx,work1
                          MOVE  cntry,work2
                          ADD   colorchanger, dcolor
                          CALL  creatline
                          SET connect
			  MOVE	to.x,savex
			  MOVE	to.y,savey
                        ENDIF

                        IF (cnt=labelp) ;time to draw label?
			  IF (pcnt>0)
                            MOVE    ((CNT)/work3),WORK    ;calculate points for 
                            SIN     work,work1            ; labels
                            COS     work,work2
                            MULT    (radius+20),work1
                            MULT    (radius+20),work2
                            ADD     cntrx,work1
                            ADD     cntry,work2
                            CALL  creatline
                          ENDIF
                          CALL  putlabel ;we have to call this to incr label cntr
                        ENDIF
                        BREAK IF (cnt>99)
                REPEAT  UNTIL (cnt>=pcnt+strt)
                MOVE  cntrx,work1
                MOVE  cntry,work2
                CALL  creatline              ; draw slice's 2nd edge
        REPEAT UNTIL (pcnt+strt>="100")
END
	Activate graph
        RETURN

creatline
        INCR cnt2
        CREATE  pWin;chart(cnt2)=work1:to.x:work2:to.y:
          BDRCOLOR=dcolor:
          OBJECTID=0:
          ZORDER=31:
          BDRWIDTH=1:
          DRAWMODE=2:
          BDRPATTERN=6
.        ACTIVATE chart(cnt2)
	LISTINS	graph,chart(cnt2)
 RETURN

putlabel
        PACK     junk,pcnt,"% "
        IF (labels)
                ENDSET junk
.                PARSE   llist,junk2,"09azAZ  "
.                BUMP    llist
		EXPLODE	llist,",",junk2
                APPEND  junk2,junk
                RESET   junk
        ENDIF
        CHOP	junk
   IF (pcnt>0)
        INCR cnt3
        IF (cnt<=25)
          CREATE   pWin;label(cnt3)=work1:(work1+13):(work2-5):(work2+100),junk:
	        "'>MS Sans Serif'(8)",ALIGNMENT=2:
	 	ZORDER=31:
	 	BACKSTYLE=2:
	 	USEALTKEY=1

        ELSE IF (cnt>25 && cnt <= 50) 
          CREATE   pWin;label(cnt3)=(work1):(work1+13):(work2-100):(work2),junk:
        	"'>MS Sans Serif'(8)",ALIGNMENT=3:
	 	BACKSTYLE=2:
	 	ZORDER=31:
 		USEALTKEY=1

        ELSE IF (cnt >50 && cnt<=75)
          CREATE   pWin;label(cnt3)=(work1-13):(work1):(work2-100):(work2),junk:
        	"'>MS Sans Serif'(8)",ALIGNMENT=3:
	 	BACKSTYLE=2:
	 	ZORDER=31:
 		USEALTKEY=1

        ELSE IF (cnt >75)
          CREATE   pWin;label(cnt3)=(work1-13):(work1):(work2-5):(work2+100),junk:
	        "'>MS Sans Serif'(8)",ALIGNMENT=2:
	 	BACKSTYLE=2:
 		ZORDER=31:
	 	USEALTKEY=1
        ENDIF
.        ACTIVATE label(cnt3)
	LISTINS	graph,label(cnt3)
   ENDIF
 RETURN

destroyChart        ROUTINE 
	TRAP	nothing	IF OBJECT
	DEACTIVATE graph
	TRAPCLR	OBJECT
	DESTROY	graph
 RETURN

nothing
	NORETURN
 RETURN

grid	FORM	2
.pointx  form    4(12,25)
pointc	FORM	1	;clear line
plista  FORM    ^(12,25)  ; 12 points for 25 catagories
TOP     FORM    4
bottom  FORM    4
LEFT    FORM    4
RIGHT   FORM    4
gh      FORM    4       ;graph hight (all x points must be smaller than this)
gw      FORM    4       ;graph width (all y points must be smaller than this)
maxv    FORM    9.2
SCALE   FORM    8.4     ;how far to scale back numbers to fit in graph
steping FORM    4
last    FORM    4
LINE    ROUTINE pWin,TOP,bottom,LEFT,RIGHT,plista
        CLEAR   cnt,cnt2,maxv,gh,gw,SCALE,steping,dcolor
        MOVE    (bottom - TOP),gh       ;graph hight
        LOOP
                INCR cnt2
                CLEAR cnt
                LOOP
                        INCR cnt
                        IF (plista(cnt,cnt2) > maxv)
                                MOVE plista(cnt,cnt2),maxv
                        ENDIF
                        BREAK IF (cnt="12")
                REPEAT
                BREAK IF (cnt2="25")
        REPEAT
        MOVE    (maxv/gh),SCALE         ;plista(x)*scale= x point
        MOVE    (RIGHT-LEFT),gw
        MOVE    (gw/"12"),steping       ;y points increment by this much
*
.Lets Draw :o)
.
	CALL	destroyChart

        CLEAR   cnt,cnt2,cnt3,grid
        LOOP
                MOVE    bottom,work1
                MOVE    LEFT,work2
                MOVE    (LEFT-steping),last
                ADD	colorchanger, dcolor
                INCR    cnt3
                CLEAR	cnt
                LOOP
                        INCR cnt
                        MOVE    (bottom-(plista(cnt,cnt3)/SCALE)),to.x
                        MOVE    (last+steping),to.y
                        IF ((work1 < bottom ) | (to.x < bottom) | Pointc)
                        	SET	pointc
	                        CALL    creatline
	                ENDIF
	                IF (grid<12)
		                CALL	creatline2
		                INCR	grid
		        ENDIF
                        MOVE    to.x,work1
                        MOVE    to.y,work2
                        MOVE    to.y,last
                        BREAK IF (cnt="12")
                REPEAT
                CLEAR	pointc
                BREAK IF (cnt3="25")
        REPEAT
	MOVE	"1",lcntr
	MOVE	".25",work3
	LOOP
		MOVE	(bottom-(gh*work3)),to.x
		MOVE	to.x,work1
		MOVE	LEFT,to.y
		MOVE	(RIGHT-steping-10),work2
		MOVE	"0000",dcolor
		CALL	creatline

		MOVE	(maxv*work3),junkf
		MOVE	junkf,junk
		LOOP
			MOVE	junk,d1
			BREAK	IF (d1!=" ")
			BUMP	junk
		REPEAT
	        CREATE   pWin;label(lcntr)=work1:(work1+13):(work2+5):(work2+30),junk:
	        	"'>MS Sans Serif'(8)",ALIGNMENT=2,ZORDER=31:
	 		BACKSTYLE=2,USEALTKEY=1
.		ACTIVATE label(lcntr)
		LISTINS	graph,label(lcntr)
		INCR	lcntr

		ADD	".25",work3
		BREAK IF (work3 >="1")
	REPEAT
	RETURN IF (maxv="0")

	MOVE	"1",cnt
	MOVE	maxv,junk
	LOOP
		MOVE	junk,d1
		BREAK	IF (d1!=" ")
		BUMP	junk
	REPEAT
	
	MOVE	TOP,work1
	MOVE	(RIGHT-steping),work2
        CREATE   pWin;label(lcntr)=work1:(work1+13):(work2-5):(work2+20),junk:
	        "'>MS Sans Serif'(8)",ALIGNMENT=2:
	 	BACKSTYLE=2:
	 	ZORDER=31:
	 	USEALTKEY=1
.	ACTIVATE label(lcntr)
	LISTINS	graph,label(lcntr)

	MOVE	"1",cnt
	MOVE	"0",junk
	INCR	lcntr
	
	MOVE	bottom,work1
	MOVE	(RIGHT-steping),work2
        CREATE   pWin;label(lcntr)=work1:(work1+13):(work2-5):(work2+10),junk:
        	"'>MS Sans Serif'(8)",ALIGNMENT=2:
	 	BACKSTYLE=2:
 		ZORDER=31:
 		USEALTKEY=1
.	ACTIVATE label(lcntr)
	LISTINS	graph,label(lcntr)

	Activate graph
 RETURN

gray	INTEGER	4,"0x00AAAAAA"
creatline2
        INCR cnt2
        CREATE  pWin;chart(cnt2)=TOP:bottom:to.y:to.y:
          BDRCOLOR=gray:	;grey devider
          OBJECTID=0:
          ZORDER=31:
          BDRWIDTH=1:
          DRAWMODE=2:
          BDRPATTERN=6
.        ACTIVATE chart(cnt2)
	LISTINS	graph,chart(cnt2)

 RETURN
