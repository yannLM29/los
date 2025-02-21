#pragma once

#include "ShaderTypes.hpp"
namespace los
{
class Renderer;

/**
 * Surface is attached to a mesh, it handles the look of the surface 
 * and use a shader program handled by the renderer
 */
class ISurface
{
public:
    /**
     * @return eShaderTypes The program shader needed by this surface to be displayed
     */
    virtual eShaderTypes getRequiredShaderType() const = 0;

    /**
     * @brief This methods is responsible to configure the openGL attribute pointer
     * @param param_ptr_id Id choosen by the mesh for the attribute pointer of this surface
     */
    virtual bool initialiseParamPtrAttr(unsigned int param_ptr_id) = 0;

    /**
     * @brief This methods is called by the mesh before displaying the surface.
     * Depending on the implementation it can perform different actions
     */
    virtual void bind(Renderer &renderer) = 0;
    
    virtual ~ISurface() = default;
};


} // namespace los
