*...........................................................................
.Example Program: SORTLV.PLS
.
.This sample program the SortColumn method for sorting ListViews.
.
.
.Copyright @ 2010, Sunbelt Computer Systems, Inc.
.All Rights Reserved.
.
. ISSUE DATE: 10-21-98
. UPDATED:  07-30-2010
.............................................................................
.
SEQ             FORM            "-1"
PATH            DIM             40
NRECS           FORM            5
RESULT          FORM            9
RET             INTEGER         1
DATA            DIM             80
CURINDEX        FORM            5
SORTCOL         FORM            2
COLUMNUM        FORM            2
HEX7F           INIT            0x7F
NDX             FORM            3
ROWCT           FORM            4
CTR             FORM            3
SORTORDR        INTEGER         1  ;0,3=None: 1=Ascending: 2=Descending
COLW                            FORM    4
ITMCNT          FORM            4
DV2             FORM            2
ITMCT           FORM            3
WIDE            FORM            5
HIGH            FORM            5
.
INPUT           FILE
WORKFL          FILE
.
REC             LIST
ACCT            DIM             5
NAME            DIM             30
ADDR1           DIM             30
ADDR2           DIM             30
CITY            DIM             16
ST              DIM             2
ZIP             DIM             10
PHONE           DIM             10
DATE            DIM             8
NOTICE          DIM             30
                LISTEND
DREC            DIM             171
NOTE            DIM             255
.
FRM             PLFORM          lvsort
...............................................................................
. Get the name of the file to open
.
                WINHIDE
.
                OPEN            INPUT,"LVDATA"
.
                FORMLOAD        FRM
.
                LOOP
                WAITEVENT
                REPEAT
...............................................................................
. Create the Listview object, column headers first
.
SETUPLV
.
.Listview InsertColumn using title, width, position
. 
                LV1.InsertColumn USING "Acct##",70,0
                LV1.InsertColumn USING "Name",200,1
                LV1.InsertColumn USING "Address",200,2
                LV1.InsertColumn USING "City",100,3
                LV1.InsertColumn USING "State",40,4
                LV1.InsertColumn USING "ZipCode",90,5
                LV1.InsertColumn USING "Phone",100,6
                LV1.InsertColumn USING "Notice",200,7
.
                RETURN
.
. Insert data
.
LOADLV
                LOOP
. read a data record and suppress trailing spaces
                READ            INPUT,SEQ;*ll,REC
                UNTIL           OVER
.
. old style
. 
.    LV1.InsertItem  GIVING CURINDEX USING ACCT
.    LV1.SetItemText USING CURINDEX, NAME, 1
.    LV1.SetItemText USING CURINDEX, ADDR1, 2
.    LV1.SetItemText USING CURINDEX, CITY, 3
.    LV1.SetItemText USING CURINDEX, ST, 4
.    LV1.SetItemText USING CURINDEX, ZIP, 5
.    LV1.SetItemText USING CURINDEX, PHONE, 6
.    LV1.SetItemText USING CURINDEX, NOTICE, 7
. 
. New style is faster
. 
                MOVE            "9999",CurIndex
                LV1.InsertItemEx using Acct,CurIndex:
                                *SubItem1=NAME:
                                *SubItem2=ADDR1:
                                *SubItem3=CITY:
                                *SubItem4=ST:
                                *SubItem5=ZIP:
                                *SubItem6=PHONE:
                                *SubItem7=NOTICE

                REPEAT

                RETURN
...............................................................................
. Sort code.
.
SORTIT
                LV1.SortColumn  using SortCol,SORTORDR

                RETURN
