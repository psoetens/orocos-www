// $Id: tableofcontents.js,v 1.1.2.4 2008/06/21 18:21:16 deviantintegral Exp $

if (Drupal.jsEnabled) {
  $(document).ready( function () {
    $('a.toc-toggle').click(function() {
      $('.toc-list').slideToggle();
	  var text = $('a.toc-toggle').text();
	  if (text == 'hide') {
		  $('a.toc-toggle').html('show');
      } else {
		  $('a.toc-toggle').html('hide');
      }
	  return false;
	});
  });
}