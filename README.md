The primary goal of this project is to develop a library management system where students can issue books and the librarian can manage the book records. The system has two main parts: user operations and admin operations.

Admin Operations:
First, the librarian must log in with a predefined username and password. Upon successful login, the librarian can add, delete, or update book records. Adding a new book incorporates it into an existing catalog, while deleting removes it from the system. In the update option, the librarian can modify both the quantity and the name of the book. Each new book added by the admin is stored in a binary search tree (BST), ensuring the books are sorted by name.

User Operations:
Students must log in with their valid university ID to issue or return books. The system verifies the ID against a predefined list of valid student IDs. When a student attempts to issue a book, the system searches for the book name in the BST. If the book isn't found, a message stating "Book is not available in the library" is displayed. If the book is found but out of stock, the message "This book is currently unavailable. Please try after some days" is shown. Students are limited to issuing a maximum of two books at a time.

When a student successfully issues a book, the issue date and time are recorded. If the student fails to return the book by the due date, they are required to pay a fine. The system handles both the tracking of issued books and the calculation of overdue fines.
