<?php
// $Id$

function feeds_tamper_admin_form($form_state) {
  $form = array();

  if (!isset($form_state['storage']['step'])) {
    $form_state['storage']['step'] = 1;
  }

  switch ($form_state['storage']['step']) {
    case 1:
      $importers = feeds_enabled_importers();

      $form['importer'] = array(
        '#type' => 'select',
        '#options' => array_combine($importers, $importers),
        '#title' => t('Importer'),
      );

      $form['next'] = array(
        '#type' => 'submit',
        '#value' => t('Next'),
      );
      break;
    case 2:
      
      break;
    case 3:
      $plugins = feeds_tamper_get_plugins();
      $options = array();
      foreach ($plugins as $key => $plugin) {
        $options[$key] = $plugin['name'];
      }
      $form['plugin'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#title' => 'The plugin to configure',
      );
      break;
  }

  if ($form_state['storage']['step'] > 1) {
    $form['previous'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
    );
  }

  return $form;
}

function feeds_tamper_admin_form_submit($form, &$form_state) {
  if (!isset($form_state['storage']['values'])) {
    $form_state['storage']['values'] = array();
  }

  $form_state['storage']['values'] += $form_state['values'];

  if ($form_state['clicked_button']['#id'] == 'edit-previous') {
    $form_state['storage']['step']--;
  }
  elseif ($form_state['clicked_button']['#id'] == 'edit-next') {
    $form_state['storage']['step']++;
  }

  $form_state['rebuild'] = TRUE;
}
