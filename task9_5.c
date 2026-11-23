#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int **inputMatrix(int *rows, int *columns)
{
    int **matrix;
    int i;
    int j;

    printf("Enter number of rows: ");
    scanf("%d", rows);
    printf("Enter number of columns: ");
    scanf("%d", columns);

    if (*rows <= 0 || *columns <= 0)
    {
        printf("Matrix dimensions must be positive.\n");
        return NULL;
    }

    matrix = (int **)malloc((size_t)(*rows) * sizeof(int *));
    if (matrix == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    for (i = 0; i < *rows; i++)
    {
        matrix[i] = (int *)malloc((size_t)(*columns) * sizeof(int));
        if (matrix[i] == NULL)
        {
            int k;
            for (k = 0; k < i; k++)
            {
                free(matrix[k]);
            }
            free(matrix);
            printf("Memory allocation failed.\n");
            return NULL;
        }
    }

    printf("Enter matrix elements:\n");
    for (i = 0; i < *rows; i++)
    {
        for (j = 0; j < *columns; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    return matrix;
}

void freeMatrix(int **matrix, int rows)
{
    int i;

    if (matrix == NULL)
    {
        return;
    }

    for (i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int matrixRank(int **matrix, int rows, int columns)
{
    double **copy;
    int rank = 0;
    int row;
    int column;

    if (matrix == NULL || rows <= 0 || columns <= 0)
    {
        return 0;
    }

    copy = (double **)malloc((size_t)rows * sizeof(double *));
    if (copy == NULL)
    {
        return -1;
    }

    for (row = 0; row < rows; row++)
    {
        copy[row] = (double *)malloc((size_t)columns * sizeof(double));
        if (copy[row] == NULL)
        {
            int i;
            for (i = 0; i < row; i++)
            {
                free(copy[i]);
            }
            free(copy);
            return -1;
        }

        for (column = 0; column < columns; column++)
        {
            copy[row][column] = (double)matrix[row][column];
        }
    }

    for (column = 0; column < columns && rank < rows; column++)
    {
        int pivot = rank;

        for (row = rank + 1; row < rows; row++)
        {
            if (fabs(copy[row][column]) > fabs(copy[pivot][column]))
            {
                pivot = row;
            }
        }

        if (fabs(copy[pivot][column]) > 1e-10)
        {
            if (pivot != rank)
            {
                double *temporary = copy[pivot];
                copy[pivot] = copy[rank];
                copy[rank] = temporary;
            }

            for (row = rank + 1; row < rows; row++)
            {
                double factor = copy[row][column] / copy[rank][column];
                int j;

                for (j = column; j < columns; j++)
                {
                    copy[row][j] -= factor * copy[rank][j];
                }
            }

            rank++;
        }
    }

    for (row = 0; row < rows; row++)
    {
        free(copy[row]);
    }
    free(copy);

    return rank;
}

int main(void)
{
    int rows;
    int columns;
    int rank;
    int **matrix = inputMatrix(&rows, &columns);

    if (matrix == NULL)
    {
        return 1;
    }

    rank = matrixRank(matrix, rows, columns);
    if (rank == -1)
    {
        printf("Memory allocation failed.\n");
        freeMatrix(matrix, rows);
        return 1;
    }

    printf("Matrix rank: %d\n", rank);

    freeMatrix(matrix, rows);
    return 0;
}

