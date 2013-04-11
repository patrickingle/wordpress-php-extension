#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_ini.h"

#include "php_wordpress.h"

// wordpress files

// declaraion of a custom my_function()
PHP_MINIT_FUNCTION(wordpress);
PHP_MSHUTDOWN_FUNCTION(wordpress);
PHP_MINFO_FUNCTION(wordpress);

static function_entry wordpress_functions[] = {
	PHP_FE(wp_load, NULL)
	{NULL, NULL, NULL}
};

zend_module_entry wordpress_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_WORDPRESS_EXTNAME,
    wordpress_functions,
    PHP_MINIT(wordpress),
    PHP_MSHUTDOWN(wordpress),
    NULL,
    NULL,
    PHP_MINFO(wordpress),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_WORDPRESS_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

PHP_INI_BEGIN()
PHP_INI_ENTRY("ABSPATH","/var/www",PHP_INI_ALL,NULL)
PHP_INI_ENTRY("WPADMIN","wp-admin",PHP_INI_ALL,NULL)
PHP_INI_ENTRY("WPINC","wp-includes",PHP_INI_ALL,NULL)
PHP_INI_ENTRY("WPLOGIN","wp-login",PHP_INI_ALL,NULL)
PHP_INI_ENTRY("VERSION","3.5",PHP_INI_ALL,NULL)
PHP_INI_ENTRY("WP_MEMORY_LIMIT","40M",PHP_INI_ALL,NULL)
PHP_INI_ENTRY("WP_MAX_MEMORY_LIMIT","256M",PHP_INI_ALL,NULL)
PHP_INI_ENTRY("WP_DEBUG","FALSE",PHP_INI_ALL,NULL)
PHP_INI_ENTRY("WP_DEBUG_DISPLAY","FALSE",PHP_INI_ALL,NULL)
PHP_INI_ENTRY("WP_DEBUG_LOG","FALSE",PHP_INI_ALL,NULL)
PHP_INI_END()

PHP_MINIT_FUNCTION(wordpress)
{
   REGISTER_INI_ENTRIES();

   return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(wordpress)
{
   UNREGISTER_INI_ENTRIES();

   return SUCCESS;
}

PHP_MINFO_FUNCTION(wordpress)
{
   php_info_print_table_start();
   php_info_print_table_row(2, "Build Date", __DATE__);
   php_info_print_table_row(2, "Build Time", __TIME__);
   php_info_print_table_end();

   DISPLAY_INI_ENTRIES();
}

ZEND_GET_MODULE(wordpress)

PHP_FUNCTION(wp_load)
{
    char *pszAbsPath = INI_STR("ABSPATH");

    RETURN_STRING(pszAbsPath, 1);
}


