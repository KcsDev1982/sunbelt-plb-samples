*---------------------------------------------------------------
.
. Program Name: chart_samp.pls
. Description:  PL/B and Google Charts
.   See link:
.      "https://developers.google.com/chart/interactive/docs/quick_start"
.
.  For web server change plbwebstartwv.html to look like
.       example_plbwebstartwv.html
.
.
. Revision History:
.
. Date: 03/25/2025
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc

                CIFNDEF         $CLI_STATE_CORDOVA
$CLI_STATE_CORDOVA EQU          2
$CLI_STATE_BOOTSTRAP5 EQU       16
                CENDIF

// Runtime status variables
isGui           BOOLEAN
isWebSrv        BOOLEAN
isPlbSrv        BOOLEAN
isWebview       BOOLEAN
isWebCliApp     BOOLEAN
isSmallScreen   BOOLEAN

// Global data
mainForm        PLFORM          chart_samp.plf
Client          CLIENT
htmlBuffer      DIM             4096
htmlPart1       INIT            "<head>":
                                "<script type='text/javascript' src='https://www.google.com/jsapi'></script>",0xD,0xA:
                                "<script type='text/javascript'>",0xD,0xA:
                                "// Load the Visualization API and the piechart package.",0xD,0xA:
                                "google.load('visualization', '1.0', {'packages':['corechart']});",0xD,0xA:
                                "// Set a callback to run when the Google Visualization API is loaded.",0xD,0xA:
                                "google.setOnLoadCallback(drawChart);",0xD,0xA:
                                "// Callback that creates and populates a data table,",0xD,0xA:
                                "// instantiates the pie chart, passes in the data and",0xD,0xA:
                                "// draws it.",0xD,0xA:
                                "function drawChart() {",0xD,0xA:
                                "// Create the data table.",0xD,0xA:
                                "var data = new google.visualization.DataTable();",0xD,0xA

htmlPart2       INIT            "chart.draw(data, options);",0xD,0xA:
                                "}",0xD,0xA:
                                "</script>",0xD,0xA:
                                "</head>",0xD,0xA:
                                "<body>",0xD,0xA:
                                "<!--Div that will hold the pie chart-->",0xD,0xA:
                                "<div id='chart_div'></div>",0xD,0xA:
                                "<script type='text/javascript'>",0xD,0xA:
                                "drawChart();",0xD,0xA:
                                "</script>",0xD,0xA:
                                "</body>",0xD,0xA

htmlChart1      INIT            "data.addColumn('string', 'Topping');",0xD,0xA:
                                "data.addColumn('number', 'Slices');",0xD,0xA:
                                "data.addRows([",0xD,0xA:
                                " ['Mushrooms', 3],",0xD,0xA:
                                " ['Onions', 1],",0xD,0xA:
                                " ['Olives', 1],",0xD,0xA:
                                " ['Zucchini', 1],",0xD,0xA:
                                " ['Pepperoni', 2]",0xD,0xA:
                                " ]);",0xD,0xA:
                                "// Set chart options",0xD,0xA:
                                "var options = {'title':'How Much Pizza I Ate Last Night',",0xD,0xA:
                                " 'width':500,",0xD,0xA:
                                " 'height':400};",0xD,0xA:
                                "// Instantiate and draw our chart, passing in some options.",0xD,0xA:
                                "var chart = new google.visualization.PieChart(document.getElementById('chart_div'));",0xD,0xA

htmlChart2      INIT            "data.addColumn('string', 'Task');",0xD,0xA:
                                "data.addColumn('number', 'Hours per Day');",0xD,0xA:
                                " data.addRows([",0xD,0xA:
                                " ['Work',     11],",0xD,0xA:
                                " ['Eat',      2],",0xD,0xA:
                                " ['Commute',  2],",0xD,0xA:
                                " ['Watch TV', 2],",0xD,0xA:
                                " ['Sleep',    7]",0xD,0xA:
                                " ]);",0xD,0xA:
                                "var options = {",0xD,0xA:
                                "title: 'My Daily Activities',",0xD,0xA:
                                " is3D: true,",0xD,0xA:
                                " 'width':500,",0xD,0xA:
                                " 'height':400};",0xD,0xA:
                                "// Instantiate and draw our chart, passing in some options.",0xD,0xA:
                                "var chart = new google.visualization.PieChart(document.getElementById('chart_div'));",0xD,0xA



*---------------------------------------------------------------
// <program wide variables>
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
. Check what type of runtime support we have
.
CheckStatus     LFUNCTION
                ENTRY
runtimeData     DIM             50
runtimeVersion  DIM             5
unused          DIM             1
plbRuntime      DIM             9
WidthData       DIM             5
checkWidth      FORM            5
.
. Check for character mode runtime
.
                GETMODE         *GUI=isGui

                IF              (isGui)
.
. check windows console.
.
                CLOCK           VERSION,runtimeData
                UNPACK          runtimeData,runtimeVersion,unused,plbRuntime
                CHOP            plbRuntime
          
                IF              (NOCASE plbRuntime == "PLBCON")
                CLEAR           isGui
                ENDIF

                IF              (NOCASE plbRuntime == "PLBWEBSV")
                SET             isWebSrv
                ENDIF

                IF              (NOCASE plbRuntime == "PLBSERVE")
                SET             isPlbSrv
                ENDIF

                ENDIF

                IF              (isGui)
                WINHIDE
               
                Client.Getstate Giving isWebCliApp Using $CLI_STATE_CORDOVA
                Client.Getstate Giving isWebview Using $CLI_STATE_BOOTSTRAP5
.
. Check for a small screen (such as iphone)
.
                IF              (isWebSrv)
                Client.GetWinInfo Giving WidthData Using 0x2
                MOVE            WidthData To checkWidth
                MOVE            (checkWidth <= 700) to isSmallScreen
                ENDIF

                ENDIF

                FUNCTIONEND

*................................................................
.
. Chart 1
.
Chart1          LFUNCTION
                ENTRY
                PACK            htmlBuffer,htmlPart1,htmlChart1,htmlPart2
                htmlChart.InnerHtml Using htmlBuffer
                FUNCTIONEND

*................................................................
.
. Chart 2
.
Chart2          LFUNCTION
                ENTRY
                PACK            htmlBuffer,htmlPart1,htmlChart2,htmlPart2
                htmlChart.InnerHtml Using htmlBuffer

                FUNCTIONEND

*................................................................
.
. Chart 3 - Turn chart2 into a Bar chart
.
Chart3          LFUNCTION
                ENTRY
                PACK            htmlBuffer,htmlPart1,htmlChart2,htmlPart2
                SCAN            "PieChart",htmlBuffer
                SPLICE          "Bar",htmlBuffer,3
                RESET           htmlBuffer
                htmlChart.InnerHtml Using htmlBuffer

                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY
result          FORM            4

                CALL            CheckStatus

                IF              (!isGui)
                KEYIN           "This runtime can't run this program. ",result
                STOP
                ENDIF

                IF              (!isWebview)
                ALERT           STOP,"This program requires WebView support.",result
                STOP
                ENDIF

.
. On smaller screens change to % positioning for left and width
.
                IF              (isWebCliApp || isSmallScreen)
                SETMODE         *PERCENTCONVERT=1
                ENDIF

                FORMLOAD        mainForm

                IF              (!isWebSrv)
                PACK            htmlBuffer,htmlPart1,htmlChart1,htmlPart2
                htmlChart.InnerHtml Using htmlBuffer
                ENDIF

		SETFOCUS	btnChart1

                FUNCTIONEND
