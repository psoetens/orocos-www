<?php
/**
 * @file
 * Small library of diagnostic feedback stuff.
 *
 * Maybe should be tracing to a file instead but...
 * Set DEBUGLEVEL > 0 to see what's going on
 * Set DEBUGSYSLOG to send messages to syslog also
 * Set DEBUGBACKTRACE for performance and callstack logging
 *
 * @package coders
 * @author Dan Morrison http://coders.co.nz/
 * @version $Id: debug.inc,v 1.8 2006/11/12 06:41:08 dman Exp $ 
 */



/*
 * This is (obviously) a debug-only library
 * and use of it should eventually be removed
 * BUT during development this library might 
 * be called upon more than once, from different locations even.
 * Do our own require_once - type check.
 */
if(! function_exists('debug')){ 

  if( isset($REQUEST["DEBUGLEVEL"]) && ( ! defined("DEBUGLEVEL")) ){
    define("DEBUGLEVEL",$REQUEST["DEBUGLEVEL"]);
  } 

  /**
   * Display a feedback message
   * If DEBUGLEVEL is set, and is greater than or equal to the threshold level of this
   * message, display it. If the threshold is greater, display nothing.
   * <pre>debug("Beginning user submission process",1)</pre>
   * <pre>debug("Checking configuration files exist",2)</pre>
   * <pre>debug("Making database lookup '$request'",3)</pre>
   *
   * if global DEBUGBACKTRACE is set, additional backtrace and timer detail 
   * is also displayed.
   *
   * ... would return varying levels of detail depending on the value of DEBUGLEVEL
   * @param string $message The message to display
   * @param int    $level The amount of detail to show - 1 is basic, 2 identifies most function calls, 3 is verbose.
   * @global DEBUGLEVEL
   */
  function debug($message,$level=0) {
    static $timestamp; static $starttime;
    if(!$timestamp){$timestamp = $starttime = debug_get_microtime(); debug("Initialized Timestamp",3);}
    $timescale=100;

    // Check if debug is turned on here
    $debug_array = debug_backtrace();
    $caller = $debug_array[1];
    if(isset($caller['file'])){
      $caller_dir = basename(dirname($caller['file']));
    } else {$caller_dir='';}
    global $debug_watch;
 
    if( (! $level) || ($level <= $debug_watch[$caller_dir]) || ($level <= DEBUGLEVEL) ){
      print "<div class='debug' style='margin-left:{$level}em'>";
      print "<div class='message'>$message</div>\n";

      if( defined("DEBUGBACKTRACE") ){

        $previous_caller = array_shift($debug_array);
        $traceDepth = DEBUGLEVEL+DEBUGBACKTRACE;

        print("<small class='trace'><i>");
        while(($bt=array_shift($debug_array))&&(1+$traceDepth--)){
          if($previous_caller['file'])
          { // sometimes debug_backtrace() returns dummy lines?
            print("\n : in <strong >".$bt['function']."()</strong>, line " . $previous_caller['line'] . " " . basename($previous_caller['file']) );
          }
          $previous_caller=$bt;
        }
        $now = debug_get_microtime();
        print(" <strong>". sprintf("%01.2f", ($now-$timestamp) ) ."s</strong> elapsed. (".((int)($timescale*($now-$starttime)))." total)");$timestamp=$now;
        print("</i></small>");
      }
      flush();
      print("</div>\n");
    }

    if( defined("DEBUGSYSLOG") && DEBUGSYSLOG){
      syslog(E_USER_NOTICE,$message);
    }
  }


  /**
   * Dump an object or code listing in viewable raw format
   */
  function debug_pre($message,$level=0) {
    debug("<pre>".htmlspecialchars(print_r($message,1)) ."</pre>",$level);
  }

  function debug_get_microtime() { 
    list($usec, $sec) = explode(" ",microtime()); 
    return ((float)$usec + (float)$sec); 
  } 

  function debug_css(){
    return '
      <style  type="text/css">
        .debug{ }
        .debug .trace{ font-size:70%; color:#cccccc;  }
        .debug:hover .trace{ display:block; }
        .debug li, .debug ul {margin-top:0.1em;margin-bottom:0.1em;}
      </style>
    ';
  }

  /**
   * Advanced debug levels - can be set different for different directories.
   * Either define the 'section' or I'll infer it from the caller
   */  
  function debug_set_level($level,$section=''){
    drupal_set_html_head(debug_css());
    if(! $section){
      $debug_array = debug_backtrace();
      $caller = $debug_array[0];
      $section = basename(dirname($caller['file']));
    }
    global $debug_watch;
    $debug_watch[$section] = $level;
  }
}


# devel.module hijacked this! Yay for core, but now I never know if it's available ;)'
#if(! function_exists('dsm')){
#  /**
#   * Shorthand for drupal_set_message(print_r($arr,1));
#   */
#  function dsm($arr){drupal_set_message(print_r($arr,1));}
#}

?>
