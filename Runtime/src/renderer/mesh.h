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

    struct Mesh
    {
        unsigned int VAO;
        unsigned int VBO;
        int size;

        void init(float* vertices, int bufferSize, int vertAmount) {

            glGenBuffers(1, &VBO);
            glGenVertexArrays(1, &VAO);

            glBindVertexArray(VAO);
            // load the vertices into the VAO and VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, vertAmount, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            glEnableVertexAttribArray(0);

            size = vertAmount;

        }

        void draw()
        {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
        }
    };

}


