<?php
// $Id$

$plugin = array(
  'schema' => 'feeds_tamper',
  'access' => 'administer feeds_tamper',
  'menu'   => array(
    'menu prefix'      => 'admin/build',
    'menu item'        => 'feeds_tamper',
    'menu title'       => 'Feeds Tamper',
    'menu description' => 'Feeds Tamper Configuration.',
  ),
  'title singular'        => t('tamper set'),
  'title singular proper' => t('Tamper set'),
  'title plural'          => t('Tamper sets'),
  'title plural proper'   => t('Tamper sets'),
  'form' => array(
    'settings' => 'feeds_tamper_ctools_export_ui_form',
  ),
);

/**
* Define the preset add/edit form.
*/
function feeds_tamper_ctools_export_ui_form(&$form, &$form_state) {
  //drupal_add_js(drupal_get_path('module', 'feeds_tamper') . '/plugins/export_ui/export.js');
  $preset = $form_state['item'];
  $settings = $preset->feeds_tamper_wrapper;
  $importers = feeds_enabled_importers();

  $form['importers'] = array(
    '#type' => 'checkboxes',
    '#options' => array_combine($importers, $importers),
    '#title' => t('Importers'),
    '#default_options' => isset($settings['importers']) ? array_keys($settings['importers']) : array(),
  );

  ctools_include('dependent');
  foreach ($importers as $importer_name) {
    $imp = str_replace('_', '-', $importer_name);
    $form['targets'][$importer_name] = array(
      '#tree' => TRUE,
      '#process' => array('ctools_dependent_process', 'expand_checkboxes'),
      '#dependency' => array("edit-importers-$imp" => array(TRUE)),
      '#type' => 'checkboxes',
      '#options' => feeds_tamper_parse_mappers($importer_name),
      '#title' => t('Targets for ' . $importer_name),
      '#prefix' => '<div id="edit-' . $imp . '-wrapper"><div id="' .$imp.'">',
      '#suffix' => '</div></div>',
      '#default_options' => isset($settings['importers'][$importer_name]) ? $settings['importers'][$importer_name] : array(),
    );
  }
  $form['plugins'] = array(
    '#type' => 'fieldset',
    '#title' => t('Plugins'),
    '#tree' => TRUE,
  );
  $plugins = feeds_tamper_get_plugins();
  $options = array();
  foreach ($plugins as $key => $plugin) {
    $options[$key] = $plugin['name'];
  }
  $k = array_keys($options);
  $form['plugins']['type'] = array(
    '#tree' => TRUE,
    '#title' => 'The plugin to add',
    '#type' => 'radios',
    '#options' => $options,
    '#default_value' => $k[0],
  );
  foreach ($plugins as $key => $plugin) {
    $plugin_form = $plugin['form'];
    $tmp_form = $plugin_form();
    foreach ($tmp_form as &$tmp_form_item) {
      $tmp_form_item['#process'] = array('ctools_dependent_process');
      $tmp_form_item['#dependency'] = array('radio:plugins[type]' => array($key));
      $tmp_form_item['#required'] = FALSE;
    }
    $form['plugins'][$key] = $tmp_form;
  }

  $form['add_plugin'] = array(
    '#type' => 'button',
    '#value' => 'Add',
  );

  $data = isset($settings['plugins']) ? $settings['plugins'] : array();
  $form['list']['#tree'] = TRUE;
  $form['list']['#theme'] = 'feeds_tamper_list_sort_form';
  foreach ($data as $key => $title) {
    $t = array_keys($title);
    $title = $t[0];
    $form['list'][$key]['title'] = array('#value' => $title);
    $form['list'][$key]['sort'] = array('#type' => 'weight', '#delta' => count($data), '#default_value' => $key);
  }
}

/**
* Submit handler for the preset edit form.
*/
function feeds_tamper_ctools_export_ui_form_submit($form, &$form_state) {
}

function theme_feeds_tamper_list_sort_form($form) {
  if (count(element_children($form)) == 0) {
    return;
  }
  drupal_add_tabledrag('feeds-tamper-sort', 'order', 'sibling', 'sort');
  $header = array('', 'title', 'sort');
  foreach (element_children($form) as $key) {
    // Add class to group weight fields for drag and drop.
    $form[$key]['sort']['#attributes']['class'] = 'sort';

    $row = array(''); //This is important. We need to start with an empty element for the drag handle.

    $row[] = drupal_render($form[$key]['title']);
    $row[] = drupal_render($form[$key]['sort']);
    $rows[] = array('data' => $row, 'class' => 'draggable'); //note the difference between $row and $rows
  }
  $output = theme('table', $header, $rows, array('id' => 'feeds-tamper-sort'));
  $output .= drupal_render($form);
  return $output;
}

function feeds_tamper_parse_mappers($importer_name) {
  $mappings_ = feeds_importer($importer_name)->processor->getMappings();
  $mappings = array();
  foreach ($mappings_ as $mapping) {
    $mappings[$mapping['source']] = $mapping['target'];
  }
  return $mappings;
}

function feeds_tamper_ctools_export_ui_form_validate(&$form, &$form_state) {
  $plugins = $form_state['values']['plugins'];
  $type = $plugins['type'];
  $values = $plugins[$type];
  if (!isset($form_state['item']->feeds_tamper_wrapper)) {
    $form_state['item']->feeds_tamper_wrapper = array();
  }
  $form_state['item']->feeds_tamper_wrapper['plugins'][] = array($type => $values);
}
