//
// Created by allos on 3/23/2025.
//
#include "types.h"
#include "registry.h"

void* get_type_info(size_t hash) {
    catos::Registry& registry = catos::Registry::get();

    catos::TypeInfo* info =  &registry.get_type(hash);

    return info;
}

bool is_type_registered(size_t hash) {
    return catos::Registry::get().is_type_registered(hash);
}
