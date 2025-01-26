#include "Renderer.hpp"
#include "FileLoader.hpp"
#include "wrappers/IWindow.hpp"
#include <stdexcept>

namespace los
{

Renderer::Renderer(IWindow &window_ref, FileLoader &fileloader_ref)
: mWindowRef(window_ref)
, mFileLoaderRef(fileloader_ref)
{
    if (!gladLoadGLLoader((GLADloadproc)mWindowRef.getProcAdressCallback())) {
		throw std::runtime_error("Failed to initialize GLAD");
	}   

	glViewport(0, 0, GLsizei(mWindowRef.getWidth()), GLsizei(mWindowRef.getHeight()));
    mWindowRef.setOnResizeCallback([this](int w, int h){
        this->setSize(w,h);
    });

    // mShaders[kMonochrome] = mFileLoaderRef.LoadShaderProgram("data/shaders/", "data/shaders/");
    // mShaders[kColored] = mFileLoaderRef.LoadShaderProgram("data/shaders/", "data/shaders/");
    // mShaders[kTextured] = mFileLoaderRef.LoadShaderProgram("data/shaders/", "data/shaders/");

    mCamera = nullptr;
	
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setBackgroundColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    setLineWidth(1.0f);

}

Renderer::~Renderer() {

}

glm::mat4x4 Renderer::getProjectionMatrix() const {
    if(mCamera) {

    }
    return glm::mat4x4(1);
}

void Renderer::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
