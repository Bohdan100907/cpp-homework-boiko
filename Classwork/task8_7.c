#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double determinant(double **matrix, size_t n)
{
    double result = 1.0;

    for (size_t i = 0; i < n; ++i)
    {
        size_t pivot = i;
        for (size_t r = i + 1; r < n; ++r)
        {
            if (fabs(matrix[r][i]) > fabs(matrix[pivot][i]))
            {
                pivot = r;
            }
        }

        if (fabs(matrix[pivot][i]) < 1e-12)
        {
            return 0.0;
        }

        if (pivot != i)
        {
            double *temporary = matrix[i];
            matrix[i] = matrix[pivot];
            matrix[pivot] = temporary;
            result = -result;
        }

        result *= matrix[i][i];
        for (size_t r = i + 1; r < n; ++r)
        {
            double factor = matrix[r][i] / matrix[i][i];
            for (size_t c = i; c < n; ++c)
            {
                matrix[r][c] -= factor * matrix[i][c];
            }
        }
    }

    return result;
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

    printf("Determinant: %.10g\n", determinant(matrix, n));

    for (size_t i = 0; i < n; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}