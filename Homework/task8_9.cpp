#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n <= 0 || n >= 200) {
        printf("n must satisfy 0 < n < 200\n");
        return 1;
    }

    double (*a)[2 * 200] = malloc((size_t)n * sizeof(*a));
    if (a == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2 * n; ++j) {
            a[i][j] = 0.0;
        }

        for (int j = 0; j < n; ++j) {
            if (scanf("%lf", &a[i][j]) != 1) {
                free(a);
                return 1;
            }
        }
        a[i][n + i] = 1.0;
    }

    for (int column = 0; column < n; ++column) {
        int pivot = column;

        for (int row = column + 1; row < n; ++row) {
            if (fabs(a[row][column]) > fabs(a[pivot][column])) {
                pivot = row;
            }
        }

        if (fabs(a[pivot][column]) < 1e-12) {
            printf("The matrix is singular and has no inverse.\n");
            free(a);
            return 0;
        }

        if (pivot != column) {
            for (int j = 0; j < 2 * n; ++j) {
                double temp = a[column][j];
                a[column][j] = a[pivot][j];
                a[pivot][j] = temp;
            }
        }

        double divisor = a[column][column];
        for (int j = 0; j < 2 * n; ++j) {
            a[column][j] /= divisor;
        }

        for (int row = 0; row < n; ++row) {
            if (row == column) {
                continue;
            }

            double factor = a[row][column];
            if (factor != 0.0) {
                for (int j = 0; j < 2 * n; ++j) {
                    a[row][j] -= factor * a[column][j];
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                printf(" ");
            }
            printf("%.6lf", a[i][n + j]);
        }
        printf("\n");
    }

    free(a);
    return 0;
}
