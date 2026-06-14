# integrative-project
this program simulates a library management system. It allows users to register students and teachers, add books, borrow and return them,and search or compare books by rating.

to compile and run the program, use this: g++ -std=c++14 -Wall library.cpp -o library

the program will show a menu with 11 options. Use the number keys to navigate.

An example of output is:

LIBRARY OPTIONS
1.  show Books
2.  register Student
   
...

student name: Ana Garcia

career: Computer Science

Person created: Ana Garcia

student created: Ana Garcia

book title: harry potter

successfully loan.

error: person not registered: Juan

error: this book is not borrowed.

The program demonstrates all the necessary concepts of OOP. Composition is shown in the Library class, which contains its books, loans, and users. Aggregation is represented by the Catalog, which exists independently and is referenced by Library through a pointer without property. Dependency is manifested in methods such as `borrowBook()` and `searchBook()`, which use temporary parameters. Encapsulation is ensured through class methods that maintain valid state, such as preventing loans or ratings of invalid books. Inheritance is demonstrated with the Student and Professor classes, which derive from the abstract Person class, while runtime polymorphism is achieved through a `unique_ptr<Person>` array and virtual calls to `displayInfo()`. Operator overloading is implemented in Book and Rating, and a virtual destructor in Person ensures the proper cleanup of derived objects.

The project follows the Zero Rule, as all resources are managed using RAII types (string, vector, and unique_ptr), eliminating the need for custom copy, move, or destructor implementations. Smart pointers are used for property management, and exception handling is implemented using LibraryException, which derives from std::exception.

Person is the abstract base class; Student and Professor are specialized derived classes; Book stores book information; Rating demonstrates operator overloading; Loan records loan transactions; Catalog acts as an independent collection of books; Library coordinates the system; and LibraryException handles runtime errors.
