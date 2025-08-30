#pragma once

#include "../Editor/editor.h"
#include "core/registry.h"

namespace catos {

    struct Foo {
        string name = "foo123";
    };

    struct Dummy {
        float dataf = 0.2f;
        int datai = 2;
        string datas = "hello";
        math::Vector3 vec3{1, 2, 3};
        Foo foo{};
    };



    static TypeInfo dummyTypeInfo;
    static Dummy instance{};

    static Registry* _registry = nullptr;
    static bool has_registered = false;

    class InspectorWindow : EditorWindow {
    public:

        static void registerType(Registry& registry) {
            if (has_registered)
                return;

            _registry = &registry;
            has_registered = true;

            registry.register_class<Foo>("Foo")
                .property("name", &Foo::name, "...");

            dummyTypeInfo = registry.register_class<Dummy>("Dummy")
                .property("dataf", &Dummy::dataf, "...")
                .property("datai", &Dummy::datai, "...")
                .property("datas", &Dummy::datas, "...")
                .property("vec3", &Dummy::vec3, "...")
                .property("foo", &Dummy::foo, "...");
        }

        InspectorWindow() = default;
        ~InspectorWindow() override = default;

        void init(App& app, int id) override;
        void render() override;
        void clean_up() override;

        DockPosition get_dock_pos() override { return DockPosition::Right; };

    private:
        float f_cache = 0.0f;
        string str_cache = "";
        int i_cache = 0;
        math::Vector3 v3_cache{0,0,0};

    };

}
