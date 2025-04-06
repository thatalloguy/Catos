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
    spdlog::info("bool: {} | {}", name.c_str(), value);
}

void catos::YamlWriter::writeInt(const catos::string &name, int value) {
    spdlog::info("int: {} | {}", name.c_str(), value);
}

void catos::YamlWriter::writeFloat(const catos::string &name, float value) {
    spdlog::info("float: {} | {}", name.c_str(), value);
}

void catos::YamlWriter::writeString(const catos::string &name, const char *value) {
    spdlog::info("string: {} | {}", name.c_str(), value);
}

void catos::YamlWriter::beginMap() {
    maps_opened++;
    spdlog::info("beginning map");
}

void catos::YamlWriter::beginMap(const catos::string &name) {
    maps_opened++;
    spdlog::info("beginning map {}", name.c_str());
}

void catos::YamlWriter::endMap() {
    maps_closed++;
    spdlog::info("ended map");
}

void catos::YamlWriter::beginArray() {
    arrays_openend++;
    spdlog::info("beginning array");
}

void catos::YamlWriter::beginArray(const catos::string &name) {
    arrays_openend++;
    spdlog::info("beginning array {}", name.c_str());
}

void catos::YamlWriter::endArray() {
    arrays_closed++;
    spdlog::info("ended array");
}

void catos::YamlWriter::begin() {

}

void catos::YamlWriter::close() {

    if (!validate()) {
        spdlog::error("Could not validate Yaml");
        return;
    }

//    FILE* file = fopen("../../../test.yaml", "w");
//
//    auto tree = ryml::parse_in_arena(out_string.c_str());
//
//    ryml::emit_yaml(tree, tree.root_id(), file);
//
//    fclose(file);

}

bool catos::YamlWriter::validate() {
    return (arrays_openend == arrays_closed && maps_opened == maps_closed);
}
