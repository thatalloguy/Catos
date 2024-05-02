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

    /// A basic script template, made for python scripts to inherit from. NOT USABLE FOR CPP USERS!
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
            _bind(vm, type, "__init__(self)", &ScriptComponent::init);
            _bind(vm, type, "update(self)", &ScriptComponent::update);
            _bind(vm, type, "destroy(self)", &ScriptComponent::destroy);
        }
    };

    /// Script (Component) handles a python scripts, acts like a component.
    /// WARNING The component Must inherit from (catos.ScriptComponent) in order for the script class to recognize it.
    class Script : public Component {

    public:

        /// Needs source code of a python file. Finds the Component class in the code and binds to it.
        void attachScript(std::string& srcCode, VM* vm) {
            auto end = srcCode.find("(catos.ScriptComponent");
            auto start = srcCode.find("class ");

            if (end != srcCode.npos && start != srcCode.npos) {
                componentName = srcCode.substr(start + 6, end - (start + 6));
                obj = vm->getattr(vm->_main, componentName.c_str());
                _vm = vm;
            }
        }

        /// Runs the __init__ function of the python script
        void init() override {
            inst = _vm->call(obj);
        };

        /// Runs the update function of the python script
        void update() override {
            if (inst) {
                _vm->call_method(inst, "update");
            }
        };

        /// Runs the destroy function of the python script, and handles their memory
        void destroy() override {
            if (inst) {
                _vm->call_method(inst, "destroy");
            }
        };
        void _gc_mark() const{

            PK_OBJ_MARK(obj);
            PK_OBJ_MARK(inst);
        }

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