
 FastErr     
 
 FastErr class     
 
 @package  OpenGallery http://github.com/par7133      
 @author   Daniele Bonini <code@gaox.io>     
 @version  1.0     
 @phpver   5.6 to 7.3      
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

For any need of software additions, plugins and improvements please write to <a href="mailto:info@5mode.com">info@5mode.com</a>  

To help please donate by clicking <a href="https://gaox.io/l/dona1">https://gaox.io/l/dona1</a> and filling the form.  

Feedback: <a href="code@gaox.io">code@gaox.io</a>
