*---------------------------------------------------------------
.
. Program Name: AGENDAGEN
. Description:  System Generation Program
.
. Revision History:
.
.

.
. Include the file specifications.
.
                INCLUDE         agenda_file.inc

CTDATA          INIT            " Initial User        12 Apr 198512:00 am12 Apr 198512:00 am"
CTDATA1         DIM             108
SEQ             FORM            "-1"
ZERO            FORM            "0"
ANS		DIM		1

                DISPLAY         *ES,"Generating inital AGENDA files"
                MOVE            "10" TO MAXUSRNO
                MOVE            "1" TO MAXAPPT
                PREP            CNTFILE,AGCTRL
                WRITE           CNTFILE,SEQ;MAXUSRNO,MAXAPPT
                CLOSE           CNTFILE

                PREP            CONTROL,AGDCONT
                MOVE            CTDATA TO CTDATA1
                WRITE           CONTROL,ZERO;CTDATA1
                CLOSE           CONTROL
 
                PREP            USRFILE,"agendau.data",FSU,"U,1-10,11-16,17-36,43-47","91"

		MOVE            "9999999999" TO USERID
                MOVE            "999999" TO USRNO
                MOVE            "Initial User" To USRNAME
                MOVE            "ADMIN" TO UGROUP
                WRITE           USRFILE;USERID,USRNO,USRNAME,USREXT,LOFLAG,UGROUP,STATDATE,STATTIME,STATFLAG,STATMSG,FMTIME,MEETFLG

		KEYIN		"Generate sample users ? (Y or N) ",ANS
		CMATCH		"Y" TO Ans

		IF 		EQUAL
                MOVE            "2" TO USERID
                MOVE            "2" TO USRNO
                MOVE            "Bill Smith" To USRNAME
                MOVE            "SUPRT" TO UGROUP
                WRITE           USRFILE;USERID,USRNO,USRNAME,USREXT,LOFLAG,UGROUP,STATDATE,STATTIME,STATFLAG,STATMSG,FMTIME,MEETFLG
                MOVE            "3" TO USERID
                MOVE            "3" TO USRNO
                MOVE            "Tom Grayson" To USRNAME
                MOVE            "SALES" TO UGROUP
                WRITE           USRFILE;USERID,USRNO,USRNAME,USREXT,LOFLAG,UGROUP,STATDATE,STATTIME,STATFLAG,STATMSG,FMTIME,MEETFLG
                MOVE            "4" TO USERID
                MOVE            "4" TO USRNO
                MOVE            "Sam Tolli" To USRNAME
                WRITE           USRFILE;USERID,USRNO,USRNAME,USREXT,LOFLAG,UGROUP,STATDATE,STATTIME,STATFLAG,STATMSG,FMTIME,MEETFLG

		ENDIF

                CLOSE           USRFILE

//
//  Aamdexing the Users File
//
                AAMDEX          "agendau.data,agendau.aam,L91 -U,P1##'*',1-10,11-16,17-36,43-47"
//
//  Indexing & Ammdexing the Appointments File
//
                PREP            AGENDA,"agenda.data",FSA,"17","98"
                CLOSE           AGENDA
                INDEX           "agenda.data,agenda.isi,L98 -1-17"
 
                PREP            AGENDAIM,"agenda.data",FSA,"U,1-6,44-98","98"
                CLOSE           AGENDAIM
                AAMDEX          "agenda.data,agenda.aam,L98 -U,1-6,44-98"
                
//
// Indexing the Appointment Graph File
//
                PREP            GRAPH,"agendag.data",FSG,"11","109"
                CLOSE           GRAPH
                INDEX           "agendag.data,agendag.isi,L109 -1-11"

//
//  Indexing the Messages File
//

                PREP            MESSAGE,"agendam.data",FSM,"18","387"
                CLOSE           MESSAGE
                INDEX           "agendam.data,agendam.isi,L387 -1-18,S,V"

//
//  Aamdexing the Directory File
//
                PREP            DIRFILE,"agendad.data",FSD,"U,1-6,7-36,157-186","186"
                CLOSE           DIRFILE
                AAMDEX          "agendad.data,agendad.aam,L186 -U,1-6,7-36,157-186"
//
//  Indexing & Aamdexing the Notepad & Alarms File
//
                PREP            NOTEFILA,"agendan.data",FSN,"U,2-7,40-94","94"
                CLOSE           NOTEFILA
                AAMDEX          "agendan.data,agendan.aam,L94 -U,P1='2',2-7,40-94"
 
                PREP            NOTEFILE,"agendan.data",FSN,"20","94"
                CLOSE           NOTEFILE
                INDEX           "agendan.data,agendan.isi,L94 -1-20"
//
//  Indexing the Meeting Planner File
//
                PREP            PLAN,"agendap.data",FSP,"17","152"
                CLOSE           PLAN
                INDEX           "agendap.data,agendap.isi,L152 -1-17,P1##*"
 
                PREP            PLAN1,"agendap.data",FSP1,"23","152"
                CLOSE           PLAN1
                INDEX           "agendap.data,agendap1.isi,L152 -18-23,7-17,1-6,P1##*"
//
//  Indexing the Help File
//
                COPYFILE        "agendah.new","agendah.data"
                INDEX           "agendah.data -2-5,P1=*,S,V"
 
                KEYIN           "File Generation Complete", Ans
.
. *** End ***
.
