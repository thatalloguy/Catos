cmake_minimum_required(VERSION 3.27)
project(catos)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)



#dependencies
add_subdirectory(Thirdparty/doctest)

add_subdirectory("Thirdparty/spdlog")
add_subdirectory("Thirdparty/fastgltf")
add_subdirectory("Thirdparty/glfw")
add_subdirectory("Thirdparty/pocketpy")

file(GLOB_RECURSE IMGUI_SOURCE
        Thirdparty/imgui/imgui.cpp
        Thirdparty/imgui/imgui.h
        Thirdparty/imgui/imgui_internal.h
        Thirdparty/imgui/imgui_internal.cpp
        Thirdparty/imgui/imconfig.h
        Thirdparty/imgui/imstb_rectpack.h
        Thirdparty/imgui/imgui_draw.cpp
        Thirdparty/imgui/imgui_tables.cpp
        Thirdparty/imgui/imgui_widgets.cpp
        Thirdparty/imgui/imgui_demo.cpp

        Thirdparty/imgui/backends/imgui_impl_glfw.h
        Thirdparty/imgui/backends/imgui_impl_glfw.cpp

        Thirdparty/imgui/extensions/imgui_dock.h
        Thirdparty/imgui/extensions/imgui_dock.cpp
)

if(EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fexceptions")
endif()

include_directories(Thirdparty/Mono/include/mono-2.0/)

include_directories("Thirdparty/imgui")
include_directories("Thirdparty/stb")
include_directories("Thirdparty/glm")
include_directories("Thirdparty/glfw/include")

include_directories(Thirdparty/pocketpy/include/pybind11/)
include_directories(Thirdparty/pocketpy/include/)
include_directories(Thirdparty/pocketpy/include/pocketpy/)

add_library(catos-headers INTERFACE)



add_subdirectory(Player)
add_subdirectory(Runtime)
add_subdirectory(Editor)


