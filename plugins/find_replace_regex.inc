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

  $form['limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Limit number of replacements'),
    '#default_value' => '0',
    '#description' => t('This sets an optional limit. 0 means no limit.'),
  );

  return $form;
}

function feeds_tamper_find_replace_regex_callback($source, &$item, &$field, $values) {
  if (!is_array($field)) {
    $limit = (int) trim($values['limit']);
    $limit = $limit ?: 0;
    $field = preg_replace($values['find_regex'], $values['replace_regex'], $field, $limit);
  }
}
