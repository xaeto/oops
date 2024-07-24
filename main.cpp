#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

GLuint loadShader(const std::string &path, GLint type){
    GLuint shaderId = glCreateShader(type);
    std::ifstream stream (path, std::ios::in);

    if(!stream.is_open()){
        std::cerr << "Error while reading Shader" << std::endl;
        return 0;
    }

    std::stringstream ss;
    ss << stream.rdbuf();
    std::string src = ss.str();
    stream.close();

    const char *src_start = src.c_str();

    glShaderSource(shaderId, 1, &src_start , NULL);
    glCompileShader(shaderId);

    GLint result = GL_FALSE;
    int logLength = 0;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

    if ( logLength > 0 ){
        std::vector<char> errorMessage(logLength+1);
        glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]);
        printf("%s\n", &errorMessage[0]);
    }

    std::cout << shaderId << std::endl;
    return shaderId;
}

GLuint LoadShaders(const std::string &vertex_file_path,const std::string &fragment_file_path){
    GLint fragmentShaderId = loadShader(fragment_file_path, GL_FRAGMENT_SHADER);
    GLint vertexShaderId = loadShader(vertex_file_path, GL_VERTEX_SHADER);

    // Link the program
    printf("Linking program\n");
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);

    GLint result = GL_FALSE;
    int logLength = 0;
    // Check the program
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
    if ( logLength > 0 ){
        std::vector<char> errorMessage(logLength+1);
        glGetProgramInfoLog(programId, logLength, NULL, &errorMessage[0]);
        printf("%s\n", &errorMessage[0]);
    }

    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

int main(){
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    glewInit();
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    GLfloat g_color_buffer_data[108] = {};

    for(int v = 0; v < 12*3; v++){
        g_color_buffer_data[3*v+0] = sin(g_vertex_buffer_data[3*v + 0]);
        g_color_buffer_data[3*v+1] = sin(g_vertex_buffer_data[3*v + 1]);
        g_color_buffer_data[3*v+2] = sin(g_vertex_buffer_data[3*v + 2]);
    }

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    GLuint programId = LoadShaders("../shader.vsh", "../shader.fsh");

    std::cout << programId << std::endl;
    glUseProgram(programId);

    int width = 1024;
    int height = 768;

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float)height, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(
            glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
            );

    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

    GLuint MatrixID = glGetUniformLocation(programId, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                nullptr            // array buffer offset
                );
        glDrawArrays(GL_TRIANGLES, 0, 12*3);
        glDisableVertexAttribArray(0);

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                3,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
                );
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();


    }
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );

    glDeleteProgram(programId);
}
