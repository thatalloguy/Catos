
file(GLOB_RECURSE EDITOR_SRC

        src/catos/Editor/*.cpp
        src/catos/Editor/*.h
)

add_executable(catos-editor
        src/catos/main.cpp ${EDITOR_SRC}

)

target_link_libraries(catos-editor PRIVATE catos-runtime-static)
target_link_libraries(catos-editor PRIVATE catos-headers)