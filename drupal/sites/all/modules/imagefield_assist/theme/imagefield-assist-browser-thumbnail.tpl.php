<?php
// $Id: imagefield-assist-browser-thumbnail.tpl.php,v 1.1.2.1 2009/07/04 15:40:33 lourenzo Exp $

/**
 * @file
 * This template outputs individual thumbnails in ImageField assist's image browser.
 * 
 * Available variables:
 *   object $view
 *   array $options
 *   object $row
 *   string $zebra
 *   int $id
 *   string $directory
 *   bool $is_admin
 *   bool $is_front
 *   bool $logged_in
 *   bool $db_is_active
 *   object $user
 * 
 *   string $thumbnail
 *   string $path
 *   string $title
 */
?>
<a href="<?php print $path; ?>" title="<?php print $title; ?>"><?php print $thumbnail; ?></a>
