#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "drawables/IDrawable.hpp"

namespace los
{

class Renderer;
class Mesh;

class Object : public IDrawable
{
private:
    unsigned int mVBO;
    std::shared_ptr<Mesh> mMesh;

    glm::vec3 mPosition = {0.0f, 0.0f, 0.0f};
    glm::vec3 mRotation = {0.0f, 0.0f, 0.0f};
    glm::vec3 mScale = {1.0f, 1.0f, 1.0f};
    glm::vec4 mColor = {0.0f, 0.0f, 0.0f, 0.0f};

public:
    Object(std::shared_ptr<Mesh> mesh);
    ~Object();
    
    void draw(Renderer &renderer) override;

    glm::vec3 getPos() const override {
        return mPosition;
    }

    glm::vec3 getAngle() const override {
        return mRotation;
    }

    void setPos(const glm::vec3 &position) override {
        mPosition = position;
    }
    void setAngle(const glm::vec3 &angle) override {
        mRotation = angle;
    }

    glm::mat4 getTransformationMatrix() const;
};

} // namespace los
