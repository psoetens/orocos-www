<?php
function _phptemplate_variables($hook, $vars = array()) {
  switch ($hook) {
  case 'page':
    
    // Add page template suggestions based on the aliased path.
    // For instance, if the current page has an alias of about/history/early,
    // we'll have templates of:
    // page-about-history-early.tpl.php
    // page-about-history.tpl.php
    // page-about.tpl.php
    // Whichever is found first is the one that will be used.
    if (module_exists('path')) {
      $alias = drupal_get_path_alias(str_replace('/edit','',$_GET['q']));
      if ( $alias != $_GET['q'] && $alias == $_REQUEST['q'] ) {
	$suggestions = array();
	$template_filename = 'page';
	foreach (explode('/', $alias) as $path_part) {
	  $template_filename = $template_filename . '-' . $path_part;
	  $suggestions[] = $template_filename;
	}
      }
      $vars['template_files'] = $suggestions;
    }
    break;
  }
  
  return $vars;
  }
?>
