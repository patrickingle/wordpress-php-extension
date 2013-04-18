PHP_ARG_ENABLE(wordpress, where to enable wordpress,
[ --enable-wordpress Enable Wordpress])

if test "$PHP_WORDPRESS" = "yes"; then
   PHP_REQUIRE_CXX()
   PHP_SUBST(WORDPRESS_SHARED_LIBADD)
   PHP_ADD_LIBRARY(stdc++, 1, WORDPRESS_SHARED_LIBADD)
   AC_DEFINE(HAVE_WORDPRESS,1, [Whether you have wordpress])
   PHP_NEW_EXTENSION(wordpress,wordpress.c wordpress.cc, $ext_shared)
fi
