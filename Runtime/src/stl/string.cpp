//
// Created by allos on 8/22/2024.
//

#include <cstring>
#include "string.h"

Catos::string::~string() {

    cleanUp();

}

Catos::string::string(const char *buffer) {
    size = strlen(buffer);
    buf = new char[size + 1];
    strncpy_s(buf, size + 1, buffer, size);

}

Catos::string::string(const Catos::string &obj) {
    size = obj.size;
    buf = new char[size + 1];
    strncpy_s(buf, size + 1, obj.buf, size);
}

Catos::string &Catos::string::operator=(const Catos::string &obj) {
    size = obj.size;
    buf = new char[size + 1];
    strncpy_s(buf, size + 1, obj.buf, size);
    return *this;
}

Catos::string::string(Catos::string &&obj) {
    //First clean up to get rid of previous allocated memory.
    cleanUp();

    size = obj.size;

    buf = obj.buf;

    //set to null, because we now handle to buffer.
    obj.buf = nullptr;
}

void Catos::string::cleanUp() {
    if (buf != nullptr) {
        delete[] buf;
    }
}

Catos::string &Catos::string::operator=(Catos::string &&obj) {
    //First clean up to get rid of previous allocated memory.
    cleanUp();

    size = obj.size;

    buf = obj.buf;

    //set to null, because we now handle to buffer.
    obj.buf = nullptr;

    return *this;
}

Catos::string Catos::string::operator+(const Catos::string &obj) {
    string s; // new string.

    s.size = this->size + obj.size;
    s.buf = new char[s.size + 1];
    strncpy_s(s.buf, this->size + 1, this->buf, this->size); // first copy our str
    strncpy_s(s.buf + this->size, obj.size + 1, obj.buf, obj.size); // Then the other obj.

    return s;
}


