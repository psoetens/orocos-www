$Id: README.txt,v 1.18 2008/02/10 01:24:19 kbahey Exp $

Copyright 2005-2008 http://2bits.com

Description
-----------
This module provides web site admins the factility to display Google AdSense
ads on their web site, thus earning revenue.

Resources
---------
You can read the module author's collection of articles on resources for
using Google Adsense with Drupal. They contain hints and tips on how to use
the module, as well as Adsense in general.

http://baheyeldin.com/click/476/0

Prerequisites
-------------
You must signup for a Google AdSense account. If you do not have an account, please
consider using the author's referral link for signup at the following URL:

http://baheyeldin.com/click/476/0


Installation
------------
To install, copy the adsense directory and all its contents to your modules
directory.


Configuration
-------------
To enable this module, visit Administer -> Site building -> Modules, and
enable adsense, and one of the other modules in the Adsense group.

To configure it, go to Administer -> Site configuration -> AdSense.

Follow the online instructions on that page on how to display ads and the
various ways to do so.


API
---
The adsense module provides developers with an API that can be used to control
the Adsense Client ID used for the particular page view.

You can decide to select a different Adsense Client ID based on the content
type, the user's role, the level of user points, the taxonomy of content
page, connecting to Google's API, or anything else imaginable.

To do so, your module must implement a hook called 'adsense', as follows:

Assuming your module is called: your_module.module, you will have the
following function in it. The function has an $op argument that you
should check:

function your_module_adsense($op) {
  if ($op == 'settings') {
    // Add here form elements for your module's settings
    // These can also contain markup elements for help text
    // These are standard FormAPI elements.
    return $form;
  }

  if ($op == 'client_id') {
    // Here you can use whatever logic you want to select a Google Adsense
    // client ID
    return $client_id;
  }
}

See the adsense_basic.module for an example of how to write your own module.

After you install the module, it should appear on the adsense module settings
page, along with other modules. You should be able to select it, and configure
it.

Bugs/Features/Patches
---------------------
If you want to report bugs, feature requests, or submit a patch, please do
so at the project page on the Drupal web site.
http://drupal.org/project/adsense


Author
------
Khalid Baheyeldin (http://baheyeldin.com/khalid and http://2bits.com)

If you use this module, find it useful, and want to send the author a thank
you note, then use the Feedback/Contact page at the URL above.

The author can also be contacted for paid customizations of this and other
modules.

