#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Person {
protected:
    int id;
    string name;
public:
    Person(int i, string n) : id(i), name(n) {}
    virtual void displayInfo() const = 0;
    virtual ~Person() {}
};

class Student : public Person {
private:
    string career;
public:
    Student(int i, string n, string c) : Person(i, n), career(c) {}
    string getName() const {
        return name;
    }
    void displayInfo() const override {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Career: " << career << endl;
    }
};

class Book {
private:
    string title;
    string author;
    string genre;
    string isbn;
    bool available;
public:
    Book(string t, string a, string g, string i) : title(t), author(a), genre(g), isbn(i), available(true) {}
    string getTitle() const {
        return title;
    }
    bool isAvailable() const {
        return available;
    }
    void borrowBook() {
        available = false;
    }
    void returnBook() {
        available = true;
    }
    void displayBook() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Genre: " << genre << endl;
        cout << "ISBN: " << isbn << endl;
        if (available)
            cout << "status: available" << endl;
        else
            cout << "status:no available" << endl;
    }
};

class Loan {
private:
    string studentName;
    string bookTitle;
public:
    Loan(string student, string book)
        : studentName(student),
          bookTitle(book) {}
    void displayLoan() const {
        cout << studentName
             << " borrowed "
             << bookTitle
             << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<Student> students;
    vector<Loan> loans;
public:
    void addBook(const Book& b) {
        books.push_back(b);
    }
    void addStudent(const Student& s) {
        students.push_back(s);
    }
    void showBooks() const {
        cout << "\nbooks\n";
        for (size_t i = 0; i < books.size(); i++) {
            books[i].displayBook();
            cout << endl;
        }
    }
    void showStudents() const {
        cout << "\nstudents\n";
        if (students.empty()) {
            cout << "no students registered\n";
            return;
        }
        for (size_t i = 0; i < students.size(); i++) {
            students[i].displayInfo();
            cout << endl;
        }
    }
    void searchBook(string title) const {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getTitle() == title) {
                cout << "\nbook found:\n";
                books[i].displayBook();
                return;
            }
        }
        cout << "book not found\n";
    }
    void borrowBook(string title, string studentName) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getTitle() == title &&
                books[i].isAvailable()) {
                books[i].borrowBook();
                loans.push_back(
                    Loan(studentName, title)
                );
                cout << "\nloan successfully\n";
                return;
            }
        }
        cout << "\nbook unavailable or not found\n";
    }
    void showLoans() const {
        cout << "\nloans\n";
        if (loans.empty()) {
            cout << "no active loans\n";
            return;
        }
        for (size_t i = 0; i < loans.size(); i++) {
            loans[i].displayLoan();
        }
    }
};


int main() {
    Library library;
    library.addBook(Book("Harry Potter and Goblet of Fire", "J.K. Rowling","Fantasy", "111"));
    library.addBook(Book("Sherlock Holmes","Arthur Conan Doyle","Mystery","222"));
    library.addBook(Book("The Hobbit","J.R.R. Tolkien","Fantasy","333"));
    library.addBook(Book("1984", "George Orwell","Dystopian","444"));
    library.addBook(Book("Dune","Frank Herbert", "Scienc Fiction","555"));
    library.addBook(Book("Dracula","Bram Stoker","Horror","666"));
    library.addBook(Book("Clean Code","Robert Martin","Programming","777"));
    library.addBook(Book("The Pragmatic Programmer","Andrew Hunt","Programming","888"));
    int option;
    int nextId = 1;

    do {
        cout << "\nlibrary menu\n";
        cout << "1. show books\n";
        cout << "2. register studentt\n";
        cout << "3. students\n";
        cout << "4. books\n";
        cout << "5. loans \n";
        cout << "6. search boook\n";
        cout << "0. Exit\n";
        cout << "Option: ";
        cin >> option;
        cin.ignore();
        switch(option) {
        case 1:
            library.showBooks();
            break;

        case 2: {
            string name;
            string career;
            cout << "student name: ";
            getline(cin, name);
            cout << "career: ";
            getline(cin, career);
            library.addStudent(
                Student(nextId, name, career)
            );
            nextId++;
            cout << "student registered.\n";
            break;
        }

        case 3:
            library.showStudents();
            break;

        case 4: {
            string studentName;
            string bookTitle;
            cout << "student name: ";
            getline(cin, studentName);
            cout << "book title: ";
            getline(cin, bookTitle);
            library.borrowBook(
                bookTitle,
                studentName
            );
            break;
        }

        case 5:
            library.showLoans();
            break;

        case 6: {
            string title;
            cout << "book title: ";
            getline(cin, title);
            library.searchBook(title);
            break;

        }
        case 0:
            cout << "program end\n";
            break;
        default:
            cout << "invalid option.\n";
        }
    } while(option != 0);
    return 0;
}