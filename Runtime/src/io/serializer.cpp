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

    writer->beginMap(object.name);

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

    if (property->get_type() == PropertyType::VECTOR) {

        writer->beginArray(property->get_name());

        catos::raw_vector* vec = (catos::raw_vector*) property->get_value(object.data);

        int i = 0;
        for (void* ptr: *vec) {

            auto name = std::to_string(i);

            if (_registry.is_type_registered(vec->hash_of_type())) {
                writeSubobject({name.c_str(), ptr}, vec->hash_of_type(), registry);
            } else {
                writeValue(name.c_str(), ptr, vec->hash_of_type());
            }

            i++;
        }

        writer->endArray();


    } else if (registry.is_type_registered(hash)) {
        Object sub_object = Object{
            property->get_name(),
            property->get_value(object.data)
        };

        writeSubobject(sub_object, hash, registry);


    } else if (hash == typeid(catos::string).hash_code()) {
            catos::string* value = (catos::string*) property->get_value(object.data);
            writer->writeString(property->get_name(), value->c_str());
    } else {
        writeValue(property->get_name(), property->get_value(object.data), property->get_type_hash());
    }
}

void Serializer::writeValue(const char *name, void *value, size_t hash) {
    switch (hash) {

        case float_hash:
            writer->writeFloat(name, *(float*)value);
            break;

        case int_hash:
            writer->writeInt(name, *(int*) value);
            break;

        case uint_hash:
            writer->writeInt(name, *(unsigned int*) value);
            break;

        case bool_hash:
            writer->writeBool(name, *(bool*) value);
            break;

        default:
            spdlog::warn("Unknown type");
            break;
    }
}
