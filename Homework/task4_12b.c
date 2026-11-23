#include <stdio.h>

int main(void)
{
    double x;
    int n;

    printf("Enter x and n: ");
    if (scanf("%lf%d", &x, &n) != 2 || n < 2)
    {
        printf("Invalid input.\n");
        return 1;
    }

    double power = x * x;
    double y = 1.0 + power;
    for (int i = 3; i <= n; ++i)
    {
        power *= x;
        y += power;
    }

    printf("y = %.10g\n", y);
    return 0;
}