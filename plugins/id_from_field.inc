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
  $sql = "SELECT node.uid
    FROM {node} node
    LEFT JOIN {content_type_school} node_data_field_school_code ON node.vid = node_data_field_school_code.vid
    INNER JOIN {users} users ON node.uid = users.uid
    WHERE node_data_field_school_code.field_school_code_value = '%s'";
  $result = db_query($sql, $field);
  $field = db_results($result);
}
