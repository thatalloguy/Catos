//
// Created by allos on 10/16/2024.
//

#include "renderPipeline.h"

#include "spdlog/spdlog.h"

catos::RenderPipeline::RenderPipeline() : _renderer(Renderer::getInstance()) {
}

catos::RenderPipeline::~RenderPipeline() {
}

catos::RenderPipelineStatus catos::RenderPipeline::setBeginPass(RenderPass& pass) {
    beginPass = &pass;

    return RenderPipelineStatus::SUCCESS;
}


catos::RenderPipelineStatus catos::RenderPipeline::addMesh(Mesh& mesh) {
    _meshes.push_back(mesh);

    return RenderPipelineStatus::SUCCESS;
}

void catos::RenderPipeline::draw() {

    RenderPass* pass = beginPass;
    RenderPass* previous = nullptr;
    string& passName = beginPass->getName();

    while (pass != nullptr) {


        pass->bindPass();

        if (previous != nullptr)
        {
            pass->getShader().setInt(previous->getName().c_str(), 0);


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, previous->getPassTexture());
        }


        glViewport(0, 0, pass->getSize().x, pass->getSize().y);

        for (auto mesh: _meshes) {
            mesh.draw();
        }


        pass->unbindPass();


        if (pass->isFinal()) {

            _renderer.renderPassToScreen(*pass);
            break;
        }

        previous = pass;
        pass = pass->getNext();
    }






}
