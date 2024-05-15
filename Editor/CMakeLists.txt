add_executable(catos-editor
        src/catos/main.cpp
)

target_link_libraries(catos-player PRIVATE catos-runtime-static)
target_link_libraries(catos-player PRIVATE catos-headers)