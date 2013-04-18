#ifndef PHP_WORDPRESS_H
#define PHP_WORDPRESS_H

#define PHP_WORDPRESS_VERSION "3.5"
#define PHP_WORDPRESS_EXTNAME "wordpress"

PHP_FUNCTION(wp_start);

extern zend_module_entry wordpress_module_entry;
#define phpext_wordpress_ptr &wordpress_module_entry;

#endif
