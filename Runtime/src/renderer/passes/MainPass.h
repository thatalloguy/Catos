//
// Created by allos on 11/15/2024.
//
#pragma once

#include "renderer/renderPass.h"
#include "stl/vector.h"

namespace catos::renderPasses {

    struct DirectLightUniform {
        math::Vector3i direction;

        math::Vector3i ambient;
        math::Vector3i diffuse;
        math::Vector3i specular;
    };

    struct PointLightUniform {
        math::Vector3i position;

        float constant;
        float linear;
        float quadratic;

        math::Vector3i ambient;
        math::Vector3i diffuse;
        math::Vector3i specular;
    };

    struct SpotLightUniform {
        math::Vector3i position;
        math::Vector3i direction;
        float cutOff;
        float outerCutOff;

        float constant;
        float linear;
        float quadratic;

        math::Vector3i ambient;
        math::Vector3i diffuse;
        math::Vector3i specular;
    };

    struct MainRenderPassLogic: RenderPassLogic {


        math::Vector3* cameraPos;

        MainRenderPassLogic();
        ~MainRenderPassLogic();

        void onPassPrepare(RenderPass& pass, Matrix4& camera) override;
        void onPassEnd(RenderPass& pass) override;


        void onMeshPrepare(RenderPass& pass, Mesh& mesh) override;
        void onMeshEnd(RenderPass& pass, Mesh& mesh) override;

        void addDirectLight(DirectLightUniform& light);
        void addPointLight(PointLightUniform& light);
        void addSpotLight(SpotLightUniform& light);

    private:

        catos::vector<DirectLightUniform> _directLights;
        catos::vector<PointLightUniform> _pointLights;
        catos::vector<SpotLightUniform> _spotLights;


    };



}


