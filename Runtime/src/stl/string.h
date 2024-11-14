//
// Created by allos on 8/22/2024.
//

#ifndef CATOS_STRING_H
#define CATOS_STRING_H

namespace catos {

    /// Custom string class that functions as dynamic C_str.
    class string {

    public:

        /// Initializes the internal buff to nullptr and size to 0.
        string() : buf(nullptr), size(0) {};

        /// Copies the char array to the internal buffer.
        string(const char* buffer);

        void reserve(int length);

        /// Copies string object to its internal values.
        string(const string& obj);

        /// Transfers ownerShip of buffers to this.
        string(string&& obj);

        /// Same as the string(const string& obj) constructor.
        string& operator=(const string& obj);

        /// Transfers ownership from a buffer to this.
        string& operator=(string&& obj);

        /// Adds a string to itself.
        string operator+(const string& obj);

        char operator[](int a);

        /// Returns the size of the internal buffer.
        unsigned int length() { return size; };

        /// Returns the internal buffer;
        const char* c_str() const { return buf; };



        /// Deletes the allocated char array
        ~string();

    private:
        void cleanUp();

        char* buf = nullptr;
        unsigned int size = 0;

    };



}



#endif //CATOS_STRING_H
