//
// Created by allos on 1/18/2025.
//
#pragma once

#include <filesystem>
#include "mesh.h"

namespace catos {


    struct RawMesh {

        unsigned int draws_buffer = 0;

        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;


        unsigned int count = 0;
        unsigned int indices_count = 0;


        catos::vector<unsigned int> indices{};
        catos::vector<catos::Vertex> vertices{};
    };


    struct LoadedMesh {


        Texture* _texture = nullptr;

        Texture* tex;
        float* transform;

        catos::vector<RawMesh> meshes;

        void draw(Shader& shader) {

        }


        void destroy() {
        }



        ~LoadedMesh() {
            destroy();
        }
    };


};