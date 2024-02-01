*---------------------------------------------------------------
.
. Module Name: agenda_alr.inc
. Description:  Desk Alarm Module
.
. Revision History:
.
.
.
ALARM
                CALL            SHOWBOX1                                                
                DISPLAY         *P34:1,DSKALRM;                                   
                MOVE            ONE,RECTYPE
                CALL            CLOCKDT              // Format Current DATE/TIME
                DISPLAY         *P7:3,DTSTAT,*H 18,TMSTAT,*H 34,ALRMMSG:
                                *P4:4,*RPTCHAR HB:11,*H 16,*RPTCHAR HB:8:
                                *H 26,*RPTCHAR HB:40;                                   
*
.Position to the User's Alarms
.
ALARM1
                PACK            KEYWORK WITH RECTYPE,CURRUSER
                MOVE            ZERO,NWORK2A                 // Reset Next Page Flag
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEYWORK;;
.
+..............................................................................
.
.                              N E X T   P A G E
...............................................................................
.
ALARM7
                MOVE            ONE,KEYPTR
                DISPLAY         *SETSWTB 5:21,*SETSWLR 3:78,*ES,*SETSWALL=1:24:1:80:
                                *P78:5;                                                
*
.Display the First Screen of Alarms
.
                MOVE            ONE,EOFSW
                MOVE            ZERO,DTLCOUNT
*
.Read Through the Alarm File
.
ALARM3
                FILEPI          1;NOTEFILE
                READKS          NOTEFILE;KEY20,DATE,TIME,DIM40
                GOTO            ALARM4 IF OVER
*
.Right User ?
.
                MATCH           KEYWORK,KEY20
                GOTO            ALARM4 IF NOT EQUAL
*
.Display the Alarm Information
.
                DISPLAY         *H 4,DATE,*H 16,TIME,*H 26,DIM40,*N                  
*
.Save the Record's Key
.
                ADD             ONE,DTLCOUNT
                STORE           KEY20 BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI
*
.Is the Screen Full ?
.
                COMPARE         NINE,DTLCOUNT
                GOTO            ALARM5 IF EQUAL      // Yes...
                GOTO            ALARM3
*
.Indicate We Encountered the End of File
.
ALARM4
                MOVE            ZERO,EOFSW
                COMPARE         ZERO,DTLCOUNT
                GOTO            ALARM5 IF NOT EQUAL
                COMPARE         ZERO,NWORK2A
                GOTO            AC$CMD1 IF EQUAL
                GOTO            ALARM1
*
.Turn On the Pointer
.
ALARM5
                MOVE            ONE,NWORK2A
                COMPARE         KEYPTR,DTLCOUNT
                GOTO            ALARM6 IF NOT LESS
                SUB             ONE,KEYPTR
.
ALARM6
                MOVE            KEYPTR,VPOS
                SUB             ONE,VPOS
                MULT            TWO,VPOS
                ADD             FIVE,VPOS                                             
                DISPLAY         *P3:VPOS,RA;                                         
+..............................................................................
.
.                   A L A R M S   C O M M A N D   H A N D L E R
...............................................................................
.
.
AC$CMD1         NORETURN
                MOVE            ZERO,CMDTRAP                                           
                TRAP            LOGON IF ESCAPE                                         
                TRAP            LOGON IF F27                                            
                DISPLAY         *P1:24,*EF,SPACE,CFUNC8,SPACE,AFUNC2,SPACE,MRFUNC5:      
                                SPACE,NFUNC1;                                            
                CLEAR           FUNCDESC           // Clear the functions.                 
                MOVE            ZERO,FLAG1         // Flag1 = 0                            
                DISPLAY         *P1:23,*EL;                                             
                CALL            CHKALRM            // Check for alarm,plan,message.       
                MOVE            ZERO,FLAG2
*
.Highlight the Correct Function
.
AC$CMD2         LOAD            FUNCDESC BY AFUNC FROM CFUNC8,AFUNC2,MRFUNC5,NFUNC1
.
                MOVE            AFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           AFPOS,NWORK2
                MOVE            AFPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
AC$CMD3         DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;                       
                KEYIN           *H HPOS,*HA -1,*T60,*+,*EOFF,*CURSON,*RV,REPLY;
                DISPLAY         *CURSOFF;
                IF              LEFT                                                             
                CMOVE           LEFT,REPLY                                              
                ENDIF           032
                IF              RIGHT                                                             
                CMOVE           RIGHT,REPLY                                             
                ENDIF           032
                IF              UP                                                             
                CMOVE           UP,REPLY                                                
                ENDIF           032
                IF              DOWN                                                             
                CMOVE           DOWN,REPLY                                              
                ENDIF           032
                GOTO            AC$CMD8 IF F5
                GOTO            AC$CMD8 IF F9                                           
                GOTO            AC$CMD7 IF LESS
                GOTO            AC$CMD6 IF EOS
*
.Check for a Direction Command
.
                CMATCH          UP,REPLY
                GOTO            AC$CMD9 IF EQUAL
                CMATCH          DOWN,REPLY
                GOTO            AC$CMD10 IF EQUAL
.
                DISPLAY         *H HPOS,*+,FUNCDESC;
.
                CMATCH          RIGHT,REPLY
                GOTO            AC$CMD4 IF EQUAL
                CMATCH          LEFT,REPLY
                GOTO            AC$CMD5 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            AC$CMD4 IF EQUAL
*
.Check for a Function Letter
.
                RESET           ALETS
                SCAN            REPLY,ALETS
                IF              NOT EQUAL             // Lower Case                            
                RESET           ALETS2                                                
                SCAN            REPLY,ALETS2                                        
                GOTO            AC$CMD3 IF NOT EQUAL                                  
                MOVEFPTR        ALETS2,AFUNC                                          
                GOTO            AC$CMD2                                               
                ENDIF           026
.         GOTO      AC$CMD3 IF NOT EQUAL                                    
                MOVEFPTR        ALETS,AFUNC
                GOTO            AC$CMD2
*
.Move Right to the Next Function
.
AC$CMD4         ADD             ONE,AFUNC
                COMPARE         FIVE,AFUNC
                GOTO            AC$CMD2 IF NOT EQUAL
                MOVE            ONE,AFUNC
                GOTO            AC$CMD2
*
.Move Left to the Next Function
.
AC$CMD5         SUB             ONE,AFUNC
                GOTO            AC$CMD2 IF NOT ZERO
                MOVE            FOUR,AFUNC
                GOTO            AC$CMD2
*
.We Have a Selected Function
.
AC$CMD6         BRANCH          AFUNC TO ACADD,ACCHG,ACDEL,ALARM7
                CALL            INTERR
*
.A Timeout Occurred - Check Alarm & Messages
.
AC$CMD7         MOVE            ZERO,FLAG1
                CALL            CHKALRM
                DISPLAY         *P59:1,DATE,SPACE2,TIME;                               
                GOTO            AC$CMD3
*
.Help Requested
.
AC$CMD8         MOVE            NINE,HMENU
                MOVE            AFUNC,HFUNCNO
                CALL            HELP
                GOTO            ALARM
*
.Position to the Next Higher Record
.
AC$CMD9         COMPARE         ZERO,DTLCOUNT
                GOTO            AC$CMD3 IF EQUAL
                BRANCH          KEYPTR TO AC$CMD3
                SUB             ONE,KEYPTR
                GOTO            AC$CMD11
*
.Position to the Next Lower Record
.
AC$CMD10        COMPARE         ZERO,DTLCOUNT
                GOTO            AC$CMD3 IF EQUAL
                COMPARE         KEYPTR,DTLCOUNT
                GOTO            AC$CMD3 IF EQUAL
                ADD             ONE,KEYPTR
.
.AC$CMD11 DISPLAY   *P1:VPOS,SPACE;                                     
AC$CMD11        DISPLAY         *P3:VPOS,SPACE;                                      
                MOVE            KEYPTR,VPOS
                SUB             ONE,VPOS
                MULT            TWO,VPOS
                ADD             FIVE,VPOS                                            
                DISPLAY         *P3:VPOS,RA;                                         
                GOTO            AC$CMD3
+..............................................................................
.
.                            A L A R M   A D D I T I O N
...............................................................................
.
.
ACADD           MOVE            FORTY4,CMDTRAP                                          
                TRAP            ACADD4 IF ESCAPE                                         
                TRAP            ACADD4 IF F27                                            
*
.Compute the Screen Position
.
                MOVE            DTLCOUNT,VPOS
                MULT            TWO,VPOS
                ADD             FIVE,VPOS                                               
*
.Is the Screen Full ?
.
                COMPARE         NINE,DTLCOUNT
                GOTO            ACADD1 IF NOT EQUAL
*
.Move the Records on the Screen Up One
.
                BRANCH          KEYPTR TO ACADDP
                SUB             ONE,KEYPTR
.
ACADDP          DISPLAY         *SETSWTB 5:21,*SETSWLR 3:78,*HD,*R,*R,*SETSWALL=1:24:1:80;          
.
                MOVE            KEYPTR,VPOS
                SUB             ONE,VPOS
                MULT            TWO,VPOS
                ADD             FIVE,VPOS                                                
                DISPLAY         *P3:VPOS,RA;                                            
*
.Move the Keys Up One
.
                MOVE            ONE,NWORK1
                MOVE            TWO,NWORK2
.
ACADDX          LOAD            KEY BY NWORK2 FROM KEYA,KEYB,KEYC:
                                KEYD,KEYE,KEYF,KEYG,KEYH,KEYI
                STORE           KEY BY NWORK1 INTO KEYA,KEYB,KEYC:
                                KEYD,KEYE,KEYF,KEYG,KEYH,KEYI
.
                ADD             ONE,NWORK1
                ADD             ONE,NWORK2
                COMPARE         NINE,NWORK1
                GOTO            ACADDX IF NOT EQUAL
                MOVE            EIGHT,DTLCOUNT
                MOVE            TWENTY1,VPOS                                              
*
.Get the Alarm Date
.
ACADD1          CALL            CLOCKDT
                DISPLAY         *HD,*EL,ALMSG0,ALMSG1,PERIOD,*P4:VPOS,DATE;              
                MOVE            FOUR,HPOS                                               
                MOVE            ZERO,REQFLAG
                MOVE            ONE,MASKSW
                CALL            GETDATE
                BRANCH          FLAG1 TO ACADD4
                CALL            CHECKDT
                GOTO            ACADD1 IF NOT EQUAL
*
.Get the Alarm Time
.
ACADD2          DISPLAY         *HD,*EL,ALMSG0,ALMSG2,PERIOD,*P16:VPOS,TIME;
                MOVE            SIXTEEN,HPOS
                CALL            GETIME
                BRANCH          FLAG1 TO ACADD1
                BRANCH          SAMEDAY TO ACADD3
                MOVE            TIME,DIM9
                CALL            CHECKTM
                GOTO            ACADD2 IF NOT EQUAL
                MOVE            DIM9,TIME
*
.Get the Alarm Information
.
ACADD3          KEYIN           *HD,*EL,*DV,ALMSG0,*DV,ALMSG3:
                                *P26:VPOS,*RPTCHAR "_":40,*H 26,*IT,*+,DIM40;
                DISPLAY         *IN,*H 26,DIM40;
                GOTO            ACADD2 IF F5
.
                BUMP            DIM40,0
                GOTO            ACADD3 IF EOS
*
.Write the Record to Disk
.
                MOVE            ZERO,COUNTER
                PACK            KEY20 WITH RECTYPE,CURRUSER,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND,COUNTER
.
                FILEPI          1;NOTEFILE
                WRITE           NOTEFILE,KEY20;KEY20,DATE,TIME,DIM40
.
                PAUSE           ONE                 // Put here to prevent duplicate keys.
*
.Save the Key
.
                ADD             ONE,DTLCOUNT
                STORE           KEY20 BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI
*
.Set Up the Alarm Time
.
                CALL            FATIME
                GOTO            ACADD
*
.End the Addition Routine
.
ACADD4          NORETURN
*
.Fix Up the Screen
.
ACADDZ          MOVE            ONE,EOFSW
                PACK            KEYWORK WITH RECTYPE,CURRUSER
                DISPLAY         *V VPOS;
                GOTO            ALARM1
+..............................................................................
.
.                             A L A R M   C H A N G E
...............................................................................
.
.
ACCHG           COMPARE         ZERO,DTLCOUNT
                GOTO            AC$CMD2 IF EQUAL
*
.Read the Selected Record
.
                LOAD            KEY20 BY KEYPTR FROM KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI
.
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEY20;REPLY,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND,COUNTER,DATE,TIME,DIM40
                CALL            INTERR IF OVER
*
.Compute the Vertical Position
.
                MOVE            KEYPTR,VPOS
                SUB             ONE,VPOS
                MULT            TWO,VPOS
                ADD             FIVE,VPOS                                              
.
                MOVE            FORTY5,CMDTRAP                                          
                TRAP            ACCHG5 IF ESCAPE                                       
                TRAP            ACCHG5 IF F27                                          
*
.Allow Changing the Date
.
ACCHG1          MOVE            ONE,FLAG2
                DISPLAY         *HD,*EL,ALMSG0,ALMSG1,PERIOD;
.
                MOVE            FOUR,HPOS                                               
                MOVE            ONE,MASKSW
                MOVE            ZERO,REQFLAG
                MOVE            ONE,TDDATE                                              
                CALL            GETDATE
                MOVE            ZERO,TDDATE                                            
.
                BRANCH          FLAG1 TO ACCHG5
                BRANCH          EOSFLAG TO ACCHG2
                MOVE            ZERO,FLAG2
*
.Allow Changing the Time
.
ACCHG2          DISPLAY         *HD,*EL,ALMSG0,ALMSG2,PERIOD;
.
                MOVE            SIXTEEN,HPOS
                CALL            GETIME
.
                BRANCH          FLAG1 TO ACCHG1
                BRANCH          EOSFLAG TO ACCHG3
                MOVE            ZERO,FLAG2
*
.Allow Changing the Information
.
ACCHG3          KEYIN           *HD,*EL,*DV,ALMSG0,*DV,ALMSG3:
                                *P26:VPOS,*IT,*RV,DIM40;
                DISPLAY         *IN,*H 26,DIM40;
                GOTO            ACCHG2 IF F5
.
                GOTO            ACCHG4 IF EOS
                MOVE            ZERO,FLAG2
*
.Correct the Record on Disk
.
ACCHG4          BRANCH          FLAG2 TO AC$CMD1         // No Changes.....
                TRAPCLR         ESCAPE                                              
                TRAPCLR         F27                                                
.
                CALL            AG2090
*
.Make the Key Unique
.
ACCHGA          PACK            KEY20 WITH RECTYPE,CURRUSER,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND,COUNTER
.
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEY20;REPLY
                GOTO            ACCHGB IF OVER
.
                ADD             ONE,COUNTER
                GOTO            ACCHGA
*
.Rewrite the Record
.
ACCHGB          FILEPI          1;NOTEFILE
                WRITE           NOTEFILE,KEY20;KEY20,DATE,TIME,DIM40
.
                STORE           KEY20 BY KEYPTR INTO KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI
                GOTO            AC$CMD1
*
.Abort Changing the Alarm
.
ACCHG5          CLEAR           KEY20
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEY20;KEY20,DATE,TIME,DIM40
*
.Redisplay the Information
.
                NORETURN
                DISPLAY         *CURSOFF,*HOFF,*H 4,DATE,*H 16,TIME,*H 26,DIM40;        
                GOTO            AC$CMD1
+..............................................................................
.
.                           A L A R M   D E L E T I O N
...............................................................................
.
.
.Position to the Correct Alarm
.
ACDEL           COMPARE         ZERO,DTLCOUNT
                TRAP            ACADD4 IF ESCAPE                                       
                TRAP            ACADD4 IF F27                                         
                GOTO            AC$CMD3 IF EQUAL
.
ACDEL0          KEYIN           *P1:24,*EF,*HD,*DV,DELALRM:
                                *EOFF,*CURSON,*T60,*RV,*+,REPLY;                        
                GOTO            ACDELR IF F5
                GOTO            ACDEL0 IF NOT EOS
*
.Read the Selected Record
.
                LOAD            KEY20 BY KEYPTR FROM KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI
.
                FILEPI          1;NOTEFILE
                READ            NOTEFILE,KEY20;REPLY,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND,COUNTER,DATE,TIME,DIM40
                CALL            INTERR IF OVER
*
.Compute the Vertical Position
.
                MOVE            KEYPTR,VPOS
                SUB             ONE,VPOS
                MULT            TWO,VPOS
                ADD             FOUR,VPOS                                               
*
.Delete the Record from Disk
.
                TRAPCLR         ESCAPE                                                 
                TRAPCLR         F27                                                    
                CALL            AG2090
*
.The Alarm is Gone; Fix Up the Screen
.
                DISPLAY         *SETSWTB 5:21,*SETSWLR 3:78,*V VPOS,*DELLIN,*DELLIN:
                                *SETSWALL=1:24:1:80;                                                
                MOVE            KEYPTR,DTLCOUNT
                SUB             ONE,DTLCOUNT
                CLEAR           FUNCDESC           // Clear the functions.                 
                MOVE            ZERO,FLAG1         // Flag1 = 0                           
                MOVE            ONE,ALRMFLG        // Do not display messages.             
                CALL            CHKALRM            // Check for alarm,plan,message.       
                MOVE            ZERO,ALRMFLG       // Display messages.                    
                GOTO            ACADDZ
*
.Help Requested
.
ACDELR          MOVE            NINE,HMENU
                MOVE            THREE,HFUNCNO
                CALL            HELP
                GOTO            ALARM
.
. *** End ***
.
