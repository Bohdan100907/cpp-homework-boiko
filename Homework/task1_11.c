#include <stdio.h>

int main(void)
{
    char first[] = "Hello";
    char second[] = "World";

    printf("%s\n", first);
    printf("%s\n", second);

    printf("%s, %s!\n", first, second);
    printf("!!! %s, %s! !!!\n", first, second);

    return 0;
}