$Id: README.txt,v 1.1.4.3 2007/01/18 07:14:35 heine Exp $

Description
===========
Comment upload allows users to attach files to individual comments.


Dependencies
============
Comment upload depends on the following core modules:

* Upload
* Comment


Installation & Configuration
============================
1. Copy the folder in the archive to your module folder (e.g. sites/all/modules).
2. Enable comment upload on Administer >> Site building >> Modules (admin/build/modules).
3. Configure the module
   * Enable "Attachments on comments" by editing content types on
     Administer >> Content management >> Content types (admin/content/types).
   * Choose on Administer >> Site configuration >> File uploads (admin/settings/uploads)
     whether to have single or multiple uploads per comment.
     You can choose whether to display images inline by selecting "Inline display"
     for the "Images on comments" setting.

All other settings are inherited from the Upload module.

Support
=======
If you require support, file a support request or post on the Drupal.org forum.

* Support request - <http://drupal.org/node/add/project-issue/comment_upload/support>.
* Drupal.org forum - <http://drupal.org/forum>.

Please search for answers before doing so however.

Bug reports & Feature requests
==============================
Please submit bug reports and feature requests to the issue tracker:

* Bug reports - <http://drupal.org/node/add/project-issue/comment_upload/bug>.
* Feature requests - <http://drupal.org/node/add/project-issue/comment_upload/feature>.

Please search for existing issues on <http://drupal.org/project/issues/37197>.

Current maintainer
==================
Heine Deelstra <http://drupal.org/user/17943>.

This started as chx's proof-of-concept project to demonstrate the new hooks in
Drupal 4.7's comment.module. Then Eaton got his hands on it and started hacking with it.

It's still very early in the development cycle, and will continue to grow.
