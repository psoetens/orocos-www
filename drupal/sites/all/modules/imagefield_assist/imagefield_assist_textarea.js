// $Id: imagefield_assist_textarea.js,v 1.1.2.1 2009/10/22 01:48:41 franz Exp $
/**
 * This javascript file allows imagefield_assist to work with a plain textarea.
 * This file is used instead of imagefield_assist_tinymce.js if imagefield_assist is called
 * from the textarea button.
 * Additional JS files similar to imagefield_assist_textarea.js and
 * imagefield_assist_tinymce.js could be created for using imagefield_assist with other
 * WYSIWYG editors. Some minor code changes to the menu function in
 * imagefield_assist.module will be necessary, at least in imagefield_assist_menu() and
 * imagefield_assist_loader().
 *
 * @todo update this
 */

// Declare global variables
var myDoc, myForm, myTextarea, hasInputFormat;

function initLoader() {
  // Save the references to the parent form and textarea to be used later. 
  myDoc      = window.opener.document; // global (so don't use var keyword)
  myForm     = '';
  myTextarea = '';
  hasInputFormat = false;
  
  var args = getArgs(); // get the querystring arguments
  var textarea = args.textarea;
  
  // Reference the form object for this textarea.
  if (myDoc.getElementsByTagName) {
    var f = myDoc.getElementsByTagName('form');
    for (var i=0; i<f.length; i++) {
      // Is this textarea is using an input format?
      if (f[i]['edit-format']) {
        hasInputFormat = true;
      }
      if (f[i][textarea]) {
        myForm = f[i];
        myTextarea = f[i][textarea];
        break;
      }
    }
  }
  frames['imagefield_assist_main'].window.location.href = Drupal.settings.basePath + 'index.php?q=imagefield_assist/thumbs/imagefield_assist_browser';
}

function initProperties() {
  setHeader('properties');
  updateCaption();
  onChangeLink();
  onChangeSizeLabel();
}

function initThumbs() {
  setHeader('browse');
}

function initHeader() {
}

function initUpload() {
  setHeader('uploading');
}

function getFilterTag(formObj) {
  var fid          = formObj['edit-fid'].value;
  var captionTitle = formObj['edit-title'].value;
  var captionDesc  = formObj['edit-desc'].value;
  var link         = formObj['edit-link'].value;
  var url          = formObj['edit-url'].value;
  var align        = formObj['edit-align'].value;
  var width        = formObj['edit-width'].value;
  var height       = formObj['edit-height'].value;
  var preset       = formObj['edit-size-label'].value;
  var lightbox     = formObj['edit-lightbox'].checked;
  
  // Create the image placeholder tag
  var miscAttribs = 'fid=' + fid + '|title=' + captionTitle + '|desc=' + captionDesc + '|link=' + link;
  if (lightbox) {
    miscAttribs += '|lightbox=true';
  }
  if (url != formObj['edit-default-url'].value) {
    miscAttribs += '|url=' + url;
  }
  var content = '[imagefield_assist|' + miscAttribs + '' + '|align=' + align + '|preset=' + preset;
  if (preset=='other'){
    content += '|width=' + width + '|height=' + height;
  }
  content += ']';
  
  return content;
}

function insertToEditor(content) {
  // Insert the image
  
  if (myDoc.selection) {
  	// IE
    myTextarea.focus();
    cursor = myDoc.selection.createRange();
    cursor.text = content;
  }
  else if (myTextarea.selectionStart || myTextarea.selectionStart == "0") {
  	// Gecko-based engines: Mozilla, Camino, Firefox, Netscape
    var startPos  = myTextarea.selectionStart;
    var endPos    = myTextarea.selectionEnd;
    var body      = myTextarea.value;  
    myTextarea.value = body.substring(0, startPos) + content + body.substring(endPos, body.length);
  }
  else {
  	// Worst case scenario: browsers that don't know about cursor position:
  	// Safari, OmniWeb, Konqueror
    myTextarea.value += content;
  }
  
  // Close the dialog
  return cancelAction();
}

function cancelAction() {
  // Close the dialog
  window.close();
  return false;
}

/**
 * getArgs() by Jim K - From Orielly JSB pp 244
 *
 * This function parses comma separated name=value argument pairs from the query
 * string of the URL. It stores the name=value pairs in properties of an object
 * and then returns that object.
 * 
 * @example
 *   var args = getArgs();
 *   alert(args.CSSPATH);
 */
function getArgs() {
  var args = new Object();

  var query = location.search.substring(1); // Get Query String
  var pairs = query.split("&"); // Split query at the ampersand
  
  for(var i = 0; i < pairs.length; i++) { // Begin loop through the querystring
    var pos = pairs[i].indexOf('='); // Look for "name=value"
    if (pos == -1) continue; // if not found, skip to next
    
    var argname = pairs[i].substring(0,pos); // Extract the name
    var value = pairs[i].substring(pos+1); // Extract the value
    args[argname] = unescape(value); // Store as a property
  }
  return args; // Return the Object
}

