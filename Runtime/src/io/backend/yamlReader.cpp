//
// Created by allos on 4/13/2025.
//

#include "yamlReader.h"
#include "stl/vector.h"
#include "spdlog/spdlog.h"

#include <string>
#include <iostream>

bool catos::YamlReader::open(const std::string &content) {
    _tree = ryml::parse_in_arena(content.c_str());
    _root = _tree.rootref();
    _current_node = _root;
    _stack.push_back(_current_node);
    _is_root_open = true;
    spdlog::info("Parsing yaml");

    return true;
}


catos::string catos::YamlReader::readString() {
    std::string value;
    for (int i=0; i<_current_node[_array_index][0].val().len; i++) {
        value += _current_node[_array_index][0].key().data()[i];
    }

    return {value.c_str()};
}

float catos::YamlReader::readFloat() {
    float out = 0;

    _current_node[_array_index ][0] >> out;

    return out;
}

int catos::YamlReader::readInt() {
    int out;
    _current_node[_array_index][0] >> out;

    return out;
}

bool catos::YamlReader::readBool() {
    bool out;
    _current_node[_array_index][0] >> out;

    return out;
}


bool catos::YamlReader::readBool(const catos::string &name) {
    if (!_current_node.has_child(name.c_str())) {
        spdlog::warn("{} Field could not be found", name.c_str());
        return false;
    }

    bool value = false;
    _current_node[name.c_str()] >> value;

    return value;
}

int catos::YamlReader::readInt(const catos::string &name) {
    if (!_current_node.has_child(name.c_str())) {
        spdlog::warn("{} Field could not be found", name.c_str());
        return -1;
    }

    int value = -1;
    _current_node[name.c_str()] >> value;

    return value;
}

float catos::YamlReader::readFloat(const catos::string &name) {
    if (!_current_node.has_child(name.c_str())) {
        spdlog::warn("{} Field could not be found", name.c_str());
        return -1.0f;
    }

    float value = -1.0f;
    _current_node[name.c_str()] >> value;

    return value;
}

catos::string catos::YamlReader::readString(const catos::string &name) {
    if (!_current_node.has_child(name.c_str())) {
        spdlog::warn("{} Field could not be found", name.c_str());
        return false;
    }

    auto child = _current_node[ryml::to_csubstr(name.c_str())];

    std::string value;
    for (int i=0; i<child.val().len; i++) {
        value += child.val().str[i];
    }

    return {value.c_str()};
}

void catos::YamlReader::beginMap(const catos::string &name) {
    if (!_current_node.has_child(name.c_str())) {
        spdlog::warn("{} SubMap could not be found", name.c_str());
        return;
    }
    _current_node = _current_node[name.c_str()];
    _stack.push_back(_current_node);
}

void catos::YamlReader::endMap() {
    if (_stack.length() <= 1) {
        spdlog::warn("Attempting to close the root instead of a map");
        _is_root_open = false;
        return;
    }

    _stack.pop_back();
    _current_node = _stack.back();
}

void catos::YamlReader::beginArray(const catos::string &name) {
    if (!_current_node.has_child(name.c_str())) {
        spdlog::warn("Array field not found {}", name.c_str());
        return;
    }

    _current_node = _current_node[name.c_str()];
    _array_index = 0;

    _stack.push_back(_current_node);
}

void catos::YamlReader::endArray() {
    if (_array_index < 1) {
        spdlog::warn("Attempting to close a non Array");
        return;
    }

    _stack.pop_back();
    _current_node = _stack.back();
}


catos::SerializedType catos::YamlReader::getNextEntryType() {
    if (_array_index >= _current_node.num_children()) {
        return SerializedType::INVALID;
    }

    auto child = _current_node[_array_index];
    _array_index++;

    if (child.is_map()) {
        return SerializedType::MAP;
    } else if (child.is_seq()) {
        return SerializedType::ARRAY;
    } else {
        if (child.val().is_integer()) {
            return SerializedType::INT;
        }else if (child.val() == "true" || child.val() == "false") {
            return SerializedType::BOOL;
        } else if (child.val().find(".") != std::string::npos) {
            return SerializedType::FLOAT;
        } else {
            return SerializedType::STRING;
        }
    }
}


bool catos::YamlReader::nextArrrayElement() {
    auto n = _current_node.num_children();


    if (_current_node.is_root() && _root.num_children() > _map_index) {
        return true;
    }

    if (_array_index >= n) {
        return false;
    }


    return true;
}

bool catos::YamlReader::validate() {
    return !_root.invalid();
}

catos::string catos::YamlReader::getCurrentKey() {

    auto node = _current_node;

    if (_current_node.is_root()) {
        node = _current_node[_map_index];
        _map_index++;
    }


    std::string value;
    for (int i=0; i<node.key().len; i++) {
        value += node.key().data()[i];
    }

    return {value.c_str()};
}

void catos::YamlReader::beginMap() {
    _current_node = _current_node[_array_index];
    _array_index++;
    _stack.push_back(_current_node);
}

void catos::YamlReader::beginArray() {
    _current_node = _current_node[0];
    _array_index = 0;

    _stack.push_back(_current_node);
}

