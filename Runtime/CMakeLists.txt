add_library(catos-runtime INTERFACE)
target_include_directories(catos-runtime INTERFACE include)


#static-lib
file(GLOB_RECURSE FASTGLTF_DEPS
        Thirdparty/fastgltf/deps/simdjson/simdjson.h
        Thirdparty/fastgltf/deps/simdjson/simdjson.cpp
)
file(GLOB_RECURSE CATOS_RUNTIME_SRC

        src/core/*.cpp
        src/core/*.h

        src/math/*.h
        src/math/*.cpp

        src/tests/*.cpp

        src/objects/*.h
        src/objects/*.cpp

        src/scripting/*.h
        src/scripting/*.cpp

        src/stl/*.h
        src/stl/*.cpp

)
add_library(catos-runtime-static STATIC ${CATOS_RUNTIME_SRC}  ${IMGUI_SOURCE} ${FASTGLTF_DEPS})
target_link_libraries(catos-runtime-static PUBLIC catos-runtime)
target_include_directories(catos-runtime-static PUBLIC src)




target_include_directories(catos-runtime-static PUBLIC "Thirdparty/imgui")
target_include_directories(catos-runtime-static PUBLIC "Thirdparty/stb")
target_include_directories(catos-runtime-static PUBLIC "Thirdparty/glm")
target_include_directories(catos-runtime-static PUBLIC "Thirdparty/pocketpy/include/pocketpy")
target_include_directories(catos-runtime-static PUBLIC "Thirdparty/pocketpy/include/pybind11/")
target_include_directories(catos-runtime-static PUBLIC "Thirdparty/glfw/include")
#tests
file(GLOB_RECURSE CATOS_RUNTIME_TEST src/tests/*.h src/tests/*.hpp src/tests/*.c src/tests/*.cpp)
add_executable(catos-runtime-tests ${CATOS_RUNTIME_TEST})
#???
target_link_libraries(catos-runtime-tests catos-runtime-static doctest)
target_link_libraries(catos-runtime-static PUBLIC dwmapi)


target_link_libraries(catos-runtime-static PUBLIC spdlog)
target_link_libraries(catos-runtime-static PUBLIC fastgltf)
target_link_libraries(catos-runtime-static PUBLIC pocketpy)
target_link_libraries(catos-runtime-static PUBLIC glfw)




add_test(NAME catos-runtime-tests COMMAND catos-runtime-tests)