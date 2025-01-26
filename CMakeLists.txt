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
    src/Renderer.hpp
    src/Renderer.cpp
    src/wrappers/IWindow.hpp
    src/wrappers/FileLoader.hpp
    src/wrappers/FileLoader.cpp    
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