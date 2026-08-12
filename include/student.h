#ifndef STUDENT_H
#define STUDENT_H


#define MAX_STUDENTS 100
#define NAME_LENGTH 50


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
void addStudent(Student students[], int *count);

void displayStudents(
    const Student students[],
    int count
);

void searchStudent(
    const Student students[],
    int count
);

void updateStudent(
    Student students[],
    int count
);

void deleteStudent(
    Student students[],
    int *count
);


/*
 * File persistence
 */
int loadStudents(Student students[]);

int saveStudents(
    const Student students[],
    int count
);


#endif /* STUDENT_H */