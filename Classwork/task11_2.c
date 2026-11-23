#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double a;
    printf("Enter a positive number: ");
    if (scanf("%lf", &a) != 1 || a <= 0)
    {
        printf("Invalid number.\n");
        return 1;
    }

    FILE *source = fopen("F.txt", "r");
    if (source == NULL)
    {
        printf("Could not open F.txt.\n");
        return 1;
    }

    FILE *selected = fopen("G.txt", "w");
    FILE *remaining = fopen("F.tmp", "w");
    if (selected == NULL || remaining == NULL)
    {
        printf("Could not create output files.\n");
        if (selected != NULL)
        {
            fclose(selected);
        }
        if (remaining != NULL)
        {
            fclose(remaining);
        }
        fclose(source);
        return 1;
    }

    double number;
    int readResult;
    int success = 1;

    while ((readResult = fscanf(source, "%lf", &number)) == 1)
    {
        FILE *destination = fabs(number) < a ? selected : remaining;
        if (fprintf(destination, "%.17g\n", number) < 0)
        {
            success = 0;
            break;
        }
    }

    if (readResult != EOF || ferror(source))
    {
        success = 0;
    }

    if (fclose(source) != 0)
    {
        success = 0;
    }
    if (fclose(selected) != 0)
    {
        success = 0;
    }
    if (fclose(remaining) != 0)
    {
        success = 0;
    }

    if (!success)
    {
        remove("F.tmp");
        printf("Error while processing the files.\n");
        return 1;
    }

    if (remove("F.txt") != 0 || rename("F.tmp", "F.txt") != 0)
    {
        printf("Could not update F.txt.\n");
        return 1;
    }

    printf("Values with absolute value less than %.6g were saved to G.txt.\n", a);
    return 0;
}