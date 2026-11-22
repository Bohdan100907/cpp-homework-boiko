#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char surname[100];
    char city[100];
    char street[100];
    int building;
    int apartment;
} Resident;

int findResidentsWithSameAddress(const Resident residents[], size_t count,
                                 size_t *first, size_t *second)
{
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = i + 1; j < count; j++)
        {
            int sameAddress =
                strcmp(residents[i].street, residents[j].street) == 0 &&
                residents[i].building == residents[j].building &&
                residents[i].apartment == residents[j].apartment;
            int differentCities = strcmp(residents[i].city, residents[j].city) != 0;

            if (sameAddress && differentCities)
            {
                *first = i;
                *second = j;
                return 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    size_t count;
    printf("Enter number of residents: ");
    if (scanf("%zu", &count) != 1 || count < 2 ||
        count > (size_t)-1 / sizeof(Resident))
    {
        printf("Invalid number of residents.\n");
        return 1;
    }

    Resident *residents = malloc(count * sizeof(Resident));
    if (residents == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    for (size_t i = 0; i < count; i++)
    {
        printf("Resident %zu surname: ", i + 1);
        if (scanf(" %99[^\n]", residents[i].surname) != 1)
        {
            free(residents);
            printf("Invalid input.\n");
            return 1;
        }

        printf("Resident %zu city: ", i + 1);
        if (scanf(" %99[^\n]", residents[i].city) != 1)
        {
            free(residents);
            printf("Invalid input.\n");
            return 1;
        }

        printf("Resident %zu street: ", i + 1);
        if (scanf(" %99[^\n]", residents[i].street) != 1)
        {
            free(residents);
            printf("Invalid input.\n");
            return 1;
        }

        printf("Enter building and apartment: ");
        if (scanf("%d %d", &residents[i].building, &residents[i].apartment) != 2)
        {
            free(residents);
            printf("Invalid input.\n");
            return 1;
        }
    }

    size_t first;
    size_t second;
    if (findResidentsWithSameAddress(residents, count, &first, &second))
    {
        printf("%s from %s and %s from %s have the same street address.\n",
               residents[first].surname,
               residents[first].city,
               residents[second].surname,
               residents[second].city);
    }
    else
    {
        printf("No matching residents found.\n");
    }

    free(residents);
    return 0;
}