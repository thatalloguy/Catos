//
// Created by allos on 9/29/2024.
//
#pragma once

#include <map>
#include <stl/string.h>

namespace catos {

    struct NodeCreationInfo {

    };

    static bool validate_node_creation_info(const NodeCreationInfo& info) {

    }


    class Node {
    public:

        static Node* create();

        Node(bool manage_memory=true): _manage_memory(manage_memory) {};
        virtual ~Node() = default;

        virtual void initialize();

        virtual void update();
        virtual void render();

        virtual void destroy();

        void set_parent(Node* parent);

        Node* find_node(const string& path, bool recursive=true) const;
        Node* get_child(const string& name) const;
        Node* get_parent() const;
        Node* get_root() const;

        int num_children() const;
        bool is_root() const;

        const string& path() const;
        const string& name() const;

    private:
        bool _manage_memory{true};

        string _path{""};
        string _name{""};
        string _type{"Node"};

    protected:
        Node* _parent{nullptr};
        Node* _root{nullptr};

        std::map<string, Node*> _children{};
    };

    static bool is_node_valid(Node* node) { return node != nullptr; };
}

