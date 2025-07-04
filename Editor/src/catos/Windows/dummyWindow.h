#pragma once

#include "../Editor/editor.h"
#include "core/registry.h"

namespace catos {


    struct Dummy {
        float dataf = 0.2f;
        int datai = 2;
        string datas = "hello";
        math::Vector3 vec3{1, 2, 3};
    };


    static TypeInfo dummyTypeInfo;
    static Dummy instance{};

    static bool has_registered = false;

    class DummyWindow : EditorWindow {
    public:

        static void registerType(Registry& registry) {
            if (has_registered)
                return;

            has_registered = true;

            dummyTypeInfo = registry.register_class<Dummy>("Dummy")
                .property("dataf", &Dummy::dataf, "...")
                .property("datai", &Dummy::datai, "...")
                .property("datas", &Dummy::datas, "...");
        }

        DummyWindow() = default;
        ~DummyWindow() override = default;

        void init(App& app, int id) override;
        void render() override;
        void clean_up() override;

        DockPosition get_dock_pos() override { return DockPosition::Right; };

    };

}
