//
// Created by allos on 4/13/2025.
//

#include "yamlReader.h"
#include "stl/vector.h"
#include <ryml.hpp>
#include <iostream>

//Static globals
namespace {

    int cursor = 0;

    struct Node {
        ryml::csubstr key;
        ryml::csubstr val;
        bool has_val;
        bool is_array;
        bool is_map;

        catos::vector<Node> children;
    };


    ryml::Tree tree;
    ryml::ConstNodeRef root;
    catos::vector<Node> nodes;
}


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

    tree = ryml::parse_in_arena(source.c_str());
    root = tree.crootref();

    nodes.reserve(root.num_children());

    for (auto n: root.children()) {
        nodes.push_back(Node{
            n.key(),
            n.has_val() ? n.val() : ryml::csubstr{},
            n.has_val(),
            n.is_seq(),
            n.is_map()
        });



        if (n.is_map() && cursor <= 0) {
            for (auto child : n.children()) {

                cursor++;

                nodes.back().children.push_back(Node{
                        child.key(),
                        child.has_val() ? child.val() : ryml::csubstr{},
                        child.has_val(),
                        child.is_seq(),
                        child.is_map()
                });

                cursor--;
            }
        }
    }


}

void catos::YamlReader::close() {

    for (const auto& node : nodes) {
        std::cout << "KEY: " << node.key << " "
                  << "VAL: " << node.val << "\n- "
                  << "HAS_VAL: " << node.has_val << "\n- "
                  << "IS_MAP: " << node.is_map << "\n- "
                  << "IS_SEQ: " << node.is_array << " "
                  << "\n";

        if (node.children.length() > 0) {
            for (const auto& child : node.children) {
                std::cout << "KEY: " << child.key << " "
                          << "VAL: " << child.val << "\n- "
                          << "HAS_VAL: " << child.has_val << "\n- "
                          << "IS_MAP: " << child.is_map << "\n- "
                          << "IS_SEQ: " << child.is_array << " "
                          << "\n";
            }
        }
    }
}

catos::SerializedType catos::YamlReader::getNextEntryType() {
    return SerializedType::MAP;
}

bool catos::YamlReader::validate() {
    return true;
}
