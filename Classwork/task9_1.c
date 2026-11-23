#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t n;

    printf("Enter n: ");
    if (scanf("%zu", &n) != 1 || n == 0 ||
        n > (size_t)-1 / sizeof(double))
    {
        printf("Invalid size.\n");
        return 1;
    }

    double *array = malloc(n * sizeof(double));
    if (array == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    printf("Enter %zu real numbers:\n", n);
    for (size_t i = 0; i < n; ++i)
    {
        if (scanf("%lf", &array[i]) != 1)
        {
            printf("Invalid input.\n");
            free(array);
            return 1;
        }
    }

    double sum = 0.0;
    for (size_t i = 0; i < n; ++i)
    {
        sum += array[i] * array[i];
    }

    printf("Sum of squares: %.10g\n", sum);

    free(array);
    return 0;
}