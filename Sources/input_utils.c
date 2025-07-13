#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input_utils.h"

/**
 * @brief Removes the newline character at the end of a string, if present.
 *
 * This is used after fgets() to eliminate the '\n' character that may be added
 * when the user presses Enter. It prevents newline-related bugs later.
 *
 * @param str The string to clean.
 */
void cleanNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

/**
 * @brief Reads a valid integer from the user with input validation.
 *
 * The function uses fgets() to safely read a full line of input, then attempts
 * to convert it to an integer using strtol(). If the input is invalid (e.g., contains
 * letters or extra characters), the function will re-prompt the user.
 *
 * @param prompt The message displayed to the user.
 * @return A valid integer entered by the user.
 */
int readInt(const char *prompt) {
    char buffer[100];
    char *endptr;

    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Input error. Try again.\n");
            continue;
        }

        cleanNewline(buffer);

        long value = strtol(buffer, &endptr, 10);

        if (endptr == buffer) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        while (*endptr) {
            if (!isspace((unsigned char)*endptr)) {
                printf("Invalid input. No characters allowed after the number.\n");
                break;
            }
            endptr++;
        }

        if (*endptr == '\0') {
            return (int)value;
        }
    }
}

/**
 * @brief Reads an integer and ensures it falls within a specific range.
 *
 * Uses readInt() internally and adds a range check. Useful for menu choices,
 * task priorities, or status flags.
 *
 * @param prompt Message to display.
 * @param min Minimum accepted value.
 * @param max Maximum accepted value.
 * @return An integer between [min, max].
 */
int readIntInRange(const char *prompt, int min, int max) {
    int value;

    do {
        value = readInt(prompt);
        if (value < min || value > max) {
            printf("Input must be between %d and %d.\n", min, max);
        }
    } while (value < min || value > max);

    return value;
}

/**
 * @brief Reads a string safely from input (supports spaces).
 *
 * Uses fgets() instead of scanf() to allow spaces in input and
 * avoid buffer overflows. Trims trailing newline.
 *
 * @param prompt Message to display.
 * @param buffer Pointer to the buffer where input is stored.
 * @param size Maximum characters to read (including null terminator).
 */
void readString(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);

    if (fgets(buffer, size, stdin) != NULL) {
        cleanNewline(buffer);
    } else {
        buffer[0] = '\0';
    }
}
