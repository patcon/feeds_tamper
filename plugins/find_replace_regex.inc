<?php
// $Id$

$plugin = array(
  'form' => 'feeds_tamper_find_replace_regex_form',
  'callback' => 'feeds_tamper_find_replace_regex_callback',
  'name' => 'Find Replace REGEX',
);

function feeds_tamper_find_replace_regex_form() {
  $form = array();
  $form['find_regex'] = array(
    '#type' => 'textfield',
    '#title' => t('REGEX to find'),
    '#default_value' => '',
  );
  $form['replace_regex'] = array(
    '#type' => 'textfield',
    '#title' => t('Replacement pattern'),
    '#default_value' => '',
  );
  return $form;
}

function feeds_tamper_find_replace_regex_callback($text, $values) {
  return str_replace($values['find'], $values['replace'], $text);
}
