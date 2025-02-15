#include "drawables/object/Mesh.hpp"

#include <glad/glad.h>
#include <stdexcept>
#include <iostream>

namespace los
{

Mesh::Mesh(std::unique_ptr<ISurface> surface, const std::vector<float> &data)
: mSurface(std::move(surface))
{
    if(data.size() % sTriangleSize != 0) {
        throw std::logic_error("Mesh are in three dimensions");
    }

    glGenVertexArrays(1, &mVAO);
    if(mVAO == 0) {
        throw std::runtime_error("Mesh failed to create VAO");
    }

    glGenBuffers(1, &mVBO);
    if(mVBO == 0) {
        throw std::runtime_error("Mesh failed to create VBO");
    }

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);    

    glVertexAttribPointer(0, sTriangleSize, GL_FLOAT, GL_FALSE, (sTriangleSize) * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if(mSurface) {
        mSurface->initialiseParamPtrAttr(1);
    }

    mNbOfTriangles = data.size() / sTriangleSize;
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}

} // namespace los
