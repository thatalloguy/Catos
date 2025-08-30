//
// Created by allos on 30/08/2025.
//
#ifndef CATOS_array_H
#define CATOS_array_H


namespace catos {

    ///Simple array with utilities.
    ///But with a pre-determined size.
    ///If it reaches max capacity it will overwrite the front.
    template<typename T,unsigned int max>
    class array {
    public:
        ~array();
        
        void push(T val);

        // Clears/deletes the entire internal buffer from memory;
        void clear();

        //Resets the writing position.
        void reset();

        void jump_to(unsigned int pos);

        unsigned int size() const;
        unsigned int write_pos() const;

        T* data();
        T operator[](int index);


        /* --- Iterator stuff */

        class iterator;

        iterator begin();

        iterator begin() const;

        iterator end();

        iterator end() const;

        iterator cbegin() const;

        iterator cend() const;

        
    private:
        T* _buf{nullptr};
        unsigned int _size{0}; 
        unsigned int _write_pos{0};
    };
    

    // ----------- array Impl
    template<typename T, unsigned int max>
    array<T, max>::~array() {
        clear();
    }
    

    template<typename T, unsigned int max>
    void array<T, max>::push(T val) {
        if (_buf == nullptr) {
            _buf = new T[max];
            _size = 0;
            _write_pos = 0;
        }

        if (_write_pos == max) {
            _write_pos = 0;
        }
        
        _buf[_write_pos] = val;
        if (_size < max) {
            _size++;
        }
        _write_pos++;
    }

    template<typename T, unsigned int max>
    void array<T, max>::clear() {
        _size = 0;
        _write_pos = 0;
        delete[] _buf;
        
        _buf = nullptr;
    }

    template<typename T, unsigned int max>
    void array<T, max>::reset() {
        _write_pos = 0;
    }

    template<typename T, unsigned int max>
    void array<T, max>::jump_to(unsigned int pos) {
        _write_pos = pos;
    }

    template<typename T, unsigned int max>
    unsigned int array<T, max>::size() const {
        return _size;
    }

    template<typename T, unsigned int max>
    unsigned int array<T, max>::write_pos() const {
        return _write_pos;
    }

    template<typename T, unsigned int max>
    T * array<T, max>::data() {
        return _buf;
    }

    template<typename T, unsigned int max>
    T array<T, max>::operator[](int index) {
        return _buf[index];
    }

    //--------- iterator impl-------///
    

    template<class T, unsigned int max> class array<T, max>::iterator
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
            return _curr != b._curr;
        }

    private:
        T* _curr;





    };


    template<class T, unsigned int max>
    inline typename array<T, max>::iterator array<T, max>::begin()
    {
        return array<T, max>::iterator(&_buf[0]);
    };

    template<class T, unsigned int max>
    inline typename array<T, max>::iterator array<T, max>::begin() const {
        return array<T, max>::iterator(&_buf[0]);
    }

    template<class T, unsigned int max>
    inline typename array<T, max>::iterator array<T, max>::end()
    {
        return array<T, max>::iterator(&_buf[_size]);
    }

    template<class T, unsigned int max>
    inline typename array<T, max>::iterator array<T, max>::end() const {
        return array<T, max>::iterator(&_buf[_size]);
    }

    template<class T, unsigned int max>
    inline typename  array<T, max>::iterator array<T, max>::cbegin() const {
        return array<T, max>::iterator(&_buf[0]);
    }

    template<class T, unsigned int max>
    inline typename array<T, max>::iterator array<T, max>::cend() const {
        return array<T, max>::iterator(&_buf[_size]);
    }
    
}




#endif //CATOS_array_H
