#include <stdio.h>
#include <argparse.h>
#include <stdlib.h>


int main(int argc, char ** argv)
{
    parser_t * parser = parser_init();
    parser_add_option(parser, 'z', INT, 1);
    parser_add_option(parser, 'C', INT, 0);
    int parse_check = parser_parse_args(parser, argc, argv);
    
    if (parse_check == -1)
    {
        parser_destroy(parser);
        exit(-1);
    }
    
    if (option_check_invoked(parser, 'z'))
    {
        printf("%s\n", option_get_argument(parser, 'z'));
    }
    
    parser_destroy(parser);
}
