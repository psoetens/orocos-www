<?php

class Text_Wiki_Parse_Ignoretag extends Text_Wiki_Parse {

  function Text_Wiki_Parse_Ignoretag(&$obj) {
    global $pearwiki_current_format;
    $this->regex = '/<('.implode('|',explode(' ',pearwiki_filter_ignore_tags($pearwiki_current_format))).')(\s[^>]*)?(>(.*)<\/\1>|\/>)/Ums';
    $this->Text_Wiki_Parse($obj);
  }

  function process(&$matches)
  {
    $options = array('text' => $matches[0]);
    return $this->wiki->addToken($this->rule, $options);
  }
}
