*---------------------------------------------------------------
.
. Module Name: agenda_note.inc
. Description: Desk Notepad Module
.
. Revision History:
.
.
.Open the Files as Needed
.
NOTEPAD         MOVE            OPENFLAG,REPLY
                AND             010,REPLY
                GOTO            NOTEPAD1 IF NOT ZERO

                TRAP            TRAPIO IF IO
                OPEN            NOTEFILA,FSN,SHARE                                                                 
                OR              010,OPENFLAG
                TRAPCLR         IO
*
.Draw the Screen
.
NOTEPAD1        MOVE            ZERO,LINE            // Force a Heading
                MOVE            ONE,PAGE
                MOVE            TWO,RECTYPE
                CALL            CLOCKDT
.
                CALL            SHOWBOXN
*
.Position to the User's Notes
.
NOTEPAD2        NORETURN
                PACK            KEYWORK WITH RECTYPE,CURRUSER
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEYWORK;;
*
.Display the First Screen of Notes
.
NOTEPAD3        MOVE            ONE,EOFSW
                MOVE            ZERO,DTLCOUNT
                MOVE            ZERO,COUNT
                MOVE            ZERO,SWITCH
                MOVE            FOUR,VPOS
*
.Read Through the Notepad File
.
NOTEPAD4        FILEPI          1;NOTEFILE
                READKS          NOTEFILE;KEY20,DATE,TIME,DATA
                GOTO            NOTEPAD7 IF OVER
*
.Right User ?
.
                MATCH           KEYWORK,KEY20
                GOTO            NOTEPAD7 IF NOT EQUAL
*
.Is This the 1st Line of a Note ?
.
                RESET           KEY20,19
                MATCH           " 1",KEY20
                RESET           KEY20
                GOTO            NOTEPAD6 IF NOT EQUAL
*
.Is This the 1st Line on the Screen ?
.
                COMPARE         ZERO,DTLCOUNT
                GOTO            NOTEPAD5 IF EQUAL
*
.Double Space Between Notes
.
                COMPARE         TWENTY1,VPOS
                GOTO            NP$CMD1 IF EQUAL
                ADD             ONE,VPOS
*
.Display the Time and Date with the First Line
.
NOTEPAD5        DISPLAY         *P3:VPOS,DATE,*H 15,TIME;
                ADD             ONE,COUNT
.
                COMPARE         ZERO,DTLCOUNT
                GOTO            NOTEPAD6 IF EQUAL
.
                ADD             ONE,DTLCOUNT
                CLEAR           KEY6
                STORE           KEY6 BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN:
                                KEYO,KEYP,KEYQ,KEYR
*
.Display the Note
.
NOTEPAD6        DISPLAY         *P24:VPOS,DATA;
*
.Save the Record's Key
.
                ADD             ONE,DTLCOUNT
                STORE           KEY20 BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN:
                                KEYO,KEYP,KEYQ,KEYR
*
.Is the Screen Full ?
.
                COMPARE         TWENTY1,VPOS
                GOTO            NP$CMD1 IF EQUAL      // Yes...
                ADD             ONE,VPOS
                GOTO            NOTEPAD4
*
.Indicate We Encountered the End of File
.
NOTEPAD7        MOVE            ZERO,EOFSW
+..............................................................................
.
.                  N O T E P A D   C O M M A N D   H A N D L E R
...............................................................................
.
.
NP$CMD1         NORETURN
                MOVE            ZERO,CMDTRAP                                         
                TRAP            LOGON IF ESCAPE                                      
                TRAP            LOGON IF F27                                        
                DISPLAY         *HOFF,*HD,*EL,SPACE,NFUNC1,SPACE,CFUNC8:
                                SPACE,AFUNC2,SPACE,MRFUNC5,SPACE,FUNC7,SPACE,FUNC4;
.
                CLEAR           FUNCDESC           // Clear the functions.                 
                MOVE            ZERO,FLAG1         // Flag1 = 0                           
                CALL            CHKALRM            // Check for alarm,plan,message.        
                MOVE            ZERO,FLAG2
*
.Highlight the Correct Function
.
NP$CMD2         LOAD            FUNCDESC BY NFUNC FROM NFUNC1,CFUNC8:
                                AFUNC2,MRFUNC5,FUNC7,FUNC4
.
                MOVE            NFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           NFPOS,NWORK2
                MOVE            NFPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
NP$CMD3         DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              LEFT                                                             
                CMOVE           LEFT,REPLY                                              
                ENDIF           
                IF              RIGHT                                                             
                CMOVE           RIGHT,REPLY                                           
                ENDIF           
                GOTO            NP$CMD8 IF F5
                GOTO            NP$CMD8 IF F9                                            
                GOTO            NP$CMD7 IF LESS
                GOTO            NP$CMD6 IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
.
                CMATCH          CMDKEY,REPLY                                             
                GOTO            LOGON IF EQUAL                                           
                GOTO            LOGON IF F27                                            
*
.Check for a Direction Command
.
                CMATCH          RIGHT,REPLY
                GOTO            NP$CMD4 IF EQUAL
                CMATCH          LEFT,REPLY
                GOTO            NP$CMD5 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            NP$CMD4 IF EQUAL
*
.Check for a Function Letter
.
                RESET           NLETS
                SCAN            REPLY,NLETS
                IF              NOT EQUAL            // Lower Case                             
                RESET           NLETS2                                              
                SCAN            REPLY,NLETS2                                       
                GOTO            NP$CMD3 IF NOT EQUAL                                
                MOVEFPTR        NLETS2,NFUNC                                        
                GOTO            NP$CMD2                                              
                ENDIF          
                MOVEFPTR        NLETS,NFUNC
                GOTO            NP$CMD2
*
.Move Right to the Next Function
.
NP$CMD4         ADD             ONE,NFUNC
                COMPARE         SEVEN,NFUNC
                GOTO            NP$CMD2 IF NOT EQUAL
                MOVE            ONE,NFUNC
                GOTO            NP$CMD2
*
.Move Left to the Next Function
.
NP$CMD5         SUB             ONE,NFUNC
                GOTO            NP$CMD2 IF NOT ZERO
                MOVE            SIX,NFUNC
                GOTO            NP$CMD2
*
.We Have a Selected Function
.
NP$CMD6         BRANCH          NFUNC TO NPNEXT,NPADD,NPCHG,NPDEL,NPSRCH,NPPRINT
                CALL            INTERR
*
.A Timeout Occurred - Check Alarm & Messages
.
NP$CMD7         MOVE            ZERO,FLAG1
                CALL            CHKALRM
                DISPLAY         *P59:1,DATE,SPACE2,TIME;
                GOTO            NP$CMD3
*
.Help Requested
.
NP$CMD8         MOVE            EIGHT,HMENU
                MOVE            NFUNC,HFUNCNO
                CALL            HELP
                CALL            SHOWBOXN
*
.Redraw the Screen
.
                FILEPI          2;NOTEFILE
                READ            NOTEFILE,KEYA;;
                READKPTB        NOTEFILE;REPLY
                GOTO            NOTEPAD3
+..............................................................................
.
.                    N O T E P A D   P A G E   F O R W A R D
...............................................................................
.
.Did We Already Hit the End of File ?
.
NPNEXT          BRANCH          EOFSW TO NPNEXT2      // No....
*
.Yes, Erase the Screen and Display the First Page Again
.
NPNEXT1         BRANCH          PAGE TO NP$CMD3       // End of File on the First Page...
.
                MOVE            ONE,PAGE
                DISPLAY         *SETSWTB 3:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,PAGE,*HD,*EL,NOTEREW;
                GOTO            NOTEPAD2
*
.See if There are More Records for the Last Note on the Screen Now
.
NPNEXT2         LOAD            KEYWORK BY DTLCOUNT FROM KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN,KEYO:
                                KEYP,KEYQ,KEYR
.
                FILEPI          2;NOTEFILE
                READ            NOTEFILE,KEYWORK;;
                READKS          NOTEFILE;DIM20,DATE,TIME,DATA
                GOTO            NPNEXT1 IF OVER
*
.Right User ?
.
                SETLPTR         KEYWORK,7
                MATCH           KEYWORK,DIM20
                GOTO            NPNEXT1 IF NOT EQUAL     // No, End of Notes
*
. Show em the rest of this note/new note.
.
                ADD             ONE,PAGE
                DISPLAY         *SETSWTB 3:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80:
                                *P77:23,PAGE,*HD,*EL;
.
                SETLPTR         KEYWORK,20
                FILEPI          1;NOTEFILE
                READTAB         NOTEFILE,KEYWORK;REPLY
                SETLPTR         KEYWORK,7
                GOTO            NOTEPAD3
+..............................................................................
.
.                        N O T E P A D   A D D I T I O N
...............................................................................
.
.
NPADD           COMPARE         ZERO,DTLCOUNT
                GOTO            NPADD1 IF EQUAL
                ADD             ONE,PAGE
                DISPLAY         *SETSWTB 3:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80,*P77:23,PAGE;
                MOVE            ZERO,DTLCOUNT
*
.Get the Current Date and Time
.
NPADD1          MOVE            ONE,COUNTER
                MOVE            FOUR,VPOS
                MOVE            ZERO,SWITCH
*
.Time and Date Stamp the Note
.
                CALL            CLOCKDT
                DISPLAY         *HD,*EL,LITENT,DIRNT,PERIOD:
                                *P3:VPOS,DATE,*H 15,TIME;
                MOVE            THIRTY1,CMDTRAP                                        
                TRAP            NPADD4 IF ESCAPE                                       
                TRAP            NPADD4 IF F27                                          
*
.Get the Note
.
NPADD2          KEYIN           *P24:VPOS,*RPTCHAR "_":55,*H 24,*IT,DATA;
                DISPLAY         *IN,*H 24,DATA;
                GOTO            NPADD7 IF F5
.
                BUMP            DATA,0
                GOTO            NPADD4 IF EOS
*
.Write the Record to Disk
.
                PACK            KEY20 WITH RECTYPE,CURRUSER,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND,COUNTER
                CALL            AG2010
*
.Bump the Counter and the Vertical Position
.
                COMPARE         NINTY9,COUNTER
                GOTO            NPADD51 IF EQUAL
                ADD             ONE,COUNTER
                COMPARE         TWENTY1,VPOS
                GOTO            NPADD3 IF EQUAL
                ADD             ONE,VPOS
*
.Save the Note Record's Key
.
                ADD             ONE,DTLCOUNT
                STORE           KEY20 BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN:
                                KEYO,KEYP,KEYQ,KEYR
                GOTO            NPADD2
*
.If the Screen is Full, Roll the Window
.
NPADD3          DISPLAY         *SETSWTB 3:21,*SETSWLR 2:79,*R,*SETSWALL=1:24:1:80;
                MOVE            ONE,SWITCH               // Force Screen Redraw
                GOTO            NPADD2
*
.End the Addition Routine
.
NPADD4          NORETURN
                BRANCH          SWITCH TO NPADD52
                DISPLAY         *SETSWLR 2:79,*P2:VPOS,*EL,*SETSWALL=1:24:1:80;
                BRANCH          COUNTER TO NPADD6       // Changed His Mind...
                GOTO            NP$CMD1
*
.If We Rolled the Screen, It Must Be Redrawn
.
NPADD51         DISPLAY         *CLICK,*HD,*EL,MAXNOTE,*W;
NPADD52         DISPLAY         *SETSWTB 3:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80,*HD,*EL;
.
NPADD6          FILEPI          2;NOTEFILE
                READ            NOTEFILE,KEYA;;
                READKPTB        NOTEFILE;REPLY;
                SUB             ONE,PAGE
                DISPLAY         *P77:23,PAGE;
                GOTO            NOTEPAD3
*
.Start another New Note
.
NPADD7          BRANCH          COUNTER TO NPADD2       // First Record....
                GOTO            NPADD
+..............................................................................
.
.                 N O T E P A D   L O C A T I O N   R O U T I N E
...............................................................................
.
.
NPLOC
.
                MOVE            FOUR,VPOS
                MOVE            ONE,KEYPTR
                MOVE            TWO,REPLY           // Indicate Move Down
.
                MOVE            KEYA,KEY20
                COMPARE         ONE,DTLCOUNT
                GOTO            NPLOC6 IF EQUAL   // Only One Record
                GOTO            NP$CMD1 IF LESS   // No Records...
.
                DISPLAY         *HD,*EL,UPDWNCMD;
*
.Get the Selected Key
.
NPLOC1          LOAD            KEY20 BY KEYPTR FROM KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN:
                                KEYO,KEYP,KEYQ,KEYR
*
.Is This a Blank Line ?
.
                BUMP            KEY20,0
                GOTO            NPLOC2 IF EOS     Yes, Skip It...
*
.Are We Locating for the Change Function ?
.
                COMPARE         THREE,NFUNC
                GOTO            NPLOC3 IF EQUAL    Yes...
*
.If Deleting or Printing, We'll Only Position to the First Record of Each Note
. (Delete gets Rid of Entire Notes, Not Single Lines; Print prints
.  Entire Notes)
.
                RESET           KEY20,19
                MATCH           " 1",KEY20
                RESET           KEY20
                GOTO            NPLOC3 IF EQUAL    1st Record
*
.Go Up or Down Another Position
.
NPLOC2          CMATCH          DOWN,REPLY
                GOTO            NPLOC5 IF EQUAL    Going Down
                GOTO            NPLOC4             Going Up
*
.See What They Want to Do
.
NPLOC3          MOVE            KEYPTR,VPOS
                ADD             THREE,VPOS
. RBM: Moved the following two statements from the beginning of the routine.
                MOVE            THIRTY2,CMDTRAP                                          
                TRAP            NPLOC8 IF ESCAPE                                        
                TRAP            NPLOC8 IF F27                                            
                KEYIN           *P2:VPOS,RA,*H 2,*+,*RV,REPLY;
                IF              UP                                                             
                CMOVE           UP,REPLY                                               
                ENDIF           032
                IF              DOWN                                                             
                CMOVE           DOWN,REPLY                                             
                ENDIF           032
                DISPLAY         *H 2,SPACE;
                GOTO            NPLOC6 IF EOS
.
                CMATCH          DOWN,REPLY
                GOTO            NPLOC5 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            NPLOC5 IF EQUAL
                CMATCH          UP,REPLY
                GOTO            NPLOC1 IF NOT EQUAL
*
.Position to the Next Higher Record
.
NPLOC4          SUB             ONE,KEYPTR
                GOTO            NPLOC1 IF NOT EQUAL
                MOVE            DTLCOUNT,KEYPTR
                GOTO            NPLOC1
*
.Position to the Next Lower Record
.
NPLOC5          ADD             ONE,KEYPTR
                COMPARE         KEYPTR,DTLCOUNT
                GOTO            NPLOC1 IF NOT LESS
                MOVE            ONE,KEYPTR
                GOTO            NPLOC1
*
.Read the Selected Record
.
NPLOC6          FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEY20;REPLY,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND,COUNTER,DATE,TIME,DATA
                GOTO            NPLOC7 IF OVER
*
.Branch to the Correct Function
.
                BRANCH          NFUNC TO NPLOC7,NPLOC7,NPCHG1,NPDEL1,NPLOC7
.
                SETLPTR         KEY20,18
                GOTO            NPPRINT5
.
NPLOC7          CALL            INTERR
*
.Exit the Location Routine
.
NPLOC8          NORETURN
                DISPLAY         *H 2,SPACE;
                COMPARE         SIX,NFUNC
                GOTO            NPPRINT8 IF EQUAL     Printing
                GOTO            NP$CMD1
+..............................................................................
.
.                         N O T E P A D   C H A N G E
...............................................................................
.
.
NPCHG           COMPARE         ZERO,DTLCOUNT
                GOTO            NP$CMD2 IF EQUAL
                GOTO            NPLOC
*
.We are Positioned to the Correct Record; Get the New Information
.
NPCHG1          MOVE            THIRTY3,CMDTRAP                                         
                TRAP            NPCHG2 IF ESCAPE                                       
                TRAP            NPCHG2 IF F27                                           
                KEYIN           *HD,*EL,*DV,LITENT,*DV,DIRNT,*DV,PERIOD,*P24:VPOS,*IT:
                                *RV,DATA;
                DISPLAY         *IN,*H 24,DATA;
                IF              EOS                                                            
                DISPLAY         *HD,*EL,UPDWNCMD;                                      
                GOTO            NPLOC3                                                 
                ENDIF           064
*
.Correct the Record on Disk
.
                TRAPCLR         ESCAPE                                                  
                TRAPCLR         F27                                                     
.
                CALL            AG2090
                CALL            AG2010
.
                DISPLAY         *HD,*EL,UPDWNCMD;                                  
                GOTO            NPLOC3
*
.Abort Changing the Note
.
NPCHG2          NORETURN
                CLEAR           KEY20
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEY20;KEY20,DATE,TIME,DATA
.
                DISPLAY         *HOFF,*H 2,SPACE,*H 24,DATA;
                GOTO            NP$CMD1
+..............................................................................
.
.                       N O T E P A D   D E L E T I O N
...............................................................................
.
.
.Position to the Correct Note
.
.        COMPARE   ZERO,COUNT
NPDEL           COMPARE         ZERO,DTLCOUNT       // Changed to DTLCOUNT from COUNT    
                GOTO            NP$CMD3 IF EQUAL
                GOTO            NPLOC
*
.Highlight the Date & Time; Verify the Deletion
.
NPDEL1          MOVE            THIRTY4,CMDTRAP                                      
                TRAP            NPDEL4 IF ESCAPE                                      
                TRAP            NPDEL4 IF F27                                           

                DISPLAY         *HON,*P3:VPOS,DATE,*H 15,TIME,*HOFF:              
                                *HD,*EL,NOTEDEL;                                  
                CALL            KREPLYN
.
                CMATCH          YES,REPLY                                           
                GOTO            NPDEL4 IF NOT EQUAL
*
.Delete All the Lines of This Note
.
                MOVE            KEY20,KEYWORK
                SETLPTR         KEYWORK,18
                TRAPCLR         ESCAPE                                           
                TRAPCLR         F27                                             
*
.Delete the Record from Disk
.
NPDEL2
                CALL            AG2090
*
.Is There Another Line ?
.
                FILEPI          1;NOTEFILE
                READKSTB        NOTEFILE;KEY20
                GOTO            NPDEL3 IF OVER
*
.Right Note ?
.
                MATCH           KEYWORK,KEY20
                GOTO            NPDEL2 IF EQUAL
*
.The Note is Gone; Erase the Screen
.
NPDEL3          DISPLAY         *HD,*EL,NTDELTD:
                                *SETSWTB VPOS:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80;
*
.Redraw the Screen
.
                MOVE            ONE,EOFSW
                MOVE            ZERO,DTLCOUNT
                MOVE            ZERO,COUNT
                MOVE            ZERO,SWITCH
                MOVE            FOUR,VPOS
                SETLPTR         KEYWORK,7
.
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEYA;REPLY,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND,COUNTER,DATE,TIME,DATA
                GOTO            NOTEPAD4 IF OVER
                MOVE            KEYA,KEY20
                GOTO            NOTEPAD5
*
.Abort Deleting the Note
.
NPDEL4          NORETURN
                DISPLAY         *HOFF,*P2:VPOS,SPACE,DATE,*H 15,TIME;
                GOTO            NP$CMD1
+.............................................................................
.
.                      N O T E P A D   S E A R C H I N G
..............................................................................
.
.
NPSRCH          COMPARE         ZERO,DTLCOUNT
                GOTO            NP$CMD3 IF EQUAL       // Nothing to Search...
                MOVE            THIRTY5,CMDTRAP                                        
                TRAP            NOTEPAD1 IF ESCAPE                                     
                TRAP            NOTEPAD1 IF F27                                       
*
.Get the Search Value
.
NPSRCH1         KEYIN           *SETSWTB 3:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80:
                                *HD,*EL,*DV,LITENT,*DV,SRCHKEY:
                                *RPTCHAR "_":20,*HA -20,*IT,DIM20;
                DISPLAY         *IN,*H 23,DIM20;
.
                CMATCH          " ",DIM20
                GOTO            NOTEPAD2 IF EOS
                GOTO            NPSRCH1 IF EQUAL
*
.Build the Keys
.
                RESET           DIM20,3
                GOTO            NPSRCH3 IF NOT EOS
.
NPSRCH2         NORETURN
                KEYIN           *CLICK,*HD,*EL,*DV,IKSPEC,REPLY;
                GOTO            NPSRCH1
.
NPSRCH3         RESET           DIM20
                MOVELPTR        DIM20,INDEX            // Save the Length Entered
                DISPLAY         *HD,*EL,SRCHFOR,*+,DIM20;
.
                PACK            KEY9 WITH X01,CURRUSER
.
                PACK            DIM40 USING ZERO,CTWO,F,DIM20
*
.Do the Initial Read
.
                TRAP            NPSRCH2 IF IO
                FILEPI          1;NOTEFILA
                READ            NOTEFILA,KEY9,DIM40;KEY20,DATE,TIME,DATA
                TRAPCLR         IO
                GOTO            NPSRCH12 IF OVER
.
                MOVE            ZERO,COUNT
                MOVE            FOUR,VPOS
                MOVE            ONE,EOFSW
                MOVE            ZERO,DTLCOUNT
                SETLPTR         KEY20,18
                GOTO            NPSRCH5
*
.Read Generically Through the File
.
NPSRCH4         FILEPI          1;NOTEFILA
                READKG          NOTEFILA;KEY20,DATE,TIME,DATA
                GOTO            NPSRCH12 IF OVER
*
.Same as the Previous Note ?
.
                SETLPTR         KEY20,18
                MATCH           KEY20,DIM30
                GOTO            NPSRCH4 IF EQUAL
*
.Position to the First Line of the Note Containing the Key
.
NPSRCH5         MOVE            KEY20,DIM30
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEY20;;
*
.Read Through the Note File
.
NPSRCH6         FILEPI          1;NOTEFILE
                READKS          NOTEFILE;KEYWORK,DATE,TIME,DATA
                GOTO            NPSRCH4 IF OVER
*
.Same Note ?
.
                MATCH           KEY20,KEYWORK
                GOTO            NPSRCH4 IF NOT EQUAL
*
.Is This the 1st Line of a Note ?
.
                RESET           KEYWORK,19
                MATCH           " 1",KEYWORK
                RESET           KEYWORK
                GOTO            NPSRCH8 IF NOT EQUAL
*
.Is This the 1st Line on the Screen ?
.
                COMPARE         FOUR,VPOS
                GOTO            NPSRCH7 IF EQUAL
*
.Double Space Between Notes
.
                COMPARE         TWENTY,VPOS
                GOTO            NPSRCH11 IF EQUAL           // Screen is Full
                ADD             ONE,VPOS
*
.Display the Time & Date with the 1st Line
.
NPSRCH7         DISPLAY         *P3:VPOS,DATE,*H 15,TIME;
                ADD             ONE,COUNT
*
.Locate the Key in the Info
.
NPSRCH8         MOVE            DATA,KEYA
                REP             CAPREP,KEYA
                REP             CAPREP,DIM20
.
                SCAN            DIM20,KEYA
                GOTO            NPSRCH9 IF EQUAL
                CLEAR           DIM40
                GOTO            NPSRCH10
.
NPSRCH9         MOVEFPTR        KEYA,HPOS
                RESET           DATA,HPOS
                MOVE            DATA,DIM40
                RESET           DATA
                SETLPTR         DIM40,INDEX
                ADD             TWENTY3,HPOS
*
.Display the Information, Highlight the Key
.
NPSRCH10        DISPLAY         *P24:VPOS,DATA,*H HPOS,*HON,*+,DIM40,*HOFF;
*
.Is the Screen Full ?
.
                ADD             ONE,VPOS
                COMPARE         TWENTY1,VPOS
                GOTO            NPSRCH6 IF NOT EQUAL
*
.The Screen is Full
.
NPSRCH11        KEYIN           *HD,*EL,*H 2,*HON,*DV,CONTPR2,*HOFF,*HD,REPLY:
                                *SETSWTB 3:21,*SETSWLR 2:79,*ES,*SETSWALL=1:24:1:80;
.
                MOVE            FOUR,VPOS
                BRANCH          COUNT TO NPSRCH6
                MOVE            ZERO,COUNT
*
                GOTO            NPSRCH6
*
.End of File Encountered
.
NPSRCH12        KEYIN           *HD,*EL,*HON,*H 2,*DV,RETPR,*HOFF,*HD,REPLY;
                GOTO            NPSRCH1
+.............................................................................
.
.                       N O T E P A D   P R I N T I N G
..............................................................................
.
.
NPPRINT         COMPARE         ZERO,DTLCOUNT
                GOTO            NP$CMD3 IF EQUAL         // Nothing to Print...
                MOVE            THIRTY6,CMDTRAP                                         
                TRAP            NP$CMD1 IF ESCAPE                                      
                TRAP            NP$CMD1 IF F27                                         
*
.Ready the Print File or Printer
.
                MOVE            ZERO,LINE
                CALL            SPOOL
                BRANCH          FLAG1 TO NP$CMD1
                MOVE            THIRTY7,CMDTRAP                                        
                TRAP            NPPRINT8 IF ESCAPE                                     
                TRAP            NPPRINT8 IF F27                                       
*
.Selected Notes or All of 'Em ?
.
NPPRINT1        MOVE            CA,REPLY
                KEYIN           *HD,*EL,*DV,PRTSPA,*HA -1,*RV,REPLY;
.
                REP             NTREP,REPLY
                MOVE            REPLY,INDEX
                BRANCH          INDEX TO NPPRINT2,NPPRINT2
                GOTO            NPPRINT1
*
.Center the User's Name
.
NPPRINT2        COUNT           NWORK1,USRNAME
                MOVE            TWENTY,NWORK2
                SUB             NWORK1,NWORK2
                DIV             TWO,NWORK2
.
                MOVE            BLANKS,USRNAME1
                RESET           USRNAME1,NWORK2
                APPEND          USRNAME,USRNAME1
                RESET           USRNAME1
*
.Print a Heading if Needed
.
                COMPARE         ZERO,LINE
                CALL            NPPRINT9 IF EQUAL
*
.If Printing Specific Notes, Go Locate 'Em
.
                COMPARE         ONE,INDEX
                GOTO            NPPRINT3 IF NOT EQUAL
*
.Make Sure There is at Least One Note on This Screen
.
                COMPARE         ZERO,COUNT
                GOTO            NPLOC IF NOT EQUAL
.
                KEYIN           *CLICK,*HD,*EL,*DV,NONTS,REPLY;
                GOTO            NP$CMD1
*
.If Printing All the Notes, Position to the First of the User's Notes
.
NPPRINT3        PACK            KEY20 WITH RECTYPE,CURRUSER
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEY20;;
*
.Read Through the Notepad File
.
NPPRINT4        FILEPI          1;NOTEFILE
                READKS          NOTEFILE;KEYWORK,DATE,TIME,DATA
                GOTO            NPPRINT7 IF OVER
*
.Same User ?
.
                MATCH           KEY20,KEYWORK
                GOTO            NPPRINT7 IF NOT EQUAL
*
.First Line of the Note ?
.
                RESET           KEYWORK,19
                MATCH           " 1",KEYWORK
                RESET           KEYWORK
                GOTO            NPPRINT6 IF NOT EQUAL    // No...
*
.If Printing Only Selected Notes, Return to Selecting
.
                COMPARE         ONE,INDEX
                GOTO            NPPRINT5 IF NOT EQUAL
                GOTO            NPLOC3
*
.Print the Date & Time of the Note
.
NPPRINT5        COMPARE         EIGHT,LINE
                CALL            NPPRINT9 IF LESS
.
                DISPLAY         *HD,*EL,PRTNTS;
                PRINT           *N,*2,DATE,*15,TIME;
                SUB             ONE,LINE
*
.Print the Note Information
.
NPPRINT6        PRINT           *25,DATA
*
.Check for Page Overflow
.
                SUB             ONE,LINE
                CALL            NPPRINT9 IF LESS
                GOTO            NPPRINT4
*
.End of Note or Notes
.
NPPRINT7        BRANCH          INDEX TO NPLOC           // Go Select Another Note
*
.Close the Spool File/Release the Printer
.
NPPRINT8        NORETURN
                RELEASE
                SPLCLOSE
                GOTO            NOTEPAD1
*
.Print a Top of Form
.
NPPRINT9        PRINT           *F,*N,*N,*37,PRTNTS:
                                *N,*40,FORMSG,*N,*36,CURRNAME,*N,*N
                MOVE            FIFTY5,LINE
                RETURN
.
. *** End ***
.
