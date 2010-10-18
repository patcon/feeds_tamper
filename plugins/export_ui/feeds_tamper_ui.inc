<?php
// $Id$

$plugin = array(
  'schema' => 'feeds_tamper_instance',
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
    'settings' => 'feeds_tamper_add_plugin_form',
    'validate' => 'feeds_tamper_add_plugin_form_validate',
    'submit' => 'feeds_tamper_add_plugin_form_submit',
  ),
);

function feeds_tamper_add_plugin_form(&$form, &$form_state) {
  $instance = $form_state['item'];
  $instance->settings = $instance->settings ?: array();
  $feeds_tamper_plugins = feeds_tamper_get_plugins();


  $plugins = array();
  foreach ($feeds_tamper_plugins as $plugin_id => $plugin) {
    $plugins[$plugin_id] = $plugin['name'];
  }
  $plugin = $instance->plugin_id ?: key($plugins);

  $form['plugin_id'] = array(
    '#title' => 'The plugin to add',
    '#type' => 'select',
    '#options' => $plugins,
    '#default_value' => $plugin,
    '#tree' => TRUE,
  );

  ctools_include('dependent');
  foreach ($feeds_tamper_plugins as $machine_name => $plugin) {
    $i = str_replace('_', '-', $machine_name);
    $form['plugin_forms'][$machine_name] = array(
      '#title' => t('Configure ' . $plugin['name']),
      '#tree' => TRUE,
      '#type' => 'fieldset',
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array('edit-plugin-id' => array($machine_name)),
      '#input' => TRUE,
      '#prefix' => '<div id="edit-'. $i .'-wrapper"><div id="edit-'. $i .'">',
      '#suffix' => '</div></div>'

    );
    foreach ($plugin['form']($instance->settings) as $key => $form_item) {
      $form['plugin_forms'][$machine_name][$key] = $form_item;
    }
  }

}

function feeds_tamper_add_plugin_form_submit(&$form, &$form_state) {
  $plugin_id = $form_state['values']['plugin_id'];
  $form_state['item']->settings = $form_state['values'][$plugin_id];
}

function feeds_tamper_add_plugin_form_validate(&$form, &$form_state) {
}
