//
// Created by allos on 10/16/2024.
//

#pragma once

#include <stl/vector.h>

#include <renderer/renderPass.h>

#include "mesh.h"
#include "renderer.h"

namespace catos {

    enum class RenderPipelineStatus: unsigned int {
        SUCCESS = 0,
        INVALID_REQUIREMENTS = 1,
        UNKNOWN_MESH = 2,
        ID_ALREADY_USED = 3,
        PASS_ALREADY_EXISTS = 4,
        UNKNOWN_PASS = 5,
    };

    class RenderPipeline {

    public:
        RenderPipeline();
        ~RenderPipeline();

        RenderPipelineStatus setBeginPass(RenderPass& pass);

        RenderPipelineStatus addMesh(Mesh& mesh);

        void draw(Matrix4& camera);

        void resize(int newWidth, int newHeight);


    private:

        Renderer& _renderer;

        RenderPass* beginPass;
        vector<Mesh> _meshes;

    };

}
