PHP_ARG_ENABLE(wordpress, where to enable wordpress,
[ --enable-wordpress Enable Wordpress])

if test "$PHP_WORDPRESS" = "yes"; then
   AC_DEFINE(HAVE_WORDPRESS,1, [Whether you have wordpress])
   PHP_NEW_EXTENSION(wordpress,wordpress.c, $ext_shared)
fi
