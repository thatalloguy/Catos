//
// Created by allos on 11/15/2024.
//
#include "MainPass.h"

catos::renderPasses::MainRenderPassLogic::MainRenderPassLogic() {
    _directLights.reserve(1);
    _pointLights.reserve(5);
    _spotLights.reserve(3);
}

catos::renderPasses::MainRenderPassLogic::~MainRenderPassLogic() {

}

void catos::renderPasses::MainRenderPassLogic::onPassPrepare(RenderPass& pass) {

}

void catos::renderPasses::MainRenderPassLogic::onPassEnd(RenderPass& pass) {

}

void catos::renderPasses::MainRenderPassLogic::onMeshPrepare(RenderPass& pass, Mesh& mesh) {

    Shader& passShader = pass.getShader();

    static Vector3 lightColor{1, 1, 1};
    static Vector3 lightPos{0, 5, 3};
    static Vector3 viewPos{cameraPos->x, cameraPos->y, cameraPos->z};

    passShader.setVector3("lightColor", lightColor);
    passShader.setVector3("lightPos", lightPos);
    passShader.setVector3("viewPos", viewPos);

}

void catos::renderPasses::MainRenderPassLogic::onMeshEnd(RenderPass& pass, Mesh& mesh) {

}

void catos::renderPasses::MainRenderPassLogic::addDirectLight(DirectLightUniform& light) {
    _directLights.push_back(light);
}

void catos::renderPasses::MainRenderPassLogic::addPointLight(PointLightUniform& light) {
    _pointLights.push_back(light);
}

void catos::renderPasses::MainRenderPassLogic::addSpotLight(SpotLightUniform& light) {
    _spotLights.push_back(light);
}
