#pragma once

#include "glm/glm.hpp"
#include "glad/glad.h"
#include <memory>
#include <map>

using vec3 = glm::vec3;
namespace los
{

enum eShaderTypes {
    kMonochrome = 0,
    kColored,
    kTextured
};

enum eDrawingModes {
    kFilled = 0,
    kWireFrame
};

class IWindow;
class FileLoader;
class Camera;

class Renderer
{
private:
    IWindow &mWindowRef;
    FileLoader &mFileLoaderRef;

    std::shared_ptr<Camera> mCamera;
    glm::vec4 mBackgroundColor;
    float mLineWidth;
    
    std::map<eShaderTypes, unsigned int> mShaders;

public:
    Renderer(IWindow &window_ref, FileLoader &fileloader_ref);
    ~Renderer();
    
    glm::mat4x4 getProjectionMatrix() const;
    
    void clearScreen();
    void useShader(eShaderTypes type);
    void setDrawingMode(eDrawingModes mode);
    
    inline void setSize(int width, int height) {
        glViewport(0, 0, width, height);
    }

    inline void setCamera(std::shared_ptr<Camera> camera) {
        mCamera = camera;
    }

    inline void setBackgroundColor(const glm::vec4 &background_color) {
        mBackgroundColor = background_color;
        glClearColor(mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
    }

    inline void setLineWidth(float line_width) {
        mLineWidth = line_width;
        glLineWidth(mLineWidth);
    }

    template<typename T>
    bool setUniformofShader(eShaderTypes type, const std::string &name, const T &value) {

    }
};
    
    
} // namespace los
