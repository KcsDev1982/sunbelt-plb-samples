*---------------------------------------------------------------
.
. Module Name: agenda_msg.inc
. Description: Telephone Messages Module
.
. Revision History:
.
.Draw the Screen
.
MESSAGE
                MOVE            ZERO,AGENDASW
                CALL            CLOCKDT
                MOVE            ONE,RECTYPE
                COMPARE         FIVE,MSGSW           	// special value from _PLAN       
                GOTO            TMADDSKT IF EQUAL
                COMPARE         TMFLAG,ONE           	// Check to see if coming from DIR.  
                IF              EQUAL                  // If so. . .                         
                MOVE            ZERO,TMFLAG          	// Reset flag to zero if 2nd time    
                ENDIF           			// through MSG. End.                 
                DISPLAY         *ES;
.
                COMPARE         ONE,INQSW
                GOTO            MESSAGE1 IF NOT EQUAL
                DISPLAY         *HON;
.
MESSAGE1        DISPLAY         *HU,*+,USRNAME,*HOFF:
                                *H 23,ULC,*RPTCHAR HE:55,URC:
                                *P23:2,VB,*H 43,TELEMSG,*H 79,VE:
                                *P1:3,DATE,SPACE,TIME:
                                *H 23,VB,*RPTCHAR HB:55,VE:
                                *P23:4,VB,*H TOPOS,TOMSG,*H 79,VE:
                                *P23:5,VB,*H 79,VE:
                                *P23:6,VB,*H CALLPOS,CALLMSG,*H 79,VE:
                                *P23:7,VB,*H OFPOS,OFMSG,*H 79,VE:
                                *P23:8,VB,*H PHPOS,PHMSG,*H 79,VE:
                                *P23:9,VB,*RPTCHAR HB:55,VE:
                                *P23:10,VB,*H 27,MDESC1:
                                *H 51,VB,*H 55,MDESC5,*H 79,VE:
                                *P23:11,VB,*RPTCHAR HB:55,VE:
                                *P23:12,VB,*H 27,MDESC2:
                                *H 51,VB,*H 55,MDESC6,*H 79,VE:
                                *P23:13,VB,*RPTCHAR HB:55,VE:
                                *P23:14,VB,*H 27,MDESC3:
                                *H 51,VB,*H 55,MDESC7,*H 79,VE:
                                *P23:15,VB,*RPTCHAR HB:55,VE:
                                *P23:16,VB,*H 27,MDESC4:
                                *H 51,VB,*H 55,MDESC8,*H 79,VE:
                                *P23:17,VB,*RPTCHAR HB:55,VE:
                                *P23:18,VB,*H 79,VE:
                                *P23:19,VB,*H 79,VE:
                                *P23:20,VB,*H 79,VE:
                                *P23:21,VB,*H 79,VE:
                                *P23:22,LLC,*RPTCHAR HB:55,LRC:
                                *HD,*EL;
.
                BRANCH          MSGSW TO TMREV,TMADD,MT$CMD,TMREV3,TMINQ4,TMINQ4        
+..............................................................................
.
.    T E L E P H O N E   M E S S A G E S   C O M M A N D   H A N D L E R
...............................................................................
.
.
TM$CMD          NORETURN
                MOVE            ZERO,CMDTRAP                                         
                TRAP            LOGON IF ESCAPE                                     
                TRAP            LOGON IF F27                                           
                DISPLAY         *P1:3,DATE,SPACE,TIME:
                                *HD,*EL,SPACE,MFUNC2,SPACE,CFUNC8:
                                SPACE,MFUNC4,SPACE,FUNC5;
                CLEAR           FUNCDESC           // Clear the functions.                
                MOVE            ZERO,FLAG1         // Flag1 = 0                           
                CALL            CHKALRM            // Check for alarm,plan,message.       
                MOVE            ZERO,FLAG2
*
.Position to the Correct Funtion
.
TM$CMD1         LOAD            FUNCDESC BY MFUNC FROM MFUNC2,CFUNC8,MFUNC4,FUNC5
.
                MOVE            MFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           MFPOS,NWORK2
                MOVE            MFPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
TM$CMD2         DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              LEFT                                                             
                CMOVE           LEFT,REPLY                                              
                ENDIF           032
                IF              RIGHT                                                          
                CMOVE           RIGHT,REPLY                                           
                ENDIF           032
                GOTO            TM$CMD7 IF F5
                GOTO            TM$CMD7 IF F9                                        
                GOTO            TM$CMD6 IF LESS
                GOTO            TM$CMD5 IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
*
.Check for a Direction Command
.
                CMATCH          RIGHT,REPLY
                GOTO            TM$CMD3 IF EQUAL
                CMATCH          LEFT,REPLY
                GOTO            TM$CMD4 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            TM$CMD3 IF EQUAL
*
.Check for a Funtion Letter
.
                RESET           MFLETS
                SCAN            REPLY,MFLETS
                IF              NOT EQUAL                // Lower case                       
                RESET           MFLETS2                                            
                SCAN            REPLY,MFLETS2                                      
                GOTO            TM$CMD2 IF NOT EQUAL                              
                MOVEFPTR        MFLETS2,MFUNC                                      
                GOTO            TM$CMD1                                            
                ENDIF           
                MOVEFPTR        MFLETS,MFUNC
                GOTO            TM$CMD1
*
.Move Right to the Next Funtion
.
TM$CMD3         ADD             ONE,MFUNC
                COMPARE         FIVE,MFUNC
                GOTO            TM$CMD1 IF NOT EQUAL
                MOVE            ONE,MFUNC
                GOTO            TM$CMD1
*
.Move Left to the Next Funtion
.
TM$CMD4         SUB             ONE,MFUNC
                GOTO            TM$CMD1 IF NOT ZERO
                MOVE            FOUR,MFUNC
                GOTO            TM$CMD1
*
.We Have the Selected Function
.
TM$CMD5         BRANCH          MFUNC TO MT$CMD,TMADD,TMBRDCST,TMINQ
                CALL            INTERR
*
.A Timeout Occurred
.
TM$CMD6         MOVE            ZERO,FLAG1
                CALL            CHKALRM
                DISPLAY         *P1:3,DATE,SPACE,TIME;
                GOTO            TM$CMD2
*
.Help Requested
.
TM$CMD7         MOVE            THREE,HMENU
                MOVE            MFUNC,HFUNCNO
                CALL            HELP
                GOTO            MESSAGE
*.............................................................................
.
.Erase the Messages Screen
.
CLRMSGS         DISPLAY         *SETSWLR 1:22,*SETSWTB 7:22,*ES:
                                *SETSWLR 35:78,*SETSWTB 4:8,*ES,*SETSWALL=1:24:1:80:
                                *P25:10,SPACE2,MDESC1,*H 53,SPACE2,MDESC5:
                                *P25:12,SPACE2,MDESC2,*H 53,SPACE2,MDESC6:
                                *P25:14,SPACE2,MDESC3,*H 53,SPACE2,MDESC7:
                                *P25:16,SPACE2,MDESC4,*H 53,SPACE2,MDESC8:
                                *SETSWLR 26:78,*SETSWTB 18:21,*ES,*SETSWALL=1:24:1:80:
                                *HD,*EL;
                RETURN
+..............................................................................
.
.                        M E S S A G E   R E V I E W
..............................................................................
.
.
MT$CMD          MOVE            TEN,CMDTRAP                                           
                TRAP            TM$CMD IF ESCAPE                                       
                BRANCH          INQSW TO SKIP01                                       
                TRAP            TM$CMD IF F27                                         
                GOTO            SKIP02                                                
SKIP01          TRAP            TMINQ4 IF F27                                        
SKIP02          DISPLAY         *P1:3,DATE,SPACE,TIME:
                                *HD,*EL,SPACE,MTYPE1,SPACE,MTYPE2,SPACE,MTYPE3;
                MOVE            ZERO,MSGSW
*
.Position to the Correct Message Type
.
MT$CMD1         LOAD            FUNCDESC BY RECTYPE FROM MTYPE1,MTYPE2,MTYPE3
.
                MOVE            RECTYPE,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           MTPOS,NWORK2
                MOVE            MTPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
MT$CMD2         DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              LEFT                                                            
                CMOVE           LEFT,REPLY                                              
                ENDIF           
                IF              RIGHT                                                              
                CMOVE           RIGHT,REPLY                                           
                ENDIF          
                GOTO            MT$CMD6 IF F5
                GOTO            MT$CMD6 IF F9                                         
                GOTO            MT$CMD5 IF LESS
                GOTO            TMREV IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
*
.Check for a Direction Command
.
                CMATCH          RIGHT,REPLY
                GOTO            MT$CMD3 IF EQUAL
                CMATCH          LEFT,REPLY
                GOTO            MT$CMD4 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            MT$CMD3 IF EQUAL
*
.Check for a Function Letter
.
                RESET           MTLETS
                SCAN            REPLY,MTLETS
                IF              NOT EQUAL                // Lower case       
                RESET           MTLETS2                                         
                SCAN            REPLY,MTLETS2                                      
                GOTO            MT$CMD2 IF NOT EQUAL                              
                MOVEFPTR        MTLETS2,RECTYPE                                  
                GOTO            MT$CMD1                                        
                ENDIF           
                MOVEFPTR        MTLETS,RECTYPE
                GOTO            MT$CMD1
*
.Move Right to the Next Type Record
.
MT$CMD3         ADD             ONE,RECTYPE
                COMPARE         FOUR,RECTYPE
                GOTO            MT$CMD1 IF NOT EQUAL
                MOVE            ONE,RECTYPE
                GOTO            MT$CMD1
*
.Move Left to the Next Type Record
.
MT$CMD4         SUB             ONE,RECTYPE
                GOTO            MT$CMD1 IF NOT ZERO
                MOVE            THREE,RECTYPE
                GOTO            MT$CMD1
*
.A Timeout Occurred
.
MT$CMD5         MOVE            ZERO,FLAG1
                CALL            CHKALRM
                DISPLAY         *P1:3,DATE,SPACE,TIME
                GOTO            MT$CMD2
*
.Help Requested
.
MT$CMD6         MOVE            FOUR,HMENU
                MOVE            RECTYPE,HFUNCNO
                CALL            HELP
                MOVE            THREE,MSGSW
                GOTO            MESSAGE
+............................................................................
.
.If Reviewing Saved or Deleted Messages, Allow Specification of
. a Starting Date.
.
TMREV           MOVE            ZERO,YEARWORK
                MOVE            ZERO,JDAYWORK
                BRANCH          RECTYPE TO TMREV1
.
                DISPLAY         *HD,*EL,MSGREV;
                MOVE            TWENTY9,HPOS
                MOVE            TWENTY4,VPOS
                MOVE            ZERO,MASKSW
                MOVE            ZERO,REQFLAG
                CALL            GETDATE
*
.Position the Message File
.
TMREV1          PACK            KEY WITH RECTYPE,USRNO,YEARWORK,JDAYWORK
.
                FILEPI          1;MESSAGE
                READ            MESSAGE,KEY;;
*
.Reset the Counters
.
                MOVE            ZERO,MSGSW
                MOVE            ZERO,NWORK1
                MOVE            ZERO,COUNT
*
.Build a Key to Match Records With
.
TMREV2          TRAPCLR         ESCAPE                                                  
                TRAPCLR         F27                                                   
                CALL            CLOCKDT
                PACK            KEYWORK WITH RECTYPE,USRNO,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK
*
.Read Key Sequentially Through the Message File
.
                FILEPI          1;MESSAGE
                READKS          MESSAGE;FLAG1,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND:
                                DATETAKN,DOWTAKEN,TIMETAKN,TAKENBY:
                                DATESAVD,DOWSAVED,TIMESAVD,SAVEDBY:
                                CALLER,CALRINFO,PHONE:
                                FLAGS,SECFLAG,MSG1,MSG2,MSG3,MSG4
                GOTO            TMREV10 IF OVER
*
.Right Type/User/Year/Day/Hour/Minute ?
.
                PACK            KEY18 WITH FLAG1,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND
.
                MATCH           KEY18,KEYWORK
                GOTO            TMREV3 IF EQUAL
                GOTO            TMREV10 IF LESS
*
.Display the Information
.
TMREV3          CALL            CLRMSGS
                ADD             ONE,COUNT
                DISPLAY         *P5:7,*+,TAKEMSG,*PDATEPOS:8,DATEMSG,DATETAKN:
                                *PDAYPOS:9,DAYMSG,DOWTAKEN,*PTIMEPOS:10,TIMEMSG,TIMETAKN:
                                *PBYPOS:11,BYMSG,TAKENBY:
                                *P35:4,USRNAME,*P35:6,CALLER,*P35:7,CALRINFO:
                                *P35:8,PHONE;
*
.Is This a Saved or Deleted Message ?
.
                BRANCH          RECTYPE TO TMREV4
.
                LOAD            DIM7 BY RECTYPE FROM BLANKS,SAVED,DELETED
.
                DISPLAY         *P4:14,*+,DIM7,*PDATEPOS:15,DATEMSG,DATESAVD:
                                *PDAYPOS:16,DAYMSG,DOWSAVED,*PTIMEPOS:17,TIMEMSG,TIMESAVD:
                                *PBYPOS:18,BYMSG,SAVEDBY;
*
.Determine Which Message Flags are Set
.
TMREV4          SCAN            CY,FLAGS
                GOTO            TMREV8 IF NOT EQUAL
                MOVEFPTR        FLAGS,INDEX
                BUMP            FLAGS
*
.We Have a Flag That is On
.
                LOAD            MDESC BY INDEX FROM MDESC1,MDESC2,MDESC3:
                                MDESC4,MDESC5,MDESC6,MDESC7,MDESC8
*
.Determine the Flag's Screen Position
.
                COMPARE         FIVE,INDEX
                GOTO            TMREV5 IF LESS
*
.Right Side of the Screen
.
                MOVE            FIFTY5,HPOS
                MOVE            INDEX,VPOS
                SUB             FIVE,VPOS
                MULT            TWO,VPOS
                ADD             TEN,VPOS
                GOTO            TMREV6
*
.Left Side of the Screen
.
TMREV5          MOVE            TWENTY7,HPOS
                MOVE            INDEX,VPOS
                SUB             ONE,VPOS
                MULT            TWO,VPOS
                ADD             TEN,VPOS
*
.Let's Blink the Urgent Line
.
TMREV6          COMPARE         FOUR,INDEX
                GOTO            TMREV7 IF NOT EQUAL
                DISPLAY         *BLINKON;
*
.Display the Flag
.
TMREV7          DISPLAY         *PHPOS:VPOS,*HON,MDESC,*HOFF;
                COMPARE         EIGHT,INDEX
                GOTO            TMREV4 IF NOT EQUAL
*
.All Flags are Displayed; Is the Message Confidential ?
.
TMREV8          RESET           FLAGS
                COMPARE         ZERO,INQSW             // Inquiring ?
                GOTO            TMREV9 IF EQUAL        // No...
                CMATCH          STAR,SECFLAG           // Confidential ?
                GOTO            TMREV9 IF NOT EQUAL    // No...
*
.Don't Allow Inquirers to See Confidential Messages
.
                MOVE            CONMSG,MSG1
                CLEAR           MSG2
                CLEAR           MSG3
                CLEAR           MSG4
*
.Display the Message
.
TMREV9          MOVE            SECFLAG,REPLY
                REP             SECREP,REPLY
.
                DISPLAY         *P26:18,*+,REPLY,MSG1,*P27:19,MSG2:
                                *P27:20,MSG3,*P27:21,MSG4;
                GOTO            MR$CMD
*
.End of File Encountered
.
TMREV10         DISPLAY         *CLICK,*HD,*EL,NOMSG,*W2;
                DISPLAY         *P10:23,"         "                 // Erase Message  
                COMPARE         ONE,COUNT
                GOTO            TMREV11 IF NOT LESS
                CALL            CLRMSGS
                GOTO            MT$CMD
*
.Position to the Last Message of This Type for This User
.
TMREV11         CALL            CLOCKDT
                PACK            KEY18 WITH RECTYPE,USRNO,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND
.
                FILEPI          2;MESSAGE
                READ            MESSAGE,KEY18;;
                READKP          MESSAGE;FLAG1,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND:
                                DATETAKN,DOWTAKEN,TIMETAKN,TAKENBY:
                                DATESAVD,DOWSAVED,TIMESAVD,SAVEDBY:
                                CALLER,CALRINFO,PHONE:
                                FLAGS,SECFLAG,MSG1,MSG2,MSG3,MSG4
                GOTO            TMREV12 IF OVER
*
.Build the Key
.
                PACK            KEY18 WITH RECTYPE,USRNO,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND
*
.Ensure We Have the Correct User
.
                COMPARE         RECTYPE,FLAG1
                GOTO            TMREV12 IF NOT EQUAL      // Wrong Record Type
                COMPARE         USRNO,USRNO1
                GOTO            TMREV3 IF EQUAL           // Right User
*
.No Messages Found
.
TMREV12         MOVE            ZERO,COUNT
                CALL            CLRMSGS
                GOTO            MT$CMD
+..............................................................................
.
.          M E S S A G E   R E V I E W   C O M M A N D   H A N D L E R
...............................................................................
.
.
MR$CMD          NORETURN
                MOVE            ELEVEN,CMDTRAP                                         
                BRANCH          INQSW TO SKIPXX                                      
                TRAP            MR$CMD7 IF ESCAPE                                     
                TRAP            MR$CMD7 IF F27                                          
                GOTO            SKIPXY                                              
SKIPXX          TRAP            TMINQ4 IF F27                                        

SKIPXY          DISPLAY         *HD,*EL,SPACE,MRFUNC2,SPACE,MRFUNC3:
                                SPACE,MRFUNC4,SPACE,MRFUNC5,SPACE,FUNC4:
                                SPACE,MRFUNC7,SPACE,MRFUNC8,SPACE,MRFUNC9; // Add option. 
*
.Position to the Correct Function
.
MR$CMD1         LOAD            FUNCDESC BY MRFUNC FROM MRFUNC2,MRFUNC3:
                                MRFUNC4,MRFUNC5,FUNC4,MRFUNC7,MRFUNC8,MRFUNC9           
.
                MOVE            MRFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           MRPOS,NWORK2
                MOVE            MRPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
MR$CMD2         DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              LEFT                                                           
                CMOVE           LEFT,REPLY                                            
                ENDIF           032
                IF              RIGHT                                                          
                CMOVE           RIGHT,REPLY                                         
                ENDIF           032
                GOTO            MR$CMD8 IF F5
                GOTO            MR$CMD8 IF F9                                        
                GOTO            MR$CMD6 IF LESS
                GOTO            MR$CMD5 IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
*
.Check for a Direction Command
.
                CMATCH          RIGHT,REPLY
                GOTO            MR$CMD3 IF EQUAL
                CMATCH          LEFT,REPLY
                GOTO            MR$CMD4 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            MR$CMD3 IF EQUAL
*
.Check for a Function Letter
.
                RESET           MRLETS
                SCAN            REPLY,MRLETS
                IF              NOT EQUAL               // Lower Case                          
                RESET           MRLETS2                                               
                SCAN            REPLY,MRLETS2                                         
                GOTO            MR$CMD2 IF NOT EQUAL                                  
                MOVEFPTR        MRLETS2,MRFUNC                                        
                GOTO            MR$CMD1                                              
                ENDIF          

                MOVEFPTR        MRLETS,MRFUNC
                GOTO            MR$CMD1
*
.Move Right to the Next Function
.
MR$CMD3         ADD             ONE,MRFUNC
                COMPARE         NINE,MRFUNC                 // instead of eight.           
                GOTO            MR$CMD1 IF NOT EQUAL
                MOVE            ONE,MRFUNC
                GOTO            MR$CMD1
*
.Move Left to the Next Function
.
MR$CMD4         SUB             ONE,MRFUNC
                GOTO            MR$CMD1 IF NOT ZERO
                MOVE            EIGHT,MRFUNC                // instead of seven.      
                GOTO            MR$CMD1
*
.We Have a Selected Function
.
MR$CMD5         BRANCH          MRFUNC TO TMREV2,TMPREV,TMSAVE:
                                TMDEL,TMPRINT,TMROUTE,TMNOTE,TMFILE     // Added option.  
                CALL            INTERR
*
.A Timeout Occurred
.
MR$CMD6         MOVE            ONE,FLAG1                // Don't Check Messages
                CALL            CHKALRM
                DISPLAY         *P1:3,DATE,SPACE,TIME;
                GOTO            MR$CMD2
*
.Exit Requested or Timeout Occurred
.
MR$CMD7         NORETURN
                CALL            CLRMSGS
                GOTO            MT$CMD
*
.Help Requested
.
MR$CMD8         MOVE            FIVE,HMENU
                MOVE            MRFUNC,HFUNCNO
                CALL            HELP
                MOVE            FOUR,MSGSW
                GOTO            MESSAGE
+..............................................................................
.
.Read the Previous Message
.
TMPREV          TRAPCLR         ESCAPE                                   
                TRAPCLR         F27                                       
.
                COMPARE         TWO,COUNT
                GOTO            TMPREV1 IF LESS
.
                FILEPI          1;MESSAGE
                READKP          MESSAGE;FLAG1,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND:
                                DATETAKN,DOWTAKEN,TIMETAKN,TAKENBY:
                                DATESAVD,DOWSAVED,TIMESAVD,SAVEDBY:
                                CALLER,CALRINFO,PHONE:
                                FLAGS,SECFLAG,MSG1,MSG2,MSG3,MSG4
                GOTO            TMPREV1 IF OVER
*
.Right Type/User ?
.
                COMPARE         RECTYPE,FLAG1
                GOTO            TMPREV0 IF NOT EQUAL
                COMPARE         USRNO,USRNO1
                GOTO            TMPREV0 IF NOT EQUAL
.
                PACK            KEY18 WITH RECTYPE,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND
                SUB             TWO,COUNT
                GOTO            TMREV3
*
.Restore the File Position
.
TMPREV0         FILEPI          1;MESSAGE
                READKSTB        MESSAGE;REPLY
*
.Beginning of Messages of This Type
.
TMPREV1         DISPLAY         *CLICK,*HD,*EL,NOPRMSG,*W2;
                GOTO            MR$CMD
+..............................................................................
.
.Save the Message
.
TMSAVE          TRAPCLR         ESCAPE                                              
                TRAPCLR         F27                                                
                COMPARE         TWO,RECTYPE
                GOTO            TMSAVE1 IF NOT EQUAL
.
                DISPLAY         *CLICK,*HD,*EL,ALLSAVE,*W;
                GOTO            MR$CMD
*
.Set up the Date, Day, Time, and User Saving the Message
.
TMSAVE1         CALL            CLOCKDT
.
                MOVE            DATE,DATESAVD
                MOVE            TIME,TIMESAVD
.
                SCAN            SPACE,CURRNAME
                LENSET          CURRNAME
                RESET           CURRNAME
                MOVE            CURRNAME,SAVEDBY
                SETLPTR         CURRNAME,20
.
                CALL            FINDOW
                LOAD            DOWSAVED BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
.
                DISPLAY         *P4:14,*+,SAVED,*PDATEPOS:15,DATEMSG,DATESAVD:
                                *PDAYPOS:16,DAYMSG,DOWSAVED,*PTIMEPOS:17,TIMEMSG,TIMESAVD:
                                *PBYPOS:18,BYMSG,SAVEDBY;
*
.Delete the Message
.
                MOVE            KEY18,KEYWORK
.
                FILEPI          1;MESSAGE
                DELETE          MESSAGE,KEY18
                CALL            INTERR IF OVER
*
.Now, Rewrite the Message
.
TMSAVE2         CMOVE           "2",KEY18
                FILEPI          1;MESSAGE
                READTAB         MESSAGE,KEY18;DIM1
                GOTO            TMSAVE3 IF OVER
*
.Duplicate Key - Bump the Seconds by One
.
                CALL            DUPBUMP
                GOTO            TMSAVE2
*
.Write the Message
.
TMSAVE3         FILEPI          1;MESSAGE
                WRITE           MESSAGE,KEY18;KEY18,DATETAKN,DOWTAKEN,TIMETAKN,TAKENBY:
                                DATESAVD,DOWSAVED,TIMESAVD,SAVEDBY:
                                CALLER,CALRINFO,PHONE:
                                FLAGS,SECFLAG,MSG1,MSG2,MSG3,MSG4
.
                DISPLAY         *HD,*EL,SVMSG;
*
.Update the First Message Date & Time
.
                MOVE            USRNO,DIM6
                COMPARE         ONE,RECTYPE
                CALL            FMTIME IF EQUAL
*
.Reposition the Message File
.
                FILEPI          1;MESSAGE
                READ            MESSAGE,KEYWORK;;
                MOVE            ONE,MRFUNC
                SUB             ONE,COUNT
                GOTO            TMREV2
+..............................................................................
.
.Delete the Message
.
TMDEL           TRAPCLR         ESCAPE                                                  
                TRAPCLR         F27                                                  
                COUNT           NWORK1,TAKENBY
                SETLPTR         TAKENBY,NWORK1
                MATCH           TAKENBY,CURRNAME
                SETLPTR         TAKENBY
                GOTO            TMDELA IF EQUAL     // Allow the Author to Delete
                BRANCH          INQSW TO TMDEL4     // Else,  Allowed While Inquiring
*
.Check the Message Type
.
TMDELA          COMPARE         THREE,RECTYPE
                GOTO            TMDEL1 IF NOT EQUAL
.
                DISPLAY         *CLICK,*HD,*EL,ALLDEL,*W;
                GOTO            MR$CMD
*
.Flag the Deletion Date, Day, Time & User
.
TMDEL1          CALL            CLOCKDT
                CALL            FINDOW
                LOAD            DOWSAVED BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
.
                SCAN            SPACE,CURRNAME
                LENSET          CURRNAME
                RESET           CURRNAME
                MOVE            CURRNAME,SAVEDBY
                SETLPTR         CURRNAME,20
*
.Delete the Message
.
                FILEPI          1;MESSAGE
                DELETE          MESSAGE,KEY18
                CALL            INTERR IF OVER
*
.Write the Deleted Message
.
TMDEL2          CMOVE           "3",KEY18
                FILEPI          1;MESSAGE
                READTAB         MESSAGE,KEY18;REPLY
                GOTO            TMDEL3 IF OVER
*
.Duplicate Keys - Bump the Seconds by One
.
                CALL            DUPBUMP
                GOTO            TMDEL2
*
.Output the Deleted Message Record
.
TMDEL3
                FILEPI          1;MESSAGE
                WRITE           MESSAGE,KEY18;KEY18,DATETAKN,DOWTAKEN,TIMETAKN,TAKENBY:
                                DATE,DOWSAVED,TIME,SAVEDBY:
                                CALLER,CALRINFO,PHONE,FLAGS,SECFLAG:
                                MSG1,MSG2,MSG3,MSG4
.
                DISPLAY         *HD,*EL,DELMSG;
*
.Update the User's First Message Time, If Necessary
.
                MOVE            USRNO,DIM6
                COMPARE         ONE,RECTYPE
                CALL            FMTIME IF EQUAL
*
.Reposition the File
.
                MOVE            RECTYPE,REPLY
                CMOVE           REPLY,KEY18
                FILEPI          1;MESSAGE
                READ            MESSAGE,KEY18;;
                MOVE            ONE,MRFUNC
                SUB             ONE,COUNT
                GOTO            TMREV2

.Function Not Allowed While Inquiring
.
TMDEL4          KEYIN           *CLICK,*HD,*EL,*DV,FUNCNOT,REPLY;
                GOTO            MR$CMD
+.............................................................................
.
. Print the Message
.
TMPRINT         MOVE            TWELVE,CMDTRAP                                        
                TRAP            MR$CMD IF ESCAPE                                    
                TRAP            MR$CMD IF F27                                        
                MOVE            KEY18,KEYA
                MOVE            ONE,SWITCH
                MOVE            ONE,FLAG2
.
                KEYIN           *HD,*EL,*DV,PRTMSG,*HA -1,REPLY;
                GOTO            MR$CMD IF F5
                CMATCH          "A",REPLY
                GOTO            TMPRINT1 IF NOT EQUAL
*
.Position the Message File
.
                MOVE            ZERO,SWITCH
                PACK            KEY WITH RECTYPE,USRNO
.
                FILEPI          1;MESSAGE
                READ            MESSAGE,KEY;;
*
.Build a Key to Match Records With
.
                CALL            CLOCKDT
                PACK            KEYWORK WITH RECTYPE,USRNO,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK
*
.Allow Deletion as Printed If Not Inquiring or Not Printing Deleted Messages
.
                COMPARE         THREE,RECTYPE
                GOTO            TMPRINT1 IF EQUAL
                BRANCH          INQSW TO TMPRINT1
.
                DISPLAY         *HD,*EL,DELPRT;                                  
                CALL            KREPLYN                                           
                GOTO            TMPRINT IF F5
.
                CMATCH          YES,REPLY                                           
                GOTO            TMPRINT1 IF NOT EQUAL
                MOVE            ZERO,FLAG2
*
.Center the User's Name
.
TMPRINT1        DISPLAY         *HD,*EL,PRINTMG;
.
                COUNT           NWORK1,USRNAME
                MOVE            THIRTY,NWORK2
                SUB             NWORK1,NWORK2
                DIV             TWO,NWORK2
.
                MOVE            BLANKS,DIM30
                RESET           DIM30,NWORK2
                APPEND          USRNAME,DIM30
                RESET           DIM30
*
.Get the Printer
.
                CALL            SPOOL
                BRANCH          FLAG1 TO MR$CMD
                MOVE            THIRTEEN,CMDTRAP                                        
                TRAP            TMPRINT9 IF ESCAPE                                    
                TRAP            TMPRINT9 IF F27                                       
.
                BRANCH          SWITCH TO TMPRINT3
*
.Read Key Sequentially Through the Message File
.
TMPRINT2        FILEPI          1;MESSAGE
                READKS          MESSAGE;FLAG1,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND:
                                DATETAKN,DOWTAKEN,TIMETAKN,TAKENBY:
                                DATESAVD,DOWSAVED,TIMESAVD,SAVEDBY:
                                CALLER,CALRINFO,PHONE:
                                FLAGS,SECFLAG,MSG1,MSG2,MSG3,MSG4
                GOTO            TMPRINT9 IF OVER
*
.Right Type/User/Year/Day/Hour/Minute ?
.
                PACK            KEY18 WITH FLAG1,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND
.
                MATCH           KEY18,KEYWORK
                GOTO            TMPRINT3 IF EQUAL
                GOTO            TMPRINT9 IF LESS
*
.Saved or Deleted Message ?
.
TMPRINT3        LOAD            DIM7 BY RECTYPE FROM BLANKS,SAVED,DELETED
*
.Print the Heading Information for Saved or Deleted
.
                PRINT           *F,*N,*N,*32,TELEMSG:
                                *N,*39,FORMSG:
                                *N,*26,DIM30,*N,*N:
                                *N,*N,*6,RECMSG,*69,DIM7:
                                *N,*N,*3,DATEMSG,DATETAKN,*23,CALLMSG,SPACE,CALLER:
                                *65,DATEMSG,DATESAVD:
                                *N,*N,*4,DAYMSG,DOWTAKEN,*27,OFMSG,SPACE,CALRINFO:
                                *66,DAYMSG,DOWSAVED:
                                *N,*N,*3,TIMEMSG,TIMETAKN,*24,PHMSG,SPACE,PHONE:
                                *65,TIMEMSG,TIMESAVD:
                                *N,*N,*5,BYMSG,TAKENBY,*67,BYMSG,SAVEDBY:
                                *N,*N
*
.Print the Flags
.
                PRINT           *N,*7,"----------------------------------------":
                                "------------------------------"
.
                MOVE            ONE,NWORK1
                MOVE            FIVE,NWORK2
*
.Get the Two Flag Descriptions
.
TMPRINT5        LOAD            MDESC BY NWORK1 FROM MDESC1,MDESC2,MDESC3:
                                MDESC4,MDESC5,MDESC6,MDESC7,MDESC8
.
                LOAD            DIM40 BY NWORK2 FROM MDESC1,MDESC2,MDESC3:
                                MDESC4,MDESC5,MDESC6,MDESC7,MDESC8
.
                RESET           FLAGS,NWORK1
                MOVE            FLAGS,DIM1
                REP             "N YX",DIM1
.
                RESET           FLAGS,NWORK2
                MOVE            FLAGS,REPLY
                REP             "N YX",REPLY
.
                PRINT           *7,"|",*37,"|   |",*72,"|   |",*N:
                                *7,"|",*14,MDESC,*37,"| ",DIM1," |":
                                *48,DIM40,*72,"| ",REPLY," |":
                                *N,*7,"----------------------------------------":
                                "------------------------------"
.
                ADD             ONE,NWORK2
                ADD             ONE,NWORK1
                COMPARE         FIVE,NWORK1
                GOTO            TMPRINT5 IF NOT EQUAL
*
.Is the Message Confidential ?
.
                COMPARE         ZERO,INQSW              // Are We Inquiring ?
                GOTO            TMPRINT6 IF EQUAL       // No...
                CMATCH          STAR,SECFLAG            // Confidential Message ?
                GOTO            TMPRINT6 IF NOT EQUAL   // No...
*
.Don't Let Then See the Confidential message
.
                MOVE            CONMSG,MSG1
                CLEAR           MSG2
                CLEAR           MSG3
                CLEAR           MSG4
*
.Print the Text of the Message
.
TMPRINT6        REP             SECREP,SECFLAG
.
                PRINT           *N,*N,*N,*N,*35,MSGDS,*N,*N:
                                *N,*15,SECFLAG,MSG1,*N,*N,*16,MSG2:
                                *N,*N,*16,MSG3,*N,*N,*16,MSG4
*
.Print All Messages of This Type ?
.
                BRANCH          SWITCH TO TMPRINT9
*
.Deleting as We Print ?
.
                BRANCH          FLAG2 TO TMPRINT2
*
.Flag the Deletion Date, Day, Time & User
.
                CALL            CLOCKDT
                CALL            FINDOW
                LOAD            DOWSAVED BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
.
                SCAN            SPACE,CURRNAME
                LENSET          CURRNAME
                RESET           CURRNAME
                MOVE            CURRNAME,SAVEDBY
                SETLPTR         CURRNAME,20
*
.Delete the Message
.
                FILEPI          1;MESSAGE
                DELETE          MESSAGE,KEY18
                CALL            INTERR IF OVER
*
.Write the Deleted Message
.
TMPRINT7        CMOVE           "3",KEY18
                FILEPI          1;MESSAGE
                READTAB         MESSAGE,KEY18;REPLY
                GOTO            TMPRINT8 IF OVER
                CALL            DUPBUMP
                GOTO            TMPRINT7
*
.Output the Deleted Message Record
.
TMPRINT8        FILEPI          1;MESSAGE
                WRITE           MESSAGE,KEY18;KEY18,DATETAKN,DOWTAKEN,TIMETAKN,TAKENBY:
                                DATE,DOWSAVED,TIME,SAVEDBY:
                                CALLER,CALRINFO,PHONE,FLAGS,SECFLAG:
                                MSG1,MSG2,MSG3,MSG4
*
.Update the User's First Message Time, If Necessary
.
                MOVE            USRNO,DIM6
                COMPARE         ONE,RECTYPE
                CALL            FMTIME IF EQUAL
*
.Reposition the File
.
                MOVE            RECTYPE,REPLY
                CMOVE           REPLY,KEY18
                FILEPI          1;MESSAGE
                READ            MESSAGE,KEY18;;
                MOVE            ONE,MRFUNC
                SUB             ONE,COUNT
                GOTO            TMPRINT2
*
.Printing Complete
.
TMPRINT9        NORETURN
                RELEASE
                SPLCLOSE
                MOVE            KEYA,KEY18
.
                DISPLAY         *CLICK,*HD,*EL,PRTCMPL,*W;
                BRANCH          SWITCH TO MR$CMD
                CALL            CLRMSGS
                GOTO            MT$CMD
+..............................................................................
.
.Forward a Copy of the Message
..
TMROUTE         BRANCH          INQSW TO TMDEL4      // Not Allowed While Inquiring
                CALL            AG9000                                           
                MOVE            ZERO,NWORK2
                MOVE            FOURTEEN,CMDTRAP                                        
                TRAP            TMROUT11 IF ESCAPE                                    
                TRAP            TMROUT11 IF F27                                        
*
.Get the New Recipients
.
TMROUT1         MOVE            ZERO,FLAG4
TMROUTE1        MOVE            THIRTY5,HPOS            // Horizontal Screen Position
                MOVE            FOUR,VPOS            // Vertical Screen Position
                MOVE            ONE,FLAG1            // Allow Any User
                CALL            FINDUSER
                BRANCH          EOSFLAG TO TMROUTEB  // Null Entry
                BRANCH          FLAG1 TO TMROUT11    // Abort Requested (Var's Indeterminate)
                DISPLAY         *P35:4,USRNAME1;     // User Name Selected
.
                MOVE            USRNO1,KEY6          // User Number Selected
                READ            SCRATCHI,KEY6;REPLY
                GOTO            TMROUTE1 IF NOT OVER
                WRITE           SCRATCHI,KEY6;USRNO1,USRNAME1
                ADD             ONE,NWORK2
                MOVE            ONE,FLAG4
                GOTO            TMROUTE1
*
.Any Users Selected ?
.
TMROUTEB        COMPARE         ZERO,NWORK2
                GOTO            TMROUT11 IF EQUAL
                BRANCH          NWORK2 TO TMROUTED
                DISPLAY         *P35:4,USRMSG;
                GOTO            TMROUTE2
.
TMROUTED        DISPLAY         *P35:4,USRNAME1;
*
.Allow the Addition of a Note
.
TMROUTE2        KEYIN           *HD,*EL,*DV,NOTEMSG2:
                                *P27:21,*RPTCHAR "_":50,*H 27,*IT,*RV,MSG4;
                DISPLAY         *IN,*H 27,MSG4
                GOTO            TMROUT1 IF F5                                          
*
.See if the Message is Confidential
.
TMROUTE3        MOVE            SECFLAG,REPLY
                REP             SPSTREP,REPLY
                KEYIN           *HD,*EL,*DV,ALLOWMG:
                                *DV,REPLY,*HA -1,*RV,REPLY;
                GOTO            TMROUTE2 IF F5
.
                CMATCH          YES,REPLY                                            
                GOTO            TMROUTE4 IF EQUAL
                CMATCH          NO,REPLY                                            
                GOTO            TMROUTE3 IF NOT EQUAL
.
TMROUTE4        MOVE            REPLY,SECFLAG
                REP             SECREP,SECFLAG
                DISPLAY         *P26:18,SECFLAG;
*
.Foward the Message
.
                TRAPCLR         ESCAPE                                                 
                TRAPCLR         F27                                                   
                MOVE            KEY18,DIM20
*
.Make the Current User the Message Taker
.
                RESET           CURRNAME
                SCAN            SPACE,CURRNAME
                LENSET          CURRNAME
                RESET           CURRNAME
                MOVE            CURRNAME,TAKENBY
                SETLPTR         CURRNAME,20
.
                CALL            CLOCKDT
                CALL            FINDOW
                LOAD            DOWTAKEN BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
.
                MOVE            BLANKS,DATESAVD
                MOVE            BLANKS,DOWSAVED
                MOVE            BLANKS,TIMESAVD
                MOVE            BLANKS,SAVEDBY
.
                REPOSIT         SCRATCHI,ZERO
*
.Foward the Message to the New User
.
TMROUTE9        READ            SCRATCHI,SEQ;USRNO1,USRNAME1
                GOTO            TMROUTEC IF OVER
                DISPLAY         *P50:24,USRNAME1;
.
                PACK            KEY18 WITH ONE,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND
.
                FILEPI          1;MESSAGE
                READTAB         MESSAGE,KEY18;REPLY
                GOTO            TMROUT10 IF OVER
*
.Duplicate Keys - Bump the Seconds by One
.
                ADD             ONE,SECOND
                GOTO            TMROUTE9
*
.Write the Record
.
TMROUT10        FILEPI          1;MESSAGE
                WRITE           MESSAGE,KEY18;KEY18,DATE,DOWTAKEN,TIME,TAKENBY:
                                DATESAVD,DOWSAVED,TIMESAVD,SAVEDBY:
                                CALLER,CALRINFO,PHONE,FLAGS:
                                SECFLAG,MSG1,MSG2,MSG3,MSG4
.
                MOVE            USRNO1,DIM6
                CALL            FMTIME
                GOTO            TMROUTE9
*
.All Copies Fowarded
.
TMROUTEC        DISPLAY         *HD,*EL,MSGFOR;
                CALL            AG9005
*
.Restore the Message File Position
.
                MOVE            DIM20,KEY18
                FILEPI          1;MESSAGE
                READ            MESSAGE,KEY18;REPLY
                CALL            INTERR IF OVER
                GOTO            MR$CMD
*
.Abort the Forward Function
.
TMROUT11        NORETURN
                CALL            AG9005
                CLEAR           KEY18
                MOVE            THIRTY38,NWORK1
.
                FILEPI          1;MESSAGE
                READTAB         MESSAGE,KEY18;KEY18,*187,SECFLAG,*NWORK1,MSG4
                CALL            INTERR IF OVER
.
                DISPLAY         *SETSWLR 1:78,*P35:4,*EL,*SETSWALL=1:24:1:80,*P35:4,USRNAME:
                                *P26:19,SECFLAG,*P27:21,MSG4;                          
                GOTO            MR$CMD
+..............................................................................
.
.Add a Remark to a Message
.
TMNOTE          BRANCH          INQSW TO TMDEL4
                MOVE            FIFTEEN,CMDTRAP                                        
                TRAP            TMNOTE6 IF ESCAPE                                     
                TRAP            TMNOTE6 IF F27                                          
.
                KEYIN           *HD,*EL,*DV,ENTREM:
                                *P27:21,*RPTCHAR "_":50,*H 27,*IT,*RV,MSG4;
                DISPLAY         *IN,*H 27,MSG4;
                GOTO            TMNOTE6 IF F5
*
.Allow Changing the Confidential Flag
.
TMNOTE1         MOVE            SECFLAG,REPLY
                REP             SPSTREP,REPLY
                DISPLAY         *HD,*EL,ALLOWMG;
                CALL            KREPLYY
                GOTO            TMNOTE IF F5
.
                CMATCH          YES,REPLY                                              
                GOTO            TMNOTE2 IF EQUAL
                CMATCH          NO,REPLY                                               
                GOTO            TMNOTE1 IF NOT EQUAL
.
TMNOTE2         MOVE            REPLY,SECFLAG
                REP             SECREP,SECFLAG
                DISPLAY         *P26:18,SECFLAG;
*
.Delete & Rewrite the Message
.
                TRAPCLR         ESCAPE                                                
                TRAPCLR         F27                                                   
                FILEPI          1;MESSAGE
                DELETE          MESSAGE,KEY18
                CALL            INTERR IF OVER
*
.Check for Duplicate Keys
.
TMNOTE4         FILEPI          1;MESSAGE
                READTAB         MESSAGE,KEY18;REPLY
                GOTO            TMNOTE5 IF OVER
*
.Duplicate Keys - Bump the Seconds by One
.
                CALL            DUPBUMP
                GOTO            TMNOTE4
*
.Output the Message Record
.
TMNOTE5         FILEPI          1;MESSAGE
                WRITE           MESSAGE,KEY18;KEY18,DATETAKN,DOWTAKEN,TIMETAKN,TAKENBY:
                                DATESAVD,DOWSAVED,TIMESAVD,SAVEDBY:
                                CALLER,CALRINFO,PHONE,FLAGS:
                                SECFLAG,MSG1,MSG2,MSG3,MSG4
.
                DISPLAY         *HD,*EL,REMADD;
                GOTO            MR$CMD
*
.Abort Changing the Message Note
.
TMNOTE6         NORETURN
                CLEAR           KEY18
                MOVE            THIRTY38,NWORK1
                FILEPI          1;MESSAGE
                READTAB         MESSAGE,KEY18;*NWORK1,MSG4;
                DISPLAY         *P27:21,MSG4;
                GOTO            MR$CMD
+...............................................................................
.                                                                              .
.                     M E S S A G E   F I L E   T O   D I R E C T O R Y        .
.  This added code sets the flag to tell the Directory module that we are      .
.  from MSG and then calls the module. The Directory module will send          .
.  us back to the top after it is finished.                                    .
.                                                                              .
................................................................................
.
TMFILE
                TRAP            MR$CMD IF F27                                            
                MOVE            ONE,TMFLAG                                               
                GOTO            TD$CMD                                                  
+.............................................................................
.
.                     M E S S A G E   A D D I T I O N
..............................................................................
.
.
.Disallow During Inquiry
.
TMADD
                BRANCH          INQSW TO TMADD32
                COMPARE         TWO,MSGSW             // If you abort out of sending a   
                GOTO            TMADDSKT IF EQUAL     // message & use CMD key...        
                MOVE            SIXTEEN,CMDTRAP                                      
                TRAP            TMADD33 IF ESCAPE                                   
                TRAP            TMADD33 IF F27                                        
*
.Initialize the Fields
.
TMADDSKT
                UNPACK          BLANKS INTO DATESAVD,DOWSAVED,TIMESAVD,SAVEDBY,CALRINFO
                MOVE            ZERO,SWITCH
                MOVE            ONE,FLAG2
.
                MOVE            BLANKS TO FLAGS                                   
                REPLACE         BN IN FLAGS                                        
                COMPARE         FIVE,MSGSW           // special PLAN CANCEL            
                GOTO            TMADD3 IF EQUAL
                UNPACK          BLANKS INTO MSG1,MSG2,MSG3,MSG4
*
.Entered from the Broadcast or Planning Funtion ?
.
                COMPARE         TWO,MSGSW
                GOTO            TMADD2 IF EQUAL
                COMPARE         FOUR,MSGSW
                GOTO            TMADD2 IF EQUAL
*
.Get the Recipient's Name
.
                MOVE            THIRTY5,HPOS
                MOVE            FOUR,VPOS
                MOVE            ONE,FLAG1               // Any user
                MOVE            ZERO,FLAG4
                CALL            FINDUSER
                BRANCH          EOSFLAG TO TMADD33
                BRANCH          FLAG1 TO TMADD33
                DISPLAY         *P35:4,USRNAME1,PAROP,STATFLAG,PARCL,EXTPH,USREXT
.                                // Added on Telephone EXT. and Usr Status.  
                GOTO            TMADD3
*
.Entry Point for Adding Messages Through the Planning Funtion
.
TMADD2          DISPLAY         *SETSWLR 1:78,*P35:4,*EL,SPUSRS,*SETSWALL=1:24:1:80;
*
.Get the Current Time and Date
.
TMADD3          CALL            CLOCKDT
                MOVE            CURRNAME,CALLER      // _PLAN CANCEL                   
.
                SCAN            SPACE,CURRNAME
                LENSET          CURRNAME
                RESET           CURRNAME
                MOVE            CURRNAME,TAKENBY
                SETLPTR         CURRNAME,20
.
                CALL            FINDOW
                LOAD            DOWTAKEN BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
                MOVE            TIME,TIMETAKN
                MOVE            DATE,DATETAKN
.
                COMPARE         FIVE,MSGSW           // _PLAN CANCEL
                GOTO            TMADD8 IF EQUAL
                DISPLAY         *P5:7,*+,TAKEMSG,*PDATEPOS:8,DATEMSG,DATE:
                                *PDAYPOS:9,DAYMSG,DOWTAKEN,*PTIMEPOS:10,TIMEMSG,TIME:
                                *PBYPOS:11,BYMSG,TAKENBY;
                GOTO            TMADD6               // Don't go into date/time        
*
.Allow Changing the Date
.
TMADD4          DISPLAY         *HD,*EL,LITENT,DTTKN;
                MOVE            SEVEN,HPOS
                MOVE            EIGHT,VPOS
                MOVE            ONE,MASKSW
                MOVE            ZERO,REQFLAG
                CALL            GETDATE
.
                BRANCH          FLAG1 TO TMADD
.
                MOVE            DATE,DATETAKN
                CALL            FINDOW
                LOAD            DOWTAKEN BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
.
                DISPLAY         *P7:9,*RPTCHAR " ":9,*H 7,*+,DOWTAKEN;
*
.Allow Changing the Time
.
                DISPLAY         *HD,*EL,LITENT,TMTKN;
                MOVE            SEVEN,HPOS
                MOVE            TEN,VPOS
                CALL            GETIME
                BRANCH          FLAG1 TO TMADD4
                MOVE            TIME,TIMETAKN
*
.Get the Caller's Name
.
TMADD6          KEYIN           *HD,*EL,*DV,LITENT,*DV,CALLENT:
                                *P35:6,*RPTCHAR "_":30,*H 35,*IT,CALLER;
                DISPLAY         *IN,*H 35,CALLER;
                GOTO            TMADD4 IF F5                                          
.
                CMATCH          " ",CALLER
                GOTO            TMADD6 IF EQUAL
                GOTO            TMADD7 IF NOT EOS
                MOVE            USRNAME TO CALLER
                DISPLAY         *IN,*H 35,CALLER;
*
.Allow a 2nd Line of Information
.
TMADD7          KEYIN           *HD,*EL,*DV,ENTADD:
                                *P35:7,*RPTCHAR "_":30,*H 35,*IT,CALRINFO;
                DISPLAY         *IN,*H 35,CALRINFO;
                GOTO            TMADD6 IF F5
*
.Get the Caller's Phone Number
.
TMADD8          COMPARE         FIVE,MSGSW           // _PLAN CANCEL                   
                GOTO            TMADD8A IF NOT EQUAL
                MOVE            CURREXT,PHONE
                GOTO            TMADD30
TMADD8A         KEYIN           *HD,*EL,*DV,LITENT,*DV,CALLPH:
                                *P35:8,*RPTCHAR "_":20,*H 35,PHONE;
                DISPLAY         *H 35,PHONE;
                GOTO            TMADD7 IF F5
*
.Set the Correct Flags
.
                MOVE            ONE,INDEX
TMADD9   	DISPLAY   	*HD,*EL,"Press Space to Highlight or Enter Key When Done.";
*
.Determine the Flag's Screen Position
.
TMADD10         COMPARE         FIVE,INDEX
                GOTO            TMADD11 IF LESS
*
.Right Side of the Screen
.
                MOVE            FIFTY5,HPOS
                MOVE            INDEX,VPOS
                SUB             FIVE,VPOS
                MULT            TWO,VPOS
                ADD             TEN,VPOS
                GOTO            TMADD12
*
.Left Side of the Screen
.
TMADD11         MOVE            TWENTY7,HPOS
                MOVE            INDEX,VPOS
                SUB             ONE,VPOS
                MULT            TWO,VPOS
                ADD             TEN,VPOS
*
.Get a Command
.
TMADD12         KEYIN           *PHPOS:VPOS,*HA -2,RA,*HA -1,*+,REPLY;
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
                IF              F18                                                          
                MOVE            FIVE,REPLY                                          
                ENDIF           
                DISPLAY         *H HPOS,*HA -2,SPACE;
                GOTO            TMADD8 IF F5
                GOTO            TMADD8 IF F9                                        
.
                BUMP            REPLY,0
                GOTO            TMADD20 IF EOS
.
                REP             "6183 5",REPLY
                MOVE            REPLY,NWORK1
                BRANCH          NWORK1 TO TMADD13,TMADD14,TMADD15,TMADD16,TMADD17
                GOTO            TMADD12
*
.Move Right
.
TMADD13         ADD             FOUR,INDEX
                COMPARE         NINE,INDEX
                GOTO            TMADD10 IF LESS
                SUB             EIGHT,INDEX
                GOTO            TMADD10
*
.Move Down
.
TMADD14         ADD             ONE,INDEX
                COMPARE         NINE,INDEX
                GOTO            TMADD10 IF LESS
                MOVE            ONE,INDEX
                GOTO            TMADD10
*
.Move Up
.
TMADD15         SUB             ONE,INDEX
                GOTO            TMADD10 IF NOT EQUAL
                MOVE            EIGHT,INDEX
                GOTO            TMADD10
*
.Move Left
.
TMADD16         SUB             FOUR,INDEX
                COMPARE         ONE,INDEX
                GOTO            TMADD10 IF NOT LESS
                ADD             EIGHT,INDEX
                GOTO            TMADD10
*
.Turn the Flag On or Off as Needed
.
TMADD17         LOAD            MDESC BY INDEX FROM MDESC1,MDESC2,MDESC3:
                                MDESC4,MDESC5,MDESC6,MDESC7,MDESC8
.
                RESET           FLAGS,INDEX
                CMATCH          CN,FLAGS
                GOTO            TMADD18 IF EQUAL
.
                CMOVE           CN,FLAGS
                DISPLAY         *HOFF;
                GOTO            TMADD19
.
TMADD18         CMOVE           CY,FLAGS
                DISPLAY         *HON;
                COMPARE         FOUR,INDEX
                GOTO            TMADD19 IF NOT EQUAL
                DISPLAY         *BLINKON;
.
TMADD19         RESET           FLAGS
                DISPLAY         *PHPOS:VPOS,MDESC,*HOFF;
                GOTO            TMADD10
*
.Get the 1st Line of the Message
.
TMADD20         CLEAR           MSG2
                CLEAR           MSG3
                CLEAR           MSG4
                KEYIN           *HD,*EL,*DV,LITENT,*DV,MSGPER,*P27:18,*IT,MSG1;
                DISPLAY         *IN,*H 27,MSG1;
                GOTO            TMADD9 IF F5
.
                BUMP            MSG1,0
                GOTO            TMADD27 IF EOS
*
.Get the 2nd Line of the Message
.
TMADD21         KEYIN           *P27:19,*IT,MSG2;
                DISPLAY         *IN,*H 27,MSG2;
                GOTO            TMADD20 IF F5
.
                BUMP            MSG2,0
                GOTO            TMADD25 IF EOS
*
.Get the 3rd Line of the Message
.
TMADD22         KEYIN           *P27:20,*IT,MSG3;
                DISPLAY         *IN,*H 27,MSG3;
                GOTO            TMADD21 IF F5
.
                BUMP            MSG3,0
                GOTO            TMADD25 IF EOS
*
.See if the Message Should Be Continued
.
TMADD23
                DISPLAY         *HD,*EL,CNTMSG;                                   
                CALL            KREPLYN                                            
                GOTO            TMADD22 IF F5
.
                CLEAR           MSG4
                CMATCH          YES,REPLY                                           
                GOTO            TMADD24 IF NOT EQUAL
                MOVE            CONTINUE,MSG4
                MOVE            ZERO,FLAG2
.
TMADD24         DISPLAY         *P27:21,MSG4;
*
.See If It's Confidential
.
TMADD25         BRANCH          SWITCH TO TMADD27          // Already Asked...
.
                DISPLAY         *HD,*EL,ALLOWMG;                                   
                CALL            KREPLYY                                           
                GOTO            TMADD23 IF F5
.
                CMATCH          YES,REPLY                                           
                GOTO            TMADD26 IF EQUAL
                CMATCH          NO,REPLY                                           
                GOTO            TMADD25 IF NOT EQUAL
.
TMADD26         MOVE            ONE,SWITCH
                MOVE            REPLY,SECFLAG
                REP             SECREP,SECFLAG
                DISPLAY         *P26:18,SECFLAG;
*
.Write the Message to Disk
.
TMADD27         DISPLAY         *HD,*EL,SNDMSG;                                     
                CALL            KREPLYY                                             
                CMATCH          YES,REPLY                                    
                GOTO            TD27A IF EQUAL                                     
                GOTO            TMADD20                                          

TD27A           COMPARE         TWO,MSGSW                                           
                GOTO            TMADD30 IF EQUAL        // Adding to Many Users
                COMPARE         FIVE,MSGSW           // _PLAN CANCEL
                GOTO            TMADD30 IF EQUAL

                MOVE            ZERO,USRNO2
                COMPARE         FOUR,MSGSW
                GOTO            TMADD30 IF EQUAL
.
                MOVE            ZERO,SECOND
TMADD28         ADD             ONE,SECOND
                PACK            KEY18 WITH ONE,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND
.
                FILEPI          3;MESSAGE
                READ            MESSAGE,KEY18;;
                GOTO            TMADD28 IF NOT OVER
.
                WRITE           MESSAGE,KEY18;KEY18,DATETAKN,DOWTAKEN,TIMETAKN,TAKENBY:
                                DATESAVD,DOWSAVED,TIMESAVD,SAVEDBY:
                                CALLER,CALRINFO,PHONE,FLAGS:
                                SECFLAG,MSG1,MSG2,MSG3,MSG4
*
.If Continued Message, Loop Back for More
.
                BRANCH          FLAG2 TO TMADD29
.
                MOVE            ONE,FLAG2
                DISPLAY         *SETSWTB 18:21,*SETSWLR 27:78,*ES,*SETSWALL=1:24:1:80;
                GOTO            TMADD20
*
.Update the Receipent's First Message Date/Time if Necessary
.
TMADD29         DISPLAY         *HD,*EL,ADDMSGS;
                MOVE            USRNO1,DIM6
                CALL            FMTIME
*
.Erase the Screen and Continue Taking Messages
.
                CALL            CLRMSGS
                GOTO            TMADD
*
.Add the Message to All Attendees' File
.
TMADD30         READ            SCRATCHI,SEQ;USRNO1,USRNAME1,CONFIRM            
                GOTO            TMADD34 IF OVER
*
.Skip Duplicates
.
                COMPARE         USRNO1,USRNO2
                GOTO            TMADD30 IF EQUAL
                CMATCH          NO,CONFIRM                                  
                IF              EQUAL                                                 
                UPDATAB         USRFILE;*91,ZERO                               
                GOTO            TMADD30                                           
                ENDIF           
                MOVE            USRNO1,USRNO2
*
.Add the Message
.
                DISPLAY         *HD,*EL,*H 50,USRNAME1;
.
                MOVE            ZERO,SECOND
TMADD31         ADD             ONE,SECOND
                PACK            KEY18 WITH ONE,USRNO1,YEARWORK,JDAYWORK:
                                HOURWORK,MINWORK,SECOND
.
                FILEPI          3;MESSAGE
                READ            MESSAGE,KEY18;;
                GOTO            TMADD31 IF NOT OVER
.
                WRITE           MESSAGE,KEY18;KEY18,DATETAKN,DOWTAKEN,TIMETAKN,TAKENBY:
                                DATESAVD,DOWSAVED,TIMESAVD,SAVEDBY:
                                CALLER,CALRINFO,PHONE,FLAGS:
                                SECFLAG,MSG1,MSG2,MSG3,MSG4
                COMPARE         FIVE,MSGSW           // special value from _PLAN     
                GOTO            TMADD30 IF EQUAL
*
.Update the Receipent's First Message Date/Time if Necessary
.
                MOVE            USRNO1,DIM6
                CALL            FMTIME
                GOTO            TMADD30
*
.Addition Not Allowed While Inquiring
.
TMADD32         KEYIN           *CLICK,*HD,*EL,*DV,FUNCNOT,REPLY;
                GOTO            TM$CMD
*
.Abort the Message Addition Routine
.
TMADD33         NORETURN
                CALL            CLRMSGS
                COMPARE         FOUR,MSGSW
                GOTO            TM$CMD IF NOT EQUAL
                CALL            AG9005
                MOVE            ZERO,MSGSW
                GOTO            TM$CMD
*
.Message Added to All Users, Continued Message ?
.
TMADD34         COMPARE         FIVE,MSGSW           // _PLAN CANCEL
                GOTO            MPADD2 IF EQUAL
                BRANCH          FLAG2 TO TMADD35       // No...
.
                DISPLAY         *SETSWTB 18:21,*SETSWLR 27:78,*ES,*SETSWALL=1:24:1:80;
                REPOSIT         SCRATCHI,ZERO
                MOVE            ONE,FLAG2
                CLEAR           MSG1
                CLEAR           MSG2
                CLEAR           MSG3
                GOTO            TMADD20
*
.Return to the Planning Function
.
TMADD35         DISPLAY         *HD,*EL,ADDMSGS,*W;
.
                COMPARE         TWO,MSGSW
                GOTO            TMADD36 IF NOT EQUAL
                COMPARE         THREE,BFUNC              // Planning Deletion Function ?   *dsh
                GOTO            PLAN2 IF EQUAL           // Yes...
                GOTO            MPADDA24                 // Plan Scheduling Function
.
TMADD36         CALL            CLRMSGS
                MOVE            ZERO,MSGSW
                CALL            AG9005
                GOTO            TM$CMD
+..............................................................................
.
.                      M E S S A G E   B R O A D C A S T
...............................................................................
.
.
TMBRDCST        BRANCH          INQSW TO TMADD32
.
                CALL            AG9000                                            
                MOVE            SEVNTEEN,CMDTRAP                                     
                TRAP            TMBCST11 IF ESCAPE                                 
                TRAP            TMBCST11 IF F27                                    
                MOVE            ZERO,NWORK1
.
TMBCAST1        KEYIN           *HD,*EL,*DV,LITENT,*DV,GRPMSG:
                                *P35:4,*RPTCHAR " ":20,*H 35,*RPTCHAR "_":6,*H 35,DIM6;
                GOTO            TMBCST11 IF F5
.
                CMATCH          " ",DIM6
                GOTO            TMBCAST1 IF EQUAL
*
.See If He Wants the Entire Group or Pick & Choose
.
                DISPLAY         *HD,*EL,SELUSR;                                  
                CALL            KREPLYN                                         
                GOTO            TMBCAST1 IF F5
.
                REP             SELREP,REPLY
                MOVE            ZERO,INDEX
                MOVE            REPLY,INDEX
*
.Branch to the Correct Routine
.
                BUMP            DIM6,0
                GOTO            TMBCAST7 IF EOS
*
.Pull All Users for the Specified Group
.
                PACK            AKEY2 WITH L04,DIM6
.
                TRAP            TMBCAST2 IF IO
                FILEPI          1;USRFILE
                READTAB         USRFILE,AKEY2;*11,USRNO1,USRNAME1
                TRAPCLR         IO
                GOTO            TMBCAST4 IF NOT OVER
.
                KEYIN           *CLICK,*HD,*EL,*DV,SPGRP,REPLY;
                GOTO            TMBCAST1
*
.Invalid Key Specification
.
TMBCAST2        NORETURN
                KEYIN           *CLICK,*HD,*EL,*DV,INGRP,REPLY;
                GOTO            TMBCAST1
*
.Read Generically Through the File
.
TMBCAST3        FILEPI          1;USRFILE
                READKGTB        USRFILE;*11,USRNO1,USRNAME1
                GOTO            TMBCAST6 IF OVER
*
.Include This User ?
.
TMBCAST4        DISPLAY         *P35:4,USRNAME1;
                BRANCH          INDEX TO TMBCAST5            // All Users Selected
.
                DISPLAY         *HD,*EL,INCUSR;                                    
                CALL            KREPLYN                                          
                GOTO            TMBCAST1 IF F5
                CMATCH          YES,REPLY                                          
                GOTO            TMBCAST3 IF NOT EQUAL
*
.Write the Info to the Work File
.
TMBCAST5        CALL            TMBCST93
                GOTO            TMBCAST3
*
.Allow Multiple Specifications
.
TMBCAST6
                DISPLAY         *HD,*EL,MOREUSR;                                  
                CALL            KREPLYN                                           
                CMATCH          YES,REPLY                                        
                GOTO            TMBCAST1 IF EQUAL
.
                COMPARE         ZERO,NWORK1
                GOTO            TMBCST10 IF EQUAL    // No User's Selected
*
.Go to Message Addition
.
                WEOF            SCRATCHI,SEQ
                REPOSIT         SCRATCHI,ZERO
                MOVE            FOUR,MSGSW
                GOTO            TMADD
*
.Broadcast the Message to All System Users
.
TMBCAST7        FILEPI          2;USRFILE
                REPOSIT         USRFILE,ZERO
                READ            USRFILE,SEQ;REPLY
*
.Read Through the User File
.
TMBCAST8        FILEPI          1;USRFILE
                READTAB         USRFILE,SEQ;USERID,USRNO1,USRNAME1
                GOTO            TMBCAST6 IF OVER
*
.Primary Group Records Only
.
                MATCH           BLANKS,USERID
                GOTO            TMBCAST8 IF EQUAL
*
.Include This User ?
.
                DISPLAY         *P35:4,USRNAME1;
                BRANCH          INDEX TO TMBCAST9          // All Users Selected
.
                DISPLAY         *HD,*EL,INCUSR;                                   
                CALL            KREPLYN
                GOTO            TMBCAST1 IF F5
                CMATCH          YES,REPLY                                           
                GOTO            TMBCAST8 IF NOT EQUAL
*
.Write the Info to the Work File
.
TMBCAST9        CALL            TMBCST93
                GOTO            TMBCAST8
*
.No User's Selected
.
TMBCST10        KEYIN           *HD,*EL,*DV,NOUSRS,REPLY;
*
.Abort the Message Broadcast
.
TMBCST11
                CALL            AG9005
                CALL            CLRMSGS
                GOTO            TM$CMD
*
.Add This User to the List, Excluding Duplicates
.
TMBCST93        MOVE            USRNO1,DIM6
                READ            SCRATCHI,DIM6;REPLY
                RETURN          IF NOT OVER
.
                WRITE           SCRATCHI,DIM6;DIM6,USRNAME
                ADD             ONE,NWORK1
                RETURN
+..............................................................................
.
.                       M E S S A G E   I N Q U I R Y
...............................................................................
.
.
TMINQ           BRANCH          INQSW TO TMINQ2
                MOVE            EIGHTEEN,CMDTRAP                                       
                TRAP            TMINQ3 IF ESCAPE                                       
                TRAP            TMINQ3 IF F27                                          
*
.Get the Name of the User
.
TMINQ1          MOVE            ONE,HPOS
                MOVE            ONE,VPOS
                MOVE            ONE,FLAG1              // Any user
                MOVE            ZERO,FLAG4
                CALL            FINDUSER
                BRANCH          EOSFLAG TO TMINQ3
                BRANCH          FLAG1 TO TMINQ3
                MOVE            USRNAME1,USRNAME
                MOVE            USRNO1,USRNO
*
.Highlight the Name
.
                COUNT           NWORK1,USRNAME
                SETLPTR         USRNAME,NWORK1
                DISPLAY         *HD,*EL,*HU,*RPTCHAR " ":20,*H 1,*HON,*+,USRNAME,*HOFF;
                MOVE            ONE,INQSW
                MOVE            ONE,MIFUNC                                              

+..............................................................................
.
.    T E L E P H O N E   M E S S A G E   I N Q U I R Y   C M D   H A N D L E R
.
...............................................................................
.
.
TMINQ4          NORETURN
                MOVE            ZERO,CMDTRAP                                            
                TRAP            TMINQ3 IF ESCAPE
                TRAP            TMINQ3 IF F27
                DISPLAY         *P1:3,DATE,SPACE,TIME:
                                *HD,*EL,SPACE,MFUNC2,SPACE,FUNC8;
                CLEAR           FUNCDESC           // Clear the functions.                
                MOVE            ZERO,FLAG1         // Flag1 = 0                         
                CALL            CHKALRM            // Check for alarm,plan,message.       
                MOVE            ZERO,FLAG2
*
.Position to the Correct Funtion
.
TMINQ5          LOAD            FUNCDESC BY MIFUNC FROM MFUNC2,FUNC8
.
                MOVE            MIFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           MIPOS,NWORK2
                MOVE            MIPOS,DIM2
                MOVE            DIM2,HPOS
*
.Get a Command
.
TMINQ6          DISPLAY         *PHPOS:24,*HON,*+,FUNCDESC,*HOFF;
                KEYIN           *H HPOS,*HA -1,*T60,*+,*RV,REPLY;
                IF              LEFT                                                           
                CMOVE           LEFT,REPLY                                            
                ENDIF           032
                IF              RIGHT                                                           
                CMOVE           RIGHT,REPLY                                            
                ENDIF           032
                GOTO            TMINQ11 IF F5
                GOTO            TMINQ11 IF F9                                          
                GOTO            TMINQ10 IF LESS
                GOTO            TMINQ9 IF EOS
                DISPLAY         *H HPOS,*HA -1,SPACE,*+,FUNCDESC;
*
.Check for a Direction Command
.
                CMATCH          RIGHT,REPLY
                GOTO            TMINQ7 IF EQUAL
                CMATCH          LEFT,REPLY
                GOTO            TMINQ8 IF EQUAL
                CMATCH          " ",REPLY
                GOTO            TMINQ7 IF EQUAL
*
.Check for a Funtion Letter
.
                RESET           MILETS
                SCAN            REPLY,MILETS
                IF              NOT EQUAL                // Lower case                       
                RESET           MILETS2                                            
                SCAN            REPLY,MILETS2                                    
                GOTO            TMINQ6 IF NOT EQUAL                            
                MOVEFPTR        MILETS2,MIFUNC                                  
                GOTO            TMINQ5                                         
                ENDIF           
                MOVEFPTR        MILETS,MIFUNC
                GOTO            TMINQ5
*
.Move Right to the Next Funtion
.
TMINQ7          ADD             ONE,MIFUNC
                COMPARE         THREE,MIFUNC
                GOTO            TMINQ5 IF NOT EQUAL
                MOVE            ONE,MIFUNC
                GOTO            TMINQ5
*
.Move Left to the Next Funtion
.
TMINQ8          SUB             ONE,MIFUNC
                GOTO            TMINQ5 IF NOT ZERO
                MOVE            TWO,MIFUNC
                GOTO            TMINQ5
*
.We Have the Selected Function
.
TMINQ9          BRANCH          MIFUNC TO MT$CMD,TMINQ2
                CALL            INTERR
*
.A Timeout Occurred
.
TMINQ10         MOVE            ZERO,FLAG1
                CALL            CHKALRM
                DISPLAY         *P1:3,DATE,SPACE,TIME;
                GOTO            TMINQ6
*
.Help Requested
.
TMINQ11         MOVE            THIRTEEN,HMENU
                MOVE            SIX,MSGSW
                MOVE            MIFUNC,HFUNCNO
                CALL            HELP
                GOTO            MESSAGE
..............................................................................
.
.    End of Message Inquire Command Handler   
.
..............................................................................
*
.Restore the Original User ?
.
TMINQ2
                TRAP            TMINQ4 IF F27                                    
                DISPLAY         *HD,*EL,FININQ;                                   
                CALL            KREPLYY                                                                              
                GOTO            TMINQ4 IF F5                                     
                CMATCH          NO,REPLY                                          
                GOTO            TMINQ1 IF EQUAL
*
.Restore the Original User
.
TMINQ3          NORETURN
                MOVE            CURRUSER,USRNO
                MOVE            CURRNAME,USRNAME
                MOVE            ZERO,INQSW
                DISPLAY         *HU,*RPTCHAR " ":20,*H 1,USRNAME;
                GOTO            TM$CMD
.
. *** End ***
.
