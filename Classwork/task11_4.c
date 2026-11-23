#include <math.h>
#include <stdio.h>

#define DATA_FILE "rectangles.dat"
#define TEMP_FILE "rectangles.tmp"

typedef struct
{
    int number;
    double leftX;
    double leftY;
    double rightX;
    double rightY;
} Rectangle;

double calculateArea(Rectangle rectangle)
{
    double width = fabs(rectangle.rightX - rectangle.leftX);
    double height = fabs(rectangle.rightY - rectangle.leftY);
    return width * height;
}

int readRectangle(Rectangle *rectangle)
{
    printf("Enter rectangle number and coordinates x1 y1 x2 y2: ");
    return scanf("%d %lf %lf %lf %lf",
                 &rectangle->number,
                 &rectangle->leftX,
                 &rectangle->leftY,
                 &rectangle->rightX,
                 &rectangle->rightY) == 5;
}

int createFile(void)
{
    int count;
    printf("Enter number of rectangles: ");
    if (scanf("%d", &count) != 1 || count <= 0)
    {
        return 0;
    }

    FILE *file = fopen(DATA_FILE, "wb");
    if (file == NULL)
    {
        return 0;
    }

    for (int i = 0; i < count; i++)
    {
        Rectangle rectangle;
        if (!readRectangle(&rectangle) ||
            fwrite(&rectangle, sizeof(Rectangle), 1, file) != 1)
        {
            fclose(file);
            return 0;
        }
    }

    return fclose(file) == 0;
}

int findLargestRectangle(int *number, double *largestArea)
{
    FILE *file = fopen(DATA_FILE, "rb");
    if (file == NULL)
    {
        return -1;
    }

    Rectangle rectangle;
    int found = 0;

    while (fread(&rectangle, sizeof(Rectangle), 1, file) == 1)
    {
        double area = calculateArea(rectangle);
        if (!found || area > *largestArea)
        {
            *number = rectangle.number;
            *largestArea = area;
            found = 1;
        }
    }

    int result = ferror(file) ? -1 : (found ? 1 : 0);
    if (fclose(file) != 0)
    {
        return -1;
    }
    return result;
}

int deleteRectangle(int number)
{
    FILE *source = fopen(DATA_FILE, "rb");
    if (source == NULL)
    {
        return -1;
    }

    FILE *temporary = fopen(TEMP_FILE, "wb");
    if (temporary == NULL)
    {
        fclose(source);
        return -1;
    }

    Rectangle rectangle;
    int removed = 0;
    int success = 1;

    while (fread(&rectangle, sizeof(Rectangle), 1, source) == 1)
    {
        if (rectangle.number == number)
        {
            removed = 1;
        }
        else if (fwrite(&rectangle, sizeof(Rectangle), 1, temporary) != 1)
        {
            success = 0;
            break;
        }
    }

    if (ferror(source))
    {
        success = 0;
    }
    if (fclose(source) != 0)
    {
        success = 0;
    }
    if (fclose(temporary) != 0)
    {
        success = 0;
    }

    if (!success || !removed)
    {
        remove(TEMP_FILE);
        return success ? 0 : -1;
    }

    if (remove(DATA_FILE) != 0 || rename(TEMP_FILE, DATA_FILE) != 0)
    {
        return -1;
    }
    return 1;
}

int replaceRectangleByPosition(int position, Rectangle replacement)
{
    if (position <= 0)
    {
        return 0;
    }

    FILE *file = fopen(DATA_FILE, "r+b");
    if (file == NULL)
    {
        return -1;
    }

    Rectangle current;
    int currentPosition = 1;
    int result = 0;

    while (fread(&current, sizeof(Rectangle), 1, file) == 1)
    {
        if (currentPosition == position)
        {
            if (fseek(file, -(long)sizeof(Rectangle), SEEK_CUR) == 0 &&
                fwrite(&replacement, sizeof(Rectangle), 1, file) == 1)
            {
                result = 1;
            }
            else
            {
                result = -1;
            }
            break;
        }
        currentPosition++;
    }

    if (ferror(file))
    {
        result = -1;
    }
    if (fclose(file) != 0)
    {
        result = -1;
    }
    return result;
}

int main(void)
{
    if (!createFile())
    {
        printf("Could not create the rectangle file or read the input.\n");
        return 1;
    }

    int choice;
    do
    {
        printf("\n1. Find largest rectangle\n");
        printf("2. Delete rectangle by number\n");
        printf("3. Replace rectangle by file position\n");
        printf("0. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid choice.\n");
            return 1;
        }

        if (choice == 1)
        {
            int number;
            double area = 0;
            int result = findLargestRectangle(&number, &area);
            if (result == 1)
            {
                printf("Rectangle %d has the largest area: %.2f\n", number, area);
            }
            else if (result == 0)
            {
                printf("The file contains no rectangles.\n");
            }
            else
            {
                printf("Could not read the rectangle file.\n");
            }
        }
        else if (choice == 2)
        {
            int number;
            printf("Enter rectangle number to delete: ");
            if (scanf("%d", &number) != 1)
            {
                printf("Invalid number.\n");
                return 1;
            }

            int result = deleteRectangle(number);
            if (result == 1)
            {
                printf("Rectangle deleted.\n");
            }
            else if (result == 0)
            {
                printf("Rectangle number not found.\n");
            }
            else
            {
                printf("Could not update the rectangle file.\n");
            }
        }
        else if (choice == 3)
        {
            int position;
            Rectangle replacement;
            printf("Enter record position to replace: ");
            if (scanf("%d", &position) != 1 || !readRectangle(&replacement))
            {
                printf("Invalid input.\n");
                return 1;
            }

            int result = replaceRectangleByPosition(position, replacement);
            if (result == 1)
            {
                printf("Rectangle record replaced.\n");
            }
            else if (result == 0)
            {
                printf("Record position not found.\n");
            }
            else
            {
                printf("Could not update the rectangle file.\n");
            }
        }
        else if (choice != 0)
        {
            printf("Unknown option.\n");
        }
    } while (choice != 0);

    return 0;
}