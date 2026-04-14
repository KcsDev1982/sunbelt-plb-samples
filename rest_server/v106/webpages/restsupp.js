// JavaScript Document

var commAddr = "http://127.0.0.1:8081/MyServices/phonemsg";


function doRestDel( msgId ) {
	var self = this;

	self.xmlHttpReq = new XMLHttpRequest();

	self.xmlHttpReq.open('DELETE', commAddr + "/" + msgId, true);

	self.xmlHttpReq.onreadystatechange = function () {
		if (self.xmlHttpReq.readyState == 4) {
			if ((self.xmlHttpReq.status > 0) && (self.xmlHttpReq.status < 300)) {
			doRestGet();
			}
		}
	}

	self.xmlHttpReq.send();
}

function processPostResult( ) {
	var elTo = document.getElementById('tofield');
	var elFrom = document.getElementById('fromfield');
	var elTel = document.getElementById('tel');
	var elMsg = document.getElementById('msgdata');
	
	elTo.value = "";
	elFrom.value = "";
	elTel.value = "";
	elMsg.value = "";
	
	elTo.focus();
}

function doRestPost(sendData) {
			var self = this;

			self.xmlHttpReq = new XMLHttpRequest();

			self.xmlHttpReq.open('POST', commAddr, true);

			self.xmlHttpReq.setRequestHeader('Content-Type', 'application/json');

			self.xmlHttpReq.onreadystatechange = function () {
				if (self.xmlHttpReq.readyState == 4) {
					if ((self.xmlHttpReq.status > 0) && (self.xmlHttpReq.status < 300)) {
						processPostResult();
					}
				}
			}

			self.xmlHttpReq.send( JSON.stringify(sendData) );
}


function makeTable( respData ) {
	var newHtml;
	var el = document.getElementById('MsgTable');
	var rMsgs;
 	var msgCount = 1;
	var rMsg;

		try {
			rMsg = JSON.parse(respData);
		}

		catch (exception) {
			return;
		}

		if (rMsg.messages != undefined) {
			if (Array.isArray(rMsg.messages)) {
				rMsgs = rMsg.messages;
				msgCount = rMsgs.length;
			}
		}

		newHtml = '<tr>' + '<th>Identifier</th>' +
								'<th>To</th>' +
								'<th>From</th>' +
								'<th>Phone Number</th>' +
								'<th>Message</th>' +
								'<th>Action</th>' 
							'</tr>';
		while (msgCount--) {
			if (rMsgs != undefined) {
				rMsg = rMsgs.shift();
			}
				newHtml += '<tr>' + '<td>' + rMsg.Message.id + '</td>' +
								'<td>' + rMsg.Message.to + '</td>' +
								'<td>' + rMsg.Message.from + '</td>' +
								'<td>' + rMsg.Message.phoneNumber + '</td>' +
								'<td>' + rMsg.Message.message + '</td>' +
								'<td><button onClick="MM_callJS(\'doRestDel(' + 
								rMsg.Message.id + ');\')">Delete</button></td>'
							'</tr>';
		}
	
		el.innerHTML = newHtml;
	
}

function doRestGet() {
			var self = this;
			var elSrch = document.getElementById('searchto');
			var newAddr;
			
			if( ( elSrch != null ) && (elSrch.value.length > 0 ) ) {
				newAddr = commAddr + "/search/" + elSrch.value;
			}
			else {
				newAddr = commAddr;
			}

			self.xmlHttpReq = new XMLHttpRequest();

			self.xmlHttpReq.open('GET', newAddr, true);

			self.xmlHttpReq.onreadystatechange = function () {
				if (self.xmlHttpReq.readyState == 4) {
					if ((self.xmlHttpReq.status > 0) && (self.xmlHttpReq.status < 300)) {
						makeTable(self.xmlHttpReq.responseText);
					}
				}
			}

			self.xmlHttpReq.send();
}

function createMessage() {
	var postObj;
	var elTo = document.getElementById('tofield');
	var elFrom = document.getElementById('fromfield');
	var elTel = document.getElementById('tel');
	var elMsg = document.getElementById('msgdata');
	
		postObj = new Object();
		
		postObj.to = elTo.value;
		postObj.from = elFrom.value;
		postObj.phoneNumber = elTel.value;
		postObj.message = elMsg.value;
		
		doRestPost(postObj)
}
