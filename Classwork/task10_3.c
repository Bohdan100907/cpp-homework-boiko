#include <stdio.h>

typedef struct
{
    int day;
    int month;
    int year;
} Date;

int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int daysInMonth(int month, int year)
{
    if (month == 2)
    {
        return isLeapYear(year) ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    return 31;
}

int validDate(const Date *date)
{
    return date->year >= 1 && date->month >= 1 && date->month <= 12 &&
           date->day >= 1 &&
           date->day <= daysInMonth(date->month, date->year);
}

Date tomorrow(const Date *date)
{
    Date result = *date;
    result.day++;
    if (result.day > daysInMonth(result.month, result.year))
    {
        result.day = 1;
        result.month++;
        if (result.month > 12)
        {
            result.month = 1;
            result.year++;
        }
    }
    return result;
}

int weekday(const Date *date)
{
    int day = date->day;
    int month = date->month;
    int year = date->year;

    if (month < 3)
    {
        month += 12;
        year--;
    }

    int k = year % 100;
    int j = year / 100;
    int value = day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + 5 * j;
    return (value % 7 + 7) % 7;
}

int main(void)
{
    Date date;
    printf("Enter date (day month year): ");
    if (scanf("%d %d %d", &date.day, &date.month, &date.year) != 3 ||
        !validDate(&date))
    {
        printf("Invalid date.\n");
        return 1;
    }

    Date next = tomorrow(&date);
    const char *names[] = {
        "Saturday",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday"
    };

    printf("Tomorrow: %02d.%02d.%04d\n", next.day, next.month, next.year);
    printf("Weekday: %s\n", names[weekday(&date)]);

    return 0;
}