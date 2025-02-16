# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (los)

# Open GL dependencies
find_package(OpenGL REQUIRED)

set(OPENGL_DEPS
    ${OPENGL_LIBRARY}
    glfw
    X11
    pthread
    Xrandr
    Xi
    dl
)

add_subdirectory(./src/external/glad ${CMAKE_BINARY_DIR}/glad)

# Sources

set(LOS_SRC_FILES
    src/Renderer.cpp
    src/FileLoader.cpp
    src/Camera.cpp    
    src/wrappers/IWindow.hpp
    src/wrappers/glfw/GlfwWindow.cpp
    src/drawables/object/Mesh.cpp
    src/drawables/object/Object.cpp
    src/drawables/object/surfaces/SurfaceTextured.cpp
    src/drawables/object/surfaces/SurfaceMonochrome.cpp
    src/drawables/object/surfaces/SurfaceColored.cpp
    src/drawables/grid/Grid.cpp
)

source_group(los FILES ${LOS_SRC_FILES})

# Lib
add_library(${PROJECT_NAME}
	${LOS_SRC_FILES}
)

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_DEPS}   
    Glad_static
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ./src
    ./src/types
)