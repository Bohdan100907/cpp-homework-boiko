#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double **allocateMatrix(int rows, int columns)
{
    double **matrix;
    int i;

    matrix = (double **)malloc((size_t)rows * sizeof(double *));
    if (matrix == NULL)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc((size_t)columns * sizeof(double));
        if (matrix[i] == NULL)
        {
            int j;

            for (j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

void freeMatrix(double **matrix, int rows)
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

void printMatrix(double **matrix, int rows, int columns)
{
    int i;
    int j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("%8.2lf", matrix[i][j]);
        }
        printf("\n");
    }
}

double **addColumnAtBeginning(double **matrix, int rows, int *columns)
{
    double **result;
    int i;
    int j;

    result = allocateMatrix(rows, *columns + 1);
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < rows; i++)
    {
        result[i][0] = (double)(rand() % 201 - 100) / 10.0;
        for (j = 0; j < *columns; j++)
        {
            result[i][j + 1] = matrix[i][j];
        }
    }

    (*columns)++;
    return result;
}

int main(void)
{
    int rows;
    int columns;
    int i;
    int j;
    double **matrix;
    double **updatedMatrix;

    printf("Enter number of rows: ");
    if (scanf("%d", &rows) != 1 || rows <= 0)
    {
        printf("Invalid number of rows.\n");
        return 1;
    }

    printf("Enter number of columns: ");
    if (scanf("%d", &columns) != 1 || columns <= 0)
    {
        printf("Invalid number of columns.\n");
        return 1;
    }

    matrix = allocateMatrix(rows, columns);
    if (matrix == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            matrix[i][j] = (double)(rand() % 201 - 100) / 10.0;
        }
    }

    printf("Original matrix:\n");
    printMatrix(matrix, rows, columns);

    updatedMatrix = addColumnAtBeginning(matrix, rows, &columns);
    if (updatedMatrix == NULL)
    {
        printf("Memory allocation failed.\n");
        freeMatrix(matrix, rows);
        return 1;
    }

    freeMatrix(matrix, rows);

    printf("Matrix after adding a column at the beginning:\n");
    printMatrix(updatedMatrix, rows, columns);

    freeMatrix(updatedMatrix, rows);
    return 0;
}
