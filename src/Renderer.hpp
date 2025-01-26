#pragma once

#include "glm/glm.hpp"
#include <memory>

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

public:
    Renderer(IWindow &window_ref, FileLoader &fileloader_ref);
    ~Renderer();
    
    glm::mat4x4 getProjectionMatrix() const;
    
    void clearScreen();
    void useShader(eShaderTypes type);
    void setDrawingMode(eDrawingModes mode);

    template<typename T>
    bool setUniformofCurrentShader(const std::string name, const T &value);
    
    
};
    
    
} // namespace los
