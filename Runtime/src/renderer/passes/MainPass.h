//
// Created by allos on 11/15/2024.
//
#pragma once
#include "renderer/renderPass.h"
#include "stl/vector.h"
#include "glm/vec3.hpp"

namespace catos::renderPasses {

    struct DirectLightUniform {
        glm::vec3 direction;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    struct PointLightUniform {
        glm::vec3 position;

        float constant;
        float linear;
        float quadratic;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    struct SpotLightUniform {
        glm::vec3 position;
        glm::vec3 direction;
        float cutOff;
        float outerCutOff;

        float constant;
        float linear;
        float quadratic;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    struct MainRenderPassLogic: RenderPassLogic {


        glm::vec3* cameraPos;

        MainRenderPassLogic();
        ~MainRenderPassLogic();

        void onPassPrepare(RenderPass& pass) override;
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


