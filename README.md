
# Student Management System

A console-based Student Management System written in **C17**.

The application provides complete CRUD operations for student records, robust input validation, duplicate ID prevention, persistent binary-file storage, safe data saving, and automated build support through GNU Make.

---

## Features

- Add student
- Display all students
- Search student by ID
- Update student
- Delete student
- Duplicate student ID prevention
- Integer input validation
- Integer range validation
- Floating-point input validation
- Floating-point range validation
- Non-empty string validation
- Oversized string input protection
- Invalid input handling
- Persistent binary-file storage
- Safe temporary-file based saving
- Automatic data loading at startup
- Automatic saving after modifications
- Data saving on application exit
- File error handling
- Maximum capacity of 100 students

---

## Technologies

- **C**
- **C17**
- **GCC**
- **GNU Make**
- **Standard C Library**
- **Git**
- **GitHub**

---

## Project Structure

```text
Student-Management-System/
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
└── README.md
```

Runtime and compiled files are intentionally excluded from Git:

```text
bin/
students.dat
students.tmp
```

---

## Architecture

```text
                         STUDENT MANAGEMENT SYSTEM
                                    │
                                    ▼
                                main.c
                                    │
                     ┌──────────────┴──────────────┐
                     │                             │
                 Main Menu                    Application Flow
                     │                             │
                     ▼                             ▼
                 input.c                       student.c
                     │                             │
          ┌──────────┼──────────┐        ┌────────┼─────────┐
          │          │          │        │        │         │
       Integer     Float      String    Add     Search    Update
       Validation  Validation Validation Display Delete   Load/Save
                                                    │
                                                    ▼
                                               students.dat
```

### `main.c`

Responsible for:

- Application startup
- Loading student data
- Displaying the main menu
- Handling menu selection
- Calling student operations
- Saving data
- Application shutdown

### `input.c`

Responsible for:

- Integer input
- Integer range validation
- Floating-point input
- Floating-point range validation
- String input
- Input buffer handling
- Invalid input detection
- Oversized input detection

### `student.c`

Responsible for:

- Adding students
- Displaying students
- Searching students
- Updating students
- Deleting students
- Loading student records
- Saving student records
- Persistent file handling

---

## Application Menu

When the application starts, the following menu is displayed:

```text
==============================
   STUDENT MANAGEMENT SYSTEM
==============================
1. Add Student
2. Display Students
3. Search Student
4. Update Student
5. Delete Student
6. Exit
==============================
Enter your choice:
```

---

# Requirements

## Windows

The project is designed to run on Windows using the **MSYS2 UCRT64** environment.

Required tools:

- Windows 10 or Windows 11
- MSYS2
- UCRT64 environment
- GCC
- GNU Make
- Git

---

# Verify the Development Environment

Open the **MSYS2 UCRT64** terminal.

## Check GCC

```bash
gcc --version
```

Check its location:

```bash
where.exe gcc
```

Example:

```text
C:\msys64\ucrt64\bin\gcc.exe
```

## Check GNU Make

```bash
mingw32-make --version
```

Example:

```text
GNU Make 4.4.1
Built for x86_64-w64-mingw32
```

---

# Get the Project

If the repository has already been cloned:

```bash
cd /c/Users/Rudra/Engineering/Student-Management-System
```

If cloning the repository on another Windows computer:

```bash
git clone https://github.com/Rudra070707/Student-Management-System.git
```

Then:

```bash
cd Student-Management-System
```

---

# Build the Project

## Recommended Method — GNU Make

From the project directory:

```bash
mingw32-make
```

This builds:

```text
bin/student_manager.exe
```

If everything is already up to date, Make may display:

```text
mingw32-make: Nothing to be done for 'all'.
```

This is normal and means the executable is already current.

---

# Run the Application

From the MSYS2 UCRT64 terminal:

```bash
mingw32-make run
```

Alternatively:

```bash
./bin/student_manager.exe
```

From Windows PowerShell:

```powershell
.\bin\student_manager.exe
```

---

# Clean the Build

To remove the compiled executable:

```bash
mingw32-make clean
```

After cleaning, the `bin` directory is removed.

---

# Rebuild from Scratch

To remove the existing executable and compile everything again:

```bash
mingw32-make rebuild
```

This performs:

```text
clean
  │
  ▼
remove bin/
  │
  ▼
create bin/
  │
  ▼
compile source files
  │
  ▼
bin/student_manager.exe
```

---

# Build Without GNU Make

The application can also be compiled directly with GCC.

From the project directory:

```bash
gcc -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wstrict-prototypes -std=c17 -Iinclude src/main.c src/student.c src/input.c -o bin/student_manager.exe
```

Then run:

```bash
./bin/student_manager.exe
```

---

# Compiler Flags

The project uses strict compiler warnings:

```text
-Wall
-Wextra
-Wpedantic
-Wconversion
-Wshadow
-Wstrict-prototypes
-std=c17
```

| Flag                    | Purpose                                                 |
| ----------------------- | ------------------------------------------------------- |
| `-Wall`               | Enables common compiler warnings                        |
| `-Wextra`             | Enables additional compiler warnings                    |
| `-Wpedantic`          | Enforces stricter ISO C conformance                     |
| `-Wconversion`        | Warns about potentially unsafe implicit conversions     |
| `-Wshadow`            | Warns when variables shadow other variables             |
| `-Wstrict-prototypes` | Requires strict function prototypes                     |
| `-std=c17`            | Uses the C17 language standard                          |
| `-Iinclude`           | Adds the`include` directory to the header search path |

---

# Makefile Commands

The project provides four main Make targets.

## Build

```bash
mingw32-make
```

or:

```bash
mingw32-make all
```

## Run

```bash
mingw32-make run
```

## Clean

```bash
mingw32-make clean
```

## Rebuild

```bash
mingw32-make rebuild
```

---

# Using the Application

## Add Student

Select:

```text
1
```

Enter:

```text
ID
Name
Age
Marks
```

Example:

```text
Enter ID: 102
Enter name: Test Student
Enter age: 20
Enter marks: 85.5

Student added successfully.
```

---

## Display Students

Select:

```text
2
```

Example:

```text
===== ALL STUDENTS =====

Student 1
ID    : 101
Name  : Rudra Bandekar
Age   : 20
Marks : 90.00
```

---

## Search Student

Select:

```text
3
```

Enter the student's ID.

Example:

```text
===== SEARCH STUDENT =====
Enter student ID: 102

Student found.
ID    : 102
Name  : Test Student
Age   : 20
Marks : 85.50
```

If the ID does not exist:

```text
Student not found.
```

---

## Update Student

Select:

```text
4
```

Enter the student's ID.

The current details are displayed, followed by prompts for the new name, age, and marks.

Example:

```text
===== UPDATE STUDENT =====
Enter student ID: 102

Current details:
ID    : 102
Name  : Test Student
Age   : 20
Marks : 85.50

Enter new details:
Enter name: Updated Student
Enter age: 21
Enter marks: 91.5

Student updated successfully.
```

---

## Delete Student

Select:

```text
5
```

Enter the student's ID.

Example:

```text
===== DELETE STUDENT =====
Enter student ID: 102

Student deleted successfully.
```

---

## Exit

Select:

```text
6
```

The application performs a final save before exiting.

Example:

```text
Saving data...
Exiting program...
```

---

# Data Persistence

Student records are stored in:

```text
students.dat
```

The file uses binary storage.

The application follows this lifecycle:

```text
Application starts
       │
       ▼
Load students.dat
       │
       ▼
Student records in memory
       │
       ├── Add
       ├── Display
       ├── Search
       ├── Update
       └── Delete
       │
       ▼
Save changes
       │
       ▼
Application exits
```

The `students.dat` file is runtime data and is intentionally ignored by Git.

---

# Safe File Saving

The application uses a temporary file while saving student records.

General process:

```text
Current data
     │
     ▼
students.tmp
     │
     │ successful write
     ▼
students.dat
```

This approach reduces the risk of leaving the primary data file partially written if a save operation fails.

---

# Input Validation

The application performs strict validation of user input.

## Integer Validation

Invalid examples:

```text
abc
12abc
12.5
```

The application accepts valid whole numbers within the supported `int` range.

---

## Integer Range Validation

Values outside the required application range are rejected.

For example, menu selection is restricted to:

```text
1 - 6
```

---

## Floating-Point Validation

Invalid examples:

```text
abc
85abc
```

The application also rejects:

- Invalid floating-point values
- Overflow
- Underflow
- NaN
- Infinity
- Values outside the requested range

---

## String Validation

The application rejects:

- Empty input
- Input longer than the available buffer

Oversized input is rejected rather than silently truncated.

---

# Student Data

Each student record contains:

```text
ID
Name
Age
Marks
```

The application supports a maximum of:

```text
100 students
```

---

# Duplicate ID Prevention

Every student ID must be unique.

If an ID already exists, the application prevents another student from being added with the same ID.

Example:

```text
A student with this ID already exists.
```

---

# Error Handling

The application includes error handling for:

- Invalid user input
- Out-of-range values
- Invalid numeric values
- Oversized strings
- Invalid file operations
- Failed file reads
- Failed file writes
- Invalid loaded student counts
- Failed final save operations

---

# Git Version Control

The project uses Git for source control.

Check repository status:

```bash
git status
```

View recent commits:

```bash
git log --oneline --decorate -5
```

View the remote repository:

```bash
git remote -v
```

View tracked files:

```bash
git ls-files
```

View unstaged changes:

```bash
git diff
```

Check whitespace errors:

```bash
git diff --check
```

---

# GitHub Repository

Repository:

https://github.com/Rudra070707/Student-Management-System

The repository contains the source code, headers, build configuration, documentation, and Git configuration.

Compiled executables and runtime student data are intentionally excluded from the repository.

---

# Git Ignore

The `.gitignore` file excludes generated and machine-specific files such as:

```text
bin/
build/
*.exe
*.out
students.dat
students.tmp
*.tmp
*.temp
*.log
.vscode/
Thumbs.db
.DS_Store
desktop.ini
*.o
*.obj
*.a
*.lib
*.dll
*.dmp
```

This keeps the Git repository focused on source code and project files rather than generated artifacts.

---

# Code Quality

The project follows basic software engineering practices including:

- Modular source files
- Header/source separation
- Static helper functions
- `const` correctness
- Input validation
- Range validation
- File error handling
- Safe temporary-file saving
- Strict compiler warnings
- C17 standard
- Build automation
- Git version control
- GitHub repository management

---

# Current Limitations

This is an educational console application.

Current limitations include:

- Maximum of 100 students
- Binary file storage
- Linear search
- Single-user operation
- No authentication
- No database server
- No concurrent access support
- Console-only interface
- No network functionality
- No graphical user interface

---

# Future Improvements

Potential future versions can add:

- Student sorting
- Student statistics
- Grade calculation
- Confirmation prompts
- Improved terminal interface
- CSV export
- CSV import
- Database storage
- SQLite integration
- MySQL integration
- Logging
- Automated unit tests
- Automated integration tests
- Search by name
- Advanced filtering
- Pagination
- Configuration files
- Backup and restore
- Authentication
- Role-based access
- Graphical user interface
- Cross-platform packaging

---

# Project Status

**Stable educational version**

Currently implemented:

- Complete CRUD operations
- Duplicate ID prevention
- Input validation
- Range validation
- Persistent binary storage
- Safe saving
- Automatic loading
- Error handling
- GCC compilation
- Strict compiler warnings
- GNU Make build system
- Git version control
- GitHub repository

---

# Author

**Rudra Bandekar**

Computer Engineering Project

---

## Quick Start

For a machine that already has MSYS2 UCRT64, GCC, GNU Make, and Git installed:

```bash
git clone https://github.com/Rudra070707/Student-Management-System.git
cd Student-Management-System
mingw32-make
mingw32-make run
```

To rebuild from scratch:

```bash
mingw32-make rebuild
```

To clean the compiled files:

```bash
mingw32-make clean
```
