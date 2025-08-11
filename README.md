# Teenminal

**Teenminal** is a fun, lightweight, and fully terminal-based productivity hub **made by teens, for teens**.  
It’s built for students who want to stay organized, manage projects, record their life and keep track of school, hobbies, and life — all without leaving the comfort of the command line.

---

## Features

### Productivity

- **Journal**: Add, read, and list daily journal entries with optional date specification.
- **Todo**: Manage your to-do list by adding tasks, marking them done, and listing tasks by date.
- **Exam**: Add exams with names and dates, list upcoming exams with countdown.
- **Homework**: Add and list homework assignments with due dates.
- **Ideas**: Quickly record and list your ideas for future reference.

### Media & Learning

- **Movies**: Add, view, and list movies with ratings and reviews.
- **Books**: Add, view, and list books you've read, with ratings and reviews.
- **Series**: Manage your favorite TV series similarly with add, view, and list commands.

### Projects & Achievements

- **Projects**: Save project titles and descriptions, view detailed project info, and list all projects.

### System Utilities

- Create directories (`mkdir` command).
- Run external system commands (`run` command).
- View command history (`history` command).
- Get a comprehensive help guide (`help` command).
- Exit the application with `exit`.

---

## Installation and Building

### Prerequisites

- C++17 or later compiler (e.g., `g++`, `clang++`).
- CMake (optional but recommended for building).
- [Filesystem library support](https://en.cppreference.com/w/cpp/filesystem) (C++17 std::filesystem).

---

### Building with g++

If you already have compiled object files (`*.o`), link them like this:

```bash
g++ obj/*.o -o bin/teenminal.exe
```

Or compile from sources directly:

```bash
g++ -std=c++17 -o bin/teenminal.exe src/*.cpp
```

### Running

```bash
./bin/teenminal.exe
```

On windows:

```bash
bin\teenminal.exe
```

## Usage

When you start the program, you will see:

```bash
teenminal>
```

Type help to see the complete list of available commands.

### Example commands

```bash
journal add "My first journal entry" 2025-08-10
todo add "Finish homework" 2025-08-11
exam list
movie add "Inception" 9 "Great sci-fi thriller"
project list
mkdir my/new/project
run ls -la
history
exit

```
