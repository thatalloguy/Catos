#pragma once

#ifndef CATOS_VERSION
#define CATOS_VERSION "0.0.1"
#endif


#include <functional>
#include <core/application.h>

#include "core/window.h"
#include "stl/string.h"


namespace catos {

    class EditorWindow {
    public:
        EditorWindow() = default;
        virtual ~EditorWindow() = default;

        bool is_valid_instance() const { return _instance >= 0 && _id >= 0; };


        virtual void init(const App& app, int id) = 0;
        virtual void render() = 0;
        virtual void clean_up() = 0;
    protected:

        int _instance{0};
        int _id{-1};
    };

    typedef std::function<EditorWindow*()> windowConstructor;


    class Editor {
    public:
        //If a window isnt passed along the editor creates one itself.
        Editor(const App& app, Window* window=nullptr);

        template<typename T>
        constexpr void registerEditorWindow(const std::string& name) {
            _editors[name] =  [] {return (EditorWindow*) new T(); };
        }

        void new_editor(const std::string& name);
        int get_new_id();


        Window* get_window();
        void run();
        void render();
        void clean_up();

    private:
        bool _is_initialized{false};
        std::unordered_map<int, EditorWindow*> _windows;
        std::unordered_map<std::string, windowConstructor> _editors;

        Window* _window{nullptr};
        const App& _app;

        int id_counter=0;
    };


}
