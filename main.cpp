#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <cmath>

#include <algorithm>
#include <memory>
#include "include/App.hpp"

#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

int main(){
    std::unique_ptr<App> app = std::make_unique<App>(1024, 768);
    app->run();

    return 0;
}
