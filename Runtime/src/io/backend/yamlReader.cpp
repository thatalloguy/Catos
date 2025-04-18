//
// Created by allos on 4/13/2025.
//

#include "yamlReader.h"

bool catos::YamlReader::readBool(const catos::string &name, bool value) {
    return false;
}

int catos::YamlReader::readInt(const catos::string &name, int value) {
    return 0;
}

float catos::YamlReader::readFloat(const catos::string &name, float value) {
    return 0;
}

catos::string catos::YamlReader::readString(const catos::string &name, const char *value) {
    return {};
}

void catos::YamlReader::beginMap(const catos::string &name) {

}

void catos::YamlReader::endMap() {

}

void catos::YamlReader::beginArray(const catos::string &name) {

}

void catos::YamlReader::endArray() {

}

void catos::YamlReader::begin(const catos::string& source) {

}

void catos::YamlReader::close() {

}

catos::SerializedType catos::YamlReader::getNextEntryType() {
    return SerializedType::MAP;
}

bool catos::YamlReader::validate() {
    return false;
}
