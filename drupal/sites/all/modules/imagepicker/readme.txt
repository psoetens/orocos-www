Imagepicker module for Drupal 5.1

If you'll have any questions or suggestions please contact me at
algisimu@gmail.com

This module will help you to upload images and insert them into your nodes in a
very easy way. To set up it follow next 5 steps and you should be done.

	1. Installation
Just copy/paste whole imagepicker directory to Drupal's modules dir.
Login to Drupal site with a user which has an administrative rights and go to
Administer > Site building > Modules. Scroll down to Other modules section, you
should now see Imagepicker module listed there. Tick it and press the button to
save configuration. Imagepicker module will create it's directory structure in
your files directory (configurable via Administer > Site configuration > File
system) and all images will be saved in these directories depending on the name
of user who is uploading images.

NOTE: Once you install Imagepicker module, it is not recomended to change
Drupal's files directory path. But if you do so, please make sure, that you will
copy whole imagepicker directory to the new location as well.

	2. Enabling imagepicker
Only users who have the right to use Full HTML filter will be able to use
imagepicker. This is done because Imagepicker uses some HTML, which will be
stipped out if user will not use this filter. Users, who has the right to use
Full HTML filter will be able to use Imagepicker instantly after installation.
If you want to enable Imagepicker module for other users, you will have to
reconfigure filters.

	3. Configuring filters
Go to Administer > Site configuration > Input formats. You should see a list of
all available filter in your site. Choose Full HTML and click on the configure
link. In the Roles fieldset select all roles you want to be able to use this
filter and save configuration. To see these changes you will need to clear
Drupal's menu cache, otherwise, you will see Access denied page instead of
Imagepicker.

	4. Clearing menu cache
Login to your site's database and truncate cache_menu table. Of course, you can
use Drupal's set of functions to clear it's cache, so it's up to you. One more
simple way to clear menu cache: go to Administer > Site building > Menus, then
select Add menu tab and click on the Submit button without adding any menu item.
This will rebuild Drupal's menu. Strange, huh? But this is Drupal, it uses lots
of functions even if it doesn't need to... Anyway, this method doesn't work all
the time, so the best way to do it is to do it stright in your database.

	5. Using Imagepicker
Login with any user, who has rights to post any type of nodes and can use Full
HTML filters. Go to a node creation page, etc. Create content > Story. Somewhere
under node body you should see expanded Imagepicker module's field. Everything
else is stright forward from this point. Browse for an image file on your local
computer, enter maximum size in pixels of bigger thumbnail side, enter maximum
size in pixels of bigger image side if you want to scale your image or leave it
empty otherwise (this means - do not scale image), enter title and description
for your image and press Upload button. If you have made any mistakes, you will
see error message, or you will be redirected to 'Insert image' page otherwise.
In 'Insert image' page just check options you want and press Insert button. You
also can edit or delete your image here. Try using 'Browse All' tab if you want
to use already uploaded image, find your image and click on it. Images are
sorted by date - latest goes into the front.

NOTE: Image title will be used as image's alternative text and a title for link.
Description will be used only in image's page (imagepicker/image/{image_id})


	Compatibility with browsers
I have tested this module only with Firefox 1.5, Firefox 2.0, IE6.5 and IE7. For
all other browsers - try it yourself, but I think it should work with most of
them.


	Compatibility with tinyMCE
I have tested this module with tinyMCE module (tinyMCE version - 2.0) and it
works fine with Firefox 1.5 and 2.0. Altough it has some problems with IE6 and
IE7. On these browsers you firstly need to select an image, check all options
you want, then click on tinyMCE wysiwyg editor window (focus it) and only then
click on the Insert image button.
After inserting an image into tinyMCE editor (doesn't matter which browser you
are using) your cursor will be before '</a></div>' HTML tags. This might cause
some problems, so be aware of it.
