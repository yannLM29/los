#pragma once

#include "wrappers/IWindow.hpp"
#include "GLFW/glfw3.h"
#include <string>
#include <unordered_map>

namespace los
{

class GlfwWindow : public IWindow
{
private:
    // System to pass from C style function pointer to class member std::function
    static void onResizeStaticCallback(GLFWwindow *window, int width, int height) {
        auto current_window = sGlfwWindows.find(window);
        if(current_window != sGlfwWindows.cend()) {
            current_window->second->mOnResizeCallback(width, height);
        }
    }
    inline static std::unordered_map<GLFWwindow*, GlfwWindow*> sGlfwWindows = {};


    // Attributes
    GLFWwindow *mWindow;
    std::function<void(int,int)> mOnResizeCallback;

public:
    GlfwWindow(int width, int height, const std::string &name);
    ~GlfwWindow();

    int getWidth() const override;
    int getHeight() const override;
    bool isOpen() const override;
    ProcAddressCallback getProcAdressCallback() override;
    
    void update() override;
    void setOnResizeCallback(std::function<void(int,int)> callback) override {
        mOnResizeCallback = callback;
        
    }

};


} // namespace los
