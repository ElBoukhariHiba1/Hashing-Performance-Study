
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 11
#define EMPTY -1

/* ========= Hash Functions ========= */
int hashModulo(int key) {
    return key % TABLE_SIZE;
}

int hashMultiplicative(int key) {
    double A = 0.618033;
    return (int)(TABLE_SIZE * (key * A - (int)(key * A)));
}

/* ========= Collision Resolution ========= */
/* Linear Probing */
void linearInsert(int table[], int key, int *collisions) {
    int index = hashModulo(key);
    while (table[index] != EMPTY) {
        (*collisions)++;
        index = (index + 1) % TABLE_SIZE;
    }
    table[index] = key;
}

/* Quadratic Probing */
void quadraticInsert(int table[], int key, int *collisions) {
    int index = hashModulo(key);
    int i = 1;
    while (table[index] != EMPTY) {
        (*collisions)++;
        index = (index + i * i) % TABLE_SIZE;
        i++;
    }
    table[index] = key;
}

/* ========= Performance Measurement ========= */
void measurePerformance(
    void (*insertFunc)(int[], int, int*),
    int table[],
    int arr[],
    int n
) {
    int collisions = 0;
    clock_t start, end;

    start = clock();
    for (int i = 0; i < n; i++) {
        insertFunc(table, arr[i], &collisions);
    }
    end = clock();

    printf("Collisions: %d\n", collisions);
    printf("Execution Time: %.6f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);
}

/* ========= Display ========= */
void displayTable(int table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] == EMPTY)
            printf("[%d] : ---\n", i);
        else
            printf("[%d] : %d\n", i, table[i]);
    }
}

/* ========= Main ========= */
int main() {
    int table[TABLE_SIZE];
    int data[] = {42, 17, 93, 58, 26, 79, 61, 34, 88, 13};
    int n = 10;

    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = EMPTY;

    printf("Linear Probing Test:\n");
    measurePerformance(linearInsert, table, data, n);
    displayTable(table);

    return 0;
}
