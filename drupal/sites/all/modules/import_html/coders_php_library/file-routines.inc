<?php

/**
 * @file File Routines : Common read/write library.
 * The actual reading and writing between remote URL, local URL and local filepath.
 * @todo Test again. Most testing was done on the CURL library implimpentation of these functions instead.
 *
 * @package coders
 * @author Dan Morrison http://coders.co.nz/
 * @version $Id: file-routines.inc,v 1.6 2007/02/12 23:39:56 dman Exp $
 */

// debug("Initiated built-in library for network requests. This means that some sites may be inaccessible as we can't do referrer-fudging or proxy-hops when leeching.",3);


/**
 * Return a directory listing as a list.
 * @parameter $dirname string Directory Path
 * @returns array Filenames, unordered.
 */
function read_dir_as_array($dirname) {
  $result = array();
  if ($dir = @opendir($dirname)) {
    while (($file = readdir($dir)) !== false) {
      if(! preg_match("/^[_\\.]/",$file)){ // skip 'hidden' items
        $result[] = $file;
      }
    }
    closedir($dir);
  }
  return $result;
}



if(! is_callable("file_put_contents") ) {
  /**
   * Save a file. Emulator for the function added to PHP later
   * @parameter $filename string 
   * @parameter $data string Content to save.
   * @returns boolean success.
   */
  function file_put_contents($filename,$data) {
       if (!$handle = fopen($filename, 'w')) {
              trigger_error ("Cannot open file ($filename)");
             return false;
       }
    
       // Write $somecontent to our opened file.
       if (fwrite($handle, $data) === FALSE) {
            trigger_error ("Cannot write to file ($filename)");
           return false;;
       }
       fclose($handle);
       return true;
  }
}


/**
 * Converts all forward slashes to backslashes for filepaths.
 * Note, if quoting this result in a commandline command, ensure 
 * you don't have to double-backslash it. 
 * @see foreslash
 * @see system_path
 * @parameter string $path
 * @returns string path.
 */
function backslash($path) {
  return preg_replace('|\/+|','\\',$path); 
}

/**
 * Converts backslashes to all forward slashes for filepaths.
 * @see backslash
 * @see system_path
 * @parameter string $path
 * @returns string path.
 */
function foreslash($path) {
  return preg_replace('|\\\\+|','/',$path); 
}

/**
 * Return either a foreslash or backslash filepath, as appropriate for the system
 * @see foreslash
 * @see backslash
 * @parameter string $path
 * @returns string path.
 */
function system_path($path) {
  return (strpos($_ENV['OS'],'Windows')===false)?foreslash($path):backslash($path);
}

/**
 * Adds a slash to a directory path if it wasn't already set
 * @parameter string $path
 * @returns string path.
 */
function ensure_trailing_slash($path) {
  return preg_replace( '|(.)/?$|' , '$1/' , $path );
}

/**
 * Removes last slash from a directory path
 * @parameter string $path
 * @returns string path.
 */
function trim_trailing_slash($path) {
  return rtrim($path,'/');
}

/**
 * Returns true if the given path/url is on the current filesystem
 * Returns false for Urls and stuff
 * @parameter string $url
 * @returns boolean
 */
function is_local($url) {
  $url_parts = parse_url($url);
  if($url_parts['host']){ return false; }
  else{ return true; }
}

/**
 * Move a file locally
 * This includes making the path, if it didn't already exist.
 *
 * @param string $current_name
 * @param string $new_mirror_root_location
 */
function move_file($current_name, $new_mirror_root_location ) {
  $path = ereg_replace("[^\\]*$" , "", $new_mirror_root_location );

  if (! file_exists($path) )
  {
    debug ("Making $path");
    mkdirs($path);
  }
  rename($current_name,$new_mirror_root_location);

  debug( "<br />MOVED \"$current_name\" \"$new_mirror_root_location\"\n");
}



/**
 * Ensure the ancestors of a given path exist.
 *
 * @param string $path
 */
function mkdir_recursive($path){
  debug('DEPRECATED, rename the function mkdir_recursive to mkdirs, please');
  return mkdirs($path);
}

if(! function_exists('mkdirs')){
/**
 * Recursive directory creation. 
 * Very common task, so it may have been declared by other libraries.
 */
	function mkdirs($strPath, $mode = 0777) //creates directory tree recursively
	{
		 return is_dir($strPath) or ( mkdirs(dirname($strPath), $mode) and mkdir($strPath, $mode) and chmod($strPath, 0777) );
	}
}


/**
 * Copy a file, supporting remote network protocols and authentication.
 *
 * Much of this is redundant with later versions of PHP, with better
 * built-in network support, this long way and paranoia is legacy.
 *
 * If the file read times out (which is possible with network)
 * The (partial) file is not created.
 *
 * The constant STAY_LOCAL will prevent network from happening.
 * Again, this is covered better in later PHP.
 *
 * @todo test and extend
 * @parameter string $from
 * @parameter string $to
 * @parameter boolean $replace = true
 */
function remote_file_copy($from,$to,$replace = true) {
  // the documented copy() does not handle URLS for me today :(
  $from = (ereg_replace("file\:\/\/\/","",$from)); // only used in extreme testing
  $to   = (ereg_replace("file\:\/\/\/","",$to)); // have to assume this

  // if $from is an URL, but the URL is actually local,
  // url_to_filePath() should return the directory mapping. (optional function implimented elsewhere)
  if(is_callable("url_to_filePath") && url_to_filePath($from) != $from) # if this succeeded it's a local location
  {
    $from_local = url_to_filePath($from);
    if(!file_exists($from_local)){
      warn("When trying to copy $from, which looks like it should be $from_local - failed to find it. Could be virtual paths or magic happening, but I can't handle it. Probably just missing.");
      print format_button("?command=forget&url=$from","Clear this 404 from the database",'Remove all trace of this odd record');
      return false;
    }
  }

  if(isset($GLOBALS['dont_stay_local'])){
    global $dont_stay_local; # - override the local restriction on a one-off basis.
  }
  
  $is_remote =  (! is_local($from) );
  
  $stay_local = ( defined(STAY_LOCAL) && STAY_LOCAL && (! $dont_stay_local) );

  if( $is_remote && $stay_local )
  { warn("Network disabled in the configuration. STAY_LOCAL='".STAY_LOCAL."' dont_stay_local='$dont_stay_local' <a href='".$_SERVER['PHP_SELF']."?".$_SERVER['QUERY_STRING']."&dont_stay_local=1'>Unset the 'STAY_LOCAL' parameter</a> to fetch foreign content");return false ;}
  
  if($is_remote && (! ini_get("allow_url_fopen")) ){
    warn("This server does not allow remote file access. Need to enable allow_url_fopen in php.ini or somewhere");
    return false;
  }

  $fd = fopen ($from, "rb");
  if (!$fd)
  { debug("The file '$from' could not be retrieved"); return false;}

  mkdirs(ereg_replace("[^\/]*.{1}$" , "", $to ));

#  if ( file_exists($to) ) // paranoia
#  { rename ($to,$to.".bak")}

  # Hard to recover correctly from timeouts during read (which is when it's most likely to happen)
  # temp-file it
  if (!$fp = fopen($to.".tmp", "wb"))
  { warn("Cannot open file ($to) for writing to."); return false; }

  $contents = "";
  while( $block = fread ($fd,10024) ){
      if (!fwrite($fp, $block))
      { warn("Cannot write to file ($to)"); return false; }
      $contents .= $block;
  }

  fclose ($fp);

  // check for failure!
  $meta_data = socket_get_status( $fd );
  fclose ($fd);

  if($meta_data['timed_out'])
  {
    warn("Bugger! Timed out on read, deleting partial result");
    unlink($to.".tmp");
    $contents = "";
  } else {
    if (file_exists($to.".tmp")){
      if($replace && file_exists($to)){unlink($to);}
      rename($to.".tmp",$to);
    } else {
      warn("Strange, no timeout reported when writing $to , yet the file failed to arrive.");
    }
  }
  return $contents;
}



?>