#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cipher.h"
#include "tests.h"

#define ARG_ERR "The program receives 1 or 4 arguments only.\n"
#define TEST_ERR "Usage: cipher test\n"
#define COMMAND_ERR "The given command is invalid.\n"
#define K_ERR "The given shift value is invalid.\n"
#define FILE_ERR "The given file is invalid.\n"
#define MAX_LINE 1024
#define CIPHER "cipher"
#define DECIPHER "decipher"
#define TEST "test"
#define ERROR (-999)

int shift = 0; //define shift default value.
int stringToInt(const char str[]) { // converts strings to integers to use in the cipher/decipher function.
    char *endptr;
    long int result = strtol(str, &endptr, 10);
    if (*endptr != '\0') {
        return ERROR;
    }
    return (int)result;
}

int isValidShift(const char str[]) { //validates K shift size.
    int shift = stringToInt(str);
    return shift != ERROR;
}

int run_tests() { //run all tests
    int test_counter = 0;
    if (test_cipher_cyclic_lower_case_negative_k() == 0) test_counter++;
    if (test_cipher_cyclic_lower_case_special_char_positive_k() == 0) test_counter++;
    if (test_cipher_cyclic_upper_case_positive_k() == 0) test_counter++;
    if (test_cipher_non_cyclic_lower_case_positive_k() == 0) test_counter++;
    if (test_cipher_non_cyclic_lower_case_special_char_negative_k() == 0) test_counter++;
    if (test_decipher_cyclic_lower_case_negative_k() == 0) test_counter++;
    if (test_decipher_cyclic_lower_case_special_char_positive_k() == 0) test_counter++;
    if (test_decipher_non_cyclic_lower_case_positive_k() == 0) test_counter++;
    if (test_decipher_cyclic_upper_case_positive_k() == 0) test_counter++;
    if (test_decipher_non_cyclic_lower_case_special_char_negative_k() == 0) test_counter++;

    if (test_counter==10) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int main (int argc, char *argv[]) {
    if (argc != 5 && argc != 2) { // wrong arguments number.
        fprintf(stderr, ARG_ERR);
        return EXIT_FAILURE;
    } else if (argc == 2 && strcmp(argv[1], TEST) != 0) { //wrong test argument
        fprintf(stderr, TEST_ERR);
        return EXIT_FAILURE;
    } else if (argc == 5 && (strcmp(argv[1], DECIPHER) != 0 && strcmp(argv[1], CIPHER) != 0)) { //wrong command argument
        fprintf(stderr, COMMAND_ERR);
        return EXIT_FAILURE;
    }
    if (argc == 5) {
        if (!isValidShift(argv[2])) {
            fprintf(stderr, K_ERR); //validate shift value
            return EXIT_FAILURE;
        }
        shift = stringToInt(argv[2]);
    }
    if (argc == 5) { //valid input
        char line[MAX_LINE] = {0};
        FILE* in_file = fopen(argv[3], "r");
        FILE* out_file = fopen(argv[4], "w");
        if (in_file == NULL) { //validates files
            fprintf(stderr, FILE_ERR);
            if (out_file != NULL) fclose(out_file);
            return EXIT_FAILURE;
        }
        if (out_file == NULL) {
            fprintf(stderr, FILE_ERR);
            fclose(in_file);
            return EXIT_FAILURE;
        }
        if (strcmp(argv[1], CIPHER) == 0) { //runs through lines in input file, cipher/decipher each line and write it to new file.
            while (fgets(line, MAX_LINE, in_file)) {
                cipher(line, shift);
                fputs(line, out_file);
            }
        } else if (strcmp(argv[1], DECIPHER) == 0) {
            while (fgets(line, MAX_LINE, in_file)) {
                decipher(line, shift);
                fputs(line, out_file);
            }
        }
        fclose(in_file);
        fclose(out_file);
        return EXIT_SUCCESS;
    }
    if (argc == 2 && strcmp(argv[1], TEST) == 0) { //run tests
        return run_tests();
    }
    return EXIT_FAILURE;
}