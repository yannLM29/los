#include "drawables/object/surfaces/SurfaceTextured.hpp"
#include "drawables/object/Mesh.hpp"
#include "drawables/object/Image.hpp"

namespace los
{

SurfaceTextured::SurfaceTextured(const std::vector<float> texture_mapping_data, std::shared_ptr<Image> image)
: mImage(image)
{
    if(texture_mapping_data.size() % sTextureMappingSize != 0) {
        throw std::logic_error("Texture mapping are in two dimensions");
    }

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);       // not sure

    glBufferData(GL_ARRAY_BUFFER, texture_mapping_data.size() * sizeof(float), texture_mapping_data.data(), GL_STATIC_DRAW);    
}

bool SurfaceTextured::initialiseParamPtrAttr(unsigned int param_ptr_id) {
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(param_ptr_id, sTextureMappingSize, GL_FLOAT, GL_FALSE, (sTextureMappingSize) * sizeof(float), (void*)0);
    glEnableVertexAttribArray(param_ptr_id);

    return true;
}

SurfaceTextured::~SurfaceTextured() {
    glDeleteBuffers(1, &mVBO);
}

void SurfaceTextured::bind(Renderer &renderer) {
    if(mImage) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mImage->getImage());
    }
}

} // namespace los
