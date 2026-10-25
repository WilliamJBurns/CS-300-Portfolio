# CS 300: Data Structures and Algorithms Portfolio

This repository showcases work completed in **CS 300: Data Structures and Algorithms** at Southern New Hampshire University. Both projects focused on an advising assistance program that reads computer science course information, displays courses in alphanumeric order, and lets a user look up an individual course and its prerequisites.

## Portfolio Artifacts

- **[Project One: Pseudocode and Runtime Analysis](CS300_Project_One_Pseudocode_and_Runtime_Analysis.docx)** — Pseudocode for vector, hash table, and binary search tree approaches, along with runtime and memory analysis and a recommendation.
- **[Project Two: Advising Assistance Program](ProjectTwo.cpp)** — A C++ implementation that stores courses in a binary search tree and supports sorted course listings and course lookups.

## Project Two: Implementation Overview

The C++ program loads comma-separated course records containing a course number, course name, and optional prerequisite course numbers. It checks required fields and verifies that each prerequisite refers to a course in the file before inserting the records into a binary search tree. The program then offers a menu to print the full course list or look up a course and display its prerequisites.

Each tree node stores a `Course` record, and course numbers determine whether a record belongs in the left or right subtree. An **in-order traversal** prints the courses in alphanumeric order without a separate sorting step. The program also includes input handling, whitespace trimming, case normalization for course-number searches, and a tree destructor to release allocated nodes.

### Compile and Run

With a C++17-compatible compiler:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic ProjectTwo.cpp -o course_planner
./course_planner
```

Choose **1** to load a course data file, **2** to print the courses in order, **3** to search for a course, or **9** to exit. Each line of the data file should follow this format:

```text
CourseNumber,CourseName,OptionalPrerequisite1,OptionalPrerequisite2
```

The prerequisite course numbers must also be present as course records in the file.

## Reflection

### What was the problem you were solving in the projects for this course?

The main problem was designing an advising assistance program that could organize computer science course information and make it useful to students and advisors. The program needed to load course records, display the full course list in alphanumeric order, and show the prerequisites for a specific course. In Project One, I evaluated different ways to store and retrieve that information before choosing an approach. In Project Two, I turned the design into a working C++ application. Together, the projects showed me that solving a programming problem involves more than getting the correct output; the underlying design matters, too.

### How did you approach the problem? Consider why data structures are important to understand.

I approached the problem by comparing a vector, hash table, and binary search tree against the program's actual requirements. A vector is simple and has relatively low memory overhead, but searching involves scanning records and printing a sorted list requires sorting. A hash table supports efficient lookups on average, but it does not naturally keep records in order. A binary search tree supports searching by course number and can print the courses in order through an in-order traversal. My Project One analysis also considered runtime and memory costs, including the O(n) storage requirements of all three approaches. This helped me understand that choosing a data structure is a decision about the operations a program needs to perform, not just where to put the data.

### How did you overcome any roadblocks you encountered while going through the activities or project?

A major design challenge was making sure the program handled relationships between courses correctly. Reading a line from a file was only part of the problem; the program also needed to confirm that every listed prerequisite referred to a course in the data. I addressed this by separating file parsing and prerequisite validation from insertion into the binary search tree. The implementation also checks for missing files or required fields, trims unnecessary whitespace, and handles invalid menu input. Another issue I had to account for was that a regular binary search tree can become unbalanced, so its performance depends on the order in which records are inserted. Working through these considerations pushed me to think about error handling and tradeoffs alongside the main features.

### How has your work on this project expanded your approach to designing software and developing programs?

These projects strengthened my habit of planning the structure of a program before writing the implementation. Writing pseudocode for three different approaches made it easier to compare their behavior and explain why one was a better fit. I chose a binary search tree because its in-order traversal directly addressed the sorted-list requirement while also supporting course searches. When I moved to C++, I organized the program around a `Course` structure, a `BinarySearchTree` class, and separate functions for loading and displaying course information. I now think more deliberately about how requirements, algorithms, data structures, and error handling fit together before focusing on individual lines of code.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

I paid more attention to separating responsibilities and making the code understandable to someone who did not write it. The `BinarySearchTree` class keeps the tree operations together, while functions such as `trim`, `loadCourses`, and `printCourseInformation` handle specific tasks. Descriptive names and comments help explain the program's intent, and the destructor cleans up dynamically allocated tree nodes. This organization makes it easier to find a problem or change one part of the program without rewriting everything. I also see opportunities for improvement, such as detecting duplicate course numbers and adding more automated tests. Those are the kinds of refinements I would consider as the program grows beyond this course assignment.
