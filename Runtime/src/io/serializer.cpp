//
// Created by allos on 3/6/2025.
//

#include "serializer.h"


#include <spdlog/spdlog.h>
#include <stl/string.h>

#include <io/writer.h>
#include <io/reader.h>
//
#include <io/backend/yamlReader.h>
#include <io/backend/yamlwriter.h>

const size_t float_hash = 12638226781420530164;
const size_t int_hash = 12638232278978672507;
const size_t uint_hash = 12638231179467044040;
const size_t double_hash = 12638230079955414429;
const size_t bool_hash = 10838281452030117757;

static catos::Writer* writer = nullptr;
static catos::Reader* reader = nullptr;

static std::string getContents(const catos::string& path) {

    std::ifstream f("../../../test.yaml");

    if (!f.is_open()) {
        std::cerr << "Error opening the file!";
    }

    std::string temp;
    std::string final;

    while (std::getline(f, temp)) {
        final += temp.c_str();
        final += "\n";
    }


    // Close the file
    f.close();

    return final;
}

catos::Serializer::Serializer(): _registry(Registry::get()) {

}

catos::Serializer::~Serializer() {
}



void catos::Serializer::serializeInstances(const catos::vector<Object> &instances, Mode mode) {
    delete writer;

    if (mode == Mode::YAML) {
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

void catos::Serializer::writeObject(const Object &object, Registry &registry) {


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


void catos::Serializer::writeSubobject(const Object& object, size_t hash, Registry &registry) {


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


void catos::Serializer::writeProperty(Property *property, Registry &registry, const Object &object) {

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

void catos::Serializer::writeValue(const char *name, void *value, size_t hash) {
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

void catos::Serializer::deserializeInstances(const catos::string &file_path, Mode mode, catos::vector<Instance*>& instances) {
    delete reader;

    reader = new YamlReader{};


    if (!reader->open(getContents(file_path))) {
        spdlog::error("Could not deserialize file: {}", file_path.c_str());
        delete reader;
        reader = nullptr;
        return;
    }

    while (true) {
        SerializedType type = reader->getNextEntryType();

        if (type != SerializedType::MAP) {
            spdlog::warn("Excepted map");
            // If we dont get objects we stop >:(
            break;
        }

        if (!reader->nextArrrayElement()) {
            break;
        }


        bool is_ptr = reader->readBool("is_ptr");
        const catos::string& name = reader->getCurrentKey();
        const TypeInfo* type_info = nullptr;

        if (_registry.is_type_registered(name.c_str())) {
            type_info = &_registry.get_type(name.c_str());
        }

        if (!type_info) {
            spdlog::error("Failed to find type in the registry: {}", name.c_str());
            reader->endMap();
            continue;
        } else {
            spdlog::info("Found: {}", name.c_str());
        }


        Instance* instance = type_info->_constructor.construct();

        if (!instance) {
            spdlog::error("Could not create instance: {}", name.c_str());
            reader->endMap();
            return;
        }

        for (auto pair: type_info->properties) {
            Property* property = pair.second;
            auto property_name = property->get_name();
            size_t property_hash = property->get_type_hash();

            if (property->get_type() == PropertyType::VECTOR) {
                //todo
                spdlog::warn("Vector property not yet supported");
            } else {
                //Basics
                if (property_hash == float_hash) {
                    property->set_value(instance->data(), reader->readFloat(property_name));
                } else if (property_hash == int_hash) {
                    property->set_value(instance->data(), reader->readInt(property_name));
                } else if (property_hash == uint_hash) {
                    property->set_value(instance->data(), reader->readInt(property_name));
                } else if (property_hash == bool_hash) {
                    property->set_value(instance->data(), reader->readBool(property_name));
                }

            }
        }

        instances.push_back(instance);

        reader->endMap();
    }

    delete reader;
    reader = nullptr;
}
