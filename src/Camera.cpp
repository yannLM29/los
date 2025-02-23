#include "Camera.hpp"

namespace los
{

glm::mat4 Camera::getView() {
    mCameraFront.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mCameraFront.y = sin(glm::radians(mPitch));
    mCameraFront.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

    mCameraTarget = mCameraPos + mCameraFront;
    glm::vec3 cameraDirection = glm::normalize(mCameraPos - mCameraTarget);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    mCameraRight = glm::normalize(glm::cross(up, cameraDirection));

    glm::vec3 cameraUp = glm::cross(cameraDirection, mCameraRight);

    return glm::lookAt(mCameraPos, mCameraTarget, cameraUp);
}

glm::mat4 Camera::getProjection() {
    return glm::perspective(glm::radians(mFov), 800.0f / 600.0f, 0.1f, 100.0f);
}

} // namespace los

