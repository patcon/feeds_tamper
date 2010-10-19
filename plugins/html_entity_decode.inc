<?php
// $Id$

$plugin = array(
  'form'     => 'feeds_tamper_html_entity_decode_form',
  'callback' => 'feeds_tamper_html_entity_decode_callback',
  'name'     => 'HTML entity decode',
  'multi'    => 'loop',
);

function feeds_tamper_html_entity_decode_form($settings) {
  $form = array();

  $form['html'] = array(
    '#value' => t('This will convert all HTML entities such as &amp;amp; and &amp;quot; to &amp; and &quot;.')
  );

  return $form;
}

function feeds_tamper_html_entity_decode_callback($source, $item_key, $element_key, &$field, $values) {
  $field = html_entity_decode($field, ENT_QUOTES, 'UTF-8');
}
