// Engine : camera.hpp

#pragma once

#ifndef ENGINE_GRAPHICS_CAMERA_CHPP
#define ENGINE_GRAPHICS_CAMERA_CHPP

#include <GLM/glm.hpp>

class Camera {

public:

    Camera() = delete;
    Camera(const glm::mat4& _ProjectionMat);

    const glm::mat4& GetProjectionMatrix() const;
    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetViewProjectionMatrix() const;

private:

    glm::mat4 ProjectionMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ViewProjectionMatrix;
};

#endif // !ENGINE_GRAPHICS_CAMERA_CHPP
