<?php
// $Id: taxonomy_breadcrumb.inc,v 1.1.2.6 2010/03/31 01:46:35 mgn Exp $

/**
 * @file
 * helper functions for taxonomy_breadcrumb
 */

/**
 * Set a Taxonomy breadcrumb and call the original taxonomy/term/% callback.
 *
 * @param $tid
 *   The TID of the term to call a callback for.
 * @param $callback
 *   The name of the original callback function.
 * @param $file
 *   The file the original term callback is in.
 * @param $filepath
 *   The path to $file.
 * @param ...
 *   Additional arguments to pass on to the callback.
 *
 * @ return
 *   The return value of the original callback function.
 */
function _taxonomy_breadcrumb_term_page($tid, $callback, $file, $filepath) {
  require_once($filepath .'/'. $file);
  $arguments = array_slice(func_get_args(), 4);
  $output =  call_user_func_array($callback, $arguments);
  // Use first term to generate breadcrumb trail.
  $terms = taxonomy_terms_parse_string($tid);
  $breadcrumb = _taxonomy_breadcrumb_generate_breadcrumb($terms['tids'][0], TRUE);
  drupal_set_breadcrumb($breadcrumb);
  return $output;
}

/**
 * Return lightest term for a given node.
 *
 * @param $node
 *   The node object.
 *
 * @ return
 *   The lightest term object associated with the node.
 */
function _taxonomy_breadcrumb_node_get_lightest_term($node) {
  $terms = taxonomy_node_get_terms($node);
  if (!empty($terms)) {
    if (count($terms) > 1) {
      foreach ($terms as $term) {
        // Only consider terms in the lightest vocabulary.
        if (!isset($vid)) {
          $vid = $term->vid;
        }
        elseif ($term->vid != $vid) continue;
        // If the term has parents, the weight of the term is the weight of the lightest parent.
        $parents = taxonomy_get_parents_all($term->tid);
        $depth = count($parents);
        if ($depth > 0) {
          $parent = array_pop($parents);
          $weight = $parent->weight;
        }
        else {
          $weight = $term->weight;
        }
        if ((isset($lweight) && ($weight < $lweight)) || !isset($lweight)) {
          $lterm = $term;
          $lweight = $weight;
          $ldepth = $depth;
        }
        elseif (isset($lweight) && ($weight == $lweight)) {
          // If the node has multiple child terms with the same parent, choose the child with the greatest depth.
          if ($depth > $ldepth) {
            $lterm = $term;
            $ldepth = $depth;
          }
          elseif ($depth == $ldepth) {
            // If the terms have the same depth, pick the term with the lightest weight.
            $lterm = ($lterm->weight < $term->weight) ? $lterm : $term;
          }
        }
      }
      return $lterm;
    }
    else {
      return array_pop($terms);
    }
  }
}

/**
 * Return the administrator defined vocabulary path for a given vocabulary
 * ($vid).  If a path doesn't exist, NULL is returned.
 */
function _taxonomy_breadcrumb_get_vocabulary_path($vid) {
  $result = db_query("SELECT path FROM {taxonomy_breadcrumb_vocabulary} WHERE vid = %d", $vid);
  $path = NULL;
  if ($row = db_fetch_array($result)) {
    $path = $row['path'];
  }
  return $path;
}

/**
 * Return the administrator defined term path for a given term ($tid).
 * If a path doesn't exist, NULL is returned.
 */
function _taxonomy_breadcrumb_get_term_path($tid) {
  $result = db_query("SELECT path FROM {taxonomy_breadcrumb_term} WHERE tid = %d", $tid);
  $path = NULL;
  if ($row = db_fetch_array($result)) {
    $path = $row['path'];
  }
  return $path;
}

/**
 * If the current drupal path (q=) is /node/nid, generate the breadcrumb trail
 * based on nid.
 */
function _taxonomy_breadcrumb_generate_breadcrumb($tid, $is_term_page = FALSE) {

  $term = taxonomy_get_term($tid);

  // Generate the HOME breadcrumb.
  $home_text = variable_get('taxonomy_breadcrumb_home', t('Home'));
  if ($home_text != '') {
    $breadcrumb[] = l($home_text, NULL);
  }
  // Generate the VOCABULARY breadcrumb.
  $vocabulary_path = _taxonomy_breadcrumb_get_vocabulary_path($term->vid);
  if ($vocabulary_path != NULL) {
    $vocabulary = taxonomy_vocabulary_load($term->vid);
    $breadcrumb[] = l(_taxonomy_breadcrumb_tt("taxonomy:vocabulary:$term->tid:name", $vocabulary->name), $vocabulary_path);
  }

  // Generate the TERM breadcrumb.
  $parent_terms = array_reverse(taxonomy_get_parents_all($tid));
  foreach ($parent_terms as $parent_term) {
    $term_path = _taxonomy_breadcrumb_get_term_path($parent_term->tid);
    if ($term_path == NULL) {
      $term_path = taxonomy_term_path(taxonomy_get_term($parent_term->tid));
    }
    if ($term_path == '<none>') {
      continue;
    }

    $term_title = $parent_term->name;
    // Use the SYNONYM instead of TERM, if we want to.
    if (variable_get('taxonomy_breadcrumb_use_synonym', FALSE)) {
      $synonyms = taxonomy_get_synonyms($parent_term->tid);
      if (!empty($synonyms)) {
        $term_title = $synonyms[0];
      }
    }
    // Do not create links to own self if we are on a taxonomy/term page.
    if ($is_term_page && $parent_term->tid == $tid) {
      $breadcrumb[] = check_plain(_taxonomy_breadcrumb_tt("taxonomy:term:$parent_term->tid:name", $term_title));
    }
    else {
      $breadcrumb[] = l(_taxonomy_breadcrumb_tt("taxonomy:term:$parent_term->tid:name", $term_title), $term_path);
    }
  }

  // Optionally remove the current TERM from end of breadcrumb trail.
  if (!variable_get('taxonomy_breadcrumb_show_current_term', TRUE) && !is_null($breadcrumb)) {
      array_pop($breadcrumb);
  }
  return $breadcrumb;
}

/**
 * Helper function for when i18ntaxonomy module is not installed.
 */

function _taxonomy_breadcrumb_tt($string_id, $default, $language = NULL) {
  return function_exists('tt') ? tt($string_id, $default, $language) : $default;
}
