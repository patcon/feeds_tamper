<?php
// $Id$

$plugin = array(
  'form' => 'feeds_tamper_find_replace_form',
  'callback' => 'feeds_tamper_find_replace_callback',
  'name' => 'Find Replace',
);

function feeds_tamper_find_replace_form() {
  $form = array();

  $form['find'] = array(
    '#type' => 'textfield',
    '#title' => t('Text to find'),
    '#default_value' => '',
  );

  $form['replace'] = array(
    '#type' => 'textfield',
    '#title' => t('Text to replace'),
    '#default_value' => '',
  );

  return $form;
}

function feeds_tamper_find_replace_callback($source, &$item, &$field, $values) {
  $text = str_replace($values['find'], $values['replace'], $text);
}
