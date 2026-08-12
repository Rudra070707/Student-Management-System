#include <stdio.h>

#include "student.h"
#include "input.h"


int main(void)
{
    Student students[MAX_STUDENTS];

    int studentCount = loadStudents(students);

    printf("\nLoaded %d student(s).\n", studentCount);

    while (1) {
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

        int choice = readIntRange(
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
                 * Save immediately after an add.
                 */
                if (!saveStudents(
                        students,
                        studentCount
                    )) {
                    printf(
                        "Warning: Student was added in memory, "
                        "but could not be saved to disk.\n"
                    );
                }

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
                 * Save immediately after an update.
                 */
                if (!saveStudents(
                        students,
                        studentCount
                    )) {
                    printf(
                        "Warning: Changes were made in memory, "
                        "but could not be saved to disk.\n"
                    );
                }

                break;


            case 5:
                deleteStudent(
                    students,
                    &studentCount
                );

                /*
                 * Save immediately after deletion.
                 */
                if (!saveStudents(
                        students,
                        studentCount
                    )) {
                    printf(
                        "Warning: Changes were made in memory, "
                        "but could not be saved to disk.\n"
                    );
                }

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
                }

                printf("Exiting program...\n");

                return 0;
        }
    }
}