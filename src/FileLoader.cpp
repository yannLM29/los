#include "FileLoader.hpp"
#include "drawables/object/Image.hpp"

#include <glad/glad.h>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <external/stb_image.h>

namespace los
{

FileLoader::FileLoader(std::function<std::vector<uint8_t>(const std::string&)> loadFileFunction)
: mLoadFile(loadFileFunction)
{

}

unsigned int FileLoader::loadShaderProgram(const std::string &vertex_path, const std::string &fragment_path) {
    auto vertex_text = mLoadFile(vertex_path);
    auto vertex_shader = compileShader(std::string(vertex_text.begin(), vertex_text.end()), GL_VERTEX_SHADER);

    auto fragment_text = mLoadFile(fragment_path);
    auto fragment_shader = compileShader(std::string(fragment_text.begin(), fragment_text.end()), GL_FRAGMENT_SHADER);

    return createShaderProgram(vertex_shader, fragment_shader);
}

unsigned int FileLoader::compileShader(const std::string &shader_data, int shader_type) {
    const char *vertex_shader_source = shader_data.c_str();

	unsigned int vertex_shader;
	vertex_shader = glCreateShader(shader_type);    // GL_FRAGMENT_SHADER or GL_VERTEX_SHADER

	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	int success;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if(!success) {
		char info_log[512];
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED " + std::string(info_log));
	}

    return vertex_shader;
}

unsigned int FileLoader::createShaderProgram(int inVertexShaderId, int inFragmentShaderId) {
    unsigned int shader_program;
	shader_program = glCreateProgram();

	glAttachShader(shader_program, inVertexShaderId);
	glAttachShader(shader_program, inFragmentShaderId);
	glLinkProgram(shader_program);

    int success;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if(!success) {
		char info_log[512];
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		throw std::runtime_error("ERROR::SHADER::PROGRAM::LINK_FAILED" + std::string(info_log));
	}

    return shader_program;
}

std::shared_ptr<Image> FileLoader::loadImage(const std::string &path) {
	stbi_set_flip_vertically_on_load(true); 
	 
	int width, height, nbChannels;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nbChannels, 0);

	auto out = std::make_shared<Image>(data, width, height, nbChannels);

	stbi_image_free(data);
	return out;
}

} // namespace los
