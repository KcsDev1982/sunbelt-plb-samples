.
*---------------------------------------------------------------
.
. Program Name: appbeacon
. Description:  PlbWebCli Application Beacon Sample 
.
. Revision History:
.
. 17-04-07 whk
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*-------------------------------------------------------

WebForm         PLFORM          appbeaconf.pwf

FullData        DIM             1000
BeaconEventData DIM             1000
.
Result          FORM            5
MaxLen          FORM            5
Form1           FORM            1
InFile          DIM             200
OutFile         DIM             40
.
Client          CLIENT
.
JsonData        XDATA
JsonOptToDisk   FORM            "6" // JSON_SAVE_USE_INDENT+JSON_SAVE_USE_EOR
.
DisplayName     DIM             40
FindRes         FORM            8

BeaconUUID      INIT            "B9407F30-F5F8-466E-AFF9-25556B57FE6D"
.  
*................................................................
.
. Code start
.
                CALL            Main
                LOOP
                EVENTWAIT
                REPEAT
                STOP

*................................................................
.
. HandleSel - Handle a request to perform a test
.
HandleSel	LFUNCTION
                ENTRY
                EVENTINFO       0,result=Result
                SWITCH          Result
                CASE            1
                CALL            MonitorBeacon
                CASE            2
                CALL            RangeBeacons
                CASE            3
                CALL            InfoBeacon
                CASE            4
                CALL            RequestState
                CASE            5 
                CALL            ClearAll 
                CASE            6
                STOP
                ENDSWITCH
                FUNCTIONEND

*................................................................
.
. BeaconEvents
.
BeaconEvents	LFUNCTION
                ENTRY
                PACK            FullData Using "<div style='word-break: break-all'>",BeaconEventData,"</div>"
                Panel2.innerHtml Using FullData
                JsonData.LoadJson Using BeaconEventData
                JsonData.SaveJson Using "appbeacon.json", JsonOptToDisk
                FUNCTIONEND

*................................................................
.
. MonitorBeacon
.
MonitorBeacon	LFUNCTION
                ENTRY
                Client.AppBeacon Giving Result Using "Mint", "B9407F30-F5F8-466E-AFF9-25556B57FE6D",16100,9770,*FLAGS=AppBeaconMonitorStart
                FUNCTIONEND

*................................................................
.
. RangeBeacons
.
RangeBeacons	LFUNCTION
                ENTRY
                Client.AppBeacon Giving Result Using "Estimote", BeaconUUID,*FLAGS=AppBeaconRangeStart
                FUNCTIONEND

*................................................................
.
. InfoBeacon
.
InfoBeacon	LFUNCTION
                ENTRY
                Client.AppBeaconStatus Giving Result
                FUNCTIONEND

*................................................................
.
. RequestState
.
RequestState	LFUNCTION
                ENTRY
                Client.AppBeacon Giving Result Using "Mint", "B9407F30-F5F8-466E-AFF9-25556B57FE6D",16100,9770,*FLAGS=AppBeaconRequestState
                FUNCTIONEND

*................................................................
.
. ClearAll
.
ClearAll	LFUNCTION
                ENTRY
                Client.AppBeacon Giving Result Using *FLAGS=(AppBeaconMonitorStopAll+AppBeaconRangeStopAll)
                Panel2.innerHtml Using "<h1>Stopped all</h1>"
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
. Register and Startup the events, load the main form
.
Main            LFUNCTION
                ENTRY
                WINHIDE

		
                FORMLOAD        WebForm
.
                EVENTREG        Client,AppEventDidDetermineStateForRegion,BeaconEvents,ARG1=BeaconEventData
                EVENTREG        Client,AppEventDidStartMonitoringForRegion,BeaconEvents,ARG1=BeaconEventData
                EVENTREG        Client,AppEventDidRangeBeaconsInRegion,BeaconEvents,ARG1=BeaconEventData
                EVENTREG        Client,AppEventMonitoringDidFailForRegionWithError,BeaconEvents,ARG1=BeaconEventData
                EVENTREG        Client,AppEventDidExitRegion,BeaconEvents,ARG1=BeaconEventData
                EVENTREG        Client,AppEventDidEnterRegion,BeaconEvents,ARG1=BeaconEventData
                EVENTREG        Client,AppEventBeaconStatus,BeaconEvents,ARG1=BeaconEventData

                Client.AppBeacon Giving Result Using *FLAGS=(AppBeaconRequestWhenInUseAuthorization+AppBeaconBlueToothEnable)
		// Client.AppBeacon Giving Result Using *FLAGS=AppBeaconRequestAlwaysAuthorization
		FUNCTIONEND
