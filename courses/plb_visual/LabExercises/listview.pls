*---------------------------------------------------------------
.
. Program Name: listview.pls
. Description:  Visual PL/B Programming program
.  
RESULT          INTEGER         1
MAIN            PLFORM          listview.plf
.
		//SETMODE		*WEBMODEPLF=3
                WINHIDE
                FORMLOAD        MAIN

		lvNames.InsertItemEx Using "12100", 1, 1, *Subitem1="Sam's Auto Sales"
		lvNames.InsertItemEx Using "12101", 2, 2, *Subitem1="Hometown Grocery"
		lvNames.InsertItemEx Using "12102", 3, 3, *Subitem1="Utility Telephone"
		lvNames.InsertItemEx Using "12103", 4, 4, *Subitem1="Swan Lawn Care"
		lvNames.InsertItemEx Using "12104", 5, 5, *Subitem1="Rural Septic Systems"
                LOOP
                EVENTWAIT
                REPEAT
