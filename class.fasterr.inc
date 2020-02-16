<?php

/**
 * Copyright (c) 2016, 2022, the Open Gallery's contributors
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither Open Gallery nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software 
 *       without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * class.fasterr.inc
 * 
 * FastErr class.
 *
 * @author Daniele Bonini <my25mb@aol.com>
 * @copyrights (c) 2016, 2022, the Open Gallery's contributors  http://opengallery.media  
 * @license https://opensource.org/licenses/BSD-3-Clause 
 */

namespace OpenGallery\OpenGallery;

/**
 * FastErr
 *
 * FastErr class
 *
 * @package  OpenGallery http://github.com/par7133
 * @author   Daniele Bonini <my25mb@aol.com>
 * @version  1.0
 * @access   public
 * @note You have to declare in your "config.inc" file - or whatever file you
 * use for the purpose, the following global constants:
 * define('APP_NAME', "YOUR_APP_NAME");
 * define('DEBUG', "true|false");
 * 
  * This class makes use of the global function isset1, declared in this way:
 * 
 * function isset1(&$var, $default=false) {
 *   if (isset($var)) {
 *     return $var;
 *   } else {
 *     return $default;
 *   }
 * }
 */
final class Err 
{
  const ERR_GENERAL = "uEh1RE49t6qn91101aZvS4xbZ9TlGLeF";
  
  public static $A_ERR_NO = [
    'ERR_GENERAL' => "uEh1RE49t6qn91101aZvS4xbZ9TlGLeF",
  ];

  public static $A_ERR_MSG = [
    'ERR_GENERAL' => "Unexpected error happened.",
  ];

  public static $A_ERR_EXTDES_MSG = [
    'ERR_GENERAL' => "A general error happened. The application is going to end here.",
  ];
  
  /**
      * the instance of the object 
      * 
      * @access private 
      * @var Err
      */
  private static $_instance = null;  
  
  /**
      * Reference to the previous error handler
      * 
      * @access public
      * @var string  
      */
  private static $_old_error_handler;

  /**
      * Param1 of the previous error handler
      * 
      * @access public
      * @var string  
      */
  private static $_old_error_handler_param1 = null;

  /**
      * Param2 of the previous error handler
      * 
      * @access public
      * @var string  
      */
  private static $_old_error_handler_param2 = null;

  /**
      * Exception handler / trigger in the form of anonymous function
      * 
      * @access public 
      * @var function
      */
  private static $_throw1;

  /**
      * Error handler / trigger in the form of anonymous function
      * 
      * @access public 
      * @var function
      */
  private static $_trigger_error1;
  
  /**
      * Default constructor
      * 
      * @return void
      */
  private function __construct()
  {
    self::$_old_error_handler = "";
  }

  /**
      * Get an instance of the resources object
      * 
      * @return object
      */
  private static function &getInstance() 
  {
    if (!isset(self::$_instance)) {
      self::$_instance = new FastErr();
    }
    return self::$_instance;
  }
  
  /**
      * Check if the static instance is set
      * 
      * @return bool
      */
  public static function issetInstance()
  {
    return isset(self::$_instance);
  }
  
  /**
      * Unset the static instance
      * 
      * @return void
      */
  public static function unsetInstance()
  {
    unset(self::$_instance);
  }

  /**
      * Load the error descriptions and other constants
      * 
      * @return void 
      */
  public static function load()
  {
      self::getInstance();
  }
  
  /**
      * Set the default error and exception handlers 
      *
      * @return void
      * @access public
      */ 
  public static function setDefaultHandlers() 
  {
    // Assigning the error handling function..
  
    // Load the error resources..
    self::load();

    // Saving reference to the current error handler..
    self::$_old_error_handler = "setDefaultHandlers";
    self::$_old_error_handler_param1 = null;
    self::$_old_error_handler_param2 = null;
    
    /**
            * Error handling function
            *
            * @param string $errNo the number of the error
            * @param string $errMsg the error message
            * @param string $errScript the script where the error happened
            * @param integer $errLine the line of code of the error
            * @return void
            */
    self::$_trigger_error1 = static function ($errNo, $errMsg, $errScript, $errLine) {

      $errKey = array_search($errNo, self::$A_ERR_NO);

      error_log(strtoupper(APP_NAME) . " " . "ERROR ($errNo): $errMsg : in script $errScript, line $errLine");

      // Logging the stack trace..
      $aDebugTrace = debug_backtrace();
      
      if (count($aDebugTrace)>0) {
        
        $aDebugTrace = array_reverse($aDebugTrace);
        array_pop($aDebugTrace);
        
        error_log(strtoupper(APP_NAME) . " " . "Stack trace:");

        $i = 1;
        foreach ($aDebugTrace as $trace) {
          error_log(strtoupper(APP_NAME) . " " . $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], ""));
          $i=$i+1;
        }
      }

      error_log(strtoupper(APP_NAME) . " " . "Ending script...");


      // Display error
      if (DEBUG) {
        echo "ERROR ($errNo): "  . Page::HTMLencode($errMsg, true) . ": in script $errScript, line $errLine<br>";

        // Printing the stack trace..
        if (count($aDebugTrace)>0) {
        
          echo "Stack trace:" . "<br>";

          $i = 1;
          foreach ($aDebugTrace as $trace) {
            echo $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], "") . "<br>";
            $i=$i+1;
          }
        }
        
      } else {
        if (isset(self::$A_ERR_MSG[$errKey])) { 
          echo Page::HTMLencode(self::$A_ERR_MSG[$errKey], true) . " in script " . basename($errScript) . ", line $errLine<br>";
        } else { 
          echo "Unexpected Error in script ".  basename($errScript) . ", line $errLine<br>";
        } 
      }
      echo "Ending script...<br>";
      
      if (!TESTING) {
        exit(1);
      } else {
        throw new Exception($errMsg);
      }
    };

    // Registering the error handling function..
    set_error_handler(self::$_trigger_error1);
    
    // Assigning the exception handling function..
    
    /**
            * Exception handling function
            *
            * @param Exception $e the exception thrown
            * @return void
            */
    self::$_throw1 = static function (\Throwable $e) {
  
      $errNo=$e->getCode(); 
      $errMsg=$e->getMessage();
      $errScript=$e->getFile();
      $errLine=$e->getLine(); 

      $errKey = array_search($errNo, self::$A_ERR_NO);

      error_log(strtoupper(APP_NAME) . " " . "ERROR ($errNo): $errMsg : in script $errScript, line $errLine");

      // Logging the stack trace..
      $aDebugTrace = $e->getTrace();
      
      if (count($aDebugTrace)>0) {
 
        $aDebugTrace = array_reverse($aDebugTrace);
        
        error_log(strtoupper(APP_NAME) . " " . "Stack trace:");

        $i = 1;
        foreach ($aDebugTrace as $trace) {
          error_log(strtoupper(APP_NAME) . " " . $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], ""));
          $i=$i+1;
        }
      }

      error_log(strtoupper(APP_NAME) . " " . "Ending script...");

      // Display error
      if (DEBUG) {
        echo "ERROR ($errNo): " . Page::HTMLencode($errMsg, true) . ": in script $errScript, line $errLine<br>";

        // Printing the stack trace..
        if (count($aDebugTrace)>0) {
 
          echo "Stack trace:" . "<br>";

          $i = 1;
          foreach ($aDebugTrace as $trace) {
            echo $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], "") . "<br>";
            $i=$i+1;
          }
        }
        
      } else {
        if (isset(self::$A_ERR_MSG[$errKey])) { 
          echo Page::HTMLencode(self::$A_ERR_MSG[$errKey], true) . " in script " . basename($errScript) . ", line $errLine<br>";
        } else { 
          echo "Unexpected Error in script ".  basename($errScript) . ", line $errLine<br>";
        } 
      }
      echo "Ending script...<br>";

      if (!TESTING) {
        exit(1);
      } else {
        throw new Exception($errMsg);
      }

    };
    
    // Registering the exception handling function
    set_exception_handler(self::$_throw1);
    
  }

  /**
      * Set the error handlers to redirect to a page 
      *
      * @param  string  $landingPage the landing page to redirect to
      * @param  string  $queryString additional query string to pass in the redirect
      * @return void
      * @access public
      */ 
  public static function setRedirectHandlers($landingPage, $queryString = "") 
  {

    // Assigning the error handling function..
    
    // Load the error resources..
    self::load();

    // Saving reference to the current error handler..
    self::$_old_error_handler = "setRedirectHandlers";
    self::$_old_error_handler_param1 = $landingPage;
    self::$_old_error_handler_param2 = $queryString;

    /**
            * Error handling function
            *
            * @param string $errNo the number of the error
            * @param string $errMsg the error message
            * @param string $errScript the script where the error happened
            * @param integer $errLine the line of code of the error
            * @return void
            */
    self::$_trigger_error1 = static function ($errNo, $errMsg, $errScript, $errLine) use ($landingPage, $queryString) {
      
      error_log(strtoupper(APP_NAME) . " " . "ERROR ($errNo): $errMsg : in script " . $errScript . ", line $errLine");
      
      // Logging the stack trace..
      $aDebugTrace = debug_backtrace();
      
      if (count($aDebugTrace)>0) {
        
        $aDebugTrace = array_reverse($aDebugTrace);
        array_pop($aDebugTrace);
        
        error_log(strtoupper(APP_NAME) . " Stack trace:");

        $i = 1;
        foreach ($aDebugTrace as $trace) {
          error_log(strtoupper(APP_NAME) . " " . $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], ""));
          $i=$i+1;
        }
      }
      
      error_log(strtoupper(APP_NAME) . " " . "Redirecting...");

      //Redirect with error..
      if (DEBUG) { 
        
        //Buffering stack trace..
        if (count($aDebugTrace)>0) {
        
          $errStack = "Stack trace:" . "<br>";

          $i = 1;
          foreach ($aDebugTrace as $trace) {
            $errStack .= $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], "") . "<br>";
            $i=$i+1;
          }
        }
        
        Page::redirect($landingPage . (stripos($landingPage, "?")>0 ? "&" : "?") . "uid=" . uniqid(rand(), true) . ($queryString!="" ? "&". $queryString : "") . "&errNo=" . urlencode($errNo) . "&errMsg=" . urlencode($errMsg) . "&errScript=" . urlencode($errScript) . "&errLine=" . urlencode($errLine) . "&errStack=" . urlencode($errStack));
      } else {
        Page::redirect($landingPage . (stripos($landingPage, "?")>0 ? "&" : "?") . "uid=" . uniqid(rand(), true) . ($queryString!="" ? "&". $queryString : "") . "&errNo=" . urlencode($errNo));
      }  

      if (!TESTING) {
        exit(1);
      } else {
        throw new Exception($errMsg);
      }
    };

    // Registering the error handling function..
    set_error_handler(self::$_trigger_error1);
    
    
    // Assigning the exception handling function..
    
    /**
            * Exception handling function
            *
            * @param Exception $e the exception thrown
            * @return void
            */
    self::$_throw1 = static function (\Throwable $e) use ($landingPage, $queryString) {
  
      $errNo=$e->getCode(); 
      $errMsg=$e->getMessage();
      $errScript=$e->getFile();
      $errLine=$e->getLine(); 

      error_log(strtoupper(APP_NAME) . " " . "ERROR ($errNo): $errMsg : in script " . $errScript . ", line $errLine");
      
      // Logging the stack trace..
      $aDebugTrace = $e->getTrace();
      
      if (count($aDebugTrace)>0) {
 
        $aDebugTrace = array_reverse($aDebugTrace);
        
        error_log(strtoupper(APP_NAME) . " Stack trace:");

        $i = 1;
        foreach ($aDebugTrace as $trace) {
          error_log(strtoupper(APP_NAME) . " " . $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], ""));
          $i=$i+1;
        }
      }
        
      error_log(strtoupper(APP_NAME) . " " . "Redirecting...");

      //Redirect with error..
      if (DEBUG) { 

        //Buffering stack trace..
        if (count($aDebugTrace)>0) {
        
          $errStack = "Stack trace:" . "<br>";

          $i = 1;
          foreach ($aDebugTrace as $trace) {
            $errStack .= $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], "") . "<br>";
            $i=$i+1;
          }
        }

        Page::redirect($landingPage . (stripos($landingPage, "?")>0 ? "&" : "?") . "uid=" . uniqid(rand(), true) . ($queryString!="" ? "&". $queryString : "") . "&errNo=" . urlencode($errNo) . "&errMsg=" . urlencode($errMsg) . "&errScript=" . urlencode($errScript) . "&errLine=" . urlencode($errLine) . "&errStack=" . urlencode($errStack));
      } else {
        Page::redirect($landingPage . (stripos($landingPage, "?")>0 ? "&" : "?") . "uid=" . uniqid(rand(), true) . ($queryString!="" ? "&". $queryString : "") . "&errNo=" . urlencode($errNo));
      }   

      if (!TESTING) {
        exit(1);
      } else {     
        throw new Exception($errMsg);
      }
    };
    
    // Registering the exception handling function
    set_exception_handler(self::$_throw1);
  }
  
  /**
      * Set the error handlers to json  
      *
      * @return void
      * @access public
      */ 
  public static function setJSONHandlers() 
  {

    // Assigning the error handling function..
    
    // Load the error resources..
    self::load();

    // Saving reference to the current error handler..
    self::$_old_error_handler = "setJSONHandlers";
    self::$_old_error_handler_param1 = null;
    self::$_old_error_handler_param2 = null;

    /**
            * Error handling function
            *
            * @param string $errNo the number of the error
            * @param string $errMsg the error message
            * @param string $errScript the script where the error happened
            * @param integer $errLine the line of code of the error
            * @return void
            */
    self::$_trigger_error1 = static function ($errNo, $errMsg, $errScript, $errLine) {
      
      error_log(strtoupper(APP_NAME) . " " . "ERROR ($errNo): $errMsg : in script " . $errScript . ", line $errLine");

      // Logging the stack trace..
      $aDebugTrace = debug_backtrace();
      
      if (count($aDebugTrace)>0) {
        
        $aDebugTrace = array_reverse($aDebugTrace);
        array_pop($aDebugTrace); 
        
        error_log(strtoupper(APP_NAME) . " Stack trace:");

        $i = 1;
        foreach ($aDebugTrace as $trace) {
          error_log(strtoupper(APP_NAME) . " " . $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], ""));
          $i=$i+1;
        }
      }
      
      error_log(strtoupper(APP_NAME) . " " . "Ending Json...");
     
      //Json encode the error..
      if (DEBUG) { 
        
        //Buffering stack trace..
        if (count($aDebugTrace)>0) {
        
          $errStack = "Stack trace:" . "<br>";

          $i = 1;
          foreach ($aDebugTrace as $trace) {
            $errStack .= $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], "") . "<br>";
            $i=$i+1;
          }
        }
        
        echo json_encode([$errNo, $errMsg, $errScript, $errLine, $errStack]);
      } else {
        echo json_encode([$errNo]);
      }  

      if (!TESTING) {
        exit(1);
      } else {
        throw new Exception($errMsg);
      }
    };
    
    // Registering the error handling function..
    set_error_handler(self::$_trigger_error1);
    
    
    // Assigning the exception handling function..
    
    /**
            * Exception handling function
            *
            * @param Exception $e the exception thrown
            * @return void
            */
    self::$_throw1 = static function (\Throwable $e) {
  
      $errNo=$e->getCode(); 
      $errMsg=$e->getMessage();
      $errScript=$e->getFile();
      $errLine=$e->getLine(); 

      error_log(strtoupper(APP_NAME) . " " . "ERROR ($errNo): $errMsg : in script " . $errScript . ", line $errLine");

      // Logging the stack trace..
      $aDebugTrace = $e->getTrace();
      
      if (count($aDebugTrace)>0) {
 
        $aDebugTrace = array_reverse($aDebugTrace);
        
        error_log(strtoupper(APP_NAME) . " Stack trace:");

        $i = 1;
        foreach ($aDebugTrace as $trace) {
          error_log(strtoupper(APP_NAME) . " " . $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], ""));
          $i=$i+1;
        }
      }

      error_log(strtoupper(APP_NAME) . " " . "Ending Json...");

      //Json encode the error..
      if (DEBUG) { 

        //Buffering stack trace..
        if (count($aDebugTrace)>0) {
        
          $errStack = "Stack trace:" . "<br>";

          $i = 1;
          foreach ($aDebugTrace as $trace) {
            $errStack .= $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], "") . "<br>";
            $i=$i+1;
          }
        }

        echo json_encode([$errNo, $errMsg, $errScript, $errLine, $errStack]);
      } else {
        echo json_encode([$errNo]);
      }  

      if (!TESTING) {
        exit(1);
      } else {    
        throw new Exception($errMsg);
      }

    };
    
    // Registering the exception handling function
    set_exception_handler(self::$_throw1);
  
  }

  /**
      * Set the error handlers to log the error only  
      *
      * @return void
      * @access public
      */ 
  public static function setLogOnlyHandlers() 
  {

    // Assigning the error handling function..
    
    // Load the error resources..
    self::load();

    /**
            * Error handling function
            *
            * @param string $errNo the number of the error
            * @param string $errMsg the error message
            * @param string $errScript the script where the error happened
            * @param integer $errLine the line of code of the error
            * @return void
            */
    self::$_trigger_error1 = static function ($errNo, $errMsg, $errScript, $errLine) {
      
      error_log(strtoupper(APP_NAME) . " " . "ERROR ($errNo): $errMsg : in script " . $errScript . ", line $errLine");

      // Logging the stack trace..
      $aDebugTrace = debug_backtrace();
      
      if (count($aDebugTrace)>0) {
        
        $aDebugTrace = array_reverse($aDebugTrace);
        array_pop($aDebugTrace);
        
        error_log(strtoupper(APP_NAME) . " Stack trace:");

        $i = 1;
        foreach ($aDebugTrace as $trace) {
          error_log(strtoupper(APP_NAME) . " " . $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], ""));
          $i=$i+1;
        }
      }
      
      error_log(strtoupper(APP_NAME) . " " . "Continuing...");

    };

    // Registering the error handling function..
    set_error_handler(self::$_trigger_error1);
    
    
    // Assigning the exception handling function..
    
    /**
            * Exception handling function
            *
            * @param Exception $e the exception thrown
            * @return void
            */
    self::$_throw1 = static function (\Throwable $e) {
  
      $errNo=$e->getCode(); 
      $errMsg=$e->getMessage();
      $errScript=$e->getFile();
      $errLine=$e->getLine(); 

      error_log(strtoupper(APP_NAME) . " " . "ERROR ($errNo): $errMsg : in script " . $errScript . ", line $errLine");

      // Logging the stack trace..
      $aDebugTrace = $e->getTrace();
      
      if (count($aDebugTrace)>0) {
 
        $aDebugTrace = array_reverse($aDebugTrace);
        
        error_log(strtoupper(APP_NAME) . " Stack trace:");

        $i = 1;
        foreach ($aDebugTrace as $trace) {
          error_log(strtoupper(APP_NAME) . " " . $i . " " . $trace['function'] . "()" . " " . ((isset($trace['file'])) ? $trace['file'] . ":" : "") . isset1($trace['line'], ""));
          $i=$i+1;
        }
      }
      
      error_log(strtoupper(APP_NAME) . " " . "Continuing...");
    };
    
    // Registering the exception handling function
    set_exception_handler(self::$_throw1);
  }

  /**
      * Set back the error handlers  
      *
      * @return void
      * @access public
      */ 
  public static function setPreviousHandlers() 
  {
    // Restoring previous error handlers..
    if (self::$_old_error_handler === "setDefaultHandlers") {
      self::setDefaultHandlers();
    } else if (self::$_old_error_handler === "setRedirectHandlers") {
      self::setRedirectHandlers(self::$_old_error_handler_param1, self::$_old_error_handler_param2);
    } else if (self::$_old_error_handler === "setJSONHandlers") {
      self::setJSONHandlers();
    }
  }  
  
  /**
      * Error trigger 
      *
      * @param string $errNo the number of the error
      * @param string $errMsg the error message
      * @param string $errScript the script where the error happened
      * @param integer $errLine the line of code of the error
      * @return void
      * @access public
      */
  public static function trigger_error1($errNo, $errMsg, $errScript, $errLine) 
  {
    $trigger_error1 = self::$_trigger_error1;
    
    $trigger_error1($errNo, $errMsg, $errScript, $errLine);
  }
  
  /**
      * Exception trigger 
      *
      * @param Exception $e the exception to trigger
      * @return void
      * @access public
      */
  public static function throw1(\Throwable $e) 
  {
    $throw1 = self::$_throw1;
    
    $throw1($e);
  }
}
