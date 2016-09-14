<?php
/**
 * @file
 * Drush commands related to nodes.
 */

/**
* Implements hook_drush_command().
*/
function drush_node_drush_command() {
  $items['node-delete'] = array(
    'description' => dt("Delete nodes."),
    'aliases' => array('nd'),
    'arguments' => array(
      'nids' => dt('The nids of the nodes to delete.'),
    ),
    'examples' => array(
      'drush node-delete 1' => dt('Delete the node with nid = 1.'),
      'drush node-delete 1 2 3' => dt('Delete the nodes with nid = 1, 2 and 3.'),

    ),
  );
  return $items;
}

/**
 * Callback for the node-delete command.
 */
function drush_drush_node_node_delete() {
  $nids = func_get_args();

  if (!empty($nids)) {
    $test_nids = $nids;
    // Check for integer ids.
    $test_nids = array_filter($test_nids, 'ctype_digit');

    if (count($test_nids) != count($nids)) {
      drush_set_error('DRUSH_NODE_DELETE_ERROR', dt('You must specify digits for the nids.'));
      return;
    }

    // Check for duplicate ids.
    $test_nids = array_unique($test_nids);
    if (count($test_nids) != count($nids)) {
      drush_set_error('DRUSH_NODE_DELETE_ERROR', dt('You have duplicate nids.'));
      return;
    }

    $nodes_in_db = array_keys(entity_load('node', $nids));
    $nodes_non_existent = array_diff($nids, $nodes_in_db);

    if(count($nodes_in_db) == 0) {
      drush_set_error('DRUSH_NODE_DELETE_ERROR', dt("The desired nodes to delete doesn't exists."));
      return;
    }

    if(count($nodes_non_existent)) {
      drush_print(dt("Non-existent nodes:"));
      drush_print(implode(' ', $nodes_non_existent));
    }

    node_delete_multiple($nids);

    drush_print(dt("Deleted nodes:"));
    drush_print(implode(' ', $nodes_in_db));
  }
  else {
    drush_set_error('DRUSH_NODE_DELETE_ERROR', dt("You must enter at least one nid."));
  }
}
