#include <stdio.h>
#include <math.h>

int main(void)
{
    double x;
    double epsilon;

    printf("Enter x and epsilon: ");
    if (scanf("%lf%lf", &x, &epsilon) != 2 ||
        x <= -1.0 || x >= 1.0 || epsilon <= 0.0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    double sum = 0.0;
    double power = x;

    for (int n = 1; n <= 1000000; n += 2)
    {
        double term = power / n;

        sum += term;
        if (fabs(term) <= epsilon)
        {
            printf("Sum: %.10lf\n", 2.0 * sum);
            return 0;
        }

        power *= x * x;
    }

    printf("Sum: %.10lf\n", sum);
    return 0;
}