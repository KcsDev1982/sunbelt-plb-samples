*---------------------------------------------------------------
.
. Program Name: wordlookup
. Description:  Look up a word defintion from a Web Service
.               using REST
.
.  For more information on the we service see:
.
.  https://dictionaryapi.dev/
.
. Revision History:
.
. 05-04-23 whk
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 


*---------------------------------------------------------------
MainForm        PLFORM          wordlookupf.plf

RestUrl         INIT            "api.dictionaryapi.dev"

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
. Decode the JSON result. Just look up the first definition.
.
DecodeResult    LFUNCTION
JsonData        DIM             ^ // Pointer to the data received
ObjectPtr       OBJECT          ^
                ENTRY
JsonInfo        XDATA
DefinitionData  DIM             400
Result          FORM            2

                JsonInfo.LoadJson Using JsonData

                CALL            FetchJsonStr Using JsonInfo,"definition",DefinitionData
                EXCEPTSET       ParamErr IF FORMAT
                EXCEPTSET       ParamErr IF OBJECT
                SETPROP         ObjectPtr;Text=DefinitionData
                RETURN
.
. Parameter error. See the plberrors.xml file for description of error.
.
ParamErr        ALERT           STOP,S$ERROR$,Result
                FUNCTIONEND
.
*................................................................
.
. Lookup a word
.
LookupWord      LFUNCTION
                ENTRY
Flags           FORM            8
Response        DIM             40960
Word            DIM             40
Resource        DIM             100
HttpResult      DIM             80
Success		FORM		1

                GETPROP         edtWord,Text=Word
                PACK            Resource with "/api/v2/entries/en/",Word
                MOVE            ($HTTP_FLAG_NOHEADER+$HTTP_FLAG_HTTP11+$HTTP_FLAG_SSL+$HTTP_FLAG_USESUNSSL) to Flags

                HTTP            RestUrl,Resource,*HttpResult=HttpResult,*Result=Response,*Flags=Flags

                IF              (Nocase HttpResult LIKE "200 ok%" )
                CALL            DecodeResult Using Response,edtResult
		SET		Success
                ELSE
                PACK            Response, "The result from the website was: ",HttpResult
                SETPROP         edtResult;Text=Response
		CLEAR		Success
                ENDIF

                FUNCTIONEND	Using Success

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY

                WINHIDE

                FORMLOAD        MainForm
                
                FUNCTIONEND
