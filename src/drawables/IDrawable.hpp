#pragma once

#include <glm/glm.hpp>
namespace los
{

class Renderer;
class IDrawable
{
public:
    /**
     * @brief Draw this object thanks to the renderer
     */
    virtual void draw(Renderer &renderer) = 0;

    /**
     * @return Object world position
     */
    virtual glm::vec3 getPos() const = 0;

    /**
     * @return Object world angle
     */
    virtual glm::vec3 getAngle() const = 0;

    /**
     * @brief Set object position in the world space
     */
    virtual void setPos(const glm::vec3 &position) = 0;

    /**
     * @brief Set object rotation in the world space
     */
    virtual void setAngle(const glm::vec3 &angle) = 0;

    /**
     * @brief Set object position in the world space by adding move_vector to its current position
     */
    virtual void move(const glm::vec3 &move_vector) = 0;

    /**
     * @brief Set object rotation in the world space by adding move_rotation to its current angle
     */
    virtual void rotate(const glm::vec3 &move_rotation) = 0;

    /**
     * @return The transformation matrix of this made with the coordinates and the angles of this
     */
    virtual glm::mat4 getTransformationMatrix() const = 0;

    virtual ~IDrawable() = default;
};
    
} // namespace los
