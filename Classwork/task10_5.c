#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[100];
    double x;
    double y;
    double height;
} MountainVertex;

int inputVertices(MountainVertex vertices[], size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        printf("Vertex %zu name: ", i + 1);
        if (scanf(" %99[^\n]", vertices[i].name) != 1)
        {
            return 0;
        }

        printf("Coordinates x y: ");
        if (scanf("%lf%lf", &vertices[i].x, &vertices[i].y) != 2)
        {
            return 0;
        }

        printf("Height: ");
        if (scanf("%lf", &vertices[i].height) != 1)
        {
            return 0;
        }
    }

    return 1;
}

MountainVertex *findByName(MountainVertex vertices[], size_t count,
                           const char *name)
{
    for (size_t i = 0; i < count; ++i)
    {
        if (strcmp(vertices[i].name, name) == 0)
        {
            return &vertices[i];
        }
    }
    return NULL;
}

double findHeight(MountainVertex vertices[], size_t count, const char *name)
{
    MountainVertex *vertex = findByName(vertices, count, name);
    if (vertex == NULL)
    {
        return 0.0;
    }
    return vertex->height;
}

int main(void)
{
    size_t count;
    printf("Enter number of vertices: ");
    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > (size_t)-1 / sizeof(MountainVertex))
    {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    MountainVertex *vertices = malloc(count * sizeof(MountainVertex));
    if (vertices == NULL)
    {
        printf("Not enough memory.\n");
        return 1;
    }

    if (!inputVertices(vertices, count))
    {
        printf("Invalid input.\n");
        free(vertices);
        return 1;
    }

    char name[100];
    printf("Enter vertex name: ");
    if (scanf(" %99[^\n]", name) != 1)
    {
        printf("Invalid name.\n");
        free(vertices);
        return 1;
    }

    MountainVertex *vertex = findByName(vertices, count, name);
    if (vertex == NULL)
    {
        printf("No vertex with that name in the array.\n");
    }
    else
    {
        printf("Vertex: %s\n", vertex->name);
        printf("Coordinates: (%.2lf, %.2lf)\n", vertex->x, vertex->y);
        printf("Height: %.2lf\n", findHeight(vertices, count, name));
    }

    free(vertices);
    return 0;
}