To use the PEAR Wiki filter module, you need some PEAR packages:

Text_Wiki: http://pear.php.net/package/Text_Wiki/

and depending on which input format to use the additional packages:

Text_Wiki_Mediawiki: http://pear.php.net/package/Text_Wiki_Mediawiki/
Text_Wiki_Doku: http://pear.php.net/package/Text_Wiki_Doku/
Text_Wiki_Tiki: http://pear.php.net/package/Text_Wiki_Tiki/
Text_Wiki_Creole: http://pear.php.net/package/Text_Wiki_Creole/
Text_Wiki_BBCode: http://pear.php.net/package/Text_Wiki_BBCode/

Use the following command to get the CVS Version of all the required PEAR packages 
(which I would recommend at least for the Mediawiki parser):

cvs -d :pserver:cvsread@cvs.php.net:/repository checkout -d Text pear/Text_Wiki/Text

Then move the directory 'Text' into the 'pearwiki_filter' directory.
You can also place it somewhere else and specify the path to the PEAR packages later.

Then you should create a new input format and select the 'PEAR Wiki Filter'. On the
input format configuration page, set the path to the PEAR installation and select the
desired format to use.
