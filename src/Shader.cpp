#include "../include/Shader.hpp"

GLuint Shader::from(std::__fs::filesystem::path path, GLint type){
    assert(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);
    GLuint shaderId = glCreateShader(type);

    std::ifstream stream (path, std::ios::in);
    if(!stream.is_open()){
        return GL_FALSE;
    }

    std::stringstream ss;
    ss << stream.rdbuf();

    std::string src = ss.str();
    const char *src_start = &src[0];

    glShaderSource(shaderId, 1, &src_start, NULL);
    glCompileShader(shaderId);

    GLint result = GL_FALSE;
    int log_length = 0;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &log_length);

    if(log_length > 0){
        return GL_FALSE;
    }

    return shaderId;
}

Shader::Shader Shader::from(std::__fs::filesystem::path path){
    return Shader {
        .fragmentShaderId = from(path, GL_FRAGMENT_SHADER),
        .vertexShaderId = from(path, GL_VERTEX_SHADER)
    };
}
