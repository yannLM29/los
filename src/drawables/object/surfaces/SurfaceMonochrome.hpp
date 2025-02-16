#pragma once

#include "drawables/object/surfaces/ISurface.hpp"
#include "glm/glm.hpp"

namespace los
{

class SurfaceMonochrome : public ISurface
{
private:
    glm::vec3 mColor;

public:
    SurfaceMonochrome(const glm::vec3 &color);

    eShaderTypes getRequiredShaderType() const override {
        return eShaderTypes::kMonochrome;
    };

    bool initialiseParamPtrAttr(unsigned int param_ptr_id) override {
        return true;
    }

    void bind(Renderer &renderer) override;
};


} // namespace los
