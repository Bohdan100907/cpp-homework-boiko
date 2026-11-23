#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t m;
    size_t n;
    long long k;

    printf("Enter number of rows m: ");
    if (scanf("%zu", &m) != 1 || m == 0)
    {
        printf("Invalid number of rows.\n");
        return 1;
    }

    printf("Enter number of columns n: ");
    if (scanf("%zu", &n) != 1 || n == 0)
    {
        printf("Invalid number of columns.\n");
        return 1;
    }

    printf("Enter k: ");
    if (scanf("%lld", &k) != 1)
    {
        printf("Invalid k.\n");
        return 1;
    }

    long long **a = malloc(m * sizeof(long long *));
    if (a == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    for (size_t i = 0; i < m; ++i)
    {
        a[i] = malloc(n * sizeof(long long));
        if (a[i] == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(a[j]);
            }
            free(a);
            printf("Not enough memory.\n");
            return 1;
        }
    }

    printf("Enter matrix elements:\n");
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (scanf("%lld", &a[i][j]) != 1)
            {
                for (size_t r = 0; r < m; ++r)
                {
                    free(a[r]);
                }
                free(a);
                printf("Invalid input.\n");
                return 1;
            }
        }
    }

    long long sum = 0;
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if ((long long)i - (long long)j == k && a[i][j] < 100)
            {
                sum += a[i][j];
            }
        }
    }

    printf("Sum: %lld\n", sum);

    for (size_t i = 0; i < m; ++i)
    {
        free(a[i]);
    }
    free(a);
    return 0;
}