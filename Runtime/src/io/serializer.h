//
// Created by allos on 3/6/2025.
//
#pragma once

#include <string>
#include "stl/vector.h"
#include "core/registry.h"

namespace catos {

    enum class OutputMode {
        YAML = 0,
        BINARY = 1,
    };

    struct Object {
        std::string name;
        void* data;
    };

    class Serializer {

    public:

        Serializer();
        ~Serializer();

        void serializeInstances(const catos::vector<Object>& instances, OutputMode mode = OutputMode::YAML);


    private:
        catos::Registry& _registry;


        void writeObject(const Object& object, Registry& registry);
        void writeSubobject(const Object& object, size_t hash, Registry& registry);
        void writeProperty(Property* property, Registry& registry, const Object& object);

        void write_type_to_string(void* value, size_t hash, std::string& out);


    };

}
