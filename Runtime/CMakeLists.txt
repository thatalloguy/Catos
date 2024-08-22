add_library(catos-runtime INTERFACE)
target_include_directories(catos-runtime INTERFACE include)

find_package(Vulkan REQUIRED)



#static-lib
file(GLOB_RECURSE FASTGLTF_DEPS
        Thirdparty/fastgltf/deps/simdjson/simdjson.h
        Thirdparty/fastgltf/deps/simdjson/simdjson.cpp
)
file(GLOB_RECURSE CATOS_RUNTIME_SRC

        src/core/*.cpp
        src/core/*.h

        src/math/*.h
        src/math/*.cpp

        src/Renderer/*.cpp
        src/Renderer/*.h

        src/tests/*.cpp

        src/world/*.h
        src/world/*.cpp

)
add_library(catos-runtime-static STATIC ${CATOS_RUNTIME_SRC}  ${IMGUI_SOURCE} ${FASTGLTF_DEPS})
target_link_libraries(catos-runtime-static PUBLIC catos-runtime)
target_include_directories(catos-runtime-static PUBLIC src)




target_include_directories(catos-runtime-static PUBLIC "Thirdparty/imgui")
target_include_directories(catos-runtime-static PUBLIC "Thirdparty/stb")
target_include_directories(catos-runtime-static PUBLIC "Thirdparty/glm")
target_include_directories(catos-runtime-static PUBLIC "Thirdparty/glfw/include")
target_include_directories(catos-runtime-static PUBLIC "Thirdparty/vk-bootstrap")
target_include_directories(catos-runtime-static PUBLIC "Thirdparty/VulkanMemoryAllocator")

#tests
file(GLOB_RECURSE CATOS_RUNTIME_TEST src/tests/*.h src/tests/*.hpp src/tests/*.c src/tests/*.cpp)
add_executable(catos-runtime-tests ${CATOS_RUNTIME_TEST})
#???
target_link_libraries(catos-runtime-tests catos-runtime-static doctest)
target_link_libraries(catos-runtime-static PUBLIC dwmapi)



target_link_libraries(catos-runtime-static PUBLIC vk-bootstrap::vk-bootstrap)
target_link_libraries(catos-runtime-static PUBLIC GPUOpen::VulkanMemoryAllocator)
target_link_libraries(catos-runtime-static PUBLIC spdlog)
target_link_libraries(catos-runtime-static PUBLIC fastgltf)
target_link_libraries(catos-runtime-static PUBLIC glfw Vulkan::Vulkan)




add_test(NAME catos-runtime-tests COMMAND catos-runtime-tests)