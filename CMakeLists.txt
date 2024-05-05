cmake_minimum_required(VERSION 3.27)
project(catos)

set(CMAKE_CXX_STANDARD 20)



#dependencies
add_subdirectory(Thirdparty/doctest)

if(EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fexceptions")
endif()

include_directories(Thirdparty/tinystl/include/)
include_directories(Thirdparty/Mono/include/mono-2.0/)
link_directories(Thirdparty/Mono/lib/)

add_library(catos-headers INTERFACE)



add_subdirectory(Player)
add_subdirectory(Runtime)


