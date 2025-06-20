
file(GLOB_RECURSE EDITOR_SRC

        src/catos/Editor/*.h
        src/catos/Editor/*.cpp

        src/catos/Windows/*.h
        src/catos/Windows/*.cpp

        ${IMGUI_SOURCE}
        ${IMGUI_SOURCE_BACKEND}
)

add_executable(catos-editor
        src/catos/main.cpp ${EDITOR_SRC}

)
target_include_directories(catos-editor PUBLIC ${imgui_content_SOURCE_DIR})



target_link_libraries(catos-editor PRIVATE catos-runtime-static)
target_link_libraries(catos-editor PRIVATE catos-headers)