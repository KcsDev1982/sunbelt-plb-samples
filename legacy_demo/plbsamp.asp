<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML><HEAD>
<META http-equiv=Content-Type content="text/html; charset=unicode">
<%@ Language=VBScript %>
<META content="MSHTML 5.50.4207.2601" name=GENERATOR></HEAD>
<BODY>
<P><STRONG><FONT size=5><FONT color=blueviolet>Sample ASP 
<FONT>Page</FONT></FONT></FONT></STRONG>
</P>
<%
       Dim PlbSrv
       Dim ResString
       Set PlbSrv = Server.CreateObject("Plbwin.ProgramNE")
       PlbSrv.Run( "nesrv" )
       ResString = "Smith" 
%>

<P>Results:</P>
<%
       PlbSrv.EventSend 1, ResString
       Response.Write ResString
       PlbSrv.EventSend 2, ResString
       Response.Write ResString
       PlbSrv.EventSend 2, ResString
       Response.Write ResString
       PlbSrv.EventSend 3
       Set PlbSrv = Nothing
 %>
</BODY></HTML>
