#pragma once

#include <glm/glm.hpp>
namespace los
{

class Renderer;
class IDrawable
{
public:
    virtual void draw(Renderer &renderer) = 0;
    virtual glm::vec3 getPos() = 0;
    virtual glm::vec3 getAngle() = 0;
    virtual void setPos(const glm::vec3 &position) = 0;
    virtual void setAngle(const glm::vec3 &angle) = 0;
    virtual ~IDrawable() = default;
};
    
} // namespace los
