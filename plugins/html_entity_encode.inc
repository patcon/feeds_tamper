<?php
// $Id$

$plugin = array(
  'form'     => 'feeds_tamper_html_entity_encode_form',
  'callback' => 'feeds_tamper_html_entity_encode_callback',
  'name'     => 'HTML entitiy encode',
  'multi'    => 'loop',
);

function feeds_tamper_html_entity_encode_form($settings) {
  $form = array();

  $form['html'] = array(
    '#value' => t('This will convert all HTML special characters such as &gt; and &amp; to &amp;gt; and &amp;apm;.')
  );

  return $form;
}

function feeds_tamper_html_entity_encode_callback($source, $item_key, $element_key, &$field, $values) {
  $field = check_plain($field);
}
