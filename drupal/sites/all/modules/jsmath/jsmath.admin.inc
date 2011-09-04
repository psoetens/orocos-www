<?php
// $Id: jsmath.admin.inc,v 1.1.2.4 2010/08/25 08:51:20 alexiswilke Exp $

/**
 * Produce the form with the jsMath settings
 */
function _jsmath_settings() {
  $form = array();

  $form['jsmath_scale'] = array(
    '#type' => 'textfield',
    '#title' => t('scale'),
    '#default_value' => variable_get('jsmath_scale', 120),
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('This controls the scaling factor for the mathematics in comparison 
      to the surrounding text. It is a percentage value, so 100 would be unscaled, and 120 
      would be scaled to 20 percent larger than normal. The math fonts often are a bit small 
      compared to the standard font used in the browser, so you may want to use a size larger 
      than 100. Also, since mathematics uses lots of super- and sub-scripts, if you are using 
      small fonts on your pages, these can become difficult to read. Enlarging the scaling 
      factor can help make super- and sub-scripts clearer. Usually, values between 120 and 133 
      are good choices.'
    ),
  );

  $form['jsmath_autoload'] = array(
    '#type' => 'checkbox',
    '#title' => t('autoload'),
    '#default_value' => variable_get('jsmath_autoload', 1),
    '#description' => t('This determines whether the 
      <a href="http://www.math.union.edu/~dpvc/jsMath/authors/autoload.html">autoload</a>
      plugin is used or not.
      The autoload plugin checks the web page to see if there is any mathematics on the page
      before loading jsMath and only loads jsMath on pages that need it. Since jsMath is a
      large file (more than 100KB), this can substantially improve the load time for pages
      that don\'t have math on them. On the other hand, the autoload plugin is an additional
      download that has to be performed, and so that pages that do include mathematics will
      open slower, since both autoload and jsMath must be loaded. Since most browsers cache
      javascript files, this should only affect the first page downloaded from your site.
      There will still be a processing cost on each page, however, so if the majority of your
      pages include mathematics, you might consider turning off autoload to make your pages
      work faster.'
    ),
  );

  $form['jsmath_processSlashParens'] = array(
    '#type' => 'checkbox',
    '#title' => t('processSlashParens'),
    '#default_value' => variable_get('jsmath_processSlashParens', 1),
    '#description' => t('<div class="tex2math_ignore">
      This controls whether the
      <a href="http://www.math.union.edu/~dpvc/jsMath/authors/tex2math.html">tex2math</a>
      plugin is used to search for \(...\) 
      within your web pages and convert them to &lt;SPAN CLASS="math">...&lt;/SPAN> tags. This makes it 
      more convenient to enter in-line mathematics for those used to typing LaTeX files.</div>'
    ),
  );

  $form['jsmath_processSlashBrakets'] = array(
    '#type' => 'checkbox',
    '#title' => t('processSlashBrakets'),
    '#default_value' => variable_get('jsmath_processSlashBrakets', 1),
    '#description' => t('<div class="tex2math_ignore">
      This controls whether the
      <a href="http://www.math.union.edu/~dpvc/jsMath/authors/tex2math.html">tex2math</a>
      plugin is used to search for \[...\] 
      within your web pages and convert them to &lt;DIV CLASS="math">...&lt;/DIV> tags. This makes it 
      more convenient to enter displayed equations for those used to typing LaTeX files.</div>'
    ),
  );

  $form['jsmath_processLaTeXenvironments'] = array(
    '#type' => 'checkbox',
    '#title' => t('processLaTeXenvironments'),
    '#default_value' => variable_get('jsmath_processLaTeXenvironments', 1),
    '#description' => t('<div class="tex2math_ignore">
      This controls whether the
      <a href="http://www.math.union.edu/~dpvc/jsMath/authors/tex2math.html">tex2math</a>
      plugin is used to search for LaTeX environments of the form \begin{xxx}...\end{xxx}  
      within your web pages and enclose them in &lt;DIV CLASS="math">...&lt;/DIV> tags.</div>'
    ),
  );

  $form['jsmath_processDoubleDollars'] = array(
    '#type' => 'checkbox',
    '#title' => t('processDoubleDollars'),
    '#default_value' => variable_get('jsmath_processDoubleDollars', 1),
    '#description' => t('<div class="tex2math_ignore">
      This controls whether the
      <a href="http://www.math.union.edu/~dpvc/jsMath/authors/tex2math.html">tex2math</a>
      plugin is used to search for $$...$$ 
      within your web pages and convert them to &lt;div class="math"&gt;...&lt;/div&gt; tags.
      This makes it more convenient to enter displayed equations for those used to typing
      plain TeX files.</div>'
    ),
  );

  $form['jsmath_doubleDollarsAreInLine'] = array(
    '#type' => 'checkbox',
    '#title' => t('doubleDollarsAreInLine'),
    '#default_value' => variable_get('jsmath_doubleDollarsAreInLine', 0),
    '#description' => t('<div class="tex2math_ignore">
      This controls whether the processDoubleDollars generate &lt;div&gt; (unchecked)
      or &lt;span&gt; (checked) tags. This has no effect if processDoubleDollars is
      not checked.</div>'
    ),
  );

  $form['jsmath_processSingleDollars'] = array(
    '#type' => 'checkbox',
    '#title' => t('processSingleDollars'),
    '#default_value' => variable_get('jsmath_processSingleDollars', 1),
    '#description' => t('<div class="tex2math_ignore">
      This controls whether the
      <a href="http://www.math.union.edu/~dpvc/jsMath/authors/tex2math.html">tex2math</a>
      plugin is used to search for $...$
      within your web pages and convert them to &lt;span class="math"&gt;...&lt;/span&gt; tags. This makes it
      more convenient to enter in-line mathematics for those used to typing plain TeX files.</div>'
    ),
  );

  $form['jsmath_fixEscapedDollars'] = array(
    '#type' => 'checkbox',
    '#title' => t('fixEscapedDollars'),
    '#default_value' => variable_get('jsmath_fixEscapedDollars', 1),
    '#description' => t('<div class="tex2math_ignore">
      If you enable processSingleDollars, you may want to enable this setting as well.
      This controls whether the
      <a href="http://www.math.union.edu/~dpvc/jsMath/authors/tex2math.html">tex2math</a>
      plugin is used to convert \$ to $ outside of math mode.
      That gives you the ability to "escape" a dollar sign, and prevent it from being used to
      initiate math mode, so it will appear as a normal dollar sign in the text of the file.</div>'
    ),
  );

  $form['jsmath_allowDoubleClicks'] = array(
    '#type' => 'checkbox',
    '#title' => t('allowDoubleClicks'),
    '#default_value' => variable_get('jsmath_allowDoubleClicks', 1),
    '#description' => t('When the user double-clicks on an equation, jsMath will display
      a popup window that shows the original TeX code for that equation. You can disable
      that feature by setting allowDoubleClicks to 0.'
    ),
  );

  $form['jsmath_showFontWarnings'] = array(
    '#type' => 'checkbox',
    '#title' => t('showFontWarnings'),
    '#default_value' => variable_get('jsmath_showFontWarnings', 1),
    '#description' => t('JsMath works best and fastest when the user has installed the
      <a href="http://www.math.union.edu/~dpvc/jsMath/download/jsMath-fonts.html">jsMath-TeX fonts</a>
      on his or her computer. Without these, jsMath will use an image fallback mode
      that is slower and doesn\'t print as well. If the user does not have these
      fonts installed, jsMath will issue a warning on the first page (containing
      mathematics) that is loaded from your site informing them that the TeX fonts
      will improve their experience of your site, and indicating how to get
      them.<br /><br />

      Some page authers mistakenly think they are helping their readers by disabling
      this feature; in reality, however, you are guaranteeing that they will have a
      poorer experience at your site, since you have deprived them of the knowledge
      that there even is a font that they could download that would improve the speed
      and quality of the mathematics at your site. Since the warning is only issued
      once and it can be dismissed by the click of a button (and even can be prevented
      for up to five years using the control panel), there is no reason for you to
      turn off these informative messages.'
    )
  );

  $form['jsmath_method'] = array(
    '#type' => 'radios',
    '#title' => t('method'),
    '#default_value' => variable_get('jsmath_method', 'Process'),
    '#options' => array('Process' => 'Process', 'ProcessBeforeShowing' => 'ProcessBeforeShowing'),
    '#description' => t('This controls which of the two methods of displaying
      mathematics jsMath should use. The default is to use "Process" (the
      jsMath.Process() function), which processes the mathematics asynchronously,
      so that the page will be displayed before the mathematics is typeset, and
      the user will see the equations turn into typeset math as jsMath processes
      them. JsMath also shows a progress message at the lower left of the screen
      while it is processing the mathematics on the page.<br /><br />

      Choosing "ProcessBeforeShowing", however, will cause all the mathematics
      to be typeset before any of it is displayed. In most browsers, this will
      mean the page shows up with the mathematics already typeset, but there is
      a longer delay before the page appears (since jsMath must perform the
      typesetting before the page is displayed).<br /><br />

      For pages with only a little mathematics, ProcesBeforeShowing may produce
      a more satisfying effect; but for pages with lots of mathematics, the user
      will probably not want to wait for all of it to be processed before being
      able to read any of the page. The Process setting allows the user to be
      reading the page even while the mathematics lower down on the page is being
      typeset, and so it is the default setting.'
    ),
  );

  $form['jsmath_customDelimiters'] = array(
    '#type' => 'textfield',
    '#title' => t('customDelimiters'),
    '#default_value' => _jsmath_delims(),
    '#size' => 80,
    '#maxlength' => 80,
    '#description' => t('This array holds four strings that are used to start
      and stop in-line and displayed mathematics. This way you can use any
      delimiters you want, rather than the TeX or LaTeX ones. Note, however,
      that these can not contain the HTML special characters &lt;, &gt;, or &amp;.
      This is because those characters are used to indicate tags and entities
      within HTML, and since tex2math doesn\'t run until after the page has been
      interpreted by the browser, these character are no longer part of the text
      that is available to tex2math when it processes the page. In particular,
      that means you can\'t make delimiters that look like normal HTML tags.<br/><br/>

      The default delimiters are !delims',
      array('!delims', JSMATH_DEFAULT_DELIMITERS)
    ),
  );

  $form['jsmath_loadFiles'] = array(
    '#type' => 'textfield',
    '#title' => t('loadFiles'),
    '#default_value' => variable_get('jsmath_loadFiles', '"extensions/AMSmath.js", "extensions/AMSsymbols.js"'),
    '#size' => 80,
    '#maxlength' => 250,
    '#description' => t('You can list additional JavaScript files that should be
      loaded once jsMath has been initialized.  This allows you to load
      <a href="http://www.math.union.edu/~dpvc/jsMath/authors/welcome.html">
      jsMath extensions or plugins</a>, or even your own JavaScript files that need
      to call jsMath functions.<br /><br />

      If you have not downloaded the AMSsymbol fonts then you should remove
      extensions/AMSsymbols.js from the list.<br /><br />

      Files are loaded relative to the jsMath folder on the server, but you can
      also include absolute URLs to load extensions from anywhere on your server.
      The <code>jsMath</code> variable will be available when these are run, and
      so you can make a file that calls <code>jsMath.Macro()</code>, for example,
      to define macros that you may need on your page (see the documentation on
      <a href="http://www.math.union.edu/~dpvc/jsMath/authors/macros.html">defining macros</a>
      for details.)'
    ),
  );

  $form['jsmath_loadFonts'] = array(
    '#type' => 'textfield',
    '#title' => t('loadFonts'),
    '#default_value' => variable_get('jsmath_loadFonts', ''),
    '#size' => 80,
    '#maxlength' => 250,
    '#description' => t('This array can be used to list extra fonts that should be
      preloaded for use by jsMath. Note that you need to have these fonts installed
      on your server for this to work. (See the
      <a href="http://www.math.union.edu/~dpvc/jsMath/download/extra-fonts/welcome.html">extra-fonts download page</a>
      for a listing of the fonts available and instructions on installing them.)
      For example, "cmmib10" would load the Computer Modern bold math italic font.
      See the documentation on
      <a href="http://www.math.union.edu/~dpvc/jsMath/authors/morefonts.html">adding fonts</a>
      for details about how to access the font once it is loaded. Multiple fonts can be specified
      by separating their name by commas "cmmib10","cmti10","...".'
    ),
  );

  $form['jsmath_allowGlobal'] = array(
    '#type' => 'checkbox',
    '#title' => t('allowGlobal'),
    '#default_value' => variable_get('jsmath_allowGlobal', 1),
    '#description' => t('JsMath has a \"global mode\" that allows it to cache
      the equations it has typeset to try to speed up processing of later pages.
      (See the
      <a href=\"http://www.math.union.edu/~dpvc/jsMath/users/global.html\">Global Mode documentation</a>
      for details.) This uses a frameset to give jsMath a persistent frame in
      which to hold the cached data, but that introduces a number of thorny
      issues for page authors. In particular, if your site already uses
      framesets, jsMath frames could interfere with that. For this reason,
      you may want to disable jsMath global mode, and can do so by unchecking
      <code>allowGlobal</code>. This will disable the "<code>Go Global</code>"
      button on the jsMath control panel to prevent the user ffrom entering
      global mode.'
    ),
  );

  $form['#validate'][] = '_jsmath_settings_validate';

  return system_settings_form($form);
}

/**
 * Make sure that textfield parameters are valid.
 */
function _jsmath_settings_validate($form, &$form_values) {
  $values = &$form_values['values'];

  $scale = $values['jsmath_scale'];
  if (!preg_match('/^[0-9]+$/', $scale)) {
    form_set_error('jsmath_scale', t('scale must be a number.'));
  }
  elseif ($scale < 20) {
    form_set_error('jsmath_scale', t('scale must be at least 20.'));
  }
  elseif ($scale > 400) {
    form_set_error('jsmath_scale', t('scale must be at most 400.'));
  }

  if (preg_match('/[<&>]/', $values['jsmath_customDelimiters'])) {
    form_set_error('jsmath_customDelimiters', t('The custom delimiter cannot include a &lt;, &amp; or &gt; character.'));
  }
  else {
    _jsmath_check_js_list($values, 'jsmath_customDelimiters', 4, t('You must define exactly 2 opening and 2 closing tags for your custom delimiters.'));
    _jsmath_check_js_list($values, 'jsmath_loadFiles', 0, NULL);
    _jsmath_check_js_list($values, 'jsmath_loadFonts', 0, NULL);
  }
}

/**
 * This function is used to verify that the JavaScript strings defined
 * in the configuration are acceptable as JavaScript strings.
 *
 * This means:
 *
 * 1. The string starts and ends with ' or "
 * 2. The string does not include a ' or "
 * 3. The string does not include a new line character (\n or \r)
 * 4. The string does not include the escape character (\)
 * 5. The string does not include a comma character (,)
 *
 * Note that although we check for commas inside strings, it should be
 * useless since the explode() command will not check whether commas are
 * inside strings.
 */
function _jsmath_check_js_list($values, $field, $count, $count_err) {
  $js = preg_replace('/, +/', ',', $values[$field]);
  if ($js) {
    $strings = explode(',', $js);
  }
  else {
    // explode(',', '') returns array('') which is wrong here
    $strings = array();
  }
  if ($count > 0 && count($strings) != $count) {
    form_set_error($field, $name);
  }
  elseif (!_jsmath_check_js_strings($strings)) {
    form_set_error($field, 
      t('!field must be a set of valid JavaScript strings (\'...\' or "...") without quotes or commas inside the string.',
        array('!field' => str_replace('jsmath_', '', $field))));
  }
}

function _jsmath_check_js_strings($strings) {
  // check the JS strings (frankly, those should be generated by us, not the other way around!?)
  foreach ($strings as $str) {
    // 1 open character + 1 close character + at least 1 character inside the string
    if (strlen($str) < 3) {
      return FALSE;
    }
    // open and close characters must be the same
    $o = $str[0];
    if ($o != substr($str, -1, 1)) {
      return FALSE;
    }
    // check string delimiters
    if ($o != "'" && $o != '"') {
      return FALSE;
    }
    // forbid string delimiter within the string even if properly escaped
    $d = substr($str, 1, -1);
    if (preg_match("/['\",\\\n\r]/", $d)) {
      return FALSE;
    }
  }

  return TRUE;
}

// vim: ts=2 sw=2 et syntax=php
