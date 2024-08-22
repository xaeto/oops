#pragma once

#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cassert>
#include <fstream>

#include <sstream>

namespace Shader {
    struct Shader {
        GLuint fragmentShaderId, vertexShaderId;
    };

    GLuint from(std::__fs::filesystem::path file, GLint type);
    Shader from(std::__fs::filesystem::path file);
};
