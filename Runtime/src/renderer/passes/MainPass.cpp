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

    passShader.setVector3("lightColor", {1, 1, 1});
    passShader.setVector3("lightPos", {0, 5, 3});
    passShader.setVector3("viewPos", {cameraPos->x, cameraPos->y, cameraPos->z});

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
