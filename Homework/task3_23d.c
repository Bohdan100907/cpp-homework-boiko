#include <stdio.h>

double sRelu(double tl, double tr, double al, double ar, double x)
{
    if (x <= tl)
    {
        return tl + al * (x - tl);
    }
    if (x < tr)
    {
        return 0.0;
    }
    return tr + ar * (x - tr);
}

int main(void)
{
    double tl;
    double tr;
    double al;
    double ar;
    double x;

    printf("Enter tl, tr, al, ar and x: ");
    if (scanf("%lf%lf%lf%lf%lf", &tl, &tr, &al, &ar, &x) != 5)
    {
        printf("Invalid input.\n");
        return 1;
    }

    printf("sReLu = %.10g\n", sRelu(tl, tr, al, ar, x));
    return 0;
}