P		PFILE
MESSAGE	DIM		80
REPLY	INTEGER	1
TODAY	DIM		8
VPOS	FORM	2
COLOR1	COLOR
PICT1	PICT
*
.Create the objects needed
.
REPORT
		CREATE	PICT1=1:10:1:40,"SUNBELT.GIF"
		CREATE	COLOR1=240:240:240
*
.Open the data files
.
		OPEN	CUSTLIST
		OPEN	ORDFILE,"ORDER.ISI"
		OPEN	DTLFILE,"DETAIL.ISI"
*
.Open the printer

		PRTOPEN	P,"@",""
		CALL	HEADING
*
.Loop through the orders
.
		LOOP
		READKS	ORDFILE;ORDDATA
		UNTIL	OVER
*
.Look up the customer name
.
		READ		CUSTFILE,ORDCUST;*LL,CUSTDATA
		IF			OVER
		PACK		MESSAGE WITH "Unable to locate customer ",ORDCUST
		ALERT		STOP,Message,Reply,"Error"
		PRTCLOSE	P,ABORT
		ENDIF
*
.Print the order line
.
		PRTPAGE		P;*OVERLAYON:
					*RNDRECT=7:12:40:90:2:2: 
					*P=43:8,CONAME," (",CUSTNUM,")":
					*P=43:9,ADDRESS,*P=43:10,*LL,CITY,", ",STATE,"  ",ZIPCODE:
					*P=43:11,*LL,CONTACTFN," ",CONTACTLN:
					*RECT=14:40:20:110:
					*P30:15,*BOLDON,"Order: ",ORDNUM:
					*HA=5,"Date: ",ORDDATE:
					*HA=5,"Ship Via:",ORDSHIP:
					*HA=5,"Salesman: ",ORDSALES,*BOLDOFF:
					*P20:17,*LINE=111:17:
					*FGCOLOR=*WHITE,*BGCOLOR=12147712,*FILL=*ON:
					*RECT=18:19:20:35:
					*RECT=18:19:35:80:
					*RECT=18:19:80:95:
					*RECT=18:19:95:110:
					*P25:19,"ITEM",*P50:19,"DESCRIPTION":
					*P83:19,"QUANTITY",*P100:19,"PRICE":
					*FGCOLOR=*BLACK
					
		MOVE		"20",VPOS
*
.Position the detail file
.
		
		READ		DTLFILE,ORDNUM;;
*
.Loop through the detail records
.
		LOOP
		READKS		DTLFILE;DTLDATA
		UNTIL		OVER or (ORDNUM != DTLORD)
*
.Print the detail records
.
		PRTPAGE		P;*BGCOLOR=*WHITE,*FILL=*ON:
					*RECT=VPOS:(VPOS+2):20:35:
					*RECT=VPOS:(VPOS+2):35:80:
					*RECT=VPOS:(VPOS+2):80:95:
					*RECT=VPOS:(VPOS+2):95:110:
					*P22:(VPOS+1),DTLITEM,*P38:(VPOS+1),DTLDESC:
					*P83:(VPOS+1),DTLQTY,*P100:(VPOS+1),DTLPRICE
		ADD			"3",VPOS
*
.Next Detail Record
.
		REPEAT
	
*
.Next Order Record
.
		PRTPAGE		P;*F
		REPEAT
*
.Close the files
.
		CLOSE		CUSTLIST
		CLOSE		ORDFILE
		CLOSE		DTLFILE
*
.Initiate Printing
.
		PRTCLOSE	P
*
.Exit
.
		RETURN
*
.Page Heading
.
HEADING	
		CLOCK		DATE,TODAY
		PRTPAGE		P;*N,*N:
					*PICT=1:10:1:40:PICT1:
					*TAB=40,*FONT=">Arial(16,BOLD)":
					*UNITS=*FONT,*FGCOLOR=*RED,"Sales Application",*N:
					*TAB=30,*FONT=">Arial(14,BOLD)":
					*UNITS=*FONT,*FGCOLOR=*BLUE:
					"ORDER REPORT FOR ",TODAY,*N,*N:
					*FONT=">Arial(11)",*UNITS=*FONT,*FGCOLOR=*BLACK
	
		RETURN
