*---------------------------------------------------------------
.
. Module Name: agenda2_tran.inc
. Description: The Agenda2 Translation File
.
. Revision History:
.
...............................................................................
. Translation Considerations:
.
. The following initialized string may be translated into any language.
. These strings are all the literals used in AGENDA2 2.8, but others may
. be added on a later version. Should this occur, new literals will be added
. to the end of this file.
.
. The strings below are separated into three sections, Months, Menus, and
. all other Miscellaneous data items.
.  1) Notes on Months.
.     Months can be translated as is to the desired language, keeping in
.     mind the three character abbreviation.
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
.
.
VERSION         INIT            "3.0.A"         Reserve 6 Positions
*
. Months
.
JAN      INIT      "Jan"          * January
FEB      INIT      "Feb"          * February
MAR      INIT      "Mar"          * March
APR      INIT      "Apr"          * April
MAY      INIT      "May"          * May
JUN      INIT      "Jun"          * June
JUL      INIT      "Jul"          * July
AUG      INIT      "Aug"          * August
SEP      INIT      "Sep"          * September
OCT      INIT      "Oct"          * October
NOV      INIT      "Nov"          * November
DEC      INIT      "Dec"          * December
*
. Exit Menu
.
FUNC1    INIT      " Exit "       * Exit Function
FUNC2    INIT      " Restore "    * Restore Function
FUNC3    INIT      " reOrganize " * Reorganize Function
CMDLETS  INIT      "ERO"          * Command Letters
CMDPOS   INIT      "020919"       * Function Positions
FUNC     FORM      "01"           * Function Number
*
. Miscellaneous Data Items
.
AG2TIT   INIT      "Agenda "
AM       INIT      " am"
AUTOMSG  INIT      " automatically" * Informative Message
BRERR    INIT      "A2$CMD4: Branch Error - Func: "
CHERR    INIT      "CFAIL: Error Chaining to AGENDA. "
NOCONT   INIT      "NOCONT: Control File Not Found. "
NOTEMSG  INIT      "  Note "      * Note Message
NO       INIT      "No"           * Negative Response
NUERR    INIT      "NOUSERS: User File Failed to Open. "
PM       INIT      " pm"
RESTSYST INIT      "Restore the System Upon Completion ? N"
ROLLFAIL INIT      "Rollout Failed. "
SECPASS  INIT      "Security Password: "
SS1      INIT      "The Agenda System is currently shutdown. It was taken ":
                   "down on "
SS2      INIT      "at "
SS3      INIT      " by "
SS4      INIT      " for "
SS5      INIT      "It is scheduled to"
SS6      INIT      " return on "
SS7      INIT      " at "
SS8      INIT      "You may choose one of four actions. "
SS9      INIT      "The Exit function will terminate "
SS10     INIT      "this program. The "
SS11     INIT      "Restore function will allow the user to bring the "
SS12     INIT      "system back up. The Reorganize function will reorganize the Agenda"
SS13     INIT      " "
SS14     INIT      " system files. If no "
SS15     INIT      "action is taken, this program will simply await "
SS16     INIT      "the restoration of the system."
SSM      INIT      "System Shutdown Monitor"
SYSREST  INIT      "Agenda System Restored."
AG2TITNI INIT      "Agenda "
CHERRNI  INIT      "CFAIL: Error Chaining to AGENDA. "
SS1NI    INIT      "The Agenda System is currently shutdown. It was taken ":
                   "down on "
SS14NI   INIT      "system files. If no "
SYSRSTNI INIT      "Agenda System Restored."
.
. *** End ***
.
