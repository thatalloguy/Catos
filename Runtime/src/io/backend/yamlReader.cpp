//
// Created by allos on 4/13/2025.
//

#include "yamlReader.h"
#include "stl/vector.h"
#include "spdlog/spdlog.h"
#include <ryml.hpp>

namespace {
    ryml::NodeRef _root;
    ryml::NodeRef _current_node;
    catos::vector<ryml::NodeRef> _stack;
    size_t _array_index = 0;

}
bool catos::YamlReader::open(const std::string &content) {
    try {
        ryml::Tree tree = ryml::parse_in_arena(content.c_str());
        _root = tree.rootref();
        _current_node = _root;
        _stack.push_back(_current_node);
        return true;
    } catch (const std::exception& e) {
        spdlog::error("Could not parse yaml :( : {}", e.what());
        return false;
    }
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
    std::string str_value;
    child >> str_value;

    return {str_value.c_str()};
}

void catos::YamlReader::beginMap(const catos::string &name) {
    if (!_current_node.has_child(name.c_str())) {
        spdlog::warn("{} Field could not be found", name.c_str());
        return;
    }

    _current_node = _current_node[name.c_str()];
    
    _stack.push_back(_current_node);
}

void catos::YamlReader::endMap() {
    if (_stack.length() <= 1) {
        spdlog::warn("Attempting to close the root instead of a map");
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
    if (_array_index <= 1) {
        spdlog::warn("Attempting to close a non Array");
        return;
    }

    _stack.pop_back();
    _current_node = _stack.back();
    _array_index = 0;
}


catos::SerializedType catos::YamlReader::getNextEntryType() {
    if (_array_index >= _current_node.num_children()) {
        return SerializedType::MAP;
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
    if (_array_index >= _current_node.num_children()) {
        return false;
    }

    _current_node = _current_node[_array_index];
    _array_index++;
    _stack.push_back(_current_node);
    return true;
}

bool catos::YamlReader::validate() {
    return !_root.invalid();
}

