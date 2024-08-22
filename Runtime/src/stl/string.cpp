//
// Created by allos on 8/22/2024.
//

#include <cstring>
#include "string.h"

STL::String::~String() {

    cleanUp();

}

STL::String::String(const char *buffer) {
    size = strlen(buffer);
    buf = new char[size + 1];
    strncpy_s(buf, size + 1, buffer, size);

}

STL::String::String(const STL::String &obj) {
    size = obj.size;
    buf = new char[size + 1];
    strncpy_s(buf, size + 1, obj.buf, size);
}

STL::String &STL::String::operator=(const STL::String &obj) {
    size = obj.size;
    buf = new char[size + 1];
    strncpy_s(buf, size + 1, obj.buf, size);
    return *this;
}

STL::String::String(STL::String &&obj) {
    //First clean up to get rid of previous allocated memory.
    cleanUp();

    size = obj.size;

    buf = obj.buf;

    //set to null, because we now handle to buffer.
    obj.buf = nullptr;
}

void STL::String::cleanUp() {
    if (buf != nullptr) {
        delete[] buf;
    }
}

STL::String &STL::String::operator=(STL::String &&obj) {
    //First clean up to get rid of previous allocated memory.
    cleanUp();

    size = obj.size;

    buf = obj.buf;

    //set to null, because we now handle to buffer.
    obj.buf = nullptr;

    return *this;
}

STL::String STL::String::operator+(const STL::String &obj) {
    String s; // new string.

    s.size = this->size + obj.size;
    s.buf = new char[s.size + 1];
    strncpy_s(s.buf, this->size + 1, this->buf, this->size); // first copy our str
    strncpy_s(s.buf + this->size, obj.size + 1, obj.buf, obj.size); // Then the other obj.

    return s;
}


