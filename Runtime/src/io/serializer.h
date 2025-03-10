//
// Created by allos on 3/6/2025.
//
#pragma once

#include <string>
#include "stl/vector.h"
#include "core/registry.h"

namespace catos {


    struct Object {
        std::string name;
        void* data;
    };

    class Serializer {

    public:

        Serializer();
        ~Serializer();

        void serializeInstances(const catos::vector<Object>& instances,  std::string& out);

        void registerHandler(const std::string& type_name, void(handler)(Property*,std::string&));

    private:
        catos::Registry& _registry;


        void write_property_to_string(Property* property, Registry& registry, Object& object, std::string& out);
        void check_handlers(Property* property, std::string& out);

        std::unordered_map<std::string, void(*)(Property*, std::string&)> _handlers;

    };

}
