# Library Management System

## Project Summary
This project implements a simplified library management system, focusing on essential functionalities to manage a collection of books. The system interacts with the user through a set of specific commands, allowing for various operations on the library's entries.

## How to Run the Project
1. Clone the repository to your local machine.
2. Navigate to the project directory in your terminal or command prompt.
3. Compile the project using your C++ compiler (e.g., `g++ -o library_management_system main.cpp`).
4. Run the executable (e.g., `./library_management_system` on Unix-based systems or `library_management_system.exe` on Windows).

## Functionalities & Commands
- **A** - Add Item To Library: Add a new book entry to the library.
- **C** - Clear The Library Of All Entries: Remove all entries from the library.
- **D** - Display Library Entries: Show all the books currently in the library.
- **I** - List Invalid Library Entries: Display entries that have invalid data.
- **L** - Load Library From File: Load library entries from a CSV file.
- **O** - Output Library To File: Save the current library entries to a CSV file.
- **P** - Print Out Checkout Stats: Display statistics on the library's entries based on their checkout status.
- **R** - Remove A Library Entry: Remove a specific entry from the library.
- **S** - Search For A Library Entry: Search for a book in the library by title or ISBN.
- **X** - Exit Program: Terminate the program.

## Data Structure
The library management system tracks three main pieces of information for each book:
- **Book Title**: A string representing the title of the book. It cannot contain commas and can be one or more words.
- **ISBN Number**: A string representing a 13-digit ISBN number, formatted with hyphens. The default value is "000-0-00-000000-0".
- **Checkout Status**: An integer representing the book's status. Possible values are:
  - 0: In Library (default)
  - 1: Checked Out
  - 2: On Loan
  - 3: Unknown State
  - All Others: Invalid State

## Milestones
1. **Data Structures & Exiting**: Set up the necessary data structures and ensure the program can exit correctly.
2. **Add Entry to the Library**: Implement the functionality to add new book entries.
3. **Display the Library**: Implement the functionality to display all library entries.
4. **Clear the Library**: Implement the functionality to remove all entries from the library.
5. **Load Library From File**: Implement the functionality to load library entries from a file.
6. **Output Library To A File**: Implement the functionality to save the current library entries to a file.
7. **Print the Checkout Stats**: Implement the functionality to display statistics based on checkout status.
8. **Search the Library**: Implement the functionality to search for a book by title or ISBN.
9. **Remove an Entry**: Implement the functionality to remove a specific entry from the library.
10. **Print Out Invalid Entries**: Implement the functionality to display entries with invalid data.

## Error Messages
- Unknown command.
- The book title cannot contain commas.
- Could not find the database file.
- Could not open database file for writing.
- Invalid remove by choice option.
- Invalid search by choice option.
- The library has no books.
- The library has no invalid entries.
