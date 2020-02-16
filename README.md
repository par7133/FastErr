
 FastErr     
 
 FastErr class     
 
 @package  OpenGallery http://github.com/par7133      
 @author   Daniele Bonini <my25mb@aol.com>     
 @version  1.0     
 @access   public    
 @note You have to declare in your "config.inc" file - or whatever file you      
 use for the purpose, the following global constants:     
 define('APP_NAME', "YOUR_APP_NAME");     
 define('DEBUG', "true|false");    
 
 This class makes use of the global function isset1, declared in this way:     
      
 function isset1(&$var, $default=false) {     
   if (isset($var))    
     return $var;     
   } else {    
     return $default;     
   }    
 }    
