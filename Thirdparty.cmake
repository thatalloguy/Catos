## We need the following libs:
#    - Pocketpy v2.0.6
#    - Doctest v2.4.11
#    - fastgltf v0.7.2
#    - GLAD
#    - GLFW v3.5.0
#    - SDL 3
#    - IMGUI
#    - RAPIDYAML v0.8.0
#    - spdlog v1.15.1
#    - stb_image

if (NOT TARGET doctest)
    FetchContent_Declare(
            doctest_content
            GIT_REPOSITORY https://github.com/doctest/doctest.git
            GIT_TAG v2.4.11
    )
    FetchContent_MakeAvailable(doctest_content)
endif ()


if (NOT TARGET glad)
    FetchContent_Declare(
            glad_content
            GIT_REPOSITORY https://github.com/Dav1dde/glad.git
            GIT_TAG c
    )

    FetchContent_MakeAvailable(glad_content)

    set(GLAD_SRC
        ${glad_content_SOURCE_DIR}/include/
    )

endif()


if (NOT TARGET rapidyaml)

    FetchContent_Declare(
            rapidyaml_content
            GIT_REPOSITORY https://github.com/biojppm/rapidyaml.git
            GIT_TAG v0.8.0
    )

    FetchContent_MakeAvailable(rapidyaml_content)
endif()


if (NOT TARGET pocketpy)

    FetchContent_Declare(
            pocketpy_content
            GIT_REPOSITORY https://github.com/pocketpy/pocketpy.git
            GIT_TAG v2.0.6
    )

    FetchContent_MakeAvailable(pocketpy_content)
endif()

#
#if (NOT TARGET glfw)
#
#    FetchContent_Declare(
#            glfw_content
#            GIT_REPOSITORY https://github.com/glfw/glfw.git
#            GIT_TAG 3.4
#    )
#
#    FetchContent_MakeAvailable(glfw_content)
#
#endif()

if (NOT TARGET SDL3::SDL3-static)
    set(SDL_STATIC ON)
    set(SDL_SHARED OFF)

    FetchContent_Declare(
            SDL_content
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG cacac6cc341d5856d1857bdcf7390551eed54865
    )
    FetchContent_MakeAvailable(SDL_content)
endif ()


if (NOT TARGET spdlog)

    FetchContent_Declare(
            spdlog_content
            GIT_REPOSITORY https://github.com/gabime/spdlog.git
            GIT_TAG v1.15.1
    )

    FetchContent_MakeAvailable(spdlog_content)

endif()

if (NOT TARGET imgui)
    FetchContent_Declare(
            imgui_content
            GIT_REPOSITORY https://github.com/ocornut/imgui.git
            GIT_TAG docking
    )
    FetchContent_MakeAvailable(imgui_content)

    set(IMGUI_SOURCE
            ${imgui_content_SOURCE_DIR}/imconfig.h
            ${imgui_content_SOURCE_DIR}/imgui.cpp
            ${imgui_content_SOURCE_DIR}/imgui.h
            ${imgui_content_SOURCE_DIR}/imgui_demo.cpp
            ${imgui_content_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_content_SOURCE_DIR}/imgui_internal.h
            ${imgui_content_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_content_SOURCE_DIR}/imgui_widgets.cpp
    )

    set(IMGUI_SOURCE_BACKEND
            ${imgui_content_SOURCE_DIR}/backends/imgui_impl_opengl3.h
            ${imgui_content_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )

endif ()
