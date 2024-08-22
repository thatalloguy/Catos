//
// Created by allos on 2/10/2024.
//



/*
 * Purpose of this file for future reference:
 * This will contain helpers to create vulkan structures
 */


#pragma once

#include "VkTypes.h"

namespace VkInit {

    VkPresentInfoKHR presentInfo();

    VkCommandPoolCreateInfo commandPoolCreateInfo(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags /*= 0*/);
    VkCommandBufferAllocateInfo commandBufferAllocateInfo(VkCommandPool pool, uint32_t count /*= 1*/);

    VkFenceCreateInfo fenceCreateInfo(VkFenceCreateFlags flags /*= 0*/);
    VkSemaphoreCreateInfo semaphoreCreateInfo(VkSemaphoreCreateFlags flags = 0);

    VkCommandBufferBeginInfo commandBufferBeginInfo(VkCommandBufferUsageFlags flags /*= 0*/);
    VkImageSubresourceRange imageSubresourceRange(VkImageAspectFlags aspectMask);

    VkSemaphoreSubmitInfo semaphoreSubmitInfo(VkPipelineStageFlags2 stageMask, VkSemaphore semaphore);
    VkCommandBufferSubmitInfo commandBufferSubmitInfo(VkCommandBuffer cmd);
    VkSubmitInfo2 submitInfo(VkCommandBufferSubmitInfo* cmd, VkSemaphoreSubmitInfo* signalSemaphoreInfo, VkSemaphoreSubmitInfo* waitSemaphoreInfo);

    VkImageCreateInfo imageCreateInfo(VkFormat format, VkImageUsageFlags usageFlags, VkExtent3D extent);
    VkImageViewCreateInfo imageViewCreateInfo(VkFormat format, VkImage image, VkImageAspectFlags  aspectFlags);

    VkRenderingAttachmentInfo attachmentInfo(VkImageView view, VkClearValue* clear, VkImageLayout layout);
    VkRenderingAttachmentInfo depthAttachmentInfo(VkImageView view, VkImageLayout layout);

    ///NOTE custom function i couldnt find vkguide's one.
    VkRenderingInfo renderingInfo(VkExtent2D renderExtent, VkRenderingAttachmentInfo* colorAttachment,
                                  VkRenderingAttachmentInfo* depthAttachment);

    VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo(VkShaderStageFlagBits stage, VkShaderModule shaderModule, const char * entry = "main");

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo();

}

