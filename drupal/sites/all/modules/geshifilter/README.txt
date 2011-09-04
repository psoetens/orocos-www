****************************
GeSHi Filter (Drupal Module)
****************************


DESCRIPTION
-----------
The GeShi Filter is a Drupal module for syntax highlighting of pieces of
source code. It implements a filter that formats and highlights the syntax of
source code between for example <code>...</code>.


DEPENDENCY
----------
This module requires the third-party library: GeShi (Generic Syntax
Highlighter, written by Nigel McNie) which can be found at
  http://qbnz.com/highlighter
See installation procedure below for more information.


INSTALLATION
------------
1. Extract the GeSHi Filter module tarball and place the entire geshifilter
  directory into your Drupal setup (e.g. in sites/all/modules).

2. Download the GeSHi library (version 1.0.x) from  http://qbnz.com/highlighter
  and place the entire extracted 'geshi' folder (which contains geshi.php)
  in the geshifilter directory (e.g. as /sites/all/modules/geshifilter/geshi)

3. Enable this module as any other Drupal module by navigating to
  administer > site building > modules


CONFIGURATION
-------------
1. The general GeSHi Filter settings and further configuration instructions
  can be found by navigating to:
  administer > site configuration > geshifilter


AUTHORS
-------
Original module by:
  Vincent Filby <vfilby at gmail dot com>

Drupal.org hosted version for Drupal 4.7:
  Vincent Filby <vfilby at gmail dot com>
  Michael Hutchinson (http://compsoc.dur.ac.uk/~mjh/contact)
  Damien Pitard <dpdev00 at gmail dot com>

Port to Drupal 5:
  rötzi (http://drupal.org/user/73064)
  Stefaan Lippens (http://drupal.org/user/41478)
