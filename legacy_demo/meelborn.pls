*............................................................................
.
.Example Program: MEELBORN.PLS
.
.This is a PL/B	implementation of the French touring card game MILLE-BORNES.
.
.Copyright @ 1997, Sunbelt Computer Systems, Inc.
.All Rights Reserved.
............................................................................
DISC	 FILE
VERSION	 INIT	   "15.1"
RELEASE	 INIT	   "27 Oct 92"
MEELBORN INIT	   "MEELSTRT"
CAR	 INIT	   "^"
.
MID	 EQU	   39
.
ALINE	 FORM	   "13"
ACOL	 FORM	   "01"
BLINE	 FORM	   "13"
BCOL	 FORM	   "41"
CFSWT	 FORM	   3
DSCNT	 FORM	   2
CARDS	 INIT	   "ROQJQRSIQISPSMDREPSSJISFRCDGGFBFEHJCHARRBIFJPJQSJQJ":
		   "FSJHFSLJNGJGHROPEPHQPHPRJOPGPQOPSIPJQPQDRGAJQKJEIR"
DECK	 DIM	   101
LETTERS	 DIM	   1(19),("A"):
			 ("B"):
			 ("C"):
			 ("D"):
			 ("E"):
			 ("F"):
			 ("G"):
			 ("H"):
			 ("I"):
			 ("J"):
			 ("K"):
			 ("L"):
			 ("M"):
			 ("N"):
			 ("O"):
			 ("P"):
			 ("Q"):
			 ("R"):
			 ("S")
DRAW	 FORM	   3
*------------------------------------------------------------------------------
. CARD VALUES
.------------------------------------------------------------------------------
. HAZARDS
.
CARDNDX	 INTEGER   1
CARDTYPE DIM	   15(19),("OUT	OF GAS"):
			  ("FLAT TIRE"):
			  ("ACCIDENT"):
			  ("SPEED LIMIT	50"):
			  ("STOP!"):
			  ("GASOLINE"):
			  ("SPARE TIRE"):
			  ("REPAIRS"):
			  ("END	OF LIMIT"):
			  ("ROLL !..."):
			  ("EXTRA TANK"):
			  ("PUNCTURE-PROOF"):
			  ("DRIVING ACE"):
			  ("RIGHT OF WAY"):
			  ("200	MILESTONES"):
			  ("100	MILESTONES"):
			  (" 75	MILESTONES"):
			  (" 50	MILESTONES"):
			  (" 25	MILESTONES")
CNT	 FORM	   2(19),("2"):
			 ("2"):
			 ("2"):
			 ("3"):
			 ("4"):
			 ("6"):
			 ("6"):
			 ("6"):
			 ("6"):
			 ("14"):
			 ("1"):
			 ("1"):
			 ("1"):
			 ("1"):
			 ("4"):
			 ("12"):
			 ("10"):
			 ("10"):
			 ("10")
CNTX	 FORM	   2(19),("2"):
			 ("2"):
			 ("2"):
			 ("3"):
			 ("4"):
			 ("6"):
			 ("6"):
			 ("6"):
			 ("6"):
			 ("14"):
			 ("1"):
			 ("1"):
			 ("1"):
			 ("1"):
			 ("4"):
			 ("12"):
			 ("10"):
			 ("10"):
			 ("10")
CNTPOS	 FORM	   2(19,2),("2"),("18"):
			   ("2"),("19"):
			   ("2"),("20"):
			   ("2"),("21"):
			   ("2"),("22"):
			   ("16"),("18"):
			   ("16"),("19"):
			   ("16"),("20"):
			   ("16"),("21"):
			   ("16"),("22"):
			   ("31"),("18"):
			   ("31"),("19"):
			   ("31"),("20"):
			   ("31"),("21"):
			   ("10"),("24"):
			   ("18"),("24"):
			   ("26"),("24"):
			   ("34"),("24"):
			   ("42"),("24")
.
KEEPCNT	 FORM	   "1"
.
OPER	 FORM	   1
MSTATUS	 DIM	   63
FAST	 DIM	   1
PORT	 FORM	   1
NAME	 DIM	   10(2)
.
SPA	 INIT	   "					    "
NDX1	 INTEGER   1
NDX2	 INTEGER   1
SCORE	 FORM	   6(2)
SCORET	 FORM	   6(2)
XCARDS	 DIM	   7(2)
PLAYER	 FORM	   1
RETRY	 INIT	   "N"
PLAY2	 DIM	   1
.
COND	 DIM	   1(2),("E"),("E")
SL	 DIM	   1(2),("I"),("I")
SAFE	 DIM	   1(2),(" "),(" ")
X200	 FORM	   1(2)
LIMIT	 FORM	   "200"(2)
OLIM	 FORM	   "200"(2)
DIST	 FORM	   4(2)
HAZARD	 INIT	   "ABCE"
REMEDY	 INIT	   "FGHJ"
SAFETY	 INIT	   "KLMN"
MILES	 FORM	   3
HZ	 FORM	   2
HI	 FORM	   2
HM	 FORM	   2
HM1	 FORM	   2
EXT	 INIT	   "NO"
GOAL	 FORM	   " 700"
MESSAGE	 DIM	   32
*------------------------------------------------------------------------------
. WORKING STORAGE
.
DIM1	 DIM	   1
DIM2	 DIM	   2
DIM2A	 DIM	   2
DIM3	 DIM	   3
DIM4	 DIM	   4
DIM10	 DIM	   10
DIM15	 DIM	   15
TIME1	 DIM	   8
FORM1	 FORM	   1
FORM2	 FORM	   2
FORM3	 FORM	   3
FORM4	 FORM	   4
FORM10	 FORM	   10
QUES	 DIM	   3
BRNCH	 FORM	   2
CN	 FORM	   "7"(2)
CARDIN	 DIM	   15
REVR	 FORM	   "0"
*------------------------------------------------------------------------------
. CONSTANTS
.
$0$	 FORM	   "0"
$1$	 FORM	   "1"
$2$	 FORM	   "2"
$19$	 FORM	   "19"
*------------------------------------------------------------------------------
. RANDOM NUMBER	GENERATOR REQUIRES THESE VARIABLES
.
RND	 FORM	   "1234567890"
RX	 FORM	   0.3
RND100	 INIT	   "07849375984839875984893758947893785894798378578584":
		   "39401203984903871734930201848598604932727664584940"
RHH	 FORM	   2
RMM	 FORM	   2
+==============================================================================
. PROGRAM ENTRY	POINT.
.
	 CLOCK	   TIME,TIME1
	 UNPACK	   TIME1,DIM2,DIM1,DIM2A
	 MOVE	   DIM2,RHH
	 MOVE	   DIM2A,RMM
*------------------------------------------------------------------------------
. CHECK	FOR PROPER RELEASE.
.
	 TRAP	   PREP	IF IO
	 OPEN	   DISC,"MEELDATA.TXT"
*------------------------------------------------------------------------------
. ATTEMPT TO READ LAST SHUFFLED	DECK
.
	 READ	   DISC,$1$;CARDS
	 MATCH	   SPA,CARDS
	 CALL	   PREP	IF EQUAL
	 MOVE	   CARDS,DECK
	 CALL	   INIT
*------------------------------------------------------------------------------
. DISPLAY MENU
.
	 DISPLAY *BGCOLOR=*BLACK,*FGCOLOR=*WHITE:
	           *ES,*P=20:2,"MILLE BORNES - THE 1000	MILESTONE GAME.":
		   *P=5:4,"1. AUTOMATIC	PLAYING	OF BOTH	HANDS (DEMO).":
		   *P=5:5,"2. COMPUTER IS YOUR OPPONENT":
		   *P=5:6,"3. EXIT":
		   *P=15:9,"SELECTION :	"
*------------------------------------------------------------------------------
. FIND OUT WHAT	WILL BE	DONE
.
	 LOOP
	   KEYIN     *P=27:9,*+,OPER;
	   BRANCH    OPER OF WHATGAM2,WHATGAM2,EXIT
	 REPEAT
*------------------------------------------------------------------------------
. SEMI RANDOM NUMBER GENERATOR.
.
SEED
	 IF	   ( RMM = 0 )
	   MOVE	     "17",RMM
	 ENDIF
	 RESET	   RND100,RMM
	 MOVE	   RND100,DIM2
	 MOVE	   DIM2,FORM10
	 ADD	   "25",FORM10
	 MOVE	   FORM10,RMM
	 RETURN
*------------------------------------------------------------------------------
. SUBROUTINE TO	DISPLAY	CARD LINE NUMBERS ON THE SCREEN.
.
DIS2
	 DISPLAY   *P=HZ:03,"		CARDS":
		   *P=HZ:04,"1.":
		   *P=HZ:05,"2.":
		   *P=HZ:06,"3.":
		   *P=HZ:07,"4.":
		   *P=HZ:08,"5.":
		   *P=HZ:09,"6.":
		   *P=HZ:10,"7."
	 RETURN
*------------------------------------------------------------------------------
. RANDOM NUMBER	GENERATOR RETURNS .NNN IF RX FORM 0.3
. REQUIRES INITIAL NON-ZERO SEED RND
.
RANDOM
	 MULT	   "357353",RND
	 ADD	   "1",RND
	 MOVE	   RND,DIM15
	 RESET	   DIM15,6
	 MOVE	   DIM15,DIM4
	 CMOVE	   ".",DIM4
	 MOVE	   DIM4,RX
	 RETURN
*------------------------------------------------------------------------------
. SET UP DISK FILE TO SAVE THE CARD DECK FROM ONE GAME TO THE NEXT.
.
PREP 
	 DISPLAY   *ES,*P=10:10,"INITIALIZING WORK FILE."
	 MOVE	   CARDS,DECK
	 PREP	   DISC,"MEELDATA.TXT"
	 WRITE	   DISC,$0$;RELEASE
	 WEOF	   DISC,$2$
INIT
	 WRITE	   DISC,$1$;DECK
	 RETURN
*------------------------------------------------------------------------------
. USER ENTERED '1' or '2'. LET HIM PLAY.
.
WHATGAM2
	 CALL	   SEED
	 ADD	   FORM10,RND
*------------------------------------------------------------------------------
. GET PERSONS NAME IF AUTOMATIC	PLAY OF	BOTH HANDS NOT SPECIFIED.
.
	 IF	   ( OPER = 1 )
	   MOVE	     "A. J. FOYT",NAME(1)
	   MOVE	     "M	ANDRETTI",NAME(2)
	   LOOP
	     KEYIN     *P=5:10,"FAST OR	SLOW GAME (F/S)	? ",*+,*UC,FAST;
	   REPEAT    IF	( FAST != "F" &	FAST !=	"S" )
	 ELSE
	   LOOP
	     KEYIN     *P=5:10,"WHAT IS	YOUR NAME ? ",NAME(1)
	     CALL      SEED
	     ADD       FORM10,RND
	     CMATCH    " ",NAME(1)
	   REPEAT    IF	EOS
	   MOVE	     "COMPUTER",NAME(2)
	   MOVE	     "1",PORT
	 ENDIF
*------------------------------------------------------------------------------
. Return to here to start the next hand	of a tournament.
.
AUTO
	 CALL	   SEED
	 MOVE	   "MEELBORN",MEELBORN
	 MULT	   FORM10,RND
	 CALL	   SEED
	 ADD	   FORM10,RND
*------------------------------------------------------------------------------
. DISPLAY BOARD	AT THIS	TIME.
.
	 DISPLAY   *ES,*WHITE,*P=60:21,"MILLE	BORNES":
		   *P=01:02,"-- PLAYER ## 1 ",*RPTCHAR "-":24,"+-":
		   *P=41:02,"-- PLAYER ## 2 ",*RPTCHAR "-":26:
		   *P=01:03,"CONDITION:	STOP!",*P=MID:03,"| CONDITION: STOP!":
		   *P=01:04,"MILESTONES:    0",*P=MID:04,"| MILESTONES:	   0":
		   *P=MID:05,"|":
		   *P=01:06,"+-SAFETY  AREA-+",*P=MID:06,"| +-SAFETY  AREA-+":
		   *P=MID:07,"|":
		   *P=MID:08,"|":
		   *P=MID:09,"|":
		   *P=MID:10,"|":
		   *GREEN:
	      *P=01:17,*WHITE,"+---",*RED,"HAZARDS":
		      *WHITE,"-------",*YELLOW,"REMEDIES":
		      *WHITE,"-------",*GREEN,"SAFETIES":
		      *WHITE,"-------+":
		   *N,"|",*RED," 2 OUT OF GAS ":
		       *YELLOW," 6 GASOLINE    ":
			*GREEN," 1 EXTRA TANK	  ",*WHITE,"|":
		   *N,"|",*RED," 2 FLAT	TIRE  ":
		       *YELLOW," 6 SPARE TIRE  ":
			*GREEN," 1 PUNCTURE-PROOF ",*WHITE,"|":
		   *N,"|",*RED," 2 ACCIDENT   ":
		       *YELLOW," 6 REPAIRS     ":
			*GREEN," 1 DRIVING ACE	  ",*WHITE,"|":
		   *N,"|",*RED," 3 SPEED LIMIT":
		       *YELLOW," 6 END OF LIMIT":
			*GREEN," 1 RIGHT OF WAY	  ",*WHITE,"|":
		   *N,"|",*RED," 4 STOP	      ":
			*GREEN,"14 ROLL		    #"	 #"   #"":
			*WHITE,"    |":
		  *n,"|",*RPTCHAR "=":16,"DISTANCE CARDS",*RPTCHAR "=":17,"|":
		   *N,"+----200( 4) 100(12)  75(10)  50(10)  25(10)----+":
		   *YELLOW:
		   *P=60:23,"VERSION : ",VERSION:
		   *P=60:24,"RELEASE : ",RELEASE:
		   *GREEN;
	 MOVE	   "19",HZ
	 CALL	   DIS2
	 ADD	   "40",HZ
	 COMPARE   "1",OPER
	 CALL	   DIS2	IF EQUAL
	 DISPLAY   *P=1:12,*EL,"NOW SHUFFLING THE DECK.	PLEASE HAVE":
		   " PATIENCE...",*P=1:11,*EL;
	 PACK	   DECK,SPA,SPA,SPA
*------------------------------------------------------------------------------
. GET ANOTHER CARD FROM	THE PILE.
.
	 LOOP
	   ADD	     "1",DRAW
	   LOOP
	     CALL      RANDOM
	     CALC      FORM10=RX*102
	   REPEAT    IF	( FORM10 < 1 | FORM10 >= 102 )
	   RESET     DECK,FORM10
	   LOOP
	     CMATCH    " ",DECK
	     BREAK     IF EQUAL
	     BUMP      DECK
	     CONTINUE  IF NOT EOS
	     RESET     DECK
	   REPEAT
	   CMOVE     CARDS,DECK
	   BUMP	     CARDS,2
	   IF	     EOS
	     RESET     CARDS,2
	   ENDIF
	   DISPLAY   "*";
	   COMPARE   "80",DRAW
	 REPEAT	   IF LESS
	 RESET	   DECK
	 LOOP
	   CMATCH    " ",DECK
	   IF	     EQUAL
	     ADD       "1",DRAW
	     DISPLAY   "*";
	     CMOVE     CARDS,DECK
	     BUMP      CARDS,2
	   ENDIF
	   BUMP	     DECK
	 REPEAT	   UNTIL EOS
	 RESET	   CARDS
	 RESET	   DECK
	 DISPLAY   *P=1:11,"SHUFFLED",*EL,*P=1:12,*EL
*------------------------------------------------------------------------------
. CUT THE DECK
.
	 CALL	   SEED
	 CLEAR	   CARDS,XCARDS,DRAW,FORM2
	 RESET	   DECK,FORM10
	 APPEND	   DECK,CARDS
	 RESET	   DECK
	 APPEND	   DECK,CARDS
	 RESET	   CARDS
	 MOVE	   CARDS,DECK
	 MOVE	   "3",FORM3
	 MOVE	   " ",DIM1
	 DISPLAY   *P=1:12,"CUT.",*EL
	 CALL	   INIT
*------------------------------------------------------------------------------
. DEAL THE CARDS - STORE HANDS
.
	 LOOP
	   ADD	     "1",FORM2
	   ADD	     "1",DRAW
	   RESET     DECK,DRAW
	   CMOVE     DECK,DIM1
	   COMPARE   "7",FORM2
	   IF	     ( FORM2 < 7 )
	     APPEND    DIM1,XCARDS(1)
	   ELSE
	     APPEND    DIM1,XCARDS(2)
	   ENDIF
	 REPEAT	   IF (	FORM2 <	12 )
	 DISPLAY   *P=1:11,*EL,*N,*EL
	 EXTEND	   XCARDS
	 RESET	   XCARDS
	 MOVE	   "7",CN
.
	 MOVE	   "3",FORM3
	 LOOP
	   MOVE	     XCARDS(1),DIM1
	   SEARCH    DIM1 IN LETTERS(1)	TO $19$	USING CARDNDX
	   ADD	     "1",FORM3
	   DISPLAY   *P=22:FORM3,CARDTYPE(CARDNDX)
	   BUMP	     XCARDS(1)
	   COMPARE   "9",FORM3
	 REPEAT	   IF LESS
	 COMPARE   "1",OPER
	 GOTO	   PLAY	IF NOT EQUAL
.
	 MOVE	   "3",FORM3
	 LOOP
	   MOVE	     XCARDS(2),DIM1
	   SEARCH    DIM1 IN LETTERS(1)	TO $19$	USING CARDNDX
	   ADD	     "1",FORM3
	   DISPLAY   *P=62:FORM3,CARDTYPE(CARDNDX)
	   BUMP	     XCARDS(2)
	   COMPARE   "9",FORM3
	 REPEAT	   IF LESS
	 DISPLAY   *P=1:11,*EL
	 GOTO	   PLAY
*------------------------------------------------------------------------------
. READY	TO START GAME -	YOU GO FIRST.
.
XPLAY2
	 IF	   ( PLAYER = 2	)
*------------------------------------------------------------------------------
. Set up Player	1 to play a card
.
PLAY
	   MOVE	     "1",PLAYER
	   MOVE	     "2",PLAY2
	   MOVE	     "1",NDX1
	   MOVE	     "2",NDX2
	   MOVE	     "1",HI
	 ELSE
*------------------------------------------------------------------------------
. Set up Player	2 to play a card
.
	   MOVE	     "2",PLAYER
	   MOVE	     "1",PLAY2
	   MOVE	     "2",NDX1
	   MOVE	     "1",NDX2
	   MOVE	     "41",HI
	 ENDIF
*------------------------------------------------------------------------------
. DRAW A CARD FROM THE DECK
.
XDRAW
	 ADD	   "1",CFSWT
	 BRANCH	   REVR	OF ENDGAME1,ENDGAME1,END
	 RESET	   XCARDS(NDX1),CN(NDX1)
	 IF	   ( DRAW >= 101 )
	   CLEAR     FORM1
	   RESET     XCARDS(NDX1)
	   LOOP
	     CMATCH    " ",XCARDS(NDX1)
	     IF	       NOT EQUAL
	       ADD	 "1",FORM1
	     ENDIF
	     BUMP      XCARDS(NDX1)
	   REPEAT    IF	NOT EOS
	   ADD	     "27",HI,HZ
	   DISPLAY   *P=HZ:3,FORM1," CARDS"
	   GOTO	     PLAYX
	 ENDIF
	 ADD	   "1",DRAW
	 MOVE	   DRAW,FORM3
	 MOVE	   "11",HZ
	 IF	   ( DRAW > 50 )
	   SUBTRACT  "50",FORM3
	   ADD	     "1",HZ
	 ENDIF
	 IF	   ( DRAW = 50 )
	   DISPLAY   *P=54:11,"HALF DECK DEALT."
	 ELSE IF   ( DRAW = 101	)
	   DISPLAY   *P=54:11,*EL,*P=54:12,"ALL	101 CARDS DEALT."
	 ENDIF
	 DISPLAY   *P=FORM3:HZ,"X",*P=52:HZ,"<"
	 RESET	   DECK,DRAW
	 MOVE	   DECK,DIM1
	 CMOVE	   DIM1,XCARDS(NDX1)
*------------------------------------------------------------------------------
. Show card drawn if proper player or if demo game.
.
	 IF	   ( OPER = 1 |	PORT = PLAYER )
	   SEARCH    DIM1 IN LETTERS(1)	TO $19$	USING CARDNDX
	   ADD	     "3",CN(NDX1),FORM3
	   ADD	     "21",HI,HZ
	   DISPLAY   *P=HZ:FORM3,CARDTYPE(CARDNDX)
	 ENDIF
PLAYX
	 RESET	   XCARDS
	 CMOVE	   "N",RETRY
	 CLOCK	   TIME,TIME1
	 IF	   ( XCARDS(1) = "	 " & XCARDS(2) = "	 " )
	   GOTO	     ENDGAME
	 ENDIF
	 MATCH	   "	   ",XCARDS(NDX1)
	 GOTO	   XPLAY2 IF EQUAL
	 IF	   ( OPER = 1 )
	   MOVE	     PLAYER,PORT
	 ENDIF
	 DISPLAY   *P=HI:1,SPA,*P=HI:1,NAME(PLAYER),*P=1:11,TIME1
	 RESET	   SAFE(NDX1),4
	 CMATCH	   "N",SAFE(NDX1)
	 GOTO	   LIMX	IF NOT EQUAL
	 CMATCH	   "J",COND(NDX1)
	 GOTO	   LIMX	IF EQUAL
	 CMATCH	   "E",COND(NDX1)
	 GOTO	   LIMX	IF LESS
	 CMATCH	   "I",COND(NDX1)
	 GOTO	   LIMX	IF NOT LESS
	 MOVE	   "J",COND(NDX1)
	 ADD	   "11",HI,HZ
	 DISPLAY   *P=HZ:3,"ROLL !...	    "
*------------------------------------------------------------------------------
. PLAY A CARD
.
LIMX
	 ADD	   "10",HI,HZ
	 ADD	   "18",HI,HM
	 BRANCH	   OPER	OF APLAY
	 COMPARE   "2",PLAYER
	 GOTO	   APLAY IF EQUAL
	 LOOP
	   KEYIN     *P=HZ:1," - CARD NUMBER: ",*+,FORM1;
	 REPEAT	   IF (	FORM1 <	1 )
*------------------------------------------------------------------------------
. PROCESS CARD INTENDED	TO BE PLAYED
.
GOTCRD
	 COMPARE   "8",FORM1
	 GOTO	   LIMX	IF NOT LESS
	 MOVE	   FORM1,CN(NDX1)
	 RESET	   XCARDS(NDX1),CN(NDX1)
	 CMATCH	   " ",XCARDS(NDX1)
	 GOTO	   PLAYX IF EQUAL
	 MOVE	   XCARDS(NDX1),DIM1
	 SEARCH	   DIM1	IN LETTERS(1) TO $19$ USING CARDNDX
	 MOVE	   CARDTYPE(CARDNDX),CARDIN
*------------------------------------------------------------------------------
. GO TO	SPECIFIC CARD ROUTINES
.
	 BRANCH	   CARDNDX OF ACOM,BCOM,CCOM,DCOM,ECOM,FCOM,GCOM:
			      HCOM,ICOM,JCOM,KCOM,KCOM,KCOM,KCOM:
			      OCOM,OCOM,OCOM,OCOM,OCOM
ACOM
	 RESET	   SAFE(NDX2)
	 CMATCH	   SAFE(NDX2),"K"
	 GOTO	   INV IF EQUAL
	 GOTO	   TAG
BCOM
	 RESET	   SAFE(NDX2),2
	 CMATCH	   "L",SAFE(NDX2)
	 GOTO	   INV IF EQUAL
	 GOTO	   TAG
CCOM
	 RESET	   SAFE(NDX2),3
	 CMATCH	   "M",SAFE(NDX2)
	 GOTO	   INV IF EQUAL
	 GOTO	   TAG
ECOM
	 RESET	   SAFE(NDX2),4
	 CMATCH	   "N",SAFE(NDX2)
	 GOTO	   INV IF EQUAL
*------------------------------------------------------------------------------
. CHANGE OPPONENT'S CONDITION
.
TAG
	 CMATCH	   "J",COND(NDX2)
	 GOTO	   INV IF NOT EQUAL
	 MOVE	   DIM1,COND(NDX2)
	 CLEAR	   CFSWT
	 CALC	   HZ=53-HI
	 DISPLAY   *P=HZ:3,CARDIN
*------------------------------------------------------------------------------
. REMOVE CARD FROM YOUR	HAND
.
DISCRD
	 RESET	   XCARDS(NDX1),CN(NDX1)
	 CMOVE	   " ",XCARDS(NDX1)
	 COMPARE   "1",KEEPCNT
	 CALL	   UPDCARD IF EQUAL
    	 IF	   ( DRAW >= 101 )
	   ADD	     "1",DSCNT
	 ENDIF
	 IF	   ( PORT = PLAYER )
	   ADD	     "3",CN(NDX1),FORM3
	   ADD	     "20",HI,HZ
	   DISPLAY   *P=HZ:FORM3,"		 "
	 ENDIF
	 CMATCH	   "Y",RETRY
	 GOTO	   XPLAY2 IF NOT EQUAL
	 GOTO	   XDRAW
*------------------------------------------------------------------------------
. CARD CHOSEN CAN'T BE PLAYED
.
INV
	 DISPLAY   *P=HI:1,SPA,*P=HI:1,CARDIN,"	DISCARD	(Y\N) ";
	 ADD	   "30",HI,HZ
	 ADD	   "25",HI,HM
	 ADD	   "27",HI,HM1
	 IF	   ( OPER = 2 &	( PORT = PLAYER	| PLAYER != 2 )	)
	   LOOP
	     KEYIN     *P=HZ:1,"? ",*+,*UC,DIM1;
	   REPEAT    IF	( DIM1 != "Y" &	DIM1 !=	"N" )
	   CMATCH    "N",DIM1
	   GOTO	     PLAYX IF EQUAL
	 ENDIF
	 GOTO	   DISCRD
DCOM
	 MOVE	   "50",MILES
	 RESET	   SAFE(NDX2),4
	 CMATCH	   "N",SAFE(NDX2)
	 GOTO	   INV IF EQUAL
	 CMATCH	   "D",SL(NDX2)
	 GOTO	   INV IF EQUAL
	 COMPARE   MILES,LIMIT(NDX2)
	 GOTO	   INV IF LESS
	 CMOVE	   "D",SL(NDX2)
	 CLEAR	   CFSWT
	 MOVE	   MILES,LIMIT(NDX2)
	 CALC	   HZ=42-HI
	 DISPLAY   *P=HZ:5,"SPEED LIMIT: ",LIMIT(NDX2)
	 GOTO	   DISCRD
FCOM
	 CMATCH	   "A",COND(NDX1)
	 GOTO	   FIXA	IF EQUAL
	 GOTO	   INV
GCOM
	 CMATCH	   "B",COND(NDX1)
	 GOTO	   FIXA	IF EQUAL
	 GOTO	   INV
HCOM
	 CMATCH	   "C",COND(NDX1)
	 GOTO	   FIXA	IF EQUAL
	 GOTO	   INV
JCOM
	 CMATCH	   "E",COND(NDX1)
	 GOTO	   INV IF LESS
	 CMATCH	   "I",COND(NDX1)
	 GOTO	   INV IF NOT LESS
*------------------------------------------------------------------------------
. CHANGE YOUR CONDITION
.
FIXA
	 MOVE	   DIM1,COND(NDX1)
	 ADD	   "11",HI,HZ
	 DISPLAY   *P=HZ:3,CARDIN
	 RESET	   SAFE(NDX1),4
	 CMATCH	   "N",SAFE(NDX1)
	 GOTO	   DISCRD IF NOT EQUAL
	 MOVE	   "J",COND(NDX1)
	 DISPLAY   *P=HZ:3,"ROLL !...	  "
	 GOTO	   DISCRD
ICOM
	 CMATCH	   "I",SL(NDX1)
	 GOTO	   INV IF EQUAL
	 COMPARE   LIMIT(NDX1),OLIM(NDX1)
	 GOTO	   INV IF LESS
	 DISPLAY   *P=HI:5,*RPTCHAR " ":16
	 CMOVE	   "I",SL(NDX1)
	 CLEAR	   FORM2
EOL
	 MOVE	   OLIM(NDX1),LIMIT(NDX1)
	 CALL	   LIMIT
	 GOTO	   DISCRD
KCOM
	 MOVE	   "1",FORM2
	 CMOVE	   "Y",RETRY
	 RESET	   SAFETY
	 ADD	   "100",SCORE(NDX1)
MATS
	 CMATCH	   DIM1,SAFETY
	 GOTO	   DISSA IF EQUAL
	 ADD	   "1",FORM2
	 BUMP	   SAFETY
	 GOTO	   MATS	IF NOT EOS
	 GOTO	   INV
DISSA
	 RESET	   HAZARD,FORM2
	 CMATCH	   COND(NDX1),HAZARD
	 IF	   EQUAL
	   MOVE	     "J",COND(NDX1)
	   ADD	     "11",HI,HZ
	   DISPLAY   *P=HZ:3,"ROLL !...	      "
	 ELSE
	   MATCH     "N",DIM1
	   GOTO	     DISER IF NOT EQUAL
	   CMATCH    "D",SL(NDX1)
	   GOTO	     DISER IF NOT EQUAL
	   MOVE	     OLIM(NDX1),LIMIT(NDX1)
	   CALL	     LIMIT
	 ENDIF
	 BEEP
	 COMPARE   "1",CFSWT
	 GOTO	   DISER IF NOT	EQUAL
	 DISPLAY   *P=HI:1,SPA,*P=HI:1,*+,NAME(PLAYER):
		    " SCORES A	COUP FOURRE !!!",*W
	 ADD	   "300",SCORE(NDX1)
DISER
	 RESET	   SAFE(NDX1),FORM2
	 CMOVE	   DIM1,SAFE(NDX1)
	 IF	   ( FORM2 >= 4	)
	   CMOVE     "I",SL(NDX1)
	   DISPLAY   *P=HI:10,CARDTYPE(14):
		     *P=HI:5,*RPTCHAR "	":16
	   GOTO	     EOL
	 ENDIF
	 ADD	   "6",FORM2
	 DISPLAY   *P=HI:FORM2,CARDIN
	 GOTO	   DISCRD
*------------------------------------------------------------------------------
. PROCESS MILESTONE CARDS
.
OCOM
	 MOVE	   CARDIN,DIM3
	 MOVE	   DIM3,MILES
	 CMATCH	   "J",COND(NDX1)
	 GOTO	   INV IF NOT EQUAL
	 COMPARE   MILES,LIMIT(NDX1)
	 GOTO	   INV IF LESS
	 ADD	   DIST(NDX1),MILES,FORM10
	 COMPARE   FORM10,GOAL
	 GOTO	   INV IF LESS
	 IF	   ( MILES = 200 )
	   COMPARE   "2",X200(NDX1)
	   GOTO	     INV IF NOT	LESS
	   ADD	     "1",X200(NDX1)
	 ENDIF
	 MOVE	   FORM10,DIST(NDX1)
	 IF	   ( PLAYER = 1	)
	   DISPLAY   *P=ACOL:ALINE,DIM3
	   ADD	     "1",ALINE
	   IF	     ( ALINE = 16 )
	     MOVE      "13",ALINE
	     ADD       "4",ACOL
	   ENDIF
	 ELSE
	   DISPLAY   *P=BCOL:BLINE,DIM3
	   ADD	     "1",BLINE
	   IF	     ( BLINE = 16 )
	     MOVE      "13",BLINE
	     ADD       "4",BCOL
	   ENDIF
	 ENDIF
	 ADD	   "12",HI,HZ
	 DISPLAY   *P=HZ:4,DIST(NDX1)
	 CALL	   LIMIT
	 COMPARE   GOAL,DIST(NDX1)
	 GOTO	   DISCRD IF LESS
	 COMPARE   "1000",GOAL
	 GOTO	   ENDGAME IF EQUAL
	 IF	   ( OPER = 1 )
	   MOVE	     "Y",DIM1
	 ENDIF
	 IF	   ( OPER = 1 |	PLAYER = 2 )
	   IF	     ( DIST(NDX2) = 0 |	DRAW > 99 )
	     MOVE      "N",DIM1
	   ELSE
	     DISPLAY   *P=HI:01,*EL,"COMPUTER WISHES AN	EXTENSION !",*W
	     MOVE      "Y",DIM1
	   ENDIF
	 ELSE
	   ADD	     "24",HI,HM
	   ADD	     "26",HI,HM1
	   LOOP
	     KEYIN     *P=HI:01,*EL,"EXTEND GAME TO 1000 M. (Y/N) ? ":
		       *+,*UC,DIM1
	   REPEAT    IF	( DIM1 != "Y" &	DIM1 !=	"N" )
	 ENDIF
	 CMATCH	   "N",DIM1
	 GOTO	   ENDGAME IF EQUAL
	 PACK	   EXT,DIM1,PLAYER
	 MOVE	   "1000",GOAL
	 MOVE	   "200",OLIM
	 MOVE	   "50",LIMIT
	 IF	   ( "D" = SL(NDX1) )
	   DISPLAY   *P=HI:5,"SPEED LIMIT: ",LIMIT(NDX1)
	 ELSE
	   MOVE	     "200",LIMIT(NDX1)
	   DISPLAY   *P=HI:5,*RPTCHAR "	":16
	 ENDIF
	 CALL	   LIMIT
	 IF	   ( "D" != SL(NDX2) )
	   MOVE	     "200",LIMIT(NDX2)
	   CALC	     HZ=42-HI
	   DISPLAY   *P=HZ:5,*RPTCHAR "	":16
	 ENDIF
	 GOTO	   DISCRD
+==============================================================================
. END OF GAME  -  COMPUTE SCORES
.
ENDGAME
	 MOVE	   "	   ",XCARDS
	 DISPLAY   *ES," C A L C U L A T I N G	 S C O R E S   A T   T H I S":
		   "   T I M E"
	 MOVE	   "1",REVR
	 COMPARE   "1",PLAYER
	 GOTO	   XPLAY2 IF NOT EQUAL
ENDGAME1
	 CALL	   SCORE
	 ADD	   "1",REVR
	 GOTO	   XPLAY2
*------------------------------------------------------------------------------
. DISPLAY WINNING PLAYER'S NAME
.
END
	 MOVE	   "1",FORM1
	 COMPARE   SCORET(1),SCORET(2)
	 IF	   EQUAL
	   DISPLAY   *P=1:12,*+,"** TIE	**";
	 ELSE
	   IF	     LESS
	     DISPLAY   *P=1:12,*+,NAME(1);
	     COMPARE   "5000",SCORET(1)
	     GOTO      TOURNOVR	IF NOT LESS
	   ELSE
	     DISPLAY   *P=1:12,*+,NAME(2);
	     COMPARE   "5000",SCORET(2)
	     GOTO      TOURNOVR	IF NOT LESS
	     MOVE      "2",FORM1
	   ENDIF
	   DISPLAY   *P=12:12,"	IS WINNING THE TOURNAMENT!";
	 ENDIF
	 LOOP
	   KEYIN     *P=41:12,"CONTINUE	THIS TOURNAMENT	(Y/N) ?	",*+,*UC,DIM1;
	 REPEAT	   IF (	DIM1 !=	"Y" & DIM1 != "N" )
	 CMATCH	   "N",DIM1
	 GOTO	   TOURNOVR IF EQUAL
	 CALL	   CLEAR
	 GOTO	   AUTO
TOURNOVR
	 DISPLAY   *B,*P=12:12,*EL," WON THE TOURNAMENT!!!!!"
	 LOOP
	   KEYIN     *P=41:12,"PLAY ANOTHER GAME (Y/N) ? ",*+,DIM1
	 REPEAT	   IF (	DIM1 !=	"Y" & DIM1 != "N" )
	 CMATCH	   "Y",DIM1
	 GOTO	   EXIT	IF NOT EQUAL
	 TRAP	   TOURNCF IF CFAIL
	 CHAIN	   "MEELBORN"
TOURNCF
	 DISPLAY   *N,"PROGRAM NOT FOUND"
EXIT
	 SHUTDOWN
*------------------------------------------------------------------------------
. CHECK	SPEED LIMIT
.
LIMIT
	 IF	   ( X200(NDX1)	> 1 )
	   MOVE	     "100",OLIM(NDX1)
	   IF	     ( LIMIT(NDX1) > 100 )
	     MOVE      "100",LIMIT(NDX1)
	   ENDIF
	 ENDIF
	 SUBTRACT  DIST(NDX1),GOAL,FORM10
	 COMPARE   LIMIT(NDX1),FORM10
	 IF	   LESS
	   MOVE	     FORM10,LIMIT(NDX1)
	   MOVE	     FORM10,OLIM(NDX1)
	   DISPLAY   *P=HI:5,"DIST. TO GO: ",LIMIT(NDX1)
	 ENDIF
	 RETURN
+==============================================================================
. SCORING ROUTINE
.
SCORE
	 DISPLAY   *P=HI:2,"Safeties":
		   *P=HI:3,"All	Safeties":
		   *P=HI:4,"Trip Completed":
		   *P=HI:5,"Bonus for Extension":
		   *P=HI:6,"Delayed Action":
		   *P=HI:7,"Safe Trip":
		   *P=HI:8,"Shut-out":
		   *P=HI:9,"Milestones":
		   *P=HI:10,"GAME TOTALS":
		   *P=HI:11,"TOURNAMENT	TOTALS";
.
	 ADD	   "19",HI,FORM2
	 IF	   ( SCORE(NDX1) > 0 )
	   DISPLAY   *P=FORM2:2,SCORE(NDX1);
	 ENDIF
*------------------------------------------------------------------------------
. CHECK	FOR ALL	SAFETIES.
.
	 RESET	   SAFETY
	 RESET	   SAFE(NDX1)
	 IF	   ( SAFETY = SAFE(NDX1) )
	   DISPLAY   *P=FORM2:3,"   300";
	   ADD	     "300",SCORE(NDX1)
	 ENDIF
*------------------------------------------------------------------------------
. CHECK	FOR COMPLETED TRIP.
.
	 IF	   ( GOAL = DIST(NDX1) )
	   DISPLAY   *P=FORM2:4,"   400";
	   ADD	     "400",SCORE(NDX1)
	 ENDIF
*------------------------------------------------------------------------------
. CHECK	FOR EXTENSION.
.
	 IF	   ( EXT != "N"	)
	   BUMP	     EXT
	   MOVE	     PLAYER,DIM1
	   IF	     ( ( DIM1  = EXT & DIST(NDX1)  = 1000 ):
		     | ( DIM1 != EXT & DIST(NDX2) != 1000 ) )
	     DISPLAY   *P=FORM2:5,"   200";
	     ADD       "200",SCORE(NDX1)
	   ENDIF
	 ENDIF
*------------------------------------------------------------------------------
. CHECK	FOR DELAYED GAME.
.
	 IF	   ( DRAW > 100	& DIST(NDX1) = GOAL )
	   DISPLAY   *P=FORM2:6,"   300";
	   ADD	     "300",SCORE(NDX1)
	 ENDIF
*------------------------------------------------------------------------------
. CHECK	FOR SAVE TRIP.
.
	 IF	   ( X200(NDX1)	= 0 & DIST(NDX1) = GOAL	)
	   DISPLAY   *P=FORM2:7,"   300";
	   ADD	     "300",SCORE(NDX1)
	 ENDIF
*------------------------------------------------------------------------------
. CHECK	FOR SHUTOUT.
.
	 IF	   ( DIST(NDX2)	= 0 )
	   DISPLAY   *P=FORM2:8,"   500";
	   ADD	     "500",SCORE(NDX1)
	 ENDIF
*------------------------------------------------------------------------------
. ADD IN DISTANCE SCORES.
.
	 DISPLAY   *P=FORM2:9,"	 ",DIST(NDX1);
	 ADD	   DIST(NDX1),SCORE(NDX1)
	 ADD	   SCORE(NDX1),SCORET(NDX1)
	 DISPLAY   *P=FORM2:10,SCORE(NDX1):
		   *P=FORM2:11,SCORET(NDX1);
	 RETURN
+==============================================================================
. FIRST	LINE OF	AUTOMATIC PLAY
. DETERMINE WHICH CARD TO PLAY
.
APLAY
	 IF	   ( OPER != 1 & FAST =	"F" )
	   DISPLAY   *W,*W;
	 ENDIF
	 COMPARE   "3",DSCNT
	 GOTO	   DISCARDQ IF NOT LESS
	 CMATCH	   "D",SL(NDX1)
	 GOTO	   LO9 IF NOT EQUAL
	 MOVE	   "N01",QUES
	 GOTO	   HAND
LO9
	 CMATCH	   "J",COND(NDX2)
	 GOTO	   LO8 IF NOT EQUAL
	 RESET	   SAFE(NDX2),4
	 CMATCH	   "N",SAFE(NDX2)
	 GOTO	   LO8 IF EQUAL
	 MOVE	   "E02",QUES
	 GOTO	   HAND
LO8
	 RESET	   XCARDS
	 RESET	   HAZARD
	 RESET	   SAFETY
	 RESET	   REMEDY
	 CMATCH	   "J",COND(NDX1)
	 GOTO	   OPPO	IF EQUAL
*------------------------------------------------------------------------------
. IF YOU HAVE A	HAZARDOUS CONDITION - CHECK FOR	SAFETY OR REMEDY
.
HAZ
	 CMATCH	   COND(NDX1),HAZARD
	 GOTO	   HAZ1	IF EQUAL
	 CMATCH	   COND(NDX1),REMEDY
	 GOTO	   ROLLCR IF EQUAL
GVB
	 BUMP	   HAZARD
	 BUMP	   SAFETY
	 BUMP	   REMEDY
	 GOTO	   HAZ IF NOT EOS
	 GOTO	   OPPO
ROLLCR
	 MOVE	   "J03",QUES
	 GOTO	   HAND
*------------------------------------------------------------------------------
. HAZARD CONDITION
.
HAZ1
	 MOVE	   SAFETY,QUES
	 RESET	   QUES
	 APPEND	   "04",QUES
	 GOTO	   HAND
HA04
	 MOVE	   REMEDY,QUES
	 RESET	   QUES
	 APPEND	   "05",QUES
	 GOTO	   HAND
*------------------------------------------------------------------------------
. NO REMEDY FOR	YOUR HAZARD
. CHECK	FOR PLAYING HAZARD AGAINST OPPONENT
.
OPPO
	 CMATCH	   "J",COND(NDX2)
	 GOTO	   ATA IF EQUAL
	 CMATCH	   "J",COND(NDX1)
	 GOTO	   MILEST IF EQUAL
	 GOTO	   DISCARD
ATA
	 RESET	   XCARDS
	 RESET	   HAZARD
	 RESET	   SAFETY
	 RESET	   SAFE(NDX2)
	 LOOP
	   MOVE	     "1",FORM1
	   LOOP
	     CMATCH    HAZARD,XCARDS(NDX1)
	     IF	       EQUAL
	       CMATCH	 SAFETY,SAFE(NDX2)
	       GOTO	 GOTCRD	IF NOT EQUAL
	     ENDIF
	     ADD       "1",FORM1
	     BUMP      XCARDS(NDX1)
	   REPEAT    IF	NOT EOS
	   RESET     XCARDS(NDX1)
	   BUMP	     SAFETY
	   BUMP	     SAFE(NDX2)
	   BUMP	     HAZARD
	 REPEAT	   IF NOT EOS
	 CMATCH	   "D",SL(NDX2)
	 GOTO	   RETES IF EQUAL
	 MOVE	   "D06",QUES
	 GOTO	   HAND
RETES
	 CMATCH	   "J",COND(NDX1)
	 GOTO	   MILEST IF EQUAL
*------------------------------------------------------------------------------
. NO PLAY
.
DISCARD
	 CLEAR	   FORM1
*------------------------------------------------------------------------------
. TRY TO PLAY SPEED LIMIT
.
	 CMATCH	   "D",SL(NDX2)
	 GOTO	   RESETXX IF EQUAL
	 RESET	   SAFE(NDX2),4
	 CMATCH	   "N",SAFE(NDX2)
	 GOTO	   RESETXX IF EQUAL
	 MOVE	   "D07",QUES
	 GOTO	   HAND
RESETXX
	 IF	   ( SL(NDX1) != "D" )
	   RESET     SAFE(NDX1),4
	   CMATCH    "N",SAFE(NDX1)
	   GOTO	     RZER IF NOT EQUAL
	 ENDIF
*------------------------------------------------------------------------------
. TRY TO PLAY END OF LIMIT
.
	 MOVE	   "I08",QUES
	 GOTO	   HAND
*------------------------------------------------------------------------------
. THROW	AWAY HAZARDS WHICH HAVE	BEEN PREVENTED BY OPPONENT'S SAFETY CARD
.
RZER
	 RESET	   HAZARD
	 RESET	   SAFE(NDX2)
	 RESET	   SAFE(NDX1),4
	 CMATCH	   "N",SAFE(NDX1)
	 GOTO	   BNM IF NOT EQUAL
	 MOVE	   "J09",QUES
	 GOTO	   HAND
BNM
	 CMATCH	   " ",SAFE(NDX2)
	 GOTO	   BNMP	IF EQUAL
	 MOVE	   HAZARD,QUES
	 RESET	   QUES
	 APPEND	   "10",QUES
	 GOTO	   HAND
BNMP
	 BUMP	   HAZARD
	 BUMP	   SAFE(NDX2)
	 GOTO	   BNM IF NOT EOS
	 RESET	   SAFE(NDX1)
	 RESET	   SAFETY
	 RESET	   REMEDY
*------------------------------------------------------------------------------
. THROW	AWAY REMEDIES FOR YOUR SAFETIES
.
	 LOOP
	   CMATCH    SAFETY,SAFE(NDX1)
	   IF	     EQUAL
	     MOVE      REMEDY,QUES
	     RESET     QUES
	     APPEND    "13",QUES
	     GOTO      HAND
	   ENDIF
HY7
	   BUMP	     SAFE(NDX1)
	   BUMP	     SAFETY
	   BUMP	     REMEDY
	 REPEAT	   IF NOT EOS
*------------------------------------------------------------------------------
. CHECK	FOR REMEDIES MATCHING SAFETIES IN YOUR HAND
.
	 RESET	   SAFETY
	 RESET	   REMEDY
	 RESET	   XCARDS
	 CLEAR	   FORM2
*------------------------------------------------------------------------------
JUN3B
	 LOOP
	   ADD	     "1",FORM2
	   COMPARE   "8",FORM2
	   BREAK     IF	NOT LESS
	   RESET     XCARDS(NDX1),FORM2
	   LOOP
	     CMATCH    XCARDS(NDX1),SAFETY
	     IF	       EQUAL
*------------------------------------------------------------------------------
. I HAVE A SAFETY - CHECK FOR MATCHING REMEDY
.
	       MOVE	REMEDY,QUES
	       RESET	 QUES
	       APPEND	 "27",QUES
	       GOTO	 HAND
	     ENDIF
	     BUMP      SAFETY
	     BUMP      REMEDY
	   REPEAT    IF	NOT EOS
	   RESET     SAFETY
	   RESET     REMEDY
	 REPEAT
*------------------------------------------------------------------------------
. PLAY SAFETIES
.
	 RESET	   SAFETY
	 COMPARE   "600",DIST(NDX1)
	 GOTO	   DUPS	IF LESS
JU1
	 MOVE	   SAFETY,QUES
	 RESET	   QUES
	 APPEND	   "11",QUES
	 GOTO	   HAND
BUMSS
	 BUMP	   SAFETY
	 GOTO	   JU1 IF NOT EOS
	 RESET	   SAFE(NDX1),4
	 CMATCH	   "N",SAFE(NDX1)
	 GOTO	   DUPS	IF NOT EQUAL
	 MOVE	   "I12",QUES
	 GOTO	   HAND
*------------------------------------------------------------------------------
. THROW	AWAY DUPLICATE CARDS
.
DUPS
	 CLEAR	   FORM1
	 COMPARE   "2",X200(NDX1)
	 GOTO	   RESETER IF LESS
	 MOVE	   "O26",QUES
	 GOTO	   HAND
RESETER
	 ADD	   "1",FORM1
	 RESET	   XCARDS(NDX1),FORM1
	 GOTO	   DISCARDX IF EOS
	 MOVE	   XCARDS(NDX1),DIM1
	 CMATCH	   " ",DIM1
	 GOTO	   RESETER IF EQUAL
	 CMATCH	   "O",DIM1
	 GOTO	   RESETER IF NOT LESS
CKL
	 BUMP	   XCARDS(NDX1)
	 GOTO	   RESETER IF EOS
	 CMATCH	   DIM1,XCARDS(NDX1)
	 GOTO	   GOTCRD IF EQUAL
	 GOTO	   CKL
DISCARDX
	 RESET	   HAZARD
	 RESET	   XCARDS(NDX1)
	 MOVE	   X200(NDX1),FORM1
*------------------------------------------------------------------------------
. THROW	AWAY 200 MILESTONE IF TOO MANY IN HAND (ALREADY	PLAYED)
.
	 LOOP
	   CMATCH    "O",XCARDS(NDX1)
	   IF	     EQUAL
	     ADD       "1",FORM1
	     COMPARE   "3",FORM1
	     IF	       ( FORM1 > 2 )
	       MOVE	 "O25",QUES
	       GOTO	 HAND
	     ENDIF
	   ENDIF
	   BUMP	     XCARDS(NDX1)
	 REPEAT	   IF NOT EOS
*------------------------------------------------------------------------------
. THROW	AWAY SMALLEST MILESTONE
.
Q22
	 COMPARE   "25",LIMIT(NDX1)
	 GOTO	   NO25	IF EQUAL
	 MOVE	   "S20",QUES
	 GOTO	   HAND
NO25
	 COMPARE   "50",LIMIT(NDX1)
	 GOTO	   NO50	IF EQUAL
	 MOVE	   "R21",QUES
	 GOTO	   HAND
NO50
	 COMPARE   "75",LIMIT(NDX1)
	 GOTO	   NO75	IF EQUAL
	 MOVE	   "Q22",QUES
	 GOTO	   HAND
NO75
	 MOVE	   "P23",QUES
	 GOTO	   HAND
NO100
	 COMPARE   "2",X200(NDX1)
	 GOTO	   JU2 IF LESS
	 MOVE	   "O24",QUES
	 GOTO	   HAND
JU2
	 MOVE	   HAZARD,QUES
	 RESET	   QUES
	 APPEND	   "14",QUES
	 GOTO	   HAND
JU3 
	 BUMP	   HAZARD
	 GOTO	   JU2 IF NOT EOS
*------------------------------------------------------------------------------
. THROW	AWAY ANY CARD
.
DISCARDQ 
	 LOOP
	   ADD	     "1",CN(NDX1)
	   IF	     ( CN(NDX1)	= 8 )
	     MOVE      "1",CN(NDX1)
	   ENDIF
	   RESET     XCARDS(NDX1),CN(NDX1)
	 REPEAT	   IF (	XCARDS(NDX1) = " " )
	 MOVE	   CN(NDX1),FORM1
	 ADD	   "1",HI,HZ
	 GOTO	   GOTCRD
*------------------------------------------------------------------------------
. PLAY MILESTONES
.
MILEST
	 CMATCH	   "J",COND(NDX1)
	 GOTO	   OPPO	IF NOT EQUAL
MS100 
	 IF	   ( LIMIT(NDX1) >= 100	)
	   MOVE	     "P16",QUES
	 ELSE
MS75
	   IF	( LIMIT(NDX1) >= 75 )
	     MOVE      "Q17",QUES
	   ELSE
MS50
	     IF	  ( LIMIT(NDX1)	>= 50 )
	       MOVE	 "R18",QUES
	     ELSE
MS25
	       IF   ( LIMIT(NDX1) >= 25	)
		 MOVE	   "S19",QUES
	       ELSE
		 MOVE	   "O15",QUES
	       ENDIF
	     ENDIF
	   ENDIF
	 ENDIF
*------------------------------------------------------------------------------
. CHECK	FOR THIS CARD IN HAND
.
HAND  
	 RESET	   QUES
	 RESET	   XCARDS(NDX1)
	 MOVE	   "1",FORM1
	 LOOP
	   CMATCH    QUES,XCARDS(NDX1)
	   GOTO	     GOTCRD IF EQUAL
	   ADD	     "1",FORM1
	   BUMP	     XCARDS(NDX1)
	 REPEAT	   IF NOT EOS
	 RESET	   QUES,2
	 MOVE	   QUES,DIM2
	 MOVE	   DIM2,BRNCH
	 BRANCH	   BRNCH OF LO9,LO8,GVB,HA04,OPPO,RETES,RESETXX:
			    RZER,BNM,BNMP,BUMSS,DUPS,HY7,JU3:
			    MS100,MS75,MS50,MS25,DISCARD:
			    NO25,NO50,NO75,NO100,JU2,Q22:
			    RESETER,JUN3B
*------------------------------------------------------------------------------
. Another hand is to be	played.	 Re-initialize the variables.
.
CLEAR  
	 CMOVE	   "N",RETRY
	 CMOVE	   "E",COND
	 MOVE	   "200",LIMIT
	 MOVE	   "200",OLIM
	 CMOVE	   "I",SL
	 MOVE	   "	",SAFE
	 MOVE	   "700",GOAL
	 READ	   DISC,$1$;DECK
	 MOVE	   DECK,CARDS
	 MOVE	   PORT,PLAYER
	 MOVE	   "7",CN
	 MOVE	   "N",EXT
	 MOVE	   "13",ALINE
	 MOVE	   ALINE,BLINE
	 MOVE	   "1",ACOL
	 MOVE	   "41",BCOL
	 MOVE	   CNTX,CNT
	 CLEAR	   SCORE:
		   PLAY2:
		   DRAW:
		   DSCNT:
		   REVR:
		   X200(NDX1):
		   DIST:
		   MILES
	 RETURN
*------------------------------------------------------------------------------
. DISPLAY UPDATED CARD COUNT ON	THE SCREEN.
.
UPDCARD	 
	 SUBTRACT  "1",CNT(CARDNDX)
	 DISPLAY   *P=CNTPOS(CARDNDX,1):CNTPOS(CARDNDX,2),CNT(CARDNDX);
	 RETURN
