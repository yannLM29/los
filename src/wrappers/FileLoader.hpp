#pragma once

#include <functional>
#include <vector>
#include <cstdint>
#include <string>
#include <memory>

namespace los
{

class FileLoader
{
private:
    std::function<std::vector<uint8_t>(const std::string&)> mLoadFile;
    
public:
    FileLoader(std::function<std::vector<uint8_t>(const std::string&)> loadFileFunction);

    unsigned int LoadShaderProgram(const std::string &vertex_path, const std::string &fragment_path);

private:
    unsigned int CompileShader(const std::string &shader_data, int shader_type);
    unsigned int CreateShaderProgram(int vertex_shader_id, int fragment_shader_id);
};


} // namespace los
