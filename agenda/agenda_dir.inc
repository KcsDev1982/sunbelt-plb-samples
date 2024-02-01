*---------------------------------------------------------------
.
. Module Name: agenda_dir.inc
. Description: Telephone Directory Module
.
. Revision History:
.
.
.Open the Directory File
.
TD$CMD          MOVE            FOUR,TDFUNC
                MOVE            OPENFLAG,REPLY
                MOVE            ONE,PAGE
                AND             020,REPLY
                GOTO            TD$CMD1 IF NOT ZERO
.
                TRAP            TRAPIO IF IO
                OPEN            DIRFILE,FSD,SHARE
                OR              020,OPENFLAG
                TRAPCLR         IO
*
.Draw the Screen
.
TD$CMD1         NORETURN

TD$CMD2
                CALL            SHOWBOX1
                DISPLAY         *P30:1,TELDIR;                                         
.
                DISPLAY         *P1:23,*EL,*H 73,TELPAGE,PAGE,*HD,*EL:
                                *PNAMPOS:5,TELNAME:
                                *PADDPOS:9,TELADD:
                                *PCSPOS:11,TELCS:
                                *PZIPPOS:13,TELZIP:
                                *PFONPOS:15,TELPHONE:
                                *PNOTEPOS:17,TELNOTE;
*
.See What He Wants to Do
.
TD$CMD3         NORETURN
                MOVE            ZERO,CMDTRAP                                           
                DISPLAY         *HD,*EL,SPACE,CFUNC8,SPACE,AFUNC2,SPACE,MRFUNC5:
                                SPACE,FUNC7,SPACE,FUNC4;
                TRAP            LOGON IF ESCAPE                                           
                TRAP            LOGON IF F27                                              
                COMPARE         TMFLAG,ONE             // See where we are coming from.    
                IF              EQUAL                    // If we are coming from MSG. . .   
                DISPLAY         *P10:23,"         "    // Erase message display.          
                ELSE            			// If user chose DIR then . . .     
                CLEAR           FUNCDESC               // Clear the functions.            
                MOVE            ZERO,FLAG1             // Flag1 = 0                       
                CALL            CHKALRM                // Check for alarm,plan,message.    
                ENDIF                                     
                MOVE            ZERO,FLAG2
*
.Position the the Correct Function
.
TD$CMD4         LOAD            FUNCDESC BY TDFUNC FROM CFUNC8,AFUNC2,MRFUNC5:
                                FUNC7,FUNC4
.
                MOVE            TDFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           TDPOS,NWORK2
                MOVE            TDPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
TD$CMD5         COMPARE         TMFLAG,ONE                             // command ring if  
                GOTO            TDADD IF EQUAL                         // coming from MSG. 
                DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              LEFT                                                              
                CMOVE           LEFT,REPLY                                                
                ENDIF           032
                IF              RIGHT                                                              
                CMOVE           RIGHT,REPLY                                             
                ENDIF           032
                GOTO            TD$CMD10 IF F5
                GOTO            TD$CMD10 IF F9                                          
                GOTO            TD$CMD9 IF LESS
                GOTO            TD$CMD8 IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
.
                CMATCH          CMDKEY,REPLY                                            
                GOTO            LOGON IF EQUAL                                           
                GOTO            LOGON IF F27                                            
*
.Check for a Direction
.
                CMATCH          RIGHT,REPLY
                GOTO            TD$CMD6 IF EQUAL
                CMATCH          LEFT,REPLY
                GOTO            TD$CMD7 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            TD$CMD6 IF EQUAL
*
.Check for a Letter
.
                RESET           TDLETS
                SCAN            REPLY,TDLETS
                IF              NOT EQUAL               // Lower Case                          
                RESET           TDLETS2                                              
                SCAN            REPLY,TDLETS2                                        
                GOTO            TD$CMD5 IF NOT EQUAL                                  
                MOVEFPTR        TDLETS2,TDFUNC                                      
                GOTO            TD$CMD4                                            
                ENDIF           

                MOVEFPTR        TDLETS,TDFUNC
                GOTO            TD$CMD4
*
.Move Right to the Next Function
.
TD$CMD6         ADD             ONE,TDFUNC
                COMPARE         SIX,TDFUNC
                GOTO            TD$CMD4 IF NOT EQUAL
                MOVE            ONE,TDFUNC
                GOTO            TD$CMD4
*
.Move Left to the Next Function
.
TD$CMD7         SUB             ONE,TDFUNC
                GOTO            TD$CMD4 IF NOT ZERO
                MOVE            FIVE,TDFUNC
                GOTO            TD$CMD4
*
.We Have a Selected Funtion
.
TD$CMD8         BRANCH          TDFUNC TO TDADD,TDLOC,TDLOC,TDSEARCH,TDPRINT
                CALL            INTERR
*
.A Timeout Occurred
.
TD$CMD9         MOVE            ZERO,FLAG1
                CALL            CHKALRM
                DISPLAY         *P59:1,DATE,SPACE2,TIME;
                GOTO            TD$CMD5
*
.Help Requested
.
TD$CMD10        MOVE            SEVEN,HMENU
                MOVE            TDFUNC,HFUNCNO
                CALL            HELP
                GOTO            TD$CMD2
+..............................................................................
.
.                  D I R E C T O R Y    A D D I T I O N
...............................................................................
.
.
TDADD           MOVE            TWENTY6,CMDTRAP                                       
                MOVE            ONE,PAGE
.
                COMPARE         TMFLAG,ONE             // See where we are coming from.    
                IF              EQUAL                    // If we are coming from MSG. . .   
                TRAP            MESSAGE IF ESCAPE      // trap to there upon ESCAPE.      
                TRAP            MESSAGE IF F27                                           
                DISPLAY         *P25:5,CALLER;         // display the info that            
                DISPLAY         *P25:7,CALRINFO;       // is already available            
                DISPLAY         *P25:15,PHONE;         // from the telephone              
                ELSE            			// If user chose DIR then . . .    
                TRAP            TDADD10 IF ESCAPE                                        
                TRAP            TDADD10 IF F27                                            
                CLEAR           CALLER                 // Use orginal trap and clear out   
                CLEAR           CALRINFO               // the info fields.                 
                CLEAR           PHONE                                                     
                ENDIF           
*
.Get the Name for the Entry
.
TDADD1          COMPARE         TMFLAG,ONE                                                
                IF              EQUAL                                                       
                KEYIN           *HD,*EL,*DV,LITENT,*DV,NAMEENT,*P77:23,*DV,PAGE:         
                                *P25:5,*RPTCHAR "_":30,*H 25,*IT,*DV,CALLER:              
                                *H 25,*RV,CALLER;                                        
                ELSE            
                KEYIN           *HD,*EL,*DV,LITENT,*DV,NAMEENT,*P77:23,*DV,PAGE:
                                *P25:5,*RPTCHAR "_":30,*H 25,*IT,CALLER;
                ENDIF           
                DISPLAY         *IN,*H 25,CALLER;
.
                CMATCH          " ",CALLER
                GOTO            TDADD1 IF EQUAL
                GOTO            TDADD10 IF EOS
*
.Allow a 2nd Line of the Name
.
TDADD2          COMPARE         TMFLAG,ONE                                                
                IF              EQUAL                                                       
                KEYIN           *P25:7,*RPTCHAR "_":30,*H 25,*IT,*DV,CALRINFO,*H 25:     
                                *RV,CALRINFO;                  // Retain the caller 'of'.  
                ELSE           
                KEYIN           *P25:7,*RPTCHAR "_":30,*H 25,*IT,CALRINFO;
                ENDIF           
                DISPLAY         *IN,*H 25,CALRINFO;
                GOTO            TDADD1 IF F5
*
.Get the Address
.
TDADD3          KEYIN           *HD,*EL,*DV,LITENT,*DV,ADDENT:
                                *P25:9,*RPTCHAR "_":30,*H 25,*IT,ADDRESS;
                DISPLAY         *IN,*H 25,ADDRESS;
                GOTO            TDADD2 IF F5
*
.Get the City and State
.
TDADD4          KEYIN           *HD,*EL,*DV,LITENT,*DV,CSENT:
                                *P25:11,*RPTCHAR "_":30,*H 25,*IT,CITYST;
                DISPLAY         *IN,*H 25,CITYST;
                GOTO            TDADD3 IF F5
*
.Get the Zipcode
.
TDADD5          KEYIN           *HD,*EL,*DV,LITENT,*DV,ZIPENT:
                                *P25:13,*RPTCHAR "_":10,*H 25,*IT,ZIPCODE;
                DISPLAY         *IN,*H 25,ZIPCODE;
                GOTO            TDADD4 IF F5
*
.Get the Phone Number
.
TDADD6          COMPARE         TMFLAG,ONE                                                
                IF              EQUAL                                                      
                KEYIN           *HD,*EL,*DV,LITENT,*DV,PHENT:                          
                                *P25:15,*RPTCHAR "_":20,*H 25,*DV:                     
                                PHONE,*H 25,*RV,PHONE;                                
                ELSE            
                KEYIN           *HD,*EL,*DV,LITENT,*DV,PHENT:
                                *P25:15,*RPTCHAR "_":20,*H 25,PHONE;
                ENDIF           
                DISPLAY         *H 25,PHONE;
                GOTO            TDADD5 IF F5
*
.Get the Note
.
TDADD7          KEYIN           *HD,*EL,*DV,NOTEENT:
                                *P25:17,*RPTCHAR "_":30,*H 25,*IT,NOTE;
                DISPLAY         *IN,*H 25,NOTE;
                GOTO            TDADD6 IF F5
*
.Is This a Personal Entry ?
.
TDADD8          MOVE            SIX0,KEY6
                DISPLAY         *HD,*EL,TELALLOW;                                  
                CALL            KREPLYY                                            
                GOTO            TDADD7 IF F5
.
                MOVE            SPACE,DIM1
                CMATCH          YES,REPLY                                           
                GOTO            TDADD9 IF EQUAL
                CMATCH          NO,REPLY                                            
                GOTO            TDADD8 IF NOT EQUAL
                MOVE            USRNO,KEY6
                MOVE            STAR,DIM1
.
TDADD9          DISPLAY         *P24:5,DIM1;
*
.Write the Directory Entry to Disk
.
                FILEPI          1;DIRFILE
                WRITE           DIRFILE;KEY6,CALLER,CALRINFO,ADDRESS:
                                CITYST,ZIPCODE,PHONE,NOTE
*
.Erase the Screen and Continue Adding
.
                DISPLAY         *HD,*EL,ENTADDED,*W:
                                *SETSWTB 5:17,*SETSWLR 23:79,*ES,*SETSWALL=1:24:1:80;
                ADD             ONE,PAGE
                COMPARE         TMFLAG,ONE                   // If we came from Message   
                GOTO            MESSAGE IF EQUAL             // then go back to Message.   
                GOTO            TDADD1
*
.Abort Adding the Entry
.
TDADD10         NORETURN
                DISPLAY         *SETSWTB 5:17,*SETSWLR 23:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,*RPTCHAR " ":3;
                GOTO            TD$CMD3
+..............................................................................
.
.                D I R E C T O R Y   E N T R Y   S E L E C T I O N
...............................................................................
.
.Use the Search Routine to Locate the Correct Entry
.
TDLOC           MOVE            YES,REPLY
                MOVE            ONE,SWITCH
                MOVE            ZERO,PAGE
                GOTO            TDSRCH1
*
.Correct Entry ?
.
TDLOC1
                DISPLAY         *HD,*EL,CORENT;                                   
                CALL            KREPLYN                                            
                GOTO            TDSRCH14 IF F5
                CMATCH          YES,REPLY                                              
                GOTO            TDLOC2 IF EQUAL
.
                DISPLAY         *SETSWTB 5:17,*SETSWLR 23:79,*ES,*SETSWALL=1:24:1:80,*HD,*EL;
                GOTO            TDSRCH7
*
.Branch to the Correct Function
.
TDLOC2          BRANCH          TDFUNC TO TDLOC3,TDCHG,TDDEL
.
TDLOC3          CALL            INTERR
+..............................................................................
.
.             D I R E C T O R Y   E N T R Y   M O D I F I C A T I O N
...............................................................................
.
.
.Display the Name & Note Without Highlighting
.
TDCHG           DISPLAY         *P25:5,CALLER,*P25:17,NOTE
*
.Allow Changing the Name
.
TDCHG1          KEYIN           *P25:5,*DV,CALLER:
                                *HD,*EL,*DV,LITENT,*DV,NAMEENT,*P25:5,*IT,*RV,CALLER;
                DISPLAY         *IN,*H 25,CALLER;
                GOTO            TDSRCH7 IF F5
*
.Allow Changing the 2nd Line of the Name
.
TDCHG2          KEYIN           *P25:7,*DV,CALRINFO,*H 25,*IT,*RV,CALRINFO;
                DISPLAY         *IN,*H 25,CALRINFO;
                GOTO            TDCHG1 IF F5
*
.Allow Changing the Address
.
TDCHG3          KEYIN           *P25:9,*DV,ADDRESS,*HD,*EL,*DV,LITENT,*DV,ADDENT:
                                *P25:9,*IT,*RV,ADDRESS;
                DISPLAY         *IN,*H 25,ADDRESS;
                GOTO            TDCHG2 IF F5
*
.Allow Changing the City & State
.
TDCHG4          KEYIN           *P25:11,*DV,CITYST,*HD,*EL,*DV,LITENT,*DV,CSENT:
                                *P25:11,*IT,*RV,CITYST;
                DISPLAY         *IN,*H 25,CITYST;
                GOTO            TDCHG3 IF F5
*
.Allow Changing the Zipcode
.
TDCHG5          KEYIN           *P25:13,*DV,ZIPCODE,*HD,*EL,*DV,LITENT,*DV,ZIPENT:
                                *P25:13,*RV,ZIPCODE;
                DISPLAY         *H 25,ZIPCODE;
                GOTO            TDCHG4 IF F5
*
.Allow Changing the Phone Number
.
TDCHG6          KEYIN           *P25:15,*DV,PHONE,*HD,*EL,*DV,LITENT,*DV,PHENT:
                                *P25:15,*RV,PHONE;
                DISPLAY         *H 25,PHONE;
                GOTO            TDCHG5 IF F5
*
.Allow Changing the Note
.
TDCHG7          KEYIN           *P25:17,*DV,NOTE,*HD,*EL,*DV,NTENT:
                                *P25:17,*IT,*RV,NOTE;
                DISPLAY         *IN,*H 25,NOTE;
                GOTO            TDCHG6 IF F5
*
.Allow Changing the Private Flag
.
                MOVE            YES,REPLY
                COMPARE         ZERO,USRNO1
                GOTO            TDCHG8 IF EQUAL
                CMOVE           NO TO REPLY                                        
.
TDCHG8          KEYIN           *HD,*EL,*DV,PRENT:
                                *DV,REPLY,*HA -1,*RV,REPLY;
                CALL            KREPLYZZ                                           
                GOTO            TDCHG7 IF F5
.
                MOVE            USRNO,KEY6
                MOVE            STAR,DIM1
.
                CMATCH          NO,REPLY                                             
                GOTO            TDCHG9 IF EQUAL
                CMATCH          YES,REPLY                                           
                GOTO            TDCHG8 IF NOT EQUAL
.
                MOVE            SIX0,KEY6                                            
                MOVE            SPACE,DIM1
*
.Delete and Rewrite the Record
.
TDCHG9          DISPLAY         *P24:5,DIM1;
.
                FILEPI          2;DIRFILE
                DELETE          DIRFILE
.
                WRITE           DIRFILE;KEY6,CALLER,CALRINFO,ADDRESS:
                                CITYST,ZIPCODE,PHONE,NOTE
.
                DISPLAY         *HD,*EL,ENTCH,*W:
                                *SETSWTB 5:17,*SETSWLR 23:79,*ES,*SETSWALL=1:24:1:80;
                GOTO            TD$CMD3
+..............................................................................
.
.              D I R E C T O R Y   E N T R Y   D E L E T I O N
...............................................................................
.
.
.Make Sure They Want to Delete It
.
TDDEL
                DISPLAY         *HD,*EL,DELENT;                                    
                CALL            KREPLYN                                          
                CMATCH          YES,REPLY                                        
                GOTO            TDSRCH14 IF NOT EQUAL
*
.Delete the Entry
.
                FILEPI          1;DIRFILE
                DELETE          DIRFILE
.
                DISPLAY         *HD,*EL,ENTDEL,*W2:
                                *SETSWTB 5:17,*SETSWLR 23:79,*ES,*SETSWALL=1:24:1:80;
                GOTO            TDSRCH7
+..............................................................................
.
.                      D I R E C T O R Y   S E A R C H
...............................................................................
.
.
TDSEARCH        MOVE            TWENTY7,CMDTRAP                                         
                TRAP            TD$CMD3 IF ESCAPE                                     
                TRAP            TD$CMD3 IF F27                                        
                MOVE            CS,REPLY
                KEYIN           *HD,*EL,*DV,LSDIS,*HA -1,*RV,REPLY;
                GOTO            TD$CMD3 IF F5
.
                CMATCH          SHORTCH,REPLY
                GOTO            TDSRCH16 IF EQUAL
*
.Signify Search Mode, Not Locate Mode
.
                MOVE            ZERO,SWITCH
                MOVE            ZERO,PAGE
.
TDSRCH1         MOVE            TWENTY8,CMDTRAP                                     
                TRAP            TDSRCH15 IF ESCAPE                                   
                TRAP            TDSRCH15 IF F27                                     
                MOVE            ONE,FLAG2
*
.Get the Name Key
.
TDSRCH2         KEYIN           *HD,*EL,*DV,LITENT,*DV,NMKEY:
                                *P25:5,*RPTCHAR "_":15,*IT,*H 25,DIM20;
                DISPLAY         *IN,*H 25,DIM20;
*
.See if Enough for a Key
.
                CLEAR           KEYA
                CLEAR           DIM30
                BUMP            DIM20,0
                GOTO            TDSRCH4 IF EOS
.
*
.Construct the Name Key
.
                RESET           DIM20
                PACK            KEYA USING ZERO,CTWO,"F",DIM20   // F to "F"             
.
                REP             CAPREP,DIM20
                MOVE            ZERO,FLAG2
*
.Get the Note Key
.
TDSRCH4         KEYIN           *HD,*EL,*DV,LITENT,*DV,NTKEY:
                                *P25:17,*RPTCHAR "_":15,*H 25,*IT,DIM15;
                DISPLAY         *IN,*H 25,DIM15;
                GOTO            TDSRCH2 IF F5
*
.See if He Specified a Key
.
                CLEAR           KEYB
                CLEAR           DIM40
                BUMP            DIM15,0
                GOTO            TDSRCH6 IF EOS
*
.Build the Note Key
.
                RESET           DIM15
                PACK            KEYB WITH F03,DIM15
.
                REP             CAPREP,DIM15
                MOVE            ZERO,FLAG2
*
.Make Sure We Have at Least One Valid Key
.
TDSRCH6         BRANCH          FLAG2 TO TDSRCH2
*
.Do the Initial Read
.
                TRAP            TDSRCH13 IF IO
                FILEPI          1;DIRFILE
                READ            DIRFILE,KEYA,KEYB;KEY6,CALLER,CALRINFO:            
                                ADDRESS,CITYST,ZIPCODE,PHONE,NOTE                   
                GOTO            TDSRCH12 IF OVER
                MATCH           KEY6,ZERO5SP                                         
                IF              EQUAL                                                         
                MOVE            ZERO,KEY6                                             
                ENDIF           
                MOVE            KEY6,USRNO1                                           
                TRAPCLR         IO
                GOTO            TDSRCH8
*
.Read Genericly Through the Directory File
.
TDSRCH7         FILEPI          1;DIRFILE
                READKG          DIRFILE;KEY6,CALLER,CALRINFO:                         
                                ADDRESS,CITYST,ZIPCODE,PHONE,NOTE                   
                GOTO            TDSRCH12 IF OVER
                MATCH           KEY6,ZERO5SP                                        
                IF              EQUAL                                                         
                MOVE            ZERO,KEY6                                             
                ENDIF          
                MOVE            KEY6,USRNO1                                          
*
.Right User or Public Number ?
.
TDSRCH8         MOVE            SPACE,REPLY
                COMPARE         ZERO,USRNO1
                GOTO            TDSRCH9 IF EQUAL        Public Number
.
                COMPARE         USRNO,USRNO1
                GOTO            TDSRCH7 IF NOT EQUAL    Wrong User
                MOVE            STAR,REPLY
*
.Highlight the Name Key
.
TDSRCH9         BUMP            DIM20,0
                GOTO            TDSRCH10 IF EOS
.
                MOVE            CALLER,DIM30
                REP             CAPREP,DIM30
                SCAN            DIM20,DIM30
                CALL            INTERR IF NOT EQUAL
.
                MOVEFPTR        DIM30,NWORK1
                RESET           CALLER,NWORK1
                MOVE            CALLER,DIM30
                RESET           CALLER
.
                MOVELPTR        DIM20,VPOS
                SETLPTR         DIM30,VPOS
*
.Highlight the Note Key
.
TDSRCH10        BUMP            DIM15,0
                GOTO            TDSRCH11 IF EOS
.
                MOVE            NOTE,DIM40
                REP             CAPREP,DIM40
                SCAN            DIM15,DIM40
                CALL            INTERR IF NOT EQUAL
.
                MOVEFPTR        DIM40,NWORK2
                RESET           NOTE,NWORK2
                MOVE            NOTE,DIM40
                RESET           NOTE
.
                MOVELPTR        DIM15,VPOS
                SETLPTR         DIM40,VPOS
*
.Display the Information
.
TDSRCH11        ADD             ONE,PAGE
                DISPLAY         *P24:5,*+,REPLY,CALLER,*H 24,*HA NWORK1,*HON,DIM30,*HOFF:
                                *P25:7,CALRINFO,*P25:9,ADDRESS,*P25:11,CITYST:
                                *P25:13,ZIPCODE,*P25:15,PHONE:
                                *P25:17,NOTE,*H 24,*HA NWORK2,*HON,DIM40,*HOFF:
                                *P77:23,PAGE;
*
.If Locating, Return to Locate Routine
.
                BRANCH          SWITCH TO TDLOC1
*
.See if He Wants More
.
                DISPLAY         *HD,*EL,CTSRCH;                                   
                CALL            KREPLYY                                           
                DISPLAY         *SETSWTB 5:17,*SETSWLR 23:79,*ES,*SETSWALL=1:24:1:80:        
                                *P77:23,*RPTCHAR " ":23,*HD,*EL;                 
.
                CMATCH          NO,REPLY                                            
                GOTO            TDSRCH7 IF NOT EQUAL
.
                MOVE            ZERO,PAGE
                GOTO            TDSRCH2
*
.End of Matching Records
.
TDSRCH12        KEYIN           *CLICK,*HD,*EL,*DV,NMME,REPLY;
                GOTO            TDSRCH14
*
.Invalid Key Specified
.
TDSRCH13        NORETURN
                KEYIN           *CLICK,*HD,*EL,*DV,IKSPEC,REPLY;
.
TDSRCH14        DISPLAY         *SETSWTB 5:17,*SETSWLR 23:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,*RPTCHAR " ":3;
                MOVE            ZERO,PAGE
                GOTO            TDSRCH2
*
.Abort the Search Routine
.
TDSRCH15        NORETURN
                DISPLAY         *SETSWTB 5:17,*SETSWLR 23:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,*RPTCHAR " ":3;
                GOTO            TD$CMD3
*...........................................................................
.
.Short Display
.
TDSRCH16        MOVE            TWENTY9,CMDTRAP                                        
                TRAP            TDSRCH31 IF ESCAPE                                   
                TRAP            TDSRCH31 IF F27                                        
                DISPLAY         *SETSWTB 4:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,*RPTCHAR " ":3:
                                *P15:4,DIRNM,*H 40,DIRPH,*H 64,DIRNT:
                                *P2:5,*RPTCHAR HB:30,SPACE,*RPTCHAR HB:20,SPACE:
                                *RPTCHAR HB:25;
.
TDSRCH17        KEYIN           *HD,*EL,*DV,LITENT,*DV,NMKEY:
                                *P3:6,*RPTCHAR "_":20,*H 3,*IT,DIM20;
                DISPLAY         *IN,*H 3,DIM20;
*
.See if Enough for a Key
.
                MOVE            ONE,FLAG2
                CLEAR           KEYA
                CLEAR           DIM30
                BUMP            DIM20,0
                GOTO            TDSRCH19 IF EOS
.
*
.Construct the Name Key
.
                RESET           DIM20
.
                PACK            KEYA USING ZERO,CTWO,"F",DIM20  // F to "F"          
.
                REP             CAPREP,DIM20
                MOVE            ZERO,FLAG2
*
.Get the Note Key
.
TDSRCH19        KEYIN           *HD,*EL,*DV,LITENT,*DV,NTKEY:
                                *P54:6,*RPTCHAR "_":15,*H 54,*IT,DIM15;
                DISPLAY         *IN,*H 54,DIM15;
                GOTO            TDSRCH17 IF F5
*
.See if He Specified a Key
.
                CLEAR           KEYB
                CLEAR           DIM40
                BUMP            DIM15,0
                GOTO            TDSRCH21 IF EOS
*
.Build the Note Key
.
                RESET           DIM15
                PACK            KEYB WITH F03,DIM15
.
                REP             CAPREP,DIM15
                MOVE            ZERO,FLAG2
*
.Make Sure We Have at Least One Valid Key
.
TDSRCH21        BRANCH          FLAG2 TO TDSRCH17
*
.Do the Initial Read
.
                TRAP            TDSRCH29 IF IO
                FILEPI          1;DIRFILE
                READ            DIRFILE,KEYA,KEYB;KEY6,CALLER,CALRINFO:              
                                ADDRESS,CITYST,ZIPCODE,PHONE,NOTE                   
                GOTO            TDSRCH28 IF OVER
                MATCH           KEY6,ZERO5SP                                          
                IF              EQUAL                                                         
                MOVE            ZERO,KEY6                                             
                ENDIF           048
                MOVE            KEY6,USRNO1                                           
                TRAPCLR         IO
.
                MOVE            ONE,PAGE
                DISPLAY         *P77:23,PAGE;
                MOVE            FIVE,VPOS
                GOTO            TDSRCH23
*
.Read Genericly Through the Directory File
.
TDSRCH22        FILEPI          1;DIRFILE
                READKG          DIRFILE;KEY6,CALLER,CALRINFO:                        
                                ADDRESS,CITYST,ZIPCODE,PHONE,NOTE                   
                GOTO            TDSRCH28 IF OVER
                MATCH           KEY6,ZERO5SP                                          
                IF              EQUAL                                                        
                MOVE            ZERO,KEY6                                             
                ENDIF           048
                MOVE            KEY6,USRNO1                                         
*
.Right User or Public Number ?
.
TDSRCH23        MOVE            SPACE,DIM1
                COMPARE         ZERO,USRNO1
                GOTO            TDSRCH24 IF EQUAL        // Public Number
.
                COMPARE         USRNO,USRNO1
                GOTO            TDSRCH22 IF NOT EQUAL    // Wrong User
                MOVE            STAR,DIM1
*
.Locate the Name Key
.
TDSRCH24        BUMP            DIM20,0
                GOTO            TDSRCH25 IF EOS
.
                MOVE            CALLER,DIM30
                REP             CAPREP,DIM30
                SCAN            DIM20,DIM30
                CALL            INTERR IF NOT EQUAL
.
                MOVEFPTR        DIM30,NWORK1
.
                RESET           CALLER,NWORK1
                MOVE            CALLER,DIM30
                RESET           CALLER
.
                MOVELPTR        DIM20,NWORK3
                SETLPTR         DIM30,NWORK3
                ADD             TWO,NWORK1
*
.Locate the Note Key
.
TDSRCH25        BUMP            DIM15,0
                GOTO            TDSRCH26 IF EOS
.
                MOVE            NOTE,DIM40
                REP             CAPREP,DIM40
                SCAN            DIM15,DIM40
                CALL            INTERR IF NOT EQUAL
.
                MOVEFPTR        DIM40,NWORK2
                RESET           NOTE,NWORK2
                MOVE            NOTE,DIM40
                RESET           NOTE
.
                MOVELPTR        DIM15,NWORK3
                SETLPTR         DIM40,NWORK3
                ADD             "53",NWORK2
*
.Check for a Full Screen
.
TDSRCH26        ADD             ONE,VPOS
                COMPARE         TWENTY2,VPOS
                GOTO            TDSRCH27 IF NOT EQUAL
.
                DISPLAY         *HD,*EL,CTSRCH;                                    
                CALL            KREPLYY                                           
                DISPLAY         *SETSWTB 7:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80;         
.
                CMATCH          NO,REPLY                                            
                GOTO            TDSRCH30 IF EQUAL
.
                ADD             ONE,PAGE
                MOVE            SIX,VPOS
                DISPLAY         *SETSWTB 6:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,PAGE;
*
.Display the Information
.
TDSRCH27        DISPLAY         *SETSWLR 1:79:
                                *P2:VPOS,*+,DIM1,CALLER,*H NWORK1,*HON,DIM30,*HOFF:
                                *H 33,PHONE,*H 54,NOTE,*H NWORK2,*HON,DIM40,*HOFF:
                                *SETSWALL=1:24:1:80;
                GOTO            TDSRCH22
*
.End of Matching Records
.
TDSRCH28        KEYIN           *CLICK,*HD,*EL,*DV,NMME,REPLY;
                GOTO            TDSRCH30
*
.Invalid Key Specified
.
TDSRCH29        NORETURN
                KEYIN           *CLICK,*HD,*EL,*DV,IKSPEC,REPLY;
.
TDSRCH30        DISPLAY         *SETSWTB 6:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,*RPTCHAR " ":3;
                GOTO            TDSRCH17
*
.Abort the Search Routine
.
TDSRCH31        NORETURN
                DISPLAY         *SETSWTB 3:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,*RPTCHAR " ":3;
                GOTO            TD$CMD2
+..............................................................................
.
.                     D I R E C T O R Y   P R I N T I N G
...............................................................................
.
.
.See if He Wants Only Personal Numbers
.
TDPRINT
                MOVE            TWENTY7,CMDTRAP                                        
                TRAP            TD$CMD3 IF ESCAPE                                      
                TRAP            TD$CMD3 IF F27                                         
TDPRINT0
                MOVE            CN,DIM1
                KEYIN           *HD,*EL,*DV,PNO,*HA -1,*RV,DIM1;
                AND             0137 TO REPLY                                     
.
                MOVE            ZERO,FLAG2
                CMATCH          YES,DIM1                                           
                GOTO            TDPRINT1 IF EQUAL
                CMATCH          NO,DIM1                                             
                GOTO            TDPRINT0 IF NOT EQUAL
                MOVE            ONE,FLAG2
*
.Make Sure We Have a Printer
.
TDPRINT1        CALL            SPOOL
                BRANCH          FLAG1 TO TD$CMD1
                MOVE            THIRTY,CMDTRAP                                          
                TRAP            TDPRNT13 IF ESCAPE                                     
                TRAP            TDPRNT13 IF F27                                       
*
.Build a Work File Containing the Selected Entries
.
                DISPLAY         *HD,*EL,SELREC;
                MOVE            ZERO,NWORK1
                CALL            AG9000                                            
                REPOSIT         DIRFILE,ZERO
*
.Read Through the Directory File Sequentially
.
TDPRINT2        FILEPI          1;DIRFILE
                READ            DIRFILE,SEQ;USRNO1,CALLER,CALRINFO,ADDRESS:
                                CITYST,ZIPCODE,PHONE,NOTE
                GOTO            TDPRINT7 IF OVER
.
                MOVE            ZERO,NWORK2
                BRANCH          FLAG2 TO TDPRINT3           // Print Everything
*
.Right User ?
.
                COMPARE         CURRUSER,USRNO1             // Current User's Private Number ?
                GOTO            TDPRINT3 IF EQUAL           // Yes...
                COMPARE         ZERO,USRNO1                 // Personal Number ?
                GOTO            TDPRINT2 IF NOT EQUAL      //  Yes...
                CMATCH          YES,DIM1                    // Printing Personal Yes ?    
                GOTO            TDPRINT2 IF EQUAL           // Yes...
*
.Write the Record to the Work File
.
TDPRINT3        ADD             ONE,NWORK2
                PACK            KEYA WITH CALLER,NWORK2
                READ            SCRATCHI,KEYA;REPLY
                GOTO            TDPRINT3 IF NOT OVER
.
                WRITE           SCRATCHI,KEYA;USRNO1,CALLER,NWORK2,CALRINFO,ADDRESS:
                                CITYST,ZIPCODE,PHONE,NOTE
                ADD             ONE,NWORK1
                DISPLAY         *P75:24,NWORK1;
                GOTO            TDPRINT2
*
.Print the Directory
.
TDPRINT7        DISPLAY         *HD,*EL,PIP;
.
                COUNT           NWORK1,USRNAME
                MOVE            TWENTY,NWORK2
                SUB             NWORK1,NWORK2
                DIV             TWO,NWORK2
.
                MOVE            BLANKS,USRNAME1
                RESET           USRNAME1,NWORK2
                APPEND          USRNAME,USRNAME1
                RESET           USRNAME1
*
.Make the Current Date Looks Good
.
                CALL            CLOCKDT
                LOAD            DIM30 BY MONWORK FROM JAN,FEB,MAR:
                                APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC

                PACK            DIM40 USING DIM30,SPACE,DAYWORK,COMMA,SPACE,YEARPREFIX:
                                YEARWORK
.
                MOVELPTR        DIM40,NWORK1
                MOVE            FORTY,NWORK2
                SUB             NWORK1,NWORK2
                DIV             TWO,NWORK2
                ADD             THIRTY,NWORK2
*
.Print the Cover Page
.
                PRINT           *F,*L,*L,*L,*L,*L,*L,*L,*L,*L,*L,*L:
                                *L,*L,*L,*L,*L,*L,*L,*L,*L,*L,*L,*L:
                                *30,PHDIR:
                                *L,*L,*L,*L,*40,USRNAME1:
                                *L,*L,*L,*L,*L,*L,*L,*L,*L,*L,*L,*L:
                                *L,*L,*L,*L,*L,*L,*L,*L,*L,*L,*L,*L:
                                *L,*L,*L,*L,*L,*L,*L,*L,*L,*L:
                                *NWORK2,DIM40
.
                MOVE            ZERO,PAGE
                MOVE            BLANKS,KEYA
*
.Print the Top of Page
.
TDPRINT8        ADD             ONE,PAGE
                MOVE            SIX,LINE
                DISPLAY         *P77:23,PAGE;
.
                PRINT           *F,*L,*L,*5,TELDIR,*60,PHPG,PAGE,*L,*L
*
.Find the Position 7 Entries Down
.
                READ            SCRATCHI,KEYA;;
                MOVE            SIX,NWORK1
                MOVE            ZERO,FLAG1                            // In Case EOF
.
TDPRNT9         READKS          SCRATCHI;USRNO1,CALLER,NWORK2,CALRINFO,ADDRESS:
                                CITYST,ZIPCODE,PHONE,NOTE
                GOTO            TDPRNTXX IF OVER                     // Not 7 More Entries
.
                SUB             ONE,NWORK1
                GOTO            TDPRNT9 IF NOT ZERO
*
.Note This Position
.
                PACK            KEYB WITH CALLER,NWORK2
                GOTO            TDPRNT10
.
TDPRNTXX        MOVE            ONE,FLAG1                     // Signify No Entries in Column 2
                MOVE            SPACE TO CALLER1
                MOVE            SPACE TO CALRINF1
                MOVE            SPACE TO ADDRESS1
                MOVE            SPACE TO CITYST1
                MOVE            SPACE TO ZIPCODE1
                MOVE            SPACE TO PHONE1
                MOVE            SPACE TO NOTE1
*
.At This Point, KEYA = Left Column Starting File Position
.               KEYB = Right Column Starting File Position
.                      (EOF if Left Column Only)
.
.Get the Left Column Entry
.
TDPRNT10        READ            SCRATCHI,KEYA;REPLY
                READKS          SCRATCHI;USRNO1,CALLER,NWORK2,CALRINFO,ADDRESS:
                                CITYST,ZIPCODE,PHONE,NOTE
                GOTO            TDPRNT13 IF OVER
.
                PACK            KEYA WITH CALLER,NWORK2
*
.Get the Right Column Entry
.
                BRANCH          FLAG1 TO TDPRNTZ1
.
                READ            SCRATCHI,KEYB;REPLY
                READKS          SCRATCHI;USRNO2,CALLER1,NWORK2,CALRINF1,ADDRESS1:
                                CITYST1,ZIPCODE1,PHONE1,NOTE1
                GOTO            TDPRNTZ2 IF NOT OVER
.
                MOVE            ONE,FLAG1
.
TDPRNTZ2        PACK            KEYB WITH CALLER1,NWORK2
*
.Print Both Entries
.
TDPRNTZ1        PRINT           *N,*N,*7,"** ",CALLER;
.
                BRANCH          FLAG1 TO TDPRNT11
                PRINT           *47,"** ",CALLER1;
.
TDPRNT11        PRINT           *N,*10,CALRINFO,*50,CALRINF1:
                                *N,*10,ADDRESS,*50,ADDRESS1:
                                *N,*10,CITYST,*50,CITYST1:
                                *N,*10,ZIPCODE,*50,ZIPCODE1:
                                *N,*10,PHONE,*50,PHONE1:
                                *N,*10,NOTE,*50,NOTE1
*
.Check for a Full Page
.
                SUB             ONE,LINE
                GOTO            TDPRNT10 IF NOT ZERO
.
                BRANCH          FLAG1 TO TDPRNT13
                MOVE            KEYB,KEYA
                GOTO            TDPRINT8
*
.Printing Complete
.
TDPRNT13        NORETURN
                RELEASE
                SPLCLOSE

                CALL            AG9005
.
                DISPLAY         *CLICK,*HD,*EL,PRTCMPL,*W2,*P77:23,*EL;
                GOTO            TD$CMD3
.
. *** End ***
.
