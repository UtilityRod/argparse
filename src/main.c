#include <stdio.h>
#include <argparse.h>


int main(int argc, char ** argv)
{
    parser_t * parser = parser_init();
    parser_add_option(parser, 'z', INT, 1);
    parser_add_option(parser, 'Z', INT, 0);
    parser_parse_args(parser, argc, argv);
    parser_destroy(parser);
}
