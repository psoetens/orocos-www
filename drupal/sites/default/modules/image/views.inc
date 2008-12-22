<?php
// $Id: views.inc,v 1.1.2.2 2007/08/27 22:48:27 drewish Exp $

/**
 * Implementation of hook_views_tables()
 */
function image_views_tables() {
  $tables['image'] = array(
    'name' => 'node',
    'fields' => array(
      'nid' => array(
        'name' => t('Image: Display Image'),
        'handler' => array(
          'image_views_handler_image_img' => t('Image'),
          'image_views_handler_image_img_link' => t('Image with link'),
        ),
        'option' => array(
          '#type' => 'select',
          '#options' => 'image_views_handler_filter_image_size',
        ),
        'notafield' => true,
        'sortable' => false,
      ),
    ),
  );
  return $tables;
}

/**
 * Views handler for displaying the image.
 */
function image_views_handler_image_img($fieldinfo, $fielddata, $value, $data) {
  $node = node_load($data->nid);
  return image_display($node, $fielddata['options']);
}

/**
 * Views handler for displaying the image in a link to the the image node
 */
function image_views_handler_image_img_link($fieldinfo, $fielddata, $value, $data) {
  $node = node_load($data->nid);
  return l(image_display($node, $fielddata['options']), "node/{$node->nid}", array(), NULL, NULL, FALSE, TRUE);
}

/**
 * Views - Generate a list of all the valid sizes that are available
 */
function image_views_handler_filter_image_size($op) {
  foreach (_image_get_sizes() as $key => $size) {
    $a[$key] = $size['label'];
  }
  return $a;
}

