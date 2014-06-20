<?php

/**
 * @file
 * Admin form and associated functions.
 */

/**
 * Form building function for admin form.
 */
function islandora_drupal_dataimporthandler_notifier_admin_form($form, &$form_state) {
  $map_handlers_to_options = function($handler, $key) {
    return array('handler_suffix' => $key);
  };
  $handlers = islandora_drupal_dataimporthandler_notifier_get_handler_info_from_solr();
  $handler_keys = array_keys($handlers);
  $form['islandora_drupal_dataimporthandler_notifier_handlers'] = array(
    '#type' => 'tableselect',
    '#title' => t('Dataimporthandlers'),
    '#header' => array(
      'handler_suffix' => t('Handler suffix/Route'),
    ),
    '#options' => array_combine($handler_keys, array_map($map_handlers_to_options, $handlers, $handler_keys)),
    '#default_value' => variable_get('islandora_drupal_dataimporthandler_notifier_handlers', array()),
  );

  dsm($form);

  return system_settings_form($form);
}

/**
 * Grab defined DataImportHandlers from Solr's config.
 *
 * @return array
 *   An associative array mapping the path suffixes/routes at which the given
 *   handlers listen to any values which may be defined in the handler.
 */
function islandora_drupal_dataimporthandler_notifier_get_handler_info_from_solr() {
  $cached_handlers =& drupal_static(__FUNCTION__, array());

  $solr_url = variable_get('islandora_solr_url', 'localhost:8080/solr');

  if (!isset($cached_handlers[$solr_url])) {
    module_load_include('inc', 'islandora_solr', 'includes/admin');
    $config_xml = islandora_solr_get_solrconfig_xml($solr_url);
    $handlers = array();
    foreach ($config_xml->xpath('//requestHandler[@class="org.apache.solr.handler.dataimport.DataImportHandler"]') as $handler_element) {
      $handler = array();
      foreach ($handler_element->xpath('//lst') as $list) {
        foreach ($list->children() as $value) {
          $handler[(string) $list['name']][(string) $value['name']] = (string) $value;
        }
      }
      $handlers[(string) $handler_element['name']] = $handler;
    }
    $cached_handlers[$solr_url] = $handlers;
  }

  return $cached_handlers[$solr_url];
}
