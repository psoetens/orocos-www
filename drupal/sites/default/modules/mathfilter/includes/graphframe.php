<?php
   /* We need to chdir to the root of the Drupal */
   /* install so includes, etc work properly     */
   /* when we bootstrap to work in a Drupal      */
   /* envronment.                                */
  /* We also need to do this before we send any */
  /* HTML                                       */
  
  // We need to determine which directory we are in.
  // We can be in:
  //   modules/mathfilter/graphframe 
  //        or
  //   sites/*/modules/mathfilter/graphframe
  
  // first assume the modules directory
   chdir("../../..");
  if (file_exists('includes/bootstrap.inc')) {
     include('includes/bootstrap.inc');
  
  // next assume the sites directory
  } else {
    chdir("../..");
    if (file_exists('includes/bootstrap.inc')) {
      include('includes/bootstrap.inc');
    }
  }
 
   drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
 
   /* graph size user defined */
   $size  = variable_get('mathfilter_dimension', '260');
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<meta http-equiv="cache-control" content="no-cache">
<meta http-equiv="cache-control" content="no-store">
<title>Iframe for Graphs</title>
</head>
<body style="margin: 0px; padding: 0px;">
<div id="fakegraphframe" style="position: relative; display: block; width: <?php echo $size ?>px; height: <?php echo $size ?>px; margin: 0px; padding: 0px;"></div>
<script type="text/javascript">
<?php  
if (array_key_exists('f', $_GET)) {
	$f = rawurldecode(ereg_replace('[?]*','',strip_tags($_GET['f'])));
} else {
	$f = 'null';
};      

if (array_key_exists('xmin', $_GET) && is_numeric($_GET['xmin'])) {
	$minx =  intval(ereg_replace('[?<>";]*','',strip_tags($_GET['xmin'])));
} else {
	$minx = -10;
};       

if (array_key_exists('xmax', $_GET) && is_numeric($_GET['xmax'])) {
	$maxx = intval(ereg_replace('[?<>";]*','',strip_tags($_GET['xmax'])));
} else {
	$maxx = 10;
};       

if (array_key_exists('ymax', $_GET) && is_numeric($_GET['ymax'])) {
	$maxy = intval(ereg_replace('[?<>";]*','',strip_tags($_GET['ymax'])));
} else {
	$maxy = 10;
};       

if (array_key_exists('ymin', $_GET) && is_numeric($_GET['ymin'])) {
	$miny = intval(ereg_replace('[?<>";]*','',strip_tags($_GET['ymin'])));
} else {
	$miny = -10;
};

if ($maxx <= $minx) {
	$minx = -10;
	$maxx = 10;
}

if ($maxy <= $miny) {
	$miny = -10;
	$maxy = 10;
}

 /* But WZ put in some hard coded numbers  */
 /* so we account for them here. These are */
 /* not adjusted because the font size is  */
 /* hardcoded as well.                     */
 $right    = 4;
 $left_top = 10;
 $bottom   = 22;

 /* This is the area where the curve will */
 /* be drawn.  So, we use the ratio that  */
 /* is the defaults in the js to start.   */
 $defw     = intval($size*(220/260));

 /* Now we make sure that these values */
 /* won't exceed our max size.  This   */
 /* equation is the pertinent one used */
 /* in WZ's js.                           */
 if (($defw + 1 + $right + 20) > $size) {
	 /* If it does, we take the excess off the */
	 /* largest part.                          */
	 $defw = $defw - ($defw + 1 + $right + 20 - $size);
}

?>
var DEFW   = <?php echo $defw; ?>;
var LEFT   = <?php echo $left_top; ?>;
var TOP    = <?php echo $left_top; ?>;
var RIGHT  = <?php echo $right; ?>;
var BOTTOM = <?php echo $bottom; ?>;
var fgraph = "<?php echo $f; ?>";
var g_xa = <?php echo $minx; ?>;
var g_xz = <?php echo $maxx; ?>;
var g_ya = <?php echo $miny; ?>;
var g_yz = <?php echo $maxy; ?>;    
</script>
<script type="text/javascript" src="../js/wz_grapherstr.js"></script>
<script type="text/javascript" src="../js/wz_grapher.js"></script>
<script type="text/javascript">
if (window.mkGraph) {
  window.setTimeout('mkGraph()', 500);
}
</script>
</body>
</html>
