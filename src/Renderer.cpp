#include "Renderer.hpp"
#include "Camera.hpp"
#include "FileLoader.hpp"
#include "wrappers/IWindow.hpp"
#include "drawables/grid/Grid.hpp"

#include <stdexcept>

namespace los
{

Renderer::Renderer(IWindow &window_ref, FileLoader &fileloader_ref)
: mWindowRef(window_ref)
, mFileLoaderRef(fileloader_ref)
{
    auto proc_addr_cb = mWindowRef.getProcAdressCallback();
    if(proc_addr_cb) {
        if (!gladLoadGLLoader((GLADloadproc)proc_addr_cb)) {
            throw std::runtime_error("Failed to initialize GLAD");
        } 
    } else {
        if (!gladLoadGL()) {
            throw std::runtime_error("Failed to initialize GLAD without proc address cb");
        }
    }
      

	glViewport(0, 0, GLsizei(mWindowRef.getWidth()), GLsizei(mWindowRef.getHeight()));
    mWindowRef.setOnResizeCallback([this](int w, int h){
        this->setSize(w,h);
    });

    mShaders[kNoSurface] = mFileLoaderRef.loadShaderProgram("data/shaders/basic-vertex.glsl", "data/shaders/gray-fragment.glsl");
    mShaders[kMonochrome] = mFileLoaderRef.loadShaderProgram("data/shaders/basic-vertex.glsl", "data/shaders/monochrome-fragment.glsl");
    mShaders[kColored] = mFileLoaderRef.loadShaderProgram("data/shaders/color-vertex.glsl", "data/shaders/color-fragment.glsl");
    mShaders[kTextured] = mFileLoaderRef.loadShaderProgram("data/shaders/texture-vertex.glsl", "data/shaders/texture-fragment.glsl");
    mShaders[kGrid] = mFileLoaderRef.loadShaderProgram("data/shaders/grid-vertex.glsl", "data/shaders/grid-fragment.glsl");

    mCamera = nullptr;
	
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setBackgroundColor(sDefaultBackgroundColor);
    setLineWidth(1.0f);

}

Renderer::~Renderer() {

}

void Renderer::setGrid(std::unique_ptr<Grid> grid) {
    mGrid = std::move(grid);
}

glm::mat4x4 Renderer::getProjectionMatrix() const {
    if(mCamera) {
        return mCamera->getProjection();
    }
    return sDefaultProjection;
}

glm::mat4x4 Renderer::getViewMatrix() const {
    if(mCamera) {
        return mCamera->getView();
    }
    return sDefaultView;
}

void Renderer::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(mGrid && mCamera) {
        auto cam = mCamera->getPosition();
        mGrid->updateGridPosition(cam);
        mGrid->draw(*this);
    }
}

void Renderer::useShader(eShaderTypes type) {
    auto program = mShaders.find(type);
    if(program == mShaders.cend()) {
        throw std::logic_error("eShaderTypes and renderer shader table does not correspond");
    }
    glUseProgram(program->second);
}

void Renderer::setDrawingMode(eDrawingModes mode) {
    static const std::map<eDrawingModes, unsigned int> lookup = {
        {kWireFrame, GL_LINE},
        {kFilled, GL_FILL},
    };

    auto drawing_mode = lookup.find(mode);
    if(drawing_mode == lookup.cend()) {
        throw std::logic_error("eDrawingModes and renderer drawing modes table does not correspond");
    }
    glPolygonMode(GL_FRONT_AND_BACK, drawing_mode->second);
}

} // namespace los
