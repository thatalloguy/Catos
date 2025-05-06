//
// Created by allos on 3/6/2025.
//
#pragma once

#include <string>
#include "stl/vector.h"
#include "core/registry.h"
#include "stl/string.h"

namespace catos {

    enum class Mode {
        YAML = 0,
        BINARY = 1,
    };

    struct Object {
        const char* name;
        void* data;
    };

    class Serializer {

    public:

        Serializer();
        ~Serializer();

        void serializeInstances(const catos::vector<Object>& instances, Mode mode = Mode::YAML);
        void deserializeInstances(const catos::string& file_path, Mode mode, catos::vector<Instance*>& instances);

    private:
        catos::Registry& _registry;


        void writeObject(const Object& object, Registry& registry);
        void writeSubobject(const Object& object, size_t hash, Registry& registry);
        void writeProperty(Property* property, Registry& registry, const Object& object);

        void readProperty(Property* property, void* instance);
        void readVectorProperty(Property* property, void* instance);
        catos::Instance* readInstance(const TypeInfo* info, const catos::string& name);
        void* readSubMap(Property* property, void* parent);


        void writeValue(const char* name, void* value, size_t hash);

    };

}
