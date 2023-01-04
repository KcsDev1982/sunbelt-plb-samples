*---------------------------------------------------------------
.
. Program Name: appqrcode
. Description:  PlbWebCli Application QRCode Generator 
.
. Revision History:
.
. 17-04-07 whk
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*---------------------------------------------------------------   
AppForm         PLFORM          "appqrcode.pwf"
Client          CLIENT
.
.
.
HtmlPageQR      INIT            "<img src='https://chart.googleapis.com/chart?chs=150x150&cht=qr&chl={#"name#": #"appmaster#"}&choe=UTF-8' ":
                                " alt='QR code' />" 
.
.
.
                FORMLOAD        AppForm
                Panel1.InnerHtml Using HtmlPageQR
                LOOP
                EVENTWAIT
                REPEAT
                STOP





