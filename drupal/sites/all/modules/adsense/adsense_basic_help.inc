<?php
// $Id: adsense_basic_help.inc,v 1.1 2008/02/10 01:24:19 kbahey Exp $

// Copyright 2005-2008 Khalid Baheyeldin - http://2bits.com

function adsense_basic_help_text() {
  $referral_link = 'http://baheyeldin.com/click/476/1';

  $output = <<<EOF
<H2>Overview</H2>
<P>This module provides a simple way of selecting the Adsense Client ID for a single owner site 
that does not need revenue sharing.</P>

<H2>Prerequisites</H2>
<P>You must have a Google AdSense account before using this module.  If you do not have an account,
then please consider using <A HREF="$referral_link">the modules author's referral link</A>, which
provides us with a referral fee from Google at absolutely no cost to you. This page also contains
various useful links and resources on AdSense, and how to optimize your site for it.</P>

<H2>Configuration</H2>
<P>To use this module, simply enter your Google Adsense Client ID in the text field, and click 
the 'Save configuration' button.</P>
EOF;
  return $output;
}

