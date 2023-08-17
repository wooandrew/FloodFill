// Engine : camera.cpp

#include "camera.hpp"

Camera::Camera(const glm::mat4& _ProjectionMat) {

    ViewMatrix = glm::mat4(1.f);
    ProjectionMatrix = _ProjectionMat;

    ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
}

const glm::mat4& Camera::GetProjectionMatrix() const {
    return ProjectionMatrix;
}

const glm::mat4& Camera::GetViewMatrix() const {
    return ViewMatrix;
}

const glm::mat4& Camera::GetViewProjectionMatrix() const {
    return ViewProjectionMatrix;
}
