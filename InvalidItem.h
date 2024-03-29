#pragma once
#include <exception>

class InvalidItem : public std::exception {
private:
    char * message;

public:
    InvalidItem(char * msg) : message(msg) {}
    char * what () {
        return message;
    }
};

