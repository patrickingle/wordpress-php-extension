
void wp_load() {
  char *pszABSPath = INI_STR("ABSPATH");
  char *pszWPConfig = INI_STR("WPCONFIG");
 
   if (exists(pszWPConfig)) {
   } else if (exists("wp-config.php")) {
      // load wp-config.php into PHP environment
   } else if (exists("../wp-config.php")) {

   } else {
     //  wp-config.php does not exist
   }
}

wp_load();
 
