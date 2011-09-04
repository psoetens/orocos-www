<?php
// $Id: drutex_latex.inc,v 1.11.8.1 2008/11/17 09:05:36 darthsteven Exp $

/**
 * @file
 * Provide the LaTeX-to-HTML transformation rules.
 */

/**
 * Implementation of subhook_info().
 */
function drutex_latex_info($format = -1) {
  return (object) array(
    'title' => t('LaTeX to HTML'),
    'description' => t('Converts many LaTeX commands and environments to plain HTML.'),
    'toggle' => TRUE,
    'weight' => 4
  );
}

/**
 * Implementation of subhook_filter_tips().
 */
function drutex_latex_filter_tips($delta, $format, $long = FALSE) {
  if (user_access('access latex source')) {
    return t('Visit drutex/latex/nid to generate a LaTeX file of this node.');
  }
}

/**
 * Implementation of subhook_link().
 */
function drutex_latex_link($type, $node = NULL, $teaser = FALSE) {
  if (user_access('access latex source')) {
    $latex_link = 'drutex/latex/'. $node->nid;
    $text = t('Generate LaTex file');
    $links['drutex_latex_link'] = array(
      'title' => $text,
      'href' => $latex_link,
      );
    return $links;
  }
}

/**
 * Implementation of subhook_defaults().
 */
function drutex_latex_defaults() {
  $D['drutex_latex_active'] = FALSE;
  return $D;
}

/**
 * Implementation of subhook_node2html().
 */
function drutex_latex_node2html() {
  $E = array();

  $E[] = (object) array(
      'type' => 'latex-command',
      'pattern' => 'section',
      'replacement' => '<h2 class="section">$1</h2>'
    );

  $E[] = (object) array(
      'type' => 'latex-command',
      'pattern' => 'subsection',
      'replacement' => '<h3 class="subsection">$1</h3>'
    );

  $E[] = (object) array(
      'type' => 'latex-command',
      'pattern' => 'minisection',
      'replacement' => '<h3 class="minisection">$1</h3>'
    );

  $E[] = (object) array(
      'type' => 'latex-command',
      'pattern' => 'paragraph',
      'replacement' => '<h4 class="paragraph">$1</h4>'
    );

  $E[] = (object) array(
      'type' => 'latex-command',
      'pattern' => 'textbf',
      'replacement' => '<b>$1</b>'
    );

  $E[] = (object) array(
      'type' => 'latex-command',
      'pattern' => 'textit',
      'replacement' => '<i>$1</i>'
    );

  $E[] = (object) array(
      'type' => 'latex-command',
      'pattern' => 'emph',
      'replacement' => '<em>$1</em>'
    );


  /*
    regex hacks for:
      enumeration aka ordered list
      itemize aka unordered list
  */

  $E[] = (object) array(
      'pattern' => '@\\\\begin\{enumerate\}@s',
      'replacement' => '<ol class="enumerate">',
      'weight' => 100
    );

  $E[] = (object) array(
      'pattern' => '@\\\\begin\{itemize\}@s',
      'replacement' => '<ul class="itemize">',
      'weight' => 100
    );

  $E[] = (object) array(
      'pattern' => '@\\\\item(.*?)(?=\\\\item|\\\\end\{enumerate\}|\\\\end\{itemize\})@s',
      'replacement' => "<li>$1</li>",
      'weight' => 101
    );

  $E[] = (object) array(
      'pattern' => '@\\\\end\{enumerate\}@s',
      'replacement' => "</ol>",
      'weight' => 102
    );

  $E[] = (object) array(
      'pattern' => '@\\\\end\{itemize\}@s',
      'replacement' => "</ul>",
      'weight' => 102
    );

  return $E;
}
