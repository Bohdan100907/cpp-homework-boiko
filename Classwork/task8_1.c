#include <stdio.h>

int main(void)
{
    int matrix[3][3] = {
        {1, 2, 3},
        {7, 8, 9},
        {4, 5, 6}
    };
    int m;
    int n;

    printf("Enter M and N: ");
    if (scanf("%d%d", &m, &n) != 2)
    {
        printf("Invalid input.\n");
        return 1;
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (matrix[i][j] == m)
            {
                matrix[i][j] = n;
            }
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}