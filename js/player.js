jQuery(document).ready(function() {

  jwplayer("mediaplayer").setup({
    flashplayer: Drupal.settings.islandora_jwplayer.jwpath + "/player.swf",
    file: Drupal.settings.islandora_jwplayer.url,
//    type: "audio", // forced to audio mode
    type: Drupal.settings.islandora_jwplayer.mimetype.split("/")[0], // automatic audio/video detection
    image: Drupal.settings.islandora_jwplayer.thumbnail,
    controlbar: "bottom"
  });
});
