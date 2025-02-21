#pragma once

#include "drawables/IDrawable.hpp"
#include "ShaderTypes.hpp"

#include <vector>
#include <iostream>

namespace los
{
    
class Grid : public IDrawable
{
private:
    unsigned int mVAO;
    unsigned int mVBO;

    float mStep;
    float mWidth;
    float mHeight;
    float mSnappingStep;

    glm::vec3 mPosition;
    glm::vec3 mAngle;
    glm::vec3 mGridColor;

    unsigned int mNbOfLines; 

    inline static const eShaderTypes sShaderType = eShaderTypes::kGrid;
    inline static const glm::vec3 sGridColor = glm::vec3(0.5f, 0.5f, 0.5f);

public:
    Grid(float w, float h, float step, float snapping_step);
    ~Grid();

    glm::vec3 getPos() const override {
        return mPosition;
    }

    glm::vec3 getAngle() const override {
        return mAngle;
    }

    void setPos(const glm::vec3 &position) override {
        mPosition = position;
    }

    void setAngle(const glm::vec3 &angle) override {
        mAngle = glm::mod(angle, 360.0f);
    }

    void move(const glm::vec3 &move_vector) override {
        setPos(mPosition+move_vector);
    }

    void rotate(const glm::vec3 &rotation_vector) override {
        setAngle(mAngle + rotation_vector);
    }

    void draw(Renderer &renderer) override;

    glm::mat4 getTransformationMatrix() const override;
    void updateGridPosition(const glm::vec3 &camera_position);
};

std::vector<glm::vec3> createGridData(float inStep, float inWidth, float inHeight);

} // namespace los
