+==============================================================================
. PROGRAM: ADMSAMP3
.
. SYSTEM:  WINDOWS
.
.
. AUTHOR:  EDWARD R. BOEDECKER
.
.    Sunbelt Computer Systems, Inc.
.    Tyler, Texas   75701
.
. PURPOSE: Demonstrate user program access to SUNADMIN utility using GUI.
.    This sample shows use of SUNADMIN_KEY access to SUNADMIN utility.
.
*==============================================================================
.
OPT             RECORD
.
KEY             DIM             16         ;User Access Key String
TYPE            FORM            1         ;Section Type
LIST            FORM            1         ;List option
VERBOSE         FORM            1         ;Verbose option to show all
PUBLIC          DIM             17         ;Public Key
ADD             DIM             17         ;Add string
DEL             DIM             17         ;Del string
IPMASK          DIM             17         ;IP MASK string    (nnn.nnn.nnn.nnn)
COMMENT         DIM             40         ;Comment string
OUTPUT          DIM             250         ;OUTPUT file name
CMDFILE         DIM             250         ;Command file name
DEVICE          DIM             250         ;Output device
.
                RECORDEND
.
KEY             RECORD
ACCESS          DIM             32         ;Access KEY
KEYSEED         DIM             16         ;KEY Seed string
MASK            DIM             16         ;KEY Mask string
USER            DIM             32         ;User encrypted string
IPOK_Left       DIM             32         ;IP Allowed     Left encrypted strin
IPOK_Right      DIM             32         ;IP Allowed     Right encrypted stri
IPNOTOK_Left    DIM             32         ;IP Not Allowed Left  encrypted st
IPNOTOK_Right   DIM             32         ;IP Not Allowed Right encrypted stri
                RECORDEND
.
USERCMD         DIM             250
RESULT          FORM            5
ERRDATA         DIM             ^500
ERRPTR          FORM            3
.
EDITDATA        DIM             ^500
.
BLANK16         INIT            "      "
.
FORMADM         PLFORM          ADMSAMP3.PLF
.
NL              INIT            0x7F
*==============================================================================
.
START
.
		WINHIDE
                FORMLOAD        FORMADM
.
                LOOP
                EVENTWAIT
                REPEAT
.
GetKeys
.
                CLEAR           OPT
.
                GETITEM         AccessKey,0,OPT.KEY
                TYPE            OPT.KEY
                IF              NOT EOS
                PACK            OPT.KEY,OPT.KEY,BLANK16
                ENDIF
.
                GETITEM         User_Id,0,OPT.ADD
.
                GETITEM         Ip_Mask,0,OPT.IPMASK
.
                GETITEM         PublicKey,0,OPT.PUBLIC
.
.
                CALLS           "SUNADMIN;SUNADMIN_KEY" USING OPT:
                                KEY:
                                RESULT:
                                ERRDATA
                IF              ( RESULT = 0 )
.
                PACK            EDITDATA, "KEY.ACCESS........:",KEY.ACCESS,NL:
                                NL:
                                "KEY.KEYSEED.......:",KEY.KEYSEED,NL:
                                NL:
                                "KEY.MASK..........:",KEY.MASK,NL:
                                NL:
                                "KEY.USER..........:",KEY.USER,NL:
                                NL:
                                "KEY.IPOK_Left.....:",KEY.IPOK_LEFT,NL:
                                NL:
                                "KEY.IPOK_Right....:",KEY.IPOK_Right,NL:
                                NL:
                                "KEY.IPNOTOK_Left..:",KEY.IPNOTOK_LEFT,NL:
                                NL:
                                "KEY.IPNOTOK_Right.:",KEY.IPNOTOK_RIGHT
                SETITEM         EDITOUT,0,EDITDATA
.
                ELSE
.
                PACK            EDITDATA,"ERROR RESULT:",RESULT
                TYPE            ERRDATA
                IF              NOT EOS
                PACK            EDITDATA,EDITDATA,NL:
                                NL:
                                "ERROR DATA :",ERRDATA
                ENDIF
                SETITEM         EDITOUT,0,EDITDATA
                ENDIF
                RETURN
.
