*---------------------------------------------------------------
.
. Module Name: agenda_subs.inc
. Description: Called Subroutines Module
.
. Revision History:
.
* File I/O Routines
. APPOINTMENT FILE
.  Write Agenda Appointment Record By Key and Insert The Aim Key      
AG1010
                FILEPI          2;AGENDA
                WRITE           AGENDA,KEY17;KEY17,ENDHOUR,ENDMIN,STIME,ETIME:
                                TPOS,NBLOCKS,SECFLAG,TFLAG,DATA
                INSERT          AGENDAIM
                RETURN
AG1090
                FILEPI          1;AGENDA
                DELETE          AGENDA,KEY17
                GOTO            INTERR IF OVER    This was a call prior to putting into this
.                                    Called Routine.  It has been changed to a
.                                    GOTO to maintain the same stack level when
.                                    entering INTERR
                RETURN
.  End of APPOINTMENT FILE I/O
. NOTE FILE
.  Write Agenda Note Record By Key and Insert The Aim Key            
AG2010
                FILEPI          2;NOTEFILE
                WRITE           NOTEFILE,KEY20;KEY20,DATE,TIME,DATA
                INSERT          NOTEFILA
                RETURN
.  Delete Agenda Appointment Record By Key                           
AG2090
                FILEPI          1;NOTEFILE
                DELETE          NOTEFILE,KEY20
                GOTO            INTERR IF OVER    // This was a call prior to putting into this
.                                   //  Called Routine.  It has been changed to a
.                                   //   GOTO to maintain the same stack level when
.                                   //  entering INTERR
                RETURN
.  End of NOTE File I/O
. SCRATCH FILE
.  Open SCRATCH File                                                 
AG9000
                COMPARE         ONE,SWITCHI          // IS SCRATCHI FILE OPEN ?
                CALL            AG9005 IF EQUAL      // YES, CLOSE IT NOW
                TRAP            TRAPIO IF IO
                PREP            SCRATCHI,FSW,FSW,"6","26"                         
                TRAPCLR         IO
                MOVE            ONE,SWITCHI          // FILE IS OPEN
                RETURN
.  Close and delete the SCRATCH File                                 
AG9005
                CLOSE           SCRATCHI,DELETE
                MOVE            ZERO,SWITCHI         // FILE IS CLOSED
                RETURN
.  End of SCRATCH File I/O
.  End Of I/O Routines

BANNER
                MOVE            TEN TO MTOP
                MOVE            THIRTY1 TO MLEFT
                MOVE            EIGHTY TO MRIGHT
                MOVE            SIXTEEN TO MBOT
                CALL            SETSW01
                CALL            BANNER01
                DISPLAY         *HOFF,*HD,*EL;
                RETURN
BANNER01
                DISPLAY         *P1:21,*HON,*EL,VISAGNI,VERSION;
                RETURN
*
.Duplicate Keys - Bump the Seconds by One
.
DUPBUMP
                RESET           KEY18,17
                MOVE            KEY18,SECOND
                ADD             ONE,SECOND
                BUMP            KEY18,-1
                APPEND          SECOND,KEY18
                RESET           KEY18
                RETURN
+..............................................................................
.
.Compute the Day of the Week from a Specified Date
.
.  Enter with:  JDAYWORK = Julian Date to Convert
.               YEARWORK = Year to Convert
.
.  Exits with:  NWORK2   = Day of the Week (1=Sunday, 7=Saturday)
.
. Based on the Fact That 01/01/20 Was a Wednesday
.
FINDOW          MOVE            YEARWORK,NWORK2
                SUB             TWENTY,NWORK2
                ADD             JDAYWORK,NWORK2   Offset 1 Day per Year
                ADD             THREE,NWORK2        01/01/20 Was a Wednesday
*
.Allow 1 Day per Year for Each Leap Year Since 2020
.
                MOVE            YEARWORK,NWORK1
                SUB             "17",NWORK1
.
FINDOW1         SUB             FOUR,NWORK1
                GOTO            FINDOW2 IF LESS
                ADD             ONE,NWORK2
                GOTO            FINDOW1
*
.Divide by Seven and Use the Remainder for the Dow
.
FINDOW2         SUB             SEVEN,NWORK2
                GOTO            FINDOW3 IF ZERO
                GOTO            FINDOW2 IF NOT LESS
.
FINDOW3         ADD             SEVEN,NWORK2
                RETURN
*..............................................................................
.                                                                             .
.              Keyin a Y or N to Reply                                        .
.               You must enter from KREPLYN or KREPLYY                        .
.               You will exit through KREPLYZZ With REPLY = Y or N            .
.               This routine will accept Cap's or Lower Case                  .
.               This routine will check Shutdown, Messages, Meetings          .
.                 and Alarms every 90 seconds.                                .
KREPLY
                DISPLAY         " ? ",REPLYH;                                      
                GOTO            KREPLY20                                          
KREPLY10
                MOVE            FLAG1 TO REPLY   Save FLAG1
                MOVE            TWO TO FLAG1     Check
                CALL            CHKALRM0          Shutdown Only
                MOVE            REPLY TO FLAG1   Restore FLAG1
                DISPLAY         " ";
KREPLY20
                MOVE            REPLYH TO REPLY                                  
                KEYIN           *HA -1,*DV,REPLYH,*HA -1,*T90,*RV,REPLY;       
                GOTO            KREPLY10 IF LESS                                
                AND             0137 TO REPLY                                  
                CMATCH          YES TO REPLY                                 
                GOTO            KREPLYZZ IF EQUAL                            
                CMATCH          NO TO REPLY                                  
                GOTO            KREPLYZZ IF EQUAL                             
                GOTO            KREPLY20                                     
KREPLYN
                RESET           REPLYH
                CMOVE           NO TO REPLYH                                 
                GOTO            KREPLY                                         
KREPLYY
                RESET           REPLYH
                CMOVE           YES TO REPLYH                                
                GOTO            KREPLY                                       
KREPLYZZ
                RETURN        
.                                                                             .
*..............................................................................
LOAD01
                LOAD            DIM9 BY MON FROM JAN,FEB,MAR,APR,MAY:              
                                JUN,JUL,AUG,SEP,OCT,NOV,DEC                      
                MOVE            DIM9 TO MONTH                                     
                RETURN          
LOAD02
                LOAD            NWORK1 BY MONWORK FROM THIRTY1,DAYFEB,THIRTY1:     
                                THIRTY,THIRTY1,THIRTY,THIRTY1:             
                                THIRTY1,THIRTY,THIRTY1,THIRTY,THIRTY1     
                RETURN          
LOAD03
                LOAD            DIM40 BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:       
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY                  
                RETURN          
LOAD04
                LOAD            KEYWORK BY NWORK1 FROM KEYA,KEYB,KEYC,KEYD,KEYE:  
                                KEYF                        
                RETURN          
LOAD05
                LOAD            KEY17 BY KEYPTR FROM KEYA,KEYB,KEYC,KEYD,KEYE,KEYF 
                RETURN          
LOAD06
                LOAD            NWORK1 BY FREQ FROM ONE,SEVEN                     
                RETURN          
LOAD07
                LOAD            USERID BY KEYPTR FROM KEYA,KEYB,KEYC,KEYD,KEYE:
                                KEYF,KEYG,KEYH,KEYI,KEYJ     *Five extra ID's   
                RETURN

PACK01
                PACK            TABLE USING BLANKS,BLANKS,BLANKS,BLANKS
                REPLACE         BN IN TABLE
                RETURN

SETMAR01
                MOVE            SIX TO MTOP
                MOVE            TWELVE TO MBOT
                MOVE            FOUR TO MLEFT
                MOVE            TWENTY6 TO MRIGHT
                CALL            SETSW01
                RETURN
SETSW01
                DISPLAY         *SETSWALL MTOP:MBOT:MLEFT:MRIGHT,*ES,*SETSWALL=1:24:1:80;    
                GOTO            SETSW99                                            
SETSW02
                DISPLAY         *SETSWALL MTOP:MBOT:MLEFT:MRIGHT,*ES;             
                GOTO            SETSW99                                            
SETSW03
                DISPLAY         *SETSWALL MTOP:MBOT:MLEFT:MRIGHT;               
                GOTO            SETSW99                                           
SETSW99
                MOVE            THREE TO MTOP                                      
                MOVE            TWO TO MLEFT                                     
                MOVE            SEVENTY9 TO MRIGHT                              
                MOVE            TWENTY1 TO MBOT                                  
                RETURN         
SETTOP06
                MOVE            SIX TO MTOP                                      
                RETURN          
SETTOP14
                MOVE            FOURTEEN TO MTOP                                
                RETURN         
SETTOP16
                MOVE            SIXTEEN TO MTOP                               
                RETURN         
*
. Draw a big box
.
SHOWBOX1        DISPLAY         *ES,*P2:1,USRNAME:                        LINE 1
                                *H 59,DATE,SPACE2,TIME:
                                *N,ULC,*RPTCHAR HE:78,URC:               LINE 2
                                *N,VB,*H 80,VE,*N,VB,*H 80,VE:           LINE 3 + 4
                                *N,VB,*H 80,VE,*N,VB,*H 80,VE:           LINE 5 + 6
                                *N,VB,*H 80,VE,*N,VB,*H 80,VE:           LINE 7 + 8
                                *N,VB,*H 80,VE,*N,VB,*H 80,VE:           LINE 9 + 10
                                *N,VB,*H 80,VE,*N,VB,*H 80,VE:           LINE 11 + 12
                                *N,VB,*H 80,VE,*N,VB,*H 80,VE:           LINE 13 + 14
                                *N,VB,*H 80,VE,*N,VB,*H 80,VE:           LINE 15 + 16
                                *N,VB,*H 80,VE,*N,VB,*H 80,VE:           LINE 17 + 18
                                *N,VB,*H 80,VE,*N,VB,*H 80,VE:           LINE 19 + 20
                                *N,VB,*H 80,VE:                          LINE 21
                                *N,LLC,*RPTCHAR HB:HLPPOSNI,"-",HLPCMDNI,"-",LRC;     
                RETURN
SHOWBOXN
                CALL            SHOWBOX1                                          
                DISPLAY         *P34:1,DSKNOTE,*P1:23,*H 73,PGSTAT,PAGE:   
                                *HD;                                              
                RETURN        
*
.Check the Alarm
.
.    Enter with FLAG1 = 0     Check Shutdown, Alarm, Messages, Meetings
.                       1     Don't Check Messages
.                       2     Check for Shutdown Only
.
...............................................................................
.           FLAG2 NO LONGER SET IN THIS ROUTINE AND IT IS NO LONGER  
.           CHECKED UPON EXITING THIS ROUTINE.                       
.                                                                     
.    Exits with FLAG2 = 0     Bottom Line Intact                      
.                       1     Bottom Line Destroyed                   
.                                                                    
...............................................................................
CHKALRM         DISPLAY         *H HPOS,*+,FUNCDESC;
                MOVE            ZERO TO FORM1                                     
*
.Check for a System Shutdown Command
.
CHKALRM0
                FILEPI          1;CONTROL
                READTAB         CONTROL,ZERO;REPLY
.
                CMATCH          SPACE,REPLY
                GOTO            START IF NOT EQUAL
*
.At Logon Screen ?
.
                COMPARE         TWO,FLAG1
                RETURN          IF EQUAL
*
.Disable During Inquiry
.
                COMPARE         ONE,INQSW
                RETURN          IF EQUAL
*
.Is the Alarm Set ?
.
                DISPLAY         *P1:23;
                CALL            CLOCKDT
                COMPARE         ZERO,AYEAR             // Alarm Not Set
                GOTO            CHKMSG IF EQUAL        // Go Check Messages
*
.Right Date/Time ?
.
                PACK            KEYWORK WITH AYEAR,ADAY,AHOUR,AMIN,ASEC
                PACK            KEY20 WITH YEARWORK,JDAYWORK,HOURWORK,MINWORK,SECOND
                MATCH           KEYWORK,KEY20
                GOTO            CHKALRM4 IF LESS       // Not Time...

*                                                                          
.Set the First Alarm Time as Needed                                         
.                                                                           
...............................................................................
                COMPARE         ONE,ALRMFLG            // Skip alarm display if from alarm 
                GOTO            CHKALRM4 IF EQUAL      //                                  
                DISPLAY         *C,*HON,*B,*BLINKON,ALRM,*HOFF;
                ADD             ONE TO FORM1                                       
CHKALRM4        CALL            FATIME
+..............................................................................
.
.See if the User Has Any New Messages
.
CHKMSG          BRANCH          FLAG1 TO CHKMEET         // Skip Checking Messages
*
.Position to His New Messages
.
                PACK            KEY9 WITH X02,CURRUSER
.
                FILEPI          1;USRFILE
                READTAB         USRFILE,KEY9;*82,FMTIME,*91,MEETFLG
                CALL            INTERR IF OVER
*
.Right Type/User/Year/Day/Hour/Min ?
.
                PACK            KEY WITH YEARWORK,JDAYWORK,HOURWORK,MINWORK
                MATCH           FMTIME,KEY
                GOTO            CHKMSG1 IF EQUAL
                GOTO            CHKMEET IF LESS
*
.He Has Some Messages
.
CHKMSG1
                COMPARE         ONE,ALRMFLG          // Skip message display if from alarm 
                GOTO            CHKMEET IF EQUAL     //                                    
                DISPLAY         *H 10,*HON,*B,*BLINKON,MSGALRM,*HOFF;
                ADD             ONE TO FORM1                                     
.
.See if He Has Any New Meetings
.
CHKMEET         COMPARE         ZERO,MEETFLG
                GOTO            CHKZ0020 IF EQUAL                                  

                COMPARE         ONE,ALRMFLG          // Skip planning disp if from alarm   
                GOTO            CHKZ0020 IF EQUAL    //                                    
                TRAP            RDJMP IF IO
                OPEN            PLAN1,FSP1,SHARE                                    
                PACK            KEY6 FROM USRNO                                        
                FILEPI          1;PLAN1                                               
                READ            PLAN1,KEY17B;;                                         
                GOTO            CHKZ0099 IF OVER                                     
RDJMP           FILEPI          1;PLAN1                                               
                READKS          PLAN1;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER:
                                USRNO2,ENDHOUR,ENDMIN,DATE,STIME,ETIME,USRNAME1:
                                LOCATION,CONFIRM,DATA                                 
                IF              OVER                                                           
                PACK            KEY9 WITH X02,CURRUSER                                
                FILEPI          3;USRFILE                                            
                READTAB         USRFILE,KEY9;REPLY;                                  
                CALL            INTERR IF OVER                                        
                UPDATAB         USRFILE;*91,ZERO                                    
                GOTO            CHKZ0099                                             
                ENDIF           
                COMPARE         USRNO1,USRNO                                        
                GOTO            RDJMP IF NOT EQUAL                                   
                MATCH           CONFIRM,CN                                             
                IF              EQUAL                                                    
                COMPARE         YEARWORK,YEAR                                          
                GOTO            RDJMP IF GREATER                                      
                COMPARE         JDAYWORK,JULDAY                                       
                GOTO            RDJMP IF GREATER                                       
                COMPARE         HOUR,HOURWORK                                        
                GOTO            RDJMP IF GREATER                                       
                DISPLAY         *H 22,*HON,*B,*BLINKON,PLANALRM,*HOFF;                
                ELSE            
                GOTO            RDJMP                                                  
                ENDIF           
                ADD             ONE TO FORM1                                     
CHKZ0020
                COMPARE         ZERO TO FORM1                                     
                GOTO            CHKZ0099 IF EQUAL                                 
                DISPLAY         *W1,*B;                                           
                SUB             ONE FROM FORM1
                GOTO            CHKZ0020                                           
CHKZ0099
                TRAPCLR         IO                                                     
                RETURN
*..............................................................................
.
.Routine to Set the First Message Time & Date
.
.  Enter with: DIM6 = User Number
.
.  Exits with: User Record Updated Correctly
.
FMTIME          PACK            KEY9 WITH X02,DIM6
.
                FILEPI          1;USRFILE
                READTAB         USRFILE,KEY9;*82,DIM9
                CALL            INTERR IF OVER
*
.See if the User Has Any New Messages
.
                PACK            KEY WITH ONE,DIM6
.
. DISPLAY *P1:23,*EL,"KEY:",KEY,*W5;
                FILEPI          2;MESSAGE
                READ            MESSAGE,KEY;;
                READKSTB        MESSAGE;DIM7,FMTIME
                GOTO            FMTIME1 IF OVER
*
.Right Record Type/User ?
.
                MATCH           KEY,DIM7
                GOTO            FMTIME1 IF NOT EQUAL
*
.Do We Need to Update the First Message Time ?
.
                MATCH           DIM9,FMTIME
                RETURN          IF EQUAL
                GOTO            FMTIME2
*
.No New Messages for This User
.
FMTIME1         MATCH           "99",DIM9
                RETURN          IF EQUAL
                MOVE            NINE9,FMTIME
*
.Update the User's Record
.
FMTIME2         FILEPI          1;USRFILE
                UPDATAB         USRFILE;*82,FMTIME
                RETURN
+..............................................................................
.
.Routine to Set the Alarm Time
.
.  Enter with: CURRUSER = User Number
.
.  Exits with: Alarm Time and Date Set Correctly
.
FATIME          PACK            KEY20 WITH ONE,CURRUSER
.
                FILEPI          2;NOTEFILE
                READ            NOTEFILE,KEY20;;
                READKS          NOTEFILE;REPLY,USRNO1,AYEAR,ADAY,AHOUR,AMIN,ASEC:
                                COUNTER,ADATE,ATIME,ALARMSG
                RETURN          IF OVER
*
.Right Record Type/User ?
.
                CMATCH          "1",REPLY
                GOTO            FATIME1 IF NOT EQUAL
                COMPARE         CURRUSER,USRNO1
                RETURN          IF EQUAL
*
.Turn Off the Alarms
.
FATIME1         MOVE            ZERO,AYEAR
                RETURN
+..............................................................................
.
.Year Computation Routine
.
.  Enter with:  YEARWORK = Year Selected
.
.  Exits with:  DAYFEB   = Number of Days in February
.               YEARLEN  = Number of Days in Year Selected
.               PYEARLEN = Number of Days in Prior Year
.
*
.Determine the Number of Days in February and the Year's Length
.
YEARCOMP        MOVE            TWENTY8,DAYFEB
                MOVE            THREE65,YEARLEN
.
                MOVE            YEARWORK,NWORK1
                DIV             FOUR,NWORK1
                MULT            FOUR,NWORK1
                COMPARE         YEARWORK,NWORK1
                GOTO            YEARCMP1 IF NOT EQUAL
                ADD             ONE,DAYFEB
                ADD             ONE,YEARLEN
*
.Determine the Length of the Previous Year
.
YEARCMP1        MOVE            THREE65,PYEARLEN
.
                MOVE            YEARWORK,NWORK1
                SUB             ONE,NWORK1
.
                MOVE            NWORK1,NWORK2
                DIV             FOUR,NWORK2
                MULT            FOUR,NWORK2
                COMPARE         NWORK1,NWORK2
                RETURN          IF NOT EQUAL
.
                ADD             ONE,PYEARLEN
                RETURN
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
.Find the Starting Day of the Week
.
DRAWCAL         MOVE            ONE,DAYWORK
                MOVE            MON,MONWORK
                MOVE            YEAR,YEARWORK
                CALL            GREGJUL
                CALL            FINDOW
                MOVE            NWORK2,FSTDAY   // Capture the column pos. of 1st of month 
                COMPARE         ONE,DATESWCH                                            
                IF              EQUAL                                                            
                COMPARE         FSTDAY,ONE                                            
                IF              EQUAL                                                           
                MOVE            SEVEN,FSTDAY                                            
                MOVE            SEVEN,NWORK2                                             
                ELSE            039
                SUB             ONE,FSTDAY                                             
                SUB             ONE,NWORK2                                              
                ENDIF           039
                ENDIF           039
*
.Determine the Number of Days in the Month
.
                LOAD            ENDDAY BY MON FROM THIRTY1,DAYFEB,THIRTY1,THIRTY:
                                THIRTY1,THIRTY,THIRTY1,THIRTY1:
                                THIRTY,THIRTY1,THIRTY,THIRTY1
*
.Make Sure the Day is Not Beyond the End of the Month
.
                COMPARE         ENDDAY,DAY
                GOTO            DRAWCAL1 IF LESS
                MOVE            ENDDAY,DAY
*
.Compute the Screen Position of the 1st Day of the Month
.
DRAWCAL1        SUB             ONE,NWORK2
                MULT            THREE,NWORK2
                ADD             FOUR,NWORK2
.
                MOVE            NWORK2,HPOSEND
                MOVE            SEVEN,VPOSEND
*
.Reset the Month Table
.
                PACK            MONTABLE WITH BLANKS,BLANKS
                REP             " N",MONTABLE
*
.Position the Graph File to This User
.
                COMPARE         ZERO,F1HIT           // Was F1 hit ?
                GOTO            DRAWCA1A IF EQUAL    // No, no special display
                BRANCH          TERMTYPE TO DRAWCAL7
                GOTO            DRAWCA1B
DRAWCA1A        BRANCH          TERMTYPE TO DRAWCAL7
DRAWCA1B        SUB             ONE,JDAYWORK
                PACK            DIM11 WITH USRNO,YEARWORK,JDAYWORK
                ADD             ONE,JDAYWORK
                FILEPI          1;GRAPH
                READ            GRAPH,DIM11;;
*
.Read the Next Graph Record
.
DRAWCAL6        MOVE            ZERO,FLAG2
                FILEPI          1;GRAPH
                READKS          GRAPH;USRNO1,YEARWRK1,JDAYWRK1
                GOTO            DRAWCAL7 IF OVER
                COMPARE         USRNO,USRNO1
                GOTO            DRAWCAL2 IF EQUAL
*
.No More Appointments for This User
.
DRAWCAL7        MOVE            NINTY9,YEARWRK1
*
.Draw the Calendar
.
DRAWCAL2        COMPARE         DAYWORK,DAY
                GOTO            DRAWCAL8 IF NOT EQUAL
.
                MOVE            HPOSEND,HPOSDAY
                MOVE            VPOSEND,VPOSDAY
                DISPLAY         *HON;
                MOVE            ONE,FLAG3
*
.Appointment on This Day ?
.
DRAWCAL8        COMPARE         ZERO,F1HIT           // Was F1 hit ?
                GOTO            DRAWCA8A IF EQUAL    // No, no special display
                BRANCH          TERMTYPE TO DRAWCAL3
                GOTO            DRAWCA8B
DRAWCA8A        BRANCH          TERMTYPE TO DRAWCAL3
DRAWCA8B        COMPARE         YEARWORK,YEARWRK1
                GOTO            DRAWCAL3 IF NOT EQUAL
                COMPARE         JDAYWORK,JDAYWRK1
                GOTO            DRAWCAL3 IF NOT EQUAL
*
.Highlight This Date, Flag the Month Table
.
                RESET           MONTABLE,DAYWORK
                CMOVE           CY,MONTABLE                          
                MOVE            ONE,FLAG2
                BRANCH          FLAG3 TO DRAWCAL3
                DISPLAY         *V2LON;
.
DRAWCAL3        DISPLAY         *PHPOSEND:VPOSEND,DAYWORK,*HOFF;
                COMPARE         DAYWORK,ENDDAY
                RETURN          IF EQUAL
.
                MOVE            ZERO,FLAG3
                ADD             ONE,JDAYWORK
                ADD             ONE,DAYWORK
                ADD             THREE,HPOSEND
                COMPARE         TWENTY5,HPOSEND
                GOTO            DRAWCAL5 IF NOT EQUAL
.
                ADD             ONE,VPOSEND
                MOVE            FOUR,HPOSEND
*
.If We Turned on the Date, Get the Next Graph Day
.
DRAWCAL5        COMPARE         ZERO,F1HIT           // Was F1 hit ?
                GOTO            DRAWCA5A IF EQUAL    // No, no special display
                BRANCH          TERMTYPE TO DRAWCAL2
                GOTO            DRAWCA5B
DRAWCA5A        BRANCH          TERMTYPE TO DRAWCAL2
DRAWCA5B        BRANCH          FLAG2 TO DRAWCAL6
                GOTO            DRAWCAL2
+..............................................................................
.
.Compute the Dates Needed to Graph the Week
.
. Enter with:  JULDAY  = Julian Date Selected
.              YEAR    = Year Selected
.              YEARLEN = Length of Year Selected (Days)
.              GRAPHSW = 1 - Force Graph to be Redrawn
.                        0 - Don't Redraw if Already On the Screen
.
. Exits with:  YEARSTR = Week's Starting Year
.              YEAREND = Week's Ending Year
.               DAY 1 - DAY 7 = Julian Dates
.              GRAPHSW = 0
.
. Note: If this is the first week of the month, we'll graph any of the
.       previous month's days which fall within this week. The same holds
.       true for the end of the month, and also for the year.
*
.See if the Week is Already on the Screen
.
GRAPH           COMPARE         ONE,DATESWCH                                        
                IF              EQUAL                                                       
                SUB             ONE,JULDAY                                           
                ENDIF           039
                BRANCH          GRAPHSW TO GRAPH1                                     
                SEARCH          JULDAY FROM DAY1 TO SEVEN INTO INDEX
.
                IF              NOT OVER                                                    
                COMPARE         ONE,DATESWCH                                         
                IF              EQUAL                                                      
                ADD             ONE,JULDAY                                           
                ENDIF           039
                RETURN          039
                ENDIF           039
*
.Determine the Selected Day of the Week
.
GRAPH1
                CALL            SETTOP06
                MOVE            TWENTY9 TO MLEFT
                MOVE            TWELVE TO MBOT
                CALL            SETSW01
                MOVE            ZERO,GRAPHSW
.
                MOVE            JULDAY,JDAYWORK
                MOVE            YEAR,YEARWORK
                CALL            FINDOW
*
.Determine the Week's Starting Date
.
                MOVE            YEAR,YEARSTR
                MOVE            JULDAY,NWORK1
                SUB             NWORK2,NWORK1
                ADD             ONE,NWORK1
*
.Is This the First Week in the Year ?
.
                MOVE            ZERO,SWITCH
                COMPARE         ONE,NWORK1
                GOTO            GRAPH2 IF NOT LESS
*
.This Week Begins in the Previous Year
.
                MOVE            ONE,SWITCH
                ADD             PYEARLEN,NWORK1
                SUB             ONE,YEARSTR
*
.At This Point, NWORK1 = Week's Starting Date
.
.Set up the Date Table
.
GRAPH2          MOVE            ONE,INDEX
                MOVE            YEARSTR,YEAREND
.
GRAPH3          STORE           NWORK1 BY INDEX INTO DAY1,DAY2,DAY3:
                                DAY4,DAY5,DAY6,DAY7
.
                ADD             ONE,INDEX
                COMPARE         EIGHT,INDEX
                GOTO            GRAPH5 IF EQUAL
                ADD             ONE,NWORK1
*
.Check for Correct Year Overflow
.
                BRANCH          SWITCH TO GRAPH4
*
.Check for This Year's Length
.
                COMPARE         NWORK1,YEARLEN
                GOTO            GRAPH3 IF NOT LESS
                MOVE            ONE,NWORK1
                ADD             ONE,YEAREND
                GOTO            GRAPH3
*
.Check for the Prior Year's Length
.
GRAPH4          COMPARE         NWORK1,PYEARLEN
                GOTO            GRAPH3 IF NOT LESS
                MOVE            ONE,NWORK1
                ADD             ONE,YEAREND
                GOTO            GRAPH3
*..............................................................................
.
.Graphically Display the Week's Appointments
.
.  Enter with:  USRNO    = User Number
.               YEARSTR  = Week Starting Year
.               DAY1     = Week Starting Julian Day
.               YEAREND  = Week Ending Year
.               DAY7     = Week Ending Julian Day
.               GRAPHPOS = 1  Begin Graphing at Midnight
.                          2  Begin Graphing at Seven AM
.                          3  Begin Graphing at Noon
.
.  Exits with:  Week Graphed on the Screen
.
.Display the Time Rule
.
GRAPH5          LOAD            DATA BY GRAPHPOS FROM RULE1,RULE2,RULE3
                DISPLAY         *P29:5,*+,DATA;
*
.Position the Appointment Graph File
.
                MOVE            DAY1,JDAYWORK
                SUB             ONE,JDAYWORK
                PACK            DIM11 WITH USRNO,YEARSTR,JDAYWORK
.
                FILEPI          1;GRAPH
                READ            GRAPH,DIM11;;
*
.Build a Key to Match With
.
                PACK            KEYWORK WITH USRNO,YEAREND,DAY7
*
.Read Through the Appointment Graph File
.
GRAPH6          FILEPI          1;GRAPH
                READKS          GRAPH;DIM11,COUNT,TABLE                                

                IF              OVER                                                           
                COMPARE         ONE,DATESWCH                                           
                IF              EQUAL                                                          
                ADD             ONE,JULDAY                                             
                ENDIF           
                UNPACK          DIM11 TO USRNO1,YEARWORK,JDAYWORK                       
                RETURN          
                ENDIF           
                UNPACK          DIM11 TO USRNO1,YEARWORK,JDAYWORK                      
*
.Right User/Year/Week ?
.
                COMPARE         ONE,DATESWCH                                           
                IF              EQUAL                                                           
                SUB             ONE,JDAYWORK                                            
                ENDIF           039
                PACK            KEY WITH USRNO1,YEARWORK,JDAYWORK
                MATCH           KEY,KEYWORK

                IF              LESS                                                          
                COMPARE         ONE,DATESWCH                                            
                IF              EQUAL                                                          
                ADD             ONE,JULDAY                                             
                ENDIF           
                RETURN         
                ENDIF          
*
.Display the Day's Appointments
.
                BRANCH          DATESWCH OF GRAPH6A                                   
                CALL            DISPDAY
                GOTO            GRAPH6
.
GRAPH6A         ADD             ONE,JDAYWORK                                           
                CALL            DISPDAY                                                
                SUB             ONE,JDAYWORK                                            
                GOTO            GRAPH6                                                
+..............................................................................
.
.Display the Appointments for the Selected Day
.
.  Enter with: USRNO = User Number
.             JULDAY = Julian Day Selected
.               YEAR = Year Selected
.
.  Exits with:  Up to Six Appointments on the Screen
.               Graph File Positioned to the Selected Day
.
*
.Format the Date and Day
.
SHOWDTL1        MOVE            JULDAY,JDAYWORK
                MOVE            YEAR,YEARWORK
                CALL            FINDOW               // NWORK2 := DAY OF WEEK
                COMPARE         ONE,DATESWCH                                           
                IF              EQUAL                                                           
                COMPARE         ONE,NWORK2                                             
                IF              EQUAL                                                          
                MOVE            SEVEN,NWORK2                                           
                ELSE            
                SUB             ONE,NWORK2                                             
                ENDIF           
                LOAD            DIM40 BY NWORK2 FROM MONDAY,TUESDAY,WEDNESDY:
                                THURSDAY,FRIDAY,SATURDY,SUNDAY                         
                ELSE            

                CALL            LOAD03
                ENDIF           
                MOVE            DIM40 TO KEY
.
                CALL            LOAD01
*
.Remove the Leading Space in Single Digit Dates
.
                MOVE            DAY,DIM2
                CMATCH          SPACE,DIM2
                GOTO            SHOWDTL2 IF NOT EQUAL
                BUMP            DIM2
*
.Build the Line
.
SHOWDTL2
                PACK            DIM30 USING KEY,COMMA,SPACE,DIM9,SPACE,DIM2,COMMA,SPACE:
                                YEARPREFIX,YEAR
.
                LOAD            HPOS BY MON FROM ONE,ZERO,TWO,TWO,THREE,TWO:
                                TWO,ONE,ZERO,ONE,ZERO,ZERO
                ADD             THIRTY2,HPOS
*
.Highlight the Day of the Week on the Graph
.
                MOVE            KEY,REPLY
                MOVE            FIVE,VPOS
                ADD             NWORK2,VPOS
*
.Fix Up the Screen
.
                CALL            SETTOP16
                CALL            SETSW02
                BRANCH          DATESWCH OF SD2A                                       
                DISPLAY         *SETSWTB 1:24,*P31:14,*EL,*SETSWALL=1:24:1:80:
                                *P28:6,CSUN,*P28:7,CMON,*P28:8,CTUE,*P28:9,CWED:
                                *P28:10,CTH,*P28:11,CFRI,*P28:12,CSAT:
                                *P28:VPOS,*HON,REPLY,*HOFF:
                                *PHPOS:14,AGTITLE,*+,DIM30,*V 16;
                GOTO            SD2B                                                   
SD2A            DISPLAY         *SETSWTB 1:24,*P31:14,*EL,*SETSWALL=1:24:1:80:
                                *P28:6,CMON,*P28:7,CTUE,*P28:8,CWED,*P28:9,CTH:
                                *P28:10,CFRI,*P28:11,CSAT,*P28:12,CSUN:
                                *P28:VPOS,*HON,REPLY,*HOFF:
                                *PHPOS:14,AGTITLE,*+,DIM30,*V 16;                
SD2B
*
.Position the File
.
                PACK            KEYWORK WITH USRNO,YEAR,JULDAY
.
                FILEPI          1;AGENDA
                READ            AGENDA,KEYWORK;;
*
.Set Up for the Appointments
.
                MOVE            ZERO,DTLCOUNT
                MOVE            ZERO,NOMORE
                MOVE            ONE,NOPREV
*
.Read Through the Appointment File
.
SHOWDTL3        FILEPI          1;AGENDA
                READKS          AGENDA;USRNO1,YEARWORK,JDAYWORK,HOUR,MIN:
                                COUNTER,ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
                GOTO            SHOWDTL5 IF OVER
*
.Right User/Year/Day ?
.
                PACK            KEY WITH USRNO1,YEARWORK,JDAYWORK,HOUR,MIN,COUNTER
                MATCH           KEY,KEYWORK
                GOTO            SHOWDTL5 IF NOT EQUAL
*
.Save the Appointment Key
.
                COMPARE         SIX,DTLCOUNT
                GOTO            SHOWDTL5 IF EQUAL    // Screen is Full
.
                ADD             ONE,DTLCOUNT

                STORE           KEY BY DTLCOUNT INTO KEYA,KEYB,KEYC:
                                KEYD,KEYE,KEYF
*
.Don't Display Confidential Information if Inquiring
.
                COMPARE         ZERO,INQSW             // Inquiring ?
                GOTO            SHOWDTL4 IF EQUAL      // No....
                CMATCH          SPACE,SECFLAG          // Confidential ?
                GOTO            SHOWDTL4 IF EQUAL      // No
                MOVE            CONMSG,DATA
*
.Display the Appointment
.
SHOWDTL4        DISPLAY         *H 3,STIME,*H 13,*+,ETIME,*H 23,SECFLAG,DATA
                GOTO            SHOWDTL3
*
.Read the Day Table and Return
.
SHOWDTL5
                IF              NOT OVER                                                        
                MATCH           KEY,KEYWORK                                             
                IF              EQUAL                                                          
                COMPARE         SIX,DTLCOUNT                                           
                IF              EQUAL                                                         
                DISPLAY         *P=23:22,*LTK,MOREPR,*DNA,SPACE,*RTK;                
                ELSE            
                DISPLAY         *P=23:22,*RPTCHAR=HB:10;                             
                DISPLAY         *P=23:15,*RPTCHAR=HB:10;                             
                ENDIF           
                ELSE            
                DISPLAY         *P=23:22,*RPTCHAR=HB:10;                             
                DISPLAY         *P=23:15,*RPTCHAR=HB:10;                             
                ENDIF           
                ELSE            
                DISPLAY         *P=23:22,*RPTCHAR=HB:10;                             
                DISPLAY         *P=23:15,*RPTCHAR=HB:10;                              
                ENDIF           
                PACK            DIM11 WITH USRNO,YEAR,JULDAY
                FILEPI          1;GRAPH
                READTAB         GRAPH,DIM11;*12,COUNT,TABLE
                RETURN          IF NOT OVER
*
.No Appointments for the Selected Day; Build an Empty Table
.
                MOVE            ZERO,COUNT
                CALL            PACK01                                            
                RETURN
+..............................................................................
.
.Compute Appointment Information
.
.  Enter with:  HOUR     = Appointment Starting Hour
.               MIN      = Appointment Starting Minute
.               ENDHOUR  = Appointment Ending Hour
.               ENDMIN   = Appointment Ending Minute
.
.  Exits with:  NBLOCKS  = Number of 15 Minute Blocks to Update
.
.  Note: Starting Time is Rounded Down to the Even Quarter Hour; Ending
.         Time is Rounded Up.
.  Note II: The above Note was changed for Ver 2.7.A, See ROUNDTIME.
.
.Compute the Number of 15 Minute Blocks to Update
.
COMPUTE         MOVE            ENDHOUR,NWORK2
                COMPARE         ZERO,NWORK2               // End at Midnight ?
                GOTO            COMPUTE1 IF NOT EQUAL     // No...
                COMPARE         ZERO,HOUR                 // Start at Midnight ?
                GOTO            COMPUTE1 IF EQUAL         // Yes...
.
                MOVE            TWENTY4,NWORK2
                GOTO            COMPUTE3
*
.Compute the Number of Minutes
.
COMPUTE1        MOVE            MIN,NWORK3                 // Round the Starting Time Down 
                MOVE            NWORK3,NWORK1              // NWORK1 is working variable  
                CALL            ROUNDTIME                  // Compute # of 15 min blocks   
                MOVE            NWORK1,NWORK3              // Return them to orig. var.   
                MULT            FIFTEEN,NWORK3
.
                MOVE            ENDMIN,NWORK1
                CALL            ROUNDTIME                  // Compute # of 15 min blocks   
                MULT            FIFTEEN,NWORK1
.
COMPUTE2        SUB             NWORK3,NWORK1
                GOTO            COMPUTE3 IF NOT LESS
                ADD             SIXTY,NWORK1
                SUB             ONE,NWORK2
*
.Compute the Hours
.
COMPUTE3        SUB             HOUR,NWORK2
                MULT            FOUR,NWORK2
*
.Add in the Minutes
.
                DIV             FIFTEEN,NWORK1
                ADD             NWORK2,NWORK1
                MOVE            NWORK1,NBLOCKS
*
.Catch All Day
.
                COMPARE         ZERO,NBLOCKS
                RETURN          IF NOT EQUAL
                MOVE            ONE,NBLOCKS
                RETURN
+..............................................................................
.
.Routine to Obtain a Date from the User
.
. Enter with: HPOS = Horizontal Position
.             VPOS = Vertical Position
.          REQFLAG = 0 - Allow Null Entry
.                    1 - Require Variable Input
.           MASKSW = 0 - Display Mask
.                    1 - Do Not Display Mask
.         DATESWCH = 0 - mm/dd/yy Format
.                    1 - dd mmm 20yy Format
.           TDDATE = 0 - Allow default to todays date upon enter      
.                    1 - Do not allow todays date on enter             
.
. Exits with: MONWORK  = Month Entered
.             DAYWORK  = Day Entered
.             YEARWORK = Year Entered
.             JDAYWORK = Julian Date Entered
.               DATE = Formatted Date (dd mmm yyyy)
.
.              FLAG1 = 0 - F5 Key Not Pressed
.                      1 - F5 Key Pressed (Date Variables Invalid)
.            EOSFLAG = 0 - Enter Key Not Pressed
.                      1 - Null Entry
.
*
. mm/dd/yy Format Routine
.
GETDATE         MOVE            ZERO,EOSFLAG
                MOVE            ZERO,FLAG1
                IF              (PRTSW = 0)                                                   
                CALL            CLOCKDT                                                
                ENDIF           044
                BRANCH          DATESWCH OF GEETDATE // Go do European format

                BRANCH          MASKSW TO GETDATE1
                DISPLAY         *PHPOS:VPOS,MASK1;
*
.Get the Month
.
GETDATE1        KEYIN           *PHPOS:VPOS,*+,*RV,MONWORK;
                GOTO            GETDATE4 IF F5
                COMPARE         ONE,TDDATE                                              
                IF              EQUAL                                                          
                GOTO            GETDATE5 IF EOS
                ENDIF           024
.
                COMPARE         ONE,MONWORK
                GOTO            GETDATE1 IF LESS
                COMPARE         THIRTEEN,MONWORK
                GOTO            GETDATE1 IF NOT LESS
*
.Get the Day
.
GETDATE2        KEYIN           *PHPOS:VPOS,*DV,MONWORK,*HA 1,*+,*RV,DAYWORK;
                GOTO            GETDATE IF F5
.
                COMPARE         ONE,DAYWORK
                GOTO            GETDATE2 IF LESS
                COMPARE         THIRTY2,DAYWORK
                GOTO            GETDATE2 IF NOT LESS
*
.Get the Year
.
GETDATE3        KEYIN           *PHPOS:VPOS,*HA 3,*DV,DAYWORK,*HA 1,*+,*RV,YEARWORK;
                GOTO            GETDATE IF F5
.
                COMPARE         TWENTY,YEARWORK
                GOTO            GETDATE3 IF LESS
*
.Format the Date
.
                PACK            DATE WITH MONWORK,SLASH,DAYWORK,SLASH,YEARWORK
                REP             SPACZERO,DATE
                GOTO            GEETSHOW
*
.Enter Key Pressed
.
GETDATE5        BRANCH          REQFLAG TO GETDATE1
                MOVE            ONE,EOSFLAG
                RETURN

*
. dd mmm 20yy Format
.
GEETDATE        MOVE            ZERO,EOSFLAG
                MOVE            ZERO,FLAG1
                BRANCH          MASKSW TO GEETDTE1
                DISPLAY         *PHPOS:VPOS,MASK2;
*
.Get the Day
.
GEETDTE1        KEYIN           *PHPOS:VPOS,*+,*RV,DAYWORK;
                GOTO            GETDATE4 IF F5
                COMPARE         ONE,TDDATE                                             
                IF              EQUAL                                                        
                GOTO            GEETDTE5 IF EOS
                ENDIF           024
.
                COMPARE         ONE,DAYWORK
                GOTO            GEETDTE1 IF LESS
                COMPARE         THIRTY2,DAYWORK
                GOTO            GEETDTE1 IF NOT LESS
*
.Get the Month Abbreviation
.
GEETDTE2        RESET           DATE,4
                MOVE            DATE,DIM3
                RESET           DATE
.
                KEYIN           *H HPOS,*DV,DAYWORK,*HA 1,*+,*IT,*RV,DIM3;
                GOTO            GEETDTE1 IF F5
.
                CMATCH          SPACE,DIM3
                GOTO            GEETDTE2 IF EOS
.
                SETLPTR         DIM3,1
                REP             MONABREV,DIM3
                SETLPTR         DIM3,3
                SEARCH          DIM3 FROM JAN TO TWELVE INTO MONWORK
                COMPARE         ZERO,MONWORK
                GOTO            GEETDTE2 IF EQUAL
                LOAD            DIM3 BY MONWORK FROM JAN,FEB,MAR,APR,MAY,JUN:
                                JUL,AUG,SEP,OCT,NOV,DEC
*
.Get the Year
.
GEETDTE3        KEYIN           *IN,*H HPOS,*HA 3,*DV,DIM3,*HA 3,*+,*RV,YEARWORK;
                GOTO            GEETDTE2 IF F5
.
                COMPARE        TWENTY,YEARWORK
                GOTO            GEETDTE3 IF LESS
*
.Format the Date
.
                LOAD            DIM3 BY MONWORK FROM JAN,FEB,MAR,APR,MAY:
                                JUN,JUL,AUG,SEP,OCT,NOV,DEC
.
                PACK            DATE WITH DAYWORK,SPACE,DIM3,SPACE,YEARPREFIX,YEARWORK
GEETSHOW        DISPLAY         *PHPOS:VPOS,DATE;
.
                GOTO            GREGJUL
*
.F5 Key Pressed
.
GETDATE4        MOVE            ONE,FLAG1
                RETURN
*
.Enter Key Pressed
.
GEETDTE5        BRANCH          REQFLAG TO GEETDTE1
                MOVE            ONE,EOSFLAG
                RETURN
+..............................................................................
.
.Routine to Get the Time from the Keyboard
.
.  Enter with:  HPOS = Horizontal Position
.               VPOS = Vertical Position
.            REQFLAG = 0 - Allow Null Entry
.                      1 - Require Variable Input
.             MASKSW = 0 - Display Mask
.                      1 - Do Not Display Mask
.
.           TIMESWCH = 0 - Input in 12 Hour Format (hh:mm ?m)
.                      1 - Input in 24 Hour Format (hh:mm)
.
.  Exits with:  HOURWORK = Hour       (Always Military Format)
.               MINWORK  = Minute
.                  TIME  = Formatted Time (hh:mm ?m)
.
.                  FLAG1 = 0 - F5 Key Not Pressed
.                          1 - F5 Key Pressed (Time Variables Invalid)
.                EOSFLAG = 0 - Enter Key Not Pressed
.                          1 - Enter Key Pressed
.
.Reset the Flag
.
GETIME          MOVE            ZERO,EOSFLAG
                MOVE            ZERO,FLAG1
.
GETIMEX         BRANCH          TIMESWCH OF G2ETIME1 // Military time in use   
*
.Display the Mask
.
GETIME1         BRANCH          MASKSW TO GETIME2
                DISPLAY         *PHPOS:VPOS,"__:__ ?m";
*
.Get the Hour
.
GETIME2         KEYIN           *PHPOS:VPOS,*+,*RV,HOURWORK;
                GOTO            GETIME6 IF F5
                GOTO            GETIME7 IF EOS
.
                COMPARE         ONE,HOURWORK
                GOTO            GETIME1 IF LESS
                COMPARE         THIRTEEN,HOURWORK
                GOTO            GETIME1 IF NOT LESS
                MOVE            HOURWORK,HOURWRK1
*
.Get the Minute
.
                KEYIN           *H HPOS,*DV,HOURWORK,*HA 1,*+,MINWORK;
                GOTO            GETIME1 IF F5
.
                COMPARE         ZERO,MINWORK
                GOTO            GETIME1 IF LESS
                COMPARE         SIXTY,MINWORK
                GOTO            GETIME1 IF NOT LESS
                MOVE            MINWORK,DIM2
                REP             SPACZERO,DIM2
*
.am or pm ?
.
GETIME3         MOVE            LOWA,REPLY
                COMPARE         TWELVE,HOURWORK
.         &IF EQUAL
                GOTO            $$$00000 IF NOT EQUAL
                MOVE            LOWP,REPLY
.         &XIF
$$$00000
                COMPARE         SEVEN,HOURWORK       // 1..6,12 == pm    7..11 == am
.         &IF LESS
                GOTO            $$$00001 IF NOT LESS
                MOVE            LOWP,REPLY
.         &XIF
$$$00001
                KEYIN           *PHPOS:VPOS,*HA 6,*DV,REPLY:
                                *H HPOS,*HA 3,*DV,DIM2,*HA 1,*IT,*+,*RV,REPLY;
                GOTO            GETIME1 IF F5
.
                REP             CAPREP,REPLY
                MOVE            AM,DIM3
                CMATCH          "a",REPLY
                GOTO            GETIME4 IF NOT EQUAL
*
.Change Twelve Am to Zero
.
                COMPARE         TWELVE,HOURWORK
                GOTO            GETIME5 IF NOT EQUAL
                MOVE            ZERO,HOURWORK
                GOTO            GETIME5
*
.Change to Military Time
.
GETIME4         CMATCH          LOWP,REPLY
                GOTO            GETIME3 IF NOT EQUAL
                MOVE            PM,DIM3
                COMPARE         TWELVE,HOURWORK
                GOTO            GETIME5 IF EQUAL
                ADD             TWELVE,HOURWORK
*
.Format the Time & Display it
.
GETIME5         PACK            TIME WITH HOURWRK1,COLON,DIM2,SPACE,DIM3
                DISPLAY         *IN,*H HPOS,TIME;
                RETURN
*
.Display the Mask
.
G2ETIME1        BRANCH          MASKSW TO G2ETIME2                                    
                DISPLAY         *PHPOS:VPOS,"__:__";
*
.Get the Hour
.
G2ETIME2        KEYIN           *PHPOS:VPOS,*+,*RV,HOURWORK;
                GOTO            GETIME6 IF F5
                GOTO            GETIME7 IF EOS
.
                COMPARE         ZERO,HOURWORK
                GOTO            G2ETIME1 IF LESS
                COMPARE         TWENTY4,HOURWORK
                GOTO            G2ETIME1 IF NOT LESS
*
.Get the Minute
.
                KEYIN           *H HPOS,*DV,HOURWORK,*HA 1,*+,MINWORK;
                GOTO            G2ETIME1 IF F5
.
                COMPARE         ZERO,MINWORK
                GOTO            G2ETIME1 IF LESS
                COMPARE         SIXTY,MINWORK
                GOTO            G2ETIME1 IF NOT LESS
                MOVE            MINWORK,DIM2
                REP             SPACZERO,DIM2
*
.Format the Time & Display it
.
                PACK            TIME WITH HOURWORK,COLON,DIM2
                DISPLAY         *H HPOS,TIME;
                RETURN
*
.Abort the Routine
.
GETIME6         MOVE            ONE,FLAG1
                RETURN
*
.Require Time Entry
.
GETIME7         BRANCH          REQFLAG TO GETIMEX                                
                MOVE            ONE,EOSFLAG
                RETURN
+..............................................................................
.
. Make Sure That the Date Entered is the Same
.  or after the Current Date
.
. Enter with:   JDAYWORK = Julian Date Specified
.               YEARWORK = Year Specified
.
. Exits with:   EQUAL    = Valid Date
.               NOT EQUAL= Invalid Date
.               SAMEDAY  = 1 Indicates Different Date as Today
.                          0 Indicates Same Date as Today
.
CHECKDT         MOVE            ONE,SAMEDAY
.
                CLOCK           YEAR,DIM2
                MOVE            DIM2,NWORK1
                COMPARE         NWORK1,YEARWORK
                GOTO            CHECKDT2 IF LESS
                GOTO            CHECKDT1 IF NOT EQUAL
.
                CLOCK           DAY,DIM3
                MOVE            DIM3,NWORK1
                COMPARE         NWORK1,JDAYWORK
                GOTO            CHECKDT2 IF LESS
                GOTO            CHECKDT1 IF NOT EQUAL
*
.Indicate Same Date
.
                MOVE            ZERO,SAMEDAY
*
.Signify Date OK
.
CHECKDT1        COMPARE         ZERO,ZERO
                RETURN
*
.Indicate Invalid Date
.
CHECKDT2
                DISPLAY         *CLICK,*HD,*EL,INVDATE;                               
                GOTO            CHECKTOV             // Check override of bad date      
+..............................................................................
.
.Make Sure That the Time Entered is Equal to or
.  After the Current Time.
.
. Enter with:   HOURWORK = Hour Specified
.               MINWORK  = Minute Specified
.
. Exits with:   EQUAL    = Valid Time
.               NOT EQUAL= Invalid Time
.
CHECKTM         CLOCK           TIME,TIME
                SETLPTR         TIME,2
                MOVE            TIME,NWORK1
                COMPARE         NWORK1,HOURWORK
                GOTO            CHECKTM2 IF LESS
                GOTO            CHECKTM1 IF NOT EQUAL
.
                SETLPTR         TIME,5
                RESET           TIME,4
                MOVE            TIME,NWORK1
                RESET           TIME
                COMPARE         NWORK1,MINWORK
                GOTO            CHECKTM2 IF LESS
.
CHECKTM1        COMPARE         ZERO,ZERO
                RETURN
.
CHECKTM2
                DISPLAY         *CLICK,*HD,*EL,INVTIME;

CHECKTOV
                DISPLAY         *HA 5,USEANYW;                                   
                CALL            KREPLYN                                           
                CMATCH          YES,REPLY                                     
                RETURN          // Sets EQUAL if OK                
...............................................................................
.
. Make Sure the Ending Time is After the Starting Time
.
.  Enter with:  HOUR    = Starting Hour
.               MIN     = Starting Minute
.               ENDHOUR = Ending Hour
.               ENDMIN  = Ending Minute
.
.  Exits with:    FLAG1 = 1 - Invalid Time
.                         0 - Valid Time
.
CHECKEND        MOVE            ZERO,FLAG1
.
                COMPARE         ZERO,ENDHOUR
                RETURN          IF EQUAL    Ends at Midnight
.
                COMPARE         ENDHOUR,HOUR
                RETURN          IF LESS
                GOTO            CHCKEND1 IF NOT EQUAL
.
                COMPARE         ENDMIN,MIN
                RETURN          IF LESS
.
CHCKEND1        KEYIN           *CLICK,*HD,*EL,*DV,EBFST,REPLY;
                MOVE            ONE,FLAG1
                RETURN
+..............................................................................
.
.Position the Table to the Starting Time
.
.  Enter with: HOUR = Starting Hour
.              MIN  = Starting Minute
.
.  Exits with: TPOS = Table Starting Position
.
.  Note: Will Round Starting Time Down to the Even Quarter Hour
.        (ie. 8:24 -> 8:15,  10:59 -> 10:45, etc.)
.  Note II: Ver 2.7.A Changed the implementation of the minutes, so the above
.           Note is no longer valid. See proc. ROUNDTIME for new implementation.
.
POSITABL        MOVE            HOUR,TPOS
                MULT            FOUR,TPOS
                MOVE            MIN,NWORK1
     
                CALL            ROUNDTIME         // Round to the nearest Quarter minute. 
                ADD             NWORK1,TPOS
                ADD             ONE,TPOS
                RESET           TABLE,TPOS
                RETURN

+...............................................................................
.
.   Rounds the minutes to the nearest Quarter Hour. Added for Ver 2.7.A.
.
.  Less than -   0  7  15  22  30  37  45  52  59
.                |  |   |   |   |   |   |   |   |
.                \ / \ / \ / \ / \ / \ / \ / \ /
.  Num 15 min-    0   1   1   2   2   3   3   4
.    Blocks
.
.  Enter with :    NWORK1 = Minutes to round.
.  Exit with  :    NWORK1 = Number of 15 minute blocks to allocate.
.                                                                            
ROUNDTIME
                COMPARE         SEVEN,NWORK1
                IF              LESS
                MOVE            ZERO,NWORK1
                ELSE
                COMPARE         TWENTY2,NWORK1
                IF              LESS
                MOVE            ONE,NWORK1
                ELSE
                COMPARE         THIRTY7,NWORK1
                IF              LESS
                MOVE            TWO,NWORK1
                ELSE
                COMPARE         FIFTY2,NWORK1
                IF              LESS
                MOVE            THREE,NWORK1
                ELSE
                MOVE            FOUR,NWORK1
                ENDIF
                ENDIF
                ENDIF
                ENDIF
                RETURN
+...............................................................................
.
. SHOWAPTS                                                                   
.
. Showapts displays a box on the main menu screen, just below the current date
.   and time box. In this box is the date and time of the users next event
.   scheduled in thier calendar events file. If there are no events scheduled or
.   all events are before the current date and time, then the appropriate
.   message is displayed.
.
. Enter with :     USRNO    = User number.
.                  YEARWORK = Current year.
.                  JDAYWORK = Current Julian date.
.
. Exits with :     Box drawn on screen with next appointment displayed in it.
.
*
SHOWAPTS
                TRAP            SHOW3 IF IO                                               
*
.Open the files
.
                OPEN            AGENDA,FSA,SHARE
                CALL            CLOCKDT
                PACK            KEYWORK WITH USRNO,YEARWORK,JDAYWORK
                FILEPI          1;AGENDA
                READ            AGENDA,KEYWORK;;
*
.Read through the records
.
SHOW1           FILEPI          1;AGENDA
                READKS          AGENDA;USRNO1,YEAR,JULDAY,HOUR,MIN,COUNTER,ENDHOUR,ENDMIN:
                                STIME,ETIME,TPOS,NBLOCKS,SECFLAG,TFLAG,DATA
                GOTO            SHOW3 IF OVER
                MATCH           NOTEMSG,STIME
                GOTO            SHOW1 IF EQUAL
                COMPARE         USRNO1,USRNO
                GOTO            SHOW3 IF LESS
*
.Find the correct next appointment, compare the day and time.
.
.Year
                COMPARE         YEARWORK,YEAR
                GOTO            SHOW1 IF LESS
                GOTO            SHOW2 IF GREATER
.Day
                COMPARE         JDAYWORK,JULDAY
                GOTO            SHOW1 IF LESS
                GOTO            SHOW2 IF GREATER
.Hour
                COMPARE         HOURWORK,HOUR
                GOTO            SHOW1 IF LESS
                GOTO            SHOW2 IF GREATER
.Minute
                COMPARE         MINWORK,MIN
                GOTO            SHOW1 IF LESS
                GOTO            SHOW2 IF GREATER
                IF              EQUAL
                DISPLAY         *B,*B,*B,*B,*B;
                GOTO            SHOW2
                ENDIF
*
.Yes, user has an appointment to attend in the future.
.
SHOW2           COMPARE         COUNTDWN,ZERO                     
                GOTO            SHOW2X IF EQUAL
                COMPARE         JDAYWORK,JULDAY
                GOTO            SHOW2X IF GREATER
                COMPARE         HOURWORK,HOUR
                GOTO            SHOW2X IF GREATER
                MOVE            MIN,TIMEDIF
                SUB             MINWORK,TIMEDIF
                COMPARE         COUNTDWN,THREE
                GOTO            DO3 IF EQUAL
                COMPARE         TIMEDIF,FIVE
                IF              EQUAL
                DISPLAY         *B,*W,*B,*W,*B,*W,*B,*W,*B;
                ENDIF
                COMPARE         TIMEDIF,FOUR
                IF              EQUAL
                DISPLAY         *B,*W,*B,*W,*B,*W,*B;
                ENDIF
DO3             COMPARE         TIMEDIF,THREE
                IF              EQUAL
                DISPLAY         *B,*W,*B,*W,*B;
                ENDIF
                COMPARE         TIMEDIF,TWO
                IF              EQUAL
                DISPLAY         *B,*W,*B;
                ENDIF
                COMPARE         TIMEDIF,ONE
                IF              EQUAL
                DISPLAY         *B;
                ENDIF           JLS
SHOW2X          MOVE            JDAYWORK,JDAYWRK1
                MOVE            YEARWORK,YEARWRK1
                MOVE            JULDAY,JDAYWORK
                MOVE            YEAR,YEARWORK
                CALL            JULGREG
                DISPLAY         *V 10,*H 43,ULC,*RPTCHAR HE:19,URC:
                                *N,*H 43,VE,SPACE,*HON,NEXTAPT,*HOFF,*H 63,VE:
                                *N,*H 43,VE,SPACE,DATEST,DATE,*H 63,VE:
                                *N,*H 43,VE,SPACE,TIMEST,STIME,*H 63,VE:
                                *N,*H 43,LLC,*RPTCHAR HE:19,LRC
                MOVE            YEARWRK1,YEAR
                MOVE            JDAYWRK1,JULDAY
                RETURN
*
.No, user does not have any appointments in the future.
.
SHOW3
                DISPLAY         *V 10,*H 43,ULC,*RPTCHAR HE:19,URC:
                                *N,*H 43,VE,SPACE,*HON,NEXTAPT,*HOFF,*H 63,VE:
                                *N,*H 43,VE,"                   ",*H 63,VE:
                                *N,*H 43,VE,NONESCH,*H 63,VE:
                                *N,*H 43,LLC,*RPTCHAR HE:19,LRC
                MOVE            YEARWORK,YEAR
                MOVE            JDAYWORK,JULDAY
                RETURN
+..............................................................................
.
.Check for Conflicting Appointments
.
.  Enter with:  TPOS     = Table Starting Position
.               NBLOCKS  = Number of Blocks to Check
.
.  Exits with:  Equal     = No Conflicts
.               Not Equal = Conflicting Appointments
.
CHECK           COMPARE         ZERO,NBLOCKS
                RETURN          IF EQUAL
.
                RESET           TABLE,TPOS
                MOVE            NBLOCKS,NWORK1
.
CHECK1          CMATCH          CN,TABLE
                RETURN          IF NOT EQUAL
.
                BUMP            TABLE
                SUB             ONE,NWORK1
                GOTO            CHECK1 IF NOT EQUAL
                RETURN
+...............................................................................
.
. Check for Conflicting Meetings                                            
.
.   This subroutine checks to see if the user has any meetings in his planner
.   that conflict with the meeting being scheduled. Only the Cancelled meetings
.   are treated as no conflict, Confirmed and Unconfirmed are treated as
.   conflicts in the schedule.
.
.   Enter with: USRNO1    = User to check on
.               YEARWORK  = Current year
.               JDAYWORK  = Current Julian Date
.               HOUR      = Hour of meeting
.               MIN       = Minute of meeting
.
.  Exits with:  EQUAL     = No Conflicts
.               NOT EQUAL = Conflicting Appointments
.
CHECKMEET
                PACK            DIM17 FROM USRNO1,YEARWORK,JDAYWORK,HOUR,MIN            
*
.Go to the Users number
.
                FILEPI          1;PLAN
                READ            PLAN,DIM17;;
*
.Read through until a conflict is found, or no conflict is found.
.
MEET1           FILEPI          1;PLAN
                READKS          PLAN;USRNO2,YEARWRK1,JULDAY,HOURWRK1,MINWRK1,COUNTER,DIM6:
                                ENDHOUR,ENDMIN,DIM11,STIME,ETIME,USRNAME1,LOCATION:
                                CONFIRM
                GOTO            MEET3 IF OVER
*
.No need to read past current user.
.
                COMPARE         USRNO2,USRNO1
                GOTO            MEET3 IF LESS
*
.Test the year.
.
                COMPARE         YEARWORK,YEARWRK1
                GOTO            MEET1 IF LESS
                GOTO            MEET3 IF GREATER
*
.Test the julian day.
.
                COMPARE         JDAYWORK,JULDAY
                GOTO            MEET1 IF LESS
                GOTO            MEET3 IF GREATER
*
.Test the hour.
.
                COMPARE         HOUR,HOURWRK1
                GOTO            MEET1 IF LESS
                GOTO            MEET3 IF GREATER
*
.Test the minute.
.
                COMPARE         MIN,MINWRK1
                GOTO            MEET1 IF LESS
                GOTO            MEET3 IF GREATER
*
.Yes, a meeting is scheduled for the same time.
.
                IF              EQUAL
*
.Is it cancelled though?
.
                MATCH           CAN,CONFIRM
                GOTO            MEET3 IF EQUAL
                COMPARE         ONE,TWO
                RETURN
                ENDIF

*
.No conflict, go back to PLAN
.
MEET3           COMPARE         TWO,TWO
                RETURN

+..............................................................................
.
.Printer Selection Routine
.
. This Routine will test for a Printer and, if none is available, allow
.  the User to spool the data to the file of his choice.
.
.   Exits with:   FLAG1 = 1   User wishes to Abort Printing
.
SPOOL           MOVE            ZERO,FLAG1
                
                GOTO            SPOOL2        
.
SPOOL1X
                NORETURN        // CLEAR 'CMDKEY' TRAP CALLER
                MOVE            ONE,FLAG1
                RETURN
*
.See if the Current Spool File Name is OK                         
.
SPOOL2          PACK            SPLNAME FROM SPLN,".",SPLE
                MOVE            SPLNAME,ADDRESS1
                TRAP            SPOOL1X IF ESCAPE                                 
                TRAP            SPOOL1X IF F27                                     
                KEYIN           *HD,*EL,*DV,PRTNM,*DV,SPLNAME:
                                *HA -26,*RV,SPLNAME;
                TRAPCLR         ESCAPE                                            
                TRAPCLR         F27                                                 
                CMATCH          SPACE,SPLNAME
                GOTO            SPOOL2 IF EOS
                GOTO            SPOOL2 IF EQUAL    
*
.Open the Spool File
.
SPOOL2O
                CMOVE           NO,REPLY                       // Default append.     
                KEYIN           *HD,*EL,*DV,OVRWRT,*DV,REPLY:
                                *HA -1,*RV,REPLY;                                       
                MOVE            ONE,SPLFLAG
                CMATCH          NO,REPLY                       // Append or Overwrite? 
                GOTO            SPOOL2P IF EQUAL               // Goto Append.             
                SPLOPEN         SPLNAME                        // Overwrite Print file.   
                DISPLAY         *HD,*EL,OVRWRT2,SPLNAME,*W2;                              
                RETURN          // Go Back                
.
SPOOL2P         SPLOPEN         SPLNAME,"Q"                    // Append Print file.       
                DISPLAY         *HD,*EL,APDFILE,SPLNAME,*W2;                             
                RETURN
.                                         OPERATOR STARTED WITH FILE EXTENSION
SPOOL2E
                PACK            ADDRESS1 USING SPLN,SPLNAME

SPOOL2R
                MOVE            ADDRESS1,SPLNAME
                GOTO            SPOOL2O
.                                        OPERATOR STARTED WITH ENVIRONMENT

SPOOL2V
                PACK            ADDRESS1 USING SPLN,SLASH,SPLE,SPLNAME
                GOTO            SPOOL2R
+..............................................................................
.
.Gregorian Date to Julian Date Conversion
.
.  Enter with:  MONWORK  = Gregorian Month
.               DAYWORK  = Gregorian Day
.               YEARWORK = Year
.
.  Exits with:  JDAYWORK = Julian Date
.
GREGJUL         CALL            YEARCOMP
                MOVE            ZERO,JDAYWORK
                MOVE            MONWORK,NWORK1
.
GREGJUL1        SUB             ONE,NWORK1
                GOTO            GREGJUL2 IF ZERO
.
                LOAD            NWORK2 BY NWORK1 FROM THIRTY1,DAYFEB,THIRTY1,THIRTY:
                                THIRTY1,THIRTY,THIRTY1,THIRTY1:
                                THIRTY,THIRTY1,THIRTY,THIRTY1
.
                ADD             NWORK2,JDAYWORK
                GOTO            GREGJUL1
.
GREGJUL2        ADD             DAYWORK,JDAYWORK
                RETURN
+..............................................................................
.
.Obtain the Current Time and Date
.
. Enter with:  TIMESWCH = 0  Non-Military Time (hh:mm ?m)
.                         1  Military Time (hh:mm)
.
.             DATESWCH  = 0  mm/dd/yy Format
.                         1  dd mmm 20yy Format
.
.  Exits with: JDAYWORK = Current Julian Day
.              YEARWORK = Current Year
.                  DATE = Formatted Date
.              HOURWORK = Current Hour
.               MINWORK = Current Minute
.                SECOND = Current Second
.                  TIME = Formatted Time
.
.
.Clock the Current Date
.
CLOCKDT         CLOCK           YEAR,DIM2
                MOVE            DIM2,YEARWORK
.
                CLOCK           DAY,DIM3
                MOVE            DIM3,JDAYWORK
.
                CALL            JULGREG
*
.Clock the Current Time
.
                CLOCK           TIME,TIME
                SETLPTR         TIME,2
                MOVE            ZERO,HOURWORK
                MOVE            TIME,HOURWORK
.
                RESET           TIME,4
                SETLPTR         TIME,5
                MOVE            ZERO,MINWORK
                MOVE            TIME,MINWORK
.
                RESET           TIME,7
                SETLPTR         TIME,8
                MOVE            ZERO,SECOND
                MOVE            TIME,SECOND
+..............................................................................
.
. Format the Time
.
.  Enter with:  HOURWORK = Hour
.                MINWORK = Minute
.
.  Exits with:  TIME = Formatted Time
.
.               If TIMESWCH = 0, Format is hh:mm ?m
.               If TIMESWCH = 1, Format is hh:mm
.
.  Note: If HOURWORK = SEQ, then TIME will be set to "Note"
.
NICETIME        COMPARE         SEQ,HOURWORK
                GOTO            NICETIM1 IF NOT EQUAL
                MOVE            NOTEMSG,TIME
                RETURN
.
NICETIM1
                BRANCH          TIMESWCH OF N2ICETIM // Military format
                MOVE            AMSP,DIM3
                MOVE            HOURWORK,INDEX
                COMPARE         TWELVE,INDEX
                GOTO            NICETIM2 IF LESS
                MOVE            PMSP,DIM3
.
NICETIM2        COMPARE         ZERO,INDEX
                GOTO            NICETIM3 IF NOT EQUAL
                MOVE            TWELVE,INDEX
                GOTO            NICETIM4
.
NICETIM3        COMPARE         THIRTEEN,INDEX
                GOTO            NICETIM4 IF LESS
                SUB             TWELVE,INDEX
.
NICETIM4        MOVE            MINWORK,DIM2
                REP             SPACZERO,DIM2
                PACK            TIME WITH INDEX,COLON,DIM2,DIM3
                RETURN
.
N2ICETIM        PACK            TIME WITH HOURWORK,COLON,MINWORK
                REP             SPACZERO,TIME
                RETURN
+..............................................................................
.
.Julian Date to Gregorian Date Conversion
.
.  Enter with:  JDAYWORK = JULIAN DAY
.               YEARWORK = YEAR
.
.               DATESWCH = 0  mm/dd/yy Format
.                          1  dd mmm 20yy Format
.
.  Exits with:  MONWORK  = Gregorian Month
.               DAYWORK  = Gregorian Day
.               YEARWORK = Year
.                 DATE   = Formatted Date (dd mmm 20yy)
.
.Convert the Date
.
JULGREG         MOVE            TWENTY8,NWORK3
                MOVE            ZERO,MONWORK
                MOVE            JDAYWORK,NWORK2
.
                MOVE            YEARWORK,NWORK1
                DIV             FOUR,NWORK1
                MULT            FOUR,NWORK1
                COMPARE         YEARWORK,NWORK1
                GOTO            JULGREG1 IF NOT EQUAL
                ADD             ONE,NWORK3
.
JULGREG1        ADD             ONE,MONWORK
                LOAD            NWORK1 BY MONWORK FROM THIRTY1,NWORK3,THIRTY1,THIRTY:
                                THIRTY1,THIRTY,THIRTY1,THIRTY1:
                                THIRTY,THIRTY1,THIRTY,THIRTY1
.
                SUB             NWORK1,NWORK2
                GOTO            JULGREG2 IF EQUAL
                GOTO            JULGREG1 IF NOT LESS
.
JULGREG2        ADD             NWORK1,NWORK2
                MOVE            NWORK2,DAYWORK
*
.Format the Date (mm/dd/yy)
.
                BRANCH          DATESWCH OF JGE
                PACK            DATE WITH MONWORK,SLASH,DAYWORK,SLASH,YEARWORK
                REP             SPACZERO,DATE
                RETURN
*
.Format the Date (dd mmm 20yy)
.
JGE             LOAD            DIM3 BY MONWORK FROM JAN,FEB,MAR,APR,MAY:
                                JUN,JUL,AUG,SEP,OCT,NOV,DEC
                PACK            DATE WITH DAYWORK,SPACE,DIM3,SPACE,YEARPREFIX,YEARWORK
                RETURN

+...............................................................................
.
. CALCWEEKS                                                                 
.
. Calcweeks sets up the variables for COMPWEEKS (JDAYWORK, MON, FSTDAY) and then
.   uses the result of compweeks to multiply by 7 (days in week) to find out
.   exactly how many days the program will add to JDAYWORK to find the next
.   Julian date.
.
.
.   Enter with:      JDAYWORK = Current Julian date.
.
.   Exits with:      NWORK1 = Number of days to advance the current Julian date
.                             to preserve the graphical calendar position.
.
CALCWEEKS
*
.Save incoming month and get month of julian date                           
.
                MOVE            MON,MONSV
                CALL            JULGREG
                MOVE            MONWORK,MON
                CALL            YEARCOMP
*
.Save julian date, compute the column position of the 1st of the month
.
                MOVE            JDAYWORK,JDAYWRK1
                MOVE            ONE,DAYWORK
                CALL            GREGJUL
                CALL            FINDOW
*
.Restore julian date, first day column and compute NUMWKS
.
                MOVE            NWORK2,FSTDAY
                MOVE            JDAYWRK1,JDAYWORK
                CALL            COMPWEEKS
*
.Calculate how many days to skip and restore incoming month
.
                MOVE            SEVEN,NWORK1
                MULT            NUMWKS BY NWORK1
                MOVE            MONSV,MON
                RETURN

+...............................................................................
.
. COMPWEEKS                                                                 
.
. Computes the number of weeks in a month and then tells us the three columns
.    two columns, or one column that hold the largest amount of days,
.    vertically. Then, the variable NUMWKS is given either a 4 or a 5 depending
.    on where our Julian day falls. If it falls within one of the longest
.    columns, NUMWKS is given a five to tell us to advance 5 weeks.
.
.
.    Enter with:     JDAYWORK = Current Julian date.
.                    MON      = Current Gregorian month.
.                    FSTDAY   = Column position of the 1st day of the month
.                               given by MON. (1-7)
.
.    Exits with:     NUMWKS   = The number of weeks to advance the current
.                               day in order to preserve the days graphical
.                               position.
.
COMPWEEKS
*
.Compute the position of the current date                                    
.
                MOVE            NWORK1,CURDAY
                CALL            FINDOW
                MOVE            CURDAY,NWORK1
                MOVE            NWORK2,CURDAY
*
.Determine the Number of Days in the Month
.
                LOAD            NUMDAYS BY MON FROM THIRTY1,DAYFEB,THIRTY1,THIRTY:
                                THIRTY1,THIRTY,THIRTY1,THIRTY1:
                                THIRTY,THIRTY1,THIRTY,THIRTY1
*
.Compute the number of weeks for a 31 day month
.
                COMPARE         NUMDAYS TO THIRTY1
                IF              EQUAL
*
.Compute the three columns with five days in them
.
                MOVE            FSTDAY TO SCNDAY
                MOVE            FSTDAY TO THRDAY
                ADD             ONE TO SCNDAY
                ADD             TWO TO THRDAY
                COMPARE         SCNDAY TO SEVEN
                IF              LESS
                SUB             SEVEN FROM SCNDAY
                ENDIF
                COMPARE         THRDAY TO SEVEN
                IF              LESS
                SUB             SEVEN FROM THRDAY
                ENDIF
*
.Check to see if our day falls in one of those three columns
.
                COMPARE         CURDAY TO FSTDAY
                IF              EQUAL
                MOVE            FIVE TO NUMWKS
                ELSE
                COMPARE         CURDAY TO SCNDAY
                IF              EQUAL
                MOVE            FIVE TO NUMWKS
                ELSE
                COMPARE         CURDAY TO THRDAY
                IF              EQUAL
                MOVE            FIVE TO NUMWKS
                ELSE
                MOVE            FOUR TO NUMWKS
                ENDIF
                ENDIF
                ENDIF
                ENDIF
*
.Compute the number of weeks for a 30 day month
.
                COMPARE         NUMDAYS TO THIRTY
                IF              EQUAL
*
.Compute the two columns with five days in them
.
                MOVE            FSTDAY TO SCNDAY
                ADD             ONE TO SCNDAY
                COMPARE         SCNDAY TO SEVEN
                IF              LESS
                SUB             SEVEN FROM SCNDAY
                ENDIF
*
.Check to see if our day falls in one of those two columns
.
                COMPARE         CURDAY TO FSTDAY
                IF              EQUAL
                MOVE            FIVE TO NUMWKS
                ELSE
                COMPARE         CURDAY TO SCNDAY
                IF              EQUAL
                MOVE            FIVE TO NUMWKS
                ELSE
                MOVE            FOUR TO NUMWKS
                ENDIF
                ENDIF
                ENDIF
*
.Compute the number of weeks for a 29 day month
.
                COMPARE         NUMDAYS TO TWENTY9
                IF              EQUAL
*
.Check to see if our day falls in that column
.
                COMPARE         CURDAY TO FSTDAY
                IF              EQUAL
                MOVE            FIVE TO NUMWKS
                ELSE
                MOVE            FOUR TO NUMWKS
                ENDIF
                ENDIF
*
.Compute the number of weeks for a 28 day month, always 4
.
                COMPARE         NUMDAYS TO TWENTY8
                IF              EQUAL
                MOVE            FOUR TO NUMWKS
                ENDIF
                RETURN
*...........................................................................
.
.Routine to Add an Appointment to the Selected Day's Table
.
. Enter with:  TFLAG = (T)entative or (F)irm Appointment
.            NBLOCKS = Number of 15 Minute Blocks to Flag
.               TPOS = Starting Position
.
.Position the Table
.
ADDTABLE        COMPARE         ZERO,NBLOCKS
                RETURN          IF EQUAL
.
                RESET           TABLE,TPOS
                MOVE            NBLOCKS,NWORK2
                MOVE            TFLAG,REPLY
                REP             TFREP,REPLY
*
.Change the Table; Catch Conflicts
.
ADDTABL1        CMATCH          CN,TABLE
                GOTO            ADDTABL2 IF EQUAL
                CMOVE           CONFREP,TABLE
                GOTO            ADDTABL3
.
ADDTABL2        CMOVE           REPLY,TABLE
*
.Continue Flagging till Done
.
ADDTABL3        BUMP            TABLE
                GOTO            ADDTABL4 IF EOS
                SUB             ONE,NWORK2
                GOTO            ADDTABL1 IF NOT ZERO
*
.Install the Divider If We Ended Against a Like Appointment
.
                CMATCH          REPLY,TABLE
                GOTO            ADDTABL4 IF NOT EQUAL     // Not Same Type
                CMOVE           006,TABLE
*
.Install the Divider If We Started Against a Like Appointment
.
ADDTABL4        RESET           TABLE,TPOS
                BUMP            TABLE,-1
                RETURN          IF EOS                    // Started at Midnight
                CMATCH          REPLY,TABLE
                RETURN          IF NOT EQUAL              // Not the Same Type
                BUMP            TABLE
                CMOVE           006,TABLE
                RETURN
+............................................................................
.
.Routine to Remove an Appointment from the Selected Day
.
. Enter with: NBLOCKS = Number of Blocks to Remove
.                TPOS = Table Starting Position
.               TFLAG = (T)entative or (F)irm Appointment
.               USRNO = User Number
.            JDAYWORK = Julian Day
.            YEARWORK = Year
.               KEY18 = Key to be Excluded
.
DELTABLE        COMPARE         ONE,COUNT
                RETURN          IF LESS
.
                MOVE            HOUR TO HOURWRK1      // Save the incoming HOUR            
                MOVE            NBLOCKS,NWORK2        // Save the Number of Blocks
                RESET           TABLE,TPOS
*
.See if We are Removing a Conflicting Appointment
.
DELTABL1        CMATCH          CONFREP,TABLE
                GOTO            DELTABL2 IF EQUAL    // We Found a Conflict
                CMATCH          VB,TABLE               // Check to see if it is a          
                IF              EQUAL                   // vertical bar.                   
                COMPARE         NBLOCKS,NWORK2         // If the vb is the 1st block       
                IF              EQUAL                                                    
                CMOVE           CN,TABLE               // Then free the space up.         
                ELSE           
                CMOVE           SPACE,TABLE            // Else, move a space to           
                ENDIF           
                ELSE            // that position.                 
                CMOVE           CN,TABLE                                     
                ENDIF           // End.                            
.
                BUMP            TABLE
                SUB             ONE,NWORK2
                GOTO            DELTABL1 IF NOT ZERO
*
.Is the Next Character a Divider ?
.
                CMATCH          006,TABLE
                RETURN          IF NOT EQUAL
                MOVE            TFLAG,REPLY
                REP             TFREP,REPLY
                CMOVE           REPLY,TABLE
                RETURN
*
.We Need to Rebuild the Table for the Selected Date
.
DELTABL2        PACK            KEY WITH USRNO,YEARWORK,JDAYWORK
                FILEPI          1;AGENDA
                READ            AGENDA,KEY;;
*
.Reset the Table
.
                CALL            PACK01                                           
                MOVE            ONE,COUNT
*
.Read Through the Appointments
.
DELTABL3        FILEPI          1;AGENDA
                READKS          AGENDA;DIM11,HOUR,MIN,COUNTER,ENDHOUR,ENDMIN:
                                STIME,ETIME,NWORK2A,NWORK2B,SECFLAG,TFLAG,DATA
                RETURN          IF OVER
*
.Right User/Year/Day ?
.
                COMPARE         ONE,FLAG5                                                 
                IF              EQUAL                                                            
                MATCH           KEY,DIM11
                RETURN          IF NOT EQUAL
                ELSE           
                MATCH           KEY,DIM11                                                
DELTABL3A
                IF              NOT EQUAL            // Check. Read the next record.        
                READKS          AGENDA;DIM11,HOUR,MIN,COUNTER,ENDHOUR,ENDMIN:
                                STIME,ETIME,NWORK2A,NWORK2B,SECFLAG,TFLAG,DATA           
                COMPARE         ZERO,HOUR           // Are we at the end of the records?   
                RETURN          IF EQUAL            // If so, return.                     
                COMPARE         HOURWRK1,HOUR       // Are we at the right record?        
                RETURN          IF EQUAL            // We found the record we need.       
                GOTO            DELTABL3A           // Continue search for record         
                ENDIF           //  with same hour.                   
                ENDIF           
*
.Disregard Notes
.
                MATCH           NOTEMSG,STIME
                GOTO            DELTABL4 IF NOT EQUAL
                MOVE            ZERO,TPOS
                MOVE            ZERO,NBLOCKS
                GOTO            DELTABL5
*
.Excluding a Key ?
.
DELTABL4        PACK            KEYWORK WITH DIM11,HOUR,MIN,COUNTER
                MATCH           KEYWORK,KEY18
                GOTO            DELTABL3 IF EQUAL         // Exclude This Key
*
.Compute the Table Starting Position and Number of Blocks
.
                CALL            POSITABL
                CALL            COMPUTE
*
.Verify the Appointment Record Values
.
DELTABL5        COMPARE         TPOS,NWORK2A
                GOTO            DELTABL6 IF NOT EQUAL
                COMPARE         NBLOCKS,NWORK2B
                GOTO            DELTABL7 IF EQUAL
*
.Correct the Appointment Record
.
DELTABL6        PACK            KEY17 WITH DIM11,HOUR,MIN,COUNTER
                DISPLAY         *CLICK;

                CALL            AG1090
                CALL            AG1010
*
.Update the Table
.
DELTABL7        COMPARE         ZERO,NBLOCKS        // Note ?
                GOTO            DELTABL3 IF EQUAL   // Yes....
                CALL            ADDTABLE
                ADD             ONE,COUNT
                GOTO            DELTABL3
+............................................................................
.
.Graphically Display a Day's Appointments
.
. Enter with:  JDAYWORK = Julian Day
.              GRAPHPOS = 1  Begin Graphing at Midnight
.                         2  Begin Graphing at Seven AM
.                         3  Begin Graphing at Noon
.
DISPDAY         LOAD            NWORK2 BY GRAPHPOS FROM ZERO,SEVEN,TWELVE
                MULT            FOUR,NWORK2
                RESET           TABLE,NWORK2
                MOVE            TWENTY9,HPOS
                COMPARE         ONE,DATESWCH                                          
                IF              EQUAL                                                        
                SUB             ONE,JDAYWORK                                           
                ENDIF           039
*
.Determine the Graph Vertical Position
.
                SEARCH          JDAYWORK FROM DAY1 TO SEVEN INTO VPOS
                IF              OVER                                                         
                COMPARE         ONE,DATESWCH                                          
                IF              EQUAL                                                         
                ADD             ONE,JDAYWORK                                           
                ENDIF           039
                RETURN          039
                ENDIF           039
                ADD             FIVE,VPOS
.
                DISPLAY         *P30:VPOS,*RPTCHAR SPACE:49,*HON;
*
.Display The Graph
.
DISPDAY1        ADD             ONE,NWORK2
                ADD             ONE,HPOS
                COMPARE         "79",HPOS
                GOTO            DISPDAY2 IF EQUAL
.
                RESET           TABLE,NWORK2
                CMATCH          CN,TABLE
                GOTO            DISPDAY1 IF EQUAL
                MOVE            TABLE,REPLY
                DISPLAY         *H HPOS,REPLY;
                GOTO            DISPDAY1
.
DISPDAY2        DISPLAY         *HOFF;
                COMPARE         ONE,DATESWCH                                          
                IF              EQUAL                                                      
                ADD             ONE,JDAYWORK                                          
                ENDIF           039
                RETURN
+...........................................................................
.
.Internal Error Handling
.
INTERR          DISPLAY         *SETSWALL=1:24:1:80,*HOFF,*B,*HD,*EL,INTERROR;
.         DEBUG
                NORETURN
                GOTO            LOGON
+...........................................................................
.
.Routine to Allow the Selection of a System User
.
.  Enter with: FLAG1 = 0  Don't Allow the Current User
.                      1  Allow Any User
.              FLAG4 = 0
.                      1  DISPLAY "MORE" MESSAGE
.              HPOS  = Horizontal Screen Position
.              VPOS  = Vertical Screen Position
.
.  Exits with: FLAG1 = 0  User Selected
.                      1  Abort Requested (Variables Indeterminate)
.            EOSFLAG = 0  Enter Key Not Pressed
.                      1  Null Entry
.           USRNAME1 = User Name Selected
.             USRNO1 = User Number Selected
.
FINDUSER        CLEAR           DIM20
                MOVE            ZERO,EOSFLAG
                DISPLAY         *HD,*EL,LITENT;
                COMPARE         ZERO,FLAG4
                GOTO            FUKEY IF EQUAL
                DISPLAY         NXT;
FUKEY           KEYIN           *DV,USRNM:
                                *PHPOS:VPOS,*RPTCHAR "_":20,*H HPOS,*IT,*T60,*RV,DIM20;
                DISPLAY         *IN,*H HPOS,DIM20;
                GOTO            FINDUSR6 IF F5
                GOTO            FINDUSR7 IF EOS
                GOTO            FINDUSR7 IF LESS
.
                CMATCH          SPACE,DIM20
                GOTO            FINDUSER IF EQUAL
                REP             CAPREP,DIM20
                MOVE            BLANK20 TO DIM20A         // Clear the Dummy input name.  
                MOVE            DIM20,DIM20A              // Save user inputed name.       
*
.Do the Initial Read
.
                PACK            DIM30 WITH F03,DIM20
.
                TRAP            FINDUSR5 IF IO
                FILEPI          1;USRFILE
                READTAB         USRFILE,DIM30;USERID,USRNO1,USRNAME1,USREXT,LOFLAG,UGROUP:
                                STATDATE,STATTIME,STATFLAG  // Read EXT,Flag 
                MOVE            USRNAME1,DIM20B           // Save USRNAME1 found in file.  
                REP             CAPREP,DIM20B             // Convert to all lower case.    
                TRAPCLR         IO
                GOTO            FINDUSR4 IF OVER
                GOTO            FINDUSR2
*
.Read Generically Through the File
.
FINDUSR1        FILEPI          1;USRFILE
                READKGTB        USRFILE;USERID,USRNO1,USRNAME1,USREXT,LOFLAG,UGROUP:
                                STATDATE,STATTIME,STATFLAG     // Read EXT & Flag  
                GOTO            FINDUSR4 IF OVER
*
.Skip the Secondary Group Records
.
FINDUSR2        MATCH           BLANKS,USERID
                GOTO            FINDUSR1 IF EQUAL
*
.Don't Allow Selecting Oneself If the Flag is Clear
.
                BRANCH          FLAG1 TO FINDUSR3
                COMPARE         USRNO1,CURRUSER
                GOTO            FINDUSR1 IF EQUAL
*
.Highlight the Key in the Name
.
FINDUSR3        MOVE            USRNAME1,DIM30
                REP             CAPREP,DIM30
                SCAN            DIM20,DIM30
                CALL            INTERR IF NOT EQUAL
.
                MOVEFPTR        DIM30,HPOS1
                RESET           USRNAME1,HPOS1
                MOVE            USRNAME1,DIM40
                RESET           USRNAME1
                MOVELPTR        DIM20,INDEX
                SETLPTR         DIM40,INDEX
*
.Right User ?
.
                SETLPTR         DIM20A                    // Reset the LL to 20           
                SETLPTR         DIM20B                    // for Comparison.               
                MATCH           DIM20A,DIM20B             // Compare the two strings.      
                GOTO            FIND3B IF EQUAL           // Skip prompt if they are =.   
                ADD             HPOS,HPOS1
                SUB             ONE,HPOS1

                DISPLAY         *PHPOS:VPOS,USRNAME1,*H HPOS1,*HON,*+,DIM40,*HOFF: 
                                *HD,*EL,CORRUSR;                                  
                CALL            KREPLYY                                          
                GOTO            FINDUSER IF F5
.
                CMATCH          NO,REPLY                                            
                GOTO            FINDUSR1 IF EQUAL
.
FIND3B          MOVE            ZERO,FLAG1
                RETURN
*
.End of User's File Encountered
.
FINDUSR4        KEYIN           *CLICK,*HD,*EL,*DV,NMMU,REPLY;
                GOTO            FINDUSER
*
.Invalid Key Specified
.
FINDUSR5        NORETURN
                KEYIN           *CLICK,*HD,*EL,*DV,INVNMSP,REPLY;
                GOTO            FINDUSER
*
.Abort Requested
.
FINDUSR6        MOVE            ONE,FLAG1
                RETURN
*
.Null Entry
.
FINDUSR7        MOVE            ONE,EOSFLAG
                RETURN
+...............................................................................
.GET TIME FORMAT & MANAGED FILE OPTION FROM SYSTEM PROFILE
.
. GET TIME FORMAT FROM SYSTEM PROFILE
. FORMAT OF TIME RECORD IS LIKE: TIME FORMAT=12 HOUR
.                          -or-  TIME FORMAT=24 HOUR
. FORMAT OF DATE RECORD IS LIKE: DATE FORMAT=American
.                          -or-  DATE FORMAT=European
.
PROFILE
                TRAP            NOFORMAT IF IO                                                
                OPEN            SCRATCH,"agendasys.cfg",SHARE
.  &LOOP
$$$00002
                READ            SCRATCH,SEQ;MSG1     // Read Profile Record
.  &UNTIL OVER
                GOTO            $$$00003 IF OVER
                MATCH           "TIME",MSG1          // Check for 'TIME FORMAT=?'
.    &IF EQUAL
                GOTO            $$$00004 IF NOT EQUAL
                SCAN            "=" IN MSG1          // Look for separator
.      &IF EQUAL
                GOTO            $$$00005 IF NOT EQUAL
                BUMP            MSG1
                CMATCH          "2",MSG1             // "24" HOUR FORMAT ?
.        &IF EQUAL
                GOTO            $$$00006 IF NOT EQUAL
                MOVE            ONE,TIMESWCH         // Set to military time
                MOVE            MSG2,RULE1           // Use Military time rulers
                MOVE            MSG3,RULE2
                MOVE            MSG4,RULE3
.        &XIF
$$$00006
.      &XIF
$$$00005
.    &ELSE
                GOTO            $$$00007
$$$00004
                MATCH           "DATE",MSG1          // Check for 'DATE FORMAT=?'
.      &IF EQUAL
                GOTO            $$$00008 IF NOT EQUAL
                SCAN            "=" IN MSG1          // Look for separator
.        &IF EQUAL
                GOTO            $$$00009 IF NOT EQUAL
                BUMP            MSG1
                CMATCH          "E",MSG1               // "European" FORMAT ?
.          &IF EQUAL
                GOTO            $$$00010 IF NOT EQUAL
                MOVE            ONE,DATESWCH
.          &XIF
$$$00010
.        &XIF
$$$00009
.      &ELSE
                GOTO            $$$00011
$$$00008
                MATCH           "MANAGED",MSG1              // Managed Files ?
.         &IF EQUAL
                GOTO            $$$00012 IF NOT EQUAL
                MOVE            ONE,MANAGESW
.         &XIF
$$$00012
                MATCH           "PROG=",MSG1            // Stop program option ?           
                GOTO            $$$00011 IF NOT EQUAL   // No, keep checking.              
                BUMP            MSG1 BY 5               // Yes,                            
                MOVE            MSG1,EXITPROG           // Get the name.                  
                MOVE            ONE,EXITFLAG            // Yes, use this program name.    
.      &XIF
$$$00011
                MATCH           "ENV=",MSG1             // Alternate Data Environment ?    
                GOTO            $$$00007 IF NOT EQUAL   // No, continue reading.           
                BUMP            MSG1 BY 4               // If yes,                         
                MOVE            MSG1,ENVIRON            // get new Environment name       
.    &XIF
$$$00007
.  &REPEAT
                GOTO            $$$00002
$$$00003
                CLOSE           SCRATCH
                RETURN
NOFORMAT        NORETURN
                RETURN

+.............................................................................
.AGENDA_PRT - Print the Calendar
.
ECPRINT         MOVE            FORTY6,CMDTRAP                                         
                MOVE            JULDAY,SAVEDAY                                        
                MOVE            YEAR,SAVEYR                                         
                MOVE            ONE,PRTSW                                            
                TRAP            ECPRNTXX IF ESCAPE                                   
                TRAP            ECPRNTXX IF F27                                       
*
.Get the Starting Date
.
                IF              (DATESWCH = ONE)                                             
                ADD             ONE,DAY1                                              
                ENDIF           044
                MOVE            DAY1,JDAYWORK        // START OF WEEK (JULIAN)
                MOVE            YEARSTR,YEARWORK     // START OF WEEK (YEAR)
                CALL            JULGREG              // Set up MONWORK/DAYWORK/YEARWORK
                DISPLAY         *P1:24,*EL,LITENT,STDATE,DATE;
.
                MOVE            VPRPOS,HPOS
                MOVE            TWENTY4,VPOS
                MOVE            ONE,MASKSW
                MOVE            ZERO,REQFLAG
                CALL            GETDATE
                BRANCH          FLAG1 TO ECPRNT27
.
                MOVE            JDAYWORK,STARTDAY
                MOVE            YEARWORK,STARTYR
                IF              (DATESWCH = ONE)                                             
                SUB             ONE,JDAYWORK                                          
                ENDIF           044
                CALL            FINDOW               // Round to the 1st Day of the Week
                IF              (DATESWCH = ONE)                                            
                ADD             ONE,JDAYWORK                                         
                ENDIF           044
                SUB             ONE,NWORK2
                SUB             NWORK2,STARTDAY
.         &IF LESS
                GOTO            $$$00013 IF NOT LESS
                ADD             PYEARLEN,STARTDAY
                SUB             ONE,STARTYR
.         &XIF
$$$00013
                MOVE            MONWORK,SMONSAV     // Used to print "->" @ beginning of line
                MOVE            DAYWORK,SDAYSAV
                MOVE            YEARWORK,SYRSAV
*
.Get the Ending Date
.
                CALL            YEARCOMP
                MOVE            JDAYWORK,JULDAY
                MOVE            YEARWORK,YEAR
                MOVE            ONE,GRAPHSW
                CALL            GRAPH                // Correct the ending date etc      
. Enter with:  JULDAY  = Julian Date Selected
.              YEAR    = Year Selected
.              YEARLEN = Length of Year Selected (Days)
.              GRAPHSW = 1 - Force Graph to be Redrawn
.                        0 - Don't Redraw if Already On the Screen
.
. Exits with:  YEARSTR = Week's Starting Year
.              YEAREND = Week's Ending Year
.               DAY 1 - DAY 7 = Julian Dates
.              GRAPHSW = 0
.
                IF              (DATESWCH = ONE)                                            
                ADD             ONE,DAY7                                              
                ADD             ONE,DAY1                                              
                ENDIF           044
                MOVE            DAY7,JDAYWORK        // LAST DAY OF WEEK (JULIAN)
                MOVE            YEAREND,YEARWORK     // LAST DAY OF WEEK (YEAR)
                CALL            JULGREG              // Set up MONWORK/DAYWORK/YEARWORK
                DISPLAY         *P1:24,*EL,LITENT,EDDATE,DATE;
.
                MOVE            VPRPOS2,HPOS
                MOVE            TWENTY4,VPOS
                CALL            GETDATE
.
                BRANCH          FLAG1 TO ECPRINT
                MOVE            JDAYWORK,LASTDAY
                MOVE            YEARWORK,LASTYR
.
                IF              (DATESWCH = ONE)                                            
                SUB             ONE,JDAYWORK                                        
                ENDIF           044
                CALL            FINDOW               // Round to the Last Day of the Week
                IF              (DATESWCH = ONE)                                           
                ADD             ONE,JDAYWORK                                         
                ENDIF           044
                COMPARE         SEVEN,NWORK2
.         &IF NOT EQUAL
                GOTO            $$$00014 IF EQUAL
                MOVE            SEVEN,NWORK1
                SUB             NWORK2,NWORK1
                ADD             NWORK1,LASTDAY
.         &XIF
$$$00014
                COMPARE         LASTDAY,YEARLEN      // Past end of year ?
.         &IF LESS
                GOTO            $$$00015 IF NOT LESS
                ADD             ONE,LASTYR        // Wrap to the First of the Next Year
                SUB             YEARLEN,LASTDAY
.         &XIF
$$$00015
*
.Make sure start is before end.
.
                COMPARE         STARTYR,LASTYR
                GOTO            DATEVER1 IF LESS
                GOTO            DATEVER2 IF NOT EQUAL
                COMPARE         STARTDAY,LASTDAY
                GOTO            DATEVER2 IF NOT LESS
DATEVER1        DISPLAY         *HD,*EL,ENDBFST;
                PAUSE           TWO
                GOTO            ECPRINT
DATEVER2
*
.Center the User's Name
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
.Get the Printer; Print a Heading
.
                CALL            SPOOL
                BRANCH          INQSW OF ECINQ6                                        
                BRANCH          FLAG1 TO EC$CMD
.
                MOVE            FORTY7,CMDTRAP                                         
                TRAP            ECPRNTXX IF ESCAPE                                    
                TRAP            ECPRNTXX IF F27                                         
                DISPLAY         *HD,*EL,PRTCAL;
*
. VARIABLES:
.  STARTDAY/STARTYR = 1ST DAY OF WEEK OF BEGINNING DATE
.  LASTDAY/LASTYR = LAST DAY OF THE WEEK OF ENDING DATE
.
.   &LOOP                   LOOP THRU ALL THE DATES REQUESTED (STARTDAY..LASTDAY
$$$00016
.     print heading
                CALL            ECPRNT24                     // Print the Top of Form
                CALL            CALENHDR                     // Print Calendar Heading Line
.                                       // Also compute 'ENDDAY'
                MOVE            ONE,DAYWORK                  // DAYWORK counts 1..ENDDAY
                MOVE            ONE,VPOS                     // VPOS counts 1..7
.     HPOS1 := 1st day of month position
                MOVE            STARTYR,YEARWORK
                CALL            GREGJUL              // convert(MONWORK/DAYWORK/YEARWORK) to JDAYWORK
                IF              (DATESWCH = ONE)                                              
                SUB             ONE,JDAYWORK                                                 
                ENDIF           044
                CALL            FINDOW               // convert(JDAYWORK/YEARWORK) TO NWORK2 (1..7)
                SUB             ONE,NWORK2           // Compute the Horizontal Position
                MULT            THREE,NWORK2         // Each day takes 3 print positions
                ADD             FIVE,NWORK2          // Bias to starting print position
                MOVE            NWORK2,HPOS1         // 'HPOS1' is print position for 'DAYWORK'

                MOVE            DAY1,WRKJUL          // Save "current" week starting day
                MOVE            YEARSTR,WRKYR        // Save "current" week starting year

                MOVE            WRKJUL,WRKJULX       // Save for appointment printing
                MOVE            WRKYR,WRKYRX         // Save for appointment printing
.      &LOOP                             // LOOP THRU THE DAYS OF THE WEEK
$$$00017
.        maybe print DAY calendar for week
                COMPARE         ONE,VPOS               // Delay printing week until Monday
.         &IF NOT EQUAL
                GOTO            $$$00018 IF EQUAL
.           print DAY calendar for week
.            &LOOP                       // Loop thru days of week stopping @ SUN
$$$00019
                COMPARE         DAYWORK,ENDDAY   // Don't print if after last day of mo.
.               &IF NOT LESS
                GOTO            $$$00020 IF LESS
                PRINT           *HPOS1,DAYWORK,SPACE;
.               &XIF
$$$00020
.              print "->" at start of line if printing currently selected date
                COMPARE         SMONSAV,MONWORK
.               &IF EQUAL
                GOTO            $$$00021 IF NOT EQUAL
                COMPARE         SDAYSAV,DAYWORK
.               &IF EQUAL
                GOTO            $$$00022 IF NOT EQUAL
                COMPARE         SYRSAV,YEARWORK
.               &IF EQUAL
                GOTO            $$$00023 IF NOT EQUAL
                PRINT           *2,"->";
.               &XIF
$$$00023
.               &XIF
$$$00022
.               &XIF
$$$00021
                ADD             ONE,DAYWORK          // Increment current day
                ADD             THREE,HPOS1          // Bump to next print position
                COMPARE         TWENTY6,HPOS1       // Off end of line ?
.            &REPEAT WHILE NOT EQUAL     // Not yet...
                GOTO            $$$00019 IF NOT EQUAL
                MOVE            FIVE,HPOS1             // Yes, reset to beginning of line
.         &XIF
$$$00018
.        print DOW (SUN..SAT)
                IF              (DATESWCH = ONE)                                             
                LOAD            REPLY BY VPOS FROM MONDAY,TUESDAY,WEDNESDY:
                                THURSDAY,FRIDAY,SATURDY,SUNDAY                        
                ELSE            044
                LOAD            REPLY BY VPOS FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
                ENDIF           044
                PRINT           *30,REPLY;

.        if IN 'CURRENT' week, read & print GRAPH line
.        STARTDAY/STARTYR = Beginning of "requested" week
.        WRKJUL/WRKYR     = Beginning of "current" week
                PACK            DIM11 WITH USRNO,WRKYR,WRKJUL
                FILEPI          1;GRAPH
                READ            GRAPH,DIM11;USRNO1,NWORK2B,DIM3,COUNTER,TABLE
.         &IF NOT OVER
                GOTO            $$$00024 IF OVER
.AM                                              P
.0   0   0   0   0   0   0   0   0   0   1   1   1   1   1   1   1   ..2   2
.00001111222233334444555566667777888899990000111122223333444455556666..22223333
.^                           ^                   ^
.1 = 12a..12p                2 = 7a..7p          3 = 12p..12a
                LOAD            NWORK2 FROM GRAPHPOS OF ZERO,SEVEN,TWELVE
                MULT            FOUR,NWORK2           // # of slots per hour
                ADD             ONE,NWORK2
                RESET           TABLE,NWORK2          // point to correct 12hour chunk
                MOVE            TABLE,MSG1
                REP             PRINTREP,MSG1         // X->blank  blank->X
                PRINT           *32,MSG1;             // Print the whole graph line
.         &XIF
$$$00024
                ADD             ONE,WRKJUL           // Increment "current" date
                COMPARE         WRKJUL,YEARLEN       // Past end of year ?
.         &IF LESS
                GOTO            $$$00025 IF NOT LESS
                ADD             ONE,WRKYR         // Wrap to the First of the Next Year
                SUB             YEARLEN,WRKJUL
.         &XIF
$$$00025
.        flush print line
                PRINT           SPACE
.        see if done with this week
                ADD             ONE,VPOS
                COMPARE         EIGHT,VPOS
.      &REPEAT WHILE NOT EQUAL
                GOTO            $$$00017 IF NOT EQUAL
.     Print Day's Detail
                CALL            ECPRNT18                     // Print Day's Detail
.     Bump to start of next week
                ADD             SEVEN,STARTDAY                // Bump to 1st day of next week
                COMPARE         STARTDAY,YEARLEN          // Adjust for end-of-year wrap
.      &IF LESS
                GOTO            $$$00026 IF NOT LESS
                SUB             YEARLEN,STARTDAY
                ADD             ONE,STARTYR
.      &XIF
$$$00026
                MOVE            STARTDAY,DAY1
                MOVE            STARTYR,YEARSTR
                MOVE            STARTDAY,JDAYWORK
                MOVE            STARTYR,YEARWORK
                CALL            JULGREG                      // Set up MONWORK/DAYWORK/YEARWORK
                DISPLAY         *P69:24,DATE;

                COMPARE         STARTDAY,LASTDAY         // printed entire calendar request?
                GOTO            $$$00027 IF EQUAL
                GOTO            $$$00016 IF NOT LESS
$$$00027
                COMPARE         STARTYR,LASTYR
                GOTO            $$$00016 IF NOT EQUAL
*
.Printing Complete
.
ECPRNT26    
                RELEASE
.
ECPRNT27        NORETURN
                SPLCLOSE
                TRAPCLR         ESCAPE                                                  
                TRAPCLR         F27                                                    
.
                DISPLAY         *HD,*EL,PRTCOMP;
*
.Re-read the Selected Day's Table
.
ECPRNTXX        MOVE            SAVEDAY,JULDAY            Restore JULDAY        
                MOVE            SAVEYR,YEAR                     and YEAR first      
                PACK            DIM11 WITH USRNO,YEAR,JULDAY
                FILEPI          1;GRAPH
                READ            GRAPH,DIM11;USRNO1,YEARWORK,DIM3,COUNTER,TABLE
                GOTO            CALENDR5 IF NOT OVER
*
.Generate a Null Table
.
                CALL            PACK01                                             
                GOTO            CALENDR5
+ Print Calendar Heading Line
CALENHDR        MOVE            STARTDAY,JDAYWORK
                MOVE            STARTYR,YEARWORK
                CALL            JULGREG             // Set up MONWORK/DAYWORK/YEARWORK
                MOVE            MONWORK,SMONSAV     // Used to print "->" @ beginning of line
                MOVE            DAYWORK,SDAYSAV
                MOVE            YEARWORK,SYRSAV
                LOAD            DIM30 FROM MONWORK OF JAN,FEB,MAR,APR,MAY,JUN:
                                JUL,AUG,SEP,OCT,NOV,DEC
*
.Determine the Number of Days in the Month
.
                LOAD            ENDDAY FROM MONWORK OF THIRTY1,DAYFEB,THIRTY1,THIRTY:
                                THIRTY1,THIRTY,THIRTY1,THIRTY1,THIRTY,THIRTY1:
                                THIRTY,THIRTY1
*
.Left Justify the Date
.
                MOVE            DAYWORK,DIM2
                CMATCH          SPACE,DIM2
.         &IF EQUAL
                GOTO            $$$00028 IF NOT EQUAL
                BUMP            DIM2
.         &XIF
$$$00028
*
.Build the Date Line for the Graph
.
                CLEAR           DIM40
                APPEND          DIM30,DIM40
                APPEND          SPACE,DIM40
                APPEND          DIM2,DIM40
                APPEND          ", 20",DIM40
                APPEND          STARTYR,DIM40
                RESET           DIM40
.
                LOAD            HPOS FROM MONWORK OF TWO,ONE,THREE,THREE,FOUR,THREE:
                                THREE,TWO,ONE,TWO,ONE,ONE
                MOVE            HPOS,HPOS1
                ADD             FORTY2,HPOS
                ADD             TEN,HPOS1
*
.Print the Top of the Graph
.
                LOAD            DATA FROM GRAPHPOS OF RULE1,RULE2,RULE3                
                IF              (DATESWCH = ONE)                                              
                PRINT           *HPOS1,DIM30,*HPOS,WKOF,DIM40,*N,*N:
                                *6,"M  T  W  T  F  S  S":
                                *31,DATA                                              
                ELSE            044
                PRINT           *HPOS1,DIM30,*HPOS,WKOF,DIM40,*N,*N:
                                *6,"S  M  T  W  T  F  S":
                                *31,DATA
                ENDIF           044
.                    *32,"7...8...9..10..11..12...1...2...3...4...5...6...7"
                RETURN

+Print the Day's Detail
.
ECPRNT18        MOVE            DASHES,DIM40
                PRINT           *N,*N,DIM40,DIM40,*N
                SUB             FIVE,LINE
                CALL            ECPRNT24 IF LESS
*
                MOVE            ZERO,NWORK2B                      // Init DOW counter
                MOVE            ZERO,NWORK2A                      // Enable printing of date
. &LOOP                                  // Loop thru 7 days
$$$00029
                PACK            KEY17 WITH USRNO,WRKYRX,WRKJULX
                FILEPI          1;AGENDA                     // Position to 1st record of group
                READ            AGENDA,KEY17;;
.   &LOOP
$$$00030
                MOVE            SPACE,DIM1                   // Init record-not-found switch
                FILEPI          1;AGENDA
                READKS          AGENDA;USRNO1,YEARWRK1,JDAYWRK1,HOUR,MIN,COUNTER:
                                ENDHOUR,ENDMIN,STIME,ETIME,TPOS,NBLOCKS:
                                SECFLAG,TFLAG,DATA
.     &IF OVER                           // PRINT may affect OVER flag
                GOTO            $$$00031 IF NOT OVER
                MOVE            "O",DIM1                    // so we use 'DIM1' as a switch
.     &ELSE
                GOTO            $$$00032
$$$00031
                MOVE            "O",DIM1                    // see if this is correct record
                COMPARE         USRNO,USRNO1
.       &IF EQUAL
                GOTO            $$$00033 IF NOT EQUAL
                COMPARE         WRKYRX,YEARWRK1
.       &IF EQUAL
                GOTO            $$$00034 IF NOT EQUAL
                COMPARE         WRKJULX,JDAYWRK1
.       &IF EQUAL                        // OK, print it
                GOTO            $$$00035 IF NOT EQUAL
                MOVE            SPACE,DIM1                  // set switch to indicate NOT OVER
                COMPARE         SIX,LINE
                CALL            ECPRNT24 IF LESS

                COMPARE         ZERO,NWORK2A         // Did we print date once ?
.         &IF EQUAL                      // Not yet
                GOTO            $$$00036 IF NOT EQUAL
                MOVE            ONE,NWORK2A        // Don't print date next time
                MOVE            JDAYWRK1,JDAYWORK
                MOVE            YEARWRK1,YEARWORK
                CALL            JULGREG            // Set up MONWORK/DAYWORK/YEARWORK
                DISPLAY         *P69:24,DATE;
                CALL            FINDOW
                LOAD            DIM20 BY NWORK2 FROM SUNDAY,MONDAY,TUESDAY:
                                WEDNESDY,THURSDAY,FRIDAY,SATURDY
                PRINT           *N,*4,DATE," - ",DIM20,*N
                SUB             THREE,LINE
.         &XIF
$$$00036

.        If Confidential and Inquiring, Don't Print Detail
                COMPARE         ZERO,INQSW
.         &IF NOT EQUAL
                GOTO            $$$00037 IF EQUAL
                CMATCH          SPACE,SECFLAG
.           &IF NOT EQUAL
                GOTO            $$$00038 IF EQUAL
                MOVE            CONMSG,DATA
.           &XIF
$$$00038
.         &XIF
$$$00037
                MOVE            DASH,DIM3           // Check for a Note
                COMPARE         ZERO,NBLOCKS
.         &IF EQUAL
                GOTO            $$$00039 IF NOT EQUAL
                CLEAR           DIM3
                CLEAR           ETIME              // Blank Out the End Time
.         &XIF
$$$00039
.        Print the Line
                PRINT           *8,STIME,DIM3,ETIME,SPACE2,SECFLAG,*+,DATA
                SUB             ONE,LINE             // Check for Page Overflow
                CALL            ECPRNT24 IF LESS
.       &XIF
$$$00035
.       &XIF
$$$00034
.       &XIF
$$$00033
.     &XIF
$$$00032
                CMATCH          "O",DIM1                    // Done with this user/date combo ?
.   &REPEAT WHILE NOT EQUAL              // No, do more
                GOTO            $$$00030 IF NOT EQUAL
                MOVE            ZERO,NWORK2A                 // Enable printing of date
                ADD             ONE,WRKJULX                  // Yes, Increment date
                COMPARE         WRKJULX,YEARLEN              // Past end of year ?
.   &IF LESS
                GOTO            $$$00040 IF NOT LESS
                ADD             ONE,WRKYRX               // Wrap to the First of the Next Year
                SUB             YEARLEN,WRKJULX
.   &XIF
$$$00040
                ADD             ONE,NWORK2B                  // Count off 7 days for outer loop
                COMPARE         SEVEN,NWORK2B
. &REPEAT WHILE NOT EQUAL
                GOTO            $$$00029 IF NOT EQUAL
                RETURN
*
.Print the Top of Form
.
ECPRNT24        MOVE            FIFTY,LINE
                CALL            CLOCKDT
.
                PRINT           *F,*N,*N,*33,DESKCAL:
                                *N,*38,WDFOR,*70,TIME,*N,*30,USRNAME1,*68,DATE,*N,*N
                MOVE            ZERO,NWORK2A           // Enable printing of date
                RETURN
.
.............................................................................
+HELP - Display a Help Message
.  Enter With: HMENU   = Menu Number
.              HFUNCNO = Function Number
.  Exits With: the Subwindow Erased
*
.Open the Help File if Closed
.
HELP            MOVE            ZERO,HLINE
                MOVE            OPENFLAG,REPLY
                AND             002,REPLY
                GOTO            HELP1 IF NOT ZERO
.
                TRAP            HELP10 IF IO
                OPEN            HELPFILE,FSH,READ                      
                OR              002,OPENFLAG
                TRAPCLR         IO
*
.Position the Help File
.
HELP1           PACK            KEY6 WITH HMENU,HFUNCNO
                REP             SPACZERO,KEY6
                READ            HELPFILE,KEY6;REPLY;
                GOTO            HELPOVER IF OVER                                       
                READ            HELPFILE,SEQ;HMENU,HFUNCNO:
                                INDEX,HPOS,VPOS,HPOS1,LINE,DIM20
                MOVE            TWENTY,VPOS          // Override user's bottom line      
                MOVE            NINETEEN,NWORK1      // Compute # of display lines
                SUBTRACT        HPOS,NWORK1          // Window size = bot - top + 1
                ADD             ONE,NWORK1
*
.Set Up the Subwindow
.
                MOVE            ONE,HFUNC
HELPMORE        DISPLAY         *P1:22,*EF:
                                *P1:21,*HON,*EL,HLPON,DIM20:
                                *H HBANNIPS,HLPBANNI,*HOFF:
                                *SETSWTB HPOS:VPOS,*SETSWLR HPOS1:LINE,*ES,*HU;
.
                COMPARE         "99",HLINE
                GOTO            HELP3 IF EQUAL
                MOVE            ONE,HLINE                                              
*
HELP2           READ            HELPFILE,SEQ;HELPDATA
.         &IF OVER
                GOTO            $$$00041 IF NOT OVER
HELP2A          MOVE            NINTY9,HLINE          // REMEMBER 'NO MORE HELP'         
                MOVE            ONE,HFUNC
                GOTO            HELP3
.         &XIF
$$$00041
*
.End of Data ?
.
                CMATCH          "*",HELPDATA
                GOTO            HELP2A IF EQUAL
*
.Display the Information on the Screen
.
                DISPLAY         *P1:HLINE,*EF,HELPDATA;
                MOVE            ONE,HFUNC            // default to END choice
                COMPARE         HLINE,NWORK1         // at bottom of window ?
.         &IF NOT EQUAL
                GOTO            $$$00042 IF EQUAL
                ADD             ONE,HLINE
                GOTO            HELP2
.         &XIF
$$$00042
                MOVE            FOUR,HFUNC           // default to MORE choice
*
.End of Message or Full Screen
.
HELP3           DISPLAY         *SETSWALL=1:24:1:80,*P1:22,*EF,SPACE,HFUNC1,SPACE,HFUNC2,SPACE,FUNC4:
                                SPACE,HFUNC4;
*
.Position to the Correct Function
.
HELP4           LOAD            FUNCDESC BY HFUNC FROM HFUNC1,HFUNC2,FUNC4,HFUNC4
.
                MOVE            HFUNC,NWORK2
                SUB             ONE,NWORK2
                MULT            TWO,NWORK2
                ADD             ONE,NWORK2
                RESET           HFPOS,NWORK2
                MOVE            HFPOS,DIM2
                MOVE            DIM2,NWORK2
*
.Get a Command
.
                DISPLAY         *PNWORK2:22,*HON,*+,FUNCDESC,*HOFF,*HD,LRCMD;
                TRAP            HELPCMD IF ESCAPE                              
                TRAP            HELPCMD IF F27                               
                KEYIN           *PNWORK2:22,*HA -1,*+,*EOFF,*CURSON,*RV,REPLY:
                                *CURSOFF,*H NWORK2,*+,*DV,FUNCDESC;
                IF              LEFT                                                             
                CMOVE           LEFT,REPLY                                             
                ENDIF           
                IF              RIGHT                                                             
                CMOVE           RIGHT,REPLY                                           
                ENDIF           
                GOTO            HELP7 IF EOS
*
.Check for a Direction Command
.
                CMATCH          066,REPLY
                GOTO            HELP5 IF EQUAL
                CMATCH          " ",REPLY                                              
                GOTO            HELP5 IF EQUAL                                         
                GOTO            HELP7 IF EOS
                CMATCH          064,REPLY
                GOTO            HELP6 IF EQUAL
*
.Check for a Function Letter
.
                RESET           HFLETS
                SCAN            REPLY,HFLETS
                IF              NOT EQUAL                  // Lower case                        
                RESET           HFLETS2                                               
                SCAN            REPLY,HFLETS2                                        
                GOTO            HELP4 IF NOT EQUAL                                    
                MOVEFPTR        HFLETS2,HFUNC                                       
                GOTO            HELP4                                                 
                ENDIF           
                MOVEFPTR        HFLETS,HFUNC
                GOTO            HELP4
*
.Move Right to the Next Function
.
HELP5           ADD             ONE,HFUNC
                COMPARE         FIVE,HFUNC
                GOTO            HELP4 IF NOT EQUAL
                MOVE            ONE,HFUNC
                GOTO            HELP4
*
.Move Left to the Next Function
.
HELP6           SUB             ONE,HFUNC
                GOTO            HELP4 IF NOT ZERO
                MOVE            FOUR,HFUNC
                GOTO            HELP4
.
HELPCMD         NORETURN        // CMD key struck
                GOTO            HELPB                // RESET ESCAPE TRAPS & RETURN TO USER
*
.We Have a Selected Function
.
HELP7           BRANCH          HFUNC TO HELPB,HELPA,HELP11,HELPMORE
..         CALL      INTERR
*
.End the Help Routine
.
HELPOVER        DISPLAY         *HD,*EL,NMHLP,*W3;
HELPB           DISPLAY         *P1:22,*EF,*SETSWTB HPOS:VPOS,*SETSWLR HPOS1:LINE:
                                *ES,*SETSWALL=1:24:1:80;
                GOTO            CMDTRAP              // Return thru CMDTRAP code
*
.Display the Generalized Help
.
HELPA           MOVE            ZERO,HMENU
                MOVE            ZERO,HFUNCNO
                MOVE            ZERO,HLINE           // Reset to top line
                GOTO            HELP1
*
.Print the Help Message
.
HELP11          CALL            SPOOL
                BRANCH          FLAG1 TO HELP3
*
.Reposition the File
.
                DISPLAY         *HD,*EL,PRTHLP;
                PRINT           *F;
.
                READ            HELPFILE,KEY6;REPLY,HMENU,HFUNCNO:
                                INDEX,HPOS,VPOS,HPOS1,LINE
                CALL            INTERR IF OVER
*
.Print the Message
.
HELP8           READ            HELPFILE,SEQ;HELPDATA
                GOTO            HELP9 IF OVER
.
                CMATCH          "*",HELPDATA
                GOTO            HELP9 IF EQUAL
.
                PRINT           HELPDATA
                GOTO            HELP8
*
.Help Message Printing Complete
.
HELP9           RELEASE
                SPLCLOSE
                GOTO            HELP3
*
.Help File Not Available
.
HELP10          NORETURN
                KEYIN           *HD,*EL,*DV,HLPNAV,REPLY;
..         RETURN
*
. RESTORE PROPER 'CMDKEY' TRAP LOCATION
.
CMDTRAP         TRAP            LOGON IF ESCAPE
                BRANCH          CMDTRAP OF $SELD19:   1
                                $ECADD15:  2
                                $ECLOC13:  3
                                $ECCHG12:  4
                                $ECINS10:  5
                                $ECDEL30:  6
                                $EC$CMD:   7
                                $ECSRC14:  8
                                $ECSRC13:  9
                                $TM$CMD:  10
                                $MR$CMD7: 11
                                $MR$CMD:  12
                                $TMPRIN9: 13
                                $TMROU11: 14
                                $TMNOTE6: 15
                                $TMADD33: 16
                                $TMBCS11: 17
                                $TMINQ3:  18
                                $KEYPASX: 19
                                $USADD9:  20
                                $USLOC7:  21
                                $USCHG7:  22
                                $USDEL27: 23
                                $USSRC14: 24
                                $USSTAT2: 25
                                $TDADD10: 26
                                $TD$CMD3: 27
                                $TDSRC15: 28
                                $TDSRC31: 29
                                $TDPRN13: 30
                                $NPADD4:  31
                                $NPLOC8:  32
                                $NPCHG2:  33
                                $NPDEL4:  34
                                $NOTEPA2: 35
                                $NP$CMD1: 36
                                $NPPRIN8: 37
                                $PLAN3:   38
                                $MPADD:   39
                                $MPADD2:  40
                                $PLAN:    41
                                $MPADD2:  42
                                $MPLOC8:  43
                                $ACADD4:  44
                                $ACCHG5:  45
                                $ECPRN27: 46
                                $ECPRN26  47
                RETURN
$SELD19         TRAP            SELD19 IF ESCAPE
                RETURN
$ECADD15        TRAP            ECADD15 IF ESCAPE
                RETURN
$ECLOC13        TRAP            ECLOC13 IF ESCAPE
                RETURN
$ECCHG12        TRAP            ECCHG12 IF ESCAPE
                RETURN
$ECINS10        TRAP            ECINS10 IF ESCAPE
                RETURN
$ECDEL30        TRAP            ECDEL30 IF ESCAPE
                RETURN
$EC$CMD         TRAP            EC$CMD IF ESCAPE
                RETURN
$ECSRC14        TRAP            ECSRCH14 IF ESCAPE
                RETURN
$ECSRC13        TRAP            ECSRCH13 IF ESCAPE
                RETURN
$TM$CMD         TRAP            TM$CMD IF ESCAPE
                RETURN
$MR$CMD7        TRAP            MR$CMD7 IF ESCAPE
                RETURN
$MR$CMD         TRAP            MR$CMD IF ESCAPE
                RETURN
$TMPRIN9        TRAP            TMPRINT9 IF ESCAPE
                RETURN
$TMROU11        TRAP            TMROUT11 IF ESCAPE
                RETURN
$TMNOTE6        TRAP            TMNOTE6 IF ESCAPE
                RETURN
$TMADD33        TRAP            TMADD33 IF ESCAPE
                RETURN
$TMBCS11        TRAP            TMBCST11 IF ESCAPE
                RETURN
$TMINQ3         TRAP            TMINQ3 IF ESCAPE
                RETURN
$KEYPASX        TRAP            KEYPASSX IF ESCAPE
                RETURN
$USADD9         TRAP            USADD9 IF ESCAPE
                RETURN
$USLOC7         TRAP            USLOC7 IF ESCAPE
                RETURN
$USCHG7         TRAP            USCHG7 IF ESCAPE
                RETURN
$USDEL27        TRAP            USDEL27 IF ESCAPE
                RETURN
$USSRC14        TRAP            USSRCH14 IF ESCAPE
                RETURN
$USSTAT2        TRAP            USSTAT2 IF ESCAPE
                RETURN
$TDADD10        TRAP            TDADD10 IF ESCAPE
                RETURN
$TD$CMD3        TRAP            TD$CMD3 IF ESCAPE
                RETURN
$TDSRC15        TRAP            TDSRCH15 IF ESCAPE
                RETURN
$TDSRC31        TRAP            TDSRCH31 IF ESCAPE
                RETURN
$TDPRN13        TRAP            TDPRNT13 IF ESCAPE
                RETURN
$NPADD4         TRAP            NPADD4 IF ESCAPE
                RETURN
$NPLOC8         TRAP            NPLOC8 IF ESCAPE
                RETURN
$NPCHG2         TRAP            NPCHG2 IF ESCAPE
                RETURN
$NPDEL4         TRAP            NPDEL4 IF ESCAPE
                RETURN
$NOTEPA2        TRAP            NOTEPAD2 IF ESCAPE
                RETURN
$NP$CMD1        TRAP            NP$CMD1 IF ESCAPE
                RETURN
$NPPRIN8        TRAP            NPPRINT8 IF ESCAPE
                RETURN
$PLAN3          TRAP            PLAN3 IF ESCAPE
                RETURN
$MPADD          TRAP            MPADD IF ESCAPE
                RETURN
$MPADD2         TRAP            MPADD2 IF ESCAPE
                RETURN
$PLAN           TRAP            PLAN IF ESCAPE
                RETURN
$MPLOC8         TRAP            MPLOC8 IF ESCAPE
                RETURN
$ACADD4         TRAP            ACADD4 IF ESCAPE
                RETURN
$ACCHG5         TRAP            ACCHG5 IF ESCAPE
                RETURN
$ECPRN27        TRAP            ECPRNT27 IF ESCAPE
                RETURN
$ECPRN26        TRAP            ECPRNT26 IF ESCAPE
                RETURN
.
. *** End ***
.
