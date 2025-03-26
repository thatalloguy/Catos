
add_executable(catos-player
        src/catos/main.cpp
)

target_link_libraries(catos-player PRIVATE catos-runtime-static)
target_link_libraries(catos-player PRIVATE catos-headers)
