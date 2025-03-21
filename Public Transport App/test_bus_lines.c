#include "test_bus_lines.h"
int is_sorted_by_distance (const BusLine *start, const BusLine *end) { //validates given Bus line array is sorted by distance
    for (const BusLine *p = start; p < end; p++) {
        if (p->distance > (p+1)->distance) {
            return 0;
        }
    } return 1;
}

int is_sorted_by_duration (const BusLine *start, const BusLine *end) { //validates given Bus line array is sorted by duration
    for (const BusLine *p = start; p < end; p++) {
        if (p->duration > (p+1)->duration) {
            return 0;
        }
    } return 1;
}

int is_sorted_by_name (const BusLine *start, const BusLine *end) { //validates given Bus line array is sorted by name
    for (const BusLine *p = start; p < end; p++) {
        if (strcmp(p->name , (p+1)->name)>0) {
            return 0;
        }
    } return 1;
}

int is_equal (const BusLine *start_sorted, //validates two bus lines arrays have the same number of lines with the same names.
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original) {
    int size_1 = end_sorted-start_sorted+1, size_2 = end_original-start_original+1, counter=0;
    if (size_1!=size_2) { //validate arrays sizes are equal
        return 0;
    }
    for ( const BusLine *p = start_sorted; p <= end_sorted; p++) {
        for ( const BusLine *q = start_original; q <= end_original; q++) { //counts each name that is equal
            if (strcmp(p->name , q->name) == 0) {
                counter ++;
            }
        }
    }
    if (counter!=size_1) { //not all bus lines names are the same
        return 0;
    }
    return 1;
}