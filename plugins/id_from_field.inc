<?php
// $Id$

$plugin = array(
  'form'     => 'feeds_tamper_id_from_field_form',
  'callback' => 'feeds_tamper_id_from_field_callback',
  'name'     => 'Convert school code to uid',
  'category' => 'BioComp',
);

function feeds_tamper_id_from_field_form($settings) {
  $form = array();

  $form['info'] = array(
    '#value' => t('This plugin has no options.<br>'),
  );

  return $form;
}

/**
 * @todo
 *   Expand to include various CCK fields as inputs, and either nid or uid as output.
 */
function feeds_tamper_id_from_field_callback($source, $item_key, $element_key, &$field, $values) {
  $sql = "SELECT uid FROM {users} WHERE name = '%s'";
  $result = db_query($sql, $field);
  $field = $result ? db_result($result) : NULL;
}
