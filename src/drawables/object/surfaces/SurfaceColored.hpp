#pragma once

#include "drawables/object/surfaces/ISurface.hpp"

#include <vector>
#include <glm/glm.hpp>

namespace los
{

class SurfaceColored : public ISurface
{
private:
    unsigned int mVBO;

    inline static const unsigned int sColorSize = 3;
public:
    SurfaceColored(const std::vector<glm::vec3> &color_data);
    SurfaceColored(const std::vector<float> &color_data);

    eShaderTypes getRequiredShaderType() const override {
        return eShaderTypes::kColored;
    };
    
    bool initialiseParamPtrAttr(unsigned int param_ptr_id) override;
    
    void bind(Renderer &renderer) {
        
    }
};
    
} // namespace los
