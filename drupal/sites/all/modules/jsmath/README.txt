; $Id: README.txt,v 1.3 2007/07/15 11:01:27 delius Exp $

This is a simply module that loads the jsMath script on every page which in turn
will render the mathematics that has been entered using the TeX syntax.

The jsMath script has been developed by Davide P. Cervone. 

For more information about jsMath see http://www.math.union.edu/~dpvc/jsMath/welcome.html

"The jsMath package provides a method of including mathematics in HTML pages that 
works across multiple browsers under Windows, Macintosh OS X, Linux and other 
flavors of unix. It overcomes a number of the shortcomings of the traditional 
method of using images to represent mathematics: jsMath uses native fonts, so 
they resize when you change the size of the text in your browser, they print at 
the full resolution of your printer, and you don't have to wait for dozens of 
images to be downloaded in order to see the mathematics in a web page."

For installation instructions see INSTALL.txt

---------------------------------------------------------------------

Future:

Currently this module does not provide filters which can be added to input
formats but instead the jsMath processing applies to all Drupal pages once
the module is enabled. In a future release this will be changed, using the
mechanism for selective processing of parts of a page described by Davide in
the forum post at https://sourceforge.net/forum/message.php?msg_id=4413480

Once the module uses the filter concept it will also be possible to provide
help about the input syntax to users below the input areas. This help will
contain a link to a help page with a dynamic preview area.
