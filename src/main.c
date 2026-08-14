#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "input.h"

/*
 * Display the main application menu.
 */
static void displayMenu(void)
{
    printf("\n==============================\n");
    printf("   STUDENT MANAGEMENT SYSTEM\n");
    printf("==============================\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Exit\n");
    printf("==============================\n");
}

/*
 * Save the current student data.
 *
 * Returns non-zero when saving succeeds
 * and zero when saving fails.
 */
static int saveCurrentData(
    const Student students[],
    int studentCount
)
{
    if (!saveStudents(students, studentCount)) {
        printf(
            "Warning: Changes were made in memory, "
            "but could not be saved to disk.\n"
        );

        return 0;
    }

    return 1;
}

int main(void)
{
    Student students[MAX_STUDENTS];

    int studentCount = loadStudents(students);

    /*
     * loadStudents() should return a valid count,
     * but protect the main application from an
     * invalid value.
     */
    if (studentCount < 0 ||
        studentCount > MAX_STUDENTS) {

        fprintf(
            stderr,
            "Error: Invalid student data was loaded.\n"
        );

        return EXIT_FAILURE;
    }

    printf(
        "\nLoaded %d student(s).\n",
        studentCount
    );

    while (1) {
        int choice;

        displayMenu();

        choice = readIntRange(
            "Enter your choice: ",
            1,
            6
        );

        switch (choice) {

            case 1:
                addStudent(
                    students,
                    &studentCount
                );

                /*
                 * Save immediately after adding.
                 */
                (void)saveCurrentData(
                    students,
                    studentCount
                );

                break;

            case 2:
                displayStudents(
                    students,
                    studentCount
                );

                break;

            case 3:
                searchStudent(
                    students,
                    studentCount
                );

                break;

            case 4:
                updateStudent(
                    students,
                    studentCount
                );

                /*
                 * Save immediately after updating.
                 */
                (void)saveCurrentData(
                    students,
                    studentCount
                );

                break;

            case 5:
                deleteStudent(
                    students,
                    &studentCount
                );

                /*
                 * Save immediately after deleting.
                 */
                (void)saveCurrentData(
                    students,
                    studentCount
                );

                break;

            case 6:
                printf("\nSaving data...\n");

                if (!saveStudents(
                        students,
                        studentCount
                    )) {

                    printf(
                        "Warning: Data could not be saved.\n"
                    );

                    /*
                     * Report a failed final save through
                     * the process exit status.
                     */
                    return EXIT_FAILURE;
                }

                printf("Exiting program...\n");

                return EXIT_SUCCESS;

            default:
                /*
                 * readIntRange() guarantees that this
                 * case cannot normally be reached.
                 */
                fprintf(
                    stderr,
                    "Internal error: invalid menu choice.\n"
                );

                return EXIT_FAILURE;
        }
    }
}