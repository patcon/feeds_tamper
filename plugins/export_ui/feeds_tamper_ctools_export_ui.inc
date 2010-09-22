<?php
// $Id$

$plugin = array(
  // The name of the table as found in the schema in hook_install. This
  // must be an exportable type with the 'export' section defined.
  'schema' => 'feeds_tamper',

  // The access permission to use. If not provided it will default to
  // 'administer site configuration'
  'access' => 'administer feeds_tamper',

  // You can actually define large chunks of the menu system here. Nothing
  // is required here. If you leave out the values, the prefix will default
  // to admin/build and the item will default to the plugin name.
  'menu' => array(
    'menu prefix' => 'admin/build',
    'menu item' => 'feeds_tamper',
    // Title of the top level menu. Note this should not be translated,
    // as the menu system will translate it.
    'menu title' => 'Feeds Tamper',
    // Description of the top level menu, which is usually needed for
    // menu items in an administration list. Will be translated
    // by the menu system.
    'menu description' => 'Feeds Tamper Configuration.',
  ),

  // These are required to provide proper strings for referring to the
  // actual type of exportable. "proper" means it will appear at the
  // beginning of a sentence.
  'title singular' => t('tamper set'),
  'title singular proper' => t('Tamper set'),
  'title plural' => t('Tamper sets'),
  'title plural proper' => t('Tamper sets'),

  // This will provide you with a form for editing the properties on your
  // exportable, with validate and submit handler.
  //
  // The item being edited will be in $form_state['item'].
  //
  // The submit handler is only responsible for moving data from
  // $form_state['values'] to $form_state['item'].
  //
  // All callbacks will accept &$form and &$form_state as arguments.
  'form' => array(
    'settings' => 'feeds_tamper_ctools_export_ui_form',
    //'validate' => 'feeds_tamper_ctools_export_ui_form_validate',
    //'submit' => 'feeds_tamper_ctools_export_ui_form_submit',
  ),
);

/**
* Define the preset add/edit form.
*/
function feeds_tamper_ctools_export_ui_form(&$form, &$form_state) {
  $preset = $form_state['item'];

  $importers = feeds_enabled_importers();

  $form['importer'] = array(
    '#type' => 'checkboxes',
    '#options' => array_combine($importers, $importers),
    '#title' => t('Importers'),
  );

  $data = array(
            0 => 'First One',
            1 => 'Another One',
            2 => 'Some One',
          );

  $form['list']['#tree'] = TRUE;
  $form['list']['#theme'] = 'feeds_tamper_list_sort_form';
  foreach ($data as $key => $title) {
    $form['list'][$key]['title'] = array('#value' => $title);
    $form['list'][$key]['sort'] = array('#type' => 'weight', '#delta' => count($data), '#default_value' => $key);
  }

  $plugins = feeds_tamper_get_plugins();
  $options = array();
  foreach ($plugins as $key => $plugin) {
    $options[$key] = $plugin['name'];
  }
  $form['plugin'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => 'The plugin to add',
  );
  ctools_include('modal');
  ctools_modal_add_js();

  $form['link']['#value'] = l('Configure', 'admin/build/feeds_tamper/nojs/plugins/test', array(
    'attributes' => array('class' => 'ctools-use-modal')));
}

/**
* Submit handler for the preset edit form.
*/
function feeds_tamper_ctools_export_ui_form_submit($form, &$form_state) {
}

function theme_feeds_tamper_list_sort_form($form) {
  drupal_add_tabledrag('feeds-tamper-sort', 'order', 'sibling', 'sort');
  $header = array('', 'title', 'sort');
  foreach (element_children($form) as $key) {
    // Add class to group weight fields for drag and drop.
    $form[$key]['sort']['#attributes']['class'] = 'sort';

    $row = array(''); //This is important. We need to start with an empty element for the drag handle.

    $row[] = drupal_render($form[$key]['title']);
    $row[] = drupal_render($form[$key]['sort']);
    $rows[] = array('data' => $row, 'class' => 'draggable'); //note the difference between $row and $rows
  }
  $output = theme('table', $header, $rows, array('id' => 'feeds-tamper-sort'));
  $output .= drupal_render($form);
  return $output;
}
