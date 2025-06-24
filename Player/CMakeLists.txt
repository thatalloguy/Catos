file(GLOB_RECURSE PLAYER_SRC
        src/catos/*.h
        src/catos/*.cpp
)
add_executable(catos-player
        src/main.cpp
        ${PLAYER_SRC}
)

target_link_libraries(catos-player PRIVATE catos-runtime-static)
target_link_libraries(catos-player PRIVATE catos-headers)
