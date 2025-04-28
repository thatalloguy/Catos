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
        catos::string key;
        catos::string val;
        bool has_val;
        bool is_array;
        bool is_map;

        catos::vector<Node> children{};
    };


    ryml::Tree tree;
    ryml::ConstNodeRef root;
    catos::vector<Node> nodes;

    catos::string to_string(const ryml::csubstr& str) {
        std::string out{""};
        for(int i=0; i<str.size(); i++) {
            out += str.data()[i];
        }
        return catos::string{out.data()};
    }


    void parseNode(Node* parent, ryml::ConstNodeRef& node) {


        if (parent == nullptr) {




            nodes.push_back({
                                    to_string(node.key()),
                                    node.has_val() ? to_string(node.val()) : catos::string{""},
                                    node.has_val(),
                                    node.is_seq(),
                                    node.is_map()
                            });
            parent = &nodes.back();

        } else {
            parent->children.push_back({
                                    to_string(node.key()),
                                    node.has_val() ? to_string(node.val()) : catos::string{},
                                    node.has_val(),
                                    node.is_seq(),
                                    node.is_map()
                            });

        }

        if (node.is_map() && cursor == 0) {
            cursor++;

            for (auto child : node.children()) {
                parseNode(parent, child);
            }

            cursor--;
        }
    }
}


bool catos::YamlReader::readBool(const catos::string &name) {
    return false;
}

int catos::YamlReader::readInt(const catos::string &name) {
    return 0;
}

float catos::YamlReader::readFloat(const catos::string &name) {
    return 0;
}

catos::string catos::YamlReader::readString(const catos::string &name) {
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

void catos::YamlReader::read(const catos::string& source, catos::vector<catos::Instance*>& out) {

    tree = ryml::parse_in_arena(source.c_str());
    root = tree.crootref();

    nodes.reserve(root.num_children());

    for (ryml::ConstNodeRef n: root.children()) {
        parseNode(nullptr, n);
    }



    for (const auto& node : nodes) {
        std::cout << "KEY: " << node.key.c_str() << " \n"
                  << "VAL: " << node.val.c_str() << "\n- "
                  << "HAS_VAL: " << node.has_val << "\n- "
                  << "IS_MAP: " << node.is_map << "\n- "
                  << "IS_SEQ: " << node.is_array << "\n- "
                  << "IS_PARENT" << node.children.length() << " "
                  << "\n";

        if (node.children.length() > 0) {
            for (const auto& child : node.children) {
                std::cout << "-KEY: " << child.key.c_str() << "\n "
                          << "-VAL: " << child.val.c_str() << "\n- "
                          << "-HAS_VAL: " << child.has_val << "\n- "
                          << "-IS_MAP: " << child.is_map << "\n- "
                          << "-IS_SEQ: " << child.is_array << " "
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
