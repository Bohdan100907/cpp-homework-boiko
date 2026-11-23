#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t n;

    printf("Enter n: ");
    if (scanf("%zu", &n) != 1 || n == 0 ||
        n > (size_t)-1 / sizeof(int))
    {
        printf("Invalid size.\n");
        return 1;
    }

    int *a = malloc(n * sizeof(int));
    if (a == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    printf("Enter %zu integers:\n", n);
    for (size_t i = 0; i < n; ++i)
    {
        if (scanf("%d", &a[i]) != 1)
        {
            printf("Invalid input.\n");
            free(a);
            return 1;
        }
    }

    int minimum = a[0];
    for (size_t i = 1; i < n; ++i)
    {
        if (a[i] < minimum)
        {
            minimum = a[i];
        }
    }

    printf("Minimum: %d\n", minimum);

    free(a);
    return 0;
}