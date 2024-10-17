//
// Created by allos on 10/17/2024.
//

#pragma once

#include <glad/glad.h>

namespace catos {

    struct Vertex {
        float x, y, z;
    };

    struct Mesh
    {
        unsigned int VAO;
        unsigned int VBO;
        int size;

        void draw()
        {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
        }
    };

}


