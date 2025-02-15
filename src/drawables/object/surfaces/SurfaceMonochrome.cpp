#include "drawables/object/surfaces/SurfaceMonochrome.hpp"
#include "Renderer.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace los
{

SurfaceMonochrome::SurfaceMonochrome(const glm::vec3 &color) : mColor(color) {

}

void SurfaceMonochrome::bind(Renderer &renderer) {
    auto color_loc = renderer.getUniformOfShader(eShaderTypes::kMonochrome, "color");
    glUniform3fv(color_loc, 1, glm::value_ptr(mColor));
}

} // namespace los
