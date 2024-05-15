//
// Created by allos on 2/10/2024.
//


/*
 * Purpose of this file for future reference:
 * Will contain GLTF loading logic
 */

#pragma once

#include "VkTypes.h"
#include "VkDescriptors.h"
#include <unordered_map>
#include <filesystem>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <fastgltf/glm_element_traits.hpp>
#include <fastgltf/tools.hpp>
#include <fastgltf/core.hpp>
#include <fastgltf/util.hpp>


class VulkanEngine;


struct DrawContext;

class IRenderable {
    ///TODO define DrawContext
    virtual void Draw(const glm::mat4& topMatrix, DrawContext& ctx) = 0;
};



struct GLTFMaterial {
    MaterialInstance data;
};

struct GeoSurface {
    uint32_t startIndex;
    uint32_t count;
    Bounds bounds;
    std::shared_ptr<GLTFMaterial> material;
};


struct MeshAsset {
    std::string name;

    std::vector<GeoSurface> surfaces;
    GPUMeshBuffers meshBuffers;
};





struct Node : public IRenderable {

    std::weak_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> childern;

    glm::mat4 localTransform;
    glm::mat4 worldTransform;

    void refreshTransform(const glm::mat4& parentMatrix) {
        worldTransform = parentMatrix * localTransform;
        for (auto c : childern) {
            c->refreshTransform(worldTransform);
        }
    }

    virtual void Draw (const glm::mat4& topMatrix, DrawContext& ctx) {

        for (auto& c : childern) {
            c->Draw(topMatrix, ctx);
        }
    }
};



struct LoadedGLTF : public IRenderable {

    //storage for all the data of a GLTF file
    std::unordered_map<std::string, std::shared_ptr<MeshAsset>> meshes;
    std::unordered_map<std::string, std::shared_ptr<Node>> nodes;
    std::unordered_map<std::string, AllocatedImage> images;
    std::unordered_map<std::string, std::shared_ptr<GLTFMaterial>> materials;

    //nodes that dont have a parent
    std::vector<std::shared_ptr<Node>> topNodes;

    std::vector<VkSampler> samplers;

    DescriptorAllocatorGrowable descriptorPool;

    AllocatedBuffer materialDataBuffer;

    VulkanEngine* creator;

    //// Do this manual instead :)
    ///~LoadedGLTF() { clearAll(); };

    virtual void Draw(const glm::mat4& topMatrix, DrawContext& ctx);

    void clearAll();
};


namespace VkLoader {

    std::optional<std::vector<std::shared_ptr<MeshAsset>>> loadGltfMeshes(VulkanEngine *engine, std::filesystem::path filePath);
    std::optional<std::shared_ptr<LoadedGLTF>> loadGltf(VulkanEngine *engine, std::string_view filePath);
    VkFilter extractFilter(fastgltf::Filter filter);
    VkSamplerMipmapMode extractMipmapMode(fastgltf::Filter filter);

    std::optional<AllocatedImage> loadImage(VulkanEngine* engine, fastgltf::Asset& asset, fastgltf::Image& image);
}
