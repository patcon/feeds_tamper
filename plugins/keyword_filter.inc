<?php
// $Id$

$plugin = array(
  'form'     => 'feeds_tamper_keyword_filter_form',
  'callback' => 'feeds_tamper_keyword_filter_callback',
  'validate' => 'feeds_tamper_keyword_filter_validate',
  'name'     => 'Keyword Filter',
  'multi'    => 'skip',
);

function feeds_tamper_keyword_filter_form($settings) {

  $form = array();

  $form['words'] = array(
    '#type' => 'textarea',
    '#title' => t('Word to filter on'),
    '#default_value' => isset($settings['words']) ? $settings['words'] : '',
    '#description' => t('A list of words that to appear in the text.'),
  );

  $form['word_boundaries'] = array(
    '#type' => 'checkbox',
    '#title' => t('Respect word boundaries'),
    '#default_value' => isset($settings['word_boundaries']) ? $settings['word_boundaries'] : TRUE,
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

function feeds_tamper_keyword_filter_validate(&$values) {
  $values['word_list'] = explode("\n", $values['words']);
  $values['word_list'] = array_map('trim', $values['word_list']);

  $values['regex'] = FALSE;

  if (!$values['word_boundaries'] && $values['case_sensetive']) {
    $values['func'] = 'strpos';
  }

  else if (!$values['word_boundaries'] && !$values['case_sensetive']) {
    $values['func'] = 'stripos';
  }
  else {
    foreach ($values['word_list'] as &$word) {
      $word = '/\b' . $word . '\b/';

      if (!$values['case_sensetive']) {
        $word .= 'i';
      }
    }
    $values['regex'] = TRUE;
  }
}

function feeds_tamper_keyword_filter_callback($source, $item_key, $element_key, &$field, $values) {
  if ($values['regex']) {
    foreach ($values['word_list'] as $word) {
      if (preg_match($word, $field) > 0) {
        return;
      }
    }
  }
  else {
    foreach ($values['word_list'] as $word) {
      if ($values['func']($field, $word) !== FALSE) {
        return;
      }
    }
  }
  unset($source->batch->items[$item_key]);
}
