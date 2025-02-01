#pragma once

#include <memory>
#include <vector>
#include "ShaderTypes.hpp"
#include "drawables/object/ISurface.hpp"

namespace los
{

class Mesh
{
private:
    std::unique_ptr<ISurface> mSurface;
    unsigned int mVAO;
    unsigned int mVBO;

    unsigned int mNbOfTriangles;

    inline static unsigned int sTriangleSize = 3;

public:
    Mesh(std::unique_ptr<ISurface> surface, const std::vector<float> &data);
    ~Mesh();

    inline unsigned int getVao() const {
        return mVAO;
    }

    inline eShaderTypes getRequiredShaderType() const {
        if(mSurface) {
            return mSurface->getRequiredShaderType();
        }
        return kNoSurface;
    }
};

} // namespace los
