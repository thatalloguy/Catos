//
// Created by allos on 4/6/2025.
//

#include <string>
#include "yamlwriter.h"
#include "spdlog/spdlog.h"
#include <ryml.hpp>
#include <unordered_set>

namespace {
    std::string out_string = "";
}

bool catos::YamlWriter::open(const catos::string &path) {
    is_file_open =true;
    out_file = path;

    return true;
}

void catos::YamlWriter::writeBool(const catos::string &name, bool value) {
   format();
   out_string += name.c_str();
   out_string += ": ";
   out_string += std::to_string(value);
   out_string += "\n";
}

void catos::YamlWriter::writeInt(const catos::string &name, int value) {
    format();
    out_string += name.c_str();
    out_string += ": ";
    out_string += std::to_string(value);
    out_string += "\n";
}

void catos::YamlWriter::writeFloat(const catos::string &name, float value) {
    format();
    out_string += name.c_str();
    out_string += ": ";
    out_string += std::to_string(value);
    out_string += "\n";
}

void catos::YamlWriter::writeString(const catos::string &name, const char *value) {
    format();
    out_string += name.c_str();
    out_string += R"(: ")";
    out_string += value;
    out_string += R"(")";
    out_string += "\n";
}

void catos::YamlWriter::beginMap(const catos::string &name) {
    if (maps_opened - maps_closed == 0) {

        for (auto map : _root_maps) {
            if (map == name) {
                spdlog::error("[YamlWriter] A root map must be Unique");
                return;
            }
        }

        _root_maps.push_back(name);
    }

    format();
    maps_opened++;
    out_string += name.c_str();
    out_string += ":\n";
}

void catos::YamlWriter::endMap() {
    maps_closed++;
}


void catos::YamlWriter::beginArray(const catos::string &name) {
    format();
    arrays_openend++;
    out_string += name.c_str();
    out_string += ":\n";
}

void catos::YamlWriter::endArray() {
    arrays_closed++;
}

void catos::YamlWriter::begin() {

}

void catos::YamlWriter::close() {

    if (!validate()) {
        spdlog::error("[YamlWriter] Could not validate Yaml");
        return;
    }

    if (!is_file_open) {
        spdlog::error("[YamlWriter] No File given to write to");
        return;
    }

    FILE* file = fopen(out_file.c_str(), "w");

    if (file != nullptr) {
        fprintf(file, out_string.c_str());

        fclose(file);
    } else {
        spdlog::error("[YamlWriter] Could not write to file: {}", out_file.c_str());
    }

    is_file_open = false;

}


void catos::YamlWriter::format() {
    for (int i=0; i<maps_opened - maps_closed; i++) {
        out_string += "  ";
    }

    if (arrays_openend != arrays_closed && maps_opened == maps_closed + 1) {
        out_string += "- ";
    }
}

bool catos::YamlWriter::validate() {


    return (arrays_openend == arrays_closed && maps_opened == maps_closed);
}
