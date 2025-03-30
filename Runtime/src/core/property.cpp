//
// Created by allos on 3/19/2025.
//

#include "property.h"
#include "registry.h"

unsigned long catos::_property_utils::get_ref(void *ptr) {

    catos::Registry& registry = catos::Registry::get();

    return registry.get_ref(ptr);
}
