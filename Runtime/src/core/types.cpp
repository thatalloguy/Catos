//
// Created by allos on 3/23/2025.
//
#include "types.h"
#include "registry.h"

void* get_type_info(size_t hash) {
    catos::Registry& registry = catos::Registry::get();

    TypeInfo* info =  &registry.get_type(hash);

    return info;
}

bool is_type_registered(size_t hash) {
    return catos::Registry::get().is_type_registered(hash);
}

void type_instance_to_string(void *type_info, void* instance, std::string&  out) {
    TypeInfo* info = (TypeInfo*) type_info;

    info->to_string(instance, out);
}

