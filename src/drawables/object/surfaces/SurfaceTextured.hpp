#pragma once

#include <vector>
#include <stdexcept>
#include <glad/glad.h>
#include <memory>
#include "drawables/object/surfaces/ISurface.hpp"

namespace los
{

class Image;
class SurfaceTextured : public ISurface
{
private:
    unsigned int mVBO;
    std::shared_ptr<Image> mImage; 

    inline static unsigned int sTextureMappingSize = 2;
public:
    SurfaceTextured(const std::vector<float> texture_mapping_data, std::shared_ptr<Image> image);
    ~SurfaceTextured();

    eShaderTypes getRequiredShaderType() const override {
        return eShaderTypes::kTextured;
    }

    void bind(Renderer &renderer) override;

    bool initialiseParamPtrAttr(unsigned int param_ptr_id) override;
};


} // namespace los
