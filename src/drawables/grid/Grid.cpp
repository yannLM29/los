#include "drawables/grid/Grid.hpp"
#include "Renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace los
{
Grid::Grid(float w, float h, float step, float snapping_step)
: mStep(step)
, mWidth(w)
, mHeight(h)
, mSnappingStep(snapping_step)
, mPosition(0.0f, 0.0f, 0.0f)
, mAngle(0.0f, 0.0f, 0.0f)
, mGridColor(0.8f, 0.8f, 0.8f)
{
    glGenVertexArrays(1, &mVAO);
    if(mVAO == 0) {
        throw std::runtime_error("Mesh failed to create VAO");
    }

    glGenBuffers(1, &mVBO);
    if(mVBO == 0) {
        throw std::runtime_error("Mesh failed to create VBO");
    }

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    auto grid_data = createGridData(mStep, mWidth, mHeight);

    mNbOfLines = grid_data.size();

    glBufferData(GL_ARRAY_BUFFER, grid_data.size() * 3 * sizeof(float), grid_data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

Grid::~Grid() {
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}

void Grid::draw(Renderer &renderer) {
    renderer.useShader(sShaderType);

    // bindings
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    
    // transformations 
    auto proj_loc = renderer.getUniformOfShader(sShaderType, "projection");
    auto proj = renderer.getProjectionMatrix();
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));

    auto view_loc = renderer.getUniformOfShader(sShaderType, "view");
    auto view = renderer.getViewMatrix();
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

    auto model_loc = renderer.getUniformOfShader(sShaderType, "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(getTransformationMatrix()));

    glDrawArrays(GL_LINES, 0, mNbOfLines);
}

glm::mat4 Grid::getTransformationMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(mPosition.x, mPosition.y, mPosition.z));
    model = glm::rotate(model, glm::radians(mAngle.x), glm::vec3(1.0f, 0.0f, 0.0f)); 
    model = glm::rotate(model, glm::radians(mAngle.y), glm::vec3(0.0f, 1.0f, 0.0f)); 
    model = glm::rotate(model, glm::radians(mAngle.z), glm::vec3(0.0f, 0.0f, 1.0f)); 

    return model;
}

void Grid::updateGridPosition(const glm::vec3 &camera_position) {
    auto new_grid_position = glm::floor(camera_position / mSnappingStep) * mSnappingStep; 
    setPos(new_grid_position);
}   

std::vector<glm::vec3> createGridData(float step, float width, float height) {
    std::vector<vec3> out = {};

    float x_start = -width / 2;
    float z_start = -height / 2;
    float x_end = width / 2;
    float z_end = height / 2;

    int number_of_x_lines = width / step;
    for (int i = 0; i < number_of_x_lines; i++) {
        float x_line_pos = x_start + i * step;
        out.emplace_back(vec3{x_line_pos, 0.f, z_start});
        out.emplace_back(vec3{x_line_pos, 0.f, z_end});
    }
    
    int number_of_z_lines = height / step;
    for (int i = 0; i < number_of_z_lines; i++) {
        out.emplace_back(vec3{x_start, 0.f, z_start + i * step});
        out.emplace_back(vec3{x_end, 0.f, z_start + i * step});
    }

    out.emplace_back(vec3{0.0f, -10.0f, 0.0f});
    out.emplace_back(vec3{0.0f, 10.0f, 0.0f});

    return out;
}

} // namespace los