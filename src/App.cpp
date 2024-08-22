#include <iostream>

#include "App.hpp"
#include "Shader.hpp"
#include "Object.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <vector>

App::App(int width, int height) : width{width}, height{height} {
}

void App::run(){
    std::cout << "DEBUG" << std::endl;
    if(!glfwInit())
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return;
    }

    // opengl settings
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (NULL == window) {
        fprintf( stderr, "Failed to created GLFWwindow\n" );
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    glewInit();

    GLuint programId = glCreateProgram();
    std::cout << programId << std::endl;

    Shader::Shader defaultShader = Shader::from("shader");

    std::cout << defaultShader.fragmentShaderId << std::endl;
    std::cout << defaultShader.vertexShaderId << std::endl;

    glAttachShader(programId, defaultShader.vertexShaderId);
    glAttachShader(programId, defaultShader.fragmentShaderId);

    glLinkProgram(programId);

    Object::Object cube = Object::from("./assets/cube.obj");

    do{
        glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );              // background color
        glBufferData(GL_ARRAY_BUFFER, cube.verticies.size() * sizeof(glm::vec3), &cube.verticies[0], GL_STATIC_DRAW);
        glUseProgram(programId);
        this->scene->render(1.0f);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );
}

void App::init() {}
