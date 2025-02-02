#include "drawables/object/Object.hpp"
#include "Renderer.hpp"
#include "drawables/object/Mesh.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace los
{
    
Object::Object(std::shared_ptr<Mesh> mesh)
: mMesh(mesh)
{

}

Object::~Object() {

}

void Object::draw(Renderer &renderer) {
    if(!mMesh) {
        return;
    }

    renderer.useShader(mMesh->getRequiredShaderType());
    glBindVertexArray(mMesh->getVao());

    // transformations 
    // gestion de la couleur mColor
    auto proj_loc = renderer.getUniformOfShader(mMesh->getRequiredShaderType(), "projection");
    auto proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));

    auto view_loc = renderer.getUniformOfShader(mMesh->getRequiredShaderType(), "view");
    glm::mat4 view(1);
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

    auto model_loc = renderer.getUniformOfShader(mMesh->getRequiredShaderType(), "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(getTransformationMatrix()));

    glDrawArrays(GL_TRIANGLES, 0, mMesh->getSize());

}

glm::mat4 Object::getTransformationMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(mScale.x, mScale.y, mScale.z));
    model = glm::translate(model, glm::vec3(mPosition.x, mPosition.y, mPosition.z));
    model = glm::rotate(model, glm::radians(mRotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); 
    model = glm::rotate(model, glm::radians(mRotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); 
    model = glm::rotate(model, glm::radians(mRotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); 

    return model;
}

} // namespace los
