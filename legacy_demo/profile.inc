*..............................................................................
.
.Example File: PROFILE.INC
.
.This file provides sample PROFILE definitions for use with WINAPI 
. instructions.
.
.Copyright @ 1997, Sunbelt Computer Systems, Inc.
.All Rights Reserved.
*..............................................................................
.
. PROFILE declarations define the parameter criteria needed to use an
. API function.	 The compiler uses the PROFILE definition to verify the
. syntax of a WINAPI statement.	 The PROFILE definitions also control the
. WINAPI statement setup to execute and	return values for an API function.
.
.   Format:
.
.<Label>   PROFILE	DllName,EntryName,TypeRet[,TypeParm1[,TypeParm2...]]
.
.   Where:   DllName	- Defines the DLL name which contains the API to be
.			  used for a statement using this profile.
.
.	     EntryName	- Defines the actual API system	call name to be	used.
.
.			  If the function is a UNICODE enabled function, then
.			  the name must	have a character 'A' (ASCII) or	'W'
.			  (WIDE) appended to it.  A UNICODE enabled function
.			  can be determined when a parameter of	the API
.			  function is string variable.	The 'A'	character
.			  indicates that the string parameters contain ASCII
.			  zero terminated data.	 The 'W' indicates that	the
.			  string parameters contain UNICODE string data.
.
.	     TypeRet	- This defines the data	type of	the variable which will
.			  receive the result of	the API	call.  This field can
.			  be any of the	keywords defined in the	following type
.			  indicators.
.
.	     INT1	- Defines an INTEGER 1 type.
.	     INT2	- Defines an INTEGER 2 type.
.	     INT4	- Defines an INTEGER 4 type.
.	     DIM	- Defines a string data	type.
.	     PINT1	- Defines an INTEGER 1 pointer type.
.	     PINT2	- Defines an INTEGER 2 pointer type.
.	     PINT4	- Defines an INTEGER 4 pointer type.
.	     NONE	- Defines nothing returned. This is only valid for the
.			  return value operand.
.
.	     TypeParm1	- This defines the data	type of	the first parameter
.			  used for an API call.
.
.	     TypeParm2	- This defines the data	type of	the second parameter
.			  used for an API call.
.
*.............................................................................
.
.Get Version
.
. The PROFILE labeled 'GetVer' defines the parameters needed to	execute
. the Window's API function 'GetVersion'.  The function	returns	a hex value
. whose	high and low order bytes define	release	and version of Windows being
. executed.  There are three parameters	defined	as follows:
.
.	 1. kernel32	 -  This defines a basic Window's DLL module to	use.
.
.	 2. GetVersion	 -  This defines the API function name to be executed
.			    by a WINAPI	statement when using this PROFILE.
.
.	 3. INT2	 -  The	third operand defines the type of variable
.			    to be used for a RETURN value.  In this case we
.			    are	only requesting	a 16 bit value be returned.
.
GetVer	 PROFILE   kernel32, GetVersion, INT2
*.............................................................................
.
.Get Drive Type
.
. The PROFILE labeled 'GetDrv' defines the parameters needed to	execute
. the Window's API function 'GetDriveType'.  The function returns a value
. which	identifies the type of drive being used.  There	are four parameters
. defined as follows:
.
.	 1. kernel32	  - This defines a basic Window's DLL module to	use.
.
.	 2. GetDriveTypeA - This defines the API function name to be executed
.			    by a WINAPI	statement when using this PROFILE.
.			    You	will note that the character 'A' has been
.			    appended to	the function name.  This is required
.			    by Windows to identify the format of string	data
.			    used in the	parameter list.	 In this case, the
.			    DIM	parameter in the parameter list	contains
.			    an ASCII string terminated with a binary zero.
.
.	 3. INT4	  - The	third operand defines the type of variable
.			    to be used for a RETURN value.  In this case we
.	       		    are	only requesting	a 32 bit value be returned.
.
.			       0 - Function cannot determine drive type.
.			       1 - Specified drive does	not exist.
.			       2 - Drive removeable.
.			       3 - Drive fixed.
.			       4 - Drive remote	(network).
.
.	 4. DIM		  - The	fourth operand defines the type	of variable
.			    to be used for the first variable in the parameter
.			    list.  In this case	the variable is	a DIM type.
.			    Note that the 'A' at the end of the	function name
.			    indicates that this	variable should	contain	an
.			    ASCII string terminated with a binary zero.
.
GetDrv	 PROFILE   kernel32, GetDriveTypeA, INT4, DIM
*.............................................................................
.
.Get Windows Directory
.
. The PROFILE labeled 'GetName'	defines	the parameters needed to execute
. the Window's API function 'GetWindowsDirectory'.  The	function returns a
. value	which indicates	if the function	work or	not.  In addition, the name
. of the Windows directory is placed into the DIM variable found in the
. parameter list.  There are four parameters defined as	follows:
.
.	 1. kernel32	  - This defines a basic Window's DLL module to	use.
.
.	 2. GetWindowsDirectoryA
.			  - This defines the API function name to be executed
.			    by a WINAPI	statement when using this PROFILE.
.			    You	will note that the character 'A' has been
.			    appended to	the function name.  This is required
.			    by Windows to identify the format of string	data
.			    used in the	parameter list.	 In this case, the
.			    DIM	parameter in the parameter list	will have
.			    an ASCII string terminated with a binary zero
.			    placed into	it by the API function.
.
.	 3. INT4	  - The	third operand defines the type of variable
.			    to be used for a RETURN value.  In this case we
.			    are	only requesting	a 32 bit value be returned.
.
.			       0 - Function failed.
.			      nn - The return value is the length of the
.				   string placed into the DIM variable not
.				   including the NULL character	which was
.				   also	stored.
.
.	 4. DIM		  - The	fourth operand defines the type	of variable
.			    to be used for the first variable in the parameter
.			    list.  In this case	the API	function will store
.			    the	name of	the Windows directory with a NULL
.			    character as the terminator.
.
.	 5. PINT4	  - The	fifth operand defines the type of variable
.			    to be used for the second variable in the API
.			    function parameter list.  In this case the PINT4
.			    indicates that the function	call expects a pointer
.			    to the actual value	is to be passed	to the API
.			    function.  For this	function, the value of this
.			    variables defines how big the output buffer	is.
.
GetName	 PROFILE   kernel32, GetWindowsDirectoryA, INT4, DIM, PINT4
*............................................................................
.
.Get Private Profile String
.
. In this case the 'GetPPStr' PROFILE defines a	function which will allow
. the KEYWORD string data from a '.INI'	file to	be retrieved.  The parameters
. are defined as follows.
.
GetPPStr PROFILE   kernel32:		     ;DLL name
		   GetPrivateProfileStringA:  ;API name
		   INT2:		     ;16 bit return value
		   DIM:			     ;Application name in init.	file
		   DIM:			     ;Keyword name
		   DIM:			     ;Default if not found
		   DIM:			     ;Return buffer
		   INT2:		     ;Maximum return buffer size
		   DIM			     ;Name of initialization file
*.............................................................................
.
.Get Cursor Position
.
. The 'GetCurse' PROFILE defines a function which allows the current absolute
. mouse	cursor coordinates to be retrieved.  This function has a single
. parameter used which is a Windows structure named POINT.  The	structure
. POINT	contains two members which define the x	and y coordinates of the
. mouse	cursor.	 There this PROFILE defines that the function parameter	is
. a DIM	which causes the user dim variable address to be passed	to the
. 'GetCursorPos'.  When	this function is completed, the	user dim variable
. will contain the POINT structure member data.	 This is a sample of how
. a structure can be used with WINAPI functions.
.
GetCurse PROFILE   user32:	       ;DLL name
		   GetCursorPos:       ;API name
		   INT4:	       ;32 bit return value
		   DIM		       ;DIM value to be	used for structure
				       ; member	data.  After a call to this
				       ; function a user can unpack the
				       ; DIM data into 2 integer variables
				       ; to get	the coordinates	of mouse.
*.............................................................................
.
.Find First File
.
. The 'FindFirstFile' function finds the first occurance of a file specified
. by the Filename parameter.  The file properities are placed into the
. second parameter which is a FileData Structure.
.
FindFirst PROFILE  kernel32:	       ;DLL name
		   FindFirstFileA:     ;API name ( ASCIIZ string format	)
		   INT4:	       ;File Handle return value
		   DIM:		       ;Search File Name ( ASCIIZ required )
		   DIM		       ;FileData structure
*.............................................................................
.
.Find Next File
.
. The 'FindNextFile' function finds the	next occurance of a file after a
. 'FindFirstFile' has succeeded.  The return value will	be non-zero when
. 'FindNextFile' locates another file.	The return value will be zero
. when no more files are found.	 When a	file is	found, the second parameter
. will contain the FileData structure information for the file found.
. The first parameter of the function is the File Handle value returned	
. from a successful 'FindFirstFile' operation.
.
FindNext   PROFILE	   kernel32, FindNextFileA, INT1, INT4,	DIM
*..............................................................................
.
.Find Close
.
. The 'FindClose' function closes the File Handle returned from	a 
. successful 'FindFirstFile' function.
.
FindClose  PROFILE	   kernel32, FindClose,	INT1, INT4
