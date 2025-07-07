#pragma once

#ifndef CATOS_VERSION
#define CATOS_VERSION "0.0.1"
#include "objects/node.h"
#endif


#include <functional>

#include <core/application.h>
#include <core/window.h>
#include <stl/string.h>
#include <core/registry.h>


namespace catos {


    ///Credits to Skore for the Dock implementation.
    enum class DockPosition: unsigned int {
        None = 0,
        Center = 1,
        Left = 2,
        Right = 3,
        RightTop = 4,
        RightBottom = 5,
        BottomLeft = 6,
        BottomRight = 7,
    };


    class EditorWindow {
    public:
        EditorWindow() = default;
        virtual ~EditorWindow() = default;

        bool is_valid_instance() const { return _instance >= 0 && _id >= 0; };


        virtual void init(App& app, int id) = 0;
        virtual void render() = 0;
        virtual void clean_up() = 0;

        virtual DockPosition get_dock_pos() = 0;
    protected:
        int _instance{0};
        int _id{-1};
    };

    typedef std::function<EditorWindow*()> windowConstructor;


    class Editor {
    public:

        static Editor* get_current_instance();

        //If a window isnt passed along the editor creates one itself.
        Editor(App& app, Window* window=nullptr);

        template<typename T>
        constexpr void registerEditorWindow(const std::string& name) {
            _editors[name] =  [] {return (EditorWindow*) new T(); };
        }

        void new_editor(const std::string& name);
        void set_current_root(Node* new_root);
        int get_new_id();


        Window* get_window();
        Node* get_current_scene_root() { return _current_root; };
        void run();
        void render();
        void clean_up();

    private:
        bool _is_initialized{false};
        std::unordered_map<int, EditorWindow*> _windows;
        std::unordered_map<std::string, windowConstructor> _editors;

        Window* _window{nullptr};
        Node* _current_root{nullptr};
        App& _app;

        int id_counter=0;
    };


}
