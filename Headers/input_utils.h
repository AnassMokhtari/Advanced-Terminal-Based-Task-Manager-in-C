#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <stddef.h>

/**
 * @brief Reads a valid integer from standard input.
 *
 * Re-prompts the user until a valid integer is entered without any trailing characters.
 *
 * @param prompt The message to show to the user.
 * @return The valid integer entered.
 */
int readInt(const char *prompt);

/**
 * @brief Reads an integer from user input and ensures it's within a specific range.
 *
 * For example, use this for priority (1-3), status (0-2), etc.
 *
 * @param prompt The message to display to the user.
 * @param min The minimum allowed value.
 * @param max The maximum allowed value.
 * @return A valid integer in the specified range.
 */
int readIntInRange(const char *prompt, int min, int max);

/**
 * @brief Reads a string safely from user input, supports spaces.
 *
 * Uses fgets() and trims the newline at the end.
 *
 * @param prompt The message to show the user.
 * @param buffer Pointer to the string buffer to fill.
 * @param size Maximum number of characters to read (including null terminator).
 */
void readString(const char *prompt, char *buffer, size_t size);

/**
 * @brief Removes trailing newline character from a string (if present).
 *
 * @param str The string to clean.
 */
void cleanNewline(char *str);

#endif
