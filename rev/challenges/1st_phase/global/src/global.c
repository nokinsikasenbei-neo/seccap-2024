#include <stdio.h>
#include <string.h>

char *a = "FLAG{H4rdc0d1ng_15_d4ng3r0u5}";
char *dummy = "FLAG{this_is_not_the_flag}";

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        printf("Usage: %s <password>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], dummy) == 0)
    {
        puts("No! This is not flag");
        puts("The true flag is somewhere");
    }
    else
    {
        puts("Incorrect!");
    }

} 