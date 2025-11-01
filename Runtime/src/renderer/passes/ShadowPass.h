//
// Created by allos on 1/6/2025.
//


#include "renderer/renderPass.h"


namespace catos::renderPasses {


    struct ShadowPassLogic: RenderPassLogic {
        ShadowPassLogic();
        ~ShadowPassLogic();

        void onPassPrepare(RenderPass& pass, Matrix4& camera_matrix) override;
        void onPassEnd(RenderPass& pass) override;
        void onMeshPrepare(RenderPass& pass, Mesh& mesh) override;
        void onMeshEnd(RenderPass& pass, Mesh& mesh) override;
        void setDistance(float new_distance);
        void setOrigin(const Vector3i& vec);
        void setDirection(const Vector3i& vec);
    private:
        float distance = 0.0f;
        math::Vector3 origin{0, 0, 0};
        math::Vector3 direction{0, 0, 0};
        math::Matrix4 shadowView{};
        void calcShadowMat4();
    };


}