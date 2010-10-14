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
  'use wizard' => TRUE,
  'show trail' => FALSE,
  'free trail' => FALSE,
  'form info' => array(
    'add order' => array(
      'create' => t('Set Name'),
      'deploy' => t('Add plugins'),
    ),
    'edit order' => array(
      'deploy' => t('Edit'),
    ),
    'forms' => array(
      'deploy' => array('form id' => 'feeds_tamper_add_plugin_form'),
    ),
  ),
);

function feeds_tamper_add_plugin_form(&$form, &$form_state) {

  $preset = $form_state['item'];

  if ($list = $form_state['function args'][1]['list']) {
    $current_order = $preset->feeds_tamper_wrapper;
    $preset->feeds_tamper_wrapper = array();
    foreach ($list as $k => $p) {
      $preset->feeds_tamper_wrapper[] = $current_order[$k];
    }
  }

  if ($form_state['function args'][1]['op'] == 'Add') {
    $plugin_args = $form_state['function args'][1];
    $plugin = $form_state['function args'][1]['feeds_tamper_plugin'];
    unset($plugin_args['feeds_tamper_plugin'], $plugin_args['op'], $plugin_args['form_build_id'], $plugin_args['form_token'], $plugin_args['form_id']);
    unset($plugin_args['list']);
    $preset->feeds_tamper_wrapper[] = array($plugin => $plugin_args);
  }

  $settings = $preset->feeds_tamper_wrapper;
  $feeds_tamper_plugins = feeds_tamper_get_plugins();
  $options = array();

  foreach ($feeds_tamper_plugins as $key => $feeds_tamper_plugin) {
    $options[$key] = $feeds_tamper_plugin['name'];
  }

  $options = array_merge(array('--' => '--'), $options);
  $k = array_keys($options);
  $plugin = isset($form_state['function args'][1]['feeds_tamper_plugin']) ? $form_state['function args'][1]['feeds_tamper_plugin'] : $k[0];

  $form['feeds_tamper_plugin'] = array(
    '#title' => 'The plugin to add',
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => $plugin,
    '#attributes' => array('class' => 'ctools-auto-submit'),
  );

  $form['add_button'] = array(
    '#type' => 'submit',
    '#value' => '',
    '#attributes' => array('class' => 'ctools-use-ajax ctools-auto-submit-click',
                           'style' => 'display:none;'),
  );

  if ($plugin != '--') {
    $plugin = feeds_tamper_get_plugin($plugin);
    $tmp_form = $plugin['form']();
    $tmp_form['add'] = array(
      '#type' => 'submit',
      '#value' => 'Add',
      '#weight' => 100,
    );
  }
  else {
    $tmp_form = array();
    $tmp_form['#value'] = '--';
  }

  $form['feeds_tamper_plugin_form'] = $tmp_form;

  ctools_add_js('auto-submit');

  $data = isset($settings) ? $settings : array();

  $form['list']['#tree'] = TRUE;
  $form['list']['#theme'] = 'feeds_tamper_list_sort_form';

  foreach ($data as $key => $item) {
    $title = array_keys($item);
    $title = $title[0];
    $form['list'][$key] = array(
      'title' => array(
        '#type' => 'markup',
        '#value' => $title,
      ),
      'sort' => array(
        '#type' => 'weight',
        '#delta' => count($data),
        '#default_value' =>$key,
        '#attributes' => array('class' => 'feeds-tamper-sort-class')
      ),
      'plugin' => array(
        '#type' => 'hidden',
        '#value' => $title,
      ),
    );
  }
}

function feeds_tamper_add_plugin_form_submit(&$from, &$form_state) {
  ctools_export_ui_wizard_next($form_state);
}

function feeds_tamper_add_plugin_form_validate(&$from, &$form_state) {
}

function theme_feeds_tamper_list_sort_form($form) {
  if (count(element_children($form)) == 0) {
    return;
  }
  drupal_add_tabledrag('feeds-tamper-sort', 'order', 'sibling', 'feeds-tamper-sort-class');
  $header = array('', 'title', '');
  foreach (element_children($form) as $key) {

    $row = array('');
    $row[] = drupal_render($form[$key]['title']);
    $row[] = drupal_render($form[$key]['sort']);
    $rows[] = array('data' => $row, 'class' => 'draggable');
  }
  $output = theme('table', $header, $rows, array('id' => 'feeds-tamper-sort'));
  $output .= drupal_render($form);
  return $output;
}
