#include <stdio.h>

int isNatural(int n)
{
    return n >= 0;
}

int lastDigit(int n)
{
    if (n < 0)
    {
        n = -n;
    }
    return n % 5;
}

int isMultiple(long long n, long long m)
{
    return m != 0 && n % m == 0;
}

int areMultiples(long long n, long long k, long long m)
{
    return m != 0 && n % m == 0 && k % m == 0;
}

int main(void)
{
    int choice;
    printf("Choose point (1-a, 2-b, 3-v, 4-g): ");
    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    if (choice == 1)
    {
        int n;
        printf("Enter n: ");
        if (scanf("%d", &n) == 1)
        {
            printf("%s\n", isNatural(n) ? "Yes" : "No");
        }
        else
        {
            printf("Invalid input.\n");
        }
    }
    else if (choice == 2)
    {
        int n;
        printf("Enter n: ");
        if (scanf("%d", &n) == 1)
        {
            printf("%d\n", lastDigit(n));
        }
        else
        {
            printf("Invalid input.\n");
        }
    }
    else if (choice == 3)
    {
        long long n;
        long long m;
        printf("Enter n and m: ");
        if (scanf("%lld%lld", &n, &m) == 2)
        {
            printf("%s\n", isMultiple(n, m) ? "Yes" : "No");
        }
        else
        {
            printf("Invalid input.\n");
        }
    }
    else if (choice == 4)
    {
        long long n;
        long long k;
        long long m;
        printf("Enter n, k and m: ");
        if (scanf("%lld%lld%lld", &n, &k, &m) == 3)
        {
            printf("%s\n", areMultiples(n, k, m) ? "Yes" : "No");
        }
        else
        {
            printf("Invalid input.\n");
        }
    }
    else
    {
        printf("Invalid choice.\n");
        return 1;
    }

    return 0;
}