#include <stdio.h>

int main(void)
{
    long long number;
    printf("Enter an integer: ");
    if (scanf("%lld", &number) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    unsigned long long value = number >= 0
                                   ? (unsigned long long)number
                                   : (unsigned long long)(-(number + 1)) + 1;

    int count[10] = {0};
    if (value == 0)
    {
        count[0]++;
    }
    else
    {
        while (value != 0)
        {
            count[value % 10]++;
            value /= 10;
        }
    }

    int maximum = count[0];
    int digit = 0;
    for (int i = 1; i < 10; ++i)
    {
        if (count[i] > maximum)
        {
            maximum = count[i];
            digit = i;
        }
        else if (count[i] == maximum && i > digit)
        {
            digit = i;
        }
    }

    printf("Digit: %d\n", digit);
    return 0;
}