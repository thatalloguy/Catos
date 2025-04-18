//
// Created by allos on 8/22/2024.
//

#include <stl/string.h>

#include <string>

catos::string::~string() {

    cleanUp();

}

catos::string::string(int new_size) {
    size = new_size;
    buf = new char[size];
}

catos::string::string(const char *buffer) {
    size = strlen(buffer);
    buf = new char[size + 1];
    std::strncpy(buf, buffer, size + 1);

}

catos::string::string(const catos::string &obj) {
    size = obj.size;
    buf = new char[size + 1];
    std::strncpy(buf, obj.buf, size + 1);
}


catos::string &catos::string::operator=(const catos::string &obj) {
    size = obj.size;
    buf = new char[size + 1];
    std::strncpy(buf, obj.buf, size + 1);
    return *this;
}

catos::string::string(catos::string &&obj) {
    //First clean up to get rid of previous allocated memory.
    cleanUp();

    size = obj.size;

    buf = obj.buf;

    //set to null, because we now handle to buffer.
    obj.buf = nullptr;
}

void catos::string::cleanUp() {
    if (buf != nullptr) {
        delete[] buf;
    }
}

catos::string &catos::string::operator=(catos::string &&obj) {
    //First clean up to get rid of previous allocated memory.
    cleanUp();

    size = obj.size;

    buf = obj.buf;

    //set to null, because we now handle to buffer.
    obj.buf = nullptr;

    return *this;
}

catos::string catos::string::operator+(const catos::string &obj) {
    string s; // new string.

    s.size = this->size + obj.size;
    s.buf = new char[s.size + 1];
    std::strncpy(s.buf, this->buf, this->size + 1); // first copy our str
    std::strncpy(s.buf + this->size, obj.buf, obj.size + 1); // Then the other obj.

    return s;
}



bool catos::string::operator==(const string& obj) const {
    const char* a = obj.c_str();
    const char* b = buf;
    bool result = strcmp(a, b);

    return !result;
}

bool catos::string::operator!=(const string& obj) const {
    const char* a = obj.c_str();
    const char* b = buf;
    bool result = strcmp(a, b);

    return result;
}

void catos::string::operator+=(const catos::string &obj) {
    char* t_buf = new char[size + obj.size + 1];
    std::strncpy(t_buf, this->buf, this->size + 1); // first copy our str
    std::strncpy(t_buf + this->size, obj.buf, obj.size + 1); // Then the other obj.


    delete[] buf;
    this->size += obj.size;

    buf = t_buf;
}
