#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 3)
    {
        printf("Invalid n.\n");
        return 1;
    }

    double *v = malloc((n + 1) * sizeof(double));
    if (v == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 3.0 / 2.0;

    for (int i = 3; i <= n; ++i)
    {
        v[i] = ((double)(i - 2) / (i - 3)) * v[i - 1] -
               v[i - 2] * v[i - 3] + 1.0;
    }

    printf("v[%d] = %.10g\n", n, v[n]);

    free(v);
    return 0;
}