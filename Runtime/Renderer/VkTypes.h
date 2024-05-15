//
// Created by allos on 2/10/2024.
//


/*
 * Purpose of this file for future reference:
 * The entire codebase will include this header, it will provide widely used default structures and includes :)
 */

#pragma once
// Include lib

#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <span>
#include <array>
#include <functional>
#include <deque>


#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>
#include <chrono>

#include <thread>
#include <vulkan/vulkan.h>

#include <vulkan/vk_enum_string_helper.h>
#include <vk_mem_alloc.h>
#include <VkBootstrap.h>

#include <spdlog/spdlog.h>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/common.hpp>


//TODO add documentation


struct EngineStats {
    float frameTime;
    int triangleCount;
    int drawCallCount;
    float sceneUpdateTime;
    float meshDrawTime;
};

struct Bounds {
    glm::vec3 origin;
    float sphereRadius;
    glm::vec3 extents;
};


struct AllocatedBuffer {
    VkBuffer buffer;
    VmaAllocation allocation;
    VmaAllocationInfo info;
};

struct Vertex {
    glm::vec3 position;
    float uv_x;
    glm::vec3 normal;
    float uv_y;
    glm::vec4 color;
};

// Holds the resources for a mesh
struct GPUMeshBuffers {
    AllocatedBuffer indexBuffer;
    AllocatedBuffer vertexBuffer;
    VkDeviceAddress vertexBufferAddress;
};

struct GPUSceneData {
    glm::mat4 view;
    glm::mat4 proj;
    glm::mat4 viewproj;
    glm::vec4 ambientColor;
    glm::vec4 sunLightDirection; // W is for sun power :)
    glm::vec4 sunlightColor;
};

//Push constants for the mesh
struct GPUDrawPushConstants {
    glm::mat4 worldMatrix;
    VkDeviceAddress vertexBuffer;
};


struct MaterialPipeline {
    VkPipeline pipeline;
    VkPipelineLayout layout;
};

enum MaterialPass : uint8_t {
    MainColor,
    Transparent,
    Other
};

struct MaterialInstance {
    MaterialPipeline* pipeline;
    VkDescriptorSet materialSet;
    MaterialPass passType;
};


struct DeletionQueue {
    std::deque<std::function<void()>> deletors;

    void pushFunction(std::function<void()>&& function) {
        deletors.push_back(function);
    }

    void flush() {

        for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
            (*it)();
        }
        deletors.clear();
    }
};

struct AllocatedImage {
    VkImage image;
    VkImageView imageView;
    VmaAllocation allocation;
    VkExtent3D imageExtent;
    VkFormat imageFormat;
};


#define VK_CHECK(x)                                                      \
    do {                                                                 \
        VkResult err = x;                                                \
        if (err != VK_SUCCESS) {                                         \
            spdlog::info("ruh roh");                                                             \
            spdlog::error("Detected Vulkan error at {}: {}", __FILE__, __LINE__); \
            abort();                                                     \
        }                                                          \
    } while (0)
