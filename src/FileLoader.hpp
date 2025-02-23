#pragma once

#include <functional>
#include <vector>
#include <cstdint>
#include <string>
#include <memory>

namespace los
{

class Image;

class FileLoader
{
private:
    std::function<std::vector<uint8_t>(const std::string&)> mLoadFile;

public:
    FileLoader(std::function<std::vector<uint8_t>(const std::string&)> loadFileFunction);

    unsigned int loadShaderProgram(const std::string &vertex_path, const std::string &fragment_path);
    std::shared_ptr<Image> loadImage(const std::string &path);

private:
    unsigned int compileShader(const std::string &shader_data, int shader_type);
    unsigned int createShaderProgram(int vertex_shader_id, int fragment_shader_id);
};


} // namespace los
