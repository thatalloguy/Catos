//
// Created by allos on 4/23/2024.
//

#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/detail/type_quat.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>

glm::mat4 Camera::getViewMatrix() {
    glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.f), position);
    glm::mat4 cameraRotation = getRotationMatrix();
    return glm::inverse(cameraTranslation * cameraRotation);
}

glm::mat4 Camera::getRotationMatrix() {

    //TODO missing Roll

    glm::quat pitchRotation = glm::angleAxis(pitch, glm::vec3 { -1.f, 0.f, 0.f });
    glm::quat yawRotation = glm::angleAxis(yaw, glm::vec3 { 0.f, -1.f, 0.f });

    return glm::toMat4(yawRotation) * glm::toMat4(pitchRotation);
}

void Camera::processEvent(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { velocity.z = -1; } //else { velocity.z = 0;}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { velocity.z =  1; } //else { velocity.z = 0;}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { velocity.x = -1; } //else { velocity.x = 0;}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { velocity.x =  1; } //else { velocity.x = 0;}

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    //yaw += (float) (xPos - lastX) / 1000.0f;
    //pitch -= (float) (yPos - lastY) / 1000.0f;
    lastX = xPos;
    lastY = yPos;
}

void Camera::update() {
    glm::mat4 cameraRotation = getRotationMatrix();
    position += glm::vec3(cameraRotation * glm::vec4(velocity * 0.5f, 0.f));
    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;
}
