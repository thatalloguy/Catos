## We need the following libs:
#    - Pocketpy v2.0.6
#    - Doctest v2.4.11
#    - fastgltf v0.7.2
#    - GLAD
#    - GLFW v3.5.0
#    - SDL 3
#    - RAPIDYAML v0.8.0
#    - spdlog v1.15.1
#    - stb_image
#    - RmlUI 6.1

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
        ${glad_content_SOURCE_DIR}/src/glad.c
    )


    set(GLAD_INCLUDE
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

if (NOT TARGET SDL3::SDL3)
    set(SDL_SHARED ON)

    FetchContent_Declare(
            SDL_content
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-3.2.14
    )
    FetchContent_MakeAvailable(SDL_content)


endif ()

if (NOT TARGET SDL3_image::SDL3_image)
    set(SDLIMAGE_VENDORED ON)
    set(SDLIMAGE_AVIF OFF)	# disable formats we don't use to make the build faster and smaller.
    set(SDLIMAGE_BMP OFF)
    set(SDLIMAGE_JPEG OFF)
    set(SDLIMAGE_WEBP OFF)

    FetchContent_Declare(
            SDL_Image_content
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG release-3.2.4
    )
    FetchContent_MakeAvailable(SDL_Image_content)


endif ()



if (NOT TARGET spdlog)

    FetchContent_Declare(
            spdlog_content
            GIT_REPOSITORY https://github.com/gabime/spdlog.git
            GIT_TAG v1.15.1
    )

    FetchContent_MakeAvailable(spdlog_content)

endif()
