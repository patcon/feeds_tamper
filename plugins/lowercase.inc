<?php
// $Id$

$plugin = array(
  'form'     => 'feeds_tamper_lowercase_form',
  'callback' => 'feeds_tamper_lowercase_callback',
  'name'     => 'Lowercase',
  'multi'    => 'loop',
);

function feeds_tamper_lowercase_form($settings) {
  $form = array();

  $form['help_text'] = array(
    '#value' => t('Will turn every letter in the string or array to lowercase.'),
  );

  return $form;
}

function feeds_tamper_lowercase_callback($source, $item_key, $element_key, &$field, $values) {
  $field = strtolower($field);
}
