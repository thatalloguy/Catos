//
// Created by allos on 8/22/2024.
//

#ifndef CATOS_STRING_H
#define CATOS_STRING_H

namespace STL {

    // Custom string class that functions as dynamic C_str.
    class String {

    public:

        // Initializes the internal buff to nullptr and size to 0.
        String() : buf(nullptr), size(0) {};

        //Copies the char array to the internal buffer.
        String(const char* buffer);

        // Copies string object to its internal values.
        String(const String& obj);

        // Transfers ownerShip of buffers to this.
        String(String&& obj);

        // Same as the String(const String& obj) constructor.
        String& operator=(const String& obj);

        // Transfers ownership from a buffer to this.
        String& operator=(String&& obj);

        //Adds a string to itself.
        String operator+(const String& obj);

        // Returns the size of the internal buffer.
        unsigned int length() { return size; };

        // Returns the internal buffer;
        const char* c_str() const { return buf; };


        // Deletes the allocated char array
        ~String();

    private:
        void cleanUp();

        char* buf = nullptr;
        unsigned int size = 0;

    };



}



#endif //CATOS_STRING_H
