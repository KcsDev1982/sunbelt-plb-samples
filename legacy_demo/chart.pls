*...........................................................................
. Example Program: TCHART.PLS by BILL KEECH
.
. This program uses automation to build an Excel chart
.
. Copyright @ 1999, Sunbelt Computer Systems, Inc. All Rights Reserved.
.............................................................................
. Change the file name D:\AutTest\Test1 to an existing scratch excel
. file if you decide to open an existing spreadsheet below.
.
App             AUTOMATION      Class="Excel.Application"
Books           AUTOMATION
Book            AUTOMATION
Sheets          AUTOMATION
Sheet           AUTOMATION
Charts          AUTOMATION
Chart           AUTOMATION
Range           AUTOMATION
.
OptVar          VARIANT
VT_ERROR        EQU             10
.
DISP_E_PARAMNOTFOUND INTEGER    4,"0x80020004"
.
AutoTrue        INTEGER         4,"0xffffffff"
FILENAME        DIM             50 

TESTCHARTS      EQU             0
.
. Lets make up a standard optional variant
.
                CREATE          OptVar,VarType=VT_ERROR:
                                VarValue=DISP_E_PARAMNOTFOUND
.
. First create excel and make it visible
.
                CREATE          App
                SETPROP         App,*Visible=AutoTrue
.
. Next lets get the workbooks collection
.
                GETPROP         App,*Workbooks=Books
.
. To open a book (This would be an existing speadsheet file)
.
.   Books.Open       Giving Book Using "D:\AutTest\Test1"
.
. To create a new book (spreadsheet)
.
                Books.Add
                Books.Item      Giving Book Using 1
.
. Now find the first sheet from the sheets collection
.
                GETPROP         Book,*Sheets=Sheets
                Sheets.Item     Giving Sheet Using 1
.
. Lets clear out the sheet
.
                Sheet.Range("A1","W40").Clear
.
. Now stuff some data into the sheet
.
                SETPROP         Sheet.Range("A3", "A3"),*Value="March"
                SETPROP         Sheet.Range( "B3", "B3"),*Value="12"
 
                SETPROP         Sheet.Range( "A4", "A4"),*Value="April"
                SETPROP         Sheet.Range( "B4", "B4"),*Value="8"
 
                SETPROP         Sheet.Range( "A5", "A5"),*Value="May"
                SETPROP         Sheet.Range( "B5", "B5"),*Value="2"
 
                SETPROP         Sheet.Range( "A6", "A6"),*Value="June"
                SETPROP         Sheet.Range( "B6", "B6"),*Value="11"
 
                SETPROP         Sheet.Range( "A7", "A7"),*Value="July"
                SETPROP         Sheet.Range( "B7", "B7"),*Value="16"

                %IFNZ           TESTCHARTS
.
. Get a chart object and add a chart, then get the actual chart object 
.
 
                Sheet.ChartObjects Giving Charts
 
                Charts.Add      Using *Left=100, *Top=10, *Width=350:
                                *Height=250
 
                GETPROP         Charts.Item(1),*Chart=Chart
 
.
. The chart wizard requires a range object to create the chart. We get this
. by using the special $IDispatch property. This will return the object
. reached after processing the object portion of the GetProp statement.
.
                GETPROP         Sheet.Range( "A3", "B7"),*$IDispatch=Range
 
.
. Now some chart wizard fun. Note that when just using positional arguments,
. optional arguments to be skipped must be replaced by a VARIANT of type
. VT_ERROR with a value of DISP_E_PARAMNOTFOUND
.
.   Chart.ChartWizard   Using Range, 11, OptVar, 1, 0, 1, 1:
.         "Use by Month", "Month", "Useage in Thousands"
.
.
. We could have also coded this as:
.
                Chart.ChartWizard Using *Source=Range:
                                *Gallery=11:
                                *PlotBy=1:
                                *CategoryLabels=0:
                                *SeriesLabels=1:
                                *HasLegend=1:
                                *Title="Use by Month":
                                *CategoryTitle="Month":
                                *ValueTitle="Useage in Thousands"
.
. Now let them see the chart before we start the next one.
.
                PAUSE           "5"
.
. Now cleanup by deleting the chart and cleaning up the data and
. releasing the objects
.
                Charts.Delete
                Range.Clear
                DESTROY         Range
                DESTROY         Chart
                DESTROY         Charts
                %ELSE
                PAUSE           "5"
                %ENDIF
.
. Now add the next set of data
.
		Sheet.Range("A1","W40").Clear
                SETPROP         Sheet.Range( "B3", "B3"),*Value="Chocolate"
                SETPROP         Sheet.Range( "B4", "B4"),*Value="12"
 
                SETPROP         Sheet.Range( "C3", "C3"),*Value="Vanilla"
                SETPROP         Sheet.Range( "C4", "C4"),*Value="8"
 
                SETPROP         Sheet.Range( "D3", "D3"),*Value="Orange"
                SETPROP         Sheet.Range( "D4", "D4"),*Value="6"

                %IFNZ           TESTCHARTS
.
. Get a chart object and add a chart, then get the actual chart object 
.
                Sheet.ChartObjects Giving Charts
                Charts.Add      Using *Top=40, *Left=250, *Width=300:
                                *Height=200
                GETPROP         Charts.Item(1),*Chart=Chart
.
. Now get the data range object for Chart Wizard
.
                GETPROP         Sheet.Range( "B3", "D4"),*$IDispatch=Range
.
. Make the chart
.
                Chart.ChartWizard Using *Source=Range, *Gallery=11, *PlotBy=2:
                                *CategoryLabels=0, *SeriesLabels=1:
                                *HasLegend=1, *Title="Use by Flavor":
                                *CategoryTitle="Flavor":
                                *ValueTitle="Useage in Barrells"
                PAUSE           "2"
.
. Now show the chart in print preview
.
                Chart.PrintOut  Using *From=1, *To=1, *Copies=1, *Preview=1:
                                *PrintToFile=0, *Collate=0
. 
.   Pause     "2"
                DESTROY         Range
                DESTROY         Chart
                DESTROY         Charts
                DESTROY         Sheet
                DESTROY         Sheets

                %ELSE
                PAUSE           "2"
                %ENDIF
.
. Lets avoid the Save Changes? dialog
.
.   SetProp   Book,*Saved=AutoTrue
.
. To save the spreadsheet we've opened or created
.
                App.GetSaveAsFileName Giving FILENAME
                Book.SaveAs     Using *FileName=FILENAME
.
. Cleanup continues
.
                DESTROY         Book
                DESTROY         Books
.
. Finally destroy excel
.
                App.Quit
                DESTROY         App
