//
// Created by allos on 4/8/2025.
//

#ifndef CATOS_RAWVECTOR_H
#define CATOS_RAWVECTOR_H

#include "vector.h"

namespace catos {


    class raw_vector {
    public:

        template<typename T>
        raw_vector(vector<T>* vector) {
            buf = (unsigned char*) vector->data();
            size = vector->length();
            type_hash = typeid(T).hash_code();
            type_size = sizeof(T);
        };

        int length() const {
            return size;
        };

        size_t hash_of_type() const {
            return type_hash;
        }

        unsigned char* data() const {
            return buf;
        }

        void* operator[](int index) {
            return &buf[index * type_size];
        }

        raw_vector() = default;

        /* --- Iterator stuff */


        class iterator;

        iterator begin();

        iterator begin() const;

        iterator end();

        iterator end() const;

        iterator cbegin() const;

        iterator cend() const;



    private:
        unsigned char* buf = nullptr;
        size_t type_hash = 0;
        int size = 0;
        int type_size = 0;

    };

    class raw_vector::iterator
    {
    public:
        iterator(unsigned char* buf, int cur, int type_size)
                : _buf(buf), _cur(cur), _type_size(type_size)
        {}

        iterator& operator++()
        {
            _cur++;
            return *this;
        }

        iterator& operator--()
        {
            _cur--;
            return *this;
        }

        void* operator*()
        {
            return &_buf[_cur * _type_size];
        }

        bool operator==(const iterator& b) const
        {
            return &_buf[_cur * _type_size] == &b._buf[b._cur * _type_size];
        }

        bool operator!=(const iterator& b) const
        {
            return &_buf[_cur * _type_size] != &b._buf[b._cur * _type_size];
        }

    private:
        unsigned char* _buf;
        int _cur;
        int _type_size;





    };


    inline raw_vector::iterator raw_vector::begin()
    {
        return {buf, 0, type_size};
    };

    inline  raw_vector::iterator raw_vector::begin() const {
        return {buf, 0, type_size};
    }


    inline raw_vector::iterator raw_vector::end()
    {
        return {buf, size, type_size};
    }

    inline raw_vector::iterator raw_vector::end() const {
        return {buf, size, type_size};
    }

    inline raw_vector::iterator raw_vector::cbegin() const {
        return {buf, 0, type_size};
    }

    inline  raw_vector::iterator raw_vector::cend() const {
        return {buf, size, type_size};
    }

}

#endif //CATOS_RAWVECTOR_H
