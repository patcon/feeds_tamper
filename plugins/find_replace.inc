<?php
// $Id$

$plugin = array(
  'form' => 'feeds_tamper_find_replace_form',
  'callback' => 'feeds_tamper_find_replace_callback',
  'name' => 'Find Replace',
);

function feeds_tamper_find_replace_form() {
  $form = array();
  $form['find'] = array(
    '#type' => 'textfield',
    '#title' => t('Text to find'),
    '#required' => TRUE,
    '#default_value' => '',
          '#process' => array('ctools_dependent_process'),
      '#dependency' => array('radio:type' => array('find_replace')),
  );
  $form['replace'] = array(
    '#type' => 'textfield',
    '#title' => t('Text to replace'),
    '#default_value' => '',
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array('radio:type' => array('find_replace')),
  );
  //$form['add'] = array(
  //  '#type' => 'submit',
  //  '#value' => 'Add',
  //);
  return $form;
}

function feeds_tamper_find_replace_form_submit($form_state) {

}

function feeds_tamper_find_replace_callback($text, $values) {
  return str_replace($values['find'], $values['replace'], $text);
}
