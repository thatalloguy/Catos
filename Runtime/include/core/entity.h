///
/// Created by allos on 4/30/2024.
///
#pragma once


#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>
#include "types.h"
#include "type_utils.h"

namespace catos {

    class Entity;



    /// Component is an abstract class that is the base for any component.
    class Component {
    public:

        virtual void init(Entity& entity) {};
        virtual void update(Entity& entity) {};
        virtual void destroy(Entity& entity) {};
    };

    /// Entities hold components which do the logic.
    class Entity {

    public:
        void setup(str name) { _name = name; };
        ~Entity() = default;


        /// Get a component via name, returns a Component pointer.
        Component* get_component(cstr name);

        /// Add a component. Needs a type for the registry name.
         void add_component(Component* component, cstr name){
            std::string t = name;
            componentTable.emplace(t, component);
        };

        /// Returns the name of the entity
        str& get_name() { return _name; };



        ///Runs Component.init() on every registered component. (Init gets run at the start of the game)
        void init();
        ///Runs Component.update() on every registered component. ( Gets called every tick)
        void update();
        ///Runs Component.destroy() on every registered component. ( Gets called at the end of the program).
        void destroy();

        void test()  { std::cout << "hello world from entity!\n"; };



    private:
        ////TODO should i allow mutliple components of the same type?
        std::unordered_map<str, Component*> componentTable;
        str _name;
    };





}