cmake_minimum_required(VERSION 3.27)
project(catos)

set(CMAKE_CXX_STANDARD 20)



#dependencies
add_subdirectory(Thirdparty/doctest)

include_directories(Thirdparty/tinystl/include/)

add_library(catos-headers INTERFACE)

add_subdirectory(Player)
add_subdirectory(Runtime)
