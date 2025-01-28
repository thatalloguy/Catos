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
        float* transform;

        catos::vector<RawMesh> meshes;

        void draw(Shader& shader) {
            shader.bind();
            shader.setTransform("transform", transform);


            for (auto mesh: meshes) {

                glBindVertexArray(mesh.VAO);
                glDrawElements(GL_TRIANGLES, mesh.indices_count, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);

            }

        }


        void destroy() {

            for (auto mesh : meshes) {
                glDeleteVertexArrays(1, &mesh.VAO);
                glDeleteBuffers(1, &mesh.VBO);
                glDeleteBuffers(1, &mesh.EBO);
            }

        }



        ~LoadedMesh() {
            destroy();
        }
    };

    namespace loaders {

        bool loadGLTF(std::filesystem::path filePath, LoadedMesh* out);
    }
};

