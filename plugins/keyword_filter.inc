<?php
// $Id$

$plugin = array(
  'form' => 'feeds_tamper_keyword_filter_form',
  'callback' => 'feeds_tamper_keyword_filter_callback',
  'name' => 'Keyword Filter',
);

function feeds_tamper_keyword_filter_form($settings) {
  $form = array();

  $form['word'] = array(
    '#type' => 'textfield',
    '#title' => t('Word to filter on'),
    '#default_value' => isset($settings['word']) ? $settings['word'] : '',
  );

  $form['word_boundaries'] = array(
    '#type' => 'checkbox',
    '#title' => t('Respect word boundaries'),
    '#default_value' => isset($settings['word_boundaries']) ? $settings['word_boundaries'] : 1,
    '#attributes' => array('checked' => 'checked'),
  );

  $form['case_sensetive'] = array(
    '#type' => 'checkbox',
    '#title' => t('Case sensetive'),
    '#default_value' => isset($settings['case_sensetive']) ? $settings['case_sensetive'] : 0,
  );

  return $form;
}

function feeds_tamper_keyword_filter_callback($source, $key, &$field, $values) {
  if ($values['word_boundaries']) {
    $regex = '/\b' . $values['word'] . '\b/';
  }
  else {
    $regex = '/' . $values['word'] . '/';
  }
  if (!$values['case_sensetive']) {
    $regex .= 'i';
  }

  $match = preg_match($regex, $field);

  if ($match === 0) {
    unset($source->batch->items[$key]);
  }
}
