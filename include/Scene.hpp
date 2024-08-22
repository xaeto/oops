#pragma once

#include <memory>
#include "Camera.hpp"
#include "CameraController.hpp"

class Scene {
    public:
        Scene();
        void render(float dt);
    private:
        std::unique_ptr<CameraController> cameraController;
};
