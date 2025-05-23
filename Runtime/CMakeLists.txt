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

add_library(catos-runtime-static STATIC ${CATOS_RUNTIME_SRC} ${GLAD_SRC} ${FASTGLTF_DEPS})
target_link_libraries(catos-runtime-static PUBLIC catos-runtime)
target_include_directories(catos-runtime-static PUBLIC src)


#tests
file(GLOB_RECURSE CATOS_RUNTIME_TEST src/tests/*.h src/tests/*.hpp src/tests/*.c src/tests/*.cpp)
add_executable(catos-runtime-tests ${CATOS_RUNTIME_TEST}  ${GLAD_SRC}  "../Thirdparty/stb/stb_image.h")
#???
target_link_libraries(catos-runtime-tests catos-runtime-static doctest)


####
set(RMLUI_BACKEND_PATH ${RmlUi_SOURCE_DIR}/Backends)
add_library(rmlui_backend_SDL_GL3 INTERFACE)
target_sources(rmlui_backend_SDL_GL3 INTERFACE
        ${RMLUI_BACKEND_PATH}/RmlUi_Platform_SDL.cpp
        ${RMLUI_BACKEND_PATH}/RmlUi_Renderer_GL3.cpp
)
target_include_directories(rmlui_backend_SDL_GL3 INTERFACE ${RMLUI_BACKEND_PATH})
target_compile_definitions(rmlui_backend_SDL_GL3 INTERFACE
        RMLUI_SDL_VERSION_MAJOR=3
        RMLUI_NUM_MSAA_SAMPLES=4
        RMLUI_GL3_CUSTOM_LOADER=<glad/glad.h>
)
####



target_link_libraries(catos-runtime-static PUBLIC
        RmlUi::RmlUi
        spdlog
        SDL3::SDL3
        ryml
        doctest
        pocketpy
        rmlui_backend_SDL_GL3
)

target_include_directories(catos-runtime-static PUBLIC
        ${GLAD_INCLUDE}
        ${pocketpy_content_SOURCE_DIR}/include
        ${SDL3_content_SOURCE_DIR}/include
        ${rapidyaml_content_SOURCE_DIR}/src
        "../Thirdparty/stb/"
)


add_test(NAME catos-runtime-tests COMMAND catos-runtime-tests)
