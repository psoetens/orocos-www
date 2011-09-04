Description
-----------

This module enables sites to automatically send customized email
notifications on the following events:

 - account activated
 - account blocked
 - account deleted

The first case is especially useful for sites that are configured to
require administrator approval for new account requests.


Database
--------
This module does not require any new database tables to be installed.


Installation
------------
Please see the INSTALL.txt document for details.

NOTE: If you are upgrading from 4.7.x-1.0 or earlier versions, the
placeholders used in the notification email body and subject have
changed to be consistent with those used by the user.module in Drupal
core.  The following changes have been made:
 - %user is now %username
 - %loginuri is now %login_url
 - a number of new placeholders are now available
Please visit the user_status settings page to update your site's
configuration accordingly:

  Administer >> User management >> User status notifications

You should consider using the 'Reset to defaults' button and
customizing again from there as desired.


Bugs/Features/Patches
---------------------
If you want to report bugs, feature requests, or submit a patch,
please file an issue: http://drupal.org/node/add/project_issue/38825


Author
------
Originally written by: Dmitry Arkhipkin ( arkhipkin at gmail.com )
Modified by: David Kent Norman < deekayen [at] deekayen {dot} net >

Major modifications by and current maintainer:
Derek Wright (http://drupal.org/user/46549)


$Id: README.txt,v 1.5.2.1 2008/01/24 05:05:41 dww Exp $
$Name: DRUPAL-5--1-2 $
