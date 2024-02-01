*---------------------------------------------------------------
.
. Module Name: agenda_cal.inc
. Description: Desk Calendar Module
.
. Revision History:
.
.
.Open the Files As Needed
.
CALENDAR
                MOVE            OPENFLAG,REPLY
                AND             0100,REPLY
                GOTO            CALENDR1 IF NOT ZERO
                TRAP            TRAPIO IF IO         // Can't open a file                
                OPEN            GRAPH,FSG,SHARE
                OPEN            AGENDA,FSA,SHARE
                OPEN            AGENDAIM,FSA,SHARE
                OR              0100,OPENFLAG
                TRAPCLR         IO
*
.Draw the Calendar
.
CALENDR1        NORETURN
                CALL            SHOWBOX1
                DISPLAY         *P30:1,DESKCAL;
.
                BRANCH          DATESWCH OF CAL2B                                      
CALENDR2        DISPLAY         *HOFF,*P2:3,YEARPR,*HON,"20",YEAR,*HOFF:
                                *P5:5,"S  M  T  W  T  F  S":
                                *P4:14,BEGINPR,*H 15,ENDPR:
                                *P3:15,*RPTCHAR HB:8,*H 13,*RPTCHAR HB:8:
                                *H 23,*RPTCHAR HB:56;
                GOTO            CAL2A                                                   
CAL2B           DISPLAY         *HOFF,*P2:3,YEARPR,*HON,"20",YEAR,*HOFF:
                                *P5:5,"M  T  W  T  F  S  S":
                                *P4:14,BEGINPR,*H 15,ENDPR:
                                *P3:15,*RPTCHAR HB:8,*H 13,*RPTCHAR HB:8:
                                *H 23,*RPTCHAR HB:56;                                  
CAL2A
*
.Do the Year Computations
.
                MOVE            YEAR,YEARWORK
                CALL            YEARCOMP
*
.Display the Months; Highlight the Selected Month
.
                MOVE            ONE,INDEX
                DISPLAY         *V 3;
.
CALENDR3        MOVE            INDEX,HPOS
                SUB             ONE,HPOS
                MULT            FIVE,HPOS
                ADD             SEVNTEEN,HPOS
.
                LOAD            MONTH BY INDEX FROM JAN,FEB,MAR,APR,MAY:
                                JUN,JUL,AUG,SEP,OCT,NOV,DEC
.
                COMPARE         INDEX,MON
                GOTO            CALENDR4 IF NOT EQUAL
                DISPLAY         *HON;
.
CALENDR4        DISPLAY         *H HPOS,MONTH,*HOFF;
                ADD             ONE,INDEX
                COMPARE         THIRTEEN,INDEX
                GOTO            CALENDR3 IF NOT EQUAL
*
.Draw the Calendar; Highlight the Selected Day
.
CALENDR5        CALL            DRAWCAL
*
.Graph the Week's Events & Display the Day's Appointments
.
                MOVE            ONE,GRAPHSW
                CALL            GRAPH
                CALL            SHOWDTL1
                BRANCH          INQSW OF ECINQ6                                       
+............................................................................
.
.    E X E C U T I V E   C A L E N D A R   C O M M A N D   H A N D L E R
.............................................................................
.
.
EC$CMD          NORETURN
                MOVE            ZERO,CMDTRAP                                         
                TRAP            LOGON IF ESCAPE                                       
                TRAP            LOGON IF F27                                          
                DISPLAY         *HD,*EL,SPACE,FUNC2,SPACE,CFUNC8,SPACE,AFUNC2:
                                SPACE,FUNC9,SPACE,FUNC1,SPACE,FUNC4,SPACE,FUNC5:
                                SPACE,FUNC6,SPACE,FUNC7;
                CLEAR           FUNCDESC           // Clear the functions.                
                MOVE            ZERO,FLAG1         // Flag1 = 0                            
                CALL            CHKALRM            // Check for alarm,plan,message.        
                MOVE            ZERO,FLAG2
*
.Position to the Correct Function
.
EC$CMD1         LOAD            FUNCDESC BY FUNC FROM FUNC2,CFUNC8,AFUNC2:
                                FUNC9,FUNC1,FUNC4,FUNC5,FUNC6,FUNC7
.
                MOVE            FUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           ECPOS,NWORK2
                MOVE            ECPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
                MOVE            SPACE,REPLY                                           
                DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              F16                                                               
                MOVE            SEVEN,REPLY                                                
                ENDIF           032
                IF              F17                                                               
                MOVE            NINE,REPLY                                                 
                ENDIF           032
                IF              F18                                                              
                MOVE            FIVE,REPLY                                                 
                ENDIF           032
                IF              F19                                                              
                MOVE            ONE,REPLY                                                 
                ENDIF           032
                IF              F20                                                              
                MOVE            THREE,REPLY                                               
                ENDIF           032
                IF              UP                                                               
                MOVE            EIGHT,REPLY                                                
                ENDIF           032
                IF              DOWN                                                              
                MOVE            TWO,REPLY                                                  
                ENDIF           032
                IF              LEFT                                                              
                CMOVE           LEFT,REPLY                                                
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;                         
                GOTO            EC$CMD3                                                   
                ENDIF           032
                IF              RIGHT                                                             
                CMOVE           RIGHT,REPLY                                               
                DISPLAY         *H HPOS,*HA -1,*+,FUNCDESC;                               
                ENDIF           032
                GOTO            EC$CMD8 IF F1
                GOTO            EC$CMD8 IF F2                                             
                GOTO            EC$CMD8 IF F4                                             
                GOTO            EC$CMD7 IF F5
                GOTO            EC$CMD7 IF F9                                             
                GOTO            EC$CMD5 IF LESS
                GOTO            EC$CMD4 IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
*
.Check for a Direction Command
.
                CMATCH          SPACE,REPLY
                GOTO            EC$CMD2 IF EQUAL
                MOVE            ZERO,INDEX
                MOVE            REPLY,INDEX
                BRANCH          INDEX TO SELDAY20,ECSCRLDN,SELDAY20,EC$CMD3:
                                EC$CMD9,EC$CMD2,SELDAY20,ECSCRLUP,SELDAY20
*
.Check for a Function Letter
.
                RESET           ECLETS
                SCAN            REPLY,ECLETS
                IF              NOT EQUAL                      // Lower case option          
                RESET           ECLETS2                                           
                SCAN            REPLY,ECLETS2                                    
                GOTO            EC$CMD1 IF NOT EQUAL                               
                MOVEFPTR        ECLETS2,FUNC                                   
                GOTO            EC$CMD1                                         
                ENDIF           026                             
                MOVEFPTR        ECLETS,FUNC
                GOTO            EC$CMD1
*
.Move Right to the Next Function
.
EC$CMD2         ADD             ONE,FUNC
                COMPARE         TEN,FUNC
                GOTO            EC$CMD1 IF NOT EQUAL
                MOVE            ONE,FUNC
                GOTO            EC$CMD1
*
.Move Left to the Next Function
.
EC$CMD3         SUB             ONE,FUNC
                GOTO            EC$CMD1 IF NOT ZERO
                MOVE            NINE,FUNC
                GOTO            EC$CMD1
*
.We Have a Selected Function
.
EC$CMD4         BRANCH          FUNC TO SELDAY,ECADD,ECLOC,ECLOC,ECLOC,ECPRINT:
                                ECINQ,ECPACK,ECSRCH
                MOVE            ZERO,PRTSW                                     
                CALL            INTERR
*
.A Timeout Occurred
.
EC$CMD5         MOVE            ZERO,FLAG1
                CALL            CHKALRM
                CALL            CLOCKDT                                                  
                DISPLAY         *P59:1,DATE,SPACE2,TIME;
...............................................................................
.  This block of code added for the 2.7.A version to solve the problem of the .
.  day rollover at midnight.                                                  .
...............................................................................
                COMPARE         JDAYWORK TO JDAYOLD    // Compare for day rollover         
                IF              LESS                                                  
                MOVE            JDAYWORK TO JULDAY     // Julian day for appointments      
                CALL            JULGREG                // convert from julian to greg       
                MOVE            MONWORK TO MON         // move to month day and year       
                MOVE            DAYWORK TO DAY         // because draw calendar uses        
                MOVE            YEARWORK TO YEAR       // *the broken down date.            
                CALL            DRAWCAL                // Redisplay the calendar.          
                MOVE            ONE,GRAPHSW                                               
                CALL            GRAPH                  // Weekly appointments graph.        
                CALL            SHOWDTL1               // Daily appointment Calendar.      
                ENDIF           001
                GOTO            EC$CMD1
*
.Selected Function Not Allowed While Inquiring
.
EC$CMD6         KEYIN           *CLICK,*HD,*EL,*DV,FUNCNOT,REPLY;
                GOTO            EC$CMD
*
.Help Requested
.
EC$CMD7         MOVE            TWO,HMENU
                MOVE            FUNC,HFUNCNO
                CALL            HELP
                CALL            SHOWBOX1
                GOTO            CALENDR2
*
.Rebuild the Graph Record for the Selected Date
.
EC$CMD8         MOVE            YEAR,YEARWORK
                MOVE            JULDAY,JDAYWORK
                MOVE            ONE,FLAG1
                MOVE            ONE,FLAG5                                             
                CALL            DELTABL2
                MOVE            ZERO,FLAG5                                           
                SUB             ONE,COUNT
.
                PACK            DIM11 WITH USRNO,YEAR,JULDAY
                FILEPI          2;GRAPH
                DELETE          GRAPH,DIM11
.
                RESET           MONTABLE,DAY
                CMOVE           CN,MONTABLE
                COMPARE         ZERO,COUNT
                GOTO            EC$CMD81 IF EQUAL
                CMOVE           CY,MONTABLE
                WRITE           GRAPH,DIM11;DIM11,COUNT,TABLE
.
EC$CMD81        MOVE            JULDAY,JDAYWORK
                BRANCH          INQSW OF EC$CMDX                                          
                MOVE            ZERO,TERMTYPE        // Hilite Dates with appointments.   
                MOVE            ONE,F1HIT            // Force Highlighting if possible     
EC$CMDX
+.............................................................................
.
.Draw the Calendar
.
.  Enter with:  MON    = Month Selected
.               YEAR   = Year Selected
.               DAY    = Day Selected
.               USRNO  = User Number
.            TERMTYPE  = 0 - Advanced Video Features Available
.                        1 - Advanced Video Features Unavailable
.
.  Exits with:  Calendar on the Screen
.               Selected Day Highlighted
.               ENDDAY          = Number of Days in Month
.               HPOSEND/VPOSEND = Screen Position of the Last Day in the Month
.               MONTABLE        = Set Up
.
*
.Redisplay the Selected Day's Appointments
.
                CALL            DRAWCAL
                MOVE            JULDAY,JDAYWORK   // Return to original date.             
                CALL            DISPDAY
                CALL            SHOWDTL1
                MOVE            ZERO,F1HIT
                BRANCH          INQSW OF ECINQ6                                        
                GOTO            EC$CMD1
*
.Express Command Handler
.
EC$CMD9         KEYIN           *H HPOS,*HA -1,*T2,*+,*RV,REPLY;
                IF              F16                                                              
                MOVE            SEVEN,REPLY                                               
                ENDIF           032
                IF              F17                                                               
                MOVE            NINE,REPLY                                                 
                ENDIF           032
                IF              LEFT                                                               
                MOVE            FOUR,REPLY                                                
                ENDIF           032
                IF              RIGHT                                                              
                MOVE            SIX,REPLY                                                 
                ENDIF           032
                GOTO            EC$CMD1 IF LESS
                GOTO            EC$CMD1 IF EOS
                DISPLAY         *HA -1,SPACE;
.
                MOVE            ZERO,NWORK1
                MOVE            REPLY,NWORK1
                BRANCH          NWORK1 TO EC$CMD1,EC$CMD1,EC$CMD1,GRAPHLT:
                                EC$CMD1,GRAPHRT,PREVMON,EC$CMD1,NEXTMON
.        If no express key was struck, then return to ring (un-express)
                GOTO            EC$CMD1
+.............................................................................
.
.                    S H I F T   T H E   G R A P H   R I G H T
...............................................................................
.
.
GRAPHRT         ADD             ONE,GRAPHPOS
                COMPARE         FOUR,GRAPHPOS
                GOTO            GRAPHRT2 IF LESS
                MOVE            ONE,GRAPHPOS
.
GRAPHRT2        MOVE            ONE,GRAPHSW
                CALL            GRAPH
                CALL            SHOWDTL5
                BRANCH          INQSW OF ECINQ7                                         
                GOTO            EC$CMD1
*.............................................................................
.
.                   S H I F T   T H E   G R A P H   L E F T
...............................................................................
.
GRAPHLT         SUB             ONE,GRAPHPOS
                GOTO            GRAPHRT2 IF NOT ZERO
                MOVE            THREE,GRAPHPOS
                GOTO            GRAPHRT2
+.............................................................................
.
.           S C R O L L   T H E   A P P O I N T M E N T S   D O W N
...............................................................................
.
.
.First, Is the Screen Full ?
.
ECSCRLDN
                COMPARE         SIX,DTLCOUNT
                GOTO            ECSCRLD1 IF NOT EQUAL       // No; That's All the Records
*
.Try to Read Another Appointment Record
.
                BRANCH          NOMORE TO ECSCRLD1
.
                FILEPI          2;AGENDA
                READ            AGENDA,KEYF;;

                READKS          AGENDA;USRNO1,YEARWORK,JDAYWORK,HOURWORK,MINWORK,COUNTER:
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                GOTO            ECSCRLD1 IF OVER
.
                COMPARE         ZERO,INQSW               //   If Inquiring, don't show
                GOTO            ECSCRLD4 IF EQUAL        //   confidential records.
                CMATCH          "*",SECFLAG
                GOTO            ECSCRLD4 IF NOT EQUAL
                MOVE            CONMSG,DATA
.
ECSCRLD4
                PACK            KEY17 WITH USRNO1,YEARWORK,JDAYWORK,HOURWORK,MINWORK,COUNTER
                PACK            KEYWORK WITH USRNO,YEAR,JULDAY
.
                MATCH           KEY17,KEYWORK
                GOTO            ECSCRLD2 IF EQUAL
*
.There are No More Records
.
ECSCRLD1        BEEP
                MOVE            ONE,NOMORE
                BRANCH          INQSW OF ECINQ7                                        
                GOTO            EC$CMD1
*
.Display the New Record
.
ECSCRLD2        DISPLAY         *SETSWTB 16:21,*SETSWLR 2:79,*R,*HD,*H 2,STIME:
                                *H 12,ETIME,*H 22,*+,SECFLAG,DATA,*SETSWALL=1:24:1:80;            
                DISPLAY         *P=23:15,*LTK,MOREPR,*UPA,SPACE,*RTK;                  
                FILEPI          1;AGENDA                                               
                READKS          AGENDA;USRNO1,YEARWORK,JDAYWORK                         
                COMPARE         JULDAY,JDAYWORK                                         
                IF              NOT EQUAL                                                      
                DISPLAY         *P=23:22,*RPTCHAR=HB:10;                                
                ENDIF           
                COMPARE         YEAR,YEARWORK                                          
                IF              NOT EQUAL                                                      
                DISPLAY         *P=23:22,*RPTCHAR=HB:10;                                
                ENDIF           
                COMPARE         USRNO1,USRNO                                            
                IF              NOT EQUAL                                                      
                DISPLAY         *P=23:22,*RPTCHAR=HB:10;                                
                ENDIF          
                FILEPI          1;AGENDA                                               
                READKP          AGENDA;USRNO1                                           
*
.Rearrange the Key List
.
                MOVE            ONE,DTLCOUNT
                MOVE            TWO,NWORK1
.
ECSCRLD3
                CALL            LOAD04
                STORE           KEYWORK BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
.
                ADD             ONE,DTLCOUNT
                ADD             ONE,NWORK1
                COMPARE         SIX,DTLCOUNT
                GOTO            ECSCRLD3 IF NOT EQUAL
*
.Exit the Scroll Up Function
.
                MOVE            KEY17,KEYF
                MOVE            ZERO,NOPREV      Indicate Previous Records Exist
                BRANCH          INQSW OF ECINQ7                                          
                GOTO            EC$CMD1
+.............................................................................
.
.              S C R O L L   T H E   A P P O I N T M E N T S   U P
...............................................................................
.
.
.We are at the Top; Is There Some Previous Records ?
.
ECSCRLUP        BRANCH          NOPREV TO ECSCRLU1
*
.Try to Read Another Previous Detail Record
.
                FILEPI          2;AGENDA
                READ            AGENDA,KEYA;;
                READKP          AGENDA;USRNO1,YEARWORK,JDAYWORK,HOURWORK,MINWORK,COUNTER:
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                GOTO            ECSCRLU1 IF OVER
.
                COMPARE         ZERO,INQSW                  // If Inquiring, don't show
                GOTO            ECSCRLU4 IF EQUAL           // confidential records.
                CMATCH          "*",SECFLAG
                GOTO            ECSCRLU4 IF NOT EQUAL
                MOVE            CONMSG,DATA
.
ECSCRLU4
                PACK            KEY17 WITH USRNO1,YEARWORK,JDAYWORK,HOURWORK,MINWORK,COUNTER
                PACK            KEYWORK WITH USRNO,YEAR,JULDAY
                MATCH           KEY17,KEYWORK
                GOTO            ECSCRLU2 IF EQUAL
*
.There are No More Previous Records
.
ECSCRLU1        BEEP
                MOVE            ONE,NOPREV
                BRANCH          INQSW OF ECINQ7                                         
                GOTO            EC$CMD1
*
.Display the New Record
.
ECSCRLU2        DISPLAY         *SETSWTB 16:21,*SETSWLR 2:79,*HU,*OPNLIN,*H 2,STIME:
                                *H 12,ETIME,*H 22,*+,SECFLAG,DATA,*SETSWALL=1:24:1:80;              
                DISPLAY         *P=23:22,*LTK,MOREPR,*DNA,SPACE,*RTK;                  
                FILEPI          1;AGENDA                                                
                READKP          AGENDA;USRNO1,YEARWORK,JDAYWORK                        
                COMPARE         JULDAY,JDAYWORK                                        
                IF              NOT EQUAL                                                     
                DISPLAY         *P=23:15,*RPTCHAR=HB:10;                               
                ENDIF          
                COMPARE         YEAR,YEARWORK                                           
                IF              NOT EQUAL                                                      
                DISPLAY         *P=23:15,*RPTCHAR=HB:10;                               
                ENDIF           
                COMPARE         USRNO1,USRNO                                           
                IF              NOT EQUAL                                                     
                DISPLAY         *P=23:15,*RPTCHAR=HB:10;                               
                ENDIF           
                FILEPI          1;AGENDA                                                
                READKS          AGENDA;USRNO1                                           
*
.Rearrange the Key List
.
                MOVE            SIX,DTLCOUNT
                MOVE            FIVE,NWORK1
.
ECSCRLU3
                CALL            LOAD04
                STORE           KEYWORK BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
                SUB             ONE,DTLCOUNT
                SUB             ONE,NWORK1
                GOTO            ECSCRLU3 IF NOT EQUAL
*
.Exit the Scroll Down Function
.
                MOVE            KEY17,KEYA
                MOVE            ZERO,NOMORE
                MOVE            SIX,DTLCOUNT
                BRANCH          INQSW OF ECINQ7                                         
                GOTO            EC$CMD1
+.............................................................................
.
.                       Y E A R   S E L E C T I O N
...............................................................................
.
.
.Select a New Year
.
SELYEAR         DISPLAY         *HD,*EL,LITENT,YRPER;
                KEYIN           *HOFF,*P2:3,*DV,YEARPR,*HON,"20",*DV,YEAR,*HOFF:
                                *HA -2,*RV,NWORK2;
                GOTO            SELYEAR1 IF F5
.
                COMPARE         TWENTY,NWORK2
                GOTO            SELYEAR IF LESS
.
                MOVE            NWORK2,YEAR
SELYEAR1        DISPLAY         *H 10,*HON,YEAR,*HOFF;
                GOTO            CALENDR3 IF F5
*
.Do the Yearly Calculations
.
                MOVE            YEAR,YEARWORK
                CALL            YEARCOMP
+.............................................................................
.
.                      M O N T H   S E L E C T I O N
.............................................................................
.
.Select a New Month
.
SELMONTH
                CALL            SETMAR01
                DISPLAY         *HD,*EL,RLCMD;
                TRAP            SELMON6 IF ESCAPE                                 
                TRAP            SELMON6 IF F27                                     
.
SELMON1         MOVE            MON,HPOS
                SUB             ONE,HPOS
                MULT            FIVE,HPOS
                ADD             SEVNTEEN,HPOS
                CALL            LOAD01
*
.Get a Command
.
                KEYIN           *PHPOS:3,*HON,*DV,MONTH,*HA -4,*+,*RV,REPLY;
                IF              LEFT                                                               
                CMOVE           LEFT,REPLY                                                
                ENDIF           
                IF              RIGHT                                                               
                CMOVE           RIGHT,REPLY                                               
                ENDIF           
                DISPLAY         *HOFF,*H HPOS,*HA -1,SPACE,MONTH;
                GOTO            SELYEAR IF F5
                GOTO            SELMON6 IF EOS
.
                CMATCH          064,REPLY
                GOTO            SELMON4 IF EQUAL
                CMATCH          SPACE,REPLY
                GOTO            SELMON2 IF EQUAL
                CMATCH          066,REPLY
                GOTO            SELMON1 IF NOT EQUAL
*
.Move Right to the Next Month
.
SELMON2         ADD             ONE,MON
                COMPARE         THIRTEEN,MON
                GOTO            SELMON1 IF NOT EQUAL
                MOVE            ONE,MON
                ADD             ONE,YEAR
                GOTO            SELMON3 IF NOT OVER
                MOVE            TWENTY,YEAR
.
SELMON3         DISPLAY         *HOFF,*P2:3,YEARPR,*HON,"20",YEAR,*HOFF;
                MOVE            YEAR,YEARWORK
                CALL            YEARCOMP
                GOTO            SELMON1
*
.Move Left to the Next Month
.
SELMON4         SUB             ONE,MON
                GOTO            SELMON1 IF NOT ZERO
                MOVE            TWELVE,MON
                SUB             ONE,YEAR
                COMPARE         TWENTY,YEAR
                GOTO            SELMON5 IF NOT LESS
                MOVE            NINTY9,YEAR
.
SELMON5         DISPLAY         *H 10,*HON,YEAR,*HOFF;
                MOVE            YEAR,YEARWORK
                CALL            YEARCOMP
                GOTO            SELMON1
*
.We Have a Selected Month
.
SELMON6         DISPLAY         *HON,*H HPOS,MONTH,*HOFF;
                CALL            DRAWCAL
+.............................................................................
.
.                        D A Y   S E L E C T I O N
..............................................................................
.
.Select a New Day
.
SELDAY          MOVE            ONE,CMDTRAP                                          
                TRAP            SELD19 IF ESCAPE                                  
                TRAP            SELD19 IF F27                              
.
                MOVE            ZERO,DTLCOUNT
                MOVE            SIXTEEN,VPOS
                MOVE            ONE,FLAG1
.
                DISPLAY         *HD,*EL,LRUDCMD;
*
.Get a Command
.
SELDAY1         KEYIN           *PHPOSDAY:VPOSDAY,*HON,*DV,DAY,*+,*HA -1,*RV,REPLY;
                IF              UP                                                           
                MOVE            EIGHT,REPLY                                          
                ENDIF           
                IF              DOWN                                                           
                MOVE            TWO,REPLY                                            
                ENDIF           
                IF              LEFT                                                          
                MOVE            FOUR,REPLY                                           
                ENDIF           
                IF              RIGHT                                                          
                MOVE            SIX,REPLY                                             
                ENDIF           
                DISPLAY         *HOFF,*H HPOSDAY,DAY;
                GOTO            SELMONTH IF F5
                GOTO            SELDAY19 IF EOS
.
                BRANCH          TERMTYPE TO SELDAY0
                RESET           MONTABLE,DAY
                CMATCH          CY,MONTABLE
                GOTO            SELDAY0 IF NOT EQUAL
                DISPLAY         *V2LON,*H HPOSDAY,DAY,*HOFF;
.
SELDAY0         MOVE            ZERO,INDEX
                MOVE            REPLY,INDEX
                BRANCH          INDEX TO SELDAY1,SELDAY16,SELDAY1,SELDAY7:
                                SELDAY1,SELDAY2,SELDAY1,SELDAY13
                GOTO            SELDAY1
*
.Move Right to the Next Day
.
SELDAY2         COMPARE         ENDDAY,DAY
                GOTO            SELDAY3 IF EQUAL
.
                ADD             ONE,DAY
                ADD             THREE,HPOSDAY
                COMPARE         TWENTY5,HPOSDAY
                GOTO            SELDAY18 IF NOT EQUAL
*
.Change Weeks
.
                MOVE            FOUR,HPOSDAY
                ADD             ONE,VPOSDAY
                GOTO            SELDAY18
*
.Wrap to the 1st of the Next Month
.
SELDAY3         MOVE            ONE,DAY
.
SELDAY4         MOVE            MON,HPOS
                SUB             ONE,HPOS
                MULT            FIVE,HPOS
                ADD             SEVNTEEN,HPOS
                CALL            LOAD01
.
                DISPLAY         *PHPOS:3,MONTH;
                CALL            SETMAR01
*
.Increment the Month
.
                ADD             ONE,MON
                COMPARE         THIRTEEN,MON
                GOTO            SELDAY6 IF NOT EQUAL
                MOVE            ONE,MON
                ADD             ONE,YEAR
                GOTO            SELDAY5 IF NOT OVER
                MOVE            TWENTY,YEAR
.
SELDAY5         DISPLAY         *P10:3,*HON,YEAR,*HOFF;
                MOVE            YEAR,YEARWORK
                CALL            YEARCOMP
*
.Highlight the New Month
.
SELDAY6         MOVE            MON,HPOS
                SUB             ONE,HPOS
                MULT            FIVE,HPOS
                ADD             SEVNTEEN,HPOS
.
                CALL            LOAD01
.
                DISPLAY         *PHPOS:3,*HON,MONTH,*HOFF;
*
.Draw the New Month's Calendar
.
                MOVE            YEAR,YEARWORK
                MOVE            DAY,DAYWORK
                MOVE            MON,MONWORK
                CALL            GREGJUL
                MOVE            JDAYWORK,JULDAY
.
                CALL            DRAWCAL
                GOTO            SELDAY18
*
.Move Left to the Previous Day
.
SELDAY7         BRANCH          DAY TO SELDAY8
.
                SUB             ONE,DAY
                SUB             THREE,HPOSDAY
                COMPARE         ONE,HPOSDAY
                GOTO            SELDAY18 IF NOT EQUAL
*
.Change Weeks
.
                MOVE            TWENTY2,HPOSDAY
                SUB             ONE,VPOSDAY
                GOTO            SELDAY18
*
.Wrap to the End of the Previous Month
.
SELDAY8         MOVE            MON,NWORK2
                SUB             ONE,NWORK2
                GOTO            SELDAY9 IF NOT ZERO
                MOVE            TWELVE,NWORK2
.
SELDAY9         LOAD            DAY BY NWORK2 FROM THIRTY1,DAYFEB,THIRTY1,THIRTY:
                                THIRTY1,THIRTY,THIRTY1,THIRTY1,THIRTY,THIRTY1:
                                THIRTY,THIRTY1
*
.Turn Off the Current Month
.
SELDAY10        MOVE            MON,HPOS
                SUB             ONE,HPOS
                MULT            FIVE,HPOS
                ADD             SEVNTEEN,HPOS
                CALL            LOAD01
.
                DISPLAY         *PHPOS:3,MONTH;
                CALL            SETMAR01
*
.Decrement the Month
.
                SUB             ONE,MON
                GOTO            SELDAY12 IF NOT ZERO
                MOVE            TWELVE,MON
                SUB             ONE,YEAR
                COMPARE         TWENTY,YEAR
                GOTO            SELDAY11 IF NOT LESS
                MOVE            NINTY9,YEAR
.
SELDAY11        DISPLAY         *P10:3,*HON,YEAR,*HOFF;
                MOVE            YEAR,YEARWORK
                CALL            YEARCOMP
*
.Highlight the New Month
.
SELDAY12        MOVE            MON,HPOS
                SUB             ONE,HPOS
                MULT            FIVE,HPOS
                ADD             SEVNTEEN,HPOS
.
                CALL            LOAD01
.
                DISPLAY         *PHPOS:3,*HON,MONTH,*HOFF;
*
.Draw the Calendar
.
                MOVE            DAY,DAYWORK
                MOVE            MON,MONWORK
                MOVE            YEAR,YEARWORK
                CALL            GREGJUL
                MOVE            JDAYWORK,JULDAY
                CALL            DRAWCAL
                GOTO            SELDAY18
*
.Move Up One Week
.
SELDAY13        COMPARE         EIGHT,DAY
                GOTO            SELDAY14 IF LESS
.
                SUB             SEVEN,DAY
                SUB             ONE,VPOSDAY
                GOTO            SELDAY18
*
.Wrap the the Previous Month
.
SELDAY14        MOVE            MON,NWORK2
                SUB             ONE,NWORK2
                GOTO            SELDAY15 IF NOT ZERO
                MOVE            TWELVE,NWORK2
.
SELDAY15        LOAD            ENDDAY BY NWORK2 FROM THIRTY1,DAYFEB,THIRTY1,THIRTY:
                                THIRTY1,THIRTY,THIRTY1,THIRTY1,THIRTY,THIRTY1:
                                THIRTY,THIRTY1
                SUB             SEVEN,DAY
                ADD             ENDDAY,DAY
                GOTO            SELDAY10
*
.Move Down a Week
.
SELDAY16        MOVE            ENDDAY,NWORK1
                SUB             DAY,NWORK1
                COMPARE         SEVEN,NWORK1
                GOTO            SELDAY17 IF LESS
.
                ADD             SEVEN,DAY
                ADD             ONE,VPOSDAY
                GOTO            SELDAY18
*
.Wrap to the Next Month
.
SELDAY17        ADD             SEVEN,DAY
                SUB             ENDDAY,DAY
                GOTO            SELDAY4
*
.Return to Day Selection or the Command Line as Needed
.
SELDAY18        BRANCH          FLAG1 TO SELDAY1
.
                DISPLAY         *PHPOSDAY:VPOSDAY,*HON,DAY,*HOFF;
.
                MOVE            DAY,DAYWORK
                MOVE            MON,MONWORK
                MOVE            YEAR,YEARWORK
                CALL            GREGJUL
                MOVE            JDAYWORK,JULDAY
.
                MOVE            ZERO,GRAPHSW
                CALL            GRAPH
                CALL            SHOWDTL1
                BRANCH          INQSW OF ECINQ6                                   
                GOTO            EC$CMD1
*
.We Have a Selected Day; Compute the Julian Date
.
SELD19          NORETURN        *dsh
SELDAY19        DISPLAY         *HON,*H HPOSDAY,DAY,*HOFF;
                MOVE            MON,MONWORK
                MOVE            DAY,DAYWORK
                MOVE            YEAR,YEARWORK
                CALL            GREGJUL
                MOVE            JDAYWORK,JULDAY
*
.Display the Week's Graph and Day's Appointments
.
                MOVE            ONE,GRAPHSW
                CALL            GRAPH
                CALL            SHOWDTL1
                BRANCH          INQSW OF ECINQ6                                    
                GOTO            EC$CMD
*
.Increment or Decrement by Day or Week
.
SELDAY20        DISPLAY         *PHPOSDAY:VPOSDAY,DAY;
.
                BRANCH          TERMTYPE TO SELDAY21
                RESET           MONTABLE,DAY
                CMATCH          CY,MONTABLE
                GOTO            SELDAY21 IF NOT EQUAL
                DISPLAY         *V2LON,*PHPOSDAY:VPOSDAY,DAY,*HOFF;
.
SELDAY21        MOVE            ZERO,FLAG1
                BRANCH          INDEX TO SELDAY7,SELDAY22,SELDAY2,SELDAY22:
                                SELDAY22,SELDAY22,SELDAY13,SELDAY22,SELDAY16
.
SELDAY22        CALL            INTERR
                GOTO            LOGON
+..............................................................................
.
.                  P O S I T I O N   B A C K   O N E   M O N T H
...............................................................................
.
PREVMON         SUB             ONE,MON
                GOTO            PREVMON1 IF NOT ZERO
                MOVE            TWELVE,MON
                SUB             ONE,YEAR
.
PREVMON1        MOVE            MON,MONWORK
                MOVE            DAY,DAYWORK
                MOVE            YEAR,YEARWORK
                CALL            GREGJUL
.
                MOVE            JDAYWORK,JULDAY
                CALL            SETMAR01
                GOTO            CALENDR2
*..............................................................................
.
.                 P O S I T I O N   F O R W A R D   M O N T H
...............................................................................
.
.
NEXTMON         ADD             ONE,MON
                COMPARE         THIRTEEN,MON
                GOTO            PREVMON1 IF NOT EQUAL
.
                MOVE            ONE,MON
                ADD             ONE,YEAR
                GOTO            PREVMON1
+..............................................................................
.
.                   A P P O I N T M E N T    A D D I T I O N
...............................................................................
.
.
ECADD           BRANCH          INQSW TO EC$CMD6
                MOVE            ZERO,FLAG2
                MOVE            TWO,CMDTRAP                                            
                TRAP            ECADD15 IF ESCAPE                                     
                TRAP            ECADD15 IF F27                                       
*
.Compute the Vertical Position
.
ECADD1          MOVE            DTLCOUNT,VPOS
                ADD             SIXTEEN,VPOS
*
.If Appointment Area is Full, Clear it Out
.
                COMPARE         SIX,DTLCOUNT
                GOTO            ECADD3 IF NOT EQUAL      // Not Full
.
                CALL            SETTOP16
                CALL            SETSW01
                UNPACK          REPLY INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
                MOVE            ZERO,DTLCOUNT
                MOVE            SIXTEEN,VPOS
                MOVE            TWO,FLAG2
*
.Get the Starting Time
.
ECADD3          DISPLAY         *HD,*EL,LITAPPT,LITST,NOTCONT:
                                *SETSWLR 2:79,*P1:VPOS,*EL,*SETSWALL=1:24:1:80;
.
                MOVE            THREE,HPOS
                MOVE            ZERO,MASKSW
                MOVE            ZERO,REQFLAG
                CALL            GETIME
.
                BRANCH          FLAG1 TO ECADD15
                BRANCH          EOSFLAG TO ECADD39
.
                MOVE            HOURWORK,HOUR
                MOVE            MINWORK,MIN
                MOVE            TIME,STIME
*
.See if the Starting Time Conflicts With a Existing Appointment
.
                MOVE            ZERO,SWITCH
                CALL            POSITABL
                CMATCH          CN,TABLE
                GOTO            ECADD4 IF EQUAL
                MOVE            ONE,SWITCH
*
.We Have a Schedule Conflict; Should We Continue ?
.
                CALL            GETCCR               // Prompt Schedule Conflict         
                CMATCH          YES,REPLY                                              
                GOTO            ECADD3 IF NOT EQUAL   // No...
*
.Get the Appointment Ending Time
.
ECADD4          DISPLAY         *HD,*EL,LITAPPT,LITET:
                                *SETSWLR 2:79,*P12:VPOS,*EL,*SETSWALL=1:24:1:80;
.
                MOVE            THIRTEEN,HPOS
                MOVE            ONE,REQFLAG
                CALL            GETIME
.
                BRANCH          FLAG1 TO ECADD3
.
                MOVE            HOURWORK,ENDHOUR
                MOVE            MINWORK,ENDMIN
                MOVE            TIME,ETIME
*
.Make Sure the Appointment Begins Before it Ends
.
                CALL            CHECKEND
                BRANCH          FLAG1 TO ECADD4
*
.Compute the Number of 15 Minute Blocks to Allocate
.
                CALL            COMPUTE
*
.Check for a Schedule Conflict
.
                BRANCH          SWITCH TO ECADD5      We Know It Does
                CALL            CHECK
                GOTO            ECADD5 IF EQUAL       No Schedule Conflict
*
.There is a Schedule Conflict; Should We Continue ?
.
                CALL            GETCCR               // Prompt Schedule Conflict    
                CMATCH          YES,REPLY                                           
                GOTO            ECADD4 IF NOT EQUAL
*
.Get the Appointment Information
.
ECADD5          KEYIN           *HD,*EL,*DV,LITAPPT,*DV,INFOPR:
                                *P24:VPOS,*RPTCHAR "_":55,*HA -55,*IT,DATA;
                DISPLAY         *IN,*H 24,DATA;
                GOTO            ECADD4 IF F5
.
                CMATCH          SPACE,DATA
                GOTO            ECADD5 IF EOS
*
.See if the Appointment is Tentative or Firm
.
ECADD6          MOVE            F,TFLAG
                KEYIN           *HD,*EL,*DV,LITIST,*HA -1,*RV,TFLAG;
                GOTO            ECADD5 IF F5
.
                CMATCH          TENTAT,TFLAG
                GOTO            ECADD7 IF EQUAL
                CMATCH          FIRM,TFLAG
                GOTO            ECADD6 IF NOT EQUAL
*
.See if the Appointment Information is Confidential
.
ECADD7          COMPARE         ZERO,NBLOCKS
                GOTO            ECADD40 IF EQUAL       Note Pad Backup
.
ECADD75
                RESET           SECFLAG
                CMOVE           YES,SECFLAG                            
                KEYIN           *HD,*EL,*DV,CONFPR,*HA -1,*RV,SECFLAG;
                AND             0137 TO REPLY                                      
                GOTO            ECADD6 IF F5
.
                CMATCH          YES,SECFLAG                                        
                GOTO            ECADD8 IF EQUAL
                CMATCH          NO,SECFLAG                                        
                GOTO            ECADD7 IF NOT EQUAL
.
ECADD8          REP             SECREP,SECFLAG                                        
                DISPLAY         *P23:VPOS,SECFLAG;
                MOVE            ZERO,COUNTER
*
.See if the Appointment Reoccurs
.
ECADD9          MOVE            ZERO,INDEX
                CMOVE           NO,REPLY                                             
                DISPLAY         *HD,*EL,REPR;
                CALL            KREPLYN
                GOTO            ECADD7 IF F5
.
                CMATCH          YES,REPLY                                            
                GOTO            ECADD16 IF EQUAL
                CMATCH          NO,REPLY                                     
                GOTO            ECADD9 IF NOT EQUAL                                   
*
.Write the Information to Disk
.
ECADD11         ADD             ONE,COUNTER
                PACK            KEY17 WITH USRNO,YEAR,JULDAY,HOUR,MIN,COUNTER
.
                FILEPI          1;AGENDA
                READ            AGENDA,KEY17;REPLY
                GOTO            ECADD11 IF NOT OVER
.
                CALL            AG1010
*
.Update the Day's Table
.
                COMPARE         ZERO,NBLOCKS
                GOTO            ECADD13 IF EQUAL
                CALL            ADDTABLE
*
.Display the Day's Graph
.
                MOVE            JULDAY,JDAYWORK
                CALL            DISPDAY
*
.Update the Graph Record
.
                ADD             ONE,COUNT
                PACK            DIM11 WITH USRNO,YEAR,JULDAY
.
                FILEPI          2;GRAPH
                READTAB         GRAPH,DIM11;REPLY
                GOTO            ECADD12 IF OVER
.
                UPDATE          GRAPH;DIM11,COUNT,TABLE
                GOTO            ECADD13
.
ECADD12         MOVE            ONE,COUNT
                FILEPI          1;GRAPH
                WRITE           GRAPH,DIM11;DIM11,COUNT,TABLE
                RESET           MONTABLE,DAY
                CMOVE           CY,MONTABLE
*
.Add the Key to the Key List
.
ECADD13         ADD             ONE,DTLCOUNT
                STORE           KEY17 BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
.
                COMPARE         ZERO,FLAG2
                GOTO            ECADD14 IF NOT EQUAL
                MOVE            ONE,FLAG2
*
.Addition Complete
.
ECADD14         DISPLAY         *HD,*EL;
                COMPARE         SIX,DTLCOUNT
                GOTO            ECADD1 IF NOT EQUAL
                GOTO            ECADD15A
*
.Exit the Addition Routine
.
ECADD15         NORETURN
                DISPLAY         *SETSWLR 2:79,*P1:VPOS,*EL,*SETSWALL=1:24:1:80;
ECADD15A
                TRAPCLR         ESCAPE                                 
                TRAPCLR         F27                                     
                COMPARE         TWO,FLAG2            // Redisplay Detail Records ?
                CALL            SHOWDTL1 IF EQUAL    // Yes....
                GOTO            EC$CMD
+..............................................................................
.
. Reoccurring Appointment
.
. This is the Verification routine for Reoccurring Appointments. It will
.  first check for schedule conflicts on any of the dates specified, and
.  if any are found, the user will be shown the date and allowed to continue
.  the Verification or Exit.
*
.Get the Frequency
.
ECADD16         MOVE            CD,REPLY
                KEYIN           *HD,*EL,*DV,REDWMPR,*HA -1,*RV,REPLY;
                GOTO            ECADD9 IF F5
.
                REP             DWMREP,REPLY
                MOVE            ZERO,FREQ
                MOVE            REPLY,FREQ
                COMPARE         ZERO,FREQ
                GOTO            ECADD16 IF EQUAL
                COMPARE         FOUR,FREQ
                GOTO            ECADD16 IF NOT LESS
*
.Get the Number of Times It Reoccurs
.
ECADD17         KEYIN           *HD,*EL,*DV,NUMOCC,INDEX;
                GOTO            ECADD16 IF F5
.
                COMPARE         ONE,INDEX
                GOTO            ECADD17 IF LESS
*
.We Can't Exclude Weekends If the Selected Date is on a Weekend
.
                MOVE            JULDAY,JDAYWORK
                MOVE            YEAR,YEARWORK
                CALL            FINDOW
.
                MOVE            ONE,SWITCH
                BRANCH          NWORK2 TO ECADD19,ECADD18,ECADD18,ECADD18:
                                ECADD18,ECADD18,ECADD19
                CALL            INTERR
*
.Weekly or Monthly Occurrances Don't Care about Weekends
.
ECADD18         MOVE            ONE,SWITCH
                COMPARE         ONE,FREQ                // Daily Reoccurrance ?
                GOTO            ECADD19 IF NOT EQUAL    // No, Never Mind Excluding
*
.See if We Will Reach a Weekend
.
                MOVE            JULDAY,JDAYWORK
                MOVE            YEAR,YEARWORK
                CALL            FINDOW
                ADD             INDEX,NWORK2
                COMPARE         EIGHT,NWORK2
                GOTO            ECADD19 IF LESS        // We Won't Involve a Weekend
*
.Exclude Weekends ?
.
                DISPLAY         *HD,*EL,EXWKEND;
                CALL            KREPLYN
                GOTO            ECADD17 IF F5
.
                REP             REPYN,REPLY
                MOVE            REPLY,SWITCH
*
.Initialize the Variables
.
ECADD19         MOVE            INDEX,LINE            // Save the Number of Occurrances
                COMPARE         ZERO,NBLOCKS          // Note ?
                GOTO            ECADD27 IF EQUAL      // Yes, Skip Checking
.
                MOVE            ZERO,COUNTER
                MOVE            JULDAY,JDAYWORK
                MOVE            YEAR,YEARWORK
                GOTO            ECAD2X2
*
.Check the Date
.
ECADD20         BRANCH          SWITCH TO ECADD21
.
                CALL            FINDOW
                BRANCH          NWORK2 TO ECADD23,ECADD21,ECADD21,ECADD21:
                                ECADD21,ECADD21,ECADD23
                CALL            INTERR
*
.Display the Date
.
ECADD21         CALL            JULGREG
                DISPLAY         *P69:24,DATE;
*
.Read the Graph Record for This Date
.
                PACK            DIM11 WITH USRNO,YEARWORK,JDAYWORK
.
                FILEPI          1;GRAPH
                READ            GRAPH,DIM11;DIM11,COUNT,TABLE
                GOTO            ECADD22 IF OVER      // No Conflict
*
.Check for a Conflict on This Date
.
                CALL            CHECK
                GOTO            ECADD22 IF EQUAL     // No Conflict
*
.We Have a Conflict
.
                ADD             ONE,COUNTER
                DISPLAY         *CLICK,*HD,*EL,MPFUNC2,CONFPR2,DATE,CONTPR;
                CALL            KREPLYY
.
                CMATCH          NO,REPLY                                                
                GOTO            ECADD35 IF EQUAL
*                                                                            
.Presents option and then sets flags.                                        
.                                                                           
ECAD2X2
                COMPARE         FREQ,THREE                                             
                GOTO            ECAD2Y2 IF NOT EQUAL                                   
                COMPARE         LOOPFLG,ONE                                             
                GOTO            ECADD22 IF EQUAL                                         
                TRAP            ROHELP IF F5                                             
                TRAP            ROHELP IF F9                                             
                KEYIN           *HD,*EL,*DV,REDTPR,REPLY;                                
                REP             REPDT,REPLY                                              
                MOVE            REPLY,ROFLAG                                            
                MOVE            ONE,LOOPFLG                                              
ECAD2Y2         DISPLAY         *HD,*EL,CHKPR,MPFUNC2,CONPR;                            
*
.This Day is OK, Position to the Next Day
.
ECADD22         SUB             ONE,INDEX            // Decrement the Count
                GOTO            ECADD26 IF EQUAL     // All are Verified
.
ECADD23         COMPARE         THREE,FREQ           // Handle Monthly Specially
                GOTO            ECADD24 IF EQUAL
.
                CALL            LOAD06
                GOTO            ECADD25
.
ECADD24         CALL            JULGREG              // Determine Gregorian Month
                CALL            YEARCOMP             // Determine the Number of Days in Feb
*                                                                            
.Day option is selected, compute # of weeks to advance, and advance         
.                                                                            
                COMPARE         FREQ,THREE                                               
                GOTO            ECADD25 IF NOT EQUAL                                      
                COMPARE         ROFLAG,ZERO                                               
                IF              EQUAL                                                       
                MOVE            TWO,FREQ                                                  
                CALL            CALCWEEKS                                                 
                ELSE            016
                CALL            LOAD02
                ENDIF           016
.
ECADD25         ADD             NWORK1,JDAYWORK      // Add in the Frequency
                COMPARE         JDAYWORK,YEARLEN     // Did We Eclipse the Year ?          
                GOTO            ECADD20 IF NOT LESS  // No                              
                ADD             ONE,YEARWORK         // Wrap to the First of the Next Year
                SUB             YEARLEN,JDAYWORK
                GOTO            ECADD20
*
.This Routine will Actually Add the Reoccurring Appointments
.
ECADD26         COMPARE         ZERO,COUNTER
                GOTO            ECADD27 IF EQUAL     There Were Some Conflicts
.
                DISPLAY         *CLICK,*HD,*EL,NUMPR,MPFUNC2,CONPR2,COUNTER,ADDPR;
                CALL            KREPLYY
                CMATCH          NO,REPLY                                            
                GOTO            ECADD37 IF EQUAL
*
.Reset the Date and Other Variables
.
ECADD27         MOVE            JULDAY,JDAYWORK
                MOVE            YEAR,YEARWORK
                CALL            YEARCOMP
                DISPLAY         *HD,*EL,ADDINFO;
                TRAPCLR         ESCAPE                                              
                TRAPCLR         F27                                                
*
.Generate the Appointment Records
.
ECADD28         BRANCH          SWITCH TO ECADD29
.
                CALL            FINDOW
                BRANCH          NWORK2 TO ECADD34,ECADD29,ECADD29,ECADD29:
                                ECADD29,ECADD29,ECADD34
                CALL            INTERR
.
ECADD29         CALL            JULGREG
                DISPLAY         *P69:24,DATE;
                COMPARE         ZERO,NBLOCKS
                GOTO            ECADD31 IF EQUAL
*
.Update the Graph File
.
                PACK            DIM11 WITH USRNO,YEARWORK,JDAYWORK
.
                FILEPI          1;GRAPH
                READ            GRAPH,DIM11;USRNO1,YEARWRK1,JDAYWRK1,COUNT,TABLE
                GOTO            ECADD30 IF OVER
.
                ADD             ONE,COUNT
                CALL            ADDTABLE
                CALL            DISPDAY
.
                FILEPI          1;GRAPH
                UPDATE          GRAPH;DIM11,COUNT,TABLE
                GOTO            ECADD31
*
.Generate a New Graph Record
.
ECADD30
                CALL            PACK01                                   
                MOVE            ONE,COUNT
                CALL            ADDTABLE
                CALL            DISPDAY
.
                FILEPI          1;GRAPH
                WRITE           GRAPH,DIM11;DIM11,COUNT,TABLE
*
.Write the Appointment record to Disk
.
ECADD31         MOVE            ZERO,COUNTER
.
ECADD32         ADD             ONE,COUNTER
                PACK            KEY17 WITH USRNO,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER
.
                FILEPI          1;AGENDA
                READ            AGENDA,KEY17;REPLY
                GOTO            ECADD32 IF NOT OVER
.
                CALL            AG1010
*
.Save the First Appointment's Key
.
                COMPARE         JULDAY,JDAYWORK
                GOTO            ECADD33 IF NOT EQUAL
.
                ADD             ONE,DTLCOUNT
                STORE           KEY17 BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
*
.See if Done
.
ECADD33         SUB             ONE,LINE
                GOTO            ECADD38 IF EQUAL     // Yes....
*
.Compute the Next Date Needed
.
ECADD34         COMPARE         THREE,FREQ           Handle Monthly Specially
                GOTO            ECADD35 IF EQUAL
.
                CALL            LOAD06
*                                                                            
.Reoccur on Day of week is selected.                                       
.                                                                            
                COMPARE         ROFLAG,ZERO                                              
                IF              EQUAL                                                      
.Compute NWORK1 for advancing by calendar position and not date.             
                CALL            CALCWEEKS                                               
                ENDIF           016
                GOTO            ECADD36
.
ECADD35         CALL            JULGREG              // Determine Gregorian Month
                CALL            YEARCOMP             // Determine the Number of Days in Feb
.
                CALL            LOAD02
.
ECADD36         ADD             NWORK1,JDAYWORK      // Add in the Frequency
                COMPARE         JDAYWORK,YEARLEN     // Did We Eclipse the Year ?        
                GOTO            ECADD28 IF NOT LESS  // No                           
                ADD             ONE,YEARWORK         // Wrap to the First of the Next Year
                SUB             YEARLEN,JDAYWORK
                GOTO            ECADD28
*
.Abort the Reoccurring Appointments
.
ECADD37         MOVE            YEAR,YEARWORK
                CALL            YEARCOMP
.
                PACK            DIM11 WITH USRNO,YEAR,JULDAY
.
                FILEPI          1;GRAPH
                READTAB         GRAPH,DIM11;*12,COUNT,TABLE
                GOTO            ECADD IF NOT OVER
.
                CALL            PACK01                                           
                MOVE            ZERO,COUNT
                GOTO            ECADD
*
.Reoccurring Appointments Complete
.
ECADD38         MOVE            YEAR,YEARWORK
                CALL            YEARCOMP
                MOVE            ONE,ROFLAG                  // Reset Reoccuring Day flags  016
                MOVE            ZERO,LOOPFLG                // and loop flags.             016
.
                PACK            DIM11 WITH USRNO,YEAR,JULDAY
                FILEPI          1;GRAPH
                READTAB         GRAPH,DIM11;*12,COUNT,TABLE
                GOTO            ECADD43 IF NOT OVER
*
.No Appointments for the Currently Selected Date
.
                CALL            PACK01                                            
                MOVE            ZERO,COUNT
*
.Return
.
ECADD43         CALL            DRAWCAL
                MOVE            TWO,CMDTRAP                                           
                TRAP            ECADD15 IF ESCAPE                                   
                TRAP            ECADD15 IF F27                                        
                GOTO            ECADD14
*                                                                           
.Help for New day option                                                  
.                                                                        
ROHELP
                MOVE            TWO,HMENU                                             
                MOVE            TEN,HFUNCNO                                         
                CALL            HELP                                                
                TRAPCLR         F5                                                   
                TRAPCLR         F9                                                
                GOTO            CALENDR1                                          
+............................................................................
.
.Addition of a Note
.
ECADD39         KEYIN           *HD,*EL,*DV,LITENT,*DV,NOTEINFO,*P3:VPOS,*DV,NOTEPR:
                                *H 24,*RPTCHAR "_":55,*H 24,*IT,DATA;
                DISPLAY         *IN,*H 24,DATA;
                GOTO            ECADD3 IF F5
.
                CMATCH          SPACE,DATA
                GOTO            ECADD39 IF EOS
*
.See if the Note is Confidential
.
ECADD40
                DISPLAY         *HD,*EL,NOTECON;
                CALL            KREPLYY
                GOTO            ECADD39 IF F5
.
                CMATCH          YES,REPLY                                            
                GOTO            ECADD41 IF EQUAL
                CMATCH          NO,REPLY                                             
                GOTO            ECADD40 IF NOT EQUAL
.
ECADD41         MOVE            REPLY,SECFLAG
                REP             SECREP,SECFLAG                                        
                DISPLAY         *P23:VPOS,SECFLAG;
*
.Place the Note after the Last Appointment Record For the Day
.
                MOVE            ZERO,HOUR
                MOVE            ZERO,MIN
                COMPARE         ZERO,DTLCOUNT
                GOTO            ECADD42 IF EQUAL
.
                LOAD            KEY17 BY DTLCOUNT FROM KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
.
                RESET           KEY17,12
                MOVE            KEY17,DIM2
                MOVE            DIM2,HOUR
                RESET           KEY17,14
                MOVE            KEY17,DIM2
                MOVE            DIM2,MIN
                RESET           KEY17
*
.Initialize the Other Fields
.
ECADD42         MOVE            NOTEMSG,STIME
                MOVE            BLANKS,ETIME
                MOVE            ZERO,ENDHOUR
                MOVE            ZERO,ENDMIN
                MOVE            ZERO,TPOS
                MOVE            ZERO,NBLOCKS
                GOTO            ECADD9
+............................................................................
.
.               A P P O I N T M E N T   S E L E C T I O N
.............................................................................
.
.
.Set the Initial Values
.
ECLOC           BRANCH          INQSW TO EC$CMD6         // Not Allowed During Inquiry
.
                MOVE            ONE,KEYPTR
                MOVE            SIXTEEN,VPOS
                COMPARE         ONE,DTLCOUNT
                GOTO            ECLOC11 IF EQUAL         // Only One Appointment
                COMPARE         ONE,DTLCOUNT
                GOTO            EC$CMD1 IF LESS          // No Appointments
*
.Position the Cursor
.
ECLOC1          MOVE            THREE,CMDTRAP                                
                TRAP            ECLOC13 IF ESCAPE                                  
                TRAP            ECLOC13 IF F27                                    
                DISPLAY         *HD,*EL,UPDWNCMD;
*
.Get a Command
.
ECLOC2          MOVE            KEYPTR,VPOS
                ADD             FIFTEEN,VPOS
                MOVE            SPACE,REPLY                                             
                KEYIN           *P2:VPOS,RA,*H 2,*+,*RV,REPLY;
                IF              UP                                                    
                CMOVE           UP,REPLY                                         
                ENDIF           032
                IF              DOWN                                                        
                CMOVE           DOWN,REPLY                                     
                ENDIF           032
                DISPLAY         *H 2,SPACE;
                GOTO            ECLOC11 IF EOS
*
.Check for a Direction Command
.
                CMATCH          062,REPLY
                GOTO            ECLOC6 IF EQUAL
                CMATCH          SPACE,REPLY
                GOTO            ECLOC6 IF EQUAL
                CMATCH          NO,REPLY                                             
                GOTO            ECLOC6 IF EQUAL
                CMATCH          070,REPLY
                GOTO            ECLOC2 IF NOT EQUAL
*
.Position to the Next Higher Record
.
ECLOC21         SUB             ONE,KEYPTR                                        
                GOTO            ECLOC2 IF NOT ZERO
*
.We are at the Top; Is There Some Previous Records ?
.
                BRANCH          NOPREV TO ECLOC3
*
.Try to Read Another Previous Detail Record
.
                FILEPI          2;AGENDA
                READ            AGENDA,KEYA;;
ECLOC14         READKP          AGENDA;USRNO1,YEARWORK,JDAYWORK,HOURWORK,MINWORK,COUNTER:
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                GOTO            ECLOC3 IF OVER
.
                COMPARE         ZERO,INQSW                  // If Inquiring, don't show
                GOTO            ECLOC15 IF EQUAL            // confidential records.
                CMATCH          "*",SECFLAG
                GOTO            ECLOC15 IF NOT EQUAL

                FILEPI          2;AGENDA
                GOTO            ECLOC14
.
ECLOC15
                PACK            KEY17 WITH USRNO1,YEARWORK,JDAYWORK,HOURWORK,MINWORK,COUNTER
                PACK            KEYWORK WITH USRNO,YEAR,JULDAY
                MATCH           KEY17,KEYWORK
                GOTO            ECLOC4 IF EQUAL
*
.There are No More Previous Records
.
ECLOC3          ADD             ONE,KEYPTR
                MOVE            ONE,NOPREV
                GOTO            ECLOC10
*
.Display the New Record
.
ECLOC4
                DISPLAY         *SETSWTB 16:21,*SETSWLR 2:79,*R,*HD,*H 2,STIME:
                                *H 12,ETIME,*H 22,*+,SECFLAG,DATA,*SETSWALL=1:24:1:80;            

                MOVE            SIX,DTLCOUNT
                MOVE            FIVE,NWORK1
.
ECLOC5
                CALL            LOAD04
.
                STORE           KEYWORK BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
.
                SUB             ONE,DTLCOUNT
                SUB             ONE,NWORK1
                GOTO            ECLOC5 IF NOT EQUAL
.
                MOVE            KEY17,KEYA
                MOVE            ZERO,NOMORE
                MOVE            SIX,DTLCOUNT
                MOVE            ONE,KEYPTR
                GOTO            ECLOC2
*
.Position to the Next Lower Record
.
ECLOC6          ADD             ONE,KEYPTR
                COMPARE         KEYPTR,DTLCOUNT
                GOTO            ECLOC2 IF NOT LESS        // Not at the End of the List
*
.End of the List; Is the Screen Full ?
.
                COMPARE         SIX,DTLCOUNT
                GOTO            ECLOC7 IF NOT EQUAL       // No; That's All the Records
*
.Try to Read Another Appointment Record
.
                BRANCH          NOMORE TO ECLOC7
.
                FILEPI          2;AGENDA
                READ            AGENDA,KEYF;;
ECLOC16         READKS          AGENDA;USRNO1,YEARWORK,JDAYWORK,HOURWORK,MINWORK,COUNTER:
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                GOTO            ECLOC7 IF OVER
.
                COMPARE         ZERO,INQSW                  // If Inquiring, don't show
                GOTO            ECLOC17 IF EQUAL            // confidential records.
                CMATCH          "*",SECFLAG
                GOTO            ECLOC17 IF NOT EQUAL
                FILEPI          2;AGENDA
                GOTO            ECLOC16
.
ECLOC17
                PACK            KEY17 WITH USRNO1,YEARWORK,JDAYWORK,HOURWORK,MINWORK,COUNTER
                PACK            KEYWORK WITH USRNO,YEAR,JULDAY
.
                MATCH           KEY17,KEYWORK
                GOTO            ECLOC8 IF EQUAL
*
.There are No More Records
.
ECLOC7          SUB             ONE,KEYPTR
                MOVE            ONE,NOMORE
                GOTO            ECLOC10
*
.Display the New Record
.
ECLOC8
                DISPLAY         *SETSWTB 16:21,*SETSWLR 2:79,*R,*HD,*H 2,STIME:
                                *H 12,ETIME,*H 22,*+,SECFLAG,DATA,*SETSWALL=1:24:1:80;             
*
.Rearrange the Key List
.
                MOVE            ONE,DTLCOUNT
                MOVE            TWO,NWORK1
.
ECLOC9
                CALL            LOAD04
                STORE           KEYWORK BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
.
                ADD             ONE,DTLCOUNT
                ADD             ONE,NWORK1
                COMPARE         SIX,DTLCOUNT
                GOTO            ECLOC9 IF NOT EQUAL
.
                MOVE            KEY17,KEYF
                MOVE            ZERO,NOPREV      // Indicate Previous Records Exist
                SUB             ONE,KEYPTR
                GOTO            ECLOC2
*
.Beginning or End of List Encountered
.
ECLOC10         BEEP
                GOTO            ECLOC2
*
.Read the Selected Record
.
ECLOC11
                CALL            LOAD05
.
                FILEPI          1;AGENDA
                READ            AGENDA,KEY17;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN:
                                COUNTER,ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                CALL            INTERR IF OVER
*
.Branch to the Correct Function
.
                BRANCH          FUNC TO ECLOC12,ECLOC12,ECCHG,ECDEL,ECINS
.
ECLOC12         CALL            INTERR
*
.Abort Appointment Selection
.
ECLOC13         NORETURN
                DISPLAY         *HOFF,*H 2,SPACE;
                GOTO            EC$CMD
+..............................................................................
.
.                   A P P O I N T M E N T   C H A N G E
...............................................................................
.
.
.Save the Appointment Information
.
ECCHG           MOVE            FOUR,CMDTRAP                                         
                TRAP            ECCHG12 IF ESCAPE                                     
                TRAP            ECCHG12 IF F27                                       
                COMPARE         ZERO,NBLOCKS
                GOTO            ECCHG6 IF EQUAL
*
.Remove It From the Table
.
                MOVE            KEY17,KEY18
                CALL            DELTABLE
.
                MOVE            VPOS,NWORK3
                CALL            DISPDAY
                MOVE            NWORK3,VPOS
*
.Re-read the Information
.
                CALL            LOAD05
.
                FILEPI          1;AGENDA
                READ            AGENDA,KEY17;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN:
                                COUNTER,ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
*
.Get the New Starting Time
.
ECCHG1          DISPLAY         *HD,*EL,LITAPPT,LITST;
.
                MOVE            THREE,HPOS
                MOVE            ZERO,REQFLAG
                MOVE            ONE,MASKSW
                CALL            GETIME
.
                BRANCH          FLAG1 TO ECCHG12
                BRANCH          EOSFLAG TO ECCHG2
.
                MOVE            HOURWORK,HOUR
                MOVE            MINWORK,MIN
                MOVE            TIME,STIME
*
.See if It Conflicts
.
ECCHG2          MOVE            ZERO,SWITCH
                CALL            POSITABL
                CMATCH          CN,TABLE
                GOTO            ECCHG3 IF EQUAL           No Conflict
*
.We Have a Schedule Conflict
.
                MOVE            ONE,SWITCH
                CALL            GETCCR               // Prompt Schedule Conflict       
                CMATCH          YES,REPLY                                               
                GOTO            ECCHG1 IF NOT EQUAL
*
.Get the Ending Time
.
ECCHG3          COMPARE         ZERO,NBLOCKS
                GOTO            ECLOC1 IF EQUAL
                DISPLAY         *HD,*EL,LITAPPT,LITET;
.
                MOVE            THIRTEEN,HPOS
                CALL            GETIME
.
                BRANCH          FLAG1 TO ECCHG5
                BRANCH          EOSFLAG TO ECCHG4
.
                MOVE            HOURWORK,ENDHOUR
                MOVE            MINWORK,ENDMIN
                MOVE            TIME,ETIME
*
.Make Sure the Ending Time is After the Starting Time
.
ECCHG4          CALL            CHECKEND
                BRANCH          FLAG1 TO ECCHG5
*
.Check for a Conflict
.
                MOVE            JULDAY,JDAYWORK
                CALL            COMPUTE
                BRANCH          SWITCH TO ECCHG6       // We Know It Does
                CALL            CHECK
                GOTO            ECCHG6 IF EQUAL
*
.We Have a Schedule Conflict
.
                CALL            GETCCR               // Prompt Schedule Conflict        
                CMATCH          YES,REPLY                                             
                GOTO            ECCHG6 IF EQUAL
*
.Backup to the Starting Time
.
ECCHG5          DISPLAY         *P13:VPOS,ETIME;
                GOTO            ECCHG1
*
.Get the Information
.
ECCHG6          KEYIN           *HD,*EL,*DV,LITENT,*DV,INFOPR:
                                *P24:VPOS,*RV,*IT,DATA;
                DISPLAY         *IN,*H 24,DATA;
                GOTO            ECCHG3 IF F5
                GOTO            ECCHG7 IF EOS
                MOVE            ONE,FLAG2
*
.See if Tentative or Firm Appointment
.
ECCHG7          COMPARE         ZERO,NBLOCKS
                GOTO            ECCHG8 IF EQUAL
.
                MOVE            F,TFLAG                                              
                KEYIN           *HD,*EL,*DV,LITIST,*HA -1,*RV,TFLAG;                   
                GOTO            ECCHG6 IF F5
                GOTO            ECCHG8 IF EOS
.
                MOVE            ONE,FLAG2
                CMATCH          TENTAT,TFLAG
                GOTO            ECCHG8 IF EQUAL
                CMATCH          FIRM,TFLAG
                GOTO            ECCHG7 IF NOT EQUAL
*
.See If It Is Confidential
.
ECCHG8          MOVE            SECFLAG,REPLY
                REP             SPSTREP,REPLY
                KEYIN           *HD,*EL,*DV,CONPRQ:
                                *DV,REPLY,*HA -1,*RV,REPLY;
                GOTO            ECCHG7 IF F5
                GOTO            ECCHG10 IF EOS
.
                CMATCH          YES,REPLY                                            
                GOTO            ECCHG9 IF EQUAL
                CMATCH          NO,REPLY                                              
                GOTO            ECCHG8 IF NOT EQUAL
.
ECCHG9          MOVE            ONE,FLAG2
.         REP       "Y N*",REPLY
                REP             SECREP,REPLY                                           
                MOVE            REPLY,SECFLAG
                DISPLAY         *P23:VPOS,SECFLAG;
*
.Delete the Record
.
ECCHG10         TRAPCLR         ESCAPE                                                
                TRAPCLR         F27                                                    
.
                CALL            AG1090
                MOVE            ZERO,COUNTER
*
.Rewrite the Record
.
ECCHG11         ADD             ONE,COUNTER
                PACK            KEY17 WITH USRNO,YEAR,JULDAY,HOUR,MIN,COUNTER
.
                FILEPI          1;AGENDA
                READ            AGENDA,KEY17;REPLY
                GOTO            ECCHG11 IF NOT OVER
.
                CALL            AG1010
*
.Update the Key List
.
                CALL            LOAD05
*
.Graph the New Appointment
.
                COMPARE         ZERO,NBLOCKS
                GOTO            ECCHG11A IF EQUAL       // Note...
.
                MOVE            JULDAY,JDAYWORK
                CALL            COMPUTE
.
                CALL            ADDTABLE
                CALL            DISPDAY
*
.Update the Graph File
.
                FILEPI          1;GRAPH
                UPDATAB         GRAPH;*14,TABLE
*
.Change Complete
.
ECCHG11A        DISPLAY         *HD,*EL,CHPR,*W;
                GOTO            ECCHG13
*
.Abort the Change Command
.
ECCHG12
                CALL            LOAD05
.
                FILEPI          1;AGENDA
                READ            AGENDA,KEY17;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN:
                                COUNTER,ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                CALL            INTERR IF OVER
*
.Restore the Table
.
                CALL            POSITABL
                CALL            ADDTABLE
                MOVE            VPOS,NWORK3
                CALL            DISPDAY
                MOVE            NWORK3,VPOS
*
.Redisplay the Information
.
                DISPLAY         *P3:VPOS,STIME,*H 13,ETIME,*H 23,SECFLAG,DATA;
*
.Exit the Function
.
ECCHG13         BRANCH          DTLCOUNT TO EC$CMD
                GOTO            EC$CMD
+..............................................................................
.
.                   A P P O I N T M E N T   I N S E R T I O N
...............................................................................
.
.
.Open Up a Line on the Screen
.
ECINS           MOVE            FIVE,CMDTRAP                                           
                TRAP            ECINS10 IF ESCAPE                                      
                TRAP            ECINS10 IF F27                                          
                COMPARE         SIX,KEYPTR        // After Last Record On the Screen ?
                GOTO            ECINS1 IF EQUAL   // Yes...
.
                MOVE            VPOS,NWORK1
                SUB             FOURTEEN,NWORK1
                ADD             ONE,VPOS
.
                CALL            SETTOP16
                CALL            SETSW03
                DISPLAY         *P1:NWORK1,*OPNLIN,*SETSWALL=1:24:1:80;
                GOTO            ECINS2
*
.Detail Area is Full - Roll Up One from Bottom
.
ECINS1
                CALL            SETTOP16
                CALL            SETSW03
                DISPLAY         *HD,*R,*SETSWALL=1:24:1:80;
*
.Get the Information
.
ECINS2          KEYIN           *HD,*EL,*DV,LITENT,*DV,INFOPR:
                                *P3:VPOS,*DV,NOTEPR,*H 24,*RPTCHAR "_":55,*H 24,*IT,DATA;
                DISPLAY         *IN,*H 24,DATA;
                GOTO            ECINS10 IF F5
*
.See if the Information is Confidential
.
ECINS3
                DISPLAY         *HD,*EL,CONPRQ;
                CALL            KREPLYY
                GOTO            ECINS2 IF F5
.
                CMATCH          YES,REPLY                                             
                GOTO            ECINS4 IF EQUAL
                CMATCH          NO,REPLY                                              
                GOTO            ECINS3 IF NOT EQUAL
.
ECINS4          MOVE            REPLY,SECFLAG
                REP             SECREP,SECFLAG                                        
                DISPLAY         *P23:VPOS,SECFLAG;
*
.Rearrange the Keys as Needed
.
                TRAPCLR         ESCAPE                                                 
                TRAPCLR         F27                                                   
                COMPARE         SIX,KEYPTR
                GOTO            ECINS6 IF EQUAL       // Move Each Up One Slot
*
.Move the Keys Beneath the Specified Record Down One
.
                MOVE            FIVE,NWORK1
                MOVE            SIX,NWORK2
.
ECINS5
                LOAD            KEY BY NWORK1 FROM KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
                STORE           KEY BY NWORK2 INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
.
                SUB             ONE,NWORK2
                SUB             ONE,NWORK1
                COMPARE         NWORK1,KEYPTR
                GOTO            ECINS5 IF NOT EQUAL
.
                COMPARE         SIX,DTLCOUNT
                GOTO            ECINS8 IF NOT EQUAL
                SUB             ONE,DTLCOUNT
                GOTO            ECINS8
*
.Move All the Keys Up One Slot
.
ECINS6          MOVE            TWO,NWORK1
                MOVE            ONE,NWORK2
.
ECINS7
                LOAD            KEY BY NWORK1 FROM KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
                STORE           KEY BY NWORK2 INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
.
                ADD             ONE,NWORK1
                ADD             ONE,NWORK2
                COMPARE         SIX,NWORK2
                GOTO            ECINS7 IF NOT EQUAL
*
.Correct the Values
.
                SUB             ONE,KEYPTR
                SUB             ONE,DTLCOUNT
*
.Place the Note after the Specified Appointment Record
.
ECINS8
                LOAD            KEY BY KEYPTR FROM KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
.
                RESET           KEY,16
                MOVE            KEY,COUNTER
                RESET           KEY,14
                SETLPTR         KEY,15
                MOVE            KEY,MIN
                RESET           KEY,12
                SETLPTR         KEY,13
                MOVE            KEY,HOUR
                SETLPTR         KEY,17
                RESET           KEY
*
.Initialize the Other Fields
.
                MOVE            NOTEMSG,STIME
                MOVE            BLANKS,ETIME
                MOVE            ZERO,ENDHOUR
                MOVE            ZERO,ENDMIN
                MOVE            ZERO,TPOS
                MOVE            ZERO,NBLOCKS
*
.Write the Information to Disk
.
ECINS9          ADD             ONE,COUNTER
                PACK            KEY17 WITH USRNO,YEAR,JULDAY,HOUR,MIN,COUNTER
.
                FILEPI          1;AGENDA
                READ            AGENDA,KEY17;REPLY
                GOTO            ECINS9 IF NOT OVER
                CALL            AG1010
*
.Save the Key
.
                ADD             ONE,DTLCOUNT
                ADD             ONE,KEYPTR
                CALL            LOAD05
*
.Insertion Complete
.
                DISPLAY         *HD,*EL,INSPR,*W;
                COMPARE         SIX,DTLCOUNT                              
                GOTO            ECLOC1 IF NOT EQUAL                       
*
.Abort the Insertion or Just quit entering (Just like write)
.
ECINS10         CALL            SHOWDTL1
                GOTO            EC$CMD
.
+.............................................................................
.
.                   A P P O I N T M E N T    R E M O V A L
...............................................................................
.
.
ECDEL           MOVE            SIX,CMDTRAP                                           
                TRAP            ECDEL30 IF ESCAPE                                    
                TRAP            ECDEL30 IF F27                                        
.
                COMPARE         ZERO,NBLOCKS
                GOTO            ECDEL1 IF NOT EQUAL
                CLEAR           ETIME
.
ECDEL1          DISPLAY         *P3:VPOS,*+,*HON,STIME,*H 13,ETIME,*HOFF;
*
.Make Sure It's to Be Deleted
.
ECDEL2
                DISPLAY         *HD,*EL,REMPR;
                CALL            KREPLYN
                CMATCH          YES,REPLY                                             
                GOTO            ECDEL29 IF NOT EQUAL
*
.If an Appointment, See if it Recurrs
.
ECDEL3          MOVE            ZERO,FLAG2
                DISPLAY         *HD,*EL,REPR;
                CALL            KREPLYN
                GOTO            ECDEL2 IF F5
.
                CMATCH          YES,REPLY                                            

                GOTO            ECDEL7 IF NOT EQUAL
                MOVE            ONE,FLAG2
*
.Get the Frequency
.
ECDEL4          MOVE            CD,REPLY
                KEYIN           *HD,*EL,*DV,REDWMPR,*HA -1,*RV,REPLY;
                GOTO            ECDEL3 IF F5
.
                REP             DWMREP,REPLY
                MOVE            REPLY,FREQ
                COMPARE         ZERO,FREQ
                GOTO            ECDEL4 IF EQUAL
                COMPARE         FOUR,FREQ
                GOTO            ECDEL4 IF NOT LESS
*
.Get the Number of Times It Recurrs
.
ECDEL5          KEYIN           *HD,*EL,*DV,NUMOCC,INDEX;
                GOTO            ECDEL4 IF F5
.
                COMPARE         ONE,INDEX
                GOTO            ECDEL5 IF LESS
                MOVE            DATA,NOTE
*                                                                           
.Option for deletion of Reoccuring Days of week.                             
.                                                                           
                TRAP            ROHELP IF F5
                TRAP            ROHELP IF F9                                            
                COMPARE         THREE,FREQ                                              
                IF              EQUAL                                                    
                KEYIN           *HD,*EL,*DV,REDTPR,REPLY;                               
                MATCH           REPLY,CD                                               
*                                                                          
.If Option is chosen, set appropriate flags.                                
.                                                                            
                IF              EQUAL                                                    
                REP             REPDT,REPLY                                             
                MOVE            REPLY,ROFLAG                                            
                MOVE            TWO,FREQ                                               
                ENDIF           016
                ENDIF           016
*
.Is the Selected Date on a Weekend ?
.
                MOVE            JULDAY,JDAYWORK
                MOVE            YEAR,YEARWORK
                CALL            FINDOW
.
                MOVE            ONE,SWITCH
                BRANCH          NWORK2 TO ECDEL7,ECDEL6,ECDEL6,ECDEL6:
                                ECDEL6,ECDEL6,ECDEL7
                CALL            INTERR
*
.Don't Ask Exclude if Monthly or Weekly
.
ECDEL6          MOVE            ONE,SWITCH
                COMPARE         ONE,FREQ
                GOTO            ECDEL7 IF NOT EQUAL        // Daily Only...
*
.See if We Will Reach a Weekend
.
                MOVE            JULDAY,JDAYWORK
                MOVE            YEAR,YEARWORK
                CALL            FINDOW
                ADD             INDEX,NWORK2
                COMPARE         EIGHT,NWORK2
                GOTO            ECDEL7 IF LESS             //  We Won't Involve a Weekend
*
.Exclude Weekends ?
.
                DISPLAY         *HD,*EL,EXWKEND;
                CALL            KREPLYN
                GOTO            ECDEL5 IF F5
.
                REP             REPYN,REPLY
                MOVE            REPLY,SWITCH
*
.Delete the Information
.
ECDEL7
                CALL            AG1090
                PACK            DIM11 WITH USRNO,YEAR,JULDAY
                FILEPI          1;GRAPH
                READ            GRAPH,DIM11;DIM11,COUNT,TABLE
*
.Update the Table
.
                COMPARE         ZERO,NBLOCKS
                GOTO            ECDEL11 IF EQUAL
.
                BRANCH          COUNT TO ECDEL9
.
                MOVE            JULDAY,JDAYWORK
                MOVE            YEAR,YEARWORK
                CLEAR           KEY18
                CALL            DELTABLE
*
.Update the Graph File
.
                SUB             ONE,COUNT
                FILEPI          1;GRAPH
                UPDATE          GRAPH;USRNO,YEAR,JULDAY,COUNT,TABLE
                GOTO            ECDEL10
*
.Delete the Graph Record
.
ECDEL9          MOVE            ZERO,COUNT
                CALL            PACK01                                             
.
                PACK            DIM11 WITH USRNO,YEAR,JULDAY
                FILEPI          1;GRAPH
                DELETE          GRAPH,DIM11
                CALL            INTERR IF OVER
.
                RESET           MONTABLE,DAY
                CMOVE           CN,MONTABLE
                COMPARE         PLANFLAG,ONE            // If we entered from PLAN then    
                RETURN          IF EQUAL                // Return, else go on.             
*
.Redisplay the Day's Graph
.
ECDEL10         MOVE            VPOS,NWORK3
                MOVE            JULDAY,JDAYWORK
                CALL            DISPDAY
                MOVE            NWORK3,VPOS
*
.Correct the Detail Section
.
ECDEL11
                SUB             FIFTEEN,VPOS
                CALL            SETTOP16
                CALL            SETSW03
                DISPLAY         *P1:VPOS,*DELLIN,*SETSWALL=1:24:1:80:
                                *HD,*EL,INFOREM,*W;
                COMPARE         SIX,COUNT                                              
                IF              EQUAL                                                         
                DISPLAY         *P=23:22,*RPTCHAR=HB:10;                               
                DISPLAY         *P=23:15,*RPTCHAR=HB:10;                               
                ENDIF           051
*
.Correct the Detail Count
.
                SUB             ONE,DTLCOUNT
                GOTO            ECDEL18 IF EQUAL            // No More Detail Records
*
.Now, Correct the Key List
.
                MOVE            KEYPTR,NWORK1
                MOVE            KEYPTR,NWORK2
.
ECDEL12         ADD             ONE,NWORK1
                CALL            LOAD04
                STORE           KEYWORK BY NWORK2 INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
                COMPARE         NWORK2,DTLCOUNT
                GOTO            ECDEL13 IF LESS
                ADD             ONE,NWORK2
                GOTO            ECDEL12
*
.Try to Pull Another Record onto the Screen
.
ECDEL13         COMPARE         SIX,COUNT                                               
                GOTO            ECDEL14 IF LESS    // The Screen Isn't Full               
                BRANCH          NOMORE TO ECDEL14       // No More Below the Screen
.
                FILEPI          2;AGENDA
                READ            AGENDA,KEYF;;
                READKS          AGENDA;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER:
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                GOTO            ECDEL14 IF OVER
.
                PACK            KEY17 WITH USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER
                PACK            KEYWORK WITH USRNO,YEAR,JULDAY
                MATCH           KEY17,KEYWORK
                GOTO            ECDEL14 IF NOT EQUAL
*
.We Have Another Record
.
                DISPLAY         *P3:21,STIME,*H 13,ETIME,*H 23,*+,SECFLAG,DATA;      
*
.Save the Key, Correct the Values
.
                MOVE            KEY17,KEYF
                MOVE            SIX,DTLCOUNT
                GOTO            ECDEL18
*
.There are No More Trailing Records
.
ECDEL14         MOVE            ONE,NOMORE
*
.See if Any Previous Record
.
                BRANCH          NOPREV TO ECDEL17      // We Already Know There Isn't Any More
.
                FILEPI          2;AGENDA
                READ            AGENDA,KEYA;;
                READKP          AGENDA;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER:
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                GOTO            ECDEL16 IF OVER
.
                PACK            KEY17 WITH USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER
                PACK            KEYWORK WITH USRNO,YEAR,JULDAY
                MATCH           KEY17,KEYWORK
                GOTO            ECDEL16 IF NOT EQUAL
*
.Display the Record
.
                CALL            SETTOP16
                CALL            SETSW03
                DISPLAY         *HU,*RD:
                                *H 2,STIME,*H 12,*+,ETIME:
                                *H 22,SECFLAG,DATA,*SETSWALL=1:24:1:80;
*
.Rearrange the Keys
.
                MOVE            FIVE,NWORK1
                MOVE            SIX,NWORK2
ECDEL15
                CALL            LOAD04
                STORE           KEYWORK BY NWORK2 INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF
                SUB             ONE,NWORK2
                SUB             ONE,NWORK1
                GOTO            ECDEL15 IF NOT ZERO
.
                MOVE            KEY17,KEYA
                ADD             ONE,DTLCOUNT
                GOTO            ECDEL18
*
.Indicate No Previous Records
.
ECDEL16         MOVE            ONE,NOPREV
*
.Did We Delete the Last Record ?
.
ECDEL17         COMPARE         KEYPTR,DTLCOUNT
                GOTO            ECDEL18 IF NOT LESS       // No.....
.
                SUB             ONE,KEYPTR
*
.If Deleting Reoccurring Information, Skip Down
.
ECDEL18         BRANCH          FLAG2 TO ECDEL19
                COMPARE         ZERO,DTLCOUNT
                GOTO            EC$CMD IF EQUAL
                GOTO            ECLOC1
+.........................................................................
.
.Reoccurring Appointment Deletion
.
.Compute the Next Date Needed
.
ECDEL19         SUB             ONE,INDEX
                GOTO            ECDEL38 IF ZERO
.
ECDEL20         COMPARE         THREE,FREQ           Handle Monthly Specially
                GOTO            ECDEL21 IF EQUAL
.
                CALL            LOAD06
*                                                                           
.Delete the reoccuring by the days of the week events.                       
.                                                                           
                COMPARE         ROFLAG,ZERO                                               
                IF              EQUAL                                                       
.Compute NWORK1 for deleting by calendar position and not date.              
                CALL            CALCWEEKS                                                
                ENDIF           016
                GOTO            ECDEL22

ECDEL21         CALL            JULGREG              // Determine Gregorian Month
                CALL            YEARCOMP             // Determine the Number of Days in Feb
.
                CALL            LOAD02
.
ECDEL22         ADD             NWORK1,JDAYWORK      // Add in the Frequency
                COMPARE         JDAYWORK,YEARLEN     // Did We Eclipse the Year ?          
                GOTO            ECDEL23 IF NOT LESS      // No                           
                ADD             ONE,YEARWORK         // Wrap to the First of the Next Year
                SUB             YEARLEN,JDAYWORK
*
.Exclude Weekends, If Requested
.
ECDEL23         BRANCH          SWITCH TO ECDEL24
.
                CALL            FINDOW
                BRANCH          NWORK2 TO ECDEL20,ECDEL24,ECDEL24,ECDEL24:
                                ECDEL24,ECDEL24,ECDEL20
                CALL            INTERR
*
.Delete the Information Records
.
ECDEL24         CALL            JULGREG
                DISPLAY         *P69:24,DATE;
*
.Locate the Information Record
.
                PACK            KEY WITH USRNO,YEARWORK,JDAYWORK,HOUR,MIN
                FILEPI          1;AGENDA
                READ            AGENDA,KEY;;
*
.Read Through Looking for the Record
.
ECDEL25         FILEPI          1;AGENDA
                READKS          AGENDA;KEY17,ENDHOUR,ENDMIN,STIME,ETIME:
                                TPOS,NBLOCKS,SECFLAG,TFLAG,DATA
                GOTO            ECDEL26 IF OVER
*
.Right User/Year/Day/Hour/Minute ?
.
                MATCH           KEY,KEY17
                GOTO            ECDEL26 IF NOT EQUAL
*
.Right Information ?
.
                MATCH           DATA,NOTE
                GOTO            ECDEL27 IF EQUAL
                GOTO            ECDEL25
*
.We Didn't Find the Information
.
ECDEL26         KEYIN           *CLICK,*HD,*EL,*DV,RECNOT,*DV,DATE,". ",REPLY;
                GOTO            ECDEL19
*
.Delete the Record
.
ECDEL27
                CALL            AG1090
*
.Update the Graph File
.
                COMPARE         ZERO,NBLOCKS
                GOTO            ECDEL19 IF EQUAL
.
                MOVE            KEY17,DIM11
                FILEPI          1;GRAPH
                READTAB         GRAPH,DIM11;*12,COUNT,TABLE
                CALL            INTERR IF OVER
*
.If Last Appointment Record for the Day, Delete the Graph Record
.
                CLEAR           KEY18
                CALL            DELTABLE
                CALL            DISPDAY
.
                BRANCH          COUNT TO ECDEL28
.
                SUB             ONE,COUNT
                FILEPI          1;GRAPH
                UPDATAB         GRAPH;*12,COUNT,TABLE
                GOTO            ECDEL19
*
.Delete the Graph Record
.
ECDEL28         FILEPI          1;GRAPH
                DELETE          GRAPH,DIM11
                CALL            INTERR IF OVER
                GOTO            ECDEL19
*
.Reoccurring Appointment Deletion Complete
.
ECDEL38         MOVE            YEAR,YEARWORK
                CALL            YEARCOMP
                CALL            DRAWCAL
                MOVE            ONE,ROFLAG                       // Reset Reoccuring flag  016
.
                COMPARE         ZERO,DTLCOUNT
                GOTO            EC$CMD IF EQUAL
.
                PACK            DIM11 WITH USRNO,YEAR,JULDAY
                FILEPI          1;GRAPH
                READTAB         GRAPH,DIM11;*12,COUNT,TABLE
                GOTO            EC$CMD IF NOT OVER
*
.No Appointments For The Currently Selected Date
.
                CALL            PACK01                                            
                MOVE            ZERO,COUNT
                GOTO            EC$CMD
*
.Abort the Remove Routine; Return to Selection
.
ECDEL29         DISPLAY         *P3:VPOS,*+,STIME,*H 13,ETIME;
                BRANCH          DTLCOUNT TO EC$CMD
                GOTO            ECLOC1
*
.Abort the Remove Routine; Return to Command Line
.
ECDEL30         NORETURN
                DISPLAY         *P3:VPOS,*+,STIME,*H 13,ETIME;
                GOTO            EC$CMD
+..............................................................................
.
.                  A P P O I N T M E N T   I N Q U I R Y
...............................................................................
.
.
ECINQ           MOVE            SEVEN,CMDTRAP                                          
                TRAP            ECINQ3 IF ESCAPE                                      
                TRAP            ECINQ3 IF F27                                          
                BRANCH          INQSW TO ECINQ2               // Already Inquiring
*
.Get the Name of the User to Inquire Upon
.
ECINQ1          MOVE            ONE,FLAG1                // Any User
                MOVE            TWO,HPOS
                MOVE            ONE,VPOS
.
                MOVE            ZERO,FLAG4               // Skip "Next"
                CALL            FINDUSER
                BRANCH          EOSFLAG TO ECINQ3
                BRANCH          FLAG1 TO ECINQ3
.
                MOVE            USRNAME1,USRNAME
                MOVE            USRNO1,USRNO
*
.Highlight the Name
.
                COUNT           NWORK1,USRNAME
                SETLPTR         USRNAME,NWORK1
                DISPLAY         *HD,*EL,*P2:1,*RPTCHAR " ":20,*H 2,*HON,*+,USRNAME,*HOFF;
                MOVE            ONE,INQSW
                GOTO            ECINQ4
*
.Restore the Original User ?
.
ECINQ2
                DISPLAY         *HD,*EL,FININQ;
                CALL            KREPLYY
                GOTO            EC$CMD IF F5
                CMATCH          NO,REPLY                                              
                GOTO            ECINQ1 IF EQUAL
*
.Restore the User
.
ECINQ3          MOVE            CURRUSER,USRNO
                MOVE            CURRNAME,USRNAME
                MOVE            ZERO,INQSW
                DISPLAY         *P2:1,*RPTCHAR " ":20,*H 2,USRNAME;
                MOVE            "01",IFUNC                                             
                GOTO            CALENDR1                                              
.
*
.Go Allow Selection of a Different Date
.
ECINQ4
                MOVE            SIX TO MTOP
                MOVE            TWELVE TO MBOT
                MOVE            TWENTY9 TO MLEFT
                CALL            SETSW02
                CALL            SETTOP16
                CALL            SETSW02
                DISPLAY         *SETSWTB 1:24,*P31:14,*EL,*SETSWALL=1:24:1:80;
.
                CALL            DRAWCAL
                MOVE            ONE,GRAPHSW
                CALL            GRAPH
                CALL            SHOWDTL1
*.............................................................................
.
.                     Inquire Command Handler                            
.
.     (From this 037 to the next 037 all the code inbetween has been
.      added for this change.)
..............................................................................

ECINQ6          NORETURN
                MOVE            ZERO,CMDTRAP                                        
                TRAP            ECINQ1 IF ESCAPE                                       
                TRAP            ECINQ1 IF F27                                           
                DISPLAY         *HD,*EL,SPACE,FUNC2,SPACE,FUNC4,SPACE,FUNC7,SPACE,FUNC8;
                CLEAR           FUNCDESC           // Clear the functions.            
                MOVE            ZERO,FLAG1         // Flag1 = 0                       
                CALL            CHKALRM            // Check for alarm,plan,message.     
                MOVE            ZERO,FLAG2
*
.Position to the Correct Function
.
ECINQ7          LOAD            FUNCDESC BY IFUNC FROM FUNC2,FUNC4,FUNC7,FUNC8
.
                MOVE            IFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           IPOS,NWORK2
                MOVE            IPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
                MOVE            SPACE,REPLY                                           
                DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              F16                                                              
                MOVE            SEVEN,REPLY                                             
                ENDIF           
                IF              F17                                                             
                MOVE            NINE,REPLY                                                
                ENDIF           
                IF              F18                                                              
                MOVE            FIVE,REPLY                                                
                ENDIF          
                IF              F19                                                            
                MOVE            ONE,REPLY                                               
                ENDIF          
                IF              F20                                                       
                MOVE            THREE,REPLY                                             
                ENDIF           
                IF              UP                                                           
                MOVE            EIGHT,REPLY                                           
                ENDIF           
                IF              DOWN                                                          
                MOVE            TWO,REPLY                                            
                ENDIF           
                IF              LEFT                                                        
                CMOVE           LEFT,REPLY                                          
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;                   
                GOTO            ECINQ9                                                 
                ENDIF           
                IF              RIGHT                                                           
                CMOVE           RIGHT,REPLY                                         
                DISPLAY         *H HPOS,*HA -1,*+,FUNCDESC;                          
                ENDIF           
                GOTO            EC$CMD8 IF F1
                GOTO            ECINQ6 IF F2                                         
                GOTO            ECINQ6 IF F4                                       
                GOTO            ECINQ12 IF F5
                GOTO            ECINQ12 IF F9                                        
                GOTO            ECINQ11 IF LESS
                GOTO            ECINQ10 IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
*
.Check for a Direction Command
.
                CMATCH          SPACE,REPLY
                GOTO            ECINQ8 IF EQUAL
                MOVE            ZERO,INDEX
                MOVE            REPLY,INDEX
                BRANCH          INDEX TO SELDAY20,ECSCRLDN,SELDAY20,ECINQ9:
                                ECINQ6,ECINQ8,SELDAY20,ECSCRLUP,SELDAY20
*
.Check for a Function Letter
.
                RESET           ILETS
                SCAN            REPLY,ILETS
                IF              NOT EQUAL                      // Lower case option           
                RESET           ILETS2                                          
                SCAN            REPLY,ILETS2                                     
                GOTO            ECINQ7 IF NOT EQUAL                             
                MOVEFPTR        ILETS2,IFUNC                                    
                GOTO            ECINQ7                                          
                ENDIF                      
                MOVEFPTR        ILETS,IFUNC
                GOTO            ECINQ7
*
.Move Right to the Next Function
.
ECINQ8          ADD             ONE,IFUNC
                COMPARE         FIVE,IFUNC
                GOTO            ECINQ7 IF NOT EQUAL
                MOVE            ONE,IFUNC
                GOTO            ECINQ7
*
.Move Left to the Next Function
.
ECINQ9          SUB             ONE,IFUNC
                GOTO            ECINQ7 IF NOT ZERO
                MOVE            FOUR,IFUNC
                GOTO            ECINQ7
*
.We Have a Selected Function
.
ECINQ10         BRANCH          IFUNC TO SELDAY,ECPRINT,ECSRCH,ECINQ
                MOVE            ZERO,PRTSW                                           
                CALL            INTERR
*
.A Timeout Occurred
.
ECINQ11         MOVE            ZERO,FLAG1
                CALL            CHKALRM
                CALL            CLOCKDT                                                
                DISPLAY         *P59:1,DATE,SPACE2,TIME;
                GOTO            ECINQ7
*
.Help Requested
.
ECINQ12         MOVE            TWELVE,HMENU
                MOVE            IFUNC,HFUNCNO
                CALL            HELP

                CALL            SHOWBOX1
                GOTO            CALENDR2
..............................................................................
.
.                  End of Inquire Command Handler                         
.
..............................................................................
.
+..............................................................................
.
.                    A P P O I N T M E N T   C L E A N   U P
...............................................................................
.
.
ECPACK          BRANCH          INQSW TO EC$CMD6     // Disallow While Inquiring
                MOVE            EIGHT,CMDTRAP                                           
                TRAP            ECSRCH14 IF ESCAPE                                     
                TRAP            ECSRCH14 IF F27                                       
.
                CMOVE           NO,REPLY                                
                CALL            SETSW01
                DISPLAY         *P=23:22,*RPTCHAR=HB:10;                               
                DISPLAY         *HD,*EL,DELPR;
                CALL            KREPLYN
                GOTO            ECSRCH14 IF F5
*
.Get the Starting Date
.
ECPACK1
                CALL            SETSW01
                DISPLAY         *HD,*EL,DELST;
.
                MOVE            THIRTY2,HPOS
                MOVE            TWENTY4,VPOS
                MOVE            ZERO,YEARWORK
                MOVE            ZERO,JDAYWORK
.
                MOVE            ZERO,MASKSW
                MOVE            ZERO,REQFLAG
                MOVE            REPLY,DIM1                                             
                MOVE            ONE,PRTSW                                               
                MOVE            ONE,TDDATE                                             
                CALL            GETDATE
                MOVE            ZERO,TDDATE                                            
                MOVE            ZERO,PRTSW                                              
                MOVE            DIM1,REPLY                                            
                BRANCH          FLAG1 TO ECPACK
                COMPARE         ZERO,EOSFLAG
                GOTO            ECPACKD IF EQUAL
                DISPLAY         *H 32,*EL,WFST;
*
.Position the File
.
ECPACKD         PACK            KEY17 WITH USRNO,YEARWORK,JDAYWORK
                FILEPI          1;AGENDA
                READ            AGENDA,KEY17;;
*
.If Cleaning up a Period, Get the Ending Date
.
                MOVE            ZERO,FLAG3
                CMATCH          YES,REPLY                                             
                GOTO            ECPACKA IF NOT EQUAL
                MOVE            ONE,FLAG3
.
                DISPLAY         *H 44,THRGH;
                MOVE            FIFTY2,HPOS
                MOVE            ZERO,MASKSW
                MOVE            ZERO,REQFLAG
                MOVE            REPLY,DIM1                                              
                CALL            GETDATE
                MOVE            DIM1,REPLY                                              
                BRANCH          FLAG1 TO ECPACK1
.
                COMPARE         ZERO,EOSFLAG
                GOTO            ECPACKF IF EQUAL
                DISPLAY         *H 52,*EL,LST;
                MOVE            NINTY9,YEARWORK
                MOVE            NINTY99,JDAYWORK
*
.Make Sure
.
ECPACKF         PACK            KEYWORK WITH USRNO,YEARWORK,JDAYWORK
                MOVE            KEYWORK,KEYWORK2
                DISPLAY         *H 70,SRE;
                CALL            KREPLYN
                CMATCH          YES,REPLY                                            
                GOTO            ECPACK IF NOT EQUAL
*
.Initialize Some Variables
.
ECPACKA         MOVE            ZERO,JDAYWRK1
                MOVE            ONE,PFUNC
*
.Read Through the Appointment File
.
ECPACK2         FILEPI          1;AGENDA
                READKS          AGENDA;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER:
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                GOTO            ECPACK18 IF OVER
*
.Within Period ?
.
                COMPARE         ZERO,FLAG3
                GOTO            ECPACK3 IF EQUAL
.
                PACK            KEY17 WITH USRNO1,YEARWORK,JDAYWORK
                MATCH           KEY17,KEYWORK2
                GOTO            ECPACK18 IF LESS
                GOTO            ECPACKC
*
.Right User ?
.
ECPACK3         COMPARE         USRNO,USRNO1
                GOTO            ECPACK18 IF NOT EQUAL
*
.Same Day ?
.
ECPACKC         COMPARE         JDAYWORK,JDAYWRK1
                GOTO            ECPACK5 IF EQUAL
*
.We Have a New Day
.
                MOVE            JDAYWORK,JDAYWRK1
                CALL            JULGREG
.
                CALL            FINDOW
                CALL            LOAD03
.
ECPACK4
                DISPLAY         *P2:4,DATE," - ",DIM40;                                
*
.Display the Information
.
ECPACK5
                DISPLAY         *SETSWTB 6:20,*SETSWLR 3:78,*R;                        
                DISPLAY         *HU,*H 5,STIME,*H 14,*+,ETIME,*H 24,SECFLAG,DATA:
                                *SETSWALL=1:24:1:80;                                             
.
                BRANCH          FLAG3 TO ECPACK16
*..............................................................................
.
.                     P A C K U P   C O M M A N D   H A N D L E R
...............................................................................
.
.
ECPACK6         DISPLAY         *HD,*EL,SPACE,MRFUNC2,SPACE,MRFUNC3,SPACE,MRFUNC5;
*
.Position to the Correct Function
.
ECPACK7         LOAD            FUNCDESC BY PFUNC FROM MRFUNC2,MRFUNC3,MRFUNC5
.
                MOVE            PFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           PFPOS,NWORK2
                MOVE            PFPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
ECPACK8         DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                MOVE            SPACE,REPLY                                             
                KEYIN           *H HPOS,*HA -1,*+,*T60,*RV,REPLY;
                IF              LEFT                                                              
                CMOVE           LEFT,REPLY                                               
                ENDIF           
                IF              RIGHT                                                              
                CMOVE           RIGHT,REPLY                                            
                ENDIF           
                GOTO            ECPACK12 IF LESS
                GOTO            ECPACK13 IF F5
                GOTO            ECPACK13 IF F9                                          
                GOTO            ECPACK11 IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
*
.Check for a Direction Command
.
                CMATCH          066,REPLY
                GOTO            ECPACK9 IF EQUAL
                CMATCH          064,REPLY
                GOTO            ECPACK10 IF EQUAL
                CMATCH          SPACE,REPLY
                GOTO            ECPACK9 IF EQUAL
*
.Check for a Function Letter
.
                RESET           PLETS
                SCAN            REPLY,PLETS
                IF              NOT EQUAL                 // Lower case            
                RESET           PLETS2                                              
                SCAN            REPLY,PLETS2                                      
                GOTO            ECPACK7 IF NOT EQUAL                                 
                MOVEFPTR        PLETS2,PFUNC                                         
                GOTO            ECPACK7                                             
                ENDIF                                     
                MOVEFPTR        PLETS,PFUNC
                GOTO            ECPACK7
*
.Move Right to Next Function
.
ECPACK9         ADD             ONE,PFUNC
                COMPARE         FOUR,PFUNC
                GOTO            ECPACK7 IF NOT EQUAL
                MOVE            ONE,PFUNC
                GOTO            ECPACK7
*
.Move Left to the Previous Function
.
ECPACK10        SUB             ONE,PFUNC
                GOTO            ECPACK7 IF NOT ZERO
                MOVE            THREE,PFUNC
                GOTO            ECPACK7
*
.We Have a Selected Function
.
ECPACK11        BRANCH          PFUNC TO ECPACK2,ECPACK14,ECPACK16
                CALL            INTERR
*
.A Timeout Occurred
.
ECPACK12        MOVE            ZERO,FLAG1
                CALL            CHKALRM
                DISPLAY         *P59:1,DATE,SPACE2,TIME;
                GOTO            ECPACK8
*
.Help Requested
.
ECPACK13        MOVE            ELEVEN,HMENU
                MOVE            PFUNC,HFUNCNO
                CALL            HELP
                GOTO            ECPACK4
*.............................................................................
.
.Read the Previous Record
.
ECPACK14        FILEPI          1;AGENDA
                READKP          AGENDA;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER:
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                GOTO            ECPACK15 IF OVER
*
.Right User ?
.
                COMPARE         USRNO,USRNO1
                GOTO            ECPACKC IF EQUAL
*
.Beginning of User's File
.
ECPACK15        KEYIN           *CLICK,*HD,*EL,*DV,NOPREVR,REPLY;
.
                FILEPI          1;AGENDA
                READKS          AGENDA;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER:
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                GOTO            ECPACK6
* ..........................................................................
.
.Delete the Record
.
ECPACK16        MOVE            ONE,PFUNC
*
.Reread the Record (Data May have Been Changed by CHKALRM Above)
.
                CLEAR           REPLY

                FILEPI          1;AGENDA
                READ            AGENDA,REPLY;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER:
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
.
                PACK            KEY17 WITH USRNO,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER
.
                CALL            AG1090
*
.Check for a Daily Reminder
.
                COMPARE         ZERO,NBLOCKS
                GOTO            ECPACK2 IF EQUAL
*
.Read the Graph Record for the Day
.
                PACK            DIM11 WITH USRNO,YEARWORK,JDAYWORK
                FILEPI          1;GRAPH
                READTAB         GRAPH,DIM11;*12,COUNT,TABLE
                CALL            INTERR IF OVER
*
.Remove the Record from the Table
.
                BRANCH          COUNT TO ECPACK17      // Last Appointment, Remove Graph Record
.
                MOVE            KEY17,KEYA
                CLEAR           KEY18
                CALL            DELTABLE
*
.Update the Graph File
.
                SUB             ONE,COUNT
                FILEPI          1;GRAPH
                UPDATAB         GRAPH;*12,COUNT,TABLE
*
.Ensure the Position of the Appointment File
.
                FILEPI          1;AGENDA
                READ            AGENDA,KEYA;;
                GOTO            ECPACK2
*
.Delete the Graph Record
.
ECPACK17        FILEPI          1;GRAPH
                DELETE          GRAPH,DIM11
                CALL            INTERR IF OVER
                GOTO            ECPACK2
*
.Packup Complete
.
ECPACK18        DISPLAY         *CLICK,*HD,*EL,CLNCPT,*W2;
                GOTO            ECSRCH14
+..............................................................................
.
.                  A P P O I N T M E N T    S E A R C H I N G
...............................................................................
.
.
ECSRCH          MOVE            EIGHT,CMDTRAP                                          
                TRAP            ECSRCH14 IF ESCAPE                                      
                TRAP            ECSRCH14 IF F27                                       
                MOVE            ONE,FLAG3
*
.Get the Search Key
.
ECSRCH1
                CALL            SETSW01
                DISPLAY         *P=23:22,*RPTCHAR=HB:10;                              
                KEYIN           *HD,*EL,*DV,LITENT,*DV,SRCHKEY:
                                *RPTCHAR "_":20,*H 23,*IT,*RV,DIM20;
                DISPLAY         *IN,*H 23,DIM20;
                GOTO            ECSRCH13 IF EOS
.
                CMATCH          SPACE,DIM20
                GOTO            ECSRCH1 IF EQUAL
.
                MOVE            ZERO,JDAYWRK1
                MOVE            TWENTY,VPOS
*
.Build the Keys
.
                RESET           DIM20,3
                GOTO            ECSRCH3 IF NOT EOS
.
ECSRCH2         NORETURN
                KEYIN           *CLICK,*HD,*EL,*DV,INVKEY,REPLY;
                GOTO            ECSRCH1
.
ECSRCH3         RESET           DIM20
                MOVELPTR        DIM20,INDEX           // Save the Length Entered
.
                PACK            KEY9 WITH X01,USRNO
                PACK            DIM40 USING ZERO,CTWO,F,DIM20
*
.See if We Should Print, too.
.
                KEYIN           *HD,*EL,*DV,PRTPR;
                CALL            KREPLYN
.
                REP             REPYN,REPLY
                MOVE            ONE,FLAG3
                MOVE            REPLY,FLAG3
*
.Open the Printer or Spool File
.
                BRANCH          FLAG3 TO ECSRCH4
.
                CALL            SPOOL
                BRANCH          FLAG1 TO ECSRCH14
.
                MOVE            NINE,CMDTRAP                                         
                TRAP            ECSRCH13 IF ESCAPE                                   
                TRAP            ECSRCH13 IF F27                                      
                CALL            ECSRCH15
*
.Do the Initial Read
.
ECSRCH4         TRAP            ECSRCH2 IF IO
                FILEPI          1;AGENDAIM
                READ            AGENDAIM,KEY9,DIM40;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN:
                                COUNTER,ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                TRAPCLR         IO
.
                DISPLAY         *HD,*EL,SCHPR,*HON,*+,DIM20,*HOFF;
                GOTO            ECSRCH12 IF OVER
                GOTO            ECSRCH6
*
.Read Generically Through the Appointment Records
.
ECSRCH5         FILEPI          1;AGENDAIM
                READKG          AGENDAIM;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN:
                                COUNTER,ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                GOTO            ECSRCH12 IF OVER
*
.Don't Display Confidential Appointments if Inquiring
.
ECSRCH6         COMPARE         ZERO,INQSW
                GOTO            ECSRCH7 IF EQUAL       // Not Inquiring
                CMATCH          "*",SECFLAG
                GOTO            ECSRCH5 IF EQUAL       // Confidential
*
.Same Date ?
.
ECSRCH7         COMPARE         YEARWORK,YEARWRK1
                GOTO            ECSRCH8 IF NOT EQUAL   // Different Year
                COMPARE         JDAYWORK,JDAYWRK1
                GOTO            ECSRCH10 IF EQUAL      // Same Date
*
.Change of Dates
.
ECSRCH8         MOVE            YEARWORK,YEARWRK1
                MOVE            JDAYWORK,JDAYWRK1
*
.Do We Have any Room on the Screen ?
.
                SUB             TWO,VPOS
                GOTO            ECSRCH9 IF NOT LESS
.
                KEYIN           *HD,*EL,*HON,*DV,CONTPR2,*HOFF,*H 1,REPLY;
                GOTO            ECSRCH IF F5
                MOVE            TWENTY,VPOS
*
.New Date
.
ECSRCH9         CALL            JULGREG
.
                CALL            FINDOW
                CALL            LOAD03
.
                CALL            SETSW03
                DISPLAY         *HD,*H 5,*R,*R:
                                DATE,SPACE2,DIM40,*SETSWALL=1:24:1:80;
.
                BRANCH          FLAG3 TO ECSRCH10
                SUB             TWO,LINE
                CALL            ECSRCH15 IF LESS
                PRINT           *N,*N,*5,DATE,SPACE2,DIM40
*
.Check for a Full Screen
.
ECSRCH10        SUB             ONE,VPOS
                GOTO            ECSRCH11 IF NOT LESS
.
                KEYIN           *HD,*EL,*HON,*DV,CONTPR2,*HOFF,*H 1,REPLY;
                GOTO            ECSRCH IF F5
                MOVE            TWENTY,VPOS
*
.Locate the Key in the Data
.
ECSRCH11        MOVE            DATA,KEYA
                REP             CAPREP,KEYA
                REP             CAPREP,DIM20
.
                SCAN            DIM20,KEYA
                CALL            INTERR IF NOT EQUAL
*
.Compute the Horizontal Position
.
                MOVEFPTR        KEYA,HPOS
                RESET           DATA,HPOS
                MOVE            DATA,DIM20
                RESET           DATA
                SETLPTR         DIM20,INDEX
                ADD             TWENTY2,HPOS
*
.Display the Information with the Key Highlighted
.
                CALL            SETSW03
                DISPLAY         *R,*HD,*H 2,STIME:
                                *H 12,ETIME,*H 22,SECFLAG,DATA:
                                *H HPOS,*HON,*+,DIM20,*HOFF,*SETSWALL=1:24:1:80;
.
                BRANCH          FLAG3 TO ECSRCH5
                PRINT           *2,STIME,*12,ETIME,*22,SECFLAG,DATA
                SUB             ONE,LINE
                CALL            ECSRCH15 IF LESS
                GOTO            ECSRCH5
*
.End of File Encountered
.
ECSRCH12        KEYIN           *HD,*EL,*HON,*DV,RETPR,*HOFF,*H 1,REPLY;
                GOTO            ECSRCH
*
.Terminate the Search Routine
.
ECSRCH13        BRANCH          FLAG3 TO ECSRCH14
                RELEASE
                SPLCLOSE
.
ECSRCH14        NORETURN
                GOTO            ECSRCH14 IF NOT OVER                              
                CALL            SETSW01
                DISPLAY         *HD,*EL;
                BRANCH          INQSW OF CALENDR1                                  
                GOTO            CALENDR2
*
.Top of Form Routine
.
ECSRCH15        MOVE            FIFTY,LINE
                PRINT           *F,*N,*N,*20,CALTIT:
                                *N,*N,*2,KEYSP,DIM20,*N,*N
                RETURN
GETCCR          KEYIN           *CLICK,*HD,*EL,*DV,SCHCON:
                                *HA -1,REPLY;
                RETURN
.
. *** End ***
.
