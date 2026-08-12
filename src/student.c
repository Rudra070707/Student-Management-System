#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "input.h"

#define DATA_FILE "students.dat"
#define TEMP_FILE "students.tmp"


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
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }

    return -1;
}


/*
 * Add a new student.
 */
void addStudent(Student students[], int *count)
{
    if (*count >= MAX_STUDENTS) {
        printf("\nStudent limit reached.\n");
        return;
    }

    printf("\n===== ADD STUDENT =====\n");

    int id = readIntRange(
        "Enter ID: ",
        1,
        2147483647
    );

    /*
     * Prevent duplicate student IDs.
     */
    if (findStudentIndex(students, *count, id) != -1) {
        printf("\nA student with this ID already exists.\n");
        return;
    }

    students[*count].id = id;

    readString(
        "Enter name: ",
        students[*count].name,
        NAME_LENGTH
    );

    students[*count].age = readIntRange(
        "Enter age: ",
        1,
        120
    );

    students[*count].marks = readFloatRange(
        "Enter marks: ",
        0.0f,
        100.0f
    );

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
    if (count == 0) {
        printf("\nNo students available.\n");
        return;
    }

    printf("\n===== ALL STUDENTS =====\n");

    for (int i = 0; i < count; i++) {
        printf("\nStudent %d\n", i + 1);

        printf("ID    : %d\n", students[i].id);
        printf("Name  : %s\n", students[i].name);
        printf("Age   : %d\n", students[i].age);
        printf("Marks : %.2f\n", students[i].marks);
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
    if (count == 0) {
        printf("\nNo students available.\n");
        return;
    }

    printf("\n===== SEARCH STUDENT =====\n");

    int id = readIntRange(
        "Enter student ID: ",
        1,
        2147483647
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

    printf("ID    : %d\n", students[index].id);
    printf("Name  : %s\n", students[index].name);
    printf("Age   : %d\n", students[index].age);
    printf("Marks : %.2f\n", students[index].marks);
}


/*
 * Update an existing student.
 */
void updateStudent(
    Student students[],
    int count
)
{
    if (count == 0) {
        printf("\nNo students available.\n");
        return;
    }

    printf("\n===== UPDATE STUDENT =====\n");

    int id = readIntRange(
        "Enter student ID: ",
        1,
        2147483647
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

    printf("ID    : %d\n", students[index].id);
    printf("Name  : %s\n", students[index].name);
    printf("Age   : %d\n", students[index].age);
    printf("Marks : %.2f\n", students[index].marks);

    printf("\nEnter new details:\n");

    /*
     * ID is intentionally not changed.
     * Student ID remains the unique identifier.
     */

    readString(
        "Enter name: ",
        students[index].name,
        NAME_LENGTH
    );

    students[index].age = readIntRange(
        "Enter age: ",
        1,
        120
    );

    students[index].marks = readFloatRange(
        "Enter marks: ",
        0.0f,
        100.0f
    );

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
    if (*count == 0) {
        printf("\nNo students available.\n");
        return;
    }

    printf("\n===== DELETE STUDENT =====\n");

    int id = readIntRange(
        "Enter student ID: ",
        1,
        2147483647
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
    for (int i = index; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }

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
 */
int loadStudents(Student students[])
{
    FILE *file = fopen(DATA_FILE, "rb");

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
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    /*
     * Protect against corrupted data containing
     * an impossible student count.
     */
    if (count < 0 || count > MAX_STUDENTS) {
        fclose(file);
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
            return 0;
        }
    }

    fclose(file);

    return count;
}


/*
 * Save students to disk.
 *
 * Data is first written to a temporary file.
 * Only after the temporary file is successfully
 * written do we replace the existing data file.
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
    FILE *file = fopen(TEMP_FILE, "wb");

    if (file == NULL) {
        printf(
            "\nError: Could not create temporary data file.\n"
        );

        return 0;
    }

    /*
     * Write the student count.
     */
    if (fwrite(&count, sizeof(int), 1, file) != 1) {
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
     * Make sure the file is properly closed.
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
     * Therefore remove the old file first.
     */
    remove(DATA_FILE);

    /*
     * Rename the successfully written temporary file.
     */
    if (rename(TEMP_FILE, DATA_FILE) != 0) {
        remove(TEMP_FILE);

        printf(
            "\nError: Could not replace data file.\n"
        );

        return 0;
    }

    return 1;
}