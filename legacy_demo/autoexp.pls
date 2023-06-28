.
. Simple Auto Expense tracking
.   By Matthew Lake
.   Feb 2006
.
. Illustrates 
.   FINDFILE to not rely on traps
.   MDICLIENT and MDICHILD windows
.   IMPLODE / EXPLODE to get/set data in objects.
.   ListView object...variouse methods.
.
. Optimization technique...
.  Multple routines have logic in common...
.   For example AutoFirst/Next  
.    AutoFirst doesn't return and allows AutoNext to complete the processing
.
.
SEQ             FORM            "-1"
EOF             FORM            "-3"
RSEQ            FORM            "-4"
ZERO            FORM            "0"
$Change         EQU             3
FM10            FORM            10
FM10a           FORM            10
FM2             FORM            2
New             FORM            1
Update          FORM            1
fm4p3           FORM            4.3
fm4p3a          FORM            4.3
fm6p1           FORM            6.1
fm6p1a          FORM            6.1
$ff             INIT            0xff
.
DIM8            DIM             9(7)
DIM9            DIM             9
rcrdbuff        DIM             200
YN              DIM             3(0..1),(" "),("Yes")
ExpKey          DIM             23
ExpKey2         DIM             106

DateR           RECORD
YY              FORM            4
MM              FORM            2
DD              FORM            2
                RECORDEND
DateR2          RECORD          LIKE DateR

Auto            FILE            fixed=106
AutoR           RECORD          ;106 bytes
Year            DIM             4 ;1-4
Make            DIM             20 ;5-24
Model           DIM             20 ;25-44
Colr            DIM             10 ;45-54
VIN             DIM             20 ;55-74
PurDate         DIM             8 ;75-82
SelDate         DIM             8 ;83-90
PurOd           FORM            6.1 ;91-98
SelOd           FORM            6.1 ;99-106
.PurPrice form 6.2 ;107-115 todo
.TotalExpenses form 6.2 ;116-124 todo
                RECORDEND

Expense         AFILE
ExpR            RECORD          ;156 bytes
ID              DIM             20 ; Auto.vin ;1-20
Date            DIM             8  ;21-28
Od              FORM            6.1  ;29-36
FuelGal         FORM            4.3  ;37-44
Price           FORM            6.2  ;45-53
Tires           FORM            2 ; # of New tires ;54-55
TRota           FORM            1 ; rotation ;55
Oil             FORM            1 ; oil change ;56
Brakes          FORM            1 ; new brakes ;57
Misc            DIM             100 ; notes ;58-157
                RECORDEND

SMaint          IFILE
SchedMaint      RECORD
ID              DIM             20 ; Auto.vin  ;1-20
MType           FORM            1 ; 0=miles 1=date ;21
FMl             FORM            6.1 ; how often ( Miles ) ;22-29
FDt             FORM            2 ; how Often ( Months ) ;30-31
TRota           FORM            1  ; rotation  ;32
Oil             FORM            1  ; oil change  ;33
Brakes          FORM            1  ; new brakes  ;34
Misc            DIM             100 ; description of Other maintenance to do ;35-134
                RECORDEND

mwin            PLFORM          automain.plf
AutoDescF       PLFORM          autodesc.plf
AutoExpL        PLFORM          autoexpL.plf
AutoExpD        PLFORM          autoexpD.plf
AutoMnt         PLFORM          automnt.plf

usrflds         COLLECTION
.
                WINHIDE
.
. Start of program.  Make sure our data files exist and if not, create them
. 
. Vehicle descriptions is a sequential flie.
. 
                FINDFILE        "Autodefs.txt"
                IF              NOT EQUAL
                PREP            Auto,"Autodefs"
                ELSE
                OPEN            Auto,"Autodefs"
                ENDIF
.
. Auto Expense log is an aam file
.
                FINDFILE        "AutoExp.txt"
                IF              NOT EQUAL
                PREP            Expense,"AutoExp","AutoExp","U,1-20,56-157","157"
                ELSE
                OPEN            Expense,"AutoExp"
                ENDIF
.
. Scheduled maintenance is isi file.
.
                FINDFILE        "AutoSMnt.txt"
                IF              NOT EQUAL
                PREP            SMaint,"AutoSMnt","AutoSMnt","1-20","134"
                ELSE
                OPEN            SMaint,"AutoSMnt"
                ENDIF
.
. When program first begins, check to see if any vehicles need scheduled
. maintenance.
.
                CALL            ChkSMaint ; check for scheduled Maintenance Due
.
. load the main MDIClient window.
.
                FORMLOAD        mwin
.
. Wait for user actions.
.
                LOOP
                EVENTWAIT
                REPEAT
 
*************************************************************************
. Vehicle description display and edit routines.
. 
.************************************************************************
ShowDesc
.
. Load the vehicle description MDIChild window into the main window
.
                FORMLOAD        AutoDescF,AutoMWin
.
. Setup a collection of user editable fields
.
                LISTINS         usrflds,AutoDEditText002,AutoDEditText003:
                                AutoDEditText004,AutoDEditText005,AutoDEditText006:
                                AutoDEditText007,AutoDEditText008,AutoDEditNumber001:
                                AutoDEditNumber002
.
. Eventreg on collection cause we want to know when anything changes
. 
                EVENTREG        usrflds,$Change,SetUpdate
.
. Get the first vehicle
.
AutoFirst
                IF              ( New || Update )
.
. If currently displayed vehicle changed, 
. check to see if we need to save changes
. 
                CALL            AutoYN
                ENDIF
.
. Position to the beginning of vehicle description file
.
                REPOSIT         Auto,ZERO
.
. This routine is called when the next button is clicked on the screen
.
AutoNext
                IF              ( New || Update )
.
. If currently displayed vehicle changed, 
. check to see if we need to save changes
. 
                CALL            AutoYN
                ENDIF
.
. Read the next sequential record
.
                READ            Auto,SEQ;*LL,AutoR
                IF              OVER
.
. If we reached the end, set state variable for a new description
.
                CLEAR           AutoR
                SET             New
                SETPROP         AutoDButton002,visible=1
                ENDIF
.
. Jump to the display routine
.
                GOTO            SetAutoDrcrd

AutoLast
                IF              ( New || Update )
                CALL            AutoYN
                ENDIF
.
. Position to the end of the file
.
                READ            Auto,EOF;;
AutoPrev
                IF              ( New || Update )
                CALL            AutoYN
                ENDIF
.
. Read the previous sequential record
.
                READ            Auto,RSEQ;*LL,AutoR
.
. If we reach the beginning of the file, go back to the first record
.
                GOTO            AutoFirst IF OVER
.
. Routine to load the vehicle description record into objects.
. 
SetAutoDrcrd
.
. Implode the record into a delimited string
. 
                IMPLODE         rcrdbuff,$ff,AutoR
.
. Explode can insert data from a delimited string into a list of objects
. 
                EXPLODE         rcrdbuff,$ff,AutoDEditText002,AutoDEditText003:
                                AutoDEditText004,AutoDEditText005,AutoDEditText006:
                                AutoDEditText007,AutoDEditText008,AutoDEditNumber001:
                                AutoDEditNumber002
                RETURN
.
. Ask if we want to save vehicle description record?
. 
AutoYN
                ALERT           PLAIN,"Save Changes?",FM2,"Data Changed"
                IF              ( FM2 = "6" ) ;YES
                CALL            SaveAutoDrcrd
                ELSE            IF ( FM2="3" ) ; Cancel
                NORETURN
                ELSE
                CLEAR           New,Update
                SETPROP         AutoDButton002,visible=0
                ENDIF
                RETURN
.
. SetUpdate routine is called when a user changes any field in the
. editable objects collection defined above
.
SetUpdate
. we assume changes when a new entry is being made
                RETURN          IF (New)
.
. Set the update state and show the Update button so user can 
. explicitly save changes.
.
                SET             Update
                SETPROP         AutoDButton002,Title="Update"
                SETPROP         AutoDButton002,visible=1
                RETURN

SaveAutoDrcrd
. Start by getting the data from the objects
                CALL            GetAutoDrcrd
.
                IF              ( New )
.
. The auto description file is a sequential file so we
. will write new records at the end of the file.
. 
                WRITE           Auto,EOF;AutoR
                ELSE            IF (Update)
.
. If we changed an existing record, the file position is aleady at
. the record being modified.  Since we are using a fixed length file
. we can simplu UPDATE the file with the new data.
.
                UPDATE          Auto;AutoR
.
. Reset save button title
. 
                SETPROP         AutoDButton002,Title="Save"
                ENDIF
. Hide the save button as it is not shown if there is nothing to save 
                SETPROP         AutoDButton002,Visible=0
                RETURN
.
GetAutoDrcrd
.
. Get the data from the object into a delimited string
. 
                IMPLODE         rcrdbuff,$ff,AutoDEditText002,AutoDEditText003:
                                AutoDEditText004,AutoDEditText005,AutoDEditText006:
                                AutoDEditText007,AutoDEditText008,AutoDEditNumber001:
                                AutoDEditNumber002
.
. Explode the delimited string into our record variable
.
                EXPLODE         rcrdbuff,$ff,AutoR
                RETURN

*************************************************************************
. Expense log routines
.************************************************************************
.
ShowMaint
. Load the expense log screen
                FORMLOAD        AutoExpL,AutoMWin
                SETFOCUS        ExpLwin
                RETURN
.
. Once a vehicle is selected, we can load the expense log
.
ExprEdit        FORM            1
MPGtxt          DIM             5
MPG             FORM            3.3
LastOD          FORM            6.1
TripMiles       FORM            3.1
TripMilesTxt    DIM             5 ;also scratch space.
TotalExp        FORM            6.3
LoadMaint
.
. Make sure we are starting fresh
. 
                CLEAR           LastOD,MPGtxt,TotalExp
                ExpLListView001.DeleteAllItems
.
. Get the selected vehicle
.
                GETITEM         ExpLCarlist,0,FM2
                IF              ( FM2 )
. Listviews load faster when AutoRedraw is turned off
                SETPROP         ExpLListView001,AutoRedraw=0
.
. Get the vehicle description record using a record number
. 
                DECR            FM2
                READ            Auto,FM2;*ll,AutoR
.
. Build the expense log aam key using the vehicle VIN number
.
                PACK            ExpKey,"01x",AutoR.VIN
                READ            Expense,ExpKey;*LL,ExpR
                LOOP
                UNTIL           OVER
.
. Save the record position of current entry
.
                FPOSITB         Expense,FM10
.
. If we have odometer readings, tabulate the miles so we can calculate
. fuel milage
.
                IF              (LastOD)
                IF              ( Expr.FuelGal )
                CALC            TripMiles = Expr.Od - LastOD
                CALC            MPG=TripMiles / Expr.FuelGal
                MOVE            MPG,MPGtxt
                MOVE            TripMiles,TripMilesTxt
                ELSE
                CLEAR           MPGtxt,TripMilesTxt
                ENDIF
                ENDIF
.
. Add the record to the listview
.
                CALL            AddExpR2LV
.
. If this entry included fuel, save the odometer reading for milage
. calculate on next fuel entry.
.
                IF              (Expr.FuelGal)
                MOVE            ExpR.Od,LastOD
                ENDIF
.
. Keep a running total of all expenses for this vehicle
.
                ADD             Expr.Price,TotalExp
.
. Read the next record
. 
                READKG          Expense;*LL,ExpR
                REPEAT
.
. With all entries loaded, set the AutoRedraw on the listview true so
. they will be displayed
.
                SETPROP         ExpLListView001,AutoRedraw=1
                ENDIF
.
. Get total miles since vehicle was purchased.
. 
                SUB             AutoR.PurOd,LastOD
.
. Using running total expense, we can figure overall cost per mile
.
                DIV             LastOD,TotalExp
                MOVE            TotalExp,DIM9
                SETITEM         ExpLCostPerMile,0,DIM9
.
. Clear out residue
                CLEAR           MPGtxt,fm6p1,fm6p1a,fm4p3,fm4p3a
.
. Calculate the last 5 tank avg from data in listview
.
                ExpLListView001.GetitemCount giving FM10a
                IF              ( FM10a > "6" )
                MOVE            "6",FM10a
                ELSE
                DECR            FM10a  // use data available if there is not enough
                ENDIF
.
. Get start and ending odometer reading for 5 tank average
.
                ExpLListView001.GetItemText giving DIM8(1) using FM10a,1
                ExpLListView001.GetItemText giving DIM8(2) using 0,1
                MOVE            DIM8(1),fm6p1
                MOVE            DIM8(2),fm6p1a
                SUB             fm6p1,fm6p1a ; number of miles...
.
. Get the total fuel.
.
                FOR             FM10,"0",(FM10a-1)
                ExpLListView001.GetItemText giving rcrdbuff using FM10,2
                MOVE            rcrdbuff,fm4p3
                ADD             fm4p3,fm4p3a ; total fuel
                REPEAT
.
. Calculate the 5 tank average based on record fuel and miles.
.
                CALC            fm4p3=fm6p1a/fm4p3a
                PACK            rcrdbuff,fm4p3," MPG"
                SETITEM         ExpLAvgMPG,0,rcrdbuff
.
                RETURN

AddExpR2LV
.
. Build a delimited string from the record
.
                IMPLODE         rcrdbuff,$ff,ExpR.Od,ExpR.FuelGal,ExpR.Price:
                                ExpR.Tires,YN(ExpR.TRota),YN(ExpR.Oil):
                                YN(ExpR.Brakes)
.
. Explode the delimited string into an array
. 
                EXPLODE         rcrdbuff,$ff,DIM8
.
. Ddon't display 0 tires 
.
                IF              ( ExpR.Tires = 0 )
                CLEAR           DIM8(4)
                ENDIF
.
. If we are not editting and existing record, insert at beginning of LV
. 
                IF              ( ExprEdit = 0 )
                CLEAR           FM10a
                ENDIF
.
. Insert the record into the listview using the *PARAM to record
. the record position within the file.
.
                ExpLListView001.InsertItemEx using Expr.Date,FM10a:
                                *SubItem1=DIM8(1),*SubItem2=DIM8(2):
                                *SubItem3=DIM8(3),*SubItem4=MPGtxt:
                                *SubItem5=DIM8(4),*SubItem6=DIM8(5),*SubItem7=DIM8(6):
                                *SubItem8=DIM8(7),*SubItem9=Expr.Misc:
                                *SUbItem10=TripMilesTxt,*PARAM=FM10
                RETURN
.
. New expense record
.
NewExpR
.
. Load the expense entry child window into the MDIClient
.
                FORMLOAD        AutoExpD,AutoMWin
.
. Get vehicle selection data
. 
                GETITEM         ExpLCarlist,0,FM2
                GETITEM         ExpLCarlist,FM2,rcrdbuff
.
. Set selection data in expense form
. 
                SETITEM         ExpID,0,AutoR.VIN
                SETITEM         ExpDesc,0,rcrdbuff
.
. Set the focus to the new MDIChild window
                SETFOCUS        ExpWin
. Then to the object within that window
                SETFOCUS        ExpEditDateTime001
                RETURN
.
SaveExpR
.
. Get the data from all the objects into a delimiet string
.
                IMPLODE         rcrdbuff,$ff,ExpID,ExpEditDateTime001,ExpOd:
                                ExpFuelGal,ExpPrice,ExpTires,ExpRotation:
                                ExpOil,ExpBrakes,ExpMisc
.
. Explode the delimited string into expense record
. 
                EXPLODE         rcrdbuff,$ff,ExpR
.
. Check odometer against previous odometer reading
.
                ExpLListView001.GetItemText giving rcrdbuff using 0,1
                MOVE            rcrdbuff,fm6p1
                IF              ( Expr.Od < fm6p1 AND ExprEdit =0 )
                ALERT           TYPE=4,"Bad Odometer Sequence. Continue?",FM2,"Odometer"
                RETURN          IF (FM2!="6") ; only continue if YES
                ENDIF
.
                IF              ( ExprEdit )
. If were are editing an existing record, update the file and remove
. the entry from the listview
                UPDATE          Expense;Expr
                EVENTSEND       ExpButton002,4 ;click the close button.
                ExpLListView001.DeleteItem using FM10a
                ExpLListView001.GetItemText giving TripMilesTxt using FM10a,1
                MOVE            TripMilesTxt,LastOD
                ELSE
. Write the new recorde and get the file position
                WRITE           Expense;Expr
                FPOSITB         Expense,FM10
                ENDIF
.
. If entry was for fuel, calculate MPG
. 
                IF              ( Expr.FuelGal )
                CALC            TripMiles= Expr.Od - LastOD
                CALC            MPG= TripMiles / Expr.FuelGal
                MOVE            MPG,MPGtxt
                MOVE            TripMiles,TripMilesTxt
                MOVE            Expr.Od,LastOD
                ELSE
                CLEAR           MPGtxt,TripMilesTxt
                ENDIF
.
. Add the entry to the listivew
                CALL            AddExpR2LV
.
. Clean up
. 
                CLEAR           Expr,ExprEdit
                IMPLODE         rcrdbuff,$ff,ExpR
                EXPLODE         rcrdbuff,$ff,ExpEditDateTime001,ExpOd:
                                ExpFuelGal,ExpPrice,ExpTires,ExpRotation:
                                ExpOil,ExpBrakes,TripMilesTxt,ExpMisc
                RETURN
.
. Routine to edit existing expense record
. 
EditExpDetail
                ExpLListView001.GetNextItem giving FM10a using 2 ; selected
.
. Abort if nothing is selected
. 
                RETURN          IF (FM10a = SEQ)
.
. Get the file position from the item parameter of the listview
. 
                ExpLListView001.GetItemParam giving FM10 using FM10a
.
. Reposition the file and read it so it can be updated using UPDATE
. 
                REPOSIT         Expense,FM10
                READ            Expense,SEQ;*LL,ExpR
.
. load the expense detail screen
.
                CALL            NewExpR
.
. Set the edit state and the data into the expense detail screen
. 
                SET             ExprEdit
                IMPLODE         rcrdbuff,$ff,ExpR
                EXPLODE         rcrdbuff,$ff,ExpID,ExpEditDateTime001,ExpOd:
                                ExpFuelGal,ExpPrice,ExpTires,ExpRotation:
                                ExpOil,ExpBrakes,ExpMisc
.   
                RETURN
.
. Export expense data to a CSV file.
. 
ExportExpData
ExpName         DIM             50
ExpPath         DIM             200
ExpFName        DIM             250
.
. Get a file name
. 

                GETFNAME        PREP,"Save File",ExpName,ExpPath,"CSV"
                RETURN          IF OVER
.
. Make sure path has a trailing "\"
.
                ENDSET          ExpPath
                CMATCH          "\",ExpPath
                IF              NOT EQUAL
                APPEND          "\",ExpPath
                ENDIF
                RESET           ExpPath
.
. Build a fully qualified file name
.
                PACK            ExpFName,ExpPath,ExpName
.
. Use the listview SaveCSVFile method to export the data.
.
                ExpLListView001.SaveCSVFile using ExpFName
                RETURN

*************************************************************************
. Auto Maintenance routines
.************************************************************************
.
FreqData1       DIM             10
FreqData2       DIM             10
FreqData3       DIM             20
DescData        DIM             100
.
. routine to check if any maintenance is due.
. 
ChkSMaint
.
. Read through vehicle descriptions and look at what scheduled maintenance 
. exist for the car.
. Then check each scheduled maintenance for an expense record. Check the data 
. against the Maint frequency.  If maintenance is due, show on list.
. 
CurOD           FORM            6.1
.
. Start at the beginning maintenance list.
.
                REPOSIT         Auto,ZERO
                LOOP
                READ            Auto,SEQ;*ll,AutoR
                UNTIL           Over
.
. If the vehicle has a odometer reading when sold, don't check maintenance
. 
                CONTINUE        if ( AutoR.SelOd )
.
                PACK            ExpKey,"01x",AutoR.VIN
.
. Get a scheduled maintenance record
. 
                READ            SMaint,AutoR.VIN;*ll,SchedMaint
                LOOP
                UNTIL           OVER
.
. Start at the end of the expense log looking for a matching expense
. 
                READLAST        Expense,ExpKey;*ll,ExpR
                IF              NOT OVER
.
. Get the most recent odometer reading
. 
                MOVE            Expr.Od,CurOD
                PACK            ExpKey2,"02L",SchedMaint.TRota,SchedMaint.Oil:
                                SchedMaint.Brakes,SchedMaint.Misc
                BUMP            ExpKey2
.
. Use wild cards for entries we don't care about
. 
                REPLACE         "0?",ExpKey2
                RESET           ExpKey2
.
. Find last occurrance of maintenance.
. 
                CALL            LastSchMaintOccr
.
                ENDIF
. Get the next scheduled maintenance record
. 
                READKS          SMaint;*ll,SchedMaint
                REPEAT          until (SchedMaint.ID != AutoR.VIN)
.  
                REPEAT
. 
                RETURN
.
. Routine to notify user that maintenance is due for a vehicle
. 
ShowMaintDue
.
. to-do...maintenance due list
. .
                CALL            BuildFreqData
                PACK            rcrdbuff,AutoR.Year,"-",AutoR.Model," - ",DescData
                ALERT           NOTE,rcrdbuff,FM2,"Maintenance Due"
. 
                RETURN
.
. Show the maintenance schedual
.
SMaint
.
.  load the maintenance MDIChild window into the MDIClient
.
                FORMLOAD        AutoMnt,AutoMWin
.
.  Setup the listview
.
                MaintListView001.InsertColumn using "Freq",80,0
                MaintListView001.InsertColumn using "Description",200,1
                MaintListView001.InsertColumn using "Next",200,2
.
.  Show which vehicle is selected
.
                SETITEM         MaintID,0,AutoR.VIN
                PACK            rcrdbuff,AutoR.Year,"-",AutoR.Model
                SETITEM         MaintLabelText001,0,rcrdbuff
.
.  Load the schedual
.
                CALL            LoadSchMaint
.
. Make sure maintenance window had focus, then the object on the window
.
                SETFOCUS        MaintWIn
                SETFOCUS        MaintFreq
. 
                RETURN
.
. Routine to get the maintenance data
.
LoadSchMaint
.
. Get a maintenance record
. 
                READ            SMaint,AutoR.VIN;*ll,SchedMaint
. 
                LOOP
                UNTIL           OVER
.
. Based on expense record, find out how long until maintenance item is due
.
                PACK            ExpKey,"01x",AutoR.VIN
                CALL            LastSchMaintOccr
                IF              ( CurOD )
.
. If maintenance is based on miles, how many more miles until it 
. needs to be done
.
                SUB             CurOD,SchedMaint.FMl,CurOD
                PACK            rcrdbuff,CurOD," Miles"
                ELSE
. Otherwise, just use due date
                IMPLODE         rcrdbuff,"-",DateR2
                ENDIF
.
. Put result in the maintenance listview
.
                CALL            AddShed2LV
.
. Get next scheduled maintenance record
. 
                READKS          SMaint;*ll,SchedMaint
                REPEAT          until ( SchedMaint.ID != AutoR.VIN )
.  
                RETURN
.
. Routine to figure out the last time a maintenance item was done
.
LastSchMaintOccr
.
. Get the current odometer reading from the last recorded expense
. 
                READLAST        Expense,ExpKey;*ll,ExpR
                IF              NOT OVER
                MOVE            Expr.Od,CurOD ;most recent odometer reading
.
. Build a key that selects the maintenance item we are looking for
. 
                PACK            ExpKey2,"02L",SchedMaint.TRota,SchedMaint.Oil:
                                SchedMaint.Brakes,SchedMaint.Misc
                BUMP            ExpKey2
                REPLACE         "0?",ExpKey2
                RESET           ExpKey2
.
. Since we want the most recent occurrance, we start reading
. at the last record
.
                READLAST        Expense,ExpKey,ExpKey2;*ll,ExpR
                IF              NOT OVER
.
. Figure out the maintenance schedual
. 
                IF              ( SchedMaint.MType )
.
. If it is by date, we don't care about odometer readings
. 
                CLEAR           CurOD
.
. Get today's date
.
                CLOCK           TIMESTAMP,rcrdbuff
                UNPACK          rcrdbuff,DateR
                UNPACK          ExpR.Date,DateR2
.
.  Offset last maintenance date by frequency
.
                ADD             SchedMaint.FDt,DateR2.MM
                IF              ( DateR2.MM > "12" )
                SUB             "12",DateR2.MM
                INCR            DateR2.YY
                ENDIF
.
.  If maintenance is past due, notify user
.
                IF              ( DateR2.YY < DateR.YY || DateR2.MM < DateR.MM )
                CALL            ShowMaintDue
                ENDIF
.
                ELSE
.
. If frequency is mileage based, how many miles have we logged since 
. it was last done
                SUB             ExpR.Od,CurOD
.
.  If maintenance is past due, notify user
.
                IF              ( CurOD > SchedMaint.FMl )
                CALL            ShowMaintDue
                ENDIF
                ENDIF
                ELSE
.
. If no expense record exists for maintenance item, assume it is due.
.
                CALL            ShowMaintDue
                ENDIF
                ENDIF
.    
                RETURN
.
. Add an item to the scheduled maintenance list
.
SaveSchMaint
.
. Make sure we do not have residual data
.
                CLEAR           SchedMaint
.
. Use the vehicle VIN number as ID
.
                GETITEM         MaintID,0,SchedMaint.ID
.
. Get the schedule type ( date or miles )
.
                GETITEM         MaintRdoMnth,0,SchedMaint.MType
.
. Get the frequency data
.
                IF              (SchedMaint.MType)
                GETPROP         MaintFreq,VALUE=SchedMaint.FDt
                ELSE
                GETPROP         MaintFreq,VALUE=SchedMaint.FMl
                ENDIF
.
. Maintenance record description
. 
                MaintDesc.GetText giving rcrdbuff
                SWITCH          rcrdbuff
                CASE            "Oil Change"
                SET             SchedMaint.Oil
                CASE            "Service Brakes"
                SET             SchedMaint.Brakes
                CASE            "Tire Rotation"
                SET             SchedMaint.TRota
                DEFAULT
                MOVE            rcrdbuff,SchedMaint.Misc
                ENDSWITCH
.
. Record the item and add it to the listview
.
                WRITE           SMaint;SchedMaint
                CALL            AddShed2LV
. 
                RETURN
.
. Add maintenance record to listview
.
AddShed2LV
.
. call data formatting routine
.
                CALL            BuildFreqData
.
. Insert all the columns with one statement
.
                MaintListView001.InsertItemEx Using FreqData3,*SubItem1=DescData,*SubItem2=rcrdbuff
. 
                RETURN

BuildFreqData
.
. Get frequency value and description
.
                LOAD            FreqData1,(SchedMaint.MType+1),SchedMaint.FMl,SchedMaint.FDt
                LOAD            FreqData2,(SchedMaint.MType+1)," Miles", " Months"
.
. Build a meaningful description
.
                PACK            FreqData3,FreqData1,FreqData2
.
. Interpret description data
.
                IF              ( SchedMaint.TRota )
                MOVE            "Tire Rotation",DescData
                ELSE            IF ( SchedMaint.Oil )
                MOVE            "Oil Change",DescData
                ELSE            IF ( SchedMaint.Brakes )
                MOVE            "Brake Service",DescData
                ELSE
                MOVE            SchedMaint.Misc,DescData
                ENDIF
. 
                RETURN

DelSchMaint
.
. Not implemented
. 
                RETURN
