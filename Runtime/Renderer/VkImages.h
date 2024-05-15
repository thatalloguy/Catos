//
// Created by allos on 2/10/2024.
//

/*
 * Purpose of this file for future reference:
 * This will contain image related vulkan helpers
 */

#pragma once

#include <vulkan/vulkan.h>

namespace VkUtil {

    void transitionImage(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout);
    void copyImageToImage(VkCommandBuffer cmd, VkImage source, VkImage destination, VkExtent2D srcSize, VkExtent2D dstSize);

    void generateMipMaps(VkCommandBuffer cmd, VkImage image, VkExtent2D imageSize);
}
