cmake_minimum_required(VERSION 3.27)
project(catos)

set(CMAKE_CXX_STANDARD 20)



#dependencies
add_subdirectory(Thirdparty/doctest)
add_subdirectory(Thirdparty/pocketpy)

if(EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fexceptions")
endif()

include_directories(Thirdparty/tinystl/include/)

add_library(catos-headers INTERFACE)

add_subdirectory(Player)
add_subdirectory(Runtime)
