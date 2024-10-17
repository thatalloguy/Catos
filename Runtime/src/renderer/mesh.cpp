//
// Created by allos on 10/17/2024.
//

#include "mesh.h"

#include <glad/glad.h>

float triangle_vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

catos::Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void catos::Mesh::init(void* raw_mesh, int sizeof_mesh) {

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    // load the vertices into the VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof_mesh, raw_mesh, GL_STATIC_DRAW);

    glVertexAttribPointer(0, sizeof_mesh / (sizeof(float) * 3), GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vertCount = sizeof_mesh / (sizeof(float) * 3);

}

void catos::Mesh::draw() {

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertCount);
    glBindVertexArray(0);

}

catos::TriangleMesh::TriangleMesh() {
    this->init(triangle_vertices, sizeof(triangle_vertices));
}

void catos::TriangleMesh::draw()
{
    Mesh::draw();
}
