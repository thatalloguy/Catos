function(configure_catos_project name)
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/projects")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/projects")
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/projects")
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/projects")
endfunction(configure_catos_project name)


function(add_catos_project name)
    file(GLOB_RECURSE ${name}_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

    add_library(${name} SHARED ${${name}_SOURCES} ${${name}_TESTS} ${ARGN})
    configure_catos_project(${name})

    target_include_directories(${name} PUBLIC src)

    target_include_directories(catos-headers INTERFACE src)

    target_link_libraries(${name} PUBLIC catos-runtime)
    target_link_libraries(${name} INTERFACE catos-headers)

endfunction(add_catos_project)