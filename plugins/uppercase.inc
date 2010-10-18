<?php
// $Id$

$plugin = array(
  'form' => 'feeds_tamper_uppercase_form',
  'callback' => 'feeds_tamper_uppercase_callback',
  'name' => 'Uppercase',
);

function feeds_tamper_uppercase_form($settings) {
  $form = array();

  $form['help_text'] = array(
    '#value' => t('Will turn every letter in the string or array to uppercase.'),
  );

  return $form;
}

function feeds_tamper_uppercase_callback($source, $key, &$field, $values) {
  if (!is_array($field)) {
    $field = strtoupper($field);
    return;
  }
  else {
    foreach ($field as &$f) {
      $f = strtoupper($f);
    }
  }
}
