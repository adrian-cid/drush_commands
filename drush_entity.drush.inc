<?php
/**
 * @file
 * Drush commands related to Entities.
 */

/**
* Implements hook_drush_command().
*/
function drush_entity_drush_command() {
  $items['entities-list'] = array(
    'description' => dt("Show a list of available entities."),
    'aliases' => array('el'),
  );
  return $items;
}

/**
 * Callback for the content-type-list command.
 */
function drush_drush_entity_entities_list() {
  $entities = array_keys(entity_get_info());
  sort($entities);

  drush_print(dt("Machine name"));
  drush_print(implode("\r\n", $entities));
}
