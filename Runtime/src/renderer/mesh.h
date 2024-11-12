//
// Created by allos on 10/17/2024.
//

#pragma once

#include <glad/glad.h>
#include "spdlog/spdlog.h"

namespace catos {

    struct Vertex {
        float x, y, z;
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


            glVertexAttribPointer(0, meshCreationInfo.verticesAmount, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            glEnableVertexAttribArray(0);

            size = meshCreationInfo.verticesAmount;
            indicesAmount = meshCreationInfo.indicesAmount;

        }

        void draw()
        {
            glBindVertexArray(VAO);
            glDrawElements(GL_LINE_LOOP, indicesAmount, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        void destroy() {
            //todo
        }
    };

}


