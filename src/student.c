#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "student.h"
#include "input.h"

#define DATA_FILE "students.dat"
#define TEMP_FILE "students.tmp"

#define MIN_STUDENT_ID 1
#define MIN_STUDENT_AGE 1
#define MAX_STUDENT_AGE 120
#define MIN_STUDENT_MARKS 0.0f
#define MAX_STUDENT_MARKS 100.0f

/*
 * Find the array index of a student using their ID.
 *
 * Returns:
 *   - Student index if found
 *   - -1 if not found
 */
static int findStudentIndex(
    const Student students[],
    int count,
    int id
)
{
    if (students == NULL || count <= 0) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }

    return -1;
}

/*
 * Check whether a student name is safely
 * null-terminated within the fixed-size array.
 *
 * Returns:
 *   1 = null terminator found
 *   0 = no null terminator found
 */
static int hasValidNameTermination(
    const char name[]
)
{
    if (name == NULL) {
        return 0;
    }

    return memchr(
        name,
        '\0',
        sizeof(((Student *)0)->name)
    ) != NULL;
}

/*
 * Check whether a name contains at least
 * one non-whitespace character.
 *
 * Returns:
 *   1 = contains non-whitespace character
 *   0 = empty or whitespace-only
 */
static int hasNonWhitespaceName(
    const char name[]
)
{
    if (name == NULL) {
        return 0;
    }

    for (size_t i = 0;
         i < sizeof(((Student *)0)->name);
         i++) {

        unsigned char character =
            (unsigned char)name[i];

        if (character == '\0') {
            break;
        }

        if (character != ' ' &&
            character != '\t' &&
            character != '\r' &&
            character != '\n' &&
            character != '\v' &&
            character != '\f') {

            return 1;
        }
    }

    return 0;
}

/*
 * Validate a single student record.
 *
 * Returns:
 *   1 = valid
 *   0 = invalid
 */
static int isValidStudent(
    const Student *student
)
{
    if (student == NULL) {
        return 0;
    }

    /*
     * Student ID must be positive.
     */
    if (student->id < MIN_STUDENT_ID) {
        return 0;
    }

    /*
     * The name must contain a null terminator
     * inside the fixed-size array.
     */
    if (!hasValidNameTermination(student->name)) {
        return 0;
    }

    /*
     * Reject empty and whitespace-only names.
     */
    if (!hasNonWhitespaceName(student->name)) {
        return 0;
    }

    /*
     * Validate age.
     */
    if (student->age < MIN_STUDENT_AGE ||
        student->age > MAX_STUDENT_AGE) {

        return 0;
    }

    /*
     * Validate marks.
     *
     * isfinite() is important because NaN would
     * otherwise bypass the normal < and > checks.
     */
    if (!isfinite(student->marks)) {
        return 0;
    }

    if (student->marks < MIN_STUDENT_MARKS ||
        student->marks > MAX_STUDENT_MARKS) {

        return 0;
    }

    return 1;
}

/*
 * Validate all loaded student records.
 *
 * This also checks for duplicate IDs.
 *
 * Returns:
 *   1 = valid
 *   0 = invalid
 */
static int validateStudents(
    const Student students[],
    int count
)
{
    /*
     * Zero students is a valid state.
     */
    if (count == 0) {
        return 1;
    }

    if (students == NULL) {
        return 0;
    }

    if (count < 0 ||
        count > MAX_STUDENTS) {

        return 0;
    }

    for (int i = 0; i < count; i++) {

        if (!isValidStudent(&students[i])) {
            return 0;
        }

        /*
         * Check for duplicate IDs.
         */
        for (int j = i + 1;
             j < count;
             j++) {

            if (students[i].id ==
                students[j].id) {

                return 0;
            }
        }
    }

    return 1;
}

/*
 * Add a new student.
 */
void addStudent(
    Student students[],
    int *count
)
{
    if (students == NULL ||
        count == NULL) {

        fprintf(
            stderr,
            "Internal error: invalid student storage.\n"
        );

        return;
    }

    if (*count < 0 ||
        *count > MAX_STUDENTS) {

        fprintf(
            stderr,
            "Internal error: invalid student count.\n"
        );

        return;
    }

    if (*count >= MAX_STUDENTS) {
        printf("\nStudent limit reached.\n");
        return;
    }

    printf("\n===== ADD STUDENT =====\n");

    int id = readIntRange(
        "Enter ID: ",
        MIN_STUDENT_ID,
        INT_MAX
    );

    /*
     * Prevent duplicate student IDs.
     */
    if (findStudentIndex(
            students,
            *count,
            id
        ) != -1) {

        printf(
            "\nA student with this ID already exists.\n"
        );

        return;
    }

    Student student = {0};

    student.id = id;

    readString(
        "Enter name: ",
        student.name,
        NAME_LENGTH
    );

    student.age = readIntRange(
        "Enter age: ",
        MIN_STUDENT_AGE,
        MAX_STUDENT_AGE
    );

    student.marks = readFloatRange(
        "Enter marks: ",
        MIN_STUDENT_MARKS,
        MAX_STUDENT_MARKS
    );

    /*
     * Final validation before inserting
     * the record into the array.
     */
    if (!isValidStudent(&student)) {

        fprintf(
            stderr,
            "Internal error: invalid student data.\n"
        );

        return;
    }

    students[*count] = student;
    (*count)++;

    printf("\nStudent added successfully.\n");
}

/*
 * Display all students.
 */
void displayStudents(
    const Student students[],
    int count
)
{
    if (count < 0 ||
        count > MAX_STUDENTS) {

        printf("\nInvalid student data.\n");
        return;
    }

    if (count == 0) {
        printf("\nNo students available.\n");
        return;
    }

    if (students == NULL) {
        printf("\nStudent data is unavailable.\n");
        return;
    }

    printf("\n===== ALL STUDENTS =====\n");

    for (int i = 0; i < count; i++) {

        printf(
            "\nStudent %d\n",
            i + 1
        );

        printf(
            "ID    : %d\n",
            students[i].id
        );

        printf(
            "Name  : %s\n",
            students[i].name
        );

        printf(
            "Age   : %d\n",
            students[i].age
        );

        printf(
            "Marks : %.2f\n",
            students[i].marks
        );
    }
}

/*
 * Search for a student by ID.
 */
void searchStudent(
    const Student students[],
    int count
)
{
    if (count < 0 ||
        count > MAX_STUDENTS) {

        printf("\nInvalid student data.\n");
        return;
    }

    if (count == 0) {
        printf("\nNo students available.\n");
        return;
    }

    if (students == NULL) {
        printf("\nStudent data is unavailable.\n");
        return;
    }

    printf("\n===== SEARCH STUDENT =====\n");

    int id = readIntRange(
        "Enter student ID: ",
        MIN_STUDENT_ID,
        INT_MAX
    );

    int index = findStudentIndex(
        students,
        count,
        id
    );

    if (index == -1) {
        printf("\nStudent not found.\n");
        return;
    }

    printf("\nStudent found.\n");

    printf(
        "ID    : %d\n",
        students[index].id
    );

    printf(
        "Name  : %s\n",
        students[index].name
    );

    printf(
        "Age   : %d\n",
        students[index].age
    );

    printf(
        "Marks : %.2f\n",
        students[index].marks
    );
}

/*
 * Update an existing student.
 */
void updateStudent(
    Student students[],
    int count
)
{
    if (count < 0 ||
        count > MAX_STUDENTS) {

        printf("\nInvalid student data.\n");
        return;
    }

    if (count == 0) {
        printf("\nNo students available.\n");
        return;
    }

    if (students == NULL) {
        printf("\nStudent data is unavailable.\n");
        return;
    }

    printf("\n===== UPDATE STUDENT =====\n");

    int id = readIntRange(
        "Enter student ID: ",
        MIN_STUDENT_ID,
        INT_MAX
    );

    int index = findStudentIndex(
        students,
        count,
        id
    );

    if (index == -1) {
        printf("\nStudent not found.\n");
        return;
    }

    printf("\nCurrent details:\n");

    printf(
        "ID    : %d\n",
        students[index].id
    );

    printf(
        "Name  : %s\n",
        students[index].name
    );

    printf(
        "Age   : %d\n",
        students[index].age
    );

    printf(
        "Marks : %.2f\n",
        students[index].marks
    );

    /*
     * Build the updated record separately.
     *
     * This prevents the existing record from being
     * partially modified if an internal validation
     * failure occurs.
     */
    Student updatedStudent = students[index];

    printf("\nEnter new details:\n");

    /*
     * ID is intentionally not changed.
     *
     * Student ID remains the unique identifier.
     */
    readString(
        "Enter name: ",
        updatedStudent.name,
        NAME_LENGTH
    );

    updatedStudent.age = readIntRange(
        "Enter age: ",
        MIN_STUDENT_AGE,
        MAX_STUDENT_AGE
    );

    updatedStudent.marks = readFloatRange(
        "Enter marks: ",
        MIN_STUDENT_MARKS,
        MAX_STUDENT_MARKS
    );

    /*
     * Validate the complete updated record
     * before replacing the existing record.
     */
    if (!isValidStudent(&updatedStudent)) {

        fprintf(
            stderr,
            "Internal error: updated student data is invalid.\n"
        );

        return;
    }

    students[index] = updatedStudent;

    printf("\nStudent updated successfully.\n");
}

/*
 * Delete a student by ID.
 */
void deleteStudent(
    Student students[],
    int *count
)
{
    if (students == NULL ||
        count == NULL) {

        fprintf(
            stderr,
            "Internal error: invalid student storage.\n"
        );

        return;
    }

    if (*count < 0 ||
        *count > MAX_STUDENTS) {

        fprintf(
            stderr,
            "Internal error: invalid student count.\n"
        );

        return;
    }

    if (*count == 0) {
        printf("\nNo students available.\n");
        return;
    }

    printf("\n===== DELETE STUDENT =====\n");

    int id = readIntRange(
        "Enter student ID: ",
        MIN_STUDENT_ID,
        INT_MAX
    );

    int index = findStudentIndex(
        students,
        *count,
        id
    );

    if (index == -1) {
        printf("\nStudent not found.\n");
        return;
    }

    /*
     * Shift all students after the deleted
     * student one position to the left.
     */
    for (int i = index;
         i < *count - 1;
         i++) {

        students[i] = students[i + 1];
    }

    /*
     * Clear the now-unused final element.
     */
    students[*count - 1] = (Student){0};

    (*count)--;

    printf("\nStudent deleted successfully.\n");
}

/*
 * Load students from the binary data file.
 *
 * Returns:
 *   Number of students loaded.
 *
 * Returns 0 if:
 *   - File does not exist
 *   - File is invalid
 *   - File cannot be read
 *   - Student records are invalid
 */
int loadStudents(Student students[])
{
    if (students == NULL) {

        fprintf(
            stderr,
            "Internal error: invalid student storage.\n"
        );

        return 0;
    }

    FILE *file = fopen(
        DATA_FILE,
        "rb"
    );

    /*
     * No data file is normal on the first run.
     */
    if (file == NULL) {
        return 0;
    }

    int count = 0;

    /*
     * Read the number of students first.
     */
    if (fread(
            &count,
            sizeof(count),
            1,
            file
        ) != 1) {

        fclose(file);
        return 0;
    }

    /*
     * Protect against corrupted data containing
     * an impossible student count.
     */
    if (count < 0 ||
        count > MAX_STUDENTS) {

        fclose(file);

        fprintf(
            stderr,
            "Warning: Invalid student count in data file.\n"
        );

        return 0;
    }

    /*
     * If there are students, read them from the file.
     */
    if (count > 0) {

        size_t studentsRead = fread(
            students,
            sizeof(Student),
            (size_t)count,
            file
        );

        if (studentsRead != (size_t)count) {

            fclose(file);

            fprintf(
                stderr,
                "Warning: Student data file is incomplete or corrupted.\n"
            );

            return 0;
        }
    }

    /*
     * Check for unexpected trailing data.
     */
    unsigned char extraByte;

    if (fread(
            &extraByte,
            sizeof(extraByte),
            1,
            file
        ) == 1) {

        fclose(file);

        fprintf(
            stderr,
            "Warning: Student data file contains unexpected data.\n"
        );

        return 0;
    }

    /*
     * Distinguish normal EOF from a real read error.
     */
    if (ferror(file)) {

        fclose(file);

        fprintf(
            stderr,
            "Warning: Error while reading student data file.\n"
        );

        return 0;
    }

    if (fclose(file) != 0) {

        fprintf(
            stderr,
            "Warning: Could not close student data file.\n"
        );

        return 0;
    }

    /*
     * Validate every loaded record and ensure
     * student IDs are unique.
     */
    if (!validateStudents(
            students,
            count
        )) {

        fprintf(
            stderr,
            "Warning: Student data file contains invalid records.\n"
        );

        return 0;
    }

    return count;
}

/*
 * Save students to disk.
 *
 * Data is first written to a temporary file.
 * Only after the temporary file is successfully
 * written is it renamed to the actual data file.
 *
 * Returns:
 *   1 = success
 *   0 = failure
 */
int saveStudents(
    const Student students[],
    int count
)
{
    /*
     * Validate arguments.
     */
    if (count < 0 ||
        count > MAX_STUDENTS) {

        fprintf(
            stderr,
            "\nError: Invalid student count.\n"
        );

        return 0;
    }

    if (count > 0 &&
        students == NULL) {

        fprintf(
            stderr,
            "\nError: Invalid student storage.\n"
        );

        return 0;
    }

    /*
     * Validate all records before writing.
     */
    if (!validateStudents(
            students,
            count
        )) {

        fprintf(
            stderr,
            "\nError: Cannot save invalid student data.\n"
        );

        return 0;
    }

    FILE *file = fopen(
        TEMP_FILE,
        "wb"
    );

    if (file == NULL) {

        printf(
            "\nError: Could not create temporary data file.\n"
        );

        return 0;
    }

    /*
     * Write the student count.
     */
    if (fwrite(
            &count,
            sizeof(count),
            1,
            file
        ) != 1) {

        fclose(file);
        remove(TEMP_FILE);

        printf(
            "\nError: Could not save student count.\n"
        );

        return 0;
    }

    /*
     * Write student records.
     *
     * If count is zero, there is nothing to write.
     */
    if (count > 0) {

        size_t studentsWritten = fwrite(
            students,
            sizeof(Student),
            (size_t)count,
            file
        );

        if (studentsWritten != (size_t)count) {

            fclose(file);
            remove(TEMP_FILE);

            printf(
                "\nError: Could not save student data.\n"
            );

            return 0;
        }
    }

    /*
     * Flush buffered data before closing the file.
     */
    if (fflush(file) != 0) {

        fclose(file);
        remove(TEMP_FILE);

        printf(
            "\nError: Could not flush data to disk.\n"
        );

        return 0;
    }

    /*
     * Finalize the temporary file.
     */
    if (fclose(file) != 0) {

        remove(TEMP_FILE);

        printf(
            "\nError: Could not finalize data file.\n"
        );

        return 0;
    }

    /*
     * Windows does not allow rename() to replace an
     * existing file in the same way as Unix systems.
     *
     * Remove the existing data file first.
     */
    if (remove(DATA_FILE) != 0) {

        /*
         * Determine whether the existing data file
         * actually exists. A missing file is acceptable.
         */
        FILE *existingFile = fopen(
            DATA_FILE,
            "rb"
        );

        if (existingFile != NULL) {

            fclose(existingFile);
            remove(TEMP_FILE);

            printf(
                "\nError: Could not replace existing data file.\n"
            );

            return 0;
        }
    }

    /*
     * Rename the successfully written temporary file.
     */
    if (rename(
            TEMP_FILE,
            DATA_FILE
        ) != 0) {

        remove(TEMP_FILE);

        printf(
            "\nError: Could not replace data file.\n"
        );

        return 0;
    }

    return 1;
}