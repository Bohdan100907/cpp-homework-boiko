#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    long long square;
    long long cube;
} PowerValues;

PowerValues *calculatePowers(const int *array, size_t n)
{
    PowerValues *values = malloc(n * sizeof(PowerValues));
    if (values == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < n; ++i)
    {
        long long value = array[i];
        values[i].square = value * value;
        values[i].cube = value * value * value;
    }

    return values;
}

int main(void)
{
    int array[100];
    size_t n;

    printf("Enter number of elements (1-100): ");
    if (scanf("%zu", &n) != 1 || n == 0 || n > 100)
    {
        printf("Invalid size.\n");
        return 1;
    }

    printf("Enter %zu integers:\n", n);
    for (size_t i = 0; i < n; ++i)
    {
        if (scanf("%d", &array[i]) != 1)
        {
            printf("Invalid input.\n");
            return 1;
        }
    }

    PowerValues *values = calculatePowers(array, n);
    if (values == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    for (size_t i = 0; i < n; ++i)
    {
        printf("%d: square = %lld, cube = %lld\n",
               array[i], values[i].square, values[i].cube);
    }

    free(values);
    return 0;
}