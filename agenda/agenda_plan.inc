*---------------------------------------------------------------
.
. Module Name: agenda_plan.inc
. Description: Meeting Planner Module
.
. Revision History:
.
.Open the Appointment Files as Needed
.
PLAN
                MOVE            ZERO,AGENDASW
                MOVE            OPENFLAG,REPLY
                AND             0100,REPLY
                GOTO            PLAN1 IF NOT ZERO
                TRAP            TRAPIO IF IO         // Can't open a file              
                OPEN            GRAPH,FSG,SHARE
                OPEN            AGENDA,FSA,SHARE
                OPEN            AGENDAIM,FSA,SHARE
                OR              0100,OPENFLAG
                TRAPCLR         IO
*
.Open the Planning Files as Needed
.
PLAN1           MOVE            OPENFLAG,REPLY
                AND             004,REPLY
                GOTO            PLAN2 IF NOT EQUAL
.
                TRAP            TRAPIO IF IO
                OPEN            PLAN,FSP,SHARE
                OPEN            PLAN1,FSP1,SHARE
                OR              004,OPENFLAG
                TRAPCLR         IO
*
.Display the User's Outstanding Meetings
.
PLAN2           CALL            CLOCKDT
                MOVE            ZERO,MSGSW
                CALL            SHOWBOX1
                DISPLAY         *P30:1,MEETPL;
*
.Turn Off His Meeting Flag
.
                PACK            KEY9 WITH X02,CURRUSER
                FILEPI          3;USRFILE
                READTAB         USRFILE,KEY9;REPLY;
                CALL            INTERR IF OVER
.
                UPDATAB         USRFILE;*91,ZERO
*
.Position the Meeting File to the Current User/Date/Time
.
PLAN3
                NORETURN
                CALL            CLOCKDT
                PACK            KEYWORK WITH USRNO,YEARWORK,JDAYWORK
                FILEPI          1;PLAN
                READ            PLAN,KEYWORK;;
.
                MOVE            USRNO,KEY6
                MOVE            ZERO,DTLCOUNT
                MOVE            ZERO,EOFSW
.
                CALL            SETSW01
                DISPLAY         *HD,*EL:
                                *P6:4,ALMSG1,*H 18,ALMSG2,*H 30,SCHBY:
                                *H 54,PLLOC,*H 70,PLCON:
                                *P3:5,*RPTCHAR HB:11,*H 16,*RPTCHAR HB:8:
                                *H 26,*RPTCHAR HB:20,*H 48,*RPTCHAR HB:20:
                                *H 70,*RPTCHAR HB:9
*
.Display a Screen of His Outstanding Meetings
.
PLAN4
                FILEPI          1;PLAN
                READKS          PLAN;KEY17,USRNO2,ENDHOUR,ENDMIN,DATE:
                                STIME,ETIME,USRNAME1,LOCATION,CONFIRM,DATA
                GOTO            PLAN5 IF OVER
*
.Right User ?
.
                MATCH           KEY6,KEY17
                GOTO            PLAN5 IF NOT EQUAL
*
.Save the Record's Key
.
                ADD             ONE,DTLCOUNT
                STORE           KEY17 BY DTLCOUNT INTO KEYA,KEYB,KEYC,KEYD,KEYE,KEYF:
                                KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN,KEYO,KEYP,KEYQ
*
.Display the Meeting Info
.
                DISPLAY         *H 3,DATE,*H 16,STIME,*H 26,USRNAME1:
                                *H 48,LOCATION,*H 73,CONFIRM
.
                COMPARE         "16",DTLCOUNT
                GOTO            PLAN4 IF NOT EQUAL
                GOTO            MP$CMD1
*
.Indicate We Encountered the End of File
.
PLAN5
                MOVE            ONE,EOFSW

+..............................................................................
.
.          M E E T I N G   P L A N N E R   C O M M A N D   H A N D L E R
...............................................................................
.
.
MP$CMD1         NORETURN
                MOVE            ZERO,CMDTRAP                                           
                TRAP            LOGON IF ESCAPE                                      
                TRAP            LOGON IF F27                                            
                DISPLAY         *HD,*EL,SPACE,MPFUNC2,SPACE,MPFUNC4,SPACE:
                                MPFUNC3,SPACE,NFUNC1; 
                CLEAR           FUNCDESC           // Clear the functions.               
                MOVE            ZERO,FLAG1         // Flag1 = 0                           
                CALL            CHKALRM            // Check for alarm,plan,message.        
                MOVE            ZERO,FLAG2
*
.Highlight the Correct Function
.
MP$CMD2         LOAD            FUNCDESC BY BFUNC FROM MPFUNC2,MPFUNC4,MPFUNC3,NFUNC1   
                MOVE            BFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           BFPOS,NWORK2
                MOVE            BFPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
MP$CMD3         DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              LEFT                                                              
                CMOVE           LEFT,REPLY                                              
                ENDIF           
                IF              RIGHT                                                              
                CMOVE           RIGHT,REPLY                                             
                ENDIF           
                GOTO            MP$CMD8 IF F5
                GOTO            MP$CMD8 IF F9                                          
                GOTO            MP$CMD7 IF LESS
                GOTO            MP$CMD6 IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
*
.Check for a Direction Command
.
                CMATCH          066 TO REPLY
                GOTO            MP$CMD4 IF EQUAL
                CMATCH          064 TO REPLY
                GOTO            MP$CMD5 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            MP$CMD4 IF EQUAL
*
.Check for a Function Letter
.
                RESET           BLETS
                SCAN            REPLY,BLETS
                IF              NOT EQUAL                     // Lower Case                   
                RESET           BLETS2                                                
                SCAN            REPLY,BLETS2                                        
                GOTO            MP$CMD3 IF NOT EQUAL                                
                MOVEFPTR        BLETS2,BFUNC                                         
                GOTO            MP$CMD2                                             
                ENDIF           
                MOVEFPTR        BLETS,BFUNC
                GOTO            MP$CMD2
*
.Move Right to the Next Function
.
MP$CMD4         ADD             ONE,BFUNC
                COMPARE         FIVE,BFUNC
                GOTO            MP$CMD2 IF NOT EQUAL
                MOVE            ONE,BFUNC
                GOTO            MP$CMD2
*
.Move Left to the Next Function
.
MP$CMD5         SUB             ONE,BFUNC
                GOTO            MP$CMD2 IF NOT ZERO
                MOVE            FOUR,BFUNC
                GOTO            MP$CMD2
*
.We Have a Selected Function

MP$CMD6         BRANCH          BFUNC TO MPADD,MPCONFRM,MPCAN,MPNEXT
                CALL            INTERR
*
.A Timeout Occurred - Check Alarm & Messages
.
MP$CMD7         MOVE            ZERO,FLAG1
                CALL            CHKALRM
                DISPLAY         *P59:1,DATE,SPACE2,TIME;
                GOTO            MP$CMD3
*
.Help Requested
.
MP$CMD8         MOVE            TEN,HMENU
                MOVE            BFUNC,HFUNCNO
                CALL            HELP
                CALL            SHOWBOX1
                GOTO            PLAN3
+..............................................................................
.
.                  N E X T   P A G E   O F   M E E T I N G S
...............................................................................
.
.
MPNEXT          BRANCH          EOFSW TO MPNEXT1         We're at the End of File
.
                TRAPCLR         ESCAPE                                                
                TRAPCLR         F27                                                    
                CALL            SETTOP06
                CALL            SETSW01
                DISPLAY         *V 6;
.
                FILEPI          1;PLAN
                READ            PLAN,KEY17;;
                MOVE            ZERO,DTLCOUNT
                GOTO            PLAN4
*
.If End of File and 1st Screen, Just Return to Command Line
.
MPNEXT1         BRANCH          PAGE TO MP$CMD3
*
.Rewind to the 1st Screen of Meetings
.
                CALL            SETSW01
                GOTO            PLAN3
+..............................................................................
.
.                    S C H E D U L E   A   M E E T I N G
...............................................................................
.
.
MPADD           NORETURN
                MOVE            THIRTY8,CMDTRAP                                       
                TRAP            PLAN3 IF ESCAPE                                       
                TRAP            PLAN3 IF F27                                          
.
                CALL            SETSW01
                DISPLAY         *P5:4,SCHM1:
                                *N,*N,*H 5,SCHM2:
                                *N,*H 2,SCHM3,SCHM4:
                                *N,*H 2,SCHM5:
                                *N,*N,*H 5,SCHM6:
                                *N,*H 2,SCHM7,SCHM8:
                                *N,*H 2,SCHM9,SCHM10:
                                *N,*H 2,SCHM11,SCHM12;
*
.See Which Mode They Want
.
MPADD1          CMOVE           "1",REPLY                                            
                KEYIN           *HD,*EL,*DV,PLANMODE,*HA -1,*RV,REPLY;               
                CMATCH          "1",REPLY
                GOTO            MPADDA IF EQUAL
                GOTO            PLAN3 IF EOS
                CMATCH          "2",REPLY
                GOTO            MPADD1 IF NOT EQUAL
                GOTO            MPADDB
*
.Delete the Work File and Return to the Command Line
.
MPADD2          COMPARE         ONE,SWITCHI          IS SCRATCHI FILE OPEN ?            
                GOTO            PLAN3 IF NOT EQUAL

                CALL            AG9005
                MOVE            ZERO TO MSGSW RE-SET MSGSW AFTER CANELLING MEETING 
                GOTO            PLAN3
+..............................................................................
.
.Meeting Planner Mode 1 (Check Availability)
.
.
MPADDA          MOVE            THIRTY9,CMDTRAP                                         
                TRAP            MPADD IF ESCAPE                                       
                TRAP            MPADD IF F27                                         

                CALL            SETSW01
                DISPLAY         *PMEETPOS:4,PLMEET,ALMSG1,COLON:
                                *PSTPOS:6,PLST,ALMSG2,COLON:
                                *PENDPOS:7,PLEND:
                                *P19:8,*RPTCHAR HB:37:
                                *PDURPOS:9,PLDUR:
                                *P8:12,PLATT,*H 46,PLSTAT:
                                *P2:13,*RPTCHAR HB:20,*H 24,*RPTCHAR HB:54;
*
.Get the Meeting Date
.
MPADDA1         MOVE            MON,MONWORK
                MOVE            DAY,DAYWORK
                MOVE            YEAR,YEARWORK
                CALL            GREGJUL
                CALL            JULGREG              // Set up 'DATE' for display
                DISPLAY         *HD,*EL,LITENT,PLMEET,ALMSG1,PERIOD:           
                                *P45:4,DATE:
                                *P59:4,*RPTCHAR " ":9;
                MOVE            ZERO,REQFLAG         // Allow Null Entry
                MOVE            ONE,MASKSW           // Do Not Display Mask
                MOVE            FORTY5,HPOS          // Horizontal Position
                MOVE            FOUR,VPOS            // Vertical Position
                CALL            GETDATE              // DATE JDAYWORK YEARWORK DAYWORK MONWORK
                BRANCH          FLAG1 TO MPADD       // F5 Key Pressed (Date Vars Invalid)
.
                CALL            CHECKDT              // Make Sure That the Date Entered
.                                       // is the Same or after the Current Date
                GOTO            MPADDA1 IF NOT EQUAL // Invalid Date
.
                CALL            FINDOW
                LOAD            DIM11 BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
                DISPLAY         *P59:4,DIM11;
*
.Get the Meeting Starting Time
.
MPADDA2         DISPLAY         *HD,*EL,LITENT,LITST;
                MOVE            FORTY5,HPOS
                MOVE            SIX,VPOS
                MOVE            ONE,REQFLAG          // Don't Allow Null Entry
                MOVE            ZERO,MASKSW          // Display Mask
                CALL            GETIME
.
                BRANCH          FLAG1 TO MPADDA1
.
                BRANCH          SAMEDAY TO MPADDA3      Different Day, No Checking
                CALL            CHECKTM
                GOTO            MPADDA2 IF NOT EQUAL
.
MPADDA3         MOVE            HOURWORK,HOUR
                MOVE            MINWORK,MIN
*
.Get the Meeting Ending Time
.
MPADDA4         DISPLAY         *HD,*EL,LITENT,LITET;
                MOVE            FORTY5,HPOS
                MOVE            SEVEN,VPOS
                CALL            GETIME
                BRANCH          FLAG1 TO MPADDA2
.
                MOVE            HOURWORK,ENDHOUR
                MOVE            MINWORK,ENDMIN
*
.Make Sure the Starting Time is Before the Ending Time
.
                CALL            CHECKEND
                BRANCH          FLAG1 TO MPADDA4
*
.Save the Date & Times
.
                MOVE            HOUR,HOURSAV
                MOVE            MIN,MINSAV
                MOVE            ENDHOUR,EHOURSAV
                MOVE            ENDMIN,EMINSAV
*
.Set up the Day Table
.
                CALL            PACK01                                            
.
                CALL            POSITABL
                CALL            COMPUTE
                MOVE            F,REPLY
                CALL            ADDTABLE
*
.Compute the Meeting Duration
.
                MOVE            ENDMIN,NWORK1
                MOVE            ENDHOUR,HOURWRK1
.
                SUB             MIN,NWORK1
                GOTO            MPADDA5 IF NOT LESS
                ADD             SIXTY,NWORK1
                SUB             ONE,HOURWRK1
.
MPADDA5         SUB             HOUR,HOURWRK1
.
                MOVE            NWORK1,MINWRK1
                MOVE            MINWRK1,DIM2
                REP             SPACZERO,DIM2
                DISPLAY         *P45:9,HOURWRK1,":",DIM2;
*
.Ready the Work File
.
                MOVE            FOURTEEN,VPOS

                CALL            AG9000                                             
                MOVE            FORTY,CMDTRAP                                           
                TRAP            MPADD2 IF ESCAPE                                       
                TRAP            MPADD2 IF F27                                           
*
................................................................................
.                                                                              .
.     The following new code was added to include the new command handler for  .
.     the two new options, Single person entry and Group entry. I copied the   .
.     code from the above command handler and modified it to fit this purpose. .
.                                                                              .
................................................................................
MPCMD0          MOVE            ZERO,CMDTRAP                                            
                TRAP            PLAN2 IF ESCAPE                                        
                TRAP            PLAN2 IF F27                                          
                DISPLAY         *HD,*EL,SPACE,MPFUNC5,SPACE,SPACE,MPFUNC6,SPACE;
                MOVE            ZERO,FLAG2
.
.Highlight the Correct Function
.
MPCMD1          LOAD            FUNCDESC BY MPFUNC FROM MPFUNC5,MPFUNC6
                MOVE            MPFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           MPPOS,NWORK2
                MOVE            MPPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
MPCMD2          DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              LEFT                                                             
                CMOVE           LEFT,REPLY                                              
                ENDIF           
                IF              RIGHT                                                            
                CMOVE           RIGHT,REPLY                                            
                ENDIF           
                GOTO            MPCMD7 IF F5
                GOTO            MPCMD7 IF F9                                            
                GOTO            MPCMD6 IF LESS
                GOTO            MPCMD5 IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
*
.Check for a Direction Command
.
                CMATCH          066 TO REPLY
                GOTO            MPCMD3 IF EQUAL
                CMATCH          064 TO REPLY
                GOTO            MPCMD4 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            MPCMD3 IF EQUAL
*
.Check for a Function Letter
.
                RESET           MPLETS
                SCAN            REPLY,MPLETS
                IF              NOT EQUAL                // Lower Case                         
                RESET           MPLETS2                                            
                SCAN            REPLY,MPLETS2                                      
                GOTO            MPCMD2 IF NOT EQUAL                                 
                MOVEFPTR        MPLETS2,MPFUNC                                    
                GOTO            MPCMD1                                            
                ENDIF          

                MOVEFPTR        MPLETS,MPFUNC
                GOTO            MPCMD1
*
.Move Right to the Next Function
.
MPCMD3          ADD             ONE,MPFUNC
                COMPARE         THREE,MPFUNC
                GOTO            MPCMD1 IF NOT EQUAL
                MOVE            ONE,MPFUNC
                GOTO            MPCMD1
*
.Move Left to the Next Function
.
MPCMD4          SUB             ONE,MPFUNC
                GOTO            MPCMD1 IF NOT ZERO
                MOVE            TWO,MPFUNC
                GOTO            MPCMD1
*
.We Have a Selected Function
.
MPCMD5          COMPARE         ONE,PLANFLG                                           
                IF              EQUAL                                                        
                BRANCH          MPFUNC TO MPADDA6,MPADDGRP
                ELSE            
                BRANCH          MPFUNC TO MPADDB10,MPADDGRP                          
                ENDIF          
                CALL            INTERR
*
.A Timeout Occurred - Check Alarm & Messages
.
MPCMD6          MOVE            ZERO,FLAG1
                CALL            CHKALRM
                DISPLAY         *P59:1,DATE,SPACE2,TIME;
                GOTO            MPCMD2
*
.Help Requested
.
MPCMD7          MOVE            TEN,HMENU
                MOVE            MPFUNC,HFUNCNO
                CALL            HELP
                CALL            SHOWBOX1
                GOTO            PLAN3
*
................................................................................
.                                                                              .
. End of the added code for the new command selection portion.                 .
.                                                                              .
................................................................................
*
.Get the Attendees
.
MPADDA6         MOVE            TWO,HPOS
                MOVE            ONE,FLAG1            // Any User
                MOVE            ZERO,FLAG4
                CALL            FINDUSER
                BRANCH          EOSFLAG TO MPADDA9
                COMPARE         ZERO,FLAG1
                GOTO            MPADDA7 IF EQUAL
*
.To Backup, Delete the Work File First
.
                CALL            AG9005               // CLOSE SCRATCH FILE           
                CALL            SETTOP14
                CALL            SETSW01
                DISPLAY         *HD,*EL,*P45:9,*RPTCHAR " ":5;
                GOTO            MPADDA4
*
.Check for Duplicate Requests
.
MPADDA7         MOVE            USRNO1,KEY6
                READ            SCRATCHI,KEY6;REPLY
                GOTO            MPADDA71 IF OVER
.
                KEYIN           *CLICK,*HD,*EL,*DV,USRREQ,REPLY;
                GOTO            MPADDA6
*
.Write the User Number to the Scratch File
.
MPADDA71        DISPLAY         *P2:VPOS,USRNAME1,*H 24,PLREQ;
                WRITE           SCRATCHI,KEY6;USRNO1,USRNAME1
.
                COMPARE         TWENTY1,VPOS
                GOTO            MPADDA8 IF NOT EQUAL
*
.Roll the Window Up One
.
                CALL            SETTOP14
                CALL            SETSW03
                DISPLAY         *HD,*R,*SETSWALL=1:24:1:80;
                GOTO            MPADDA6
*
.Position to the Next Line Down
.
MPADDA8         ADD             ONE,VPOS
                GOTO            MPADDA6
*
.All Users are Entered
.
MPADDA9         REPOSIT         SCRATCHI,ZERO
.
MPADDA10        CALL            DISPCAA
                CALL            SETTOP14
                CALL            SETSW02
                DISPLAY         *HU;
.
                MOVE            ZERO,COUNT
*
.Get a User Name
.
MPADDA11        READ            SCRATCHI,SEQ;USRNO1,USRNAME1
                GOTO            MPADDA15 IF OVER
.
                DISPLAY         *H 1,USRNAME1,*H 24,PLCHK;
*
.Position to the Correct Day
.
                PACK            DIM11 WITH USRNO1,YEARWORK,JDAYWORK                     
                FILEPI          1;GRAPH                                                    
                READ            GRAPH,DIM11;DIM11,COUNTER,TABLE                           
                GOTO            MPADDA12 IF NOT OVER      // Possible Conflict                         
                CALL            CHECKMEET               // Check for conflicting meeting.  
                GOTO            MPADDA14 IF EQUAL       // No conflict.                   
.See if the Appointment Conflicts
.
.  Establish TPOS and NBLOCKS prior to calling CHECK
MPADDA12
                CALL            CHECK
                GOTO            MP12A IF EQUAL      // No Problem                            
                GOTO            MP12B                                                     
MP12A           CALL            CHECKMEET               // Check for conflicting meeting.  
                GOTO            MPADDA14 IF EQUAL      // No Problem
                                             
*
.User Can't Attend
.
MP12B           CMATCH          SPACE,SECFLAG            // Confidential?
                GOTO            MPADDA13 IF EQUAL      // No...
                MOVE            CONMSG,DATA
.
MPADDA13        DISPLAY         *H 24,PLUNAV,PAROP,TFLAG,PARCL,SPACE
                ADD             ONE,COUNT
                GOTO            MPADDA11
*
.User Can Attend
.
MPADDA14        DISPLAY         *H 24,PLAVAIL
                GOTO            MPADDA11
*
................................................................................
.                                                                              .
.        GROUP BROADCAST FOR THE MEETING PLANNER                               .
.                                                                              .
.   This is the new code added for the GROUP option in the meeting planner. It .
.   was copied from the broadcast in the message section and modified to fit   .
.   meeting section design.                                                    .
.   The code checks the group name, gathers all the users in that group,       .
.   checks thier schedules, and either confirms or displays that they are not  .
.   able to attend.                                                            .
.                                                                              .
................................................................................
MPADDGRP        CALL            AG9000                                             
                MOVE            ZERO,COUNT
                MOVE            SEVNTEEN,CMDTRAP                                       
                TRAP            MPADDG11 IF ESCAPE                                  
                TRAP            MPADDG11 IF F27                                      
                MOVE            ZERO,NWORK1
.
MPADDGR1        COMPARE         ONE,PLANFLG                                          
                IF              EQUAL                                                          
                KEYIN           *HD,*EL,*DV,LITENT,*DV,PLGRP:
                                *P2:14,*RPTCHAR "_":6,*H 2,DIM6;
                ELSE           
                KEYIN           *HD,*EL,*DV,LITENT,*DV,PLGRP:
                                *P30:16,*RPTCHAR "_":6,*H 30,DIM6;                   
                ENDIF           
                GOTO            MPADDG11 IF F5
.
                CMATCH          " ",DIM6
                GOTO            MPADDA16 IF EQUAL
*
.See If He Wants the Entire Group or Pick & Choose
.
                DISPLAY         *HD,*EL,PLSEL;                                     
                CALL            KREPLYN                                            
                GOTO            MPADDGR1 IF F5
.
                REP             PLREP,REPLY
                MOVE            ZERO,INDEX
                MOVE            REPLY,INDEX
*
.Branch to the Correct Routine
.
                BUMP            DIM6,0
                GOTO            MPADDGR7 IF EOS
*
.Pull All Users for the Specified Group
.
                PACK            AKEY2 WITH L04,DIM6
.
                TRAP            MPADDGR2 IF IO
                FILEPI          1;USRFILE
                READTAB         USRFILE,AKEY2;*11,USRNO1,USRNAME1
                TRAPCLR         IO
                GOTO            MPADDGR4 IF NOT OVER
.
                KEYIN           *CLICK,*HD,*EL,*DV,GRNFND,REPLY;
                GOTO            MPADDGR1
*
.Invalid Key Specification
.
MPADDGR2        NORETURN
                KEYIN           *CLICK,*HD,*EL,*DV,IGRPSPEC,REPLY;
                GOTO            MPADDGR1
*
.Read Generically Through the File
.
MPADDGR3        FILEPI          1;USRFILE
                READKGTB        USRFILE;*11,USRNO1,USRNAME1
                GOTO            MPADDGR6 IF OVER
*
.Include This User ?
.
MPADDGR4        COMPARE         ONE,PLANFLG                                         
                IF              EQUAL                                                       
                DISPLAY         *P2:VPOS,USRNAME1;
                ELSE            058
                DISPLAY         *P30:VPOS,USRNAME1;                                 
                ENDIF           058
                BRANCH          INDEX TO MPADDGR5            // All Users Selected
                DISPLAY         *HD,*EL,INCUSR;                                   
                CALL            KREPLYN                                            
                GOTO            MPADDGR1 IF F5
                CMATCH          YES,REPLY                                          
                GOTO            MPADDGR3 IF NOT EQUAL
*
.Write the Info to the Work File
.
MPADDGR5        CALL            MPADDG93
                GOTO            MPADDGR3
*
.Allow Multiple Specifications
.
MPADDGR6
                COMPARE         ONE,PLANFLG                                        
                IF              EQUAL                                                        
                DISPLAY         *P2:VPOS,*RPTCHAR SPACE:20;
                ELSE             
                DISPLAY         *P30:VPOS,*RPTCHAR SPACE:20;                        
                ENDIF            
                DISPLAY         *HD,*EL,SPECMR;                                    
                CALL            KREPLYN                                            
                CMATCH          YES,REPLY                                        

                IF              EQUAL                                                       
                COMPARE         ONE,PLANFLG                                        
                IF              EQUAL                                                      
                MOVE            ZERO,MPCOUNT                                        
                GOTO            MPADDA6
                ELSE             
                GOTO            MPADDB10                                             
                ENDIF            
                ENDIF            
                COMPARE         TWO,PLANFLG                                          
                GOTO            MPADDB95 IF EQUAL                                    
                MOVE            ZERO,MPCOUNT                                        
.
                COMPARE         ZERO,NWORK1
                GOTO            MPADDG10 IF EQUAL    // No User's Selected
*
.Go to Confirmation and Scheduling
.
                WEOF            SCRATCHI,SEQ
                REPOSIT         SCRATCHI,ZERO
                MOVE            FOUR,MSGSW
                MOVE            ZERO,NWORKSV
                MOVE            THIRTEEN,VPOS
                GOTO            MPADDG12
*
.Broadcast the Meeting to All System Users
.
MPADDGR7        FILEPI          2;USRFILE
                REPOSIT         USRFILE,ZERO
                READ            USRFILE,SEQ;REPLY
*
.Read Through the User File
.
MPADDGR8        FILEPI          1;USRFILE
                READTAB         USRFILE,SEQ;USERID,USRNO1,USRNAME1
                GOTO            MPADDGR6 IF OVER
*
.Primary Group Records Only
.
                MATCH           BLANKS,USERID
                GOTO            MPADDGR8 IF EQUAL
*
.Include This User ?
.
                COMPARE         ONE,PLANFLG                                          
                IF              EQUAL                                                       
                DISPLAY         *P2:VPOS,USRNAME1;
                ELSE           
                DISPLAY         *P30:VPOS,USRNAME1;                                  
                ENDIF           
                BRANCH          INDEX TO MPADDGR9          // All Users Selected
                DISPLAY         *HD,*EL,INCUSR;                                 
                CALL            KREPLYN
                GOTO            MPADDGR1 IF F5
                CMATCH          YES,REPLY                                          
                GOTO            MPADDGR8 IF NOT EQUAL
*
.Write the Info to the Work File
.
MPADDGR9        CALL            MPADDG93
                GOTO            MPADDGR8
*
.No User's Selected
.
MPADDG10        KEYIN           *HD,*EL,*DV,NOUSRSL,REPLY;
*
.Abort the Meeting Broadcast
.
MPADDG11
                CALL            AG9005
                MOVE            ONE,PLANFLG                                           
                GOTO            PLAN2
*
.Add This User to the List, Excluding Duplicates
.
MPADDG93        MOVE            USRNO1,KEY6
                READ            SCRATCHI,KEY6;REPLY
                GOTO            MPADDG94 IF OVER
.
                KEYIN           *CLICK,*HD,*EL,*DV,ALREQ,REPLY;
                RETURN
*
.Write the User Number to the Scratch File
.
MPADDG94        COMPARE         ONE,PLANFLG                                         
                IF              EQUAL                                                        
                DISPLAY         *P2:VPOS,USRNAME1,*H 24,PLREQ;
                ENDIF           058
                WRITE           SCRATCHI,KEY6;USRNO1,USRNAME1
                ADD             ONE,NWORK1
                ADD             ONE,VPOS
                COMPARE         ONE,PLANFLG                                          
                IF              EQUAL                                                        
                COMPARE         EIGHT,NWORK1
                RETURN          IF LESS
                SUB             ONE,VPOS
                CALL            SETTOP14
                ELSE            058
                ADD             ONE,MPCOUNT                                         
                COMPARE         SIX,NWORK1                                          
                RETURN          IF LESS                                             
                SUB             ONE,VPOS                                             
                CALL            SETTOP16                                            
                ENDIF           058
                CALL            SETSW03
                DISPLAY         *HD,*R,*SETSWALL=1:24:1:80;
                RETURN
.Get a User Name
.
MPADDG12        READ            SCRATCHI,SEQ;USRNO1,USRNAME1
                GOTO            MPADDA15 IF OVER
.
                ADD             ONE,NWORKSV
                ADD             ONE,VPOS
                COMPARE         SEVEN,NWORKSV
                GOTO            MPDISP IF LESS
                SUB             ONE,VPOS
                CALL            SETTOP14
                CALL            SETSW03
                DISPLAY         *HD,*R,*SETSWALL=1:24:1:80;
MPDISP          DISPLAY         *P2:VPOS,USRNAME1,*H 24,PLCHK;

                PACK            DIM11 WITH USRNO1,YEARWORK,JDAYWORK                     
                FILEPI          1;GRAPH                                                  
                READ            GRAPH,DIM11;DIM11,COUNTER,TABLE                         
                GOTO            MPADDG14 IF OVER      // No Conflict                       
.See if the Appointment Conflicts
.
.  Establish TPOS and NBLOCKS prior to calling CHECK
                CALL            CHECK
                GOTO            MPADDG14 IF EQUAL      // No Problem

*
.User Can't Attend
.
                CMATCH          SPACE,SECFLAG            // Confidential?
                GOTO            MPADDG13 IF EQUAL      // No...
                MOVE            CONMSG,DATA
.
MPADDG13        DISPLAY         *H 24,PLUNAV,PAROP,TFLAG,PARCL;
                ADD             ONE,COUNT
                GOTO            MPADDG12
*
.User Can Attend
.
MPADDG14        DISPLAY         *H 24,PLAVAIL
                GOTO            MPADDG12
*
................................................................................
.                                                                              .
.  End of group broadcast for the meeting planner.                             .
.                                                                              .
................................................................................
*
.Checking Complete - Display the Conflict Count
.
MPADDA15        DISPLAY         *N,*H 24,COUNT,SCHCON2,*SETSWALL=1:24:1:80;
.
*
.Schedule Everyone ?
.
MPADDA16
                DISPLAY         *HD,*EL,SCHMEET;                                  
                CALL            KREPLYN                                           
                CMATCH          YES,REPLY                                         
                GOTO            MPADDA25 IF NOT EQUAL
*
.Get the Meeting Information
.
MPADDA17        KEYIN           *HD,*EL,*DV,PLINFO,*RPTCHAR "_":55,*HA -55,*IT,DATA;
                DISPLAY         *IN,*H 7,DATA;
                GOTO            MPADDA16 IF F5
.
                CMATCH          " ",DATA
                GOTO            MPADDA17 IF EQUAL
                GOTO            MPADDA17 IF EOS
*
.Get the Meeting Location
.
MPADDA18        KEYIN           *HD,*EL,*DV,PLLOC2,*RPTCHAR "_":20,*HA -20,*IT,LOCATION;
                DISPLAY         *IN,*H 11,LOCATION;
                GOTO            MPADDA17 IF F5
.
                CMATCH          " ",LOCATION
                GOTO            MPADDA18 IF EQUAL
                GOTO            MPADDA18 IF EOS
*
.Rewind the Work File
.
                TRAPCLR         ESCAPE                                                
                TRAPCLR         F27                                                 
                REPOSIT         SCRATCHI,ZERO
                DISPLAY         *HD,*EL,PLSCH;
*
.Get the Next Meeting Number
.
                FILEPI          3;CNTFILE
                READ            CNTFILE,ZERO;MAXUSRNO,COUNTER
                ADD             ONE,COUNTER
                WRITE           CNTFILE,ZERO;MAXUSRNO,COUNTER
*
.Format the Data
.
                MOVE            HOURSAV,HOURWORK
                MOVE            MINSAV,MINWORK
                CALL            NICETIME
                MOVE            TIME,STIME
.
                MOVE            EHOURSAV,HOURWORK
                MOVE            EMINSAV,MINWORK
                CALL            NICETIME
                MOVE            TIME,ETIME
.
                MOVE            ZERO,FLAG1
*
.Add the Meeting to Each User
.
MPADDA19        READ            SCRATCHI,SEQ;USRNO1,USRNAME1
                GOTO            MPADDA22 IF OVER
                DISPLAY         *H 50,*EL,USRNAME1;
*
.Automatically Confirm Your Own Meetings
.
                MOVE            CN,CONFIRM
                COMPARE         USRNO1,CURRUSER
                GOTO            MPADDA21 IF NOT EQUAL
.
MPADDA20        MOVE            SCH,CONFIRM
                MOVE            ONE,FLAG1
*
.Check for Duplicates
.
MPADDA21        PACK            KEY17 WITH USRNO1,YEARWORK,JDAYWORK,HOURSAV,MINSAV,COUNTER
                FILEPI          1;PLAN
                READ            PLAN,KEY17;REPLY
                GOTO            MPADDA19 IF NOT OVER
*
.Add the Meeting
.
                PACK            DIM30 WITH CURRUSER,YEARWORK,JDAYWORK,HOURSAV:
                                MINSAV,COUNTER,USRNO1
                FILEPI          2;PLAN
                WRITE           PLAN,KEY17;KEY17,CURRUSER,EHOURSAV,EMINSAV,DATE:
                                STIME,ETIME,CURRNAME,LOCATION,CONFIRM,DATA
                INSERT          PLAN1,DIM30
*
.Turn on the Attendee's Meeting Flag
.
                COMPARE         CURRUSER,USRNO1
                GOTO            MPADDA19 IF EQUAL          // But Not Your Own...
.
                PACK            KEY9 WITH X02,USRNO1
                FILEPI          3;USRFILE
                READTAB         USRFILE,KEY9;REPLY
                CALL            INTERR IF OVER
.
                UPDATAB         USRFILE;*91,ONE
                GOTO            MPADDA19
*
.Make Sure The Author is Included
.
MPADDA22        BRANCH          FLAG1 TO MPADDA23
                MOVE            CURRUSER,USRNO1
                GOTO            MPADDA20
*
.Send a Message to Everyone ?
.
MPADDA23        MOVE            YEARWORK,YEAR
                MOVE            JDAYWORK,JULDAY
.
                MOVE            THIRTY8,CMDTRAP                                       
                TRAP            PLAN3 IF ESCAPE                                      
                TRAP            PLAN3 IF F27                                         

                DISPLAY         *HD,*EL,PLMSG;                                   
                CALL            KREPLYN                                           
                CMATCH          YES,REPLY                                        
                GOTO            MPADDA24 IF NOT EQUAL
*
.Don't Send a Message to the Author
.
                MOVE            CURRUSER,KEY6
                DELETE          SCRATCHI,KEY6
*
.Exit to the Message Routine
.
                REPOSIT         SCRATCHI,ZERO
                MOVE            FORTY1,CMDTRAP                                          
                TRAP            PLAN IF ESCAPE                                         
                TRAP            PLAN IF F27                                              
                GOTO            MPGOMSG              // Go to MESSAGE routine            
*
.Planning Mode 1 Complete
.
MPADDA24
                CALL            AG9005
.
                MOVE            ZERO,MSGSW
                MOVE            YEAR,YEARWORK
                MOVE            JULDAY,JDAYWORK
                MOVE            HOURSAV,HOUR
                MOVE            MINSAV,MIN
                MOVE            EHOURSAV,ENDHOUR
                MOVE            EMINSAV,ENDMIN
*
.If Cancelling, Return to Menu - If Scheduling, Allow Entry Into Calendar
.
                COMPARE         THREE,BFUNC
                GOTO            PLAN IF EQUAL        Cancelling
                GOTO            MPCNFRM4
*
.Try a Different Date/Time ?
.
MPADDA25
                DISPLAY         *HD,*EL,PLTRY,ALMSG1,SLASH,ALMSG2;                
                CALL            KREPLYN                                           
                CMATCH          YES,REPLY                                          
                GOTO            MPADDA26 IF EQUAL
*
.Exit This Function
.
                CALL            AG9005
                GOTO            MPADD
*
.Get Another Date
.
MPADDA26        DISPLAY         *HD,*EL,LITENT,PLMEET,ALMSG1,PERIOD:
                                *P59:4,*RPTCHAR " ":9;
.
                MOVE            ZERO,REQFLAG
                MOVE            ONE,MASKSW
                MOVE            FORTY5,HPOS
                MOVE            FOUR,VPOS
                CALL            GETDATE
                BRANCH          FLAG1 TO MPADDA25
.
                CALL            CHECKDT
                GOTO            MPADDA26 IF NOT EQUAL
.
                CALL            FINDOW
                LOAD            DIM11 BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
                DISPLAY         *P59:4,DIM11;
*
.Get the Meeting Starting Time
.
MPADDA27        DISPLAY         *HD,*EL,LITENT,LITST;
.
                MOVE            HOURSAV,HOURWORK
                MOVE            MINSAV,MINWORK
                MOVE            FORTY5,HPOS
                MOVE            SIX,VPOS
                MOVE            ONE,REQFLAG                                        
                CALL            GETIME
.
                BRANCH          FLAG1 TO MPADDA26
.
                BRANCH          SAMEDAY TO MPADDA28      // Different Day, No Checking
                CALL            CHECKTM
                GOTO            MPADDA27 IF NOT EQUAL
.
MPADDA28        MOVE            HOURWORK,HOUR
                MOVE            MINWORK,MIN
*
.Get the Meeting Ending Time
.
MPADDA29        DISPLAY         *HD,*EL,LITENT,LITET;
.
                MOVE            EHOURSAV,HOURWORK
                MOVE            EMINSAV,MINWORK
                MOVE            FORTY5,HPOS
                MOVE            SEVEN,VPOS
                CALL            GETIME
                MOVE            ZERO,REQFLAG                                    
.
                BRANCH          FLAG1 TO MPADDA27
.
                MOVE            HOURWORK,ENDHOUR
                MOVE            MINWORK,ENDMIN
*
.Make Sure the Starting Time is Before the Ending Time
.
                CALL            CHECKEND
                BRANCH          FLAG1 TO MPADDA29
*
.Save the Times
.
                MOVE            HOUR,HOURSAV
                MOVE            MIN,MINSAV
                MOVE            ENDHOUR,EHOURSAV
                MOVE            ENDMIN,EMINSAV
*
.Set up the Day Table
.
                CALL            PACK01                                          
.
                CALL            POSITABL
                CALL            COMPUTE
                MOVE            F,REPLY
                CALL            ADDTABLE
*
.Compute the Meeting Duration
.
                MOVE            ENDMIN,NWORK1
                MOVE            ENDHOUR,HOURWRK1
.
                SUB             MIN,NWORK1
                GOTO            MPADDA30 IF NOT LESS
                ADD             SIXTY,NWORK1
                SUB             ONE,HOURWRK1
.
MPADDA30        SUB             HOUR,HOURWRK1
.
                MOVE            NWORK1,MINWRK1
                MOVE            MINWRK1,DIM2
                REP             SPACZERO,DIM2
                DISPLAY         *P45:9,HOURWRK1,":",DIM2;
*
.Ready the Work File
.
                MOVE            FOURTEEN,VPOS
                REPOSIT         SCRATCHI,ZERO
                GOTO            MPADDA10
+..............................................................................
.
.Meeting Planner Mode 2 (Find a Date & Time)
.
MPADDB
                CALL            SETSW01
                DISPLAY         *PDTSTPOS:4,SCHST,ALMSG1,COLON:
                                *PTMSTPOS:6,SCHST,ALMSG2,COLON:
                                *PTMEDPOS:7,SCHEND,ALMSG2,COLON:
                                *PMTDURPOS:9,SCHDUR:
                                *PINCSTPOS:11,SCHSAT:
                                *P35:14,PLATT,*P25:15,*RPTCHAR HB:30;
*
.Get the Search Starting Date
.
MPADDB1         DISPLAY         *HD,*EL,LITENT,SCHST,ALMSG1,PERIOD:
                                *P59:4,*RPTCHAR " ":9;
.
                MOVE            ZERO,MASKSW

                MOVE            ZERO,REQFLAG                                      
                MOVE            FORTY5,HPOS
                MOVE            FOUR,VPOS
                CALL            GETDATE
                BRANCH          FLAG1 TO MPADD
                BRANCH          EOSFLAG TO MPADD
.
                CALL            CHECKDT
                GOTO            MPADDB1 IF NOT EQUAL
.
                MOVE            JDAYWORK,STARTDAY
                MOVE            YEARWORK,YEARSTR
.
                CALL            YEARCOMP
                CALL            FINDOW
                LOAD            DIM11 BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
                DISPLAY         *P59:4,DIM11;
*
.Get the Search Starting Time
.
MPADDB2         DISPLAY         *HD,*EL,LITENT,SCHSRCH,LITST;
.
                MOVE            FORTY5,HPOS
                MOVE            SIX,VPOS
                MOVE            ONE,REQFLAG                                       
                CALL            GETIME
                BRANCH          SAMEDAY OF MPADDB2a                                 
                CALL            CHECKTM                                              
                GOTO            MPADDB2 IF NOT EQUAL                                
MPADDB2a        BRANCH          FLAG1 TO MPADDB1                                    

.
                MOVE            HOURWORK,HOUR
                MOVE            MINWORK,MIN
*
.Get the Search Ending Time
.
MPADDB3         DISPLAY         *HD,*EL,LITENT,SCHSRCH,LITET;
                MOVE            FORTY5,HPOS
                MOVE            SEVEN,VPOS
                CALL            GETIME
                MOVE            ZERO,REQFLAG                                       
                BRANCH          SAMEDAY OF MPADDB3a                                   
                CALL            CHECKTM                                             
                GOTO            MPADDB3 IF NOT EQUAL                                
MPADDB3a        BRANCH          FLAG1 TO MPADDB2                                   
.
                MOVE            HOURWORK,ENDHOUR
                MOVE            MINWORK,ENDMIN
*
.Make Sure the Ending Time is After the Beginning Time
.
                CALL            CHECKEND
                BRANCH          FLAG1 TO MPADDB3
.
                MOVE            HOURWORK,ENDHOUR2
                MOVE            MINWORK,ENDMIN2
*
.Get the Meeting Duration
.
MPADDB4         KEYIN           *HD,*EL,*DV,LITENT,*DV,SCHDURP:
                                *P45:9,"__:__",*H 45,*+,MEETHOUR;
                GOTO            MPADDB3 IF F5
.
                COMPARE         ZERO,MEETHOUR
                GOTO            MPADDB4 IF LESS
                COMPARE         TWENTY4,MEETHOUR
                GOTO            MPADDB4 IF NOT LESS
.
                KEYIN           *H 45,*DV,MEETHOUR,*H 48,MEETMIN;
                GOTO            MPADDB4 IF F5
.
                COMPARE         ZERO,MEETMIN
                GOTO            MPADDB4 IF LESS
                COMPARE         SIXTY,MEETMIN
                GOTO            MPADDB4 IF NOT LESS
                MOVE            MEETMIN,DIM2
                REP             SPACZERO,DIM2
                DISPLAY         *H 48,DIM2;
*
.Compute the Number of Blocks
.
                MOVE            MEETHOUR,NBLOCKS
                MULT            FOUR,NBLOCKS
                MOVE            MEETMIN,NWORK1
                DIV             FIFTEEN,NWORK1
                ADD             NWORK1,NBLOCKS
.
                COMPARE         ZERO,NBLOCKS
                GOTO            MPADDB4 IF EQUAL
*
.Save the Beginning Time
.
                MOVE            HOUR,HOURSAV
                MOVE            MIN,MINSAV
*
.Include Saturdays ?
.
MPADDB5
                CMOVE           NO,DIM1                                            
                KEYIN           *P45:11,*DV,DIM1,*HA -1,*RV,DIM1;
                GOTO            MPADDB4 IF F5
.
                CMATCH          YES,DIM1                                           
                GOTO            MPADDB6 IF EQUAL
                CMATCH          NO,DIM1                                            
                GOTO            MPADDB5 IF NOT EQUAL
*
.See if the Starting Search Date is Saturday or Sunday
.
MPADDB6         CALL            FINDOW
                COMPARE         ONE,NWORK2                    // Sunday ?
                GOTO            MPADDB7 IF NOT EQUAL          // No...
                ADD             ONE,JDAYWORK                  // Position to Monday
                GOTO            MPADDB8
.
MPADDB7         COMPARE         SEVEN,NWORK2                  // Saturday ?
                GOTO            MPADDB8 IF NOT EQUAL          // No...
                CMATCH          YES,DIM1                      // Allow Saturdays ?      
                GOTO            MPADDB8 IF EQUAL              // Yes...
                ADD             TWO,JDAYWORK                  // Position to Monday
.
MPADDB8         COMPARE         JDAYWORK,YEARLEN
                GOTO            MPADDB9 IF NOT LESS
                SUB             YEARLEN,JDAYWORK
                ADD             ONE,YEARWORK
                CALL            YEARCOMP
*
.Ready a Work File
.
MPADDB9         MOVE            SIXTEEN,VPOS
                CALL            AG9000                                            
                MOVE            FORTY2,CMDTRAP                                        
                TRAP            MPADD2 IF ESCAPE                                        
                TRAP            MPADD2 IF F27                                         
                MOVE            ZERO,MPCOUNT         // INITIALIZE ATTENDEE COUNT
*                                                                         
.Offer the group option to the user.                                      
.                                                                         
                MOVE            TWO,PLANFLG                                          
                GOTO            MPCMD0                                              
MPADDB95        MOVE            ONE,PLANFLG                                          
                GOTO            MPADDB13                                              
*
.Get the Attendees
.
MPADDB10        MOVE            ONE,PLANFLG                                             
                MOVE            THIRTY,HPOS
                MOVE            ONE,FLAG1            // Any User
                MOVE            ZERO,FLAG4
                CALL            FINDUSER
                BRANCH          EOSFLAG TO MPADDB13  // NULL ENTRY
                COMPARE         ZERO,FLAG1
                GOTO            MPADDB11 IF EQUAL    // USER SELECTED
*
.To Backup, Delete the Work File First
.
                CALL            AG9005
                CALL            SETTOP16
                CALL            SETSW01
                DISPLAY         *HD,*EL,*P45:8,*RPTCHAR " ":10;
                GOTO            MPADDB5
*
.Check for Duplicate Requests
.
MPADDB11        MOVE            USRNO1,KEY6
                READ            SCRATCHI,KEY6;REPLY
                GOTO            MPADDB99 IF OVER
.
                KEYIN           *CLICK,*HD,*EL,*DV,ALREQ,REPLY;
                GOTO            MPADDB10
*
.Write the User Number and Name to the Work File
.
MPADDB99        DISPLAY         *P30:VPOS,USRNAME1;
                WRITE           SCRATCHI,KEY6;USRNO1,USRNAME1
.
                ADD             ONE,MPCOUNT          // INCREMENT ATTENDEE COUNT
                COMPARE         TWENTY1,VPOS                                           
                GOTO            MPADDB12 IF EQUAL
                ADD             ONE,VPOS
                GOTO            MPADDB10
*
.Screen is Full, Roll Up One Line
.
MPADDB12
                CALL            SETTOP16
                CALL            SETSW03
                DISPLAY         *HD,*R,*SETSWALL=1:24:1:80;
                GOTO            MPADDB10
*
.All Users Entered
.
MPADDB13        COMPARE         ZERO,MPCOUNT         // ANY ATTENDEES REQUESTED ?
                GOTO            MPADD2 IF ZERO       // NO
.
MPADDB14
                CALL            SETTOP14
                CALL            SETSW01
                CALL            DISPCAA
                DISPLAY         *P35:14,PLCHK,*P25:15,*RPTCHAR HB:30;
.
                MOVE            HOURSAV,HOURWRK1
                MOVE            MINSAV,MINWRK1
*
.Rewind the Work File
.
MPADDB15        REPOSIT         SCRATCHI,ZERO
*
.Get a User
.
MPADDB16        READ            SCRATCHI,SEQ;USRNO1,USRNAME1
                GOTO            MPADDB25 IF OVER
.
                MOVE            USRNO1,USRNO2
                DISPLAY         *P30:16,USRNAME1;
*
.Read His Graph Record for the Selected Date
.
                PACK            KEY WITH USRNO1,YEARWORK,JDAYWORK
                FILEPI          1;GRAPH
                READ            GRAPH,KEY;DIM11,COUNT,TABLE
                GOTO            MPADDB16 IF OVER            // He's Available
*
.See if He Is Available
.
                MOVE            HOURWRK1,HOUR
                MOVE            MINWRK1,MIN
                CALL            POSITABL
                CALL            CHECK
                GOTO            MPADDB16 IF EQUAL           // Yes, Next User
*
.He's Not Available, Find When He Is
.
MPADDB17        ADD             FIFTEEN,MINWRK1
                COMPARE         SIXTY,MINWRK1
                GOTO            MPADDB18 IF LESS
                SUB             SIXTY,MINWRK1
                ADD             ONE,HOURWRK1
*
.Is the New Time Within the Specified Window ?
.
MPADDB18        COMPARE         ENDHOUR2,HOURWRK1
                GOTO            MPADDB24 IF LESS
                GOTO            MPADDB19 IF NOT EQUAL
                COMPARE         ENDMIN2,MINWRK1
                GOTO            MPADDB24 IF LESS
                GOTO            MPADDB24 IF EQUAL
*
.The New Time is Outside the Window - Go to the Next Day
.
MPADDB19        ADD             ONE,JDAYWORK
                COMPARE         JDAYWORK,YEARLEN
                GOTO            MPADDB20 IF NOT LESS
                SUB             YEARLEN,JDAYWORK
                ADD             ONE,YEARWORK
                CALL            YEARCOMP
*
.Check the Day of the Week
.
MPADDB20        CALL            FINDOW
.
                COMPARE         SEVEN,NWORK2            // Saturday ?
                GOTO            MPADDB21 IF NOT EQUAL   // No...
                CMATCH          YES,DIM1                // Include Saturdays ?           
                GOTO            MPADDB22 IF EQUAL       // Yes...
                ADD             TWO,JDAYWORK            // Else, Bump to Monday
                GOTO            MPADDB22
.
MPADDB21        COMPARE         ONE,NWORK2              // Sunday ?
                GOTO            MPADDB22 IF NOT EQUAL   // No...
                ADD             ONE,JDAYWORK            // Bump to Monday
.
MPADDB22        COMPARE         JDAYWORK,YEARLEN
                GOTO            MPADDB23 IF NOT LESS
                SUB             YEARLEN,JDAYWORK
                ADD             ONE,YEARWORK
                CALL            YEARCOMP
*
.Reset the Times
.
MPADDB23        MOVE            HOURSAV,HOURWRK1
                MOVE            MINSAV,MINWRK1
*
.Read His Graph Record for the New Day
.
                PACK            DIM11 WITH USRNO1,YEARWORK,JDAYWORK
                FILEPI          1;GRAPH
                READ            GRAPH,DIM11;DIM11,COUNT,TABLE
                GOTO            MPADDB15 IF OVER        // Nothing For This Day
*
.See if He Can Make It Here
.
MPADDB24        MOVE            HOURWRK1,HOUR
                MOVE            MINWRK1,MIN
                CALL            POSITABL
                CALL            CHECK
                GOTO            MPADDB17 IF NOT EQUAL   // No, Try 15 Minutes Later
                GOTO            MPADDB15                // Yes, Go Try Everyone Again
*
.We Found a Time
.
MPADDB25        MOVE            HOURWRK1,HOURWORK
                MOVE            MINWRK1,MINWORK
                CALL            NICETIME
.
                CALL            JULGREG
.
                CALL            FINDOW
                LOAD            DIM11 BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
*
.See if He Wants to Schedule This Meeting
.
                DISPLAY         *P29:14,MEETAVL,*P20:15,*RPTCHAR HB:40:
                                *P22:16,*+,DIM11," - ",DATE,WAT,TIME;
.
                DISPLAY         *HD,*EL,SCHMEET;                                   
                CALL            KREPLYN                                          
                CMATCH          YES,REPLY                                          
                GOTO            MPADDB27 IF NOT EQUAL
*
.Compute the Ending Time
.
                MOVE            HOURWRK1,EHOURSAV
                ADD             MEETHOUR,EHOURSAV
                MOVE            MINWRK1,EMINSAV
                ADD             MEETMIN,EMINSAV
.
                COMPARE         SIXTY,EMINSAV
                GOTO            MPADDB26 IF LESS
.
                SUB             SIXTY,EMINSAV
                ADD             ONE,EHOURSAV
*
.Set up the Starting Time
.
MPADDB26        MOVE            HOURWRK1,HOURSAV
                MOVE            MINWRK1,MINSAV
*
.Allow Scheduling and Messages
.
                GOTO            MPADDA17
*
.See If He Wants to Continue Searching 15 Minutes Later
.
MPADDB27        MOVE            USRNO2,USRNO1
                DISPLAY         *HD,*EL,CTSRCH;                                    
                CALL            KREPLYN                                            
                CMATCH          YES,REPLY                                          
                GOTO            MPADDB28 IF NOT EQUAL
.
                CALL            SETTOP14
                CALL            SETSW01
                CALL            DISPCAA
                DISPLAY         *P35:14,PLCHK,*P25:15,*RPTCHAR HB:30;
.
                CALL            PACK01                                             
                GOTO            MPADDB17
*
.See If He Wants to Change the Search Parameters
.
MPADDB28
                DISPLAY         *HD,*EL,CHPARA;                                    
                CALL            KREPLYN                                           
                GOTO            MPADDB27 IF F5
                CMATCH          YES,REPLY                                         
                GOTO            MPADDB29 IF EQUAL
*
.Exit the Function
.
                CALL            AG9005
                GOTO            MPADD
*
.Allow Entry of Another Date/Time
.
MPADDB29        MOVE            STARTDAY,JDAYWORK
                MOVE            YEARSTR,YEARWORK
.
                DISPLAY         *HD,*EL,LITENT,SCHST,ALMSG1,PERIOD:
                                *P59:4,*RPTCHAR " ":9;
.
                MOVE            ONE,MASKSW
                MOVE            ZERO,REQFLAG
                MOVE            FORTY5,HPOS
                MOVE            FOUR,VPOS
                CALL            GETDATE
                BRANCH          FLAG1 TO MPADDB27
.
                CALL            CHECKDT
                GOTO            MPADDB29 IF NOT EQUAL
.
                CALL            FINDOW
                LOAD            DIM11 BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
                DISPLAY         *P59:4,DIM11;
*
.Get the Search Starting Time
.
MPADDB30        DISPLAY         *HD,*EL,LITENT,SCHSRCH,LITST;
.
                MOVE            HOURSAV,HOURWORK
                MOVE            MINSAV,MINWORK
                MOVE            FORTY5,HPOS
                MOVE            SIX,VPOS
                MOVE            ONE,REQFLAG                                        
                CALL            GETIME
                BRANCH          FLAG1 TO MPADDB29
.
                MOVE            HOURWORK,HOUR
                MOVE            MINWORK,MIN
*
.Get the Search Ending Time
.
MPADDB31        DISPLAY         *HD,*EL,LITENT,SCHSRCH,LITET;
.
                MOVE            EHOURSAV,HOURWORK
                MOVE            EMINSAV,MINWORK
                MOVE            FORTY5,HPOS
                MOVE            SEVEN,VPOS
                CALL            GETIME
                MOVE            ZERO,REQFLAG                                      
                BRANCH          FLAG1 TO MPADDB30
*
.Make Sure the Ending Time is After the Beginning Time
.
                CALL            CHECKEND
                BRANCH          FLAG1 TO MPADDB31
.
                MOVE            HOURWORK,ENDHOUR
                MOVE            MINWORK,ENDMIN
                MOVE            HOURWORK,ENDHOUR2
                MOVE            MINWORK,ENDMIN2
*
.Get the Meeting Duration
.
MPADDB32        KEYIN           *HD,*EL,*DV,LITENT,*DV,SCHDUR:
                                *P45:9,"__:__",*HA -5,*+,*RV,MEETHOUR;
                GOTO            MPADDB31 IF F5
.
                COMPARE         ZERO,MEETHOUR
                GOTO            MPADDB32 IF LESS
                COMPARE         TWENTY4,MEETHOUR
                GOTO            MPADDB32 IF NOT LESS
.
                KEYIN           *H 45,*DV,MEETHOUR,*H 48,*RV,MEETMIN;
                GOTO            MPADDB32 IF F5
.
                COMPARE         ZERO,MEETMIN
                GOTO            MPADDB32 IF LESS
                COMPARE         SIXTY,MEETMIN
                GOTO            MPADDB32 IF NOT LESS
                MOVE            MEETMIN,DIM2
                REP             SPACZERO,DIM2
                DISPLAY         *H 48,DIM2;
*
.Compute the Number of Blocks
.
                MOVE            MEETHOUR,NBLOCKS
                MULT            FOUR,NBLOCKS
                MOVE            MEETMIN,NWORK1
                DIV             FIFTEEN,NWORK1
                ADD             NWORK1,NBLOCKS
.
                COMPARE         ZERO,NBLOCKS
                GOTO            MPADDB32 IF EQUAL
*
.Save the Times
.
                MOVE            HOUR,HOURSAV
                MOVE            MIN,MINSAV
                MOVE            ENDHOUR,EHOURSAV
                MOVE            ENDMIN,EMINSAV
*
.Include Saturdays ?
.
MPADDB33        CMOVE           NO,DIM1                                      
                KEYIN           *P45:11,*DV,DIM1,*HA -1,*RV,DIM1;
                GOTO            MPADDB32 IF F5
.
                CMATCH          YES,DIM1                                      
                GOTO            MPADDB34 IF EQUAL
                CMATCH          NO,DIM1                                          
                GOTO            MPADDB33 IF NOT EQUAL
*
.See if the Starting Search Date is Saturday or Sunday
.
MPADDB34        CALL            FINDOW
                COMPARE         ONE,NWORK2                    // Sunday ?
                GOTO            MPADDB35 IF NOT EQUAL         // No...
                ADD             ONE,JDAYWORK                  // Position to Monday
                GOTO            MPADDB36
.
MPADDB35        COMPARE         SEVEN,NWORK2                  // Saturday ?
                GOTO            MPADDB36 IF NOT EQUAL         // No...
                CMATCH          YES,DIM1                      // Allow Saturdays ?        
                GOTO            MPADDB36 IF EQUAL             // Yes...
                ADD             TWO,JDAYWORK                  // Position to Monday
.
MPADDB36        COMPARE         JDAYWORK,YEARLEN
                GOTO            MPADDB37 IF NOT LESS
                SUB             YEARLEN,JDAYWORK
                ADD             ONE,YEARWORK
                CALL            YEARCOMP
*
.Ready the Work File
.
MPADDB37        REPOSIT         SCRATCHI,ZERO
                GOTO            MPADDB14
+..............................................................................
.
.                  M E E T I N G   L O C A T I O N   R O U T I N E
...............................................................................
.
.
MPLOC           MOVE            ONE,KEYPTR
.
                COMPARE         ONE,DTLCOUNT
                GOTO            MPLOC5 IF EQUAL   // Only One Record
                GOTO            MP$CMD1 IF LESS   // No Records...
.
                MOVE            FORTY3,CMDTRAP                                          
                TRAP            MPLOC8 IF ESCAPE                                        
                TRAP            MPLOC8 IF F27                                           
                DISPLAY         *HD,*EL,UPDWNCMD;
*
.Determine the Vertical Position
.
MPLOC2          MOVE            KEYPTR,VPOS
                ADD             FIVE,VPOS
*
.Get a Command
.
MPLOC3          KEYIN           *P2:VPOS,RA,*H 2,*+,*RV,REPLY;
                IF              UP                                                          
                CMOVE           UP,REPLY                                              
                ENDIF           
                IF              DOWN                                                           
                CMOVE           DOWN,REPLY                                            
                ENDIF          
                DISPLAY         *H 2,SPACE;
                GOTO            MPLOC5 IF EOS
.
                CMATCH          062 TO REPLY
                GOTO            MPLOC4 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            MPLOC4 IF EQUAL
                CMATCH          070,REPLY
                GOTO            MPLOC3 IF NOT EQUAL
*
.Position to the Next Higher Record
.
                SUB             ONE,KEYPTR
                GOTO            MPLOC2 IF NOT EQUAL
                MOVE            DTLCOUNT,KEYPTR
                GOTO            MPLOC2
*
.Position to the Next Lower Record
.
MPLOC4          ADD             ONE,KEYPTR
                COMPARE         KEYPTR,DTLCOUNT
                GOTO            MPLOC IF LESS     // Wrap from the End to the First
                GOTO            MPLOC2
*
.Read the Selected Record
.
MPLOC5          LOAD            KEY17 BY KEYPTR FROM KEYA,KEYB,KEYC,KEYD,KEYE,KEYF:
                                KEYG,KEYH,KEYI,KEYJ,KEYK,KEYL,KEYM,KEYN,KEYO,KEYP,KEYQ
.
                FILEPI          1;PLAN
                READ            PLAN,KEY17;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN:
                                COUNTER,USRNO2,ENDHOUR,ENDMIN,DATE,STIME,ETIME:
                                USRNAME1,LOCATION,CONFIRM,DATA
                GOTO            MPLOC7 IF OVER
*
.Display the Meeting On the Screen
.
                CALL            SETSW01
                DISPLAY         *PDATEPOS2:4,MEETDT,DATE:
                                *H SCHBYPOS,MEETSCH,USRNAME1:
                                *PSTRTPOS:6,MEETST,STIME:
                                *H LOC2POS,PLLOC2,LOCATION:
                                *PENDPOS2:8,MEETEND,ETIME:
                                *H CONFPOS,PLCON,": ",CONFIRM:
                                *PINFOPOS:10,PLINFO,DATA;
*
.Branch to the Correct Function
.
                BRANCH          BFUNC TO MPLOC7,MPCNFRM1,MPCAN1,MPLOC7
.
MPLOC7          CALL            INTERR
*
.Exit the Location Routine
.
MPLOC8          NORETURN
                GOTO            PLAN3
+..............................................................................
.
.                        C A N C E L   A   M E E T I N G
...............................................................................
.
.
MPCAN           COMPARE         ZERO,DTLCOUNT
                GOTO            MP$CMD3 IF EQUAL
                MOVE            THIRTY8,CMDTRAP                                         
                TRAP            PLAN3 IF ESCAPE                                       
                TRAP            PLAN3 IF F27                                         
                GOTO            MPLOC
*
.Check for an Already Cancelled Meeting
.
MPCAN1          MATCH           CAN,CONFIRM
                GOTO            MPCAN2 IF NOT EQUAL
.
                KEYIN           *CLICK,*HD,*EL,*DV,MEETCAN,REPLY;
                GOTO            PLAN3
*
.Only the Author May Cancel a Meeting
.
MPCAN2          COMPARE         CURRUSER,USRNO2
                GOTO            MPCAN3 IF EQUAL
.
                KEYIN           *CLICK,*HD,*EL,*DV,CANNOT,REPLY;
                GOTO            PLAN3
*
.Make Sure He Wants to Cancel It
.
MPCAN3
                DISPLAY         *HD,*EL,CANMEET;                                  
                CALL            KREPLYN                                        
                CMATCH          YES,REPLY                                         
                GOTO            PLAN3 IF NOT EQUAL
*
.Ready the Scratch File
.
                CALL            AG9000                                          
*
.Position the Meeting Planner File
.
                PACK            KEY17 WITH USRNO2,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER
                FILEPI          1;PLAN1
                READ            PLAN1,KEY17;;
.
                DISPLAY         *HD,*EL,CANMEET2;
*
.Read Through the Planner File by Author, Date, Time, & Meeting Number
.
                MOVE            ZERO,NWORK2A
MPCAN4          FILEPI          1;PLAN1
                READKS          PLAN1;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER:
                                USRNO2,ENDHOUR,ENDMIN,DATE,STIME,ETIME,USRNAME1:
                                LOCATION,CONFIRM,DATA
                GOTO            MPCAN5 IF OVER
                BRANCH          NWORK2A OF MSGMADE
.
. BUILD A PHONE MESSAGE                                               
.
                MOVE            ONE,NWORK2A
                CLEAR           MSG1
MPXT            EXTEND          MSG1
                GOTO            MPXT IF NOT EOS
                RESET           MSG1
                MOVE            MSG1,MSG2
                MOVE            MSG1,MSG3
                MOVE            MSG1,MSG4
                CLEAR           MSG1
                APPEND          PLMSG1,MSG1
                APPEND          USRNAME1,MSG1
                CLEAR           MSG2
                APPEND          PLMSG2,MSG2
                APPEND          PLMSG3,MSG2
                APPEND          LOCATION,MSG2
                RESET           MSG2
                CLEAR           MSG3
                APPEND          PLMSG4,MSG3
                CALL            JULGREG
                APPEND          DATE,MSG3
                APPEND          PLMSG5,MSG3
                MOVE            HOUR,HOURWORK
                MOVE            MIN,MINWORK
                CALL            NICETIME
                APPEND          TIME,MSG3
                APPEND          PLMSG6,MSG3
                MOVE            ENDHOUR,HOURWORK
                MOVE            ENDMIN,MINWORK
                CALL            NICETIME
                APPEND          TIME,MSG3
                APPEND          ".",MSG3
                RESET           MSG3
                CLEAR           MSG4
                APPEND          PLMSG7,MSG4
                APPEND          PLMSG8,MSG4
                RESET           MSG4
.
                PACK            KEY WITH USRNO2,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER,USRNO1 
                MOVE            KEY17,KEY17B                                 // Save Key.  
                MOVE            USRNO,USRNOSV                                // Save User. 
                PACK            KEY11 WITH USRNO,YEARWORK,JDAYWORK           // Pack new   
                FILEPI          1;GRAPH                                      // key and    
                READ            GRAPH,KEY11;USRNO,YEAR,JULDAY,COUNT,TABLE    // read file. 
                MOVE            ONE,COUNT                                                 
                PACK            KEY17 WITH USRNO,YEARWORK,JDAYWORK,HOUR,MIN,COUNT        
                FILEPI          1;AGENDA                                                  
                READ            AGENDA,KEY17;USRNO,YEARWORK,JDAYWORK,HOUR,MIN,COUNT:      
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS,SECFLAG:       
                                TFLAG,DATA             // Find planned meeting.           
                GOTO            SKIP1 IF OVER                                            
                MOVE            ONE,PLANFLAG            // We are coming from PLAN.        
                CALL            ECDEL7                  // Goto delete to delete the       
                MOVE            ZERO,PLANFLAG           // planned meeting.               
SKIP1           MOVE            KEY17B,KEY17            // Restore old key.              
                MOVE            USRNOSV,USRNO           // Restore old user.             
                GOTO            MSG1                                                    
*
.Right Author/Date/Time/Meeting ?
.
MSGMADE         PACK            KEY WITH USRNO2,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER,USRNO1
MSG1            MATCH           KEY,KEY17
                GOTO            MPCAN5 IF NOT EQUAL
*
.Save the User Number for a Possible Message
.
                COMPARE         CURRUSER,USRNO1
                GOTO            MPCAN7 IF EQUAL              // Skip Sending Ourself a Msg
.
                PACK            KEY9 WITH X02,USRNO1
                FILEPI          1;USRFILE
                READTAB         USRFILE,KEY9;*17,USRNAME1
                CALL            INTERR IF OVER
.
                DISPLAY         *H 50,USRNAME1;
                WRITE           SCRATCHI,SEQ;USRNO1,USRNAME1,CONFIRM                
*
.Update the Record
.
MPCAN7          MOVE            PLCANCEL,LOCATION
                MOVE            CAN,CONFIRM
.
                FILEPI          1;PLAN1
                UPDATAB         PLAN1;*75,LOCATION,CONFIRM
                GOTO            MPCAN4
*
.All Meeting Records Deleted - Send a Message for Sure
.
MPCAN5          WEOF            SCRATCHI,SEQ
                DISPLAY         *SETSWLR 1:79,*P54:6,*EL,PLCANCEL:
                                *P54:8,*EL,"Can",*SETSWALL=1:24:1:80;
*
. SEND A PHONE MESSAGE TO LIST
.
                REPOSIT         SCRATCHI,ZERO
                MOVE            TWO,MFUNC
                MOVE            FIVE,MSGSW           // special value for _MSG         
                GOTO            MESSAGE
+..............................................................................
.
.                       C O N F I R M   A   M E E T I N G
...............................................................................
.
.
MPCONFRM        COMPARE         ZERO,DTLCOUNT
                GOTO            MP$CMD3 IF EQUAL
                MOVE            THIRTY8,CMDTRAP
                TRAP            PLAN3 IF ESCAPE                                         
                TRAP            PLAN3 IF F27                                           
                GOTO            MPLOC
*
.Allow the Author to Check Confirmations
.
MPCNFRM1        COMPARE         CURRUSER,USRNO2
                GOTO            MPCHK1 IF EQUAL
*
.Don't Allow Confirmations of Cancelled Meetings
.
                MATCH           CAN,CONFIRM
                GOTO            MPCNFRM2 IF NOT EQUAL
.
                KEYIN           *CLICK,*HD,*EL,*DV,MEETCAN2,REPLY;
                GOTO            PLAN3
*
.Make Sure It's Not Already Confirmed
.
MPCNFRM2        CMATCH          YES,CONFIRM                                      
                GOTO            MPCNFRM3 IF NOT EQUAL
                KEYIN           *CLICK,*HD,*EL,*DV,ALCON,REPLY;
                GOTO            PLAN3
*
.Make Sure He Wants to Confirm
.
MPCNFRM3
                DISPLAY         *HD,*EL,PLCON2;
                CALL            KREPLYN
                CMATCH          YES,REPLY                                        
                GOTO            PLAN3 IF NOT EQUAL
*
.Update the Record
.
                MOVE            YES,CONFIRM
                DISPLAY         *P54:8,CONFIRM
.
                FILEPI          1;PLAN
                UPDATAB         PLAN;*95,CONFIRM
                DISPLAY         *HD,*EL,CONFMEET,*W2;
*..............................................................................
.
.Allow Addition to the Calendar
.
MPCNFRM4
                DISPLAY         *HD,*EL,ADDCAL;                                    
                CALL            KREPLYN                                           
                CMATCH          YES,REPLY                                         
                GOTO            PLAN2 IF NOT EQUAL
*
.Check for a Conflict
.
                PACK            DIM11 WITH USRNO,YEARWORK,JDAYWORK
                FILEPI          1;GRAPH
                READ            GRAPH,DIM11;DIM11,COUNT,TABLE
                GOTO            MPCNFRM5 IF OVER     No Conflict
.
                CALL            POSITABL
                CALL            COMPUTE
                CALL            CHECK
                GOTO            MPCNFRM5 IF EQUAL
*
.We Have a Schedule Conflict
.
                DISPLAY         *CLICK,*HD,*EL,SCHCONF;
                CALL            KREPLYN
                GOTO            MPCNFRM4 IF F5
                CMATCH          YES,REPLY                                              
                GOTO            PLAN2 IF NOT EQUAL
*
.Add as Tentative or Firm ?
.
MPCNFRM5        MOVE            F,TFLAG
                KEYIN           *HD,*EL,*DV,LITIST,*HA -1,*RV,TFLAG;                   
                GOTO            MPCNFRM4 IF F5
.
                CMATCH          TENTAT,TFLAG
                GOTO            MPCNFRM6 IF EQUAL
                CMATCH          FIRM,TFLAG
                GOTO            MPCNFRM5 IF NOT EQUAL
*
.Is the Appointment Information Confidential ?
.
MPCNFRM6
                DISPLAY         *HD,*EL,MEETAL;                                   
                CALL            KREPLYY                                            
                GOTO            MPCNFRM5 IF F5
.
                CMATCH          YES,REPLY                                          
                GOTO            MPCNFRM7 IF EQUAL
                CMATCH          NO,REPLY                                           
                GOTO            MPCNFRM6 IF NOT EQUAL
.
MPCNFRM7        REP             SECREP,REPLY                                         
                MOVE            REPLY,SECFLAG
*
.Add it To His Calendar
.
                CALL            POSITABL
                CALL            COMPUTE
.
                MOVE            HOUR,HOURWORK
                MOVE            MIN,MINWORK
                CALL            NICETIME
                MOVE            TIME,STIME
.
                MOVE            ENDHOUR,HOURWORK
                MOVE            ENDMIN,MINWORK
                CALL            NICETIME
                MOVE            TIME,ETIME
.
                MOVE            ZERO,COUNTER
MPCNFRM8        ADD             ONE,COUNTER
                PACK            KEY17 WITH CURRUSER,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER
.
                FILEPI          1;AGENDA
                READ            AGENDA,KEY17;REPLY
                GOTO            MPCNFRM8 IF NOT OVER
                CALL            AG1010
*
.Read the Graph Record for the Specified Date
.
                PACK            DIM11 WITH CURRUSER,YEARWORK,JDAYWORK
                FILEPI          1;GRAPH
                READ            GRAPH,DIM11;USRNO1,YEARWRK1,JDAYWRK1,COUNT,TABLE
                GOTO            MPCNFRM9 IF OVER
*
.Update the Graph Record
.
                ADD             ONE,COUNT
                CALL            ADDTABLE
.
                FILEPI          1;GRAPH
                UPDATE          GRAPH;DIM11,COUNT,TABLE
                GOTO            MPCNFR10
*
.Write the Graph Record
.
MPCNFRM9        MOVE            ONE,COUNT
                CALL            PACK01                                            
                CALL            ADDTABLE
.
                FILEPI          1;GRAPH
                WRITE           GRAPH,DIM11;DIM11,COUNT,TABLE
*
.Confirmation Complete
.
MPCNFR10        DISPLAY         *HD,*EL,MEETAPP,*W;
                GOTO            PLAN2
+..............................................................................
.
.Allow the Author to View Confirmations
.
MPCHK1          FILEPI          1;PLAN1
                READ            PLAN1,KEY17;;
.
                DISPLAY         *HD,*EL,MEETCONF:
                                *P10:12,MEETATT,*H 28,PLCON:
                                *P4:13,*RPTCHAR HB:20,*H 28,*RPTCHAR HB:9
                MOVE            FOUR,HPOS
                MOVE            ZERO,COUNT
*
.Read Through the Planner File by Author, Date, Time, & Meeting Number
.
MPCHK2          FILEPI          1;PLAN1
                READKS          PLAN1;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER:
                                USRNO2,ENDHOUR,ENDMIN,DATE,STIME,ETIME,USRNAME1:
                                LOCATION,CONFIRM,DATA
                GOTO            MPCHK4 IF OVER
*
.Right Author/Date/Time/Meeting ?
.
                PACK            KEY WITH USRNO2,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER,USRNO1
                MATCH           KEY,KEY17
                GOTO            MPCHK4 IF NOT EQUAL
*
.Look up the User's Name
.
                PACK            KEY9 WITH X02,USRNO1
                FILEPI          1;USRFILE
                READTAB         USRFILE,KEY9;*17,USRNAME1
                CALL            INTERR IF OVER
*
.Display the User & His Confirmation Flag
.
                DISPLAY         *H HPOS,USRNAME1,*HA 4,CONFIRM
                ADD             ONE,COUNT
                COMPARE         SEVNTEEN,COUNT
                GOTO            MPCHK3 IF EQUAL
                COMPARE         NINE,COUNT
                GOTO            MPCHK2 IF NOT EQUAL
*
.Switch to Left Column
.
                DISPLAY         *P50:12,MEETATT,*H 68,PLCON:
                                *P44:13,*RPTCHAR HB:20,*H 68,*RPTCHAR HB:9
                MOVE            FORTY4,HPOS
                GOTO            MPCHK2
*
.The Screen is Full
.
MPCHK3
                KEYIN           *HD,*EL,*HON,*DV,CONTPR2,*HOFF,*HD,REPLY;
                CALL            SETTOP14
                CALL            SETSW01
                DISPLAY         *HD,*EL,MEETCONF,*V 14;
                MOVE            FOUR,HPOS
                MOVE            ZERO,COUNT
                GOTO            MPCHK2
*
.All Users Displayed
.
MPCHK4          KEYIN           *HD,*EL,*HON," ",*DV,RETPR,*HOFF,*HD,REPLY;
                GOTO            PLAN3

MPGOMSG         MOVE            TWO,MSGSW
                MOVE            TWO,MFUNC
                GOTO            MESSAGE
.
DISPCAA         DISPLAY         *HD,*EL,CHKAVAIL;
                RETURN
.
. *** End ***
.
