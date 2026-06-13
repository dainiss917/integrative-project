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




