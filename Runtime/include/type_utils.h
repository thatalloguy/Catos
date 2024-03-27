#pragma once
#include <typeinfo>

namespace catos::TypeUtils {

    // -----Returns the name of the given type-----
    template<typename T>
    const char* getTypeName() {
        return typeid(T).name();
    };


}