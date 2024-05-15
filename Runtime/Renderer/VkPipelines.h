//
// Created by allos on 2/10/2024.
//


/*
 * Purpose of this file for future reference:
 * Will contain abstractions for pipelines
 */


#pragma once
#ifndef ATOMUSVULKAN_VKPIPELINES_H
#define ATOMUSVULKAN_VKPIPELINES_H


#include <fstream>
#include "VkInitializers.h"


namespace VkUtil {
    bool loadShaderModule(const char* filePath,
                          VkDevice device,
                          VkShaderModule* outShaderModule);
}

class PipelineBuilder {

public:
    std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;

    VkPipelineInputAssemblyStateCreateInfo _inputAssembly;
    VkPipelineRasterizationStateCreateInfo _rasterizer;
    VkPipelineColorBlendAttachmentState  _colorBlendAttachment;
    VkPipelineMultisampleStateCreateInfo _multisampling;
    VkPipelineLayout _pipelineLayout;
    VkPipelineDepthStencilStateCreateInfo _depthStencil;
    VkPipelineRenderingCreateInfo _renderInfo;
    VkFormat _colorAttachmentformat;

    PipelineBuilder(){ clear(); };

    void clear();

    void setShaders(VkShaderModule vertexShader, VkShaderModule fragmentShader);
    void setInputToplogy(VkPrimitiveTopology topology);
    void setPolygonMode(VkPolygonMode mode);
    void setCullMode(VkCullModeFlags cullMode, VkFrontFace frontFace);
    void setMultisamplingNone();
    void disableBlending();
    void setColorAttachmentFormat(VkFormat format);
    void setDepthFormat(VkFormat format);
    void disableDepthtest();
    void enableDepthtest(bool depthWriteEnable, VkCompareOp op);
    void enableBlendingAdditive();
    void enableBlendingAlphablend();

    VkPipeline buildPipeline(VkDevice device);

};


#endif //ATOMUSVULKAN_VKPIPELINES_H
