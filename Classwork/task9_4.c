#include <stdio.h>
#include <stdlib.h>

double **createMatrix2D(size_t n)
{
    if (n > (size_t)-1 / sizeof(double *))
    {
        return NULL;
    }

    double **matrix = calloc(n, sizeof(double *));
    if (matrix == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < n; ++i)
    {
        if (n > (size_t)-1 / sizeof(double))
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }

        matrix[i] = calloc(n, sizeof(double));
        if (matrix[i] == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

double *createMatrix1D(size_t n)
{
    if (n > (size_t)-1 / n ||
        n * n > (size_t)-1 / sizeof(double))
    {
        return NULL;
    }
    return calloc(n * n, sizeof(double));
}

void freeMatrix2D(double **matrix, size_t n)
{
    if (matrix == NULL)
    {
        return;
    }
    for (size_t i = 0; i < n; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int inputMatrix2D(double **matrix, size_t n)
{
    printf("Enter %zu x %zu matrix:\n", n, n);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (scanf("%lf", &matrix[i][j]) != 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

int inputMatrix1D(double *matrix, size_t n)
{
    printf("Enter %zu x %zu matrix:\n", n, n);
    for (size_t i = 0; i < n * n; ++i)
    {
        if (scanf("%lf", &matrix[i]) != 1)
        {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    size_t n;
    printf("Enter n: ");
    if (scanf("%zu", &n) != 1 || n == 0)
    {
        printf("Invalid size.\n");
        return 1;
    }

    printf("Two-dimensional representation:\n");
    double **matrix2D = createMatrix2D(n);
    if (matrix2D == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    if (!inputMatrix2D(matrix2D, n))
    {
        printf("Invalid input.\n");
        freeMatrix2D(matrix2D, n);
        return 1;
    }

    freeMatrix2D(matrix2D, n);

    printf("One-dimensional representation:\n");
    double *matrix1D = createMatrix1D(n);
    if (matrix1D == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    if (!inputMatrix1D(matrix1D, n))
    {
        printf("Invalid input.\n");
        free(matrix1D);
        return 1;
    }

    free(matrix1D);
    return 0;
}