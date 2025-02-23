#include "wrappers/glfw/GlfwWindow.hpp"
#include <stdexcept>

namespace los
{

GlfwWindow::GlfwWindow(int width, int height, const std::string &name) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (mWindow == NULL) {
        glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

    sGlfwWindows[mWindow] = this;
    glfwSetFramebufferSizeCallback(mWindow, onResizeStaticCallback);

    glfwMakeContextCurrent(mWindow);
}

GlfwWindow::~GlfwWindow() {
    sGlfwWindows.erase(mWindow);
}

int GlfwWindow::getWidth() const {
    int width = 0, height = 0;
    glfwGetWindowSize(mWindow, &width, &height);
    return width;
}

int GlfwWindow::getHeight() const {
    int width = 0, height = 0;
    glfwGetWindowSize(mWindow, &width, &height);
    return height;
}

bool GlfwWindow::isOpen() const {
    return !glfwWindowShouldClose(mWindow);
}

ProcAddressCallback GlfwWindow::getProcAdressCallback() {
    return reinterpret_cast<ProcAddressCallback>(glfwGetProcAddress);
}

void GlfwWindow::update() {
    
    if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(mWindow, true);
    }

    glfwPollEvents();
    glfwSwapBuffers(mWindow);
}

} // namespace los
