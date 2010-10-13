<?php
// $Id$

$plugin = array(
  'form' => 'feeds_tamper_keyword_filter_form',
  'callback' => 'feeds_tamper_keyword_filter_callback',
  'name' => 'Keyword Filter',
);

function feeds_tamper_keyword_filter_form() {
  $form = array();

  $form['word'] = array(
    '#type' => 'textfield',
    '#title' => t('Word to filter on'),
    '#default_value' => '',
  );

  $form['word_boundaries'] = array(
    '#type' => 'checkbox',
    '#title' => t('Respect word boundaries'),
    '#default_value' => TRUE,
  );

  $form['case_sensetive'] = array(
    '#type' => 'checkbox',
    '#title' => t('Case sensetive'),
    '#default_value' => FALSE,
  );

  return $form;
}

function feeds_tamper_keyword_filter_callback(&$item, &$text, $values) {
  if ($values['word_boundaries']) {
    $regex = '/\b' . $values['word'] . '\b/';
  }
  else {
    $regex = '/' . $values['word'] . '/';
  }
  if (!$values['case_sensetive']) {
    $regex .= 'i';
  }

  $match = preg_match($regex, $text);

  if ($match === 0) {
    $item = NULL;
  }
}
