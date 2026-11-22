#include <stdio.h>
#include <stdlib.h>

int writeArrayToFile(const char *filename, const double array[], int length)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return 0;
    }

    for (int i = 0; i < length; i++)
    {
        if (fprintf(file, "%.17g\n", array[i]) < 0)
        {
            fclose(file);
            return 0;
        }
    }

    return fclose(file) == 0;
}

int printArrayFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0;
    }

    double number;
    int first = 1;

    while (fscanf(file, "%lf", &number) == 1)
    {
        if (!first)
        {
            printf(", ");
        }

        printf("%g", number);
        first = 0;
    }

    int success = feof(file) && !ferror(file);
    if (fclose(file) != 0)
    {
        success = 0;
    }
    printf("\n");
    return success;
}

int main(void)
{
    int length;
    char filename[256];

    printf("Enter array length: ");
    if (scanf("%d", &length) != 1 || length <= 0)
    {
        printf("Invalid array length.\n");
        return 1;
    }

    double *array = malloc((size_t)length * sizeof(double));
    if (array == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    printf("Enter %d numbers: ", length);
    for (int i = 0; i < length; i++)
    {
        if (scanf("%lf", &array[i]) != 1)
        {
            printf("Invalid number.\n");
            free(array);
            return 1;
        }
    }

    printf("Enter file name: ");
    if (scanf("%255s", filename) != 1)
    {
        printf("Invalid file name.\n");
        free(array);
        return 1;
    }

    if (!writeArrayToFile(filename, array, length))
    {
        printf("Could not write to the file.\n");
        free(array);
        return 1;
    }

    free(array);

    printf("Numbers from the file: ");
    if (!printArrayFromFile(filename))
    {
        printf("Could not read the file.\n");
        return 1;
    }

    return 0;
}