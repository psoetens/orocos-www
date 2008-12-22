<?php

class Text_Wiki_Parse_Ignoretoken extends Text_Wiki_Parse {

  function Text_Wiki_Parse_Ignoretoken(&$obj) {
    global $pearwiki_current_format;
    $this->regex = '/\[('.implode('|',explode(' ',pearwiki_filter_ignore_tokens($pearwiki_current_format))).')([^\]]*)?(\](.*)\[\/\1\]|\])/Ums';
    $this->Text_Wiki_Parse($obj);
  }

  function process(&$matches)
  {
    $options = array('text' => $matches[0]);
    return $this->wiki->addToken($this->rule, $options);
  }
}
