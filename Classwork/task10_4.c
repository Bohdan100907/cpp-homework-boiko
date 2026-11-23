#include <stdio.h>

typedef struct
{
    int numerator;
    unsigned int denominator;
} Rational;

unsigned int gcd(unsigned int a, unsigned int b)
{
    while (b != 0)
    {
        unsigned int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

Rational normalize(Rational value)
{
    if (value.denominator == 0)
    {
        value.denominator = 1;
        return value;
    }

    unsigned int numerator = value.numerator < 0
                                 ? (unsigned int)(-(value.numerator + 1)) + 1
                                 : (unsigned int)value.numerator;
    unsigned int divisor = gcd(numerator, value.denominator);

    if (divisor != 0)
    {
        numerator /= divisor;
        value.denominator /= divisor;
    }

    value.numerator = value.numerator < 0
                          ? -(int)numerator
                          : (int)numerator;

    return value;
}

Rational add(Rational a, Rational b)
{
    Rational result;
    result.numerator = (int)((long long)a.numerator * b.denominator +
                             (long long)b.numerator * a.denominator);
    result.denominator = a.denominator * b.denominator;
    return normalize(result);
}

Rational multiply(Rational a, Rational b)
{
    Rational result;
    result.numerator = (int)((long long)a.numerator * b.numerator);
    result.denominator = a.denominator * b.denominator;
    return normalize(result);
}

int compare(Rational a, Rational b)
{
    long long left = (long long)a.numerator * b.denominator;
    long long right = (long long)b.numerator * a.denominator;

    if (left < right)
    {
        return -1;
    }
    if (left > right)
    {
        return 1;
    }
    return 0;
}

int inputRational(Rational *value)
{
    printf("Enter numerator and positive denominator: ");
    if (scanf("%d%u", &value->numerator, &value->denominator) != 2 ||
        value->denominator == 0)
    {
        return 0;
    }
    *value = normalize(*value);
    return 1;
}

void outputRational(Rational value)
{
    printf("%d/%u", value.numerator, value.denominator);
}

int main(void)
{
    Rational first;
    Rational second;

    if (!inputRational(&first) || !inputRational(&second))
    {
        printf("Invalid rational number.\n");
        return 1;
    }

    Rational sum = add(first, second);
    Rational product = multiply(first, second);

    printf("Sum: ");
    outputRational(sum);
    printf("\nProduct: ");
    outputRational(product);
    printf("\nComparison: %d\n", compare(first, second));

    printf("First denominator form: ");
    outputRational(first);
    printf("\n");

    return 0;
}