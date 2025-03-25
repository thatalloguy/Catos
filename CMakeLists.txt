cmake_minimum_required(VERSION 3.27)
project(catos)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)


include(FetchContent)



if(EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fexceptions")
endif()


include(Thirdparty.cmake)


add_library(catos-headers INTERFACE)



add_subdirectory(Player)
add_subdirectory(Runtime)
add_subdirectory(Editor)


