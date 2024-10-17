//
// Created by allos on 10/16/2024.
//

#pragma once

#include <stl/string.h>
#include <stl/vector.h>
#include <stl/hashmap.h>

#include <renderer/renderPass.h>

namespace catos {

    struct PipelineCreationInfo {

    };

    class RenderPipeline {

    public:
        RenderPipeline(PipelineCreationInfo& creationInfo);
        ~RenderPipeline();

        void addRenderPass(string&& name, RenderPass& pass, vector<string> requirements);
        void removePass(string&& name);


    private:
    };

}
