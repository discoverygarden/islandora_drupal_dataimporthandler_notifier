<?php

/**
 * @file
 * Utility functions.
 */

/**
 * Poke dataimporthandlers to cause the node to be indexed.
 */
function islandora_drupal_dataimporthandler_notifier_poke_handlers($node) {
  module_load_include('inc', 'islandora_solr', 'includes/luke');
  $solr_url = islandora_solr_check_http(variable_get('islandora_solr_url', 'localhost:8080/solr'));
  foreach (variable_get('islandora_drupal_dataimporthandler_notifier_handlers', array()) as $handler_path_suffix) {
    $url = url("$solr_url$handler_path_suffix", array(
      'query' => array(
        'command' => 'delta-import',
      ),
    ));
    $result = drupal_http_request($url);
  }
}
