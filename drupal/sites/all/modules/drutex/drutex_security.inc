<?php
// $Id: drutex_security.inc,v 1.4.8.1 2008/11/17 09:05:37 darthsteven Exp $

/**
 * @file
 * Provide security features for DruTeX.
 *
 * This module covers functions to restrict the set of allowed
 * LaTeX commands and environments.
 */

/**
 * Implementation of subhook_info().
 */
function drutex_security_info($format = -1) {
  return (object) array(
    'title' => t('Security restrictions'),
    'description' => t('Restricts the set of allowed LaTeX commands.'),
    'toggle' => TRUE,
    'weight' => 20
  );
}

/**
 * Implementation of subhook_filter_tips().
 */

function drutex_security_filter_tips($delta, $format, $long = FALSE) {

  if (drutex_var_get("drutex_security_active_$format") == TRUE) {
    $allowed_commands = drutex_var_get("drutex_security_allowedcommands_$format");
    $allowed_environments = drutex_var_get("drutex_security_allowedenvironments_$format");
    $text = t('Allowed commands include: %cmd', array('%cmd' => $allowed_commands));
    $text .= '<br />'. t('Allowed environments include: %env', array('%env' => $allowed_environments));
  }
  else {
    $text = '';
  }
  return $text;
}

/**
 * Implementation of subhook_defaults().
 */
function drutex_security_defaults() {
  $D['drutex_security_active'] = FALSE;
  $D['drutex_security_allowedcommands'] = '\atop \binom \cdot \cfrac \choose \frac \int \ln \over \sum \to';
  $D['drutex_security_allowedenvironments'] = 'align array equation equations gather matrix split';

  return $D;
}

/**
 * Checks if $text only includes allowed commands/environments.
 */
function drutex_security($text, $format = -1) {
  static $allowed_commands = array();

  if (empty($allowed_commands[$format])) {
    $allowed_commands[$format] = explode(' ', drutex_var_get("drutex_security_allowedcommands_$format"));
    $allowed_environments = explode(' ', drutex_var_get("drutex_security_allowedenvironments_$format"));

    foreach ($allowed_environments as $env) {
      $allowed_commands[$format] = array_merge($allowed_commands[$format],
        array("\\begin\{$env}", "\\begin\{$env*}", "\\end\{$env}", "\\end\{$env*}"));
    }
  }

  $matches = array();
  preg_match_all('/(\\\\begin\{[a-zA-Z*]+\})|(\\\\end\{[a-zA-Z*]+\})|(\\\\[a-zA-Z]+)/s', $text, $matches);

  $commands = $matches[0];

  foreach ($commands as $command) {
    if (array_search($command, $allowed_commands[$format]) === FALSE) {
      watchdog('DruTeX', "Unallowed command (by security submodule): %cmd", array('%cmd' => $command), WATCHDOG_WARNING);
      return FALSE;
    }
  }

  return TRUE;
}

/**
 * Implementation of subhook_filter_settings().
 */
function drutex_security_filter_settings($format = -1) {
  $form["drutex_security_allowedcommands_$format"] = array(
    '#type' => 'textarea',
    '#title' => t('Allowed commands'),
    '#rows' => 4,
    '#cols' => 50,
    '#default_value' => drutex_var_get("drutex_security_allowedcommands_$format"),
    '#description' => t('Commands are seperated by single space.')
  );

  $form["drutex_security_allowedenvironments_$format"] = array(
    '#type' => 'textarea',
    '#title' => t('Allowed environments'),
    '#rows' => 4,
    '#cols' => 50,
    '#default_value' => drutex_var_get("drutex_security_allowedenvironments_$format"),
    '#description' => t('Environments are seperated by single space.')
  );

  return $form;
}

