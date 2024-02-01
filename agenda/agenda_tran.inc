*---------------------------------------------------------------
.
. Module Name: agenda_tran.inc
. Description: The Agenda Translation File
.
. Revision History:
.
. 
...............................................................................
. Translation Considerations:
.
. The following initialized string may be translated into any language.
. These strings are all the literals used in AGENDA 2.7, but others may
. be added on a later version. Should this occur, new literals will be added
. to the end of this file.
.
. The strings below are seperated into three sections, Months, Menus, and
. all other Miscellaneous data items.
.  1) Notes on Months.
.     Months can be translated as is to the desired language.
.  2) Notes on Menus.
.     The translator will need to note the significance of the following
.     variables (the main menu is used as an example) :
.     A) The function names are defined first. These can be translated as
.        is into any language. (note, for the system main menu the spacing
.        within the quotes must be maintained as is to ensure the main menu
.        appears correctly on the opening screen)
.             .
.             . System Menu Functions
.             .
.             SFUNC1   INIT      " Calendar "
.             SFUNC2   INIT      " Messages "
.             SFUNC3   INIT      " Users "
.             SFUNC4   INIT      " Directory "
.             SFUNC5   INIT      " Notes "
.             SFUNC6   INIT      " Alarm "
.             SFUNC7   INIT      " Plan "
.             SFUNC8   INIT      " Logon "
.             SFUNC9   INIT      " Exit "
.     B) The two variables below do not need any translation and are just
.        here for menu completeness.
.             FUNCDESC DIM       21
.             SFUNC    FORM      "01"
.     C) The *LETS variable contains the capital letter used to key over to
.        that menu item, and *LETS2 contains the lower case of the same letters
.        so both upper and lower case are available. These should be translated
.        accordingly. THE *POS variable contains the horizontal position, as
.        a two character number, for each menu item. For example, Calendar will
.        be placed at horizontal position "02", Messages at "13",. . ., and
.        Exit at "75". These can be changed to fit your needs.
.             SLETS    INIT      "CMUDNAPLE"
.             SLETS2   INIT      "cmudnaple"
.             SFPOS    INIT      "021324324452606775"
.  3) Notes on Miscellaneous data items.
.     These can be translated directly, note that the spacing on the Telephone
.     message flags and the User status variables must be as is. Also,
.     spaces that occur at the beginning or end of strings are there for
.     proper spacing among data items and should be maintained, N's or
.     Y's that occur after '?' in strings represent 'Yes' or 'No' and
.     should be translated in this way.
...............................................................................
.                    ***   Note on "Can"   ***
.
.  If you translate the abreviation 'Can' to another language, please remember
.  to do the same in the AGENDA_REORG/CHN as this checks and eliminates all
.  cancelled meetings from the file.
...............................................................................
.                    ***   Use of FORM's   ***
.
.  The FORM variables that occur after certain words are there for positioning
.  relative to the new word length. Follow the directions specified in the
.  documentation following each form and change the variable to the new number.
.  {LEN(FOO) - refers to the number of characters in variable FOO.}
...............................................................................
.
VERSION         INIT            "3.0.A"         Reserve 6 Positions     
.
AGNINM          INIT            "AGENDA"
HELPSTNI        INIT            "Help  Quit"                                             
HELPPSNI        FORM            "69"           ** 79 - LEN(HELPSTNI)
HLPBANNI        INIT            "F3=Fast Exit  Quit "
HBANNIPS        FORM            "60"           ** 79 - LEN(HLPBANNI)
HLPCMDNI        INIT            " Help  Quit "
HLPPOSNI        FORM            "64"           ** 76 - LEN(HLPCMD)
VISAGNI         INIT            " AGENDA "       *NAME CHANGE              
.
*
.Months
.
JAN             INIT            "January"
FEB             INIT            "February"
MAR             INIT            "March"
APR             INIT            "April"
MAY             INIT            "May"
JUN             INIT            "June"
JUL             INIT            "July"
AUG             INIT            "August"
SEP             INIT            "September"
OCT             INIT            "October"
NOV             INIT            "November"
DEC             INIT            "December"
*
. If Month names begin in lower case letters, change this representation
. variable to reflect that.
.
MONABREV        INIT            "jJfFmMaAsSoOnNdD"
*
. Menus
.
. System Menu Functions   ** Please Note the spacing in these variables.
.                            The way they stand now they fit perfectly across
.                            the main menu screen. You may have to adjust them
.                            to suit your needs.
.
SFUNC1          INIT            " Calendar  "
SFUNC2          INIT            " Messages  "
SFUNC3          INIT            " Users  "
SFUNC4          INIT            " Directory  "
SFUNC5          INIT            " Notes  "
SFUNC6          INIT            " Alarm  "
SFUNC7          INIT            " Plan  "
SFUNC8          INIT            " Logon  "
SFUNC9          INIT            " Exit "
.
FUNCDESC        DIM             21
SFUNC           FORM            "01"
SLETS           INIT            "CMUDNAPLE"
SLETS2          INIT            "cmudnaple"                                             
SFPOS           INIT            "021324324452606775"
.
.Desk Calendar Functions
.
FUNC2           INIT            " daTe "
.        INIT      " Write "
.        INIT      " Modify "          * AFUNC2
FUNC9           INIT            " Delete "
FUNC1           INIT            " Note "
FUNC4           INIT            " Print "
FUNC5           INIT            " Inquire "
FUNC6           INIT            " Clean up "
FUNC7           INIT            " Search "
.
FUNC            FORM            "01"
ECLETS          INIT            "TWMDNPICS"
ECLETS2         INIT            "twmdnpics"                                            
ECPOS           INIT            "020917263542506071"
.
.Calendar Inquire Functions                                               
.                                                                         
.        INIT      " daTe "                                               
.        INIT      " Print "                                              
.        INIT      " Search "                                             
FUNC8           INIT            " Exit inquire "                                       
.                                                                          
IFUNC           FORM            "01"                                                   
ILETS           INIT            "TPSE"                                                 
ILETS2          INIT            "tpse"                                                 
IPOS            INIT            "02091726"                                            
.
.Calendar Clean Up Functions
.
.        INIT      " Next "
.        INIT      " Back "
.        INIT      " Delete "
.
PFUNC           FORM            "01"
PLETS           INIT            "NBD"
PLETS2          INIT            "nbd"                                                  
PFPOS           INIT            "020916"
.
.Telephone Message Functions
.
MFUNC2          INIT            " Review "
.        INIT      " Write "
MFUNC4          INIT            " Broadcast "
.        INIT      " Inquire "
.
MFUNC           FORM            "01"
MFLETS          INIT            "RWBI"
MFLETS2         INIT            "rwbi"                                                  
MFPOS           INIT            "02111931"
.
.Telephone Message Inquire Functions                                       
.                                                                          
.        INIT      " Review "                                              
.        INIT      " Exit inquire "                                        
.                                                                          
MIFUNC          FORM            "01"                                                   
MILETS          INIT            "RE"                                                   
MILETS2         INIT            "re"                                                    
MIPOS           INIT            "0211"                                                 
.
.Telephone Message Review Functions
.
MRFUNC2         INIT            " Next "
MRFUNC3         INIT            " Back "
MRFUNC4         INIT            " Save "
MRFUNC5         INIT            " Delete "
.MRFUNC6  INIT      " Print "                               
MRFUNC7         INIT            " Forward "
MRFUNC8         INIT            " Remark "
MRFUNC9         INIT            " fiLe "                      * New Message Option.       
.
MRFUNC          FORM            "01"
MRLETS          INIT            "NBSDPFRL"
MRLETS2         INIT            "nbsdpfrl"                                              
MRPOS           INIT            "0209162332405059"
.
.Message Type Descriptions
.
MTYPE1          INIT            " New "
MTYPE2          INIT            " Saved "
MTYPE3          INIT            " Deleted "
.
MTLETS          INIT            "NSD"
MTLETS2         INIT            "nsd"                                                  
MTPOS           INIT            "020817"
.
.User Status Functions
.
.        INIT      " Search "           * 'FUNC7'
CFUNC6          INIT            " sTatus "
.        INIT      " Next page "        * 'NFUNC1'
CFUNC8          INIT            " Write "
.        INIT      " Modify "           * 'AFUNC2'
.        INIT      " Delete "           * 'FUNC9'
CFUNC7          INIT            " sHutdown "
.
CFUNC           FORM            "01"
CFLETS          INIT            "STNWMDH"
CFLETS2         INIT            "stnwmdh"                                           
CFPOS           INIT            "02112032404958"
.
.Telephone Directory Functions
.
.        INIT      " Write "
.        INIT      " Modify "
.        INIT      " Delete "
.        INIT      " Search "
.        INIT      " Print "
.
TDFUNC          FORM            "01"
TDLETS          INIT            "WMDSP"
TDLETS2         INIT            "wmdsp"                                                
TDPOS           INIT            "0210192837"
.
.Desk Notepad Functions
.
NFUNC1          INIT            " Next page "
.        INIT      " Write "
.        INIT      " Modify "
.        INIT      " Delete "
.        INIT      " Search "
.        INIT      " Print "
.
NFUNC           FORM            "01"
NLETS           INIT            "NWMDSP"
NLETS2          INIT            "nwmdsp"                                              
NFPOS           INIT            "021422314048"
.
.Desk Alarm Functions
.
.        INIT      " Write "
AFUNC2          INIT            " Modify "
.        INIT      " Delete "
.        INIT      " Next page "                                         
.
AFUNC           FORM            "01"
ALETS           INIT            "WMDN"
ALETS2          INIT            "wmdn"                                              
AFPOS           INIT            "02101928"
.
.Meeting Planner Functions
.
MPFUNC2         INIT            " Schedule "
MPFUNC4         INIT            " cOnfirm "
MPFUNC3         INIT            " Cancel "
.        INIT      " Next page "
.
BFUNC           FORM            "01"
BLETS           INIT            "SOCN"
BLETS2          INIT            "socn"                                                 
BFPOS           INIT            "02132332"
.
.Meeting Planner Group Entry Functions
.
MPFUNC5         INIT            " Single person entry "        * For new PLAN options.   
MPFUNC6         INIT            " Group entry "                * New option.             
MPFUNC          FORM            "01"                           * New position.           
MPLETS          INIT            "SG"                           * New letter.            
MPLETS2         INIT            "sg"                                                   
MPPOS           INIT            "0225"
.
.Help Message Functions
.
HFUNC1          INIT            " End "
HFUNC2          INIT            " Help "
.        INIT      " Print "
HFUNC4          INIT            " More "
.
HFUNC           FORM            "01"
HFLETS          INIT            "EHPM"
HFLETS2         INIT            "ehpm"                                                
HFPOS           INIT            "02081523"
*
. Miscellaneous data items
.
.Telephone Messages Flag Descriptions
.
MDESC1          INIT            "     Telephoned     "
MDESC2          INIT            " Came By to See You "
MDESC3          INIT            "  Wants to See You  "
MDESC4          INIT            "       URGENT       "
MDESC5          INIT            "    Please Call     "
MDESC6          INIT            "  Will Call Again   "
MDESC7          INIT            " Returned Your Call "
MDESC8          INIT            "  See the Operator  "
.
.User Status Flag Descriptions
.
OUT             INIT            "Out"
IN              INIT            "In "
NA              INIT            "N/A"
.
.The balance of the data names are in alphabetical order.
.
ADDCAL          INIT            "Add This Meeting to Your Calendar"
ADDENT          INIT            "Address."
ADDGRP          INIT            "Add to Another Group"
ADDINFO         INIT            "Adding the Information."
ADDMSG          INIT            "Message Added."
ADDMSGS         INIT            "Messages Added."
ADDPR           INIT            " - Add Appointments Anyway"
AGENEND         INIT            "Agenda Ending."
AGTITLE         INIT            "Agenda for "
ALCON           INIT            "You Have Already Confirmed This Meeting. "
ALLAR           INIT            "Use Up, Down, Left, or Right to select.  "
ALLDEL          INIT            "Message Already Deleted."
ALLOWMG         INIT            "Allow Others to View This Message"
ALLSAVE         INIT            "Message Already Saved."
ALRM            INIT            "*ALARM*"
ALMSG0          INIT            "Enter the Alarm "
ALMSG1          INIT            "Date"
ALMSG2          INIT            "Time"
ALMSG3          INIT            "Information."
ALREQ           INIT            "That User Already Requested. "
ALRMMSG         INIT            "Alarm Message"
ALTPRT          INIT            "Use an Alternate Printer or Spool to Disk"
AM              INIT            "am"
AMSP            INIT            " am"
APDFILE         INIT            "Appending output file "
AUTOREST        INIT            "Automatically Restore the System at the Specified Date/Time"
BEGINPR         INIT            "Begin"
BYMSG           INIT            "By: "
BYPOS           FORM            "4"          ** 8 - LEN(BYMSG)
CALLENT         INIT            "Caller's Name or Press Enter for Yours."
CALLER1         INIT            "Welcome to "
CALLMSG         INIT            "Caller:"
CALLPOS         FORM            "27"      ** 34 - LEN(CALLMSG)
CALLPH          INIT            "Caller's Phone Number."
AGENDANM        INIT            "AGENDA"
CALTIT          INIT            "AGENDA - Calendar Search"
CANMEET         INIT            "Cancel This Meeting"
CANMEET2        INIT            "Cancelling the Meeting."
CAN             INIT            "Can"
CANNOT          INIT            "You Did Not Schedule This Meeting - You May Not Cancel It. "
CHGCOMP         INIT            "Change Complete."
CHKAVAIL        INIT            "Checking Attendee Availability."
CHKPR           INIT            "Checking for"
CHPARA          INIT            "Would You Like to Change the Search Parameters"
CHPR            INIT            "Change Complete."
CHSTAT          INIT            "Change Your User Status to IN ? Y"
CLNCPT          INIT            "Clean up Complete"
CMSTAT          INIT            "Comment"
CNTMSG          INIT            "Continue This Message"
COMMAND         INIT            "Use command letter Up, Down, Right, Left":
                                ", SPACEBAR, Enter"
CONFMEET        INIT            "Meeting Confirmed."
CONFPR          INIT            "Allow Others to View This Appointment Information ? Y"
CONFPR2         INIT            "Conflict on "
CONFREP         INIT            "c"
CONMSG          INIT            "Confidential" * Confidential Message
CONPR           INIT            "Conflicts."
CONPR2          INIT            "Conflicts: "
CONPRQ          INIT            "Allow Others to View This Information ? "
CONTINUE        INIT            "          (Continued with Next Message)"
CONTPR          INIT            " - Continue Checking"
CONTPR2         INIT            " Continue "
CONTRET         INIT            " to continue."           
CORENT          INIT            "Correct Entry"
CORRUSR         INIT            "Correct User"
CSENT           INIT            "City/State."
CSUN            INIT            "S"                                                    
CMON            INIT            "M"
CTUE            INIT            "T"
CWED            INIT            "W"
CTH             INIT            "T"
CFRI            INIT            "F"
CSAT            INIT            "S"
CTSRCH          INIT            "Continue Searching"
DATEMSG         INIT            "Date: "
DATEPOS         FORM            "2"               ** 8 - LEN(DATEMSG)
DATEST          INIT            " Date: "
DAYMSG          INIT            "Day: "
DAYPOS          FORM            "3"               ** 8 - LEN(DAYMSG)
DELALRM         INIT            "Use Enter to Delete Alarm"
DELENT          INIT            "Delete This Entry"
DELETED         INIT            "Deleted"      * Deleted Message Type
DELETING        INIT            "Deleting "
DELMSG          INIT            "Message Deleted."
DELPR           INIT            "Delete ALL Appointments within a Specific Period Without":
                                " Prompting"
DELPRT          INIT            "Delete Messages as Printed"
DELST           INIT            "Delete Appointments Starting"
DELUSR          INIT            "Delete This User"
DESKCAL         INIT            "Desk Calendar"
DIRNM           INIT            "Name"
DIRNT           INIT            "Note"
DIRPH           INIT            "Phone"
DSKALRM         INIT            "Desk Alarms"
DSKNOTE         INIT            "Desk Notepad"
DSKNTS          INIT            "Desk Notes"
DTREST          INIT            "Date to be Restored: "
DTSTAT          INIT            "Date"
DTTKN           INIT            "Date Taken."
EBFST           INIT            "Ending Time is Before Starting Time. "
EDDATE          INIT            "Ending Date of the Last Week: "
VPRPOS2         FORM            "41"          ** LEN(EDDATA) + LEN(LITENT) + 1
ENDBFST         INIT            "Ending Date Before Starting Date!  Please Try Again"
ENDPR           INIT            "End"
ENTADD          INIT            "Enter Additional Caller Information."
ENTADDED        INIT            "Entry Added."
ENTCH           INIT            "Entry Changed."
ENTDEL          INIT            "Entry Deleted."
ENTREM          INIT            "Enter a Remark."
ENTUSR          INIT            "F5=Enter User Number "
ENVIRON         INIT            "AGENDA  "     * Default environment                      
ERRAG2          INIT            "Error Chaining to agenda2. "
ERRFILE         INIT            "ERROR OPENING FILE: "
EXITAG          INIT            "E"            ** First letter of word EXIT.
LOWEXIT         INIT            "e"            ** Lower case letter for EXIT.
EXSTAT          INIT            "Press Enter to Exit.  To change status enter (I)n, (O)ut, or"
EXSTAT2         INIT            " (N)ot available: "
EXOPT           INIT            "O1I2N3o1i2n3"                                            
EXTPH           INIT            "     Ext. "
EXTSTAT         INIT            "Ext"
EXWKEND         INIT            "Exclude Weekends"
FASTEX          INIT            "Fast Exit requested. Continue? (Y or N) "                
FININQ          INIT            "Are You Finished Inquiring"
FIRM            INIT            "Firm"
FORMSG          INIT            "for"
FRIDAY          INIT            "Friday"
FUNCNOT         INIT            "Function Not Allowed While Inquiring. "
GRNFND          INIT            "Specified Group Not Found. "
GRPDES          INIT            "Group Designation."
GRPMSG          INIT            "Group Designation or Press Enter for ALL System Users."
GRPSTAT         INIT            "Grp"
HELPST          INIT            "Help  Cmd"                                             
HELPPOS         FORM            "70"           ** 79 - LEN(HELPST)
HIGHMSG         INIT            "Press #"5#" to highlight.  "
HILITEST        INIT            "HILITE"
HLPBAN          INIT            "F3=Fast Exit  Command "
HLPBANPS        FORM            "57"           ** 79 - LEN(HLPBAN)
HLPCMD          INIT            " Help  Cmd "
HLPPOS          FORM            "65"           ** 76 - LEN(HLPCMD)
HLPNAV          INIT            "Help File Not Available. "
HLPON           INIT            " Help on: "
IDBAD           INIT            "Bad "
IDINUSE         INIT            "Identification Number Already in Use."
IGRPSPEC        INIT            "Invalid Group Specification. "
IKSPEC          INIT            "Invalid Key Specified. "
INCUSR          INIT            "Include This User"
INFOPR          INIT            "Information."
INFOREM         INIT            "Information Removed."
INKEY           INIT            "Invalid Key Specification. "
INGRP           INIT            "Invalid Group Specification. "
INSPR           INIT            "Insertion Complete."
INTERROR        INIT            "Internal Program Error - Press #"E#" and Enter":
                                " to continue."
INUSEID         INIT            " Already in Use. "
INVDATE         INIT            "Invalid Date Entered. "
INVID           INIT            "Invalid User ID"                                     
INVID2          INIT            "Invalid ID in ID file: "
INVKEY          INIT            "Invalid Key Specification. "
INVNMSP         INIT            "Invalid Name Specification. "
INVTIME         INIT            "Invalid Time Entered. "
IONA            INIT            "(I)N, (O)UT, or (N)OT Available ? "
IONAREP         INIT            "O1I2N3"
KEYSP           INIT            "Key Specified was: "
LITAPPT         INIT            "Enter the Appointment "
LITENT          INIT            "Enter the "
LITET           INIT            "Ending Time."
LITIST          INIT            "Is this a (T)entative or (F)irm Appointment ? F"
LITST           INIT            "Starting Time."
LRCMD           INIT            "Use command letter, Left, Right, Space Bar, or Enter"
LRUDCMD         INIT            "Use Left, Right, Up, or Down, then Enter"
LSDIS           INIT            "(L)ong or (S)hort Display ? S"
SHORTCH         INIT            "S"      *The Character that 'Short' is tested against.
LST             INIT            "Last"
MASK1           INIT            "mm/dd/yy"
MASK2           INIT            "dd mmm 20yy"
MAXNOTE         INIT            "Maximum Lines Entered - Note Entry Complete"
MEETAL          INIT            "Allow Others to View This Appointment Information"
MEETAPP         INIT            "Appointment Added."
MEETATT         INIT            "Attendee"
MEETAVL         INIT            "Available Meeting Time"
MEETCAN         INIT            "This Meeting Has Already Been Cancelled. "
MEETCAN2        INIT            "This Meeting Has Been Cancelled. "
MEETCONF        INIT            "Checking Confirmations."
MEETDT          INIT            "Meeting Date: "
DATEPOS2        FORM            "7"            ** 21 - LEN(MEETDT)
MEETEND         INIT            "Ending Time: "
ENDPOS2         FORM            "8"            ** 21 - LEN(MEETEND)
MEETPL          INIT            "Meeting Planner"
MEETSCH         INIT            "Scheduled by: "
SCHBYPOS        FORM            "40"           ** 55 - [LEN(MEETSCH) + 1]
MEETST          INIT            "Starting Time: "
STRTPOS         FORM            "6"            ** 21 - LEN(MEETST)
MOREPR          INIT            " More "
MOREUSR         INIT            "Specify More Users"
MSGALRM         INIT            "*MESSAGE*"
MSGDS           INIT            "- Message -"
MSGPER          INIT            "Message."
MSGFOR          INIT            "Message Forwarded."
MSGREV          INIT            "Review Messages Beginning:"
MSGST           INIT            "Message: "
MSGSTAT         INIT            "Msgs"
MONDAY          INIT            "Monday"
NAMEENT         INIT            "Name."
NEWUS0          INIT            "User's "
NEWUS1          INIT            "Name."
NEWUS2          INIT            "Telephone Extension."
NEWUS3          INIT            "Primary Group Designation."
NEWUS4          INIT            "Identification Number. "
NEWUS5          INIT            "Enter the New "
NEXTAPT         INIT            "Next Appointment"
NMHLP           INIT            "There Is No More HELP."
NMKEY           INIT            "Name Key."
NMMU            INIT            "No More Matching Users. "
NO              INIT            "No"
NOMSG           INIT            "No More Messages. "
NONESCH         INIT            "  None Scheduled"
NONTS           INIT            "No Notes on This Screen. "
NOPRMSG         INIT            "No Previous Messages."
NOPREVR         INIT            "No Previous Records. "
NOTCONT         INIT            " or Press Enter if Note or Continuation."
NOTECON         INIT            "Allow Others to View This Note Information"
NOTEDEL         INIT            "Delete This Note"
NOTEENT         INIT            "Enter Other Information."
NOTEINFO        INIT            "Note Information."
NOTEMSG         INIT            "  Note "      * Note Message
NOTEMSG2        INIT            "Enter a Note."
NOTEPR          INIT            "  Note  "
NOTEREW         INIT            "Rewinding to the First Page."
NOUSRSL         INIT            "No Users Selected. "
NOUSRS          INIT            "No Matching Users Found. "
NMME            INIT            "No More Matching Entries. "
NTDELTD         INIT            "Note Deleted."
NTENT           INIT            "Enter a Note."
NTKEY           INIT            "Note Key."
NUMOCC          INIT            "Enter Number of Occurences: "
NUMPR           INIT            "Number of"
NXT             INIT            "Next "
NXTGRP          INIT            "Next Group: "
OFMSG           INIT            "of:"
OFPOS           FORM            "31"        ** 34 - LEN(OFMSG)
OVRWRT          INIT            "Overwrite file? Default will append: "
OVRWRT2         INIT            "Overwriting output file "
PGSTAT          INIT            "Page"
PHDIR           INIT            "T E L E P H O N E   D I R E C T O R Y"
PHENT           INIT            "Phone Number."
PHMSG           INIT            "Phone:"
PHPOS           FORM            "28"              ** 34 - LEN(PHMSG)
PHPG            INIT            "Page: "
PIP             INIT            "Printing in Progress."
PLANALRM        INIT            "*PLAN*"
PLANMODE        INIT            "Which Mode (1 or 2) ? 1"
PLATT           INIT            "Attendees"
PLAVAIL         INIT            "Available"
PLCANCEL        INIT            "  ** Cancelled **"
PLCHK           INIT            "Checking"
PLCON           INIT            "Confirmed"
CONFPOS         FORM            "43"             ** 54 - [LEN(PLCON) + 2]
PLCON2          INIT            "Confirm This Meeting"
PLDUR           INIT            "Meeting Duration:"
DURPOS          FORM            "24"             ** 41 - LEN(PLDUR)
PLEND           INIT            "Meeting Ending Time:"
ENDPOS          FORM            "21"             ** 41 - LEN(PLEND)
PLGRP           INIT            "Group Designation or Press Enter for ALL System Users."
PLINFO          INIT            "Info: "
INFOPOS         FORM            "15"             ** 21 - LEN(PLINFO)
PLLOC           INIT            "Location"
PLLOC2          INIT            "Location: "
LOC2POS         FORM            "44"             ** 54 - LEN(PLLOC2)
PLMEET          INIT            "Meeting "
MEETPOS         FORM            "28"             ** 41 - (LEN(PLMEET) + LEN(ALMSG1) + 1)
PLMSG           INIT            "Send Message to All Attendees"
PLMSG1          INIT            "The meeting scheduled by "
PLMSG2          INIT            "has been cancelled."
PLMSG3          INIT            " Location "
PLMSG4          INIT            "Date "
PLMSG5          INIT            ", Time "
PLMSG6          INIT            " to "
PLMSG7          INIT            "Please remove it from your "
PLMSG8          INIT            "calendar.   Thank you."
PLREQ           INIT            "Requested"
PLSCH           INIT            "Scheduling the Meeting."
PLSEL           INIT            "Do You Wish to Select Specific Users"
PLTRY           INIT            "Try a Different "
PLREP           INIT            "N1"
PLST            INIT            "Meeting Starting "
STPOS           FORM            "19"            ** 41 - (LEN(PLST) + LEN(ALMSG2) + 1)
PLSTAT          INIT            "Status"
PLUNAV          INIT            "Unavailable:"
PLUSR           INIT            "Please Enter Your User Number: "
PM              INIT            "pm"
PMSP            INIT            " pm"
PNO             INIT            "Personal Numbers Only ? N"
PRENT           INIT            "Allow Others to View this Entry ? "
PRESSRT         INIT            "Press "
PRINTMG         INIT            "Printing the Message."
PRTCAL          INIT            "Printing the Calendar."
PRTCMPL         INIT            "Printing Complete."
PRTCOMP         INIT            "Printing Complete."
PRTHLP          INIT            "Printing the Help Message."
PRTPR           INIT            "Do You Wish to Print the Information, too"
PRTMSG          INIT            "Print (S)elected Message or (A)ll Messages of this Type ? S"
PRTNM           INIT            "Printer or Spool File Name: "
PRTNTS          INIT            "Printing the Notes."
PRTSPA          INIT            "Print a (S)pecific Note or (A)ll Notes ? A"
PRTUNAV         INIT            "System Printer Unavailable.  "
NTREP           INIT            "S1A2"
RECMSG          INIT            "Received"
RECNOT          INIT            "Record Not Found for "
REDWMPR         INIT            "Does it Re-occur (D)aily, (W)eekly or (M)onthly ? D"
DWMREP          INIT            "D1W2M3"
REDTPR          INIT            "Does the event reoccur by (D)ay or da(T)e ? "
REMADD          INIT            "Remark Added."
REMPR           INIT            "Remove This Information"
REPDT           INIT            "D0T1"
REPR            INIT            "Does This Information Re-occur"
REPYN           INIT            "Y0N1"
RETPR           INIT            " Return "
RLCMD           INIT            "Use > or <, then Enter"
RWFILE          INIT            "Rewinding the File."
SATURDY         INIT            "Saturday"
SAVED           INIT            " Saved "      * Saved Message Type
SCH             INIT            "Sch"
SCHBY           INIT            "Scheduled by"
SCHCON          INIT            "Schedule Conflict - Continue ? N"
SCHCON2         INIT            " Schedule Conflicts"
SCHCONF         INIT            "Schedule Conflict - Continue"
SCHDUR          INIT            "Meeting Duration:"
MTDURPOS        FORM            "24"            ** 41 - LEN(SCHDUR)
SCHDURP         INIT            "Meeting Duration."
SCHEND          INIT            "Search Ending "
TMEDPOS         FORM            "22"            ** 41 - [LEN(SCHEND) + LEN(ALMSG2) + 1]
SCHM1           INIT            "The two Scheduling Modes:"
SCHM2           INIT            "1. Specify date, Start time, End time, and attendees ":
                                "and allow"
SCHM3           INIT            "AGENDA to check their availability. "
SCHM4           INIT            "If someone cannot attend, their"
SCHM5           INIT            "conflicting appointment is shown."
SCHM6           INIT            "2. Specify starting date, times between which the ":
                                "meeting should"
SCHM7           INIT            "begin, meeting duration, and attendees. "
SCHM8           INIT            "Then, allow AGENDA to"
SCHM9           INIT            "determine the first date/time that all "
SCHM10          INIT            "attendees are available."
SCHM11          INIT            "Saturdays optionally included, "
SCHM12          INIT            "Sundays are never searched."
SCHMEET         INIT            "Schedule the Meeting"
SCHPR           INIT            "Searching for: "
SCHSAT          INIT            "Include Saturdays:"
INCSTPOS        FORM            "23"             ** 41 - LEN(SCHSAT)
SCHSRCH         INIT            "Search "
SCHST           INIT            "Search Starting "
DTSTPOS         FORM            "20"             ** 41 - [LEN(SCHST) + LEN(ALMSG1) + 1]
TMSTPOS         FORM            "20"             ** 41 - [LEN(SCHST) + LEN(ALMSG2) + 1]
SCPASSW         INIT            "Security Password: "
SDFOR           INIT            "Shutdown For: "
SECGRP          INIT            "Secondary Group"
SECREP          INIT            "N*Y "
SELREC          INIT            "Selecting Records."
SELREP          INIT            "N1"
SELUSR          INIT            "Do You Wish to Select Specific Users"
SNDMSG          INIT            "Send Message"
SPECMR          INIT            "Specify More Users"
SPGRP           INIT            "Specified Group Not Found. "
SPLE            INIT            "PRT"          * DEFAULT SPOOL FILE <ext>
SPLN            INIT            "AGENDA"       * DEFAULT SPOOL FILE <name>
SPLV            INIT            "W"            * DEFAULT SPOOL FILE <env>
SPSTREP         INIT            " Y*N"
SPUSRS          INIT            "Specified Users"
SRCHFOR         INIT            "Searching for: "
SRCHKEY         INIT            "Search Key: "
SRE             INIT            "Sure"
STCHG           INIT            "Status Changed."
STDATE          INIT            "Starting Date of the First Week. "
VPRPOS          FORM            "44"     ** LEN(STDATE) + LEN(LITENT) + 1
STPRIGR         INIT            "Status Must Be Changed on Primary Group. "
STSTAT          INIT            "Stat"
SUNDAY          INIT            "Sunday"
SVMSG           INIT            "Message Saved."
SYSTPRT         INIT            "SYSTEMPRT="
SYSTPRTQ        INIT            "Use the System Printer"
SYSTSD          INIT            "System Shutdown In Progess."
TAKEMSG         INIT            "Taken"
TELADD          INIT            "Address:"
ADDPOS          FORM            "16"          ** 24 - LEN(TELADD)
TELALLOW        INIT            "Allow Others to View this Entry"
TELCS           INIT            "City/St:"
CSPOS           FORM            "16"          ** 24 - LEN(TELCS)
TELDIR          INIT            "Telephone Directory"
TELNAME         INIT            "Name:"
NAMPOS          FORM            "19"           ** 24 - LEN(TELNAME)
TELNOTE         INIT            "Note:"
NOTEPOS         FORM            "19"           ** 24 - LEN(TELNOTE)
TELPAGE         INIT            "Page"
TELPHONE        INIT            "Phone:"
FONPOS          FORM            "18"           ** 24 - LEN(TELPHONE)
TELEMSG         INIT            "Telephone Message"
TELZIP          INIT            "Zipcode:"
ZIPPOS          FORM            "16"            ** 24 - LEN(TELZIP)
TENTAT          INIT            "Tentative"
TFREP           INIT            "TtF "
THRGH           INIT            "Through"
THURSDAY        INIT            "Thursday"
TIMEMSG         INIT            "Time: "
TIMEPOS         FORM            "2"       ** 8 - LEN(TIMEMSG)
TIMEST          INIT            " Time: "
TMSTAT          INIT            "Time"
TMTKN           INIT            "Time Taken."
TOMSG           INIT            "To:"
TOPOS           FORM            "31"         ** 34 - LEN(TOMSG)
TUESDAY         INIT            "Tuesday"
UPDWNCMD        INIT            "Use Up, Down, SPACE BAR, Enter"
USEANYW         INIT            "Use it anyway"
USRADD          INIT            "User Added."
USRALRM         INIT            "Alarms."
USRAPTS         INIT            "Appointments."
USRDIR          INIT            "Directory Entries."
USRGRPH         INIT            "Appointment Graph Records."
USRMSG          INIT            "Specified Users"
USRMSGS         INIT            "Messages."
USRNKEY         INIT            "User Name Key."
USRNM           INIT            "User Name."
USRNOTE         INIT            "Notes."
USRPLAN         INIT            "Meetings."
USRREQ          INIT            "That User Already Requested. "
USRSTAT         INIT            "Status of Users"
USRSTAT2        INIT            "User"
USRUSR          INIT            "the User."
VISAG           INIT            " AGENDA "
WAT             INIT            " at "
WDFOR           INIT            "for"
WEDNESDY        INIT            "Wednesday"
WFST            INIT            "with First"
WKOF            INIT            "Week of "
YEARPR          INIT            "Year: "
YES             INIT            "Yes"
YRPER           INIT            "Year."
ZIPENT          INIT            "Zip Code."
.
. *** End  ***
.
