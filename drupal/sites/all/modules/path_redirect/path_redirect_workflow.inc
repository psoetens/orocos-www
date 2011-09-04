<?php
// $Id: path_redirect_workflow.inc,v 1.1.2.2 2008/01/27 03:43:16 horsepunchkid Exp $

/**
 * @file Workflow-ng integration for the path_redirect module
 *
 * Based heavily on workflow_ng_path.inc
 */

/**
 * Implementation of hook_condition_info()
 */
function path_redirect_condition_info() {
  return array(
    'path_redirect_condition_path_has_redirect' => array(
      '#label' => t('Path has redirect'),
      '#module' => t('Path Redirect'),
    ),
    'path_redirect_condition_redirect_exists' => array(
      '#label' => t('URL redirect destination already exists'),
      '#module' => t('Path Redirect'),
    ),
  );
}

/**
 * Condition implementation: Check if the path has a redirect
 */
function path_redirect_condition_path_has_redirect($settings, &$arguments, &$log) {
  extract(workflow_ng_token_replace_all(array('path'), $settings, $arguments, $log));
  return (bool)path_redirect_load(NULL, $path);
}

function path_redirect_condition_path_has_redirect_form($settings = array(), $argument_info) {
  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Existing system path'),
    '#default_value' => $settings['path'],
    '#maxlength' => 255,
    '#size' => 50,
    '#description' => t('Specify the existing path for which you want to check if a redirect exists.'),
    '#field_prefix' => url(NULL, NULL, NULL, TRUE) . (variable_get('clean_url', 0) ? '' : '?q='),
    '#required' => TRUE,
  );
  workflow_ng_token_replacement_help($form, $argument_info);
  return $form;
}

function path_redirect_condition_path_has_redirect_submit($form_id, $form_values) {
  return workflow_ng_token_get_settings(array('path'), $form_values);
}

/**
 * Implementation of hook_action_info()
 */
function path_redirect_action_info() {
  return array(
    'path_redirect_action_create' => array(
      '#label' => t('Create or delete a URL redirect'),
      '#module' => t('Path Redirect'),
    ),
  );
}

/**
 * Action implementation: Create a URL redirect
 */
function path_redirect_action_create($settings, &$arguments, &$log) {
  extract(workflow_ng_token_replace_all(array('path', 'redirect', 'query', 'fragment', 'type'), $settings, $arguments, $log));

  path_redirect_save(array('path' => $path, 'redirect' => $redirect, 'query' => $query, 'fragment' => $fragment, 'type' => $type));
}

function path_redirect_action_create_form($settings = array(), $argument_info) {
  $form = path_redirect_edit($settings);
  $form['submit'] = NULL;
  workflow_ng_token_replacement_help($form, $argument_info);
  return $form;
}

function path_redirect_action_create_submit($form_id, $form_values) {
  return workflow_ng_token_get_settings(array('path', 'redirect', 'query', 'fragment', 'type'), $form_values);
}

