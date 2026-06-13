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


