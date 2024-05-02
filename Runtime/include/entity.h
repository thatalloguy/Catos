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
        PY_CLASS(Entity, catos, Entity)
        //Entity() { };
        void setup(str name) { _name = name; };
        ~Entity() = default;

        template<class Comp>
        /// Get a component via its type. returns a pointer of that type.
        Comp* getComponent();

        /// Get a component via name, returns a Component pointer.
        Component* getComponent(str& name);

        float test = 3.f;

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

        // POCKETPY IMPL
/*        bool operator==(Entity& other) {
            return _name == other._name; // bob is unique ;)
        }*/

        static void _register(VM* vm, PyObject* mod, PyObject* type){
            PY_FIELD(Entity, "test", test);
            _bind(vm, type, "__init__(self, name)", &Entity::setup);
            _bind(vm, type, "init(self)", &Entity::init);
            _bind(vm, type, "update(self)", &Entity::update);
            _bind(vm, type, "destroy(self)", &Entity::destroy);

        }

    private:
        ////TODO should i allow mutliple components of the same type?
        std::unordered_map<str, Component*> componentTable;
        str _name;
    };



    /// Script (Component) handles a python scripts, acts like a component. WARNING The component Must inherit from (catos.ScriptComponent) in order for the script class to recognize it.
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
            } else {
                std::cerr << "COULDNT FIND SCRIPTCOMPONENT\n";
                exit(-1);
            }
        }

        /// Runs the __init__ function of the python script
        void init(Entity& entity) override {

            PyObject* ent = py_var(_vm, entity);

            inst = _vm->call(obj, ent);

            entity.test = py_cast<Entity>(_vm, ent).test;
        };

        /// Runs the update function of the python script
        void update(Entity& entity) override {
            if (inst) {
                PyObject* ent = py_var(_vm, entity);

                _vm->call_method(inst, "update", ent);

                entity = py_cast<Entity>(_vm, ent);

            }
        };

        /// Runs the destroy function of the python script, and handles their memory
        void destroy(Entity& entity) override {
            if (inst) {
                _vm->call_method(inst, "destroy");
            }
        };

        /// FOR POCKETPY
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



    /// A basic script template, made for python scripts to inherit from. NOT USABLE FOR CPP USERS!
    class ScriptComponent {
    public:
        PY_CLASS(ScriptComponent, catos, ScriptComponent)
        void init(Entity entity)  {}

        void update(Entity entity)  {}

        void destroy(Entity entity)  {}

        // POCKETPY IMPL
        bool operator==(ScriptComponent other) {
            return false; // bob is unique ;)
        }

        static void _register(VM* vm, PyObject* mod, PyObject* type){
            _bind(vm, type, "__init__(self, entity)", &ScriptComponent::init);
            _bind(vm, type, "update(self, entity)", &ScriptComponent::update);
            _bind(vm, type, "destroy(self, entity)", &ScriptComponent::destroy);
        }
    };


}
