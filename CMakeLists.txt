cmake_minimum_required(VERSION 3.27)
project(catos)



include(FetchContent)



if(EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fexceptions")
endif()


set(GLFW_BUILD_WAYLAND OFF)
include(Thirdparty.cmake)


add_library(catos-headers INTERFACE)



add_subdirectory(Player)
add_subdirectory(Runtime)
add_subdirectory(Editor)


