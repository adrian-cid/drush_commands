<?php
/**
 * @file
 * Drush commands related to taxonomy.
 */

include 'common_functions.inc.php';

/**
* Implements hook_drush_command().
*/
function drush_taxonomy_drush_command() {
  $items['vocabulary-clean'] = array(
    'description' => dt("Delete all terms in a vocabulary."),
    'aliases' => array('vc'),
    'arguments' => array(
      'name' => dt('The vocabulary names to clean.'),
    ),
    'examples' => array(
      'drush vocabulary-clean tags' => dt('Delete all the terms in tags vocabulary'),
      'drush vocabulary-clean tags test' => dt('Delete all the terms in tags and test vocabularies'),

    ),
  );
  return $items;
}

/**
 * Callback for the vocabulary clean command.
 */
function drush_drush_taxonomy_vocabulary_clean() {
  $names = func_get_args();

  if (!empty($names)) {
    // Check for duplicate ids.
    $test_names = array_unique($names);
    if (count($test_names) != count($names)) {
      drush_set_error('DRUSH_VOCABULARY_CLEAN_ERROR', dt('You have duplicate vocabulary names.'));
      return;
    }
    //Searching the vocabularies in the site
    $vocabulary_in_db = array_column(taxonomy_get_vocabularies(), 'machine_name');
    $vocabulary_non_existent = array_diff($names, $vocabulary_in_db);
    $vocabulary_existent = array_diff($names, $vocabulary_non_existent);
    
    if(count($vocabulary_existent) == 0) {
      drush_set_error('DRUSH_VOCABULARY_CLEAN_ERROR', drush_plural(count($vocabulary_non_existent), "The desired vocabulary to clean doesn't exists.", "The desired vocabularies to clean doesn't exists."));
      return;
    }

    if(count($vocabulary_non_existent)) {
      drush_print(drush_plural(count($vocabulary_non_existent), 'Non-existent vocabulary:', 'Non-existent vocabularies:'));
      drush_print(implode(' ', $vocabulary_non_existent));
    }
    
    foreach ($vocabulary_existent as $name) {
      $vid = taxonomy_vocabulary_machine_name_load($name)->vid;
      foreach(taxonomy_get_tree($vid) as $term) {
        taxonomy_term_delete($term->tid);
      }
    }

    drush_print(drush_plural(count($vocabulary_existent), 'Vocabulary cleaned:', 'Vocabularies cleaned:'));
    drush_print(implode(' ', $vocabulary_existent));
  }
  else {
    drush_set_error('DRUSH_VOCABULARY_CLEAN_ERROR', dt('You must enter at least one vocabulary name.'));
  }
}