#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int day;
    int month;
    int year;
} Date;

typedef struct
{
    char file;
    int rank;
} ChessSquare;

typedef struct
{
    double x;
    double y;
} Point;

typedef struct
{
    Point first;
    Point second;
} Rectangle;

typedef struct
{
    size_t degree;
    double *coefficients;
} Polynomial;

int inputDate(Date *date)
{
    printf("Enter date (day month year): ");
    return scanf("%d %d %d", &date->day, &date->month, &date->year) == 3;
}

void outputDate(const Date *date)
{
    printf("%02d.%02d.%04d\n", date->day, date->month, date->year);
}

int inputChessSquare(ChessSquare *square)
{
    printf("Enter chess square (for example, a5): ");
    return scanf(" %c%d", &square->file, &square->rank) == 2;
}

void outputChessSquare(const ChessSquare *square)
{
    printf("%c%d\n", square->file, square->rank);
}

int inputPoint(Point *point)
{
    printf("Enter point coordinates (x y): ");
    return scanf("%lf %lf", &point->x, &point->y) == 2;
}

void outputPoint(const Point *point)
{
    printf("(%.2lf, %.2lf)", point->x, point->y);
}

int inputRectangle(Rectangle *rectangle)
{
    printf("Enter the first vertex:\n");
    if (!inputPoint(&rectangle->first))
    {
        return 0;
    }

    printf("Enter the second vertex:\n");
    return inputPoint(&rectangle->second);
}

void outputRectangle(const Rectangle *rectangle)
{
    outputPoint(&rectangle->first);
    printf(" - ");
    outputPoint(&rectangle->second);
    printf("\n");
}

int inputPolynomial(Polynomial *polynomial)
{
    printf("Enter polynomial degree: ");
    if (scanf("%zu", &polynomial->degree) != 1 ||
        polynomial->degree == (size_t)-1)
    {
        return 0;
    }

    size_t count = polynomial->degree + 1;
    if (count > (size_t)-1 / sizeof(double))
    {
        return 0;
    }

    polynomial->coefficients = malloc(count * sizeof(double));
    if (polynomial->coefficients == NULL)
    {
        return 0;
    }

    printf("Enter coefficients from degree %zu down to degree 0:\n",
           polynomial->degree);
    for (size_t i = 0; i < count; ++i)
    {
        if (scanf("%lf", &polynomial->coefficients[i]) != 1)
        {
            free(polynomial->coefficients);
            polynomial->coefficients = NULL;
            return 0;
        }
    }

    return 1;
}

void outputPolynomial(const Polynomial *polynomial)
{
    for (size_t i = 0; i <= polynomial->degree; ++i)
    {
        size_t power = polynomial->degree - i;
        printf("%g", polynomial->coefficients[i]);
        if (power > 0)
        {
            printf("*x^%zu", power);
        }
        if (i < polynomial->degree)
        {
            printf(" + ");
        }
    }
    printf("\n");
}

int main(void)
{
    Date date;
    ChessSquare square;
    Rectangle rectangle;
    Polynomial polynomial = {0, NULL};

    if (!inputDate(&date) || !inputChessSquare(&square) ||
        !inputRectangle(&rectangle) || !inputPolynomial(&polynomial))
    {
        printf("Invalid input or not enough memory.\n");
        free(polynomial.coefficients);
        return 1;
    }

    outputDate(&date);
    outputChessSquare(&square);
    outputRectangle(&rectangle);
    outputPolynomial(&polynomial);

    free(polynomial.coefficients);
    return 0;
}