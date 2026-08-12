#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

#include "input.h"

#define INPUT_BUFFER_SIZE 256

/*
 * Discard all remaining characters from the
 * current input line.
 */
static void clearInputBuffer(void)
{
    int character;

    while ((character = getchar()) != '\n' &&
           character != EOF) {
        /* Discard remaining input. */
    }
}

/*
 * Read a valid integer from the user.
 *
 * The function keeps asking until the user
 * enters a valid integer.
 */
int readInt(const char *prompt)
{
    char buffer[INPUT_BUFFER_SIZE];

    while (1) {
        char *end;
        long value;

        printf("%s", prompt);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nInput error. Please try again.\n");
            clearerr(stdin);
            continue;
        }

        errno = 0;

        value = strtol(buffer, &end, 10);

        /*
         * Allow spaces and tabs after the number.
         */
        while (*end == ' ' || *end == '\t') {
            end++;
        }

        /*
         * Reject invalid input.
         */
        if (end == buffer ||
            (*end != '\n' && *end != '\0')) {

            printf(
                "Invalid input. "
                "Please enter a whole number.\n"
            );

            continue;
        }

        /*
         * Check integer overflow/underflow.
         */
        if (errno == ERANGE ||
            value < INT_MIN ||
            value > INT_MAX) {

            printf("Number is out of range.\n");
            continue;
        }

        return (int)value;
    }
}

/*
 * Read an integer within a specified range.
 */
int readIntRange(
    const char *prompt,
    int min,
    int max
)
{
    if (min > max) {
        fprintf(
            stderr,
            "Internal error: invalid integer range.\n"
        );

        return min;
    }

    while (1) {
        int value = readInt(prompt);

        if (value < min || value > max) {
            printf(
                "Please enter a value between "
                "%d and %d.\n",
                min,
                max
            );

            continue;
        }

        return value;
    }
}

/*
 * Read a floating-point number within
 * a specified range.
 */
float readFloatRange(
    const char *prompt,
    float min,
    float max
)
{
    char buffer[INPUT_BUFFER_SIZE];

    if (!isfinite(min) ||
        !isfinite(max) ||
        min > max) {

        fprintf(
            stderr,
            "Internal error: invalid floating-point range.\n"
        );

        return min;
    }

    while (1) {
        char *end;
        float value;

        printf("%s", prompt);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nInput error. Please try again.\n");
            clearerr(stdin);
            continue;
        }

        errno = 0;

        value = strtof(buffer, &end);

        /*
         * Allow spaces and tabs after
         * the numeric value.
         */
        while (*end == ' ' || *end == '\t') {
            end++;
        }

        /*
         * Reject invalid input.
         */
        if (end == buffer ||
            (*end != '\n' && *end != '\0')) {

            printf(
                "Invalid input. "
                "Please enter a number.\n"
            );

            continue;
        }

        /*
         * Reject overflow, underflow,
         * NaN and infinity.
         */
        if (errno == ERANGE ||
            !isfinite(value)) {

            printf(
                "Invalid or out-of-range number.\n"
            );

            continue;
        }

        /*
         * Check application-specific range.
         */
        if (value < min || value > max) {
            printf(
                "Please enter a value between "
                "%.2f and %.2f.\n",
                min,
                max
            );

            continue;
        }

        return value;
    }
}

/*
 * Read a non-empty string.
 *
 * Input longer than the supplied buffer
 * is rejected rather than silently truncated.
 */
void readString(
    const char *prompt,
    char *buffer,
    size_t size
)
{
    if (buffer == NULL || size < 2) {
        fprintf(
            stderr,
            "Internal error: invalid string buffer.\n"
        );

        return;
    }

    /*
     * fgets() takes an int as its size argument.
     *
     * Validate the size before converting size_t
     * to int so -Wconversion remains clean.
     */
    if (size > (size_t)INT_MAX) {
        fprintf(
            stderr,
            "Internal error: string buffer is too large.\n"
        );

        return;
    }

    const int inputSize = (int)size;

    while (1) {
        size_t length;

        printf("%s", prompt);

        if (fgets(buffer, inputSize, stdin) == NULL) {
            printf("\nInput error. Please try again.\n");
            clearerr(stdin);
            continue;
        }

        length = strlen(buffer);

        /*
         * Normal case:
         * fgets() captured the newline.
         */
        if (length > 0 &&
            buffer[length - 1] == '\n') {

            buffer[length - 1] = '\0';
        }

        /*
         * No newline means the input was
         * longer than the available buffer.
         */
        else {
            clearInputBuffer();

            printf(
                "Input is too long. "
                "Maximum length is %zu characters.\n",
                size - 1
            );

            continue;
        }

        /*
         * Reject empty input.
         */
        if (buffer[0] == '\0') {
            printf("Input cannot be empty.\n");
            continue;
        }

        return;
    }
}