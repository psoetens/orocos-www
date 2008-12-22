<?php
// $Id: adsense_help.inc,v 1.10.2.3 2008/03/31 22:03:53 kbahey Exp $

// Copyright 2005-2008 Khalid Baheyeldin - http://2bits.com

function adsense_help_text() {
  global $user;

  $uid = $user->uid;

  // Get the ad formats
  $headers = array(t('Ad type'), t('Dimensions'));
  $rows = array();
  foreach (adsense_ad_formats() as $format => $data) {
    $rows[] = array($data['desc'], $format);
  }
  // Create the ad format text
  $ad_formats_text = theme('table', $headers, $rows);

  $referral_link = 'http://baheyeldin.com/click/476/1';

  $output = <<<EOF
<H2>Overview</H2>
<P>This module provides web site admins the factility to display Google AdSense ads on their web site,
thus earning revenue.</P>

<H2>Prerequisites</H2>
<P>You must have a Google AdSense account before using this module.  If you do not have an account,
then please consider using <A HREF="$referral_link">the modules author's referral
link</A>, which provides us with a referral fee from Google at absolutely no cost to you. This page
also contains various useful links and resources on AdSense, and how to optimize your site for it.</P>

<H2>Configuration</H2>
<P>To use this module, you need to select one of the Adsense Client ID selection modules first, and configure
it correctly. See below for a list of available modules, and their settings page.</P>

<H2>Supported formats</H2>
<P>Most of Adsense's ad formats are supported.</P>
$ad_formats_text

<H2>Displaying AdSense ads</H2>
<P>There are several ways to display ads, summarized as follows:</P>
<P>Ads can be displayed in pre-defined blocks, in custom blocks, in content or in any phptemplate based theme.</P>

<H3>Using blocks</H3>
<P>The easiest way to get started with this module is to use one or more of the pre-defined blocks.</P>
<P>Visit the <A HREF="/admin/build/block">blocks</A> configuration page, and click on the <STRONG>configure</STRONG>
link of one of the AdSense blocks. You must select a format, a group, and a channel.</P>
<P>Enable the block, and specify a region for it to be displayed in.</P>

<H3>Using custom PHP code</H3>
<P>To display ads, you call the function adsense_display() and supply
it with the following arguments.</P>
<UL>
  <LI>Format: This is a string of two numbers with an &quot;x&quot; in between. It can be any valid
  combination from the list provided above. If not specified, then 160x600 is assumed. 
  <LI>Group: This is the group that denotes the type (text or image) and color of the ad. This can be 1,
  2 or 3. If not specified, then 1 is assumed. 
  <LI>Channel: This is the Custom Channel for the ad, as configured in AdSense. This is an optional parameter
  and if not specified, then 1 is assumed. If you did not configure any channels, then leave this parameter out. 
</UL>
<P>To display ads in blocks, add a new block, make its type &quot;PHP&quot;, and enclose it in PHP tags.</P>
<PRE>
<CODE>print adsense_display('120x600', 1, 2);</CODE></PRE><P>
If you want to make sure that you do not get errors if the AdSense module is accidentally disabled or deleted, then
use the longer form:</P>
<PRE>
<CODE>if (module_exists('adsense')) {</CODE>
<CODE>  print adsense_display('120x600', 2, 4);</CODE>
<CODE>}</CODE>
</PRE>

<H3>Using themes</H3>
<P>You must use a phptemplate-based theme to display ads from within the theme. This requires some familiarity
with PHP. Edit the appropriate <STRONG>.tpl.php</STRONG> file in your theme directory,
and add:</P>
<PRE>
<CODE>print adsense_display('468x60');</CODE>
</PRE>
<P>Make sure you enclose it in PHP tags.</P>
<P>You could also use the longer format that protects you against deleting or disabling the module:</P>
<PRE>
<CODE>if (module_exists('adsense')) {</CODE>
<CODE>  print adsense_display('120x600', 2, 4);</CODE>
<CODE>}</CODE>
</PRE>

<H3>Using tags</H3>
<P>The tags feature allows placement of ads anywhere in the content.  Please note that content here means any
part that is passed through Drupal's filter system. Text in the slogan, mission, and footer is normally not
filtered the same way as text in nodes, so you cannot put tags in those places.</P>
<P>To enable the tags feature, you have to enable the &quot;AdSense tag&quot; filter in the input format you
are using (such as Full HTML or Filtered HTML) from Administer -&gt; Site configuration -&gt; Input formats.
Then you have to insert the appropriate tag in your node where you would like the ad to appear.</P>
<P>Note that filters sometimes may have conflicts, and changing the order can make AdSense work in some cases.</P>
<P>The tag syntax comes in these variants:</P>
<DL>
  <DT>1. [adsense:<EM>format:group:channel:slot</EM>]</DT>
</DL>
<P>Where:</P>
<UL>
  <LI>format: One of the supported ad formats (such as 468x60). (required)
  <LI>group: A number corresponding to the ad group this ad belongs to, determines colors.
  <LI>channel: A number corresponding to the ad channel.
        <LI>slot: Your ad's slot ID as provided by Google.
</UL>
<P>Example:</P>
<PRE>[adsense:468x60:1:2:0123456789]</PRE><P>
Display a 468x60 banner with the colors defined in group 1, channel ID 2 and with slot ID 0123456789.</P>
<DL>
  <DT>2. [adsense:block:<EM>block_id</EM>]</DT>
</DL>
<P>Where:</P>
<UL>
  <LI>block_id: The block ID of a custom block with input format of PHP with a call to the adsense_display() function. (required)
</UL>
<P>This allows more fine grained visibility control via the block mechanism. The block does not need to be
enabled, and therefore will be hidden from the sidebars and other regions. The title of the block will not be
displayed.</P>
<P>Example:</P>
<PRE>[adsense:block:7]</PRE>
<P>Display the ad code of the block with ID 7.</P>
<DL>
  <DT>3. [adsense:referral:<EM>format:group:channel:slot:CPA</EM>]</DT>
</DL>
<P>Where:</P>
<UL>
  <LI>format: One of the supported ad formats (such as 468x60). (required)
  <LI>group: A number corresponding to the ad group this ad belongs to, determines colors.
  <LI>channel: A number corresponding to the ad channel.
        <LI>slot: Your ad's slot ID as provided by Google.
        <LI>CPA: Your referral link CPA value.
</UL>
<P>Example:</P>
<PRE>[adsense:referral:468x60:1:2:0123456789:CAAxxxxxxxxxxxxxxxxxxxxxxxxxxxxx]</PRE><P>
Display a 468x60 banner with the colors defined in group 1, channel ID 2, slot ID 0123456789
and with CPA value CAAxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.</P>
<DL>
  <DT>4. [adsense:flexiblock:<EM>location</EM>]</DT>
</DL>
<P>
This is provided for backward compatibility, but will be deprecated
in a future release. Use the normal block filter instead.</P>
<P>Where:</P>
<UL>
  <LI>location: A number corresponding to a location in flexiblock that contains only one block with
  the call to the adsense_display() function. This allows visibility control via the block mechanism.
  flexiblock must be installed and configured. The title of the flexiblock will not be displayed. (required)
</UL>
<P>Example:</P>
<PRE>[adsense:flexiblock:2]</PRE><P>
Display the contents of the flexiblock in location 2</P>

<H2>AdSense clicks</H2>
<P>AdSense clicks are now tracked, and the IP address and timestamp are recorded for each click.
This should help with fraud detection.  There are three reports under Administer -&gt; Logs: the
default one shows click details, &quot;By date&quot; shows the number of clicks per day by day,
and &quot;Top pages&quot; shows the top pages of a site that get clicks, the total number of clicks
it got, and the last click date/time.</P>
<P>Note that there are some potential limitations with click tracking:</P>
<UL>
  <LI>The javascript code does not work in Firefox, and perhaps Opera. Patches to make it work on Firefox
  would be appreciated. 
  <LI>Google throws out what it sees as invalid clicks. 
  <LI>There is a lag of 15 to 20 minutes before Google records the click. 
  <LI>When using AdLinks, the click on the link is recorded but any subsequent click on links is not recorded
  (since it is not actually on your site anymore). 
</UL>

<H2>Hints and Tips</H2>
  <P>This section has a collection of tips and hints. Please read it before submitting support requests.
  Also, if you find a useful hint or tip relating to using this module, consider submitting a patch to 
  the adsense_help.inc file so the community would benefit from it.</P>

  <H3>Visibility of Ads</H3>
  <P>The site administrator will not see ads displayed as long as they are logged in. This is by design, in
  order not to skew the page views, and not to accidentally click on ads (against Google's policy). Log out
  to see the ads.</P>

  <P>You can use the advanced options to disable ads and configure a placeholder when you are developing or
  theming to know where the ads will appear.</P>

  <P>Also, the test mode for ads would help with showing what parameters are used for an ad.</P>

  <H3>Ads not showing</H3>
  <P>If ads are not displayed, that could be caused by several things:</P>
  <UL>
    <LI>You are logged in as the site administrator. Log off to see the ads. 
    <LI>Your site is still new and Google has not indexed it yet. 
    <LI>Your site has been blacklisted by Google.
    <LI>The maximum number of ad units has already been displayed. Your page does not have enough content
    to display more than one or two units. 
    <LI>Check the page source for comments like this: &lt;!--adsense: ???--&gt;. These give hints to what
    is going on, and if you know PHP you can trace those in the module's source code. 
  </UL>

  <H3>Module Weight</H3></p>
  <P>Unless configured otherwise, Drupal normally calls modules in alphabetical order. Insofar as Adsense starts
  with "a," this may occasionally cause conflicts with other installed modules. For example, with <strong>image_attach</strong>
  (a function of the <a href = "http://drupal.org/project/image">image</a> module), Adsense will normally be invoked
  <strong>first</strong> ("a" coming before "i"); this may interfere with inline styling of images attached to posts.</P>

  <P><strong>Solution:</strong> Install and configure the <a href = "http://drupal.org/project/moduleweight">Module Weight</a>
  module and configure modules to load in the desired order. In this case, giving Image Attach a weight of -1 should resolve the
  issue.</P>

EOF;
  return $output;
}

