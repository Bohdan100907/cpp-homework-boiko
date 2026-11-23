#include <stdio.h>

int main(void)
{
    double matrix[3][3] = {
        {1.0, 0.23, 0.0},
        {4.56, 7.8, 9.0},
        {0.0, 0.0, 0.0}
    };
    int i;
    int j;
    double a;

    printf("Enter i, j and a: ");
    if (scanf("%d%d%lf", &i, &j, &a) != 3 ||
        i < 0 || i >= 3 || j < 0 || j >= 3)
    {
        printf("Invalid input.\n");
        return 1;
    }

    matrix[i][j] = a;

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            printf("%.10g ", matrix[row][column]);
        }
        printf("\n");
    }

    return 0;
}