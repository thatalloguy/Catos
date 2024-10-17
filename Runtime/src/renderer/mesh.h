//
// Created by allos on 10/17/2024.
//

#pragma once

namespace catos {

    struct Vertex {
        float x, y, z;
    };

    class Mesh {
    public:

        Mesh() = default;
        ~Mesh();

        void init(void* raw_mesh, int sizeof_mesh);

        void draw();

    protected:
        unsigned int VAO;
        unsigned int VBO;

        int vertCount = 0;

    };

    class TriangleMesh: Mesh {

    public:

        TriangleMesh();
        ~TriangleMesh() = default;

        void draw();


    };

}


