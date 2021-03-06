<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language ?>" xml:lang="<?php print $language ?>">

<head>
  <title><?php print $head_title ?></title>
  <?php print $head ?>
  <?php print $styles ?>
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
</head>

<body>

<table border="0" cellpadding="0" cellspacing="0" id="header">
  <tr>
    <td id="logo">
      <?php if ($logo) { ?><a href="<?php print $base_path ?>" title="<?php print t('Home') ?>"><img src="<?php print $logo ?>" alt="<?php print t('Home') ?>" /></a><?php } ?>
      <?php if (preg_match("/rtt/i", drupal_get_path_alias($_GET['q'])) ) { ?>
          <h1 class='site-name'><a href="<?php print $base_path ?><?php print "rtt" ?>" title="<?php print t('RTT Home') ?>">Orocos Real-Time Toolkit</a></h1>
          <div class='site-slogan'><?php print "Smarter realtime. Safer threads" ?></div> 
      <?php } else if (preg_match("/kdl/i", drupal_get_path_alias($_GET['q'])) ) { ?>
          <h1 class='site-name'><a href="<?php print $base_path ?><?php print "kdl" ?>" title="<?php print t('KDL Home') ?>">Orocos Kinematics and Dynamics</a></h1>
          <div class='site-slogan'><?php print "Smarter in motion!" ?></div> 
      <?php } else if (preg_match("/bfl/i", drupal_get_path_alias($_GET['q'])) ) { ?>
          <h1 class='site-name'><a href="<?php print $base_path ?><?php print "bfl" ?>" title="<?php print t('BFL Home') ?>">Orocos Bayesian Filtering Library</a></h1>
          <div class='site-slogan'><?php print "Think smarter. Guess better!" ?></div> 
      <?php } else { ?>
          <?php if ($site_name) { ?><h1 class='site-name'><a href="<?php print $base_path ?>" title="<?php print t('Home') ?>"><?php print $site_name ?></a></h1><?php } ?>
      <?php if ($site_slogan) { ?><div class='site-slogan'><?php print $site_slogan ?></div><?php } ?>
    <?php } ?>
    <?php print $breadcrumb ?>
    </td>
    <td id="menu">
      <?php if (isset($secondary_links)) { ?><div id="secondary"><?php print theme('links', $secondary_links) ?></div><?php } ?>
      <?php if (isset($primary_links)) { ?><div id="primary"><?php print theme('links', $primary_links) ?></div><?php } ?>
      <?php print $search_box ?>
    </td>
  </tr>
  <tr>
    <td colspan="2" align="center">
    <div><?php print $header ?></div>
    </td>
    </tr>
</table>

<table border="0" cellpadding="0" cellspacing="0" id="content">
  <tr>
    <?php if ($sidebar_left) { ?><td id="sidebar-left">
      <?php print $sidebar_left ?>
    </td><?php } ?>
    <td valign="top">

        <?php print $messages ?>
	
	<?php if ($mission) { /* altered by PS to work around HTML stripping: http://drupal.org/node/57650 */
		$my_mission = theme_get_setting('mission');
        if ($my_mission != ""): ?>
     <div id="mission"><?php print $my_mission ?></div>
     <?php endif; } ?>

      <div id="main">
        <h1 class="title"><?php print $title ?></h1>
        <div class="tabs"><?php print $tabs ?></div>
        <?php print $help ?>
        <?php print $content; ?>
      </div>
    </td>
    <?php if ($sidebar_right) { ?><td id="sidebar-right">
      <?php print $sidebar_right ?>
    </td><?php } ?>
  </tr>
</table>

<div id="footer">
  <?php print $footer_message ?>
</div>
<?php print $closure ?>
</body>
</html>
