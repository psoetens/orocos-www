User Mailman Register
------

This is a module for mailman subscribing which extends the Mailman manager module features.
The main feature is that, instead of sending user commands in mail format as Mailman Manager does, it sends url requests to the mailman web interface where admins manage lists members.
In this way, the subscription managment in drupal can be:

    * Completely invisible to the end-user, because the mail processing step is not needed
    * Immediate, because it's an http request.
    * Correctly syncronized with mailman.
    * More customizable, because the user options in the mailman administration page are,or can be, integrated.

Requirements
------------

1. A mailman server ( http://www.gnu.org/software/mailman/index.html ) with the web interface enbled and accessible from your drupal webserver.

2. Mailman Manager module ( http://drupal.org/project/mailman_manager ) must be installed and enabled.

Installation
------------

1. Install the mailman manager form fix at http://drupal.org/node/195437. It's optional but it prevents to show an empty mailman manager tab in the profile of users with mailman manager access denied. 

2. Activate this module as usual.

3. Go to admin/settings/mailman_manager and add your mailman lists.

4. Go to admin/settings/user_mailman_register, choose the general module preferences and activate one or more lists added previuosly. 

 * The mailman list web url for administration, usually something like http://www.mysite.com/cgi-bin/mailman/admin/mylist. 
 * The mailman administrator list password.
 * Default mailman setting applied to new and edit subscriptions. 
 * Your site list interface settings. 

5. Go to admin/user/access and set permissions for your users.

6. Go to user profile to manage the User Mailman Register subscriptions.


Access control
------------------

With user permissions you'll be able to choose the subscription method (Mailman Manager email and/or User Mailman Register http) for a user of your site, and in any moment you can switch between the two methods preserving his subscription status.

The general "access user_mailman_register" permission controls who can subscribe and manage his own subscriptions for allowed lists. The "Visible in user registration form" site configuration option don't need this permission to be on.
 
The "can subscribe to" permission controls what lists, and by who, are allowed to be subscribed.

If you want deny the Mailman Manager method and use only the User Mailman Register method you have simply to uncheck the "access mailman manager" permission of Mailman Manager module.

Just a note: Drupal administrator can always access to mailman manager forms in users profile, but not other users without that permission.

Author and Credits
----------

The User Mailman Register module is developed by Samuele Tognini <samuele@netsons.org>
