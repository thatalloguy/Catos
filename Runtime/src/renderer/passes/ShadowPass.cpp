//
// Created by allos on 1/6/2025.
//

#include "ShadowPass.h"



catos::renderPasses::ShadowPassLogic::ShadowPassLogic() {}
catos::renderPasses::ShadowPassLogic::~ShadowPassLogic() {}

void catos::renderPasses::ShadowPassLogic::onPassPrepare(RenderPass& pass, Matrix4& camera_matrix) {
    calcShadowMat4();
    glCullFace(GL_FRONT);
}
void catos::renderPasses::ShadowPassLogic::onMeshPrepare(catos::RenderPass &pass, catos::Mesh &mesh) {
    pass.getShader().setTransform("cameraMat", shadowView.value_ptr());
}
void catos::renderPasses::ShadowPassLogic::onPassEnd(catos::RenderPass &pass) {
    glCullFace(GL_BACK);
    auto next_pass = pass.getNext();
    if (next_pass != nullptr) {
        next_pass->getShader().bind();
        next_pass->getShader().setTransform("shadowView", shadowView.value_ptr());
    }
}
void catos::renderPasses::ShadowPassLogic::onMeshEnd(catos::RenderPass &pass, catos::Mesh &mesh) { }
void catos::renderPasses::ShadowPassLogic::calcShadowMat4() {
    Vector3 position = origin + (direction * distance);
    Matrix4 proj = math::ortho(-20, 20, -20, 20, 0.01f, 100.0f);
    Matrix4 view = math::lookAt(position, {0, 0, 0}, {0, 1, 0});
    shadowView = proj * view;
}
void catos::renderPasses::ShadowPassLogic::setDistance(float new_distance) {
    distance = new_distance;
}
void catos::renderPasses::ShadowPassLogic::setOrigin(const Vector3i &vec) {
    origin = (const Vector3&) vec;
}
void catos::renderPasses::ShadowPassLogic::setDirection(const Vector3i &vec) {
    direction = (const Vector3&) vec;
}