		    LISTOFF
		    %IFNDEF   $DATATYPES_PLBH
*==============================================================================
. WINAPI support Integer Constants and Definitions.
.
. Last Revision	Date:  31 Oct 2001
.
.------------------------------------------------------------------------
. The following	Integer	constants and Definitions have been provided by
. Festus Redelinghuys.	These constants	and definitions	can be used in
. PROFILE definitions and associated WINAPI statements.
.
. Revision History:
.
	 %IFDEF	   $PLBAPI_HISTORY
.:: 31 Oct 01 -	Create PLB WINAPI include definitions.			 :8.3F
	 %ENDIF
.
.------------------------------------------------------------------------
.
$DATATYPES_PLBH	      EQU	1    . This module is now defined
.
.------------------------------------------------------------------------
 
.   Constants
.   =========
FALSE		      Integer	1,"0x00"
INVALID_HANDLE_VALUE  Integer	4,"0xFFFFFFFF"
NULL		      Integer	1,"0x00"
S_FALSE		      Integer	1,"0x01"
S_OK		      Integer	1,"0x00"
TRUE		      Integer	1,"0x01"
GENERIC_ALL	      Integer	4,"0x10000000"
GENERIC_WRITE	      Integer	4,"0x40000000"
GENERIC_READ	      Integer	4,"0x80000000"
FILE_SHARE_READ	      Integer	1,"0x01"
FILE_SHARE_WRITE      Integer	1,"0x02"
OPEN_EXISTING	      Integer	1,"3"
OPEN_ALWAYS	      Integer	1,"4"
FILE_ATTRIBUTE_NORMAL Integer	4,"0x00000080"
.
.   Datatypes -	ANSI
.   ================
.   Note :
.	 Prior to release 8.5F,	a duplicate 'DEFINE' label would cause
.	 the compiler to hang.
.	 Int4  - Pass the integer value	to the WinApi
.	 Pint4 - Pass the address(pointer) of an integer to the	WinApi
.	 Dim   - Pass the address(pointer) of a	string variable	to the WInApi
.	 Pdim  - Pass the address(pointer) of a	string variable	to the
.		 WInApi. The WinApi is responsible for FP and LP.  Only
.		 used by custom	DLL's.
.
ACCESS_MASK	      DEFINE	Int4
BOOL		      DEFINE	Int4
BYTE		      DEFINE	Int4
COLORREF	      DEFINE	Int4
DWORD		      DEFINE	Int4
HANDLE		      DEFINE	Int4
HDC		      DEFINE	Int4
HICON		      DEFINE	Int4
HINSTANCE	      DEFINE	Int4
HKL		      DEFINE	Int4
HMENU		      DEFINE	Int4
HRGN		      DEFINE	Int4
HWND		      DEFINE	Int4
LONG		      DEFINE	Int4
LPBYTE		      DEFINE	Dim   ;	May have to appended 'A' to
				      ;	 Function name
LPCTSTR		      DEFINE	Dim   ;	May have to appended 'A' to
				      ;	 Function name
LPCVOID		      DEFINE	Dim   ;	May have to appended 'A' to
				      ;	 Function name
LPDWORD		      DEFINE	Pint4
LPHANDLE	      DEFINE	Pint4
LPSECURITY_ATTRIBUTES DEFINE	Int4   ; Pass NULL for a pointer
LPTSTR		      DEFINE	Dim    ; May have to appended 'A' to
				       ;  Function name
LPVOID		      DEFINE	Dim    ; This could also be a Pint4
PHANDLE		      DEFINE	Int4   ; Pass the pointer(address)
				       ;  using	an integer
PVOID		      DEFINE	Int4   ; Pass the pointer(address)
				       ; using an integer
UINT		      DEFINE	Int4
ULONG_PTR	      DEFINE	Pint4
INT		      DEFINE	Int4
LPOVERLAPPED	      DEFINE	Int4
.
.   Datatypes -	STRUCTures
.   ========================
.   Pointers to	strings	that represent a structure.
.   The	corresponding RECORD must be 'Unpacked'	before the WinAPi call
.   and	'Pack'd	after the WinApi call.
.
LARGE_INTEGER	      DEFINE	Dim
LPMSG		      DEFINE	Dim
LPRECT		      DEFINE	Dim
POINT		      DEFINE	Dim
SYSTEM_INFO	      DEFINE	Dim
.
.   Datatypes -	UNICODE	WIDE
.   ========================
.   Unicode characters occupy double the space of ANSI characters,
.   including zero termination.
.
LPCWSTR		      DEFINE	Dim
.
		    %ENDIF
		    LISTON
