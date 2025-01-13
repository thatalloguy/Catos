//
// Created by allos on 1/6/2025.
//

#include "stl/vector.h"
#include "ShadowPass.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/detail/type_quat.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




catos::renderPasses::ShadowPassLogic::ShadowPassLogic() {

    glGenBuffers(1, &matricesUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, matricesUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Matrix4) * 8, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, matricesUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    shadowCascadeLevels.reserve(6);
    lightDir = normalize(lightDir);
}

catos::renderPasses::ShadowPassLogic::~ShadowPassLogic() {
    glDeleteBuffers(1, &matricesUBO);
}

void catos::renderPasses::ShadowPassLogic::onPassPrepare(catos::RenderPass &pass, Matrix4& camera) {
    glCullFace(GL_FRONT);
    glBindBuffer(GL_UNIFORM_BUFFER, matricesUBO);
}


void catos::renderPasses::ShadowPassLogic::onMeshPrepare(catos::RenderPass &pass, catos::Mesh &mesh) {
    //pass.getShader().setTransform("cameraMat", shadowView.value_ptr());


}

void catos::renderPasses::ShadowPassLogic::onPassEnd(catos::RenderPass &pass) {


    glCullFace(GL_BACK);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    auto next_pass = pass.getNext();

    if (next_pass != nullptr) {
        next_pass->getShader().bind();
        next_pass->getShader().setInt("cascadeCount", shadowCascadeLevels.length());

        next_pass->getShader().setVector3("lightDir", lightDir);

        next_pass->getShader().setTransform("view", cameraView.value_ptr());

        for (int i=0; i<shadowCascadeLevels.length(); i++) {
            std::string name = "cascadePlaneDistances[" + std::to_string(i) + "]";
            next_pass->getShader().setFloat(name.c_str(), shadowCascadeLevels[i]);
        }
    }

}
void catos::renderPasses::ShadowPassLogic::onMeshEnd(catos::RenderPass &pass, catos::Mesh &mesh) { }

void catos::renderPasses::ShadowPassLogic::setDirection(const Vector3i &vec) {
    lightDir = vec;
}


void catos::renderPasses::ShadowPassLogic::updateCameraInfo(Matrix4 &view, const Vector2 &viewport, float fov,
                                                            float near_plane, float far_plane) {
    cameraView = view;

    lightMatrices.clear();
    shadowCascadeLevels.clear();
    lightMatrices.push_back(calcLightMatrices(20.0f));
    lightMatrices.push_back(calcLightMatrices(40.0f));
    lightMatrices.push_back(calcLightMatrices(60.0f));
    lightMatrices.push_back(calcLightMatrices(80.0f));


    glBindBuffer(GL_UNIFORM_BUFFER, matricesUBO);
    for (size_t i = 0; i < lightMatrices.length(); ++i)
    {
        glBufferSubData(GL_UNIFORM_BUFFER, i * sizeof(Matrix4), sizeof(Matrix4), lightMatrices[i].value_ptr());
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Matrix4 catos::renderPasses::ShadowPassLogic::calcLightMatrices(float distance) {

    Matrix4 shadowCam{};

    shadowCascadeLevels.push_back(distance);

    Vector3 position = origin + (lightDir * distance);

    Matrix4 proj = math::ortho(-distance, distance, -distance, distance, 0.01f, 10000.0f);
    Matrix4 view = math::lookAt(position, origin, {0, 1, 0});

    shadowCam = proj * view;

    return shadowCam;
}
