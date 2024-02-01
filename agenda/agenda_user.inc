*---------------------------------------------------------------
.
. Module Name: agenda_user.inc
. Description: User Status Module
.
. Revision History:
.
.Display the User Status Screen
.
USERS           CALL            CLOCKDT
                MOVE            ZERO,EOFSW
                MOVE            ONE,PAGE
                CALL            SHOWBOX1
                DISPLAY         *P30:1,USRSTAT;
.
USERS1          DISPLAY         *P1:23,*EL,*H 73,PGSTAT,PAGE:
                                *P12:3,USRSTAT2,*H 26,EXTSTAT,*H 32,GRPSTAT:
                                *H 37,MSGSTAT,*H 42,STSTAT,*H 48,DTSTAT:
                                *H 56,TMSTAT,*H 68,CMSTAT:
                                *P3:4,*RPTCHAR HB:21,*HA 1,*RPTCHAR HB:5:
                                *HA 1,*RPTCHAR HB:5:
                                *HA 1,*RPTCHAR HB:4,*HA 1,*RPTCHAR HB:4:
                                *HA 1,*RPTCHAR HB:6,*HA 1,*RPTCHAR HB:8:
                                *HA 1,*RPTCHAR HB:16
                CLEAR           FUNCDESC           // Clear the functions.                
                MOVE            ZERO,FLAG1         // Flag1 = 0                           
                CALL            CHKALRM            // Check for alarm,plan,message.        
                DISPLAY         *P3:5;                                                    
*
.Set Up the Variables for the Search Function
.
USERS2          MOVE            CURRGRP,UGROUP1    // Select Current User's Group
		MATCH 		"     " TO UGROUP1
		IF		NOT ZERO
                MOVE            ONE,FLAG3
		ENDIF
                CLEAR           AKEY1
                GOTO            USSRCH4
+..............................................................................
.
.            U S E R   S T A T U S   C O M M A N D   H A N D L E R
...............................................................................
.
.Get the Security Password & return only if equal in values and length
.
KEYPASS         MOVE            NINETEEN,CMDTRAP                                       
                TRAP            KEYPASSX IF ESCAPE                               
                TRAP            KEYPASSX IF F27                            
                KEYIN           *HD,*EL,*DV,SCPASSW,*ESON,DIM40,*ESOFF;
                BUMP            DIM40,0
                GOTO            KEYPASSX IF EOS
                MATCH           PASSWORD,DIM40
                GOTO            KEYPASSX IF NOT EQUAL
                GOTO            KEYPASSX IF LESS
                MATCH           DIM40,PASSWORD
                GOTO            KEYPASSX IF LESS
                RETURN
KEYPASSX        NORETURN        // Clean up stack from CMD key
.
US$CMD          NORETURN
                MOVE            ZERO,CMDTRAP                                            
                TRAP            LOGON IF ESCAPE                                        
                TRAP            LOGON IF F27                                            
                DISPLAY         *HD,*EL,SPACE,FUNC7,SPACE,CFUNC6,SPACE,NFUNC1:
                                SPACE,CFUNC8,SPACE,AFUNC2,SPACE,FUNC9,SPACE,CFUNC7;
                MOVE            ZERO,FLAG2
                MOVE            FIVE,TOCOUNT
*
.Highlight the Function
.
US$CMD1         LOAD            FUNCDESC BY CFUNC FROM FUNC7,CFUNC6:                    
                                NFUNC1,CFUNC8,AFUNC2,FUNC9,CFUNC7
.
                MOVE            CFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           CFPOS,NWORK2
                MOVE            CFPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
US$CMD2         DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              LEFT                                                           
                CMOVE           LEFT,REPLY                                             
                ENDIF           032
                IF              RIGHT                                                           
                CMOVE           RIGHT,REPLY                                            
                ENDIF           032
                GOTO            US$CMD7 IF F5
                GOTO            US$CMD7 IF F9                                          
                GOTO            US$CMD6 IF LESS
                GOTO            US$CMD5 IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
.
                CMATCH          CMDKEY,REPLY                                      
                GOTO            LOGON IF EQUAL                                    
                GOTO            LOGON IF F27                                        
.
                CMATCH          RIGHT,REPLY
                GOTO            US$CMD3 IF EQUAL
                CMATCH          LEFT,REPLY
                GOTO            US$CMD4 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            US$CMD3 IF EQUAL
*
.Check for a Command Letter
.
                RESET           CFLETS
                SCAN            REPLY,CFLETS
                IF              NOT EQUAL               // Lower case     
                RESET           CFLETS2                                            
                SCAN            REPLY,CFLETS2                                   
                GOTO            US$CMD2 IF NOT EQUAL                               
                MOVEFPTR        CFLETS2,CFUNC                                     
                GOTO            US$CMD1                                           
                ENDIF           026
                MOVEFPTR        CFLETS,CFUNC
                GOTO            US$CMD1
*
.Move Right to the Next Function
.
US$CMD3         ADD             ONE,CFUNC
                COMPARE         EIGHT,CFUNC
                GOTO            US$CMD1 IF NOT EQUAL
                MOVE            ONE,CFUNC
                GOTO            US$CMD1
*
.Move Left to the Previous Function
.
US$CMD4         SUB             ONE,CFUNC
                GOTO            US$CMD1 IF NOT ZERO
                MOVE            SEVEN,CFUNC
                GOTO            US$CMD1
*
.We Have a Selected Function
.
US$CMD5         BRANCH          CFUNC TO USSRCH,USSTAT,USNEXT,USADD,USCHG,USDEL,USSTOP  
                CALL            INTERR
*
.A Timeout Occurred
.
US$CMD6         MOVE            ZERO,FLAG1
                CALL            CHKALRM
                DISPLAY         *P59:1,DATE,SPACE2,TIME;
.
                SUB             ONE,TOCOUNT
                GOTO            US$CMD2 IF NOT ZERO
                DISPLAY         *SETSWTB 5:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80;
                GOTO            USNEXT
*
.Help Requested
.
US$CMD7         MOVE            SIX,HMENU
                MOVE            CFUNC,HFUNCNO
                CALL            HELP
                CALL            SHOWBOX1
                GOTO            USERS1
+..............................................................................
.
.                       N E X T   P A G E   OF   U S E R S
...............................................................................
.
.
USNEXT          BRANCH          EOFSW TO USNEXT1
.
                ADD             ONE,PAGE
                MOVE            ZERO,DTLCOUNT
                DISPLAY         *SETSWTB 5:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,PAGE,*HD,*EL,*V 5;
                GOTO            USSRCH8
*
.Rewind the File
.
USNEXT1         MOVE            ONE,PAGE
                MOVE            ZERO,EOFSW
                MOVE            ZERO,DTLCOUNT
.
                DISPLAY         *SETSWTB 5:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,PAGE,*HD,*EL,RWFILE,*V 5;
                GOTO            USSRCH4
+..............................................................................
.
.                           U S E R   A D D I T I O N
...............................................................................
.
.
.Get the Security Password
.
USADD           CALL            KEYPASS              // ENTER SECURITY PASSWORD        
*
.Check for a Full Screen
.
USADD1          COMPARE         "17",DTLCOUNT
                GOTO            USADD2 IF NOT EQUAL
                MOVE            ZERO,DTLCOUNT
                ADD             ONE,PAGE
                DISPLAY         *SETSWTB 5:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80,*P77:23,PAGE;
*
.Compute the Screen Position
.
USADD2          MOVE            DTLCOUNT,VPOS
                ADD             FIVE,VPOS
                MOVE            TWENTY,CMDTRAP                                     
                TRAP            USADD9 IF ESCAPE                                    
                TRAP            USADD9 IF F27                                        
*
.Get the User's Name
.
USADD3          KEYIN           *HD,*EL,*DV,NEWUS5,*DV,NEWUS0,*DV,NEWUS1:
                                *P4:VPOS,*RPTCHAR "_":20,*H 4,*IT,USRNAME1;
                DISPLAY         *IN,*H 4,USRNAME1;
                GOTO            USADD9 IF F5
.
                CMATCH          " ",USRNAME1
                GOTO            USADD3 IF EQUAL
                GOTO            USADD9 IF EOS
*
.Get the User's Telephone Extension
.
USADD4          KEYIN           *HD,*EL,*DV,NEWUS5,*DV,NEWUS0,*DV,NEWUS2:
                                *P25:VPOS,*RPTCHAR "_":5,*H 25,*JR,USREXT;
                GOTO            USADD3 IF F5
.
                DISPLAY         *H 25,USREXT;
*
.Get the User's Group Designation
.
USADD5          KEYIN           *HD,*EL,*DV,NEWUS5,*DV,NEWUS0,*DV,NEWUS3:
                                *P31:VPOS,*RPTCHAR "_":5,*H 31,UGROUP;
                GOTO            USADD4 IF F5
.
                CMATCH          " ",UGROUP
                GOTO            USADD5 IF EQUAL
                GOTO            USADD5 IF EOS
.
                DISPLAY         *H 31,UGROUP;
*
.Get the User's Identification Number
.
USADD6          KEYIN           *HD,*EL,*DV,NEWUS5,*DV,NEWUS0,*DV,NEWUS4:
                                *RPTCHAR "_":10,*HA -10,USERID;
                GOTO            USADD5 IF F5
.
                CMATCH          " ",USERID
                GOTO            USADD6 IF EQUAL
                GOTO            USADD6 IF EOS
*
.Make Sure the Identification Number isn't Already In Use
.
                PACK            KEYWORK WITH X01,USERID
                FILEPI          1;USRFILE
                READTAB         USRFILE,KEYWORK;REPLY
                GOTO            USADD7 IF OVER
.
                DISPLAY         *CLICK,*HD,*EL,IDINUSE,*W;
                GOTO            USADD6
*
.Set up the Other Variables
.
USADD7          MOVE            SPACE,LOFLAG
                MOVE            OUT,STATFLAG
                CLEAR           STATMSG
                CALL            CLOCKDT
                MOVE            DATE,STATDATE
                MOVE            ZERO,MEETFLG
.
                MOVE            NINE9,FMTIME
                CALL            FIXSTATD
                DISPLAY         *P37:VPOS,NO,*H 42,STATFLAG,*H 47,DIM6,*H 54,TIME;
*
.Get the Next Available User Number
.
USADD8          FILEPI          3;CNTFILE
                READ            CNTFILE,ZERO;USRNO1,MAXAPPT
                ADD             ONE,USRNO1
                WRITE           CNTFILE,ZERO;USRNO1,MAXAPPT
*
.Make Sure the Number Isn't Already In Use
.
                PACK            KEY9 WITH X02,USRNO1
                FILEPI          1;USRFILE
                READTAB         USRFILE,KEY9;REPLY
                GOTO            USADD8 IF NOT OVER
*
.Output the New User Record
.
                FILEPI          1;USRFILE
                WRITE           USRFILE;USERID,USRNO1,USRNAME1,USREXT,LOFLAG,UGROUP:
                                STATDATE,TIME,STATFLAG,STATMSG,FMTIME,MEETFLG
*
.Save the New User's Key
.
                ADD             ONE,DTLCOUNT
                MOVE            USRNO1,KEY6
                SETLPTR         UGROUP
                PACK            KEY WITH KEY6,UGROUP,ONE
.
                STORE           KEY BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN:
                                KEYO,KEYP,KEYQ,KEYR
.
                DISPLAY         *HD,*EL,USRADD;
*
.Allow Adding Another Group Designation
.
USADD10
                DISPLAY         *HD,*EL,ADDGRP;                                  
                CALL            KREPLYN                                            
                CMATCH          YES,REPLY                                           
                GOTO            USADD14 IF NOT EQUAL
*
.Get the Subsequent Group
.
USADD11         KEYIN           *HD,*EL,*DV,NXTGRP,*RPTCHAR "_":5,*H 13,UGROUP;
                GOTO            USADD14 IF F5
.
                CMATCH          " ",UGROUP
                GOTO            USADD11 IF EQUAL
                GOTO            USADD14 IF EOS
.
                MOVE            BLANKS,USERID
*
.Output the Subsequent Group Record
.
                FILEPI          1;USRFILE
                WRITE           USRFILE;USERID,USRNO1,USRNAME1,USREXT,LOFLAG,UGROUP:
                                STATDATE,TIME,STATFLAG,STATMSG,FMTIME,MEETFLG
*
.Check for a Full Screen
.
                COMPARE         "17",DTLCOUNT
                GOTO            USADD12 IF NOT EQUAL
                MOVE            ZERO,DTLCOUNT
                ADD             ONE,PAGE
                DISPLAY         *SETSWTB 5:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80,*P77:23,PAGE;
.
USADD12         MOVE            DTLCOUNT,VPOS
                ADD             FIVE,VPOS
                DISPLAY         *P4:VPOS,USRNAME1,*H 31,UGROUP,*H 63,SECGRP;
*
.Save the New User's Key
.
                ADD             ONE,DTLCOUNT
                MOVE            USRNO1,KEY6
                PACK            KEY WITH KEY6,UGROUP,ZERO
.
                STORE           KEY BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN:
                                KEYO,KEYP,KEYQ,KEYR
                GOTO            USADD10
*
.Abort Adding the User
.
USADD9          NORETURN
                DISPLAY         *SETSWLR 2:79,*P2:VPOS,*EL,*SETSWALL=1:24:1:80;
                COMPARE         ZERO,DTLCOUNT
                GOTO            USERS2 IF EQUAL
                GOTO            US$CMD
*
.Exit the Addition Section
.
USADD14         COMPARE         "5",CFUNC
                GOTO            USLOC1 IF EQUAL
                GOTO            USADD1
+..............................................................................
.
.                          U S E R   S E L E C T I O N
...............................................................................
.
.
USLOC           MOVE            ONE,KEYPTR
                MOVE            FIVE,VPOS
                BRANCH          DTLCOUNT TO USLOC5      // Only One Record...
.
USLOC1          NORETURN
                MOVE            TWENTY1,CMDTRAP                                        
                TRAP            USLOC7 IF ESCAPE                                       
                TRAP            USLOC7 IF F27                                           
                DISPLAY         *HD,*EL,UPDWNCMD;
*
.Position to the Correct Record
.
USLOC2          MOVE            KEYPTR,VPOS
                ADD             FOUR,VPOS
*
.Get a Command
.
USLOC3K
                KEYIN           *P2:VPOS,RA,*H 2,*+,*T90,*RV,REPLY;                
                IF              UP                                                       
                CMOVE           UP,REPLY                                         
                ENDIF           032
                IF              DOWN                                                       
                CMOVE           DOWN,REPLY                                        
                ENDIF           032
                CALL            USLOC7 IF LESS                                     
                DISPLAY         *H 2,SPACE;
                GOTO            USLOC5 IF EOS
.
                CMATCH          CMDKEY,REPLY                                      
                GOTO            USLOC7 IF EQUAL                                   
                GOTO            USLOC7 IF F27                                     
.
                CMATCH          DOWN,REPLY
                GOTO            USLOC4 IF EQUAL
                CMATCH          UP,REPLY
                GOTO            USLOC3K IF NOT EQUAL                               
*
.Position to the Next Higher Record
.
                SUB             ONE,KEYPTR
                GOTO            USLOC2 IF NOT EQUAL
                MOVE            DTLCOUNT,KEYPTR
                GOTO            USLOC2
*
.Position to the Next Lower Record
.
USLOC4          ADD             ONE,KEYPTR
                COMPARE         KEYPTR,DTLCOUNT
                GOTO            USLOC2 IF NOT LESS
                MOVE            ONE,KEYPTR
                GOTO            USLOC2
*
.We Have a Selected User
.
USLOC5          LOAD            KEY BY KEYPTR FROM KEYA,KEYB,KEYC,KEYD,KEYE,KEYF:
                                KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN,KEYO:
                                KEYP,KEYQ,KEYR
.
                UNPACK          KEY INTO KEY6,UGROUP,REPLY
                MOVE            REPLY,GROUPFLG
.
                PACK            KEY9 WITH X02,KEY6
                PACK            AKEY2 WITH L04,UGROUP
.
                FILEPI          1;USRFILE
                READTAB         USRFILE,KEY9,AKEY2;USERID,USRNO1,USRNAME1,USREXT,LOFLAG
                GOTO            USLOC6 IF OVER
*
.Branch Back to the Correct Function
.
                BRANCH          CFUNC OF USLOC6,USSTAT1,USLOC6,USLOC6,USCHG1,USDEL1    
.
USLOC6          CALL            INTERR
                GOTO            US$CMD
*
.Exit the Location Routine
.
USLOC7          NORETURN
                DISPLAY         *HOFF,*H 2,SPACE;
                GOTO            US$CMD
+..............................................................................
.
.            U S E R   I N F O R M A T I O N   M O D I F I C A T I O N
...............................................................................
.
.
USCHG           COMPARE         ZERO,DTLCOUNT
                GOTO            US$CMD1 IF EQUAL     No Records
*
.Get the Security Password
.
                CALL            KEYPASS              // ENTER SECURITY PASSWORD          
.
                GOTO            USLOC
*
.Allow Changing the User Name
.
USCHG1          MOVE            TWENTY2,CMDTRAP                                         
                TRAP            USCHG7 IF ESCAPE                                      
                TRAP            USCHG7 IF F27                                           
                MOVE            ONE,FLAG2
.
USCHG2          KEYIN           *HD,*EL,*DV,NEWUS5,*DV,NEWUS0,*DV,NEWUS1:
                                *P4:VPOS,*IT,*RV,USRNAME1;
                DISPLAY         *IN,*H 4,USRNAME1;
                GOTO            USLOC1 IF F5
                GOTO            USCHG3 IF EOS
.
                CMATCH          " ",USRNAME1
                GOTO            USCHG2 IF EQUAL
                MOVE            ZERO,FLAG2
*
.Allow Changing the Telephone Extension
.
USCHG3          COMPARE         ZERO,GROUPFLG
                GOTO            USCHG4 IF EQUAL
.
                KEYIN           *HD,*EL,*DV,NEWUS5,*DV,NEWUS2:
                                *P25:VPOS,*JR,*RV,USREXT;
                DISPLAY         *H 25,USREXT;
                GOTO            USCHG2 IF F5
                GOTO            USCHG4 IF EOS
                MOVE            ZERO,FLAG2
*
.Allow Changing the Group
.
USCHG4          KEYIN           *HD,*EL,*DV,NEWUS5,*DV,GRPDES:
                                *P31:VPOS,*RV,UGROUP;
                DISPLAY         *IN,*H 31,UGROUP
                GOTO            USCHG3 IF F5
                GOTO            USCHG5 IF EOS
                MOVE            ZERO,FLAG2
                SETLPTR         UGROUP
*
.Allow Changing the User Identification Number
.
USCHG5          COMPARE         ZERO,GROUPFLG
                GOTO            USCHG6 IF EQUAL
.
                KEYIN           *HD,*EL,*DV,NEWUS5,*DV,NEWUS0,*DV,NEWUS4:
                                *DV,USERID,*H 45,*RV,USERID;
                GOTO            USCHG4 IF F5
                GOTO            USCHG6 IF EOS
*
.See if The ID is Already In Use
.
                MOVE            ZERO,FLAG2
                PACK            KEYWORK WITH X01,USERID
                FILEPI          1;USRFILE
                READ            USRFILE,KEYWORK;REPLY
                GOTO            USCHG6 IF OVER
.
                KEYIN           *CLICK,*HD,*EL,*DV,IDBAD,*DV,NEWUS4,*DV,INUSEID:
                                REPLY;
                GOTO            USCHG5
*
FIXSTATD        MOVE            STATDATE,DIM6
                COMPARE         ONE,DATESWCH         // European format ?
                RETURN          IF EQUAL
                RESET           DIM6,6
                CMOVE           " ",DIM6
                RESET           DIM6
                RETURN
*
.Changes Complete
.
USCHG6          BRANCH          FLAG2 TO USADD10
*
.Read the User's Record
.
                TRAPCLR         ESCAPE                                               
                TRAPCLR         F27                                                  
                FILEPI          1;USRFILE
                READTAB         USRFILE,KEY9,AKEY2;*11,KEY6,*42,LOFLAG:
                                *48,STATDATE,STATTIME,STATFLAG,STATMSG,FMTIME,MEETFLG
                CALL            INTERR IF OVER
*
.Delete & Rewrite the Information
.
                FILEPI          2;USRFILE
                DELETE          USRFILE
.
                WRITE           USRFILE;USERID,KEY6,USRNAME1,USREXT,LOFLAG,UGROUP:
                                STATDATE,STATTIME,STATFLAG,STATMSG,FMTIME,MEETFLG
*
.Update the Key in Memory
.
                PACK            KEY WITH KEY6,UGROUP,ONE
                STORE           KEY BY KEYPTR FROM KEYA,KEYB,KEYC,KEYD,KEYE,KEYF:
                                KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN,KEYO:
                                KEYP,KEYQ,KEYR
.
                DISPLAY         *HD,*EL,CHGCOMP,*W;
*
.If We Changed the Current User, Update the Information In Memory
.
                MOVE            KEY6,USRNO1
                COMPARE         USRNO1,CURRUSER
                GOTO            USADD10 IF NOT EQUAL
.
                MOVE            USRNAME1,CURRNAME
                MOVE            UGROUP,CURRGRP
                DISPLAY         *P2:1,CURRNAME;
                GOTO            USADD10
*
.Abort Changing the User Information
.
USCHG7          NORETURN
                CLEAR           KEY6
                FILEPI          1;USRFILE
                READ            USRFILE,KEY6;USERID,KEY6,USRNAME1,USREXT,LOFLAG,UGROUP
.
                DISPLAY         *P2:VPOS,SPACE,*H 4,USRNAME1,*H 25,USREXT,*H 31,UGROUP;
                GOTO            US$CMD
+..............................................................................
.
.                           U S E R   R E M O V A L
...............................................................................
.
.
USDEL           COMPARE         ZERO,DTLCOUNT
                GOTO            US$CMD1 IF EQUAL
*
.Get the Security Password
.
                CALL            KEYPASS              // ENTER SECURITY PASSWORD        
.
                GOTO            USLOC
*
.Verify the Deletion
.
USDEL1          MOVE            TWENTY3,CMDTRAP                                       
                TRAP            USDEL27 IF ESCAPE                                     
                TRAP            USDEL27 IF F27                                      
                DISPLAY         *P4:VPOS,*HON,USRNAME1,*HOFF:                      
                                *HD,*EL,DELUSR;                                
                CALL            KREPLYN
                CMATCH          YES,REPLY                                            
                GOTO            USDEL27 IF NOT EQUAL
*
.If Secondary Record, Delete It Alone
.
                BRANCH          GROUPFLG TO USDEL2
                DELETE          USRFILE
                GOTO            USNEXT1
*
.Position to His New Messages
.
USDEL2          DISPLAY         *HD,*EL,DELETING,USRMSGS;
                MOVE            ONE,RECTYPE
.
USDEL3          PACK            KEYWORK WITH RECTYPE,KEY6
                MOVE            ZERO,NWORK1
.
                FILEPI          1;MESSAGE
                READ            MESSAGE,KEYWORK;;
*
.Read Through the Message File
.
USDEL4          FILEPI          1;MESSAGE
                READKSTB        MESSAGE;KEY18
                GOTO            USDEL5 IF OVER
*
.Right User ?
.
                MATCH           KEYWORK,KEY18
                GOTO            USDEL5 IF NOT EQUAL
*
.Delete the Message Record
.
                ADD             ONE,NWORK1
                DISPLAY         *P75:24,NWORK1;
.
                FILEPI          1;MESSAGE
                DELETE          MESSAGE,KEY18
                CALL            INTERR IF OVER
                GOTO            USDEL4
*
.Delete All the Saved Messages
.
USDEL5          COMPARE         TWO,RECTYPE
                GOTO            USDEL6 IF EQUAL
                MOVE            TWO,RECTYPE
                GOTO            USDEL3
*
.Open the Appointments Files as Needed
.
USDEL6          MOVE            OPENFLAG,REPLY
                AND             0100,REPLY
                GOTO            USDEL7 IF NOT ZERO

                TRAP            TRAPIO IF IO         // Can't open a file                     
                OPEN            GRAPH,FSG,SHARE              
                OPEN            AGENDA,FSA,SHARE
                OPEN            AGENDAIM,FSA,SHARE
                OR              0100,OPENFLAG
                TRAPCLR         IO
*
.Delete All His Appointment Records
.
USDEL7          DISPLAY         *HD,*EL,DELETING,USRAPTS;
.
                FILEPI          1;AGENDA
                READ            AGENDA,KEY6;;
                MOVE            ZERO,NWORK1
*
.Read Through the Appointment File
.
USDEL8          FILEPI          1;AGENDA
                READKSTB        AGENDA;KEY17
                GOTO            USDEL9 IF OVER
*
.Right User ?
.
                MATCH           KEY6,KEY17
                GOTO            USDEL9 IF NOT EQUAL
*
.Delete the Appointment Record
.
                ADD             ONE,NWORK1
                DISPLAY         *P75:24,NWORK1;
                CALL            AG1090
                GOTO            USDEL8
*
.Delete All His Appointment Graph Records
.
USDEL9          DISPLAY         *HD,*EL,DELETING,USRGRPH;
.
                FILEPI          1;GRAPH
                READ            GRAPH,KEY6;;
                MOVE            ZERO,NWORK1
*
.Read Through the Appointment Graph File
.
USDEL10         FILEPI          1;GRAPH
                READKSTB        GRAPH;KEY11
                GOTO            USDEL11 IF OVER
*
.Right User ?
.
                MATCH           KEY6,KEY11
                GOTO            USDEL11 IF NOT EQUAL
*
.Delete the Appointment Graph Record
.
                ADD             ONE,NWORK1
                DISPLAY         *P75:24,NWORK1;
.
                FILEPI          1;GRAPH
                DELETE          GRAPH,KEY11
                CALL            INTERR IF OVER
                GOTO            USDEL10
*
.Open the Directory File as Needed
.
USDEL11         MOVE            OPENFLAG,REPLY
                AND             020,REPLY
                GOTO            USDEL12 IF NOT ZERO
.
                TRAP            TRAPIO IF IO         // Can't open a file              
                OPEN            DIRFILE,FSD,SHARE
                OR              020,OPENFLAG
                TRAPCLR         IO
*
.Delete His Directory Records
.
USDEL12         MOVE            KEY6,USRNO1
                PACK            KEY9 WITH X01,USRNO1
.
                DISPLAY         *HD,*EL,DELETING,USRDIR;
                MOVE            ZERO,NWORK1
.
                FILEPI          1;DIRFILE
                READTAB         DIRFILE,KEY9;REPLY
                GOTO            USDEL15 IF OVER
                GOTO            USDEL14
*
.Read Through the Directory File
.
USDEL13         FILEPI          1;DIRFILE
                READKGTB        DIRFILE;REPLY
                GOTO            USDEL15 IF OVER
*
.Delete the Entry
.
USDEL14         ADD             ONE,NWORK1
                DISPLAY         *P75:24,NWORK1;
.
                FILEPI          1;DIRFILE
                DELETE          DIRFILE
                GOTO            USDEL13
*
.Open the Notepad Files as Needed
.
USDEL15         MOVE            OPENFLAG,REPLY
                AND             010,REPLY
                GOTO            USDEL16 IF NOT ZERO

                TRAP            TRAPIO IF IO         // Can't open a file             
                OPEN            NOTEFILA,FSN,SHARE
                OR              010,OPENFLAG
                TRAPCLR         IO
*
.Delete His Notes
.
USDEL16         PACK            KEYWORK WITH TWO,KEY6
                MOVE            ZERO,NWORK1
                DISPLAY         *HD,*EL,DELETING,USRNOTE;
.
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEYWORK;;
*
.Read Through the Note File
.
USDEL17         FILEPI          1;NOTEFILE
                READKSTB        NOTEFILE;KEY20
                GOTO            USDEL18 IF OVER
*
.Right User ?
.
                MATCH           KEYWORK,KEY20
                GOTO            USDEL18 IF NOT EQUAL
*
.Delete the Note
.
                ADD             ONE,NWORK1
                DISPLAY         *P75:24,NWORK1;
                CALL            AG2090
                GOTO            USDEL17
*
.Delete All His Alarms
.
USDEL18         PACK            KEYWORK WITH ONE,KEY6
                MOVE            ZERO,NWORK1
                DISPLAY         *HD,*EL,DELETING,USRALRM;
.
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEYWORK;;
*
.Read Through the Alarms File
.
USDEL19         FILEPI          1;NOTEFILE
                READKSTB        NOTEFILE;KEY20
                GOTO            USDEL20 IF OVER
*
.Right User ?
.
                MATCH           KEYWORK,KEY20
                GOTO            USDEL20 IF NOT EQUAL
*
.Delete the Alarm
.
                ADD             ONE,NWORK1
                DISPLAY         *P75:24,NWORK1;
.
                CALL            AG2090
                GOTO            USDEL19
*
.Open the Meeting Planner Files as Needed
.
USDEL20         MOVE            OPENFLAG,REPLY
                AND             004,REPLY
                GOTO            USDEL21 IF NOT ZERO
.
                TRAP            TRAPIO IF IO
                OPEN            PLAN,FSP,SHARE
                OPEN            PLAN1,FSP1,SHARE
                OR              004,OPENFLAG
                TRAPCLR         IO
*
.Delete All His Meetings
.
USDEL21         FILEPI          1;PLAN
                READ            PLAN,KEY6;;
.
                MOVE            ZERO,NWORK1
                DISPLAY         *HD,*EL,DELETING,USRPLAN;
*
.Read Through the Meeting File
.
USDEL22         FILEPI          1;PLAN
                READKSTB        PLAN;DIM6,DIM11,USRNO2
                GOTO            USDEL23 IF OVER
*
.Right User ?
.
                MATCH           KEY6,DIM6
                GOTO            USDEL23 IF NOT EQUAL
*
.Delete the Meeting
.
                ADD             ONE,NWORK1
                DISPLAY         *P75:24,NWORK1;
.
                PACK            KEY17 WITH DIM6,DIM11
                FILEPI          1;PLAN
                DELETE          PLAN,KEY17
                CALL            INTERR IF OVER
.
                PACK            DIM30 WITH USRNO2,DIM11,DIM6
                FILEPI          1;PLAN1
                DELETEK         PLAN1,DIM30
                CALL            INTERR IF OVER
                GOTO            USDEL22
*
.Finally, Delete the User Record
.
USDEL23         DISPLAY         *HD,*EL,DELETING,USRUSR;
.
                PACK            KEY9 WITH X02,KEY6
.
USDELF          FILEPI          3;USRFILE
                READ            USRFILE,KEY9;REPLY;
                GOTO            USDELG IF OVER
                DELETE          USRFILE
                GOTO            USDELF
*
.Did We Delete the Current User ?
.
USDELG          MOVE            KEY6,USRNO1
                COMPARE         USRNO1,CURRUSER
                GOTO            USNEXT1 IF NOT EQUAL
                MOVE            ZERO,LOGONSW
                GOTO            LOGON
*
.Abort the User Delete
.
USDEL27         DISPLAY         *P4:VPOS,*HOFF,USRNAME1;
                BRANCH          DTLCOUNT TO US$CMD
                GOTO            USLOC1
+..............................................................................
.
.                           U S E R   S E A R C H
...............................................................................
.
.
USSRCH          MOVE            TWENTY4,CMDTRAP                                        
                TRAP            USSRCH14 IF ESCAPE                                    
                TRAP            USSRCH14 IF F27                                         
*
.Allow Specification of a User Name
.
USSRCH1         MOVE            ZERO,FLAG3
                CLEAR           AKEY1
                CLEAR           AKEY2
.
                MOVE            ZERO,SWITCH
                MOVE            ONE,PAGE
.
                KEYIN           *SETSWTB 5:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,*DV,PAGE:
                                *HD,*EL,*DV,LITENT,*DV,USRNKEY:
                                *P4:5,*RPTCHAR "_":20,*H 4,*IT,DIM20;
                DISPLAY         *IN,*H 4,DIM20;
                GOTO            USSRCH14 IF F5
.
                CMATCH          " ",DIM20
                GOTO            USSRCH3 IF EOS                                         
*
.Construct the Name Key
.
                PACK            AKEY1 WITH F03,DIM20
                MOVE            ONE,FLAG3
                MOVE            DIM20,DIM30
                REP             CAPREP,DIM30
*
.Allow Specification of a Group
.
USSRCH3         KEYIN           *HD,*EL,*DV,LITENT,*DV,GRPDES:
                                *P31:5,*RPTCHAR "_":5,*H 31,UGROUP1;
                DISPLAY         *IN,*H 31,UGROUP1;
                GOTO            USSRCH1 IF F5
.
                CMATCH          " ",UGROUP1
                GOTO            USSRCH3 IF EQUAL
                GOTO            USSRCH4 IF EOS
                MOVE            ONE,FLAG3
*
.If One of the Keys is Specified, We'll Read Generically -
. Otherwise, We'll Read Sequentially
.
USSRCH4         MOVE            ZERO,DTLCOUNT
                MOVE            ZERO,EOFSW
.
                CALL            CLOCKDT
                PACK            KEYWORK WITH YEARWORK,JDAYWORK,HOURWORK,MINWORK
.
                BRANCH          FLAG3 TO USSRCH5
*
.Position for a Read Sequential
.
                FILEPI          2;USRFILE
                REPOSIT         USRFILE,ZERO
                READTAB         USRFILE,SEQ;REPLY
                GOTO            USSRCH8
*
.Construct the Group Key
.
USSRCH5         CLEAR           AKEY2
                BUMP            UGROUP1,0
                GOTO            USSRCH6 IF EOS
                PACK            AKEY2 WITH L04,UGROUP1
*
.Do the Initial Aim Read
.
USSRCH6         TRAP            USSRCH7 IF IO
                FILEPI          1;USRFILE
                READ            USRFILE,AKEY1,AKEY2;USERID,KEY6,USRNAME1,USREXT,LOFLAG:
                                UGROUP,STATDATE,STATTIME,STATFLAG,STATMSG,FMTIME,MEETFLG
                TRAPCLR         IO
                GOTO            USSRCH10 IF NOT OVER
.
                KEYIN           *CLICK,*HD,*EL,*DV,NOUSRS,REPLY;
                GOTO            USSRCH1
*
.Invalid Key Specification
.
USSRCH7         NORETURN
                KEYIN           *CLICK,*HD,*EL,*DV,INKEY,REPLY;
                GOTO            USSRCH1
*
.Determine the Correct Read Method
.
USSRCH8         BRANCH          FLAG3 TO USSRCH9
*
.Read Sequentially Through the File
.
                FILEPI          1;USRFILE
                READ            USRFILE,SEQ;USERID,KEY6,USRNAME1,USREXT,LOFLAG:
                                UGROUP,STATDATE,STATTIME,STATFLAG,STATMSG,FMTIME,MEETFLG
                GOTO            USSRCH13 IF OVER
                GOTO            USSRCH10
*
.Read Generically Through the User File
.
USSRCH9         FILEPI          1;USRFILE
                READKG          USRFILE;USERID,KEY6,USRNAME1,USREXT,LOFLAG,UGROUP:
                                STATDATE,STATTIME,STATFLAG,STATMSG,FMTIME,MEETFLG
                GOTO            USSRCH13 IF OVER
*
.Highlight the Specified Keys
.
USSRCH10        CLEAR           DIM30
                COMPARE         ZERO,FLAG3
                GOTO            USSRCHA IF EQUAL
.
                BUMP            AKEY1,0                                             
                GOTO            USSRCH11 IF EOS                                     
.
                MOVE            USRNAME1,DIM40
                REP             CAPREP,DIM40
                SCAN            DIM20,DIM40
*
.Compute the Horizontal Position of the Key
.
                MOVEFPTR        DIM40,HPOS1
                RESET           USRNAME1,HPOS1
                ADD             THREE,HPOS1
*
.Generate the Matching Key String
.
                MOVE            USRNAME1,DIM30
                MOVELPTR        DIM20,INDEX
                SETLPTR         DIM30,INDEX
*
.Primary or Secondary Group Designation ?
.
USSRCH11
                MATCH           BLANKS,USERID
                GOTO            USSRCHA IF NOT EQUAL    // Primary...
*
.Display a Secondary Group Record
.
                MOVE            ZERO,GROUPFLG
                DISPLAY         *H 4,*+,USRNAME1,*H HPOS1,*HON,DIM30,*HOFF:
                                *H 31,UGROUP,*H 31,*HON,UGROUP1,*HOFF:
                                *H 63,SECGRP
                GOTO            USSRCHB
*
.See if He Has Any New Messages
.
USSRCHA         MOVE            NO,DIM3
                MATCH           FMTIME,KEYWORK
                GOTO            USSRCH12 IF LESS
                MOVE            YES,DIM3
*
.Show 'Em the Information
.
USSRCH12        CALL            FIXSTATD
                MOVE            ONE,GROUPFLG
                DISPLAY         *H 3,*+,LOFLAG,USRNAME1,*H HPOS1,*HON,DIM30,*HOFF:
                                *H 25,USREXT,*H 31,UGROUP,*H 31,*HON,UGROUP1:
                                *HOFF,*H 37,DIM3,*H 42,STATFLAG:
                                *H 47,DIM6,*H 54,STATTIME,*H 63,STATMSG
*
.Save the Key
.
USSRCHB         PACK            KEY WITH KEY6,UGROUP,GROUPFLG
                ADD             ONE,DTLCOUNT
                STORE           KEY BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN:
                                KEYO,KEYP,KEYQ,KEYR
.
                COMPARE         "17",DTLCOUNT
                GOTO            USSRCH8 IF NOT EQUAL
                GOTO            US$CMD
*
.Indicate We Hit the End of File
.
USSRCH13        MOVE            ONE,EOFSW
                GOTO            US$CMD
*
.Abort the Search Routine
.
USSRCH14        NORETURN
                DISPLAY         *SETSWTB 5:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80:
                                *P79:5;                                               
                MOVE            CURRGRP,UGROUP1
                GOTO            USERS2
+..............................................................................
.
.                U S E R   S T A T U S   M O D I F I C A T I O N
...............................................................................
.
.
USSTAT          COMPARE         ZERO,DTLCOUNT
                GOTO            US$CMD1 IF EQUAL    No Records
                GOTO            USLOC
*
.Primary Records Only
.
USSTAT1
                BRANCH          GROUPFLG TO USSTATA
.
                KEYIN           *CLICK,*HD,*EL,*DV,STPRIGR:
                                REPLY;
                GOTO            USLOC1
*
.Get the New Status
.
USSTATA         MOVE            TWENTY5,CMDTRAP                                     
                TRAP            USSTAT2 IF ESCAPE                                    
                TRAP            USSTAT2 IF F27                                     
                RESET           REPLY
                KEYIN           *HD,*EL,*DV,IONA,*+,REPLY;
                GOTO            USLOC1 IF F5
.
                BUMP            REPLY,0
                GOTO            USSTAT1 IF EOS
.
                REP             IONAREP,REPLY
                MOVE            ZERO,INDEX
                MOVE            REPLY,INDEX
                COMPARE         ONE,INDEX
                GOTO            USSTAT1 IF LESS
                COMPARE         FOUR,INDEX
                GOTO            USSTAT1 IF NOT LESS
.
                LOAD            STATFLAG BY INDEX FROM OUT,IN,NA
*
.Get the Comment
.
                KEYIN           *P63:VPOS,*RPTCHAR "_":17,*H 63,*IT,STATMSG;
                DISPLAY         *IN,*H 63,STATMSG;
                GOTO            USSTAT1 IF F5
*
.Time and Date Stamp the Change
.
                TRAPCLR         ESCAPE                                               
                TRAPCLR         F27                                                
                CALL            CLOCKDT
                MOVE            DATE,STATDATE
                CALL            FIXSTATD
.
                DISPLAY         *H 42,STATFLAG,*H 47,DIM6,*H 54,TIME;
*
.Update the User's Record
.
                FILEPI          1;USRFILE
                UPDATAB         USRFILE;*48,STATDATE,TIME,STATFLAG,STATMSG
.
                DISPLAY         *HD,*EL,STCHG,*W;
*
.If We Changed the Current User, Update the Memory Information
.
                COMPARE         USRNO1,CURRUSER
                GOTO            USLOC1 IF NOT EQUAL
                MOVE            STATFLAG,CURRSTAT
                GOTO            USLOC1
*
.Abort Changing the Status
.
USSTAT2         NORETURN
                DISPLAY         *HOFF,*P2:VPOS,SPACE,*H 63,STATMSG;
                GOTO            US$CMD
+..............................................................................
.
.                      S Y S T E M   S H U T D O W N
...............................................................................
.
.
.Get the Security Password
.
USSTOP          CALL            KEYPASS              // ENTER SECURITY PASSWORD         
*
.Get the Current Date & Time
.
                CALL            CLOCKDT
                MOVE            DATE,ADATE
                MOVE            TIME,ATIME
*
.Get the Date and Time It Will Be Back
.
USSTOP1         DISPLAY         *HD,*EL,DTREST;
                MOVE            TWENTY4,VPOS
                MOVE            TWENTY2,HPOS
                MOVE            ZERO,MASKSW
                MOVE            ONE,REQFLAG
                CALL            GETDATE
                BRANCH          FLAG1 TO USSTOP
*
.Get the Time It Will Be Back
.
                DISPLAY         *H 40,TIMEMSG;
                MOVE            FORTY6,HPOS
                MOVE            ZERO,MASKSW
                MOVE            ONE,REQFLAG
                CALL            GETIME
                BRANCH          FLAG1 TO USSTOP1
*
.Get the Reason It Is Being Shutdown
.
USSTOP2         KEYIN           *HD,*EL,*DV,SDFOR,*RPTCHAR "_":40,*HA -40,*IT,DIM40;
                DISPLAY         *IN,*H 15,DIM40;
                BUMP            DIM40
                GOTO            USSTOP2 IF EOS
*
.See if Auto-Restart Requested
.
                DISPLAY         *HD,*EL,AUTOREST;                                 
                CALL            KREPLYN                                            
                GOTO            USSTOP2 IF F5
.
                MOVE            STAR,DIM1
                CMATCH          YES,REPLY                                          
                GOTO            USSTOP4 IF NOT EQUAL
                MOVE            C$,DIM1
*
.Write the Shutdown Information in the Control File
.
USSTOP4         FILEPI          1;CONTROL
                WRITE           CONTROL,ZERO;DIM1,CURRNAME,ADATE,ATIME,DATE,TIME:
                                YEARWORK,JDAYWORK,HOURWORK,MINWORK,DIM40
*
.Exit to AGENDA2
.
                NORETURN
                DISPLAY         *CLICK,*HD,*EL,SYSTSD;
                GOTO            START
.
. *** End ***
.
