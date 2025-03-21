#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif //EX2_REPO_SORTBUSLINES_H
#include <string.h>
#define NAME_LEN 21
/**
 * TODO add documentation
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;

typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

//bubble sort for sorting bus lines based on name
void bubble_sort (BusLine *start, BusLine *end);

// main quick sort function that divides the array to smaller arrays based on pivot
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);


//quick sort help function that gets a partition and sorts part of the array based on size
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);

//swaps two bus lines in array
void swap(BusLine *first, BusLine *second);

// write only between #define EX2_REPO_SORTBUSLINES_H and #endif //EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H