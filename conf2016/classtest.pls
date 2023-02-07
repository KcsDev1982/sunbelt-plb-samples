*---------------------------------------------------------------
.
. Program Name: classtest
. Description:  Conf 2016 Sample
.
.  This program requires gauge.html, myjstest.html
.  and mycss.css to be put in the http_root or plbwv_html directory
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*-------------------------------------------------------

ClassForm       PLFORM          "classtest.pwf"
Client          CLIENT
Count           FORM            "0"
OkFlag          FORM            "1"
ErrTry          FORM            "5"
.
.
.
HtmlPageQR      INIT            "<img src='https://chart.googleapis.com/chart?chs=150x150&cht=qr&chl=Hello%20world&choe=UTF-8' ":
                                " alt='QR code' />" 
.
. Table
.
HtmlTable       INIT            "<table>":
                                "<tr><th>Month</th><th>Weather</th></tr>":
                                "<tr><td>March</td><td>Snow<td></tr>":
                                "</table>"
.
. Map
.
LocData         DIM             300
LocHtml         DIM             300
.
. Chart
.
ChartHtml       INIT            "<iframe width='500px' height='200px' src='gauge.html'</iframe>"
.
. Js Class
.
ResStr          DIM             200
HtmlObjId       DIM             20
GetJsStr        PROFILE         !js@frame1,MyJsFuncStr,DIM,DIM
HtmlPageJs1     INIT            "<iframe id='frame1' style='width:80%; border-width:0; margin-left:10px;'":
                                " src='myjstest.html' sandbox='allow-same-origin allow-scripts allow-top-navigation'></iframe>"
.
.
.
                WINHIDE
                FORMLOAD        ClassForm
                WebForm1.SetAsClient
                LOOP
                EVENTWAIT
                REPEAT
                STOP

TestIt          LFUNCTION
                ENTRY
                ADD             "1" TO Count
                PERFORM         Count Of TestItQR, TestItTable,TestItLoc, TestItG, TestItJs
                FUNCTIONEND
                

TestItQR        LFUNCTION
                ENTRY
                Panel1.InnerHtml Using HtmlPageQR
                FUNCTIONEND

TestItTable     LFUNCTION
                ENTRY
                Client.AddCss   Using "mycss.css"
                SETPROP         Button2,WebClass="myclass"
                Panel1.InnerHtml Using HtmlTable
                FUNCTIONEND

TestItLoc       LFUNCTION
                ENTRY
                Client.GetLocation Giving LocData
                PACK            LocHtml Using "<img src='http://maps.googleapis.com/maps/api/staticmap?center=":
                                LocData:
                                "&zoom=14&size=400x300&sensor=false' />"

                Panel1.InnerHtml Using LocHtml
                FUNCTIONEND

TestItG         LFUNCTION
                ENTRY
                Panel1.InnerHtml USING ChartHtml
                FUNCTIONEND

TestItJs        LFUNCTION
                ENTRY
                MOVE            "0" To Count
                Panel1.InnerHtml Using HtmlPageJs1
                Client.FlushMessages
                Client.JsMakeString Giving HtmlObjId Using "MyJsTest1"
                MOVE            "5" To ErrTry
                TRAP            RetryFunc Noreset If Object  
                LOOP
                MOVE            "1" To OkFlag
                WINAPI          GetJsStr Giving ResStr Using HtmlObjId
                BREAK           If (OkFlag = 1)
                REPEAT
                TRAPCLR         Object
                SETPROP         LabelText1, Text=ResStr  
                FUNCTIONEND

RetryFunc       LFUNCTION
                ENTRY
                SUB             "1" From ErrTry
                IF              ( ErrTry = 0 ) 
                TRAPCLR         Object
                ELSE
                MOVE            "0" To OkFlag
                ENDIF
                PAUSE           "1"
                FUNCTIONEND




