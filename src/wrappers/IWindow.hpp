#pragma once

#include <functional>

namespace los
{

using ProcAddressCallback = void*(*)(const char *);

class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual bool isOpen() const = 0;
    virtual ProcAddressCallback getProcAdressCallback() = 0;
    
    virtual void update() = 0;
    virtual void setOnResizeCallback(std::function<void(int,int)> callback) = 0;
};
    
} // namespace los
