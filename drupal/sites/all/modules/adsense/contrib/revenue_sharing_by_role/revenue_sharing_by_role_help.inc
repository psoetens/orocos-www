<?php
// $Id: revenue_sharing_by_role_help.inc,v 1.1 2008/06/11 16:51:29 kbahey Exp $

function revenue_sharing_by_role_help_text() {
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
<P>This module provides web site admins the factility to share revenue from Google AdSense ads with 
those writing the content on the site, according to certain percentages.</P>

<H2>Prerequisites</H2>
<P>You must have a Google AdSense account before using this module.  If you do not have an account,
then please consider using <A HREF="$referral_link">the modules author's referral link</A>, which
provides us with a referral fee from Google at absolutely no cost to you. This page also contains
various useful links and resources on AdSense, and how to optimize your site for it.</P>

<H2>Revenue sharing</H2>
<P>For revenue sharing, each author gets a predefined share of ad revenue from clicks occuring on
nodes they authored.</P>
<P>In order for the user to be credited they must have a Google AdSense account. As a site admin,
please advertise <A HREF="$referral_link">the module author's referral link</A>, which provides us
with a referral fee from Google, at absolutely no cost to you. This page also contains various useful
links and resources on AdSense and how to optimize your site for it.</P>
<P>Each user must enter their Google AdSense client ID in the profile field you defined above.</P>

<H2>Configuration</H2>
<P>To use this module, you need to do the following first:</P>
<UL>
	<LI>
    <P>Go to <A HREF="/admin/user/profile">Administer -&gt; User management -&gt; Profiles</A> and
    create a new profile field of type &quot;single-line textfield&quot;. Name this field something like
    &quot;Google AdSense client ID&quot;, and form name &quot;profile_google_adsense_client_id&quot;. This
    is a required configuration parameter. At a minimum you should enter this field for user 1. 
	  </P>
	  <P>Note that the new profile field must be setup as: &quot;Private field, content only available to privileged
    users&quot;. All other values are either insecure (others can see the Google Adsense ID of the user), or will
    not work, so do not use any of them.</P>
	  <P>If you want to force users to enter a value when they sign up, then use the following settings:</P>
	  <UL>
		  <LI>The user must enter a value (checked). 
		  <LI>Visible in user registration form (checked). 
	  </UL>
	  <P>You should enter a descriptive explanation for the Google AdSense client ID, so users know what to
    enter in this field.</P>

	<LI>Go to <A HREF="/user/$uid/edit">My account -&gt; Edit</A>, then click on the category that you defined
  for the Google AdSense client ID and enter your Google ID, which is something like &quot;pub-9999999999999&quot;,
  and click Submit. 
</UL>

EOF;
  return $output;
}

