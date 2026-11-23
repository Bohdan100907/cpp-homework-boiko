#include <stdio.h>
#include <math.h>

int main(void)
{
    double a;
    double b;
    double angle;

    printf("Enter two sides and the included angle in degrees: ");
    if (scanf("%lf%lf%lf", &a, &b, &angle) != 3 ||
        a <= 0.0 || b <= 0.0 || angle <= 0.0 || angle >= 180.0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    double radians = angle * acos(-1.0) / 180.0;
    double area = 0.5 * a * b * sin(radians);

    printf("Area: %.10g\n", area);
    return 0;
}