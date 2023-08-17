// Engine : mouse.cpp

#include "mouse.hpp"

double Mouse::x = 0;
double Mouse::y = 0;

bool Mouse::Buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::ButtonsDown[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::ButtonsUp[GLFW_MOUSE_BUTTON_LAST] = { 0 };

void Mouse::PositionCallback(GLFWwindow* window, double _x, double _y) {

    int width;
    int height;

    glfwGetFramebufferSize(window, &width, &height);

    x = _x;
    y = height - _y;
}

void Mouse::ButtonCallback(GLFWwindow* window, int button, int action, int modifiers) {

    if (button < 0)
        return;

    if ((action != GLFW_RELEASE) && (!Buttons[button])) {
        ButtonsDown[button] = true;
        ButtonsUp[button] = false;
    }

    if ((action == GLFW_RELEASE) && (Buttons[button])) {
        ButtonsDown[button] = false;
        ButtonsUp[button] = true;
    }

    Buttons[button] = action != GLFW_RELEASE;
}

bool Mouse::ButtonDown(int button) {

    bool buttonsDown = ButtonsDown[button];
    ButtonsDown[button] = false;

    return buttonsDown;
}

bool Mouse::ButtonUp(int button) {

    bool buttonUp = ButtonsUp[button];
    ButtonsUp[button] = false;

    return buttonUp;
}

bool Mouse::ButtonIsPressed(int button) {
    return Buttons[button];
}
