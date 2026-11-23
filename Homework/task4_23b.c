#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid n.\n");
        return 1;
    }

    double *y = malloc((size_t)n * sizeof(double));
    if (y == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; ++i)
    {
        if (scanf("%lf", &y[i]) != 1)
        {
            printf("Invalid input.\n");
            free(y);
            return 1;
        }
    }

    double z0 = y[0] <= -1.0 || y[0] >= 1.0 ? y[0] : 2.0;
    if (z0 < 0.0)
    {
        z0 = -z0;
    }
    double minimum = z0;

    for (int i = 1; i < n; ++i)
    {
        double z = y[i] <= -1.0 || y[i] >= 1.0 ? y[i] : 2.0;
        if (z < 0.0)
        {
            z = -z;
        }
        if (z < minimum)
        {
            minimum = z;
        }
    }

    printf("Minimum: %.10g\n", minimum);

    free(y);
    return 0;
}