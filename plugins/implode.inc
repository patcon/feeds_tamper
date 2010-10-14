<?php
// $Id$

$plugin = array(
  'form' => 'feeds_tamper_implode_form',
  'callback' => 'feeds_tamper_implode_callback',
  'name' => 'Explode',
);

function feeds_tamper_implode_form() {
  $form = array();

  $form['glue'] = array(
    '#type' => 'textfield',
    '#title' => t('String glue'),
    '#default_value' => ',',
    '#description' => t('Join array elements into a string. For example, array(\'a\', \'b\', \'c\') would become "a, b, c".
                        A space can be represented by %s, tabs by %t, and newlines by %n.'),
  );

  return $form;
}

function feeds_tamper_implode_callback($source, &$item, &$field, $values) {
  if (is_array($field)) {
    $glue = str_replace(array('%s', '%t', '%n'), array(' ', "\t", "\n"), $values['glue']);
    $field = implode($glue, $field);
  }
}
