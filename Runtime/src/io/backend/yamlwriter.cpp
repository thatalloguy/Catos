//
// Created by allos on 4/6/2025.
//

#include <string>
#include "yamlwriter.h"
#include "spdlog/spdlog.h"
#include <ryml.hpp>
#include <iostream>

namespace {
    std::string out_string = "";
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
    out_string += "- ";
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
        spdlog::error("Could not validate Yaml");
        return;
    }


    FILE* file = fopen("../../../test.yaml", "w");

    fprintf(file, out_string.c_str());

    fclose(file);

}


void catos::YamlWriter::format() {
    for (int i=0; i<maps_opened; i++) {
        out_string += "  ";
    }

    if (arrays_openend > arrays_closed) {
        out_string += "- ";
    }
}

bool catos::YamlWriter::validate() {
    return (arrays_openend == arrays_closed && maps_opened == maps_closed);
}
