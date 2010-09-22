<?php
// $Id$

/**
 * @file
 * CTools plugins declarations.
 */

/**
 * Break out for feeds_tamper_feeds_tamper_plugins().
 */
function _feeds_tamper_feeds_tamper_plugins() {
  $path = drupal_get_path('module', 'feeds_tamper') .'/plugins';

  $info = array();
  $info['FeedsPlugin'] = array(
    'hidden' => TRUE,
    'handler' => array(
      'class' => 'FeedsPlugin',
      'file' => 'FeedsPlugin.inc',
      'path' => $path,
    ),
  );
  return $info;
}
