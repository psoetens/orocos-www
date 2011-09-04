/**
 * @file
 * Javascript functions for imagepicker_postlet module
 *
 * @Author Bob Hutchinson
*/

// Global killswitch
if (Drupal.jsEnabled) {
  $(document).ready( function() {
    //wrap_imagepicker_postlet_role
    if ($("#edit-imagepicker-postlet-byrole").attr('checked')) {
      $("#wrap_imagepicker_postlet_role").show();
    }
    else {
      $("#wrap_imagepicker_postlet_role").hide();
    }

    $("#edit-imagepicker-postlet-byrole").change(function() {
      if ($("#edit-imagepicker-postlet-byrole").attr('checked')) {
        $("#wrap_imagepicker_postlet_role").show();
      }
      else {
        $("#wrap_imagepicker_postlet_role").hide();
      }
    });
  });
}
