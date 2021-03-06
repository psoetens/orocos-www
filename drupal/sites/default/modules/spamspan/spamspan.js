/*
	--------------------------------------------------------------------------
	(c) 2007 Lawrence Akka
	 - jquery version of the spamspan code (c) 2006 SpamSpan (www.spamspan.com)

	This program is distributed under the terms of the GNU General Public
	Licence version 2, available at http://www.gnu.org/licenses/gpl.txt
	--------------------------------------------------------------------------
*/

/*  
	IF YOU MAKE ANY CHANGES HERE COMPRESS THIS SOURCE CODE USING
   	http://alex.dojotoolkit.org/shrinksafe/ TO MAKE spamspan.compressed.js
*/


// load SpamSpan
if (Drupal.jsEnabled) {
   $(function () {
// get each span with class spamSpanMainClass
       $("span." + Drupal.settings.spamspan.m).each(function (index) {
// for each such span, set mail to the relevant value, removing spaces	
	    var _mail = ($("span." + Drupal.settings.spamspan.u, this).text() + 
	    	"@" + 
	    	$("span." + Drupal.settings.spamspan.d, this).text())
	    	.replace(/\s+/g, '')
	    	.replace(/\[dot\]/g, '.');		
	    var _anchorText = $("span." +  Drupal.settings.spamspan.t, this).text();
// create the <a> element, and replace the original span contents
   	    $(this).after(
		$("<a></a>")
		.attr("href", "mailto:" + _mail)
		.html(_anchorText ? _anchorText : _mail)
		.addClass("spamspan")
		).remove();
	} );
	} )
}
