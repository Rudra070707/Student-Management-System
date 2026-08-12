# Student Management System

A console-based Student Management System written in C.

## Features

- Add student
- Display students
- Search student by ID
- Update student
- Delete student
- Duplicate ID prevention
- Persistent binary file storage
- Input validation
- Range validation
- Error handling

## Technologies

- C
- GCC
- C17
- Standard C Library

## Project Structure

```text
Student-Management-System/
│
├── bin/
│   └── student_manager.exe
│
├── include/
│   ├── input.h
│   └── student.h
│
├── src/
│   ├── input.c
│   ├── main.c
│   └── student.c
│
├── .gitignore
├── Makefile
├── README.md
└── students.dat
```

## Architecture

```text
main.c
  │
  ├── Menu
  │
  ▼
input.c
  │
  ├── Integer validation
  ├── Float validation
  └── String validation
  │
  ▼
student.c
  │
  ├── Add
  ├── Display
  ├── Search
  ├── Update
  └── Delete
  │
  ▼
students.dat
```

## Compile

```powershell
gcc -Wall -Wextra -Wpedantic -std=c17 -Iinclude src/main.c src/student.c src/input.c -o bin\student_manager.exe
```

## Run

```powershell
.\bin\student_manager.exe
```

## Compiler Flags

- `-Wall` — enable common warnings
- `-Wextra` — enable additional warnings
- `-Wpedantic` — enforce stricter ISO C conformance
- `-std=c17` — compile using the C17 standard
- `-Iinclude` — include header files from `include/`

## Current Limitations

This is an educational console application.

Current limitations include:

- Fixed maximum of 100 students
- Binary data file
- Linear search
- Single-user operation
- No authentication
- No database server
- No concurrent access support

## Future Improvements

Potential future versions can add:

- Sorting
- Student statistics
- Confirmation prompts
- Better terminal UI
- CSV export
- Database storage
- Logging
- Automated tests
- Modular service architectu

# Student Management System

A simple console-based Student Management System written in C.

## Features

- Add student
- Display all students
- Search student by ID
- Exit application

## Technologies

- C
- GCC
- C17

## Project Structure

```text
Student-Management-System/
│
├── bin/
├── include/
│   └── student.h
├── src/
│   ├── main.c
│   └── student.c
├── Makefile
└── README.md
```
