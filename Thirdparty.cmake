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

if(NOT TARGET Freetype::Freetype)
    FetchContent_Declare(
            freetype
            GIT_REPOSITORY https://github.com/freetype/freetype.git
            GIT_TAG VER-2-13-0
    )

    #Freetype options straight from my a##
    set(FT_DISABLE_ZLIB ON CACHE BOOL "" FORCE)
    set(FT_DISABLE_BZIP2 ON CACHE BOOL "" FORCE)
    set(FT_DISABLE_PNG ON CACHE BOOL "" FORCE)
    set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)
    set(FT_DISABLE_BROTLI ON CACHE BOOL "" FORCE)

    # Make FreeType available
    FetchContent_MakeAvailable(freetype)

    add_library(Freetype::Freetype ALIAS freetype)
endif()


if (NOT TARGET RmlUi)

    FetchContent_Declare(
            RmlUi_content
            GIT_REPOSITORY https://github.com/mikke89/RmlUi.git
            GIT_TAG 58c751531f4c1a1eb2dc56f409b8e8a323a0c9ad
    )
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
    set(NO_FONT_INTERFACE_DEFAULT OFF CACHE BOOL "" FORCE)

    set(FREETYPE_DIR "${freetype_SOURCE_DIR}" CACHE PATH "" FORCE)


    FetchContent_MakeAvailable(RmlUi_content)
endif()

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
