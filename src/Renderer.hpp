#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <memory>
#include <map>
#include <string>
#include <iostream>

#include "ShaderTypes.hpp"

using vec3 = glm::vec3;
namespace los
{

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

    inline static const glm::mat4x4 sDefaultProjection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    inline static const glm::mat4x4 sDefaultView = glm::mat4x4(1);

public:
    Renderer(IWindow &window_ref, FileLoader &fileloader_ref);
    ~Renderer();
    
    glm::mat4x4 getProjectionMatrix() const;
    glm::mat4x4 getViewMatrix() const;
    
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

    int getUniformOfShader(eShaderTypes type, const std::string &name) {
        auto location = glGetUniformLocation(mShaders[type], name.c_str());
        if(location < 0) {
            std::cerr << "Renderer can't find " << name << "\n";
        }
        return location;
    }
};
    
    
} // namespace los
