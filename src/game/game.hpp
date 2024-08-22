#pragma once

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Game {
    public:
        Game(int width, int height);
        void init();
        ~Game();
    private:
        int height;
        int width;
        GLFWwindow* window;
};
