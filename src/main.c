#include <stdio.h>
#include <argparse.h>
#include <stdlib.h>

enum {opt_z = 'z', opt_C = 'C'};


int main(int argc, char ** argv)
{
    parser_t * parser = parser_create();
    parser_add_option(parser, 'A');
    parser_add_option(parser, 'Z');
    parser_add_option(parser, 'a');
    parser_add_option(parser, 'z');
    parser_add_option(parser, '@');
    parser_add_option(parser, '[');
    parser_add_option(parser, '`');
    parser_add_option(parser, '{');

    if (parse_args(parser, argc, argv) < 0)
    {
        return -1;
    }
    
    char * a_arg = parser_get_arg(parser, 'a');
    char * cap_a_arg = parser_get_arg(parser, 'A');
    char * z_arg = parser_get_arg(parser, 'z');
    char * cap_z_arg = parser_get_arg(parser, 'Z');
    printf("a: %s\n", a_arg);
    printf("A: %s\n", cap_a_arg);
    printf("z: %s\n", z_arg);
    printf("Z: %s\n", cap_z_arg);
    parser_destroy(parser);
}
