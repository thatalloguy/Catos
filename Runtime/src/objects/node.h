//
// Created by allos on 9/29/2024.
//
#pragma once

#include <unordered_map>
#include <stl/string.h>

#include "spdlog/spdlog.h"

#include <ranges>

#include "stl/vector.h"


template <>
struct std::hash<catos::string>
{
    std::size_t operator()(const catos::string& str) const noexcept
    {
        unsigned int hash = 0;
        for (auto it = str.begin(); it != str.end(); ++it) {
            hash = *it + (hash << 6) + (hash << 16) - hash;
        }
        //hash = hash % str.length();
        return hash;
    }
};

namespace catos {
    class Node;



    class Node {
    public:


        Node(bool manage_memory=true): _manage_memory(manage_memory) {};
        virtual ~Node() = default;

        virtual void initialize(const string& name);

        virtual void update();
        virtual void render();

        virtual void destroy();

        virtual size_t get_node_type_hash() ;

        void set_parent(Node* parent);

        bool has_child(const string& name);

        Node* find_node(const string& name, bool recursive=true);
        Node* get_child(const string& name);
        Node* get_parent();

        int num_children();
        bool is_root();

        const string& path();
        const string& path() const { return _path; };
        const string& name() const;

        vector<Node*>&  children() { return _children; };

        void change_name(const string& new_name);


        string _name{""};

    private:
        bool _manage_memory{true};

        string _path{""};

    protected:
        string _type{"Node"};

        Node* _parent{nullptr};

        ///TODO REPLACE WITH CUSTOM STRUCTURE THATS FAST FOR LOOK UP (hashmap wont work)
        vector<Node*> _children{};

        void remove_child(const string& child);
    };

    class DummyNode: public Node {
    public:
        size_t get_node_type_hash() override{
            return typeid(DummyNode).hash_code();
        }
    };

    class DummyNode2: public DummyNode {

    };

    class DummyNode3: public Node {

    };



    static bool is_node_valid(Node* node) { return node != nullptr; };
}

