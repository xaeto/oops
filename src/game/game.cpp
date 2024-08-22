#include "game.hpp"
#include <iostream>
#include <memory>

Game::Game(int width, int height) {
    this->width = width;
    this->height = height;
}

Game::~Game() {
    free(window);
}

void Game::init(){
    if (!glfwInit()){
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    this->window = std::move(glfwCreateWindow( this->width, this->height, "Tutorial 01", NULL, NULL));
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return;
    }
}
