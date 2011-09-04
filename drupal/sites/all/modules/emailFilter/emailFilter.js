// $Id: emailFilter.js,v 1.2.2.2 2009/08/31 13:58:41 philipnet Exp $
// Author: Philip Ludlam

if (Drupal.jsEnabled) {
  // Borrowed from:
  // Andy Langton's show/hide/mini-accordion - updated 18/03/2009
  // Latest version @ http://andylangton.co.uk/jquery-show-hide

  // this tells jquery to run the function below once the DOM is ready
  $(document).ready(function() {

    // choose text for the show/hide link - can contain HTML (e.g. an image)
    var showText='- Show quoted text -';
    var hideText='- Hide quoted text -';

    // append show/hide links to the element directly preceding the element with a class of "toggle"
    $('.emailFilterToggle').prev().append(' <a href="#" class="emailFilterToggleLink">'+showText+'</a>');

    // hide all of the elements with a class of 'toggle'
    $('.emailFilterToggle').hide();

    // capture clicks on the toggle links
    $('a.emailFilterToggleLink').click(function() {

    // change the link depending on whether the element is shown or hidden
    $(this).html ($(this).html()==hideText ? showText : hideText);

    // toggle the display - uncomment the next line for a basic "accordion" style
    //$('.emailFilterToggle').hide();$('a.emailFilterToggleLink').html(showText);
    $(this).parent().next('.emailFilterToggle').toggle();

    // return false so any link destination is not followed
    return false;

    });
  });
}
