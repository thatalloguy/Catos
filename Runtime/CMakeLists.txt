add_library(catos-runtime INTERFACE)
target_include_directories(catos-runtime INTERFACE include)
#static-lib
file(GLOB_RECURSE FASTGLTF_DEPS
        Thirdparty/fastgltf/deps/simdjson/simdjson.h
        Thirdparty/fastgltf/deps/simdjson/simdjson.cpp

        Thirdparty/stb/stb_image.h
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

        src/renderer/*.h
        src/renderer/*.cpp
        src/renderer/passes/*.h
        src/renderer/passes/*.cpp

        src/stl/*.h
        src/stl/*.cpp

        src/io/*.h
        src/io/*.cpp

        src/io/backend/*.h
        src/io/backend/*.cpp

)


file(GLOB_RECURSE FASTGLTF_DEPS
        ${fastgltf_content_SOURCE_DIR}/deps/simdjson/simdjson.h
        ${fastgltf_content_SOURCE_DIR}deps/simdjson/simdjson.cpp

        ../Thirdparty/stb/stb_image.h
)

add_library(catos-runtime-static STATIC ${CATOS_RUNTIME_SRC} ${FASTGLTF_DEPS} ${IMGUI_SOURCE} ${IMGUI_SOURCE_BACKEND})
target_link_libraries(catos-runtime-static PUBLIC catos-runtime)
target_include_directories(catos-runtime-static PUBLIC src)



#tests
file(GLOB_RECURSE CATOS_RUNTIME_TEST src/tests/*.h src/tests/*.hpp src/tests/*.c src/tests/*.cpp)
add_executable(catos-runtime-tests ${CATOS_RUNTIME_TEST}  "../Thirdparty/stb/stb_image.h")
#???
target_link_libraries(catos-runtime-tests catos-runtime-static doctest)

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
        target_link_libraries(catos-runtime-static PUBLIC dwmapi)
endif()

target_link_libraries(catos-runtime-static PUBLIC spdlog)
#target_link_libraries(catos-runtime-static PUBLIC glfw)
target_link_libraries(catos-runtime-static PUBLIC SDL3::SDL3-static)
target_link_libraries(catos-runtime-static PUBLIC ryml)
target_link_libraries(catos-runtime-static PUBLIC doctest)
target_link_libraries(catos-runtime-static PUBLIC pocketpy)


target_include_directories(catos-runtime-static PUBLIC ${GLAD_SRC})
target_include_directories(catos-runtime-static PUBLIC ${pocketpy_content_SOURCE_DIR}/include)
target_include_directories(catos-runtime-static PUBLIC ${SDL3_content_SOURCE_DIR}/include)
target_include_directories(catos-runtime-static PUBLIC ${rapidyaml_content_SOURCE_DIR}/src)
target_include_directories(catos-runtime-static PUBLIC ${imgui_content_SOURCE_DIR})
target_include_directories(catos-runtime-static PUBLIC "../Thirdparty/stb/")


add_test(NAME catos-runtime-tests COMMAND catos-runtime-tests)
