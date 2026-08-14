#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

/*
 * Read a valid integer from standard input.
 *
 * The function keeps prompting until a valid integer
 * within the range of int is entered.
 */
int readInt(const char *prompt);

/*
 * Read an integer within the specified inclusive range.
 *
 * The function keeps prompting until the entered value
 * is between min and max.
 */
int readIntRange(
    const char *prompt,
    int min,
    int max
);

/*
 * Read a floating-point number within the specified
 * inclusive range.
 *
 * The function rejects invalid, non-finite, and
 * out-of-range values.
 */
float readFloatRange(
    const char *prompt,
    float min,
    float max
);

/*
 * Read a non-empty string from standard input.
 *
 * The supplied size includes space for the terminating
 * null character ('\0').
 *
 * Input longer than the available buffer is rejected
 * rather than silently truncated.
 */
void readString(
    const char *prompt,
    char *buffer,
    size_t size
);

#endif /* INPUT_H */