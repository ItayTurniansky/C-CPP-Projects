#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort_bus_lines.h"
#include "test_bus_lines.h"

#define MAX_FIELD 20
#define MAX_ROW 60
#define MIN_duration 10
#define MAX_duration 100
#define MAX_distance 1000


int get_total_bus_number() { //receives and validates number of bus lines from user.
    int number = 0;
    char *end_ptr;
    while (1) {
        char num_line[MAX_FIELD];
        printf("Enter number of lines. Then enter\n");
        if (fgets(num_line, sizeof(num_line), stdin)) {
            number = (int)strtol(num_line, &end_ptr, 10);
            if ((*end_ptr == '\n' || *end_ptr == '\0') && number > 0) { //checks that the number is a positive integer
                return number;
            }
        }
        printf("Error: Number of lines should be a positive integer\n");
    }
}

int validate_line_name(char line_name[]) { //validates the line name is only made from small chars an integers up to 9
    for (int j = 0; line_name[j] != '\0'; j++) {
        if (!((line_name[j] >= 'a' && line_name[j] <= 'z') || (line_name[j] >= '0' && line_name[j] <= '9'))) {
            return 0; // Invalid character found.
        }
    }
    return 1; // Valid name
}

int validate_line_distance(char distance[]) { //validates distance is an int between range
    char *end_ptr;
    int number = (int)strtol(distance, &end_ptr, 10);
    return ((*end_ptr == '\n' || *end_ptr == '\0') && number >= 0 && number <= MAX_distance);
}

int validate_line_duration(char duration[]) { //validates duration is an int between range
    char *end_ptr;
    int number = (int)strtol(duration, &end_ptr, 10);
    return ((*end_ptr == '\n' || *end_ptr == '\0') && number >= MIN_duration && number <= MAX_duration);
}

int run_all_tests(BusLine *start, BusLine *end) { //runs all 6 tests (3 sort validation with 1 sanity check each time(total 6)).
    int size = end-start+1;
    BusLine *bus_lines_copy = malloc(sizeof(*bus_lines_copy) * size); //saves original array
    for (int i = 0; i < size; i++) {
        bus_lines_copy[i] = start[i];
    }
    if (bus_lines_copy == NULL) {
        return 0;
    }

    quick_sort(start, start + size - 1, DISTANCE);// check sort by distance
    if (is_sorted_by_distance(start,end)==1) {
        printf("TEST 1 PASSED: The array is sorted by distance\n");
    }else {
        printf("TEST 1 FAILED: The array is Not sorted by distance\n");
    }
    if (is_equal(start,end,bus_lines_copy,bus_lines_copy+size-1)==1) {
        printf("TEST 2 PASSED: The array has the same items after sorting\n");
    }else {
        printf("TEST 2 FAILED: array changed\n");
    }

    quick_sort(start, start + size - 1, DURATION);// check sort by duration
    if (is_sorted_by_duration(start,end)==1) {
        printf("TEST 3 PASSED: The array is sorted by duration\n");
    }else {
        printf("TEST 3 FAILED: Not sorted by duration\n");
    }
    if (is_equal(start,end,bus_lines_copy,bus_lines_copy+size-1)==1) {
        printf("TEST 4 PASSED: The array has the same items after sorting\n");
    }else {
        printf("TEST 4 FAILED: array changed\n");
    }

    bubble_sort(start, start + size - 1);// check sort by name
    if (is_sorted_by_name(start,end)==1) {
        printf("TEST 5 PASSED: The array is sorted by name\n");
    }else {
        printf("TEST 5 FAILED: Not sorted by name\n");
    }
    if (is_equal(start,end,bus_lines_copy,bus_lines_copy+size-1)==1) {
        printf("TEST 6 PASSED: The array has the same items after sorting\n");
    }else {
        printf("TEST 6 FAILED: array changed\n");
    }
    free(bus_lines_copy);
    return 1;

}


int main(int argc, char *argv[]) {
    if (argc < 2) {// check cli argument count
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "by_duration") != 0 && strcmp(argv[1], "by_distance")!=0 && strcmp(argv[1], "by_name") != 0 && strcmp(argv[1], "test") != 0) { //validate cli arguments
        return EXIT_FAILURE;
    }

    int number_of_lines = get_total_bus_number();
    BusLine *bus_lines = malloc(sizeof(*bus_lines) * number_of_lines);
    if (bus_lines == NULL) {
        return EXIT_FAILURE;
    }

    int i = 0;
    while (i < number_of_lines) { // creates array of Bus Lines based on user input while validating each field input.
        char line_name[MAX_FIELD], distance[MAX_FIELD], duration[MAX_FIELD];
        char line[MAX_ROW];
        printf("Enter line info. Then enter\n");
        if (!fgets(line, sizeof(line), stdin)) {
            continue;
        }
        if (sscanf(line, "%16[^,],%16[^,],%16[^,]", line_name, distance, duration) != 3) {
            continue;
        }

        if (!validate_line_name(line_name)) { //validates name
            printf("Error: bus name should contains only digits and small chars\n");
            continue;
        }
        if (!validate_line_distance(distance)) { //validates distance
            printf("Error: distance should be an integer between 0 and 1000 (includes)\n");
            continue;
        }
        if (!validate_line_duration(duration)) { //validates duration
            printf("Error: duration should be an integer between 10 and 100 (includes)\n");
            continue;
        }

        char *end_ptr; // enters Bus line to array
        bus_lines[i].distance = (int)strtol(distance, &end_ptr, 10);
        bus_lines[i].duration = (int)strtol(duration, &end_ptr, 10);
        strncpy(bus_lines[i].name, line_name, MAX_FIELD - 1);
        bus_lines[i].name[MAX_FIELD - 1] = '\0'; // Ensure null termination.
        i++;
    }

    if (strcmp(argv[1], "by_distance") == 0) { // select action (sort by field or test)
        quick_sort(bus_lines, bus_lines + number_of_lines - 1, DISTANCE);
    } else if (strcmp(argv[1], "by_duration") == 0) {
        quick_sort(bus_lines, bus_lines + number_of_lines - 1, DURATION);
    } else if (strcmp(argv[1], "by_name") == 0) {
        bubble_sort(bus_lines, bus_lines + number_of_lines - 1);
    }else if(strcmp(argv[1], "test") == 0) {
        if (run_all_tests(bus_lines, bus_lines + number_of_lines - 1)==1) {
            free(bus_lines);
            return EXIT_SUCCESS;
        }else {
            free(bus_lines);
            return EXIT_FAILURE;
        }
    }else {
        printf("Usage: wrong arguments\n");
        return EXIT_FAILURE;
    }

    for (int j = 0; j < number_of_lines; j++) { //print sorted array
        printf("%s,%d,%d\n", bus_lines[j].name, bus_lines[j].distance, bus_lines[j].duration);
    }

    free(bus_lines);
    return EXIT_SUCCESS;
}