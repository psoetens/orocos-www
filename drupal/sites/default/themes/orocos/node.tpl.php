  <div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
    <?php if ($picture) {
      print $picture;
    }?>
    <?php if ($page == 0) { ?><h2 class="title"><a href="<?php print $node_url?>"><?php print $title?></a></h2><?php }; ?>
    <table border="0" cellpadding="0" cellspacing="0" id="nodeinfo" width="100%"><tr>
      <td><span class="submitted"><?php print $submitted?></span></td>
      <td align="right"><span class="taxonomy"><?php print $terms?></span></td>
    </tr></table>
    <div class="content"><?php print $content?></div>
    <?php if ($links) { ?><div class="links">&raquo; <?php print $links?></div><?php }; ?>
  </div>
