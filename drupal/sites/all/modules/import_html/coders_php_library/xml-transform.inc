<?php
/**
 * @file
 * Utility for formatting XML files using XSL. 
 *
 * Compliant with the different XML implimentations in PHP versions 4 & 5.
 * 
 * @package coders
 * @author Dan Morrison http://coders.co.nz/
 * @version $Id: xml-transform.inc,v 1.23.2.1 2007/02/20 12:30:40 dman Exp $
 */

/*
 * For debug routines, parameter passing and some output formatting
 */
if(defined("DEBUGLEVEL")){
  require_once("debug.inc");
}
// and may conditionally call file-routines and tidy-functions.inc
// but only when this library is actually used.
//  require_once("file-routines.inc");

/**
 * Load whichever XML support is available
 */
function init_xsl() {
  // Just loading this lib means we really want to have XML
  // OK, support both old & new PHP library ways of doing things ...
  if (!extension_loaded('xsl') && !extension_loaded('xslt')) {
    debug("Need to try and dynamically load XSL extension. Please do this properly on the server to avoid this message.");
    if (!@dl('xslt.so')&&!@dl('php_xslt.dll')&&!@dl('php_xsl.dll')) {
      trigger_error("No XSL library support at all on this server!" , E_USER_ERROR );
      return FALSE;
    }
    debug("Ready to use XSL on the server",2);
  }
  return TRUE;
}


/**
 * Try to load an xml doc from file, 
 *
 * Running tidy over the source first to override most parsing 
 * problems before they happen.
 * @parameter string Source filepath or URL
 * @parameter $do_tidy bool Whether to pre-process with HTMLTidy before parsing - ONLY do this with suspect HTML inout, not other XML sources.
 * @returns xmldoc
 */
function parse_in_xml_file($xmlfile,$do_tidy=0) {
  require_once("file-routines.inc");

  if(! file_exists($xmlfile)){
    trigger_error("File '$xmlfile' not found, cannot load XML source.",E_USER_WARNING);
    return false;
  }

  // Almost no content out there can be trusted to be valid :-(
  // I guess I'll tidy it myself before I attempt to parse it.
  if($do_tidy){
    include_once('tidy-functions.inc');
    if (! extension_loaded  ( "tidy" ) ){
      debug("Doing tidy via commandline",2);
      // No tidy module available. 
      // Old-school tidy must be run directly on the file, so do this first
      $xmlsource = xml_tidy_file($xmlfile);
    } else {
      debug("Doing tidy via PHP extension",2);
      $xmlsource = xml_tidy_string( file_get_contents($xmlfile) );
    }

    // Also Need to remove any php tags that may have had (they look like XML processing instructions)
    $xmlsource = tidy_strip_php($xmlsource);
    debug("<h3>File loaded, tidied, stripped ?php tags</h3>".debug_xml_source($xmlsource),3);
  } else {
    $xmlsource = file_get_contents($xmlfile);
  }

  if(! trim($xmlsource)) { trigger_error("Failed to read contents of '$xmlfile' ",E_USER_WARNING);return;}
  else { debug("Retrieved source of '$xmlfile' OK, it's ".strlen($xmlsource)." characters",3);}
  debug("<h3>After loading text</h3>".debug_xml_source($xmlsource),4);

  // If we force the source into the strict namespace, the XSL transformations 
  // (also in that namespace) SHOULD not litter the output with unwanted xmlns tags. 
  // so lets try and ensure the document knows that it's the right ns
  // $namespaceURI = "http://www.w3.org/TR/REC-html40";
  $namespaceURI = "http://www.w3.org/1999/xhtml"; // All XSL output should be this also, ok?

  // support PHP4 or 5 with their different xmls
  if ( extension_loaded( "dom" )) {
    ///////////
    // PHP 5 //
    $xmldoc = new DOMDocument; // DOM PHP5 version
    debug("Using PHP5 DOM extension to process XML",4);
 
    if (! $xmldoc->loadXML($xmlsource) ) {
      trigger_error("Failed to parse in xml source. [$xmlfile]",E_USER_WARNING);
      debug(debug_xml_source($xmlsource),1);
      return;
    }

    // Some files need to know where they came from (XSL includes)
    $xmldoc->documentURI = $xmlfile;
    
    // How to add namespaces in PHP5?

    debug_pre($xmldoc->saveXML(), 4);
    debug("XML source $xmlfile successfully loaded as an XML doc.",3);
    return $xmldoc;
  } 
  else if ( extension_loaded ( "domxml" )) {
    ///////////
    // PHP 4 //
    debug("Using older DOM_XML extension (PHP4) to process XML",2);
    if ( ! $xmldoc = domxml_open_mem($xmlsource) ) {
      trigger_error("Failed to parse in xml source. ",E_USER_WARNING);
      debug( "This source failed to be parsed as valid XML: (It probably needs to be tidied) ".debug_xml_source($xmlsource) ,2);
      return false;
    }

    if (is_callable(array($xmldoc,"document_object"))) {
      $d = $xmldoc->document_object(); // DOM XML PHP4 version
      $d->add_namespace( $namespaceURI,"" );
    } else if (is_callable(array($xmldoc,"root"))){
      $d = $xmldoc->root(); // DOM XML Old deprecated PHP4 version
    } else {debug("Odd, no root available to fix the namespace of. Which PHP/domxml version is this again?",3);}

    debug("XML source successfuly loaded as an XML doc.",1);
    debug("<h3>After loading as XML</h3>".debug_xml_source($xmldoc->dump_mem()),3);
    return $xmldoc; 
  } else {
    trigger_error("No known DOM XML support on this server at all - can't really do anything! We need to enable php module dom or domxml to parse web pages nicely");
    return false;
  }
}

function debug_xml_source($text) {
    return("<textarea rows='40' cols='80' wrap='none'>$text</textarea>");
}


/**
 * Version-safe string->xmldoc parser.
 * Convert a String to a DOM, via PHP4 or 5.
 * @parameter xmlsource $string Source XML
 * @parameter $do_tidy bool ONLY run HTMLTidy on HTML input, not once you already have XML source,
 * @returns xmldoc, or NULL if parse failed
 */
function parse_in_xml_string($xmlsource, $do_tidy=0) {
  if ($do_tidy){
    include_once('tidy-functions.inc');
    $xmlsource = xml_tidy_string($xmlsource);
  }

  init_xsl();
  // support PHP4 or 5 with their different xmls
  if ( extension_loaded  ( "dom" )) {
    ///////////
    // PHP 5 //
    $xmldoc = new DOMDocument;
    if($xmldoc->loadXML($xmlsource))
      return $xmldoc;
    return NULL;
    trigger_error('Problem parsing XML String'); 
  } 
  else if ( extension_loaded ( "domxml" )) {
    ///////////
    // PHP 4 //
    if($xmldoc = domxml_open_mem($xmlsource))
      return $xmldoc; 
    trigger_error('Problem parsing XML String'); 
    debug_pre($xmlsource);
    return NULL;
  } else {
    trigger_error("No known DOM XML support on this server at all - can't really do anything! We need to enable php module dom or domxml to parse web pages nicely");
    return false;
  }
}


/**
 * Do the actual conversion between XML+XSL
 *
 * Input and output are full DOM objects in PHP5
 * We return the result STRING, as that's what 
 * the process gives us :-/ 
 * Need to parse it back in again for pipelining.
 *
 * Painfully, the entire library support changed between PHP4 & 5.
 * We need to see if it's the "xsl" or the "xslt" library that's in use!
 *
 * @param DOMDocument or string $xmldoc 
 * @param DOMDocument or string $xsldoc . If it uses includes, the xsl must have
 * had its documentURI set correctly prior to this, but it can be set in the
 * parameters also. This may be mandatory for php4?
 * @param array $parameters To be passed into the xslt_process()
 * @returns string The result.
 */
function xmldoc_plus_xsldoc($xmldoc,$xsldoc,$parameters) {
  // OK, support both old & new PHP library ways of doing things ...
  init_xsl();

  if(extension_loaded("xsl")) {
    //////////
    // PHP5 //
    debug("Doing XSL using PHP5 xsl module. XSL base should be '".$parameters['xsl_path']."'",2);
    $xsltproc = new XSLTProcessor;

    if( $parameters['xsl_path']) $xsldoc->documentURI = $parameters['xsl_path'];
   
    $xsltproc->importStyleSheet($xsldoc); // attach the xsl rules
    // Set parameters when defined
    if ($parameters) {
       foreach ($parameters as $param => $value) {
         $xsltproc->setParameter("", $param, $value);
       }
    }
    return $xsltproc->transformToXML($xmldoc);
  }
  if(extension_loaded("xslt")) {
    //////////
    // PHP4 //
    debug("Doing XSL using PHP4 xslt module",3);
    $xsltproc = xslt_create();
    xslt_set_encoding($xsltproc, 'UTF-8');
    xslt_set_base( $xsltproc, $parameters['xsl_path']);
    debug("Set the XSLT processing base to ". $parameters['xsl_path'],3);

    // xslt_process can take text or sockets, but it's not accepting DomDocuments today.
    // If We are handed DOMs, flatten it out and stream it in. (Isn't that a waste?)
    $args = array();
    $args['/_xml'] = (is_callable(array($xmldoc,"dumpmem")))?$xmldoc->dump_mem():$xmldoc;
    $args['/_xsl'] = (is_callable(array($xsldoc,"dumpmem")))?$xsldoc->dump_mem():$xsldoc;
    debug("Calling xslt_process() with parameters:".print_r($parameters,1),3);


    xslt_set_error_handler($xsltproc, "xslt_error_handler");
    $out = @xslt_process($xsltproc, 'arg:/_xml', 'arg:/_xsl', NULL, $args, $parameters);
    if (empty($out)) {
      trigger_error('PHP4 XSLT processing error: '. xslt_error($xsltproc), E_USER_WARNING);
      debug("<h2>Adding this XML</h2>" . debug_xml_source($args['/_xml']) . "<h2>To this XSL</h2>" . debug_xml_source($args['/_xsl']) . "<h3>failed</h3>saying".xslt_error($xsltproc), 2);
      $wrong = parse_in_xml_string(file_get_contents('modules/contributions/modules/import_html/safe_pass_through.xsl'));
debug_pre($wrong);      
debug_pre($wrong->dump_mem());      
    }
    xslt_free($xsltproc);
    return $out;
  }
}

function xslt_error_handler($handler, $errno, $level, $info)
{
  // for now, let's just see the arguments
  debug_pre(func_get_args());
}

/**
 * A version safe way to make an XML doc from a filename
 */
function load_xml_from_file($xmlfile) {
  $xmldoc = new DomDocument('1.0');
  if(is_callable (array($xmldoc,"load"))){ // PHP5
    $xmldoc->load($xmlfile);
  } else {                                 // PHP4
    $xmldoc = domxml_open_file($xmlfile);
  }
  return $xmldoc;
}

/**
 * PHP directives can make it through and validate OK,
 * but confuse the hell out of the XML DOM it would seem
 * I'll have to discard them here.
 */
function tidy_strip_php($source){
  return preg_replace('/<\?.*?\?>/sS',"",$source,-1);
}


/**
 * Returns the XML as a string from a document object.
 * Due to total differences between 4&5, this func combines
 *     dump_mem() with saveXML()
 * @param $xmlnode to be dumped
 * @param $innerXML BOOL discard the wrapper element, only return the contents
 */
function xml_toString($xmlnode,$innerXML=FALSE){
  if(!$xmlnode){return '';}
  if(!is_object($xmlnode)){debug("Problem extracting string from what should have been a DOM node. ".print_r($xmlnode)); return '';}
  if(extension_loaded("xsl")) {
    # debug("Dumping XML to string using PHP5 xsl module",4);
    $xmldoc = ($xmlnode->ownerDocument) ? $xmlnode->ownerDocument : $xmlnode;
    if($innerXML){
      foreach($xmlnode->childNodes as $child){
        $out .= $xmldoc->saveXML($child);
      }
      return $out;
    }
    return $xmldoc->saveXML($xmlnode);
  }
  if(extension_loaded("xslt")) {
    # debug("Dumping XML to string using PHP4 xslt module",4);
    $xmldoc = ($xmlnode->owner_document()) ? $xmlnode->owner_document() : $xmlnode;
    return ($xmlnode->node_type() == XML_DOCUMENT_NODE ) ? $xmldoc->dump_mem(TRUE) : xml_dump_child_nodes($xmlnode);
  }
}

function xml_dump_child_nodes($node){
   $owner_document = $node->owner_document();
   $children = $node->child_nodes();
   $total_children = count($children);
   for ($i = 0; $i < $total_children; $i++){
       $cur_child_node = $children[$i];
       $output .= $owner_document->dump_node($cur_child_node);
   }
   return $output;
}

/**
 * Tedious PHP version-safe method
 * Optionally just return the first one.
 * Encapsulated here so I don't have to think about nodelist item(0) vs array[0]
 */
function xml_getElementsByTagName($xmldoc, $tagname, $just_one=FALSE){
  $func = (extension_loaded('xsl'))?'getElementsByTagName':'get_elements_by_tagname';
  $result = $xmldoc->$func($tagname);
  if($just_one){ foreach($result as $element){return $element;}}
  return $result;
}

/**
 * Tedious PHP version-safe method
 * Adapted to try an attribute search as well, if xml:id is not working.
 * A document id element is not neccesarily the XML DOM ID handle, unless 
 * some special hoops are jumped through. 
 * Works when handed either a node or the whole document
 */
function xml_getElementById($xmlnode, $id){
  $xmldoc = xml_getOwnerDocument($xmlnode);
  
  $element = (extension_loaded('xsl'))
    ? $xmldoc->getElementById($id) 
    : $xmldoc->get_element_by_id($id);

  if($element)
    return $element;

  debug("lookup for xml:ID $id failed, doing query instead",3);
  // For occult reasons, http://blog.bitflux.ch/wiki/GetElementById_Pitfalls 
  // the above may fail when the below may work : (100+ times slower)
  // http://php5.bitflux.org/xmlonspeed/slide_20.php

  if(extension_loaded('xsl')){ // PHP5
    $xp = new DomXPath($xmldoc);
    $res = $xp->query(".//*[@id = '$id']", $xmlnode);
    return $res->item(0);
  }

  // PHP4 TODO test
  $xp = $xmldoc->xpath_new_context();
  $res = $xp->xpath_eval("//*[@id = '$id']");
  return $res[0];
}  

/**
 * Version-safe, and allows a document's owner to be itself, to be nice.
 */
function xml_getOwnerDocument($xmlnode){
  return (extension_loaded('xsl')) ? 
    ( ($xmlnode->nodeType == XML_DOCUMENT_NODE ) ? $xmlnode : $xmlnode->ownerDocument) 
    : $xmlnode->owner_document(); // ...don't ask.
}

function xml_query($xmlnode,$query){
  if(extension_loaded('xsl')){ // PHP5
    $xp = new DomXPath(xml_getOwnerDocument($xmlnode));
    return $xp->query($query, $xmlnode);
  }
  // PHP4
  $xmldoc = xml_getOwnerDocument($xmlnode);
  $xp = $xmldoc->xpath_new_context();
  $result = $xp->xpath_eval($query, $xmlnode);
  if(is_object($result) && $result->nodeset) return $result->nodeset; // DOM/XML API Version  20020815
  return $result;
}

/**
 * PHP version-safe implimentation of element->toString;
 */
function xml_textContent($xmlnode){
  if(!is_object($xmlnode)){debug("Null node to get text from. Returning empty string.",3);return '';}
  return (extension_loaded('xsl')) ? $xmlnode->textContent : $xmlnode->get_content();
}

/**
 * Tedious PHP version-safe method
 */
function xml_getAttribute($xmlnode, $attname){
  if(!is_object($xmlnode)){debug("Invalid Parameter, null node",1);return '';}
  $func = (extension_loaded('xsl'))?'getAttribute':'get_attribute';
  return $xmlnode->$func ($attname);
}


/**
 * Find element by tagname, return its content.
 */
function xml_get_element_content($xmldoc, $tagname)
{
  $tags = xml_getElementsByTagName($xmldoc, $tagname);
  foreach($tags as $tag){
    return  xml_textContent($tag);
  }
  // Note this just breaks the loop on the first item. 
  // foreach just happens to work in both PHP4&5 over either array or nodelist
}



?>