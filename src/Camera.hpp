#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace los
{

class Camera
{
private:

    // view
    glm::vec3 mCameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 mCameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 mCameraRight;
    glm::vec3 mCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    float mYaw = -90.0f;     // y
    float mPitch = 0;   // x

    // projection
    float mFov = 45.0f;

public:

    inline void setCameraPosition(const glm::vec3 &value) {
        mCameraPos = value;
    }
    
    inline void moveCameraX(float value) {
        mCameraPos = mCameraPos + (mCameraRight * value);
    }

    inline void moveCameraZ(float value) {
        mCameraTarget = mCameraPos - glm::vec3(0.0f, 0.0f, 1.0f);
        mCameraPos = mCameraPos + (mCameraFront * value);
    }

    inline void moveCameraY(float value) {
        mCameraPos = mCameraPos + (glm::vec3(0.0f, 1.0f, 0.0f)  * value);
    }

    inline void turnYaw(float value) {
        mYaw += value;
    }

    inline void turnPitch(float value) {
        mPitch += value;

        if(mPitch > 89.0f)
            mPitch = 89.0f;
        if(mPitch < -89.0f)
            mPitch = -89.0f;
    }

    inline void setFov(float value) {
        mFov = value;
    }

    glm::mat4 getView();
    glm::mat4 getProjection();
};


} // namespace los
