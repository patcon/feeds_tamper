<?php
// $Id$

$plugin = array(
  'form'     => 'feeds_tamper_find_replace_regex_form',
  'callback' => 'feeds_tamper_find_replace_regex_callback',
  'validate' => 'feeds_tamper_find_replace_regex_validate',
  'name'     => 'Find Replace REGEX',
  'multi'    => 'direct',
);

function feeds_tamper_find_replace_regex_form($settings) {
  $form = array();

  $form['find'] = array(
    '#type' => 'textfield',
    '#title' => t('REGEX to find'),
    '#default_value' => isset($settings['find']) ? $settings['find'] : '',
    '#description' => t(check_plain('A regular expression in the form: /<your regex here>/')),
  );

  $form['replace'] = array(
    '#type' => 'textfield',
    '#title' => t('Replacement pattern'),
    '#default_value' => isset($settings['replace']) ? $settings['replace'] : '',
    '#description' => t('The replacement pattern.'),
  );

  $form['limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Limit number of replacements'),
    '#default_value' => isset($settings['limit']) ? $settings['limit'] : 0,
    '#description' => t('This sets an optional limit. 0 means no limit.'),
  );

  return $form;
}

function feeds_tamper_find_replace_regex_validate(&$values) {
  // test the regex
  $test = @preg_replace($values['find'], '', 'asdfsadf');
  if ($test === NULL) {
    return form_set_error('find', 'Invalid regular expression.');
  }
  $values['limit'] = intval(trim($values['limit']));
}

function feeds_tamper_find_replace_regex_callback($source, $item_key, $element_key, &$field, $values) {
  $field = preg_replace($values['find'], $values['replace'], $field, $values['limit']);
}
