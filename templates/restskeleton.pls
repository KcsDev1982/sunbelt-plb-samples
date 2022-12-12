*---------------------------------------------------------------
.
. Program Name: restskeleton
. Description:  A skeleton program for the REST API
.
. Revision History:
.
. <date> <programmer>
. Original code
.
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*---------------------------------------------------------------

Runtime         RUNTIME

GUI             FORM            2  

Request         DIM             40
Uri             DIM             400
UriSections     FORM            3
UriParts        DIM             100(7)
Host            DIM             100

*................................................................
.
. Code start
.
                CALL            Main
                STOP

*................................................................
.
. RestDelete
.
. Return the supported actions
.
RestDelete      LFUNCTION
                ENTRY
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                FUNCTIONEND

*................................................................
.
. RestGet
.
. Return the supported actions
.
RestGet         LFUNCTION
                ENTRY
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                FUNCTIONEND

*................................................................
.
. RestOptions
.
. Return the supported actions
.
RestOptions     LFUNCTION
                ENTRY
OptionHdr       INIT            "Allow: GET,POST,PUT,DELETE,OPTIONS",0xD,0xA

                Runtime.HttpResponse Using *HttpCode=200,*MimeType="text/html", *Body="",*ExtraHdrs=OptionHdr, *Options=0
                FUNCTIONEND

*................................................................
.
. RestPatch
.
. Return the supported actions
.
RestPatch       LFUNCTION
                ENTRY
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                FUNCTIONEND

*................................................................
.
. RestPost
.
. Return the supported actions
.
RestPost        LFUNCTION
                ENTRY
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                FUNCTIONEND

*................................................................
.
. RestPut
.
. Return the supported actions
.
RestPut         LFUNCTION
                ENTRY
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0
                FUNCTIONEND

*................................................................
.
. Main - Main program entry point
.
Main            LFUNCTION
                ENTRY

.
. Decoding the requested action
.
                GETMODE         *GUI=GUI
                IF              ( GUI != 0 )
                WINHIDE
                ENDIF

                Runtime.CgiString Giving Request Using "REQUEST_METHOD"
                Runtime.CgiString Giving Uri Using "REQUEST_URI"
                Runtime.CgiString Giving Host Using "HTTP_HOST"

                EXPLODE         Uri Using "/" Giving UriSections into UriParts

                SWITCH          Request
 
                CASE            "DELETE"
                CALL            RestDelete

                CASE            "GET"
                CALL            RestGet

                CASE            "OPTIONS"
                CALL            RestOptions

                CASE            "PATCH"
                CALL            RestPatch

                CASE            "POST"
                CALL            RestPost

                CASE            "PUT"
                CALL            RestPut
 
                DEFAULT
                Runtime.HttpResponse Using *HttpCode=501,*MimeType="text/html", *Body="Not Implemented" *ExtraHdrs="", *Options=0

                ENDSWITCH

                FUNCTIONEND
