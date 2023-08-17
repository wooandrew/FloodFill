// Engine : graphics.cpp

#include "graphics.hpp"

void Graphics::init(const glm::vec4& color) {

    glad_glEnable(GL_BLEND);
    glad_glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glad_glEnable(GL_DEPTH_TEST);

    SetClearColor(color);
}

void Graphics::shutdown() {

}

void Graphics::SetViewPort(int x, int y, int width, int height) {
    glad_glViewport(x, y, width, height);
}

void Graphics::SetClearColor(const glm::vec4& color) {
    glad_glClearColor(color.r, color.g, color.b, color.a);
}

void Graphics::Clear() {
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::BeginRender() {
    Clear();
}

void Graphics::EndRender(GLFWwindow* window) {
    glfwSwapBuffers(window);
}


