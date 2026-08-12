#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

/*
 * Read a valid integer.
 */
int readInt(const char *prompt);

/*
 * Read an integer within a specified range.
 */
int readIntRange(
    const char *prompt,
    int min,
    int max
);

/*
 * Read a floating-point number within
 * a specified range.
 */
float readFloatRange(
    const char *prompt,
    float min,
    float max
);

/*
 * Read a non-empty string.
 */
void readString(
    const char *prompt,
    char *buffer,
    size_t size
);

#endif /* INPUT_H */
