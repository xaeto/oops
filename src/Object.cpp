#include "../include/Object.hpp"
#include "glm/glm.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

Object::Object Object::from(const std::string &path) {
    FILE * file = fopen(path.c_str(), "r");
    if(file == NULL){
        printf("Impossible to open the file !\n");
        return Object();
    }

    Object obj{};

    while(1){
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            obj.verticies.push_back(vertex);
        } else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            obj.uvs.push_back(uv);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            obj.normals.push_back(normal);
        } else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vertexIndex[0],
                    &uvIndex[0],
                    &normalIndex[0],
                    &vertexIndex[1],
                    &uvIndex[1],
                    &normalIndex[1],
                    &vertexIndex[2],
                    &uvIndex[2],
                    &normalIndex[2]
                    );

            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return Object();
            }

            obj.vertexIndices.push_back(vertexIndex[0]);
            obj.vertexIndices.push_back(vertexIndex[1]);
            obj.vertexIndices.push_back(vertexIndex[2]);
            obj.uvIndices    .push_back(uvIndex[0]);
            obj.uvIndices    .push_back(uvIndex[1]);
            obj.uvIndices    .push_back(uvIndex[2]);
            obj.normalIndices.push_back(normalIndex[0]);
            obj.normalIndices.push_back(normalIndex[1]);
            obj.normalIndices.push_back(normalIndex[2]);
        }

    }

    // For each vertex of each triangle
    for(unsigned int i = 0; i < obj.vertexIndices.size(); i++){
        unsigned int vertexIndex = obj.vertexIndices[i];
        glm::vec3 vertex = obj.verticies[ vertexIndex-1 ];
        obj.verticies.push_back(vertex);
    }

    return obj;
}
