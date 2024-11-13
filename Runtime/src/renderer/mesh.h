//
// Created by allos on 10/17/2024.
//

#pragma once

#include <glad/glad.h>
#include "spdlog/spdlog.h"
#include "texture.h"

namespace catos {

    struct Vertex {
        float x, y, z;
        float r, g, b;
        float uv_x, uv_y;
    };

    struct MeshCreationInfo {
        void* vertices;
        void* indices;

        int sizeOfVertices;
        int sizeOfIndices;

        int verticesAmount;
        int indicesAmount;
    };

    struct Mesh
    {
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        Texture* _texture = nullptr;

        int size;
        int indicesAmount;

        void init(MeshCreationInfo& meshCreationInfo) {
            //Generate needed buffers
            glGenBuffers(1, &VBO);
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
            // load the vertices into the VAO and VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, meshCreationInfo.sizeOfVertices, meshCreationInfo.vertices, GL_STATIC_DRAW);

            //do the same for indices.
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshCreationInfo.sizeOfIndices, meshCreationInfo.indices, GL_STATIC_DRAW);

            // pos
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            glEnableVertexAttribArray(0);

            // vertex colors
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // tex_coords
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);


            size = meshCreationInfo.verticesAmount;
            indicesAmount = meshCreationInfo.indicesAmount;

        }

        void draw()
        {
            if (_texture != nullptr) {
                _texture->bind();
            }

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indicesAmount, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        void destroy() {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }
    };

}


