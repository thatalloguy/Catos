#pragma once
#include <typeinfo>

namespace catos::type_utils {

    // -----Returns the name of the given type-----
    template<typename T>
    std::string get_type_name() {
        return std::string(typeid(T).name());
    };

    // -----Returns the hash of the given Type-----
    template<typename T>
    size_t get_type_hash() {
        return typeid(T).hash_code();
    }



}
