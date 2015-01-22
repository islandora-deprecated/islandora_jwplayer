<?php

/**
 * @file
 * drush integration for islandora_jwplayer.
 */

/**
 * The JWPlayer plugin URI.
 */
define('JWPLAYER_DOWNLOAD_URI', 'https://account.jwplayer.com/static/download/jwplayer-6.10.zip');

/**
 * Implements hook_drush_command().
 */
function islandora_jwplayer_drush_command() {
  $items = array();
  // The key in the $items array is the name of the command.
  $items['jwplayer-plugin'] = array(
    'callback' => 'drush_islandora_jwplayer_plugin',
    'description' => dt('Download and install the JWPlayer plugin.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'path' => dt('Optional. A path where to install the JWPlayer plugin. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('jwplayerplugin'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function islandora_jwplayer_drush_help($section) {
  switch ($section) {
    case 'drush:jwplayer-plugin':
      return dt('Download and install the JWPlayer plugin, default location is sites/all/libraries.');
  }
}

/**
 * Command to download the JWPlayer plugin.
 */
function drush_islandora_jwplayer_plugin() {
  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = 'sites/all/libraries';
  }

  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);

  // Download the zip archive.
  if ($filepath = drush_download_file(JWPLAYER_DOWNLOAD_URI)) {
    $filename = basename($filepath);
    $dirname = 'jwplayer';

    // Remove any existing JWPlayer plugin directory.
    if (is_dir($dirname) || is_dir('jwplayer')) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir('jwplayer', TRUE);
      drush_log(dt('A existing JWPlayer plugin was deleted from @path', array('@path' => $path)), 'notice');
    }

    // Decompress the zip archive.
    drush_tarball_extract($filename);

    // Change the directory name to "jwplayer" if needed.
    if ($dirname != 'jwplayer') {
      drush_move_dir($dirname, 'jwplayer', TRUE);
      $dirname = 'jwplayer';
    }
  }

  if (is_dir($dirname)) {
    drush_log(dt('JWPlayer plugin has been installed in @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the JWPlayer plugin to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
}
