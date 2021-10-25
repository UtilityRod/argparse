#include <stdio.h>
#include <argparse.h>


int main(void)
{
    parser_t * parser = parser_init();
    int check = parser_get_value(parser);
    printf("%d\n", check);
    parser_destroy(parser);
}
