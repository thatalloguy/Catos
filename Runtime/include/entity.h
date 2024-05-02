///
/// Created by allos on 4/30/2024.
///
#pragma once


#include "pocketpy/pocketpy.h"

#include <unordered_map>
#include <vector>
#include <memory>
#include "types.h"
#include "type_utils.h"

using namespace pkpy;

namespace catos {

    /// Component is an abstract class that is the base for any component.
    class Component {
    public:
        virtual void init() {};
        virtual void update() {};
        virtual void destroy() {};
    };


    class ScriptComponent {
    public:
        PY_CLASS(ScriptComponent, catos, ScriptComponent)
        void init()  {}

        void update()  {}

        void destroy()  {}

        // POCKETPY IMPL
        bool operator==(ScriptComponent other) {
            return false; // bob is unique ;)
        }

        ScriptComponent* _() {
            return this;
        }

        static void _register(VM* vm, PyObject* mod, PyObject* type){
            //PY_STRUCT_LIKE(Game)

            _bind(vm, type, "__init__(self)", &ScriptComponent::init);
            _bind(vm, type, "update(self)", &ScriptComponent::update);
            _bind(vm, type, "destroy(self)", &ScriptComponent::destroy);

        }
    };

    class Script : public Component {

    public:

        /// The component Must have catos.ScriptComponent before it in order for the script class to recognize it.
        void attachScript(std::string& srcCode, VM* vm) {
            auto end = srcCode.find("(catos.ScriptComponent");
            auto start = srcCode.find("class ");

            if (end != srcCode.npos && start != srcCode.npos) {
                componentName = srcCode.substr(start + 6, end - (start + 6));
                std::cout << "NAME: " << componentName << "\n";

                obj = vm->getattr(vm->_main, componentName.c_str());

                _vm = vm;
            }
        }

        void init() override {
            inst = _vm->call(obj);
        };

        void update() override {
            _vm->call_method(inst, "update");
        };

        void destroy() override {
            _vm->call_method(inst, "destroy");
        };

    private:
        std::string componentName;
        PyObject* obj = nullptr;
        PyObject* inst = nullptr;
        VM* _vm = nullptr;
    };

    /// Entities hold components which do the logic.
    class Entity {

    public:
        Entity(str& name) : _name(name) {};
        ~Entity() = default;

        template<class Comp>
        /// Get a component via its type. returns a pointer of that type.
        Comp* getComponent();

        /// Get a component via name, returns a Component pointer.
        Component* getComponent(str& name);


        template<class Comp>
        /// Add a component. Needs a type for the registry name.
        void addComponent(Component* component);

        /// Returns the name of the entity
        str& getName() { return _name; };



        ///Runs Component.init() on every registered component. (Init gets run at the start of the game)
        void init();
        ///Runs Component.update() on every registered component. ( Gets called every tick)
        void update();
        ///Runs Component.destroy() on every registered component. ( Gets called at the end of the program).
        void destroy();

    private:
        ////TODO should i allow mutliple components of the same type?
        std::unordered_map<str, Component*> componentTable;
        str& _name;
    };



}