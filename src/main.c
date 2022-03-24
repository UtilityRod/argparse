#include <stdio.h>
#include <argparse.h>
#include <stdlib.h>

enum {opt_z = 'z', opt_C = 'C'};


int main(int argc, char ** argv)
{
    parser_t * parser = parser_create();
    parser_destroy(parser);
}
