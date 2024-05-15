//
// Created by allo on 2/10/2024.

/*
 * Purpose of this file (for future reference):
 * -This will be the main class for the (render) engine, and where most of the code will go.
 */



#pragma once

#include "VkInitializers.h"
#include "VkTypes.h"
#include "VkDescriptors.h"
#include "VkLoader.h"
#include "Camera.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


struct FrameData {

    VkCommandPool _commandPool;
    VkCommandBuffer _mainCommandBuffer;

    VkSemaphore _swapchainSemaphore, _renderSemaphore;
    VkFence _renderFence;

    DeletionQueue _deletionQueue;
    DescriptorAllocatorGrowable _frameDescriptors;
};


struct ComputePushConstants {
    glm::vec4 data1;
    glm::vec4 data2;
    glm::vec4 data3;
    glm::vec4 data4;
};

struct ComputeEffect {
    const char* name;

    VkPipeline pipeline;
    VkPipelineLayout layout;

    ComputePushConstants data;
};

struct GLTFMetallic_roughness {
    MaterialPipeline opaquePipeline;
    MaterialPipeline transparentPipeline;

    VkDescriptorSetLayout materialLayout;

    struct MaterialConstants {
        glm::vec4 colorFactors;
        glm::vec4 metalRoughFactors;

        //padding we need it for the uniform buffer
        glm::vec4 extra[14];
    };

    struct MaterialResources {
        AllocatedImage colorImage;
        VkSampler colorSampler;
        AllocatedImage metalRoughImage;
        VkSampler metalRoughSampler;
        VkBuffer dataBuffer;
        uint32_t dataBufferOffset;
    };

    DescriptorWriter writer;

    void buildPipelines(VulkanEngine* engine);
    void clearResources(VkDevice device);

    MaterialInstance writeMaterial(VkDevice device, MaterialPass pass, const MaterialResources& resources, DescriptorAllocatorGrowable descriptorAllocator);
    void destroy(VkDevice device, MaterialPass passType);
};


struct RenderObject {
    uint32_t indexCount;
    uint32_t firstIndex;
    VkBuffer indexBuffer;

    MaterialInstance* material;

    Bounds bounds;

    glm::mat4 transform;
    VkDeviceAddress vertexBufferAddress;
};


struct DrawContext {
    std::vector<RenderObject> OpaqueSurfaces;
    std::vector<RenderObject> TransparentSurfaces;
};

struct MeshNode : public Node {

    std::shared_ptr<MeshAsset> mesh;

    virtual void Draw(const glm::mat4& topMatrix, DrawContext& ctx) override;

};

constexpr unsigned int FRAME_OVERLAP = 2;


class VulkanEngine {

    public:


        bool _isInitialized{ false };
        int _frameNumber{0};
        bool _stopRendering{ false };

        VkExtent2D _windowExtent{800, 600};
        GLFWwindow* _window{ nullptr };
        float renderScale = 1.f;
        Camera mainCamera;

        //Vulkan types
        VkInstance _instance;
        VkDebugUtilsMessengerEXT  _debugMessenger;
        VkPhysicalDevice _chosenGPU;
        VkDevice _device;
        VkSurfaceKHR _surface;

        // swapchain
        VkSwapchainKHR _swapchain;
        VkFormat _swapchainImageFormat;

        std::vector<VkImage> _swapchainImages;
        std::vector<VkImageView> _swapchainImageViews;
        VkExtent2D _swapchainExtent;

        // Command stuff idk

        FrameData _frames[FRAME_OVERLAP];

        FrameData& getCurrentFrame() { return _frames[_frameNumber % FRAME_OVERLAP]; };

        VkQueue _graphicsQueue;
        uint32_t _graphicsQueueFamily;


        DeletionQueue _mainDeletionQueue;
        VmaAllocator _allocator;

        // draw resources
        AllocatedImage _drawImage;
        AllocatedImage _depthImage;
        VkExtent2D _drawExtent;

        //Descriptor stuff ;-;
        DescriptorAllocatorGrowable globalDescriptorAllocator;

        VkDescriptorSet _drawImageDescriptors;
        VkDescriptorSetLayout _drawImageDescriptorLayout;

        //Pipeline :)
        VkPipeline _gradientPipeline;
        VkPipelineLayout _gradientPipelineLayout;


        //ImGui impl
        VkFence _immFence;
        VkCommandBuffer _immCommandBuffer;
        VkCommandPool _immCommandPool;

        //textu
        VkDescriptorSetLayout _singleImageDescriptorLayout;

        // misc

        int calledNum = 0;
        bool displayDebugMenu = true;
        EngineStats stats;

        //scene

        DrawContext mainDrawContext;
        GPUSceneData sceneData;

        std::unordered_map<std::string, std::shared_ptr<Node>> loadedNodes;


        VkDescriptorSetLayout _gpuSceneDataDescriptorLayout;

        void immediate_submit(std::function<void(VkCommandBuffer cmd)>&& function);

        AllocatedBuffer createBuffer(size_t allocSize, VkBufferUsageFlags usage, VmaMemoryUsage memoryUsage);
        void  destroyBuffer(const AllocatedBuffer& buffer);

        GPUMeshBuffers uploadMesh(std::span<uint32_t> indices, std::span<Vertex> vertices);

        AllocatedImage createImage(VkExtent3D size, VkFormat format, VkImageUsageFlags usage, bool mipmapped = false);
        AllocatedImage createImage(void* data, VkExtent3D size, VkFormat format, VkImageUsageFlags usage, bool mipmapped = false);

        void destroyImage(const AllocatedImage& img);

        bool isVisible(const RenderObject& obj, const Camera& camera);

        // Life-time functions
        static VulkanEngine& Get();

        void Init(GLFWwindow* renderWindow, bool displayDebugMenu = false);
        void CleanUp();
        void Draw();
        void Run();

        AllocatedImage _blackImage;
        AllocatedImage _greyImage;

        VkSampler _defaultSamplerLinear;
        VkSampler _defaultSamplerNearest;

        MaterialInstance defaultData;
        GLTFMetallic_roughness metalRoughMaterial;


        AllocatedImage _errorImage;

        AllocatedImage _whiteImage;

        std::unordered_map<std::string, std::shared_ptr<LoadedGLTF>> loadedScenes;


        void updateScene();
private:
        void initVulkan();
        void initSwapchain();
        void initCommands();
        void initSyncStructures();

        void drawBackground(VkCommandBuffer cmd);

        // swapchain lifetime functions
        void createSwapchain(uint32_t width, uint32_t height);
        void resizeSwapchain();
        void destroySwapchain();

        void initDescriptors();

        void initPipelines();
        void initBackgroundPipelines();

        void initImGui();
        void drawImgui(VkCommandBuffer cmd, VkImageView targetImageView);



        std::vector<ComputeEffect> backgroundEffects;
        int currentBackgroundEffect{0};

        VkPipelineLayout _trianglePipelineLayout;
        VkPipeline _trianglePipeline;

        void initTrianglePipeline();
        void drawGeometry(VkCommandBuffer cmd);


        std::vector<std::shared_ptr<MeshAsset>> testMeshes;

        VkPipelineLayout _meshPipelineLayout;
        VkPipeline _meshPipeline;

        GPUMeshBuffers rectangle;

        void initMeshPipeline();

        bool resizeRequested = false;


        void initDefaultData();
};


