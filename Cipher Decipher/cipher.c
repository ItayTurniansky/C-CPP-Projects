#include "cipher.h"
#define LETTERS_COUNT 26

void cipher(char s[], int k) { //ciphers an input string to a new string based on a shift value using caesar code.
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = (char)((((s[i] - 'A' + k) % LETTERS_COUNT + LETTERS_COUNT) % LETTERS_COUNT) + 'A');
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = (char)((((s[i] - 'a' + k) % LETTERS_COUNT + LETTERS_COUNT) % LETTERS_COUNT) + 'a');
        } else {
            continue;
        }
    }
}

void decipher(char s[], int k) { //deciphers an input string to a new string based on a shift value using caesar code.
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = (char)((((s[i] - 'A' - k) % LETTERS_COUNT + LETTERS_COUNT) % LETTERS_COUNT) + 'A');
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = (char)((((s[i] - 'a' - k) % LETTERS_COUNT + LETTERS_COUNT) % LETTERS_COUNT) + 'a');
        } else {
            continue;
        }
    }
}
