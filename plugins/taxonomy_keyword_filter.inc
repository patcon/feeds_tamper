<?php
// $Id$
if (module_exists('taxonomy')) {
  $plugin = array(
    'form' => 'feeds_tamper_taxonomy_keyword_filter_form',
    'callback' => 'feeds_tamper_taxonomy_keyword_filter_callback',
    'validate' => 'feeds_tamper_taxonomy_keyword_filter_validate',
    'name' => 'Keyword Filter by Vocabulary',
  );
}

function feeds_tamper_taxonomy_keyword_filter_form($settings) {
  $form = array();

  $tax = taxonomy_get_vocabularies();
  $tax_options = array();

  foreach ($tax as $t) {
    $tax_options[$t->vid] = $t->name;
  }

  $form['t'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['t']['vocabularies'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Vocabularies to use'),
    '#description' => t('Words from these vocabularies will be used to filter against.'),
    '#options' => $tax_options,
    '#default_value' => isset($settings['t']['vocabularies']) ? $settings['t']['vocabularies'] : array(),
  );

  $form['synonyms'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use synonyms'),
    '#default_value' => isset($settings['synonyms']) ? $settings['synonyms'] : TRUE,
    '#description' => t('If checked, then synonyms of a term will be added.'),
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

function feeds_tamper_taxonomy_keyword_filter_validate(&$values) {
  $values['strpos'] = FALSE;
  $values['stripos'] = FALSE;
  $values['regex'] = FALSE;

  if (!$values['word_boundaries'] && $values['case_sensetive']) {
    $values['strpos'] = TRUE;
  }

  else if (!$values['word_boundaries'] && !$values['case_sensetive']) {
    $values['stripos'] = TRUE;
  }
  
  else {
    $values['regex'] = TRUE;
  }
}


function feeds_tamper_taxonomy_keyword_filter_callback($source, $key, &$field, $values) {
  static $words = NULL;
  if (!$words) {
    $words = array();
    foreach ($values['t']['vocabularies'] as $vid) {
      foreach (taxonomy_get_tree($vid) as $term) {
        $word_array = array();
        if ($values['synonyms']) {
          $word_array = taxonomy_get_synonyms($term->tid);
        }
        $word_array[] = $term->name;
        foreach ($word_array as $word) {
          if ($values['regex']) {
            $word = '/\b' . $word . '\b/';
            if (!$values['case_sensetive']) {
              $word .= 'i';
            }
          }
          $words[] = $word;
        }
      }
    }
  }

  if (!is_array($field)) {
    if ($values['regex']) {
      foreach ($words as $word) {
        if (preg_match($word, $field) > 0) {
          return;
        }
      }
    }
    else if ($values['strpos']) {
      foreach ($words as $word) {
        if (strpos($field, $word) !== FALSE) {
          return;
        }
      }
    }
    else {
      foreach ($words as $word) {
        if (stripos($field, $word) !== FALSE) {
          return;
        }
      }
    }
    unset($source->batch->items[$key]);
  }
}
