*---------------------------------------------------------------
.
. Program Name: getphoto
. Description:  Take a picture on a phone
. 
. Revision History:
.
.   21 Jun 19   W Keech
.      Original code
.
*---------------------------------------------------------------
                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc

signonPath      DIM             %100
httpRootPath    DIM             %100 // For downloads
httpRootPath1   DIM             %100 // For browser access 
urlPath         DIM             %100
signonName      DIM             %40
.
mainForm        PLFORM          getphotof.pwf
fileUrl         DIM             400
eventData       DIM             600
fileName        DIM             200
Client          CLIENT
runtime         RUNTIME

*................................................................
.
. Code start
.
                CALL            Main
                STOP
 
*................................................................
.
. FetchJsonStringValue - Fetch string data for String 'label'
. 
. Only update the result if the label is found
. 
FetchJsonStringValue LFUNCTION
pXData          XDATA           ^
xLabel          DIM             50
dReturn         DIM             ^
                ENTRY
.
xString         DIM             200
x200            DIM             200
xError          DIM             100
nvar            FORM            2
.
. Find the specified JSON label node
. 
                PACK            s$cmdlin, "label='",xLabel,"'"
                pXData.FindNode GIVING nvar:
                                USING *FILTER=S$cmdlin:  //Locate specified JSON label!
                                *POSITION=START_DOCUMENT_NODE //Start at the beginning of the document!
                IF              ( nvar == 0 )
...
. Move to the child node of the 'orient' JSON label.
. 
                pXData.MoveToNode GIVING nvar USING *POSITION=MOVE_FIRST_CHILD
.
                IF              ( nvar == 0 )
...
. Fetch the data for the JSON  label.
. 
                pXData.GetText  GIVING xString
                PACK            s$cmdlin, xLabel,"= '",xString,"'"
                ELSE
                MOVE            "Error Move Node:", s$cmdlin
                ENDIF
                ELSE
                PACK            s$cmdlin, "Error Find Node:",nvar
                ENDIF

                TYPE            xString 
                IF              NOT EOS
                MOVE            xString, dReturn
                ENDIF
 
                FUNCTIONEND
 
*................................................................
.
. PictEvent - A picture was taken - upload it
. 
PictUploaded    LFUNCTION
                ENTRY
iname           DIM             300  
oname           DIM             300
fullUrl         DIM             300
 
                EXCEPTSET       CopyFileError IF IO
                runtime.GetDir  GIVING iname Using $GETDIR_UPLOADS
                ENDSET          iname
                APPEND          fileName to iname
                RESET           iname
                PACK            oname Using signonPath, "\", fileName 
                COPYFILE        iname To oname 

CopyFileError
                PACK            fullUrl, "http://scstestdrive.eastus.cloudapp.azure.com:8081/uploads/", fileName
                SETPROP         Pict1,*urlsource=fullUrl
                FUNCTIONEND
*................................................................
.
. PictEvent - A picture was taken - upload it
. 
PictEvent       LFUNCTION
                ENTRY

                EVENTREG        Client,AppEventDoUpload,PictUploaded,ARG1=eventData
                Client.AppUpload Using fileUrl, fileName 
                FUNCTIONEND
*................................................................
.
. TakePict - Take the picture and upload it
. 
TakePict        LFUNCTION
                ENTRY
                Client.AppGetPicture Using "{#"cleanUp#":  true }"
                Client.AppGetPicture 
                FUNCTIONEND
*................................................................
.
. Main - Main entry point
. 
Main            LFUNCTION
                ENTRY
isCordova       FORM            1

                WINHIDE
 
                Client.GetState GIVING isCordova USING *STATEMASK=2
                IF              ( isCordova == 0 )
                ALERT           NOTE,"No camera support", isCordova, "GetPhoto Error"
                STOP
                ENDIF
 
                PACK            fileName Using signonName,".jpg"
                SQUEEZE         fileName,fileName," "
 
                EVENTREG        Client,AppEventGetPict,PictEvent,ARG1=fileUrl
                SETMODE         *PercentConvert=1
                FORMLOAD        mainForm
                SETMODE         *PercentConvert=0
 
                LOOP
                EVENTWAIT
                REPEAT
                FUNCTIONEND
 
