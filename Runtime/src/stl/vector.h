//
// Created by allos on 8/22/2024.
//

#ifndef CATOS_VECTOR_H
#define CATOS_VECTOR_H

#include <cstring>

struct out_of_range {

};

namespace Catos {


    template<typename T>
    class vector {

    public:

        /// Initializes the vector to empty.
        vector(): buf(nullptr), size(0) {};

        /// Copy Constructor
        vector(const vector& obj) {
            //Allocate enough mem then copy the item values
            if (maxSize >= obj.size)
                reserve(obj.size);


            for (int i=0; i<obj.size; i++)
                buf[i] = obj.buf[i];
        }

        /// Move Constructor
        vector(vector&& obj) {
            buf = obj.buf;
            size = obj.size;
            maxSize = obj.size;

        }

        /// Copies the obj.
        vector<T>& operator=(const vector<T>& obj) {
            if (this == obj) return *this; // no self asignment.

            if (maxSize >= obj.size)
                reserve(obj.size);


            for (int i=0; i<obj.size; i++)
                buf[i] = obj.buf[i];

            return *this;
        }


        /// allocates enough memory for the amount given.
        void reserve(unsigned int amount) {

            // no need if its the smaller or same size.
            if (amount <= maxSize) return;


            //allocate a new buffer with the desired size.
            T* temp = new T[amount];

            // copy our current items to that array.
            for (int i=0; i < size; i++)
                temp[i] = buf[i];


            //destroy our previous allocated memory;
            delete[] buf;

            // Now our buffer should point to the newly allocated memory.
            buf = temp;
            maxSize = amount;
        }

        void resize(unsigned int newSize) {

            // no need if its the smaller or same size.
            if (newSize == maxSize) return;

            if (newSize > size) throw out_of_range();


            //allocate a new buffer with the desired size.
            T* temp = new T[newSize];

            // copy our current items to that array.
            for (int i=0; i < newSize; i++)
                temp[i] = buf[i];


            //destroy our previous allocated memory;
            delete[] buf;

            // Now our buffer should point to the newly allocated memory.
            buf = temp;
            maxSize = newSize;
        }

        /// Adds the new item to the array.
        void push_back(T obj) {

            if (size >= maxSize) {
                // do 8 so that we dont have to allocate every push_back.
                reserve(maxSize + 8);
            }

            //add the object to the internal array
            buf[size] = obj;

            //increase the size;
            size++;

        }

        /// clears the buffer
        void clear() {


            if (buf != nullptr) {
                delete[] buf;
            }

            maxSize = 0;
            size = 0;

        };

        /// removes the item at the index
        void remove(int index) {

            for (int i = index; i < size - 1; i++) {
                buf[i] = buf[i + 1];
            }

            size--;
        };

        /// returns the item at the desired index.
        T& at(int index) {
            return buf[index];
        }



        /// gives the internal buffer
        T* data() { return buf; };

        /// returns the amount of objects in the internal buffer.
        unsigned int length() {
            return size;
        }

        /// returns the maximum amount of objects in our internal buffer
        unsigned int maxLength() {
            return maxSize;
        }

        T& operator[](int i) {
           return buf[i];
        }



        /// Deletes the allocated objects.
        ~vector() {

            if (buf != nullptr) {
                delete[] buf;
            }

        };


        /* --- Iterator stuff */

        class iterator;

        iterator begin();

        iterator begin() const;

        iterator end();

        iterator end() const;

        iterator cbegin() const;

        iterator cend() const;




    private:


        T* buf = nullptr;
        // The actual amount of items in the buffer
        unsigned int size = 0;
        // The max amount of items in the buffer.
        unsigned int maxSize = 0;
    };



    template<class T> class vector<T>::iterator
    {
    public:
        iterator(T* p)
                :_curr(p)
        {}

        iterator& operator++()
        {
            _curr++;
            return *this;
        }

        iterator& operator--()
        {
            _curr--;
            return *this;
        }

        T& operator*()
        {
            return *_curr;
        }

        bool operator==(const iterator& b) const
        {
            return *_curr == *b._curr;
        }

        bool operator!=(const iterator& b) const
        {
            return *_curr != *b._curr;
        }

    private:
        T* _curr;





    };


    template<class T>
    inline typename vector<T>::iterator vector<T>::begin()
    {
        return vector<T>::iterator(&buf[0]);
    };

    template<class T>
    inline typename vector<T>::iterator vector<T>::begin() const {
        return vector<T>::iterator(&buf[0]);
    }

    template<class T>
    inline typename vector<T>::iterator vector<T>::end()
    {
        return vector<T>::iterator(&buf[size]);
    }

    template<class T>
    inline typename vector<T>::iterator vector<T>::end() const {
        return vector<T>::iterator(&buf[size]);
    }

    template<class T>
    inline typename  vector<T>::iterator vector<T>::cbegin() const {
        return vector<T>::iterator(&buf[0]);
    }

    template<class T>
    inline typename vector<T>::iterator vector<T>::cend() const {
        return vector<T>::iterator(&buf[size]);
    }



}




#endif //CATOS_VECTOR_H
