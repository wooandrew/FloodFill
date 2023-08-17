// Engine : graphics.hpp

#pragma once

#ifndef ENGINE_GRAPHICS_GRAPHICS_CHPP
#define ENGINE_GRAPHICS_GRAPHICS_CHPP

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/vec4.hpp>

class Graphics {

public:

    Graphics() = delete;
    
    static void init(const glm::vec4& color = glm::vec4(0));
    static void shutdown();

    static void SetViewPort(int x, int y, int width, int height);
    static void SetClearColor(const glm::vec4& color);
    static void Clear();

    static void BeginRender();
    static void EndRender(GLFWwindow* window);
};

#endif // !ENGINE_GRAPHICS_GRAPHICS_CHPP
