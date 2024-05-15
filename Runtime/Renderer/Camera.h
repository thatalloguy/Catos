//
// Created by allos on 4/23/2024.
//
#pragma once
#include "VkTypes.h"


class Camera {
public:
    glm::vec3 velocity{0, 0, 0};
    glm::vec3 position{0, 0, 0};

    //vertical rotation / y
    float pitch { 0.f };
    // horizontal rotation / x
    float yaw { 0.f };
    // z //TODO impl this
    float roll{0.f};

    float fov{ 90.f};
    float near{-0.9f};
    float far{0.9f};

    glm::mat4 getViewMatrix();
    glm::mat4 getRotationMatrix();

    ///TODO remove this, its just a dummy
    void processEvent(GLFWwindow* window);

    void update();

private:


    double lastY = 0;
    double lastX = 0;
};

