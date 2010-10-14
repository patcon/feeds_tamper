<?php
// $Id$

$plugin = array(
  'form' => 'feeds_tamper_explode_form',
  'callback' => 'feeds_tamper_explode_callback',
  'name' => 'Explode',
);

function feeds_tamper_explode_form() {
  $form = array();

  $form['separator'] = array(
    '#type' => 'textfield',
    '#title' => t('String separator'),
    '#default_value' => ',',
    '#description' => t('This will break up sequenced data into an array. For example, "a, b, c" would get broken up into the array(\'a\', \'b\', \'c\').
                        A space can be represented by %s, tabs by %t, and newlines by %n.'),
  );

  return $form;
}

function feeds_tamper_explode_callback($source, &$item, &$field, $values) {
  if (!is_array($field)) {
    $separator = str_replace(array('%s', '%t', '%n'), array(' ', "\t", "\n"), $values['separator']);
    $field = explode($separator, $field);
  }
}
