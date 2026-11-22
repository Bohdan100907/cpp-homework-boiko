#include <math.h>
#include <stdio.h>

int isPerfectSquare(int number)
{
    if (number < 0)
    {
        return 0;
    }

    long long root = (long long)sqrt((double)number);
    while ((root + 1) * (root + 1) <= number)
    {
        root++;
    }
    while (root * root > number)
    {
        root--;
    }

    return root * root == number;
}

int isPowerOfThree(int number)
{
    if (number < 1)
    {
        return 0;
    }

    while (number % 3 == 0)
    {
        number /= 3;
    }

    return number == 1;
}

int createInputFile(void)
{
    FILE *file = fopen("F.txt", "w");
    if (file == NULL)
    {
        return 0;
    }

    int number;
    printf("Enter integers, 0 to stop:\n");

    while (1)
    {
        if (scanf("%d", &number) != 1)
        {
            fclose(file);
            return 0;
        }
        if (number == 0)
        {
            break;
        }
        if (fprintf(file, "%d\n", number) < 0)
        {
            fclose(file);
            return 0;
        }
    }

    return fclose(file) == 0;
}

int createFilteredFiles(void)
{
    FILE *source = fopen("F.txt", "r");
    FILE *evenFile = fopen("G_even.txt", "w");
    FILE *powerFile = fopen("G_powers_of_3.txt", "w");
    FILE *squareFile = fopen("G_squares.txt", "w");

    if (source == NULL || evenFile == NULL || powerFile == NULL || squareFile == NULL)
    {
        if (source != NULL)
        {
            fclose(source);
        }
        if (evenFile != NULL)
        {
            fclose(evenFile);
        }
        if (powerFile != NULL)
        {
            fclose(powerFile);
        }
        if (squareFile != NULL)
        {
            fclose(squareFile);
        }
        return 0;
    }

    int number;
    int readResult;
    int success = 1;

    while ((readResult = fscanf(source, "%d", &number)) == 1)
    {
        if (number % 2 == 0 && fprintf(evenFile, "%d\n", number) < 0)
        {
            success = 0;
            break;
        }
        if (isPowerOfThree(number) && fprintf(powerFile, "%d\n", number) < 0)
        {
            success = 0;
            break;
        }
        if (isPerfectSquare(number) && fprintf(squareFile, "%d\n", number) < 0)
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
    if (fclose(evenFile) != 0)
    {
        success = 0;
    }
    if (fclose(powerFile) != 0)
    {
        success = 0;
    }
    if (fclose(squareFile) != 0)
    {
        success = 0;
    }

    return success;
}

int main(void)
{
    if (!createInputFile())
    {
        printf("Could not create F.txt or read the input.\n");
        return 1;
    }

    if (!createFilteredFiles())
    {
        printf("Could not create the result files.\n");
        return 1;
    }

    printf("Created F.txt, G_even.txt, G_powers_of_3.txt, and G_squares.txt.\n");
    return 0;
}