//
// Created by allos on 3/6/2025.
//

#include "serializer.h"
#include "spdlog/spdlog.h"
#include "handlers.h"

const size_t float_hash = 12638226781420530164;
const size_t int_hash = 12638232278978672507;
const size_t uint_hash = 12638231179467044040;
const size_t double_hash = 12638230079955414429;
const size_t string_hash = 1292088526669925081;

Serializer::Serializer(): _registry(Registry::get()) {
    registerHandler("vector", catos::handlers::saveVectorToFile);
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
            //out += " ";
            write_property_to_string(properties.second, registry, instance_object, out);
        }

        // Write that object info to the file.
    } else {

        switch (property->get_type_hash()) {

            case float_hash:
                out += std::to_string(*static_cast<float*>(property->get_value(object.data)));
                break;

            case int_hash:
                out += std::to_string(*static_cast<int*>(property->get_value(object.data)));
                break;

            case uint_hash:
                out += std::to_string(*static_cast<unsigned int*>(property->get_value(object.data)));
                break;

            case double_hash:
                out += std::to_string(*static_cast<double*>(property->get_value(object.data)));
                break;

            case string_hash:
                out += R"(")";
                out += static_cast<catos::string*>(property->get_value(object.data))->c_str();
                out += R"(")";
                break;

            default:
                check_handlers(property, out);
                break;
        }


        out += "\n";
    }



}

void Serializer::registerHandler(const std::string &type_name, void (*handler)(Property *, std::string &)) {
    _handlers.insert({type_name, handler});
}

void Serializer::check_handlers(Property *property, std::string &out) {


    std::string prop_name = property->get_type_name();

    for (auto handler : _handlers) {
        if (prop_name.find(handler.first) != std::string::npos) {
            handler.second(property, out);
            return;
        }
    }

}
