#include <stdio.h>
#include <argparse.h>
#include <stdlib.h>

enum {opt_z = 'z', opt_C = 'C'};


int main(int argc, char ** argv)
{
    parser_t * parser = parser_create();
    ssize_t check = parser_add_option(parser, 'A');
    printf("%ld\n", check);
    check = parser_add_option(parser, 'Z');
    printf("%ld\n", check);
    check = parser_add_option(parser, 'a');
    printf("%ld\n", check);
    check = parser_add_option(parser, 'z');
    printf("%ld\n", check);
    check = parser_add_option(parser, '@');
    printf("%ld\n", check);
    check = parser_add_option(parser, '[');
    printf("%ld\n", check);
    check = parser_add_option(parser, '`');
    printf("%ld\n", check);
    check = parser_add_option(parser, '{');
    printf("%ld\n", check);
    parser_destroy(parser);
}
