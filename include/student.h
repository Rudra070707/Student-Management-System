#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

/*
 * Represents a single student record.
 *
 * id    : Unique student identifier.
 * name  : Student name, including space for the
 *         terminating null character.
 * age   : Student age.
 * marks : Student marks.
 */
typedef struct
{
    int id;
    char name[NAME_LENGTH];
    int age;
    float marks;
} Student;

/*
 * Student operations
 */

/*
 * Add a new student to the array.
 *
 * The function updates count when a student is
 * successfully added.
 */
void addStudent(
    Student students[],
    int *count
);

/*
 * Display all stored students.
 */
void displayStudents(
    const Student students[],
    int count
);

/*
 * Search for a student by ID and display the
 * matching student if found.
 */
void searchStudent(
    const Student students[],
    int count
);

/*
 * Update an existing student identified by ID.
 */
void updateStudent(
    Student students[],
    int count
);

/*
 * Delete an existing student identified by ID.
 *
 * The function decreases count when a student
 * is successfully deleted.
 */
void deleteStudent(
    Student students[],
    int *count
);

/*
 * File persistence
 */

/*
 * Load student records from persistent storage.
 *
 * Returns the number of successfully loaded students.
 */
int loadStudents(
    Student students[]
);

/*
 * Save student records to persistent storage.
 *
 * Returns a non-zero value on success and zero
 * on failure.
 */
int saveStudents(
    const Student students[],
    int count
);

#endif /* STUDENT_H */