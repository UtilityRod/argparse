#include <stdio.h>
#include <argparse.h>


int main(void)
{
    parser_t * parser = parser_init();
    parser_destroy(parser);
}
