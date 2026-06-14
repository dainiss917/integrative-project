#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <exception>
using namespace std;

class LibraryException : public exception {
private:
    string message;
public:
    LibraryException(const string& msg)
        : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Rating {
private:
    int value; // 1 to 5
public:
    explicit Rating(int v) : value(v) {
        if (v < 1 || v > 5) {
            throw LibraryException("rating must be between 1 and 5.");
        }
    }
    int getValue() const noexcept {
        return value;
    }
    bool operator==(const Rating& other) const noexcept {
        return value == other.value;
    }
    bool operator<(const Rating& other) const noexcept {
        return value < other.value;
    }
    friend ostream& operator<<(ostream& os, const Rating& r) {
        os << r.value << "/5";
        return os;
    }
};

class Person {
protected:
    int id;
    string name;
public:
    Person(int i, const string& n)
        : id(i), name(n) {
        cout << "Person created: " << name << "\n";
    }
    virtual void displayInfo() const = 0;
    string getName() const noexcept {
        return name;
    }
    int getId() const noexcept {
        return id;
    }
    virtual ~Person() noexcept {
        cout << "person destroyed: " << name << "\n";
    }
};

class Student : public Person {
private:
    string career;
public:
    Student(int i, const string& n, const string& c)
        : Person(i, n), career(c) {
        cout << "student created: " << name << "\n";
    }
    void displayInfo() const override {
        cout << "  ID:     " << id << "\n";
        cout << "  name:   " << name << "\n";
        cout << "  career: " << career << "\n";
    }
    ~Student() noexcept override {
        cout << "student destroyed: " << name << "\n";
    }
};

class Professor : public Person {
private:
    string department;
public:
    Professor(int i, const string& n, const string& d)
        : Person(i, n), department(d) {
        cout << "professor created: " << name << "\n";
    }
    void displayInfo() const override {
        cout << "  ID:         " << id << "\n";
        cout << "  name:       " << name << "\n";
        cout << "  department: " << department << "\n";
    }
    ~Professor() noexcept override {
        cout << "professor destroyed: " << name << "\n";
    }
};

class Book {
private:
    string title;
    string author;
    string genre;
    string INB;
    bool available;
    Rating rating;
public:
    Book(const string& t,const string& a,const string& g,const string& i,int r = 3)
        : title(t),author(a),genre(g),INB(i),available(true),rating(r) {}
    string getTitle() const noexcept {
        return title;
    }
    string getINB() const noexcept {
        return INB;
    }
    bool isAvailable() const noexcept {
        return available;
    }
    const Rating& getRating() const noexcept {
        return rating;
    }
    void borrowBook() {
        if (!available) {
            throw LibraryException("this book is already borrowed.");
        }
        available = false;
    }
    void returnBook() noexcept {
        available = true;
    }
    bool operator==(const Book& other) const noexcept {
        return INB == other.INB;
    }
    bool operator<(const Book& other) const noexcept {
        return rating < other.rating;
    }
    friend ostream& operator<<(ostream& os, const Book& b) {
        os << "Title:  " << b.title  << "\n";
        os << "Author: " << b.author << "\n";
        os << "Genre:  " << b.genre  << "\n";
        os << "ISBN:   " << b.INB  << "\n";
        os << "Rating: " << b.rating << "\n";
        os << "Status: "
           << (b.available ? "Available" : "Borrowed")
           << "\n";
        return os;
    }
};

class Loan {
private:
    string personName;
    string bookTitle;
public:
    Loan(const string& p, const string& b)
        : personName(p),
          bookTitle(b) {}
    void displayLoan() const {
        cout << "  " << personName
             << " borrowed \""
             << bookTitle
             << "\"\n";
    }
};

class Catalog {
private:
    string description;
public:
    explicit Catalog(const string& desc)
        : description(desc) {}
    void displayInfo() const {
        cout << "  Description: " << description << "\n";
    }
    ~Catalog() noexcept {
        cout << "catalog destroyed\n";
    }
};

class Library {
private:
    vector<Book>                  books;
    vector<Loan>                  loans;
    vector<unique_ptr<Person>>    people;
    const Catalog* catalog;
public:
    explicit Library(const Catalog* cat)
        : catalog(cat) {}
    void addBook(const Book& book) {
        books.push_back(book);
    }
    void showBooks() const {
        cout << "\nBOOKS\n";
        for (size_t i = 0; i < books.size(); i++) {
            cout << books[i] << "\n";
        }
    }
    void searchBook(const string& title) const {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getTitle() == title) {
                cout << "\nbook found:\n";
                cout << books[i] << "\n";
                return;
            }
        }
        throw LibraryException("book not found: " + title);
    }
    void borrowBook(const string& title,
                    const string& personName) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getTitle() == title) {
                books[i].borrowBook(); 
                loans.push_back(Loan(personName, title));
                cout << "\nsuccessfully loan.\n";
                return;
            }
        }
        throw LibraryException("book not found: " + title);
    }
    void returnBook(const string& title) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getTitle() == title) {
                books[i].returnBook();
                cout << "\nsuccessfully return.\n";
                return;
            }
        }
        throw LibraryException("book not found: " + title);
    }
    void addPerson(unique_ptr<Person> person) {
        people.push_back(move(person));
    }
    void showPeople() const {
        cout << "\nPEOPLE\n";
        if (people.empty()) {
            cout << "no registered people.\n";
            return;
        }
        for (size_t i = 0; i < people.size(); i++) {
            people[i]->displayInfo();
            cout << "\n";
        }
    }
    void showLoans() const {
        cout << "\nLOANS\n";
        if (loans.empty()) {
            cout << "no active loans.\n";
            return;
        }
        for (size_t i = 0; i < loans.size(); i++) {
            loans[i].displayLoan();
        }
    }
    void showCatalogInfo() const {
        if (catalog == nullptr) {
            cout << "no catalog linked.\n";
            return;
        }
        cout << "\nCATALOG\n";
        catalog->displayInfo();
    }
    void compareBooks(const string& titleA,
                      const string& titleB) const {
        const Book* a = nullptr;
        const Book* b = nullptr;
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getTitle() == titleA) a = &books[i];
            if (books[i].getTitle() == titleB) b = &books[i];
        }
        if (a == nullptr || b == nullptr) {
            throw LibraryException("One or both books not found.");
        }
        cout << "\nBOOK COMPARISON\n";
        cout << "\"" << titleA << "\" rating: " << a->getRating() << "\n";
        cout << "\"" << titleB << "\" rating: " << b->getRating() << "\n";
        if (*a == *b) {
            cout << "obth of them have the same ISBN.\n";
        } else if (*a < *b) {
            cout << "\"" << titleA << "\" is rated lower than \""
                 << titleB << "\".\n";
        } else {
            cout << "\"" << titleA << "\" is rated higher than \""
                 << titleB << "\".\n";
        }
    }
};

