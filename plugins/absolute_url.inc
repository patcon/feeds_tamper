<?php
// $Id$

$plugin = array(
  'form' => 'feeds_tamper_absolute_url_form',
  'callback' => 'feeds_tamper_absolute_url_callback',
  'name' => 'Keyword Filter',
);

function feeds_tamper_absolute_url_form() {
  $form = array();

  $form['info'] = array(
    '#value' => t('This plugin has no options.'),
  );

  return $form;
}

/**
 * @todo
 *   Make this not suck.
 */
function feeds_tamper_absolute_url_callback($source, &$item, &$field, $values) {
  $base_url = rtrim($source->batch->getLink(), '/') . '/';
  $regex = '/<.*(href|src)(\s*=\s*)(\'|")(.*)("|\').*>/';
  preg_match_all($regex, $item, $matches, PREG_SET_ORDER);
  foreach ($matches as $match) {
    if (!strpos($match[4], 'http://') === 0 && !strpos($match[4], 'https://') === 0) {
      $find_text = implode('', $match);
      $match[4] = $base_url . ltrim($match[4], '/');
      $replace_text = implode('', $match);
      $field = str_replace($find_text, $replace_text, $field);
    }
  }
}
