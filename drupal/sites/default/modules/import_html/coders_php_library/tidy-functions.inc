<?php
/**
 * @file
 * Pass HTMLTidy over some inputs to make them valid XHTML
 *
 * Uses either the PHP5 extension module or the commandline binary.
 *
 * Run htmltidy_test() to try and initialize the
 * htmltidy_apppath variable, which is needed to find the 'tidy' binary.
 *
 * In the commandline version, the xhtml_tidy.conf file
 * is read from the same directory as this library.
 *
 * @package coders
 * @author Dan Morrison http://coders.co.nz/
 * @version $Id: tidy-functions.inc,v 1.16.2.1 2007/02/20 12:30:40 dman Exp $
 */

@require_once('debug.inc');

/**
 * Use the tidy extension (Whee!) to fix randomly downloaded 'html'
 *
 * The result should be valid XHTML that can now be converted into a DOM
 * if the extension is unavailable, try doing it on the commandline
 * if the executable is available.
 *
 * @param $data string Raw web page source
 * @param $xhtml If set, the correct namespace will be inserted into the
 * document, and later xhtml imports will work without bogus namespace tags.
 * @return $string Cooked web page source
 */
function xml_tidy_string($data,$xhtml=TRUE) {
  // Because HTML character entities should have been properly declared (but naturally are not) &nbsp; and friends will cause complaints.
  // Decode them, then let tidy re-encode them as XML-friendly _numerical_ entities; Dunno if there's a tidy option to re-convert already encoded entities.
  $data = html_entity_decode( $data ) ;

  // Tidy
  if ( extension_loaded( "tidy" ) && function_exists('tidy') ) {
    // Specify configuration
    // The DOCTYPE syntax seems to cause complaints
    // <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
    // is apparently illegal ? Need to omit it. Wants space inside the end of the tag ...
    // The xml declaration also causes trouble with browser rendering.
    //
    $config = array(
       'indent'           => true,
       'output-xml'       => true,
       'numeric-entities' => true,
       'add-xml-decl'     => false,
       'doctype'          => 'omit',
       'char-encoding'    => 'utf8',
       'wrap'             => 200,
       'repeated-attributes' => 'keep-last',
    );
    if($xhtml){$config['output-xhtml'] = true; }
    

    $tidy = new tidy();
    $tidy->parseString($data, $config);
    $tidy->cleanRepair();
    return (string)tidy_get_output($tidy) ;
  }

 // No Tidy Module, go commando

  debug("No PHP tidy support, attempting to use the command-line way to process a string. This is pretty hokey!",2);
  // Need to write, pipe & read the result.
  $temp_path =  foreslash( tempnam($_ENV['TEMP'],"htm") );

  file_put_contents($temp_path,$data);
  if(! file_exists($temp_path)){
    trigger_error("Failed to create/write temp file '$temp_path'");
    return FALSE;
  }
  $out = xml_tidy_file($temp_path);
  if(! DEBUGLEVEL){ unlink($temp_path); }

  if($out){
    return $out;
  }
  debug("No html tidy support at all. Trying to tidy returned null. You need to enable the PHP module to use this, or ensure the 'tidy' executable is present and defined as TIDY_PATH and use that",2);
  return $data;
}


/**
 * Tidy an xml file in place
 *
 * If we don't have the tidy module, we can still try to get the effect
 * using the command-line version.
 * Remote files are supported, they are fetched into a the temp dir
 * before being processed.
 *
 * @parameter $filepath string The full filepath of the file to be tidied
 * @returns string the content of the tidied file
 */
function xml_tidy_file($filepath) {
  debug("Tidying file '$filepath' ",2);

  if(! is_local($filepath)){
    // OK, so it's a remote file and I have to process it on the command-line ...
    // Copy it down
    $source = file_get_contents($filepath);
    if(! $source){
      trigger_error("No content from '$filepath'", E_USER_WARNING ); return false;
    }
    debug("Retrieved remote file:$filepath is ".strlen($source)." big",3);
    // put it in a temp place
    $target_path =  tempnam($_ENV['TEMP'],"htm");

    file_put_contents( foreslash($target_path) , $source );
  } else {
    $target_path = $filepath;
  }

  if(! file_exists($target_path) ){
    debug("Attempted to tidy a file that doesnt exist. Looking for $target_path failed!");
    return;
  }


  if(! $htmltidy_apppath = variable_get("htmltidy_apppath", '')){
    // first run?
    include_once "install-htmltidy.inc";
    if( ! htmltidy_test() ){
      // test returned an error
      drupal_set_message('Unable to tidy file - htmltidy was unavailable. Returning the original source.','error');
      return file_get_contents($target_path );
    };
  }
  if(! $htmltidy_apppath = variable_get("htmltidy_apppath", '')){
    drupal_set_message('Shouldnt get here!','error');
    return;
  }

  define("TIDY_OPTIONS"," -q -config ".foreslash( dirname(__FILE__)."/xhtml_tidy.conf ") );

  // format it
  #$command = $htmltidy_apppath ." ". TIDY_OPTIONS . '"'.escapeshellcmd( foreslash($target_path) ).'"' ;
  # escapeshellcmd killed ~, which may be required in windows.
  $command = $htmltidy_apppath ." ". TIDY_OPTIONS . '"'. foreslash($target_path).'" ' ;
  # Errors are compressed into the output so I can see them

  // TODO - check for exploits here? What could happen?
  debug("Running \n$command" ,1);
  $result = exec($command, $response, $return_code);
  $out=join("\n",$response);

  if(!$out){
    // run the exact same command again, but collect the errors this time
    $result = exec($command.' 2>&1', $response, $return_code);
    $out=join("\n",$response);
    
		debug_pre($out);
		trigger_error("HTMLTidy failed to parse the input at all! It's probably very problematic HTML.\n A working version of tidy IS at ".$htmltidy_apppath." isn't it?\nI ran <code>\n$command\n</code> and it returned: $return_code \n" , E_USER_WARNING);
    $out = FALSE; // file_get_contents($target_path );
  }


  debug("<h3>After command-line tidy</h3><textarea rows='40' cols='80'>$out</textarea>",2);

  if($target_path != $filepath)
  { // remove temp file we just made up.
    unlink($target_path);
  }

  return $out;
}

/**
 * Tidies an incomplete fragment of HTML 
 * 
 * by wrapping it in a document header/footer,
 * passing it through htmltidy full,
 * then stripping the 'body'
 * 
 */
function xml_tidy_fragment($input){
  if(!$input){ return ''; }
  
  // Pretend it's a full document. This declaration just suppresses one of the warnings.
  $declaration = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">';
  $output = xml_tidy_string($declaration.'<html><head><title></title></head><body>'.$input.'</body></html>');

  if(preg_match('|<body[^>]*>([\s\S]*)</body>|',$output,$matches)){
    $output = $matches[1];
  }

  return $output;
}


?>