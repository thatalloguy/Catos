//
// Created by allos on 3/6/2025.
//

#include "serializer.h"
#include "spdlog/spdlog.h"
#include "stl/string.h"
#include "writer.h"
#include "io/backend/yamlwriter.h"

const size_t float_hash = 12638226781420530164;
const size_t int_hash = 12638232278978672507;
const size_t uint_hash = 12638231179467044040;
const size_t double_hash = 12638230079955414429;
const size_t bool_hash = 10838281452030117757;

static Writer* writer = nullptr;

Serializer::Serializer(): _registry(Registry::get()) {

}

Serializer::~Serializer() {
}



void Serializer::serializeInstances(const vector<Object> &instances, OutputMode mode) {
    delete writer;

    if (mode == OutputMode::YAML) {
        writer = new YamlWriter{};
    } else {
        writer = new YamlWriter{};
    }


    writer->begin();

    for (const auto& object : instances) {
        writeObject(object, _registry);
    }


    writer->close();

    delete writer;
}


void Serializer::write_type_to_string(void *value, size_t hash, std::string& out) {



    out += "\n";
}

void Serializer::writeObject(const Object &object, Registry &registry) {


    TypeInfo type = _registry.get_type(object.name);

    writer->beginMap(type.name.c_str());

    if (_registry.is_ref_registered(object.data)) {
        writer->writeBool("is_ptr", true);
    } else {
        writer->writeBool("is_ptr", false);
    }

    for (auto entry : type.properties) {
        writeProperty(entry.second, registry, object);
    }


    writer->endMap();
}


void Serializer::writeSubobject(const Object& object, size_t hash, Registry &registry) {


    TypeInfo type = _registry.get_type(hash);

    writer->beginMap(object.name.c_str());

    if (_registry.is_ref_registered(object.data)) {
        writer->writeBool("is_ptr", true);
    } else {
        writer->writeBool("is_ptr", false);
    }

    for (auto entry : type.properties) {
        writeProperty(entry.second, registry, object);
    }


    writer->endMap();
}


void Serializer::writeProperty(Property *property, Registry &registry, const Object &object) {

    size_t hash = property->get_type_hash();
    if (registry.is_type_registered(hash)) {
        Object sub_object = Object{
            property->get_name(),
            property->get_value(object.data)
        };

        writeSubobject(sub_object, hash, registry);


    } else if (hash == typeid(catos::string).hash_code()) {
        catos::string* value = (catos::string*) property->get_value(object.data);
        writer->writeString(property->get_name(), value->c_str());
    } else {
        switch (hash) {

            case float_hash:
                writer->writeFloat(property->get_name(), *(float*) property->get_value(object.data));
                break;

            case int_hash:
                writer->writeInt(property->get_name(), *(int*) property->get_value(object.data));
                break;

            case uint_hash:
                writer->writeInt(property->get_name(), *(unsigned int*) property->get_value(object.data));
                break;

            case bool_hash:
                writer->writeBool(property->get_name(), *(bool*) property->get_value(object.data));
                break;

            default:
                spdlog::warn("Unknown type");
                break;
        }
    }
}
