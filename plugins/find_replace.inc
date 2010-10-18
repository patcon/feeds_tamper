<?php
// $Id$

$plugin = array(
  'form' => 'feeds_tamper_find_replace_form',
  'callback' => 'feeds_tamper_find_replace_callback',
  'name' => 'Find Replace',
);

function feeds_tamper_find_replace_form($settings) {
  $form = array();

  $form['find'] = array(
    '#type' => 'textfield',
    '#title' => t('Text to find'),
    '#default_value' => isset($settings['find']) ? $settings['find'] : '',
  );

  $form['replace'] = array(
    '#type' => 'textfield',
    '#title' => t('Text to replace'),
    '#default_value' => isset($settings['replace']) ? $settings['replace'] : '',
  );
  return $form;
}

function feeds_tamper_find_replace_callback($source, &$key, &$field, $values) {
  $field = str_replace($values['find'], $values['replace'], $field);
}
