<?php
// $Id$

$plugin = array(
  'form'     => 'feeds_tamper_rewrite_form',
  'callback' => 'feeds_tamper_rewrite_callback',
  'validate' => 'feeds_tamper_rewrite_validate',
  'name'     => 'Rewrite',
  'multi'    => 'skip',
  'allowed'  => 'feeds_tamper_rewrite_allowed',
  'category' => 'Other',
);

function feeds_tamper_rewrite_form($settings) {
  $form = array();

  $importers = feeds_importer_load_all();
  $options = array_keys($importers);
  $options = array_combine($options, $options);

  $form['importer'] = array(
    '#type' => 'select',
    '#title' => t('Importer'),
    '#options' => $options,
    '#default_value' => isset($settings['importer']) ? $settings['importer'] : array(),
  );

  ctools_include('dependent');
  foreach($importers as $importer_id => $importer) {
    $i = str_replace('_', '-', $importer_id);

    $form[$importer_id] = array(
      '#type' => 'fieldset',
      '#title' => t('Fields for '. $importer_id),
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array('edit-rewrite-importer' => array($importer_id)),
      '#input' => TRUE,
      '#prefix' => '<div id="edit-rewrite-'. $i .'-wrapper"><div id="edit-rewrite-'. $i .'">',
      '#suffix' => '</div></div>'
    );

    $mappings = $importer->processor->config['mappings'];
    $options = array();
    $replace = array();
    foreach ($mappings as $map) {
      $options[$map['source']] = $map['source'] . ' (' . $map['target'] . ')';
      $replace[] = '[' . $map['source'] . ']';
    }
    $replace = implode(', ', $replace);

    $form[$importer_id]['check'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Select which fields to rewrite'),
      '#options' => $options,
      '#default_value' => isset($settings[$importer_id]['check']) ? $settings[$importer_id]['check'] : array(),
    );

    foreach ($mappings as $map) {
      $form[$importer_id][$map['source']] = array(
        '#type' => 'textarea',
        '#title' => t($map['source'] . '(' . $map['target'] . ')'),
        '#default_value' => isset($settings[$importer_id][$map['source']]) ? $settings[$importer_id][$map['source']] : '',
      );
    }
    $form[$importer_id]['help'] = array(
      '#value' => t("The selected fields will be rewritten with the replacement values: $replace"),
    );
  }

  return $form;
}

function feeds_tamper_rewrite_validate(&$values) {
  $importer_id = $values['importer'];
  $values = $values[$importer_id];
  $values['check'] = array_filter($values['check']);
  $values = array('importer' => $importer_id, $importer_id => $values);
}

function feeds_tamper_rewrite_callback($source, $item_key, $element_key, &$field, $values) {
  $res = $values[$values['importer']][$element_key];
  $sources = $source->batch->items[$item_key];
  $trans = array();
  foreach ($sources as $key => $value) {
    $trans['[' . $key . ']'] = $value;
  }
  $field = strtr($res, $trans);
}

function feeds_tamper_rewrite_allowed($importer_id, $element_key, $values) {
  return $importer_id == $values['importer'] && isset($values[$importer_id]['check'][$element_key]);
}
