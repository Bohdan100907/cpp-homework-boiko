#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_LEN 10

typedef struct TPair {
    unsigned key;
    char data[DATA_LEN];
} TPair;

static int writeRecords(const char *filename, const TPair *records, long count) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    if (count > 0 && fwrite(records, sizeof(TPair), (size_t)count, file) != (size_t)count) {
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

static long readRecords(const char *filename, TPair **recordsOut) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        *recordsOut = NULL;
        return 0;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        *recordsOut = NULL;
        return 0;
    }

    long fileSize = ftell(file);
    if (fileSize < 0) {
        fclose(file);
        *recordsOut = NULL;
        return 0;
    }

    rewind(file);

    long count = fileSize / (long)sizeof(TPair);
    if (count == 0) {
        fclose(file);
        *recordsOut = NULL;
        return 0;
    }

    TPair *records = (TPair *)malloc((size_t)count * sizeof(TPair));
    if (records == NULL) {
        fclose(file);
        *recordsOut = NULL;
        return 0;
    }

    if (fread(records, sizeof(TPair), (size_t)count, file) != (size_t)count) {
        free(records);
        fclose(file);
        *recordsOut = NULL;
        return 0;
    }

    fclose(file);
    *recordsOut = records;
    return count;
}

static int detectOrder(const TPair *records, long count) {
    if (count < 2) {
        return 1;
    }

    return records[0].key <= records[1].key ? 1 : -1;
}

static int searchInArray(const TPair *records, long count, unsigned key, int ascending, long *indexOut) {
    long left = 0;
    long right = count - 1;

    while (left <= right) {
        long mid = left + (right - left) / 2;

        if (records[mid].key == key) {
            if (indexOut != NULL) {
                *indexOut = mid;
            }
            return 1;
        }

        if (ascending) {
            if (records[mid].key < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            if (records[mid].key > key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    return 0;
}

int searchInOrderedFile(const char *filename, unsigned key, long *indexOut) {
    TPair *records = NULL;
    long count = readRecords(filename, &records);
    if (records == NULL || count <= 0) {
        return 0;
    }

    int ascending = detectOrder(records, count) > 0;
    int found = searchInArray(records, count, key, ascending, indexOut);

    free(records);
    return found;
}

int deleteFromOrderedFile(const char *filename, unsigned key) {
    TPair *records = NULL;
    long count = readRecords(filename, &records);
    if (records == NULL || count <= 0) {
        return 0;
    }

    int ascending = detectOrder(records, count) > 0;
    long index = -1;
    int found = searchInArray(records, count, key, ascending, &index);
    if (!found) {
        free(records);
        return 0;
    }

    for (long i = index; i + 1 < count; ++i) {
        records[i] = records[i + 1];
    }

    if (!writeRecords(filename, records, count - 1)) {
        free(records);
        return 0;
    }

    free(records);
    return 1;
}

int deleteFromUnorderedFile(const char *filename, unsigned key) {
    TPair *records = NULL;
    long count = readRecords(filename, &records);
    if (records == NULL || count <= 0) {
        return 0;
    }

    long index = -1;
    for (long i = 0; i < count; ++i) {
        if (records[i].key == key) {
            index = i;
            break;
        }
    }

    if (index < 0) {
        free(records);
        return 0;
    }

    for (long i = index; i + 1 < count; ++i) {
        records[i] = records[i + 1];
    }

    if (!writeRecords(filename, records, count - 1)) {
        free(records);
        return 0;
    }

    free(records);
    return 1;
}

static void fillData(TPair *pair, unsigned key, const char *text) {
    pair->key = key;
    snprintf(pair->data, sizeof(pair->data), "%s", text);
}

int main(void) {
    const char *orderedFile = "ordered.bin";
    const char *unorderedFile = "unordered.bin";

    TPair ordered[4];
    TPair unordered[4];

    fillData(&ordered[0], 10, "alpha");
    fillData(&ordered[1], 20, "beta");
    fillData(&ordered[2], 35, "gamma");
    fillData(&ordered[3], 50, "delta");

    fillData(&unordered[0], 12, "zulu");
    fillData(&unordered[1], 7, "bravo");
    fillData(&unordered[2], 33, "echo");
    fillData(&unordered[3], 21, "hotel");

    writeRecords(orderedFile, ordered, 4);
    writeRecords(unorderedFile, unordered, 4);

    long orderedIndex = -1;
    if (searchInOrderedFile(orderedFile, 35, &orderedIndex)) {
        printf("Record found in ordered file at index %ld\n", orderedIndex);
    } else {
        printf("Record not found in ordered file\n");
    }

    if (deleteFromOrderedFile(orderedFile, 20)) {
        printf("Deleted key 20 from ordered file\n");
    } else {
        printf("Key 20 was not found in ordered file\n");
    }

    if (deleteFromUnorderedFile(unorderedFile, 7)) {
        printf("Deleted key 7 from unordered file\n");
    } else {
        printf("Key 7 was not found in unordered file\n");
    }

    return 0;
}
