<?php
// $Id$

$plugin = array(
  'form'     => 'feeds_tamper_convert_date_form',
  'callback' => 'feeds_tamper_convert_date_callback',
  'name'     => 'Convert year to UNIX time',
  'category' => 'BioComp',
);

function feeds_tamper_convert_date_form($settings) {
  $form = array();

  $form['info'] = array(
    '#value' => t('This plugin has no options. It will convert year yyyy to the proper format for the database.<br>'),
  );

  return $form;
}

/**
 * @todo
 *   Expand to include various date conversions.
 */
function feeds_tamper_convert_date_callback($source, $item_key, $element_key, &$field, $values) {
  //
  $field = strtotime('May ' . $field);
}
