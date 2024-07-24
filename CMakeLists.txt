cmake_minimum_required(VERSION 3.1...3.29)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CXX_FLAGS "-Wall")

project(
    oops
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(oops main.cpp)

find_package(OpenGL REQUIRED)
target_link_libraries(oops PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(oops PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
target_link_libraries(oops PRIVATE OpenGL::GL)

find_package(GLEW REQUIRED)
target_link_libraries(oops PRIVATE GLEW::GLEW)

# this is heuristically generated, and may not be correct
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(oops PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(oops PRIVATE glm::glm)

# Or use the header-only version
find_package(glm CONFIG REQUIRED)
target_link_libraries(oops PRIVATE glm::glm-header-only "-framework Cocoa" "-framework OpenGL" "-framework IOKit")
