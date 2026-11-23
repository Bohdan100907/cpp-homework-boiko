#include <stdio.h>
#include <stdlib.h>

void transpose(double **matrix, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            double temporary = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temporary;
        }
    }
}

int main(void)
{
    size_t n;
    printf("Enter matrix size n: ");
    if (scanf("%zu", &n) != 1 || n == 0)
    {
        printf("Invalid size.\n");
        return 1;
    }

    double **matrix = malloc(n * sizeof(double *));
    if (matrix == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    for (size_t i = 0; i < n; ++i)
    {
        matrix[i] = malloc(n * sizeof(double));
        if (matrix[i] == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(matrix[j]);
            }
            free(matrix);
            printf("Not enough memory.\n");
            return 1;
        }
    }

    printf("Enter matrix elements:\n");
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (scanf("%lf", &matrix[i][j]) != 1)
            {
                for (size_t k = 0; k < n; ++k)
                {
                    free(matrix[k]);
                }
                free(matrix);
                printf("Invalid input.\n");
                return 1;
            }
        }
    }

    transpose(matrix, n);

    printf("Transposed matrix:\n");
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            printf("%.10g ", matrix[i][j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < n; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}