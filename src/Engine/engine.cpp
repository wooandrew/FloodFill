// FloodFill : engine.hpp

#include "engine.hpp"

#include <iostream>

#include "Inputs/keyboard.hpp"
#include "Inputs/mouse.hpp"

Engine::Engine(std::string windowTitle, int windowWidth, int windowHeight) {

    WindowTitle = windowTitle;

    std::pair<int, int> windowDimensions = std::make_pair(windowWidth, windowHeight);
    WindowDimensions = std::make_shared<std::pair<int, int>>(windowDimensions);
}

Engine::~Engine() {
    glfwDestroyWindow(Window);
}

int Engine::init() {

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "glfw init failed." << std::endl;
        return -1;
    }

    // Create OpenGL Window
    Window = glfwCreateWindow(WindowDimensions->first, WindowDimensions->second,
        WindowTitle.c_str(), NULL, NULL);
    if (!Window) {
        std::cerr << "glfwCreateWindow failed." << std::endl;
        glfwTerminate();
        return -2;
    }

    // Create Window Context
    glfwMakeContextCurrent(Window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "gladLoadGLLoader failed." << std::endl;
        return -3;
    }

    int width;
    int height;

    glfwGetFramebufferSize(Window, &width, &height);
    glfwSwapInterval(1);

    // Window Setup
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int xPos = (mode->width - WindowDimensions->first) / 2;
    int yPos = (mode->height - WindowDimensions->second) / 2;
    glfwSetWindowPos(Window, xPos, yPos);

    // Input Callback
    glfwSetKeyCallback(Window, Keyboard::KeyCallback);
    
    glfwSetCursorPosCallback(Window, Mouse::PositionCallback);
    glfwSetMouseButtonCallback(Window, Mouse::ButtonCallback);

    glfwSetWindowSizeLimits(Window, WindowDimensions->first, WindowDimensions->second,
        WindowDimensions->first, WindowDimensions->second);

    return 0;
}

void Engine::BeginRender() const {
    glad_glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glad_glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::Update() const {
    glfwPollEvents();
}

void Engine::EndRender() const {
    glfwSwapBuffers(Window);
}

GLFWwindow* Engine::GetWindow() {
    return Window;
}
