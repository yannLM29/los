#pragma once

#include "ShaderTypes.hpp"
namespace los
{
class Renderer;

class ISurface
{
public:
    virtual eShaderTypes getRequiredShaderType() const = 0;
    virtual bool initialiseParamPtrAttr(unsigned int param_ptr_id) = 0;
    virtual void bind(Renderer &renderer) = 0;
    virtual ~ISurface() = default;
};


} // namespace los
