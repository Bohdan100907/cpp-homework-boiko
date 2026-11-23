#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("x  ");
    for (int i = -1; i <= 1; ++i)
    {
        printf("|%+d", i);
    }
    printf("\n");

    printf("---");
    for (int i = -1; i <= 1; ++i)
    {
        printf("|---");
    }
    printf("\n");

    printf("F(x)");
    for (int i = -1; i <= 1; ++i)
    {
        double x = i;
        printf("|%.2f", exp(-(x * x)));
    }
    printf("\n");

    return 0;
}