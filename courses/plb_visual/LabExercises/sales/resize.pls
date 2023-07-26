		GOTO		#SKIP
OBJFORM	COLLECTION	^
.
COUNT	INTEGER		4
INDEX 	INTEGER		4
INT		FORM		7(4)
h		INTEGER		4
t		INTEGER		4
w		INTEGER		4
l		INTEGER		4
FSIZE	INTEGER		4
OBJECT1	OBJECT
FONT1	FONT
DIM21	DIM			21
ZOOM	FORM		3
FACTOR	FORM		"  1.0000"
CURRENT	FORM		"10"
SHRINK	INTEGER		1
*............................................................................
.
.Resizing Routine
.
. Call with the form as the first parameter and the zoom percentage 
.  as the second parameter
.
Resize	ROUTINE		OBJFORM,ZOOM
		debug
*
.Compute the zooming factor
.
		COMPARE		CURRENT,ZOOM
		RETURN 		IF EQUAL			// no change
.		
		IF			LESS
		SET			SHRINK
		MOVE		(1 + ((CURRENT - ZOOM) * .1)),FACTOR
		ELSE
		CLEAR		SHRINK
		MOVE		(1 + ((ZOOM - CURRENT) * .1)),FACTOR
		ENDIF
.
		MOVE		ZOOM,CURRENT
*
.Retrieve the number of controls on the form
.
		LISTCNT		Count,OBJFORM
*
.Loop through the controls
.
		FOR			Index From "1" to Count
		LISTGET		Object1,Index,OBJFORM
*
.Does the control have an updatable size?
.		
		CHECKPROP	Object1,"Height",Type=3
		IF			ZERO
		GETPROP		Object1,Height=INT(1),Top=INT(2),Width=INT(3),Left=INT(4)
		IF			(SHRINK)
		DIV			FACTOR,INT
		ELSE
		MULT		FACTOR,INT
		ENDIF
		SETPROP		Object1,Height=INT(1),Top=INT(2),Width=INT(3),Left=INT(4)
		ENDIF
*
.Is this a line object ?
.
		CHECKPROP	Object1,"X1",TYPE=3
		IF			ZERO
		GETPROP		Object1,X1=INT(1),X2=INT(2),Y1=INT(3),Y2=INT(4)
		IF			(SHRINK)
		DIV			FACTOR,INT
		ELSE
		MULT		FACTOR,INT
		ENDIF
		SETPROP		Object1,X1=INT(1),X2=INT(2),Y1=INT(3),Y2=INT(4)
		ENDIF
*
.Resize any Font in the object
.		
		CHECKPROP	Object1,"Font",TYPE=3
		IF			ZERO
		GETPROP		Object1,FONT=FONT1
		GETPROP		Font1,Size=FSIZE
		IF			(SHRINK)
		SETPROP		Font1,Size=(FSIZE / Factor)
		ELSE
		SETPROP		Font1,Size=(FSIZE * Factor)
		ENDIF
		SETPROP		Object1,FONT=FONT1
		DESTROY		FONT1
		ENDIF	
*
.Next object
.		
		REPEAT
*
.All done
.
		Return
#SKIP
