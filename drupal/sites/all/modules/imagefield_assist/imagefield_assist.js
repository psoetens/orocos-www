/* $Id: imagefield_assist.js,v 1.1 2009/07/03 12:53:49 lourenzo Exp $ */

Drupal.behaviors.imagefield_assist = function(context) {
  $('textarea.imagefield_assist:not(.imagefield_assist-processed)', context).each(function() {
    // Drupal's teaser behavior is a destructive one and needs to be run first.
    if ($(this).is('textarea.teaser:not(.teaser-processed)')) {
      Drupal.behaviors.teaser(context);  
    }
    $(this).addClass('imagefield_assist-processed').parent().append(Drupal.theme('imagefield_assist_link', this));
  });
}

Drupal.theme.prototype.imagefield_assist_link = function(el) {
  var html = '<div class="imagefield_assist-button">', link = Drupal.t('Add image');
  if (Drupal.settings.imagefield_assist.link == 'icon') {
    link = '<img src="'+ Drupal.settings.basePath + Drupal.settings.imagefield_assist.icon +'" alt="'+ link +'" title="'+ link +'" />';
  }
  html += '<a href="'+ Drupal.settings.basePath +'index.php?q=imagefield_assist/load/textarea&textarea='+ el.name +'" class="imagefield_assist-link" id="imagefield_assist-link-'+ el.id +'" title="'+ Drupal.t('Click here to add images') +'" onclick="window.open(this.href, \'imagefield_assist_link\', \'width=600,height=350,scrollbars=yes,status=yes,resizable=yes,toolbar=no,menubar=no\'); return false;">'+ link +'</a>';
  html += '</div>';
  return html;
}

function launch_popup(nid, mw, mh) {
  var ox = mw;
  var oy = mh;
  if((ox>=screen.width) || (oy>=screen.height)) {
    var ox = screen.width-150;
    var oy = screen.height-150;
    var winx = (screen.width / 2)-(ox / 2);
    var winy = (screen.height / 2)-(oy / 2);
    var use_scrollbars = 1;
  }
  else {
    var winx = (screen.width / 2)-(ox / 2);
    var winy = (screen.height / 2)-(oy / 2);
    var use_scrollbars = 0;
  }
  var win = window.open(Drupal.settings.basePath + 'index.php?q=imagefield_assist/popup/' + nid, 'imagev', 'height='+oy+'-10,width='+ox+',top='+winy+',left='+winx+',scrollbars='+use_scrollbars+',resizable');
}

