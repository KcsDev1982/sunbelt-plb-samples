*---------------------------------------------------------------
.
. Program Name: web_calc_class
. Description:  This classmodule will display a sample web calcualtor.
.
. Revision History:
.
.   17 Jul 23   W Keech
.      Original code
.
. This program is created using 'CLASSMODULE'.
. In this case, this program can ONLY be accessed using public
. entry points ( FUNCTIONs ) included in this PL/B program.
.
*
. The 'CLASSMODULE' MUST be the first statement in this program
. logic.
. 
eStandAlone	EQU	0
.
		%IF eStandAlone = 0
		 CLASSMODULE	
		%ENDIF

                INCLUDE         plbequ.inc
                INCLUDE         plbmeth.inc
                INCLUDE         plbstdlib.inc 

*---------------------------------------------------------------
.
. All PL/B variables in this class module are private.
. COMMON variables are NOT ALLOWED in a class module.
. Only public access is through FUNCTIONs.
. CHAIN, TRAP, and Routine are not allowed.
. The class module can not be executed directly.
. LRoutine is allowed.

CalcHtml	INIT		"<html> ":
				"<head> ":
				"<!-- Sample of a calculator --> ":
				"<style> ":
				"##calculator { ":
				"  border: solid; ":
				"  background-color: ##0d6efd; ":
				"  width: 400px; ":
				"  margin-left: auto; ":
				"  margin-right: auto; ":
				"  text-align: center; ":
				"  padding: 10px; ":
				"} ":
				"input.calc { ":
				"  width: 85%; ":
				"  height: 7%; ":
				"  text-align: right; ":
				"  padding: 5px; ":
				"  border: inset; ":
				"} ":
				"button.calc { ":
 				" background-color: ##6ea8fe; ":
 				" width: 90%; ":
 				" height: 10%; ":
				"  border: outset; ":
				"} ":
				"  button.calc:hover { ":
				"  background-color: ##cfe2ff; ":
				"} ":
				"  button.calc:active { ":
				"  border: inset; ":
				"  border-width: thick; ":
				"  border-color: ##FFFFFF; ":
				"} ":
				"input.calc, button.calc { ":
				"  font-family: Arial; ":
				"  font-size: 20pt; ":
				"  border-width: thick; ":
				"  border-color: ##FFFFFF; ":
				"  margin: 5px; ":
				"} ":
				".calc [readonly] { ":
				"  background-color: ##9ec5fe; ":
				"} ":
				"table.calc { ":
				"  width: 100%; ":
				"} ":
				"table.calc td { ":
				"  width: 25%; ":
				"} ":
				"</style> ":
				"</head> ":
				"<body> ":
				"  <div id='calculator'> ":
				"    <table class='calc'> ":
 				"     <tr> ":
 				"       <td colspan='4'> ":
 				"         <input class='calc' id='txtResult' type='text' readonly='readonly' data-plbenable='on' /> ":
				"        </td> ":
				"      </tr> ":
 				"     <tr> ":
 				"       <td colspan='4'> ":
 				"         <input class='calc' id='txtInput' type='text' data-plbenable='on' /> ":
 				"       </td> ":
 				"     </tr> ":
 				"     <tr> ":
 				"       <td></td> ":
 				"       <td></td> ":
				"        <td><button class='calc' id='btnClearEntry' data-plbenable='on'>CE</button></td> ":
 				"       <td><button class='calc' id='btnClear' data-plbenable='on'>C</button></td> ":
 				"     </tr> ":
 				"     <tr> ":
 				"       <td><button class='calc' id='btnNumber7' data-plbenable='on'>7</button></td> ":
   				"     <td><button class='calc' id='btnNumber8' data-plbenable='on'>8</button></td> ":
 				"       <td><button class='calc' id='btnNumber9' data-plbenable='on'>9</button></td> ":
 				"       <td><button class='calc' id='btnPlus' data-plbenable='on'>+</button></td> ":
 				"      </tr> ":
 				"     <tr> ":
				"        <td><button class='calc' id='btnNumber4' data-plbenable='on' >4</button></td> ":
				"        <td><button class='calc' id='btnNumber5' data-plbenable='on' >5</button></td> ":
				"        <td><button class='calc' id='btnNumber6' data-plbenable='on'>6</button></td> ":
				"        <td><button class='calc' id='btnMinus' data-plbenable='on' >-</button></td> ":
 				"     </tr> ":
 				"     <tr> ":
 				"       <td><button class='calc' id='btnNumber1' data-plbenable='on' >1</button></td> ":
 				"       <td><button class='calc' id='btnNumber2' data-plbenable='on' >2</button></td> ":
 				"       <td><button class='calc' id='btnNumber3' data-plbenable='on'>3</button></td> ":
				"        <td><button class='calc' id='btnEqual' data-plbevent='click' data-plbenable='on' >=</button></td> ":
 				"       <td></td> ":
 				"     </tr> ":
 				"     <tr> ":
 				"       <td></td> ":
 				"       <td><button class='calc' id='btnNumber0' data-plbenable='on'>0</button></td> ":
				"        <td></td> ":
				"        <td></td> ":
				"      </tr> ":
				"    </table> ":
				"  </div> ":
				"<script type='text/javascript'> ":
				"var txtInput; ":
				"var txtResult; ":
				"    for (var i = 0; i < 10; i++) { ":
				"        document.getElementById('btnNumber'+i).addEventListener('click', numberClick, false); ":
				"    } ":
				"    txtInput = document.getElementById('txtInput'); ":
				"    txtResult = document.getElementById('txtResult'); ":
				"    document.getElementById('btnPlus').addEventListener('click', plusClick, false); ":
				"    document.getElementById('btnMinus').addEventListener('click', minusClick, false); ":
				"    document.getElementById('btnEqual').addEventListener('click', plusClick, false); ":
				"    document.getElementById('btnClearEntry').addEventListener('click', clearEntry, false); ":
				"    document.getElementById('btnClear').addEventListener('click', clear, false); ":
 				"   clear(); ":
				"function numberClick() { ":
				"    txtInput.value = txtInput.value == '0' ? this.innerText : txtInput.value + this.innerText; ":
				"     txtInput.focus(); ":
				"} ":
				"function plusClick() { ":
				"    txtResult.value = Number(txtResult.value) + Number(txtInput.value); ":
				"    clearEntry(); ":
				"    txtInput.focus(); ":
				"} ":
				"function minusClick() { ":
				"    txtResult.value = Number(txtResult.value) - Number(txtInput.value); ":
				"    clearEntry(); ":
				"    txtInput.focus(); ":
				"} ":
				"function clearEntry() { ":
				"    txtInput.value = '0'; ":
 				"   txtInput.focus(); ":
				"} ":
				"function clear() { ":
				"    txtInput.value = '0'; ":
				"    txtResult.value = '0'; ":
 				"   txtInput.focus(); ":
				"} ":
				"</script> ":
				"</body> ":
				"</html>"

CalcContainer		HTMLCONTROL
JsonMsg         	PLBOBJECT       
JsonData		DIM		200

*................................................................
.
. Class Create
.
ClassCreate	FUNCTION		
		ENTRY
.
. Create the JsonMsg PLBOBJECT to decode the $JQueryEvent event data
.
		CREATE			JsonMsg,CLASS="jsonmsg_class"
		FUNCTIONEND

*................................................................
.
. Class Destroy
.
ClassDestroy	FUNCTION		
		ENTRY
		DESTROY			CalcContainer
		DESTROY			JsonMsg
		FUNCTIONEND

*................................................................
.
. Properties
.
Get_Value	FUNCTION		// Get the value of the calculator result
         	ENTRY
Result		FORM		10
Value		DIM		10
		TEST		CalcContainer
		IF		ZERO
		MOVE		"0" to Result
		ELSE
		CalcContainer.GetAttr Giving Value Using "txtResult","val"
		MOVE		Value to Result
		ENDIF
		FUNCTIONEND	USING Result
.
Set_Value	FUNCTION		// Set the value of the calculator result
Num		FORM		10
         	ENTRY
Value		DIM		10
		TEST		CalcContainer
		IF		NOT ZERO
		MOVE		Num To Value
		CalcContainer.SetAttr Using "txtResult","val",Value
		ENDIF
		FUNCTIONEND

*................................................................
.
. Local event handler
.
CalcEvent	LFUNCTION	// Handle the CalcContainer $JQueryEvent event
		ENTRY
Id		DIM		30
Result		FORM		10
Value		DIM		10

		JsonMsg.ChangeMsg	Using JsonData
		GETPROP			JsonMsg;*id=Id
                IF		(Id == "btnEqual" )
		CalcContainer.GetAttr Giving Value Using "txtResult","val"
		MOVE		Value to Result
.
. Send the event to the associated PLBOBJECT
.
		EVENTSEND	*CLASS,$CHANGE,RESULT=Result
		ENDIF
		FUNCTIONEND
*................................................................
.
. Methods
.
CalcBind	FUNCTION	// Bind the HTML calculator to a provided PANEL object
Container	Panel		^
		ENTRY

		MOVEPTR		Container to Container 
		RETURN		IF OVER
		TEST		Container
		RETURN		IF ZERO
		CREATE		Container;CalcContainer=1:1:1:1,Visible=1,dock=$DOCKFULL
		CalcContainer.InnerHtml Using CalcHtml,$HTML_HAS_EVENTS
		EVENTREG	CalcContainer,$JQueryEvent,CalcEvent,ARG1=JsonData
		FUNCTIONEND
......
*................................................................
.
. Testing
.
		%IF eStandAlone = 1
		CALL		ClassCreate
		%ENDIF
.
 
