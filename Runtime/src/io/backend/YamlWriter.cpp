//
// Created by allos on 4/6/2025.
//

#include <string>
#include "YamlWriter.h"
#include "spdlog/spdlog.h"
#include <ryml.hpp>

namespace {
    std::string out_string = "";
}

void catos::YamlWriter::writeBool(const catos::string &name, bool value) {

}

void catos::YamlWriter::writeInt(const catos::string &name, int value) {

}

void catos::YamlWriter::writeFloat(const catos::string &name, float value) {

}

void catos::YamlWriter::writeString(const catos::string &name, const char *value) {

}

void catos::YamlWriter::beginMap() {
    maps_opened++;
}

void catos::YamlWriter::beginMap(const catos::string &name) {
    maps_opened++;
}

void catos::YamlWriter::endMap() {
    maps_closed++;
}

void catos::YamlWriter::beginArray() {
    arrays_openend++;
}

void catos::YamlWriter::beginArray(const catos::string &name) {
    arrays_openend++;
}

void catos::YamlWriter::endArray() {
    arrays_closed++;
}

void catos::YamlWriter::begin() {

}

void catos::YamlWriter::close() {

    if (!validate()) {
        spdlog::error("Could not validate Yaml");
        return;
    }

    FILE* file = fopen("../../../test.yaml", "w");

    auto tree = ryml::parse_in_arena(out_string.c_str());

    ryml::emit_yaml(tree, tree.root_id(), file);

    fclose(file);

}

bool catos::YamlWriter::validate() {
    return (arrays_openend == arrays_closed && maps_opened == maps_closed);
}
