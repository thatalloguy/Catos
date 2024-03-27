add_library(catos-runtime INTERFACE)
target_include_directories(catos-runtime INTERFACE include)


#static-lib
file(GLOB_RECURSE CATOS_RUNTIME_SRC src/*.cpp src/*.h src/*.c src/*.hpp)
add_library(catos-runtime-static STATIC ${CATOS_RUNTIME_SRC})
target_link_libraries(catos-runtime-static PUBLIC catos-runtime)
target_include_directories(catos-runtime-static PUBLIC src)

#tests
file(GLOB_RECURSE CATOS_RUNTIME_TEST tests/*.h tests/*.hpp tests/*.c tests/*.cpp)
add_executable(catos-runtime-tests ${CATOS_RUNTIME_TEST})
#???
target_link_libraries(catos-runtime-tests catos-runtime-static doctest)

add_test(NAME catos-runtime-tests COMMAND catos-runtime-tests)