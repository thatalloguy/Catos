//
// Created by allos on 10/16/2024.
//

#include "renderPipeline.h"

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

void catos::RenderPipeline::draw(Matrix4& cameraMat) {

    RenderPass* pass = beginPass;
    RenderPass* previous = nullptr;

    while (pass != nullptr) {


        RenderPassLogic* renderLogic = pass->getRenderPassLogic();
        pass->bindPass();

        if (renderLogic != nullptr) {
            renderLogic->onPassPrepare(*pass, cameraMat);
        }

        if (previous != nullptr)
        {
            pass->getShader().bind();
            pass->getShader().setInt(previous->getName().c_str(), 0);

        }


        glViewport(0, 0, pass->getSize().x, pass->getSize().y);



        for (auto mesh: _meshes) {
            pass->getShader().bind();
            //todo need better way to do this :|
            pass->getShader().setInt("albedo", 1);
            pass->getShader().setTransform("cameraMat", cameraMat.value_ptr());

            if (previous != nullptr) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(previous->getImageType(), previous->getPassTexture());
            }

            if (mesh._texture != nullptr) {
                mesh._texture->bind();
            }


            if (renderLogic != nullptr){
                renderLogic->onMeshPrepare(*pass, mesh);
            }

            mesh.draw(pass->getShader());


            if (renderLogic != nullptr){
                renderLogic->onMeshEnd(*pass, mesh);
            }
        }

        if (renderLogic != nullptr) {
            renderLogic->onPassEnd(*pass);
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

void catos::RenderPipeline::resize(int newWidth, int newHeight){
    RenderPass* pass = beginPass;

    while (pass != nullptr) {

        if (pass->shouldResize()){

            pass->destroyTextures();

            pass->generateFrameBuffer({(float) newWidth,(float) newHeight});
            pass->generateColorBuffer({(float) newWidth,(float) newHeight}, pass->getPassType(), pass->getColorType(), pass->getImageType(), pass->getTexAmount());

            pass->generateRenderBuffer({(float) newWidth,(float) newHeight});


            pass->setSize({(float) newWidth,(float) newHeight});
        }

        pass = pass->getNext();
    }
}
