#pragma once

#ifndef ENGINE_CHPP
#define ENGINE_CHPP

#include <string>
#include <memory>
#include <utility>

#include <GLFW/glfw3.h>

class Engine {

public:
    
    Engine(std::string windowTitle = "FloodFill", int windowWidth = 1000, int windowHeight = 618);

    int init();

    void BeginRender() const;
    void Update() const;
    void EndRender() const;

    GLFWwindow* GetWindow();

private:

    GLFWwindow* Window;
    std::string WindowTitle;
    std::shared_ptr<std::pair<int, int>> WindowDimensions;
};

#endif
