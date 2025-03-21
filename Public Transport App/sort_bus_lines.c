#include "sort_bus_lines.h"

void swap(BusLine *first, BusLine *second) { //swaps two bus lines in array
    BusLine temp = *first;
    *first = *second;
    *second = temp;
}

BusLine *partition(BusLine *start, BusLine *end, SortType sort_type) { //quick sort help function that gets a partition and sorts part of the array based on size
    BusLine *pivot = end;
    BusLine *i = start - 1;

    for (BusLine *j = start; j < end; j++) {
        if ((sort_type == DURATION && j->duration <= pivot->duration) ||
            (sort_type == DISTANCE && j->distance <= pivot->distance)) {
            i++;
            swap(i, j);
            }
    }
    swap(i + 1, end);
    return i + 1;
}

void quick_sort(BusLine *start, BusLine *end, SortType sort_type) { // main quick sort function that divides the array to smaller arrays based on pivot
    if (start < end) {
        BusLine *pi = partition(start, end, sort_type);
        quick_sort(start, pi - 1, sort_type);
        quick_sort(pi + 1, end, sort_type);
    }
}

void bubble_sort(BusLine *start, BusLine *end) { //bubble sort for sorting bus lines based on name
    int size = end - start;
    for (int i = 0; i < size; i++) {
        for (BusLine *j = start; j < end - i; j++) {
            if (strcmp(j->name, (j + 1)->name) > 0) {
                swap(j, j + 1);
            }
        }
    }
}