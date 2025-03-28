add_library(catos-runtime INTERFACE)
target_include_directories(catos-runtime INTERFACE include)


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

        src/renderer/*.h
        src/renderer/*.cpp
        src/renderer/passes/*.h
        src/renderer/passes/*.cpp

        src/stl/*.h
        src/stl/*.cpp

        src/io/*.h
        src/io/*.cpp

        src/io/handlers/*.h
        src/io/handlers/*.cpp

)


file(GLOB_RECURSE FASTGLTF_DEPS
        ${fastgltf_content_SOURCE_DIR}/deps/simdjson/simdjson.h
        ${fastgltf_content_SOURCE_DIR}deps/simdjson/simdjson.cpp

        ../Thirdparty/stb/stb_image.h
)

add_library(catos-runtime-static STATIC ${CATOS_RUNTIME_SRC} )
target_link_libraries(catos-runtime-static PUBLIC catos-runtime)
target_include_directories(catos-runtime-static PUBLIC src)



#tests
file(GLOB_RECURSE CATOS_RUNTIME_TEST src/tests/*.h src/tests/*.hpp src/tests/*.c src/tests/*.cpp)
add_executable(catos-runtime-tests ${CATOS_RUNTIME_TEST} "../Thirdparty/stb/stb_image.h")
#???
target_link_libraries(catos-runtime-tests catos-runtime-static doctest)
target_link_libraries(catos-runtime-static PUBLIC dwmapi)


target_link_libraries(catos-runtime-static PUBLIC spdlog)
target_link_libraries(catos-runtime-static PUBLIC glfw)
target_link_libraries(catos-runtime-static PUBLIC fastgltf)
target_link_libraries(catos-runtime-static PUBLIC pocketpy)


target_include_directories(catos-runtime-static PUBLIC ${GLAD_SRC})
target_include_directories(catos-runtime-static PUBLIC "../Thirdparty/stb/")


add_test(NAME catos-runtime-tests COMMAND catos-runtime-tests)
