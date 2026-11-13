#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 32

typedef struct {
    char name[NAME_LEN];
    unsigned int price;
    int minAge;
    int maxAge;
} Toy;

typedef struct {
    char name[NAME_LEN];
} ToyName;

static int saveToys(const char *filename, const Toy *toys, size_t count) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    if (fwrite(&count, sizeof(count), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    if (count > 0 && fwrite(toys, sizeof(Toy), count, file) != count) {
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

static int loadToys(const char *filename, Toy **toysOut, size_t *countOut) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        *toysOut = NULL;
        *countOut = 0;
        return 0;
    }

    size_t count = 0;
    if (fread(&count, sizeof(count), 1, file) != 1) {
        fclose(file);
        *toysOut = NULL;
        *countOut = 0;
        return 0;
    }

    Toy *toys = NULL;
    if (count > 0) {
        toys = (Toy *)malloc(count * sizeof(Toy));
        if (toys == NULL) {
            fclose(file);
            *toysOut = NULL;
            *countOut = 0;
            return 0;
        }

        if (fread(toys, sizeof(Toy), count, file) != count) {
            free(toys);
            fclose(file);
            *toysOut = NULL;
            *countOut = 0;
            return 0;
        }
    }

    fclose(file);
    *toysOut = toys;
    *countOut = count;
    return 1;
}

static void printMatches(const ToyName *matches, size_t count) {
    if (count == 0) {
        printf("Result: no toys found\n");
        return;
    }

    printf("Result:\n");
    for (size_t i = 0; i < count; ++i) {
        printf("- %s\n", matches[i].name);
    }
}

static int writeMatchesToBinaryFile(const char *filename, const ToyName *matches, size_t count) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    if (fwrite(&count, sizeof(count), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    if (count > 0 && fwrite(matches, sizeof(ToyName), count, file) != count) {
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

int findToysForAgeRange(const char *inputFile, int ageA, int ageB, const char *outputFile) {
    Toy *toys = NULL;
    size_t toyCount = 0;

    if (!loadToys(inputFile, &toys, &toyCount)) {
        printf("Unable to read toys file.\n");
        return 0;
    }

    int left = ageA;
    int right = ageB;
    if (left > right) {
        int tmp = left;
        left = right;
        right = tmp;
    }

    ToyName *matches = NULL;
    size_t matchCount = 0;

    if (toyCount > 0) {
        matches = (ToyName *)malloc(toyCount * sizeof(ToyName));
        if (matches == NULL) {
            free(toys);
            return 0;
        }
    }

    for (size_t i = 0; i < toyCount; ++i) {
        if (toys[i].minAge <= left && toys[i].maxAge >= right) {
            snprintf(matches[matchCount].name, sizeof(matches[matchCount].name), "%s", toys[i].name);
            ++matchCount;
        }
    }

    printMatches(matches, matchCount);

    if (!writeMatchesToBinaryFile(outputFile, matches, matchCount)) {
        free(matches);
        free(toys);
        return 0;
    }

    free(matches);
    free(toys);
    return 1;
}

int main(void) {
    const char *inputFile = "toys.bin";
    const char *outputFile = "matches.bin";

    Toy toys[] = {
        {"М'яч", 120, 3, 8},
        {"Лялька", 210, 4, 7},
        {"Конструктор", 380, 5, 12},
        {"Велосипед", 650, 6, 10},
        {"Пазли", 150, 2, 5},
        {"Кубики", 100, 1, 4}
    };

    size_t toyCount = sizeof(toys) / sizeof(toys[0]);

    if (!saveToys(inputFile, toys, toyCount)) {
        printf("Error while saving toys file.\n");
        return 1;
    }

    printf("Search for toys intended for children of ages 5 and 8:\n");
    if (!findToysForAgeRange(inputFile, 5, 8, outputFile)) {
        printf("Error while searching toys.\n");
        return 1;
    }

    printf("\nResults were also written to binary file: %s\n", outputFile);
    return 0;
}
