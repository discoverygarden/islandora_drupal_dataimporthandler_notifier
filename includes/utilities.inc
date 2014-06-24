<?php

/**
 * @file
 * Utility functions.
 */

/**
 * Poke dataimporthandlers to cause new content to be indexed.
 */
function islandora_drupal_dataimporthandler_notifier_poke_handlers() {
  module_load_include('inc', 'islandora_solr', 'includes/luke');
  $solr_url = islandora_solr_check_http(variable_get('islandora_solr_url', 'localhost:8080/solr'));
  foreach (array_filter(variable_get('islandora_drupal_dataimporthandler_notifier_handlers', array())) as $handler_path_suffix) {
    $url = url("$solr_url$handler_path_suffix", array(
      'query' => array(
        'command' => 'full-import',
        'clean' => 'false',
      ),
    ));
    $result = drupal_http_request($url);
  }
}

/**
 * Add shutdown handler.
 *
 * Drupal uses transactions in node_save(), so hook_node_insert() and
 * hook_node_update() do not suffice, as the data is not necessarily in the
 * database... To help ensure that the node has been committed, let's push this
 * into the shutdown handler.
 */
function islandora_drupal_dataimporthandler_notifier_add_shutdown_handler() {
  $set =& drupal_static(__FUNCTION__, FALSE);

  if (!$set) {
    $set = TRUE;
    module_load_include('inc', 'islandora_drupal_dataimporthandler_notifier', 'includes/utilities');
    drupal_register_shutdown_function('islandora_drupal_dataimporthandler_notifier_poke_handlers');
  }
}
