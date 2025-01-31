#pragma once

#include "ShaderTypes.hpp"
namespace los
{

class ISurface
{
public:
    virtual eShaderTypes getRequiredShaderType() const = 0;
    virtual unsigned int getVBOLength() const = 0;
    virtual bool initialiseParamPtrAttr(unsigned int param_ptr_id) = 0;
    virtual ~ISurface() = default;
};


} // namespace los
