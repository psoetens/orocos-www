/* $Id: README.txt,v 1.1.2.2 2009/07/04 20:18:39 lourenzo Exp $ */

-- SUMMARY --

ImageField Assist is a javascript assistant to add images added as ImageField CCK fields to any textarea/tinyMCE instance. 

For a full description visit the project page:
  http://drupal.org/project/imagefield_assist
Bug reports, feature suggestions and latest developments:
  http://drupal.org/project/issues/imagefield_assist


-- REQUIREMENTS --

* ImageField module <http://drupal.org/project/imagefield>

* ImageCache module <http://drupal.org/project/imagecache>

-- INSTALLATION --

Install as usual. See configuration section for more information.


-- CONFIGURATION --

In order to upload files, enable Content Copy module from CCK bundle, then use the contents of the ifa_upload_content_type.php file in the import form, using the name ifa_upload for the content type.

Add the Inline Images filter to the desired Input Formats for better use of the module.