#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Scene.hpp"

class App {
    public:
        App(const int width, const int height);
        void run();
        void init();
    private:
        int width = 1024, height = 768;
        GLFWwindow *window;
        std::unique_ptr<Scene> scene;
};
