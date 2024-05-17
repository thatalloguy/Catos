
file(GLOB_RECURSE EDITOR_SRC

        src/catos/Editor/Editor.cpp
        src/catos/Editor/Editor.h


        src/catos/Editor/World/WorldTreeView.h
        src/catos/Editor/World/WorldTreeView.cpp
)

add_executable(catos-editor
        src/catos/main.cpp ${EDITOR_SRC}

)

target_link_libraries(catos-editor PRIVATE catos-runtime-static)
target_link_libraries(catos-editor PRIVATE catos-headers)