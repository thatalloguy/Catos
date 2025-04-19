//
// Created by allos on 4/18/2025.
//
#pragma once

#include <typeinfo>

namespace catos {

    class Variant {
    public:

        template <typename T>
        Variant(T&& val) {
            ptr = val;
            size_of_type = sizeof(T);
            hash_of_type = std::type_info(val).hash_code();
        };

        template<typename T>
        T&& get_value() {
            return (T&&) ptr;
        }

    private:
        void* ptr = nullptr;
        size_t size_of_type = 0;
        size_t hash_of_type = 0;
    };


}