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

  $form['word_boundaries'] = array(
    '#type' => 'checkbox',
    '#title' => t('Respect word boundaries'),
    '#default_value' => isset($settings['word_boundaries']) ? $settings['word_boundaries'] : FALSE,
    '#description' => t('If checked, then "book" will match "book" but not "bookcase".'),
  );

  $form['case_sensetive'] = array(
    '#type' => 'checkbox',
    '#title' => t('Case sensetive'),
    '#default_value' => isset($settings['case_sensetive']) ? $settings['case_sensetive'] : FALSE,
    '#description' => t('If checked, then "book" will match "book" but not "Book" or "BOOK".')
  );

  return $form;
}

function feeds_tamper_find_replace_validate(&$values) {
  $values['str_replace'] = FALSE;
  $values['str_ireplace'] = FALSE;

  if (!$values['word_boundaries'] && $values['case_sensetive']) {
    $values['str_replace'] = TRUE;
    return;
  }

  if (!$values['word_boundaries'] && !$values['case_sensetive']) {
    $values['str_ireplace'] = TRUE;
    return;
  }

  $regex = '/\b' . $values['find'] . '\b/';

  if (!$values['case_sensetive']) {
    $regex .= 'i';
  }

  $values['regex_find'] = $regex;
}

function feeds_tamper_find_replace_callback($source, $key, &$field, $values) {
  if ($values['str_replace']) {
    $field = str_replace($values['find'], $values['replace'], $field);
  }

  else if ($values['str_ireplace']) {
    $field = str_ireplace($values['find'], $values['replace'], $field);
  }

  else {
    $field = preg_replace($values['regex_find'], $values['replace'], $field);
  }
}
