#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    size_t size;
    double *values;
} Vector;

int inputVector(Vector *vector)
{
    printf("Enter vector size: ");
    if (scanf("%zu", &vector->size) != 1 || vector->size == 0)
    {
        return 0;
    }

    if (vector->size > (size_t)-1 / sizeof(double))
    {
        return 0;
    }

    vector->values = malloc(vector->size * sizeof(double));
    if (vector->values == NULL)
    {
        vector->size = 0;
        return 0;
    }

    printf("Enter %zu real numbers:\n", vector->size);
    for (size_t i = 0; i < vector->size; ++i)
    {
        if (scanf("%lf", &vector->values[i]) != 1)
        {
            free(vector->values);
            vector->values = NULL;
            vector->size = 0;
            return 0;
        }
    }

    return 1;
}

void outputVector(const Vector *vector)
{
    printf("Vector: ");
    for (size_t i = 0; i < vector->size; ++i)
    {
        printf("%g", vector->values[i]);
        if (i + 1 < vector->size)
        {
            printf(", ");
        }
    }
    printf("\n");
}

void freeVector(Vector *vector)
{
    free(vector->values);
    vector->values = NULL;
    vector->size = 0;
}

int main(void)
{
    Vector vector = {0, NULL};

    if (!inputVector(&vector))
    {
        printf("Invalid input or not enough memory.\n");
        freeVector(&vector);
        return 1;
    }

    outputVector(&vector);
    freeVector(&vector);

    return 0;
}