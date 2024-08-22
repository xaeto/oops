#pragma once
#include <glm/glm.hpp>

class Camera {
    public:
        Camera();
        void update(float dt);
        // void handleEvent(Event e);
    private:
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 viewProjectionMatrix;

        glm::vec3 position {0.0f, 0.0f, 0.0f};
        float rotation = 0.0f;
};
