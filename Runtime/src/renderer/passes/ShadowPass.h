//
// Created by allos on 1/6/2025.
//


#include "renderer/renderPass.h"

#include <glm/mat4x4.hpp>

namespace catos::renderPasses {


    struct ShadowPassLogic: RenderPassLogic {

        ShadowPassLogic();
        ~ShadowPassLogic() override;

        void updateCameraInfo(Matrix4& view, const Vector2& viewport, float fov, float near_plane, float far_plane);
        void setDirection(const Vector3i& vec);

        void onPassPrepare(RenderPass& pass, Matrix4& camera) override;
        void onPassEnd(RenderPass& pass) override;
        void onMeshPrepare(RenderPass& pass, Mesh& mesh) override;
        void onMeshEnd(RenderPass& pass, Mesh& mesh) override;


    private:
        unsigned int matricesUBO;

        Vector3 lightDir{20.0f, 50.0f, 0.0f};
        Vector3 origin{0.0f, 0.0f, 0.0f};
        catos::vector<float> shadowCascadeLevels;
        catos::vector<Matrix4> lightMatrices;
        Matrix4 cameraView{};

        Matrix4 calcLightMatrices(float distance);

    };

}