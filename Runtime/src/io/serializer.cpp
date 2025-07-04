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



void catos::Serializer::serializeInstances(const string& file_path, const catos::vector<Object> &instances, Mode mode) {
    delete writer;

    if (mode == Mode::YAML) {
        writer = new YamlWriter{};
    } else {
        writer = new YamlWriter{};
    }

    writer->open(file_path);
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
    
    if (hash == float_hash) {
            writer->writeFloat(name, *(float*)value);
    } else if (int_hash == hash) {
            writer->writeInt(name, *(int*) value);
    } else if (hash == uint_hash) {
            writer->writeInt(name, *(unsigned int*) value);
    } else if (hash == bool_hash) {
            writer->writeBool(name, *(bool*) value);
    } else if (hash == typeid(catos::string).hash_code()) {
            writer->writeString(name, ((catos::string*) value)->c_str());
    } else {
        spdlog::warn("Could not write: {}", name);
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

    bool quit = false;
    while (true) {
        SerializedType type = reader->getNextEntryType();

        if (type == SerializedType::INVALID) {
            spdlog::warn("Stopping reading because: SerializedType is INVALID");
            //break;
        }

        if (!reader->nextArrrayElement()) {
            spdlog::warn("Stopping reading because: No extra element");
            break;
        }

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
            spdlog::info("Beginnig map {}", name.c_str());
            reader->beginMap(name.c_str());
        }

        auto instance = readInstance(type_info, name);

        if (instance) {
            instances.push_back(instance);
        } else {
            spdlog::warn("Instance was nullptr");
        }


        reader->endMap();
    }

    delete reader;
    reader = nullptr;

    spdlog::info("Finish reading: size {} ", instances.length());
}

void catos::Serializer::readProperty(catos::Property *property, void* instance) {
    auto property_name = property->get_name();
    size_t property_hash = property->get_type_hash();

    if (_registry.is_type_registered(property_hash) && property->get_type() != PropertyType::VECTOR) {

        reader->beginMap(property_name);

        readSubMap(property, instance);

        reader->endMap();
    } else if (property->get_type() == PropertyType::VECTOR) {

        reader->beginArray(property_name);

        readVectorProperty(property, instance);

        reader->endArray();

    } else {
        //Basics
        if (property_hash == float_hash) {
            property->set_value(instance, reader->readFloat(property_name));
        } else if (property_hash == int_hash) {

            property->set_value(instance, reader->readInt(property_name));
        } else if (property_hash == uint_hash) {
            property->set_value(instance, reader->readInt(property_name));
        } else if (property_hash == bool_hash) {
            property->set_value(instance, reader->readBool(property_name));
        } else {
            property->set_value(instance, reader->readString(property_name));
        }

    }
}


void catos::Serializer::readVectorProperty(catos::Property *property, void* instance) {

    auto* vec_property = (catos::VectorProperty*) property;
    auto property_hash = vec_property->get_type_hash();

    auto t = reader->getNextEntryType();

    while (t != SerializedType::INVALID) {
        if (!reader->nextArrrayElement()) {
            break;
        }



        if (_registry.is_type_registered(property_hash)) {

            reader->beginMap();
            vec_property->push_back_ptr(
                    instance,
                    readSubMap(property, instance)
            );
            reader->endMap();

        } else {
            //Basics
            if (property_hash == float_hash) {
                vec_property->push_back_value(
                        instance,
                        reader->readFloat()
                );
            } else if (property_hash == int_hash) {
                vec_property->push_back_value(
                        instance,
                        reader->readInt()
                );
            } else if (property_hash == uint_hash) {
                vec_property->push_back_value(
                        instance,
                        reader->readInt()
                );
            } else if (property_hash == bool_hash) {
                vec_property->push_back_value(
                        instance,
                        reader->readBool()
                );
            } else if (property_hash == typeid(catos::string).hash_code()) {
                vec_property->push_back_value(
                        instance,
                        reader->readString()
                );
            } else {
                spdlog::warn("Could not read: {} | {}", property->get_name(), static_cast<unsigned int>(t));
            }

        }
        t = reader->getNextEntryType();
    }

}

catos::Instance* catos::Serializer::readInstance(const catos::TypeInfo* info, const catos::string& name) {


    Instance* instance = info->_constructor.construct();

    if (!instance) {
        spdlog::error("Could not create instance: {}", name.c_str());
        reader->endMap();
        return instance;
    }

    for (auto pair: info->properties) {
        readProperty(pair.second, instance->data());
    }



    return instance;
}

void* catos::Serializer::readSubMap(catos::Property *property, void* parent) {
    
    TypeInfo& info = _registry.get_type(property->get_type_hash());
    void* inst = property->get_value(parent);
    for (auto prop_pair: info.properties) {
        readProperty(prop_pair.second, inst);
    }

    return inst;
}
