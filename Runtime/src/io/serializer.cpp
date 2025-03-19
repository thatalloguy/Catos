//
// Created by allos on 3/6/2025.
//

#include "serializer.h"
#include "spdlog/spdlog.h"
#include "stl/string.h"

const size_t float_hash = 12638226781420530164;
const size_t int_hash = 12638232278978672507;
const size_t uint_hash = 12638231179467044040;
const size_t double_hash = 12638230079955414429;
const size_t string_hash = 1292088526669925081;

Serializer::Serializer(): _registry(Registry::get()) {
}

Serializer::~Serializer() {}

void Serializer::serializeInstances(const vector<Object> &instances, std::string& out) {

    for (auto object: instances) {

        TypeInfo type = _registry.get_type(object.name);

        out += "- class: ";
        out += type.name;
        out += "\n";

        for (auto property_entry : type.properties) {

            auto property = property_entry.second;

            write_property_to_string(property, _registry, object, out);

        }

    }

}


void catos::Serializer::write_property_to_string(Property* property, Registry& registry, Object& object, std::string& out) {

    out += "  ";
    out += property->get_name();
    out += ": ";

    if (registry.is_type_registered(property->get_type_hash())) {
        auto& instance_property = registry.get_type(property->get_type_hash());

        out += "instance: ";
        out += instance_property.name + "\n";

        Object instance_object{
                .name = instance_property.name,
                .data = property->get_value(object.data)
        };

        for (auto properties: instance_property.properties) {
            write_property_to_string(properties.second, registry, instance_object, out);
        }

        // Write that object info to the file.
    } else {
        property->to_string(object.data, out);
        out += "\n";
    }



}

void Serializer::write_type_to_string(void *value, size_t hash, std::string& out) {

    switch (hash) {

        case float_hash:
            out += std::to_string(*static_cast<float*>(value));
            break;

        case int_hash:
            out += std::to_string(*static_cast<int*>(value));
            break;

        case uint_hash:
            out += std::to_string(*static_cast<unsigned int*>(value));
            break;

        case double_hash:
            out += std::to_string(*static_cast<double*>(value));
            break;

        case string_hash:
            out += R"(")";
            out += static_cast<catos::string*>(value)->c_str();
            out += R"(")";
            break;

        default:
            spdlog::warn("Unknown type");
            break;
    }
}
