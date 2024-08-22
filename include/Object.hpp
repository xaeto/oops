#pragma once

#include <filesystem>
#include <glm/glm.hpp>
#include <vector>

namespace Object {
    struct Object {
            std::vector<glm::vec3> verticies;
            std::vector<glm::vec2> uvs;
            std::vector<glm::vec3> normals;
            std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    };

    Object from(const std::string &path);
};
