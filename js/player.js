jQuery(document).ready(function() {
  jwplayer("mediaplayer").setup({
    file: Drupal.settings.islandora_jwplayer.url,
    image: Drupal.settings.islandora_jwplayer.thumbnail,
    width: Drupal.settings.islandora_jwplayer.width,
  });
});