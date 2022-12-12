//==============================================================================
var theEntry;
var theEntries;
var theFileSystem;
//Some HTML tag constants to use to create HTML output
var br = '<br />';
var hr = '<hr />';
var startP = '<p>';
var endP = '</p>';

//Dialog constants
var alertTitle = "Note:";
var alertBtn = "Continue";
var plboffline;

function programStart() {
/*
  The 'plbappstart.html' returns to the 'plbwebcli' App.
*/
	$("#hello").on("click", function() { location.replace("plbappstart.html");});
/*
  The 'plbappload.html' attempts to reconnect to the PWS server.
*/
	$("#reload").on("click", function() { location.replace("plbappload.html");});

	//navigator.notification.alert("ProgramStart has started.", null, alertTitle, alertBtn);
/*
  Start the web page in 'sunhello.html' with the 'id="main"'.
*/
	$("#desktop").pagecontainer("change", "#main", { transition: "flip" });
}
