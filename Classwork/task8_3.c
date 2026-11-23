#include <stdio.h>
#include <stdlib.h>

int inputMatrix(double **matrix, size_t m, size_t n)
{
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            printf("matrix[%zu][%zu] = ", i, j);
            if (scanf("%lf", &matrix[i][j]) != 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

double **createMatrix(size_t m, size_t n)
{
    if (m == 0 || n == 0 ||
        m > (size_t)-1 / sizeof(double *) ||
        n > (size_t)-1 / sizeof(double))
    {
        return NULL;
    }

    double **matrix = malloc(m * sizeof(double *));
    if (matrix == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < m; ++i)
    {
        matrix[i] = malloc(n * sizeof(double));
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

void freeMatrix(double **matrix, size_t m)
{
    for (size_t i = 0; i < m; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void)
{
    size_t m;
    size_t n;

    printf("Enter number of rows m: ");
    if (scanf("%zu", &m) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter number of columns n: ");
    if (scanf("%zu", &n) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    double **matrix = createMatrix(m, n);
    if (matrix == NULL)
    {
        printf("Invalid size or not enough memory.\n");
        return 1;
    }

    if (!inputMatrix(matrix, m, n))
    {
        printf("Invalid input.\n");
        freeMatrix(matrix, m);
        return 1;
    }

    printf("Matrix:\n");
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            printf("%.10g ", matrix[i][j]);
        }
        printf("\n");
    }

    freeMatrix(matrix, m);
    return 0;
}