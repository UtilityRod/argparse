#include <stdio.h>
#include <argparse.h>
#include <stdlib.h>

enum {opt_z = 'z', opt_C = 'C'};


int main(int argc, char ** argv)
{
    parser_t * parser = parser_init();

    parser_add_option(parser, opt_z, INT, 1);
    parser_add_option(parser, opt_C, INT, 0);
    int parse_check = parser_parse_args(parser, argc, argv);
    
    if (parse_check == -1)
    {
        parser_destroy(parser);
        exit(-1);
    }
    
    fputs("---------------------------------------------\n", stdout);
    fputs("Arguments\n", stdout);
    printf("-%c -%c\n", opt_z, opt_C);
    fputs("---------------------------------------------\n", stdout);
    fputs("Option: z\n", stdout);
    fputs("Invoked: ", stdout);
    parser_opt_invoked(parser, opt_z) ? fputs("Yes\n", stdout) : fputs("No\n", stdout);
    fputs("Associated argument: ", stdout);
    char * arg = parser_get_optarg(parser, opt_z);
    arg ? fprintf(stdout, "%s\n", arg) : fputs("None\n", stdout);
    fputs("---------------------------------------------\n", stdout);
    fputs("Option: C\n", stdout);
    fputs("Invoked: ", stdout);
    parser_opt_invoked(parser, opt_C) ? fputs("Yes\n", stdout) : fputs("No\n", stdout);
    fputs("Associated argument: ", stdout);
    arg = parser_get_optarg(parser, opt_C);
    arg ? fprintf(stdout, "%s\n", arg) : fputs("None\n", stdout);
    fputs("---------------------------------------------\n", stdout);
    fputs("Extra command line arguments\n", stdout);
    char ** args = parser_get_arguments(parser);
    if (args)
    {
        while((arg = *(args++))) 
        { 
            printf("%s\n", arg);
        }
    }
    else
    {
        fputs("None\n", stdout);
    }
    
    parser_destroy(parser);
}
