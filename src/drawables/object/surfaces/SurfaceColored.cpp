#include "drawables/object/surfaces/SurfaceColored.hpp"

#include <glad/glad.h>

namespace los
{

SurfaceColored::SurfaceColored(const std::vector<glm::vec3> &color_data) {

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);       // not sure

    glBufferData(GL_ARRAY_BUFFER, color_data.size() * sColorSize * sizeof(float), color_data.data(), GL_STATIC_DRAW);    

}

SurfaceColored::SurfaceColored(const std::vector<float> &color_data) {

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);       // not sure

    glBufferData(GL_ARRAY_BUFFER, color_data.size() * sizeof(float), color_data.data(), GL_STATIC_DRAW);    

}

bool SurfaceColored::initialiseParamPtrAttr(unsigned int param_ptr_id) {
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(param_ptr_id, sColorSize, GL_FLOAT, GL_FALSE, (sColorSize) * sizeof(float), (void*)0);
    glEnableVertexAttribArray(param_ptr_id);
    return true;
}

} // namespace los
