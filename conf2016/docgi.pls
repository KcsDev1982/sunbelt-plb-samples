*---------------------------------------------------------------
.
. Program Name: docgi
. Description:  Conference 2016 Sample CGI Program
.
.  This program requires docgitest.html to be
.  put in the http_root directory. This html page
.  must be used to run the docgi program
.
.  The webserver configuration must set PLBWEB_CGI_INFODIR
.
. PLBWEB_CGI_INFODIR=c:\temp\cgi
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*-------------------------------------------------------

R               RUNTIME
DATA            DIM             240
xDATA           DIM             300
CgiName         DIM             30
.
X               PLFORM          docgi.pwf
.
                FORMLOAD        X
.
                CALL            FetchQuery_String_Raw
.
                LOOP
                EVENTWAIT
                REPEAT
		STOP
.....
. 'GetCGI'
. 
GetCGI          FUNCTION
CgiKey          DIM             30
Opt             FORM            2
                ENTRY
.
                R.CgiString     Giving DATA Using CgiKey,  Opt
                PACK            xData, CgiKey, "='", DATA,"'"
                INSERTITEM      DataList1, 0, xData
.
                FUNCTIONEND
.....
. 'GetUserParm'
.    This function retrieves a URL parameter by
.    keyname found in the EditText1.
. 
GetUserParm     FUNCTION
                ENTRY
.
                GETPROP         EditText1, TEXT=CgiName
.
                SQUEEZE         CgiName, CgiName
                TYPE            CgiName
                IF              EOS
                SETPROP         STATTEXT1, TEXT="CGI Name Required!"
                RETURN
                ENDIF
.
                CALL            GetCGI USING CgiName, "1" //Fetch URL parameter data!
.
                FUNCTIONEND
.
.....
. 'GetField'
.   This function retrieves a URL parameter by
.   pre-defined (static) keyname.
. 
GetField        FUNCTION
                ENTRY
.
NVAR            FORM            3
CNT             FORM            3
.
                ComboBox1.GetCurSel GIVING NVAR
                ComboBox1.GetText GIVING CgiName USING NVAR
.
                IF              ( NVAR == 0 )
                DataList1.ResetContent
                ENDIF
.
                CALL            GetCGI USING CgiName, "2" //Fetch pre-defined HTTP header fields!
.
                ComboBox1.GetCount GIVING CNT
                INCR            NVAR
                IF              ( NVAR >= CNT )
                CLEAR           NVAR
                ENDIF
                ComboBox1.SetCurSel USING NVAR
.
                FUNCTIONEND
.
.....
.
FetchQuery_String_Raw FUNCTION
                ENTRY
.
                R.CgiString     Giving DATA Using "QUERY_STRING"  //Query_String raw!!
.
                PACK            xData, "QUERY_STRING='", DATA,"'"
                TYPE            DATA
                IF              EOS
                SETPROP         STATTEXT1, TEXT="URL Query_String not specified!"
                RETURN
                ENDIF
.
                INSERTITEM      DataList1, 0, xData
                SETPROP         STATTEXT1, TEXT="URL QUERY_STRING parameters available!"
.
                FUNCTIONEND
.
