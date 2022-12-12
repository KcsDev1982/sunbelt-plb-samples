//===============================================
var theEntry;
var theEntries;
var theEntrySub;	/*Single entry from a sub-directory!*/
var theEntriesSub;	/*Allow 1 sub-directory level to be evaluated!*/
var theEntrySubDeleted;
var theFileSystem;

//Some HTML tag constants to use to create HTML output
var br = '<br />';
var hr = '<hr />';
var startP = '<p>';
var endP = '</p>';

//Dialog constants
var alertTitleDir = "Directory"
var alertTitle = "File";
var alertBtn = "Continue";
var plboffline;

/*********************************************
  This function is the entry point for the 'PlbWebCli' App.
*/

function programStart() {
	
	$("#btem").on("click", function() {processDir(LocalFileSystem.TEMPORARY);} );
	$("#bper").on("click", function() {processDir(LocalFileSystem.PERSISTENT);} );
	$("#bfil").on("click", function() {writeSampleFile();});
	$("#bonl").on("click", function() { location.replace("plbappload.html");});

	$("#bflvsub").on("click", function() {viewFileSub();});
	$("#bflrsub").on("click", function() {removeFileSub();});

	$("#bdlv").on("click", function() {viewDirectory();});
	$("#bflv").on("click", function() {viewFile();});
	$("#bflr").on("click", function() {removeFile();});
	$("#bwrt").on("click", function() {writeFile();});
	$("#desktop").pagecontainer("change", "#main", { transition: "flip" });
}	

/*********************************************
*/

function processDir(fileSystemType) {
  //Get a handle to the local file system (allocate 5 Mb for storage)
  window.requestFileSystem(fileSystemType, (5 * 1024 * 1024), getFileSystemSuccess, onFileError);
}

/*********************************************
*/

function getFileSystemSuccess(fs) {
  //Save the file system object so we can access it later

  theFileSystem = fs;
  //Kick off a refresh of the file list
  refreshFileList();
  //Switch the directory entries page as the file list is built
  $.mobile.changePage("#dirList", {
    transition : "slide"
  }, false, true);
}

/*********************************************
*/

function refreshFileList() {
  var dr = theFileSystem.root.createReader();
  
  dr.readEntries(dirReaderSuccess, onFileError);	// Get a list of all the entries in the directory

  //navigator.notification.alert("refreshFileList:", null, alertTitle, alertBtn);	//Debug
}

/*********************************************
*/

function refreshFileListSub() {
  var dr = theFileSystem.root.createReader();
  
  dr.readEntries(dirReaderSuccessSub, onFileError);	// Get a list of all the entries in the directory

  //navigator.notification.alert("refreshFileListSub:", null, alertTitle, alertBtn);	//Debug
}

/*********************************************
*/

function dirReaderSuccess(dirEntries) {
  var i, j, fl, len;

  $('#dirEntryList').empty();	//Whack the previous dir entries

  theEntries = dirEntries;	//Save the entries to the global variable I created.

  len = dirEntries.length;	//Do we have any entries to process?
  if (len > 0) {

    fl = '';	//Empty out the file list variable
    for ( i = 0; i < len; i++) {
      if (dirEntries[i].isDirectory) {
        fl += '<li><a href="#" id="dentl' + i + '">Directory: ' + dirEntries[i].name + '</a></li>';
      } else {
        fl += '<li><a href="#" id="dentl' + i + '">File: ' + dirEntries[i].name + '</a></li>';
      }
    }
  } else {
    fl = "<li>No entries found</li>";
  }

  //navigator.notification.alert("dirReaderSuccess Exit:", null, alertTitle, alertBtn);

  //Update the page content with our directory list
  $('#dirEntryList').html(fl);
  $('#dirEntryList').listview('refresh');
  
  if (len > 0) {
  
	for ( i = 0; i < len; i++) {
		$("#dentl"+i).on("click", processEntry);
	}
  }
  

}

/*********************************************
*/

function dirReaderSuccessSub(dirEntriesSub) {
  var i, j, fl, len;

	$('#dirEntryListSub').empty();	//Whack the previous dir entries
	theEntriesSub = dirEntriesSub;	//Save the entries to the global variable I created.

	len = dirEntriesSub.length;	//Do we have any entries to process?
	if (len > 0) {

	fl = '';			//Empty out the file list variable
	for ( i = 0; i < len; i++) {
	    if (dirEntriesSub[i].isDirectory) {
	      fl += '<li><a href="#" id="dent2' + i + '">Directory: ' + dirEntriesSub[i].name + '</a></li>';
	    } else {
	      fl += '<li><a href="#" id="dent2' + i + '">File: ' + dirEntriesSub[i].name + '</a></li>';
	    }
	}

	//navigator.notification.alert("dirReaderSuccessSub:" + dirEntriesSub[0].name, null, alertTitle, alertBtn);	//Debug

	} else {
	  fl = "<li>No entries found</li>";
	}

	//Update the page content with our directory list
	$('#dirEntryListSub').html(fl);
	$('#dirEntryListSub').listview('refresh');

	if (len > 0) {

	  //navigator.notification.alert("dirReaderSuccessSub(1): " + len, null, alertTitle, alertBtn);	//Debug

	  for ( i = 0; i < len; i++) {
		$("#dent2"+i).on("click", processEntrySub);
	  }
	}
}

/*********************************************
  This function is to process a directory entry.
*/

function processEntry(e) {

   var entryIndex = parseInt(e.target.id.slice(5));

  theEntry = theEntries[entryIndex];	//Get access to the inidividual file entry

  var fi = "";				//FileInfo variable

  fi += startP + '<strong>Name</strong>: ' + theEntry.name + endP;
  fi += startP + '<strong>Full Path</strong>: ' + theEntry.fullPath + endP;
  fi += startP + '<strong>URI</strong>: ' + theEntry.toURI() + endP;

  if (theEntry.isFile) {
    fi += startP + 'The entry is a file' + endP;
  } else {
    fi += startP + 'The entry is a directory' + endP;
  }

  $('#fileInfo').html(fi);	//Update the page content with information about the file

  //Display the directory entries page
  $.mobile.changePage("#fileDetails", {
    transition : "slide"
  }, false, true);

  //Show or hide the View File button based on whether it's a 
  //directory entry or file entry
  if (theEntry.isFile) {

    $('#viewDirButton').hide();		//Hide the directory button.
    $('#viewFileButton').show();	//Show the results page View File button (since this is a file and we can open it)
    $('#viewRemoveButton').show();	//Show the Remove File button

  } else {

    $('#viewFileButton').hide();	//Hide the results page View File button (since we're working with a directory)
    $('#viewDirButton').show();		//Show the directory button.
    $('#viewRemoveButton').hide();	//Hide the Remove File button.

  }

  theEntry.getMetadata(getMetadataSuccess, onFileError);	//Now go off and see if you can get meta data about the file

}

/*********************************************
  This function is to process a directory entry.
*/

function processEntrySub(e) {

	//navigator.notification.alert("processEntrySub(0): ", null, alertTitle, alertBtn);	//Debug

	var entryIndex = parseInt(e.target.id.slice(5));

	//navigator.notification.alert("processEntrySub(1): ", null, alertTitle, alertBtn);	//Debug

	theEntrySub = theEntriesSub[entryIndex];	//Get access to the inidividual file entry

	var fi = "";				//FileInfo variable

	fi += startP + '<strong>Name</strong>: ' + theEntrySub.name + endP;
	fi += startP + '<strong>Full Path</strong>: ' + theEntrySub.fullPath + endP;
	fi += startP + '<strong>URI</strong>: ' + theEntrySub.toURI() + endP;

	if (theEntrySub.isFile) {
	  fi += startP + 'The entry is a file' + endP;
	} else {
	  fi += startP + 'The entry is a directory' + endP;
	}

	//navigator.notification.alert("processEntrySub(2): ", null, alertTitle, alertBtn);	//Debug

	$('#fileInfoSub').html(fi);	//Update the page content with information about the file

	//Display the directory entries page
	$.mobile.changePage("#fileDetailsSub", {
	  transition : "slide"
	}, false, true);

	//Show or hide the View File button based on whether it's a 
	//directory entry or file entry
	if (theEntrySub.isFile) {

	  $('#viewFileButtonSub').show();	//Show the results page View File button (since this is a file and we can open it)
	  $('#viewRemoveButtonSub').show();	//Show the Remove File button

	} else {
/*
  The 'sunviewfile' demo DOES NOT support multiple sub-directory levels.
*/
	  $('#viewFileButtonSub').hide();	//Hide the results page View File button (since we're working with a directory)
	  $('#viewRemoveButtonSub').hide();	//Hide the Remove File button.

	}

	theEntrySub.getMetadata(getMetadataSuccessSub, onFileError);	//Now go off and see if you can get meta data about the file
}

/*********************************************
  This function retrieves the directory entry metadata.
*/

function getMetadataSuccess(metadata) {
  var md = '';

  for (var aKey in metadata) {
    md += '<b>' + aKey + '</b>: ' + metadata[aKey] + br;
  }

  md += hr;

  $('#fileMetadata').html(md);	//Update the page content with information about the file
}


/*********************************************
  This function retrieves the sub-directory entry metadata.
*/

function getMetadataSuccessSub(metadata) {
  var md = '';

	for (var aKey in metadata) {
	  md += '<b>' + aKey + '</b>: ' + metadata[aKey] + br;
	}

	md += hr;

	$('#fileMetadataSub').html(md);	//Update the page content with information about the file
}

/*********************************************
*/

function writeSampleFile() {
	window.requestFileSystem(LocalFileSystem.PERSISTENT, (5 * 1024 * 1024), getSampleSysSuccess, onFileError);
}

/*********************************************
*/

function getSampleSysSuccess(fs) {
  
    //Get a file name for the file
    var theFileName = 'sampleData.txt';

    var theFileOptions = {
      create : true,
      exclusive : false
    };
    fs.root.getFile(theFileName, theFileOptions, getSampleFileSuccess, onFileError);
  
}

/***********************************************************
*/

function getSampleFileSuccess(theEntry) {
  //Let the user know we have created a file
  navigator.notification.alert("File entry created.", null, alertTitle, alertBtn);
  
  //Now create the file writer to write to the file
  theEntry.createWriter(createSampleWriterSuccess, onFileError);

}

/***********************************************************
*/

function createSampleWriterSuccess(writer) {

	var sampData = { name: "Charles", extension: "431", email: "k@v.ca" };
	
  writer.write(JSON.stringify(sampData));

}

/***********************************************************
*/

function writeFile() {
  if (theFileSystem) {
    //Get a file name for the file
    var theFileName = createRandomString(8) + '.txt';

    var theFileOptions = {
      create : true,
      exclusive : false
    };
    theFileSystem.root.getFile(theFileName, theFileOptions, getFileSuccess, onFileError);
  } 
}

/***********************************************************
*/

function createRandomString(numChars) {
  var chars = "abcdefghijklmnopqrstuvwxyz";
  var tmpStr = "";
  for (var i = 0; i < numChars; i++) {
    var rnum = Math.floor(Math.random() * chars.length);
    tmpStr += chars.substring(rnum, rnum + 1);
  }
  return tmpStr;
}

/***********************************************************
*/

function getFileSuccess(theEntry) {

  navigator.notification.alert("File entry created.", null, alertTitle, alertBtn);  //Let the user know we have created a file

  refreshFileList();	//refresh the file list to display the new file in the list

  theEntry.createWriter(createWriterSuccess, onFileError);	//Now create the file writer to write to the file

}

/***********************************************************
*/

function createWriterSuccess(writer) {
  
	//Write some writer stuff to the log
	writer.onabort = function(e) {
    
  };

/****/
  writer.onwritestart = function(e) {
  };

/****/
  writer.onwrite = function(e) {
  };

/****/
  writer.onwriteend = function(e) {
  };

/****/
  writer.onerror = function(e) {
  };

/****/
  writer.write("This file contains sample data");
}

/***********************************************************
*/

function removeFile() {
  theEntry.remove(removeFileSuccess, onFileError);
}

/***********************************************************
*/

function removeFileSuccess(entry) {

  navigator.notification.alert("File entry removed.", null, alertTitle, alertBtn);//Let the user know the file was removed

  refreshFileList();	//kick off a refresh of the file list

  history.back();	//Close the current page since the file no longer exists
}


/***********************************************************
*/

function removeFileSub() {
	theEntrySubDeletedName = theEntrySub.name;
	theEntrySub.remove(removeFileSuccessSub, onFileError);
}

/***********************************************************
*/

function removeFileSuccessSub(entry) {

	if ( theEntrySubDeletedName == undefined ) {
	  navigator.notification.alert("File entry removed! ", null, alertTitle, alertBtn);//Let the user know the file was removed
	} else {
	  navigator.notification.alert("File entry removed: " + theEntrySubDeletedName, null, alertTitle, alertBtn);//Let the user know the file was removed
	}

	refreshFileListSub();	//kick off a refresh of the file list

	viewDirectory();
}

/***********************************************************
*/

function viewFile() {

  $('#viewFileName').html('<h1>' + theEntry.name + '</h1>');	//Set the file name on the page

  $('#readInfo').html('');					//Clear out any previous load messages

  //Display the directory entries page
  $.mobile.changePage("#viewFile", {
    transition : "slide"
  }, false, true);

  theEntry.file(fileReaderSuccess, onFileError);
}

/***********************************************************
  View the contents of a file found in a sub-directory.
*/

function viewFileSub() {

	$('#viewFileNameSub').html('<h1>' + theEntrySub.name + '</h1>');	//Set the file name on the page

	$('#readInfoSub').html('');						//Clear out any previous load messages

	//Display the directory entries page
	$.mobile.changePage("#viewFileSub", {
	  transition : "slide"
	}, false, true);

	theEntrySub.file(fileReaderSuccessSub, onFileError);
}

/*------------------------------------------------------------
*/

function fileReaderSuccess(file) {

  var reader = new FileReader();

  reader.onloadend = function(e) {
    $('#readInfo').append("Load end" + br);
    $('#fileContents').html(e.target.result);
  };

  reader.onloadstart = function(e) {
    $('#readInfo').append("Load start" + br);
  };

  reader.onloaderror = function(e) {
    $('#readInfo').append("Load error: " + e.target.error.code + br);
  };

  reader.readAsText(file);
}

/*------------------------------------------------------------
*/

function fileReaderSuccessSub(file) {

  var reader = new FileReader();

	reader.onloadend = function(e) {
	  $('#readInfoSub').append("Load end" + br);
	  $('#fileContentsSub').html(e.target.result);
	};

	reader.onloadstart = function(e) {
	  $('#readInfoSub').append("Load start" + br);
	};

	reader.onloaderror = function(e) {
	  $('#readInfoSub').append("Load error: " + e.target.error.code + br);
	};

	reader.readAsText(file);
}

/*------------------------------------------------------------
*/

function onFileError(errObj) {
  
  var msgText = "Unknown error.";
  switch(errObj.code) {
    case FileError.NOT_FOUND_ERR:
      msgText = "File not found error.";
      break;
    case FileError.SECURITY_ERR:
      msgText = "Security error.";
      break;
    case FileError.ABORT_ERR:
      msgText = "Abort error.";
      break;
    case FileError.NOT_READABLE_ERR:
      msgText = "Not readable error.";
      break;
    case FileError.ENCODING_ERR:
      msgText = "Encoding error.";
      break;
    case FileError.NO_MODIFICATION_ALLOWED_ERR:
      msgText = "No modification allowed.";
      break;
    case FileError.INVALID_STATE_ERR:
      msgText = "Invalid state.";
      break;
    case FileError.SYNTAX_ERR:
      msgText = "Syntax error.";
      break;
    case FileError.INVALID_MODIFICATION_ERR:
      msgText = "Invalid modification.";
      break;
    case FileError.QUOTA_EXCEEDED_ERR:
      msgText = "Quota exceeded.";
      break;
    case FileError.TYPE_MISMATCH_ERR:
      msgText = "Type mismatch.";
      break;
    case FileError.PATH_EXISTS_ERR:
      msgText = "Path exists error.";
      break;
  }
  //Now tell the user what happened
  navigator.notification.alert(msgText, null, alertTitle, alertBtn);
}

/***********************************************************
*/
function viewDirectory() {

	//navigator.notification.alert("viewDirectory Start:" + theEntry.name, null, alertTitleDir, alertBtn);	//Debug

	var drx = theEntry.createReader();
	if ( drx == undefined ) {
	     //navigator.notification.alert("drx undefined:" + theEntry.name, null, alertTitleDir, alertBtn);	//Debug
	} else {
		//navigator.notification.alert("drx defined:" + theEntry.name, null, alertTitleDir, alertBtn);	//Debug
		drx.readEntries(dirReaderSuccessSub, onFileError );
	}

	$.mobile.changePage("#dirListSub", {
		 transition : "slide"
	}, false, true);
}

