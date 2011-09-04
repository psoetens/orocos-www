<?php

class Text_Wiki_Parse_Ignoreregexp extends Text_Wiki_Parse {

  function Text_Wiki_Parse_Ignoreregexp(&$obj) {
    global $pearwiki_current_format;
    $this->regex = pearwiki_filter_ignore_regexp($pearwiki_current_format);
    $this->Text_Wiki_Parse($obj);
  }

  var $regex = '/<($tags)(\s[^>]*)?>(.*)<\/\1>/Ums';

  function process(&$matches)
  {
    $options = array('text' => $matches[0]);
    return $this->wiki->addToken($this->rule, $options);
  }
}
