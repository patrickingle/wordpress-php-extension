
int wp_did_header = 0;

if (wp_did_header == 0) {
    wp_did_header = 1;

    #include "wp-load.c";
 
    wp();

    #include "template-loader.c";
}
