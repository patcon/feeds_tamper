<?php
// $Id$

$plugin = array(
  'form' => 'feeds_tamper_trim_form',
  'callback' => 'feeds_tamper_trim_callback',
  'validate' => 'feeds_tamper_trim_validate',
  'name' => 'Trim',
);

function feeds_tamper_trim_form($settings) {
  $form = array();

  $form['mask'] = array(
    '#type' => 'textfield',
    '#title' => t('Characters to trim'),
    '#default_value' => isset($settings['mask']) ? $settings['mask'] : '',
    '#description' => t('The characters to remove from the string. If blank, then whitespace will be removed.'),
  );

  $form['side'] = array(
    '#type' => 'radios',
    '#title' => t('Side'),
    '#default_value' => isset($settings['mask']) ? $settings['mask'] : 'trim',
    '#options' => array('trim' => t('Both'), 'ltrim' => t('Left'), 'rtrim' => t('Right')),
  );

  return $form;
}

function feeds_tamper_trim_callback($source, $key, &$field, $values) {
  if (is_array($field)) {
    foreach ($field as &$f) {
      $f = $values['side']($f, $values['mask']);
    }
  }
  else {
    $field = $values['side']($field, $values['mask']);
  }
}
