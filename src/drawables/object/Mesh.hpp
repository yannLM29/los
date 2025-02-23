#pragma once

#include <memory>
#include <vector>
#include "ShaderTypes.hpp"
#include "drawables/object/surfaces/ISurface.hpp"

namespace los
{

class Mesh
{
public:
    inline static unsigned int sTriangleSize = 3;
    
private:
    std::unique_ptr<ISurface> mSurface;
    unsigned int mVAO;
    unsigned int mVBO;

    unsigned int mNbOfTriangles;

public:
    Mesh(std::unique_ptr<ISurface> surface, const std::vector<float> &data);
    ~Mesh();

    inline unsigned int getVao() const {
        return mVAO;
    }

    /**
     * @return eShaderTypes The shader program needed by the surface of this mesh
     */
    inline eShaderTypes getRequiredShaderType() const {
        if(mSurface) {
            return mSurface->getRequiredShaderType();
        }
        return kNoSurface;
    }

    /**
     * @return Return the number of triangles that are in this mesh
     */
    unsigned int getSize() {
        return mNbOfTriangles;
    }

    /**
     * @brief Bind the surface, this method has to be called every time this mesh is draw
     */
    inline void bindSurface(Renderer &renderer) {
        if(mSurface) {
            mSurface->bind(renderer);
        }
    }
};

} // namespace los
