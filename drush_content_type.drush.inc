<?php
/**
 * @file
 * Drush commands related to Content Types.
 */

/**
* Implements hook_drush_command().
*/
function drush_content_type_drush_command() {
  $items['content-types-list'] = array(
    'description' => dt("Show a list of available content types."),
    'aliases' => array('ctl'),
  );
  return $items;
}

/**
 * Callback for the content-type-list command.
 */
function drush_drush_content_type_content_types_list() {
  $content_types = array_keys(node_type_get_types());
  sort($content_types);

  drush_print(dt("Machine name"));
  drush_print(implode("\r\n", $content_types));
}
